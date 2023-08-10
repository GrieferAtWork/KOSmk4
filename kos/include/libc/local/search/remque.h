/* HASH CRC-32:0x64f9f44d */
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
#ifndef __local_remque_defined
#define __local_remque_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(remque) __ATTR_INOUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(remque))(void *__restrict __elem) {
	struct __queue_link {
		struct __queue_link *__l_forw; /* [0..1] Forward link */
		struct __queue_link *__l_back; /* [0..1] Backward link */
	};
	struct __queue_link *__prev, *__next;
	__prev = ((struct __queue_link *)__elem)->__l_back;
	__next = ((struct __queue_link *)__elem)->__l_forw;
	if (__prev)
		__prev->__l_forw = __next;
	if (__next)
		__next->__l_back = __prev;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_remque_defined
#define __local___localdep_remque_defined
#define __localdep_remque __LIBC_LOCAL_NAME(remque)
#endif /* !__local___localdep_remque_defined */
#endif /* !__local_remque_defined */
