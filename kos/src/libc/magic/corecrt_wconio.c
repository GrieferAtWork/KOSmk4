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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wconio.h) */
}

%[default:section(".text.crt.dos.wchar.conio")]

%(auto_source){
#include "../libc/globals.h"
}

%[define_replacement(stdtty = __LOCAL_stdtty)]
%[define_replacement(WEOF = __WEOF)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <asm/crt/stdio.h>
)]%{

#ifdef __USE_DOS
#include <crtdefs.h>
#endif /* __USE_DOS */

#if !defined(WEOF) && defined(__WEOF)
#define WEOF __WEOF
#endif /* !WEOF && __WEOF */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t; /* Errno code (one of `E*' from <errno.h>) */
#endif /* !__errno_t_defined */

}


[[wchar, wunused]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_getwch_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(_getwch_nolock))]]
[[impl_include("<libc/template/stdtty.h>")]]
wint_t _getwch(void) {
	wint_t result;
@@pp_if $has_function(flockfile, funlockfile)@@
	FILE *fp = stdtty;
	flockfile(fp);
@@pp_endif@@
	result = _getwch_nolock();
@@pp_if $has_function(flockfile, funlockfile)@@
	funlockfile(fp);
@@pp_endif@@
	return result;
}

[[wchar, wunused, doc_alias("_getwch")]]
[[requires($extended_include_prefix("<asm/os/termios.h>")
           defined(__ECHO) && defined(__TCSANOW) && defined(__CRT_HAVE_stdtty) &&
           $has_function(fileno, fgetwc_unlocked, tcgetattr, tcsetattr))]]
[[impl_include("<bits/types.h>", "<asm/os/termios.h>", "<bits/os/termios.h>", "<libc/template/stdtty.h>")]]
wint_t _getwch_nolock(void) {
	wint_t result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = fileno(fp);
	tcgetattr(fd, &oios);
	memcpy(&nios, &oios, sizeof(nios));
	nios.@c_lflag@ &= ~__ECHO;
	tcsetattr(fd, __TCSANOW, &nios);
	result = fgetwc_unlocked(fp);
	tcsetattr(fd, __TCSANOW, &oios);
	return result;
}

[[wchar, wunused]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_getwche_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(_getwche_nolock))]]
[[impl_include("<libc/template/stdtty.h>")]]
wint_t _getwche(void) {
	wint_t result;
@@pp_if $has_function(flockfile, funlockfile)@@
	FILE *fp = stdtty;
	flockfile(fp);
@@pp_endif@@
	result = _getwche_nolock();
@@pp_if $has_function(flockfile, funlockfile)@@
	funlockfile(fp);
@@pp_endif@@
	return result;
}

[[wchar, wunused, doc_alias("_getwche")]]
[[requires($extended_include_prefix("<asm/os/termios.h>")
           defined(__ECHO) && defined(__TCSANOW) && defined(__CRT_HAVE_stdtty) &&
           $has_function(fileno, fgetwc_unlocked, tcgetattr, tcsetattr))]]
[[impl_include("<bits/types.h>", "<asm/os/termios.h>", "<bits/os/termios.h>", "<libc/template/stdtty.h>")]]
wint_t _getwche_nolock(void) {
	wint_t result;
	struct termios oios, nios;
	FILE *fp = stdtty;
	fd_t fd  = fileno(fp);
	tcgetattr(fd, &oios);
	memcpy(&nios, &oios, sizeof(nios));
	nios.@c_lflag@ |= __ECHO;
	tcsetattr(fd, __TCSANOW, &nios);
	result = fgetwc_unlocked(fp);
	tcsetattr(fd, __TCSANOW, &oios);
	return result;
}

[[requires(defined(__CRT_HAVE_stdtty) && $has_function(fputwc))]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_putwch_nolock")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[wchar]] wint_t _putwch(wchar_t ch) {
	return fputwc(ch, stdtty);
}

