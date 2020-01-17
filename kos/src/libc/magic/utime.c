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


%[default_impl_section(.text.crt.fs.modify_time)]
%[define_replacement(fd_t     = __fd_t)]
%[define_replacement(time_t   = __TM_TYPE(time))]
%[define_replacement(time32_t = __time32_t)]
%[define_replacement(time64_t = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]

%{
#include <features.h>
#include <bits/types.h>
#include <bits/utimebuf.h>

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K) || \
    defined(__USE_DOS)
#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t;
#endif /* !__time_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifdef __USE_DOS
#ifndef _UTIMBUF_DEFINED
#define _UTIMBUF_DEFINED 1
#define _utimbuf   utimbuf
#endif /* !_UTIMBUF_DEFINED */
#endif /* __USE_DOS */

/* Used assembly names (Required for binary compatibility):
 * FMT       TIME  KOS         DOS(HOSTED)      DOS        GLC
 * char      32    utime       DOS$_utime32    _utime32   utime
 * char      64    utime64     DOS$_utime64    _utime64   ---
 * fd_t fd   32    futime      _futime32       _futime32  ---
 * fd_t fd   64    futime64    _futime64       _futime64  ---
 */

}

[cp][ignore][alias(_utime32)] crt_utime32:([nonnull] char const *filename, [nullable] struct __utimbuf32 const *file_times) -> int = utime?;
[cp][ignore][alias(_utime64)] crt_utime64:([nonnull] char const *filename, [nullable] struct __utimbuf64 const *file_times) -> int = utime64?;
[cp][ignore][alias(_futime32)] crt_futime32:($fd_t fd, [nullable] struct __utimbuf32 const *file_times) -> int = futime?;
[cp][ignore][alias(_futime64)] crt_futime64:($fd_t fd, [nullable] struct __utimbuf64 const *file_times) -> int = futime64?;

