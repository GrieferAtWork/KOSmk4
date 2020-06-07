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

%[define_replacement(pid_t = __pid_t)]
%[define_replacement(cpu_set_t = __cpu_set_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(time_t = "__TM_TYPE(time)")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]


%{
#include <features.h>

#include <bits/sched.h>
#include <bits/timespec.h>
#include <bits/types.h>

#define sched_priority __sched_priority

__SYSDECL_BEGIN

}
%#ifdef __USE_GNU
%{

#ifdef __CC__
typedef __cpu_set_t cpu_set_t;
#endif /* __CC__ */

#ifdef __USE_KOS
#define CPU_SETNONE                  __CPU_SETNONE
#define CPU_SETALL                   __CPU_SETALL
#define CPU_SETONE(i)                __CPU_SETONE(i)
#define CPU_ISEMPTY(cpusetp)         __CPU_ISEMPTY_S(sizeof(cpu_set_t), cpusetp)
#define CPU_FILL(cpusetp)            __CPU_FILL_S(sizeof(cpu_set_t), cpusetp)
#define CPU_FILL_S(setsize, cpusetp) __CPU_FILL_S(setsize, cpusetp)
#endif /* __USE_KOS */
#define CPU_SETSIZE   __CPU_SETSIZE

#define CPU_SET(cpu, cpusetp)                         __CPU_SET_S(cpu, sizeof(cpu_set_t), cpusetp)
#define CPU_CLR(cpu, cpusetp)                         __CPU_CLR_S(cpu, sizeof(cpu_set_t), cpusetp)
#define CPU_ISSET(cpu, cpusetp)                     __CPU_ISSET_S(cpu, sizeof(cpu_set_t), cpusetp)
#define CPU_ZERO(cpusetp)                            __CPU_ZERO_S(sizeof(cpu_set_t), cpusetp)
#define CPU_COUNT(cpusetp)                          __CPU_COUNT_S(sizeof(cpu_set_t), cpusetp)
#define CPU_SET_S(cpu, setsize, cpusetp)              __CPU_SET_S(cpu, setsize, cpusetp)
#define CPU_CLR_S(cpu, setsize, cpusetp)              __CPU_CLR_S(cpu, setsize, cpusetp)
#define CPU_ISSET_S(cpu, setsize, cpusetp)          __CPU_ISSET_S(cpu, setsize, cpusetp)
#define CPU_ZERO_S(setsize, cpusetp)                 __CPU_ZERO_S(setsize, cpusetp)
#define CPU_COUNT_S(setsize, cpusetp)               __CPU_COUNT_S(setsize, cpusetp)
#define CPU_EQUAL(cpusetp1, cpusetp2)               __CPU_EQUAL_S(sizeof(cpu_set_t), cpusetp1, cpusetp2)
#define CPU_EQUAL_S(setsize, cpusetp1, cpusetp2)    __CPU_EQUAL_S(setsize, cpusetp1, cpusetp2)
#define CPU_AND(destset, srcset1, srcset2)            __CPU_AND_S(sizeof(cpu_set_t), destset, srcset1, srcset2, &)
#define CPU_OR(destset, srcset1, srcset2)              __CPU_OR_S(sizeof(cpu_set_t), destset, srcset1, srcset2, |)
#define CPU_XOR(destset, srcset1, srcset2)            __CPU_XOR_S(sizeof(cpu_set_t), destset, srcset1, srcset2, ^)
#define CPU_AND_S(setsize, destset, srcset1, srcset2) __CPU_AND_S(setsize, destset, srcset1, srcset2, &)
#define CPU_OR_S(setsize, destset, srcset1, srcset2)   __CPU_OR_S(setsize, destset, srcset1, srcset2, |)
#define CPU_XOR_S(setsize, destset, srcset1, srcset2) __CPU_XOR_S(setsize, destset, srcset1, srcset2, ^)
#define CPU_ALLOC_SIZE(count)                    __CPU_ALLOC_SIZE(count)
#define CPU_ALLOC(count)                              __CPU_ALLOC(count)
#define CPU_FREE(cpuset)                               __CPU_FREE(cpuset)

}
%#ifdef __CC__


%[default_impl_section(".text.crt.sched.param")];

int sched_setparam($pid_t pid, struct sched_param const *param);

[[export_alias("__sched_getparam")]]
int sched_getparam($pid_t pid, struct sched_param *param);
[[export_alias("__sched_setscheduler")]]
int sched_setscheduler($pid_t pid, int policy, struct sched_param const *param);
[[export_alias("__sched_getscheduler")]]
int sched_getscheduler($pid_t pid);

%
%[default_impl_section(".text.crt.sched.thread")];

@@@return: 1: Another thread was executed prior to the function returning
@@            The thread may not necessarily be apart of the calling process
@@@return: 0: The function returned immediately when no other thread was executed
[[export_alias("thrd_yield", "pthread_yield", "__sched_yield")]]
int sched_yield();

%[default_impl_section(".text.crt.sched.param")];

[[export_alias("__sched_get_priority_max")]]
int sched_get_priority_max(int algorithm);
[[export_alias("__sched_get_priority_min")]]
int sched_get_priority_min(int algorithm);

int sched_setaffinity($pid_t pid, $size_t cpusetsize, cpu_set_t const *cpuset);
int sched_getaffinity($pid_t pid, $size_t cpusetsize, cpu_set_t *cpuset);

[[ignore, nocrt, alias("sched_rr_get_interval")]]
int sched_rr_get_interval32($pid_t pid, struct $timespec32 *tms);

[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(sched_rr_get_interval64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(sched_rr_get_interval)]]
[[userimpl, requires($has_function(sched_rr_get_interval32) || $has_function(sched_rr_get_interval64))]]
int sched_rr_get_interval($pid_t pid, struct timespec *tms) {
@@pp_if $has_function(sched_rr_get_interval32)@@
	struct timespec32 tms32;
	if (!tms)
		return sched_rr_get_interval32(pid, NULL);
	tms32.tv_sec  = (time32_t)tms->tv_sec;
	tms32.tv_nsec = tms->tv_nsec;
	return sched_rr_get_interval32(pid, &tms32);
@@pp_else@@
	struct timespec64 tms64;
	if (!tms)
		return sched_rr_get_interval64(pid, NULL);
	tms64.tv_sec  = (time64_t)tms->tv_sec;
	tms64.tv_nsec = tms->tv_nsec;
	return sched_rr_get_interval64(pid, &tms64);
@@pp_endif@@
}

%#ifdef __USE_TIME64
[[time64_variant_of(sched_rr_get_interval)]]
[[userimpl, requires_function(sched_rr_get_interval32)]]
sched_rr_get_interval64:($pid_t pid, struct $timespec64 *tms) -> int {
	struct timespec32 tms32;
	if (!tms)
		return sched_rr_get_interval32(pid, NULL);
	tms32.tv_sec  = (time32_t)tms->tv_sec;
	tms32.tv_nsec = tms->tv_nsec;
	return sched_rr_get_interval32(pid, &tms32);
}
%#endif /* __USE_TIME64 */


%#endif /* __CC__ */
%#endif /* __USE_GNU */
%{

__SYSDECL_END

}