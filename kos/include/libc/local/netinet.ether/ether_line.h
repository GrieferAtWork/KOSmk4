/* HASH CRC-32:0xe4d588e2 */
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
#ifndef __local_ether_line_defined
#define __local_ether_line_defined
#include <__crt.h>
struct ether_addr;
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ether_paton_r_defined
#define __local___localdep_ether_paton_r_defined
#ifdef __CRT_HAVE_ether_paton_r
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_OUT(2),struct ether_addr *,__NOTHROW_NCX,__localdep_ether_paton_r,(char const **__restrict __pasc, struct ether_addr *__restrict __addr),ether_paton_r,(__pasc,__addr))
#else /* __CRT_HAVE_ether_paton_r */
__NAMESPACE_LOCAL_END
#include <libc/local/netinet.ether/ether_paton_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ether_paton_r __LIBC_LOCAL_NAME(ether_paton_r)
#endif /* !__CRT_HAVE_ether_paton_r */
#endif /* !__local___localdep_ether_paton_r_defined */
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isspace) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __crt_isspace(__ch); })
#elif defined(__crt_isspace)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isspace)(int __ch) { return __crt_isspace(__ch); }
#elif __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#endif /* !__local___localdep_isspace_defined */
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
#ifdef __CRT_HAVE_mempcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
__NAMESPACE_LOCAL_END
#include <net/ethernet.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ether_line) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) __ATTR_OUT(3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_line))(char const *__line, struct ether_addr *__addr, char *__hostname) {
	__SIZE_TYPE__ __hnlen;
	while ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__line) && *__line != '\r' && *__line != '\n')
		++__line;
	if (!(__NAMESPACE_LOCAL_SYM __localdep_ether_paton_r)(&__line, __addr))
		return -1; /* This also handles comment lines! */
	while ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__line) && *__line != '\r' && *__line != '\n')
		++__line;
	/* The remainder of the line is the hostname. */
	for (__hnlen = 0;
	     __line[__hnlen] &&
	     __line[__hnlen] != '\r' &&
	     __line[__hnlen] != '\n';
	     ++__hnlen)
		;
	while (__hnlen && (__NAMESPACE_LOCAL_SYM __localdep_isspace)(__line[__hnlen - 1]))
		--__hnlen;
	if (!__hnlen)
		return -1; /* No hostname */
	__hostname = (char *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__hostname, __line, __hnlen);
	*__hostname = '\0'; /* NUL-terminate */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ether_line_defined
#define __local___localdep_ether_line_defined
#define __localdep_ether_line __LIBC_LOCAL_NAME(ether_line)
#endif /* !__local___localdep_ether_line_defined */
#endif /* !__local_ether_line_defined */
