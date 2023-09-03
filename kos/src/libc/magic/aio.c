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
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/aio.h) */
/* (#) Portability: GNU C Library (/rt/aio.h) */
/* (#) Portability: GNU Hurd      (/usr/include/aio.h) */
/* (#) Portability: NetBSD        (/include/aio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/aio.h) */
/* (#) Portability: libc6         (/include/aio.h) */
/* (#) Portability: musl libc     (/include/aio.h) */
}

%[default:section(".text.crt{|.dos}.utility.aio")]

%[define_decl_include_implication("<bits/crt/aiocb.h>" => ["<bits/os/sigevent.h>", "<bits/types.h>"])]
%[define_decl_include("<bits/crt/aiocb.h>": ["struct aiocb", "struct __aiocb64"])]
%[define_decl_include("<bits/os/sigevent.h>": ["struct sigevent"])]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <asm/crt/aio.h>
)]%[insert:prefix(
#include <bits/os/sigevent.h> /* struct sigevent */
)]%[insert:prefix(
#include <bits/os/timespec.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/crt/aiocb.h>
)]%{

#ifdef __USE_GNU
#include <bits/crt/aioinit.h>
#endif /* __USE_GNU */

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

/* Return values of cancellation function. */
#if !defined(AIO_CANCELED) && defined(__AIO_CANCELED)
#define AIO_CANCELED    __AIO_CANCELED    /* ??? */
#endif /* !AIO_CANCELED && __AIO_CANCELED */
#if !defined(AIO_NOTCANCELED) && defined(__AIO_NOTCANCELED)
#define AIO_NOTCANCELED __AIO_NOTCANCELED /* ??? */
#endif /* !AIO_NOTCANCELED && __AIO_NOTCANCELED */
#if !defined(AIO_ALLDONE) && defined(__AIO_ALLDONE)
#define AIO_ALLDONE     __AIO_ALLDONE     /* ??? */
#endif /* !AIO_ALLDONE && __AIO_ALLDONE */

/* Operation codes for `aio_lio_opcode'. */
#if !defined(LIO_READ) && defined(__LIO_READ)
#define LIO_READ  __LIO_READ  /* Perform an async `read(2)' or `pread(2)' */
#endif /* !LIO_READ && __LIO_READ */
#if !defined(LIO_WRITE) && defined(__LIO_WRITE)
#define LIO_WRITE __LIO_WRITE /* Perform an async `write(2)' or `pwrite(2)' */
#endif /* !LIO_WRITE && __LIO_WRITE */
#if !defined(LIO_NOP) && defined(__LIO_NOP)
#define LIO_NOP   __LIO_NOP   /* No-op */
#endif /* !LIO_NOP && __LIO_NOP */

/* Synchronization options for `lio_listio' function. */
#if !defined(LIO_WAIT) && defined(__LIO_WAIT)
#define LIO_WAIT   __LIO_WAIT   /* ??? */
#endif /* !LIO_WAIT && __LIO_WAIT */
#if !defined(LIO_NOWAIT) && defined(__LIO_NOWAIT)
#define LIO_NOWAIT __LIO_NOWAIT /* ??? */
#endif /* !LIO_NOWAIT && __LIO_NOWAIT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */

}

%[define_replacement(aiocb = aiocb)]
%[define_replacement(aiocb64 = __aiocb64)]
%[define_c_language_keyword(__restrict_arr)]

