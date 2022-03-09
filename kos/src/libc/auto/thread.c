/* HASH CRC-32:0xd5b92fbb */
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
#ifndef GUARD_LIBC_AUTO_THREAD_C
#define GUARD_LIBC_AUTO_THREAD_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "thread.h"
#include "../user/pthread.h"
#include "pthread_np.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/crt/pthreadvalues.h>
#include <libc/errno.h>
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((3)) errno_t
NOTHROW_NCX(LIBCCALL libc_thr_create)(void *stack_base,
                                      size_t stack_size,
                                      void *(LIBCCALL *start_routine)(void *arg),
                                      void *arg,
                                      long flags,
                                      thread_t *newthread) {
	errno_t result;
	if (flags || stack_base || stack_size) {







		pthread_attr_t attr;
		if (flags & ~(0 |
#ifdef __PTHREAD_SCOPE_SYSTEM
		              0x00000001 |
#endif /* __PTHREAD_SCOPE_SYSTEM */
#ifdef __PTHREAD_CREATE_DETACHED
		              0x00000040 |
#endif /* __PTHREAD_CREATE_DETACHED */
		              0)







		    )
		{
#ifdef ENOSYS
			return ENOSYS;
#else /* ENOSYS */
			return 1;
#endif /* !ENOSYS */
		}
		result = libc_pthread_attr_init(&attr);
		if unlikely(result != 0)
			return result;
#ifdef __PTHREAD_SCOPE_SYSTEM
		if (flags & 0x00000001) {
			result = libc_pthread_attr_setscope(&attr, __PTHREAD_SCOPE_SYSTEM);
			if unlikely(result != 0)
				goto done_attr;
		}
#endif /* __PTHREAD_SCOPE_SYSTEM */
#ifdef __PTHREAD_CREATE_DETACHED
		if (flags & 0x00000040) {
			result = libc_pthread_attr_setdetachstate(&attr, __PTHREAD_CREATE_DETACHED);
			if unlikely(result != 0)
				goto done_attr;
		}
#endif /* __PTHREAD_CREATE_DETACHED */

		if (stack_base) {
			result = libc_pthread_attr_setstack(&attr, stack_base, stack_size);
			if unlikely(result != 0)
				goto done_attr;
		} else


		if (stack_size) {
			result = libc_pthread_attr_setstacksize(&attr, stack_size);
			if unlikely(result != 0)
				goto done_attr;
		} else

		{
		}

		/* Actually create the new thread. */
		result = libc_pthread_create(newthread, &attr, start_routine, arg);
		goto done_attr; /* Suppress warnings if not otherwise used. */
done_attr:;

		libc_pthread_attr_destroy(&attr);


	} else {
		/* Create new thread with default attributes. */
		result = libc_pthread_create(newthread, NULL, start_routine, arg);
	}
	return result;
}
INTERN ATTR_SECTION(".text.crt.sched.threads") errno_t
NOTHROW_RPC(LIBCCALL libc_thr_join)(thread_t thr,
                                    thread_t *p_departed,
                                    void **thread_return) {
	errno_t result;
	result = libc_pthread_join(thr, thread_return);
	if (result == 0)
		*p_departed = thr;
	return result;
}
#include <bits/os/sched.h>
INTERN ATTR_SECTION(".text.crt.sched.threads") errno_t
NOTHROW_NCX(LIBCCALL libc_thr_setprio)(thread_t thr,
                                       int priority) {
	errno_t result;
	struct sched_param param;
	int policy;
	result = libc_pthread_getschedparam(thr, &policy, &param);
	if (result == 0 && param.sched_priority != priority) {
		param.sched_priority = priority;
		result = libc_pthread_setschedparam(thr, policy, &param);
	}
	return result;
}
#include <bits/os/sched.h>
INTERN ATTR_SECTION(".text.crt.sched.threads") NONNULL((2)) errno_t
NOTHROW_NCX(LIBCCALL libc_thr_getprio)(thread_t thr,
                                       int *p_priority) {
	errno_t result;
	struct sched_param param;
	int policy;
	result = libc_pthread_getschedparam(thr, &policy, &param);
	if (result == 0)
		*p_priority = param.sched_priority;
	return result;
}
INTERN ATTR_SECTION(".text.crt.sched.threads") errno_t
NOTHROW_NCX(LIBCCALL libc_thr_getspecific)(thread_key_t key,
                                           void **p_val) {
	void *val;
	*p_val = val = libc_pthread_getspecific(key);
	if (val != NULL)
		return 0;
	return libc_pthread_setspecific(key, NULL);
}
/* >> thr_stksegment(3)
 * Wrapper for `pthread_stackseg_np(pthread_self(), sinfo)' */
INTERN ATTR_SECTION(".text.crt.sched.threads") errno_t
NOTHROW_NCX(LIBCCALL libc_thr_stksegment)(stack_t *sinfo) {
	return libc_pthread_stackseg_np(libc_pthread_self(), sinfo);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(thr_create, libc_thr_create);
DEFINE_PUBLIC_ALIAS(thr_join, libc_thr_join);
DEFINE_PUBLIC_ALIAS(thr_setprio, libc_thr_setprio);
DEFINE_PUBLIC_ALIAS(thr_getprio, libc_thr_getprio);
DEFINE_PUBLIC_ALIAS(thr_getspecific, libc_thr_getspecific);
DEFINE_PUBLIC_ALIAS(thr_stksegment, libc_thr_stksegment);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_THREAD_C */
