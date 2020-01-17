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

%{
#include <sys/ucontext.h>

__SYSDECL_BEGIN

/* Comments taken from /usr/include/ucontext.h of a linux machine.
 * The following is the copyright notice found in the original file. */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.
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
}

%
@@Get user context and store it in variable pointed to by UCP
getcontext:([nonnull] ucontext_t *__restrict ucp) -> int;

%
@@Set user context from information of variable pointed to by UCP
setcontext:([nonnull] ucontext_t const *__restrict ucp) -> int;

%
@@Save current context in context variable pointed to by OUCP and set
@@context from variable pointed to by UCP
swapcontext:([nonnull] ucontext_t *__restrict oucp,
             [nonnull] ucontext_t const *__restrict ucp) -> int;

%
%typedef void (*__makecontext_func_t)(void);

%
@@Manipulate user context UCP to continue with calling functions FUNC
@@and the ARGC-1 parameters following ARGC when the context is used
@@the next time in `setcontext' or `swapcontext'.
@@We cannot say anything about the parameters FUNC takes; `void'
@@is as good as any other choice
makecontext:([nonnull] ucontext_t *ucp,
             [nonnull] __makecontext_func_t func, int argc, ...);

%{

#endif /* __CC__ */

__SYSDECL_END

}