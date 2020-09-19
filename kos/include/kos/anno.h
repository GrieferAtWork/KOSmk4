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
#ifndef _KOS_ANNO_H
#define _KOS_ANNO_H 1

/* KOS-specific data/function annotations. */

#include <__stdinc.h>

#define __PHYS          /* Annotation for physical pointers */
#define __VIRT          /* Annotation for virtual pointers */
#define __USER          /* Annotation for user-space memory (default outside kernel). */
#define __CHECKED       /* Annotation for checked memory. */
#define __UNCHECKED     /* Annotation for unchecked memory. */
#define __KERNEL        /* Annotation for kernel-space memory (default within kernel). */
#define __WEAK          /* Annotation for weakly referenced data/data updated randomly with both the old/new state remaining valid. */
#define __REF           /* Annotation for reference holders/transfers.
                         * When used on a struct-field/local/global variable: Reference storage
                         * When used on a return type: The function returns a reference
                         * When used on an argument: The function inherited a reference (but look out for `inherit(<condition>)' annotations) */
#define __REF_IF(x)     /* Same as `__REF', but only when `x' is true. */
#define __NOBLOCK       /* Annotation for functions that are guarantied to never block,
                         * making them safe to-be called from any asynchronous context. */
#define __NOBLOCK_IF(x) /* Same as `__NOBLOCK', but only when `x' is true. */
#define __NOPREEMPT     /* Annotation for functions that may only be called with preemption disabled. */
#define __NOCONNECT     /* Annotation for functions which may only be called when the calling
                         * thread isn't already connected to a signal. (only affects kernel-space) */
#define __THROWS(...)   /* Annotation for the set of error codes/classes/sub-classes that may be thrown by a function.
                         * You may include `...' as a possible error code to indicate that the function
                         * is also allowed to throw any other kind of exception, usually indicative of
                         * the function following a path that includes a call to `task_serve()'
                         * Note however that this is merely for documentation purposes, as well as to
                         * document the ~expected~ error codes (e.g. anything that can throw E_SEGFAULT
                         * usually does so by accessing user-space memory, which also implies access to
                         * VIO callbacks, and the fact that VIO is also allowed to throw arbitrary exceptions,
                         * meaning that technically speaking, `E_SEGFAULT' would also imply `...').
                         * Any function that isn't `__NOTHROW()' is still always allowed to throw any error
                         * that isn't apart of the `__THROWS()' set. */
#define __THROWING      /* Use in place of __NOTHROW() for the same effect as `__THROWS(...)' */


#if defined(__clang_tidy__) && defined(__cplusplus)
/* This forces warnings in clang-tidy, if a THROWS-annotated
 * function is called from another function annotated as NOTHROW()
 * s.a. `bugprone-exception-escape' */
#undef __THROWS
#define __THROWS(...) throw(int)
#undef __THROWING
#define __THROWING(...) (__VA_ARGS__) __PRIVATE_THROWING
#define __PRIVATE_THROWING(...) (__VA_ARGS__) throw(int)
#elif defined(__INTELLISENSE__) && defined(__cplusplus)
/* Highlight invalid use of this annotation in intellisense! */
#undef __THROWS
#define __THROWS(...) noexcept(false)
#undef __THROWING
#define __THROWING(...) (__VA_ARGS__) __PRIVATE_THROWING
#define __PRIVATE_THROWING(...) (__VA_ARGS__) noexcept(false)
#endif /* __clang_tidy__ && __cplusplus */


#endif /* !_KOS_ANNO_H */
