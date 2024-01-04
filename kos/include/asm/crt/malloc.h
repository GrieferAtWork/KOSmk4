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
#ifndef _ASM_CRT_MALLOC_H
#define _ASM_CRT_MALLOC_H 1

#include <__stdinc.h>
#include <__crt.h>

#if defined(__CRT_CYG) || defined(__CRT_NEWLIB)
#define __M_TRIM_THRESHOLD (-1)
#define __M_TOP_PAD        (-2)
#define __M_MMAP_THRESHOLD (-3)
#define __M_MMAP_MAX       (-4)
#elif defined(__CRT_LIBC6)
#define __M_TRIM_THRESHOLD (-1)
#define __M_TOP_PAD        (-2)
#define __M_MMAP_THRESHOLD (-3)
#define __M_MMAP_MAX       (-4)
#define __M_CHECK_ACTION   (-5)
#define __M_PERTURB        (-6)
#define __M_ARENA_TEST     (-7)
#define __M_ARENA_MAX      (-8)
#elif defined(__CRT_uCLIBC)
#define __M_MXFAST         1
#define __M_NLBLKS         2
#define __M_GRAIN          3
#define __M_KEEP           4
#define __M_TRIM_THRESHOLD (-1)
#define __M_TOP_PAD        (-2)
#define __M_MMAP_THRESHOLD (-3)
#define __M_MMAP_MAX       (-4)
#define __M_CHECK_ACTION   (-5)
#define __M_PERTURB        (-6)
#elif defined(__CRT_DOS) && !defined(__CRT_KOS)
#define __MALLOC_ZERO_IS_NONNULL
#undef __REALLOC_ZERO_IS_NONNULL /* Nope, `realloc(p, 0)' acts like `free(p)'... */
#elif defined(__CRT_KOS) || defined(__CRT_GLC) || defined(__KOS__)
/* malloc behavior attributes. */
#ifndef __clang_tidy__
#define __MALLOC_ZERO_IS_NONNULL
#define __REALLOC_ZERO_IS_NONNULL
#endif /* !__clang_tidy__ */

/* Options for `mallopt(3)' */
#define __M_MXFAST         1 /* XXX: Not implemented on KOS */
#define __M_NLBLKS         2 /* XXX: Not implemented on KOS */
#define __M_GRAIN          3 /* XXX: Not implemented on KOS */
#define __M_KEEP           4 /* XXX: Not implemented on KOS */
#define __M_TRIM_THRESHOLD (-1)
#define __M_TOP_PAD        (-2) /* XXX: Not implemented on KOS */
#define __M_MMAP_THRESHOLD (-3)
#define __M_MMAP_MAX       (-4) /* XXX: Not implemented on KOS */
#define __M_CHECK_ACTION   (-5) /* XXX: Not implemented on KOS */
#define __M_PERTURB        (-6) /* XXX: Not implemented on KOS */
#define __M_ARENA_TEST     (-7) /* XXX: Not implemented on KOS */
#define __M_ARENA_MAX      (-8) /* XXX: Not implemented on KOS */
#if defined(__CRT_KOS) || defined(__KOS__)
#define __M_GRANULARITY (-101)
#endif /* __CRT_KOS || __KOS__ */
#elif defined(__solaris__)
#define __M_MXFAST 1
#define __M_NLBLKS 2
#define __M_GRAIN  3
#define __M_KEEP   4
#endif /* ... */


#endif /* !_ASM_CRT_MALLOC_H */
