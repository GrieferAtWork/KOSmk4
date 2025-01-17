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
/* (>) Standard: POSIX.1c (Issue 3, IEEE Std 1003.1c-1995) */
/* (#) Portability: Cygwin        (/newlib/libc/include/utime.h) */
/* (#) Portability: DJGPP         (/include/utime.h) */
/* (#) Portability: DragonFly BSD (/include/utime.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/utime.h) */
/* (#) Portability: FreeBSD       (/include/utime.h) */
/* (#) Portability: GNU C Library (/io/utime.h) */
/* (#) Portability: GNU Hurd      (/usr/include/utime.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/utime.h) */
/* (#) Portability: NetBSD        (/include/utime.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/utime.h) */
/* (#) Portability: OpenBSD       (/include/utime.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/utime.h) */
/* (#) Portability: diet libc     (/include/utime.h) */
/* (#) Portability: libc4/5       (/include/utime.h) */
/* (#) Portability: libc6         (/include/utime.h) */
/* (#) Portability: mintlib       (/include/utime.h) */
/* (#) Portability: musl libc     (/include/utime.h) */
/* (#) Portability: uClibc        (/include/utime.h) */
}

%[define_decl_include("<bits/os/utimbuf.h>": [
	"struct utimbuf", "struct utimbuf32", "struct utimbuf64"
])]

%[default:section(".text.crt{|.dos}.fs.modify_time")]
%[define_replacement(fd_t       = __fd_t)]
%[define_replacement(time_t     = "__time_t")]
%[define_replacement(time32_t   = __time32_t)]
%[define_replacement(time64_t   = __time64_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[define_replacement(timeval32  = __timeval32)]
%[define_replacement(timeval64  = __timeval64)]
%[define_replacement(utimbuf32  = __utimbuf32)]
%[define_replacement(utimbuf64  = __utimbuf64)]

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/os/utimbuf.h>
)]%{


#ifdef __CC__
__SYSDECL_BEGIN

#if (defined(__USE_XOPEN) || defined(__USE_XOPEN2K) || defined(__USE_DOS))
#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K || __USE_DOS */

#ifdef __USE_DOS
#ifndef _UTIMBUF_DEFINED
#define _UTIMBUF_DEFINED 1
#define _utimbuf utimbuf
#endif /* !_UTIMBUF_DEFINED */
#endif /* __USE_DOS */

/* Used assembly names (Required for binary compatibility):
 * FMT       TIME  KOS         DOS(HOSTED)      DOS        GLC
 * char      32    utime       DOS$_utime32    _utime32   utime
 * char      64    utime64     DOS$_utime64    _utime64   ---
 * fd_t fd   32    futime      _futime32       _futime32  ---
 * fd_t fd   64    futime64    _futime64       _futime64  ---
 */

};

[[decl_include("<bits/os/utimbuf.h>")]]
[[cp, ignore, nocrt, alias("utime", "__utime", "__libc_utime", "_utime", "_utime32")]]
int crt_utime32([[in]] char const *filename, [[in_opt]] struct $utimbuf32 const *file_times);

[[decl_include("<bits/os/utimbuf.h>")]]
[[cp, ignore, nocrt, alias("utime64", "_utime64", "__utime64")]]
int crt_utime64([[in]] char const *filename, [[in_opt]] struct $utimbuf64 const *file_times);

[[decl_include("<bits/os/utimbuf.h>", "<bits/types.h>")]]
[[cp, ignore, nocrt, alias("futime", "_futime", "_futime32")]]
int crt_futime32([[fdarg]] $fd_t fd, [[in_opt]] struct $utimbuf32 const *file_times);

[[decl_include("<bits/os/utimbuf.h>", "<bits/types.h>")]]
[[cp, ignore, nocrt, alias("futime64", "_futime64")]]
int crt_futime64([[fdarg]] $fd_t fd, [[in_opt]] struct $utimbuf64 const *file_times);


