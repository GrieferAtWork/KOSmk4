/* HASH CRC-32:0xb74e94cd */
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
#ifndef __local_pthread_once_defined
#define __local_pthread_once_defined 1
#include <__crt.h>
#include <kos/anno.h>
#ifndef ____pthread_once_routine_t_defined
#define ____pthread_once_routine_t_defined 1
typedef void (__LIBKCALL *__pthread_once_routine_t)(void);
#endif /* !____pthread_once_routine_t_defined */
#include <bits/crt/pthreadtypes.h>
#include <bits/types.h>
#include <asm/crt/pthreadvalues.h>
#include <hybrid/__atomic.h>
#include <hybrid/sched/__yield.h>
__NAMESPACE_LOCAL_BEGIN
/* Guarantee that the initialization function INIT_ROUTINE will be called
 * only once, even if pthread_once is executed several times with the
 * same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
 * extern variable initialized to PTHREAD_ONCE_INIT.
 * @return: EOK: Success */
__LOCAL_LIBC(pthread_once) __ATTR_NONNULL((1, 2)) __errno_t
(__LIBCCALL __LIBC_LOCAL_NAME(pthread_once))(__pthread_once_t *__once_control, __pthread_once_routine_t __init_routine) __THROWS(...) {
	__pthread_once_t __status;
	__status = __hybrid_atomic_cmpxch_val(*__once_control,
	                                    __PTHREAD_ONCE_INIT,
	                                    __PTHREAD_ONCE_INIT + 1,
	                                    __ATOMIC_SEQ_CST,
	                                    __ATOMIC_SEQ_CST);
	if (__status == __PTHREAD_ONCE_INIT) {
		(*__init_routine)();
		__hybrid_atomic_store(*__once_control,
		                      __PTHREAD_ONCE_INIT + 2,
		                      __ATOMIC_RELEASE);
	} else if (__status != __PTHREAD_ONCE_INIT + 2) {
		/* Wait for some other thread to finish init_routine() */
		do {
			__hybrid_yield();
		} while (__hybrid_atomic_load(*__once_control, __ATOMIC_ACQUIRE) !=
		         __PTHREAD_ONCE_INIT + 2);
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pthread_once_defined
#define __local___localdep_pthread_once_defined 1
#define __localdep_pthread_once __LIBC_LOCAL_NAME(pthread_once)
#endif /* !__local___localdep_pthread_once_defined */
#endif /* !__local_pthread_once_defined */
