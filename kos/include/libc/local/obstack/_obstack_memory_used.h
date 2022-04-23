/* HASH CRC-32:0xb2fee632 */
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
#ifndef __local__obstack_memory_used_defined
#define __local__obstack_memory_used_defined
#include <__crt.h>
#include <features.h>
#include <bits/crt/obstack.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_obstack_memory_used) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_obstack_memory_used))(struct obstack __KOS_FIXED_CONST *__self) {
	__SIZE_TYPE__ __result = 0;
	struct _obstack_chunk *__iter;
	for (__iter = __self->chunk; __iter; __iter = __iter->prev)
		__result += (__SIZE_TYPE__)(__iter->limit - (char *)__iter);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__obstack_memory_used_defined
#define __local___localdep__obstack_memory_used_defined
#define __localdep__obstack_memory_used __LIBC_LOCAL_NAME(_obstack_memory_used)
#endif /* !__local___localdep__obstack_memory_used_defined */
#endif /* !__local__obstack_memory_used_defined */
