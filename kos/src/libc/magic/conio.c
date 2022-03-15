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
/* (#) Portability: DJGPP        (/include/conio.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/crt/conio.h) */
/* (#) Portability: Windows Kits (/ucrt/conio.h) */
}

%[default:section(".text.crt.dos.conio")]

%(auto_source){
#include "../libc/globals.h"
}

%[define_replacement(stdtty = __LOCAL_stdtty)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __USE_DOS
#include <crtdefs.h>
#include <corecrt_wconio.h>
#endif /* __USE_DOS */

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

[[wunused]]
int _kbhit(void);


@@>> _getch(3), _getch_nolock(3)
@@Read a character from the console, without echoing it on-screen
@@@return: * : The character read from the console
@@@return: -1: End-of-file on console
[[wunused]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_getch_nolock")]]
int _getch(void);

[[wunused, alias("_getch"), doc_alias("_getch")]]
int _getch_nolock(void);

@@>> _getche(3), _getche_nolock(3)
@@Read a character from the console, whilst also echoing it on-screen
@@@return: * : The character read from the console
@@@return: -1: End-of-file on console
[[wunused]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_getche_nolock")]]
int _getche(void);

[[wunused, alias("_getche"), doc_alias("_getche")]]
int _getche_nolock(void);

[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_putch_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(fputc))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _putch(int ch) {
	return fputc(ch, stdtty);
}

[[alias("_putch"), doc_alias("_putch")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(fputc_unlocked))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _putch_nolock(int ch) {
	return fputc_unlocked(ch, stdtty);
}

[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("_ungetch_nolock")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(ungetc))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _ungetch(int ch) {
	return ungetc(ch, stdtty);
}

[[alias("_ungetch"), doc_alias("_ungetch")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(ungetc_unlocked))]]
[[impl_include("<libc/template/stdtty.h>")]]
int _ungetch_nolock(int ch) {
	return ungetc_unlocked(ch, stdtty);
}


[[decl_include("<bits/types.h>"), requires_function(_cgets_s)]]
char *_cgets([[nonnull]] char *__restrict buf) {
	char *result = buf + 2;
	size_t readsize;
	if (_cgets_s(result, buf[0], &readsize) != 0)
		result = NULL;
	buf[1] = (char)(unsigned char)readsize;
	return result;
}

[[decl_include("<bits/types.h>")]]
[[requires_function(_getch, _ungetch)]]
errno_t _cgets_s([[outp(bufsize)]] char *buf, size_t bufsize,
                 [[nonnull]] size_t *__restrict p_readsize) {
	int ch;
	if unlikely(!bufsize)
		return DOS_ENOSPC;
	buf[0]      = '\0';
	*p_readsize = 0;
	--bufsize;
	while (bufsize && (ch = _getche()) != -1) {
		if (ch == '\r') {
			ch = _getche();
			if (ch != -1 && ch != '\n')
				_ungetch(ch);
			break;
		}
		if (ch == '\n')
			break;
		*buf++ = (char)(unsigned char)(unsigned int)ch;
		*buf   = '\0';
		++*p_readsize;
		--bufsize;
	}
	return 0;
}

[[impl_include("<libc/template/stdtty.h>")]]
[[requires($has_function(_putch) || (defined(__CRT_HAVE_stdtty) && $has_function(fwrite)))]]
int _cputs([[nonnull]] char const *__restrict str) {
@@pp_if defined(__CRT_HAVE_stdtty) && $has_function(fwrite)@@
	size_t len = strlen(str);
	size_t ok  = fwrite(str, sizeof(char), len, stdtty);
	return ok >= len ? 0 : -1;
@@pp_else@@
	int result = 0;
	do {
		char ch = *str++;
		if (!ch)
			break;
		result = _putch(ch);
	} while (result != -1);
	return result;
@@pp_endif@@
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfprintf))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcprintf($uint64_t options, [[nonnull, format]] char const *format,
                                              $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf(options, stdtty, format, locale, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfprintf_s))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcprintf_s($uint64_t options, [[nonnull, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf_s(options, stdtty, format, locale, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[crt_intern_alias("__conio_common_vcprintf")]] /* Normal printf already supports positional arguments! */
[[impl_include("<libc/template/stdtty.h>")]]
[[requires(defined(__CRT_HAVE_stdtty) && $has_function(__stdio_common_vfprintf_p))]]
__STDC_INT_AS_SSIZE_T __conio_common_vcprintf_p($uint64_t options, [[nonnull, format]] char const *format,
                                                $locale_t locale, $va_list args) {
	return __stdio_common_vfprintf_p(options, stdtty, format, locale, args);
}

[[decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]]
[[requires_dependent_function(_getwche, _ungetwch)]]
[[impl_prefix(
@@push_namespace(local)@@
__LOCAL_LIBC(__conio_common_vcscanf_getc) ssize_t
(__FORMATPRINTER_CC __conio_common_vcscanf_getc)(void *__UNUSED(arg)) {
	return (ssize_t)_getwche();
}
__LOCAL_LIBC(__conio_common_vcscanf_ungetc) ssize_t
(__FORMATPRINTER_CC __conio_common_vcscanf_ungetc)(void *arg, char32_t ch) {
	return _ungetwch((int)(unsigned int)ch);
}
@@pop_namespace@@
)]]
__STDC_INT_AS_SSIZE_T __conio_common_vcscanf($uint64_t options, [[nonnull, format]] char const *format,
                                             $locale_t locale, $va_list args) {
	(void)options;
	(void)locale;
	return format_vscanf(&__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_getc,
	                     &__NAMESPACE_LOCAL_SYM __conio_common_vcscanf_ungetc,
	                     NULL, format, args);
}


/************************************************************************/
/* __conio_common_* wrappers.                                           */
/************************************************************************/
[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcprintf)]]
__STDC_INT_AS_SSIZE_T _vcprintf_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcprintf_s)]]
__STDC_INT_AS_SSIZE_T _vcprintf_s_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcprintf_p)]]
[[crt_intern_alias("_vcprintf_l")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vcprintf_p_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), wunused, impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcscanf)]]
__STDC_INT_AS_SSIZE_T _vcscanf_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, format, locale, args);
}

