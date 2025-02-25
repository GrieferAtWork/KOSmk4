/* HASH CRC-32:0x6a1ee266 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getgrnam_defined
#define __local_getgrnam_defined
#include <__crt.h>
#if defined(__CRT_HAVE_setgrent) && defined(__CRT_HAVE_getgrent)
#include <bits/crt/db/group.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getgrent_defined
#define __local___localdep_getgrent_defined
__CREDIRECT(__ATTR_WUNUSED,struct group *,__NOTHROW_RPC,__localdep_getgrent,(void),getgrent,())
#endif /* !__local___localdep_getgrent_defined */
#ifndef __local___localdep_setgrent_defined
#define __local___localdep_setgrent_defined
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_setgrent,(void),setgrent,())
#endif /* !__local___localdep_setgrent_defined */
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
__LOCAL_LIBC(getgrnam) __ATTR_WUNUSED __ATTR_IN(1) struct group *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getgrnam))(char const *__restrict __name) {
	struct group *__result;
	(__NAMESPACE_LOCAL_SYM __localdep_setgrent)();
	while ((__result = (__NAMESPACE_LOCAL_SYM __localdep_getgrent)()) != __NULLPTR) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__result->gr_name, __name) == 0)
			break;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getgrnam_defined
#define __local___localdep_getgrnam_defined
#define __localdep_getgrnam __LIBC_LOCAL_NAME(getgrnam)
#endif /* !__local___localdep_getgrnam_defined */
#else /* __CRT_HAVE_setgrent && __CRT_HAVE_getgrent */
#undef __local_getgrnam_defined
#endif /* !__CRT_HAVE_setgrent || !__CRT_HAVE_getgrent */
#endif /* !__local_getgrnam_defined */
