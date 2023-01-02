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
#ifndef _ASM_OS_OFLAGS_H
#define _ASM_OS_OFLAGS_H 1

#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include <asm/os/kos/oflags.h>
#elif defined(__NetBSD__)
#include <asm/os/netbsd/oflags.h>
#elif defined(__solaris__)
#include <asm/os/solaris/oflags.h>
#else /* ... */
#include <__crt.h>
#if defined(__CRT_DOS_PRIMARY)
#include <asm/os/dos/oflags.h>
#elif defined(__CRT_CYG_PRIMARY)
#include <asm/os/cygwin/oflags.h>
#else /* ... */
/************************************************************************/
/* GENERIC                                                              */
/************************************************************************/
#define __O_ACCMODE 0x003 /* Mask for access modes (O_RDONLY, O_WRONLY, O_RDWR) */
#define __O_RDONLY  0x000 /* Read-only file access */
#define __O_WRONLY  0x001 /* Write-only file access */
#define __O_RDWR    0x002 /* Read/Write file access */
#endif /* !... */
#endif /* !... */

#ifndef __O_LARGEFILE
#define __O_LARGEFILE 0 /* Assume native supported (if necessary CRT functions are available) */
#endif /* !__O_LARGEFILE */


#ifdef __O_CLOEXEC
#define __PRIVATE_O_CLOEXEC __O_CLOEXEC
#else /* __O_CLOEXEC */
#define __PRIVATE_O_CLOEXEC 0
#endif /* !__O_CLOEXEC */

#ifdef __O_CLOFORK
#define __PRIVATE_O_CLOFORK __O_CLOFORK
#else /* __O_CLOFORK */
#define __PRIVATE_O_CLOFORK 0
#endif /* !__O_CLOFORK */

#endif /* !_ASM_OS_OFLAGS_H */
