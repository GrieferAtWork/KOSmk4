/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_UTIL_C
#define GUARD_KERNEL_SRC_DEBUGGER_UTIL_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _GNU_SOURCE 1 /* strchrnul() */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/io.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>

#include <kos/keyboard.h>

#include <alloca.h>
#include <stdarg.h>
#include <string.h>

DECL_BEGIN

/* Print addr2line optimized for the debugger.
 * Example (of an inlined function):
 * >> c010783a+4   [my_inline_function+8] [bar.c:9]
 * >> c0107828+38  [my_function+26] [bar.c:42]
 * This is similar to `addr2line_printf()', however doesn't include the full source path,
 * and doesn't follow the file(line,col) format, but instead opts for much shorter lines
 * which can then (usually) be displayed in one continuous line, rather than having to be
 * split up into multiple lines.
 * Additionally, this function also highlights output using differing colors. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(VCALL dbg_addr2line_printf)(uintptr_t start_pc, uintptr_t end_pc,
                                    char const *message_format, ...) {
	va_list args;
	va_start(args, message_format);
	dbg_addr2line_vprintf(start_pc, end_pc, message_format, args);
	va_end(args);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL do_dbg_addr2line_vprintf)(struct addr2line_buf const *__restrict ainfo,
                                        uintptr_t module_relative_pc,
                                        uintptr_t start_pc, uintptr_t end_pc,
                                        char const *message_format, va_list args) {
	di_debug_addr2line_t info;
	addr2line_errno_t error;
	error = addr2line(ainfo, module_relative_pc, &info, 0);
	if (error != DEBUG_INFO_ERROR_SUCCESS) {
		dbg_printf(DBGSTR(DF_SETFGCOLOR(DBG_COLOR_WHITE) "%p" DF_DEFFGCOLOR "+"
		                  DF_SETFGCOLOR(DBG_COLOR_WHITE) "%-4Iu" DF_DEFFGCOLOR),
		           start_pc, (size_t)(end_pc - start_pc));
		if (message_format) {
			dbg_print(DBGSTR("[" DF_SETFGCOLOR(DBG_COLOR_WHITE)));
			dbg_vprintf(message_format, args);
			dbg_print(DBGSTR(DF_DEFFGCOLOR "]"));
		}
		dbg_putc('\n');
	} else {
		uintptr_t level = 0;
		u8 color;
		dbg_attr_t attr;
again_printlevel:
		if (!info.al_rawname)
			info.al_rawname = info.al_name;
		if (!info.al_rawname)
			info.al_rawname = (char *)DBGSTR("??" "?");
		color = level < info.al_levelcnt - 1
		        ? DBG_COLOR_AQUA
		        : DBG_COLOR_WHITE;
		attr  = dbg_attr;
		dbg_setfgcolor(color);
		dbg_printf(DBGSTR("%p"), level == 0 ? start_pc : info.al_symstart);
		dbg_attr = attr;
		dbg_putc('+');
		attr = dbg_attr;
		dbg_setfgcolor(color);
		dbg_printf(DBGSTR("%-4Iu"),
		           level == 0 ? (size_t)(end_pc - start_pc)
		                      : (size_t)(info.al_lineend - info.al_linestart));
		dbg_attr = attr;
		dbg_putc('[');
		attr = dbg_attr;
		dbg_setfgcolor(color);
		dbg_print(info.al_rawname);
		dbg_attr = attr;
		dbg_putc('+');
		attr = dbg_attr;
		dbg_setfgcolor(color);
		dbg_printf(DBGSTR("%Iu"),
		           level == 0 ? (size_t)(start_pc - info.al_symstart)
		                      : (size_t)(info.al_linestart - info.al_symstart));
		dbg_attr = attr;
		dbg_putc(']');
		if (info.al_srcfile) {
			char const *p1, *p2;
			p1 = strrchr(info.al_srcfile, '/');
			p2 = strrchr(info.al_srcfile, '\\');
			if (p1)
				++p1;
			if (p2)
				++p2;
			if (p2 > p1)
				p1 = p2;
			if (!p1)
				p1 = info.al_srcfile;
			dbg_print(" [");
			attr = dbg_attr;
			dbg_setfgcolor(color);
			dbg_print(p1);
			dbg_attr = attr;
			if (info.al_srcline) {
				dbg_putc(':');
				attr = dbg_attr;
				dbg_setfgcolor(color);
				dbg_printf(DBGSTR("%Iu"), info.al_srcline);
				dbg_attr = attr;
				if (info.al_srccol) {
					dbg_putc(':');
					attr = dbg_attr;
					dbg_setfgcolor(color);
					dbg_printf(DBGSTR("%Iu"), info.al_srccol);
					dbg_attr = attr;
				}
			}
			dbg_putc(']');
		}
		if (message_format) {
			dbg_print(DBGSTR(" ["));
			attr = dbg_attr;
			dbg_setfgcolor(color);
#ifndef __i386__
			if (level == info.al_levelcnt - 1) {
				va_list copy;
				va_copy(copy, args);
				dbg_vprintf(message_format, copy);
				va_end(copy);
			} else
#endif
			{
				dbg_vprintf(message_format, args);
			}
			dbg_attr = attr;
			dbg_putc(']');
		}
		dbg_putc('\n');
		if (++level < info.al_levelcnt) {
			/* Print additional levels */
			error = addr2line(ainfo, start_pc, &info, level);
			if (error == DEBUG_INFO_ERROR_SUCCESS)
				goto again_printlevel;
		}
	}
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_addr2line_vprintf)(uintptr_t start_pc, uintptr_t end_pc,
                                     char const *message_format, va_list args) {
	struct addr2line_buf ainfo;
	uintptr_t module_relative_pc;
	module_relative_pc = addr2line_begin(&ainfo, start_pc);
	do_dbg_addr2line_vprintf(&ainfo,
	                         module_relative_pc,
	                         start_pc,
	                         end_pc,
	                         message_format,
	                         args);
	addr2line_end(&ainfo);
}





