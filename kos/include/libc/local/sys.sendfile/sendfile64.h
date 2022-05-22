/* HASH CRC-32:0xe00d287a */
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
#ifndef __local_sendfile64_defined
#define __local_sendfile64_defined
#include <__crt.h>
#ifdef __CRT_HAVE_sendfile
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sendfile32_defined
#define __local___localdep_sendfile32_defined
__CREDIRECT(__ATTR_INOUT_OPT(3),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_sendfile32,(__fd_t __out_fd, __fd_t __in_fd, __off32_t *__offset, __SIZE_TYPE__ __count),sendfile,(__out_fd,__in_fd,__offset,__count))
#endif /* !__local___localdep_sendfile32_defined */
__LOCAL_LIBC(sendfile64) __ATTR_INOUT_OPT(3) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sendfile64))(__fd_t __out_fd, __fd_t __in_fd, __off64_t *__offset, __SIZE_TYPE__ __count) {
	__SSIZE_TYPE__ __result;
	if (__offset) {
		__off32_t __temp = (__off32_t)*__offset;
		__result = (__NAMESPACE_LOCAL_SYM __localdep_sendfile32)(__out_fd, __in_fd, &__temp, __count);
		*__offset = (__off64_t)__temp;
	} else {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_sendfile32)(__out_fd, __in_fd, __NULLPTR, __count);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sendfile64_defined
#define __local___localdep_sendfile64_defined
#define __localdep_sendfile64 __LIBC_LOCAL_NAME(sendfile64)
#endif /* !__local___localdep_sendfile64_defined */
#else /* __CRT_HAVE_sendfile */
#undef __local_sendfile64_defined
#endif /* !__CRT_HAVE_sendfile */
#endif /* !__local_sendfile64_defined */
