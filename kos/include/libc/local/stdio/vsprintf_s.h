/* HASH CRC-32:0xc0034b01 */
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
#ifndef __local_vsprintf_s_defined
#define __local_vsprintf_s_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vsprintf_s_l_defined
#define __local___localdep__vsprintf_s_l_defined
#ifdef __CRT_HAVE__vsprintf_s_l
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep__vsprintf_s_l,(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __locale_t __locale, __builtin_va_list __args),_vsprintf_s_l,(__buf,__bufsize,__format,__locale,__args))
#else /* __CRT_HAVE__vsprintf_s_l */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/_vsprintf_s_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsprintf_s_l __LIBC_LOCAL_NAME(_vsprintf_s_l)
#endif /* !__CRT_HAVE__vsprintf_s_l */
#endif /* !__local___localdep__vsprintf_s_l_defined */
__LOCAL_LIBC(vsprintf_s) __ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_OUTS(1, 2) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vsprintf_s))(char *__buf, __SIZE_TYPE__ __bufsize, char const *__format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep__vsprintf_s_l)(__buf, __bufsize, __format, __NULLPTR, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsprintf_s_defined
#define __local___localdep_vsprintf_s_defined
#define __localdep_vsprintf_s __LIBC_LOCAL_NAME(vsprintf_s)
#endif /* !__local___localdep_vsprintf_s_defined */
#endif /* !__local_vsprintf_s_defined */
