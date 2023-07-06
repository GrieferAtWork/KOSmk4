/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_DEBUGGER_UTIL_C
#define GUARD_KERNEL_SRC_DEBUGGER_UTIL_C 1
#define DISABLE_BRANCH_PROFILING
#define _GNU_SOURCE 1 /* strchrnul() */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <debugger/util.h>
#include <kernel/addr2line.h>

#include <kos/keyboard.h>

#include <alloca.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#include <libdebuginfo/errno.h>

DECL_BEGIN

#ifndef LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH
DECL_END

#undef CC
#include "../../../libinstrlen/api.h" /* ARCH_INSTRUCTION_MAXLENGTH */
#undef CC

DECL_BEGIN
/* Helper wrappers to  determine the predecessor/successor  of a given  `pc',
 * which is allowed to point into user-space, in which case user-space memory
 * is accessed through use of `dbg_readmemory()', rather than direct  access. */
PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED byte_t *
NOTHROW(LIBINSTRLEN_CC dbg_instruction_succ_nx)(void const *pc, isa_t isa) {
	/* This `12' must  be >=  the max number  of remaining  zero-bytes
	 * following  after  any  other  sequence  of  instruction  bytes.
	 * This is used to ensure that libdisasm sees that our instruction
	 * sequence terminates after a certain offset. */
	byte_t textbuf[ARCH_INSTRUCTION_MAXLENGTH], *result;
	size_t textsiz;
	textsiz = ARCH_INSTRUCTION_MAXLENGTH -
	          dbg_readmemory(pc, textbuf, ARCH_INSTRUCTION_MAXLENGTH);
	if (!textsiz)
		return NULL;
	/* zero-fill a small tail area after the text. */
	bzero(textbuf + textsiz, ARCH_INSTRUCTION_MAXLENGTH - textsiz);
	result = instruction_succ_nx(textbuf, isa);
	if (result)
		result = (byte_t *)pc + (result - textbuf);
	return result;
}


/* Return the length the longest valid instruction with a length <= maxlen that ends at `pc'
 * If no such instruction exists, return `0' instead. */
PRIVATE ATTR_DBGTEXT ATTR_PURE WUNUSED u8
NOTHROW_NCX(FCALL dbg_predmaxone)(void const *pc, isa_t isa, u8 maxlen) {
	byte_t const *result;
	result = (byte_t const *)pc - maxlen;
	for (; (uintptr_t)result < (uintptr_t)pc; ++result) {
		byte_t *nextptr;
		nextptr = dbg_instruction_succ_nx(result, isa);
		if (nextptr == (byte_t const *)pc)
			return (u8)(size_t)((byte_t const *)pc - result);
	}
	return 0;
}

/* # of instructions to back-track in order to verify that
 * some  given instruction point fits into the instruction
 * stream described by surrounding instructions. */
#ifndef LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE
#define LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE 16
#endif /* !LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE */

PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED byte_t *
NOTHROW(LIBINSTRLEN_CC dbg_instruction_pred_nx)(void const *pc, isa_t isa) {
	byte_t const *iter, *lowest_iter;
	unsigned int i;
	u8 maxlen[LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE];
	memset(maxlen, ARCH_INSTRUCTION_MAXLENGTH,
	       LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE);
	lowest_iter = (byte_t const *)pc;
	iter        = (byte_t const *)pc;
	for (i = 0; i < LIBINSTRLEN_ARCH_INSTRUCTION_VERIFY_DISTANCE; ++i) {
		u8 length;
find_shorter_instructions:
		length = dbg_predmaxone(iter, isa, maxlen[i]);
		if (!length) {
			/* Try to go back and find a shorter instruction. */
			while (i) {
				maxlen[i] = ARCH_INSTRUCTION_MAXLENGTH;
				--i;
				iter += maxlen[i];
				--maxlen[i];
				if (maxlen[i] != 0)
					goto find_shorter_instructions;
			}
			goto done_backtrack;
		}
		maxlen[i] = length;
		iter -= length;
		if (lowest_iter > iter)
			lowest_iter = iter;
	}
done_backtrack:
	if (lowest_iter >= (byte_t const *)pc)
		return NULL; /* No base-reference found... */
	/* Find  the  start  of the  first  instruction that
	 * ends at `>= pc', but starts at `>= rev_iter_curr' */
	iter = lowest_iter;
	for (;;) {
		byte_t const *next;
		next = dbg_instruction_succ_nx(iter, isa);
		if (!next)
			break; /* No such instruction... */
		if (next >= pc)
			return (byte_t *)iter; /* Found it! */
		iter = next;
	}
	return NULL;
}

