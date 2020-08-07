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
#ifndef _ASM_IOCTLS_SOCKET_H
#define _ASM_IOCTLS_SOCKET_H 1

#include <__stdinc.h>
#include <features.h> /* __USE_TIME_BITS64 */

#include <asm/ioctl.h>

#define FIOSETOWN            _IO(0x89, 0x01) /* ... */
#define SIOCSPGRP            _IO(0x89, 0x02) /* ... */
#define FIOGETOWN            _IO(0x89, 0x03) /* ... */
#define SIOCGPGRP            _IO(0x89, 0x04) /* ... */
#define SIOCATMARK           _IO(0x89, 0x05) /* ... */

#ifdef __KOS__
#include <bits/timeval.h>
#include <bits/timespec.h>
#define __SIOCGSTAMP32       _IOR(0x89, 0x06, struct __timeval32) /* [struct timeval32 *arg] Get stamp */
#define __SIOCGSTAMP64       _IOR(0x89, 0x06, struct __timeval64) /* [struct timeval64 *arg] Get stamp */
#define __SIOCGSTAMPNS32     _IOR(0x89, 0x07, struct __timeval32) /* [struct timespec32 *arg] Get stamp */
#define __SIOCGSTAMPNS64     _IOR(0x89, 0x07, struct __timeval64) /* [struct timespec64 *arg] Get stamp */
#else /* __KOS__ */
#include <bits/types.h>
#define __SIOCGSTAMP32       _IO(0x89, 0x06) /* [struct timeval32 *arg] Get stamp */
#define __SIOCGSTAMPNS32     _IO(0x89, 0x07) /* [struct timespec32 *arg] Get stamp */
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define __SIOCGSTAMP64       __SIOCGSTAMP32    /* [struct timeval64 *arg] Get stamp */
#define __SIOCGSTAMPNS64     __SIOCGSTAMPNS32  /* [struct timespec64 *arg] Get stamp */
#endif /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
#endif /* !__KOS__ */

#ifdef __USE_TIME_BITS64
#ifdef __SIOCGSTAMP64
#define SIOCGSTAMP   __SIOCGSTAMP64   /* [struct timeval *arg] Get stamp */
#endif /* __SIOCGSTAMP64 */
#ifdef __SIOCGSTAMPNS64
#define SIOCGSTAMPNS __SIOCGSTAMPNS64 /* [struct timespec *arg] Get stamp */
#endif /* __SIOCGSTAMPNS64 */
#else /* __USE_TIME_BITS64 */
#ifdef __SIOCGSTAMP32
#define SIOCGSTAMP   __SIOCGSTAMP32   /* [struct timeval *arg] Get stamp */
#endif /* __SIOCGSTAMP32 */
#ifdef __SIOCGSTAMPNS32
#define SIOCGSTAMPNS __SIOCGSTAMPNS32 /* [struct timespec *arg] Get stamp */
#endif /* __SIOCGSTAMPNS32 */
#endif /* !__USE_TIME_BITS64 */


#ifdef __USE_KOS
#ifdef __SIOCGSTAMP32
#define SIOCGSTAMP32   __SIOCGSTAMP32 /* [struct timeval32 *arg] Get stamp */
#endif /* __SIOCGSTAMP32 */
#ifdef __SIOCGSTAMPNS32
#define SIOCGSTAMPNS32 __SIOCGSTAMPNS32 /* [struct timespec32 *arg] Get stamp */
#endif /* __SIOCGSTAMPNS32 */
#endif /* __USE_KOS */

#ifdef __USE_TIME64
#ifdef __SIOCGSTAMP64
#define SIOCGSTAMP64   __SIOCGSTAMP64 /* [struct timeval64 *arg] Get stamp */
#endif /* __SIOCGSTAMP64 */
#ifdef __SIOCGSTAMPNS64
#define SIOCGSTAMPNS64 __SIOCGSTAMPNS64 /* [struct timespec64 *arg] Get stamp */
#endif /* __SIOCGSTAMPNS64 */
#endif /* __USE_TIME64 */

#endif /* !_ASM_IOCTLS_SOCKET_H */
