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
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/timeb.h) */
/* (#) Portability: DJGPP         (/include/sys/timeb.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/timeb.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/timeb.h) */
/* (#) Portability: FreeBSD       (/sys/sys/timeb.h) */
/* (#) Portability: GNU C Library (/time/sys/timeb.h) */
/* (#) Portability: MSVC          (/include/sys/timeb.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/timeb.h) */
/* (#) Portability: NetBSD        (/sys/sys/timeb.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/timeb.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/timeb.h) */
/* (#) Portability: Windows Kits  (/ucrt/sys/timeb.h) */
/* (#) Portability: diet libc     (/include/sys/timeb.h) */
/* (#) Portability: libc4/5       (/include/sys/timeb.h) */
/* (#) Portability: mintlib       (/include/sys/timeb.h) */
/* (#) Portability: musl libc     (/include/sys/timeb.h) */
/* (#) Portability: uClibc        (/include/sys/timeb.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(time_t = "__time_t")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(timeb32 = __timeb32)]
%[define_replacement(timeb64 = __timeb64)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/os/timeb.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */

};

[[doc_alias("ftime"), ignore, nocrt, alias("ftime")]]
[[decl_include("<bits/os/timeb.h>")]]
int crt_ftime32([[out]] struct $timeb32 *timebuf);

[[doc_alias("ftime"), ignore, nocrt, alias("ftime64")]]
[[decl_include("<bits/os/timeb.h>")]]
int crt_ftime64([[out]] struct $timeb64 *timebuf);

%#ifdef __USE_DOS
%{
#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
}

[[doc_alias("ftime"), ignore, nocrt, alias("_ftime32", "_ftime")]]
[[decl_include("<bits/os/timeb.h>")]]
void crt_dos_ftime32([[out]] struct $timeb32 *timebuf);

[[doc_alias("ftime"), ignore, nocrt, alias("_ftime64")]]
[[decl_include("<bits/os/timeb.h>")]]
void crt_dos_ftime64([[out]] struct $timeb64 *timebuf);

[[doc_alias("ftime"), ignore, nocrt, alias("_ftime32_s")]]
[[decl_include("<bits/os/timeb.h>", "<bits/types.h>")]]
$errno_t crt_ftime32_s([[out]] struct $timeb32 *timebuf);

[[doc_alias("ftime"), ignore, nocrt, alias("_ftime64_s")]]
[[decl_include("<bits/os/timeb.h>", "<bits/types.h>")]]
$errno_t crt_ftime64_s([[out]] struct $timeb64 *timebuf);



