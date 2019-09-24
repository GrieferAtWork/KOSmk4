/* Copyright (c) 2019 Griefer@Work                                            *
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

%[define_ccompat_header(cwchar)]

%[define_replacement(wchar_t = __WCHAR_TYPE__)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_wchar_replacement(__SIZEOF_WCHAR_T__ = 2, 4)]
%[define_replacement(rsize_t  = __SIZE_TYPE__)]

%(auto_header){
#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef int errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined 1
typedef size_t rsize_t;
#endif /* !__rsize_t_defined */

}

%{
#include <features.h>
#include <bits/mbstate.h>
#ifdef __USE_KOS
#include <parts/malloca.h>
#endif /* __USE_KOS */
#ifdef __USE_DOS
#include <crtdefs.h>
#include <parts/errno.h>
#endif /* __USE_DOS */

__SYSDECL_BEGIN

/* Define `NULL' */
#ifndef NULL
#define NULL __NULLPTR
#endif

#ifndef WCHAR_MIN
#define WCHAR_MIN __WCHAR_MIN__
#define WCHAR_MAX __WCHAR_MAX__
#endif

#ifndef WEOF
#if __SIZEOF_WCHAR_T__ == 4
#define WEOF             0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define WEOF    (wint_t)(0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif /* !WEOF */

#ifdef __CC__

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __mbstate_t mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

/* Define 'FILE' */
}%(c, ccompat){
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_DOS)
}%{
#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}%(c, ccompat){
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_DOS */
}%{

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined 1
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

/* Define `size_t' */
__NAMESPACE_STD_BEGIN
#ifndef __std_tm_defined
#define __std_tm_defined 1
#ifdef __tm_defined
__NAMESPACE_GLB_USING(tm)
#else /* __tm_defined */
struct tm {
	int         tm_sec;      /* seconds [0, 61]. */
	int         tm_min;      /* minutes [0, 59]. */
	int         tm_hour;     /* hour [0, 23]. */
	int         tm_mday;     /* day of month [1, 31]. */
	int         tm_mon;      /* month of year [0, 11]. */
	int         tm_year;     /* years since 1900. */
	int         tm_wday;     /* day of week [0, 6] (Sunday = 0). */
	int         tm_yday;     /* day of year [0, 365]. */
	int         tm_isdst;    /* daylight savings flag. */
#if defined(__CRT_GLC)
#ifdef __USE_MISC
	long int    tm_gmtoff;   /* Seconds east of UTC. */
	char const *tm_zone;     /* Timezone abbreviation. */
#else /* __USE_MISC */
	long int    __tm_gmtoff; /* Seconds east of UTC. */
	char const *__tm_zone;   /* Timezone abbreviation. */
#endif /* !__USE_MISC */
#endif /* !... */
};
#endif /* !__tm_defined */
#endif /* !__std_tm_defined */
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_wint_t_defined
#define __std_wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __tm_defined
#define __tm_defined 1
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __wint_t_defined
#define __wint_t_defined 1
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

}

%[insert:std]


%[default_impl_section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
[std][ATTR_WUNUSED] btowc:(int ch) -> wint_t {
	/* TODO */
	return ch;
}
[std][ATTR_WUNUSED] wctob:(wint_t ch) -> int {
	/* TODO */
	return ch;
}
[std][wchar]
mbrtowc:([nullable] wchar_t *pwc,
         [inp(maxlen)] char const *__restrict str, size_t maxlen,
         [nullable] mbstate_t *ps) -> size_t {
	/* TODO */
	return 0;
}
[std][wchar]
wcrtomb:([nonnull] char *__restrict str, wchar_t wc,
         [nullable] mbstate_t *ps) -> size_t {
	/* TODO */
	return 0;
}
[std][ATTR_WUNUSED][wchar]
mbrlen:([inp(maxlen)] char const *__restrict str, size_t maxlen,
        [nullable] mbstate_t *ps) -> size_t {
	/* TODO */
	return 0;
}
[std][wchar]
mbsrtowcs:([outp(len)] wchar_t *dst,
           [nonnull] char const **__restrict psrc, size_t len,
           [nullable] mbstate_t *ps) -> size_t {
	/* TODO */
	return 0;
}
[std][wchar]
wcsrtombs:([outp(len)] char *dst,
           [nonnull] wchar_t const **__restrict psrc, size_t len,
           [nullable] mbstate_t *ps) -> size_t {
	/* TODO */
	return 0;
}

%(std,c,ccompat)#ifndef __NO_FPU
[std][wchar]
wcstod:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr) -> double {
	/* TODO */
	return 0;
}
%(std,c,ccompat)#endif /* !__NO_FPU */

