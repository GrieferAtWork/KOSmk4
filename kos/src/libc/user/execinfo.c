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
#ifndef GUARD_LIBC_USER_EXECINFO_C
#define GUARD_LIBC_USER_EXECINFO_C 1

#include "../api.h"
/**/

#include <hybrid/align.h>
#include <hybrid/atomic.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <format-printer.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <libdebuginfo/addr2line.h>
#include <libunwind/unwind.h>

#include "../libc/dl.h"
#include "execinfo.h"

DECL_BEGIN

#define SECTION_DEBUG_TEXT(x)   ATTR_SECTION(".text.crt.debug" x)
#define SECTION_DEBUG_BSS(x)    ATTR_SECTION(".bss.crt.debug" x)
#define SECTION_DEBUG_STRING(x) ATTR_SECTION(".rodata.crt.debug" x)

INTDEF void *pdyn_libunwind; /* From `../libc/except.c' */
INTDEF void LIBCCALL initialize_libunwind(void); /* From `../libc/except.c' */

PRIVATE SECTION_DEBUG_BSS("pdyn_unwind") PUNWIND pdyn_unwind = NULL;
PRIVATE SECTION_DEBUG_BSS("pdyn_unwind_getreg_lcpustate") PUNWIND_GETREG_LCPUSTATE pdyn_unwind_getreg_lcpustate = NULL;
PRIVATE SECTION_DEBUG_BSS("pdyn_unwind_setreg_lcpustate") PUNWIND_SETREG_LCPUSTATE pdyn_unwind_setreg_lcpustate = NULL;
PRIVATE SECTION_DEBUG_STRING("name_unwind") char const name_unwind[] = "unwind";
PRIVATE SECTION_DEBUG_STRING("name_unwind_getreg_lcpustate") char const name_unwind_getreg_lcpustate[] = "unwind_getreg_lcpustate";
PRIVATE SECTION_DEBUG_STRING("name_unwind_setreg_lcpustate") char const name_unwind_setreg_lcpustate[] = "unwind_setreg_lcpustate";

PRIVATE bool LIBCCALL initialize_libunwind_debug(void) {
	initialize_libunwind();
#define BIND(func, name)                                                 \
	if unlikely((*(void **)&func = dlsym(pdyn_libunwind, name)) == NULL) \
		goto err_init_failed
	BIND(pdyn_unwind, name_unwind);
	BIND(pdyn_unwind_getreg_lcpustate, name_unwind_getreg_lcpustate);
	BIND(pdyn_unwind_setreg_lcpustate, name_unwind_setreg_lcpustate);
#undef BIND
	return true;
err_init_failed:
	return false;
}

#define unwind                   (*pdyn_unwind)
#define unwind_getreg_lcpustate  (*pdyn_unwind_getreg_lcpustate)
#define unwind_setreg_lcpustate  (*pdyn_unwind_setreg_lcpustate)

#define ENSURE_LIBUNWIND_LOADED() \
	(ATOMIC_READ(pdyn_unwind) != NULL || initialize_libunwind_debug())


PRIVATE SECTION_DEBUG_BSS("pdyn_libdebuginfo") void *pdyn_libdebuginfo = NULL;
PRIVATE SECTION_DEBUG_BSS("pdyn_debug_dllocksections")     PDEBUG_DLLOCKSECTIONS     pdyn_debug_dllocksections     = NULL;
PRIVATE SECTION_DEBUG_BSS("pdyn_debug_dlunlocksections")   PDEBUG_DLUNLOCKSECTIONS   pdyn_debug_dlunlocksections   = NULL;
PRIVATE SECTION_DEBUG_BSS("pdyn_debug_sections_addr2line") PDEBUG_SECTIONS_ADDR2LINE pdyn_debug_sections_addr2line = NULL;

#define debug_dllocksections     (*pdyn_debug_dllocksections)
#define debug_dlunlocksections   (*pdyn_debug_dlunlocksections)
#define debug_sections_addr2line (*pdyn_debug_sections_addr2line)

PRIVATE ATTR_NOINLINE WUNUSED SECTION_DEBUG_TEXT("get_libdebuginfo")
void *LIBCCALL get_libdebuginfo(void) {
	void *result;
again:
	result = ATOMIC_READ(pdyn_libdebuginfo);
	if (result == (void *)-1)
		return NULL;
	if (!result) {
		result = dlopen(LIBDEBUGINFO_LIBRARY_NAME, RTLD_LOCAL);
		if (!result)
			result = (void *)-1;
		if (!ATOMIC_CMPXCH(pdyn_libdebuginfo, NULL, result)) {
			if (result != (void *)-1)
				dlclose(result);
			goto again;
		}
	}
	return result;
}

