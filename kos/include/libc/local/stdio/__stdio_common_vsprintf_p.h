/* HASH CRC-32:0xbcb6d07c */
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
#ifndef __local___stdio_common_vsprintf_p_defined
#define __local___stdio_common_vsprintf_p_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vsnprintf_defined
#define __local___localdep_vsnprintf_defined
#if __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
__CEIREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vsnprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsnprintf __LIBC_LOCAL_NAME(vsnprintf)
#endif /* !... */
#endif /* !__local___localdep_vsnprintf_defined */
__LOCAL_LIBC(__stdio_common_vsprintf_p) __ATTR_IN(4) __ATTR_LIBC_PRINTF_P(4, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__stdio_common_vsprintf_p))(__UINT64_TYPE__ __options, char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args) {
	__STDC_INT_AS_SSIZE_T __result;
	(void)__locale;
	/* NOTE: DOS positional arguments work the same as Glibc's, only that
	 *       Glibc and KOS  already bake them  into the normal  `printf'. */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vsnprintf)(__buf, __bufsize, __format, __args);
	if (!(__options & 2) && (__SIZE_TYPE__)__result > __bufsize)
		__result = __bufsize;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___stdio_common_vsprintf_p_defined
#define __local___localdep___stdio_common_vsprintf_p_defined
#define __localdep___stdio_common_vsprintf_p __LIBC_LOCAL_NAME(__stdio_common_vsprintf_p)
#endif /* !__local___localdep___stdio_common_vsprintf_p_defined */
#endif /* !__local___stdio_common_vsprintf_p_defined */
