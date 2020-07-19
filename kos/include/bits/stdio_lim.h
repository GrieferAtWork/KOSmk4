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
#ifndef _BITS_STDIO_LIM_H
#define _BITS_STDIO_LIM_H 1

#include <__crt.h>
#include <asm/limits.h>

#ifndef L_tmpnam
#ifdef __CRT_DOS_PRIMARY
#define L_tmpnam 14
#else /* __CRT_DOS_PRIMARY */
#define L_tmpnam 20
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !L_tmpnam */

#ifndef FILENAME_MAX
#ifdef __CRT_DOS_PRIMARY
#define FILENAME_MAX 260
#else /* __CRT_DOS_PRIMARY */
#define FILENAME_MAX 4096
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !FILENAME_MAX */

#ifndef TMP_MAX
#ifdef __CRT_DOS_PRIMARY
#define TMP_MAX 32767
#else /* __CRT_DOS_PRIMARY */
#define TMP_MAX 238328
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !TMP_MAX */

#ifdef __USE_POSIX
#ifndef L_ctermid
#define L_ctermid 9
#endif /* !L_ctermid */
#if !defined(__USE_XOPEN2K) || defined(__USE_GNU)
#ifndef L_cuserid
#define L_cuserid 9
#endif /* !L_cuserid */
#endif /* !__USE_XOPEN2K || __USE_GNU */
#endif /* __USE_POSIX */

#ifndef FOPEN_MAX
#ifdef __CRT_DOS_PRIMARY
#define FOPEN_MAX 20
#else /* __CRT_DOS_PRIMARY */
#define FOPEN_MAX 16
#endif /* !__CRT_DOS_PRIMARY */
#endif /* !FOPEN_MAX */

#ifndef IOV_MAX
/* [default:_POSIX_UIO_MAXIOV] Max # of elements in a `struct iovec' vector. */
#if defined(__IOV_MAX) && __IOV_MAX != -1
#define IOV_MAX __IOV_MAX
#else /* __IOV_MAX != -1 */
#define IOV_MAX 16 /* 16 == _XOPEN_IOV_MAX */
#endif /* __IOV_MAX == -1 */
#endif /* !IOV_MAX */

#endif /* !_BITS_STDIO_LIM_H */
