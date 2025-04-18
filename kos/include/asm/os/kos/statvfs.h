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
/*!replace_with_include <asm/os/statvfs.h>*/
#ifndef _ASM_OS_KOS_STATVFS_H
#define _ASM_OS_KOS_STATVFS_H 1

#include <__stdinc.h>

#define __ST_RDONLY      0x0001 /* Disallow all file writes */
#define __ST_NOSUID      0x0002 /* Ignore `S_ISUID' and `S_ISGID' */
#define __ST_NODEV       0x0004 /* ??? */
#define __ST_NOEXEC      0x0008 /* ??? */
#define __ST_SYNCHRONOUS 0x0010 /* ??? */
/*      __ST_            0x0020  * ... */
#define __ST_MANDLOCK    0x0040 /* ??? */
#define __ST_WRITE       0x0080 /* ??? */
#define __ST_APPEND      0x0100 /* ??? */
#define __ST_IMMUTABLE   0x0200 /* ??? */
#define __ST_NOATIME     0x0400 /* ??? */
#define __ST_NODIRATIME  0x0800 /* ??? */
#define __ST_RELATIME    0x1000 /* ??? */

#endif /* !_ASM_OS_KOS_STATVFS_H */
