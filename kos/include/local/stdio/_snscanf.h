/* HASH 0xdf3f5a42 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__snscanf_defined
#if 1
#define __local__snscanf_defined 1
/* Dependency: "_vsnscanf" from "stdio" */
#ifndef ____localdep__vsnscanf_defined
#define ____localdep__vsnscanf_defined 1
#if defined(__CRT_HAVE__vsnscanf)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnscanf,(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __builtin_va_list __args),_vsnscanf,(__input,__inputlen,__format,__args))
#elif defined(__CRT_HAVE__vsnscanf_s)
__CREDIRECT(__ATTR_WUNUSED __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)),__STDC_INT_AS_SIZE_T,__NOTHROW_NCX,__localdep__vsnscanf,(char const *__restrict __input, __SIZE_TYPE__ __inputlen, char const *__restrict __format, __builtin_va_list __args),_vsnscanf_s,(__input,__inputlen,__format,__args))
#else /* LIBC: _vsnscanf */
#include <local/stdio/_vsnscanf.h>
#define __localdep__vsnscanf (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_vsnscanf))
#endif /* _vsnscanf... */
#endif /* !____localdep__vsnscanf_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_snscanf) __ATTR_LIBC_SCANF(3, 4) __ATTR_NONNULL((1, 3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(_snscanf))(char const *__restrict __input,
                                                       __SIZE_TYPE__ __inputlen,
                                                       char const *__restrict __format,
                                                       ...) {
#line 1906 "kos/src/libc/magic/stdio.c"
	__STDC_INT_AS_SIZE_T __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = __localdep__vsnscanf(__input, __inputlen, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* 1 */
#endif /* !__local__snscanf_defined */
