/* HASH CRC-32:0x126f8ec1 */
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
#ifndef __local_lfind_defined
#define __local_lfind_defined 1
#include <__crt.h>
#ifndef ____compar_fn_t_defined
#define ____compar_fn_t_defined 1
typedef int (__LIBCCALL *__compar_fn_t)(void const *__a, void const *__b);
#endif /* !____compar_fn_t_defined */
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Perform linear search for KEY by comparing by COMPAR in an array [BASE, BASE+NMEMB*SIZE) */
__LOCAL_LIBC(lfind) __ATTR_NONNULL((2, 3, 5)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(lfind))(void const *__key, void const *__base, __SIZE_TYPE__ __KOS_FIXED_CONST *__nmemb, __SIZE_TYPE__ __size, __compar_fn_t __compar) {
	__SIZE_TYPE__ __i, __count = *__nmemb;
	void const *__result = __base;
	for (__i = 0; __i < __count; ++__i) {
		if ((*__compar)(__key, __result) == 0)
			return (void *)__result;
		__result = (__BYTE_TYPE__ *)__result + __size;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lfind_defined
#define __local___localdep_lfind_defined 1
#define __localdep_lfind __LIBC_LOCAL_NAME(lfind)
#endif /* !__local___localdep_lfind_defined */
#endif /* !__local_lfind_defined */
