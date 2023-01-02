/* HASH CRC-32:0x88163ee4 */
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
#ifndef __local_uid_from_user_defined
#define __local_uid_from_user_defined
#include <__crt.h>
#if defined(__CRT_HAVE_getpwnam) || (defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpwnam_defined
#define __local___localdep_getpwnam_defined
#ifdef __CRT_HAVE_getpwnam
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),struct passwd *,__NOTHROW_RPC,__localdep_getpwnam,(char const *__name),getpwnam,(__name))
#elif defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent)
__NAMESPACE_LOCAL_END
#include <libc/local/pwd/getpwnam.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getpwnam __LIBC_LOCAL_NAME(getpwnam)
#else /* ... */
#undef __local___localdep_getpwnam_defined
#endif /* !... */
#endif /* !__local___localdep_getpwnam_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(uid_from_user) __ATTR_IN(1) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(uid_from_user))(char const *__name, __uid_t *__p_uid) {
	struct passwd *__ent = (__NAMESPACE_LOCAL_SYM __localdep_getpwnam)(__name);
	if (__ent) {
		*__p_uid = __ent->pw_uid;
		return 0;
	}
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_uid_from_user_defined
#define __local___localdep_uid_from_user_defined
#define __localdep_uid_from_user __LIBC_LOCAL_NAME(uid_from_user)
#endif /* !__local___localdep_uid_from_user_defined */
#else /* __CRT_HAVE_getpwnam || (__CRT_HAVE_setpwent && __CRT_HAVE_getpwent) */
#undef __local_uid_from_user_defined
#endif /* !__CRT_HAVE_getpwnam && (!__CRT_HAVE_setpwent || !__CRT_HAVE_getpwent) */
#endif /* !__local_uid_from_user_defined */
