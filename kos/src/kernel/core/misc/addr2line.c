/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_ADDR2LINE_C
#define GUARD_KERNEL_SRC_MISC_ADDR2LINE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/addr2line.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/module.h>
#include <kernel/types.h>
#include <kernel/vm/usermod.h>

#include <elf.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#include <libdebuginfo/debug_aranges.h>
#include <libdebuginfo/debug_info.h>
#include <libdebuginfo/debug_line.h>

DECL_BEGIN

/* Lookup addr2line information for the given source address. */
PUBLIC ATTR_COLDTEXT NONNULL((1)) unsigned int
NOTHROW(KCALL addr2line)(struct addr2line_buf const *__restrict info,
                         uintptr_t module_relative_pc,
                         di_debug_addr2line_t *__restrict result,
                         uintptr_t level) {
#ifdef CONFIG_HAVE_USERMOD
	NESTED_TRY
#endif /* CONFIG_HAVE_USERMOD */
	{
		return debug_addr2line(&info->ds_info,
		                                result,
		                                module_relative_pc,
		                                level,
		                                DEBUG_ADDR2LINE_FNORMAL);
	}
#ifdef CONFIG_HAVE_USERMOD
	EXCEPT {
		/* XXX: What do we do about RT-level exceptions? */
	}
	return DEBUG_INFO_ERROR_CORRUPT;
#endif /* CONFIG_HAVE_USERMOD */
}


PUBLIC ATTR_COLDTEXT WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL addr2line_begin)(struct addr2line_buf *__restrict buf,
                               void const *abs_pc,
                               struct addr2line_modinfo *modinfo) {
	REF module_t *mod;
	module_type_var(modtype);
	mod = module_ataddr_nx(abs_pc, modtype);
	if unlikely(!mod) {
		memset(buf, 0, sizeof(*buf));
		if (modinfo)
			memset(modinfo, 0, sizeof(*modinfo));
		return (uintptr_t)abs_pc;
	}
	abs_pc = (byte_t *)abs_pc - module_getloadaddr(mod, modtype);
	if (debug_addr2line_sections_lock(mod, &buf->ds_info, &buf->ds_sect
	                                  module_type__arg(modtype)) !=
	    DEBUG_INFO_ERROR_SUCCESS)
		memset(buf, 0, sizeof(*buf));
	if (modinfo) {
#ifdef CONFIG_HAVE_USERMOD
		if (modtype == MODULE_TYPE_USRMOD) {
			modinfo->ami_fsfile   = (REF struct inode *)incref(mod->m_usrmod.um_file);
			modinfo->ami_fspath   = xincref(mod->m_usrmod.um_fspath);
			modinfo->ami_fsname   = xincref(mod->m_usrmod.um_fsname);
			modinfo->ami_name     = NULL;
			modinfo->ami_filename = NULL;
			if (modinfo->ami_fsname)
				modinfo->ami_name = modinfo->ami_fsname->de_name;
		} else
#endif /* CONFIG_HAVE_USERMOD */
		{
			struct driver *d;
			d = (struct driver *)mod;
			modinfo->ami_fsfile   = (REF struct inode *)xincref(d->d_file);
			modinfo->ami_fspath   = NULL;
			modinfo->ami_fsname   = NULL;
			modinfo->ami_name     = d->d_name;
			modinfo->ami_filename = d->d_filename;
		}
	}
	buf->ds_mod = mod; /* Inherit reference */
	module_type_arg(buf->ds_modtype = modtype);
	return (uintptr_t)abs_pc;
}

