/* HASH CRC-32:0xaedf2e00 */
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
#ifndef __local_re_search_defined
#define __local_re_search_defined
#include <__crt.h>
#ifdef __CRT_HAVE_re_search_2
#include <features.h>
#include <bits/crt/regex.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_re_search_2_defined
#define __local___localdep_re_search_2_defined
__CREDIRECT(__ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_INS(4, 5) __ATTR_OUT_OPT(8),__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,__localdep_re_search_2,(struct re_pattern_buffer __KOS_FIXED_CONST *__self, char const *__string1, __STDC_INT_AS_SIZE_T __length1, char const *__string2, __STDC_INT_AS_SIZE_T __length2, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __range, struct __re_registers *__regs, __STDC_INT_AS_SIZE_T __stop),re_search_2,(__self,__string1,__length1,__string2,__length2,__start,__range,__regs,__stop))
#endif /* !__local___localdep_re_search_2_defined */
__LOCAL_LIBC(re_search) __ATTR_IN(1) __ATTR_INS(2, 3) __ATTR_OUT_OPT(6) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(re_search))(struct re_pattern_buffer __KOS_FIXED_CONST *__self, char const *__string, __STDC_INT_AS_SIZE_T __length, __STDC_INT_AS_SIZE_T __start, __STDC_INT_AS_SIZE_T __range, struct __re_registers *__regs) {
	return (__NAMESPACE_LOCAL_SYM __localdep_re_search_2)(__self, __string, __length, __NULLPTR, 0, __start, __range, __regs, __length);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_re_search_defined
#define __local___localdep_re_search_defined
#define __localdep_re_search __LIBC_LOCAL_NAME(re_search)
#endif /* !__local___localdep_re_search_defined */
#else /* __CRT_HAVE_re_search_2 */
#undef __local_re_search_defined
#endif /* !__CRT_HAVE_re_search_2 */
#endif /* !__local_re_search_defined */
