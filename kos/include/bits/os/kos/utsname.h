/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_UTSNAME_H
#define _BITS_OS_KOS_UTSNAME_H 1

#include <__stdinc.h>
#include <features.h>

#include <asm/os/utsname.h> /* _UTSNAME_*_LENGTH */

#define __OFFSET_UTSNAME_SYSNAME    0
#define __OFFSET_UTSNAME_NODENAME   _UTSNAME_SYSNAME_LENGTH
#define __OFFSET_UTSNAME_RELEASE    (_UTSNAME_SYSNAME_LENGTH + _UTSNAME_NODENAME_LENGTH)
#define __OFFSET_UTSNAME_VERSION    (_UTSNAME_SYSNAME_LENGTH + _UTSNAME_NODENAME_LENGTH + _UTSNAME_RELEASE_LENGTH)
#define __OFFSET_UTSNAME_MACHINE    (_UTSNAME_SYSNAME_LENGTH + _UTSNAME_NODENAME_LENGTH + _UTSNAME_RELEASE_LENGTH + _UTSNAME_VERSION_LENGTH)
#define __OFFSET_UTSNAME_DOMAINNAME (_UTSNAME_SYSNAME_LENGTH + _UTSNAME_NODENAME_LENGTH + _UTSNAME_RELEASE_LENGTH + _UTSNAME_VERSION_LENGTH + _UTSNAME_MACHINE_LENGTH)
#define __SIZEOF_UTSNAME            (_UTSNAME_SYSNAME_LENGTH + _UTSNAME_NODENAME_LENGTH + _UTSNAME_RELEASE_LENGTH + _UTSNAME_VERSION_LENGTH + _UTSNAME_MACHINE_LENGTH + _UTSNAME_DOMAIN_LENGTH)
#define __ALIGNOF_UTSNAME           1

#ifdef __CC__
__DECL_BEGIN

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
#if defined(__USE_GNU) && _UTSNAME_DOMAIN_LENGTH
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("domainname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef domainname
#endif /* __USE_GNU && _UTSNAME_DOMAIN_LENGTH */

/* Structure describing the system and machine.  */
struct utsname /*[PREFIX()]*/ {
	char sysname[_UTSNAME_SYSNAME_LENGTH];   /* Name of the implementation of the operating system. */
	char nodename[_UTSNAME_NODENAME_LENGTH]; /* Name of this node on the network. */
	char release[_UTSNAME_RELEASE_LENGTH];   /* Current release level of this implementation. */
	char version[_UTSNAME_VERSION_LENGTH];   /* Current version level of this release. */
	char machine[_UTSNAME_MACHINE_LENGTH];   /* Name of the hardware type the system is running on. */
#if _UTSNAME_DOMAIN_LENGTH
#ifdef __USE_GNU
	char domainname[_UTSNAME_DOMAIN_LENGTH]; /* Name of the domain of this node on the network. */
#define __PRIVATE_UTSNAME_DOMAINNAME domainname
#else /* __USE_GNU */
	char __domainname[_UTSNAME_DOMAIN_LENGTH]; /* Name of the domain of this node on the network. */
#define __PRIVATE_UTSNAME_DOMAINNAME __domainname
#endif /* !__USE_GNU */
#endif /* _UTSNAME_DOMAIN_LENGTH */
};

#if defined(__USE_GNU) && _UTSNAME_DOMAIN_LENGTH
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("domainname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#endif /* __USE_GNU && _UTSNAME_DOMAIN_LENGTH */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("machine")
#pragma pop_macro("version")
#pragma pop_macro("release")
#pragma pop_macro("nodename")
#pragma pop_macro("sysname")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_UTSNAME_H */
