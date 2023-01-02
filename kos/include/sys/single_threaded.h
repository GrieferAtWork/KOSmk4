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
/* (#) Portability: DragonFly BSD (/sys/sys/single_threaded.h) */
/* (#) Portability: GNU C Library (/misc/sys/single_threaded.h) */
#ifndef _SYS_SINGLE_THREADED_H
#define _SYS_SINGLE_THREADED_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#ifdef __CC__
__DECL_BEGIN

/* >> __libc_single_threaded(3)
 * When zero, the calling process might be multi-threaded. */
#ifndef __libc_single_threaded
#ifdef __CRT_HAVE___libc_single_threaded
__CSDECLARE(,char __KOS_FIXED_CONST,__libc_single_threaded)
#define __libc_single_threaded __libc_single_threaded
#else /* __CRT_HAVE___libc_single_threaded */
#define __libc_single_threaded ((char)0)
#endif /* !__CRT_HAVE___libc_single_threaded */
#endif /* !__libc_single_threaded */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_SINGLE_THREADED_H */