%{
/*
 * The implementation of NOTIFY_COMPLETION behaves identical to:
 *
 * >> struct thread_cookie {
 * >>     void (LIBKCALL *tc_func)(sigval_t value);
 * >>     sigval_t        tc_value;
 * >> };
 * >> static void *LIBCCALL thread_wrapper(void *arg) {
 * >>     struct thread_cookie cookie;
 * >>     cookie = *(struct thread_cookie *)arg;
 * >>     free(arg);
 * >>     (*cookie.tc_func)(cookie.tc_value);
 * >>     return NULL;
 * >> }
 * >>
 * >> errno_t NOTIFY_COMPLETION(struct sigevent *ev) {
 * >>     errno_t result = EOK;
 * >>     if (ev->sigev_notify == SIGEV_THREAD) {
 * >>         pthread_attr_t _attr;
 * >>         pthread_attr_t *attr = ev->sigev_notify_attributes;
 * >>         struct thread_cookie *cookie;
 * >>         if (!attr) {
 * >>             result = pthread_attr_init(&_attr);
 * >>             if (result != EOK)
 * >>                 goto done;
 * >>             result = pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_DETACHED);
 * >>             if (result != EOK) {
 * >>                 pthread_attr_destroy(&_attr);
 * >>                 goto done;
 * >>             }
 * >>             attr = &_attr;
 * >>         }
 * >>         cookie = (struct thread_cookie *)malloc(sizeof(struct thread_cookie));
 * >>         if (!cookie)
 * >>             result = errno; // Likely: ENOMEM
 * >>         else {
 * >>             pthread_t p;
 * >>             cookie->tc_func  = ev->sigev_notify_function;
 * >>             cookie->tc_value = ev->sigev_value;
 * >>             result = pthread_create(&p, attr, &thread_wrapper, cookie);
 * >>             if (result != EOK)
 * >>                 free(cookie);
 * >>         }
 * >>         if (!ev->sigev_notify_attributes)
 * >>             pthread_attr_destroy(&_attr);
 * >>     } else if ((ev->sigev_notify == SIGEV_SIGNAL ||
 * >>                 ev->sigev_notify == SIGEV_THREAD_ID) &&
 * >>                (ev->sigev_signo != 0)) {
 * >>         // When `sigev_signo == 0', the below syscalls would become no-ops
 * >>         // Or   rather,   would  "test if we're allowed to send a signal".
 * >>         siginfo_t info;
 * >>         bzero(&info, sizeof(siginfo_t));
 * >>         info.si_signo = ev->sigev_signo;
 * >>         info.si_code  = SI_ASYNCIO;
 * >>         info.si_pid   = getpid();
 * >>         info.si_uid   = getuid();
 * >>         info.si_value = ev->sigev_value;
 * >>         if (ev->sigev_notify == SIGEV_SIGNAL) {
 * >>             result = -sys_rt_sigqueueinfo(info.si_pid, info.si_signo, &info);
 * >>         } else {
 * >>             // PORTABILITY WARNING: Support for this case isn't implemented by
 * >>             //                      Glibc, which only supports `SIGEV_SIGNAL'!
 * >>             result = -sys_rt_tgsigqueueinfo(info.si_pid, ev->_sigev_tid,
 * >>                                             info.si_signo, &info);
 * >>         }
 * >>     }
 * >> done:
 * >>     return result;
 * >> }
 *
 * WARNING: Errors returned by `NOTIFY_COMPLETION()' are silently discarded!
 */


/*
 * WARNING: ONCE STARTED, YOU MUST NOT FREE THE BACKING STRUCTURE
 *          OF `struct aiocb' UNTIL `aio_error() != EINPROGRESS'!
 *
 * Until that point, the address of the structure itself may be
 * used internally as  part of linked  lists which will  become
 * corrupted if one  of their elements  isn't properly  removed
 * prior to being free'd.
 */


}