[[requires(defined(__CRT_HAVE_stdtty) && $has_function(fputwc_unlocked))]]
[[impl_include("<libc/template/stdtty.h>")]]
[[wchar]] wint_t _putwch_nolock(wchar_t ch) {
	return fputwc_unlocked(ch, stdtty);
}

[[requires(defined(__CRT_HAVE_stdtty) && $has_function(ungetwc))]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_ungetwch_nolock")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[wchar]] wint_t _ungetwch(wint_t ch) {
	return ungetwc(ch, stdtty);
}

[[requires(defined(__CRT_HAVE_stdtty) && $has_function(ungetwc_unlocked))]]
[[impl_include("<libc/template/stdtty.h>")]]
[[wchar]] wint_t _ungetwch_nolock(wint_t ch) {
	return ungetwc_unlocked(ch, stdtty);
}


[[wchar, decl_include("<bits/types.h>"), requires_function(_cgetws_s)]]
wchar_t *_cgetws([[nonnull]] wchar_t *__restrict buf) {
	wchar_t *result = buf + 2;
	size_t readsize;
	if (_cgetws_s(result, buf[0], &readsize) != 0)
		result = NULL;
	buf[1] = (wchar_t)readsize;
	return result;
}


[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(_getch, _ungetch)]]
[[impl_include("<asm/crt/stdio.h>")]]
errno_t _cgetws_s([[outp(bufsize)]] wchar_t *buf, size_t bufsize,
                  [[nonnull]] size_t *__restrict p_readsize) {
	wchar_t ch;
	if unlikely(!bufsize)
		return $ENOSPC;
	buf[0]      = (wchar_t)'\0';
	*p_readsize = 0;
	--bufsize;
	while (bufsize && (ch = _getwche()) != WEOF) {
		if (ch == (wchar_t)'\r') {
			ch = _getwche();
			if (ch != WEOF && ch != (wchar_t)'\n')
				_ungetwch(ch);
			break;
		}
		if (ch == (wchar_t)'\n')
			break;
		*buf++ = ch;
		*buf   = (wchar_t)'\0';
		++*p_readsize;
		--bufsize;
	}
	return 0;
}


[[wchar, impl_include("<libc/template/stdtty.h>")]]
[[requires($has_function(_putwch) || (defined(__CRT_HAVE_stdtty) && $has_function(file_wprinter)))]]
int _cputws([[nonnull]] wchar_t const *__restrict str) {
@@pp_if defined(__CRT_HAVE_stdtty) && $has_function(file_wprinter)@@
	size_t len = wcslen(str);
	size_t ok  = file_wprinter(stdtty, str, len);
	return ok >= len ? 0 : -1;
@@pp_else@@
	for (;;) {
		wchar_t ch = *str++;
		if (!ch)
			break;
		if (_putwch(ch) == WEOF)
			return -1;
	}
	return 0;
@@pp_endif@@
}






[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfwprintf))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcwprintf($uint64_t options, [[nonnull, format]] wchar_t const *format,
                                               $locale_t locale, $va_list args) {
	return __stdio_common_vfwprintf(options, stdtty, format, locale, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfwprintf_s))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcwprintf_s($uint64_t options, [[nonnull, format]] wchar_t const *format,
                                                 $locale_t locale, $va_list args) {
	return __stdio_common_vfwprintf_s(options, stdtty, format, locale, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[crt_intern_alias("__conio_common_vcwprintf")]] /* Normal printf already supports positional arguments! */
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfwprintf_p))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcwprintf_p($uint64_t options, [[nonnull, format]] wchar_t const *format,
                                                 $locale_t locale, $va_list args) {
	return __stdio_common_vfwprintf_p(options, stdtty, format, locale, args);
}


