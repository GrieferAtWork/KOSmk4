/* HASH CRC-32:0x1073d650 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getenv_defined
#define __local_getenv_defined 1
#include <__crt.h>
#include <libc/local/environ.h>
#ifdef __LOCAL_environ
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined 1
#ifdef __CRT_HAVE_memcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getenv) __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getenv))(char const *__varname) {
	char *__result, **___envp;
	if __unlikely(!__varname)
		return __NULLPTR;
	___envp = __LOCAL_environ;
	if __unlikely(!___envp)
		__result = __NULLPTR;
	else {
		__SIZE_TYPE__ __namelen;
		__namelen = __localdep_strlen(__varname);
		for (; (__result = *___envp) != __NULLPTR; ++___envp) {
			if (__localdep_memcmp(__result, __varname, __namelen * sizeof(char)) != 0 ||
			    __result[__namelen] != '=')
				continue;
			__result += __namelen + 1;
			break;
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined 1
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#endif /* !__local___localdep_getenv_defined */
#else /* __LOCAL_environ */
#undef __local_getenv_defined
#endif /* !__LOCAL_environ */
#endif /* !__local_getenv_defined */
