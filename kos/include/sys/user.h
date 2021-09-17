/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: FreeBSD       (/sys/sys/user.h) */
/* (#) Portability: GNU C Library (/sysdeps/unix/sysv/linux/sys/user.h) */
/* (#) Portability: OpenBSD       (/sys/sys/user.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/user.h) */
/* (#) Portability: libc4/5       (/include/sys/user.h) */
/* (#) Portability: musl libc     (/include/sys/user.h) */
#ifndef _SYS_USER_H
#define _SYS_USER_H 1

#include <__stdinc.h>

__DECL_BEGIN

#ifdef __CC__
struct user_regs_struct {
	int __placeholder[41];
};
struct user_fpregs_struct {
	int __placeholder[42];
};
#endif /* __CC__ */

__DECL_END

#endif /* !_SYS_USER_H */
