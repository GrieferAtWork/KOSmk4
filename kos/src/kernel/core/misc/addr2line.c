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
#ifndef GUARD_KERNEL_SRC_MISC_ADDR2LINE_C
#define GUARD_KERNEL_SRC_MISC_ADDR2LINE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/addr2line.h>
#include <kernel/types.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/debug_line.h>

#include <elf.h>
#include <format-printer.h>
#include <stdarg.h>
#include <string.h>

DECL_BEGIN

INTDEF byte_t __kernel_debug_line_start[];
INTDEF byte_t __kernel_debug_line_end[];
INTDEF byte_t __kernel_debug_line_size[];
INTDEF byte_t __kernel_debug_info_start[];
INTDEF byte_t __kernel_debug_info_end[];
INTDEF byte_t __kernel_debug_info_size[];
INTDEF byte_t __kernel_debug_aranges_start[];
INTDEF byte_t __kernel_debug_aranges_end[];
INTDEF byte_t __kernel_debug_aranges_size[];
INTDEF byte_t __kernel_debug_abbrev_start[];
INTDEF byte_t __kernel_debug_abbrev_end[];
INTDEF byte_t __kernel_debug_abbrev_size[];
INTDEF byte_t __kernel_debug_str_start[];
INTDEF byte_t __kernel_debug_str_end[];
INTDEF byte_t __kernel_debug_str_size[];
INTDEF byte_t __kernel_debug_ranges_start[];
INTDEF byte_t __kernel_debug_ranges_end[];
INTDEF byte_t __kernel_debug_ranges_size[];

PUBLIC_CONST ATTR_COLDRODATA di_debug_sections_t const kernel_debug_sections = {
	/* .ds_debug_line_start    = */(byte_t *)__kernel_debug_line_start,
	/* .ds_debug_line_end      = */(byte_t *)__kernel_debug_line_end,
	/* .ds_debug_info_start    = */(byte_t *)__kernel_debug_info_start,
	/* .ds_debug_info_end      = */(byte_t *)__kernel_debug_info_end,
	/* .ds_debug_abbrev_start  = */(byte_t *)__kernel_debug_abbrev_start,
	/* .ds_debug_abbrev_end    = */(byte_t *)__kernel_debug_abbrev_end,
	/* .ds_debug_aranges_start = */(byte_t *)__kernel_debug_aranges_start,
	/* .ds_debug_aranges_end   = */(byte_t *)__kernel_debug_aranges_end,
	/* .ds_debug_str_start     = */(byte_t *)__kernel_debug_str_start,
	/* .ds_debug_str_end       = */(byte_t *)__kernel_debug_str_end,
	/* .ds_debug_ranges_start  = */(byte_t *)__kernel_debug_ranges_start,
	/* .ds_debug_ranges_end    = */(byte_t *)__kernel_debug_ranges_end,
	/* .ds_symtab_start        = */(byte_t *)NULL,
	/* .ds_symtab_end          = */(byte_t *)NULL,
	/* .ds_symtab_ent          = */sizeof(Elf_Sym),
	/* .ds_strtab_start        = */(byte_t *)NULL,
	/* .ds_strtab_end          = */(byte_t *)NULL
};

/* Lookup addr2line information for the given source address. */
PUBLIC ATTR_COLDTEXT addr2line_errno_t
NOTHROW(KCALL addr2line)(uintptr_t abs_pc,
                         di_debug_addr2line_t *__restrict result,
                         uintptr_t level) {
	return debug_sections_addr2line(&kernel_debug_sections,
	                                result,
	                                abs_pc,
	                                level,
	                                DEBUG_ADDR2LINE_FNORMAL);
}