[std][wchar]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(wcstoll), alias(wcstoq)]
[if(__SIZEOF_LONG__ == 4), alias(wcsto32)]
[if(__SIZEOF_LONG__ == 8), alias(wcsto64, _wcstoi64)]
[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoimax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstol:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> long %{copy(%auto, str2wcs)}

[std][wchar]
[if(__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(wcstoull), alias(wcstouq)]
[if(__SIZEOF_LONG__ == 4), alias(wcstou32)]
[if(__SIZEOF_LONG__ == 8), alias(wcstou64, _wcstoui64)]
[if(__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoumax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstoul:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> unsigned long %{copy(%auto, str2wcs)}

[std][ATTR_WUNUSED][ATTR_PURE]
[section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
mbsinit:([nullable] mbstate_t const *ps) -> int {
	return !ps || @__MBSTATE_ISINIT@(ps);
}

[std][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wmemcmp:([inp(num_chars)] wchar_t const *s1,
         [inp(num_chars)] wchar_t const *s2,
         size_t num_chars) -> int {
#if __SIZEOF_WCHAR_T__ == 2
	return memcmpw(s1, s2, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return memcmpl(s1, s2, num_chars);
#else
	return memcmp(s1, s2, num_chars * sizeof(wchar_t));
#endif
}

[std][ATTR_RETNONNULL][wchar]
[if(__SIZEOF_WCHAR_T__ == 2), alias(memcpyw)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(memcpyl)]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wmemcpy:([outp(num_chars)] wchar_t *__restrict dst,
         [inp(num_chars)] wchar_t const *__restrict src,
         size_t num_chars) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memcpyw(dst, src, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memcpyl(dst, src, num_chars);
#else
	return (wchar_t *)memcpy(dst, src, num_chars * sizeof(wchar_t));
#endif
}

[std][ATTR_RETNONNULL][wchar]
[if(__SIZEOF_WCHAR_T__ == 2), alias(memmovew)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(memmovel)]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wmemmove:([outp(num_chars)] wchar_t *dst,
          [inp(num_chars)] wchar_t const *src,
          size_t num_chars) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memmovew(dst, src, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memmovel(dst, src, num_chars);
#else
	return (wchar_t *)memmove(dst, src, num_chars * sizeof(wchar_t));
#endif
}

[std][ATTR_RETNONNULL][wchar]
[if(__SIZEOF_WCHAR_T__ == 2), alias(memsetw)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(memsetl)]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wmemset:([outp(num_chars)] wchar_t *dst, wchar_t filler, size_t num_chars) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memsetw(dst, (u16)filler, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memsetl(dst, (u32)filler, num_chars);
#else
	return (wchar_t *)memset(dst, (int)filler, num_chars * sizeof(wchar_t));
#endif
}

[std][std_guard][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcscpy:([nonnull] wchar_t *__restrict buf, [nonnull] wchar_t const *__restrict src) -> wchar_t * {
	return wmemcpy(buf, src, wcslen(src) + 1);
}

[std][std_guard][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcscat:([nonnull] wchar_t *__restrict buf, [nonnull] wchar_t const *__restrict src) -> wchar_t * {
	wmemcpy(wcsend(buf), src, wcslen(src) + 1);
	return buf;
}

[std][std_guard][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsncat:([nonnull] wchar_t *__restrict buf,
         [inp(wcsnlen(src, buflen))] wchar_t const *__restrict src,
         size_t buflen) -> wchar_t * {
	size_t srclen = wcsnlen(src, buflen);
	wchar_t *dst = wcsend(buf);
	wmemcpy(dst, src, srclen);
	dst[srclen] = '\0';
	return buf;
}

[std][std_guard][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsncpy:([nonnull] wchar_t *__restrict buf,
         [inp(wcsnlen(src, buflen))] wchar_t const *__restrict src,
         size_t buflen) -> wchar_t * {
	size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	wmemset(buf+srclen, '\0', buflen - srclen);
	return buf;
}


[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcscmp:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2) -> int %{copy(%auto, str2wcs)}

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsncmp:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2, size_t maxlen) -> int %{copy(%auto, str2wcs)}

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcscoll:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2) -> int %{copy(%auto, str2wcs)}

[std][std_guard][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcsxfrm:([nonnull] wchar_t *dst, [inp(maxlen)] wchar_t const *__restrict src, size_t maxlen) -> size_t %{copy(%auto, str2wcs)}


%[default_impl_section({.text.crt.wchar.FILE.locked.read.getc|.text.crt.dos.wchar.FILE.locked.read.getc})]
[cp_stdio][std][std_guard][wchar]
[requires_include(<features.h>)]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fgetwc))]
[dependency_include(<local/stdstreams.h>)][same_impl]
getwchar:() -> wint_t {
	return fgetwc(@__LOCAL_stdin@);
}
[cp_stdio][std][std_guard][wchar][alias(getwc)] fgetwc:([nonnull] $FILE *__restrict stream) -> wint_t;
[cp_stdio][std][std_guard][wchar] getwc:([nonnull] $FILE *__restrict stream) -> wint_t = fgetwc;

[section({.text.crt.wchar.FILE.locked.write.putc|.text.crt.dos.wchar.FILE.locked.write.putc})]
[cp_stdio][std][std_guard][wchar][requires_include(<features.h>)]
[requires(!defined(__NO_STDSTREAMS) && $has_function(fputwc))]
[dependency_include(<local/stdstreams.h>)][same_impl]
putwchar:(wchar_t wc) -> wint_t {
	return fputwc(wc, @__LOCAL_stdout@);
}

[section({.text.crt.wchar.FILE.locked.write.putc|.text.crt.dos.wchar.FILE.locked.write.putc})]
[cp_stdio][std][std_guard][wchar][alias(putwc)]
fputwc:(wchar_t wc, [nonnull] $FILE *stream) -> wint_t;

[section({.text.crt.wchar.FILE.locked.write.putc|.text.crt.dos.wchar.FILE.locked.write.putc})]
[cp_stdio][std][std_guard][wchar]
putwc:(wchar_t wc, [nonnull] $FILE *stream) -> wint_t = fputwc;



[section({.text.crt.wchar.FILE.locked.read.read|.text.crt.dos.wchar.FILE.locked.read.read})]
[cp_stdio][std][std_guard][wchar][ATTR_WUNUSED][alias(fgetws_unlocked, _fgetws_nolock)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fgetws_unlocked, _fgetws_nolock)]
[requires($has_function(fgetwc) && $has_function(ungetwc) && $has_function(ferror))][same_impl]
[dependency_include(<parts/errno.h>)][same_impl][impl_prefix(
#ifndef @__WEOF@
#if __SIZEOF_WCHAR_T__ == 4
#define @__WEOF@             0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define @__WEOF@    (wint_t)(0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif
)]
fgetws:([outp(bufsize)] wchar_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, [notnull] $FILE *__restrict stream) -> wchar_t * {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef @__ERANGE@
		__libc_seterrno(@__ERANGE@);
#endif /* __ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = fgetwc(stream);
		if (ch == @__WEOF@) {
			if (n == 0 || ferror(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetwc(stream);
			if (ch == @__WEOF@) {
				if (n == 0 || ferror(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			ungetwc(ch, stream);
			break;
		}
		buf[n] = (wchar_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}



[section({.text.crt.wchar.FILE.locked.write.write|.text.crt.dos.wchar.FILE.locked.write.write})]
[cp_stdio][std][std_guard][wchar][same_impl]
[requires($has_function(file_wprinter))][alias(fputws_unlocked, _fputws_nolock)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(fputws_unlocked, _fputws_nolock)]
fputws:([nonnull] wchar_t const *__restrict string, [nonnull] $FILE *__restrict stream) -> __STDC_INT_AS_SIZE_T {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter(stream, string, wcslen(string));
	return result;
}

[section({.text.crt.wchar.FILE.locked.write.putc|.text.crt.dos.wchar.FILE.locked.write.putc})]
[std][std_guard][wchar][alias(ungetwc_unlocked)]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(ungetwc_unlocked)]
ungetwc:(wint_t wc, [nonnull] $FILE *stream) -> wint_t;

[section({.text.crt.wchar.unicode.static.format.strftime|.text.crt.dos.wchar.unicode.static.format.strftime})]
[std][std_guard][wchar][same_impl]
wcsftime:([outp(min(return,buflen))] wchar_t *__restrict buf, size_t buflen,
          [nonnull] wchar_t const *__restrict format,
          [nonnull] struct tm const *__restrict tp) -> size_t {
	/* TODO */
	return 0;
}

%[default_impl_section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
%(std)
%(std)#if !defined(__USE_DOS) || defined(__USE_ISOC95)
[std][std_guard][wchar][noexport][nouser]
[if(!defined(__CRT_DOS_PRIMARY)), preferred_alias(wcstok)][alias(wcstok_s)]
wcstok:([nullable] wchar_t *string,
        [nonnull] wchar_t const *__restrict delim,
        [nonnull] wchar_t **__restrict save_ptr) -> wchar_t *
	%{copy(strtok_r, str2wcs)}
%(std)#endif

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
wcslen:([nonnull] wchar_t const *__restrict string) -> size_t %{copy(%auto, str2wcs)}

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
wcsspn:([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *accept) -> size_t %{copy(%auto, str2wcs)}
[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
wcscspn:([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *reject) -> size_t %{copy(%auto, str2wcs)}

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
wcschr:([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> wchar_t *
	[([nonnull] wchar_t *__restrict haystack, wchar_t needle) -> wchar_t *]
	[([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
wcsrchr:([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> wchar_t *
	[([nonnull] wchar_t *__restrict haystack, wchar_t needle) -> wchar_t *]
	[([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][wchar]
wcspbrk:([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *accept) -> wchar_t *
	[([nonnull] wchar_t *haystack, [nonnull] wchar_t const *accept) -> wchar_t *]
	[([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *accept) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

[std][std_guard][ATTR_WUNUSED][ATTR_PURE][alias(wcswcs)][wchar]
wcsstr:([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle) -> wchar_t *
	[([nonnull] wchar_t *haystack, [nonnull] wchar_t *needle) -> wchar_t *]
	[([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

[std][ATTR_WUNUSED][ATTR_PURE][wchar]
[if(__SIZEOF_WCHAR_T__ == 2), alias(memchrw)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(memchrl)]
wmemchr:([inp(num_chars)] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars) -> wchar_t *
	[([inp(num_chars)] wchar_t *__restrict haystack, wchar_t needle, size_t num_chars) -> wchar_t *]
	[([inp(num_chars)] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars) -> wchar_t const *]
{
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memchrw(haystack, needle, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memchrl(haystack, needle, num_chars);
#else
	return (wchar_t *)memchr(haystack, (int)needle, num_chars * sizeof(wchar_t));
#endif
}

%(std)#if defined(__USE_ISOC95) || defined(__USE_UNIX98)
[std][std_guard]
[section({.text.crt.wchar.FILE.locked.utility|.text.crt.dos.wchar.FILE.locked.utility})]
fwide:([nonnull] $FILE *fp, int mode) -> int {
	return 0;
}
%(std)#endif /* __USE_ISOC95 || __USE_UNIX98 */

%(std)
%(std)#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)
[cp_stdio][std][std_guard][ATTR_LIBC_WPRINTF(2, 3)][wchar]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})]
fwprintf:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vfwprintf))}

[cp_stdio][std][std_guard][ATTR_LIBC_WPRINTF(2, 0)][wchar][requires($has_function(file_wprinter))]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})][same_impl]
vfwprintf:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter, stream, format, args);
}

[cp_stdio][std][std_guard][ATTR_LIBC_WPRINTF(1, 2)][wchar]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})]
wprintf:([nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vwprintf))}

[cp_stdio][std][std_guard][ATTR_LIBC_WPRINTF(1, 0)][wchar]
[requires_include(<features.h>)]
[requires($has_function(vfwprintf) && !defined(__NO_STDSTREAMS))]
[dependency_include(<local/stdstreams.h>)][same_impl]
[section({.text.crt.wchar.FILE.locked.write.printf|.text.crt.dos.wchar.FILE.locked.write.printf})]
vwprintf:([nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return vfwprintf(@__LOCAL_stdout@, format, args);
}

[cp_stdio][std][std_guard][ATTR_LIBC_WSCANF(2, 3)][wchar]
[section({.text.crt.wchar.FILE.locked.read.scanf|.text.crt.dos.wchar.FILE.locked.read.scanf})]
fwscanf:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vfwscanf))}
[cp_stdio][std][std_guard][ATTR_LIBC_WSCANF(1, 2)][wchar]
[section({.text.crt.wchar.FILE.locked.read.scanf|.text.crt.dos.wchar.FILE.locked.read.scanf})]
wscanf:([nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vwscanf))}

[std][std_guard][ATTR_LIBC_WSCANF(2, 3)][wchar]
[section({.text.crt.wchar.unicode.static.format.scanf|.text.crt.dos.wchar.unicode.static.format.scanf})]
swscanf:([nonnull] wchar_t const *__restrict src, [nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vswscanf))}

[std][std_guard][ATTR_LIBC_WPRINTF(3, 0)][wchar]
[section({.text.crt.wchar.unicode.static.format.printf|.text.crt.dos.wchar.unicode.static.format.printf})]
vswprintf:([outp(min(return+1,buflen))] wchar_t *__restrict buf, size_t buflen,
           [nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	/* TODO: format_wprintf() */
	return 0;
}

[std][std_guard][ATTR_LIBC_WPRINTF(3, 4)][wchar]
[section({.text.crt.wchar.unicode.static.format.printf|.text.crt.dos.wchar.unicode.static.format.printf})]
swprintf:([outp(min(return+1,buflen))] wchar_t *__restrict buf, size_t buflen,
          [nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vswprintf))}

%(std)#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

%[default_impl_section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
%(std)

%(std)#ifdef __USE_ISOC99
%(std,c,compat)#ifndef __NO_FPU
[std][std_guard][ATTR_PURE][wchar]
wcstof:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr) -> float
	%{copy(%auto, str2wcs)}
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
[std][std_guard][ATTR_PURE][wchar]
wcstold:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr) -> long double
	%{copy(%auto, str2wcs)}
%(std,c,compat)#endif /* !__NO_FPU */
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */

[std][std_guard][wchar][alias(wcstoq)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(wcstol)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcsto32)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcsto64, _wcstoi64)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoimax)]
wcstoll:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> __LONGLONG %{copy(%auto, str2wcs)}

[std][std_guard][wchar][alias(wcstouq)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(wcstoul)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstou32)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstou64, _wcstoui64)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoumax)]
wcstoull:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> __ULONGLONG %{copy(%auto, str2wcs)}

%[default_impl_section({.text.crt.wchar.FILE.locked.read.scanf|.text.crt.dos.wchar.FILE.locked.read.scanf})]
[cp_stdio][std][std_guard][ATTR_WUNUSED][ATTR_LIBC_WSCANF(2, 0)][wchar]
vfwscanf:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T;
/* TODO: format_scanf() implementation for `vfwscanf'! */

[cp_stdio][std][std_guard][ATTR_WUNUSED][ATTR_LIBC_WSCANF(1, 0)]
[requires_include(<features.h>)]
[requires($has_function(vfwscanf) && !defined(__NO_STDSTREAMS))]
[dependency_include(<local/stdstreams.h>)][wchar][same_impl]
vwscanf:([nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return vfwscanf(@__LOCAL_stdin@, format, args);
}
%[default_impl_section({.text.crt.wchar.unicode.static.format.scanf|.text.crt.dos.wchar.unicode.static.format.scanf})]
[std][std_guard][ATTR_WUNUSED][ATTR_LIBC_WSCANF(2, 0)][wchar]
vswscanf:([nonnull] wchar_t const *__restrict src,
          [nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	/* TODO: format_wscanf() */
	return 0;
}

%(std)#endif /* __USE_ISOC99 */




%{
#ifndef __std_wcstok_defined
#define __std_wcstok_defined 1
/* Define wcstok() incorrectly, the same way DOS does. */
#if defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE_wcstok)
__NAMESPACE_STD_BEGIN
__CDECLARE(__ATTR_NONNULL((2)),wchar_t *,__NOTHROW_NCX,wcstok,(wchar_t *__string,wchar_t const *__restrict __delim),(__string,__delim))
__NAMESPACE_STD_END
#else /* __CRT_DOS_PRIMARY && __CRT_HAVE_wcstok */
#ifdef __CRT_HAVE_wcstok_s
__CREDIRECT(__ATTR_NONNULL((2,3)),wchar_t *,__NOTHROW_NCX,__crt_wcstok,(wchar_t *__string,wchar_t const *__restrict __delim,wchar_t **__restrict __save_ptr),wcstok_s,(__string,__delim,__save_ptr))
#elif defined(__CRT_HAVE_wcstok)
__CREDIRECT(__ATTR_NONNULL((2,3)),wchar_t *,__NOTHROW_NCX,__crt_wcstok,(wchar_t *__string,wchar_t const *__restrict __delim,wchar_t **__restrict __save_ptr),wcstok,(__string,__delim,__save_ptr))
#else
#include <local/wchar/wcstok.h>
#define __crt_wcstok(string, delim, save_ptr) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcstok))(string, delim, save_ptr)
#endif
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK wchar_t *__wcstok_save_ptr = __NULLPTR;
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY wchar_t *__wcstok_save_ptr = __NULLPTR;
#else
__PRIVATE __ATTR_UNUSED wchar_t *__wcstok_save_ptr = __NULLPTR;
#endif
__NAMESPACE_STD_BEGIN
__LOCAL_LIBC(wcstok) __ATTR_NONNULL((2)) wchar_t *
__NOTHROW_NCX(__LIBCCALL wcstok)(wchar_t *__string, wchar_t const *__restrict __delim) {
	return __crt_wcstok(__string, __delim, &__wcstok_save_ptr);
}
__NAMESPACE_STD_END
#endif /* !__CRT_DOS_PRIMARY || !__CRT_HAVE_wcstok */
#endif /* !__std_wcstok_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __wcstok_defined
#define __wcstok_defined 1
__NAMESPACE_STD_USING(wcstok)
#endif /* !__wcstok_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}


[ATTR_WUNUSED][alias(*)]
__mbrlen:([inp(maxlen)] char const *__restrict str, $size_t maxlen,
          [nullable] __mbstate_t *ps) -> $size_t = mbrlen;


%
%#ifdef __USE_XOPEN2K8
[alias(_wcsicmp, wcsicmp)][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcscasecmp:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2) -> int %{copy(%auto, str2wcs)}

[alias(_wcsnicmp, wcsnicmp)][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcsncasecmp:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2, $size_t maxlen) -> int %{copy(%auto, str2wcs)}

[alias(_wcsicmp_l, wcsicmp_l)][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcscasecmp_l:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2, $locale_t locale) -> int %{copy(%auto, str2wcs)}

[alias(_wcsnicmp_l, wcsnicmp_l)][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcsncasecmp_l:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2, $size_t maxlen, $locale_t locale) -> int %{copy(%auto, str2wcs)}

[alias(_wcscoll_l)][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcscoll_l:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2, $locale_t locale) -> int %{copy(%auto, str2wcs)}

[alias(_wcsxfrm_l)][requires($has_function(wcsxfrm))][wchar][same_impl]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcsxfrm_l:(wchar_t *dst, [nonnull] wchar_t const *__restrict src, $size_t maxlen, $locale_t locale) -> $size_t %{copy(%auto, str2wcs)}

[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcpcpy:([nonnull] wchar_t *__restrict dst, [nonnull] wchar_t const *__restrict src) -> wchar_t * {
	return wmempcpy(dst, src, wcslen(src) + 1);
}

[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcpncpy:([nonnull] wchar_t *__restrict buf, [nonnull] wchar_t const *__restrict src, $size_t buflen) -> wchar_t * {
	$size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	wmemset(buf + srclen, '\0', ($size_t)(buflen - srclen));
	return buf + srclen;
}

[wchar][section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
mbsnrtowcs:([nullable] wchar_t *dst,
            [nonnull] char const **__restrict psrc, $size_t nmc, $size_t len,
            [nullable] __mbstate_t *ps) -> $size_t;

[wchar][section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
wcsnrtombs:([nullable] char *dst,
            [nonnull] wchar_t const **__restrict psrc, $size_t nwc, $size_t len,
            [nullable] __mbstate_t *ps) -> $size_t;

[wchar][section({.text.crt.wchar.FILE.locked.access|.text.crt.dos.wchar.FILE.locked.access})]
open_wmemstream:(wchar_t **bufloc, $size_t *sizeloc) -> $FILE *;
%#endif /* __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)

[guard][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnlen:([nonnull] wchar_t const *__restrict string, $size_t maxlen) -> $size_t %{copy(%auto, str2wcs)}

[requires($has_function(malloc))][ATTR_WUNUSED][alias(_wcsdup)]
[ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC][wchar][guard]
[section({.text.crt.wchar.heap.strdup|.text.crt.dos.wchar.heap.strdup})][same_impl]
wcsdup:([nonnull] wchar_t const *__restrict string) -> wchar_t * %{copy(%auto, str2wcs)}

%#endif /* __USE_XOPEN2K8 || __USE_DOS */

%
%#ifdef __USE_XOPEN
[section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
[ATTR_WUNUSED][wchar] wcwidth:(wchar_t ch) -> int;

[ATTR_WUNUSED][wchar]
[section({.text.crt.wchar.unicode.static.mbs|.text.crt.dos.wchar.unicode.static.mbs})]
wcswidth:([inp(num_chars)] wchar_t const *__restrict string, $size_t num_chars) -> int;
%#endif /* __USE_XOPEN */

%
%#if defined(__USE_XOPEN) || defined(__USE_DOS)
%#ifndef __wint_t_defined
%#define __wint_t_defined 1
%__NAMESPACE_STD_USING(wint_t)
%#endif /* !__wint_t_defined */


@@Search for a given `NEEDLE' appearing as a sub-string within `HAYSTACK'
@@If no such needle exists, return `NULL'
[guard][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcswcs:([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle) -> wchar_t *
	[([nonnull] wchar_t *haystack, [nonnull] wchar_t *needle) -> wchar_t *]
	[([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle) -> wchar_t const *]
	= wcsstr;
%#endif /* __USE_XOPEN || __USE_DOS */

%
%#ifdef __USE_GNU
@@Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_PURE][ATTR_WUNUSED][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcschrnul:([nonnull] wchar_t const *haystack, wchar_t needle) -> wchar_t *
	[([nonnull] wchar_t *__restrict haystack, wchar_t needle) -> wchar_t *]
	[([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> wchar_t const *]
	%{copy(%auto, str2wcs)}



[ATTR_RETNONNULL][wchar]
[if(__SIZEOF_WCHAR_T__ == 2), alias(mempcpyw)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(mempcpyl)]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wmempcpy:([outp(num_chars)] wchar_t *__restrict dst,
          [inp(num_chars)] wchar_t const *__restrict src, $size_t num_chars) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)mempcpyw(dst, src, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)mempcpyl(dst, src, num_chars);
#else
	return (wchar_t *)mempcpy(dst, src, num_chars * sizeof(wchar_t));
#endif
}

[std][ATTR_RETNONNULL][wchar]
[if(__SIZEOF_WCHAR_T__ == 2), alias(mempmovew)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(mempmovel)]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wmempmove:([outp(num_chars)] wchar_t *dst,
           [inp(num_chars)] wchar_t const *src, $size_t num_chars) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)mempmovew(dst, src, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)mempmovel(dst, src, num_chars);
#else
	return (wchar_t *)mempmove(dst, src, num_chars * sizeof(wchar_t));
#endif
}

[ATTR_PURE][ATTR_WUNUSED][wchar]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstol_l:([notnull] wchar_t const *__restrict nptr, wchar_t **__restrict endptr, int base, $locale_t locale) -> long %{copy(%auto, str2wcs)}
[ATTR_PURE][ATTR_WUNUSED][wchar]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstoul_l:([notnull] wchar_t const *__restrict nptr, wchar_t **__restrict endptr, int base, $locale_t locale) -> unsigned long %{copy(%auto, str2wcs)}

[wchar]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(wcstol)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcsto32)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcsto64, _wcstoi64)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoimax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstoq:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> __LONGLONG = wcstoll;

[wchar]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(wcstoul)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstou32)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstou64, _wcstoui64)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoumax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstouq:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> __ULONGLONG = wcstoull;

[wchar]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(wcstol_l, _wcstol_l)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(_wcstoi64_l)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoimax_l, _wcstoimax_l)]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstoll_l:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base, $locale_t locale) -> __LONGLONG %{copy(%auto, str2wcs)}

[wchar]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias(wcstoul_l, _wcstoul_l)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(_wcstoui64_l)]
[if(__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(wcstoumax_l, _wcstoumax_l)]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstoull_l:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base, $locale_t locale) -> __ULONGLONG %{copy(%auto, str2wcs)}

%#ifndef __NO_FPU
[alias(_wcstof_l)][ATTR_PURE][ATTR_WUNUSED][wchar]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstof_l:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, $locale_t locale) -> float %{copy(%auto, str2wcs)}

[alias(_wcstod_l)][ATTR_PURE][ATTR_WUNUSED][wchar]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstod_l:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, $locale_t locale) -> double %{copy(%auto, str2wcs)}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[alias(_wcstold_l)][ATTR_PURE][ATTR_WUNUSED][wchar]
[section({.text.crt.wchar.unicode.locale.convert|.text.crt.dos.wchar.unicode.locale.convert})]
wcstold_l:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, $locale_t locale) -> long double %{copy(%auto, str2wcs)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

[cp_stdio][alias(_getwchar_nolock)][requires_include(<features.h>)][wchar]
[requires($has_function(fgetwc_unlocked) && !defined(__NO_STDSTREAMS))][same_impl]
[section({.text.crt.wchar.FILE.unlocked.read.getc|.text.crt.dos.wchar.FILE.unlocked.read.getc})]
getwchar_unlocked:() -> wint_t {
	return fgetwc_unlocked(@__LOCAL_stdin@);
}

[cp_stdio][alias(_putwchar_nolock)][requires_include(<features.h>)][wchar]
[requires($has_function(fputwc_unlocked) && !defined(__NO_STDSTREAMS))][same_impl]
[section({.text.crt.wchar.FILE.unlocked.write.putc|.text.crt.dos.wchar.FILE.unlocked.write.putc})]
putwchar_unlocked:(wchar_t wc) -> wint_t {
	return fputwc_unlocked(wc, @__LOCAL_stdin@);
}

[cp_stdio][alias(fgetwc_unlocked, _fgetwc_nolock)][wchar]
[section({.text.crt.wchar.FILE.unlocked.read.getc|.text.crt.dos.wchar.FILE.unlocked.read.getc})]
getwc_unlocked:([notnull] $FILE *__restrict stream) -> wint_t = fgetwc_unlocked;

[cp_stdio][alias(fputwc_unlocked, _fputwc_nolock)][wchar]
[section({.text.crt.wchar.FILE.unlocked.write.putc|.text.crt.dos.wchar.FILE.unlocked.write.putc})]
putwc_unlocked:(wchar_t wc, [notnull] $FILE *__restrict stream) -> wint_t = fputwc_unlocked;

[cp_stdio][alias(_fgetwc_nolock)][wchar]
[section({.text.crt.wchar.FILE.unlocked.read.getc|.text.crt.dos.wchar.FILE.unlocked.read.getc})]
fgetwc_unlocked:([notnull] $FILE *__restrict stream) -> wint_t;

[cp_stdio][alias(_fputwc_nolock)][wchar]
[section({.text.crt.wchar.FILE.unlocked.write.putc|.text.crt.dos.wchar.FILE.unlocked.write.putc})]
fputwc_unlocked:(wchar_t wc, [notnull] $FILE *__restrict stream) -> wint_t;

[cp_stdio][alias(fgetws)][alias(_fgetws_nolock)][wchar][dependency_include(<parts/errno.h>)][same_impl]
[section({.text.crt.wchar.FILE.unlocked.read.read|.text.crt.dos.wchar.FILE.unlocked.read.read})]
[requires($has_function(fgetwc_unlocked) && $has_function(ungetwc_unlocked) && $has_function(ferror_unlocked))][same_impl]
[impl_prefix(
#ifndef @__WEOF@
#if __SIZEOF_WCHAR_T__ == 4
#define @__WEOF@             0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define @__WEOF@    (wint_t)(0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif
)]
fgetws_unlocked:([outp(bufsize)] wchar_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize, [notnull] $FILE *__restrict stream) -> wchar_t * {
	$size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
#ifdef @__ERANGE@
		__libc_seterrno(@__ERANGE@);
#endif /* __ERANGE */
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = fgetwc_unlocked(stream);
		if (ch == @__WEOF@) {
			if (n == 0 || ferror_unlocked(stream))
				return NULL;
			break;
		}
		if (ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = '\n';
			ch = fgetwc_unlocked(stream);
			if (ch == @__WEOF@) {
				if (n == 0 || ferror_unlocked(stream))
					return NULL;
				break;
			}
			if (ch == '\r')
				continue;
			ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (wchar_t)ch;
		if (ch == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}

[section({.text.crt.wchar.FILE.unlocked.write.write|.text.crt.dos.wchar.FILE.unlocked.write.write})]
[cp_stdio][alias(_fputws_nolock)][wchar][same_impl][requires($has_function(file_wprinter_unlocked))]
fputws_unlocked:([notnull] wchar_t const *__restrict string, [notnull] $FILE *__restrict stream) -> __STDC_INT_AS_SIZE_T {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter_unlocked(stream, string, wcslen(string));
	return result;
}


[wchar][same_impl]
[section({.text.crt.wchar.unicode.locale.format.strftime|.text.crt.dos.wchar.unicode.locale.format.strftime})]
wcsftime_l:([outp(maxsize)] wchar_t *__restrict buf, $size_t maxsize,
            [notnull] wchar_t const *__restrict format,
            [notnull] struct tm const *__restrict tp, $locale_t locale) -> $size_t {
	(void)locale;
	return wcsftime(buf, maxsize, format, tp);
}

%#endif /* __USE_GNU */

%
%
%
%

%#ifdef __USE_KOS
%
%/* KOS FILE extension functions. */
%

%[default_impl_section(.text.crt.wchar.FILE.locked.write.write)]
@@For use with `format_printf()' and friends: Prints to a `FILE *' closure argument
[cp_stdio][noexport]
[if(defined(__USE_STDIO_UNLOCKED)), preferred_alias(file_wprinter_unlocked)]
[alias(file_wprinter_unlocked)][same_impl][requires($has_function(fputwc))]
[impl_prefix(
#ifndef @__WEOF@
#if __SIZEOF_WCHAR_T__ == 4
#define @__WEOF@             0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define @__WEOF@    (wint_t)(0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif
)][wchar]
file_wprinter:([nonnull] void *arg, [inp(datalen)] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t {
	$size_t i;
	for (i = 0; i < datalen; ++i) {
		if (fputwc(data[i], ($FILE *)arg) == @__WEOF@)
			break;
	}
	return (ssize_t)i;
}

%[default_impl_section(.text.crt.wchar.FILE.unlocked.write.write)]
@@Same as `file_wprinter()', but performs I/O without acquiring a lock to `($FILE *)ARG'
[cp_stdio][alias(file_wprinter)][noexport]
[same_impl][requires($has_function(fputwc_unlocked))]
[impl_prefix(
#ifndef @__WEOF@
#if __SIZEOF_WCHAR_T__ == 4
#define @__WEOF@             0xffffffffu
#else /* __SIZEOF_WCHAR_T__ == 4 */
#define @__WEOF@    (wint_t)(0xffff)
#endif /* __SIZEOF_WCHAR_T__ != 4 */
#endif
)][wchar]
file_wprinter_unlocked:([nonnull] void *arg, [inp(datalen)] wchar_t const *__restrict data, $size_t datalen) -> $ssize_t {
	$size_t i;
	for (i = 0; i < datalen; ++i) {
		if (fputwc_unlocked(data[i], ($FILE *)arg) == @__WEOF@)
			break;
	}
	return (ssize_t)i;
}


[wchar][user][section({.text.crt.wchar.FILE.unlocked.write.putc|.text.crt.dos.wchar.FILE.unlocked.write.putc})]
ungetwc_unlocked:(wint_t ch, [nonnull] $FILE *__restrict stream) -> wint_t = ungetwc;

[cp_stdio][ATTR_LIBC_WPRINTF(2, 0)][wchar][requires($has_function(file_wprinter_unlocked))]
[section({.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf})][same_impl]
vfwprintf_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter_unlocked, stream, format, args);
}

[cp_stdio][ATTR_LIBC_WPRINTF(2, 3)][wchar]
[section({.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf})]
fwprintf_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vfwprintf_unlocked))}

[cp_stdio][ATTR_LIBC_WPRINTF(1, 2)][wchar]
[section({.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf})]
wprintf_unlocked:([nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T
	%{auto_block(printf(vwprintf_unlocked))}

[cp_stdio][ATTR_LIBC_WPRINTF(1, 0)][wchar]
[requires_include(<features.h>)]
[requires($has_function(vfwprintf_unlocked) && !defined(__NO_STDSTREAMS))]
[dependency_include(<local/stdstreams.h>)][same_impl]
[section({.text.crt.wchar.FILE.unlocked.write.printf|.text.crt.dos.wchar.FILE.unlocked.write.printf})]
vwprintf_unlocked:([nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T {
	return vfwprintf_unlocked(@__LOCAL_stdout@, format, args);
}

%[default_impl_section({.text.crt.wchar.FILE.unlocked.read.scanf|.text.crt.dos.wchar.FILE.unlocked.read.scanf})]
[cp_stdio][ATTR_WUNUSED][ATTR_LIBC_WSCANF(2, 0)][wchar]
vfwscanf_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vfwscanf;

[cp_stdio][ATTR_LIBC_SCANF(1, 0)][ATTR_WUNUSED][user][wchar]
vwscanf_unlocked:([nonnull] wchar_t const *__restrict format, $va_list args) -> __STDC_INT_AS_SIZE_T = vwscanf;

[cp_stdio][ATTR_LIBC_SCANF(2, 3)][ATTR_WUNUSED][user][wchar]
fwscanf_unlocked:([nonnull] $FILE *__restrict stream, [nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T = fwscanf;

[cp_stdio][ATTR_LIBC_SCANF(1, 2)][ATTR_WUNUSED][user][wchar]
wscanf_unlocked:([nonnull] wchar_t const *__restrict format, ...) -> __STDC_INT_AS_SIZE_T = wscanf;


%
%
%
%



/* KOS String extension functions. */
@@Same as `STR+wcslen(STR)'
[ATTR_WUNUSED][ATTR_PURE][wchar][ATTR_RETNONNULL]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsend:([notnull] wchar_t const *__restrict string) -> wchar_t *
	[([notnull] wchar_t *__restrict string) -> wchar_t *]
	[([notnull] wchar_t const *__restrict string) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

@@Same as `STR+wcsnlen(STR, MAX_CHARS)'
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnend:([inp(maxlen)] wchar_t const *__restrict string, $size_t maxlen) -> wchar_t *
	[([inp(maxlen)] wchar_t *__restrict string, $size_t maxlen) -> wchar_t *]
	[([inp(maxlen)] wchar_t const *__restrict string, $size_t maxlen) -> wchar_t const *]
	%{copy(%auto, str2wcs)}


[wchar][ATTR_PURE][ATTR_WUNUSED]
[if(__SIZEOF_LONG__ == 4), alias(wcstoul)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstoull, wcstouq)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstoumax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstou32:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> $uint32_t %{copy(%auto, str2wcs)}

[wchar][ATTR_PURE][ATTR_WUNUSED]
[if(__SIZEOF_LONG__ == 4), alias(wcstol)]
[if(__SIZEOF_LONG_LONG__ == 4), alias(wcstoll, wcstoq)]
[if(__SIZEOF_INTMAX_T__ == 4), alias(wcstoimax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcsto32:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> $int32_t %{copy(%auto, str2wcs)}

%#ifdef __UINT64_TYPE__
[wchar][ATTR_PURE][ATTR_WUNUSED][alias(_wcstoui64)]
[if(__SIZEOF_LONG__ == 8), alias(wcstoul)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstoull), alias(wcstouq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstoumax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcstou64:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> $uint64_t %{copy(%auto, str2wcs)}

[wchar][ATTR_PURE][ATTR_WUNUSED][alias(_wcstoi64)]
[if(__SIZEOF_LONG__ == 8), alias(wcstol)]
[if(__SIZEOF_LONG_LONG__ == 8), alias(wcstoll), alias(wcstoq)]
[if(__SIZEOF_INTMAX_T__ == 8), alias(wcstoimax)]
[section({.text.crt.wchar.unicode.static.convert|.text.crt.dos.wchar.unicode.static.convert})]
wcsto64:([notnull] wchar_t const *__restrict nptr, [nullable] wchar_t **endptr, int base) -> $int64_t %{copy(%auto, str2wcs)}
%#endif /* __UINT64_TYPE__ */
%
%#ifdef _PROCESS_H
%#ifndef __TWARGV
%#ifdef __USE_DOS
%#   define __TWARGV wchar_t const *const *__restrict ___argv
%#   define __TWENVP wchar_t const *const *__restrict ___envp
%#else
%#   define __TWARGV wchar_t *const ___argv[__restrict_arr]
%#   define __TWENVP wchar_t *const ___envp[__restrict_arr]
%#endif
%#endif /* !__TWARGV */
%[insert:extern(wexecv)]
%[insert:extern(wexecve)]
%[insert:extern(wexecvp)]
%[insert:extern(wexecvpe)]
%[insert:extern(wexecl)]
%[insert:extern(wexecle)]
%[insert:extern(wexeclp)]
%[insert:extern(wexeclpe)]
%[insert:extern(wspawnv)]
%[insert:extern(wspawnve)]
%[insert:extern(wspawnvp)]
%[insert:extern(wspawnvpe)]
%[insert:extern(wspawnl)]
%[insert:extern(wspawnle)]
%[insert:extern(wspawnlp)]
%[insert:extern(wspawnlpe)]
%[insert:extern(wsystem)]
%#endif /* _PROCESS_H */

%
[alias(_wcsncoll)][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcsncoll:([inp(maxlen)] wchar_t const *s1, [inp(maxlen)] wchar_t const *s2, $size_t maxlen) -> int %{copy(%auto, str2wcs)}

[alias(_wcsicoll, wcsicoll, wcscasecmp, _wcsicmp, wcsicmp)][wchar]
[ATTR_WUNUSED][ATTR_PURE]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcscasecoll:([notnull] wchar_t const *s1, [notnull] wchar_t const *s2) -> int %{copy(%auto, str2wcs)}

[alias(_wcsnicoll, wcsncasecmp, _wcsnicmp, wcsnicmp)][wchar]
[ATTR_WUNUSED][ATTR_PURE]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcsncasecoll:([inp(maxlen)] wchar_t const *s1, [inp(maxlen)] wchar_t const *s2, $size_t maxlen) -> int %{copy(%auto, str2wcs)}

[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnrev:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memrevw(str, wcsnlen(str, maxlen));
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memrevl(str, wcsnlen(str, maxlen));
#else
	return (wchar_t *)memrev(str, wcsnlen(str, maxlen) * sizeof(wchar_t));
#endif
}

[ATTR_RETNONNULL]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcsnlwr:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen) -> wchar_t * %{copy(%auto, str2wcs)}

[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcsnupr:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen) -> wchar_t * %{copy(%auto, str2wcs)}

[ATTR_WUNUSED][ATTR_PURE][alias(wcswcs)][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wcscasestr:([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle) -> wchar_t *
	[([nonnull] wchar_t *haystack, [nonnull] wchar_t *needle) -> wchar_t *]
	[([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

@@Same as wcscpy, but return a pointer after the last written character
[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcspcpy:([nonnull] wchar_t *__restrict buf, [nonnull] wchar_t const *__restrict src) -> wchar_t * {
	return wmempcpy(buf, src, wcslen(src) + 1);
}
@@Same as wcsncpy, but return a pointer after the last written character
[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcspncpy:([outp(buflen)] wchar_t *__restrict buf, [nonnull] wchar_t const *__restrict src, $size_t buflen) -> wchar_t * {
	$size_t srclen = wcsnlen(src, buflen);
	wmemcpy(buf, src, srclen);
	return wmempset(buf+srclen, '\0', buflen - srclen);
}
@@Same as wmemset, but return a pointer after the last written character
[ATTR_RETNONNULL][wchar]
[if(__SIZEOF_WCHAR_T__ == 2), alias(mempsetw)]
[if(__SIZEOF_WCHAR_T__ == 4), alias(mempsetl)]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wmempset:([outp(num_chars)] wchar_t *dst, wchar_t filler, $size_t num_chars) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)mempsetw(dst, (u16)filler, num_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)mempsetl(dst, (u32)filler, num_chars);
#else
	return (wchar_t *)mempset(dst, (int)filler, num_chars * sizeof(wchar_t));
#endif
}


@@Same as `wcschr', but don't exceed `MAX_CHARS' characters.
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnchr:([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *
	[([inp(maxlen)] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *]
	[([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

@@Same as `wcsrchr', but don't exceed `MAX_CHARS' characters.
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnrchr:([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *
	[([inp(maxlen)] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *]
	[([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

[wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcssep:([nonnull] wchar_t **__restrict stringp,
        [nonnull] wchar_t const *__restrict delim) -> wchar_t * %{copy(%auto, str2wcs)}

[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsfry:([nonnull] wchar_t *__restrict string) -> wchar_t * %{copy(%auto, str2wcs)}

[requires($has_function(malloc))][ATTR_WUNUSED]
[ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC][wchar]
[section({.text.crt.wchar.heap.strdup|.text.crt.dos.wchar.heap.strdup})][same_impl]
wcsndup:([inp(max_chars)] wchar_t const *__restrict string, $size_t max_chars) -> wchar_t * %{copy(%auto, str2wcs)}


@@Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_WUNUSED][ATTR_PURE][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsrchrnul:([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> wchar_t *
	[([nonnull] wchar_t *__restrict haystack, wchar_t needle) -> wchar_t *]
	[([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

@@Same as `wcsnchr', but return `wcsnend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_WUNUSED][ATTR_PURE][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnchrnul:([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *
	[([inp(maxlen)] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *]
	[([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

@@Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found.
[ATTR_WUNUSED][ATTR_PURE][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnrchrnul:([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *
	[([inp(maxlen)] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t *]
	[([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

@@Same as `wcschrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsoff:([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> $size_t %{copy(%auto, str2wcs)}

@@Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsroff:([nonnull] wchar_t const *__restrict haystack, wchar_t needle) -> $size_t %{copy(%auto, str2wcs)}

@@Same as `wcsnchrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnoff:([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> $size_t %{copy(%auto, str2wcs)}

@@Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsnroff:([inp(maxlen)] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen) -> $size_t %{copy(%auto, str2wcs)}

[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
[dependency_include(<parts/malloca.h>)]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
[ATTR_WUNUSED][ATTR_PURE][wchar]
fuzzy_wmemcmp:([inp(s1_chars)] wchar_t const *s1, $size_t s1_chars,
               [inp(s2_chars)] wchar_t const *s2, $size_t s2_chars) -> $size_t {
#if __SIZEOF_WCHAR_T__ == 2
	return fuzzy_memcmpw(s1, s1_chars, s2, s2_chars);
#elif __SIZEOF_WCHAR_T__ == 4
	return fuzzy_memcmpl(s1, s1_chars, s2, s2_chars);
#else
	return fuzzy_memcmp(s1, s1_chars * sizeof(wchar_t), s2, s2_chars * sizeof(wchar_t));
#endif
}

[ATTR_WUNUSED][ATTR_PURE]
[dependency_include(<parts/malloca.h>)][wchar]
[same_impl][requires($has_function(fuzzy_wmemcmp))][export]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
fuzzy_wcscmp:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2) -> $size_t {
	return fuzzy_wmemcmp(s1, wcslen(s1), s2, wcslen(s2));
}
[ATTR_WUNUSED][ATTR_PURE]
[dependency_include(<parts/malloca.h>)][wchar]
[same_impl][requires($has_function(fuzzy_wmemcmp))][export]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
fuzzy_wcsncmp:([inp(s1_maxlen)] wchar_t const *s1, $size_t s1_maxlen,
               [inp(s2_maxlen)] wchar_t const *s2, $size_t s2_maxlen) -> $size_t {
	return fuzzy_wmemcmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

[dependency_include(<parts/malloca.h>)]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
fuzzy_wmemcasecmp:([inp(s1_bytes)] wchar_t const *s1, $size_t s1_bytes,
                   [inp(s2_bytes)] wchar_t const *s2, $size_t s2_bytes) -> $size_t
	%{copy(fuzzy_memcasecmp, str2wcs)}

[ATTR_WUNUSED][ATTR_PURE]
[dependency_include(<parts/malloca.h>)][wchar]
[same_impl][requires($has_function(fuzzy_wmemcasecmp))][export]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
fuzzy_wcscasecmp:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2) -> $size_t {
	return fuzzy_wmemcasecmp(s1, wcslen(s1), s2, wcslen(s2));
}

[ATTR_WUNUSED][ATTR_PURE]
[dependency_include(<parts/malloca.h>)][wchar]
[same_impl][requires($has_function(fuzzy_wmemcasecmp))][export]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
fuzzy_wcsncasecmp:([inp(s1_maxlen)] wchar_t const *s1, $size_t s1_maxlen,
                   [inp(s2_maxlen)] wchar_t const *s2, $size_t s2_maxlen) -> $size_t {
	return fuzzy_wmemcasecmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wildwcscmp:([nonnull] wchar_t const *pattern, [nonnull] wchar_t const *string) -> int %{copy(wildstrcmp, str2wcs)}

[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.static.memory|.text.crt.dos.wchar.unicode.static.memory})]
wildwcscasecmp:([nonnull] wchar_t const *pattern, [nonnull] wchar_t const *string) -> int
	%{copy(wildstrcasecmp, str2wcs)}

[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.string.memory|.text.crt.dos.wchar.string.memory})]
wcsverscmp:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2) -> int %{copy(%auto, str2wcs)}






%
%#ifdef __USE_XOPEN2K8
[alias(_wcsncoll_l)][ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcsncoll_l:([inp(maxlen)] wchar_t const *s1,
            [inp(maxlen)] wchar_t const *s2,
            $size_t maxlen, $locale_t locale) -> int %{copy(%auto, str2wcs)}

[alias(_wcsicoll_l, wcscasecmp_l, _wcsicmp_l)]
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcscasecoll_l:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2, $locale_t locale) -> int %{copy(%auto, str2wcs)}

[alias(_wcsnicoll_l, wcsncasecmp_l, _wcsnicmp_l)]
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcsncasecoll_l:([inp(maxlen)] wchar_t const *s1,
                [inp(maxlen)] wchar_t const *s2, $size_t maxlen, $locale_t locale) -> int %{copy(%auto, str2wcs)}

[alias(_wcslwr_l)][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcslwr_l:([nonnull] wchar_t *__restrict str, $locale_t locale) -> wchar_t * %{copy(%auto, str2wcs)}

[alias(_wcsupr_l)][ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcsupr_l:([nonnull] wchar_t *__restrict str, $locale_t locale) -> wchar_t * %{copy(%auto, str2wcs)}

[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcsnlwr_l:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen, $locale_t locale) -> wchar_t * %{copy(%auto, str2wcs)}

[ATTR_RETNONNULL][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcsnupr_l:([inoutp(maxlen)] wchar_t *__restrict str, $size_t maxlen, $locale_t locale) -> wchar_t * %{copy(%auto, str2wcs)}

[ATTR_WUNUSED][ATTR_PURE][alias(wcswcs)][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wcscasestr_l:([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle, $locale_t locale) -> wchar_t *
	[([nonnull] wchar_t *haystack, [nonnull] wchar_t *needle, $locale_t locale) -> wchar_t *]
	[([nonnull] wchar_t const *haystack, [nonnull] wchar_t const *needle, $locale_t locale) -> wchar_t const *]
	%{copy(%auto, str2wcs)}

[dependency_include(<parts/malloca.h>)]
[same_impl][requires(!defined(__NO_MALLOCA))][export]
[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
fuzzy_wmemcasecmp_l:([inp(s1_bytes)] wchar_t const *s1, $size_t s1_bytes,
                     [inp(s2_bytes)] wchar_t const *s2, $size_t s2_bytes, $locale_t locale) -> $size_t
	%{copy(fuzzy_memcasecmp_l, str2wcs)}

[ATTR_WUNUSED][ATTR_PURE]
[dependency_include(<parts/malloca.h>)][wchar]
[same_impl][requires($has_function(fuzzy_wmemcasecmp_l))][export]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
fuzzy_wcscasecmp_l:([nonnull] wchar_t const *s1, [nonnull] wchar_t const *s2, $locale_t locale) -> $size_t {
	return fuzzy_wmemcasecmp_l(s1, wcslen(s1), s2, wcslen(s2), locale);
}
[ATTR_WUNUSED][ATTR_PURE]
[dependency_include(<parts/malloca.h>)][wchar]
[same_impl][requires($has_function(fuzzy_wmemcasecmp_l))][export]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
fuzzy_wcsncasecmp_l:([inp(s1_maxlen)] wchar_t const *s1, $size_t s1_maxlen,
                     [inp(s2_maxlen)] wchar_t const *s2, $size_t s2_maxlen, $locale_t locale) -> $size_t {
	return fuzzy_wmemcasecmp_l(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen), locale);
}

[ATTR_WUNUSED][ATTR_PURE][wchar]
[section({.text.crt.wchar.unicode.locale.memory|.text.crt.dos.wchar.unicode.locale.memory})]
wildwcscasecmp_l:([nonnull] wchar_t const *pattern, [nonnull] wchar_t const *string, $locale_t locale) -> int
	%{copy(wildstrcasecmp_l, str2wcs)}

%#endif /* __USE_XOPEN2K8 */


%#endif /* __USE_KOS */
















%
%
%
%

%
%#ifdef __USE_DOS
%#ifndef _WSTRING_DEFINED
%#define _WSTRING_DEFINED 1

[ATTR_WUNUSED][wchar]
[ATTR_MALL_DEFAULT_ALIGNED][ATTR_MALLOC][ATTR_NONNULL((1))][guard]
[section({.text.crt.wchar.heap.strdup|.text.crt.dos.wchar.heap.strdup})]
_wcsdup:(wchar_t const *__restrict string) -> wchar_t * = wcsdup;

%
%#ifdef __USE_DOS_SLIB
[ATTR_NONNULL((1, 3))][dependency_include(<parts/errno.h>)][wchar]
[section(.text.crt.dos.wchar.string.memory)][guard]
wcscat_s:(wchar_t *dst, $size_t dstsize, wchar_t const *src) -> $errno_t
	%{copy(%auto, str2wcs)}

[dependency_include(<parts/errno.h>)][wchar]
[section(.text.crt.dos.wchar.string.memory)][guard]
wcscpy_s:(wchar_t *dst, rsize_t dstsize, wchar_t const *src) -> $errno_t
	%{copy(%auto, str2wcs)}

%{
#ifndef __wcsnlen_s_defined
#define __wcsnlen_s_defined 1
__LOCAL __ATTR_WUNUSED __ATTR_PURE
__SIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL wcsnlen_s)(wchar_t const *__str, __SIZE_TYPE__ __maxlen) {
	return __str ? wcsnlen(__str, __maxlen) : 0;
}
#endif /* !__wcsnlen_s_defined */
}

[section(.text.crt.dos.wchar.string.memory)][wchar][guard]
wcsncat_s:(wchar_t *dst, rsize_t dstsize, wchar_t const *src, rsize_t maxlen) -> $errno_t
	%{copy(%auto, str2wcs)}

[section(.text.crt.dos.wchar.string.memory)][wchar][guard]
wcsncpy_s:(wchar_t *dst, rsize_t dstsize, wchar_t const *src, rsize_t maxlen) -> $errno_t
	%{copy(%auto, str2wcs)}

[ATTR_NONNULL((2, 3))][wchar][noexport][nouser]
[section(.text.crt.dos.wchar.string.memory)][guard]
wcstok_s:(wchar_t *string, wchar_t const *__restrict delim, wchar_t **__restrict save_ptr) -> wchar_t *
	= wcstok;

%#endif  /* __USE_DOS_SLIB */

%[default_impl_section(.text.crt.dos.wchar.errno)]
[wchar][guard] _wcserror:(int errno_value) -> wchar_t *;
[wchar][guard] _wcserror_s:(wchar_t *buf, $size_t bufsize, int errno_value) -> $errno_t;
[wchar][guard] __wcserror:(wchar_t const *message) -> wchar_t *;
[wchar][guard] __wcserror_s:(wchar_t *buf, $size_t bufsize, wchar_t const *message) -> $errno_t;

[alias(wcsicmp)][attribute(*)][wchar][guard]
[section(.text.crt.dos.wchar.unicode.static.memory)]
_wcsicmp:(wchar_t const *s1, wchar_t const *s2) -> int = wcscasecmp;

[alias(wcsnicmp)][attribute(*)][wchar][guard]
[section(.text.crt.dos.wchar.unicode.static.memory)]
_wcsnicmp:(wchar_t const *s1, wchar_t const *s2, $size_t maxlen) -> int = wcsncasecmp;

[alias(wcsicmp_l)][attribute(*)][wchar][guard]
[section(.text.crt.dos.wchar.unicode.locale.memory)]
_wcsicmp_l:(wchar_t const *s1, wchar_t const *s2, $locale_t locale) -> int = wcscasecmp_l;

[alias(wcsnicmp_l)][attribute(*)][wchar][guard]
[section(.text.crt.dos.wchar.unicode.locale.memory)]
_wcsnicmp_l:(wchar_t const *s1, wchar_t const *s2, $size_t maxlen, $locale_t locale) -> int = wcsncasecmp_l;

[section(.text.crt.dos.wchar.string.memory)][wchar][attribute(*)][guard]
_wcsnset_s:(wchar_t *buf, $size_t buflen, wchar_t ch, $size_t maxlen) -> $errno_t
	%{copy(_strnset_s, str2wcs)}

[section(.text.crt.dos.wchar.string.memory)][wchar][attribute(*)][guard]
_wcsset_s:(wchar_t *dst, $size_t dstsize, wchar_t ch) -> $errno_t
	%{copy(_strset_s, str2wcs)}

[section(.text.crt.dos.wchar.unicode.static.memory)]
[wchar][attribute(*)][guard]
_wcslwr_s:(wchar_t *buf, $size_t buflen) -> $errno_t
	%{copy(_strlwr_s, str2wcs)}

[section(.text.crt.dos.wchar.unicode.static.memory)]
[wchar][attribute(*)][guard]
_wcsupr_s:(wchar_t *buf, $size_t buflen) -> $errno_t
	%{copy(_strupr_s, str2wcs)}

[section(.text.crt.dos.wchar.unicode.locale.memory)]
[wchar][attribute(*)][guard]
_wcslwr_s_l:(wchar_t *buf, $size_t buflen, $locale_t locale) -> $errno_t
	%{copy(_strlwr_s_l, str2wcs)}

[section(.text.crt.dos.wchar.unicode.locale.memory)]
[wchar][attribute(*)][guard]
_wcsupr_s_l:(wchar_t *buf, $size_t buflen, $locale_t locale) -> $errno_t
	%{copy(_strupr_s_l, str2wcs)}

[section(.text.crt.dos.wchar.string.memory)][wchar][attribute(*)][guard]
wmemcpy_s:(wchar_t *dst, rsize_t dstlength, wchar_t const *src, rsize_t srclength) -> $errno_t
	%{copy(memcpy_s, str2wcs)}

[section(.text.crt.dos.wchar.string.memory)][wchar][attribute(*)][guard]
wmemmove_s:(wchar_t *dst, rsize_t dstlength, wchar_t const *src, rsize_t srclength) -> $errno_t
	%{copy(memmove_s, str2wcs)}

%
%
%

[alias(*)][attribute(*)][wchar][guard] _wcsnset:(*) = wcsnset;
[alias(*)][attribute(*)][wchar][guard] _wcsrev:(*) = wcsrev;
[alias(*)][attribute(*)][wchar][guard] _wcsset:(*) = wcsset;
[alias(*)][attribute(*)][wchar][guard] _wcslwr:(*) = wcslwr;
[alias(*)][attribute(*)][wchar][guard] _wcsupr:(*) = wcsupr;
[alias(*)][attribute(*)][wchar][guard] _wcslwr_l:(*) = wcslwr_l;
[alias(*)][attribute(*)][wchar][guard] _wcsupr_l:(*) = wcsupr_l;
[alias(*)][attribute(*)][wchar][guard] _wcsxfrm_l:(*) = wcsxfrm_l;
[alias(*)][attribute(*)][wchar][guard] _wcscoll_l:(*) = wcscoll_l;
[alias(*)][attribute(*)][wchar][guard] _wcsicoll:(*) = wcscasecoll;
[alias(*)][attribute(*)][wchar][guard] _wcsicoll_l:(*) = wcscasecoll_l;
[alias(*)][attribute(*)][wchar][guard] _wcsncoll:(*) = wcsncasecoll;
[alias(*)][attribute(*)][wchar][guard] _wcsncoll_l:(*) = wcsncoll_l;
[alias(*)][attribute(*)][wchar][guard] _wcsnicoll:(*) = wcsncasecoll;
[alias(*)][attribute(*)][wchar][guard] _wcsnicoll_l:(*) = wcsncasecoll_l;

%
%
%

[alias(*)][attribute(*)][wchar][guard] wcsicmp:(*) = wcscasecmp;
[alias(*)][attribute(*)][wchar][guard] wcsnicmp:(*) = wcsncasecmp;
[alias(*)][attribute(*)][wchar][guard] wcsicoll:(*) = wcscasecoll;

%#endif /* !_WSTRING_DEFINED */
%#endif /* __USE_DOS */


%#if defined(__USE_DOS) || defined(__USE_KOS)
[alias(_wcsnset)][ATTR_RETNONNULL][ATTR_NONNULL((1))][wchar]
[section(.text.crt.dos.wchar.string.memory)][guard]
wcsnset:(wchar_t *__restrict str, wchar_t ch, $size_t maxlen) -> wchar_t *
	%{copy(%auto, str2wcs)}

[alias(_wcsrev)][ATTR_RETNONNULL][ATTR_NONNULL((1))][wchar][guard]
[section(.text.crt.dos.wchar.string.memory)][doc_alias(strrev)]
wcsrev:(wchar_t *__restrict str) -> wchar_t * {
#if __SIZEOF_WCHAR_T__ == 2
	return (wchar_t *)memrevw(str, wcslen(str));
#elif __SIZEOF_WCHAR_T__ == 4
	return (wchar_t *)memrevl(str, wcslen(str));
#else
	return (wchar_t *)memrev(str, wcslen(str) * sizeof(wchar_t));
#endif
}



[alias(_wcsset)][ATTR_RETNONNULL][ATTR_NONNULL((1))][wchar]
[section(.text.crt.dos.wchar.string.memory)][guard]
wcsset:(wchar_t *__restrict str, wchar_t ch) -> wchar_t * %{copy(%auto, str2wcs)}

[alias(_wcslwr)][ATTR_RETNONNULL][ATTR_NONNULL((1))][wchar]
[section(.text.crt.dos.wchar.unicode.static.memory)][guard]
wcslwr:(wchar_t *__restrict str) -> wchar_t * %{copy(%auto, str2wcs)}

[alias(_wcsupr)][ATTR_RETNONNULL][ATTR_NONNULL((1))][wchar]
[section(.text.crt.dos.wchar.unicode.static.memory)][guard]
wcsupr:(wchar_t *__restrict str) -> wchar_t * %{copy(%auto, str2wcs)}
%#endif /* __USE_DOS || __USE_KOS */


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_KOS

#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_WCHAR_FORMAT_PRINTER_H)
#include <parts/wchar/format-printer.h>
#endif

#if defined(_PROCESS_H) && !defined(_PARTS_WCHAR_PROCESS_H)
#include <parts/wchar/process.h>
#endif

#if defined(_UTIME_H) && !defined(_PARTS_WCHAR_UTIME_H)
#include <parts/wchar/utime.h>
#endif

#if defined(_UNISTD_H) && !defined(_PARTS_WCHAR_UNISTD_H)
#include <parts/wchar/unistd.h>
#endif

#endif /* __USE_KOS */

}

