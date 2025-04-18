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
#ifndef _ASM_OS_SOLARIS_FCNTL_H
#define _ASM_OS_SOLARIS_FCNTL_H 1

#include <__stdinc.h>

/************************************************************************/
/* SOLARIS                                                              */
/************************************************************************/
#define __F_DUPFD               0
#define __F_GETFD               1
#define __F_SETFD               2
#define __F_GETFL               3
#define __F_SETFL               4
#define __F_SETLK               6
#define __F_SETLKW              7
#define __F_CHKFL               8
#define __F_DUP2FD              9
#define __F_ALLOCSP             10
#define __F_FREESP              11
#define __F_ISSTREAM            13
#define __F_GETLK               14
#define __F_PRIV                15
#define __F_NPRIV               16
#define __F_QUOTACTL            17
#define __F_BLOCKS              18
#define __F_BLKSIZE             19
#define __F_GETOWN              23
#define __F_SETOWN              24
#define __F_REVOKE              25
#define __F_HASREMOTELOCKS      26
#define __F_SHARE               40
#define __F_UNSHARE             41
#define __F_SETLK_NBMAND        42
#define __F_SHARE_NBMAND        43
#define __F_GETXFL              45
#define __F_BADFD               46
#define __F_RDLCK               1
#define __F_WRLCK               2
#define __F_UNLCK               3
#define __F_UNLKSYS             4
#define __O_ACCMODE             3
#define __FD_CLOEXEC            1
#define __F_RDACC               0x1
#define __F_WRACC               0x2
#define __F_RWACC               0x3
#define __F_RMACC               0x4
#define __F_MDACC               0x20
#define __F_NODNY               0x0
#define __F_RDDNY               0x1
#define __F_WRDNY               0x2
#define __F_RWDNY               0x3
#define __F_RMDNY               0x4
#define __F_COMPAT              0x8
#define __F_MANDDNY             0x10
#define __AT_FDCWD              0xffd19553
#define __AT_SYMLINK_NOFOLLOW   0x1000
#define __AT_REMOVEDIR          0x1
#define __AT_TRIGGER            0x2
#define __POSIX_FADV_NORMAL     0
#define __POSIX_FADV_RANDOM     1
#define __POSIX_FADV_SEQUENTIAL 2
#define __POSIX_FADV_WILLNEED   3
#define __POSIX_FADV_DONTNEED   4
#define __POSIX_FADV_NOREUSE    5
#ifdef __CC__
#include <features.h>

#ifdef __USE_SOLARIS
#include <hybrid/typecore.h>
__DECL_BEGIN

typedef struct fshare {
	__INT16_TYPE__ f_access;
	__INT16_TYPE__ f_deny;
	__INT32_TYPE__ f_id;
} fshare_t;

__DECL_END
#endif /* __USE_SOLARIS */
#endif /* __CC__ */

#endif /* !_ASM_OS_SOLARIS_FCNTL_H */
