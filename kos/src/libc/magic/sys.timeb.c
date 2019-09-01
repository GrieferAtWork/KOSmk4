/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(time_t = __TM_TYPE(time))]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]

%{
#include <features.h>
#include <bits/types.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */

#if __TM_SIZEOF(TIME) <= 4
#define __timeb64  __timeb_alt
#define __timeb32  timeb
#else
#define __timeb64  timeb
#define __timeb32  __timeb_alt
#endif

#ifdef __USE_TIME64
#ifndef __time64_t_defined
#define __time64_t_defined 1
typedef __time64_t time64_t;
#endif /* !__time64_t_defined */
#if __TM_SIZEOF(TIME) <= 4
#define __timeb_alt timeb64
#else
#define timeb64     timeb
#endif
#endif /* __USE_TIME64 */


}%[push_macro @undef { time millitm timezone dstflag }]%{
struct timeb {
#if __TM_SIZEOF(TIME) <= 4
	__time64_t      time;     /* Seconds since epoch, as from `time'. */
#else
	__time32_t      time;     /* Seconds since epoch, as from `time'. */
#endif
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
};
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define timeb64     timeb
#else
#define __timeb_alt timeb
#endif
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timeb_alt {
#if __TM_SIZEOF(TIME) <= 4
	__time32_t      time;     /* Seconds since epoch, as from `time'. */
#else
	__time64_t      time;     /* Seconds since epoch, as from `time'. */
#endif
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
};
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
}%[pop_macro]%{

}

[doc_alias(ftime)][ignore] __crt_ftime32:([nonnull] struct __timeb32 *timebuf) -> int = ftime?;
[doc_alias(ftime)][ignore] __crt_ftime64:([nonnull] struct __timeb64 *timebuf) -> int = ftime64?;

%#ifdef __USE_DOS
%#ifndef __errno_t_defined
%#define __errno_t_defined 1
%typedef int errno_t;
%#endif /* !__errno_t_defined */

[doc_alias(ftime)][ignore] __crt_dos_ftime32:([nonnull] struct __timeb32 *timebuf) = _ftime32?;
[doc_alias(ftime)][ignore] __crt_dos_ftime64:([nonnull] struct __timeb64 *timebuf) = _ftime64?;
[doc_alias(ftime)][ignore] __crt_ftime32_s:([nonnull] struct __timeb32 *timebuf) -> errno_t = _ftime32_s?;
[doc_alias(ftime)][ignore] __crt_ftime64_s:([nonnull] struct __timeb64 *timebuf) -> errno_t = _ftime64_s?;



[doc_alias(ftime)]
[requires(defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime64))]
_ftime32:([nonnull] struct __timeb32 *timebuf) {
#if defined(__CRT_HAVE__ftime32_s)
	if unlikely(__crt_ftime32_s(timebuf))
		memset(timebuf,0,sizeof(*timebuf));
#elif defined(__CRT_HAVE_ftime)
	if unlikely(__crt_ftime32(timebuf))
		memset(timebuf,0,sizeof(*timebuf));
#elif defined(__CRT_HAVE__ftime64)
	struct __timeb64 temp;
	__crt_dos_ftime64(&temp)
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
#else
	struct __timeb64 temp;
#ifdef __CRT_HAVE__ftime64_s
	if unlikely(__crt_ftime64_s(&temp))
#else
	if unlikely(__crt_ftime64(&temp))
#endif
		memset(timebuf,0,sizeof(*timebuf));
	else {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
#endif
}

[doc_alias(ftime)]
[time64_variant_of(_ftime32)]
[requires(defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32))]
_ftime64:([nonnull] struct __timeb64 *timebuf) {
#if defined(__CRT_HAVE__ftime64_s)
	if unlikely(__crt_ftime64_s(timebuf))
		memset(timebuf,0,sizeof(*timebuf));
#elif defined(__CRT_HAVE_ftime64)
	if unlikely(__crt_ftime64(timebuf))
		memset(timebuf,0,sizeof(*timebuf));
#elif defined(__CRT_HAVE__ftime32)
	struct __timeb32 temp;
	__crt_dos_ftime32(&temp)
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
#else
	struct __timeb32 temp;
#ifdef __CRT_HAVE__ftime32_s
	if unlikely(__crt_ftime32_s(&temp))
#else
	if unlikely(__crt_ftime32(&temp))
#endif
		memset(timebuf,0,sizeof(*timebuf));
	else {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
#endif
}

[doc_alias(ftime)]
[requires(defined(__CRT_HAVE__ftime64_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64))]
[dependency_include(<parts/errno.h>)]
_ftime32_s:([nonnull] struct __timeb32 *timebuf) -> errno_t {
#ifdef __CRT_HAVE_ftime
	return __crt_ftime32(timebuf) ? 0 : __libc_geterrno_or(@EPERM@);
#elif defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime64_s)
	struct __timeb64 temp;
#ifdef __CRT_HAVE__ftime64_s
	errno_t error = __crt_ftime64_s(&temp);
	if (error)
		return error;
#else /* __CRT_HAVE__ftime64_s */
	if (__crt_ftime64(&temp))
		return __libc_geterrno_or(@EPERM@);
#endif /* !__CRT_HAVE__ftime64_s */
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
#elif defined(__CRT_HAVE__ftime32)
	__crt_dos_ftime32(timebuf);
	return 0;
#else
	struct __timeb64 temp;
	__crt_dos_ftime64(&temp);
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
#endif
}

[doc_alias(ftime)][time64_variant_of(_ftime32_s)]
[requires(defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64))]
[dependency_include(<parts/errno.h>)]
_ftime64_s:([nonnull] struct __timeb64 *timebuf) -> errno_t {
#ifdef __CRT_HAVE_ftime64
	return __crt_ftime64(timebuf) ? 0 : __libc_geterrno_or(@EPERM@);
#elif defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE__ftime32_s)
	struct __timeb32 temp;
#ifdef __CRT_HAVE__ftime32_s
	errno_t error = __crt_ftime32_s(&temp);
	if (error)
		return error;
#else /* __CRT_HAVE__ftime32_s */
	if (__crt_ftime32(&temp))
		return __libc_geterrno_or(@EPERM@);
#endif /* !__CRT_HAVE__ftime32_s */
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
#elif defined(__CRT_HAVE__ftime64)
	__crt_dos_ftime64(timebuf);
	return 0;
#else
	struct __timeb32 temp;
	__crt_dos_ftime32(&temp);
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
#endif
}