@@>> aio_read(3), aio_read64(3)
@@Begin an async `pread(2)' operation:
@@>> pread(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
@@>> NOTIFY_COMPLETION(&self->aio_sigevent);
@@When `pread(2)' would fail due to the type of file that `self->aio_fildes' is,
@@then `read(2)' is called instead (in which case `self->aio_offset' is ignored)
[[decl_include("<bits/crt/aiocb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_read")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_read64")]]
int aio_read([[nonnull]] struct aiocb *self);

@@>> aio_write(3), aio_write64(3)
@@Begin an async `pwrite(2)' operation:
@@>> pwrite(self->aio_fildes, self->aio_buf, self->aio_nbytes, self->aio_offset);
@@>> NOTIFY_COMPLETION(&self->aio_sigevent);
@@When `pwrite(2)' would fail due to the type of file that `self->aio_fildes' is,
@@then `write(2)' is called instead (in which case `self->aio_offset' is ignored)
[[decl_include("<bits/crt/aiocb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_write")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_write64")]]
int aio_write([[nonnull]] struct aiocb *self);


@@>> aio_fsync(3), aio_fsync64(3)
@@Begin an async `fsync(2)' or `fdatasync(2)' operation:
@@>> if (operation == O_SYNC) {
@@>>     fsync(self->aio_fildes);
@@>> } else if (operation == O_DSYNC) {
@@>>     fdatasync(self->aio_fildes);
@@>> }
@@>> NOTIFY_COMPLETION(&self->aio_sigevent);
@@@param: operation: One of `O_SYNC' or `O_DSYNC'
@@@return: 0 : Operation was started successfully
@@@return: -1: [errno=EAGAIN] Insufficient resources  (read:  `ENOMEM',  but  posix
@@                            didn't want to use that errno for whatever reason...)
@@@return: -1: [errno=EINVAL] `operation' was invalid
[[decl_include("<bits/crt/aiocb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_fsync")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_fsync64")]]
int aio_fsync($oflag_t operation, [[nonnull]] struct aiocb *self);


@@>> lio_listio(3), lio_listio64(3)
@@Execute/perform  a `list' of  AIO operations, where  each element of `list'
@@describes a read (`elem->aio_lio_opcode == LIO_READ'), write (`LIO_WRITE'),
@@or no-op (`LIO_NOP') operation.
@@
@@Once all operations are in progress, and `mode == LIO_WAIT', wait for all
@@of  them to complete  and return `0' on  success, or `-1'  is any of them
@@failed (individual errors/return values can be queried via `aio_error(3)'
@@and `aio_return(3)' on each of the elements from `list')
@@
@@Alternatively,  when `mode == LIO_NOWAIT', AIO is performed asynchronously,
@@and the function returns immediately once all operations have been started.
@@If  this was successful, return `0', or  `-1' if doing so failed (`errno').
@@Note that upon error here, no AIO operations will have been started, yet.
@@
@@Additionally, the given `sigev' (if non-NULL) will be assigned as a master
@@completion event that is only triggered  once _all_ of the AIO  operations
@@have completed. Note that in this case, `sigev' will/has always be invoked
@@if this function returns  `0', even if  any of the  AIO operations end  up
@@being canceled (s.a. `aio_cancel(3)') before they could be performed.
@@
@@@param: mode: One of `LIO_WAIT', `LIO_NOWAIT'
@@@return: 0 : Success
@@@return: -1: [errno=EAGAIN] Out of memory (read: `ENOMEM')
@@@return: -1: [errno=EINVAL] Invalid `mode'
@@@return: -1: [errno=EINTR]  When `mode == LIO_WAIT': Calling thread was interrupted.
@@                            Note that in  this case incomplete  AIO operations  will
@@                            continue to run and that  the caller should handle  this
@@                            case by looping over  all and using `aio_suspend(3)'  to
@@                            wait for each until doing so has succeeded at least once
@@                            for every entry.
@@@return: -1: [errno=EIO]    When `mode == LIO_WAIT': At least one of the operations
@@                            failed (s.a. `aio_error(3)')
[[decl_include("<features.h>", "<bits/os/sigevent.h>", "<bits/crt/aiocb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("lio_listio")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("lio_listio64")]]
int lio_listio(int mode, [[in(nent)]] struct aiocb *const list[__restrict_arr],
               __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sigev);


@@>> aio_error(3), aio_error64(3)
@@@return: 0 :          Operation completed
@@@return: EINPROGRESS: Async operation is still in progress (or pending)
@@@return: ECANCELED:   Operation was canceled (s.a. `aio_cancel(3)')
@@@return: EINVAL:      `self' is invalid, or its return value has already been read.
@@@return: * :          The   `errno'  with  which   the  async  operation  failed.
@@                      s.a. `pread(2)', `pwrite(2)', `fsync(2)' and `fdatasync(2)'
[[wunused, decl_include("<bits/types.h>", "<bits/crt/aiocb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_error")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_error64")]]
$errno_t aio_error([[in]] struct aiocb const *self);


@@>> aio_return(3), aio_return64(3)
@@@return: * : Return value of async `pread(2)', `pwrite(2)', `fsync(2)' or `fdatasync(2)'
@@@return: -1: [errno=<unchanged>] AIO operation failed (s.a. `aio_error(3)')
@@@return: -1: [errno=EINVAL]      `self' is invalid (including the case where `self' is still
@@                                 in progress), or  its return value  has already been  read.
[[decl_include("<bits/crt/aiocb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_return")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_return64")]]
$ssize_t aio_return([[inout]] struct aiocb *self);


@@>> aio_cancel(3), aio_cancel64(3)
@@Cancel  a specific AIO  operation (self != NULL),  or all operations currently
@@operating on a given `fd' (self !=  NULL && fd == self->aio_fildes). For  this
@@purpose,  it is undefined if the numerical value of `fd' is used for searching
@@active operations, or the pointed-to kernel object. As such, it is recommended
@@that you always aio_cancel the same fd as was also used when the AIO operation
@@was initiated.
@@NOTE: When `AIO_CANCELED' is returned, the completion event of `self',
@@      as  specified in `self->aio_sigevent'  will have been triggered,
@@      as completion events are triggered even for canceled operations.
@@@return: AIO_CANCELED:    At least one operation was canceled successfully
@@@return: AIO_NOTCANCELED: At least one operation was still in progress (s.a. `aio_error(3)')
@@                          This KOS implementation never returns  this value, as it  includes
@@                          facilities to force-abort any async operation (in the same vain as
@@                          sending SIGKILL can also force-aborts a process)
@@                          NOTE: In other implementations, this return value outweighs
@@                                `AIO_CANCELED'  and `AIO_ALLDONE' in face of multiple
@@                                AIO operations.
@@@return: AIO_ALLDONE:     Operations had  already been  completed
@@                          (or canceled) before the call was made.
@@@return: -1: [errno=EBADF]  `fd' is not a valid file descriptor
@@@return: -1: [errno=EINVAL] `self != NULL' and the given `fd' differs from `self->aio_fildes'
[[decl_include("<bits/types.h>", "<bits/crt/aiocb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_cancel")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_cancel64")]]
int aio_cancel([[fdarg]] $fd_t fd, [[nullable]] struct aiocb *self);


[[cp, ignore, nocrt, decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_suspend64")]]
int aio_suspendt32([[in(nent)]] struct aiocb const *const list[],
                   __STDC_INT_AS_SIZE_T nent,
                   struct $timespec32 const *__restrict timeout);


@@>> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
@@Suspend  the calling thread until at least  one of the given AIO operations
@@has been completed, a  signal is delivered to,  or (if non-NULL) the  given
@@`rel_timeout' expired.
@@@param: rel_timeout: The amount of time (relative) for which to wait.
@@@return: 0:  Success (At least one of the given AIO operations has completed)
@@@return: -1: [errno=EAGAIN] The time specified by `rel_timeout' has elapsed
@@@return: -1: [errno=EINTR]  A signal was delivered to the calling thread
[[cp, decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")( defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("aio_suspend64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")(!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && ( defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("aio_suspendt64", "__aio_suspend_time64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")( defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__) && ( defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("aio_suspend64t64", "__aio_suspend64_time64")]]
[[userimpl, requires($has_function(aio_suspendt32) || $has_function(aio_suspendt64))]]
int aio_suspend([[in(nent)]] struct aiocb const *const list[],
                __STDC_INT_AS_SIZE_T nent,
                struct timespec const *__restrict rel_timeout) {
@@pp_if $has_function(aio_suspendt32)@@
	struct timespec32 rel_timeout32;
	if (!rel_timeout)
		return aio_suspendt32(list, nent, NULL);
	rel_timeout32.tv_sec  = (time32_t)rel_timeout->tv_sec;
	rel_timeout32.tv_nsec = rel_timeout->tv_nsec;
	return aio_suspendt32(list, nent, &rel_timeout32);
@@pp_else@@
	struct timespec64 rel_timeout64;
	if (!rel_timeout)
		return aio_suspendt64(list, nent, NULL);
	rel_timeout64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	rel_timeout64.tv_nsec = rel_timeout->tv_nsec;
	return aio_suspendt64(list, nent, &rel_timeout64);
@@pp_endif@@
}



%
%#ifdef __USE_LARGEFILE64

[[preferred_off64_variant_of(aio_read)]]
[[decl_include("<bits/crt/aiocb.h>"), doc_alias("aio_read")]]
int aio_read64([[nonnull]] struct aiocb64 *self);

[[preferred_off64_variant_of(aio_write)]]
[[decl_include("<bits/crt/aiocb.h>"), doc_alias("aio_write")]]
int aio_write64([[nonnull]] struct aiocb64 *self);

[[preferred_off64_variant_of(aio_fsync)]]
[[decl_include("<bits/crt/aiocb.h>"), doc_alias("aio_fsync")]]
int aio_fsync64(int operation, [[nonnull]] struct aiocb64 *self);

[[preferred_off64_variant_of(lio_listio), doc_alias("lio_listio")]]
[[decl_include("<bits/os/sigevent.h>", "<bits/crt/aiocb.h>")]]
int lio_listio64(int mode, [[in(nent)]] struct aiocb64 *const list[__restrict_arr],
                 __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sigev);

[[wunused, preferred_off64_variant_of(aio_error), doc_alias("aio_error")]]
[[decl_include("<bits/crt/aiocb.h>")]]
int aio_error64([[in]] struct aiocb64 const *self);

[[preferred_off64_variant_of(aio_return), doc_alias("aio_return")]]
[[decl_include("<bits/crt/aiocb.h>")]]
$ssize_t aio_return64([[inout]] struct aiocb64 *self);

[[preferred_off64_variant_of(aio_cancel), doc_alias("aio_cancel")]]
[[decl_include("<bits/crt/aiocb.h>")]]
int aio_cancel64([[fdarg]] $fd_t fildes, [[nullable]] struct aiocb64 *self);

[[ignore, nocrt, doc_alias("aio_suspend")]]
[[decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_suspend")]]
[[alias("aio_suspend64")]]
int aio_suspend64t32([[in(nent)]] struct aiocb64 const *const list[],
                     __STDC_INT_AS_SIZE_T nent,
                     struct $timespec32 const *__restrict rel_timeout);

[[doc_alias("aio_suspend"), decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                             !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("aio_suspend64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && ( defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), alias("aio_suspendt64", "__aio_suspend_time64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                              defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  alias("aio_suspend64t64", "__aio_suspend64_time64")]]
[[userimpl, requires($has_function(aio_suspend64t32) || $has_function(aio_suspend64t64))]]
int aio_suspend64([[in(nent)]] struct aiocb64 const *const list[],
                  __STDC_INT_AS_SIZE_T nent,
                  struct timespec const *__restrict rel_timeout) {
@@pp_if $has_function(aio_suspend64t32)@@
	struct timespec32 rel_timeout32;
	if (!rel_timeout)
		return aio_suspend64t32(list, nent, NULL);
	rel_timeout32.tv_sec  = (time32_t)rel_timeout->tv_sec;
	rel_timeout32.tv_nsec = rel_timeout->tv_nsec;
	return aio_suspend64t32(list, nent, &rel_timeout32);
@@pp_else@@
	struct timespec64 rel_timeout64;
	if (!rel_timeout)
		return aio_suspend64t64(list, nent, NULL);
	rel_timeout64.tv_sec  = (time64_t)rel_timeout->tv_sec;
	rel_timeout64.tv_nsec = rel_timeout->tv_nsec;
	return aio_suspend64t64(list, nent, &rel_timeout64);
@@pp_endif@@
}

%#endif /* __USE_LARGEFILE64 */


%
%#ifdef __USE_TIME64

[[doc_alias("aio_suspend"), decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_kos_alias("libc_aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)), alias("aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ && ( defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)), alias("aio_suspend64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                               !defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__),  alias("aio_suspendt64", "__aio_suspend_time64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                                defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__),  alias("aio_suspend64t64", "__aio_suspend64_time64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__), crt_self_export]]
[[time64_export_as("__aio_suspend_time64")]]
[[userimpl, requires_function(aio_suspendt32)]]
int aio_suspendt64([[in(nent)]] struct aiocb const *const list[],
                   __STDC_INT_AS_SIZE_T nent,
                   struct timespec64 const *__restrict rel_timeout) {
	struct timespec32 rel_timeout32;
	if (!rel_timeout)
		return aio_suspendt32(list, nent, NULL);
	rel_timeout32.tv_sec  = (time32_t)rel_timeout->tv_sec;
	rel_timeout32.tv_nsec = rel_timeout->tv_nsec;
	return aio_suspendt32(list, nent, &rel_timeout32);
}

%
%#ifdef __USE_LARGEFILE64

[[doc_alias("aio_suspend"), decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alt_variant_of(aio_suspend)]]
[[if($extended_include_prefix("<bits/types.h>")                                            __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alt_variant_of(aio_suspend64)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__                                              ), preferred_alt_variant_of(aio_suspendt64)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__                                              ), alias("__aio_suspend_time64")]]
[[time64_export_alias("__aio_suspend64_time64")]]
[[userimpl, requires_function(aio_suspend64t32)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__), crt_self_export]]
int aio_suspend64t64([[in(nent)]] struct aiocb64 const *const list[],
                     __STDC_INT_AS_SIZE_T nent,
                     struct timespec64 const *__restrict rel_timeout) {
	struct timespec32 rel_timeout32;
	if (!rel_timeout)
		return aio_suspend64t32(list, nent, NULL);
	rel_timeout32.tv_sec  = (time32_t)rel_timeout->tv_sec;
	rel_timeout32.tv_nsec = rel_timeout->tv_nsec;
	return aio_suspend64t32(list, nent, &rel_timeout32);
}

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_TIME64 */



%
%#ifdef __USE_GNU

@@>> aio_init(3)
[[decl_include("<bits/crt/aioinit.h>")]]
void aio_init([[in]] struct aioinit const *init);

%#endif /* __USE_GNU */

%{

__SYSDECL_END
#endif /* __CC__ */

}
