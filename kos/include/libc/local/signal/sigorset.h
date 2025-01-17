/* HASH CRC-32:0xe093d39c */
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
#ifndef __local_sigorset_defined
#define __local_sigorset_defined
#include <__crt.h>
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigorset) __ATTR_IN(2) __ATTR_IN(3) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigorset))(struct __sigset_struct *__set, struct __sigset_struct const *__left, struct __sigset_struct const *__right) {
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < __COMPILER_LENOF(__set->__val); ++__i)
		__set->__val[__i] = __left->__val[__i] | __right->__val[__i];
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigorset_defined
#define __local___localdep_sigorset_defined
#define __localdep_sigorset __LIBC_LOCAL_NAME(sigorset)
#endif /* !__local___localdep_sigorset_defined */
#endif /* !__local_sigorset_defined */