%[define_wchar_replacement(conio_common_vcwscanf_getc = conio_common_vcc16scanf_getc, conio_common_vcc32scanf_getc)]
%[define_wchar_replacement(conio_common_vcwscanf_ungetc = conio_common_vcc16scanf_ungetc, conio_common_vcc32scanf_ungetc)]

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[wunused, requires_dependent_function(_getwche, _ungetwch), impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(conio_common_vcwscanf_getc) __format_word_t
(__FORMATPRINTER_CC conio_common_vcwscanf_getc)(void *__UNUSED(arg)) {
	return (__format_word_t)_getwche();
}
__LOCAL_LIBC(conio_common_vcwscanf_ungetc) ssize_t
(__FORMATPRINTER_CC conio_common_vcwscanf_ungetc)(void *__UNUSED(arg), __format_word_t word) {
	return _ungetwch((wint_t)word);
}
@@pop_namespace@@
)]]
__STDC_INT_AS_SSIZE_T __conio_common_vcwscanf($uint64_t options, [[nonnull, format]] wchar_t const *format,
                                              $locale_t locale, $va_list args) {
	(void)options;
	(void)locale;
	return format_vwscanf(&__NAMESPACE_LOCAL_SYM conio_common_vcwscanf_getc,
	                      &__NAMESPACE_LOCAL_SYM conio_common_vcwscanf_ungetc,
	                      NULL, format, args);
}



