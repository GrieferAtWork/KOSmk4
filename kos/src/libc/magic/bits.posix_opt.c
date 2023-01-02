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

%(c_prefix){
/* (#) Portability: GNU C Library (/bits/posix_opt.h) */
/* (#) Portability: mintlib       (/include/bits/posix_opt.h) */
}

%{

/* NOTE: This file must _always_ be kept for Glibc compatibility! */

}%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/os/termios.h> /* __VDISABLE */
)]%{

#ifndef __VDISABLE
#define __VDISABLE '\0'
#endif /* !__VDISABLE */

}


%[insert:pp_if($has_function(setpgid, tcdrain, tcflush, tcgetpgrp,
                             tcsendbreak, tcsetattr, tcsetpgrp))]
%#define _POSIX_JOB_CONTROL                   1 /* Job control is supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(geteuid, getegid, getgid, getuid, seteuid, setegid, setgid, setuid))]
%#define _POSIX_SAVED_IDS                     1 /* Processes have a saved set-user-ID and a saved set-group-ID. */
%[insert:pp_endif]


%[insert:pp_if($has_function(nice, sched_getparam, sched_setparam,
                             sched_get_priority_max, sched_get_priority_min,
                             sched_getscheduler, sched_setscheduler,
                             sched_rr_get_interval))]
%#define _POSIX_PRIORITY_SCHEDULING           200809L /* Priority scheduling is supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(fsync))]
%#define _POSIX_FSYNC                         200809L /* The fsync function is present. */
%[insert:pp_endif]


%[insert:pp_if($has_function(fdatasync))]
%#define _POSIX_SYNCHRONIZED_IO               200809L /* Synchronizing file data is supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(mmap, msync, munmap))]
%#define _POSIX_MAPPED_FILES                  200809L /* Mapping of files to memory is supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(mlockall, munlockall))]
%#define _POSIX_MEMLOCK                       200809L /* Locking of all memory is supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(mlock, munlock))]
%#define _POSIX_MEMLOCK_RANGE                 200809L /* Locking of ranges of memory is supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(mprotect))]
%#define _POSIX_MEMORY_PROTECTION             200809L /* Setting of memory protections is supported. */
%[insert:pp_endif]


%#define _POSIX_CHOWN_RESTRICTED              0       /* Some filesystems allow all users to change file ownership. */


%#ifndef _POSIX_VDISABLE
%#define _POSIX_VDISABLE                      __VDISABLE /* `c_cc' member of `struct termios' structure can be disabled by using the value _POSIX_VDISABLE. */
%#endif /* !_POSIX_VDISABLE */


%#define _POSIX_NO_TRUNC                      1       /* Filenames are not silently truncated. */


%#if 0
%#define _XOPEN_REALTIME                      1       /* X/Open realtime support is available. */
%#define _XOPEN_REALTIME_THREADS              1       /* X/Open thread realtime support is available. */
%#endif


%#define _XOPEN_SHM                           1       /* XPG4.2 shared memory is supported. */


/* >> pthread_atfork()
 * >> pthread_attr_destroy()
 * >> pthread_attr_getdetachstate()
 * >> pthread_attr_getschedparam()
 * >> pthread_attr_init()
 * >> pthread_attr_setdetachstate()
 * >> pthread_attr_setschedparam()
 * >> pthread_cancel()
 * >> pthread_cleanup_push()
 * >> pthread_cleanup_pop()
 * >> pthread_cond_broadcast()
 * >> pthread_cond_destroy()
 * >> pthread_cond_init()
 * >> pthread_cond_signal()
 * >> pthread_cond_timedwait()
 * >> pthread_cond_wait()
 * >> pthread_condattr_destroy()
 * >> pthread_condattr_init()
 * >> pthread_create()
 * >> pthread_detach()
 * >> pthread_equal()
 * >> pthread_exit()
 * >> pthread_getspecific()
 * >> pthread_join()
 * >> pthread_key_create()
 * >> pthread_key_delete()
 * >> pthread_mutex_destroy()
 * >> pthread_mutex_init()
 * >> pthread_mutex_lock()
 * >> pthread_mutex_trylock()
 * >> pthread_mutex_unlock()
 * >> pthread_mutexattr_destroy()
 * >> pthread_mutexattr_init()
 * >> pthread_once()
 * >> pthread_rwlock_destroy()
 * >> pthread_rwlock_init()
 * >> pthread_rwlock_rdlock()
 * >> pthread_rwlock_tryrdlock()
 * >> pthread_rwlock_trywrlock()
 * >> pthread_rwlock_unlock()
 * >> pthread_rwlock_wrlock()
 * >> pthread_rwlockattr_destroy()
 * >> pthread_rwlockattr_init()
 * >> pthread_self()
 * >> pthread_setcancelstate()
 * >> pthread_setcanceltype()
 * >> pthread_setspecific()
 * >> pthread_testcancel() */
