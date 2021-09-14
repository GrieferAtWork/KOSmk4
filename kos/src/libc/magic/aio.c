/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: POSIX.1-2001 (Issue 5, IEEE Std 1003.1-2001) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/aio.h) */
/* (#) Portability: GNU C Library (/rt/aio.h) */
/* (#) Portability: NetBSD        (/include/aio.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/aio.h) */
/* (#) Portability: musl libc     (/include/aio.h) */
}

%[default:section(".text.crt{|.dos}.utility.aio")]

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

#ifdef __USE_GLIBC
#include <sys/types.h>
#endif /* __USE_GLIBC */

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
#define LIO_READ  __LIO_READ  /* ??? */
#endif /* !LIO_READ && __LIO_READ */
#if !defined(LIO_WRITE) && defined(__LIO_WRITE)
#define LIO_WRITE __LIO_WRITE /* ??? */
#endif /* !LIO_WRITE && __LIO_WRITE */
#if !defined(LIO_NOP) && defined(__LIO_NOP)
#define LIO_NOP   __LIO_NOP   /* ??? */
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
#define __sigevent_t_defined 1
typedef struct sigevent sigevent_t;
#endif /* !__sigevent_t_defined */

}

%[define_replacement(aiocb = aiocb)]
%[define_replacement(aiocb64 = aiocb64)]
%[define_c_language_keyword(__restrict_arr)]



@@>> aio_read(3)
[[no_crt_self_import, decl_include("<bits/crt/aiocb.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_read64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_read")]]
int aio_read([[nonnull]] struct aiocb *aiocbp);

@@>> aio_write(3)
[[no_crt_self_import, decl_include("<bits/crt/aiocb.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_write64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_write")]]
int aio_write([[nonnull]] struct aiocb *aiocbp);


[[decl_include("<features.h>", "<bits/os/sigevent.h>", "<bits/crt/aiocb.h>")]]
int lio_listio(int mode, [[nonnull]] struct aiocb *const list[__restrict_arr],
               __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig);


@@>> aio_error(3)
[[wunused, no_crt_self_import, decl_include("<bits/crt/aiocb.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_error64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_error")]]
int aio_error([[nonnull]] struct aiocb const *aiocbp);


@@>> aio_return(3)
[[no_crt_self_import, decl_include("<bits/crt/aiocb.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_return64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_return")]]
$ssize_t aio_return([[nonnull]] struct aiocb *aiocbp);


@@>> aio_cancel(3)
[[no_crt_self_import, decl_include("<bits/types.h>", "<bits/crt/aiocb.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_cancel64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_cancel")]]
int aio_cancel($fd_t fildes, [[nonnull]] struct aiocb *aiocbp);


