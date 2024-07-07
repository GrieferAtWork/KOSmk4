/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_EXECINFO_C
#define GUARD_LIBC_USER_EXECINFO_C 1

#include "../api.h"
/**/

#include <hybrid/align.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <atomic.h>
#include <dlfcn.h>
#include <format-printer.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <libdebuginfo/addr2line.h>
#include <libdebuginfo/unwind.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

#include "../libc/dl.h"
#include "execinfo.h"
#include "unistd.h"

DECL_BEGIN

#define SECTION_DEBUG_TEXT   ".text.crt.debug"
#define SECTION_DEBUG_BSS    ".bss.crt.debug"
#define SECTION_DEBUG_STRING ".rodata.crt.debug"

INTDEF void *pdyn_libunwind;                     /* From `../libc/except.c' */
INTDEF void LIBCCALL initialize_libunwind(void); /* From `../libc/except.c' */

PRIVATE ATTR_SECTION(SECTION_DEBUG_BSS) PUNWIND_GETREG_LCPUSTATE pdyn_unwind_getreg_lcpustate = NULL;
PRIVATE ATTR_SECTION(SECTION_DEBUG_BSS) PUNWIND_SETREG_LCPUSTATE pdyn_unwind_setreg_lcpustate = NULL;
PRIVATE ATTR_SECTION(SECTION_DEBUG_STRING) char const name_unwind_getreg_lcpustate[] = UNWIND_GETREG_LCPUSTATE_NAME;
PRIVATE ATTR_SECTION(SECTION_DEBUG_STRING) char const name_unwind_setreg_lcpustate[] = UNWIND_SETREG_LCPUSTATE_NAME;

PRIVATE ATTR_SECTION(SECTION_DEBUG_TEXT) bool
NOTHROW(LIBCCALL initialize_libunwind_debug)(void) {
	initialize_libunwind();
#define BIND(func, name)                                                 \
	if unlikely((*(void **)&func = dlsym(pdyn_libunwind, name)) == NULL) \
		goto err_init_failed
	BIND(pdyn_unwind_getreg_lcpustate, name_unwind_getreg_lcpustate);
	BIND(pdyn_unwind_setreg_lcpustate, name_unwind_setreg_lcpustate);
#undef BIND
	return true;
err_init_failed:
	return false;
}

#define unwind_getreg_lcpustate (*pdyn_unwind_getreg_lcpustate)
#define unwind_setreg_lcpustate (*pdyn_unwind_setreg_lcpustate)

#define ENSURE_LIBUNWIND_LOADED() \
	(atomic_read(&pdyn_unwind_setreg_lcpustate) != NULL || initialize_libunwind_debug())


PRIVATE ATTR_SECTION(SECTION_DEBUG_BSS) void *pdyn_libdebuginfo                                               = NULL;
PRIVATE ATTR_SECTION(SECTION_DEBUG_BSS) PUNWIND_FOR_DEBUG pdyn_unwind_for_debug                               = NULL;
PRIVATE ATTR_SECTION(SECTION_DEBUG_BSS) PDEBUG_ADDR2LINE_SECTIONS_LOCK pdyn_debug_addr2line_sections_lock     = NULL;
PRIVATE ATTR_SECTION(SECTION_DEBUG_BSS) PDEBUG_ADDR2LINE_SECTIONS_UNLOCK pdyn_debug_addr2line_sections_unlock = NULL;
PRIVATE ATTR_SECTION(SECTION_DEBUG_BSS) PDEBUG_ADDR2LINE pdyn_debug_addr2line                                 = NULL;
#define unwind_for_debug                (*pdyn_unwind_for_debug)
#define debug_addr2line_sections_lock   (*pdyn_debug_addr2line_sections_lock)
#define debug_addr2line_sections_unlock (*pdyn_debug_addr2line_sections_unlock)
#define debug_addr2line                 (*pdyn_debug_addr2line)

PRIVATE ATTR_NOINLINE WUNUSED ATTR_SECTION(SECTION_DEBUG_TEXT) void *
NOTHROW(LIBCCALL open_libdebuginfo)(void) {
	void *result;
again:
	result = atomic_read(&pdyn_libdebuginfo);
	if (result == (void *)-1)
		return NULL;
	if (!result) {
		result = dlopen(LIBDEBUGINFO_LIBRARY_NAME, RTLD_LAZY | RTLD_LOCAL);
		if (!result)
			result = (void *)-1;
		if (!atomic_cmpxch(&pdyn_libdebuginfo, NULL, result)) {
			if (result != (void *)-1)
				(void)dlclose(result);
			goto again;
		}
	}
	return result;
}

