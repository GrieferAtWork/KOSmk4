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
#include <kernel/types.h>
#include <kernel/vm/usermod.h>

#include <elf.h>
#include <format-printer.h>
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
	struct exception_info exinfo;
	/* Preserve exception information. */
	memcpy(&exinfo, error_info(), sizeof(struct exception_info));
	TRY
#endif /* CONFIG_HAVE_USERMOD */
	{
		return debug_sections_addr2line(&info->ds_info,
		                                result,
		                                module_relative_pc,
		                                level,
		                                DEBUG_ADDR2LINE_FNORMAL);
	}
#ifdef CONFIG_HAVE_USERMOD
	EXCEPT {
		/* XXX: What do we do about RT-level exceptions? */
	}
	memcpy(error_info(), &exinfo, sizeof(struct exception_info));
	return DEBUG_INFO_ERROR_CORRUPT;
#endif /* CONFIG_HAVE_USERMOD */
}


#ifdef CONFIG_HAVE_USERMOD
PRIVATE ATTR_COLDRODATA char const secname_debug_line[]    = ".debug_line";
PRIVATE ATTR_COLDRODATA char const secname_debug_info[]    = ".debug_info";
PRIVATE ATTR_COLDRODATA char const secname_debug_abbrev[]  = ".debug_abbrev";
PRIVATE ATTR_COLDRODATA char const secname_debug_aranges[] = ".debug_aranges";
PRIVATE ATTR_COLDRODATA char const secname_debug_str[]     = ".debug_str";
PRIVATE ATTR_COLDRODATA char const secname_debug_ranges[]  = ".debug_ranges";
PRIVATE ATTR_COLDRODATA char const secname_symtab[]        = ".symtab";
PRIVATE ATTR_COLDRODATA char const secname_strtab[]        = ".strtab";
PRIVATE ATTR_COLDRODATA char const secname_dynsym[]        = ".dynsym";
PRIVATE ATTR_COLDRODATA char const secname_dynstr[]        = ".dynstr";

#define LOCK_SECTION(name)   ((REF struct driver_section *)usermod_section_lock(um, name))
#define UNLOCK_SECTION(sect) decref((REF struct driver_section *)(sect))

