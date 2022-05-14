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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wtime.h) */
}

%[define_decl_include("<bits/crt/tm.h>": ["struct tm"])]

%[default:section(".text.crt.dos.wchar.time")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/crt/tm.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __USE_DOS
#include <crtdefs.h>
#endif /* __USE_DOS */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

}

[[wchar, wunused, requires_function(_wasctime_s)]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
wchar_t *_wasctime([[nonnull]] struct $tm const *tp) {
	static wchar_t wasctime_retbuf[26] = { 0 };
	return _wasctime_s(wasctime_retbuf, 26, tp) ? NULL : wasctime_retbuf;
}

[[wchar, requires_function(asctime_r)]]
[[decl_include("<bits/types.h>", "<bits/crt/tm.h>")]]
errno_t _wasctime_s([[outp(buflen)]] wchar_t *buf, size_t buflen,
                    [[nonnull]] struct $tm const *tp) {
	char abuf[26], *ptr;
	unsigned int i;
	if unlikely(buflen < 26)
		return $ERANGE;
	/* asctime --> ASCiiTIME --> No unicode here --> directly  copy
	 * This is also why its  kind of <redacted for profanity>  that
	 * a function like `_wasctime_s()' even exists, but whatever... */
	ptr = asctime_r(tp, abuf);
	for (i = 0; i < 26; ++i)
		buf[i] = (wchar_t)ptr[i];
	return 0;
}

%[insert:extern(wcsftime)]
%[insert:function(_wcsftime_l = wcsftime_l)]

[[wchar, wunused, requires_function(_wctime64), dos_export_alias("_wctime")]]
[[if(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_dos_alias("libd__wctime64")]]
[[if(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_kos_alias("libc__wctime64")]]
[[decl_include("<bits/types.h>")]]
wchar_t *_wctime32([[nonnull]] $time32_t const *timer) {
	time64_t timer64 = (time64_t)*timer;
	return _wctime64(&timer64);
}

[[wchar, wunused, requires_function(_wctime64_s)]]
[[decl_include("<bits/types.h>")]]
wchar_t *_wctime64([[nonnull]] $time64_t const *timer) {
	static wchar_t wctime64_retbuf[26];
@@pp_ifdef __BUILDING_LIBC@@
	_wctime64_s(wctime64_retbuf, 26, timer);
	return wctime64_retbuf;
@@pp_else@@
	return _wctime64_s(wctime64_retbuf, 26, timer) ? NULL : wctime64_retbuf;
@@pp_endif@@
}

[[wchar, requires_function(_ctime32_s)]]
[[decl_include("<bits/types.h>")]]
[[if(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_dos_alias("libd__wctime64_s")]]
[[if(__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), crt_intern_kos_alias("libc__wctime64_s")]]
errno_t _wctime32_s([[outp(buflen)]] wchar_t *buf, size_t buflen,
                    [[nonnull]] $time32_t const *timer) {
	time64_t timer64 = (time64_t)*timer;
	return _wctime64_s(buf, buflen, &timer64);
}

[[wchar, requires_function(_ctime64_s)]]
[[decl_include("<bits/types.h>"), impl_include("<libc/errno.h>")]]
errno_t _wctime64_s([[outp(buflen)]] wchar_t *buf, size_t buflen,
                    [[nonnull]] $time64_t const *timer) {
	char abuf[26], *ptr;
	unsigned int i;
	if unlikely(buflen < 26)
		return $ERANGE;
	ptr = ctime64_r(timer, abuf);
@@pp_ifndef __BUILDING_LIBC@@
	if unlikely(!ptr)
		return __libc_geterrno_or(1);
@@pp_endif@@
	for (i = 0; i < 26; ++i)
		buf[i] = (wchar_t)ptr[i]; /* Guarantied no unicode in here! */
	return 0;
}

[[wchar, requires_function(_strtime)]]
[[decl_include("<hybrid/typecore.h>")]]
wchar_t *_wstrtime([[nonnull]] wchar_t buf[9]) {
	unsigned int i;
	char abuf[9], *ptr;
	ptr = _strtime(abuf);
@@pp_ifndef __BUILDING_LIBC@@
	if unlikely(!ptr)
		return NULL;
@@pp_endif@@
	for (i = 0; i < 9; ++i)
		buf[i] = (wchar_t)ptr[i]; /* Guarantied no unicode in here! */
	return buf;
}

[[wchar, requires_function(_strdate)]]
[[decl_include("<hybrid/typecore.h>")]]
wchar_t *_wstrdate([[nonnull]] wchar_t buf[9]) {
	unsigned int i;
	char abuf[9], *ptr;
	ptr = _strdate(abuf);
@@pp_ifndef __BUILDING_LIBC@@
	if unlikely(!ptr)
		return NULL;
@@pp_endif@@
	for (i = 0; i < 9; ++i)
		buf[i] = (wchar_t)ptr[i]; /* Guarantied no unicode in here! */
	return buf;
}

[[wchar, requires_function(_wstrtime)]]
[[decl_include("<bits/types.h>"), impl_include("<libc/errno.h>")]]
errno_t _wstrtime_s([[outp(buflen)]] wchar_t *buf, size_t buflen) {
	if unlikely(buflen < 9)
		return $ERANGE;
@@pp_ifdef __BUILDING_LIBC@@
	_wstrtime(buf);
@@pp_else@@
	if (!_wstrtime(buf))
		return __libc_geterrno_or(1);
@@pp_endif@@
	return 0;
}

[[wchar, requires_function(_wstrdate)]]
[[decl_include("<bits/types.h>"), impl_include("<libc/errno.h>")]]
errno_t _wstrdate_s([[outp(buflen)]] wchar_t *buf, size_t buflen) {
	if unlikely(buflen < 9)
		return $ERANGE;
@@pp_ifdef __BUILDING_LIBC@@
	_wstrdate(buf);
@@pp_else@@
	if (!_wstrdate(buf))
		return __libc_geterrno_or(1);
@@pp_endif@@
	return 0;
}


%
%
%{
#ifdef __USE_TIME_BITS64
#define _wctime   _wctime64
#define _wctime_s _wctime64_s
#else /* __USE_TIME_BITS64 */
#define _wctime   _wctime32
#define _wctime_s _wctime32_s
#endif /* !__USE_TIME_BITS64 */
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
