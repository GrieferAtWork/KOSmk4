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
%[define_replacement(time_t = "__TM_TYPE(time)")]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]

%{
#include <features.h>
#include <bits/timeb.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

};

[[doc_alias("ftime"), ignore, nocrt, alias("ftime")]]
int crt_ftime32([[nonnull]] struct __timeb32 *timebuf);
[[doc_alias("ftime"), ignore, nocrt, alias("ftime64")]]
int crt_ftime64([[nonnull]] struct __timeb64 *timebuf);

%#ifdef __USE_DOS
%{
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
}

[[doc_alias("ftime"), ignore, nocrt, alias("_ftime32")]] void crt_dos_ftime32([[nonnull]] struct __timeb32 *timebuf);
[[doc_alias("ftime"), ignore, nocrt, alias("_ftime64")]] void crt_dos_ftime64([[nonnull]] struct __timeb64 *timebuf);
[[doc_alias("ftime"), ignore, nocrt, alias("_ftime32_s")]] errno_t crt_ftime32_s([[nonnull]] struct __timeb32 *timebuf);
[[doc_alias("ftime"), ignore, nocrt, alias("_ftime64_s")]] errno_t crt_ftime64_s([[nonnull]] struct __timeb64 *timebuf);


[[userimpl, doc_alias("ftime")]]
[[requires($has_function(crt_ftime32_s) || $has_function(crt_ftime32) ||
           $has_function(crt_dos_ftime64) || $has_function(crt_ftime64_s) ||
           $has_function(crt_ftime64))]]
