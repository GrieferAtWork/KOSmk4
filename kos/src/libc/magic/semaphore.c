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

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(sem_t = __sem_t)]
%[default:section(".text.crt{|.dos}.sched.semaphore")]

%{
#include <features.h>

#include <asm/crt/semaphore.h>  /* __ARCH_HAVE_INTERPROCESS_SEMAPHORES, __ARCH_HAVE_NON_UNIQUE_SEM_OPEN */
#include <bits/crt/semaphore.h> /* __sem_t */
#include <bits/types.h>
#ifdef __USE_XOPEN2K
#include <bits/os/timespec.h>
#endif /* __USE_XOPEN2K */

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

#if !defined(SEM_FAILED) && defined(__SEM_FAILED)
#define SEM_FAILED (__CCAST(sem_t *)__SEM_FAILED) /* Returned by `sem_open(3)' upon failure. */
#endif /* !SEM_FAILED && __SEM_FAILED */

#ifdef __CC__
__SYSDECL_BEGIN

typedef __sem_t sem_t;

}

@@>> sem_init(3)
@@Initialize the given semaphore `sem' to start out with `value' tickets
@@@param: sem:     The semaphore to initialize
@@@param: pshared: When non-zero, `sem' may point to a memory region shared
@@                 with another process, such that both caller, and any process
@@                 the pointed-to memory is shared with can safely operate on
@@                 the same semaphore.
@@@param: value:   The initial # of tickets available.
@@@return: 0:      Success
@@@return: -1:     [errno=EINVAL] `value > SEM_VALUE_MAX'
@@                 HINT: Never returned `#if SEM_VALUE_MAX >= UINT_MAX'
@@@return: -1:     [errno=ENOSYS] `pshared != 0', but inter-process semaphores aren't supported
@@                 HINT: Never returned `#ifdef __ARCH_HAVE_INTERPROCESS_SEMAPHORES'
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_init([[nonnull]] sem_t *sem, int pshared, unsigned int value);

@@>> sem_destroy(3)
@@Destroy a semaphore previously initialized by `sem_init(3)'
@@@return: 0: Success
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_destroy([[nonnull]] sem_t *sem);

