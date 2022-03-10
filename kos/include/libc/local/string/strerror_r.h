/* HASH CRC-32:0xe564aa08 */
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
#ifndef __local_strerror_r_defined
#define __local_strerror_r_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
#ifndef __local___localdep_snprintf_defined
#define __local___localdep_snprintf_defined
#if __has_builtin(__builtin_snprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_snprintf) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_snprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...),snprintf,{ return __builtin_snprintf(__buf, __buflen, __format, __builtin_va_arg_pack()); })
#elif defined(__CRT_HAVE_snprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_LIBC_PRINTF(3, 4) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T __NOTHROW_NCX(__VLIBCCALL __localdep_snprintf)(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, ...) __CASMNAME("snprintf");
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/snprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_snprintf __LIBC_LOCAL_NAME(snprintf)
#endif /* !... */
#endif /* !__local___localdep_snprintf_defined */
#ifndef __local___localdep_strerror_defined
#define __local___localdep_strerror_defined
#ifdef __CRT_HAVE_strerror
__CREDIRECT(__ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_strerror,(__errno_t __errnum),strerror,(__errnum))
#else /* __CRT_HAVE_strerror */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerror.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerror __LIBC_LOCAL_NAME(strerror)
#endif /* !__CRT_HAVE_strerror */
#endif /* !__local___localdep_strerror_defined */
#ifndef __local___localdep_strerrordesc_np_defined
#define __local___localdep_strerrordesc_np_defined
#ifdef __CRT_HAVE_strerrordesc_np
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,char const *,__NOTHROW,__localdep_strerrordesc_np,(__errno_t __errnum),strerrordesc_np,(__errnum))
#else /* __CRT_HAVE_strerrordesc_np */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strerrordesc_np.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strerrordesc_np __LIBC_LOCAL_NAME(strerrordesc_np)
#endif /* !__CRT_HAVE_strerrordesc_np */
#endif /* !__local___localdep_strerrordesc_np_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
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
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerror_r) __ATTR_COLD __ATTR_RETNONNULL __ATTR_NONNULL((2)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strerror_r))(__errno_t __errnum, char *__buf, __SIZE_TYPE__ __buflen) {
	char const *__string;
	if (!__buf)
		goto __fallback;
	if (!__buflen)
		goto __fallback;
	__string = (__NAMESPACE_LOCAL_SYM __localdep_strerrordesc_np)(__errnum);
	if (__string) {
		/* Copy the descriptor text. */
		__SIZE_TYPE__ __msg_len = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__string) + 1;
		if (__msg_len > __buflen)
			goto __fallback;
		(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__buf, __string, __msg_len, sizeof(char));
	} else {
		if ((__SIZE_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_snprintf)(__buf, __buflen, "Unknown error %d", __errnum) >= __buflen)
			goto __fallback;
	}
	return __buf;
__fallback:
	return (__NAMESPACE_LOCAL_SYM __localdep_strerror)(__errnum);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strerror_r_defined
#define __local___localdep_strerror_r_defined
#define __localdep_strerror_r __LIBC_LOCAL_NAME(strerror_r)
#endif /* !__local___localdep_strerror_r_defined */
#endif /* !__local_strerror_r_defined */
