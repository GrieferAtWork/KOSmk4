/* HASH CRC-32:0xbb24e768 */
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
#ifndef __local_getdomainname_defined
#define __local_getdomainname_defined
#include <__crt.h>
#include <bits/os/utsname.h>
#if (defined(__CRT_HAVE_uname) || defined(__CRT_HAVE___uname) || defined(__CRT_HAVE___libc_uname)) && defined(__OFFSET_UTSNAME_DOMAINNAME) && defined(_UTSNAME_DOMAIN_LENGTH) && _UTSNAME_DOMAIN_LENGTH
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__str, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),strnlen,(__str,__maxlen))
#elif defined(__CRT_HAVE___strncnt)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 2) __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __str, __SIZE_TYPE__ __maxlen),__strncnt,(__str,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#endif /* !__local___localdep_strnlen_defined */
#ifndef __local___localdep_uname_defined
#define __local___localdep_uname_defined
#ifdef __CRT_HAVE_uname
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_uname,(struct utsname *__name),uname,(__name))
#elif defined(__CRT_HAVE___uname)
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_uname,(struct utsname *__name),__uname,(__name))
#elif defined(__CRT_HAVE___libc_uname)
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_uname,(struct utsname *__name),__libc_uname,(__name))
#else /* ... */
#undef __local___localdep_uname_defined
#endif /* !... */
#endif /* !__local___localdep_uname_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getdomainname) __ATTR_OUTS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getdomainname))(char *__name, __SIZE_TYPE__ __buflen) {
#ifndef __PRIVATE_UTSNAME_DOMAINNAME
#define __PRIVATE_UTSNAME_DOMAINNAME domainname
#endif /* !__PRIVATE_UTSNAME_DOMAINNAME */
	struct utsname __uts;
	int __result = (__NAMESPACE_LOCAL_SYM __localdep_uname)(&__uts);
	if (__result == 0) {
		__SIZE_TYPE__ __len = (__NAMESPACE_LOCAL_SYM __localdep_strnlen)(__uts.__PRIVATE_UTSNAME_DOMAINNAME, _UTSNAME_DOMAIN_LENGTH);
		if (__buflen <= __len) {
			/* EINVAL For getdomainname() under libc: name is NULL or name is longer than len bytes. */
#ifdef __EINVAL
			return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
			return __libc_seterrno(1);
#endif /* !__EINVAL */
		}
		(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__name, __uts.__PRIVATE_UTSNAME_DOMAINNAME, __len * sizeof(char));
		__name[__len] = '\0';
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getdomainname_defined
#define __local___localdep_getdomainname_defined
#define __localdep_getdomainname __LIBC_LOCAL_NAME(getdomainname)
#endif /* !__local___localdep_getdomainname_defined */
#else /* (__CRT_HAVE_uname || __CRT_HAVE___uname || __CRT_HAVE___libc_uname) && __OFFSET_UTSNAME_DOMAINNAME && _UTSNAME_DOMAIN_LENGTH && _UTSNAME_DOMAIN_LENGTH */
#undef __local_getdomainname_defined
#endif /* (!__CRT_HAVE_uname && !__CRT_HAVE___uname && !__CRT_HAVE___libc_uname) || !__OFFSET_UTSNAME_DOMAINNAME || !_UTSNAME_DOMAIN_LENGTH || !_UTSNAME_DOMAIN_LENGTH */
#endif /* !__local_getdomainname_defined */
