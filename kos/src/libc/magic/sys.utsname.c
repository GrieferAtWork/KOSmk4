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
#include <features.h>
#include <bits/utsname.h>

__SYSDECL_BEGIN

#ifndef _UTSNAME_SYSNAME_LENGTH
#define _UTSNAME_SYSNAME_LENGTH  _UTSNAME_LENGTH
#endif /* !_UTSNAME_SYSNAME_LENGTH */
#ifndef _UTSNAME_NODENAME_LENGTH
#define _UTSNAME_NODENAME_LENGTH _UTSNAME_LENGTH
#endif /* !_UTSNAME_NODENAME_LENGTH */
#ifndef _UTSNAME_RELEASE_LENGTH
#define _UTSNAME_RELEASE_LENGTH  _UTSNAME_LENGTH
#endif /* !_UTSNAME_RELEASE_LENGTH */
#ifndef _UTSNAME_VERSION_LENGTH
#define _UTSNAME_VERSION_LENGTH  _UTSNAME_LENGTH
#endif /* !_UTSNAME_VERSION_LENGTH */
#ifndef _UTSNAME_MACHINE_LENGTH
#define _UTSNAME_MACHINE_LENGTH  _UTSNAME_LENGTH
#endif /* !_UTSNAME_MACHINE_LENGTH */

/* Note that SVID assumes all members have the same size.  */
#ifdef __USE_MISC
#define SYS_NMLN    _UTSNAME_LENGTH
#endif /* __USE_MISC */





/* Some documentation comments are taken from /usr/include/i386-linux-gnu/sys/utsname.h on a linux machine.
 * The following copyright notice can be found at the top of that file: */
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
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

}%[push_macro @undef { sysname nodename release version machine }]%{
#if defined(__USE_GNU) && (_UTSNAME_DOMAIN_LENGTH-0) != 0
}%[push_macro @undef { domainname }]%{
#endif /* __USE_GNU && _UTSNAME_DOMAIN_LENGTH != 0 */

/* Structure describing the system and machine.  */
struct utsname {
	char sysname[_UTSNAME_SYSNAME_LENGTH];   /* Name of the implementation of the operating system. */
	char nodename[_UTSNAME_NODENAME_LENGTH]; /* Name of this node on the network. */
	char release[_UTSNAME_RELEASE_LENGTH];   /* Current release level of this implementation. */
	char version[_UTSNAME_VERSION_LENGTH];   /* Current version level of this release. */
	char machine[_UTSNAME_MACHINE_LENGTH];   /* Name of the hardware type the system is running on. */
#if (_UTSNAME_DOMAIN_LENGTH-0) != 0
#ifdef __USE_GNU
	char domainname[_UTSNAME_DOMAIN_LENGTH]; /* Name of the domain of this node on the network. */
#else /* __USE_GNU */
	char __domainname[_UTSNAME_DOMAIN_LENGTH]; /* Name of the domain of this node on the network. */
#endif /* !__USE_GNU */
#endif /* (_UTSNAME_DOMAIN_LENGTH-0) != 0 */
};

#if defined(__USE_GNU) && (_UTSNAME_DOMAIN_LENGTH-0) != 0
}%[pop_macro]%{
#endif /* __USE_GNU && _UTSNAME_DOMAIN_LENGTH != 0 */
}%[pop_macro]%{

}

@@Put information about the system in NAME
int uname([[nonnull]] struct utsname *name);

%{

#endif /* __CC__ */

__SYSDECL_END

}