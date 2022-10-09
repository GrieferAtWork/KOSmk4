/* Copyright (c) 2019-2022 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_APPS_DMESG_C
#define GUARD_KERNEL_SRC_DEBUGGER_APPS_DMESG_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define _KOS_SOURCE 1
#define SYSLOG_LINEMAX CONFIG_KERNEL_SYSLOG_LINEMAX

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

#include <debugger/debugger.h>
#include <kernel/dmesg.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/mman/execinfo.h>
#include <kernel/panic.h>
#include <sched/group.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/keyboard.h>

#include <alloca.h>
#include <format-printer.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unicode.h>

DECL_BEGIN

PRIVATE ATTR_DBGRODATA char const dbg_dmesg_colors[SYSLOG_LEVEL_COUNT][10] = {
	/* [(unsigned int)SYSLOG_LEVEL_EMERG  ] */ AC_COLOR(ANSITTY_CL_RED, ANSITTY_CL_WHITE),
	/* [(unsigned int)SYSLOG_LEVEL_ALERT  ] */ AC_COLOR(ANSITTY_CL_RED, ANSITTY_CL_WHITE),
	/* [(unsigned int)SYSLOG_LEVEL_CRIT   ] */ AC_COLOR(ANSITTY_CL_RED, ANSITTY_CL_WHITE),
	/* [(unsigned int)SYSLOG_LEVEL_ERR    ] */ AC_FG(ANSITTY_CL_MAROON),
	/* [(unsigned int)SYSLOG_LEVEL_WARNING] */ AC_FG(ANSITTY_CL_YELLOW),
	/* [(unsigned int)SYSLOG_LEVEL_NOTICE ] */ AC_COLOR(ANSITTY_CL_NAVY, ANSITTY_CL_LIGHT_GRAY),
	/* [(unsigned int)SYSLOG_LEVEL_INFO   ] */ AC_COLOR(ANSITTY_CL_AQUA, ANSITTY_CL_DARK_GRAY),
	/* [(unsigned int)SYSLOG_LEVEL_TRACE  ] */ AC_FG(ANSITTY_CL_CYAN),
	/* [(unsigned int)SYSLOG_LEVEL_DEBUG  ] */ AC_FG(ANSITTY_CL_OLIVE),
	/* [(unsigned int)SYSLOG_LEVEL_DEFAULT] */ "",
	/* [(unsigned int)SYSLOG_LEVEL_RAW    ] */ "",
};


struct dbg_dmesg_render_data {
	unsigned int rd_lastpacket;         /* nth-value of the last packet in-cache. */
	unsigned int rd_minpacket;          /* First packet within the scroll area. */
	unsigned int rd_maxpacket;          /* Last packet within the scroll area. */
	unsigned int rd_selected;           /* Index of the currently selected packet. */
	unsigned int rd_scroll_area_height; /* Height of the scroll area (in lines) */
	unsigned int rd_packet_area_height; /* Height of the packet area (in lines) */
};

PRIVATE ATTR_DBGTEXT NONNULL((1, 2)) ssize_t KCALL
dbg_dmesg_count_enum(void *arg, struct syslog_packet *__restrict UNUSED(packet),
                     unsigned int UNUSED(level), unsigned int nth) {
	unsigned int *presult = (unsigned int *)arg;
	if (*presult < nth)
		*presult = nth;
	return 0;
}

