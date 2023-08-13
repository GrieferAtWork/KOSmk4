/* HASH CRC-32:0x6f80c9c6 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strerror_defined
#define __local_strerror_defined
#include <__crt.h>
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
#ifndef __local___localdep_strncpy_defined
#define __local___localdep_strncpy_defined
#if __has_builtin(__builtin_strncpy) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strncpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,{ return __builtin_strncpy(__buf, __src, __buflen); })
#elif defined(__CRT_HAVE_strncpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_strncpy,(char *__restrict __buf, char const *__restrict __src, __SIZE_TYPE__ __buflen),strncpy,(__buf,__src,__buflen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strncpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strncpy __LIBC_LOCAL_NAME(strncpy)
#endif /* !... */
#endif /* !__local___localdep_strncpy_defined */
__NAMESPACE_LOCAL_END
#include <libc/template/itoa_digits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strerror) __ATTR_COLD __ATTR_RETNONNULL __ATTR_WUNUSED char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strerror))(__errno_t __errnum) {
	static char __strerror_buf[64] = {0};
	char *__result;
	char const *__string;
	__result = __strerror_buf;
	__string = (__NAMESPACE_LOCAL_SYM __localdep_strerrordesc_np)(__errnum);
	if (__string) {
		/* Copy the descriptor text. */
		__result[__COMPILER_LENOF(__strerror_buf) - 1] = '\0';
		(__NAMESPACE_LOCAL_SYM __localdep_strncpy)(__result, __string, __COMPILER_LENOF(__strerror_buf) - 1);
	} else {



		/* Can't use sprintf() because that would form a  dependency
		 * loop with format_vprintf() which uses strerror() in order
		 * to implement %m! */
		__errno_t __iter = __errnum;
		if (__iter < 0)
			__iter = -__iter;
		__result = __COMPILER_ENDOF(__strerror_buf);
		*--__result = '\0';
		do {
			*--__result = __LOCAL_itoa_decimal(__iter % 10);
		} while ((__iter /= 10) != 0);
		if (__errnum < 0)
			*--__result = '-';
		__result -= 14;
		(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__result, "Unknown error ", 14 * sizeof(char));

	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strerror_defined
#define __local___localdep_strerror_defined
#define __localdep_strerror __LIBC_LOCAL_NAME(strerror)
#endif /* !__local___localdep_strerror_defined */
#endif /* !__local_strerror_defined */