PRIVATE ATTR_NOINLINE WUNUSED SECTION_DEBUG_TEXT("init_libdebuginfo")
bool LIBCCALL init_libdebuginfo(void) {
	void *lib;
	if (pdyn_debug_dllocksections)
		return true;
	lib = get_libdebuginfo();
	if (!lib)
		return false;
	*(void **)&pdyn_debug_sections_addr2line = dlsym(lib, "debug_sections_addr2line");
	if unlikely(!pdyn_debug_sections_addr2line)
		return false;
	*(void **)&pdyn_debug_dlunlocksections = dlsym(lib, "debug_dlunlocksections");
	if unlikely(!pdyn_debug_dlunlocksections)
		return false;
	COMPILER_WRITE_BARRIER();
	*(void **)&pdyn_debug_dllocksections = dlsym(lib, "debug_dllocksections");
	if unlikely(!pdyn_debug_dllocksections)
		return false;
	return true;
}



/*[[[start:implementation]]]*/

/*[[[head:libc_backtrace,hash:CRC-32=0xb681b400]]]*/
/* Create a traceback of up to `SIZE' instruction pointers from
 * the calling function, their caller, and so forth. On KOS, this
 * information is constructed with the help of CFI instrumentation,
 * and the function from `<libunwind/...>'. However, on other systems,
 * this function is fairly dump and relies on all traversed code
 * having been compiled with function frames enabled.
 * @return: * : The actual number of pointers written to `ARRAY' (always `<= SIZE') */
INTERN ATTR_SECTION(".text.crt.debug") NONNULL((1)) __STDC_INT_AS_SIZE_T
NOTHROW_NCX(LIBCCALL libc_backtrace)(void **array,
                                     __STDC_INT_AS_SIZE_T size)
/*[[[body:libc_backtrace]]]*/
{
	unsigned int result;
	struct lcpustate ost, st;
	if unlikely((int)size < 0) {
		libc_seterrno(EINVAL);
		return -1;
	}
	if (!ENSURE_LIBUNWIND_LOADED()) {
		libc_seterrno(ENOENT);
		return -1;
	}
	lcpustate_current(&st);
	for (result = 0; result < size; ++result) {
		unsigned int error;
		memcpy(&ost, &st, sizeof(struct lcpustate));
		error = unwind((void *)lcpustate_getpc(&ost),
		               &unwind_getreg_lcpustate, &ost,
		               &unwind_setreg_lcpustate, &st);
		if (error != UNWIND_SUCCESS)
			break;
		array[result] = (void *)lcpustate_getpc(&st);
	}
	return result;
}
/*[[[end:libc_backtrace]]]*/

PRIVATE ATTR_SECTION(".text.crt.debug.print_function_name") ssize_t
NOTHROW_NCX(LIBCCALL print_function_name)(void *pc,
                                          pformatprinter printer,
                                          void *arg) {
	void *mod;
	ssize_t result;
	di_debug_sections_t sections;
    di_dl_debug_sections_t dl_sections;
	di_debug_addr2line_t a2l;
	/* Figure out the module mapped at the given program counter. */
	mod = dlgethandle(pc, DLGETHANDLE_FINCREF);
	if unlikely(!mod)
		goto err0;
	/* Load debug sections for that module. */
	if (debug_dllocksections(mod, &sections, &dl_sections) != DEBUG_INFO_ERROR_SUCCESS)
		goto err0_handle;
	/* Try to extract debug information about the given address. */
	if (debug_sections_addr2line(&sections, &a2l,
	                             (uintptr_t)pc - (uintptr_t)dlmodulebase(mod),
	                             DEBUG_ADDR2LINE_LEVEL_SOURCE,
	                             DEBUG_ADDR2LINE_FNORMAL) != DEBUG_INFO_ERROR_SUCCESS)
		goto err0_sect;
	if (!a2l.al_rawname)
		a2l.al_rawname = a2l.al_name;
	if (!a2l.al_rawname)
		goto err0_sect;
	/* Print the function's name. */
	result = (*printer)(arg, a2l.al_rawname, strlen(a2l.al_rawname));
	/* Release references to acquired data. */
	debug_dlunlocksections(&dl_sections);
	dlclose(mod);
	return result;
err0_sect:
	debug_dlunlocksections(&dl_sections);
err0_handle:
	dlclose(mod);
err0:
	return 0;
}

