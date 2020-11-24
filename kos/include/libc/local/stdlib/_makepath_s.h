/* HASH CRC-32:0xf9c502b */
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
#ifndef __local__makepath_s_defined
#define __local__makepath_s_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mempcpyc from string */
#ifndef __local___localdep_mempcpyc_defined
#define __local___localdep_mempcpyc_defined 1
#ifdef __CRT_HAVE_mempcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyc.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `memcpyc', but return `DST + (ELEM_COUNT * ELEM_SIZE)', rather than `DST' */
#define __localdep_mempcpyc __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__CRT_HAVE_mempcpyc */
#endif /* !__local___localdep_mempcpyc_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_makepath_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_makepath_s))(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext) {
#define __path_putn(__p, __n)                                  \
	do {                                                 \
		if __unlikely(__buflen < __n)                          \
			goto __err_buflen;                             \
		__buf = (char *)__localdep_mempcpyc(__buf, __p, __n, sizeof(char)); \
	} __WHILE0
#define __path_putc(__ch)          \
	do {                       \
		if __unlikely(!__buflen--) \
			goto __err_buflen;   \
		*__buf++ = (__ch);         \
	} __WHILE0
	if (__drive && *__drive) {
		__path_putc(*__drive);
		__path_putc(':');
	}
	if (__dir && *__dir) {
		__SIZE_TYPE__ __len = __localdep_strlen(__dir);
		__path_putn(__dir, __len);
		if (__dir[__len - 1] != '/' && __dir[__len - 1] != '\\')
			__path_putc('\\');
	}
	if (__file && *__file) {
		__SIZE_TYPE__ __len = __localdep_strlen(__file);
		__path_putn(__file, __len);
	}
	if (__ext && *__ext) {
		__SIZE_TYPE__ __len = __localdep_strlen(__ext);
		if (*__ext != '.')
			__path_putc('.');
		__path_putn(__ext, __len);
	}
	__path_putc('\0');
	return 0;
__err_buflen:
#ifdef __EINVAL
	return __EINVAL;
#else /* EINVAL */
	return 1;
#endif /* !EINVAL */
#undef __path_putn
#undef __path_putc
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__makepath_s_defined
#define __local___localdep__makepath_s_defined 1
#define __localdep__makepath_s __LIBC_LOCAL_NAME(_makepath_s)
#endif /* !__local___localdep__makepath_s_defined */
#endif /* !__local__makepath_s_defined */
