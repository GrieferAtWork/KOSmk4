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
/* (#) Portability: Windows Kits (/ucrt/corecrt_wstdio.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(oflag_t = __oflag_t)]

%(auto_source){
#include "../libc/globals.h"
}

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <asm/crt/stdio.h>
)]%[insert:prefix(
#include <corecrt_stdio_config.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wint_t_defined
#define __wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__wint_t_defined */

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

#ifndef WEOF
#define WEOF __WEOF
#endif /* !WEOF */

#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */

}


%#ifndef _WSTDIO_DEFINED
%#define _WSTDIO_DEFINED 1


%/* Standard functions (already defined in <wchar.h>) */
%[insert:extern(fgetwc)]
%[insert:extern(fputwc)]
%[insert:guarded_function(getwc = fgetwc)]
%[insert:extern(getwchar)]
%[insert:guarded_function(putwc = fputwc)]
%[insert:extern(putwchar)]
%[insert:extern(ungetwc)]
%[insert:extern(fgetws)]
%[insert:extern(fputws)]
%[insert:extern(vfwprintf)]
%[insert:extern(fwprintf)]
%[insert:extern(vfwscanf)]
%[insert:extern(fwscanf)]
%[insert:extern(vwprintf)]
%[insert:extern(wprintf)]
%[insert:extern(vwscanf)]
%[insert:extern(wscanf)]
%[insert:extern(vswscanf)]
%[insert:extern(swscanf)]


%
%
%
%/* DOS-specific aliases for differently named functions */
%[insert:function(_wfopen = wfopen)]
%[insert:function(_wfreopen = wfreopen)]
%[insert:function(_fgetwchar = getwchar)]
%[insert:function(_fputwchar = putwchar)]
%[insert:function(_wpopen = wpopen)]
%[insert:function(_wremove = wremove)]
%[insert:function(_fgetwc_nolock = fgetwc_unlocked)]
%[insert:function(_fputwc_nolock = fputwc_unlocked)]
%[insert:function(_ungetwc_nolock = ungetwc_unlocked)]
%[insert:function(_getwc_nolock = fgetwc_unlocked)]
%[insert:function(_putwc_nolock = fputwc_unlocked)]


[[section(".text.crt.dos.wchar.errno.utility")]]
[[cp_stdio, wchar, ATTR_COLD, guard("_CRT_WPERROR_DEFINED")]]
[[impl_include("<libc/template/stdstreams.h>", "<libc/errno.h>")]]
[[requires_include("<libc/template/stdstreams.h>", "<libc/errno.h>")]]
[[requires(defined(__LOCAL_stderr) && defined(__libc_geterrno) &&
           $has_function(fprintf) && $has_function(strerror))]]
[[impl_include("<parts/printf-config.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
void _wperror([[in_opt]] wchar_t const *__restrict message) {
@@pp_ifdef __NO_PRINTF_STRERROR@@
	char const *enodesc;
	enodesc = strerror(__libc_geterrno());
	if (message) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
		fprintf(stderr, "%I16s: %I8s\n", message, enodesc);
@@pp_else@@
		fprintf(stderr, "%I32s: %I8s\n", message, enodesc);
@@pp_endif@@
	} else {
		fprintf(stderr, "%I8s\n", enodesc);
	}
@@pp_else@@
	if (message) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
		fprintf(stderr, "%I16s: %m\n", message);
@@pp_else@@
		fprintf(stderr, "%I32s: %m\n", message);
@@pp_endif@@
	} else {
		fprintf(stderr, "%m\n");
	}
@@pp_endif@@
}



%
%
%
%/* DOS-specific functions */
%[default:section(".text.crt.dos.wchar.FILE.locked.access")]

[[wchar, wunused]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_function(_fsopen, convert_wcstombs)]]
FILE *_wfsopen([[in]] wchar_t const *filename,
               [[in]] wchar_t const *mode,
               __STDC_INT_AS_UINT_T sh_flag) {
	FILE *result = NULL;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_filename;
	result = _fsopen(utf8_filename, utf8_mode, sh_flag);
@@pp_if $has_function(free)@@
	free(utf8_mode);
@@pp_endif@@
done_filename:
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
done:
	return result;
}

