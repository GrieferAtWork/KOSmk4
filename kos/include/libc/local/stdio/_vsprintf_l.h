/* HASH CRC-32:0xf592e097 */
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
#ifndef __local__vsprintf_l_defined
#define __local__vsprintf_l_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_vsprintf_defined
#define __local___localdep_vsprintf_defined
#if __has_builtin(__builtin_vsprintf) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_vsprintf)
__CEIREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),vsprintf,{ return __builtin_vsprintf(__dest, __format, __args); })
#elif defined(__CRT_HAVE_vsprintf)
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),vsprintf,(__dest,__format,__args))
#elif defined(__CRT_HAVE__IO_vsprintf)
__CREDIRECT(__ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 0),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_vsprintf,(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args),_IO_vsprintf,(__dest,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/vsprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_vsprintf __LIBC_LOCAL_NAME(vsprintf)
#endif /* !... */
#endif /* !__local___localdep_vsprintf_defined */
__LOCAL_LIBC(_vsprintf_l) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsprintf_l))(char *__buf, char const *__format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return (__NAMESPACE_LOCAL_SYM __localdep_vsprintf)(__buf, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vsprintf_l_defined
#define __local___localdep__vsprintf_l_defined
#define __localdep__vsprintf_l __LIBC_LOCAL_NAME(_vsprintf_l)
#endif /* !__local___localdep__vsprintf_l_defined */
#endif /* !__local__vsprintf_l_defined */
