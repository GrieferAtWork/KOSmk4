/* HASH CRC-32:0xae118b3e */
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
#ifndef __local_xvasprintf_defined
#define __local_xvasprintf_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))) && defined(__CRT_HAVE_xmalloc_failed)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vsnprintf_defined
#define __local___localdep_vsnprintf_defined
#if __has_builtin(__builtin_vsnprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsnprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,{ return __builtin_vsnprintf(__buf, __buflen, __format, __args); })
#elif defined(__CRT_HAVE_vsnprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),vsnprintf,(__buf,__buflen,__format,__args))
#elif defined(__CRT_HAVE___vsnprintf)
__NAMESPACE_LOCAL_END
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep_vsnprintf,(char *__restrict __buf, __SIZE_TYPE__ __buflen, char const *__restrict __format, __builtin_va_list __args),__vsnprintf,(__buf,__buflen,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vsnprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsnprintf __LIBC_LOCAL_NAME(vsnprintf)
#endif /* !... */
#endif /* !__local___localdep_vsnprintf_defined */
#ifndef __local___localdep_vstrdupf_defined
#define __local___localdep_vstrdupf_defined
#ifdef __CRT_HAVE_vstrdupf
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),char *,__NOTHROW_NCX,__localdep_vstrdupf,(char const *__restrict __format, __builtin_va_list __args),vstrdupf,(__format,__args))
#elif defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
__NAMESPACE_LOCAL_END
#include <libc/local/string/vstrdupf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vstrdupf __LIBC_LOCAL_NAME(vstrdupf)
#else /* ... */
#undef __local___localdep_vstrdupf_defined
#endif /* !... */
#endif /* !__local___localdep_vstrdupf_defined */
#ifndef __local___localdep_xmalloc_failed_defined
#define __local___localdep_xmalloc_failed_defined
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_NORETURN,__THROWING,__localdep_xmalloc_failed,(__SIZE_TYPE__ __num_bytes),xmalloc_failed,(__num_bytes))
#endif /* !__local___localdep_xmalloc_failed_defined */
__LOCAL_LIBC(xvasprintf) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(xvasprintf))(char const *__format, __builtin_va_list __args) {
	__builtin_va_list __args2;
	char *__result;
	__builtin_va_copy(__args2, __args);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_vstrdupf)(__format, __args2);
	__builtin_va_end(__args2);
	if (__result == __NULLPTR)
		(__NAMESPACE_LOCAL_SYM __localdep_xmalloc_failed)(((__NAMESPACE_LOCAL_SYM __localdep_vsnprintf)(__NULLPTR, 0, __format, __args) + 1) * sizeof(char));
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_xvasprintf_defined
#define __local___localdep_xvasprintf_defined
#define __localdep_xvasprintf __LIBC_LOCAL_NAME(xvasprintf)
#endif /* !__local___localdep_xvasprintf_defined */
#else /* (__CRT_HAVE_vstrdupf || __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free))) && __CRT_HAVE_xmalloc_failed */
#undef __local_xvasprintf_defined
#endif /* (!__CRT_HAVE_vstrdupf && !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free))) || !__CRT_HAVE_xmalloc_failed */
#endif /* !__local_xvasprintf_defined */
