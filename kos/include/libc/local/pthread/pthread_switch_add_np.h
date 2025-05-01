/* HASH CRC-32:0x8477ece3 */
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
#ifndef __local_pthread_switch_add_np_defined
#define __local_pthread_switch_add_np_defined
#include <__crt.h>
#include <bits/types.h>
#include <libc/errno.h>
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pthread_switch_add_np) __ATTR_WUNUSED __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_switch_add_np))(__pthread_switch_routine_t __routine) {
	/* This right here also matches what FreeBSD current does (that is: returning "ENOTSUP") */
	__COMPILER_IMPURE();
	(void)__routine;
#ifdef __ENOTSUP
	return __ENOTSUP;
#elif defined(__EOPNOTSUPP)
	return __EOPNOTSUPP;
#else /* ... */
	return 1;
#endif /* !... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_switch_add_np_defined
#define __local___localdep_pthread_switch_add_np_defined
#define __localdep_pthread_switch_add_np __LIBC_LOCAL_NAME(pthread_switch_add_np)
#endif /* !__local___localdep_pthread_switch_add_np_defined */
#endif /* !__local_pthread_switch_add_np_defined */
