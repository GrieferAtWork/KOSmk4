/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <asm/os/fcntl.h>*/
#ifndef _ASM_OS_CYGWIN_FCNTL_H
#define _ASM_OS_CYGWIN_FCNTL_H 1

#include <__stdinc.h>
#include <__crt.h>

/************************************************************************/
/* CYGWIN                                                               */
/************************************************************************/

#define __AT_FDCWD        (-2)
#define __FD_CLOEXEC      1
#define __F_DUPFD         0
#define __F_GETFD         1
#define __F_SETFD         2
#define __F_GETFL         3
#define __F_SETFL         4
#define __F_GETOWN        5
#define __F_SETOWN        6
#define __F_GETLK         7
#define __F_SETLK         8
#define __F_SETLKW        9
#define __F_RGETLK        10
#define __F_RSETLK        11
#define __F_CNVT          12
#define __F_RSETLKW       13
#define __F_DUPFD_CLOEXEC 14

#define __F_RDLCK   1
#define __F_WRLCK   2
#define __F_UNLCK   3
#define __F_UNLKSYS 4

#define __AT_EACCESS          1
#define __AT_SYMLINK_NOFOLLOW 2
#define __AT_SYMLINK_FOLLOW   4
#define __AT_REMOVEDIR        8
#define __AT_EMPTY_PATH       16

#define __LOCK_SH 0x01
#define __LOCK_EX 0x02
#define __LOCK_NB 0x04
#define __LOCK_UN 0x08

#ifdef __CC__
#include <features.h>
#if defined(__USE_NEWLIB) && defined(__USE_MISC)
#include <hybrid/typecore.h>
__DECL_BEGIN
struct eflock {
	__INT16_TYPE__   l_type;
	__INT16_TYPE__   l_whence;
	__LONGPTR_TYPE__ l_start;
	__LONGPTR_TYPE__ l_len;
	__INT16_TYPE__   l_pid;
	__INT16_TYPE__   l_xxx;
	__LONGPTR_TYPE__ l_rpid;
	__LONGPTR_TYPE__ l_rsys;
};
__DECL_END
#endif /* __USE_NEWLIB && __USE_MISC */
#endif /* __CC__ */

#endif /* !_ASM_OS_CYGWIN_FCNTL_H */
