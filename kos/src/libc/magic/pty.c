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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(pid_t = __pid_t)]
%[default:section(".text.crt{|.dos}.io.tty")]

%{
#include <features.h>
#include <termios.h>
#include <bits/types.h>
#include <sys/ioctl.h>

__SYSDECL_BEGIN

/* Documentation taken from Glibc /usr/include/pty.h */
/* Functions for pseudo TTY handling.
   Copyright (C) 1996-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef __CC__

struct termios;
struct winsize;

}

@@Create pseudo tty master slave pair with NAME and set terminal
@@attributes according to TERMP and WINP and return handles for
@@both ends in AMASTER and ASLAVE
[[decl_prefix(struct termios;)]]
[[decl_prefix(struct winsize;)]]
[[decl_include("<bits/types.h>")]]
int openpty([[nonnull]] $fd_t *amaster,
            [[nonnull]] $fd_t *aslave,
            [[nullable]] char *name,
            [[nullable]] struct termios const *termp,
            [[nullable]] struct winsize const *winp);

@@Create child process and establish the slave pseudo
@@terminal as the child's controlling terminal
[[decl_prefix(struct termios;)]]
[[decl_prefix(struct winsize;)]]
[[decl_include("<bits/types.h>")]]
$pid_t forkpty([[nonnull]] $fd_t *amaster,
               [[nonnull]] char *name,
               [[nullable]] struct termios const *termp,
               [[nullable]] struct winsize const *winp);

%{

#endif /* __CC__ */

__SYSDECL_END

}