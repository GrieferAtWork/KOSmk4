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
/*!replace_with_include <asm/os/signal.h>*/
#ifndef _ASM_OS_DOS_SIGNAL_H
#define _ASM_OS_DOS_SIGNAL_H 1

#include <__stdinc.h>

/************************************************************************/
/* DOS/MSVCRT                                                           */
/************************************************************************/

/* Fake signal functions. */
#define __SIG_ERR (-1) /* Error return. */
#define __SIG_DFL 0    /* Default action. */
#define __SIG_IGN 1    /* Ignore signal. */
#define __SIG_GET 2    /* Return current value. */
#define __SIG_SGE 3    /* Signal gets error. */
#define __SIG_ACK 4    /* Acknowledge. */

/* Signals. */
#define __SIGINT          2  /* Interrupt (ANSI). */
#define __SIGILL          4  /* Illegal instruction (ANSI). */
#define __SIGABRT_COMPAT  6  /* Abort (ANSI). */
#define __SIGFPE          8  /* Floating-point exception (ANSI). */
#define __SIGSEGV         11 /* Segmentation violation (ANSI). */
#define __SIGTERM         15 /* Termination (ANSI). */
#define __SIGBREAK        21 /* Background read from tty (POSIX). */
#define __SIGABRT         22 /* Abort (ANSI). */
#define __NSIG            33 /* Biggest signal number + 1 (including real-time signals). */

#endif /* !_ASM_OS_DOS_SIGNAL_H */
