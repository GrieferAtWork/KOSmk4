/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Windows Kits (/ucrt/corecrt_wstdlib.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#define _MAX_I64TOSTR_BASE16_COUNT (16 + 1)
#define _MAX_I64TOSTR_BASE10_COUNT (1 + 19 + 1)
#define _MAX_I64TOSTR_BASE8_COUNT  (22 + 1)
#define _MAX_I64TOSTR_BASE2_COUNT  (64 + 1)
#define _MAX_U64TOSTR_BASE16_COUNT (16 + 1)
#define _MAX_U64TOSTR_BASE10_COUNT (20 + 1)
#define _MAX_U64TOSTR_BASE8_COUNT  (22 + 1)
#define _MAX_U64TOSTR_BASE2_COUNT  (64 + 1)

#if __SIZEOF_INT__ == 4
#define _MAX_ITOSTR_BASE16_COUNT (8 + 1)
#define _MAX_ITOSTR_BASE10_COUNT (1 + 10 + 1)
#define _MAX_ITOSTR_BASE8_COUNT  (11 + 1)
#define _MAX_ITOSTR_BASE2_COUNT  (32 + 1)
#endif /* __SIZEOF_INT__ == 4 */

#if __SIZEOF_LONG__ == 4
#define _MAX_LTOSTR_BASE16_COUNT  (8 + 1)
#define _MAX_LTOSTR_BASE10_COUNT  (1 + 10 + 1)
#define _MAX_LTOSTR_BASE8_COUNT   (11 + 1)
#define _MAX_LTOSTR_BASE2_COUNT   (32 + 1)
#define _MAX_ULTOSTR_BASE16_COUNT (8 + 1)
#define _MAX_ULTOSTR_BASE10_COUNT (10 + 1)
#define _MAX_ULTOSTR_BASE8_COUNT  (11 + 1)
#define _MAX_ULTOSTR_BASE2_COUNT  (32 + 1)
#elif __SIZEOF_LONG__ == 8
#define _MAX_LTOSTR_BASE16_COUNT  (16 + 1)
#define _MAX_LTOSTR_BASE10_COUNT  (1 + 19 + 1)
#define _MAX_LTOSTR_BASE8_COUNT   (22 + 1)
#define _MAX_LTOSTR_BASE2_COUNT   (64 + 1)
#define _MAX_ULTOSTR_BASE16_COUNT (16 + 1)
#define _MAX_ULTOSTR_BASE10_COUNT (20 + 1)
#define _MAX_ULTOSTR_BASE8_COUNT  (22 + 1)
#define _MAX_ULTOSTR_BASE2_COUNT  (64 + 1)
#endif /* ... */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ernno_t_defined
#define __ernno_t_defined
typedef __errno_t errno_t;
#endif /* !__ernno_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef __SIZE_TYPE__ rsize_t;
#endif /* !__rsize_t_defined */

}

%#ifndef _WSTDLIB_DEFINED
%#define _WSTDLIB_DEFINED

%[insert:function(_wgetenv = _wgetenv)]     /* Implemented in "stdlib.c" (but only exposed here) */
%[insert:function(_wgetenv_s = _wgetenv_s)] /* Implemented in "stdlib.c" (but only exposed here) */
%[insert:function(_wdupenv_s = _wdupenv_s)] /* Implemented in "stdlib.c" (but only exposed here) */

%[insert:function(_wsystem = wsystem, guardName: "_CRT_WSYSTEM_DEFINED")]

%[insert:extern(wcstol)]
%[insert:extern(wcstoll)]
%[insert:extern(wcstoul)]
%[insert:extern(wcstoull)]
%[insert:function(_wcstol_l = wcstol_l)]
%[insert:function(_wcstoul_l = wcstoul_l)]