[[wchar, wunused, decl_include("<bits/types.h>")]]
[[requires_function(fdopen, convert_wcstombs)]]
FILE *_wfdopen($fd_t fd, [[in]] wchar_t const *mode) {
	FILE *result = NULL;
	char *utf8_mode;
	utf8_mode = convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done;
	result = fdopen(fd, utf8_mode);
@@pp_if $has_function(free)@@
	free(utf8_mode);
@@pp_endif@@
done:
	return result;
}

[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(fopen_s, convert_wcstombs)]]
[[impl_include("<libc/errno.h>")]]
$errno_t _wfopen_s([[out]] FILE **pstream,
                   [[in]] wchar_t const *filename,
                   [[in]] wchar_t const *mode) {
	errno_t result;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto err_badalloc;
	utf8_mode = convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto err_badalloc_filename;
	result = fopen_s(pstream, utf8_filename, utf8_mode);
@@pp_if $has_function(free)@@
	free(utf8_mode);
	free(utf8_filename);
@@pp_endif@@
	return result;
err_badalloc_filename:
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
err_badalloc:
@@pp_ifdef ENOMEM@@
	return __libc_geterrno_or(ENOMEM);
@@pp_else@@
	return __libc_geterrno_or(1);
@@pp_endif@@
}

[[wchar, decl_include("<bits/types.h>")]]
[[requires_function(freopen_s, convert_wcstombs)]]
[[impl_include("<libc/errno.h>")]]
$errno_t _wfreopen_s([[out]] FILE **pstream,
                     [[in]] wchar_t const *filename,
                     [[in]] wchar_t const *mode,
                     [[inout_opt]] FILE *stream) {
	errno_t result;
	char *utf8_filename;
	char *utf8_mode;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto err_badalloc;
	utf8_mode = convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto err_badalloc_filename;
	result = freopen_s(pstream, utf8_filename, utf8_mode, stream);
@@pp_if $has_function(free)@@
	free(utf8_mode);
	free(utf8_filename);
@@pp_endif@@
	return result;
err_badalloc_filename:
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
err_badalloc:
@@pp_ifdef ENOMEM@@
	return __libc_geterrno_or(ENOMEM);
@@pp_else@@
	return __libc_geterrno_or(1);
@@pp_endif@@
}



[[wchar, decl_include("<hybrid/typecore.h>")]]
[[requires($has_function(_getws_s))]]
[[section(".text.crt.dos.wchar.FILE.locked.read.read")]]
wchar_t *_getws([[out]] wchar_t *buf) {
	return _getws_s(buf, (size_t)-1);
}

[[wchar, decl_include("<hybrid/typecore.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(fgetws))]]
[[section(".text.crt.dos.wchar.FILE.locked.read.read")]]
[[impl_include("<libc/template/stdstreams.h>")]]
wchar_t *_getws_s([[out(? <= buflen)]] wchar_t *buf, size_t buflen) {
	return fgetws(buf, buflen, stdin);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(fputws))]]
[[section(".text.crt.dos.wchar.FILE.locked.write.write")]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SIZE_T _putws([[in]] wchar_t const *str) {
	return fputws(str, stdout);
}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, section(".text.crt.dos.wchar.fs.utility")]]
wchar_t *_wtempnam([[in_opt]] wchar_t const *directory,
                   [[in_opt]] wchar_t const *file_prefix);

[[decl_include("<bits/types.h>")]]
[[wchar, section(".text.crt.dos.wchar.fs.utility")]]
$errno_t _wtmpnam_s([[out(? <= wchar_count)]] wchar_t *dst, size_t wchar_count);

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, section(".text.crt.dos.wchar.fs.utility")]]
wchar_t *_wtmpnam(wchar_t *buf);


