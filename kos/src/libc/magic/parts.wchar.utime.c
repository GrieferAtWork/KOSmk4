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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(utimbuf32 = __utimbuf32)]
%[define_replacement(utimbuf64 = __utimbuf64)]
%[default:section(".text.crt{|.dos}.wchar.fs.modify_time")]

%{
#include <features.h>
#ifndef _UTIME_H
#include <utime.h>
#endif /* !_UTIME_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

[[cp, wchar, ignore, nocrt, alias("wutime", "_wutime32")]]
int crt_wutime32([[nonnull]] $wchar_t const *filename,
                 [[nullable]] struct $utimbuf32 const *file_times);

[[cp, wchar, ignore, nocrt, alias("wutime64", "_wutime64")]]
int crt_wutime64([[nonnull]] $wchar_t const *filename,
                 [[nullable]] struct $utimbuf64 const *file_times);

[[cp, wchar, export_as("_wutime32"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias("wutime64", "_wutime64")]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias("wutime", "_wutime32")]]
[[userimpl, requires($has_function(crt_wutime32) || $has_function(crt_wutime64))]]
int wutime([[nonnull]] wchar_t const *filename,
           [[nullable]] struct utimbuf const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
@@pp_if $has_function(crt_wutime32)@@
	struct utimbuf32 buf32;
	if (!file_times)
		return crt_wutime32(filename, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_wutime32(filename, &buf32);
@@pp_else@@
	struct utimbuf64 buf64;
	if (!file_times)
		return wutime64(filename, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return wutime64(filename, &buf64);
@@pp_endif@@
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%
%#ifdef __USE_TIME64
[[time64_variant_of(wutime)]]
[[cp, wchar, dos_export_alias("_wutime64"), doc_alias("wutime")]]
[[userimpl, requires_function(crt_wutime32)]]
int wutime64([[nonnull]] $wchar_t const *filename,
             [[nullable]] struct utimbuf64 const *file_times) {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct utimbuf32 buf32;
	if (!file_times)
		return crt_wutime32(filename, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_wutime32(filename, &buf32);
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}
%#endif /* __USE_TIME64 */


%{

#endif /* __CC__ */

__SYSDECL_END

}

