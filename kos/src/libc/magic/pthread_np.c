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
%(c_prefix){
/* (#) Portability: DragonFly BSD (/include/pthread_np.h) */
/* (#) Portability: FreeBSD       (/include/pthread_np.h) */
/* (#) Portability: OpenBSD       (/include/pthread_np.h) */
/*!always_includes <pthread.h>*/
}

%[default:section(".text.crt{|.dos}.sched.pthread")]
%[define_replacement(stack_t = "struct sigaltstack")]

%[define_decl_include_implication("<bits/crt/pthreadtypes.h>" => ["<hybrid/typecore.h>"])]
%[define_decl_include("<bits/crt/pthreadtypes.h>": ["__pthread_t"])]

%[define_decl_include("<bits/os/sigstack.h>": ["struct sigaltstack"])]

%[insert:prefix(
#include <bits/os/sigstack.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <pthread.h>
)]%{


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __pthread_switch_routine_t_defined
#define __pthread_switch_routine_t_defined
typedef void (__LIBKCALL *pthread_switch_routine_t)(pthread_t, pthread_t);
#endif /* !__pthread_switch_routine_t_defined */

#ifndef __stack_t_defined
#define __stack_t_defined
typedef struct sigaltstack stack_t;
#endif /* !__stack_t_defined */

#ifndef __pthread_id_np_t_defined
#define __pthread_id_np_t_defined
typedef __pid_t pthread_id_np_t;
#endif /* !__pthread_id_np_t_defined */

}

%[define_replacement(pthread_id_np_t = __pid_t)]


%[insert:function(pthread_mutexattr_getkind_np = pthread_mutexattr_gettype)]
%[insert:function(pthread_mutexattr_setkind_np = pthread_mutexattr_settype)]
%[insert:function(pthread_get_name_np = pthread_getname_np)]
%[insert:extern(pthread_getname_np)]
%[insert:function(pthread_set_name_np = pthread_setname_np)]
%[insert:extern(pthread_setname_np)]
%[insert:function(pthread_attr_get_np = pthread_getattr_np)]
%[insert:extern(pthread_main_np)]
%[insert:extern(pthread_attr_getaffinity_np)]
%[insert:extern(pthread_attr_setaffinity_np)]
%[insert:extern(pthread_getaffinity_np)]
%[insert:function(pthread_multi_np = pthread_multi_np)]
%[insert:function(pthread_single_np = pthread_suspend_all_np)]
%[insert:function(pthread_peekjoin_np = pthread_tryjoin_np)]
%[insert:extern(pthread_setaffinity_np)]
%[insert:extern(pthread_timedjoin_np)]
%[insert:extern(pthread_timedjoin64_np)]

[[decl_include("<bits/types.h>")]]
pthread_id_np_t pthread_getthreadid_np() = gettid;

@@>> pthread_stackseg_np(3)
@@Convenience wrapper for `pthread_getattr_np(3)' + `pthread_attr_getstack()'
[[decl_include("<bits/os/sigstack.h>", "<bits/types.h>", "<bits/crt/pthreadtypes.h>")]]
[[requires_function(pthread_getattr_np, pthread_attr_getstack)]]
$errno_t pthread_stackseg_np(pthread_t self, [[out]] stack_t *sinfo) {
	errno_t result;
	pthread_attr_t attr;
	result = pthread_getattr_np(self, &attr);
	if likely(result == 0) {
		void *stackaddr;
		size_t stacksize;
		result = pthread_attr_getstack(&attr, &stackaddr, &stacksize);
		if likely(result == 0) {
			sinfo->@ss_sp@    = stackaddr;
			sinfo->@ss_size@  = stacksize;
			sinfo->@ss_flags@ = 0;
		}
@@pp_if $has_function(pthread_attr_destroy)@@
		pthread_attr_destroy(&attr);
@@pp_endif@@
	}
	return result;
}


%[insert:extern(pthread_attr_setcreatesuspend_np)]
%[insert:extern(pthread_suspend_np)]
%[insert:extern(pthread_resume_np)]
%[insert:extern(pthread_continue_np)]
%[insert:guarded_function(pthread_unsuspend_np = pthread_continue_np)]
%[insert:extern(pthread_suspend_all_np)]
%[insert:guarded_function(pthread_resume_all_np = pthread_multi_np)]

%[insert:function(pthread_getunique_np = pthread_getunique_np)]

%{

__SYSDECL_END
#endif /* __CC__ */

}