PRIVATE ATTR_DBGTEXT NONNULL((1, 2)) ssize_t KCALL
dbg_dmesg_render_enum(void *arg, struct syslog_packet *__restrict packet,
                      unsigned int level, unsigned int nth) {
	struct tm tms;
	struct dbg_dmesg_render_data *data;
	data = (struct dbg_dmesg_render_data *)arg;
	if (nth > data->rd_lastpacket)
		return 0; /* Shouldn't happen... */
	nth = data->rd_lastpacket - nth;
	if (nth >= data->rd_minpacket && nth <= data->rd_maxpacket) {
		/* This one's visible! */
		struct tm tms;
		unsigned int curx, cury, avail;
		char const *reader, *endp;
		gmtime_r(&packet->sp_time, &tms);
		dbg_setcolor(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_BLACK);
		if (nth == data->rd_selected)
			dbg_setbgcolor(ANSITTY_CL_DARK_GRAY);
		cury = nth - data->rd_minpacket;
		curx = (unsigned int)dbg_pprintf(0, cury,
		                                 DBGSTR("%.2u:%.2u:%.2u.%.4" PRIu32 " "),
		                                 tms.tm_hour, tms.tm_min, tms.tm_sec,
		                                 packet->sp_nsec / 100000);
		dbg_print(dbg_dmesg_colors[level]);
		avail = 0;
		if ((dbg_screen_width - 1) > curx)
			avail = (dbg_screen_width - 1) - curx;
		reader = packet->sp_msg;
		endp   = packet->sp_msg + packet->sp_len;
		while (endp > reader && endp[-1] == '\n')
			--endp;
		/* Print truncated packet text. */
		for (;;) {
			char32_t ch;
			if (!avail) {
				if (dbg_screen_width >= 4) {
					/* Truncated */
					dbg_setfgcolor(ANSITTY_CL_LIGHT_GRAY);
					dbg_pprint(dbg_screen_width - 4, cury, DBGSTR("..."));
				}
				break;
			}
			ch = unicode_readutf8_n(&reader, endp);
			if (!ch) {
				/* Ensure that the whole line has proper highlighting. */
				if (nth == data->rd_selected)
					dbg_hline(curx, cury, avail, ' ');
				break;
			}
			dbg_pputuni(curx, cury, ch);
			++curx;
			--avail;
		}
	}
	if (nth == data->rd_selected) {
		u16 real_len;
		gmtime_r(&packet->sp_time, &tms);
		/* Render the contents of this packet in full. */
		real_len = packet->sp_len;
		while (real_len && packet->sp_msg[real_len] == '\n')
			--real_len;
		/* NOTE: Can't use dbg_pprintf(), since that one doesn't wrap around on new-line. */
		dbg_setcur(0, data->rd_scroll_area_height + 1);
		dbg_setcolor(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_BLACK);
		dbg_printf(DBGSTR("%$s"), (size_t)real_len, packet->sp_msg);
		/* Print the packet timestamp within the status bar,
		 * alongside  the   F1:help   information   message. */
		dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
		{
			dbg_pprinter_arg_t printer = DBG_PPRINTER_ARG_INIT(0, (int)dbg_screen_height - 1);
			format_printf(&dbg_pprinter, &printer,
			              DBGSTR("F1:help %.4u-%.2u-%.2uT%.2u:%.2u:%.2u.%.9" PRIu32 "/%u"),
			              tms.tm_year + 1900, tms.tm_mon + 1, tms.tm_mday,
			              tms.tm_hour, tms.tm_min, tms.tm_sec,
			              packet->sp_nsec, packet->sp_tid);
			if (!kernel_poisoned()) {
				/* Include the name of the main executable associated
				 * with  the  process  of  the  packet  writer's tid.
				 *
				 * Of course, there is the race condition where the writer
				 * has since terminated, and a different process has taken
				 * its place, but that could only happen if the system had
				 * to recycle PIDs since then,  and we're already back  to
				 * where we were before in terms of allocated PIDs.
				 *
				 * Admittedly, this could (fairly easily) happen when someone
				 * sets the value  in /proc/sys/kernel/pid_max  too low,  but
				 * in  this case  I want to  point out that  we're within the
				 * debugger here, and any sane person probably wouldn't  want
				 * to make their life pointlessly  harder, so they'd have  to
				 * intentionally lower the pid_max value, at which point they
				 * (at  the very least) should be aware of its possible side-
				 * effects.
				 *
				 * And aside from forcing the kernel to recycle PIDs early on,
				 * the  only other way  is to somehow  keep on allocating PIDs
				 * without causing any writes to  the system log, because  the
				 * dmesg buffer most definitely couldn't hold
				 * `PID_RECYCLE_THRESHOLD_DEFAULT' individual packets  without
				 * having to wrap around and  overwrite earlier ones at  least
				 * once (at which point this whole problem would also go away)
				 */
				REF struct task *sender;
				TRY {
					sender = pidns_lookuptask(&pidns_root,
					                              packet->sp_tid);
				} EXCEPT {
				}
				if (sender) {
					struct mexecinfo *ei;
					ei = &FORMMAN(sender->t_mman, thismman_execinfo);
					if (ei->mei_path && ei->mei_dent) {
						dbg_pprinter_putuni(&printer, ':');
						path_printent(ei->mei_path,
						              ei->mei_dent->fd_name,
						              ei->mei_dent->fd_namelen,
						              &dbg_pprinter, &printer);
					}
					decref_unlikely(sender);
				}
			}
		}
	}
	return 0;
}