/************************************************************************/
/* The whole printf system                                              */
/************************************************************************/
%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(vfwprintf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vfwprintf($uint64_t options, [[inout]] FILE *stream,
                                               [[in, format]] wchar_t const *format,
                                               $locale_t locale, $va_list args) {
	(void)locale;
	(void)options;
	return vfwprintf(stream, format, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), crt_intern_alias(__stdio_common_vfwprintf), requires_function(__stdio_common_vfwprintf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vfwprintf_s($uint64_t options, [[inout]] FILE *stream,
                                                 [[in, format]] wchar_t const *format,
                                                 $locale_t locale, $va_list args) {
	return __stdio_common_vfwprintf(options, stream, format, locale, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(vfwprintf)]]
[[crt_intern_alias("__stdio_common_vfwprintf")]] /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T __stdio_common_vfwprintf_p($uint64_t options, [[inout]] FILE *stream,
                                                 [[in, format]] wchar_t const *format,
                                                 $locale_t locale, $va_list args) {
	/* NOTE: DOS positional arguments work the same as gLibc's, only that
	 *       glibc and KOS already bake  them into the normal  `wprintf'. */
	(void)locale;
	(void)options;
	return vfwprintf(stream, format, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T __stdio_common_vswprintf($uint64_t options, wchar_t *buf, size_t bufsize,
                                               [[in, format]] wchar_t const *format,
                                               $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)locale;
	result = vswprintf(buf, bufsize, format, args);
	if (!(options & _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR) && (size_t)result > bufsize)
		result = bufsize;
	return result;
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), crt_intern_alias(__stdio_common_vswprintf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vswprintf_s($uint64_t options, wchar_t *buf, size_t bufsize,
                                                 [[in, format]] wchar_t const *format,
                                                 $locale_t locale, $va_list args) {
	return __stdio_common_vswprintf(options, buf, bufsize, format, locale, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<hybrid/__assert.h>")]]
__STDC_INT_AS_SSIZE_T __stdio_common_vsnwprintf_s($uint64_t options, wchar_t *buf, size_t bufsize, size_t maxsize,
                                                  [[in, format]] wchar_t const *format,
                                                  $locale_t locale, $va_list args) {
	__hybrid_assert(bufsize <= maxsize);
	return __stdio_common_vswprintf(options, buf, bufsize, format, locale, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[crt_intern_alias("__stdio_common_vswprintf")]] /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T __stdio_common_vswprintf_p($uint64_t options, wchar_t *buf, size_t bufsize,
                                                 [[in, format]] wchar_t const *format,
                                                 $locale_t locale, $va_list args) {
	__STDC_INT_AS_SSIZE_T result;
	(void)locale;
	/* NOTE: DOS positional arguments work the same as gLibc's, only that
	 *       glibc and KOS already bake  them into the normal  `wprintf'. */
	result = vswprintf(buf, bufsize, format, args);
	if (!(options & _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR) && (size_t)result > bufsize)
		result = bufsize;
	return result;
}

%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(vfwscanf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vfwscanf($uint64_t options, [[inout]] FILE *stream,
                                              [[in, format]] wchar_t const *format,
                                              $locale_t locale, $va_list args) {
	(void)options;
	(void)locale;
	return vfwscanf(stream, format, args);
}

[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(vswscanf)]]
__STDC_INT_AS_SSIZE_T __stdio_common_vswscanf($uint64_t options,
                                              [[in(bufsize)]] [[in(bufsize)]] wchar_t const *buf, size_t bufsize,
                                              [[in, format]] wchar_t const *format,
                                              $locale_t locale, $va_list args) {
	/* TODO: format_wscanf() */
	(void)options;
	(void)buf;
	(void)bufsize;
	(void)format;
	(void)locale;
	(void)args;
	COMPILER_IMPURE();
	return -1;
}










/************************************************************************/
/* __stdio_common_* wrappers                                            */
/************************************************************************/
%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vswprintf)]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	int result = __stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vswprintf_s)]]
__STDC_INT_AS_SSIZE_T _vswprintf_s_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	int result = __stdio_common_vswprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vswprintf_p)]]
[[crt_intern_alias("_vswprintf_c_l")]] /* _vswprintf_l */ /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vswprintf_p_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	int result = __stdio_common_vswprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vswprintf)]]
__STDC_INT_AS_SSIZE_T _vscwprintf_l([[in, format]] wchar_t const *format, $locale_t locale, $va_list args ) {
	int result = __stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR, NULL, 0, format, locale, args);
	return result < 0 ? -1 : result;
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vswprintf_p)]]
[[crt_intern_alias("_vscwprintf_l")]] /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vscwprintf_p_l([[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	int result = __stdio_common_vswprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR, NULL, 0, format, locale, args);
	return result < 0 ? -1 : result;
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>")]]
[[requires_function(__stdio_common_vswprintf), preferred_export_alias("_vswprintf_l")]]
__STDC_INT_AS_SSIZE_T _vswprintf_c_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	int result = __stdio_common_vswprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vsnwprintf_s)]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_s_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, size_t maxsize, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	int result = __stdio_common_vsnwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, buf, bufsize, maxsize, format, locale, args);
	return result < 0 ? -1 : result;
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vfwprintf_s)]]
__STDC_INT_AS_SSIZE_T _vfwprintf_s_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, stream, format, locale, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), requires_function(__stdio_common_vfwprintf_p)]]
[[crt_intern_alias("_vfwprintf_l")]] /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vfwprintf_p_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfwprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS, stream, format, locale, args);
}
%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), wunused, requires_function(__stdio_common_vfscanf)]]
__STDC_INT_AS_SSIZE_T _vfwscanf_l([[inout]] FILE *stream,[[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, stream, format, locale, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"),  wunused, requires_function(__stdio_common_vfscanf)]]
__STDC_INT_AS_SSIZE_T _vfwscanf_s_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vfwscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | _CRT_INTERNAL_SCANF_SECURECRT, stream, format, locale, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), ignore, wunused, requires_function(__stdio_common_vsscanf)]]
__STDC_INT_AS_SSIZE_T _vsnwscanf_l([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vswscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS, buf, bufsize, format, locale, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), impl_include("<corecrt_stdio_config.h>"), ignore, wunused, requires_function(__stdio_common_vsscanf)]]
__STDC_INT_AS_SSIZE_T _vsnwscanf_s_l([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return __stdio_common_vswscanf(_CRT_INTERNAL_LOCAL_SCANF_OPTIONS | _CRT_INTERNAL_SCANF_SECURECRT, buf, bufsize, format, locale, args);
}



/************************************************************************/
/* Direct aliases                                                       */
/************************************************************************/
%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(vwprintf)]]
__STDC_INT_AS_SSIZE_T  _vwprintf_l([[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vwprintf(format, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(vfwprintf)]]
__STDC_INT_AS_SSIZE_T _vfwprintf_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vfwprintf(stream, format, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
__STDC_INT_AS_SSIZE_T __vswprintf_l([[out]] wchar_t *buf, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vswprintf(buf, (size_t)-1, format, args);
}
%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused, requires_function(vwscanf)]]
__STDC_INT_AS_SSIZE_T _vwscanf_l([[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	(void)locale;
	return vwscanf(format, args);
}


/************************************************************************/
/* Misc. wrappers                                                       */
/************************************************************************/
%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
%[insert:function(_vswprintf_l = _vswprintf_c_l)];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vfwprintf_p_l)]]
[[no_crt_impl]] /* This symbol gets defined by `vfwprintf()' in "wchar.c" */
__STDC_INT_AS_SSIZE_T _vfwprintf_p([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $va_list args) {
	return _vfwprintf_p_l(stream, format, NULL, args);
}
%[default:section(".text.crt.dos.wchar.unicode.static.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnwprintf_s_l)]]
__STDC_INT_AS_SSIZE_T _vsnwprintf_s([[out(bufsize)]] wchar_t *buf, size_t bufsize, size_t maxsize, [[in, format]] wchar_t const *format, $va_list args) {
	return _vsnwprintf_s_l(buf, bufsize, maxsize, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnwprintf_l)]]
__STDC_INT_AS_SSIZE_T _vsnwprintf([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $va_list args) {
	return _vsnwprintf_l(buf, bufsize, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vswprintf_c_l)]]
__STDC_INT_AS_SSIZE_T _vswprintf_c([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $va_list args) {
	return _vswprintf_c_l(buf, bufsize, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vswprintf_c_l)]]
__STDC_INT_AS_SSIZE_T _vswprintf([[out]] wchar_t *buf, [[in, format]] wchar_t const *format, $va_list args) {
	return _vswprintf_c_l(buf, (size_t)-1, format, NULL, args); /* _vswprintf_l */
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vwprintf_p_l)]]
[[no_crt_impl]] /* This symbol gets defined by `wprintf()' in "wchar.c" */
__STDC_INT_AS_SSIZE_T _vwprintf_p([[in, format]] wchar_t const *format, $va_list args) {
	return _vwprintf_p_l(format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vswprintf_p_l)]]