PUBLIC ATTR_DBGTEXT ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW(LIBINSTRLEN_CC dbg_instruction_trysucc)(void const *pc, isa_t isa) {
	byte_t *result;
	result = dbg_instruction_succ_nx(pc, isa);
	if unlikely(!result)
		result = (byte_t *)pc + 1;
	return result;
}

PUBLIC ATTR_DBGTEXT ATTR_PURE ATTR_RETNONNULL WUNUSED byte_t *
NOTHROW(LIBINSTRLEN_CC dbg_instruction_trypred)(void const *pc, isa_t isa) {
	byte_t *result;
	result = dbg_instruction_pred_nx(pc, isa);
	if unlikely(!result)
		result = (byte_t *)pc - 1;
	return result;
}
#endif /* !LIBINSTRLEN_FIXED_INSTRUCTION_LENGTH */


/* Print addr2line optimized for the debugger.
 * Example   (of    an   inlined    function):
 * >> c010783a+4   [my_inline_function+8] [bar.c:9]
 * >> c0107828+38  [my_function+26] [bar.c:42]
 * This is similar to `addr2line_printf()', however doesn't include the full source path,
 * and doesn't follow the file(line,col) format, but instead opts for much shorter  lines
 * which can then (usually) be displayed in one continuous line, rather than having to be
 * split up into multiple lines.
 * Additionally, this function also highlights output using differing colors. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(VCALL dbg_addr2line_printf)(void const *start_pc, void const *end_pc,
                                    char const *message_format, ...) {
	va_list args;
	va_start(args, message_format);
	dbg_addr2line_vprintf(start_pc, end_pc, message_format, args);
	va_end(args);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL do_dbg_addr2line_vprintf)(struct addr2line_buf const *__restrict ainfo,
                                        uintptr_t module_relative_start_pc,
                                        void const *start_pc, void const *end_pc,
                                        char const *message_format, va_list args) {
	di_debug_addr2line_t info;
	debuginfo_errno_t error;
	u8 normal_fgcolor = ANSITTY_CL_WHITE;
	u8 inline_fgcolor = ANSITTY_CL_AQUA;
	if (ainfo->ds_mod && !module_isdriver(ainfo->ds_mod)) {
		normal_fgcolor = ANSITTY_CL_OLIVE;
		inline_fgcolor = ANSITTY_CL_TEAL;
	}
	error = addr2line(ainfo, module_relative_start_pc, &info, 0);
	if (error != DEBUG_INFO_ERROR_SUCCESS) {
		dbg_savecolor();
		dbg_setfgcolor(normal_fgcolor);
		dbg_printf(DBGSTR("%p"), start_pc);
		dbg_loadcolor();
		dbg_putc('+');
		dbg_savecolor();
		dbg_setfgcolor(normal_fgcolor);
		dbg_printf(DBGSTR("%-4" PRIuSIZ),
		           (size_t)((byte_t *)end_pc -
		                    (byte_t *)start_pc));
		dbg_loadcolor();
		if (ainfo->ds_mod && module_hasname(ainfo->ds_mod)) {
			dbg_putc('[');
			dbg_savecolor();
			dbg_setfgcolor(normal_fgcolor);
			module_printname(ainfo->ds_mod, &dbg_printer, NULL);
			dbg_loadcolor();
			dbg_putc(']');
		}
		if (message_format) {
			dbg_putc('[');
			dbg_savecolor();
			dbg_setfgcolor(normal_fgcolor);
			dbg_vprintf(message_format, args);
			dbg_loadcolor();
			dbg_putc(']');
		}
		dbg_putc('\n');
	} else {
		uintptr_t level = 0;
		u8 fgcolor;
again_printlevel:
		if (!info.al_rawname)
			info.al_rawname = info.al_name;
		if (!info.al_rawname)
			info.al_rawname = (char *)DBGSTR("??" "?");
		dbg_logecho_push();
		fgcolor = level < info.al_levelcnt - 1
		        ? inline_fgcolor
		        : normal_fgcolor;
		dbg_savecolor();
		if (info.al_srcfile) {
			dbg_logecho_enabled = false;
			debug_addr2line_print_filename(&dbg_logecho_printer, NULL,
			                               info.al_cubase,
			                               info.al_srcpath,
			                               info.al_srcfile);
			if (info.al_srcline) {
				if (info.al_srccol) {
					dbg_logechof(DBGSTR("(%" PRIuPTR ",%" PRIuPTR ")"),
					             info.al_srcline, info.al_srccol);
				} else {
					dbg_logechof(DBGSTR("(%" PRIuPTR ")"),
					             info.al_srcline);
				}
			}
			dbg_logechof(DBGSTR(" : %p+%" PRIuSIZ),
			             level == 0 ? start_pc
			                      : (((byte_t *)start_pc - module_relative_start_pc) +
			                         info.al_symstart),
			             level == 0 ? (size_t)((byte_t *)end_pc - (byte_t *)start_pc)
			                      : (size_t)(info.al_lineend - info.al_linestart));
			if (ainfo->ds_mod && module_haspath_or_name(ainfo->ds_mod)) {
				dbg_logecho(DBGSTR("["));
				module_printpath_or_name(ainfo->ds_mod, &dbg_logecho_printer, NULL);
				dbg_logecho(DBGSTR("]"));
			}
			dbg_logechof(DBGSTR("[%s+%" PRIuSIZ "]"),
			             info.al_rawname,
			             level == 0 ? (size_t)(module_relative_start_pc - info.al_symstart)
			                        : (size_t)(info.al_linestart - info.al_symstart));
			if (message_format) {
				va_list copy;
				dbg_logecho(DBGSTR(" ["));
				va_copy(copy, args);
				dbg_vlogechof(message_format, copy);
				va_end(copy);
				dbg_logecho(DBGSTR("]"));
			}
			dbg_logecho(DBGSTR("\n"));
		}
		dbg_setfgcolor(fgcolor);
		dbg_printf(DBGSTR("%p"),
		           level == 0 ? start_pc
		                      : (((byte_t *)start_pc - module_relative_start_pc) +
		                         info.al_symstart));
		dbg_loadcolor();
		dbg_putc('+');
		dbg_savecolor();
		dbg_setfgcolor(fgcolor);
		dbg_printf(DBGSTR("%-4" PRIuSIZ),
		           level == 0 ? (size_t)((byte_t *)end_pc - (byte_t *)start_pc)
		                      : (size_t)(info.al_lineend - info.al_linestart));
		dbg_loadcolor();
		if (ainfo->ds_mod && module_hasname(ainfo->ds_mod)) {
			dbg_putc('[');
			dbg_savecolor();
			dbg_setfgcolor(fgcolor);
			module_printname(ainfo->ds_mod, &dbg_printer, NULL);
			dbg_loadcolor();
			dbg_putc(']');
		}
		dbg_putc('[');
		dbg_savecolor();
		dbg_setfgcolor(fgcolor);
		dbg_print(info.al_rawname);
		dbg_loadcolor();
		dbg_putc('+');
		dbg_savecolor();
		dbg_setfgcolor(fgcolor);
		dbg_printf(DBGSTR("%" PRIuSIZ),
		           level == 0 ? (size_t)(module_relative_start_pc - info.al_symstart)
		                      : (size_t)(info.al_linestart - info.al_symstart));
		dbg_loadcolor();
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
			dbg_print(DBGSTR(" ["));
			dbg_savecolor();
			dbg_setfgcolor(fgcolor);
			dbg_print(p1);
			dbg_loadcolor();
			if (info.al_srcline) {
				dbg_putc(':');
				dbg_savecolor();
				dbg_setfgcolor(fgcolor);
				dbg_printf(DBGSTR("%" PRIuSIZ), info.al_srcline);
				dbg_loadcolor();
				if (info.al_srccol) {
					dbg_putc(':');
					dbg_savecolor();
					dbg_setfgcolor(fgcolor);
					dbg_printf(DBGSTR("%" PRIuSIZ), info.al_srccol);
					dbg_loadcolor();
				}
			}
			dbg_putc(']');
		}
		if (message_format) {
			dbg_print(DBGSTR(" ["));
			dbg_savecolor();
			dbg_setfgcolor(fgcolor);
#ifndef __i386__
			if (level == info.al_levelcnt - 1) {
				va_list copy;
				va_copy(copy, args);
				dbg_vprintf(message_format, copy);
				va_end(copy);
			} else
#endif /* !__i386__ */
			{
				dbg_vprintf(message_format, args);
			}
			dbg_loadcolor();
			dbg_putc(']');
		}
		dbg_putc('\n');
		dbg_logecho_pop();
		if (++level < info.al_levelcnt) {
			/* Print additional levels */
			error = addr2line(ainfo, module_relative_start_pc, &info, level);
			if (error == DEBUG_INFO_ERROR_SUCCESS)
				goto again_printlevel;
		}
	}
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_addr2line_vprintf)(void const *start_pc, void const *end_pc,
                                     char const *message_format, va_list args) {
	struct addr2line_buf ainfo;
	uintptr_t module_relative_start_pc;
	module_relative_start_pc = addr2line_begin(&ainfo, start_pc);
	do_dbg_addr2line_vprintf(&ainfo, module_relative_start_pc,
	                         start_pc, end_pc, message_format, args);
	addr2line_end(&ainfo);
}





