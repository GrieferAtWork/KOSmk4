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
#ifndef GUARD_LIBDL_API_H
#define GUARD_LIBDL_API_H 1

#define __BUILDING_LIBDL 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1


/* Setup a custom CRT configuration for our very specific setup:
 *   - Free-standing
 *   - Custom CRT feature functions (see __CRT_HAVE_* below)
 *   - Functions are linked as INTERN
 *   - Substitute the rest using implementations from <local/xxx/yyy.h> */
#define __CRT_FREESTANDING 1
#define __LIBC __INTDEF

/* Disable some format_printf() features that we're not using. */
#define __NO_PRINTF_FLOATING_POINT 1 /* %f, %e, %g, %F, %E, %G */
#define __NO_PRINTF_VINFO          1 /* %[vinfo] */
#define __NO_PRINTF_GEN            1 /* %[gen] */
#define __NO_PRINTF_DISASM         1 /* %[disasm] */
#define __NO_PRINTF_HEX            1 /* %[hex] */
#define __NO_PRINTF_UNICODE_CHARS  1 /* %I16c, %I32c, %Lc */
#define __NO_PRINTF_UNICODE_STRING 1 /* %I16s, %I32s, %Ls */
#define __NO_SCANF_FLOATING_POINT  1 /* %f, %e, %g, %E, %a */

/* Invoke system calls as inline (NOTE: We don't enable support for
 * i386 sysenter optimizations because this would require linking
 * against parts of the libc source tree, as well as add an unnecessary
 * page-fault when the first system call is invoked. - libdl should have
 * minimal startup time, and be optimized for size; not performance, both
 * of which are followed more closely by always just using `int 80h') */
#define __WANT_INLINE_SYSCALLS 1

/* Prevent the global variable `__peb' from being defined prematurely
 * (and breaking the visibility of us exporting that variable for real) */
#define ____peb_defined 1

/* Commit our custom configuration by using it to setup-CRT definitions. */
#include <__crt.h>

#ifdef __CRT_HAVE_memcpy
#error "Bad configuration"
#endif /* __CRT_HAVE_memcpy */

/* Define CRT features which may be exposed in
 * headers, that we are explicitly implementing. */

/* Functions defined by libdl itself */
#define __CRT_HAVE_dlfopen 1
#define __CRT_HAVE_dlexceptaware 1
#define __CRT_HAVE_dlgethandle 1
#define __CRT_HAVE_dlgetmodule 1
#define __CRT_HAVE_dlmodulefd 1
#define __CRT_HAVE_dlmodulename 1
#define __CRT_HAVE_dlmodulebase 1
#define __CRT_HAVE_dllocksection 1
#define __CRT_HAVE_dlunlocksection 1
#define __CRT_HAVE_dlsectionname 1
#define __CRT_HAVE_dlsectionindex 1
#define __CRT_HAVE_dlsectionmodule 1
#define __CRT_HAVE_dlinflatesection 1
#define __CRT_HAVE_dlclearcaches 1
#define __CRT_HAVE_dltlsallocseg 1
#define __CRT_HAVE_dltlsfreeseg 1
#define __CRT_HAVE_dltlsalloc 1
#define __CRT_HAVE_dltlsfree 1
#define __CRT_HAVE_dltlsaddr 1
#define __CRT_HAVE_dlauxctrl 1
#define __CRT_HAVE_dladdr 1
#define __CRT_HAVE_dl_iterate_phdr 1
#define __CRT_HAVE_dlopen 1
#define __CRT_HAVE_dlclose 1
#define __CRT_HAVE_dlsym 1
#define __CRT_HAVE_dlerror 1

/* Functions defined through dlmalloc */
#define __CRT_HAVE_malloc 1
#define __CRT_HAVE_free 1
#define __CRT_HAVE_cfree 1
#define __CRT_HAVE_calloc 1
#define __CRT_HAVE_realloc 1
#define __CRT_HAVE_realloc_in_place 1
#define __CRT_HAVE_memalign 1
#define __CRT_HAVE_posix_memalign 1
#define __CRT_HAVE_valloc 1
#define __CRT_HAVE_mallopt 1
#define __CRT_HAVE_malloc_footprint 1
#define __CRT_HAVE_malloc_max_footprint 1
#define __CRT_HAVE_malloc_footprint_limit 1
#define __CRT_HAVE_malloc_set_footprint_limit 1
#define __CRT_HAVE_mallinfo 1
#define __CRT_HAVE_independent_calloc 1
#define __CRT_HAVE_independent_comalloc 1
#define __CRT_HAVE_bulk_free 1
#define __CRT_HAVE_pvalloc 1
#define __CRT_HAVE_malloc_trim 1
#define __CRT_HAVE_malloc_usable_size 1
#define __CRT_HAVE__msize 1

