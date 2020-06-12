/* HASH CRC-32:0xab09732e */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ether_line_defined
#define __local_ether_line_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mempcpy from string */
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined 1
#ifdef __CRT_HAVE_mempcpy
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
/* Dependency: isspace from ctype */
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined 1
#if __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/ctype/isspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#endif /* !__local___localdep_isspace_defined */
/* Dependency: ether_paton_r from netinet.ether */
#ifndef __local___localdep_ether_paton_r_defined
#define __local___localdep_ether_paton_r_defined 1
#ifdef __CRT_HAVE_ether_paton_r
/* Convert ASCII string S to 48 bit Ethernet address */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),struct ether_addr *,__NOTHROW_NCX,__localdep_ether_paton_r,(char const **__restrict __pasc, struct ether_addr *__restrict __addr),ether_paton_r,(__pasc,__addr))
#else /* __CRT_HAVE_ether_paton_r */
__NAMESPACE_LOCAL_END
#include <local/netinet.ether/ether_paton_r.h>
__NAMESPACE_LOCAL_BEGIN
/* Convert ASCII string S to 48 bit Ethernet address */
#define __localdep_ether_paton_r __LIBC_LOCAL_NAME(ether_paton_r)
#endif /* !__CRT_HAVE_ether_paton_r */
#endif /* !__local___localdep_ether_paton_r_defined */
/* Scan LINE and set ADDR and HOSTNAME */
__LOCAL_LIBC(ether_line) __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_line))(char const *__line, struct ether_addr *__addr, char *__hostname) {
	__SIZE_TYPE__ __hnlen;
	while (__localdep_isspace(*__line) && *__line != '\r' && *__line != '\n')
		++__line;
	if (!__localdep_ether_paton_r(&__line, __addr))
		return -1; /* This also handles comment lines! */
	while (__localdep_isspace(*__line) && *__line != '\r' && *__line != '\n')
		++__line;
	/* The remainder of the line is the hostname. */
	for (__hnlen = 0; __line[__hnlen] && __line[__hnlen] != '\r' && __line[__hnlen] != '\n'; ++__hnlen)
		;
	while (__hnlen && __localdep_isspace(__line[__hnlen - 1]))
		--__hnlen;
	if (!__hnlen)
		return -1; /* No hostname */
	__hostname = (char *)__localdep_mempcpy(__hostname, __line, __hnlen);
	*__hostname = '\0'; /* NUL-terminate */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ether_line_defined
#define __local___localdep_ether_line_defined 1
#define __localdep_ether_line __LIBC_LOCAL_NAME(ether_line)
#endif /* !__local___localdep_ether_line_defined */
#endif /* !__local_ether_line_defined */