/* Render the main dmesg screen.
 * @param: data: Render  data.  Only  `rd_minpacket'  and
 *               `rd_selected' must be set by the caller! */
PRIVATE ATTR_DBGTEXT void KCALL
dbg_dmesg_render(struct dbg_dmesg_render_data *__restrict data) {
	bool must_rerender;
	/* The packet detail area must be large enough  to
	 * fit all the text of a max-length syslog packet. */
	data->rd_packet_area_height = CEILDIV(CONFIG_KERNEL_SYSLOG_LINEMAX, dbg_screen_width);
	/* Need at least 3 additional lines of vertical screen estate. */
	if unlikely(dbg_screen_width < 2 || dbg_screen_height < data->rd_packet_area_height + 3)
		return; /* I can't work like this :( */
	data->rd_scroll_area_height = dbg_screen_height - (data->rd_packet_area_height + 1);
	if (data->rd_minpacket > data->rd_selected)
		data->rd_minpacket = data->rd_selected;
	data->rd_maxpacket = data->rd_minpacket + data->rd_scroll_area_height - 1;
	dbg_beginupdate();
again_render_screen:
	/* Render the screen. */
	dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_BLACK);
	dbg_fillscreen(' ');

	/* Render the status bar background. */
	dbg_setcolor(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_LIGHT_GRAY);
	dbg_hline(0, dbg_screen_height - 1, dbg_screen_width, ' ');

	/* Render the scroll/packet area separator. */
	dbg_setcolor(ANSITTY_CL_DARK_GRAY, ANSITTY_CL_BLACK);
	dbg_hline(0, data->rd_scroll_area_height, dbg_screen_width - 1, 0x2500);
	dbg_pputuni(dbg_screen_width - 1, data->rd_scroll_area_height, 0x2580);

	/* Enumerate and render packets. */
	data->rd_lastpacket = 0;
	dmesg_enum(&dbg_dmesg_count_enum, &data->rd_lastpacket, 0, UINT_MAX);
	dmesg_enum(&dbg_dmesg_render_enum, data, 0, UINT_MAX);

	must_rerender = false;
	/* Check if we must reduce the screen-top value. */
	if (data->rd_lastpacket < data->rd_maxpacket) {
		unsigned int diff;
		diff = data->rd_maxpacket - data->rd_lastpacket;
		/* We've `diff' lines too far down. */
		if (diff > data->rd_minpacket)
			diff = data->rd_minpacket;
		if (diff) {
			data->rd_minpacket -= diff;
			data->rd_maxpacket -= diff;
			must_rerender = true;
		}
	}
	if (data->rd_selected > data->rd_lastpacket) {
		data->rd_selected = data->rd_lastpacket;
		must_rerender     = true;
	}
	if (data->rd_selected > data->rd_maxpacket) {
		unsigned int diff;
		diff = data->rd_selected - data->rd_maxpacket;
		data->rd_minpacket += diff;
		data->rd_maxpacket += diff;
		must_rerender = true;
	}
	if (must_rerender)
		goto again_render_screen;


	/* Render the scroll bar for the scroll area. */
	{
		unsigned int num_packets;
		dbg_setcolor(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_DARK_GRAY);
		dbg_vline(dbg_screen_width - 1, 0, data->rd_scroll_area_height, ' ');
		num_packets = data->rd_lastpacket + 1;
		if (num_packets > data->rd_scroll_area_height) {
			unsigned int scrollbar_top;
			unsigned int scrollbar_height;
			/* scrollbar_height = data->rd_scroll_area_height /
			 *                    (num_packets / data->rd_scroll_area_height); */
			scrollbar_height = (data->rd_scroll_area_height *
			                    data->rd_scroll_area_height) /
			                   num_packets;
			/* scrollbar_top = (data->rd_minpacket / (num_packets - data->rd_scroll_area_height)) *
			 *                 (data->rd_scroll_area_height - scrollbar_height); */
			scrollbar_top = (data->rd_minpacket * (data->rd_scroll_area_height - scrollbar_height)) /
			                (num_packets - data->rd_scroll_area_height);
			dbg_setcolor(ANSITTY_CL_WHITE, ANSITTY_CL_DARK_GRAY);
			dbg_vline(dbg_screen_width - 1, scrollbar_top,
			          scrollbar_height, 0x2502);
		}
	}
	/* Render the status selection index in the status bar. */
	{
		char buf[lengthof(PRIMAXu "/" PRIMAXu)];
		size_t len;
		len = sprintf(buf, DBGSTR("%u/%u"),
		              data->rd_selected + 1,
		              data->rd_lastpacket + 1);
		dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
		dbg_pprint(dbg_screen_width - len, dbg_screen_height - 1, buf);
	}
	dbg_endupdate(false);
}


