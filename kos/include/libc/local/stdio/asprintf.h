/* HASH CRC-32:0x5f20b77 */
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
#ifndef __local_asprintf_defined
#define __local_asprintf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_vasprintf) || ((defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: vasprintf from stdio */
#ifndef __local___localdep_vasprintf_defined
#define __local___localdep_vasprintf_defined 1
#ifdef __CRT_HAVE_vasprintf
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__CREDIRECT(__ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vasprintf,(char **__restrict __pstr, char const *__restrict __format, __builtin_va_list __args),vasprintf,(__pstr,__format,__args))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc)) && (defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vasprintf.h>
__NAMESPACE_LOCAL_BEGIN
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
#define __localdep_vasprintf __LIBC_LOCAL_NAME(vasprintf)
#else /* ... */
#undef __local___localdep_vasprintf_defined
#endif /* !... */
#endif /* !__local___localdep_vasprintf_defined */
/* Print the given `FORMAT' into a newly allocated, heap-allocated string which is then stored in `*PSTR' */
__LOCAL_LIBC(asprintf) __ATTR_LIBC_PRINTF(2, 3) __ATTR_NONNULL((1, 2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(asprintf))(char **__restrict __pstr, char const *__restrict __format, ...) {
	__STDC_INT_AS_SSIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep_vasprintf(__pstr, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_asprintf_defined
#define __local___localdep_asprintf_defined 1
#define __localdep_asprintf __LIBC_LOCAL_NAME(asprintf)
#endif /* !__local___localdep_asprintf_defined */
#else /* __CRT_HAVE_vasprintf || ((__CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc) && (__CRT_HAVE_free || __CRT_HAVE_cfree)) */
#undef __local_asprintf_defined
#endif /* !__CRT_HAVE_vasprintf && ((!__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc) || (!__CRT_HAVE_free && !__CRT_HAVE_cfree)) */
#endif /* !__local_asprintf_defined */
