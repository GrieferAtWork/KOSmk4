/* HASH 0x7326d10 */
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
#ifndef _SYS_UTSNAME_H
#define _SYS_UTSNAME_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/utsname.h>

__SYSDECL_BEGIN

#ifndef _UTSNAME_SYSNAME_LENGTH
#define _UTSNAME_SYSNAME_LENGTH  _UTSNAME_LENGTH
#endif
#ifndef _UTSNAME_NODENAME_LENGTH
#define _UTSNAME_NODENAME_LENGTH _UTSNAME_LENGTH
#endif
#ifndef _UTSNAME_RELEASE_LENGTH
#define _UTSNAME_RELEASE_LENGTH  _UTSNAME_LENGTH
#endif
#ifndef _UTSNAME_VERSION_LENGTH
#define _UTSNAME_VERSION_LENGTH  _UTSNAME_LENGTH
#endif
#ifndef _UTSNAME_MACHINE_LENGTH
#define _UTSNAME_MACHINE_LENGTH  _UTSNAME_LENGTH
#endif

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

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("sysname")
#pragma push_macro("nodename")
#pragma push_macro("release")
#pragma push_macro("version")
#pragma push_macro("machine")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef sysname
#undef nodename
#undef release
#undef version
#undef machine
#if defined(__USE_GNU) && (_UTSNAME_DOMAIN_LENGTH-0) != 0
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("domainname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef domainname
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
#else
	char __domainname[_UTSNAME_DOMAIN_LENGTH]; /* Name of the domain of this node on the network. */
#endif
#endif
};

#if defined(__USE_GNU) && (_UTSNAME_DOMAIN_LENGTH-0) != 0
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("domainname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __USE_GNU && _UTSNAME_DOMAIN_LENGTH != 0 */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("machine")
#pragma pop_macro("version")
#pragma pop_macro("release")
#pragma pop_macro("nodename")
#pragma pop_macro("sysname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#if defined(__CRT_HAVE_uname)
/* Put information about the system in NAME */
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,uname,(struct utsname *__name),(__name))
#endif /* uname... */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_SYS_UTSNAME_H */