PRIVATE ATTR_DBGRODATA char const dm_help[] =
"Esc:          Exit       F1:              Help\n"
"Up/Down:      Navigate   Pg-Up/Down:      Navigate\n"
"Ctrl+Up/Down: Scroll     Ctrl+Pg-Up/Down: First/Last line\n"
"                         Ctrl+Home/End:   Go to top/bottom";

PRIVATE ATTR_DBGTEXT void KCALL dbg_dmesg_main(void) {
	struct dbg_dmesg_render_data data;
	data.rd_minpacket = 0;
	/* Start-out by highlighting the last back in-buffer. */
	data.rd_selected = (unsigned int)-1;
	for (;;) {
		unsigned int key;

		/* Re-draw the screen. */
		dbg_dmesg_render(&data);

		/* Wait for the user to press a key. */
		do {
			key = dbg_getkey();
		} while (key & KEY_FRELEASED);

		/* Act upon whatever key was pressed. */
		switch (key) {

		case KEY_UP:
			if (dbg_isholding_ctrl()) {
				if (data.rd_minpacket) {
					--data.rd_minpacket;
					if (data.rd_selected == data.rd_maxpacket)
						--data.rd_selected;
				}
			} else {
				if (data.rd_selected)
					--data.rd_selected;
			}
			break;

		case KEY_DOWN:
			if (dbg_isholding_ctrl()) {
				if (data.rd_selected == data.rd_minpacket &&
				    data.rd_maxpacket != data.rd_lastpacket)
					++data.rd_selected;
				++data.rd_minpacket;
			} else {
				++data.rd_selected;
			}
			break;

		case KEY_PAGEUP:
			if (dbg_isholding_ctrl()) {
				data.rd_selected = data.rd_minpacket;
			} else {
				if (data.rd_selected >= data.rd_scroll_area_height) {
					data.rd_selected -= data.rd_scroll_area_height;
				} else {
					data.rd_selected = 0;
				}
				if (data.rd_minpacket >= data.rd_scroll_area_height) {
					data.rd_minpacket -= data.rd_scroll_area_height;
				} else {
					data.rd_minpacket = 0;
				}
			}
			break;

		case KEY_PAGEDOWN:
			if (dbg_isholding_ctrl()) {
				data.rd_selected = data.rd_maxpacket;
			} else {
				data.rd_selected += data.rd_scroll_area_height;
				data.rd_minpacket += data.rd_scroll_area_height;
			}
			break;

		case KEY_HOME:
			if (dbg_isholding_ctrl())
				data.rd_selected = 0;
			break;

		case KEY_END:
			if (dbg_isholding_ctrl())
				data.rd_selected = data.rd_lastpacket;
			break;

		case KEY_ESC:
			goto done;

		case KEY_F1:
			dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
			dbg_messagebox(DBGSTR("Help"), dm_help);
			/* Wait until the user presses ESC or F1 */
			do {
				key = dbg_getkey();
			} while (key != KEY_F1 && key != KEY_ESC);
			continue;

		default:
			break;
		}
	}
done:
	;
}



PRIVATE ATTR_DBGTEXT void KCALL dbg_dmesg(void) {
	void *buf;
	bool was_cursor_visible;
	u32 oldcur;

	/* Save terminal settings and display contents. */
	was_cursor_visible = dbg_setcur_visible(false);
	buf      = alloca(dbg_screen_width * dbg_screen_height * dbg_screen_cellsize);
	oldcur   = dbg_getcur();
	dbg_logecho_pushoff();
	dbg_savecolor();
	dbg_getscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);

	dbg_dmesg_main();

	/* Restore display contents and terminal settings. */
	dbg_setscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_loadcolor();
	dbg_logecho_pop();
	dbg_setcur(DBG_GETCUR_X(oldcur), DBG_GETCUR_Y(oldcur));
	dbg_setcur_visible(was_cursor_visible);
}




DBG_COMMAND(dmesg,
            "dmesg\n"
            "\tGraphical mini-application for inspecting the dmesg backlog buffer\n",
            argc, argv) {
	(void)argv;
	if (argc >= 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	dbg_dmesg();
	return 0;
}


DECL_END

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_APPS_DMESG_C */
