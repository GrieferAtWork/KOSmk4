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
/* (#) Portability: NetBSD      (/sys/sys/ttydev.h) */
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/ttydev.h) */
#ifndef _SYS_TTYDEV_H
#define _SYS_TTYDEV_H 1

#include <__stdinc.h>
#include <features.h>

#include <asm/os/termios.h> /* __B0, ... */

#if !defined(B0) && defined(__B0)
#define B0        __B0 /* hang up */
#endif /* !B0 && __B0 */
#if !defined(B50) && defined(__B50)
#define B50       __B50
#endif /* !B50 && __B50 */
#if !defined(B75) && defined(__B75)
#define B75       __B75
#endif /* !B75 && __B75 */
#if !defined(B110) && defined(__B110)
#define B110      __B110
#endif /* !B110 && __B110 */
#if !defined(B134) && defined(__B134)
#define B134      __B134
#endif /* !B134 && __B134 */
#if !defined(B150) && defined(__B150)
#define B150      __B150
#endif /* !B150 && __B150 */
#if !defined(B200) && defined(__B200)
#define B200      __B200
#endif /* !B200 && __B200 */
#if !defined(B300) && defined(__B300)
#define B300      __B300
#endif /* !B300 && __B300 */
#if !defined(B600) && defined(__B600)
#define B600      __B600
#endif /* !B600 && __B600 */
#if !defined(B1200) && defined(__B1200)
#define B1200     __B1200
#endif /* !B1200 && __B1200 */
#if !defined(B1800) && defined(__B1800)
#define B1800     __B1800
#endif /* !B1800 && __B1800 */
#if !defined(B2400) && defined(__B2400)
#define B2400     __B2400
#endif /* !B2400 && __B2400 */
#if !defined(B4800) && defined(__B4800)
#define B4800     __B4800
#endif /* !B4800 && __B4800 */
#if !defined(B9600) && defined(__B9600)
#define B9600     __B9600
#endif /* !B9600 && __B9600 */
#if !defined(B19200) && defined(__B19200)
#define B19200    __B19200
#endif /* !B19200 && __B19200 */
#if !defined(B38400) && defined(__B38400)
#define B38400    __B38400
#endif /* !B38400 && __B38400 */

#ifdef __USE_MISC
#if !defined(EXTA) && defined(__EXTA)
#define EXTA      __EXTA
#endif /* !EXTA && __EXTA */
#if !defined(EXTB) && defined(__EXTB)
#define EXTB      __EXTB
#endif /* !EXTB && __EXTB */
#endif /* __USE_MISC */

#endif /* !_SYS_TTYDEV_H */
