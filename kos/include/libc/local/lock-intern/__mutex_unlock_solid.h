/* HASH CRC-32:0x9617dc54 */
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
#ifndef __local___mutex_unlock_solid_defined
#define __local___mutex_unlock_solid_defined
#include <__crt.h>
#include <kos/sched/shared-lock.h>
#if defined(__shared_lock_tryacquire) && defined(__shared_lock_release)
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__mutex_unlock_solid) __ATTR_INOUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__mutex_unlock_solid))(void *__lock) {
	if (__shared_lock_tryacquire((struct shared_lock *)__lock))
		__shared_lock_release((struct shared_lock *)__lock);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___mutex_unlock_solid_defined
#define __local___localdep___mutex_unlock_solid_defined
#define __localdep___mutex_unlock_solid __LIBC_LOCAL_NAME(__mutex_unlock_solid)
#endif /* !__local___localdep___mutex_unlock_solid_defined */
#else /* __shared_lock_tryacquire && __shared_lock_release */
#undef __local___mutex_unlock_solid_defined
#endif /* !__shared_lock_tryacquire || !__shared_lock_release */
#endif /* !__local___mutex_unlock_solid_defined */
