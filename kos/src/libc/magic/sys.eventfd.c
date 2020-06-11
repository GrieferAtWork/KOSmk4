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
%[define_replacement(eventfd_t = __UINT64_TYPE__)]
%[default_impl_section(".text.crt.sched.eventfd")]

%{
#include <features.h>
#include <stdint.h>
#include <bits/types.h>
#include <bits/eventfd.h>


/* Documentation taken from Glibc /usr/include/i386-linux-gnu/sys/eventfd.h */
/* Copyright (C) 2007-2016 Free Software Foundation, Inc.
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

__SYSDECL_BEGIN

#ifdef __CC__

/* Type for event counter. */
#ifndef __eventfd_t_defined
#define __eventfd_t_defined 1
typedef uint64_t eventfd_t;
#endif /* !__eventfd_t_defined */

}

@@Return file descriptor for generic event channel. Set initial value to COUNT
[[wunused, decl_include("<features.h>", "<bits/types.h>")]]
$fd_t eventfd(__STDC_UINT_AS_SIZE_T count,
              __STDC_INT_AS_UINT_T flags);

@@Read event counter and possibly wait for events
[[cp, userimpl, requires_function(read)]]
[[decl_include("<bits/types.h>"), impl_include("<parts/errno.h>")]]
int eventfd_read($fd_t fd, eventfd_t *value) {
	ssize_t error;
	error = read(fd, value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
@@pp_ifdef EINVAL@@
	if (error >= 0)
		__libc_seterrno(EINVAL);
@@pp_endif@@
	return -1;
}

@@Increment event counter
[[cp, userimpl, requires_function(write)]]
[[decl_include("<bits/types.h>"), impl_include("<parts/errno.h>")]]
int eventfd_write($fd_t fd, eventfd_t value) {
	ssize_t error;
	error = write(fd, &value, sizeof(eventfd_t));
	if (error == sizeof(eventfd_t))
		return 0;
@@pp_ifdef EINVAL@@
	if (error >= 0)
		__libc_seterrno(EINVAL);
@@pp_endif@@
	return -1;
}

%{
#endif /* __CC__ */

__SYSDECL_END

}