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
#ifndef _SYS_TTYDEFAULTS_H
#define _SYS_TTYDEFAULTS_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/i386-linux-gnu/sys/ttydefaults.h' */

#include <__stdinc.h>

__SYSDECL_BEGIN

/*-
 * Copyright (c) 1982, 1986, 1993
 *    The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *    @(#)ttydefaults.h    8.4 (Berkeley) 1/21/94
 */

/* Defaults on "first" open. */
#define TTYDEF_IFLAG (BRKINT|ISTRIP|ICRNL|IMAXBEL|IXON|IXANY)
#define TTYDEF_OFLAG (OPOST|ONLCR|XTABS)
#define TTYDEF_LFLAG (ECHO|ICANON|ISIG|IEXTEN|ECHOE|ECHOKE|ECHOCTL)
#define TTYDEF_CFLAG (CREAD|CS7|PARENB|HUPCL)
#define TTYDEF_SPEED (B9600)

/* Control Character Defaults */
#define CTRL(x)    (x&037)
#define CEOF        CTRL('d')
#ifdef _POSIX_VDISABLE
#   define CEOL     _POSIX_VDISABLE
#else
#   define CEOL     '\0'
#endif
#define CERASE      0177
#define CINTR       CTRL('c')
#ifdef _POSIX_VDISABLE
#   define CSTATUS  _POSIX_VDISABLE
#else
#   define CSTATUS  '\0'
#endif
#define CKILL       CTRL('u')
#define CMIN        1
#define CQUIT       034        /* FS, ^\ */
#define CSUSP       CTRL('z')
#define CTIME       0
#define CDSUSP      CTRL('y')
#define CSTART      CTRL('q')
#define CSTOP       CTRL('s')
#define CLNEXT      CTRL('v')
#define CDISCARD    CTRL('o')
#define CWERASE     CTRL('w')
#define CREPRINT    CTRL('r')
#define CEOT        CEOF

#define CBRK        CEOL
#define CRPRNT      CREPRINT
#define CFLUSH      CDISCARD

__SYSDECL_END

#endif /* !_SYS_TTYDEFAULTS_H */

/* #define TTYDEFCHARS to include an array of default control characters. */
#ifdef TTYDEFCHARS
#undef TTYDEFCHARS
cc_t ttydefchars[NCCS] = {
	CEOF,CEOL,CEOL,CERASE,CWERASE,CKILL,CREPRINT,
	_POSIX_VDISABLE,CINTR,CQUIT,CSUSP,CDSUSP,CSTART,CSTOP,
	CLNEXT,CDISCARD,CMIN,CTIME,CSTATUS,_POSIX_VDISABLE
};
#endif

