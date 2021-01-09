/* HASH CRC-32:0x89404a01 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__vsnscanf_l_defined
#define __local__vsnscanf_l_defined 1
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _vsnscanf from stdio */
#ifndef __local___localdep__vsnscanf_defined
#define __local___localdep__vsnscanf_defined 1
#ifdef __CRT_HAVE__vsnscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnscanf,(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __builtin_va_list __args),_vsnscanf,(__input,__inputlen,__format,__args))
#elif defined(__CRT_HAVE__vsnscanf_s)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnscanf,(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __builtin_va_list __args),_vsnscanf_s,(__input,__inputlen,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/_vsnscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsnscanf __LIBC_LOCAL_NAME(_vsnscanf)
#endif /* !... */
#endif /* !__local___localdep__vsnscanf_defined */
__LOCAL_LIBC(_vsnscanf_l) __ATTR_LIBC_SCANF(3, 5) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_vsnscanf_l))(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __locale_t __locale, __builtin_va_list __args) {
	(void)__locale;
	return __localdep__vsnscanf(__input, __inputlen, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__vsnscanf_l_defined
#define __local___localdep__vsnscanf_l_defined 1
#define __localdep__vsnscanf_l __LIBC_LOCAL_NAME(_vsnscanf_l)
#endif /* !__local___localdep__vsnscanf_l_defined */
#endif /* !__local__vsnscanf_l_defined */
