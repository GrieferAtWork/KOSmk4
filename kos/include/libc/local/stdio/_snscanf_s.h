/* HASH CRC-32:0x2d961d65 */
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
#ifndef __local__snscanf_s_defined
#define __local__snscanf_s_defined 1
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__vsnscanf_s_defined
#define __local___localdep__vsnscanf_s_defined 1
#ifdef __CRT_HAVE__vsnscanf
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnscanf_s,(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __builtin_va_list __args),_vsnscanf,(__input,__inputlen,__format,__args))
#elif defined(__CRT_HAVE__vsnscanf_s)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnscanf_s,(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __builtin_va_list __args),_vsnscanf_s,(__input,__inputlen,__format,__args))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/_vsnscanf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__vsnscanf_s __LIBC_LOCAL_NAME(_vsnscanf)
#endif /* !... */
#endif /* !__local___localdep__vsnscanf_s_defined */
__LOCAL_LIBC(_snscanf_s) __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_snscanf_s))(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, ...) {
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vsnscanf_s(__input, __inputlen, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__snscanf_s_defined
#define __local___localdep__snscanf_s_defined 1
#define __localdep__snscanf_s __LIBC_LOCAL_NAME(_snscanf_s)
#endif /* !__local___localdep__snscanf_s_defined */
#endif /* !__local__snscanf_s_defined */
