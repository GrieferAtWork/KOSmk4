/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C95 (ISO/IEC 9899:1990/AMD1:1995) */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/wchar.h) */
/* (#) Portability: DJGPP         (/include/wchar.h) */
/* (#) Portability: DragonFly BSD (/include/wchar.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/wchar.h) */
/* (#) Portability: FreeBSD       (/include/wchar.h) */
/* (#) Portability: GNU C Library (/wcsmbs/wchar.h) */
/* (#) Portability: GNU Hurd      (/usr/include/wchar.h) */
/* (#) Portability: MSVC          (/include/wchar.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/wchar.h) */
/* (#) Portability: NetBSD        (/include/wchar.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/wchar.h) */
/* (#) Portability: OpenBSD       (/include/wchar.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/wchar.h) */
/* (#) Portability: Windows Kits  (/ucrt/wchar.h) */
/* (#) Portability: diet libc     (/include/wchar.h) */
/* (#) Portability: libbsd        (/include/bsd/wchar.h) */
/* (#) Portability: libc6         (/include/wchar.h) */
/* (#) Portability: mintlib       (/include/wchar.h) */
/* (#) Portability: musl libc     (/include/wchar.h) */
/* (#) Portability: uClibc        (/include/wchar.h) */
}

%[define_ccompat_header("cwchar")]

%[define_decl_include("<bits/crt/tm.h>": ["struct tm"])]
%[define_decl_include("<bits/crt/mbstate.h>": ["struct __mbstate"])]

%[define_replacement(mbstate_t = "struct __mbstate")]
%[define_replacement(wchar_t = __WCHAR_TYPE__)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_replacement(WEOF = __WEOF)]
%[define_replacement(mbstate_isempty = __mbstate_isempty)]
%[define_replacement(mbstate_init = __mbstate_init)]

%[define_wchar_replacement(wchar_t = char16_t, char32_t)]
%[define_wchar_replacement(wint_t = wint16_t, wint32_t)]
%[define_wchar_replacement(__WINT_TYPE__ = __WINT16_TYPE__, __WINT32_TYPE__)]
%[define_wchar_replacement(__WCHAR_TYPE__ = __CHAR16_TYPE__, __CHAR32_TYPE__)]
%[define_wchar_replacement(__SIZEOF_WINT_T__ = "2", "4")]
%[define_wchar_replacement(__SIZEOF_WCHAR_T__ = "2", "4")]
%[define_wchar_replacement(WEOF = __WEOF16, __WEOF32)]
%[define_wchar_replacement(__WEOF = __WEOF16, __WEOF32)]

%[assume_defined_in_kos(__SIZEOF_WINT_T__ = "4")]
%[assume_defined_in_kos(__SIZEOF_WCHAR_T__ = "4")]


%[define_replacement(rsize_t  = __SIZE_TYPE__)]

%(auto_source){
#include "../libc/globals.h"
}

%(auto_header){
#include <bits/crt/wformat-printer.h>
#include <bits/crt/uformat-printer.h>
#ifndef __errno_t_defined
#define __errno_t_defined
typedef __errno_t errno_t;
#endif /* !__errno_t_defined */
#ifndef __rsize_t_defined
#define __rsize_t_defined
typedef size_t rsize_t;
#endif /* !__rsize_t_defined */

}

%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/limitcore.h> /* __WCHAR_MIN__, __WCHAR_MAX__ */
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

}%[insert:prefix(
#include <asm/crt/stdio.h> /* __WEOF */
)]%[insert:prefix(
#include <bits/crt/tm.h>   /* struct tm */
)]%[insert:prefix(
#include <bits/crt/mbstate.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __USE_KOS
#include <bits/crt/wformat-printer.h>
#include <parts/malloca.h>
#endif /* __USE_KOS */

#ifdef __USE_DOS
#include <bits/types.h>
#include <libc/errno.h>
#include <crtdefs.h>
#endif /* __USE_DOS */


/* Define `NULL' */
#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

#ifndef WCHAR_MIN
#define WCHAR_MIN __WCHAR_MIN__
#define WCHAR_MAX __WCHAR_MAX__
#endif /* !WCHAR_MIN */

#ifndef WEOF
#define WEOF __WEOF
#endif /* !WEOF */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined
__NAMESPACE_STD_BEGIN
typedef struct __mbstate mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __mbstate_t_defined
#define __mbstate_t_defined
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

/* Define 'FILE' */
}%(c, ccompat){
#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K) || defined(__USE_DOS)
}%{
#ifndef __std_FILE_defined
#define __std_FILE_defined
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __FILE_defined
#define __FILE_defined
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
}%(c, ccompat){
#endif /* __USE_UNIX98 || __USE_XOPEN2K || __USE_DOS */
}%{

/* Define 'wchar_t' */
#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

__NAMESPACE_STD_BEGIN
#ifndef __std_size_t_defined
#define __std_size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__std_size_t_defined */
#ifndef __std_wint_t_defined
#define __std_wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__std_wint_t_defined */
__NAMESPACE_STD_END

#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __tm_defined
#define __tm_defined
__NAMESPACE_STD_USING(tm)
#endif /* !__tm_defined */
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
#ifndef __wint_t_defined
#define __wint_t_defined
__NAMESPACE_STD_USING(wint_t)
#endif /* !__wint_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

}

%[insert:std]
%[define_replacement(tm = "__NAMESPACE_STD_SYM tm")];

%[define_crt_name_list(CNL_wcstol      = ["wcstol"])]
%[define_crt_name_list(CNL_wcstoul     = ["wcstoul"])]
%[define_crt_name_list(CNL_wcstoll     = ["wcstoll", "wcstoq"])]
%[define_crt_name_list(CNL_wcstoull    = ["wcstoull", "wcstouq"])]
%[define_crt_name_list(CNL_wcsto32     = ["wcsto32"])]
%[define_crt_name_list(CNL_wcstou32    = ["wcstou32"])]
%[define_crt_name_list(CNL_wcsto64     = ["wcsto64", "_wcstoi64"])]
%[define_crt_name_list(CNL_wcstou64    = ["wcstou64", "_wcstoui64"])]
%[define_crt_name_list(CNL_wcstoimax   = ["wcstoimax"])]
%[define_crt_name_list(CNL_wcstoumax   = ["wcstoumax"])]
%[define_crt_name_list(CNL_wcstol_l    = ["wcstol_l", "_wcstol_l", "__wcstol_l"])]
%[define_crt_name_list(CNL_wcstoul_l   = ["wcstoul_l", "_wcstoul_l", "__wcstoul_l"])]
%[define_crt_name_list(CNL_wcstoll_l   = ["wcstoll_l", "_wcstoll_l", "__wcstoll_l"])]
%[define_crt_name_list(CNL_wcstoull_l  = ["wcstoull_l", "_wcstoull_l", "__wcstoull_l"])]
%[define_crt_name_list(CNL_wcsto32_l   = ["wcsto32_l"])]
%[define_crt_name_list(CNL_wcstou32_l  = ["wcstou32_l"])]
%[define_crt_name_list(CNL_wcsto64_l   = ["wcsto64_l", "_wcstoi64_l"])]
%[define_crt_name_list(CNL_wcstou64_l  = ["wcstou64_l", "_wcstoui64_l"])]
%[define_crt_name_list(CNL_wcstoimax_l = ["wcstoimax_l", "_wcstoimax_l"])]
%[define_crt_name_list(CNL_wcstoumax_l = ["wcstoumax_l", "_wcstoumax_l"])]



%[default:section(".text.crt{|.dos}.wchar.unicode.static.mbs")];

@@>> btowc(3)
@@Convert a single-byte into a wide character. If the given
@@character `ch' isn't valid, or  is `EOF', then `WEOF'  is
@@returned instead.
[[wchar, std, const, wunused, nothrow]]
[[decl_include("<hybrid/typecore.h>")]]
[[impl_include("<asm/crt/stdio.h>")]]
wint_t btowc(int ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (wint_t)ch;
	return WEOF;
}

@@>> wctob(3)
@@Convert a wide-character into a single-byte character. If
@@doing so isn't possible, then `EOF' is returned  instead.
[[wchar, std, const, wunused, nothrow]]
[[impl_include("<asm/crt/stdio.h>")]]
[[decl_include("<hybrid/typecore.h>")]]
int wctob(wint_t ch) {
	if (ch >= 0 && ch <= 0x7f)
		return (int)ch;
	return EOF;
}


%[declare_user_export("mbrtoc16", "c16rtomb")]
%[declare_known_section_class(".crt.dos.wchar.unicode.static.mbs")]

%(auto_source){
#ifndef __KERNEL__
#ifdef __LIBCCALL_IS_LIBDCALL
DEFINE_INTERN_ALIAS(libc_mbrtoc16, libd_mbrtowc);
DEFINE_INTERN_ALIAS(libc_c16rtomb, libd_wcrtomb);
#else /* __LIBCCALL_IS_LIBDCALL */
/* Because STDC mandates the uchar16 and uchar32 variants:
 *    mbrtowc:mbrtoc16:mbrtoc32
 *    wcrtomb:c16rtomb:c32rtomb
 * which are exposed in <uchar.h>, we need to be a little bit
 * more  careful when it comes to defining them on a platform
 * where the standard DOS calling convention differs from the
 * calling convention used by KOS (e.g. x86-64)
 *
 * In this scenario, magic will have already given the symbols:
 *   - LIBDCALL:DOS$mbrtowc:   size_t(wchar16_t *pwc, char const *str, size_t maxlen, mbstate_t *mbs);
 *     LIBDCALL:DOS$mbrtoc16:  ...
 *   - LIBKCALL:mbrtowc:       size_t(wchar32_t *pwc, char const *str, size_t maxlen, mbstate_t *mbs);
 *     LIBKCALL:mbrtoc32:      ...
 *     LIBDCALL:DOS$mbrtoc32:  ...  (msabi64-generator)
 *   - LIBDCALL:DOS$wcrtomb:   size_t(char *str, wchar16_t wc, mbstate_t *mbs);
 *     LIBDCALL:DOS$c16rtomb:  ...
 *   - LIBKCALL:wcrtomb:       size_t(char *str, wchar32_t wc, mbstate_t *mbs);
 *     LIBKCALL:c32rtomb:      ...
 *     LIBDCALL:DOS$c32rtomb:  ...  (msabi64-generator)
 *
 * However,  you can  see that this  system is still  lacking the LIBKCALL
 * variants of 2 functions that are only available as LIBDCALL (thus far):
 *     LIBKCALL:mbrtoc16:  ...
 *     LIBKCALL:c16rtomb:  ...
 *
 * And because the msabi64 generator doesn't include special handling for this case,
 * we  simply have to manually implement these  2 functions as LIBKCALL wrappers for
 * the associated LIBDCALL functions:
 *
 *     libc_mbrtoc16(...) { return libd_mbrtowc(...); }
 *     libc_c16rtomb(...) { return libd_wcrtomb(...); }
 */
DEFINE_PUBLIC_ALIAS(mbrtoc16, libc_mbrtoc16);
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_mbrtoc16)(char16_t *pwc,
                                    char const *__restrict str,
                                    size_t maxlen,
                                    mbstate_t *mbs) {
	return libd_mbrtowc(pwc, str, maxlen, mbs);
}

DEFINE_PUBLIC_ALIAS(c16rtomb, libc_c16rtomb);
INTERN ATTR_SECTION(".text.crt.dos.wchar.unicode.static.mbs") size_t
NOTHROW_NCX(LIBKCALL libc_c16rtomb)(char *__restrict str,
                                    char16_t wc,
                                    mbstate_t *mbs) {
	return libd_wcrtomb(str, wc, mbs);
}
#endif /* !__LIBCCALL_IS_LIBDCALL */
#endif /* !__KERNEL__ */
}

