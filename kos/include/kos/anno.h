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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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
#define __WEAK          /* Annotation for weakly referenced data/data updated randomly with both the old/new state remaining valid forever. */
#define __REF           /* Annotation for reference holders. */
#define __FREE          /* Annotation for functions / data that are apart of the .free section. */
#define __NOBLOCK       /* Annotation for functions that are guarantied to never block,
                         * making them safe to-be called from any asynchronous context. */
#define __NOCONNECT     /* Annotation for functions which may only be called when
                         * the calling thread isn't already connected to a signal. */
#define __NOBLOCK_IF(x) /* Annotation for functions that are conditionally non-blocking. */
#define __THROWS(...)   /* Annotation for the set of error codes/classes/sub-classes that may be thrown by a function.
                         * You may include `...' as a possible error code to indicate that the function
                         * is also allowed to throw any other kind of exception, usually indicative of
                         * the function following a path that includes a call to `task_serve()'
                         * Note however that this is merely for documentation purposes, as well as to
                         * document the ~expected~ error codes. - Any function that isn't NOTHROW is
                         * still always allowed to throw any error that isn't apart of the THROWS set. */
#define __THROWS_INDIRECT(...) /* Similar to `__THROWS()', but the error is propgated by non-standard means. */

#endif /* !_KOS_ANNO_H */