PRIVATE ATTR_COLDTEXT NONNULL((1, 2, 3)) unsigned int KCALL
usermod_debug_dllocksections(struct usermod *__restrict um,
                             di_debug_sections_t *__restrict sections,
                             di_dl_debug_sections_t *__restrict dl_sections) {
	memset(sections, 0, sizeof(*sections));
	dl_sections->dl_debug_line = LOCK_SECTION(secname_debug_line);
	if (!dl_sections->dl_debug_line) {
		/* No debug information sections */
		dl_sections->dl_debug_info = NULL;
set_no_extened_debug_info_2:
		dl_sections->dl_debug_abbrev = NULL;
set_no_extened_debug_info:
		dl_sections->dl_debug_aranges = NULL;
		dl_sections->dl_debug_str     = NULL;
		dl_sections->dl_debug_ranges  = NULL;
	} else {
		/* Load .debug_info and .dl_debug_abbrev */
		dl_sections->dl_debug_info = LOCK_SECTION(secname_debug_info);
		if (!dl_sections->dl_debug_info)
			goto set_no_extened_debug_info_2;
		dl_sections->dl_debug_abbrev = LOCK_SECTION(secname_debug_abbrev);
		if (!dl_sections->dl_debug_abbrev) {
			UNLOCK_SECTION(dl_sections->dl_debug_info);
			goto set_no_extened_debug_info;
		}
		/* All all of the remaining debug information sections (which are optional, though) */
		dl_sections->dl_debug_aranges = LOCK_SECTION(secname_debug_aranges);
		dl_sections->dl_debug_str     = LOCK_SECTION(secname_debug_str);
		dl_sections->dl_debug_ranges  = LOCK_SECTION(secname_debug_ranges);
	}
	dl_sections->dl_symtab = LOCK_SECTION(secname_symtab);
	if (dl_sections->dl_symtab) {
		dl_sections->dl_strtab = LOCK_SECTION(secname_strtab);
		if unlikely(!dl_sections->dl_strtab) {
			UNLOCK_SECTION(dl_sections->dl_symtab);
			goto try_load_dynsym;
		}
	} else {
		dl_sections->dl_strtab = NULL;
try_load_dynsym:
		dl_sections->dl_symtab = LOCK_SECTION(secname_dynsym);
		if (dl_sections->dl_symtab) {
			dl_sections->dl_strtab = LOCK_SECTION(secname_dynstr);
			if unlikely(!dl_sections->dl_strtab) {
				UNLOCK_SECTION(dl_sections->dl_symtab);
				goto handle_missing_symbol_tables;
			}
		} else {
handle_missing_symbol_tables:
			/* Check if we've got anything at all... */
			if (!dl_sections->dl_debug_line) {
				memset(dl_sections, 0, sizeof(*dl_sections));
				return DEBUG_INFO_ERROR_NOFRAME; /* Nope; nothing... */
			}
		}
	}
#undef LOCK_SECTION
#ifdef __KERNEL__
	/* Support for compressed sections. */
#define LOAD_SECTION(sect, lv_start, lv_end)               \
	((lv_start) = (byte_t *)driver_section_cdata_nx(sect), \
	 (lv_end)   = (byte_t *)(lv_start) + (sect)->ds_csize)
#else /* __KERNEL__ */
#define LOAD_SECTION(sect, lv_start, lv_end) \
	((lv_start) = (byte_t *)(sect)->ds_data, \
	 (lv_end)   = (byte_t *)(sect)->ds_data + (sect)->ds_size)
#endif /* !__KERNEL__ */
	/* Fill in section mapping information. */
	if (dl_sections->dl_debug_line) {
		LOAD_SECTION(dl_sections->dl_debug_line,
		             sections->ds_debug_line_start,
		             sections->ds_debug_line_end);
	}
	if (dl_sections->dl_debug_info) {
		LOAD_SECTION(dl_sections->dl_debug_info,
		             sections->ds_debug_info_start,
		             sections->ds_debug_info_end);
	}
	if (dl_sections->dl_debug_abbrev) {
		LOAD_SECTION(dl_sections->dl_debug_abbrev,
		             sections->ds_debug_abbrev_start,
		             sections->ds_debug_abbrev_end);
	}
	if (dl_sections->dl_debug_aranges) {
		LOAD_SECTION(dl_sections->dl_debug_aranges,
		             sections->ds_debug_aranges_start,
		             sections->ds_debug_aranges_end);
	}
	if (dl_sections->dl_debug_str) {
		LOAD_SECTION(dl_sections->dl_debug_str,
		             sections->ds_debug_str_start,
		             sections->ds_debug_str_end);
	}
	if (dl_sections->dl_debug_ranges) {
		LOAD_SECTION(dl_sections->dl_debug_ranges,
		             sections->ds_debug_ranges_start,
		             sections->ds_debug_ranges_end);
	}
	if (dl_sections->dl_symtab) {
		LOAD_SECTION(dl_sections->dl_symtab,
		             sections->ds_symtab_start,
		             sections->ds_symtab_end);
		sections->ds_symtab_ent = dl_sections->dl_symtab->ds_entsize;
		if (!sections->ds_symtab_ent)
			sections->ds_symtab_ent = sizeof(ElfW(Sym));
	}
	if (dl_sections->dl_strtab) {
		LOAD_SECTION(dl_sections->dl_strtab,
		             sections->ds_strtab_start,
		             sections->ds_strtab_end);
	}
#undef LOAD_SECTION
	return DEBUG_INFO_ERROR_SUCCESS;
}

