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
#ifndef GUARD_LIBDL_API_H
#define GUARD_LIBDL_API_H 1

#define __BUILDING_LIBDL 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1


/* Setup a custom CRT configuration for our very specific setup:
 * - Free-standing
 * - Inline system call declarations (s.a. <kos/syscalls.h>)
 * - Custom CRT feature functions (see __CRT_HAVE_* below)
 * - Functions are linked as INTERN
 * - Substitute the rest using implementations from <libc/local/xxx/yyy.h> */
#define __CRT_FREESTANDING
#define __LIBC __INTDEF

/* Disable some format_printf() features that we're not using. */
#define __NO_PRINTF_FLOATING_POINT /* %f, %e, %g, %F, %E, %G */
#define __NO_PRINTF_VINFO          /* %[vinfo] */
#define __NO_PRINTF_GEN            /* %[gen] */
#define __NO_PRINTF_DISASM         /* %[disasm] */
#define __NO_PRINTF_HEX            /* %[hex] */
#define __NO_PRINTF_UNICODE_CHARS  /* %I16c, %I32c, %Lc */
#define __NO_PRINTF_UNICODE_STRING /* %I16s, %I32s, %Ls */
#define __NO_PRINTF_STRERROR       /* %m */
#define __NO_PRINTF_POSITIONAL     /* %1$s */
#define __NO_SCANF_FLOATING_POINT  /* %f, %e, %g, %E, %a */

/* Prevent the global variable  `__peb' from being defined  prematurely
 * (and breaking the visibility of us exporting that variable for real) */
#define ____peb_defined

/* Commit our custom configuration by using it to setup CRT definitions. */
#include <__crt.h>

/* Ensure that our __CRT_HAVE_* namespace is empty by checking for a
 * symbol we can assume to be defined under "normal" configurations. */
#ifdef __CRT_HAVE_memcpy
#error "Bad configuration"
#endif /* __CRT_HAVE_memcpy */

/* Define  CRT features which  may be exposed in
 * headers, that we are explicitly implementing. */

/* Functions defined by libdl itself */
#define __CRT_HAVE_dlfopen
#define __CRT_HAVE_dlexceptaware
#define __CRT_HAVE_dlgethandle
#define __CRT_HAVE_dlgetmodule
#define __CRT_HAVE_dlmodulefd
#define __CRT_HAVE_dlmodulename
#define __CRT_HAVE_dlmodulebase
#define __CRT_HAVE_dllocksection
#define __CRT_HAVE_dlunlocksection
#define __CRT_HAVE_dlsectionname
#define __CRT_HAVE_dlsectionindex
#define __CRT_HAVE_dlsectionmodule
#define __CRT_HAVE_dlinflatesection
#define __CRT_HAVE_dlclearcaches
#define __CRT_HAVE_dltlsallocseg
#define __CRT_HAVE_dltlsfreeseg
#define __CRT_HAVE_dltlsalloc
#define __CRT_HAVE_dltlsfree
#define __CRT_HAVE_dltlsaddr
#define __CRT_HAVE_dlauxctrl
#define __CRT_HAVE_dladdr
#define __CRT_HAVE_dl_iterate_phdr
#define __CRT_HAVE_dlopen
#define __CRT_HAVE_dlclose
#define __CRT_HAVE_dlsym
#define __CRT_HAVE_dlerror

/* Functions defined through dlmalloc */
#define __CRT_HAVE_malloc
#define __CRT_HAVE_free
#define __CRT_HAVE_cfree
#define __CRT_HAVE_calloc
#define __CRT_HAVE_realloc
#define __CRT_HAVE_realloc_in_place
#define __CRT_HAVE_memalign
#define __CRT_HAVE_posix_memalign
#define __CRT_HAVE_valloc
#define __CRT_HAVE_mallopt
#define __CRT_HAVE_malloc_footprint
#define __CRT_HAVE_malloc_max_footprint
#define __CRT_HAVE_malloc_footprint_limit
#define __CRT_HAVE_malloc_set_footprint_limit
#define __CRT_HAVE_mallinfo
#define __CRT_HAVE_independent_calloc
#define __CRT_HAVE_independent_comalloc
#define __CRT_HAVE_bulk_free
#define __CRT_HAVE_pvalloc
#define __CRT_HAVE_malloc_trim
#define __CRT_HAVE_malloc_usable_size
#define __CRT_HAVE__msize

/* These are defined explicitly */
#define __CRT_HAVE_syslog_printer /* Required for using `syslog()' */
#ifndef NDEBUG
#ifndef __CRT_HAVE___afail
#define __CRT_HAVE___afail
#endif /* !__CRT_HAVE___afail */
#ifndef __CRT_HAVE___afailf
#define __CRT_HAVE___afailf
#endif /* !__CRT_HAVE___afailf */
#define __CRT_HAVE___stack_chk_guard
#define __CRT_HAVE___stack_chk_fail
#define __CRT_HAVE___stack_chk_fail_local
#endif /* !NDEBUG */

#undef __LIBC
#define __LIBC __INTDEF

#include <hybrid/compiler.h>

#include <hybrid/host.h>

#include <kos/anno.h>
#include <kos/config/config.h> /* Pull in config-specific macro overrides */
#include <kos/types.h>

#include <libdl/api.h>

#define CC        LIBDL_CC    /* Internal and hidden API calling convention */
#define VCC       LIBDL_VCC   /* *ditto* */
#define DLFCN_CC  __DLFCN_CC  /* Public (aka. <dlfcn.h>) calling convention */
#define DLFCN_VCC __DLFCN_VCC /* *ditto* */

#ifndef FCALL
#define FCALL __FCALL
#endif /* FCALL */
#ifndef WEAK
#define WEAK __WEAK
#endif /* !WEAK */
#ifndef REF
#define REF __REF
#endif /* !REF */
#ifndef REF_IF
#define REF_IF __REF_IF
#endif /* !REF_IF */
#ifndef LIBCCALL
#define LIBCCALL __LIBCCALL
#endif /* !LIBCCALL */
#ifndef LIBDCALL
#define LIBDCALL __LIBDCALL
#endif /* !LIBDCALL */
#ifndef VLIBCCALL
#define VLIBCCALL __VLIBCCALL
#endif /* !VLIBCCALL */
#ifndef VLIBDCALL
#define VLIBDCALL __VLIBDCALL
#endif /* !VLIBDCALL */

#endif /* !GUARD_LIBDL_API_H */