/* Display a selections menu with a set of `options' (which is a NULL-terminated vector strings)
 * Options are on top of each other, and can be navigated using the arrow keys.
 * @return: * : The index of the selected option, or one of `DBG_MENU_SELECTION_*' */
PUBLIC ATTR_DBGTEXT WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(KCALL dbg_menuex)(char const *__restrict title,
                          char const *const *__restrict options,
                          unsigned int default_option,
                          void (KCALL *print_message)(void *arg),
                          void *arg) {
	unsigned int i;
	unsigned int message_end_y;
	void *buf;
	dbg_attr_t attr = dbg_attr;
	dbg_setcolor(DBG_COLOR_LIGHT_GRAY, DBG_COLOR_BLACK);
	buf = alloca(dbg_screen_width *
	             dbg_screen_height *
	             dbg_screen_cellsize);
	dbg_getscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_fillscreen(' ');
	dbg_fillrect_doublestroke(0, 0, dbg_screen_width, dbg_screen_height);
	dbg_pprint(2, 1, title);
	dbg_pputuni(0, 2, 0x255F);
	dbg_pputuni(dbg_screen_width - 1, 2, 0x2562);
	dbg_hline(1, 2, dbg_screen_width - 2, 0x2500);

	message_end_y = 3;
	if (print_message) {
		unsigned int old_dbg_indent;
		dbg_setcur(2, 3);
		old_dbg_indent = dbg_indent;
		dbg_indent     = 2;
		(*print_message)(arg);
		dbg_indent    = old_dbg_indent;
		message_end_y = dbg_getcur_y();
		dbg_pputuni(0, message_end_y, 0x255F);
		dbg_pputuni(dbg_screen_width - 1, message_end_y, 0x2562);
		dbg_hline(1, message_end_y, dbg_screen_width - 2, 0x2500);
		++message_end_y;
	}
	for (;;) {
		unsigned int key;
		dbg_setcur(1, message_end_y);
		for (i = 0; options[i]; ++i) {
			dbg_setcolor(DBG_COLOR_WHITE, i == default_option ? DBG_COLOR_LIGHT_GRAY : DBG_COLOR_BLACK);
			dbg_hline(1, message_end_y + i, dbg_screen_width - 2, ' ');
			dbg_pprintf(5, message_end_y + i, DBGSTR("%s"), options[i]);
		}
		key = dbg_getkey();
		switch (key) {
		case KEY_ENTER:
		case KEY_KP_ENTER:
			goto done;
		case KEY_ESC:
			default_option = DBG_MENU_SELECTION_CANCEL;
			goto done;
		case KEY_UP:
			if (default_option)
				--default_option;
			break;
		case KEY_DOWN:
			if (options[default_option + 1])
				++default_option;
			break;
		default: break;
		}
	}
done:
	dbg_setscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_attr = attr;
	return default_option;
}

