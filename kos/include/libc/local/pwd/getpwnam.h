/* HASH CRC-32:0x56afa22d */
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
#ifndef __local_getpwnam_defined
#define __local_getpwnam_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setpwent) && defined(__CRT_HAVE_getpwent)
#include <bits/crt/db/passwd.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getpwent_defined
#define __local___localdep_getpwent_defined
__CREDIRECT(,struct passwd *,__NOTHROW_RPC,__localdep_getpwent,(void),getpwent,())
#endif /* !__local___localdep_getpwent_defined */
#ifndef __local___localdep_setpwent_defined
#define __local___localdep_setpwent_defined
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_setpwent,(void),setpwent,())
#endif /* !__local___localdep_setpwent_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
__LOCAL_LIBC(getpwnam) __ATTR_WUNUSED __ATTR_IN(1) struct passwd *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getpwnam))(char const *__name) {
	struct passwd *__result;
	(__NAMESPACE_LOCAL_SYM __localdep_setpwent)();
	while ((__result = (__NAMESPACE_LOCAL_SYM __localdep_getpwent)()) != __NULLPTR) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__result->pw_name, __name) == 0)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getpwnam_defined
#define __local___localdep_getpwnam_defined
#define __localdep_getpwnam __LIBC_LOCAL_NAME(getpwnam)
#endif /* !__local___localdep_getpwnam_defined */
#else /* __CRT_HAVE_setpwent && __CRT_HAVE_getpwent */
#undef __local_getpwnam_defined
#endif /* !__CRT_HAVE_setpwent || !__CRT_HAVE_getpwent */
#endif /* !__local_getpwnam_defined */