PRIVATE ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL usermod_debug_dlunlocksections)(di_dl_debug_sections_t *__restrict dl_sections) {
	if (dl_sections->dl_strtab)
		UNLOCK_SECTION(dl_sections->dl_strtab);
	if (dl_sections->dl_symtab)
		UNLOCK_SECTION(dl_sections->dl_symtab);
	if (dl_sections->dl_debug_ranges)
		UNLOCK_SECTION(dl_sections->dl_debug_ranges);
	if (dl_sections->dl_debug_str)
		UNLOCK_SECTION(dl_sections->dl_debug_str);
	if (dl_sections->dl_debug_aranges)
		UNLOCK_SECTION(dl_sections->dl_debug_aranges);
	if (dl_sections->dl_debug_abbrev)
		UNLOCK_SECTION(dl_sections->dl_debug_abbrev);
	if (dl_sections->dl_debug_info)
		UNLOCK_SECTION(dl_sections->dl_debug_info);
	if (dl_sections->dl_debug_line)
		UNLOCK_SECTION(dl_sections->dl_debug_line);
#ifndef NDEBUG
	memset(dl_sections, 0xcc, sizeof(*dl_sections));
#endif /* !NDEBUG */
}

PRIVATE ATTR_COLDTEXT ATTR_NOINLINE WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL addr2line_begin_user)(struct addr2line_buf *__restrict buf,
                                    uintptr_t abs_pc,
                                    struct addr2line_modinfo *modinfo) {
	uintptr_t result;
	struct exception_info exinfo;
	/* Make sure that we're actually dealing with user-space here! */
	if (!ADDR_ISUSER(abs_pc))
		goto nope;
	if (modinfo)
		memset(modinfo, 0, sizeof(*modinfo));
	/* Preserve exception information. */
	memcpy(&exinfo, error_info(), sizeof(struct exception_info));
	TRY {
		REF struct usermod *um;
		/* Try to load the user-space module at the given address.
		 * Also: Make sure that `abs_pc' is executable the first time around! */
		um = getusermod((void *)abs_pc, true);
		if (!um)
			goto nope;
		if (modinfo) {
			modinfo->ami_fsfile = (REF struct inode *)incref(um->um_file);
			modinfo->ami_fspath = xincref(um->um_fspath);
			modinfo->ami_fsname = xincref(um->um_fsname);
			if (modinfo->ami_fsname)
				modinfo->ami_name = modinfo->ami_fsname->de_name;
		}
		TRY {
			if (usermod_debug_dllocksections(um,
			                                 &buf->ds_info,
			                                 &buf->ds_sect) !=
			    DEBUG_INFO_ERROR_SUCCESS) {
				decref_unlikely(um);
				goto nope;
			}
		} EXCEPT {
			decref_unlikely(um);
			goto restore_except;
		}
		buf->ds_user = um; /* Inherit reference. */
		result = abs_pc - um->um_loadaddr;
	} EXCEPT {
		goto restore_except;
	}
	return result;
restore_except:
	memcpy(error_info(), &exinfo, sizeof(struct exception_info));
nope:
	memset(buf, 0, sizeof(*buf));
	return abs_pc;
}
#endif /* CONFIG_HAVE_USERMOD */