@@>> sem_open(3)
@@Open a named semaphore `name', which must be string that starts with `/'
@@NOTE: When called multiple times with identical strings for `name',
@@      the behavior of this function differes between implementations:
@@      #ifdef __ARCH_HAVE_NON_UNIQUE_SEM_OPEN
@@         The returned pointer is allowed to be unique and different from
@@         any previously returned semaphore, but the backing physical memory
@@         will be shared with other semaphores with the same name.
@@      #else // __ARCH_HAVE_NON_UNIQUE_SEM_OPEN
@@         The returned pointer may be identical to a pointer previously
@@         returned for the same semaphore. In this case, `sem_close()' may
@@         only have to be called once to close all open handles for the
@@         semaphore
@@      #endif // !__ARCH_HAVE_NON_UNIQUE_SEM_OPEN
@@@param: oflags:      Set of `0 | O_CREAT | O_EXCL' (When `O_CREAT' is given, this functions
@@                     takes 2 additional arguments `..., mode_t mode, unsigned int value')
@@@return: * :         A pointer to the opened semaphore, which must be closed by `sem_close(3)'
@@@return: SEM_FAILED: [errno=EINVAL] The given `name' contains no characters after the initial `/'
@@@return: SEM_FAILED: Error (s.a. `errno')
[[cp_kos, vartypes($mode_t, unsigned int)]]
[[decl_include("<bits/crt/semaphore.h>")]]
sem_t *sem_open([[nonnull]] char const *name, $oflag_t oflags,
                ... /*mode_t mode, unsigned int value*/);

@@>> sem_close(3)
@@Close a semaphore previously returned by `sem_open(3)'. But note the case
@@of opening the same semaphore more than once within the same process, as
@@described by in `sem_open(3)' and by `__ARCH_HAVE_NON_UNIQUE_SEM_OPEN'->
@@@return: 0: Success
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_close([[nonnull]] sem_t *sem);

@@>> sem_unlink(3)
@@Unlink (delete) a named semaphore `name' that was
@@previously created by `sem_open(name, O_CREAT)'
@@@return: 0:  Success
@@@return: -1: [errno=EINVAL] The given `name' contains no characters after the initial `/'
@@@return: -1: Error (s.a. `errno')
[[cp_kos]]
int sem_unlink([[nonnull]] const char *name);


@@>> sem_wait(3)
@@Wait for a ticket to become available to the given semaphore `sem'
@@Once a ticket has become available, consume it and return. Until that
@@point in time, keep on blocking.
@@@return: 0:  Success
@@@return: -1: [errno=EINTR] Interrupted.
[[cp, decl_include("<bits/crt/semaphore.h>")]]
int sem_wait([[nonnull]] sem_t *sem);

[[cp, doc_alias(sem_timedwait), ignore, nocrt, alias("sem_timedwait")]]
[[decl_include("<bits/crt/semaphore.h>", "<bits/os/timespec.h>")]]
int sem_timedwait32([[nonnull]] sem_t *__restrict sem,
                    [[nonnull]] struct $timespec32 const *__restrict abstime);


%
%#ifdef __USE_XOPEN2K
@@>> sem_timedwait(3)
@@Wait for a ticket to become available to the given semaphore `sem'
@@Once a ticket has become available, consume it and return. If no ticket
@@becomes available until `abstime' has passed, return `errno=ETIMEDOUT'
@@@return: 0:  Success
@@@return: -1: [errno=EINTR]     Interrupted.
@@@return: -1: [errno=ETIMEDOUT] The given `abstime' expired before a ticket became available.
[[cp, no_crt_self_import, decl_include("<bits/crt/semaphore.h>", "<bits/os/timespec.h>")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("sem_timedwait")]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("sem_timedwait64")]]
[[userimpl, requires($has_function(sem_timedwait32) || $has_function(sem_timedwait64))]]
int sem_timedwait([[nonnull]] sem_t *__restrict sem,
                  [[nonnull]] struct timespec const *__restrict abstime) {
@@pp_if $has_function(sem_timedwait32)@@
	struct timespec32 ts32;
	ts32.tv_sec = (time32_t)abstime->tv_sec;
	ts32.tv_nsec = abstime->tv_nsec;
	return sem_timedwait32(sem, &ts32);
@@pp_else@@
	struct timespec64 ts64;
	ts64.tv_sec = (time64_t)abstime->tv_sec;
	ts64.tv_nsec = abstime->tv_nsec;
	return sem_timedwait64(sem, &ts64);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[cp, time64_variant_of(sem_timedwait), doc_alias(sem_timedwait)]]
[[userimpl, requires_function(sem_timedwait32)]]
[[decl_include("<bits/crt/semaphore.h>", "<bits/os/timespec.h>")]]
int sem_timedwait64([[nonnull]] sem_t *__restrict sem,
                    [[nonnull]] struct timespec64 const *__restrict abstime) {
	struct timespec32 ts32;
	ts32.tv_sec  = (time32_t)abstime->tv_sec;
	ts32.tv_nsec = abstime->tv_nsec;
	return sem_timedwait32(sem, &ts32);
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K */

@@>> sem_trywait(3)
@@Atomically check if at least 1 ticket is available for `sem', and consume
@@one if this is the case, or return with `errno=EAGAIN' if no tickets were
@@available at the time of the call.
@@@return: 0:  Success
@@@return: -1: [errno=EAGAIN] A ticket could not be acquired without blocking.
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_trywait([[nonnull]] sem_t *sem);

@@>> sem_post(3)
@@Post a ticket to the given semaphore `sem', waking up to 1 other thread
@@that may be waiting for tickets to become available before returning.
@@@return: 0:  Success
@@@return: -1: [errno=EOVERFLOW] The maximum number of tickets have already been posted.
[[decl_include("<bits/crt/semaphore.h>")]]
int sem_post([[nonnull]] sem_t *sem);

@@>> sem_getvalue(3)
@@Capture a snapshot of how may tickets are available storing that number in `*sval'
@@@return: 0: Success
[[decl_include("<features.h>", "<bits/crt/semaphore.h>")]]
int sem_getvalue([[nonnull]] sem_t *__restrict sem,
                 [[nonnull]] __STDC_INT_AS_UINT_T *__restrict sval);


%{
#endif /* __CC__ */

__SYSDECL_END

}