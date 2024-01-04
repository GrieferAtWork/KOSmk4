/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: FreeBSD (/sys/sys/_sockaddr_storage.h) */
#ifndef _SYS__SOCKADDR_STORAGE_H
#define _SYS__SOCKADDR_STORAGE_H 1

#include <__stdinc.h>

#include <bits/os/sockaddr_storage.h>

#if !defined(_SS_MAXSIZE) && defined(__SIZEOF_SOCKADDR_STORAGE)
#define _SS_MAXSIZE __SIZEOF_SOCKADDR_STORAGE
#endif /* !_SS_MAXSIZE && __SIZEOF_SOCKADDR_STORAGE */

#ifndef _SS_ALIGNSIZE
#ifdef __ALIGNOF_SOCKADDR_STORAGE
#define _SS_ALIGNSIZE __ALIGNOF_SOCKADDR_STORAGE
#else /* __ALIGNOF_SOCKADDR_STORAGE */
#include <hybrid/typecore.h>
#ifndef _SS_ALIGNSIZE
#define _SS_ALIGNSIZE __SIZEOF_POINTER__
#endif /* !_SS_ALIGNSIZE */
#endif /* !__ALIGNOF_SOCKADDR_STORAGE */
#endif /* !_SS_ALIGNSIZE */

#ifndef _SS_PAD1SIZE
#ifdef _SS_PADSIZE
#define _SS_PAD1SIZE _SS_PADSIZE
#else /* _SS_PADSIZE */
#define _SS_PAD1SIZE 0
#endif /* !_SS_PADSIZE */
#endif /* !_SS_PAD1SIZE */

#ifndef _SS_PAD2SIZE
#define _SS_PAD2SIZE 0
#endif /* !_SS_PAD2SIZE */

#endif /* !_SYS__SOCKADDR_STORAGE_H */