PRIVATE ATTR_NOINLINE WUNUSED ATTR_SECTION(SECTION_DEBUG_TEXT) bool
NOTHROW(LIBCCALL init_libdebuginfo)(void) {
	void *lib;
	if (pdyn_debug_addr2line_sections_lock)
		return true;
	lib = open_libdebuginfo();
	if (!lib)
		return false;
	*(void **)&pdyn_unwind_for_debug = dlsym(lib, "unwind_for_debug");
	if unlikely(!pdyn_unwind_for_debug)
		return false;
	*(void **)&pdyn_debug_addr2line = dlsym(lib, "debug_addr2line");
	if unlikely(!pdyn_debug_addr2line)
		return false;
	*(void **)&pdyn_debug_addr2line_sections_unlock = dlsym(lib, "debug_addr2line_sections_unlock");
	if unlikely(!pdyn_debug_addr2line_sections_unlock)
		return false;
	COMPILER_WRITE_BARRIER();
	*(void **)&pdyn_debug_addr2line_sections_lock = dlsym(lib, "debug_addr2line_sections_lock");
	if unlikely(!pdyn_debug_addr2line_sections_lock)
		return false;
	return true;
}





/*[[[head:libc_backtrace,hash:CRC-32=0xd9683e49]]]*/
/* >> backtrace(3)
 * Create a  traceback of  up to  `size' instruction  pointers  from
 * the  calling function, their  caller, and so  forth. On KOS, this
 * information is constructed with the help of CFI  instrumentation,
 * and  the  functions  from  `<libunwind/...>'.  However,  on other
 * systems, this function is fairly dumb and relies on all traversed
 * code having been compiled with function frames enabled.
 * @return: * : The actual number of pointers written to `array' (always `<= size') */
INTERN ATTR_SECTION(".text.crt.debug") ATTR_OUTS(1, 2) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_backtrace)(void **array,
                                     __STDC_INT_AS_SIZE_T size)
/*[[[body:libc_backtrace]]]*/
{
	unsigned int result;
	struct lcpustate ost, st;
	if ((int)size <= 1) {
		if unlikely((int)size < 0)
			return libc_seterrno(EINVAL);
		if (!size)
			return 0; /* Nothing to do here :) */
		if (size == 1) {
			/* Simple: Just use `__builtin_return_address()' */
			array[0] = __builtin_return_address(0);
			return 1;
		}
	}
	if (!ENSURE_LIBUNWIND_LOADED() || !init_libdebuginfo())
		return libc_seterrno(ENOENT);
	lcpustate_current(&st);
	for (result = 0; result < size; ++result) {
		unsigned int error;
		memcpy(&ost, &st, sizeof(struct lcpustate));
		error = unwind_for_debug(lcpustate_getpc(&ost),
		                         &unwind_getreg_lcpustate, &ost,
		                         &unwind_setreg_lcpustate, &st);
		if (error != UNWIND_SUCCESS)
			break;
		array[result] = (void *)lcpustate_getpc(&st);
	}
	return result;
}
/*[[[end:libc_backtrace]]]*/

PRIVATE ATTR_SECTION(".rodata.crt.debug") char const
backtrace_default_fmt[] = "%a <%n%D> at %f";
PRIVATE ATTR_SECTION(".rodata.crt.debug") char const
backtrace_missing_str[] = "??" "?";


/*[[[head:libc_backtrace_symbol_printf,hash:CRC-32=0x5f5899fe]]]*/
/* >> backtrace_symbol_printf(3)
 * Print the formatted representation of `address' to `printer'
 *  - The used format is `format' (or "%a <%n%D> at %f" if NULL)
 *  - No trailing linefeed is printed
 *  - If debug information could not be loaded, use "???" for strings
 * @return: * : pformatprinter-compatible return value */
INTERN ATTR_SECTION(".text.crt.debug") ATTR_IN_OPT(4) NONNULL((1)) ssize_t
NOTHROW_NCX(LIBCCALL libc_backtrace_symbol_printf)(pformatprinter printer,
                                                   void *arg,
                                                   void const *address,
                                                   char const *format)