/*[[[head:libc_backtrace_symbols,hash:CRC-32=0xd6351c6f]]]*/
/* Return an array of exactly `size' elements that contains the
 * names associated with program-counters from the given `ARRAY'
 * This function is meant to be used together with `backtrace(3)'.
 * On KOS, the names of functions are gathered with the help of
 * functions from `<libdebuginfo/...>', meaning that many sources of
 * function names are looked at, including `.dynsym' and `.debug_info'
 * On other systems, this function is fairly dump and only looks at
 * names from `.dynsym', meaning that functions not declared as `PUBLIC'
 * would not show up.
 * The returned pointer is a size-element long vector of strings
 * describing the names of functions, and should be freed() using
 * `free(3)'. Note however that you must _ONLY_ `free(return)', and
 * not the individual strings pointed-to by that vector!
 * @return: * :   A heap pointer to a vector of function names
 * @return: NULL: Insufficient heap memory available */
INTERN ATTR_SECTION(".text.crt.debug") NONNULL((1)) char **
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols)(void *const *array,
                                             __STDC_INT_AS_SIZE_T size)
/*[[[body:libc_backtrace_symbols]]]*/
{
	char **result;
	unsigned int i;
	struct format_aprintf_data data;
	if unlikely((int)size < 0) {
		libc_seterrno(EINVAL);
		return NULL;
	}
	if (!init_libdebuginfo()) {
		libc_seterrno(ENOENT);
		return NULL;
	}
	format_aprintf_data_init(&data);
	/* Make space for the string array itself. */
	if unlikely(!format_aprintf_alloc(&data, CEILDIV((size + 1) * sizeof(char *), sizeof(char))))
		goto err;
	for (i = 0; i < size; ++i) {
		PRIVATE SECTION_DEBUG_STRING("debug_empty_string") char const debug_empty_string[1] = { 0 };
		if unlikely(print_function_name(array[i], &format_aprintf_printer, &data) < 0)
			goto err;
		if unlikely(format_aprintf_printer(array[i], debug_empty_string, 1) < 0)
			goto err;
	}
	result = (char **)format_aprintf_pack(&data, NULL);
	if likely(result) {
		char *name = (char *)result + CEILDIV((size + 1) *
		                                      sizeof(char *),
		                                      sizeof(char));
		for (i = 0; i < size; ++i, name = strend(name) + 1)
			result[i] = name;
		result[i] = NULL;
	}
	return result;
err:
	format_aprintf_data_fini(&data);
	return NULL;
}
/*[[[end:libc_backtrace_symbols]]]*/

/*[[[head:libc_backtrace_symbols_fd,hash:CRC-32=0x722999a8]]]*/
/* Same as `backtrace_symbols()', but rather than return a vector
 * of symbol names, print the names directly to `fd', such that
 * one function NAME will be written per line, with `size' lines
 * written in total. */
INTERN ATTR_SECTION(".text.crt.debug") NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_backtrace_symbols_fd)(void *const *array,
                                                __STDC_INT_AS_SIZE_T size,
                                                fd_t fd)
/*[[[body:libc_backtrace_symbols_fd]]]*/
{
	ssize_t error;
	unsigned int i;
	if unlikely((int)size < 0)
		return;
	if (!init_libdebuginfo())
		return;
	for (i = 0; i < size; ++i) {
		PRIVATE SECTION_DEBUG_STRING("debug_lf") char const debug_lf[1] = { '\n' };
		PRIVATE SECTION_DEBUG_STRING("debug_unknown_name") char const debug_unknown_name[1] = { '?' };
#ifndef __LIBCCALL_IS_FORMATPRINTER_CC
#error "Shouldn't happen?"
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC */
		error = print_function_name(array[i],
		                            (pformatprinter)(void *)&write,
		                            (void *)(uintptr_t)(unsigned int)fd);
		if unlikely(error < 0)
			break;
		if (!error)
			write(fd, debug_unknown_name, sizeof(debug_unknown_name));
		write(fd, debug_lf, sizeof(debug_lf));
	}
}
/*[[[end:libc_backtrace_symbols_fd]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xf511d171]]]*/
DEFINE_PUBLIC_ALIAS(__backtrace, libc_backtrace);
DEFINE_PUBLIC_ALIAS(backtrace, libc_backtrace);
DEFINE_PUBLIC_ALIAS(__backtrace_symbols, libc_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(backtrace_symbols, libc_backtrace_symbols);
DEFINE_PUBLIC_ALIAS(__backtrace_symbols_fd, libc_backtrace_symbols_fd);
DEFINE_PUBLIC_ALIAS(backtrace_symbols_fd, libc_backtrace_symbols_fd);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_EXECINFO_C */