[cp]
[if(defined(__USE_TIME_BITS64)),preferred_alias(utime64,_utime64)]
[if(!defined(__USE_TIME_BITS64)),preferred_alias(utime,_utime32)]
[requires(defined(__CRT_HAVE_utime) || defined(__CRT_HAVE__utime32) || defined(__CRT_HAVE_utime64) || defined(__CRT_HAVE__utime64))]
[alternate_names(_utime32)]
utime:([nonnull] char const *filename, [nullable] struct utimbuf const *file_times) -> int {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
#if defined(__CRT_HAVE_utime) || defined(__CRT_HAVE__utime32)
	struct __utimbuf32 buf32;
	if (!file_times)
		return crt_utime32(filename,NULL);
	buf32.actime  = (time32_t)file_times->actime;
	buf32.modtime = (time32_t)file_times->modtime;
	return crt_utime32(filename,&buf32);
#else
	struct __utimbuf64 buf64;
	if (!file_times)
		return utime64(filename,NULL);
	buf64.actime  = (time64_t)file_times->actime;
	buf64.modtime = (time64_t)file_times->modtime;
	return utime64(filename,&buf64);
#endif
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%
%#ifdef __USE_TIME64
[cp][alias(_utime64)][time64_variant_of(utime)]
[requires(defined(__CRT_HAVE_utime) || defined(__CRT_HAVE__utime32))]
utime64:([nonnull] char const *filename, [nullable] struct utimbuf64 const *file_times) -> int {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
	struct __utimbuf32 buf32;
	if (!file_times)
		return crt_utime32(filename,NULL);
	buf32.actime  = (time32_t)file_times->actime;
	buf32.modtime = (time32_t)file_times->modtime;
	return crt_utime32(filename,&buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
%#endif /* __USE_TIME64 */

%
%
%#ifdef __USE_KOS

[cp]
[if(defined(__USE_TIME_BITS64)),preferred_alias(futime64,_futime64)]
[if(!defined(__USE_TIME_BITS64)),preferred_alias(futime,_futime32)]
[requires(defined(__CRT_HAVE_futime) || defined(__CRT_HAVE__futime32) || defined(__CRT_HAVE_futime64) || defined(__CRT_HAVE__futime64))]
[alternate_names(_futime32)]
futime:($fd_t fd, [nullable] struct utimbuf const *file_times) -> int {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
#if defined(__CRT_HAVE_futime) || defined(__CRT_HAVE__futime32)
	struct __utimbuf32 buf32;
	if (!file_times)
		return crt_futime32(fd,NULL);
	buf32.actime  = (time32_t)file_times->actime;
	buf32.modtime = (time32_t)file_times->modtime;
	return crt_futime32(fd,&buf32);
#else
	struct __utimbuf64 buf64;
	if (!file_times)
		return futime64(fd,NULL);
	buf64.actime  = (time64_t)file_times->actime;
	buf64.modtime = (time64_t)file_times->modtime;
	return futime64(fd,&buf64);
#endif
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%
%#ifdef __USE_TIME64
[cp][alias(_futime64)][time64_variant_of(futime)]
[requires(defined(__CRT_HAVE_futime) || defined(__CRT_HAVE__futime32))]
futime64:($fd_t fd, [nullable] struct utimbuf64 const *file_times) -> int {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("actime")
#pragma push_macro("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef actime
#undef modtime
	struct __utimbuf32 buf32;
	if (!file_times)
		return crt_futime32(fd,NULL);
	buf32.actime  = (time32_t)file_times->actime;
	buf32.modtime = (time32_t)file_times->modtime;
	return crt_futime32(fd,&buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("modtime")
#pragma pop_macro("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_KOS */


%
%
%
%#ifdef __USE_DOS
%#ifndef __wchar_t_defined
%#define __wchar_t_defined 1
%typedef __WCHAR_TYPE__ wchar_t;
%#endif /* !__wchar_t_defined */

[cp][noexport][nocrt]
[if(defined(__USE_TIME_BITS64)),preferred_alias(utime64, _utime64)]
[if(!defined(__USE_TIME_BITS64)),preferred_alias(utime, _utime32)]
_utime:([notnull] char const *filename, [nullable] struct _utimbuf __KOS_FIXED_CONST *file_times) -> int = utime;

[cp]
[if(defined(__USE_TIME_BITS64)),preferred_alias(futime64,_futime64)]
[if(!defined(__USE_TIME_BITS64)),preferred_alias(futime,_futime32)][noexport][nocrt]
_futime:($fd_t fd, [nullable] struct _utimbuf __KOS_FIXED_CONST *file_times) -> int = futime;

[cp][alias(utime)][nouser][noexport]
[requires(defined(__CRT_HAVE__utime64) || defined(__CRT_HAVE_utime64))]
_utime32:([notnull] char const *filename, [nullable] struct __utimbuf32 __KOS_FIXED_CONST *file_times) -> int {
	struct __utimbuf64 buf64;
	if (!file_times)
		return crt_utime64(filename,NULL);
	buf64.actime  = (time64_t)file_times->actime;
	buf64.modtime = (time64_t)file_times->modtime;
	return crt_utime64(filename,&buf64);
}
[cp] _utime64:([notnull] char const *filename, [nullable] struct utimbuf64 const *file_times) -> int = utime64;

[cp][alias(futime)][nouser][noexport]
[requires(defined(__CRT_HAVE__futime64) || defined(__CRT_HAVE_futime64))]
_futime32:($fd_t fd, [nullable] struct __utimbuf32 __KOS_FIXED_CONST *file_times) -> int {
	struct __utimbuf64 buf64;
	if (!file_times)
		return crt_futime64(fd,NULL);
	buf64.actime  = (time64_t)file_times->actime;
	buf64.modtime = (time64_t)file_times->modtime;
	return crt_futime64(fd,&buf64);
}
[cp] _futime64:($fd_t fd, struct utimbuf64 const *file_times) -> int = futime64;

[cp][noexport][nocrt][wchar]
[if(defined(__USE_TIME_BITS64)),preferred_alias(wutime64,_wutime64)]
[if(!defined(__USE_TIME_BITS64)),preferred_alias(wutime,_wutime32)]
_wutime:([notnull] wchar_t const *filename, [nullable] struct _utimbuf __KOS_FIXED_CONST *file_times) -> int = wutime;

[cp][alias(wutime)][nouser][noexport][wchar]
[requires(defined(__CRT_HAVE__wutime64) || defined(__CRT_HAVE_wutime64))]
_wutime32:([notnull] wchar_t const *filename, [nullable] struct __utimbuf32 __KOS_FIXED_CONST *file_times) -> int {
	struct __utimbuf64 buf64;
	if (!file_times)
		return crt_wutime64(filename,NULL);
	buf64.actime  = (time64_t)file_times->actime;
	buf64.modtime = (time64_t)file_times->modtime;
	return crt_wutime64(filename,&buf64);
}

[cp][wchar] _wutime64:([notnull] wchar_t const *filename, [nullable] struct utimbuf64 const *file_times) -> int = wutime64;
%#endif /* __USE_DOS */



%{
#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_UTIME_H)
#include <parts/wchar/utime.h>
#endif
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif
#endif /* __USE_UTF */


}