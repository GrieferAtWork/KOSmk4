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
#ifndef _BITS_DLFCN_H
#define _BITS_DLFCN_H 1

#include <__stdinc.h>
#include <features.h>

__SYSDECL_BEGIN

/* System dependent definitions for run-time dynamic loading.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/* The MODE argument to `dlopen' contains one of the following: */
#ifndef RTLD_LAZY
#define RTLD_LAZY         0x00001 /* Lazy function call binding. */
#endif /* !RTLD_LAZY */
#ifndef RTLD_NOW
#define RTLD_NOW          0x00002 /* Immediate function call binding. */
#endif /* !RTLD_NOW */
#ifndef RTLD_BINDING_MASK
#define RTLD_BINDING_MASK 0x00003 /* Mask of binding time value. */
#endif /* !RTLD_BINDING_MASK */

#ifndef RTLD_NOLOAD
#ifdef __CRT_CYG_PRIMARY
#define RTLD_NOLOAD       0x00010 /* Do not load the object. */
#else /* __CRT_CYG_PRIMARY */
#define RTLD_NOLOAD       0x00004 /* Do not load the object. */
#endif /* !__CRT_CYG_PRIMARY */
#endif /* !RTLD_NOLOAD */

/* If the associated library uses a symbol that it itself also defines,
 * the the library will use its own symbol, rather than go through the
 * global scope to find the first (primary) definition of some symbol.
 * e.g.:
 *    - libfoo: (linked against `libc.so')
 *       >> PUBLIC void *memcpy(void *dst, void const *src, size_t num_bytes) { ... }
 *       >> PUBLIC void foo() {
 *       >>     memcpy(a, b, 42);
 *       >> }
 *    - libc:
 *       >> PUBLIC void *memcpy(void *dst, void const *src, size_t num_bytes) { ... }
 * - When `libfoo' is loaded without `RTLD_DEEPBIND', its function
 *   `foo' will be using the memcpy() function provided by libc.so
 * - When `libfoo' is loaded with `RTLD_DEEPBIND', its function
 *   `foo' will be using the memcpy() function it defines itself.
 * NOTE: This is the same as `DF_SYMBOLIC'
 */
#ifndef RTLD_DEEPBIND
#ifdef __CRT_CYG_PRIMARY
#define RTLD_DEEPBIND     0x00020 /* Use deep binding. */
#else /* __CRT_CYG_PRIMARY */
#define RTLD_DEEPBIND     0x00008 /* Use deep binding. */
#endif /* !__CRT_CYG_PRIMARY */
#endif /* !RTLD_DEEPBIND */

/* If the following bit is set in the MODE argument to `dlopen',
 * the symbols of the loaded object and its dependencies are made
 * visible as if the object were linked directly into the program. */
#ifndef RTLD_GLOBAL
#define RTLD_GLOBAL       0x00100
#endif /* !RTLD_GLOBAL */

/* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL.
 * The implementation does this by default and so we can define the
 * value to zero. */
#ifndef RTLD_LOCAL
#define RTLD_LOCAL        0x00000
#endif /* !RTLD_LOCAL */

/* Do not delete object when closed.  */
#ifndef RTLD_NODELETE
#ifdef __CRT_CYG_PRIMARY
#define RTLD_NODELETE     0x00008
#else /* __CRT_CYG_PRIMARY */
#define RTLD_NODELETE     0x01000
#endif /* !__CRT_CYG_PRIMARY */
#endif /* !RTLD_NODELETE */

#if defined(__USE_KOS) && defined(__KOS__)
/* KOS Extension: Don't run module initializers, and consequently skip running finalizers as well.
 * When set, `dlopen()' will immeditaly return to the caller upon success,
 * rather than running initializers of all affected libraries first.
 * HINT: You may run initializers (and finalizers during exit()) at a
 *       later time by calling `dlopen()' again without passing this flag.
 * WARNING: Initializers of the newly loaded dependencies will not be executed either! */
#ifndef RTLD_NOINIT
#define RTLD_NOINIT    0x80000000
#endif /* !RTLD_NOINIT */
#endif /* __USE_KOS && __KOS__ */

#ifdef __USE_GNU
#ifndef DL_CALL_FCT
/* To support profiling of shared objects it is a good idea to call
 * the function found using `dlsym' using the following macro since
 * these calls do not use the PLT.  But this would mean the dynamic
 * loader has no chance to find out when the function is called.  The
 * macro applies the necessary magic so that profiling is possible.
 * Rewrite
 *  foo = (*fctp)(arg1,arg2);
 * into
 *      foo = DL_CALL_FCT(fctp,(arg1,arg2));
 */
#ifdef __KERNEL__
#define DL_CALL_FCT(fctp, args) (*(fctp)) args)
#else /* __KERNEL__ */
#define DL_CALL_FCT(fctp, args) \
	(_dl_mcount_wrapper_check((void *)(fctp)), (*(fctp))args)
__IMPDEF void (_dl_mcount_wrapper_check)(void *__selfpc);
#endif /* !__KERNEL__ */
#endif /* !DL_CALL_FCT */
#endif /* __USE_GNU */

__SYSDECL_END

#endif /* !_BITS_DLFCN_H */