/* Display a selections menu with a set of `options' (which is a NULL-terminated vector strings)
 * Options  are  on  top  of   each  other,  and  can  be   navigated  using  the  arrow   keys.
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
	bool was_cursor_visible;
	dbg_savecolor();
	dbg_setcolor(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_BLACK);
	buf = alloca(dbg_screen_width *
	             dbg_screen_height *
	             dbg_screen_cellsize);
	was_cursor_visible = dbg_setcur_visible(false);
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
		dbg_beginupdate();
		for (i = 0; options[i]; ++i) {
			dbg_setcolor(ANSITTY_CL_WHITE, i == default_option ? ANSITTY_CL_LIGHT_GRAY : ANSITTY_CL_BLACK);
			dbg_hline(1, message_end_y + i, dbg_screen_width - 2, ' ');
			dbg_pprintf(5, message_end_y + i, DBGSTR("%s"), options[i]);
		}
		dbg_endupdate(true);
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
	dbg_setcur_visible(was_cursor_visible);
	dbg_loadcolor();
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
	if unlikely(box_sx >= dbg_screen_width) {
		box_x = 0;
	} else {
		box_x = (dbg_screen_width - box_sx) / 2;
	}
	if unlikely(box_sy >= dbg_screen_height) {
		box_y = 0;
	} else {
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
	if unlikely(title_length >= dbg_screen_width) {
		box_x = 0;
	} else {
		box_x = (dbg_screen_width - title_length) / 2;
	}
	dbg_pprint(box_x, box_y, title);
}



DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_UTIL_C */
