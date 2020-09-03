/* HASH CRC-32:0x4b148bfa */
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
#ifndef __local_inet_neta_defined
#define __local_inet_neta_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memcpy from string */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined 1
#ifdef __CRT_HAVE_memcpy
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
/* Dependency: snprintf from stdio */
#ifndef __local___localdep_snprintf_defined
#define __local___localdep_snprintf_defined 1
#if __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_snprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...),snprintf,{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_snprintf)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) __CASMNAME("snprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/snprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* Print a formatted string to a given in-member string buffer `BUF'
 * Always return the REQUIRED buffer size (excluding a trailing NUL-character),
 * and never write more than `BUFLEN' characters to `BUF' */
#define __localdep_snprintf __LIBC_LOCAL_NAME(snprintf)
#endif /* !... */
#endif /* !__local___localdep_snprintf_defined */
__NAMESPACE_LOCAL_END
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Similar to `inet_ntoa_r(3)', but use smaller formats if possible:
 *     0.0.0.0      For net = 0
 *     %u           For net <= 255
 *     %u.%u        For net <= 65535
 *     %u.%u.%u     For net <= 16777215
 *     %u.%u.%u.%u  For everything else
 * @return: buf:  Success
 * @return: NULL: [errno=EMSGSIZE]: The given `len' is too small */
__LOCAL_LIBC(inet_neta) __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(inet_neta))(__UINT32_TYPE__ __net, char *__buf, __SIZE_TYPE__ __len) {
	__SIZE_TYPE__ __reqlen;
	if (__net <= 0xff) {
		if (!__net) {
			__reqlen = 8;
			if __likely(__len >= 8)
				__localdep_memcpy(__buf, "0.0.0.0", 8 * sizeof(char));
		} else {
			__reqlen = __localdep_snprintf(__buf, __len, "%u", (unsigned int)__net);
		}
	} else if (__net <= 0xffff) {
		__reqlen = __localdep_snprintf(__buf, __len, "%u.%u",
		                  (unsigned int)((__net & 0xff00) >> 8),
		                  (unsigned int)(__net & 0xff));
	} else if (__net <= 0xffffff) {
		__reqlen = __localdep_snprintf(__buf, __len, "%u.%u.%u",
		                  (unsigned int)((__net & 0xff0000) >> 16),
		                  (unsigned int)((__net & 0xff00) >> 8),
		                  (unsigned int)(__net & 0xff));
	} else {
		__reqlen = __localdep_snprintf(__buf, __len, "%u.%u.%u.%u",
		                  (unsigned int)((__net & 0xff000000) >> 24),
		                  (unsigned int)((__net & 0xff0000) >> 16),
		                  (unsigned int)((__net & 0xff00) >> 8),
		                  (unsigned int)(__net & 0xff));
	}
	if __unlikely(__reqlen > __len)
		goto __too_small;
	return __buf;
__too_small:
#ifdef __EMSGSIZE
	__libc_seterrno(__EMSGSIZE);
#elif defined(__ERANGE)
	__libc_seterrno(__ERANGE);
#elif defined(__EINVAL)
	__libc_seterrno(__EINVAL);
#endif /* ... */
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_inet_neta_defined
#define __local___localdep_inet_neta_defined 1
#define __localdep_inet_neta __LIBC_LOCAL_NAME(inet_neta)
#endif /* !__local___localdep_inet_neta_defined */
#endif /* !__local_inet_neta_defined */
