/* HASH CRC-32:0xa706b9af */
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
#ifndef __local__lfind_s_defined
#define __local__lfind_s_defined
#include <__crt.h>
#include <kos/anno.h>
#include <hybrid/typecore.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_lfind_s) __ATTR_WUNUSED __ATTR_IN(3) __ATTR_IN_OPT(1) __ATTR_IN_OPT(2) __ATTR_NONNULL((5)) void *
(__LIBCCALL __LIBC_LOCAL_NAME(_lfind_s))(void const *__key, void const *__pbase, __SIZE_TYPE__ __KOS_FIXED_CONST *__pitem_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void *__arg, void const *__a, void const *__b), void *__arg) __THROWS(...) {
	__SIZE_TYPE__ __i, __count = *__pitem_count;
	void const *__result = __pbase;
	for (__i = 0; __i < __count; ++__i) {
		if ((*__compar)(__arg, __key, __result) == 0)
			return (void *)__result;
		__result = (__BYTE_TYPE__ *)__result + __item_size;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__lfind_s_defined
#define __local___localdep__lfind_s_defined
#define __localdep__lfind_s __LIBC_LOCAL_NAME(_lfind_s)
#endif /* !__local___localdep__lfind_s_defined */
#endif /* !__local__lfind_s_defined */
