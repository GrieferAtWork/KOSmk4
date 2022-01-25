/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Windows Kits (/ucrt/corecrt_wstring.h) */
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

%#ifndef _WSTRING_DEFINED
%#define _WSTRING_DEFINED 1

%/* Standard functions (already defined in <wchar.h>) */
%[insert:extern(wcscat)]
%[insert:extern(wcschr)]
%[insert:extern(wcscmp)]
%[insert:extern(wcscpy)]
%[insert:extern(wcscspn)]
%[insert:extern(wcslen)]
%[insert:extern(wcsnlen)]
%[insert:extern(wcsncat)]
%[insert:extern(wcsncmp)]
%[insert:extern(wcsncpy)]
%[insert:extern(wcspbrk)]
%[insert:extern(wcsrchr)]
%[insert:extern(wcsspn)]
%[insert:extern(wcsstr)]
%[insert:extern(wcstok)]
%[insert:extern(wcsxfrm)]
%[insert:extern(wcscoll)]
%[insert:extern(wcsdup)]
%[insert:extern(wcsnset)]
%[insert:extern(wcsrev)]
%[insert:extern(wcsset)]
%[insert:extern(wcslwr)]
%[insert:extern(wcsupr)]

%
%
%
%/* DOS-specific aliases for differently named functions */
%[insert:guarded_function(wcswcs = wcsstr)]
%[insert:function(wcsicmp = wcscasecmp)]
%[insert:function(wcsnicmp = wcsncasecmp)]
%[insert:function(wcsicoll = wcscasecoll)]
%[insert:function(_wcsdup = wcsdup)]
%[insert:function(_wcsicmp = wcscasecmp)]
%[insert:function(_wcsnicmp = wcsncasecmp)]
%[insert:function(_wcsicmp_l = wcscasecmp_l)]
%[insert:function(_wcsnicmp_l = wcsncasecmp_l)]
%[insert:function(_wcsnset = wcsnset)]
%[insert:function(_wcsrev = wcsrev)]
%[insert:function(_wcsset = wcsset)]
%[insert:function(_wcslwr = wcslwr)]
%[insert:function(_wcsupr = wcsupr)]
%[insert:function(_wcslwr_l = wcslwr_l)]
%[insert:function(_wcsupr_l = wcsupr_l)]
%[insert:function(_wcsxfrm_l = wcsxfrm_l)]
%[insert:function(_wcscoll_l = wcscoll_l)]
%[insert:function(_wcsicoll = wcscasecoll)]
%[insert:function(_wcsicoll_l = wcscasecoll_l)]
%[insert:function(_wcsncoll = wcsncasecoll)]
%[insert:function(_wcsncoll_l = wcsncoll_l)]
%[insert:function(_wcsnicoll = wcsncasecoll)]
%[insert:function(_wcsnicoll_l = wcsncasecoll_l)]


%
%
%
%/* DOS-specific functions */
%[default:section(".text.crt.dos.wchar.errno")];

[[wchar, decl_include("<hybrid/typecore.h>")]]
wchar_t *_wcserror(int errno_value);

[[wchar, decl_include("<bits/types.h>")]]
$errno_t _wcserror_s(wchar_t *buf, $size_t bufsize, int errno_value);

[[wchar, decl_include("<hybrid/typecore.h>")]]
wchar_t *__wcserror(wchar_t const *message);

[[wchar, decl_include("<bits/types.h>")]]
$errno_t __wcserror_s(wchar_t *buf, $size_t bufsize, wchar_t const *message);

[[wchar, section(".text.crt.dos.wchar.string.memory")]]
[[decl_include("<bits/types.h>")]]
$errno_t _wcsnset_s(wchar_t *__restrict buf, $size_t buflen, wchar_t ch, $size_t maxlen)
	%{generate(str2wcs("_strnset_s"))}

[[wchar, section(".text.crt.dos.wchar.string.memory")]]
[[decl_include("<bits/types.h>")]]
$errno_t _wcsset_s([[nonnull]] wchar_t *dst, $size_t dstsize, wchar_t ch)
	%{generate(str2wcs("_strset_s"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.memory")]]
_wcslwr_s(*) %{generate(str2wcs("_strlwr_s"))}

[[wchar, section(".text.crt.dos.wchar.unicode.static.memory")]]
_wcsupr_s(*) %{generate(str2wcs("_strupr_s"))}

[[wchar, section(".text.crt.dos.wchar.unicode.locale.memory")]]
_wcslwr_s_l(*) %{generate(str2wcs("_strlwr_s_l"))}

[[wchar, section(".text.crt.dos.wchar.unicode.locale.memory")]]
_wcsupr_s_l(*) %{generate(str2wcs("_strupr_s_l"))}

[[decl_include("<bits/types.h>")]]
[[wchar, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wmemcpy_s([[nonnull]] wchar_t *dst, rsize_t dstlength,
                   [[nonnull]] wchar_t const *src, rsize_t srclength)
	%{generate(str2wcs("memcpy_s"))}

[[decl_include("<bits/types.h>")]]
[[wchar, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wmemmove_s([[nonnull]] wchar_t *dst, rsize_t dstlength,
                    [[nonnull]] wchar_t const *src, rsize_t srclength)
	%{generate(str2wcs("memmove_s"))}

%
%#ifdef __USE_DOS_SLIB
@@>> wcscat_s(3)
[[wchar, section(".text.crt.dos.wchar.string.memory")]]
wcscat_s(*) %{generate(str2wcs("strcat_s"))}

@@>> wcscpy_s(3)
[[wchar, section(".text.crt.dos.wchar.string.memory")]]
wcscpy_s(*) %{generate(str2wcs("strcpy_s"))}

@@>> wcsnlen_s(3)
[[decl_include("<hybrid/typecore.h>")]]
[[inline, nocrt, pure, wunused]]
$size_t wcsnlen_s([[nullable]] wchar_t const *str, $size_t maxlen) {
	return str ? wcsnlen(str, maxlen) : 0;
}

@@>> wcsncat_s(3)
[[wchar, section(".text.crt.dos.wchar.string.memory")]]
wcsncat_s(*) %{generate(str2wcs("strncat_s"))}

@@>> wcsncpy_s(3)
[[wchar, section(".text.crt.dos.wchar.string.memory")]]
wcsncpy_s(*) %{generate(str2wcs("strncpy_s"))}

%[insert:function(wcstok_s = wcstok)]
%#endif  /* __USE_DOS_SLIB */

%#endif /* !_WSTRING_DEFINED */

%[insert:function(_wcstok = broken_dos_wcstok)]

%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STRING_H */
#endif /* __USE_UTF */

}