%[insert:pp_if($has_function(pthread_self))]
%#define _POSIX_THREADS                       200809L /* Tell we have POSIX threads. */
%[insert:pp_endif]


%#define _POSIX_REENTRANT_FUNCTIONS           1       /* We have the reentrant functions described in POSIX. */


%[insert:pp_if($has_function(readdir_r, getgrgid_r, getgrnam_r, getpwnam_r, getpwuid_r,
                             flockfile, ftrylockfile, funlockfile, fgetc_unlocked,
                             getchar_unlocked, fputc_unlocked, putchar_unlocked,
                             rand_r, strerror_r, strtok_r, asctime_r, ctime_r,
                             gmtime_r, localtime_r))]
%#define _POSIX_THREAD_SAFE_FUNCTIONS         200809L
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_attr_getinheritsched, pthread_attr_getschedpolicy,
                             pthread_attr_getscope, pthread_attr_setinheritsched,
                             pthread_attr_setschedpolicy, pthread_attr_setscope,
                             pthread_getschedparam, pthread_setschedparam,
                             pthread_setschedprio))]
%#define _POSIX_THREAD_PRIORITY_SCHEDULING    200809L /* We provide priority scheduling for threads. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_attr_getstack, pthread_attr_getstackaddr,
                             pthread_attr_setstack, pthread_attr_setstackaddr))]
%#define _POSIX_THREAD_ATTR_STACKADDR         200809L /* We support user-defined stacks. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_attr_getstack, pthread_attr_getstacksize,
                             pthread_attr_setstack, pthread_attr_setstacksize))]
%#define _POSIX_THREAD_ATTR_STACKSIZE         200809L /* We support user-defined stack sizes. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_mutexattr_getprotocol, pthread_mutexattr_setprotocol))]
%#define _POSIX_THREAD_PRIO_INHERIT           200809L /* We support priority inheritance. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_mutex_getprioceiling, pthread_mutex_setprioceiling,
                             pthread_mutexattr_getprioceiling, pthread_mutexattr_getprotocol,
                             pthread_mutexattr_setprioceiling, pthread_mutexattr_setprotocol))]
%#define _POSIX_THREAD_PRIO_PROTECT           200809L /* We support priority protection, though only for non-robust mutexes. */
%[insert:pp_endif]


%#ifdef __USE_XOPEN2K8
%#define _POSIX_THREAD_ROBUST_PRIO_INHERIT    200809L /* We support priority inheritance for robust mutexes. */
%#define _POSIX_THREAD_ROBUST_PRIO_PROTECT    (-1)    /* We do not support priority protection for robust mutexes. */
%#endif /* __USE_XOPEN2K8 */


%[insert:pp_if($has_function(sem_close, sem_destroy, sem_getvalue,
                             sem_init, sem_open, sem_post,
                             sem_trywait, sem_unlink, sem_wait))]
%#define _POSIX_SEMAPHORES                    200809L /* We support POSIX.1b semaphores. */
%[insert:pp_endif]


%[insert:pp_if($has_function(sigqueue, sigtimedwait, sigwaitinfo))]
%#define _POSIX_REALTIME_SIGNALS              200809L /* Real-time signals are supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(aio_cancel, aio_error, aio_fsync, aio_read,
                             aio_return, aio_suspend, aio_write, lio_listio))]
%#define _POSIX_ASYNCHRONOUS_IO               200809L /* We support asynchronous I/O. */
%#define _POSIX_ASYNC_IO                      1
%#define _LFS_ASYNCHRONOUS_IO                 1       /* Alternative name for Unix98. */
%#define _POSIX_PRIORITIZED_IO                200809L /* Support for prioritization is also available. */
%[insert:pp_endif]


%[insert:pp_if($has_function(open64))]
%#ifdef _LFS_ASYNCHRONOUS_IO
%#define _LFS64_ASYNCHRONOUS_IO               1       /* The LFS support in asynchronous I/O is also available. */
%#endif /* _LFS_ASYNCHRONOUS_IO */
%#define _LFS_LARGEFILE                       1       /* The rest of the LFS is also available. */
%#define _LFS64_LARGEFILE                     1
%[insert:pp_endif]


%[insert:pp_if($has_function(fopen64))]
%#define _LFS64_STDIO                         1
%[insert:pp_endif]


