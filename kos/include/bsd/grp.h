/* HASH CRC-32:0x39e805f9 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: libbsd (/include/bsd/grp.h) */
#ifndef _BSD_GRP_H
#define _BSD_GRP_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <grp.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef _GR_BUF_LEN
#define _GR_BUF_LEN (1024 + 200 * sizeof(char *)) /* ??? */
#endif /* !_GR_BUF_LEN */

#ifndef __gid_from_group_defined
#define __gid_from_group_defined
#ifdef __CRT_HAVE_gid_from_group
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,gid_from_group,(char const *__name, gid_t *__p_gid),(__name,__p_gid))
#elif defined(__CRT_HAVE_getgrnam) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))
#include <libc/local/grp/gid_from_group.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(gid_from_group, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL gid_from_group)(char const *__name, gid_t *__p_gid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(gid_from_group))(__name, __p_gid); })
#else /* ... */
#undef __gid_from_group_defined
#endif /* !... */
#endif /* !__gid_from_group_defined */
#ifndef __group_from_gid_defined
#define __group_from_gid_defined
#ifdef __CRT_HAVE_group_from_gid
__CDECLARE(__ATTR_WUNUSED,char const *,__NOTHROW_NCX,group_from_gid,(gid_t __gid, int __nogroup),(__gid,__nogroup))
#elif defined(__CRT_HAVE_getgrgid) || (defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent))
#include <libc/local/grp/group_from_gid.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(group_from_gid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL group_from_gid)(gid_t __gid, int __nogroup) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(group_from_gid))(__gid, __nogroup); })
#else /* ... */
#undef __group_from_gid_defined
#endif /* !... */
#endif /* !__group_from_gid_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_GRP_H */
