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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[default_impl_section({.text.crt.wchar.fs.modify_time|.text.crt.dos.wchar.fs.modify_time})]

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

[cp][ignore][alias(_wutime32)][wchar]
crt_wutime32:([nonnull] $wchar_t const *filename, [nullable] struct __utimbuf32 const *file_times) -> int = wutime?;
[cp][ignore][alias(_wutime64)][wchar]
crt_wutime64:([nonnull] $wchar_t const *filename, [nullable] struct __utimbuf64 const *file_times) -> int = wutime64?;

[cp][alternate_names(_wutime32)][wchar]
[if(defined(__USE_TIME_BITS64)), preferred_alias(wutime64, _wutime64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(wutime, _wutime32)]
[requires(defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32) || defined(__CRT_HAVE_wutime64) || defined(__CRT_HAVE__wutime64))]
wutime:([nonnull] wchar_t const *filename, [nullable] struct utimbuf const *file_times) -> int {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
#if defined(__CRT_HAVE_utime) || defined(__CRT_HAVE__utime32)
	struct __utimbuf32 buf32;
	if (!file_times)
		return crt_wutime32(filename, NULL);
	buf32.@actime@  = (time32_t)file_times->@actime@;
	buf32.@modtime@ = (time32_t)file_times->@modtime@;
	return crt_wutime32(filename, &buf32);
#else
	struct __utimbuf64 buf64;
	if (!file_times)
		return wutime64(filename, NULL);
	buf64.@actime@  = (time64_t)file_times->@actime@;
	buf64.@modtime@ = (time64_t)file_times->@modtime@;
	return wutime64(filename, &buf64);
#endif
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @pop_macro@("modtime")
#pragma @pop_macro@("actime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
}

%
%#ifdef __USE_TIME64
[cp][alias(_wutime64)][wchar][time64_variant_of(wutime)]
[requires(defined(__CRT_HAVE_wutime) || defined(__CRT_HAVE__wutime32))]
wutime64:([nonnull] $wchar_t const *filename, [nullable] struct utimbuf64 const *file_times) -> int {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma @push_macro@("actime")
#pragma @push_macro@("modtime")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef @actime@
#undef @modtime@
	struct __utimbuf32 buf32;
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

