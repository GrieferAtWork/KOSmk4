/* HASH CRC-32:0x7e065987 */
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
#ifndef __local_pthread_spin_unlock_defined
#define __local_pthread_spin_unlock_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/crt/pthreadtypes.h>
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
/* >> pthread_spin_unlock(3)
 * Release spinlock LOCK
 * @return: EOK: Success */
__LOCAL_LIBC(pthread_spin_unlock) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pthread_spin_unlock))(__pthread_spinlock_t *__lock) {
	__hybrid_atomic_store(*__lock, 0, __ATOMIC_RELEASE);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_spin_unlock_defined
#define __local___localdep_pthread_spin_unlock_defined 1
#define __localdep_pthread_spin_unlock __LIBC_LOCAL_NAME(pthread_spin_unlock)
#endif /* !__local___localdep_pthread_spin_unlock_defined */
#endif /* !__local_pthread_spin_unlock_defined */