%#ifndef __NO_FPU
%[insert:extern(wcstof)]
%[insert:extern(wcstod)]
%[insert:function(_wcstof_l = wcstof_l)]
%[insert:function(_wcstod_l = wcstod_l)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:extern(wcstold)]
%[insert:function(_wcstold_l = wcstold_l)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.unicode.static.convert")]]
double _wtof([[in]] wchar_t const *nptr) {
	return wcstod(nptr, NULL);
}

[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt.dos.wchar.unicode.static.convert")]]
double _wtof_l([[in]] wchar_t const *nptr,
               [[nullable]] $locale_t locale) {
	return wcstod_l(nptr, NULL, locale);
}
%#endif /* !__NO_FPU */

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_itow(*) %{generate(str2wcs("itoa"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ltow(*) %{generate(str2wcs("ltoa"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ultow(*) %{generate(str2wcs("ultoa"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_i64tow(*) %{generate(str2wcs("_i64toa"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ui64tow(*) %{generate(str2wcs("_ui64toa"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_itow_s(*) %{generate(str2wcs("_itoa_s"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ltow_s(*) %{generate(str2wcs("_ltoa_s"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ultow_s(*) %{generate(str2wcs("_ultoa_s"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_i64tow_s(*) %{generate(str2wcs("_i64toa_s"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
_ui64tow_s(*) %{generate(str2wcs("_ui64toa_s"))}

%[insert:function(_wtoi = wtoi)]
%[insert:function(_wtol = wtol)]

[[wchar, section(".text.crt.dos.wchar.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),       alias("_wtoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      alias("_wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_wtoll")]]
_wtoi64(*) %{generate(str2wcs("_atoi64"))}

%[insert:function(_wcstoi64  = wcsto64)]
%[insert:function(_wcstoui64 = wcstou64)]

[[wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__),      alias("_wtol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("_wtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8),                    alias("_wtoi64_l")]]
_wtoi_l(*) %{generate(str2wcs("_atoi_l"))}

[[wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, _wtoi_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("_wtoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias("_wtoi64_l")]]
_wtol_l(*) %{generate(str2wcs("_atol_l"))}

[[wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_INT__ == 8, _wtoi_l)]]
[[alt_variant_of(__SIZEOF_LONG__ == 8, _wtol_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == 8, _wtoll_l)]]
_wtoi64_l(*) %{generate(str2wcs("_atoi64_l"))}

%[insert:function(_wcstoi64_l  = wcsto64_l)]
%[insert:function(_wcstoui64_l = wcstou64_l)]


%#ifdef __LONGLONG
%[insert:function(_wcstoll_l  = wcstoll_l)]
%[insert:function(_wcstoull_l = wcstoull_l)]
%[insert:function(_wtoll      = wtoll)]

[[wchar, section(".text.crt.dos.wchar.unicode.locale.convert")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, _wtoi_l)]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, _wtol_l)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_wtoi64_l")]]
_wtoll_l(*) %{generate(str2wcs("_atoll_l"))}
%#endif /* __LONGLONG */

%#endif /* !_WSTDLIB_DEFINED */



%#ifndef _WSTDLIBP_DEFINED
%#define _WSTDLIBP_DEFINED 1

[[wchar, section(".text.crt.dos.wchar.fs.utility")]]
[[requires_include("<asm/os/fcntl.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires(defined(__AT_FDCWD) && $has_function(_fullpath, convert_wcstombs, convert_mbstowcs))]]
[[impl_include("<libc/errno.h>", "<asm/os/fcntl.h>")]]
wchar_t *_wfullpath([[out(? <= buflen)]] wchar_t *buf,
                    [[in]] wchar_t const *path,
                    $size_t buflen) {
	size_t reqlen;
	char *utf8_path, *utf8_realpath;
	wchar_t *wcs_realpath;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		return NULL;
	utf8_realpath = _fullpath(NULL, utf8_path, 0);
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
	if unlikely(!utf8_realpath)
		return NULL;
	wcs_realpath = convert_mbstowcs(utf8_realpath);
@@pp_if $has_function(free)@@
	free(utf8_realpath);
@@pp_endif@@
	if unlikely(!wcs_realpath)
		return NULL;
	if (!buf)
		return wcs_realpath;
	reqlen = wcslen(wcs_realpath) + 1;
	if (reqlen > buflen) {
@@pp_if $has_function(free)@@
		free(wcs_realpath);
@@pp_endif@@
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		return NULL;
	}
	buf = wmemcpy(buf, wcs_realpath, reqlen);
@@pp_if $has_function(free)@@
	free(wcs_realpath);
@@pp_endif@@
	return buf;
}

[[wchar, section(".text.crt.dos.wchar.fs.utility")]]
_wmakepath_s(*) %{generate(str2wcs("_makepath_s"))}

[[wchar, section(".text.crt.dos.wchar.fs.utility")]]
_wmakepath(*) %{generate(str2wcs("_makepath"))}

%[insert:function(_wperror = _wperror, guardName: "_CRT_WPERROR_DEFINED")]

%[insert:function(_wputenv = _wputenv)]           /* Implemented in "stdlib.c" (but only exposed here) */
%[insert:function(_wputenv_s = _wputenv_s)]       /* Implemented in "stdlib.c" (but only exposed here) */
%[insert:function(_wsearchenv_s = _wsearchenv_s)] /* Implemented in "stdlib.c" (but only exposed here) */

[[wchar, section(".text.crt.dos.wchar.fs.environ")]]
_wsearchenv(*) %{generate(str2wcs("_searchenv"))}

[[wchar, section(".text.crt.dos.wchar.fs.environ")]]
_wsplitpath(*) %{generate(str2wcs("_splitpath"))}

[[wchar, section(".text.crt.dos.wchar.fs.environ")]]
_wsplitpath_s(*) %{generate(str2wcs("_splitpath_s"))}

%#endif /* !_WSTDLIBP_DEFINED */



%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDLIB_H */
#endif /* __USE_UTF */

}
