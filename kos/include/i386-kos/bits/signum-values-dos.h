/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_SIGNUM_VALUES_DOS_H
#define _I386_KOS_BITS_SIGNUM_VALUES_DOS_H 1

#include <__stdinc.h>

/* Fake signal functions. */
#define __DOS_SIG_ERR   (__CCAST(__sighandler_t)-1) /* Error return. */
#define __DOS_SIG_DFL   (__CCAST(__sighandler_t)0)  /* Default action. */
#define __DOS_SIG_IGN   (__CCAST(__sighandler_t)1)  /* Ignore signal. */
#define __DOS_SIG_GET   (__CCAST(__sighandler_t)2)  /* Return current value. */
#define __DOS_SIG_SGE   (__CCAST(__sighandler_t)3)  /* Signal gets error. */
#define __DOS_SIG_ACK   (__CCAST(__sighandler_t)4)  /* Acknowledge. */

/* Signals. */
#define __DOS_SIGINT          2  /* Interrupt (ANSI). */
#define __DOS_SIGILL          4  /* Illegal instruction (ANSI). */
#define __DOS_SIGABRT_COMPAT  6  /* Abort (ANSI). */
#define __DOS_SIGFPE          8  /* Floating-point exception (ANSI). */
#define __DOS_SIGSEGV         11 /* Segmentation violation (ANSI). */
#define __DOS_SIGTERM         15 /* Termination (ANSI). */
#define __DOS_SIGBREAK        21 /* Background read from tty (POSIX). */
#define __DOS_SIGABRT         22 /* Abort (ANSI). */
#define __DOS_NSIG            33 /* Biggest signal number + 1 (including real-time signals). */

#endif /* !_I386_KOS_BITS_SIGNUM_VALUES_DOS_H */
