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
/* (#) Portability: Linux (/usr/include/[...]/asm/termios.h) */
#ifndef _ASM_TERMIOS_H
#define _ASM_TERMIOS_H 1

#include <__stdinc.h>

#include <asm/ioctls.h>
#include <asm/os/tty.h>
#include <asm/termbits.h>
#include <bits/os/termio.h>  /* struct termio */
#include <bits/os/termios.h> /* struct winsize */

/* modem lines */
#if !defined(TIOCM_LE) && defined(__TIOCM_LE)
#define TIOCM_LE  __TIOCM_LE  /* ??? */
#endif /* !TIOCM_LE && __TIOCM_LE */
#if !defined(TIOCM_DTR) && defined(__TIOCM_DTR)
#define TIOCM_DTR __TIOCM_DTR /* ??? */
#endif /* !TIOCM_DTR && __TIOCM_DTR */
#if !defined(TIOCM_RTS) && defined(__TIOCM_RTS)
#define TIOCM_RTS __TIOCM_RTS /* ??? */
#endif /* !TIOCM_RTS && __TIOCM_RTS */
#if !defined(TIOCM_ST) && defined(__TIOCM_ST)
#define TIOCM_ST  __TIOCM_ST  /* ??? */
#endif /* !TIOCM_ST && __TIOCM_ST */
#if !defined(TIOCM_SR) && defined(__TIOCM_SR)
#define TIOCM_SR  __TIOCM_SR  /* ??? */
#endif /* !TIOCM_SR && __TIOCM_SR */
#if !defined(TIOCM_CTS) && defined(__TIOCM_CTS)
#define TIOCM_CTS __TIOCM_CTS /* ??? */
#endif /* !TIOCM_CTS && __TIOCM_CTS */
#if !defined(TIOCM_CAR) && defined(__TIOCM_CAR)
#define TIOCM_CAR __TIOCM_CAR /* ??? */
#endif /* !TIOCM_CAR && __TIOCM_CAR */
#if !defined(TIOCM_RNG) && defined(__TIOCM_RNG)
#define TIOCM_RNG __TIOCM_RNG /* ??? */
#endif /* !TIOCM_RNG && __TIOCM_RNG */
#if !defined(TIOCM_DSR) && defined(__TIOCM_DSR)
#define TIOCM_DSR __TIOCM_DSR /* ??? */
#endif /* !TIOCM_DSR && __TIOCM_DSR */
#if !defined(TIOCM_CD) && defined(__TIOCM_CAR)
#define TIOCM_CD  __TIOCM_CAR /* Alias */
#endif /* !TIOCM_CD && __TIOCM_CAR */
#if !defined(TIOCM_RI) && defined(__TIOCM_RNG)
#define TIOCM_RI  __TIOCM_RNG /* Alias */
#endif /* !TIOCM_RI && __TIOCM_RNG */
#if !defined(TIOCM_OUT1) && defined(__TIOCM_OUT1)
#define TIOCM_OUT1 __TIOCM_OUT1 /* ??? */
#endif /* !TIOCM_OUT1 && __TIOCM_OUT1 */
#if !defined(TIOCM_OUT2) && defined(__TIOCM_OUT2)
#define TIOCM_OUT2 __TIOCM_OUT2 /* ??? */
#endif /* !TIOCM_OUT2 && __TIOCM_OUT2 */
#if !defined(TIOCM_LOOP) && defined(__TIOCM_LOOP)
#define TIOCM_LOOP __TIOCM_LOOP /* ??? */
#endif /* !TIOCM_LOOP && __TIOCM_LOOP */

#endif /* !_ASM_TERMIOS_H */