/*[[[body:libc_backtrace_symbol_printf]]]*/
{
	ssize_t temp, result = 0;
	module_t *mod;
	di_addr2line_dl_sections_t dl_sections;
	Dl_info info;
	char const *flush_start;

	/* Load generic ELF symbol information. */
	bzero(&info, sizeof(info));
	dladdr(address, &info);
	if (!info.dli_fname)
		info.dli_fname = backtrace_missing_str;
	if (!info.dli_sname) {
		info.dli_sname = backtrace_missing_str;
		info.dli_saddr = (void *)address;
	}

	/* Try to load extended addr2line information */
	mod = NULL;
	if ((init_libdebuginfo()) &&
	    (mod = dlgethandle(address, DLGETHANDLE_FINCREF)) != NULL) {
		di_addr2line_sections_t sections;
		di_debug_addr2line_t a2l;
		uintptr_t modbase = (uintptr_t)dlmodulebase(mod);

		/* Try to extract debug information about the given address.
		 * HINT: Upon failure, `debug_addr2line_sections_lock()'  fills
		 *       in `dl_sections' for `debug_addr2line_sections_unlock'
		 *       to become a no-op! */
		if (debug_addr2line_sections_lock(mod, &sections, &dl_sections) == DEBUG_INFO_ERROR_SUCCESS &&
		    debug_addr2line(&sections, &a2l, (uintptr_t)address - modbase,
		                    DEBUG_ADDR2LINE_LEVEL_SOURCE,
		                    DEBUG_ADDR2LINE_FNORMAL) == DEBUG_INFO_ERROR_SUCCESS) {
			/* Use debug information strings. */
			if (!a2l.al_rawname)
				a2l.al_rawname = a2l.al_name;
			if (a2l.al_rawname) {
				info.dli_sname = a2l.al_rawname;
				info.dli_saddr = (void *)(modbase + a2l.al_symstart);
				info.dli_fname = dlmodulename(mod);
			}
		}
	}

	/* Time for the meat of it all: processing the format string. */
	if (format == NULL)
		format = backtrace_default_fmt;
	flush_start = format;
	for (;;) {
		char ch = *format;
		if (ch == '\0')
			break;
		if (ch != '%') {
			++format;
			continue;
		}
		/* Flush until here! */
		if (format > flush_start) {
			temp = (*printer)(arg, flush_start,
			                  (size_t)(format - flush_start));
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}

		/* Load the format character. */
		ch = *++format;
		++format;
		switch (ch) {

		case 'a':
			temp = format_printf(printer, arg, "%p", address);
			break;

		case 'n':
			temp = (*printer)(arg, info.dli_sname, strlen(info.dli_sname));
			break;

		case 'D':
		case 'd':
			temp = (ssize_t)(size_t)((uintptr_t)address -
			                         (uintptr_t)info.dli_saddr);
			if (temp != 0 || ch == 'd')
				temp = format_printf(printer, arg, "+%#" PRIxSIZ, (size_t)temp);
			break;

		case 'f':
			temp = (*printer)(arg, info.dli_fname, strlen(info.dli_fname));
			break;

		case '\0':
			--format; /* Special handling for an unescaped, trailing '%' */
			ATTR_FALLTHROUGH
		default:
			/* Skip over the leading '%', but print the following character as-is */
			flush_start = format - 1;
			continue;
		}
		if unlikely(temp < 0)
			goto err;
		result += temp;
		flush_start = format;
	}

	/* Flush trailing data. */
	if (format > flush_start) {
		temp = (*printer)(arg, flush_start,
		                  (size_t)(format - flush_start));
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
out:
	if (mod) {
		(void)debug_addr2line_sections_unlock(&dl_sections);
		(void)dlclose(mod);
	}
	return result;
err:
	result = temp;
	goto out;
}
/*[[[end:libc_backtrace_symbol_printf]]]*/


/*[[[start:exports,hash:CRC-32=0xac1c8535]]]*/
DEFINE_PUBLIC_ALIAS_P(__backtrace,libc_backtrace,ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(void **array, __STDC_INT_AS_SIZE_T size),(array,size));
DEFINE_PUBLIC_ALIAS_P(backtrace,libc_backtrace,ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,NOTHROW_NCX,LIBCCALL,(void **array, __STDC_INT_AS_SIZE_T size),(array,size));
DEFINE_PUBLIC_ALIAS_P(backtrace_symbol_printf,libc_backtrace_symbol_printf,ATTR_IN_OPT(4) NONNULL((1)),ssize_t,NOTHROW_NCX,LIBCCALL,(pformatprinter printer, void *arg, void const *address, char const *format),(printer,arg,address,format));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_EXECINFO_C */