/* These are defined explicitly */
#define __CRT_HAVE_syslog_printer 1 /* Required for using `syslog()' */
#ifndef NDEBUG
#define __CRT_HAVE___afail 1
#define __CRT_HAVE___afailf 1
#define __CRT_HAVE___stack_chk_guard 1
#define __CRT_HAVE___stack_chk_fail 1
#define __CRT_HAVE___stack_chk_fail_local 1
#endif /* !NDEBUG */

#undef __LIBC
#define __LIBC __INTDEF

#include <hybrid/compiler.h>
#include <hybrid/host.h>
#include <kos/types.h>
#include <libdl/api.h>

#define CC  LIBDL_CC
#define VCC LIBDL_VCC

#ifndef FCALL
#define FCALL __FCALL
#endif /* FCALL */
#ifndef WEAK
#define WEAK /* nothing */
#endif /* !WEAK */
#define REF       /* nothing */
#define REF_IF(x) /* nothing */
#ifndef LIBCCALL
#define LIBCCALL  __LIBCCALL
#endif /* !LIBCCALL */
#ifndef LIBDCALL
#define LIBDCALL  __LIBDCALL
#endif /* !LIBDCALL */
#ifndef VLIBCCALL
#define VLIBCCALL __VLIBCCALL
#endif /* !VLIBCCALL */
#ifndef VLIBDCALL
#define VLIBDCALL __VLIBDCALL
#endif /* !VLIBDCALL */
#ifndef DLFCN_CC
#define DLFCN_CC __DLFCN_CC
#endif /* !DLFCN_CC */
#ifndef DLFCN_VCC
#define DLFCN_VCC __DLFCN_VCC
#endif /* !DLFCN_VCC */

/* Addressable sections of the RTLD driver itself.
 * Of note here are mostly the .eh_frame and .gcc_except_table
 * sections, which are required for allowing exceptions to work
 * properly when being propagated through the callbacks invoked
 * by the RTLD driver.
 * NOTE: Each section has 2 symbols defined by the linker script:
 *       `__rtld_<name>_start' and `__rtld_<name>_end', that are
 *       used to lazily fill in section information as-per the
 *       request of a call to `dllocksection()' when given a handle
 *       for the RTLD core library. */
#define BUILTIN_SECTIONS_COUNT 6
#define BUILTIN_SECTIONS_ENUMERATE(cb)                                                    \
	cb(0, ".text",             text,             SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR) \
	cb(1, ".rodata",           rodata,           SHT_PROGBITS, SHF_ALLOC)                 \
	cb(2, ".eh_frame",         eh_frame,         SHT_PROGBITS, SHF_ALLOC)                 \
	cb(3, ".gcc_except_table", gcc_except_table, SHT_PROGBITS, SHF_ALLOC)                 \
	cb(4, ".data",             data,             SHT_PROGBITS, SHF_ALLOC | SHF_WRITE)     \
	cb(5, ".bss",              bss,              SHT_NOBITS,   SHF_ALLOC | SHF_WRITE)

/* For the purpose of being able to safely handle exceptions the same way
 * loaded modules do, a couple of global functions that aren't defined by
 * the RTLD driver itself need to be provided by loaded libraries
 * Note that these functions are only needed when thrown exceptions pass
 * through functions apart of the RTLD core, meaning that when exceptions
 * aren't being used by the hosted application or its libraries, or even
 * if no exception is ever thrown from an __attribute__((constructor)) function,
 * these are never loaded. - However, if they are, then they must be provided
 * by one of the loaded libraries (usually that library simply being `libc.so')
 * If one of these functions is used, but isn't provided by any of the loaded
 * modules, the hosted application gets terminated ungracefully, and an error
 * message is written to the system log.
 * HINT: When required, the functions are searched for the same way
 *       `dlsym(RTLD_DEFAULT, ...)' would search for them, following regular
 *       symbol lookup order throughout all globally visible libraries.
 * NOTE: The behavior of these functions is specified and standardized in different
 *       places. - Search around the project and on the internet to find out what
 *       each of these has to do, and how it has to do exactly that. */
#define BUILTIN_GLOBALS_ENUMERATE(cb) \
	cb(__gxx_personality_v0)          \
	cb(__cxa_begin_catch)             \
	cb(__cxa_end_catch)               \
	cb(__cxa_rethrow)                 \
	cb(_Unwind_Resume)


/* TODO: Add a way of extending the RTLD driver with custom executable format
 *       back-ends, such as (once again) allowing PE binaries to be loaded.
 * -> There should be a seperate shared librariy `libdl-pe.so' similar to
 *    `libdl.so' that can simply be loaded using `dlopen()' and contains
 *    everything that's necessary to implement dynamic linking of PE binaries.
 *    As such, `DlModule' also needs to be given an optional v-table that can
 *    be filled with overrides for functions such as dlsym() or dllocksection(). */


#endif /* !GUARD_LIBDL_API_H */
