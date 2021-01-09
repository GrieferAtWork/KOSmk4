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
#ifndef _ASM_OS_NETBSD_SIGNAL_H
#define _ASM_OS_NETBSD_SIGNAL_H 1

#include <__stdinc.h>

/************************************************************************/
/* NetBSD                                                               */
/************************************************************************/

#define __SA_ONSTACK    0x0001
#define __SA_RESTART    0x0002
#define __SA_RESETHAND  0x0004
#define __SA_NODEFER    0x0010
#define __SA_NOCLDSTOP  0x0008
#define __SA_NOCLDWAIT  0x0020
#define __SA_SIGINFO    0x0040
#define __SA_NOKERNINFO 0x0080

#define __SIG_BLOCK   1
#define __SIG_UNBLOCK 2
#define __SIG_SETMASK 3

/* TODO: signum values */

#endif /* !_ASM_OS_NETBSD_SIGNAL_H */