[[decl_include("<bits/os/timeb.h>")]]
[[userimpl, doc_alias("ftime"), export_alias("_ftime")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_ftime64")]]
[[requires($has_function(crt_ftime32_s) || $has_function(crt_ftime32) ||
           $has_function(crt_dos_ftime64) || $has_function(crt_ftime64_s) ||
           $has_function(crt_ftime64))]]
void _ftime32([[out]] struct $timeb32 *timebuf) {
@@pp_if $has_function(crt_ftime32_s)@@
	if unlikely(crt_ftime32_s(timebuf))
		bzero(timebuf, sizeof(*timebuf));
@@pp_elif $has_function(crt_ftime32)@@
	if unlikely(crt_ftime32(timebuf))
		bzero(timebuf, sizeof(*timebuf));
@@pp_elif $has_function(crt_dos_ftime64)@@
	struct timeb64 temp;
	crt_dos_ftime64(&temp)
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
@@pp_else@@
	struct timeb64 temp;
@@pp_if $has_function(crt_ftime64_s)@@
	if unlikely(crt_ftime64_s(&temp))
@@pp_else@@
	if unlikely(crt_ftime64(&temp))
@@pp_endif@@
	{
		bzero(timebuf, sizeof(*timebuf));
	} else {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
@@pp_endif@@
}

[[decl_include("<bits/os/timeb.h>")]]
[[userimpl, preferred_time64_variant_of(_ftime32), doc_alias("_ftime32")]]
[[requires($has_function(crt_ftime64_s) || $has_function(crt_ftime64) ||
           $has_function(crt_dos_ftime32) || $has_function(crt_ftime32_s) ||
           $has_function(crt_ftime32))]]
void _ftime64([[out]] struct $timeb64 *timebuf) {
@@pp_if $has_function(crt_ftime64_s)@@
	if unlikely(crt_ftime64_s(timebuf))
		bzero(timebuf, sizeof(*timebuf));
@@pp_elif $has_function(crt_ftime64)@@
	if unlikely(crt_ftime64(timebuf))
		bzero(timebuf, sizeof(*timebuf));
@@pp_elif $has_function(crt_dos_ftime32)@@
	struct timeb32 temp;
	crt_dos_ftime32(&temp)
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
@@pp_else@@
	struct timeb32 temp;
@@pp_if $has_function(crt_ftime32_s)@@
	if unlikely(crt_ftime32_s(&temp))
@@pp_else@@
	if unlikely(crt_ftime32(&temp))
@@pp_endif@@
	{
		bzero(timebuf, sizeof(*timebuf));
	} else {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
@@pp_endif@@
}

[[decl_include("<bits/os/timeb.h>", "<bits/types.h>"), doc_alias("ftime")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("_ftime64_s")]]
[[requires($has_function(crt_ftime32) || $has_function(crt_ftime64_s) ||
           $has_function(crt_ftime64) || $has_function(crt_dos_ftime32) ||
           $has_function(crt_dos_ftime64))]]
[[userimpl, impl_include("<libc/errno.h>")]]
errno_t _ftime32_s([[out]] struct $timeb32 *timebuf) {
@@pp_if $has_function(crt_ftime32)@@
	if likely(crt_ftime32(timebuf) == 0)
		return 0;
@@pp_ifdef EPERM@@
	return __libc_geterrno_or(EPERM);
@@pp_else@@
	return __libc_geterrno_or(1);
@@pp_endif@@
@@pp_elif $has_function(crt_ftime64_s) || $has_function(crt_ftime64)@@
	struct timeb64 temp;
@@pp_if $has_function(crt_ftime64_s)@@
	errno_t error = crt_ftime64_s(&temp);
	if unlikely(error)
		return error;
@@pp_else@@
	if unlikely(crt_ftime64(&temp) != 0) {
@@pp_ifdef EPERM@@
		return __libc_geterrno_or(EPERM);
@@pp_else@@
		return __libc_geterrno_or(1);
@@pp_endif@@
	}
@@pp_endif@@
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_elif $has_function(crt_dos_ftime32)@@
	crt_dos_ftime32(timebuf);
	return 0;
@@pp_else@@
	struct timeb64 temp;
	crt_dos_ftime64(&temp);
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_endif@@
}

[[decl_include("<bits/os/timeb.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(_ftime32_s), doc_alias("ftime")]]
[[requires($has_function(crt_ftime64) || $has_function(crt_ftime32_s) ||
           $has_function(crt_ftime32) || $has_function(crt_dos_ftime64) ||
           $has_function(crt_dos_ftime32))]]
[[userimpl, impl_include("<libc/errno.h>")]]
errno_t _ftime64_s([[out]] struct $timeb64 *timebuf) {
@@pp_if $has_function(crt_ftime64)@@
	if likely(crt_ftime64(timebuf) == 0)
		return 0;
@@pp_ifdef EPERM@@
	return __libc_geterrno_or(EPERM);
@@pp_else@@
	return __libc_geterrno_or(1);
@@pp_endif@@
@@pp_elif $has_function(crt_ftime32_s) || $has_function(crt_ftime32)@@
	struct timeb32 temp;
@@pp_if $has_function(crt_ftime32_s)@@
	errno_t error = crt_ftime32_s(&temp);
	if unlikely(error)
		return error;
@@pp_else@@
	if unlikely(crt_ftime32(&temp)) {
@@pp_ifdef EPERM@@
		return __libc_geterrno_or(EPERM);
@@pp_else@@
		return __libc_geterrno_or(1);
@@pp_endif@@
	}
@@pp_endif@@
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_elif $has_function(crt_dos_ftime64)@@
	crt_dos_ftime64(timebuf);
	return 0;
@@pp_else@@
	struct timeb32 temp;
	crt_dos_ftime32(&temp);
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_endif@@
}

%#endif /* __USE_DOS */


%
%

@@>> ftime(3), ftime64(3)
@@Write information about the current time to `*timebuf'
@@@return: 0 : Success
@@@return: -1: Error (s.a. `errno')
[[decl_include("<bits/os/timeb.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ftime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("ftime64")]]
[[requires($has_function(crt_ftime32_s) || $has_function(crt_ftime64_s) ||
           $has_function(crt_dos_ftime32) || $has_function(crt_dos_ftime64) ||
           $has_function(crt_ftime32) || $has_function(crt_ftime64))]]
[[userimpl, impl_include("<features.h>", "<libc/errno.h>")]]
int ftime([[out]] struct timeb *timebuf) {
@@pp_if $has_function(crt_ftime32_s) && !defined(__USE_TIME_BITS64)@@
	errno_t error = crt_ftime32_s(timebuf);
	if unlikely(error)
		error = libc_seterrno(error);
	return (int)error;
@@pp_elif $has_function(crt_ftime64_s) && defined(__USE_TIME_BITS64)@@
	errno_t error = crt_ftime64_s(timebuf);
	if unlikely(error)
		error = libc_seterrno(error);
	return (int)error;
@@pp_elif $has_function(crt_dos_ftime32) && !defined(__USE_TIME_BITS64)@@
	crt_dos_ftime32(&temp);
	return 0;
@@pp_elif $has_function(crt_dos_ftime64) && defined(__USE_TIME_BITS64)@@
	crt_dos_ftime64(&temp);
	return 0;
@@pp_elif $has_function(crt_ftime32)@@
	struct timeb32 temp;
	int error = crt_ftime32(&temp);
	if likely(!error) {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
@@pp_elif $has_function(crt_ftime64)@@
	struct timeb64 temp;
	int error = crt_ftime64(&temp);
	if likely(!error) {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
@@pp_elif $has_function(crt_ftime32_s)@@
	struct timeb32 temp;
	errno_t error = crt_ftime32_s(&temp);
	if unlikely(error) {
		error = libc_seterrno(error);
	} else {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return (int)error;
@@pp_elif $has_function(crt_ftime64_s)@@
	struct timeb64 temp;
	errno_t error = crt_ftime64_s(&temp);
	if unlikely(error) {
		error = libc_seterrno(error);
	} else {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return (int)error;
@@pp_elif $has_function(crt_dos_ftime32)@@
	struct timeb32 temp;
	crt_dos_ftime32(&temp);
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_else@@
	struct timeb64 temp;
	crt_dos_ftime64(&temp);
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[decl_include("<bits/os/timeb.h>")]]
[[preferred_time64_variant_of(ftime), doc_alias("ftime")]]
[[requires($has_function(crt_ftime64_s) || $has_function(crt_dos_ftime64) ||
           $has_function(crt_ftime32) || $has_function(crt_ftime32_s) ||
           $has_function(crt_dos_ftime32))]]
[[userimpl, impl_include("<libc/errno.h>")]]
int ftime64([[out]] struct timeb64 *timebuf) {
@@pp_if $has_function(crt_ftime64_s)@@
	errno_t error = crt_ftime64_s(timebuf);
	if unlikely(error) {
		error = libc_seterrno(error);
	}
	return (int)error;
@@pp_elif $has_function(crt_dos_ftime64)@@
	crt_dos_ftime64(&temp);
	return 0;
@@pp_elif $has_function(crt_ftime32)@@
	struct timeb32 temp;
	int error = crt_ftime32(&temp);
	if likely(!error) {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
@@pp_elif $has_function(crt_ftime32_s)@@
	struct timeb32 temp;
	errno_t error = crt_ftime32_s(&temp);
	if unlikely(error) {
		error = libc_seterrno(error);
	} else {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return (int)error;
@@pp_else@@
	struct timeb32 temp;
	crt_dos_ftime32(&temp);
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_endif@@
}
%#endif /* __USE_TIME64 */



%{

__SYSDECL_END
#endif /* __CC__ */

}
