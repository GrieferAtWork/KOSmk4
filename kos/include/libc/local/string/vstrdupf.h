/* HASH CRC-32:0x9389c5fc */
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
#ifndef __local_vstrdupf_defined
#define __local_vstrdupf_defined
#include <__crt.h>
#if defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vasprintf_defined
#define __local___localdep_vasprintf_defined
#ifdef __CRT_HAVE_vasprintf
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 0) __ATTR_OUT(1),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vasprintf,(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args),vasprintf,(__pstr,__format,__args))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vasprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vasprintf __LIBC_LOCAL_NAME(vasprintf)
#else /* ... */
#undef __local___localdep_vasprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vasprintf_defined */
__LOCAL_LIBC(vstrdupf) __ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1) __ATTR_LIBC_PRINTF(1, 0) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vstrdupf))(char const *__restrict __format, __builtin_va_list __args) {
	char *__result;
	return (__NAMESPACE_LOCAL_SYM __localdep_vasprintf)(&__result, __format, __args) >= 0 ? __result : 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vstrdupf_defined
#define __local___localdep_vstrdupf_defined
#define __localdep_vstrdupf __LIBC_LOCAL_NAME(vstrdupf)
#endif /* !__local___localdep_vstrdupf_defined */
#else /* __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free)) */
#undef __local_vstrdupf_defined
#endif /* !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree && !__CRT_HAVE___libc_free)) */
#endif /* !__local_vstrdupf_defined */
