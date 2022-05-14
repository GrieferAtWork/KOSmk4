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
%(c_prefix){
/* (#) Portability: OpenSolaris (/usr/src/head/thread.h) */
}

%[default:section(".text.crt{|.dos}.sched.threads")]

%[define_decl_include_implication("<bits/os/sigset.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/os/sigset.h>": ["struct __sigset_struct"])]
%[define_replacement(sigset_t = "struct __sigset_struct")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/crt/pthreadvalues.h>
)]%[insert:prefix(
#include <bits/crt/pthreadtypes.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __USE_SOLARIS
#include <bits/os/sigset.h>
#include <bits/os/sigstack.h>
#endif /* __USE_SOLARIS */

#if 1 /* ??? */
#include <sys/signal.h>
#include <sys/time.h>
/*#include <synch.h>*/ /* TODO: Solaris-style synchronization primitives */
#endif

#define THR_MIN_STACK thr_min_stack()

/* Flags for `thr_create(3)' */
#define THR_BOUND     0x00000001 /* s.a. PTHREAD_SCOPE_SYSTEM */
#define THR_NEW_LWP   0x00000002 /* ??? */
#define THR_DETACHED  0x00000040 /* s.a. PTHREAD_CREATE_DETACHED */
#define THR_SUSPENDED 0x00000080 /* TODO: pthread_attr_setcreatesuspend_np */
#define THR_DAEMON    0x00000100 /* ??? */

/* Static initializer for `thr_keycreate_once(3)' */
#ifdef __PTHREAD_ONCE_KEY_NP
#define THR_ONCE_KEY __PTHREAD_ONCE_KEY_NP
#else /* __PTHREAD_ONCE_KEY_NP */
#define THR_ONCE_KEY ((thread_key_t)-1)
#endif /* !__PTHREAD_ONCE_KEY_NP */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

typedef __pthread_t thread_t;
typedef __pthread_key_t thread_key_t;

}

%[define(THR_BOUND     = 0x00000001)] /* s.a. PTHREAD_SCOPE_SYSTEM */
%[define(THR_NEW_LWP   = 0x00000002)] /* ??? */
%[define(THR_DETACHED  = 0x00000040)] /* s.a. PTHREAD_CREATE_DETACHED */
%[define(THR_SUSPENDED = 0x00000080)] /* TODO: pthread_attr_setcreatesuspend_np */
%[define(THR_DAEMON    = 0x00000100)] /* ??? */


%[define_replacement(thread_key_t = __pthread_key_t)]
%[define_replacement(thread_t = __pthread_t)]

[[decl_include("<bits/crt/pthreadtypes.h>", "<bits/types.h>")]]
[[impl_include("<asm/crt/pthreadvalues.h>", "<libc/errno.h>")]]
[[requires($has_function(pthread_create))]]
$errno_t thr_create(void *stack_base, size_t stack_size,
                    [[nonnull]] void *(LIBCCALL *start_routine)(void *arg),
                    void *arg, long flags, thread_t *newthread) {
	errno_t result;
	if (flags || stack_base || stack_size) {
@@pp_if !$has_function(pthread_attr_init)@@
@@pp_ifdef ENOSYS@@
		return ENOSYS;
@@pp_else@@
		return 1;
@@pp_endif@@
@@pp_else@@
		pthread_attr_t attr;
		if (flags & ~(0 |
@@pp_if $has_function(pthread_attr_setscope) && defined(__PTHREAD_SCOPE_SYSTEM)@@
		              THR_BOUND |
@@pp_endif@@
@@pp_if $has_function(pthread_attr_setdetachstate) && defined(__PTHREAD_CREATE_DETACHED)@@
		              THR_DETACHED |
@@pp_endif@@
		              0)
@@pp_if !$has_function(pthread_attr_setstack) && !$has_function(pthread_attr_setstacksize)@@
		    || stack_base || stack_size
@@pp_elif !$has_function(pthread_attr_setstack)@@
		    || stack_base
@@pp_elif !$has_function(pthread_attr_setstacksize)@@
		    || (!stack_base && stack_size)
@@pp_endif@@
		    )
		{
@@pp_ifdef ENOSYS@@
			return ENOSYS;
@@pp_else@@
			return 1;
@@pp_endif@@
		}
		result = pthread_attr_init(&attr);
		if unlikely(result != 0)
			return result;
@@pp_if $has_function(pthread_attr_setscope) && defined(__PTHREAD_SCOPE_SYSTEM)@@
		if (flags & THR_BOUND) {
			result = pthread_attr_setscope(&attr, __PTHREAD_SCOPE_SYSTEM);
			if unlikely(result != 0)
				goto done_attr;
		}
@@pp_endif@@
@@pp_if $has_function(pthread_attr_setdetachstate) && defined(__PTHREAD_CREATE_DETACHED)@@
		if (flags & THR_DETACHED) {
			result = pthread_attr_setdetachstate(&attr, __PTHREAD_CREATE_DETACHED);
			if unlikely(result != 0)
				goto done_attr;
		}
@@pp_endif@@
@@pp_if $has_function(pthread_attr_setstack)@@
		if (stack_base) {
			result = pthread_attr_setstack(&attr, stack_base, stack_size);
			if unlikely(result != 0)
				goto done_attr;
		} else
@@pp_endif@@
@@pp_if $has_function(pthread_attr_setstacksize)@@
		if (stack_size) {
			result = pthread_attr_setstacksize(&attr, stack_size);
			if unlikely(result != 0)
				goto done_attr;
		} else
@@pp_endif@@
		{
		}

		/* Actually create the new thread. */
		result = pthread_create(newthread, &attr, start_routine, arg);
		goto done_attr; /* Suppress warnings if not otherwise used. */
done_attr:;
@@pp_if $has_function(pthread_attr_destroy)@@
		pthread_attr_destroy(&attr);
@@pp_endif@@
@@pp_endif@@
	} else {
		/* Create new thread with default attributes. */
		result = pthread_create(newthread, NULL, start_routine, arg);
	}
	return result;
}


[[cp, decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_join)]]
$errno_t thr_join(thread_t thr, thread_t *p_departed, void **thread_return) {
	errno_t result;
	result = pthread_join(thr, thread_return);
	if (result == 0)
		*p_departed = thr;
	return result;
}