/************************************************************************/
/* __conio_common_* wrappers.                                           */
/************************************************************************/
[[wchar, decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcwprintf)]]
__STDC_INT_AS_SSIZE_T _vcwprintf_l([[nonnull, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcwprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[wchar, decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcwprintf_s)]]
__STDC_INT_AS_SSIZE_T _vcwprintf_s_l([[nonnull, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[wchar, decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcwprintf_p)]]
[[crt_intern_alias("_vcwprintf_l")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vcwprintf_p_l([[nonnull, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcwprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[wchar, decl_include("<features.h>"), wunused, impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcwscanf)]]
__STDC_INT_AS_SSIZE_T _vcwscanf_l([[nonnull, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, format, locale, args);
}

[[wchar, decl_include("<features.h>"), wunused, impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcwscanf)]]
__STDC_INT_AS_SSIZE_T _vcwscanf_s_l([[nonnull, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS |
	                               _CRT_INTERNAL_SCANF_SECURECRT,
	                               format, locale, args);
}


/************************************************************************/
/* Simple wrappers.                                                     */
/************************************************************************/
[[wchar, decl_include("<features.h>"), requires_function(_vcwprintf_l)]]
__STDC_INT_AS_SSIZE_T _vcwprintf([[nonnull, format]] wchar_t const *format, $va_list args) {
	return _vcwprintf_l(format, NULL, args);
}

[[wchar, decl_include("<features.h>"), requires_function(_vcwprintf_s_l)]]
__STDC_INT_AS_SSIZE_T _vcwprintf_s([[nonnull, format]] wchar_t const *format, $va_list args) {
	return _vcwprintf_s_l(format, NULL, args);
}

[[wchar, decl_include("<features.h>"), requires_function(_vcwprintf_p_l)]]
[[crt_intern_alias("_vcwprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vcwprintf_p([[nonnull, format]] const wchar_t *format, $va_list args) {
	return _vcwprintf_p_l(format, NULL, args);
}

[[wchar, decl_include("<features.h>"), wunused, requires_function(_vcwscanf_l)]]
__STDC_INT_AS_SSIZE_T _vcwscanf([[nonnull, format]] wchar_t const *format, $va_list args) {
	return _vcwscanf_l(format, NULL, args);
}

[[wchar, decl_include("<features.h>"), wunused, requires_function(_vcwscanf_s_l)]]
__STDC_INT_AS_SSIZE_T _vcwscanf_s([[nonnull, format]] wchar_t const *format, $va_list args) {
	return _vcwscanf_s_l(format, NULL, args);
}



/************************************************************************/
/* Varargs wrappers.                                                    */
/************************************************************************/
[[wchar, decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cwprintf([[nonnull, format]] wchar_t const *format, ...) %{printf("_vcwprintf")}
[[wchar, decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cwprintf_l([[nonnull, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vcwprintf_l")}
[[wchar, decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cwprintf_s([[nonnull, format]] wchar_t const *format, ...) %{printf("_vcwprintf_s")}
[[wchar, decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cwprintf_s_l([[nonnull, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vcwprintf_s_l")}
[[crt_intern_alias("_cwprintf")]] /* Normal printf already supports positional arguments! */
[[wchar, decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cwprintf_p([[nonnull, format]] wchar_t const *format, ...) %{printf("_vcwprintf_p")}
[[crt_intern_alias("_cwprintf_l")]] /* Normal printf already supports positional arguments! */
[[wchar, decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cwprintf_p_l([[nonnull, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vcwprintf_p_l")}
[[wchar, decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cwscanf([[nonnull, format]] wchar_t const *format, ...) %{printf("_vcwscanf")}
[[wchar, decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cwscanf_l([[nonnull, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vcwscanf_l")}
[[wchar, decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cwscanf_s([[nonnull, format]] wchar_t const *format, ...) %{printf("_vcwscanf_s")}
[[wchar, decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cwscanf_s_l([[nonnull, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vcwscanf_s_l")}




/************************************************************************/
/* Internal char16_t/char32_t variants (currently not exposed)          */
/************************************************************************/
[[hidden]] _getc16ch(*) %{uchar16("_getwch")}
[[hidden]] _getc32ch(*) %{uchar32("_getwch")}
[[hidden]] _getc16ch_nolock(*) %{uchar16("_getwch_nolock")}
[[hidden]] _getc32ch_nolock(*) %{uchar32("_getwch_nolock")}
[[hidden]] _getc16che(*) %{uchar16("_getwche")}
[[hidden]] _getc32che(*) %{uchar32("_getwche")}
[[hidden]] _getc16che_nolock(*) %{uchar16("_getwche_nolock")}
[[hidden]] _getc32che_nolock(*) %{uchar32("_getwche_nolock")}
[[hidden]] _putc16ch(*) %{uchar16("_putwch")}
[[hidden]] _putc32ch(*) %{uchar32("_putwch")}
[[hidden]] _putc16ch_nolock(*) %{uchar16("_putwch_nolock")}
[[hidden]] _putc32ch_nolock(*) %{uchar32("_putwch_nolock")}
[[hidden]] _ungetc16ch(*) %{uchar16("_ungetwch")}
[[hidden]] _ungetc32ch(*) %{uchar32("_ungetwch")}
[[hidden]] _ungetc16ch_nolock(*) %{uchar16("_ungetwch_nolock")}
[[hidden]] _ungetc32ch_nolock(*) %{uchar32("_ungetwch_nolock")}
[[hidden]] _cgetc16s(*) %{uchar16("_cgetws")}
[[hidden]] _cgetc32s(*) %{uchar32("_cgetws")}
[[hidden]] _cgetc16s_s(*) %{uchar16("_cgetws_s")}
[[hidden]] _cgetc32s_s(*) %{uchar32("_cgetws_s")}
[[hidden]] _cputc16s(*) %{uchar16("_cputws")}
[[hidden]] _cputc32s(*) %{uchar32("_cputws")}
[[hidden]] __conio_common_vcc16printf(*) %{uchar16("__conio_common_vcwprintf")}
[[hidden]] __conio_common_vcc32printf(*) %{uchar32("__conio_common_vcwprintf")}
[[hidden]] __conio_common_vcc16printf_s(*) %{uchar16("__conio_common_vcwprintf_s")}
[[hidden]] __conio_common_vcc32printf_s(*) %{uchar32("__conio_common_vcwprintf_s")}
[[hidden]] __conio_common_vcc16printf_p(*) %{uchar16("__conio_common_vcwprintf_p")}
[[hidden]] __conio_common_vcc32printf_p(*) %{uchar32("__conio_common_vcwprintf_p")}
[[hidden]] __conio_common_vcc16scanf(*) %{uchar16("__conio_common_vcwscanf")}
[[hidden]] __conio_common_vcc32scanf(*) %{uchar32("__conio_common_vcwscanf")}
[[hidden]] _vcc16printf_l(*) %{uchar16("_vcwprintf_l")}
[[hidden]] _vcc32printf_l(*) %{uchar32("_vcwprintf_l")}
[[hidden]] _vcc16printf_s_l(*) %{uchar16("_vcwprintf_s_l")}
[[hidden]] _vcc32printf_s_l(*) %{uchar32("_vcwprintf_s_l")}
[[hidden]] _vcc16printf_p_l(*) %{uchar16("_vcwprintf_p_l")}
[[hidden]] _vcc32printf_p_l(*) %{uchar32("_vcwprintf_p_l")}
[[hidden]] _vcc16scanf_l(*) %{uchar16("_vcwscanf_l")}
[[hidden]] _vcc32scanf_l(*) %{uchar32("_vcwscanf_l")}
[[hidden]] _vcc16scanf_s_l(*) %{uchar16("_vcwscanf_s_l")}
[[hidden]] _vcc32scanf_s_l(*) %{uchar32("_vcwscanf_s_l")}
[[hidden]] _vcc16printf(*) %{uchar16("_vcwprintf")}
[[hidden]] _vcc32printf(*) %{uchar32("_vcwprintf")}
[[hidden]] _vcc16printf_s(*) %{uchar16("_vcwprintf_s")}
[[hidden]] _vcc32printf_s(*) %{uchar32("_vcwprintf_s")}
[[hidden]] _vcc16printf_p(*) %{uchar16("_vcwprintf_p")}
[[hidden]] _vcc32printf_p(*) %{uchar32("_vcwprintf_p")}
[[hidden]] _vcc16scanf(*) %{uchar16("_vcwscanf")}
[[hidden]] _vcc32scanf(*) %{uchar32("_vcwscanf")}
[[hidden]] _vcc16scanf_s(*) %{uchar16("_vcwscanf_s")}
[[hidden]] _vcc32scanf_s(*) %{uchar32("_vcwscanf_s")}
[[hidden]] _cc16printf(*) %{uchar16("_cwprintf")}
[[hidden]] _cc32printf(*) %{uchar32("_cwprintf")}
[[hidden]] _cc16printf_l(*) %{uchar16("_cwprintf_l")}
[[hidden]] _cc32printf_l(*) %{uchar32("_cwprintf_l")}
[[hidden]] _cc16printf_s(*) %{uchar16("_cwprintf_s")}
[[hidden]] _cc32printf_s(*) %{uchar32("_cwprintf_s")}
[[hidden]] _cc16printf_s_l(*) %{uchar16("_cwprintf_s_l")}
[[hidden]] _cc32printf_s_l(*) %{uchar32("_cwprintf_s_l")}
[[hidden]] _cc16printf_p(*) %{uchar16("_cwprintf_p")}
[[hidden]] _cc32printf_p(*) %{uchar32("_cwprintf_p")}
[[hidden]] _cc16printf_p_l(*) %{uchar16("_cwprintf_p_l")}
[[hidden]] _cc32printf_p_l(*) %{uchar32("_cwprintf_p_l")}
[[hidden]] _cc16scanf(*) %{uchar16("_cwscanf")}
[[hidden]] _cc32scanf(*) %{uchar32("_cwscanf")}
[[hidden]] _cc16scanf_l(*) %{uchar16("_cwscanf_l")}
[[hidden]] _cc32scanf_l(*) %{uchar32("_cwscanf_l")}
[[hidden]] _cc16scanf_s(*) %{uchar16("_cwscanf_s")}
[[hidden]] _cc32scanf_s(*) %{uchar32("_cwscanf_s")}
[[hidden]] _cc16scanf_s_l(*) %{uchar16("_cwscanf_s_l")}
[[hidden]] _cc32scanf_s_l(*) %{uchar32("_cwscanf_s_l")}


%{

__SYSDECL_END
#endif /* __CC__ */

}
