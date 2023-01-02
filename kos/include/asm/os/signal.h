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
#ifndef _ASM_OS_SIGNAL_H
#define _ASM_OS_SIGNAL_H 1

#include <__stdinc.h>

#if defined(__KOS__) || defined(__linux__)
#include <asm/os/kos/signal.h>
#elif defined(__NetBSD__)
#include <asm/os/netbsd/signal.h>
#elif defined(__solaris__)
#include <asm/os/solaris/signal.h>
#else /* ... */
#include <__crt.h>
#if defined(__CRT_CYG_PRIMARY)
#include <asm/os/cygwin/signal.h>
#elif defined(__CRT_DOS_PRIMARY)
#include <asm/os/dos/signal.h>
#endif /* ... */
#endif /* !... */

#ifndef __NSIG
#define __NSIG 1 /* Biggest signal number + 1 (including real-time signals). */
#endif /* !__NSIG */


#endif /* !_ASM_OS_SIGNAL_H */