PUBLIC ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL addr2line_end)(struct addr2line_buf *__restrict buf) {
	debug_addr2line_sections_unlock(&buf->ds_sect module_type__arg(buf->ds_modtype));
	module_xdecref(buf->ds_mod, buf->ds_modtype);
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
 *    debug_addr2line_print_filename(SRC) + "(" + al_srcline + (al_srccol ? ("," + al_srccol) : "") + ")" +
 *    " : " + (al_rawname ? al_rawname : al_name ? al_name : "???") + "+" +
 *            (level == 0 ? (start_pc - al_symstart) : (al_linestart - al_symstart)) +
 *    " : " + (level == 0 ? (start_pc.hex() + "+" + (end_pc - start_pc))
 *                        : (al_symstart.hex() + "+" + (al_symend - al_symstart).hex())) +
 *   (message_format ? (" : " + message_format % args) : "");
 * Or in other words:
 * >> filename(line[,col]) : name+offset_of_start_pc_from_name : instr_start+instr_length[ : message]
 * Where `instr_start' and `instr_length' refer to the inlined function for levels > 0
 * Additionally, when no addr2line information is available, the following is printed:
 * >> start_pc+end_pc_minus_start_pc[ : message] */
PUBLIC ATTR_COLDTEXT NONNULL((1)) ssize_t VCALL
addr2line_printf(pformatprinter printer, void *arg, void const *start_pc,
                 void const *end_pc, char const *message_format, ...) {
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

PRIVATE ATTR_COLDTEXT ssize_t KCALL
do_addr2line_vprintf(struct addr2line_buf const *__restrict ainfo,
                     pformatprinter printer, void *arg,
                     module_t *mod module_type__param(modtype),
                     uintptr_t module_relative_start_pc, void const *start_pc,
                     void const *end_pc, char const *message_format,
                     va_list args) {
	ssize_t result, temp;
	di_debug_addr2line_t info;
	unsigned int error;
	error = addr2line(ainfo, module_relative_start_pc, &info, 0);
	if (error != DEBUG_INFO_ERROR_SUCCESS) {
		if (mod) {
#ifdef CONFIG_HAVE_USERMOD
			if (modtype == MODULE_TYPE_USRMOD) {
				static char const prefix[] = "%{vinfo:";
				static char const suffix[] = ":";
				if (!mod->m_usrmod.um_fspath || !mod->m_usrmod.um_fsname)
					goto unknown_module;
				result = (*printer)(arg, prefix, COMPILER_STRLEN(prefix));
				if unlikely(result < 0)
					goto done;
				temp = path_printent(mod->m_usrmod.um_fspath,
				                     mod->m_usrmod.um_fsname->de_name,
				                     mod->m_usrmod.um_fsname->de_namelen,
				                     printer, arg);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				temp = (*printer)(arg, suffix, COMPILER_STRLEN(suffix));
				if unlikely(temp < 0)
					goto err;
				result += temp;
			} else
#endif /* CONFIG_HAVE_USERMOD */
			{
				struct driver *d = (struct driver *)mod;
				if (d->d_filename) {
					result = format_printf(printer, arg, "%%{vinfo:%s:",
					                       d->d_filename);
				} else {
					result = format_printf(printer, arg, "%%{vinfo:/os/drivers/%s:",
					                       d->d_name);
				}
				if unlikely(result < 0)
					goto done;
			}
			temp = format_printf(printer, arg,
			                     "%p:%p:%%f(%%l,%%c) : %%n : %%p",
			                     module_relative_start_pc, start_pc);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			if (message_format) {
				temp = (*printer)(arg, " : ", 3);
				if unlikely(temp < 0)
					goto err;
				result += temp;
				temp = format_vprintf(printer, arg, message_format, args);
				if unlikely(temp < 0)
					goto err;
				result += temp;
			}
			temp = (*printer)(arg, "}\n", 2);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		} else {
#ifdef CONFIG_HAVE_USERMOD
unknown_module:
#endif /* CONFIG_HAVE_USERMOD */
			result = format_printf(printer, arg, "%p+%" PRIuSIZ,
			                       start_pc,
			                       (size_t)((byte_t *)end_pc -
			                                (byte_t *)start_pc));
			if unlikely(result < 0)
				goto done;
			if (message_format) {
				temp = (*printer)(arg, " : ", 3);
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
		}
	} else {
		uintptr_t level = 0;
again_printlevel:
		if (!info.al_srcfile)
			info.al_srcfile = (char *)"??" "?";
		if (!info.al_rawname)
			info.al_rawname = info.al_name;
		if (!info.al_rawname)
			info.al_rawname = (char *)"??" "?";
		result = debug_addr2line_print_filename(printer, arg, info.al_cubase, info.al_srcpath, info.al_srcfile);
		if unlikely(result < 0)
			goto done;
		temp = format_printf(printer, arg, "(%" PRIuPTR, info.al_srcline);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (info.al_srccol > 0) {
			temp = format_printf(printer, arg, ",%" PRIuPTR, info.al_srccol);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		temp = format_printf(printer, arg, ") : %s+%" PRIuPTR " : %p+%" PRIuPTR,
		                     info.al_rawname,
		                     level == 0 ? (module_relative_start_pc - info.al_symstart)
		                                : (info.al_linestart - info.al_symstart),
		                     level == 0 ? (start_pc)
		                                : (((byte_t *)start_pc - module_relative_start_pc) + info.al_linestart),
		                     level == 0 ? ((byte_t *)end_pc - (byte_t *)start_pc)
		                                : (info.al_lineend - info.al_linestart));
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
			} else
#endif /* !__i386__ */
			{
				temp = format_vprintf(printer, arg, message_format, args);
			}
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		temp = (*printer)(arg, "\n", 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
		if (++level < info.al_levelcnt) {
			/* Print additional levels */
			error = addr2line(ainfo, module_relative_start_pc, &info, level);
			if (error == DEBUG_INFO_ERROR_SUCCESS)
				goto again_printlevel;
		}
	}
done:
	return result;
err:
	return temp;
}

PUBLIC ATTR_COLDTEXT NONNULL((1)) ssize_t KCALL
addr2line_vprintf(pformatprinter printer, void *arg, void const *start_pc,
                  void const *end_pc, char const *message_format,
                  va_list args) {
	ssize_t result;
	uintptr_t module_relative_pc;
	struct addr2line_buf ainfo;
	module_relative_pc = addr2line_begin(&ainfo, start_pc, NULL);
	result = do_addr2line_vprintf(&ainfo,
	                              printer,
	                              arg,
	                              ainfo.ds_mod
	                              module_type__arg(ainfo.ds_modtype),
	                              module_relative_pc,
	                              start_pc,
	                              end_pc,
	                              message_format,
	                              args);
	addr2line_end(&ainfo);
	return result;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_ADDR2LINE_C */
