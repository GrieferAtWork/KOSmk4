/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_COMPAT_LINUX_UNAME_H
#define _I386_KOS_KOS_COMPAT_LINUX_UNAME_H 1

#include <__stdinc.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("sysname")
#pragma push_macro("nodename")
#pragma push_macro("release")
#pragma push_macro("version")
#pragma push_macro("machine")
#pragma push_macro("domainname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#undef sysname
#undef nodename
#undef release
#undef version
#undef machine
#undef domainname

struct linux_oldolduname {
	char sysname[9];     /* Name of the implementation of the operating system. */
	char nodename[9];    /* Name of this node on the network. */
	char release[9];     /* Current release level of this implementation. */
	char version[9];     /* Current version level of this release. */
	char machine[9];     /* Name of the hardware type the system is running on. */
};

struct linux_olduname {
	char sysname[65];    /* Name of the implementation of the operating system. */
	char nodename[65];   /* Name of this node on the network. */
	char release[65];    /* Current release level of this implementation. */
	char version[65];    /* Current version level of this release. */
	char machine[65];    /* Name of the hardware type the system is running on. */
};

struct linux_uname {
	char sysname[65];    /* Name of the implementation of the operating system. */
	char nodename[65];   /* Name of this node on the network. */
	char release[65];    /* Current release level of this implementation. */
	char version[65];    /* Current version level of this release. */
	char machine[65];    /* Name of the hardware type the system is running on. */
	char domainname[65]; /* Name of the domain of this node on the network. */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("domainname")
#pragma pop_macro("machine")
#pragma pop_macro("version")
#pragma pop_macro("release")
#pragma pop_macro("nodename")
#pragma pop_macro("sysname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */


__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_COMPAT_LINUX_UNAME_H */