[[no_crt_impl]] /* This symbol gets defined by `vswprintf()' in "wchar.c" */
__STDC_INT_AS_SSIZE_T _vswprintf_p([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $va_list args) {
	return _vswprintf_p_l(buf, bufsize, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vscwprintf_l)]]
__STDC_INT_AS_SSIZE_T _vscwprintf([[in, format]] wchar_t const *format, $va_list args) {
	return _vscwprintf_l(format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vscwprintf_p_l)]]
[[crt_intern_alias("_vscwprintf")]] /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vscwprintf_p([[in, format]] wchar_t const *format, $va_list args) {
	return _vscwprintf_p_l(format, NULL, args);
}
%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnwscanf_l)]]
__STDC_INT_AS_SSIZE_T _vswscanf_l([[in]] wchar_t const *buf, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return _vsnwscanf_l(buf, (size_t)-1, format, locale, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnwscanf_s_l)]]
__STDC_INT_AS_SSIZE_T _vswscanf_s_l([[in]] wchar_t const *buf, [[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return _vsnwscanf_s_l(buf, (size_t)-1, format, locale, args);
}
[[ignore, wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnwscanf_l)]]
__STDC_INT_AS_SSIZE_T _vsnwscanf([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, $va_list args) {
	return _vsnwscanf_l(buf, bufsize, format, NULL, args);
}
[[ignore, wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vsnwscanf_s_l)]]
__STDC_INT_AS_SSIZE_T _vsnwscanf_s([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, $va_list args) {
	return _vsnwscanf_s_l(buf, bufsize, format, NULL, args);
}



/************************************************************************/
/* STD-stream wrapper functions                                         */
/************************************************************************/
%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(_vfwprintf_s_l))]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SSIZE_T _vwprintf_s_l([[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return _vfwprintf_s_l(stdout, format, locale, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(_vfwprintf_p_l))]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[crt_intern_alias("_vwprintf_l")]] /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SSIZE_T _vwprintf_p_l([[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return _vfwprintf_p_l(stdout, format, locale, args);
}
%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(_vfwscanf_s_l))]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SSIZE_T _vwscanf_s_l([[in, format]] wchar_t const *format, $locale_t locale, $va_list args) {
	return _vfwscanf_s_l(stdin, format, locale, args);
}


/************************************************************************/
/* Auto-generated printf wrapper functions                              */
/************************************************************************/
%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _fwprintf_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vfwprintf_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _fwprintf_s_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vfwprintf_s_l")}
[[crt_intern_alias("_fwprintf_l")]] /* Normal wprintf already supports positional arguments! */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _fwprintf_p_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vfwprintf_p_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _wprintf_l([[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vwprintf_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _wprintf_s_l([[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vwprintf_s_l")}
[[crt_intern_alias("_wprintf_l")]] /* Normal wprintf already supports positional arguments! */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _wprintf_p_l([[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vwprintf_p_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T __swprintf_l([[out]] wchar_t *buf, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("__vswprintf_l")}
%[default:section(".text.crt.dos.wchar.unicode.static.format.printf")];
[[no_crt_impl]] /* This symbol gets defined by `fwprintf()' in "wchar.c" */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _fwprintf_p([[inout]] FILE *stream, [[in, format]] wchar_t const *format, ...) %{printf("_vfwprintf_p")}
[[no_crt_impl]] /* This symbol gets defined by `wprintf()' in "wchar.c" */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _wprintf_p([[in, format]] wchar_t const *format, ...) %{printf("_vwprintf_p")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _swprintf([[out]] wchar_t *buf, [[in, format]] wchar_t const *format, ...) %{printf("_vswprintf")}

%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
%[insert:function(_swprintf_l = _swprintf_c_l)];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _swprintf_s_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vswprintf_s_l")}
[[crt_intern_alias("_swprintf_c_l")]] /* _swprintf_l */ /* Normal wprintf already supports positional arguments! */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _swprintf_p_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vswprintf_p_l")}
[[preferred_export_alias("_swprintf_l")]]
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _swprintf_c_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vswprintf_c_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snwprintf_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vsnwprintf_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snwprintf_s_l([[out(bufsize)]] wchar_t *buf, size_t bufsize, size_t maxsize, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vsnwprintf_s_l")}
%[default:section(".text.crt.dos.wchar.unicode.static.format.printf")];
[[no_crt_impl]] /* This symbol gets defined by `swprintf()' in "wchar.c" */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _swprintf_p([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, ...) %{printf("_vswprintf_p")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _swprintf_c([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, ...) %{printf("_vswprintf_c")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snwprintf([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, ...) %{printf("_vsnwprintf")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _snwprintf_s([[out(bufsize)]] wchar_t *buf, size_t bufsize, size_t maxsize, [[in, format]] wchar_t const *format, ...) %{printf("_vsnwprintf_s")}

%[default:section(".text.crt.dos.wchar.unicode.locale.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _scwprintf_l([[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vscwprintf_l")}
[[crt_intern_alias("_scwprintf_l")]] /* Normal wprintf already supports positional arguments! */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _scwprintf_p_l([[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vscwprintf_p_l")}
%[default:section(".text.crt.dos.wchar.unicode.static.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _scwprintf([[in, format]] wchar_t const *format, ...) %{printf("_vscwprintf")}
[[crt_intern_alias("_scwprintf")]] /* Normal wprintf already supports positional arguments! */
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T _scwprintf_p([[in, format]] wchar_t const *format, ...) %{printf("_vscwprintf_p")}

%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _fwscanf_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vfwscanf_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _fwscanf_s_l([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vfwscanf_s_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _wscanf_l([[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vwscanf_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _wscanf_s_l([[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vwscanf_s_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _swscanf_l([[in]] wchar_t const *buf, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vswscanf_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _swscanf_s_l([[in]] wchar_t const *buf, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vswscanf_s_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snwscanf_l([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vsnwscanf_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snwscanf([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, ...) %{printf("_vsnwscanf")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snwscanf_s_l([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, $locale_t locale, ...) %{printf("_vsnwscanf_s_l")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T _snwscanf_s([[in(bufsize)]] wchar_t const *buf, size_t bufsize, [[in, format]] wchar_t const *format, ...) %{printf("_vsnwscanf_s")}




/************************************************************************/
/* DOS's "secure" functions                                             */
/************************************************************************/
%#ifdef __USE_DOS_SLIB
%[default:section(".text.crt.dos.wchar.unicode.static.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vfwprintf_s_l)]]
__STDC_INT_AS_SSIZE_T vfwprintf_s([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $va_list args) {
	return _vfwprintf_s_l(stream, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vfwprintf_s_l)]]
__STDC_INT_AS_SSIZE_T vwprintf_s([[in, format]] wchar_t const *format, $va_list args) {
	return _vfwprintf_s_l(stdout, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vswprintf_s_l)]]
__STDC_INT_AS_SSIZE_T vswprintf_s([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, $va_list args) {
	return _vswprintf_s_l(buf, bufsize, format, NULL, args);
}
%[default:section(".text.crt.dos.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vfwscanf_s_l), wunused]]
__STDC_INT_AS_SSIZE_T vfwscanf_s([[inout]] FILE *stream, [[in, format]] wchar_t const *format, $va_list args) {
	return _vfwscanf_s_l(stream, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vfwscanf_s_l), wunused]]
__STDC_INT_AS_SSIZE_T vwscanf_s([[in, format]] wchar_t const *format, $va_list args) {
	return _vfwscanf_s_l(stdin, format, NULL, args);
}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), requires_function(_vswscanf_s_l), wunused]]
__STDC_INT_AS_SSIZE_T vswscanf_s([[in]] wchar_t const *buf, [[in, format]] wchar_t const *format, $va_list args) {
	return _vswscanf_s_l(buf, format, NULL, args);
}

%[default:section(".text.crt.dos.wchar.unicode.static.format.printf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T fwprintf_s([[inout]] FILE *stream, [[in, format]] wchar_t const *format, ...) %{printf("vfwprintf_s")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T wprintf_s([[in, format]] wchar_t const *format, ...) %{printf("vwprintf_s")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]] __STDC_INT_AS_SSIZE_T swprintf_s([[out(bufsize)]] wchar_t *buf, size_t bufsize, [[in, format]] wchar_t const *format, ...) %{printf("vswprintf_s")}
%[default:section(".text.crt.dos.wchar.FILE.locked.read.scanf")];
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T fwscanf_s([[inout]] FILE *stream, [[in, format]] wchar_t const *format, ...) %{printf("vfwscanf_s")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T wscanf_s([[in, format]] wchar_t const *format, ...) %{printf("vwscanf_s")}
[[wchar, decl_include("<features.h>", "<hybrid/typecore.h>"), wunused]] __STDC_INT_AS_SSIZE_T swscanf_s([[in]] wchar_t const *buf, [[in, format]] wchar_t const *format, ...) %{printf("vswscanf_s")}
%#endif /* __USE_DOS_SLIB */

%#endif /* !_WSTDIO_DEFINED */

%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_STDIO_H */
#endif /* __USE_UTF */

}