[[decl_include("<features.h>"), wunused, impl_include("<corecrt_stdio_config.h>"), requires_function(__conio_common_vcscanf)]]
__STDC_INT_AS_SSIZE_T _vcscanf_s_l([[nonnull, format]] char const *format, $locale_t locale, $va_list args) {
	return __conio_common_vcscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS |
	                              _CRT_INTERNAL_SCANF_SECURECRT,
	                              format, locale, args);
}


/************************************************************************/
/* Simple wrappers.                                                     */
/************************************************************************/
[[decl_include("<features.h>"), requires_function(_vcprintf_l)]]
__STDC_INT_AS_SSIZE_T _vcprintf([[nonnull, format]] char const *format, $va_list args) {
	return _vcprintf_l(format, NULL, args);
}

[[decl_include("<features.h>"), requires_function(_vcprintf_s_l)]]
__STDC_INT_AS_SSIZE_T _vcprintf_s([[nonnull, format]] char const *format, $va_list args) {
	return _vcprintf_s_l(format, NULL, args);
}

[[decl_include("<features.h>"), requires_function(_vcprintf_p_l)]]
[[crt_intern_alias("_vcprintf")]] /* Normal printf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vcprintf_p([[nonnull, format]] char const *format, $va_list args) {
	return _vcprintf_p_l(format, NULL, args);
}

[[decl_include("<features.h>"), wunused, requires_function(_vcscanf_l)]]
__STDC_INT_AS_SSIZE_T _vcscanf([[nonnull, format]] char const *format, $va_list args) {
	return _vcscanf_l(format, NULL, args);
}

[[decl_include("<features.h>"), wunused, requires_function(_vcscanf_s_l)]]
__STDC_INT_AS_SSIZE_T _vcscanf_s([[nonnull, format]] char const *format, $va_list args) {
	return _vcscanf_s_l(format, NULL, args);
}



/************************************************************************/
/* Varargs wrappers.                                                    */
/************************************************************************/
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf([[nonnull, format]] char const *format, ...) %{printf("_vcprintf")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vcprintf_l")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_s([[nonnull, format]] char const *format, ...) %{printf("_vcprintf_s")}
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_s_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vcprintf_s_l")}
[[crt_intern_alias("_cprintf")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_p([[nonnull, format]] char const *format, ...) %{printf("_vcprintf_p")}
[[crt_intern_alias("_cprintf_l")]] /* Normal printf already supports positional arguments! */
[[decl_include("<features.h>")]] __STDC_INT_AS_SSIZE_T _cprintf_p_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vcprintf_p_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf([[nonnull, format]] char const *format, ...) %{printf("_vcscanf")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vcscanf_l")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf_s([[nonnull, format]] char const *format, ...) %{printf("_vcscanf_s")}
[[decl_include("<features.h>"), wunused]] __STDC_INT_AS_SSIZE_T _cscanf_s_l([[nonnull, format]] char const *format, $locale_t locale, ...) %{printf("_vcscanf_s_l")}



/************************************************************************/
/* Unescaped aliases                                                    */
/************************************************************************/
%[insert:function(cgets = _cgets)]
%[insert:function(cputs = _cputs)]
%[insert:function(getch = _getch)]
%[insert:function(getche = _getche)]
%[insert:function(kbhit = _kbhit)]
%[insert:function(putch = _putch)]
%[insert:function(ungetch = _ungetch)]
%[insert:function(cprintf = _cprintf)]
%[insert:function(cscanf = _cscanf)]


%{

__SYSDECL_END
#endif /* __CC__ */

}