%[insert:pp_if($has_function(mmap, munmap, shm_open, shm_unlink))]
%#define _POSIX_SHARED_MEMORY_OBJECTS         200809L /* POSIX shared memory objects are implemented. */
%[insert:pp_endif]


%[insert:pp_if($has_function(clock_getcpuclockid))]
%#define _POSIX_CPUTIME                       0       /* CPU-time clocks support needs to be checked at runtime. */
%[insert:pp_endif]

%[insert:pp_if($has_function(pthread_getcpuclockid))]
%#define _POSIX_THREAD_CPUTIME                0       /* Clock support in threads must be also checked at runtime. */
%[insert:pp_endif]


%[insert:pp_if($has_function(regcomp, regerror, regexec, regfree))]
%#define _POSIX_REGEXP                        1       /* We provides regular expression handling. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_rwlock_destroy, pthread_rwlock_init, pthread_rwlock_rdlock,
                             pthread_rwlock_tryrdlock, pthread_rwlock_trywrlock,
                             pthread_rwlock_unlock, pthread_rwlock_wrlock,
                             pthread_rwlockattr_destroy, pthread_rwlockattr_init))]
%#define _POSIX_READER_WRITER_LOCKS           200809L /* Reader/Writer locks are available. */
%[insert:pp_endif]


%[insert:pp_if($has_function(system))]
%#define _POSIX_SHELL                         1       /* We have a POSIX shell. */
%[insert:pp_endif]


%[insert:pp_if($has_function(mq_timedreceive, mq_timedsend, pthread_mutex_timedlock,
                             pthread_rwlock_timedrdlock, pthread_rwlock_timedwrlock,
                             sem_timedwait, /*, posix_trace_timedgetnext_event*/))]
%#define _POSIX_TIMEOUTS                      200809L /* We support the Timeouts option. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_spin_destroy, pthread_spin_init,
                             pthread_spin_lock, pthread_spin_trylock,
                             pthread_spin_unlock))]
%#define _POSIX_SPIN_LOCKS                    200809L /* We support spinlocks. */
%[insert:pp_endif]


%[insert:pp_if($has_function(posix_spawn, posix_spawnp,
                             posix_spawn_file_actions_addclose, posix_spawn_file_actions_adddup2,
                             posix_spawn_file_actions_addopen, posix_spawn_file_actions_destroy,
                             posix_spawn_file_actions_init, posix_spawnattr_destroy,
                             posix_spawnattr_getsigdefault, posix_spawnattr_getflags,
                             posix_spawnattr_getpgroup, posix_spawnattr_getsigmask,
                             posix_spawnattr_init, posix_spawnattr_setsigdefault,
                             posix_spawnattr_setflags, posix_spawnattr_setpgroup,
                             posix_spawnattr_setsigmask))]
%#define _POSIX_SPAWN                         200809L /* The `spawn' function family is supported. */
%[insert:pp_endif]


%[insert:pp_if($has_function(timer_create, timer_delete, timer_gettime, timer_getoverrun, timer_settime))]
%#define _POSIX_TIMERS                        200809L /* We have POSIX timers. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_barrier_destroy, pthread_barrier_init,
                             pthread_barrier_wait, pthread_barrierattr_destroy,
                             pthread_barrierattr_init))]
%#define _POSIX_BARRIERS                      200809L /* The barrier functions are available. */
%[insert:pp_endif]


%[insert:pp_if($has_function(mq_close, mq_getattr, mq_notify, mq_open,
                             mq_receive, mq_send, mq_setattr, mq_unlink))]
%#define _POSIX_MESSAGE_PASSING               200809L /* POSIX message queues are available. */
%[insert:pp_endif]


%[insert:pp_if($has_function(pthread_barrierattr_getpshared, pthread_barrierattr_setpshared,
                             pthread_condattr_getpshared, pthread_condattr_setpshared,
                             pthread_mutexattr_getpshared, pthread_mutexattr_setpshared,
                             pthread_rwlockattr_getpshared, pthread_rwlockattr_setpshared))]
%#define _POSIX_THREAD_PROCESS_SHARED         200809L /* Thread process-shared synchronization is supported. */
%[insert:pp_endif]


%#define _POSIX_MONOTONIC_CLOCK               0       /* The monotonic clock might be available. */


%[insert:pp_if($has_function(pthread_condattr_getclock, pthread_condattr_setclock, clock_nanosleep))]
%#define _POSIX_CLOCK_SELECTION               200809L /* The clock selection interfaces are available. */
%[insert:pp_endif]