@@>> mbrtowc(3)
[[std, wchar, export_alias("__mbrtowc")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("mbrtoc16")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("mbrtoc32")]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)),  dos_export_as("mbrtoc16")]]
[[if(!defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$mbrtoc16")]]
[[kos_export_as("mbrtoc32")]]
size_t mbrtowc([[out_opt]] wchar_t *pwc,
               [[in_opt/*(maxlen)*/]] char const *__restrict str, size_t maxlen,
               [[inout_opt]] mbstate_t *mbs) {
	size_t error;
	wchar_t fallback_wc;
	if (mbs == NULL) {
@@pp_ifdef __BUILDING_LIBC@@
		mbs = &_mb_shift;
@@pp_else@@
		/* For whatever reason, libc4/5 exported this `mbrtowc_ps' as `_mb_shift' */
		static mbstate_t mbrtowc_ps = __MBSTATE_INIT;
		mbs = &mbrtowc_ps;
@@pp_endif@@
	}
	if (str == NULL) {
		mbstate_init(mbs);
		return 0;
	}
	if (maxlen == 0 || *str == '\0')
		return 0;
	if unlikely(pwc == NULL)
		pwc = &fallback_wc;
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	error = unicode_c8toc16((char16_t *)pwc, str, maxlen, mbs);
@@pp_else@@
	error = unicode_c8toc32((char32_t *)pwc, str, maxlen, mbs);
@@pp_endif@@
@@pp_ifdef EILSEQ@@
	if (error == (size_t)-1)
		(void)libc_seterrno(EILSEQ);
@@pp_endif@@
	return error;
}


@@>> wcrtomb(3)
[[std, wchar]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
[[impl_include("<libc/errno.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("c16rtomb")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("c32rtomb")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)),  dos_export_as("c16rtomb")]]
[[if(!defined(__LIBCCALL_IS_LIBDCALL)), dos_export_as("DOS$c16rtomb")]]
[[kos_export_as("c32rtomb")]]
size_t wcrtomb([[out_opt]] char *__restrict str/*char str[MB_CUR_MAX]*/, wchar_t wc,
               [[inout_opt]] mbstate_t *mbs) {
	char *endptr;
	size_t result;
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	/* unicode_c16toc8() */
	if (!mbs) {
@@pp_ifdef __BUILDING_LIBC@@
		mbs = &_mb_shift;
@@pp_else@@
		/* For whatever reason, libc4/5 exported this `wcrtomb_ps' as `_mb_shift' */
		static mbstate_t wcrtomb_ps = @__MBSTATE_INIT@;
		mbs = &wcrtomb_ps;
@@pp_endif@@
	}
	if (!str) {
		mbstate_init(mbs);
		return 1;
	}
	if ((mbs->@__mb_word@ & __MBSTATE_TYPE_MASK) == __MBSTATE_TYPE_UTF16_LO) {
		/* Complete surrogate */
		char32_t ch32;
		if unlikely(!((u16)wc >= UTF16_LOW_SURROGATE_MIN &&
		              (u16)wc <= UTF16_LOW_SURROGATE_MAX)) {
			/* Expected low surrogate */
@@pp_ifdef EILSEQ@@
			(void)libc_seterrno(EILSEQ);
@@pp_endif@@
			return (size_t)-1;
		}
		ch32 = ((mbs->@__mb_word@ & 0x000003ff) << 10) +
		       0x10000 + ((u16)wc - 0xdc00);
		mbs->@__mb_word@ = __MBSTATE_TYPE_EMPTY;
		endptr = unicode_writeutf8(str, ch32);
	} else if ((u16)wc >= UTF16_HIGH_SURROGATE_MIN &&
	           (u16)wc <= UTF16_HIGH_SURROGATE_MAX) {
		mbs->@__mb_word@ = __MBSTATE_TYPE_UTF16_LO | ((u16)wc - UTF16_HIGH_SURROGATE_MIN);
		return 0;
	} else {
		endptr = unicode_writeutf8(str, (char32_t)(u32)(u16)wc);
	}
@@pp_else@@
	/* unicode_c32toc8() */
	(void)mbs;
	if (!str)
		return 1;
	endptr = unicode_writeutf8(str, (char32_t)wc);
@@pp_endif@@
	result = (size_t)(endptr - str);
	return result;
}

@@>> mbrlen(3)
[[std, wchar, wunused, export_alias("__mbrlen")]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
$size_t mbrlen([[in_opt/*(maxlen)*/]] char const *__restrict str, $size_t maxlen,
               [[inout_opt]] $mbstate_t *mbs) {
	wchar_t wc;
	return mbrtowc(&wc, str, maxlen, mbs);
}

@@>> mbsrtowcs(3)
[[std, wchar, requires_function(mbsnrtowcs)]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
size_t mbsrtowcs([[out_opt/*(dstlen)*/]] wchar_t *__restrict dst,
                 [[inout]] char const **__restrict psrc, size_t dstlen,
                 [[inout_opt]] mbstate_t *mbs) {
	return mbsnrtowcs(dst, psrc, (size_t)-1, dstlen, mbs);
}

@@>> wcsrtombs(3)
[[std, wchar, requires_function(wcsnrtombs)]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
size_t wcsrtombs([[out_opt/*(dstlen)*/]] char *dst,
                 [[inout]] wchar_t const **__restrict psrc, size_t dstlen,
                 [[inout_opt]] mbstate_t *mbs) {
	return wcsnrtombs(dst, psrc, (size_t)-1, dstlen, mbs);
}

@@>> wcstol(3)
[[std, guard, wchar]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_wcstol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_wcstoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),                    alias(CNL_wcsto32...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias(CNL_wcsto64...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__),  alias(CNL_wcstoimax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), crt_intern_alias("wcsto32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), crt_intern_alias("wcsto64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), export_as("wcstoimax")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstol(*) %{generate(str2wcs("strtol"))}

@@>> wcstoul(3)
[[std, guard, wchar]]
[[no_crt_self_import, no_crt_self_export, export_alias(CNL_wcstoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias(CNL_wcstoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),                    alias(CNL_wcstou32...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),                    alias(CNL_wcstou64...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INTMAX_T__),  alias(CNL_wcstoumax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), crt_intern_alias("wcstou32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), crt_intern_alias("wcstou64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__), export_as("wcstoumax")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstoul(*) %{generate(str2wcs("strtoul"))}

@@>> mbsinit(3)
[[std, pure, wunused, decl_include("<bits/crt/mbstate.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[decl_include("<bits/crt/mbstate.h>")]]
int mbsinit([[in_opt]] mbstate_t const *mbs) {
	return !mbs || mbstate_isempty(mbs);
}

%[define_wchar_replacement(wmemcmp = memcmpw, memcmpl)]

@@>> wmemcmp(3)
[[std, wchar, pure, wunused, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("memcmpw")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("memcmpl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(memcmpw)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(memcmpl)]]
int wmemcmp([[in(num_chars)]] wchar_t const *s1,
            [[in(num_chars)]] wchar_t const *s2,
            size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return memcmpw(s1, s2, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return memcmpl(s1, s2, num_chars);
@@pp_else@@
	return memcmpc(s1, s2, num_chars, sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmemcpy = "(char16_t *)memcpyw", "(char32_t *)memcpyl")]

@@>> wmemcpy(3)
[[std, wchar, nonnull, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("memcpyw")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("memcpyl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(memcpyw)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(memcpyl)]]
wchar_t *wmemcpy([[out(num_chars)]] wchar_t *__restrict dst,
                 [[in(num_chars)]] wchar_t const *__restrict src,
                 size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memcpyw(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memcpyl(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)memcpyc(dst, src, num_chars, sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmemmove = "(char16_t *)memmovew", "(char32_t *)memmovel")]

@@>> wmemmove(3)
[[std, wchar, nonnull, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("memmovew")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("memmovel")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(memmovew)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(memmovel)]]
wchar_t *wmemmove([[out(num_chars)]] wchar_t *dst,
                  [[in(num_chars)]] wchar_t const *src,
                  size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memmovew(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memmovel(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)memmove(dst, src, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmemset = "(char16_t *)memsetw", "(char32_t *)memsetl")]

@@>> wmemset(3)
[[std, wchar, no_crt_impl]]
[[decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("memsetw")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("memsetl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(memsetw)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(memsetl)]]
[[nonnull]] wchar_t *wmemset([[out(num_chars)]] wchar_t *dst,
                             wchar_t filler, size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memsetw(dst, (u16)filler, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memsetl(dst, (u32)filler, num_chars);
@@pp_else@@
	return (wchar_t *)memset(dst, (int)filler, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

@@>> wcscpy(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcscpy([[out]] wchar_t *__restrict buf,
                            [[in]] wchar_t const *__restrict src) {
	return wmemcpy(buf, src, wcslen(src) + 1);
}

@@>> wcscat(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcscat([[inout]] wchar_t *__restrict buf,
                            [[in]] wchar_t const *__restrict src) {
	(void)wmemcpy(wcsend(buf), src, wcslen(src) + 1);
	return buf;
}

@@>> wcsncat(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsncat([[inout(buflen)]] wchar_t *__restrict buf,
                             [[in(wcsnlen(., buflen))]] wchar_t const *__restrict src,
                             $size_t buflen) {
	size_t srclen = wcsnlen(src, buflen);
	wchar_t *dst = wcsend(buf);
	*wmempcpy(dst, src, srclen) = (wchar_t)'\0';
	return buf;
}

@@>> wcsncpy(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsncpy([[out(buflen)]] wchar_t *__restrict buf,
                             [[in(wcsnlen(src, buflen))]] wchar_t const *__restrict src,
                             $size_t buflen) {
	wchar_t *ptr;
	size_t srclen = wcsnlen(src, buflen);
	ptr = wmempcpy(buf, src, srclen);
	(void)wmemset(ptr, (wchar_t)'\0', buflen - srclen);
	return buf;
}


@@>> wcscmp(3)
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcscmp(*) %{generate(str2wcs("strcmp"))}

@@>> wcsncmp(3)
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcsncmp(*) %{generate(str2wcs("strncmp"))}

@@>> wcscoll(3)
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcscoll(*) %{generate(str2wcs("strcoll"))}

@@>> wcsxfrm(3)
[[std, guard, wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsxfrm(*) %{generate(str2wcs("strxfrm"))}


%[default:section(".text.crt{|.dos}.wchar.FILE.locked.read.getc")]

@@>> getwchar(3), getwchar_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("getwchar_unlocked")]]
[[dos_export_alias("_fgetwchar"), alias("getwchar_unlocked")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(fgetwc))]]
[[impl_include("<libc/template/stdstreams.h>")]]
wint_t getwchar() {
	return fgetwc(stdin);
}

@@>> putwchar(3), putwchar_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("putwchar_unlocked")]]
[[dos_export_alias("_fputwchar"), alias("putwchar_unlocked")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(fputwc))]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.putc")]]
[[impl_include("<libc/template/stdstreams.h>")]]
wint_t putwchar(wchar_t wc) {
	return fputwc(wc, stdout);
}


@@>> fgetwc(3), getwc(3), fgetwc_unlocked(3), getwc_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fgetwc_unlocked", "getwc_unlocked")]]
[[export_alias("getwc"), alias("fgetwc_unlocked", "getwc_unlocked")]]
wint_t fgetwc([[inout]] FILE *__restrict stream);

@@>> fputwc(3), putwc(3), fputwc_unlocked(3), putwc_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fputwc_unlocked", "putwc_unlocked")]]
[[export_alias("putwc"), alias("fputwc_unlocked", "putwc_unlocked")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.putc")]]
wint_t fputwc(wchar_t wc, [[inout]] FILE *stream);


%[insert:guarded_std_function(getwc = fgetwc)]
%[insert:guarded_std_function(putwc = fputwc)]


@@>> fgetws(3), fgetws_unlocked(3)
[[cp_stdio, std, guard, wchar, wunused, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fgetws_unlocked", "_fgetws_nolock")]]
[[alias("fgetws_unlocked", "_fgetws_nolock")]]
[[requires($has_function(fgetwc) && $has_function(ungetwc) && $has_function(ferror))]]
[[impl_include("<libc/errno.h>", "<asm/crt/stdio.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.read.read")]]
wchar_t *fgetws([[out(? <= bufsize)]] wchar_t *__restrict buf,
                __STDC_INT_AS_SIZE_T bufsize,
                [[inout]] FILE *__restrict stream) {
	size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_endif@@
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = fgetwc(stream);
		if (ch == WEOF) {
			if (n == 0 || ferror(stream))
				return NULL;
			break;
		}
		if (ch == (wchar_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = (wchar_t)'\n';
			ch = fgetwc(stream);
			if (ch == WEOF) {
				if (n == 0 || ferror(stream))
					return NULL;
				break;
			}
			if (ch == (wchar_t)'\r')
				continue;
			ungetwc(ch, stream);
			break;
		}
		buf[n] = (wchar_t)ch;
		if (ch == (wchar_t)'\n')
			break;
	}
	buf[n] = (wchar_t)'\0';
	return buf;
}



@@>> fputws(3), fputws_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fputws_unlocked", "_fputws_nolock")]]
[[alias("fputws_unlocked", "_fputws_nolock")]]
[[requires_function(file_wprinter)]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.write")]]
__STDC_INT_AS_SIZE_T fputws([[in]] wchar_t const *__restrict str,
                            [[inout]] FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter(stream, str, wcslen(str));
	return result;
}

@@>> ungetwc(3), ungetwc_unlocked(3)
[[std, guard, wchar, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("ungetwc_unlocked")]]
[[alias("ungetwc_unlocked")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.putc")]]
wint_t ungetwc(wint_t wc, [[inout]] FILE *stream);

@@>> wcsftime(3)
[[std, guard, wchar]]
[[decl_include("<hybrid/typecore.h>", "<bits/crt/tm.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.strftime")]]
size_t wcsftime([[out(return <= buflen)]] wchar_t *__restrict buf, size_t buflen,
                [[in, format("wcsftime")]] wchar_t const *__restrict format,
                [[in]] struct $tm const *__restrict tp) {
	if (buflen)
		*buf = 0;
	/* TODO */
	(void)format;
	(void)tp;
	return 0;
}

%[default:section(".text.crt{|.dos}.wchar.string.memory")]
%(std)
%(std,c,ccompat)#if !defined(__USE_DOS) || defined(__USE_ISOC95)

@@>> wcstok(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, no_crt_self_import, no_crt_self_export]]
[[dos_export_as("DOS$wcstok_s"), kos_export_as("wcstok")]]
[[if(!defined(__CRT_DOS_PRIMARY)), preferred_alias("wcstok")]]
[[if( defined(__CRT_DOS_PRIMARY)), preferred_alias("wcstok_s")]]
wchar_t *wcstok([[inout_opt]] wchar_t *str,
                [[in]] wchar_t const *__restrict delim,
                [[inout]] wchar_t **__restrict save_ptr)
	%{generate(str2wcs("strtok_r"))}

%(std,c,ccompat)#endif /* !__USE_DOS || __USE_ISOC95 */

@@>> wcslen(3)
[[std, guard, wchar]]
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SLEN))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SLEN))]]
wcslen(*) %{generate(str2wcs("strlen"))}

@@>> wcsspn(3)
[[std, guard, wchar]]
wcsspn(*) %{generate(str2wcs("strspn"))}

@@>> wcscspn(3)
[[std, guard, wchar]]
wcscspn(*) %{generate(str2wcs("strcspn"))}

@@>> wcschr(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, pure, wunused]]
[[nullable]] wchar_t *wcschr([[in]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[in]] wchar_t *__restrict haystack, wchar_t needle): [[nullable]] wchar_t *]
	[([[in]] wchar_t const *__restrict haystack, wchar_t needle): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strchr"))}

@@>> wcsrchr(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, pure, wunused]]
[[nullable]] wchar_t *wcsrchr([[in]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[in]] wchar_t *__restrict haystack, wchar_t needle): [[nullable]] wchar_t *]
	[([[in]] wchar_t const *__restrict haystack, wchar_t needle): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strrchr"))}

@@>> wcspbrk(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, pure, wunused]]
[[nullable]] wchar_t *wcspbrk([[in]] wchar_t const *haystack, [[in]] wchar_t const *accept)
	[([[in]] wchar_t *haystack, [[in]] wchar_t const *accept): [[nullable]] wchar_t *]
	[([[in]] wchar_t const *haystack, [[in]] wchar_t const *accept): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strpbrk"))}

@@>> wcsstr(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, pure, wunused, export_alias("wcswcs")]]
[[nullable]] wchar_t *wcsstr([[in]] wchar_t const *haystack, [[in]] wchar_t const *needle)
	[([[in]] wchar_t *haystack, [[in]] wchar_t *needle): [[nullable]] wchar_t *]
	[([[in]] wchar_t const *haystack, [[in]] wchar_t const *needle): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strstr"))}

%[define_wchar_replacement(wmemchr = "(char16_t *)memchrw", "(char32_t *)memchrl")]

@@>> wmemchr(3)
[[decl_include("<hybrid/typecore.h>")]]
[[std, wchar, pure, wunused, no_crt_impl]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("memchrw")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("memchrl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(memchrw)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(memchrl)]]
[[nullable]] wchar_t *wmemchr([[in(num_chars)]] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars)
	[([[in(num_chars)]] wchar_t *__restrict haystack, wchar_t needle, size_t num_chars): [[nullable]] wchar_t *]
	[([[in(num_chars)]] wchar_t const *__restrict haystack, wchar_t needle, size_t num_chars): [[nullable]] wchar_t const *]
{
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memchrw(haystack, needle, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memchrl(haystack, needle, num_chars);
@@pp_else@@
	return (wchar_t *)memchr(haystack, (int)needle, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

%(std,c,ccompat)#if defined(__USE_ISOC95) || defined(__USE_UNIX98)

@@>> fwide(3)
[[std, guard]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.utility")]]
int fwide([[inout]] FILE *fp, int mode) {
	(void)fp;
	(void)mode;
	COMPILER_IMPURE();
	return 0;
}

%(std,c,ccompat)#endif /* __USE_ISOC95 || __USE_UNIX98 */

%(std)
%(std,c,ccompat)#if defined(__USE_ISOC95) || defined(__USE_UNIX98) || defined(__USE_DOS)

@@>> fwprintf(3), vfwprintf(3), fwprintf_unlocked(3), vfwprintf_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fwprintf_unlocked")]]
[[alias("fwprintf_unlocked"), export_as("_fwprintf_p")]] /* Normal wprintf already supports positional arguments! */
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
__STDC_INT_AS_SIZE_T fwprintf([[inout]] FILE *__restrict stream,
                              [[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vfwprintf")}

[[cp_stdio, std, guard, wchar, doc_alias("fwprintf"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("vfwprintf_unlocked")]]
[[alias("vfwprintf_unlocked"), export_as("_vfwprintf_p")]] /* Normal wprintf already supports positional arguments! */
[[requires_dependent_function(file_wprinter)]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
__STDC_INT_AS_SIZE_T vfwprintf([[inout]] FILE *__restrict stream,
                               [[in, format]] wchar_t const *__restrict format,
                               $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter, stream, format, args);
}

@@>> wprintf(3), vwprintf(3), wprintf_unlocked(3), vwprintf_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("wprintf_unlocked")]]
[[alias("wprintf_unlocked"), export_as("_wprintf_p")]] /* Normal wprintf already supports positional arguments! */
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
__STDC_INT_AS_SIZE_T wprintf([[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vwprintf")}

[[cp_stdio, std, guard, wchar, doc_alias("wprintf"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("vwprintf_unlocked")]]
[[alias("vwprintf_unlocked"), export_as("_vwprintf_p")]] /* Normal wprintf already supports positional arguments! */
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(vfwprintf))]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.printf")]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SIZE_T vwprintf([[in, format]] wchar_t const *__restrict format, $va_list args) {
	return vfwprintf(stdout, format, args);
}

@@>> fwscanf(3), vfwscanf(3), fwscanf_unlocked(3), vfwscanf_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("fwscanf_unlocked")]]
[[alias("fwscanf_unlocked")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T fwscanf([[inout]] FILE *__restrict stream,
                             [[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vfwscanf")}

@@>> wscanf(3), vwscanf(3), wscanf_unlocked(3), vwscanf_unlocked(3)
[[cp_stdio, std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("wscanf_unlocked")]]
[[alias("wscanf_unlocked")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.read.scanf")]]
__STDC_INT_AS_SIZE_T wscanf([[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vwscanf")}

@@>> swscanf(3), vswscanf(3)
[[std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.scanf")]]
__STDC_INT_AS_SIZE_T swscanf([[in]] wchar_t const *__restrict src,
                             [[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vswscanf")}

%[define_wchar_replacement(____format_wsnprintf_data_defined = ____format_c16snprintf_data_defined, ____format_c32snprintf_data_defined)]
%[define_wchar_replacement(__format_wsnprintf_data = __format_c16snprintf_data, __format_c32snprintf_data)]

@@>> vswprintf(3)
[[std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[export_as("_vswprintf_p")]] /* Normal wprintf already supports positional arguments! */
[[impl_prefix(
@@pp_ifndef ____format_wsnprintf_data_defined@@
@#define@ ____format_wsnprintf_data_defined
struct __format_wsnprintf_data {
	wchar_t      *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
@@pp_endif@@
), dependency(format_wsnprintf_printer)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.printf")]]
__STDC_INT_AS_SIZE_T vswprintf([[out(? <= buflen)]] wchar_t *__restrict buf, size_t buflen,
                               [[in, format]] wchar_t const *__restrict format, $va_list args) {
	struct __format_wsnprintf_data data;
	__STDC_INT_AS_SSIZE_T result;
	data.__sd_buffer = buf;
	data.__sd_bufsiz = buflen;
	result = (__STDC_INT_AS_SSIZE_T)format_vwprintf(&format_wsnprintf_printer,
	                                                (void *)&data, format, args);
	if (result >= 0) {
		if (data.__sd_bufsiz != 0) {
			*data.__sd_buffer = (wchar_t)'\0';
		} else {
			if (buflen != 0)
				buf[buflen - 1] = (wchar_t)'\0';
		}
	}
	return result;
}

@@>> swprintf(3)
[[std, guard, wchar, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.format.printf")]]
[[export_as("_swprintf_p")]] /* Normal wprintf already supports positional arguments! */
__STDC_INT_AS_SIZE_T swprintf([[out(? <= buflen)]] wchar_t *__restrict buf, size_t buflen,
                              [[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vswprintf")}

%(std,c,ccompat)#endif /* __USE_ISOC95 || __USE_UNIX98 || __USE_DOS */

%[default:section(".text.crt{|.dos}.wchar.unicode.static.convert")]
%(std)

%(std,c,ccompat)#ifndef __NO_FPU

@@>> wcstod(3)
[[std, guard, wchar]]
[[dependency(unicode_readutf16, unicode_readutf16_rev)]]
wcstod(*) %{generate(str2wcs("strtod"))}

%(std,c,ccompat)#endif /* !__NO_FPU */

%(std,c,ccompat)#ifdef __USE_ISOC99
%(std,c,ccompat)#ifndef __NO_FPU

@@>> wcstof(3)
[[std, guard, wchar]]
[[dependency(unicode_readutf16, unicode_readutf16_rev)]]
wcstof(*) %{generate(str2wcs("strtof"))}

%(std,c,ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE

@@>> wcstold(3)
[[std, guard, wchar]]
[[dependency(unicode_readutf16, unicode_readutf16_rev)]]
wcstold(*) %{generate(str2wcs("strtold"))}

%(std,c,ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std,c,ccompat)#endif /* !__NO_FPU */

@@>> wcstoll(3)
[[std, guard, wchar]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_wcstoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_wcstol...)]]
[[                                                                                                alias(CNL_wcstoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias(CNL_wcsto64...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4),                   alias(CNL_wcsto32...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_wcstoimax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), crt_intern_alias("wcsto64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), crt_intern_alias("wcsto32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), export_as("wcstoimax")]]
wcstoll(*) %{generate(str2wcs("strtoll"))}

@@>> wcstoull(3)
[[std, guard, wchar]]
[[no_crt_self_import, no_crt_self_export, export_as(CNL_wcstoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_wcstoul...)]]
[[                                                                                                alias(CNL_wcstoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4),                   alias(CNL_wcstou32...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias(CNL_wcstou64...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_wcstoumax...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), crt_intern_alias("wcstou64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), crt_intern_alias("wcstou32")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__), export_as("wcstoumax")]]
wcstoull(*) %{generate(str2wcs("strtoull"))}

%[default:section(".text.crt{|.dos}.wchar.FILE.locked.read.scanf")]

%[define_wchar_replacement(__LIBCCALL_IS_FORMATPRINTER_CC = __LIBDCALL_IS_FORMATPRINTER_CC, __LIBKCALL_IS_FORMATPRINTER_CC)]
%[define_wchar_replacement(vfwscanf_getc = vfc16scanf_getc, vfc32scanf_getc)]
%[define_wchar_replacement(vfwscanf_ungetc = vfc16scanf_ungetc, vfc32scanf_ungetc)]
%[define_wchar_replacement(____vfwscanf_getc_defined = ____vfc16scanf_getc_defined, ____vfc32scanf_getc_defined)]
%[define_wchar_replacement(DEFINE_VFWSCANF_HELPERS = DEFINE_VFC16SCANF_HELPERS, DEFINE_VFC32SCANF_HELPERS)]

%[define(DEFINE_VFWSCANF_HELPERS =
@@pp_ifndef ____vfwscanf_getc_defined@@
#define ____vfwscanf_getc_defined
@@push_namespace(local)@@
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_WINT_T__@@
__LOCAL_LIBC(@vfwscanf_getc@) __format_word_t
(__FORMATPRINTER_CC vfwscanf_getc)(void *arg) {
	return (__format_word_t)fgetwc((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfwscanf_ungetc@) ssize_t
(__FORMATPRINTER_CC vfwscanf_ungetc)(void *arg, __format_word_t word) {
	return ungetwc((wint_t)word, (FILE *)arg);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VFC16SCANF_HELPERS =
@@pp_ifndef ____vfc16scanf_getc_defined@@
#define ____vfc16scanf_getc_defined
@@push_namespace(local)@@
@@pp_if !defined(__LIBDCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 2@@
__LOCAL_LIBC(@vfc16scanf_getc@) __format_word_t
(__FORMATPRINTER_CC vfc16scanf_getc)(void *arg) {
	return (__format_word_t)fgetc16((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfc16scanf_ungetc@) ssize_t
(__FORMATPRINTER_CC vfc16scanf_ungetc)(void *arg, __format_word_t word) {
	return ungetc16((wint16_t)word, (FILE *)arg);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VFC32SCANF_HELPERS =
@@pp_ifndef ____vfc32scanf_getc_defined@@
#define ____vfc32scanf_getc_defined
@@push_namespace(local)@@
@@pp_if !defined(__LIBKCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 4@@
__LOCAL_LIBC(@vfc32scanf_getc@) __format_word_t
(__FORMATPRINTER_CC vfc32scanf_getc)(void *arg) {
	return (__format_word_t)fgetc32((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfc32scanf_ungetc@) ssize_t
(__FORMATPRINTER_CC vfc32scanf_ungetc)(void *arg, __format_word_t word) {
	return ungetc32((wint32_t)word, (FILE *)arg);
}
@@pop_namespace@@
@@pp_endif@@
)]


[[std, cp_stdio, guard, wchar, wunused, doc_alias("fwscanf"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("vfwscanf_unlocked")]]
[[alias("vfwscanf_unlocked")]]
[[requires_dependent_function(fgetwc, ungetwc)]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_VFWSCANF_HELPERS)]]
__STDC_INT_AS_SIZE_T vfwscanf([[inout]] FILE *__restrict stream,
                              [[in, format]] wchar_t const *__restrict format,
                              $va_list args) {
@@pp_if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_WINT_T__@@
	return format_vwscanf((pformatgetc)(void *)&fgetwc,
	                      &__NAMESPACE_LOCAL_SYM vfwscanf_ungetc,
	                      (void *)stream,
	                      format, args);
@@pp_else@@
	return format_vwscanf(&__NAMESPACE_LOCAL_SYM vfwscanf_getc,
	                      &__NAMESPACE_LOCAL_SYM vfwscanf_ungetc,
	                      (void *)stream,
	                      format, args);
@@pp_endif@@
}



@@>> vwscanf(3)
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[cp_stdio, std, guard, wchar, wunused]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(vfwscanf))]]
__STDC_INT_AS_SIZE_T vwscanf([[in, format]] wchar_t const *__restrict format, $va_list args) {
	return vfwscanf(stdin, format, args);
}

%[default:section(".text.crt{|.dos}.wchar.unicode.static.format.scanf")]

%[define_wchar_replacement(vswscanf_getc = vsc16scanf_getc, vsc32scanf_getc)]
%[define_wchar_replacement(vswscanf_ungetc = vsc16scanf_ungetc, vsc32scanf_ungetc)]
%[define_wchar_replacement(____vswscanf_getc_defined = ____vsc16scanf_getc_defined, ____vsc32scanf_getc_defined)]
%[define_wchar_replacement(DEFINE_VSWSCANF_HELPERS = DEFINE_VSC16SCANF_HELPERS, DEFINE_VSC32SCANF_HELPERS)]

%[define(DEFINE_VSWSCANF_HELPERS =
@@pp_ifndef ____vswscanf_getc_defined@@
#define ____vswscanf_getc_defined
@@push_namespace(local)@@
__LOCAL_LIBC(@vswscanf_getc@) __format_word_t
(FORMATPRINTER_CC vswscanf_getc)(void *arg) {
	wchar_t const *reader = *(wchar_t const **)arg;
	wchar_t result        = *reader++;
	if (!result)
		return __EOF;
	*(wchar_t const **)arg = reader;
	return (__format_word_t)result;
}
__LOCAL_LIBC(@vswscanf_ungetc@) ssize_t
(FORMATPRINTER_CC vswscanf_ungetc)(void *arg, __format_word_t UNUSED(word)) {
	--(*(wchar_t const **)arg);
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VSC16SCANF_HELPERS =
@@pp_ifndef ____vsc16scanf_getc_defined@@
#define ____vsc16scanf_getc_defined
@@push_namespace(local)@@
__LOCAL_LIBC(@vsc16scanf_getc@) __format_word_t
(FORMATPRINTER_CC vsc16scanf_getc)(void *arg) {
	char16_t const *reader = *(char16_t const **)arg;
	char16_t result        = *reader++;
	if (!result)
		return __EOF;
	*(char16_t const **)arg = reader;
	return (__format_word_t)result;
}
__LOCAL_LIBC(@vsc16scanf_ungetc@) ssize_t
(FORMATPRINTER_CC vsc16scanf_ungetc)(void *arg, __format_word_t UNUSED(word)) {
	--(*(char16_t const **)arg);
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VSC32SCANF_HELPERS =
@@pp_ifndef ____vsc32scanf_getc_defined@@
#define ____vsc32scanf_getc_defined
@@push_namespace(local)@@
__LOCAL_LIBC(@vsc32scanf_getc@) __format_word_t
(FORMATPRINTER_CC vsc32scanf_getc)(void *arg) {
	char32_t const *reader = *(char32_t const **)arg;
	char32_t result        = *reader++;
	if (!result)
		return __EOF;
	*(char32_t const **)arg = reader;
	return (__format_word_t)result;
}
__LOCAL_LIBC(@vsc32scanf_ungetc@) ssize_t
(FORMATPRINTER_CC vsc32scanf_ungetc)(void *arg, __format_word_t UNUSED(word)) {
	--(*(char32_t const **)arg);
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
)]



[[std, guard, wchar, wunused, decl_include("<features.h>", "<hybrid/typecore.h>"), doc_alias("swscanf")]]
[[impl_include("<hybrid/typecore.h>", "<bits/crt/format-printer.h>", "<asm/crt/stdio.h>")]]
[[impl_prefix(DEFINE_VSWSCANF_HELPERS)]]
__STDC_INT_AS_SIZE_T vswscanf([[in]] wchar_t const *__restrict input,
                              [[in, format]] wchar_t const *__restrict format, $va_list args) {
	return format_vwscanf(&__NAMESPACE_LOCAL_SYM vswscanf_getc,
	                      &__NAMESPACE_LOCAL_SYM vswscanf_ungetc,
	                      (void *)&input, format, args);
}

%(std,c,ccompat)#endif /* __USE_ISOC99 */




@@>> wcstok(3)
@@Define wcstok() incorrectly, the same way DOS does
[[decl_include("<hybrid/typecore.h>")]]
[[std, guard, wchar, nocrt, inline, exposed_name("wcstok")]]
[[if(defined(__CRT_DOS_PRIMARY)), preferred_alias("wcstok")]]
wchar_t *broken_dos_wcstok([[inout_opt]] wchar_t *str,
                           [[in]] wchar_t const *__restrict delim) {
	static wchar_t *save_ptr = NULL;
	return wcstok(str, delim, &save_ptr);
}


%[insert:function(__mbrlen = mbrlen)]


%
%#ifdef __USE_XOPEN2K8
@@>> wcscasecmp(3)
[[wchar, dos_export_alias("_wcsicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcscasecmp(*) %{generate(str2wcs("strcasecmp"))}

@@>> wcsncasecmp(3)
[[wchar, dos_export_alias("_wcsnicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsncasecmp(*) %{generate(str2wcs("strncasecmp"))}

@@>> wcscasecmp_l(3)
[[wchar, dos_export_alias("_wcsicmp_l"), export_alias("__wcscasecmp_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcscasecmp_l(*) %{generate(str2wcs("strcasecmp_l"))}

@@>> wcsncasecmp_l(3)
[[wchar, dos_export_alias("_wcsnicmp_l"), export_alias("__wcsncasecmp_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcsncasecmp_l(*) %{generate(str2wcs("strncasecmp_l"))}

@@>> wcscoll_l(3)
[[wchar, dos_export_alias("_wcscoll_l"), export_alias("__wcscoll_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcscoll_l(*) %{generate(str2wcs("strcoll_l"))}

@@>> wcsxfrm_l(3)
[[wchar, dos_export_alias("_wcsxfrm_l"), export_alias("__wcsxfrm_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.memory")]]
wcsxfrm_l(*) %{generate(str2wcs("strxfrm_l"))}

@@>> wcpcpy(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcpcpy([[out]] wchar_t *__restrict dst,
                            [[in]] wchar_t const *__restrict src) {
	return wmempcpy(dst, src, wcslen(src) + 1);
}

@@>> wcpncpy(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcpncpy([[out(buflen)]] wchar_t *__restrict buf,
                             [[in(wcsnlen(., buflen))]] wchar_t const *__restrict src,
                             $size_t buflen) {
	$size_t srclen = wcsnlen(src, buflen);
	buf = wmempcpy(buf, src, srclen);
	buf = wmemset(buf, (wchar_t)'\0', ($size_t)(buflen - srclen));
	return buf;
}

@@>> mbsnrtowcs(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[decl_include("<hybrid/typecore.h>", "<bits/crt/mbstate.h>")]]
$size_t mbsnrtowcs([[out_opt/*(dstlen)*/]] wchar_t *__restrict dst,
                   [[inout]] char const **__restrict psrc, $size_t nmc, $size_t dstlen,
                   [[inout_opt]] $mbstate_t *mbs) {
	size_t result = 0;
	char const *src = *psrc;
	if (nmc) {
		while (dstlen) {
			size_t error;
			wchar_t wc;
			if (nmc >= UNICODE_UTF8_CURLEN) {
				error = mbrtowc(&wc, src, (size_t)-1, mbs);
			} else {
				char temp[UNICODE_UTF8_CURLEN];
				bzero(mempcpy(temp, src, nmc), UNICODE_UTF8_CURLEN - nmc);
				error = mbrtowc(&wc, temp, (size_t)-1, mbs);
			}
			if (!error) {
				src = NULL; /* NUL-character reached */
				break;
			}
			if (error == (size_t)-1) {
				result = (size_t)-1; /* EILSEQ */
				break;
			}
			if (dst != NULL)
				*dst++ = wc;
			--dstlen;
			++result;
			if (error >= nmc) {
				src = NULL; /* (implicit) NUL-character reached */
				break;
			}
			src += error;
			nmc -= error;
		}
	} else {
		src = NULL; /* (implicit) NUL-character reached */
	}
	if (dst != NULL)
		*psrc = src; /* Only update source if destination was given */
	return result;
}


@@>> wcsnrtombs(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[decl_include("<hybrid/typecore.h>", "<bits/crt/mbstate.h>")]]
$size_t wcsnrtombs([[out_opt/*(dstlen)*/]] char *dst,
                   [[inout]] wchar_t const **__restrict psrc, $size_t nwc, $size_t dstlen,
                   [[inout_opt]] $mbstate_t *mbs) {
	size_t result = 0;
	wchar_t const *src = *psrc;
	while (dstlen) {
		size_t error;
		char buf[UNICODE_UTF8_CURLEN];
		wchar_t ch;
		if (!nwc) {
			src = NULL; /* (implicit) NUL-character reached */
			break;
		}
		ch = *src;
		error = wcrtomb(buf, ch, mbs);
		if (error == (size_t)-1) {
			result = (size_t)-1; /* EILSEQ */
			break;
		}
		if (error > dstlen)
			break;
		if (dst != NULL)
			dst = (char *)mempcpy(dst, buf, error);
		result += error;
		dstlen -= error;
		++src;
		--nwc;
		if (ch == (wchar_t)'\0') {
			src = NULL; /* NUL-character reached */
			break;
		}
	}
	if (dst != NULL)
		*psrc = src; /* Only update source if destination was given */
	return result;
}

@@>> open_wmemstream(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
$FILE *open_wmemstream(wchar_t **bufloc, $size_t *sizeloc);
%#endif /* __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN2K8) || defined(__USE_DOS)

@@>> wcsnlen(3)
[[guard, wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
[[dos_export_alias("__wcsncnt")]] /* DOS-specific name */
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SNLEN))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SNLEN))]]
wcsnlen(*) %{generate(str2wcs("strnlen"))}

@@>> wcsdup(3)
[[guard, wchar, dos_export_alias("_wcsdup")]]
[[section(".text.crt{|.dos}.wchar.heap.strdup")]]
wcsdup(*) %{generate(str2wcs("strdup"))}

%#endif /* __USE_XOPEN2K8 || __USE_DOS */

%
%#ifdef __USE_XOPEN
@@>> wcwidth(3)
@@Returns the number of columns needed to display `ch' in a system terminal
@@When `ch' cannot be  displayed at all, `-1'  is returned (but `errno'  is
@@never modified by this function). Zero-width characters return `0'.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, const, wunused, nothrow, impl_include("<libc/unicode.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
int wcwidth(wchar_t ch) {
	if (__libc_unicode_isprint(ch))
		return 1;
	if (ch == 0)
		return 0;
	return -1;
}

@@>> wcswidth(3)
@@Returns the number of columns needed to display `str...+=wcslen(str, num_chars)'
@@in a system terminal. If any of the contained characters cannot be printed, then
@@`-1' is returned. (s.a. `wcwidth(3)')
[[section(".text.crt{|.dos}.wchar.unicode.static.mbs")]]
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>", "<features.h>")]]
__STDC_INT32_AS_SSIZE_T wcswidth([[in(wcsnlen(str, num_chars))]] wchar_t const *__restrict str,
                                 $size_t num_chars) {
	int temp;
	__STDC_INT32_AS_SSIZE_T result = 0;
	for (; num_chars; ++str, --num_chars) {
		wchar_t ch = *str;
		if (!ch)
			break;
		temp = wcwidth(ch);
		if (temp < 0)
			return temp;
		result += temp;
	}
	return result;
}
%#endif /* __USE_XOPEN */

%
%#ifdef __USE_XOPEN
%[insert:guarded_function(wcswcs = wcsstr)]
%#endif /* __USE_XOPEN */

%
%#ifdef __USE_GNU
@@>> wcschrnul(3)
@@Same as `wcschr', but return `wcsend(str)', rather than `NULL' if `needle' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nullable]] wchar_t *wcschrnul([[in]] wchar_t const *haystack, wchar_t needle)
	[([[in]] wchar_t *__restrict haystack, wchar_t needle): [[nullable]] wchar_t *]
	[([[in]] wchar_t const *__restrict haystack, wchar_t needle): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strchrnul"))}


%[define_wchar_replacement(wmempcpy = "(char16_t *)mempcpyw", "(char32_t *)mempcpyl")]

@@>> wmempcpy(3)
[[wchar, no_crt_impl, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("mempcpyw")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("mempcpyl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(mempcpyw)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(mempcpyl)]]
[[nonnull]] wchar_t *wmempcpy([[out(num_chars)]] wchar_t *__restrict dst,
                              [[in(num_chars)]] wchar_t const *__restrict src,
                              $size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempcpyw(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempcpyl(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)mempcpy(dst, src, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

%[define_wchar_replacement(wmempmove = "(char16_t *)mempmovew", "(char32_t *)mempmovel")]

@@>> wmempmove(3)
[[std, wchar, no_crt_impl, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("mempmovew")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("mempmovel")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(mempmovew)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(mempmovel)]]
[[nonnull]] wchar_t *wmempmove([[out(num_chars)]] wchar_t *dst,
                               [[in(num_chars)]] wchar_t const *src,
                               $size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempmovew(dst, src, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempmovel(dst, src, num_chars);
@@pp_else@@
	return (wchar_t *)mempmove(dst, src, num_chars * sizeof(wchar_t));
@@pp_endif@@
}

@@>> wcstol_l(3)
[[wchar, dos_export_alias("_wcstol_l"), export_alias("__wcstol_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),
  export_as("wcstoimax_l"), dos_export_as("DOS$_wcstoimax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstol_l(*) %{generate(str2wcs("strtol_l"))}

@@>> wcstoul_l(3)
[[wchar, dos_export_alias("_wcstoul_l"), export_alias("__wcstoul_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),
  export_as("wcstoumax_l"), dos_export_as("DOS$_wcstoumax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstoul_l(*) %{generate(str2wcs("strtoul_l"))}

%[insert:function(wcstoq = wcstoll)]
%[insert:function(wcstouq = wcstoull)]

%
%#ifdef __LONGLONG

@@>> wcstoll_l(3)
[[wchar, dos_export_alias("_wcstoll_l"), export_alias("__wcstoll_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_wcstol_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias(CNL_wcsto64_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_wcstoimax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),
  export_as("wcstoimax_l"), dos_export_as("DOS$_wcstoimax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstoll_l(*) %{generate(str2wcs("strtoll_l"))}

@@>> wcstoull_l(3)
[[wchar, dos_export_alias("_wcstoull_l"), export_alias("__wcstoull_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__),     alias(CNL_wcstoul_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8),                   alias(CNL_wcstou64_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INTMAX_T__), alias(CNL_wcstoumax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")
     __SIZEOF_INTMAX_T__ != 4 && __SIZEOF_INTMAX_T__ != 8 &&
     __SIZEOF_INTMAX_T__ != __SIZEOF_LONG__ &&
     __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),
  export_as("wcstoumax_l"), dos_export_as("DOS$_wcstoumax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstoull_l(*) %{generate(str2wcs("strtoull_l"))}
%#endif /* __LONGLONG */

%#ifndef __NO_FPU
@@>> wcstof_l(3)
[[wchar, dos_export_alias("_wcstof_l"), export_alias("__wcstof_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstof_l(*) %{generate(str2wcs("strtof_l"))}

@@>> wcstod_l(3)
[[wchar, dos_export_alias("_wcstod_l"), export_alias("__wcstod_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstod_l(*) %{generate(str2wcs("strtod_l"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
@@>> wcstold_l(3)
[[wchar, dos_export_alias("_wcstold_l"), export_alias("__wcstold_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstold_l(*) %{generate(str2wcs("strtold_l"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */

[[cp_stdio, wchar, doc_alias("getwchar"), decl_include("<hybrid/typecore.h>")]]
[[alias("getwchar")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(fgetwc_unlocked))]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.read.getc")]]
$wint_t getwchar_unlocked() {
	return fgetwc_unlocked(stdin);
}

[[cp_stdio, wchar, doc_alias("putwchar"), decl_include("<hybrid/typecore.h>")]]
[[alias("putwchar")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(fputwc_unlocked))]]
[[impl_include("<libc/template/stdstreams.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.putc")]]
$wint_t putwchar_unlocked(wchar_t wc) {
	return fputwc_unlocked(wc, stdout);
}

%[insert:function(getwc_unlocked = fgetwc_unlocked)]
%[insert:function(putwc_unlocked = fputwc_unlocked)]

[[cp_stdio, wchar, decl_include("<hybrid/typecore.h>")]]
[[export_alias("getwc_unlocked")]]
[[dos_export_alias("_getwc_nolock", "_fgetwc_nolock")]]
[[doc_alias("fgetwc"), alias("getwc", "fgetwc")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.read.getc")]]
$wint_t fgetwc_unlocked([[inout]] $FILE *__restrict stream);

[[cp_stdio, wchar, decl_include("<hybrid/typecore.h>")]]
[[export_alias("putwc_unlocked")]]
[[dos_export_alias("_putwc_nolock", "_fputwc_nolock")]]
[[doc_alias("fputwc"), alias("putwc", "fputwc")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.putc")]]
$wint_t fputwc_unlocked(wchar_t wc, [[inout]] $FILE *__restrict stream);

[[cp_stdio, wchar, doc_alias("fgetws"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_export_alias("_fgetws_nolock"), alias("fgetws")]]
[[requires_function(fgetwc_unlocked, ungetwc_unlocked, ferror_unlocked)]]
[[impl_include("<asm/crt/stdio.h>", "<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.read.read")]]
wchar_t *fgetws_unlocked([[out(? <= bufsize)]] wchar_t *__restrict buf, __STDC_INT_AS_SIZE_T bufsize,
                         [[inout]] $FILE *__restrict stream) {
	$size_t n;
	if unlikely(!buf || !bufsize) {
		/* The buffer cannot be empty! */
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_endif@@
		return NULL;
	}
	for (n = 0; n < bufsize - 1; ++n) {
		wint_t ch = fgetwc_unlocked(stream);
		if (ch == WEOF) {
			if (n == 0 || ferror_unlocked(stream))
				return NULL;
			break;
		}
		if (ch == (wchar_t)'\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			buf[n++] = (wchar_t)'\n';
			ch = fgetwc_unlocked(stream);
			if (ch == WEOF) {
				if (n == 0 || ferror_unlocked(stream))
					return NULL;
				break;
			}
			if (ch == (wchar_t)'\r')
				continue;
			ungetwc_unlocked(ch, stream);
			break;
		}
		buf[n] = (wchar_t)ch;
		if (ch == (wchar_t)'\n')
			break;
	}
	buf[n] = (wchar_t)'\0';
	return buf;
}

[[wchar, cp_stdio, doc_alias("fputws"), decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[dos_export_alias("_fputws_nolock"), alias("fputws")]]
[[requires_function(file_wprinter_unlocked)]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.write")]]
__STDC_INT_AS_SIZE_T fputws_unlocked([[in]] wchar_t const *__restrict str,
                                     [[inout]] $FILE *__restrict stream) {
	__STDC_INT_AS_SIZE_T result;
	result = file_wprinter_unlocked(stream, str, wcslen(str));
	return result;
}


@@>> wcsftime_l(3)
[[wchar, decl_include("<bits/crt/tm.h>", "<hybrid/typecore.h>")]]
[[dos_export_alias("_wcsftime_l"), export_alias("__wcsftime_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.format.strftime")]]
$size_t wcsftime_l([[out(return <= maxsize)]] wchar_t *__restrict buf, $size_t maxsize,
                   [[in, format("wcsftime")]] wchar_t const *__restrict format,
                   [[in]] struct $tm const *__restrict tp,
                   $locale_t locale) {
	(void)locale;
	return wcsftime(buf, maxsize, format, tp);
}

%#endif /* __USE_GNU */

%
%
%
%

%#ifdef __USE_KOS

%{
/* Static initializer for `mbstate_t':
 * >> mbstate_t mbs = MBSTATE_INIT; */
#if !defined(MBSTATE_INIT) && defined(__MBSTATE_INIT)
#define MBSTATE_INIT __MBSTATE_INIT
#endif /* !MBSTATE_INIT && __MBSTATE_INIT */

/* Dynamic initializer for `mbstate_t':
 * >> mbstate_t mbs;
 * >> mbstate_init(&mbs); */
#if !defined(mbstate_init) && defined(__mbstate_init)
#define mbstate_init __mbstate_init
#endif /* !mbstate_init && __mbstate_init */

/* Check if the given mbstate_t is in its zero-shift state:
 * >> if (mbstate_isempty(&mbs)) { ... } */
#if !defined(mbstate_isempty) && defined(__mbstate_isempty)
#define mbstate_isempty __mbstate_isempty
#endif /* !mbstate_isempty && __mbstate_isempty */
}


%
%/* KOS FILE extension functions. */
%

%[define(DEFINE_FREE_AND_RETURN_ZERO =
@@pp_ifndef ____free_and_return_zero_defined@@
#define ____free_and_return_zero_defined
@@pp_if $has_function(free)@@
@@push_namespace(local)@@
__LOCAL_LIBC(@free_and_return_zero@) int
(__LIBKCALL __free_and_return_zero)(void *arg) {
	free(arg);
	return 0;
}
@@pop_namespace@@
@@pp_endif@@
@@pp_endif@@
)]

%[define(DEFINE_FOPEN_WPRINTER_FLUSH =
@@pp_ifndef ____fopen_wprinter_flush_defined@@
#define ____fopen_wprinter_flush_defined
@@push_namespace(local)@@
__LOCAL_LIBC(@fopen_wprinter_flush@) int
(__LIBKCALL __fopen_wprinter_flush)(void *arg) {
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		$pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		$mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *me = (struct __local_format_8tow_data *)arg;

	/* Verify that the mbstate is in an empty state. */
	if (__mbstate_isempty(&me->fd_incomplete))
		return 0;

	/* If it isn't then we must indicate an illegal-sequence error. */
@@pp_ifdef EILSEQ@@
	return libc_seterrno(EILSEQ);
@@pp_else@@
	return libc_seterrno(1);
@@pp_endif@@
}
@@pop_namespace@@
@@pp_endif@@
)]


@@>> fopen_wprinter(3)
@@Create and return a new write-only file-stream that will write to the given printer.
@@Note  that by default, the buffering is enabled for the file-stream, meaning you may
@@have to call `fflush(return)' before printed data is committed to the given printer.
@@- Buffering can be disabled with `setvbuf(return, NULL, _IONBF, 0)'
@@- When `printer' returns a negative value, `ferror(return)' becomes set
@@- When calling `fflush(return)', with the current unicode sequence is incomplete,
@@  that function will return with `-1' and `errno == EILSEQ'
@@@return: * :   A file-stream that emits its data to `printer'
@@@return: NULL: Insufficient memory.
[[wunused, wchar, decl_include("<bits/crt/wformat-printer.h>")]]
[[requires($has_function(malloc, format_8tow) &&
           ($has_function(funopen2_64) || $has_function(funopen2)))]]
[[impl_include("<bits/crt/wformat-printer.h>", "<hybrid/typecore.h>")]]
[[impl_include("<bits/crt/mbstate.h>", "<libc/errno.h>")]]
[[impl_prefix(DEFINE_FREE_AND_RETURN_ZERO)]]
[[impl_prefix(DEFINE_FOPEN_WPRINTER_FLUSH)]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
$FILE *fopen_wprinter([[nonnull]] __pwformatprinter printer, void *arg) {
	FILE *result;
	struct __local_format_8tow_data {   /* == `struct format_8tow_data' */
		$pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void            *fd_arg;        /* Argument for `fd_printer' */
		$mbstate_t       fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	} *cookie;
	cookie = (struct __local_format_8tow_data *)malloc(sizeof(struct __local_format_8tow_data));
	if unlikely(!cookie)
		return NULL;
	cookie->fd_printer = printer;
	cookie->fd_arg     = arg;
	__mbstate_init(&cookie->fd_incomplete);

	/* KOS's pformatprinter is ABI-compatible with the `writefn' of `funopen2(3)' / `funopen2_64(3)'
	 * -> As such, this function can super-easily be implemented with the help of that one! */
@@pp_if $has_function(free)@@
@@pp_if $has_function(funopen2_64)@@
	result = funopen2_64(cookie, NULL, (ssize_t (LIBKCALL *)(void *, void const *, size_t))&format_8tow, NULL,
	                     &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush,
	                     &__NAMESPACE_LOCAL_SYM __free_and_return_zero);
@@pp_else@@
	result = funopen2(cookie, NULL, (ssize_t (LIBKCALL *)(void *, void const *, size_t))&format_8tow, NULL,
	                  &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush,
	                  &__NAMESPACE_LOCAL_SYM __free_and_return_zero);
@@pp_endif@@
@@pp_else@@
@@pp_if $has_function(funopen2_64)@@
	result = funopen2_64(cookie, NULL, (ssize_t (LIBKCALL *)(void *, void const *, size_t))&format_8tow,
	                     NULL, &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush, NULL);
@@pp_else@@
	result = funopen2(cookie, NULL, (ssize_t (LIBKCALL *)(void *, void const *, size_t))&format_8tow,
	                  NULL, &__NAMESPACE_LOCAL_SYM __fopen_wprinter_flush, NULL);
@@pp_endif@@
@@pp_endif@@

	/* Cleanup on error. */
@@pp_if $has_function(free)@@
	if unlikely(!result)
		free(cookie);
@@pp_endif@@
	return result;
}


@@>> file_wprinter(3), file_wprinter_unlocked(3)
@@For use with `format_wprintf()' and friends: Prints to a `FILE *' closure argument
[[cp_stdio, wchar, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<features.h>")defined(__USE_STDIO_UNLOCKED)), preferred_alias("file_wprinter_unlocked")]]
[[alias("file_wprinter_unlocked")]]
[[userimpl, requires($has_function(fputwc))]]
[[impl_include("<asm/crt/stdio.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.write.write")]]
$ssize_t file_wprinter([[nonnull]] void *arg,
                       [[in(datalen)]] wchar_t const *__restrict data,
                       $size_t datalen) {
	$size_t i;
	for (i = 0; i < datalen; ++i) {
		if (fputwc(data[i], ($FILE *)arg) == WEOF)
			break;
	}
	return (ssize_t)i;
}

[[cp_stdio, wchar, doc_alias("file_wprinter"), decl_include("<hybrid/typecore.h>")]]
[[alias("file_wprinter")]]
[[userimpl, requires_function(fputwc_unlocked)]]
[[impl_include("<asm/crt/stdio.h>")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.write")]]
$ssize_t file_wprinter_unlocked([[nonnull]] void *arg,
                                [[in(datalen)]] wchar_t const *__restrict data,
                                $size_t datalen) {
	$size_t i;
	for (i = 0; i < datalen; ++i) {
		if (fputwc_unlocked(data[i], ($FILE *)arg) == WEOF)
			break;
	}
	return (ssize_t)i;
}


[[wchar, doc_alias("ungetwc"), decl_include("<hybrid/typecore.h>")]]
[[dos_export_alias("_ungetwc_nolock"), alias("ungetwc")]]
[[section(".text.crt{|.dos}.wchar.FILE.unlocked.write.putc")]]
$wint_t ungetwc_unlocked($wint_t ch, [[inout]] $FILE *__restrict stream);


%[default:section(".text.crt{|.dos}.wchar.FILE.unlocked.write.printf")]

[[cp_stdio, wchar, doc_alias("vfwprintf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("vfwprintf")]]
[[requires_dependent_function(file_wprinter_unlocked)]]
__STDC_INT_AS_SIZE_T vfwprintf_unlocked([[inout]] $FILE *__restrict stream,
                                        [[in, format]] wchar_t const *__restrict format,
                                        $va_list args) {
	return (__STDC_INT_AS_SSIZE_T)format_vwprintf(&file_wprinter_unlocked,
	                                              stream, format, args);
}

[[cp_stdio, wchar, doc_alias("fwprintf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("fwprintf")]]
__STDC_INT_AS_SIZE_T fwprintf_unlocked([[inout]] $FILE *__restrict stream,
                                       [[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vfwprintf_unlocked")}

[[cp_stdio, wchar, doc_alias("wprintf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("wprintf")]]
__STDC_INT_AS_SIZE_T wprintf_unlocked([[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vwprintf_unlocked")}

[[cp_stdio, wchar, doc_alias("vwprintf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("vwprintf")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdout) && $has_function(vfwprintf_unlocked))]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SIZE_T vwprintf_unlocked([[in, format]] wchar_t const *__restrict format, $va_list args) {
	return vfwprintf_unlocked(stdout, format, args);
}

%[default:section(".text.crt{|.dos}.wchar.FILE.unlocked.read.scanf")]

%[define_wchar_replacement(vfwscanf_unlocked_getc = vfc16scanf_unlocked_getc, vfc32scanf_unlocked_getc)]
%[define_wchar_replacement(vfwscanf_unlocked_ungetc = vfc16scanf_unlocked_ungetc, vfc32scanf_unlocked_ungetc)]
%[define_wchar_replacement(____vfwscanf_unlocked_getc_defined = ____vfc16scanf_unlocked_getc_defined, ____vfc32scanf_unlocked_getc_defined)]
%[define_wchar_replacement(DEFINE_VFWSCANF_UNLOCKED_HELPERS = DEFINE_VFC16SCANF_UNLOCKED_HELPERS, DEFINE_VFC32SCANF_UNLOCKED_HELPERS)]

%[define(DEFINE_VFWSCANF_UNLOCKED_HELPERS =
@@pp_ifndef ____vfwscanf_unlocked_getc_defined@@
#define ____vfwscanf_unlocked_getc_defined
@@push_namespace(local)@@
@@pp_if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != __SIZEOF_WINT_T__@@
__LOCAL_LIBC(@vfwscanf_unlocked_getc@) __format_word_t
(__FORMATPRINTER_CC vfwscanf_unlocked_getc)(void *arg) {
	return (__format_word_t)fgetwc_unlocked((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfwscanf_unlocked_ungetc@) ssize_t
(__FORMATPRINTER_CC vfwscanf_unlocked_ungetc)(void *arg, __format_word_t word) {
	return ungetwc_unlocked((wint_t)word, (FILE *)arg);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VFC16SCANF_UNLOCKED_HELPERS =
@@pp_ifndef ____vfc16scanf_unlocked_getc_defined@@
#define ____vfc16scanf_unlocked_getc_defined
@@push_namespace(local)@@
@@pp_if !defined(__LIBDCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 2@@
__LOCAL_LIBC(@vfc16scanf_unlocked_getc@) __format_word_t
(__FORMATPRINTER_CC vfc16scanf_unlocked_getc)(void *arg) {
	return (__format_word_t)fgetc16_unlocked((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfc16scanf_unlocked_ungetc@) ssize_t
(__FORMATPRINTER_CC vfc16scanf_unlocked_ungetc)(void *arg, __format_word_t word) {
	return ungetc16_unlocked((wint16_t)word, (FILE *)arg);
}
@@pop_namespace@@
@@pp_endif@@
)]

%[define(DEFINE_VFC32SCANF_UNLOCKED_HELPERS =
@@pp_ifndef ____vfc32scanf_unlocked_getc_defined@@
#define ____vfc32scanf_unlocked_getc_defined
@@push_namespace(local)@@
@@pp_if !defined(__LIBKCALL_IS_FORMATPRINTER_CC) || __SIZEOF_FORMAT_WORD_T__ != 4@@
__LOCAL_LIBC(@vfc32scanf_unlocked_getc@) __format_word_t
(__FORMATPRINTER_CC vfc32scanf_unlocked_getc)(void *arg) {
	return (__format_word_t)fgetc32_unlocked((FILE *)arg);
}
@@pp_endif@@
__LOCAL_LIBC(@vfc32scanf_unlocked_ungetc@) ssize_t
(__FORMATPRINTER_CC vfc32scanf_unlocked_ungetc)(void *arg, __format_word_t word) {
	return ungetc32_unlocked((wint32_t)word, (FILE *)arg);
}
@@pop_namespace@@
@@pp_endif@@
)]


[[cp_stdio, wunused, wchar, doc_alias("vfwscanf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("vfwscanf")]]
[[requires_dependent_function(fgetwc_unlocked, ungetwc_unlocked)]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_prefix(DEFINE_VFWSCANF_UNLOCKED_HELPERS)]]
__STDC_INT_AS_SIZE_T vfwscanf_unlocked([[inout]] $FILE *__restrict stream,
                                       [[in, format]] wchar_t const *__restrict format,
                                       $va_list args) {
@@pp_if defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_FORMAT_WORD_T__ == __SIZEOF_WINT_T__@@
	return format_vwscanf((pformatgetc)(void *)&fgetwc_unlocked,
	                      &__NAMESPACE_LOCAL_SYM vfwscanf_unlocked_ungetc,
	                      (void *)stream,
	                      format, args);
@@pp_else@@
	return format_vwscanf(&__NAMESPACE_LOCAL_SYM vfwscanf_unlocked_getc,
	                      &__NAMESPACE_LOCAL_SYM vfwscanf_unlocked_ungetc,
	                      (void *)stream,
	                      format, args);
@@pp_endif@@
}



[[cp_stdio, wchar, wunused, doc_alias("vwscanf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("vwscanf")]]
[[requires_include("<libc/template/stdstreams.h>")]]
[[requires(defined(__LOCAL_stdin) && $has_function(vfwscanf_unlocked))]]
[[impl_include("<libc/template/stdstreams.h>")]]
__STDC_INT_AS_SIZE_T vwscanf_unlocked([[in, format]] wchar_t const *__restrict format,
                                      $va_list args) {
	return vfwscanf_unlocked(stdin, format, args);
}

[[cp_stdio, wchar, wunused, doc_alias("fwscanf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("fwscanf")]]
__STDC_INT_AS_SIZE_T fwscanf_unlocked([[inout]] $FILE *__restrict stream,
                                      [[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vfwscanf_unlocked")}

[[cp_stdio, wchar, wunused, doc_alias("wscanf")]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[alias("wscanf")]]
__STDC_INT_AS_SIZE_T wscanf_unlocked([[in, format]] wchar_t const *__restrict format, ...)
	%{printf("vwscanf_unlocked")}


%
%
%
%



/* KOS String extension functions. */
@@>> wcsend(3)
@@Same as `str + wcslen(str)'
[[wchar, pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SEND))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SEND))]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsend([[in]] wchar_t const *__restrict str)
	[([[in]] wchar_t *__restrict str): [[nonnull]] wchar_t *]
	[([[in]] wchar_t const *__restrict str): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strend"))}

@@>> wcsnend(3)
@@Same as `str + wcsnlen(str, max_chars)'
[[wchar, pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
[[crt_dos_impl_requires(!defined(LIBC_ARCH_HAVE_C16SNEND))]]
[[crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_C32SNEND))]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnend([[in(wcsnlen(str, maxlen))]] wchar_t const *__restrict str, $size_t maxlen)
	[([[in(wcsnlen(str, maxlen))]] wchar_t *__restrict str, $size_t maxlen): [[nonnull]] wchar_t *]
	[([[in(wcsnlen(str, maxlen))]] wchar_t const *__restrict str, $size_t maxlen): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strnend"))}


@@>> wcsto32_r(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcsto32_r(*) %{generate(str2wcs("strto32_r"))}

@@>> wcstou32_r(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstou32_r(*) %{generate(str2wcs("strtou32_r"))}


@@>> wcsto32(3)
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), export_as("wcstoimax")]]
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      preferred_alias(CNL_wcstol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), preferred_alias(CNL_wcstoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_wcstoimax...)]]
wcsto32(*) %{generate(str2wcs("strto32"))}

@@>> wcstou32(3)
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4), export_as("wcstoumax")]]
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      preferred_alias(CNL_wcstoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), preferred_alias(CNL_wcstoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_wcstoumax...)]]
wcstou32(*) %{generate(str2wcs("strtou32"))}

%
%#ifdef __UINT64_TYPE__
@@>> wcsto64_r(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcsto64_r(*) %{generate(str2wcs("strto64_r"))}

@@>> wcstou64_r(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstou64_r(*) %{generate(str2wcs("strtou64_r"))}


@@>> wcsto64(3)
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), export_as("wcstoimax")]]
[[wchar, dos_export_alias("_wcstoi64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      preferred_alias(CNL_wcstol...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), preferred_alias(CNL_wcstoll...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_wcstoimax...)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcsto64(*) %{generate(str2wcs("strto64"))}

@@>> wcstou64(3)
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8), export_as("wcstoumax")]]
[[wchar, dos_export_alias("_wcstoui64")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      preferred_alias(CNL_wcstoul...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), preferred_alias(CNL_wcstoull...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_wcstoumax...)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.convert")]]
wcstou64(*) %{generate(str2wcs("strtou64"))}
%#endif /* __UINT64_TYPE__ */

/************************************************************************/
/* WARNING: The following functions aren't exported by-name from libc!  */
/************************************************************************/
@@>> wcstol_r(3)
[[wchar, nocrt]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), alias("wcsto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("wcsto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(wcsto32_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(wcsto64_r)]]
wcstol_r(*) %{generate(str2wcs("strtol_r"))}

@@>> wcstoul_r(3)
[[wchar, nocrt]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), alias("wcstou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("wcstou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4), bind_local_function(wcstou32_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), bind_local_function(wcstou64_r)]]
wcstoul_r(*) %{generate(str2wcs("strtoul_r"))}

%#ifdef __LONGLONG
@@>> wcstoll_r(3)
[[wchar, nocrt]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("wcsto64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias("wcsto32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(wcsto64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(wcsto32_r)]]
wcstoll_r(*) %{generate(str2wcs("strtoll_r"))}

@@>> wcstoull_r(3)
[[wchar, nocrt]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("wcstou64_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), alias("wcstou32_r")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), bind_local_function(wcstou64_r)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), bind_local_function(wcstou32_r)]]
wcstoull_r(*) %{generate(str2wcs("strtoull_r"))}
%#endif /* __LONGLONG */
/************************************************************************/


%
%#ifdef __USE_XOPEN2K8
@@>> wcsto32_l(3)
[[wchar]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      preferred_alias(CNL_wcstol_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), preferred_alias(CNL_wcstoll_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_wcstoimax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  export_as("wcstoimax_l"), dos_export_as("DOS$_wcstoimax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcsto32_l(*) %{generate(str2wcs("strto32_l"))}

@@>> wcstou32_l(3)
[[wchar]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 4),      preferred_alias(CNL_wcstoul_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 4), preferred_alias(CNL_wcstoull_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  alias(CNL_wcstoumax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 4),  export_as("wcstoumax_l"), dos_export_as("DOS$_wcstoumax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstou32_l(*) %{generate(str2wcs("strtou32_l"))}

%
%#ifdef __UINT64_TYPE__
@@>> wcsto64_l(3)
[[wchar, dos_export_alias("_wcstoi64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      preferred_alias(CNL_wcstol_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), preferred_alias(CNL_wcstoll_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_wcstoimax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  export_as("wcstoimax_l"), dos_export_as("DOS$_wcstoimax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcsto64_l(*) %{generate(str2wcs("strto64_l"))}

@@>> wcstou64_l(3)
[[wchar, dos_export_alias("_wcstoui64_l")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8),      preferred_alias(CNL_wcstoul_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), preferred_alias(CNL_wcstoull_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  alias(CNL_wcstoumax_l...)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INTMAX_T__ == 8),  export_as("wcstoumax_l"), dos_export_as("DOS$_wcstoumax_l")]]
[[section(".text.crt{|.dos}.wchar.unicode.locale.convert")]]
wcstou64_l(*) %{generate(str2wcs("strtou64_l"))}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_XOPEN2K8 */




%
@@>> wcsncoll(3)
[[wchar, dos_export_alias("_wcsncoll")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsncoll(*) %{generate(str2wcs("strncoll"))}

@@>> wcscasecoll(3)
[[wchar, dos_export_alias("_wcsicoll"), alias("wcsicoll")]]
[[alias("wcscasecmp", "_wcsicmp", "wcsicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcscasecoll(*) %{generate(str2wcs("strcasecoll"))}

@@>> wcsncasecoll(3)
[[wchar, dos_export_alias("_wcsnicoll"), alias("wcsnicoll")]]
[[alias("wcsncasecmp", "_wcsnicmp", "wcsnicmp")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsncasecoll(*) %{generate(str2wcs("strncasecoll"))}

@@>> wcsnrev(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, leaf, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnrev([[inout(wcsnlen(str, maxlen))]] wchar_t *__restrict str, $size_t maxlen) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memrevw(str, wcsnlen(str, maxlen));
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memrevl(str, wcsnlen(str, maxlen));
@@pp_else@@
	return (wchar_t *)memrev(str, wcsnlen(str, maxlen) * sizeof(wchar_t));
@@pp_endif@@
}

@@>> wcsnlwr(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsnlwr(*) %{generate(str2wcs("strnlwr"))}

@@>> wcsnupr(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wcsnupr(*) %{generate(str2wcs("strnupr"))}

@@>> wcscasestr(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
[[nullable]] wchar_t *wcscasestr([[in]] wchar_t const *haystack, wchar_t const *needle)
	[([[in]] wchar_t *haystack, [[in]] wchar_t *needle): [[nullable]] wchar_t *]
	[([[in]] wchar_t const *haystack, [[in]] wchar_t const *needle): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strcasestr"))}

@@>> wcspcpy(3)
@@Same as wcscpy, but return a pointer after the last written character
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, leaf, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcspcpy([[out]] wchar_t *__restrict buf,
                             [[in]] wchar_t const *__restrict src) {
	return wmempcpy(buf, src, wcslen(src) + 1);
}

@@>> wcspncpy(3)
@@Same as wcsncpy, but return a pointer after the last written character
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, leaf, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcspncpy([[out(buflen)]] wchar_t *__restrict buf,
                              [[in(wcsnlen(src, buflen))]] wchar_t const *__restrict src, $size_t buflen) {
	$size_t srclen = wcsnlen(src, buflen);
	buf = wmempcpy(buf, src, srclen);
	buf = wmempset(buf, (wchar_t)'\0', buflen - srclen);
	return buf;
}

%[define_wchar_replacement(wmempset = "(char16_t *)mempsetw", "(char32_t *)mempsetl")]

@@>> wmempset(3)
@@Same as wmemset, but return a pointer after the last written character
[[wchar, leaf, no_crt_impl, decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("mempsetw")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("mempsetl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(mempsetw)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(mempsetl)]]
[[nonnull]] wchar_t *wmempset([[out(num_chars)]] wchar_t *dst,
                              wchar_t filler, $size_t num_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)mempsetw(dst, (u16)filler, num_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)mempsetl(dst, (u32)filler, num_chars);
@@pp_else@@
	return (wchar_t *)mempset(dst, (int)filler, num_chars * sizeof(wchar_t));
@@pp_endif@@
}


@@>> wcsnchr(3)
@@Same as `wcschr', but don't exceed `max_chars' characters.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nullable]] wchar_t *wcsnchr([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[in(wcsnlen(., maxlen))]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): [[nullable]] wchar_t *]
	[([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strnchr"))}

@@>> wcsnrchr(3)
@@Same as `wcsrchr', but don't exceed `max_chars' characters.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nullable]] wchar_t *wcsnrchr([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[in(wcsnlen(., maxlen))]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): [[nullable]] wchar_t *]
	[([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): [[nullable]] wchar_t const *]
	%{generate(str2wcs("strnrchr"))}

@@>> wcssep(3)
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcssep(*) %{generate(str2wcs("strsep"))}

@@>> wcsfry(3)
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcsfry(*) %{generate(str2wcs("strfry"))}

@@>> wcsndup(3)
[[wchar, section(".text.crt{|.dos}.wchar.heap.strdup")]]
wcsndup(*) %{generate(str2wcs("strndup"))}


@@>> wcsrchrnul(3)
@@Same as `wcsrchr', but return `str-1', rather than `NULL' if `needle' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsrchrnul([[in]] wchar_t const *__restrict haystack, wchar_t needle)
	[([[in]] wchar_t *__restrict haystack, wchar_t needle): [[nonnull]] wchar_t *]
	[([[in]] wchar_t const *__restrict haystack, wchar_t needle): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strrchrnul"))}

@@>> wcsnchrnul(3)
@@Same as `wcsnchr', but return `wcsnend(str, max_chars)', rather than `NULL' if `needle' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnchrnul([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[in(wcsnlen(., maxlen))]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t *]
	[([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strnchrnul"))}

@@>> wcsnrchrnul(3)
@@Same as `wcsnrchr', but return `str-1', rather than `NULL' if `needle' wasn't found.
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnrchrnul([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	[([[in(wcsnlen(., maxlen))]] wchar_t *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t *]
	[([[in(wcsnlen(., maxlen))]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen): [[nonnull]] wchar_t const *]
	%{generate(str2wcs("strnrchrnul"))}

@@>> wcsoff(3)
@@Same as `wcschrnul', but return the offset from `str', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsoff([[in]] wchar_t const *__restrict haystack, wchar_t needle)
	%{generate(str2wcs("stroff"))}

@@>> wcsroff(3)
@@Same as `wcsrchrnul', but return the offset from `str', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsroff([[in]] wchar_t const *__restrict haystack, wchar_t needle)
	%{generate(str2wcs("strroff"))}

@@>> wcsnoff(3)
@@Same as `wcsnchrnul', but return the offset from `str', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsnoff([[in]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	%{generate(str2wcs("strnoff"))}

@@>> wcsnroff(3)
@@Same as `wcsnrchrnul', but return the offset from `str', rather than the actual address
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t wcsnroff([[in]] wchar_t const *__restrict haystack, wchar_t needle, $size_t maxlen)
	%{generate(str2wcs("strnroff"))}


%[define_wchar_replacement(fuzzy_wmemcmp = fuzzy_memcmpw, fuzzy_memcmpl)]

@@>> fuzzy_wmemcmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, no_crt_impl]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("fuzzy_memcmpw")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("fuzzy_memcmpl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(fuzzy_memcmpw)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(fuzzy_memcmpl)]]
$size_t fuzzy_wmemcmp([[in(s1_chars)]] wchar_t const *s1, $size_t s1_chars,
                      [[in(s2_chars)]] wchar_t const *s2, $size_t s2_chars) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return fuzzy_memcmpw(s1, s1_chars, s2, s2_chars);
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return fuzzy_memcmpl(s1, s1_chars, s2, s2_chars);
@@pp_else@@
	return fuzzy_memcmp(s1, s1_chars * sizeof(wchar_t), s2, s2_chars * sizeof(wchar_t));
@@pp_endif@@
}

@@>> fuzzy_wcscmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, requires_function(fuzzy_wmemcmp)]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t fuzzy_wcscmp([[in]] wchar_t const *s1,
                     [[in]] wchar_t const *s2) {
	return fuzzy_wmemcmp(s1, wcslen(s1), s2, wcslen(s2));
}

@@>> fuzzy_wcsncmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, requires_function(fuzzy_wmemcmp)]]
[[section(".text.crt{|.dos}.wchar.string.memory")]]
$size_t fuzzy_wcsncmp([[in(wcsnlen(., s1_maxlen))]] wchar_t const *s1, $size_t s1_maxlen,
                      [[in(wcsnlen(., s2_maxlen))]] wchar_t const *s2, $size_t s2_maxlen) {
	return fuzzy_wmemcmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

@@>> fuzzy_wmemcasecmp(3)
[[wchar, pure, wunused, decl_include("<hybrid/typecore.h>")]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
$size_t fuzzy_wmemcasecmp([[in(s1_bytes)]] wchar_t const *s1, $size_t s1_bytes,
                          [[in(s2_bytes)]] wchar_t const *s2, $size_t s2_bytes)
	%{generate(str2wcs("fuzzy_memcasecmp"))}

@@>> fuzzy_wcscasecmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, requires_function(fuzzy_wmemcasecmp)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
$size_t fuzzy_wcscasecmp([[in]] wchar_t const *s1, [[in]] wchar_t const *s2) {
	return fuzzy_wmemcasecmp(s1, wcslen(s1), s2, wcslen(s2));
}

@@>> fuzzy_wcsncasecmp(3)
[[decl_include("<hybrid/typecore.h>")]]
[[wchar, pure, wunused, requires_function(fuzzy_wmemcasecmp)]]
[[section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
$size_t fuzzy_wcsncasecmp([[in(wcsnlen(., s1_maxlen))]] wchar_t const *s1, $size_t s1_maxlen,
                          [[in(wcsnlen(., s2_maxlen))]] wchar_t const *s2, $size_t s2_maxlen) {
	return fuzzy_wmemcasecmp(s1, wcsnlen(s1, s1_maxlen), s2, wcsnlen(s2, s2_maxlen));
}

@@>> wildwcscmp(3)
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wildwcscmp(*) %{generate(str2wcs("wildstrcmp"))}

@@>> wildwcscasecmp(3)
[[wchar, section(".text.crt{|.dos}.wchar.unicode.static.memory")]]
wildwcscasecmp(*) %{generate(str2wcs("wildstrcasecmp"))}

@@>> wcsverscmp(3)
[[wchar, section(".text.crt{|.dos}.wchar.string.memory")]]
wcsverscmp(*) %{generate(str2wcs("strverscmp"))}



@@>> wcslstrip(3)
[[wchar]]
wcslstrip(*) %{generate(str2wcs("strlstrip"))}

@@>> wcsrstrip(3)
[[wchar]]
wcsrstrip(*) %{generate(str2wcs("strrstrip"))}

@@>> wcsstrip(3)
[[wchar]]
wcsstrip(*) %{generate(str2wcs("strstrip"))}


@@>> wmemcasecmp(3)
[[wchar]]
wmemcasecmp(*) %{generate(str2wcs("memcasecmp"))}

%
%#ifdef __USE_XOPEN2K8
%[default:section(".text.crt{|.dos}.wchar.unicode.locale.memory")]

@@>> wmemcasecmp_l(3)
[[wchar]]
wmemcasecmp_l(*) %{generate(str2wcs("memcasecmp_l"))}

@@>> wcsncoll_l(3)
[[wchar, dos_export_alias("_wcsncoll_l")]]
wcsncoll_l(*) %{generate(str2wcs("strncoll_l"))}

@@>> wcscasecoll_l(3)
[[wchar, dos_export_alias("_wcsicoll_l")]]
[[alias("wcscasecmp_l", "_wcsicmp_l")]]
wcscasecoll_l(*) %{generate(str2wcs("strcasecoll_l"))}

@@>> wcsncasecoll_l(3)
[[wchar, dos_export_alias("_wcsnicoll_l")]]
[[alias("wcsncasecmp_l", "_wcsnicmp_l")]]
wcsncasecoll_l(*) %{generate(str2wcs("strncasecoll_l"))}

@@>> wcslwr_l(3)
[[wchar, dos_export_alias("_wcslwr_l")]]
wcslwr_l(*) %{generate(str2wcs("strlwr_l"))}

@@>> wcsupr_l(3)
[[wchar, dos_export_alias("_wcsupr_l")]]
wcsupr_l(*) %{generate(str2wcs("strupr_l"))}

@@>> wcsnlwr_l(3)
[[wchar]]
wcsnlwr_l(*) %{generate(str2wcs("strnlwr_l"))}

@@>> wcsnupr_l(3)
[[wchar]]
wcsnupr_l(*) %{generate(str2wcs("strnupr_l"))}

@@>> wcscasestr_l(3)
[[wchar]]
wcscasestr_l(*) %{generate(str2wcs("strcasestr_l"))}


@@>> fuzzy_wmemcasecmp_l(3)
[[wchar, pure, wunused]]
[[decl_include("<hybrid/typecore.h>")]]
$size_t fuzzy_wmemcasecmp_l([[in(s1_bytes)]] wchar_t const *s1, $size_t s1_bytes,
                            [[in(s2_bytes)]] wchar_t const *s2, $size_t s2_bytes,
                            $locale_t locale)
	%{generate(str2wcs("fuzzy_memcasecmp_l"))}

@@>> fuzzy_wcscasecmp_l(3)
[[wchar]]
fuzzy_wcscasecmp_l(*) %{generate(str2wcs("fuzzy_strcasecmp_l"))}

@@>> fuzzy_wcsncasecmp_l(3)
[[wchar]]
fuzzy_wcsncasecmp_l(*) %{generate(str2wcs("fuzzy_strncasecmp_l"))}

@@>> wildwcscasecmp_l(3)
[[wchar]]
wildwcscasecmp_l(*) %{generate(str2wcs("wildstrcasecmp_l"))}

%#endif /* __USE_XOPEN2K8 */
%#endif /* __USE_KOS */


%
%#ifdef __USE_BSD
@@>> fgetwln(3)
[[wchar, guard, wunused, decl_include("<hybrid/typecore.h>")]]
wchar_t *fgetwln([[inout]] FILE *__restrict fp,
                 [[out_opt]] $size_t *__restrict lenp);

@@>> wcslcat(3)
[[wchar, guard]]
wcslcat(*) %{generate(str2wcs("strlcat"))}

@@>> wcslcpy(3)
[[wchar, guard]]
wcslcpy(*) %{generate(str2wcs("strlcpy"))}
%#endif /* __USE_BSD */
















%
%
%
%

%#if defined(__USE_DOS) || defined(__USE_KOS)
@@>> wcsnset(3)
[[decl_include("<hybrid/typecore.h>")]]
[[guard, wchar, dos_export_alias("_wcsnset")]]
[[section(".text.crt.dos.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsnset([[inout(? <= maxlen)]] wchar_t *__restrict str,
                             wchar_t ch, $size_t maxlen)
	%{generate(str2wcs("strnset"))}

@@>> wcsrev(3)
[[decl_include("<hybrid/typecore.h>")]]
[[guard, wchar, dos_export_alias("_wcsrev")]]
[[section(".text.crt.dos.wchar.string.memory")]]
[[nonnull]] wchar_t *wcsrev([[inout]] wchar_t *__restrict str) {
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	return (wchar_t *)memrevw(str, wcslen(str));
@@pp_elif __SIZEOF_WCHAR_T__ == 4@@
	return (wchar_t *)memrevl(str, wcslen(str));
@@pp_else@@
	return (wchar_t *)memrev(str, wcslen(str) * sizeof(wchar_t));
@@pp_endif@@
}


@@>> wcsset(3)
[[guard, wchar, dos_export_alias("_wcsset")]]
[[section(".text.crt.dos.wchar.string.memory")]]
wcsset(*) %{generate(str2wcs("strset"))}

@@>> wcslwr(3)
[[guard, wchar, dos_export_alias("_wcslwr")]]
[[section(".text.crt.dos.wchar.unicode.static.memory")]]
wcslwr(*) %{generate(str2wcs("strlwr"))}

@@>> wcsupr(3)
[[guard, wchar, dos_export_alias("_wcsupr")]]
[[section(".text.crt.dos.wchar.unicode.static.memory")]]
wcsupr(*) %{generate(str2wcs("strupr"))}

%#endif /* __USE_DOS || __USE_KOS */

%{

__SYSDECL_END
#endif /* __CC__ */


#ifdef __USE_KOS
#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_WCHAR_FORMAT_PRINTER_H)
#include <parts/wchar/format-printer.h>
#endif /* _FORMAT_PRINTER_H && !_PARTS_WCHAR_FORMAT_PRINTER_H */

#if defined(_PROCESS_H) && !defined(_PARTS_WCHAR_PROCESS_H)
#include <parts/wchar/process.h>
#endif /* _PROCESS_H && !_PARTS_WCHAR_PROCESS_H */

#if defined(_UTIME_H) && !defined(_PARTS_WCHAR_UTIME_H)
#include <parts/wchar/utime.h>
#endif /* _UTIME_H && !_PARTS_WCHAR_UTIME_H */

#if defined(_UNISTD_H) && !defined(_PARTS_WCHAR_UNISTD_H)
#include <parts/wchar/unistd.h>
#endif /* _UNISTD_H && !_PARTS_WCHAR_UNISTD_H */

#if defined(_STDLIB_H) && !defined(_PARTS_WCHAR_STDLIB_H)
#include <parts/wchar/stdlib.h>
#endif /* _STDLIB_H && !_PARTS_WCHAR_STDLIB_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_WCHAR_H)
#include <parts/uchar/wchar.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_WCHAR_H */
#endif /* __USE_UTF */

#ifdef __USE_DOS
#include <corecrt_wconio.h>
#include <corecrt_wdirect.h>
#include <corecrt_wio.h>
#include <corecrt_wprocess.h>
#include <corecrt_wstdio.h>
#include <corecrt_wstdlib.h>
#include <corecrt_wstring.h>
#include <corecrt_wtime.h>
#ifndef __USE_DOS_CLEAN
#include <corecrt_memcpy_s.h> /* Include <string.h> instead */
#include <corecrt_wctype.h>   /* Include <wctype.h> instead */
#endif /* !__USE_DOS_CLEAN */
#endif /* __USE_DOS */

}
