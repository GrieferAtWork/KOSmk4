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
/*!included_by <fcntl.h>*/
/*!included_by <io.h>*/
/*!included_by <sys/file.h>*/
/*!included_by <unistd.h>*/
#ifndef _ASM_OS_FCNTL_H
#define _ASM_OS_FCNTL_H 1

#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include <asm/os/kos/fcntl.h>
#elif defined(__NetBSD__)
#include <asm/os/netbsd/fcntl.h>
#elif defined(__solaris__)
#include <asm/os/solaris/fcntl.h>
#else /* ... */
#include <__crt.h>
#if defined(__CRT_DOS_PRIMARY)
#include <asm/os/dos/fcntl.h>
#elif defined(__CRT_CYG_PRIMARY)
#include <asm/os/cygwin/fcntl.h>
#else /* ... */
/************************************************************************/
/* GENERIC                                                              */
/************************************************************************/
/* ... */
#endif /* !... */
#endif /* !... */


#ifndef __R_OK
#define __R_OK 4 /* Test for read permission. */
#define __W_OK 2 /* Test for write permission. */
#define __X_OK 1 /* Test for execute permission. */
#define __F_OK 0 /* Test for existence. */
#endif /* !__R_OK */

#ifndef __F_ULOCK
#define __F_ULOCK 0 /* Unlock a previously locked region. */
#define __F_LOCK  1 /* Lock a region for exclusive use. */
#define __F_TLOCK 2 /* Test and lock a region for exclusive use. */
#define __F_TEST  3 /* Test a region for other processes locks. */
#endif /* !__F_ULOCK */


/* Deal with fcntl redirection on platforms with 64-bit-by-default filesystems. */
#if (defined(__F_FREESP64) || defined(__F_ALLOCSP64) || \
     defined(__F_GETLK64) || defined(__F_SETLK64) ||    \
     defined(__F_SETLKW64) || defined(__F_SETLK64_NBMAND))
#include <bits/typesizes.h>
#if __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
#ifdef __F_FREESP64
#undef __F_FREESP64
#ifdef __F_FREESP
#define __F_FREESP64 __F_FREESP
#endif /* __F_FREESP */
#endif /* __F_FREESP64 */

#ifdef __F_ALLOCSP64
#undef __F_ALLOCSP64
#ifdef __F_ALLOCSP
#define __F_ALLOCSP64 __F_ALLOCSP
#endif /* __F_ALLOCSP */
#endif /* __F_ALLOCSP64 */

#ifdef __F_GETLK64
#undef __F_GETLK64
#ifdef __F_GETLK
#define __F_GETLK64 __F_GETLK
#endif /* __F_GETLK */
#endif /* __F_GETLK64 */

#ifdef __F_SETLK64
#undef __F_SETLK64
#ifdef __F_SETLK
#define __F_SETLK64 __F_SETLK
#endif /* __F_SETLK */
#endif /* __F_SETLK64 */

#ifdef __F_SETLKW64
#undef __F_SETLKW64
#ifdef __F_SETLKW
#define __F_SETLKW64 __F_SETLKW
#endif /* __F_SETLKW */
#endif /* __F_SETLKW64 */

#ifdef __F_SETLK64_NBMAND
#undef __F_SETLK64_NBMAND
#ifdef __F_SETLK_NBMAND
#define __F_SETLK64_NBMAND __F_SETLK_NBMAND
#endif /* __F_SETLK_NBMAND */
#endif /* __F_SETLK64_NBMAND */
#endif /* __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ */
#endif /* ... */


#endif /* !_ASM_OS_FCNTL_H */
