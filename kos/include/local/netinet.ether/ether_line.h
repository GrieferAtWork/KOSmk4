/* HASH CRC-32:0xf2ef8c03 */
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
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
/* Dependency: "isspace" from "ctype" */
#ifndef ____localdep_isspace_defined
#define ____localdep_isspace_defined 1
#if __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* LIBC: isspace */
#include <local/ctype/isspace.h>
#define __localdep_isspace (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(isspace))
#endif /* isspace... */
#endif /* !____localdep_isspace_defined */

/* Dependency: "ether_paton_r" from "netinet.ether" */
#ifndef ____localdep_ether_paton_r_defined
#define ____localdep_ether_paton_r_defined 1
#ifdef __CRT_HAVE_ether_paton_r
/* Convert ASCII string S to 48 bit Ethernet address */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),struct ether_addr *,__NOTHROW_NCX,__localdep_ether_paton_r,(char const **__restrict __pasc, struct ether_addr *__restrict __addr),ether_paton_r,(__pasc,__addr))
#else /* LIBC: ether_paton_r */
#include <local/netinet.ether/ether_paton_r.h>
/* Convert ASCII string S to 48 bit Ethernet address */
#define __localdep_ether_paton_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(ether_paton_r))
#endif /* ether_paton_r... */
#endif /* !____localdep_ether_paton_r_defined */

/* Dependency: "mempcpy" from "string" */
#ifndef ____localdep_mempcpy_defined
#define ____localdep_mempcpy_defined 1
#ifdef __fast_mempcpy_defined
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(mempcpy))
#elif defined(__CRT_HAVE_mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* LIBC: mempcpy */
#include <local/string/mempcpy.h>
/* Same as `memcpy', but return `DST + N_BYTES', rather than `DST' */
#define __localdep_mempcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mempcpy))
#endif /* mempcpy... */
#endif /* !____localdep_mempcpy_defined */

__NAMESPACE_LOCAL_BEGIN
/* Scan LINE and set ADDR and HOSTNAME */
__LOCAL_LIBC(ether_line) __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ether_line))(char const *__line,
                                                        struct ether_addr *__addr,
                                                        char *__hostname) {
#line 134 "kos/src/libc/magic/netinet.ether.c"
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
#endif /* !__local_ether_line_defined */