PUBLIC ATTR_DBGTEXT WUNUSED NONNULL((1, 2, 4)) unsigned int
NOTHROW(VCALL dbg_menuf)(char const *__restrict title,
                         char const *const *__restrict options,
                         unsigned int default_option,
                         char const *__restrict message_format,
                         ...) {
	va_list args;
	unsigned int result;
	va_start(args, message_format);
	result = dbg_vmenuf(title,
	                    options,
	                    default_option,
	                    message_format,
	                    args);
	va_end(args);
	return result;
}


struct print_message_format_data {
	char const *pmf_format;
	va_list     pmf_args;
};
PRIVATE ATTR_DBGTEXT NONNULL((1)) void KCALL print_message_format(void *arg) {
	struct print_message_format_data *data;
	data = (struct print_message_format_data *)arg;
	dbg_vprintf(data->pmf_format,
	            data->pmf_args);
}

PUBLIC ATTR_DBGTEXT WUNUSED NONNULL((1, 2, 4)) unsigned int
NOTHROW(KCALL dbg_vmenuf)(char const *__restrict title,
                          char const *const *__restrict options,
                          unsigned int default_option,
                          char const *__restrict message_format,
                          va_list args) {
	unsigned int result;
	struct print_message_format_data data;
	data.pmf_format = message_format;
	va_copy(data.pmf_args, args);
	result = dbg_menuex(title,
	                    options,
	                    default_option,
	                    &print_message_format,
	                    &data);
	va_end(data.pmf_args);
	return result;
}


/* Print a messagebox centered on-screen. */
PUBLIC void
NOTHROW(KCALL dbg_messagebox)(char const *__restrict title,
                              char const *__restrict text) {
	unsigned int box_x, box_y, box_sx, box_sy, y;
	size_t num_lines = 0, longest_line, title_length;
	char const *iter = text;
	if (!title)
		title = DBGSTR("");
	longest_line = title_length = strlen(title);
	for (;;) {
		char const *end = strchrnul(iter, '\n');
		size_t temp;
		++num_lines;
		temp = (size_t)(end - iter);
		if (longest_line < temp)
			longest_line = temp;
		if (!*end)
			break;
		iter = end + 1;
	}
	box_sx = longest_line + 4;
	box_sy = num_lines + 4;
	if unlikely(box_sx >= dbg_screen_width)
		box_x = 0;
	else {
		box_x = (dbg_screen_width - box_sx) / 2;
	}
	if unlikely(box_sy >= dbg_screen_height)
		box_y = 0;
	else {
		box_y = (dbg_screen_height - box_sy) / 2;
	}
	dbg_fillrect_singlestroke(box_x, box_y, box_sx, box_sy);
	dbg_fillbox(box_x + 1, box_y + 1, box_sx - 2, box_sy - 2, ' ');
	for (iter = text, y = box_y + 2;; ++y) {
		char const *end = strchrnul(iter, '\n');
		++num_lines;
		dbg_pprintf(box_x + 2, y, DBGSTR("%$s"), (size_t)(end - iter), iter);
		if (!*end)
			break;
		iter = end + 1;
	}
	if unlikely(title_length >= dbg_screen_width)
		box_x = 0;
	else {
		box_x = (dbg_screen_width - title_length) / 2;
	}
	dbg_pprint(box_x, box_y, title);
}



DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_UTIL_C */
