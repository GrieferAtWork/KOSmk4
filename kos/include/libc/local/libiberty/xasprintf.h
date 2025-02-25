/* HASH CRC-32:0xee0d1266 */
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
#ifndef __local_xasprintf_defined
#define __local_xasprintf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_xvasprintf) || ((defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))) && defined(__CRT_HAVE_xmalloc_failed))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_xvasprintf_defined
#define __local___localdep_xvasprintf_defined
#ifdef __CRT_HAVE_xvasprintf
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0),char *,__NOTHROW_NCX,__localdep_xvasprintf,(char const *__format, __builtin_va_list __args),xvasprintf,(__format,__args))
#elif (defined(__CRT_HAVE_vstrdupf) || defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))) && defined(__CRT_HAVE_xmalloc_failed)
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/xvasprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_xvasprintf __LIBC_LOCAL_NAME(xvasprintf)
#else /* ... */
#undef __local___localdep_xvasprintf_defined
#endif /* !... */
#endif /* !__local___localdep_xvasprintf_defined */
__LOCAL_LIBC(xasprintf) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 2) char *
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(xasprintf))(char const *__restrict __format, ...) {
	char *__result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_xvasprintf)(__format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_xasprintf_defined
#define __local___localdep_xasprintf_defined
#define __localdep_xasprintf __LIBC_LOCAL_NAME(xasprintf)
#endif /* !__local___localdep_xasprintf_defined */
#else /* __CRT_HAVE_xvasprintf || ((__CRT_HAVE_vstrdupf || __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free))) && __CRT_HAVE_xmalloc_failed) */
#undef __local_xasprintf_defined
#endif /* !__CRT_HAVE_xvasprintf && ((!__CRT_HAVE_vstrdupf && !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free))) || !__CRT_HAVE_xmalloc_failed) */
#endif /* !__local_xasprintf_defined */
