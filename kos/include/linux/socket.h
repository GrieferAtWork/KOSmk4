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
/* (#) Portability: Linux (/usr/include/linux/socket.h) */
#ifndef _LINUX_SOCKET_H
#define _LINUX_SOCKET_H 1

#include <__stdinc.h>

#include <bits/os/sockaddr_storage.h> /* `struct sockaddr_storage', __SIZEOF_SOCKADDR_STORAGE, __SOCKADDR_COMMON_ALIGN */

#if !defined(_K_SS_MAXSIZE) && defined(__SIZEOF_SOCKADDR_STORAGE)
#define _K_SS_MAXSIZE __SIZEOF_SOCKADDR_STORAGE
#endif /* !_K_SS_MAXSIZE && __SIZEOF_SOCKADDR_STORAGE */
#ifndef _K_SS_ALIGNSIZE
#include <hybrid/typecore.h>
#if defined(__SOCKADDR_COMMON_ALIGN) && __SOCKADDR_COMMON_ALIGN > __ALIGNOF_POINTER__
#define _K_SS_ALIGNSIZE __SOCKADDR_COMMON_ALIGN
#else /* __SOCKADDR_COMMON_ALIGN > __ALIGNOF_POINTER__ */
#define _K_SS_ALIGNSIZE __ALIGNOF_POINTER__
#endif /* __SOCKADDR_COMMON_ALIGN <= __ALIGNOF_POINTER__ */
#endif /* !_K_SS_ALIGNSIZE */

#ifdef __CC__
#define __kernel_sa_family_t      __sa_family_t
#define __kernel_sockaddr_storage sockaddr_storage
#endif /* __CC__ */

#endif /* !_LINUX_SOCKET_H */