@@>> utime(2), utime64(2)
[[cp, decl_include("<bits/os/utimbuf.h>"), no_crt_self_import, export_as("__utime", "__libc_utime")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("utime", "__utime", "__libc_utime", "_utime", "_utime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("utime64", "_utime64", "__utime64")]]
[[userimpl, requires($has_function(crt_utime32) || $has_function(crt_utime64))]]
[[crt_dos_variant, dos_only_export_as("_utime", "_utime32")]]
int utime([[in]] char const *filename, [[in_opt]] struct utimbuf const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
@@pp_if $has_function(crt_utime32)@@
	struct $utimbuf32 buf32;
	if (!file_times)
		return crt_utime32(filename, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_utime32(filename, &buf32);
@@pp_else@@
	struct $utimbuf64 buf64;
	if (!file_times)
		return crt_utime64(filename, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return crt_utime64(filename, &buf64);
@@pp_endif@@
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%
%#ifdef __USE_TIME64
[[cp, crt_dos_variant, decl_include("<bits/os/utimbuf.h>")]]
[[preferred_time64_variant_of(utime)], doc_alias("utime")]
[[time64_export_alias("__utime64")]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), preferred_alias("__utime", "__libc_utime", "_utime", "_utime32")]]
[[userimpl, requires_function(crt_utime32)]]
[[dos_only_export_alias("_utime64")]]
int utime64([[in]] char const *filename, [[in_opt]] struct utimbuf64 const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct $utimbuf32 buf32;
	if (!file_times)
		return crt_utime32(filename, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_utime32(filename, &buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
%#endif /* __USE_TIME64 */

%
%
%#ifdef __USE_KOS
@@>> futime(3), futime64(3)
[[cp, decl_include("<bits/os/utimbuf.h>", "<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futime", "_futime", "_futime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futime64", "_futime64")]]
[[userimpl, requires($has_function(crt_futime32) || $has_function(crt_futime64))]]
[[dos_only_export_as("_futime", "_futime32")]]
int futime([[fdarg]] $fd_t fd, [[in_opt]] struct utimbuf const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
@@pp_if $has_function(crt_futime32)@@
	struct $utimbuf32 buf32;
	if (!file_times)
		return crt_futime32(fd, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_futime32(fd, &buf32);
@@pp_else@@
	struct $utimbuf64 buf64;
	if (!file_times)
		return crt_futime64(fd, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return crt_futime64(fd, &buf64);
@@pp_endif@@
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%
%#ifdef __USE_TIME64
[[cp, decl_include("<bits/os/utimbuf.h>", "<bits/types.h>")]]
[[preferred_time64_variant_of(futime), doc_alias("futime")]]
[[userimpl, requires_function(crt_futime32)]]
[[dos_only_export_alias("_futime64")]]
int futime64([[fdarg]] $fd_t fd, [[in_opt]] struct utimbuf64 const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct $utimbuf32 buf32;
	if (!file_times)
		return crt_futime32(fd, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_futime32(fd, &buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
%#endif /* __USE_TIME64 */
%#endif /* __USE_KOS */


%
%
%
%#ifdef __USE_DOS
%{
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */
}

%[insert:function(_utime = utime)]
%[insert:function(_futime = futime)]

%[define_c_language_keyword(__KOS_FIXED_CONST)]

[[crt_dos_variant, decl_include("<features.h>", "<bits/os/utimbuf.h>")]]
[[cp, alias("utime", "__utime", "__libc_utime", "_utime")]]
[[no_crt_impl, requires_function(crt_utime64)]]
int _utime32([[in]] char const *filename,
             [[in_opt]] struct $utimbuf32 __KOS_FIXED_CONST *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct $utimbuf64 buf64;
	if (!file_times)
		return crt_utime64(filename, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return crt_utime64(filename, &buf64);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%[insert:function(_utime64 = utime64)]

[[decl_include("<features.h>", "<bits/os/utimbuf.h>", "<bits/types.h>")]]
[[cp, alias("futime", "_futime"), no_crt_impl, requires_function(crt_futime64)]]
int _futime32([[fdarg]] $fd_t fd, [[in_opt]] struct $utimbuf32 __KOS_FIXED_CONST *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct $utimbuf64 buf64;
	if (!file_times)
		return crt_futime64(fd, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return crt_futime64(fd, &buf64);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%[insert:function(_futime64 = futime64)]

%[insert:function(_wutime = wutime)]

[[crt_dos_variant, decl_include("<features.h>", "<bits/os/utimbuf.h>", "<hybrid/typecore.h>")]]
[[cp, alias("wutime", "_wutime"), nocrt, wchar, requires_function(crt_wutime64)]]
int _wutime32([[in]] wchar_t const *filename,
              [[in_opt]] struct $utimbuf32 __KOS_FIXED_CONST *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct $utimbuf64 buf64;
	if (!file_times)
		return crt_wutime64(filename, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return crt_wutime64(filename, &buf64);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%[insert:function(_wutime64 = wutime64)]
%#endif /* __USE_DOS */



%{

__SYSDECL_END
#endif /* __CC__ */


#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_UTIME_H)
#include <parts/wchar/utime.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_UTIME_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_UTIME_H */
#endif /* __USE_UTF */

}