%[insert:function(thr_exit = pthread_exit)]

[[const, nothrow, decl_include("<bits/crt/pthreadtypes.h>")]]
thread_t thr_self() = pthread_self;

%[insert:extern(thr_main)]

[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t thr_kill(thread_t thr, $signo_t signo) = pthread_kill;

// TODO: $errno_t thr_suspend(thread_t thr) = pthread_suspend_np;
// TODO: $errno_t thr_continue(thread_t thr) = pthread_resume_np;

[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_setschedparam, pthread_getschedparam)]]
[[impl_include("<bits/os/sched.h>")]]
$errno_t thr_setprio(thread_t thr, int priority) {
	errno_t result;
	struct sched_param param;
	int policy;
	result = pthread_getschedparam(thr, &policy, &param);
	if (result == 0 && param.@sched_priority@ != priority) {
		param.@sched_priority@ = priority;
		result = pthread_setschedparam(thr, policy, &param);
	}
	return result;
}

[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_getschedparam)]]
[[impl_include("<bits/os/sched.h>")]]
$errno_t thr_getprio(thread_t thr, [[nonnull]] int *p_priority) {
	errno_t result;
	struct sched_param param;
	int policy;
	result = pthread_getschedparam(thr, &policy, &param);
	if (result == 0)
		*p_priority = param.@sched_priority@;
	return result;
}

[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t thr_keycreate([[nonnull]] thread_key_t *key,
                       [[nullable]] void (LIBKCALL *destr_function)(void *))
	= pthread_key_create;

[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t thr_keycreate_once([[nonnull]] thread_key_t *key,
                            [[nullable]] void (LIBKCALL *destr_function)(void *))
	= pthread_key_create_once_np;


[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
$errno_t thr_setspecific(thread_key_t key, void *val) = pthread_setspecific;

[[decl_include("<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_getspecific, pthread_setspecific)]]
$errno_t thr_getspecific(thread_key_t key, void **p_val) {
	void *val;
	*p_val = val = pthread_getspecific(key);
	if (val != NULL)
		return 0;
	return pthread_setspecific(key, NULL);
}

%[insert:extern(thr_min_stack)]
%[insert:function(thr_getconcurrency = pthread_getconcurrency)]
%[insert:function(thr_setconcurrency = pthread_setconcurrency)]

void thr_yield(void) = sched_yield;

%
%#ifdef __USE_SOLARIS
%{

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */

}

%[insert:function(thr_sigsetmask = pthread_sigmask)]

@@>> thr_stksegment(3)
@@Wrapper for `pthread_stackseg_np(pthread_self(), sinfo)'
[[decl_include("<bits/os/sigstack.h>", "<bits/types.h>")]]
[[requires_function(pthread_stackseg_np, pthread_self)]]
$errno_t thr_stksegment(stack_t *sinfo) {
	return pthread_stackseg_np(pthread_self(), sinfo);
}
%#endif /* __USE_SOLARIS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
