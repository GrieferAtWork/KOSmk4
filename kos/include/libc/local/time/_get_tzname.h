/* HASH CRC-32:0x880fa3cd */
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
#ifndef __local__get_tzname_defined
#define __local__get_tzname_defined
#include <__crt.h>
#include <libc/template/tzname.h>
#ifdef __LOCAL_tzname
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_tzset_defined
#define __local___localdep_tzset_defined
#ifdef __CRT_HAVE_tzset
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_tzset,(void),tzset,())
#elif defined(__CRT_HAVE__tzset)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_tzset,(void),_tzset,())
#else /* ... */
#undef __local___localdep_tzset_defined
#endif /* !... */
#endif /* !__local___localdep_tzset_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_get_tzname) __ATTR_OUT(1) __ATTR_OUT_OPT(2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_get_tzname))(__SIZE_TYPE__ *__result, char *__buf, __SIZE_TYPE__ __bufsize, int __index) {
	char *__reqstr;
	__SIZE_TYPE__ __reqsiz;
	if (__index < 0 || __index > 1 || !__result || (!__buf && __bufsize)) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
#if defined(__CRT_HAVE_tzset) || defined(__CRT_HAVE__tzset)
	(__NAMESPACE_LOCAL_SYM __localdep_tzset)(); /* Update state of `tzname' */
#endif /* __CRT_HAVE_tzset || __CRT_HAVE__tzset */
	__reqstr  = __LOCAL_tzname[(unsigned int)__index];
	__reqsiz  = ((__NAMESPACE_LOCAL_SYM __localdep_strlen)(__reqstr) + 1) * sizeof(char);
	*__result = __reqsiz;
	if (__bufsize > __reqsiz)
		__bufsize = __reqsiz;
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__buf, __reqstr, __bufsize);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_tzname_defined
#define __local___localdep__get_tzname_defined
#define __localdep__get_tzname __LIBC_LOCAL_NAME(_get_tzname)
#endif /* !__local___localdep__get_tzname_defined */
#else /* __LOCAL_tzname */
#undef __local__get_tzname_defined
#endif /* !__LOCAL_tzname */
#endif /* !__local__get_tzname_defined */
