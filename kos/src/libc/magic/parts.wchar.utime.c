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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(utimbuf32 = __utimbuf32)]
%[define_replacement(utimbuf64 = __utimbuf64)]
%[default:section(".text.crt{|.dos}.wchar.fs.modify_time")]

%[define_decl_include("<bits/os/utimbuf.h>": [
	"struct utimbuf", "struct utimbuf32", "struct utimbuf64"
])]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _UTIME_H
#include <utime.h>
#endif /* !_UTIME_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

}%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

[[decl_include("<hybrid/typecore.h>", "<bits/os/utimbuf.h>")]]
[[cp, wchar, ignore, nocrt, alias("wutime", "_wutime", "_wutime32")]]
int crt_wutime32([[in]] $wchar_t const *file,
                 [[in_opt]] struct $utimbuf32 const *file_times);

[[decl_include("<hybrid/typecore.h>", "<bits/os/utimbuf.h>")]]
[[cp, wchar, ignore, nocrt, alias("wutime64", "_wutime64")]]
int crt_wutime64([[in]] $wchar_t const *file,
                 [[in_opt]] struct $utimbuf64 const *file_times);

[[ignore]] crt_c16utime32(*) %{uchar16("crt_wutime32")}
[[ignore]] crt_c32utime32(*) %{uchar32("crt_wutime32")}
[[ignore]] crt_c16utime64(*) %{uchar16("crt_wutime64")}
[[ignore]] crt_c32utime64(*) %{uchar32("crt_wutime64")}


[[decl_include("<hybrid/typecore.h>", "<bits/os/utimbuf.h>")]]
[[cp, wchar, no_crt_self_import, dos_export_alias("_wutime", "_wutime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wutime", "_wutime", "_wutime32")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("wutime64", "_wutime64")]]
[[requires($has_function(crt_wutime32) ||
           $has_function(crt_wutime64) ||
           $has_function(utime, convert_wcstombs))]]
int wutime([[in]] wchar_t const *file,
           [[in_opt]] struct utimbuf const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
@@pp_if $has_function(crt_wutime32) && !defined(__BUILDING_LIBC)@@
	struct utimbuf32 buf32;
	if (!file_times)
		return crt_wutime32(file, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_wutime32(file, &buf32);
@@pp_elif $has_function(crt_wutime64) && (!defined(__BUILDING_LIBC) || __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__)@@
	struct utimbuf64 buf64;
	if (!file_times)
		return wutime64(file, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return wutime64(file, &buf64);
@@pp_else@@
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = utime(utf8_file, file_times);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_endif@@
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}


%
%#ifdef __USE_TIME64

[[decl_include("<hybrid/typecore.h>", "<bits/os/utimbuf.h>")]]
[[preferred_time64_variant_of(wutime), doc_alias("wutime")]]
[[cp, wchar, dos_export_alias("_wutime64")]]
[[requires($has_function(utime64, convert_wcstombs) ||
           $has_function(crt_wutime32))]]
int wutime64([[in]] $wchar_t const *file,
             [[in_opt]] struct utimbuf64 const *file_times) {
@@pp_if $has_function(utime64, convert_wcstombs)@@
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = utime64(utf8_file, file_times);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_else@@
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct utimbuf32 buf32;
	if (!file_times)
		return crt_wutime32(file, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_wutime32(file, &buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
@@pp_endif@@
}

%#endif /* __USE_TIME64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
