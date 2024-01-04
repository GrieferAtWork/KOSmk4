/* HASH CRC-32:0x55ca400 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_dyn_string_eq_defined
#define __local_dyn_string_eq_defined
#include <__crt.h>
#include <features.h>
#include <bits/crt/dyn-string.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bcmpc_defined
#define __local___localdep_bcmpc_defined
#ifdef __CRT_HAVE_bcmpc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmpc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bcmpc __LIBC_LOCAL_NAME(memcmpc)
#endif /* !... */
#endif /* !__local___localdep_bcmpc_defined */
__LOCAL_LIBC(dyn_string_eq) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dyn_string_eq))(struct dyn_string __KOS_FIXED_CONST *__lhs, struct dyn_string __KOS_FIXED_CONST *__rhs) {
	if (__lhs->length != __rhs->length)
		return 0;
	return (__NAMESPACE_LOCAL_SYM __localdep_bcmpc)(__lhs->s, __rhs->s, __lhs->length, sizeof(char)) == 0 ? 1 : 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dyn_string_eq_defined
#define __local___localdep_dyn_string_eq_defined
#define __localdep_dyn_string_eq __LIBC_LOCAL_NAME(dyn_string_eq)
#endif /* !__local___localdep_dyn_string_eq_defined */
#endif /* !__local_dyn_string_eq_defined */
