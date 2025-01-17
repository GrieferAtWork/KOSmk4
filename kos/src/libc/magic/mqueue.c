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
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/mqueue.h) */
/* (#) Portability: DragonFly BSD (/include/mqueue.h) */
/* (#) Portability: FreeBSD       (/include/mqueue.h) */
/* (#) Portability: GNU C Library (/rt/mqueue.h) */
/* (#) Portability: GNU Hurd      (/usr/include/mqueue.h) */
/* (#) Portability: NetBSD        (/include/mqueue.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/mqueue.h) */
/* (#) Portability: diet libc     (/include/mqueue.h) */
/* (#) Portability: libc6         (/include/mqueue.h) */
/* (#) Portability: musl libc     (/include/mqueue.h) */
/* (#) Portability: uClibc        (/include/mqueue.h) */
}

%[default:section(".text.crt{|.dos}.utility.mqueue")]

%[define_decl_include("<bits/os/sigevent.h>": ["struct sigevent"])]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/os/mqueue.h>
)]%[insert:prefix(
#include <bits/os/sigevent.h> /* struct sigevent */
)]%[insert:prefix(
#include <bits/os/timespec.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#include <fcntl.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __sigevent_t_defined
#define __sigevent_t_defined
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */

typedef __mqd_t mqd_t;

}

%[define_decl_include_implication("<bits/os/mqueue.h>" => ["<bits/types.h>"])]
%[define_decl_include("<bits/os/mqueue.h>": ["__mqd_t", "struct mq_attr"])]
%[define_decl_include("<bits/os/sigevent.h>": ["struct sigevent"])]

%[define_type_class(__mqd_t = "TD")]
%[define_replacement(mqd_t = __mqd_t)]
%[define_replacement(mq_attr = mq_attr)]


@@>> mq_open(3)
[[cp, wunused, vartypes($mode_t)]]
[[decl_include("<bits/os/mqueue.h>")]]
mqd_t mq_open([[in]] char const *__restrict name,
              $oflag_t oflags, ...);


@@>> mq_close(3)
[[nothrow, decl_include("<bits/os/mqueue.h>")]]
int mq_close(mqd_t mqdes);

@@>> mq_getattr(3)
[[decl_include("<bits/os/mqueue.h>")]]
int mq_getattr(mqd_t mqdes,
               [[out]] struct mq_attr *__restrict mqstat);

@@>> mq_setattr(3)
[[decl_include("<bits/os/mqueue.h>")]]
int mq_setattr(mqd_t mqdes,
               [[in]] struct mq_attr const *__restrict mqstat,
               [[out_opt]] struct mq_attr *__restrict old_mqstat);

@@>> mq_unlink(3)
[[decl_include("<bits/os/mqueue.h>")]]
int mq_unlink([[in]] char const *name);

@@>> mq_notify(3)
[[decl_include("<bits/os/mqueue.h>", "<bits/os/sigevent.h>")]]
int mq_notify(mqd_t mqdes,
              struct sigevent const *notification);


@@>> mq_receive(3)
[[cp, decl_include("<bits/os/mqueue.h>")]]
$ssize_t mq_receive(mqd_t mqdes,
                    [[out(return <= msg_len)]] char *__restrict msg_ptr,
                    $size_t msg_len, unsigned int *pmsg_prio);

@@>> mq_send(3)
[[cp, decl_include("<bits/os/mqueue.h>")]]
int mq_send(mqd_t mqdes,
            [[in(msg_len)]] char const *msg_ptr,
            $size_t msg_len, unsigned int msg_prio);


%
%#ifdef __USE_XOPEN2K


[[ignore, nocrt, alias("mq_timedreceive"), doc_alias("mq_timedreceive")]]
[[cp, decl_include("<bits/os/timespec.h>", "<bits/os/mqueue.h>")]]
$ssize_t mq_timedreceive32(mqd_t mqdes,
                           [[out(return <= msg_len)]] char *__restrict msg_ptr, $size_t msg_len, unsigned int *pmsg_prio,
                           [[in]] struct $timespec32 const *__restrict abs_timeout);
[[ignore, nocrt, alias("mq_timedsend"), doc_alias("mq_timedsend")]]
[[cp, decl_include("<bits/os/timespec.h>", "<bits/os/mqueue.h>")]]
int mq_timedsend32(mqd_t mqdes,
                   [[out(return <= msg_len)]] char const *msg_ptr, $size_t msg_len, unsigned int msg_prio,
                   [[in]] struct $timespec32 const *abs_timeout);


@@>> mq_timedreceive(3), mq_timedreceive64(3)
[[cp, decl_include("<bits/os/timespec.h>", "<bits/os/mqueue.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mq_timedreceive")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mq_timedreceive64", "____mq_timedreceive_time64")]]
[[userimpl, requires($has_function(mq_timedreceive32) || $has_function(mq_timedreceive64))]]
$ssize_t mq_timedreceive(mqd_t mqdes,
                         [[out(return <= msg_len)]] char *__restrict msg_ptr, $size_t msg_len,
                         [[out_opt]] unsigned int *pmsg_prio,
                         [[in]] struct timespec const *__restrict abs_timeout) {
@@pp_if $has_function(mq_timedreceive32)@@
	struct timespec32 abs_timeout32;
	abs_timeout32.tv_sec  = (time32_t)abs_timeout->tv_sec;
	abs_timeout32.tv_nsec = abs_timeout->tv_nsec;
	return mq_timedreceive32(mqdes, msg_ptr, msg_len, pmsg_prio, &abs_timeout32);
@@pp_else@@
	struct timespec64 abs_timeout64;
	abs_timeout64.tv_sec  = (time64_t)abs_timeout->tv_sec;
	abs_timeout64.tv_nsec = abs_timeout->tv_nsec;
	return mq_timedreceive64(mqdes, msg_ptr, msg_len, pmsg_prio, &abs_timeout64);
@@pp_endif@@
}


@@>> mq_timedsend(3), mq_timedsend64(3)
[[cp, decl_include("<bits/os/timespec.h>", "<bits/os/mqueue.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mq_timedsend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("mq_timedsend64", "__mq_timedsend_time64")]]
[[userimpl, requires($has_function(mq_timedsend32) || $has_function(mq_timedsend64))]]
int mq_timedsend(mqd_t mqdes,
                 [[in(msg_len)]] char const *msg_ptr, $size_t msg_len, unsigned int msg_prio,
                 [[in]] struct timespec const *abs_timeout) {
@@pp_if $has_function(mq_timedsend32)@@
	struct timespec32 abs_timeout32;
	abs_timeout32.tv_sec  = (time32_t)abs_timeout->tv_sec;
	abs_timeout32.tv_nsec = abs_timeout->tv_nsec;
	return mq_timedsend32(mqdes, msg_ptr, msg_len, msg_prio, &abs_timeout32);
@@pp_else@@
	struct timespec64 abs_timeout64;
	abs_timeout64.tv_sec  = (time64_t)abs_timeout->tv_sec;
	abs_timeout64.tv_nsec = abs_timeout->tv_nsec;
	return mq_timedsend64(mqdes, msg_ptr, msg_len, msg_prio, &abs_timeout64);
@@pp_endif@@
}


%
%#ifdef __USE_TIME64

[[cp, decl_include("<bits/os/timespec.h>", "<bits/os/mqueue.h>")]]
[[preferred_time64_variant_of(mq_timedreceive), doc_alias("mq_timedreceive")]]
[[time64_export_alias("__mq_timedreceive_time64")]]
[[userimpl, requires_function(mq_timedreceive32)]]
$ssize_t mq_timedreceive64(mqd_t mqdes,
                           [[out(return <= msg_len)]] char *__restrict msg_ptr,
                           $size_t msg_len, unsigned int *pmsg_prio,
                           [[in]] struct timespec64 const *__restrict abs_timeout) {
	struct timespec32 abs_timeout32;
	abs_timeout32.tv_sec  = (time32_t)abs_timeout->tv_sec;
	abs_timeout32.tv_nsec = abs_timeout->tv_nsec;
	return mq_timedreceive32(mqdes, msg_ptr, msg_len, pmsg_prio, &abs_timeout32);
}

[[cp, decl_include("<bits/os/timespec.h>", "<bits/os/mqueue.h>")]]
[[preferred_time64_variant_of(mq_timedsend), doc_alias("mq_timedsend")]]
[[time64_export_alias("__mq_timedsend_time64")]]
[[userimpl, requires_function(mq_timedsend32)]]
int mq_timedsend64(mqd_t mqdes,
                   [[in(msg_len)]] char const *msg_ptr,
                   $size_t msg_len, unsigned int msg_prio,
                   [[in]] struct timespec64 const *abs_timeout) {
	struct timespec32 abs_timeout32;
	abs_timeout32.tv_sec  = (time32_t)abs_timeout->tv_sec;
	abs_timeout32.tv_nsec = abs_timeout->tv_nsec;
	return mq_timedsend32(mqdes, msg_ptr, msg_len, msg_prio, &abs_timeout32);
}

%#endif /* __USE_TIME64 */
%#endif /* __USE_XOPEN2K */


%{

__SYSDECL_END
#endif /* __CC__ */

}
