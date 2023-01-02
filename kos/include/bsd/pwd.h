/* HASH CRC-32:0x725311f8 */
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
/* (#) Portability: libbsd (/include/bsd/pwd.h) */
#ifndef _BSD_PWD_H
#define _BSD_PWD_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <pwd.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __uid_from_user_defined
#define __uid_from_user_defined
#ifdef __CRT_HAVE_uid_from_user
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,uid_from_user,(char const *__name, uid_t *__p_uid),(__name,__p_uid))
#elif defined(__CRT_HAVE_getpwnam) || (defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent))
#include <libc/local/pwd/uid_from_user.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(uid_from_user, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL uid_from_user)(char const *__name, uid_t *__p_uid) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(uid_from_user))(__name, __p_uid); })
#else /* ... */
#undef __uid_from_user_defined
#endif /* !... */
#endif /* !__uid_from_user_defined */
#ifndef __user_from_uid_defined
#define __user_from_uid_defined
#ifdef __CRT_HAVE_user_from_uid
__CDECLARE(__ATTR_WUNUSED,char const *,__NOTHROW_NCX,user_from_uid,(uid_t __uid, int __nouser),(__uid,__nouser))
#elif defined(__CRT_HAVE_getpwuid) || (defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent))
#include <libc/local/pwd/user_from_uid.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(user_from_uid, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED char const *__NOTHROW_NCX(__LIBCCALL user_from_uid)(uid_t __uid, int __nouser) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(user_from_uid))(__uid, __nouser); })
#else /* ... */
#undef __user_from_uid_defined
#endif /* !... */
#endif /* !__user_from_uid_defined */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_PWD_H */
