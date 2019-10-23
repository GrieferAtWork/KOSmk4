/* HASH CRC-32:0x1b0d29e5 */
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
#ifndef _TTYENT_H
#define _TTYENT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

/* Documentation taken from Glibc /usr/include/ttyent.h */
/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)ttyent.h	8.1 (Berkeley) 6/2/93
 */

#define _PATH_TTYS    "/etc/ttys"
#define _TTYS_OFF     "off"
#define _TTYS_ON      "on"
#define _TTYS_SECURE  "secure"
#define _TTYS_WINDOW  "window"

#define TTY_ON      0x01 /* enable logins (start ty_getty program) */
#define TTY_SECURE  0x02 /* allow uid of 0 to login */

__SYSDECL_BEGIN

#ifdef __CC__

struct ttyent {
	char           *ty_name;    /* terminal device name */
	char           *ty_getty;   /* command to execute, usually getty */
	char           *ty_type;    /* terminal type for termcap */
	__INTPTR_TYPE__ ty_status;  /* status flags (Set of `TTY_ON|TTY_SECURE') */
	char           *ty_window;  /* command to start up window manager */
	char           *ty_comment; /* comment field */
};

#if defined(__CRT_HAVE_getttyent)
__CDECLARE(,struct ttyent *,__NOTHROW_RPC_KOS,getttyent,(void),())
#endif /* getttyent... */
#if defined(__CRT_HAVE_getttynam)
__CDECLARE(__ATTR_NONNULL((1)),struct ttyent *,__NOTHROW_RPC_KOS,getttynam,(char const *__tty),(__tty))
#endif /* getttynam... */
#if defined(__CRT_HAVE_setttyent)
__CDECLARE(,int,__NOTHROW_RPC_KOS,setttyent,(void),())
#endif /* setttyent... */
#if defined(__CRT_HAVE_endttyent)
__CDECLARE(,int,__NOTHROW_RPC_KOS,endttyent,(void),())
#endif /* endttyent... */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_TTYENT_H */
