/* HASH CRC-32:0x17ba8a97 */
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
#ifndef _SYS_FILE_H
#define _SYS_FILE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/fcntl.h>  /* __LOCK_* */
#include <asm/stdio.h>  /* __SEEK_* */
#include <bits/types.h> /* fd_t */

#ifdef __USE_GLIBC
#include <fcntl.h>
#endif /* __USE_GLIBC */

#ifndef SEEK_SET
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#ifdef __USE_GNU
#ifdef __SEEK_DATA
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* __SEEK_DATA */
#ifdef __SEEK_HOLE
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* __SEEK_HOLE */
#endif /* __USE_GNU */
#endif /* !SEEK_SET */

#ifndef L_SET
#define L_SET  __SEEK_SET /* Seek from beginning of file. */
#define L_CURR __SEEK_CUR /* Seek from current position. */
#define L_INCR __SEEK_CUR /* Seek from current position. */
#define L_XTND __SEEK_END /* Seek from end of file. */
#endif /* !L_SET */

/* Shared lock. */
#ifdef __LOCK_SH
#define LOCK_SH __LOCK_SH
#endif /* __LOCK_SH */

/* Exclusive lock. */
#ifdef __LOCK_EX
#define LOCK_EX __LOCK_EX
#endif /* __LOCK_EX */

/* Or'd with one of the above to prevent blocking. */
#ifdef __LOCK_NB
#define LOCK_NB __LOCK_NB
#endif /* __LOCK_NB */

/* Remove lock. */
#ifdef __LOCK_UN
#define LOCK_UN __LOCK_UN
#endif /* __LOCK_UN */


#ifdef __CC__
__SYSDECL_BEGIN

/* Apply or remove an advisory lock, according to OPERATION, on the file FD refers to */
__CDECLARE_OPT(,int,__NOTHROW_RPC,flock,(__fd_t __fd, __STDC_INT_AS_UINT_T __operation),(__fd,__operation))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_FILE_H */