%[insert:pp_if($has_function(posix_fadvise, posix_fallocate, posix_memalign, posix_madvise))]
%#define _POSIX_ADVISORY_INFO                 200809L /* Advisory information interfaces are available. */
%[insert:pp_endif]


%#define _POSIX_IPV6                          200809L /* IPv6 support is available. */
%#define _POSIX_RAW_SOCKETS                   200809L /* Raw socket support is available. */


%[insert:pp_if($has_function(isatty))]
%#define _POSIX2_CHAR_TERM                    200809L /* We have at least one terminal. */
%[insert:pp_endif]


//%[insert:pp_if($has_function(sched_getparam, sched_getscheduler,
//                             sched_setparam, sched_setscheduler))]
%#define _POSIX_SPORADIC_SERVER               (-1)    /* Neither process nor thread sporadic server interfaces is available. */
%#define _POSIX_THREAD_SPORADIC_SERVER        (-1)    /* Neither process nor thread sporadic server interfaces is available. */
//%[insert:pp_endif]


//%[insert:pp_if($has_function(posix_trace_attr_destroy, posix_trace_attr_getclockres,
//                             posix_trace_attr_getcreatetime,          posix_trace_attr_getgenversion,
//                             posix_trace_attr_getmaxdatasize, posix_trace_attr_getmaxsystemeventsize,
//                             posix_trace_attr_getmaxusereventsize,          posix_trace_attr_getname,
//                             posix_trace_attr_getstreamfullpolicy,    posix_trace_attr_getstreamsize,
//                             posix_trace_attr_init,                  posix_trace_attr_setmaxdatasize,
//                             posix_trace_attr_setname,                posix_trace_attr_setstreamsize,
//                             posix_trace_attr_setstreamfullpolicy,                 posix_trace_clear,
//                             posix_trace_create,    posix_trace_event,     posix_trace_eventid_equal,
//                             posix_trace_eventid_get_name, posix_trace_eventid_open,
//                             posix_trace_eventtypelist_getnext_id, posix_trace_eventtypelist_rewind,
//                             posix_trace_flush,    posix_trace_get_attr,     posix_trace_get_status,
//                             posix_trace_getnext_event,   posix_trace_shutdown,   posix_trace_start,
//                             posix_trace_stop, posix_trace_trygetnext_event))]
%#define _POSIX_TRACE                         (-1)    /* trace.h is not available. */
//%[insert:pp_endif]


//%[insert:pp_if($has_function(posix_trace_eventset_add, posix_trace_eventset_del,
//                             posix_trace_eventset_empty,   posix_trace_eventset_fill,
//                             posix_trace_eventset_ismember,   posix_trace_get_filter,
//                             posix_trace_set_filter, posix_trace_trid_eventid_open))]
%#define _POSIX_TRACE_EVENT_FILTER            (-1)
//%[insert:pp_endif]


//%[insert:pp_if($has_function(posix_trace_attr_getinherited, posix_trace_attr_setinherited))]
%#define _POSIX_TRACE_INHERIT                 (-1)
//%[insert:pp_endif]


//%[insert:pp_if($has_function(posix_trace_attr_getlogfullpolicy, posix_trace_attr_getlogsize,
//                             posix_trace_attr_setlogfullpolicy,  posix_trace_attr_setlogsize,
//                             posix_trace_close, posix_trace_create_withlog, posix_trace_open,
//                             posix_trace_rewind))]
%#define _POSIX_TRACE_LOG                     (-1)
//%[insert:pp_endif]


//%[insert:pp_if($has_function(posix_mem_offset, posix_typed_mem_get_info, posix_typed_mem_open))]
%#define _POSIX_TYPED_MEMORY_OBJECTS          (-1)    /* Typed memory objects are not available. */
//%[insert:pp_endif]


%[insert:pp_if($has_function(crypt, encrypt, setkey))]
%#define _XOPEN_CRYPT 1
%[insert:pp_endif]


%[insert:pp_if($has_function(catclose, catgets, catopen, nl_langinfo, setlocale))]
%#define _XOPEN_ENH_I18N 1
%[insert:pp_endif]


%[insert:pp_if($has_function(bcmp, bcopy, bzero, ecvt, fcvt, ftime, gcvt,
                             getwd, strchr/*index*/, mktemp, strrchr/*rindex*/,
                             utimes, wcsstr/*wcswcs*/))]
%#define _XOPEN_LEGACY 1
%[insert:pp_endif]


%[insert:pp_if($has_function(isastream, getmsg, getpmsg, ioctl, putmsg, putpmsg, fattach, fdetach))]
%#define _XOPEN_STREAMS 1
%[insert:pp_endif]