/* Print addr2line information for the given source address:
 * @param: printer:  The printer to which to output data.
 * @param: arg:      Argument to-be passed to `printer'
 * @param: start_pc: Starting program counter position (the one to pass to `addr2line')
 *                   This should be the address of the instruction who's source location
 *                   should be displayed.
 * @param: end_pc:   Ending program counter position.
 *                   This should be the address of the instruction following the one who's
 *                   source location should be displayed.
 *                   Note that the PC found in tracebacks, or exception information always
 *                   points to the _FOLLOWING_ PC, meaning that this argument should THAT
 *                   PC, whilst `start_pc' should be `arch_instruction_tryprev(end_pc)'
 * @param: message_format: printf-format of a message to print on each line
 * Example (of an inlined function):
 * >> /cygdrive/e/c/kls/kos/src/kernel/core/foo/bar.c(9) : my_inline_function+8 : c010783a+4 : Called from here
 * >> /cygdrive/e/c/kls/kos/src/kernel/core/foo/bar.c(42) : my_function+26 : c0107828+38 : Called from here
 * The format used is:
 *    debug_print_filename(SRC) + "(" + al_srcline + (al_srccol ? ("," + al_srccol) : "") + ")" +
 *    " : " + (al_rawname ? al_rawname : al_name ? al_name : "???") + "+" +
 *            (level == 0 ? (start_pc - al_symstart) : level == 0 ? (al_linestart - al_symstart)) +
 *    " : " + (level == 0 ? (start_pc.hex() + "+" + (end_pc - start_pc))
 *                        : (al_symstart.hex() + "+" + (al_symend - al_symstart).hex())) +
 *   (message_format ? (" : " + message_format % args) : "");
 * Or in other words:
 * >> filename(line[,col]) : name+offset_of_start_pc_from_name : instr_start+instr_length[ : message]
 * Where `instr_start' and `instr_length' refer to the inlined function for levels > 0
 * Additionally, when no addr2line information is available, the following is printed:
 * >> start_pc+end_pc_minus_start_pc[ : message] */
PUBLIC ssize_t
(VCALL addr2line_printf)(pformatprinter printer, void *arg, uintptr_t start_pc,
                         uintptr_t end_pc, char const *message_format, ...) {
	va_list args;
	ssize_t result;
	va_start(args, message_format);
	result = addr2line_vprintf(printer,
	                           arg,
	                           start_pc,
	                           end_pc,
	                           message_format,
	                           args);
	va_end(args);
	return result;
}

PUBLIC ssize_t
(KCALL addr2line_vprintf)(pformatprinter printer, void *arg, uintptr_t start_pc,
                          uintptr_t end_pc, char const *message_format,
                          va_list args) {
	ssize_t result, temp;
	di_debug_addr2line_t info;
	addr2line_errno_t error;
	error = addr2line(start_pc, &info, 0);
	if (error != DEBUG_INFO_ERROR_SUCCESS) {
		result = format_printf(printer, arg, "%p+%Iu",
		                       start_pc,
		                       (size_t)(end_pc - start_pc));
		if unlikely(result < 0)
			goto done;
		if (message_format) {
			temp = (*printer)(arg, " : ", 1);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			temp = format_vprintf(printer, arg, message_format, args);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		temp = (*printer)(arg, "\n", 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	} else {
		uintptr_t level = 0;
again_printlevel:
		if (!info.al_srcfile)
			info.al_srcfile = (char *)"??" "?";
		if (!info.al_rawname)
			info.al_rawname = info.al_name;
		if (!info.al_rawname)
			info.al_rawname = (char *)"??" "?";
		result = debug_print_filename(printer, arg, info.al_cubase, info.al_srcpath, info.al_srcfile);
		if unlikely(result < 0)
			goto done;
		temp = format_printf(printer, arg, "(%Iu", info.al_srcline);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (info.al_srccol > 0) {
			temp = format_printf(printer, arg, ",%Iu", info.al_srccol);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		temp = format_printf(printer, arg, ") : %s+%Iu : %p+%Iu",
		                     info.al_rawname,
		                     level == 0 ? (start_pc - info.al_symstart) : (info.al_linestart - info.al_symstart),
		                     level == 0 ? start_pc : info.al_linestart,
		                     level == 0 ? (end_pc - start_pc) : (info.al_lineend - info.al_linestart));
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (message_format) {
			temp = (*printer)(arg, " : ", 3);
			if unlikely(temp < 0)
				goto err;
			result += temp;
#if !defined(__i386__) /* Unnecessary on i386 */
			if (level < info.al_levelcnt - 1) {
				va_list copy;
				va_copy(copy, args);
				temp = format_vprintf(printer, arg, message_format, copy);
				va_end(copy);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			} else
#endif
			{
				temp = format_vprintf(printer, arg, message_format, args);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
		}
		temp = (*printer)(arg, "\n", 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (++level < info.al_levelcnt) {
			/* Print additional levels */
			error = addr2line(start_pc, &info, level);
			if (error == DEBUG_INFO_ERROR_SUCCESS)
				goto again_printlevel;
		}
	}
done:
	return result;
err:
	return temp;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_ADDR2LINE_C */