void _ftime32([[nonnull]] struct __timeb32 *timebuf) {
@@pp_if $has_function(crt_ftime32_s)@@
	if unlikely(crt_ftime32_s(timebuf))
		memset(timebuf, 0, sizeof(*timebuf));
@@pp_elif $has_function(crt_ftime32)@@
	if unlikely(crt_ftime32(timebuf))
		memset(timebuf, 0, sizeof(*timebuf));
@@pp_elif $has_function(crt_dos_ftime64)@@
	struct __timeb64 temp;
	crt_dos_ftime64(&temp)
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
@@pp_else@@
	struct __timeb64 temp;
@@pp_if $has_function(crt_ftime64_s)@@
	if unlikely(crt_ftime64_s(&temp))
@@pp_else@@
	if unlikely(crt_ftime64(&temp))
@@pp_endif@@
	{
		memset(timebuf, 0, sizeof(*timebuf));
	} else {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
@@pp_endif@@
}

[[userimpl, doc_alias("ftime"), time64_variant_of(_ftime32)]]
[[requires($has_function(crt_ftime64_s) || $has_function(crt_ftime64) ||
           $has_function(crt_dos_ftime32) || $has_function(crt_ftime32_s) ||
           $has_function(crt_ftime32))]]
void _ftime64([[nonnull]] struct __timeb64 *timebuf) {
@@pp_if $has_function(crt_ftime64_s)@@
	if unlikely(crt_ftime64_s(timebuf))
		memset(timebuf,0,sizeof(*timebuf));
@@pp_elif $has_function(crt_ftime64)@@
	if unlikely(crt_ftime64(timebuf))
		memset(timebuf,0,sizeof(*timebuf));
@@pp_elif $has_function(crt_dos_ftime32)@@
	struct __timeb32 temp;
	crt_dos_ftime32(&temp)
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
@@pp_else@@
	struct __timeb32 temp;
@@pp_if $has_function(crt_ftime32_s)@@
	if unlikely(crt_ftime32_s(&temp))
@@pp_else@@
	if unlikely(crt_ftime32(&temp))
@@pp_endif@@
	{
		memset(timebuf, 0, sizeof(*timebuf));
	} else {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
@@pp_endif@@
}

[[doc_alias("ftime")]]
[[requires($has_function(crt_ftime32) || $has_function(crt_ftime64_s) ||
           $has_function(crt_ftime64) || $has_function(crt_dos_ftime32) ||
           $has_function(crt_dos_ftime64))]]
[[userimpl, impl_include("<parts/errno.h>")]]
errno_t _ftime32_s([[nonnull]] struct __timeb32 *timebuf) {
@@pp_if $has_function(crt_ftime32)@@
	return crt_ftime32(timebuf) ? 0 : __libc_geterrno_or(@EPERM@);
@@pp_elif $has_function(crt_ftime64_s) || $has_function(crt_ftime64)@@
	struct __timeb64 temp;
@@pp_if $has_function(crt_ftime64_s)@@
	errno_t error = crt_ftime64_s(&temp);
	if (error)
		return error;
@@pp_else@@
	if (crt_ftime64(&temp))
		return __libc_geterrno_or(@EPERM@);
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
	struct __timeb64 temp;
	crt_dos_ftime64(&temp);
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_endif@@
}

[[doc_alias("ftime"), time64_variant_of(_ftime32_s)]]
[[requires($has_function(crt_ftime64) || $has_function(crt_ftime32_s) ||
           $has_function(crt_ftime32) || $has_function(crt_dos_ftime64) ||
           $has_function(crt_dos_ftime32))]]
[[userimpl, impl_include("<parts/errno.h>")]]
errno_t _ftime64_s([[nonnull]] struct __timeb64 *timebuf) {
@@pp_if $has_function(crt_ftime64)@@
	return crt_ftime64(timebuf) ? 0 : __libc_geterrno_or(@EPERM@);
@@pp_elif $has_function(crt_ftime32_s) || $has_function(crt_ftime32)@@
	struct __timeb32 temp;
@@pp_if $has_function(crt_ftime32_s)@@
	errno_t error = crt_ftime32_s(&temp);
	if (error)
		return error;
@@pp_else@@
	if (crt_ftime32(&temp))
		return __libc_geterrno_or(@EPERM@);
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
	struct __timeb32 temp;
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
%
@@Fill in TIMEBUF with information about the current time
[[no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("ftime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("ftime")]]
[[requires($has_function(crt_ftime32_s) || $has_function(crt_ftime64_s) ||
           $has_function(crt_dos_ftime32) || $has_function(crt_dos_ftime64) ||
           $has_function(crt_ftime32) || $has_function(crt_ftime64))]]
[[userimpl, impl_include("<parts/errno.h>")]]
int ftime([[nonnull]] struct timeb *timebuf) {
@@pp_if $has_function(crt_ftime32_s) && !defined(__USE_TIME_BITS64)@@
	errno_t error = crt_ftime32_s(timebuf);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	}
	return (int)error;
@@pp_elif $has_function(crt_ftime64_s) && defined(__USE_TIME_BITS64)@@
	errno_t error = crt_ftime64_s(timebuf);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	}
	return (int)error;
@@pp_elif $has_function(crt_dos_ftime32) && !defined(__USE_TIME_BITS64)@@
	crt_dos_ftime32(&temp);
	return 0;
@@pp_elif $has_function(crt_dos_ftime64) && defined(__USE_TIME_BITS64)@@
	crt_dos_ftime64(&temp);
	return 0;
@@pp_elif $has_function(crt_ftime32)@@
	struct __timeb32 temp;
	int error = crt_ftime32(&temp);
	if likely(!error) {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
@@pp_elif $has_function(crt_ftime64)@@
	struct __timeb64 temp;
	int error = crt_ftime64(&temp);
	if likely(!error) {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
@@pp_elif $has_function(crt_ftime32_s)@@
	struct __timeb32 temp;
	errno_t error = crt_ftime32_s(&temp);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	} else {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return (int)error;
@@pp_elif $has_function(crt_ftime64_s)@@
	struct __timeb64 temp;
	errno_t error = crt_ftime64_s(&temp);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	} else {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return (int)error;
@@pp_elif $has_function(crt_dos_ftime32)@@
	struct __timeb32 temp;
	crt_dos_ftime32(&temp);
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
@@pp_else@@
	struct __timeb64 temp;
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
[[time64_variant_of(ftime)]]
[[requires($has_function(crt_ftime64_s) || $has_function(crt_dos_ftime64) ||
           $has_function(crt_ftime32) || $has_function(crt_ftime32_s) ||
           $has_function(crt_dos_ftime32))]]
[[userimpl, impl_include("<parts/errno.h>")]]
int ftime64([[nonnull]] struct timeb64 *timebuf) {
@@pp_if $has_function(crt_ftime64_s)@@
	errno_t error = crt_ftime64_s(timebuf);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	}
	return (int)error;
@@pp_elif $has_function(crt_dos_ftime64)@@
	crt_dos_ftime64(&temp);
	return 0;
@@pp_elif $has_function(crt_ftime32)@@
	struct __timeb32 temp;
	int error = crt_ftime32(&temp);
	if likely(!error) {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
@@pp_elif $has_function(crt_ftime32_s)@@
	struct __timeb32 temp;
	errno_t error = crt_ftime32_s(&temp);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	} else {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return (int)error;
@@pp_else@@
	struct __timeb32 temp;
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

#endif /* __CC__ */

__SYSDECL_END

}