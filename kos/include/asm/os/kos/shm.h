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
#ifndef _ASM_OS_KOS_SHM_H
#define _ASM_OS_KOS_SHM_H 1

#include <__stdinc.h>

/* Permission flag for use with `shmget()'. */
#define __SHM_W 0x080 /* or S_IWUGO */
#define __SHM_R 0x100 /* or S_IRUGO */

/* Flags for use with `shmat()'. */
#define __SHM_RDONLY 0x1000 /* ??? */
#define __SHM_RND    0x2000 /* ??? */
#define __SHM_REMAP  0x4000 /* ??? */
#define __SHM_EXEC   0x8000 /* ??? */

/* Command codes for use with `shmctl()'. */
#define __SHM_LOCK   11 /* ??? */
#define __SHM_UNLOCK 12 /* ??? */

/* ipcs ctl commands */
#define __SHM_STAT 13 /* ??? */
#define __SHM_INFO 14 /* ??? */

/* shm_mode upper byte flags. */
#define __SHM_DEST      0x0200 /* ??? */
#define __SHM_LOCKED    0x0400 /* ??? */
#define __SHM_HUGETLB   0x0800 /* ??? */
#define __SHM_NORESERVE 0x1000 /* ??? */

#endif /* !_ASM_OS_KOS_SHM_H */