PUBLIC ATTR_COLDTEXT WUNUSED NONNULL((1)) uintptr_t
NOTHROW(KCALL addr2line_begin)(struct addr2line_buf *__restrict buf,
                               uintptr_t abs_pc,
                               struct addr2line_modinfo *modinfo) {
	REF struct driver *d;
	d = driver_at_address((void const *)abs_pc);
	if unlikely(!d) {
#ifdef CONFIG_HAVE_USERMOD
		/* Try to do some user-space addr2line... */
		return addr2line_begin_user(buf, abs_pc, modinfo);
#else /* CONFIG_HAVE_USERMOD */
		memset(buf, 0, sizeof(*buf));
		if (modinfo)
			memset(modinfo, 0, sizeof(*modinfo));
		return abs_pc;
#endif /* !CONFIG_HAVE_USERMOD */
	}
	buf->ds_user = NULL;
	abs_pc -= d->d_loadaddr;
	if (debug_dllocksections(d, &buf->ds_info, &buf->ds_sect) != DEBUG_INFO_ERROR_SUCCESS)
		memset(buf, 0, sizeof(*buf));
	if (modinfo) {
		modinfo->ami_fsfile   = (REF struct inode *)xincref(d->d_file);
		modinfo->ami_fspath   = NULL;
		modinfo->ami_fsname   = NULL;
		modinfo->ami_name     = d->d_name;
		modinfo->ami_filename = d->d_filename;
	}
	decref_unlikely(d);
	return abs_pc;
}

PUBLIC ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL addr2line_end)(struct addr2line_buf *__restrict buf) {
#ifdef CONFIG_HAVE_USERMOD
	if (buf->ds_user) {
		usermod_debug_dlunlocksections(&buf->ds_sect);
	} else
#endif /* CONFIG_HAVE_USERMOD */
	{
		debug_dlunlocksections(&buf->ds_sect);
	}
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
PUBLIC ATTR_COLDTEXT NONNULL((1)) ssize_t VCALL
addr2line_printf(pformatprinter printer, void *arg, uintptr_t start_pc,
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

PRIVATE ATTR_COLDTEXT ssize_t KCALL
do_addr2line_vprintf(struct addr2line_buf const *__restrict ainfo,
                     pformatprinter printer, void *arg, struct driver *d,
                     uintptr_t module_relative_start_pc, uintptr_t start_pc,
                     uintptr_t end_pc, char const *message_format,
                     va_list args) {
	ssize_t result, temp;
	di_debug_addr2line_t info;
	unsigned int error;
	error = addr2line(ainfo, module_relative_start_pc, &info, 0);
	if (error != DEBUG_INFO_ERROR_SUCCESS) {
		if (d) {
			if (d->d_filename) {
				result = format_printf(printer, arg, "%%{vinfo:%s:",
				                       d->d_filename);
			} else {
				result = format_printf(printer, arg, "%%{vinfo:/os/drivers/%s:",
				                       d->d_name);
			}
			if unlikely(result < 0)
				goto done;
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
			result = format_printf(printer, arg, "%p+%Iu",
			                       start_pc,
			                       (size_t)(end_pc - start_pc));
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
		                     level == 0 ? (module_relative_start_pc - info.al_symstart)
		                                : (info.al_linestart - info.al_symstart),
		                     level == 0 ? (start_pc)
		                                : ((start_pc - module_relative_start_pc) + info.al_linestart),
		                     level == 0 ? (end_pc - start_pc)
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
addr2line_vprintf(pformatprinter printer, void *arg, uintptr_t start_pc,
                  uintptr_t end_pc, char const *message_format,
                  va_list args) {
	ssize_t result;
	uintptr_t module_relative_pc;
	struct addr2line_buf ainfo;
	REF struct driver *d;
	d = driver_at_address((void const *)start_pc);
	if unlikely(!d) {
		memset(&ainfo, 0, sizeof(ainfo));
		module_relative_pc = start_pc;
	} else {
		if (debug_dllocksections(d, &ainfo.ds_info, &ainfo.ds_sect) != DEBUG_INFO_ERROR_SUCCESS)
			memset(&ainfo, 0, sizeof(ainfo));
		module_relative_pc = start_pc - d->d_loadaddr;
	}
	result = do_addr2line_vprintf(&ainfo,
	                              printer,
	                              arg,
	                              d,
	                              module_relative_pc,
	                              start_pc,
	                              end_pc,
	                              message_format,
	                              args);
	xdecref_unlikely(d);
	addr2line_end(&ainfo);
	return result;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_ADDR2LINE_C */