[[cp, ignore, nocrt, decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_suspend64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_suspend")]]
int aio_suspendt32([[nonnull]] struct aiocb const *const list[],
                   __STDC_INT_AS_SIZE_T nent,
                   struct $timespec32 const *__restrict timeout);


@@>> aio_suspend(3), aio_suspend64(3), aio_suspendt64(3), aio_suspend64t64(3)
[[cp, no_crt_self_import, decl_include("<features.h>", "<bits/crt/aiocb.h>", "<bits/os/timespec.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64) &&  defined(__USE_TIME_BITS64)), preferred_alias("aio_suspend64t64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64) &&  defined(__USE_TIME_BITS64)), preferred_alias("aio_suspendt64")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64) && !defined(__USE_TIME_BITS64)), preferred_alias("aio_suspend64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64) && !defined(__USE_TIME_BITS64)), preferred_alias("aio_suspend")]]
[[userimpl, requires($has_function(aio_suspendt32) || $has_function(aio_suspendt64))]]
int aio_suspend([[nonnull]] struct aiocb const *const list[],
                __STDC_INT_AS_SIZE_T nent,
                struct timespec const *__restrict timeout) {
@@pp_if $has_function(aio_suspendt32)@@
	struct timespec32 timeout32;
	if (!timeout)
		return aio_suspendt32(list, nent, NULL);
	timeout32.@tv_sec@  = (time32_t)timeout->@tv_sec@;
	timeout32.@tv_nsec@ = timeout->@tv_nsec@;
	return aio_suspendt32(list, nent, &timeout32);
@@pp_else@@
	struct timespec64 timeout64;
	if (!timeout)
		return aio_suspendt64(list, nent, NULL);
	timeout64.@tv_sec@  = (time64_t)timeout->@tv_sec@;
	timeout64.@tv_nsec@ = timeout->@tv_nsec@;
	return aio_suspendt64(list, nent, &timeout64);
@@pp_endif@@
}


@@>> aio_fsync(3)
[[no_crt_self_import, decl_include("<bits/types.h>", "<bits/crt/aiocb.h>")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_fsync64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_fsync")]]
int aio_fsync(int operation, [[nonnull]] struct aiocb *aiocbp);


%
%#ifdef __USE_LARGEFILE64

[[preferred_off64_variant_of(aio_read), doc_alias("aio_read")]]
int aio_read64([[nonnull]] struct aiocb64 *aiocbp);

[[preferred_off64_variant_of(aio_write), doc_alias("aio_write")]]
int aio_write64([[nonnull]] struct aiocb64 *aiocbp);

[[preferred_off64_variant_of(aio_write), doc_alias("aio_write")]]
int lio_listio64(int mode, [[nonnull]] struct aiocb64 *const list[__restrict_arr],
                 __STDC_INT_AS_SIZE_T nent, struct sigevent *__restrict sig);

[[wunused, preferred_off64_variant_of(aio_error), doc_alias("aio_error")]]
int aio_error64([[nonnull]] struct aiocb64 const *aiocbp);

[[preferred_off64_variant_of(aio_return), doc_alias("aio_return")]]
$ssize_t aio_return64([[nonnull]] struct aiocb64 *aiocbp);

[[preferred_off64_variant_of(aio_cancel), doc_alias("aio_cancel")]]
int aio_cancel64($fd_t fildes, [[nonnull]] struct aiocb64 *aiocbp);

[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("aio_suspend")]]
[[ignore, nocrt, doc_alias("aio_suspend"), alias("aio_suspend64")]]
int aio_suspend64t32([[nonnull]] struct aiocb64 const *const list[],
                     __STDC_INT_AS_SIZE_T nent,
                     struct $timespec32 const *__restrict timeout);

[[no_crt_self_import, doc_alias("aio_suspend")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), crt_intern_kos_alias("libc_aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), preferred_alias("aio_suspend")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && ( defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)), preferred_alias("aio_suspendt64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                             !defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  preferred_alias("aio_suspend64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")                                              defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__),  preferred_alias("aio_suspend64t64")]]
[[userimpl, requires($has_function(aio_suspend64t32) || $has_function(aio_suspend64t64))]]
int aio_suspend64([[nonnull]] struct aiocb64 const *const list[],
                  __STDC_INT_AS_SIZE_T nent,
                  struct timespec const *__restrict timeout) {
@@pp_if $has_function(aio_suspend64t32)@@
	struct timespec32 timeout32;
	if (!timeout)
		return aio_suspend64t32(list, nent, NULL);
	timeout32.@tv_sec@  = (time32_t)timeout->@tv_sec@;
	timeout32.@tv_nsec@ = timeout->@tv_nsec@;
	return aio_suspend64t32(list, nent, &timeout32);
@@pp_else@@
	struct timespec64 timeout64;
	if (!timeout)
		return aio_suspend64t64(list, nent, NULL);
	timeout64.@tv_sec@  = (time64_t)timeout->@tv_sec@;
	timeout64.@tv_nsec@ = timeout->@tv_nsec@;
	return aio_suspend64t64(list, nent, &timeout64);
@@pp_endif@@
}

[[preferred_off64_variant_of(aio_fsync), doc_alias("aio_fsync")]]
int aio_fsync64(int operation, [[nonnull]] struct aiocb64 *aiocbp);

%#endif /* __USE_LARGEFILE64 */


%
%#ifdef __USE_TIME64

[[no_crt_self_import, time64_variant_of(aio_suspend), doc_alias("aio_suspend")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_kos_alias("libc_aio_suspend")]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("aio_suspend64t64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("aio_suspendt64")]]
[[userimpl, requires_function(aio_suspendt32)]]
int aio_suspendt64([[nonnull]] struct aiocb const *const list[],
                   __STDC_INT_AS_SIZE_T nent,
                   struct timespec64 const *__restrict timeout) {
	struct timespec32 timeout32;
	if (!timeout)
		return aio_suspendt32(list, nent, NULL);
	timeout32.@tv_sec@  = (time32_t)timeout->@tv_sec@;
	timeout32.@tv_nsec@ = timeout->@tv_nsec@;
	return aio_suspendt32(list, nent, &timeout32);
}

%
%#ifdef __USE_LARGEFILE64

[[no_crt_self_import, doc_alias("aio_suspend")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__ && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alt_variant_of(aio_suspend)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alt_variant_of(aio_suspendt64)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alt_variant_of(aio_suspend64)]]
[[userimpl, requires_function(aio_suspend64t32)]]
int aio_suspend64t64([[nonnull]] struct aiocb64 const *const list[],
                     __STDC_INT_AS_SIZE_T nent,
                     struct timespec64 const *__restrict timeout) {
	struct timespec32 timeout32;
	if (!timeout)
		return aio_suspend64t32(list, nent, NULL);
	timeout32.@tv_sec@  = (time32_t)timeout->@tv_sec@;
	timeout32.@tv_nsec@ = timeout->@tv_nsec@;
	return aio_suspend64t32(list, nent, &timeout32);
}

%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_TIME64 */



%
%#ifdef __USE_GNU

@@>> aio_init(3)
[[decl_include("<bits/crt/aioinit.h>")]]
void aio_init([[nonnull]] struct aioinit const *init);

%#endif /* __USE_GNU */

%{

__SYSDECL_END
#endif /* __CC__ */

}