%#endif /* __USE_DOS */


%
%
%
@@Fill in TIMEBUF with information about the current time
[if(defined(__USE_TIME_BITS64)),preferred_alias(ftime64)]
[if(!defined(__USE_TIME_BITS64)),preferred_alias(ftime)]
[requires(defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE_ftime64) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s))]
[dependency_include(<parts/errno.h>)]
ftime:([nonnull] struct timeb *timebuf) -> int {
#if defined(__CRT_HAVE__ftime32_s) && !defined(__USE_TIME_BITS64)
	errno_t error = __crt_ftime32_s(timebuf);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	}
	return (int)error;
#elif defined(__CRT_HAVE__ftime64_s) && defined(__USE_TIME_BITS64)
	errno_t error = __crt_ftime64_s(timebuf);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	}
	return (int)error;
#elif defined(__CRT_HAVE__ftime32) && !defined(__USE_TIME_BITS64)
	__crt_dos_ftime32(&temp);
	return 0;
#elif defined(__CRT_HAVE__ftime64) && defined(__USE_TIME_BITS64)
	__crt_dos_ftime64(&temp);
	return 0;
#elif defined(__CRT_HAVE_ftime)
	struct __timeb32 temp;
	int error = __crt_ftime32(&temp);
	if likely(!error) {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
#elif defined(__CRT_HAVE_ftime64)
	struct __timeb64 temp;
	int error = __crt_ftime64(&temp);
	if likely(!error) {
		timebuf->@time@     = (time32_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
#elif defined(__CRT_HAVE__ftime32_s)
	struct __timeb32 temp;
	errno_t error = __crt_ftime32_s(&temp);
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
#elif defined(__CRT_HAVE__ftime64_s)
	struct __timeb64 temp;
	errno_t error = __crt_ftime64_s(&temp);
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
#elif defined(__CRT_HAVE__ftime32)
	struct __timeb32 temp;
	__crt_dos_ftime32(&temp);
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
#else
	struct __timeb64 temp;
	__crt_dos_ftime64(&temp);
	timebuf->@time@     = (time32_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
#endif
}

%
%#ifdef __USE_TIME64
[requires(defined(__CRT_HAVE_ftime) || defined(__CRT_HAVE__ftime32) || defined(__CRT_HAVE__ftime64) || defined(__CRT_HAVE__ftime32_s) || defined(__CRT_HAVE__ftime64_s))]
[time64_variant_of(ftime)][dependency_include(<parts/errno.h>)]
ftime64:([nonnull] struct timeb64 *timebuf) -> int {
#ifdef __CRT_HAVE__ftime64_s
	errno_t error = __crt_ftime64_s(timebuf);
	if unlikely(error) {
		__libc_seterrno(error);
		error = -1;
	}
	return (int)error;
#elif defined(__CRT_HAVE__ftime64)
	__crt_dos_ftime64(&temp);
	return 0;
#elif defined(__CRT_HAVE_ftime)
	struct __timeb32 temp;
	int error = __crt_ftime32(&temp);
	if likely(!error) {
		timebuf->@time@     = (time64_t)temp.@time@;
		timebuf->@millitm@  = temp.@millitm@;
		timebuf->@timezone@ = temp.@timezone@;
		timebuf->@dstflag@  = temp.@dstflag@;
	}
	return error;
#elif defined(__CRT_HAVE__ftime32_s)
	struct __timeb32 temp;
	errno_t error = __crt_ftime32_s(&temp);
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
#else
	struct __timeb32 temp;
	__crt_dos_ftime32(&temp);
	timebuf->@time@     = (time64_t)temp.@time@;
	timebuf->@millitm@  = temp.@millitm@;
	timebuf->@timezone@ = temp.@timezone@;
	timebuf->@dstflag@  = temp.@dstflag@;
	return 0;
#endif
}
%#endif /* __USE_TIME64 */



%{

#endif /* __CC__ */

__SYSDECL_END

}