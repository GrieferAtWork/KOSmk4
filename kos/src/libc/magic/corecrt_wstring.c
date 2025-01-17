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

[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(strerror, convert_mbstowcs)]]
[[impl_include("<libc/errno.h>", "<bits/types.h>")]]
wchar_t *_wcserror($errno_t errno_value) {
	@@static void *_strerror_buf = NULL; [fini: free(_strerror_buf)]@@
	wchar_t *result;
	char const *newmsg;
@@pp_ifdef __libc_geterrno@@
	errno_t saved_errno;
@@pp_endif@@
	newmsg = strerror(errno_value);
	/*if unlikely(!newmsg) // `strerror()' returns non-NULL
		return NULL;*/

	/* Convert message. */
@@pp_ifdef __libc_geterrno@@
	saved_errno = __libc_geterrno();
@@pp_endif@@
	result = convert_mbstowcs(newmsg);
@@pp_if $has_function(free)@@
	free(_strerror_buf);
@@pp_endif@@
	_strerror_buf = result;
@@pp_ifdef __libc_geterrno@@
	__libc_seterrno(saved_errno);
@@pp_endif@@
	return result;
}

[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(_wcserror)]]
[[impl_include("<libc/errno.h>")]]
$errno_t _wcserror_s([[out(? <= buflen)]] wchar_t *buf,
                     $size_t buflen, $errno_t errno_value) {
	wchar_t *msg  = _wcserror(errno_value);
	size_t msglen = wcslen(msg) + 1;
	if (msglen >= buflen) {
@@pp_ifdef ERANGE@@
		return $ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	(void)wmemcpy(buf, msg, msglen);
	return 0;
}

[[wchar, decl_include("<hybrid/typecore.h>")]]
[[requires_function(_strerror, convert_mbstowcs, convert_wcstombs)]]
[[impl_include("<libc/errno.h>", "<bits/types.h>")]]
wchar_t *__wcserror([[in_opt]] wchar_t const *message) {
	@@static void *_strerror_buf = NULL; [fini: free(_strerror_buf)]@@
	wchar_t *result;
	char const *newmsg;
	char *utf8_message;
@@pp_ifdef __libc_geterrno@@
	errno_t saved_errno;
@@pp_endif@@
	if (message == NULL) {
		newmsg = _strerror(NULL);
	} else {
		utf8_message = convert_wcstombs(message);
		if unlikely(!utf8_message)
			return NULL;
		newmsg = _strerror(utf8_message);
@@pp_if $has_function(free)@@
		free(utf8_message);
@@pp_endif@@
		if unlikely(!newmsg)
			return NULL;
	}

	/* Convert message. */
@@pp_ifdef __libc_geterrno@@
	saved_errno = __libc_geterrno();
@@pp_endif@@
	result = convert_mbstowcs(newmsg);
@@pp_if $has_function(free)@@
	free(_strerror_buf);
@@pp_endif@@
	_strerror_buf = result;
@@pp_ifdef __libc_geterrno@@
	__libc_seterrno(saved_errno);
@@pp_endif@@
	return result;
}

[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(__wcserror)]]
[[impl_include("<libc/errno.h>")]]
$errno_t __wcserror_s([[out(? <= buflen)]] wchar_t *buf, $size_t buflen,
                      [[in_opt]] wchar_t const *message) {
	wchar_t *msg  = __wcserror(message);
	size_t msglen;
	if (!msg) {
@@pp_ifdef EINVAL@@
		return $EINVAL;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	msglen = wcslen(msg) + 1;
	if (msglen >= buflen) {
@@pp_ifdef ERANGE@@
		return $ERANGE;
@@pp_else@@
		return 1;
@@pp_endif@@
	}
	(void)wmemcpy(buf, msg, msglen);
	return 0;
}

[[wchar, section(".text.crt.dos.wchar.string.memory")]]
[[decl_include("<bits/types.h>")]]
$errno_t _wcsnset_s([[inout_opt(? <= maxlen)]] wchar_t *__restrict buf,
                    $size_t buflen, wchar_t ch, $size_t maxlen)
	%{generate(str2wcs("_strnset_s"))}

[[wchar, section(".text.crt.dos.wchar.string.memory")]]
[[decl_include("<bits/types.h>")]]
$errno_t _wcsset_s([[inout_opt(? <= dstsize)]] wchar_t *dst,
                   $size_t dstsize, wchar_t ch)
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
$errno_t wmemcpy_s([[out_opt(dstlength)]] wchar_t *dst, rsize_t dstlength,
                   [[in_opt (srclength)]] wchar_t const *src, rsize_t srclength)
	%{generate(str2wcs("memcpy_s"))}

[[decl_include("<bits/types.h>")]]
[[wchar, section(".text.crt.dos.wchar.string.memory")]]
$errno_t wmemmove_s([[out_opt(dstlength)]] wchar_t *dst, rsize_t dstlength,
                    [[in_opt (srclength)]] wchar_t const *src, rsize_t srclength)
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
$size_t wcsnlen_s([[in_opt(wcsnlen(., maxlen))]] wchar_t const *str, $size_t maxlen) {
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

[[hidden]] _c16error(*) %{uchar16("_wcserror")}
[[hidden]] _c32error(*) %{uchar32("_wcserror")}
[[hidden]] _c16error_s(*) %{uchar16("_wcserror_s")}
[[hidden]] _c32error_s(*) %{uchar32("_wcserror_s")}
[[hidden]] __c16error(*) %{uchar16("__wcserror")}
[[hidden]] __c32error(*) %{uchar32("__wcserror")}
[[hidden]] __c16error_s(*) %{uchar16("__wcserror_s")}
[[hidden]] __c32error_s(*) %{uchar32("__wcserror_s")}


%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STRING_H */
#endif /* __USE_UTF */

}
