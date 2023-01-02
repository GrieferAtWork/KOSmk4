/* HASH CRC-32:0xdeb696ce */
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
#ifndef __local_insque_defined
#define __local_insque_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(insque) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(insque))(void *__restrict __elem, void *__prev) {
	struct __queue_link {
		struct __queue_link *__l_forw; /* [0..1] Forward link */
		struct __queue_link *__l_back; /* [0..1] Backward link */
	};
	if (__prev) {
		struct __queue_link *__next;
		__next = ((struct __queue_link *)__prev)->__l_forw;
		((struct __queue_link *)__elem)->__l_back = (struct __queue_link *)__prev;
		((struct __queue_link *)__elem)->__l_forw = __next;
		((struct __queue_link *)__prev)->__l_forw = (struct __queue_link *)__elem;
		if (__next)
			__next->__l_back = (struct __queue_link *)__elem;
	} else {
		((struct __queue_link *)__elem)->__l_back = __NULLPTR;
		((struct __queue_link *)__elem)->__l_forw = __NULLPTR;
	}
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_insque_defined
#define __local___localdep_insque_defined
#define __localdep_insque __LIBC_LOCAL_NAME(insque)
#endif /* !__local___localdep_insque_defined */
#endif /* !__local_insque_defined */
