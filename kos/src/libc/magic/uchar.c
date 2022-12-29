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
/* (>) Standard: ISO C11 (ISO/IEC 9899:2011) */
/* (#) Portability: DragonFly BSD (/include/uchar.h) */
/* (#) Portability: FreeBSD       (/include/uchar.h) */
/* (#) Portability: GNU C Library (/wcsmbs/uchar.h) */
/* (#) Portability: GNU Hurd      (/usr/include/uchar.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/uchar.h) */
/* (#) Portability: Windows Kits  (/ucrt/uchar.h) */
/* (#) Portability: libc6         (/include/uchar.h) */
/* (#) Portability: musl libc     (/include/uchar.h) */
/* (#) Portability: uClibc        (/include/uchar.h) */
}

%[define_ccompat_header("cuchar")]
%[define_replacement(locale_t = __locale_t)]
%[define_replacement(wint_t = __WINT_TYPE__)]
%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(mbstate_t = "struct __mbstate")]
%[default:section(".text.crt{|.dos}.unicode.mbr")]

%[define_decl_include("<bits/crt/mbstate.h>": ["struct __mbstate"])]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <bits/crt/mbstate.h>
)]%{


#ifdef __USE_KOS
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
#endif /* __USE_KOS */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined
__NAMESPACE_STD_BEGIN
typedef struct __mbstate mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c,ccompat){
#ifndef __mbstate_t_defined
#define __mbstate_t_defined
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */


/* Define `size_t' */
#ifndef __std_size_t_defined
#define __std_size_t_defined
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __char16_t_defined
#define __char16_t_defined
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

/* Libc uses utf16/utf32 to encode/decode char16_t and char32_t */
#define __STD_UTF_16__ 1
#define __STD_UTF_32__ 1

}

%[insert:std]

@@>> mbrtoc16(3)
[[std, no_crt, preferred_alias("mbrtoc16")]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("mbrtowc", "__mbrtowc")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$mbrtowc")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(mbrtowc)]]
[[exposed_name("mbrtoc16"), bind_local_function(uchar_mbrtoc16)]]
size_t stdc_mbrtoc16([[out_opt]] char16_t *pc16,
                     [[in_opt/*(maxlen)*/]] char const *__restrict str,
                     size_t maxlen, [[inout_opt]] mbstate_t *mbs);

@@>> mbrtoc32(3)
[[std, no_crt, preferred_alias("mbrtoc32")]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("mbrtowc", "__mbrtowc")]]
[[if(defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$mbrtowc")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(mbrtowc)]]
[[exposed_name("mbrtoc32"), bind_local_function(uchar_mbrtoc32)]]
size_t stdc_mbrtoc32([[out_opt]] char32_t *pc32,
                     [[in_opt/*(maxlen)*/]] char const *__restrict str,
                     size_t maxlen, [[inout_opt]] mbstate_t *mbs);

@@>> c16rtomb(3)
[[std, no_crt, preferred_alias("c16rtomb")]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), alias("wcrtomb")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wcrtomb")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 2), bind_local_function(wcrtomb)]]
[[exposed_name("c16rtomb"), bind_local_function(uchar_c16rtomb)]]
size_t stdc_c16rtomb([[out_opt]] char *__restrict str, char16_t c16,
                     [[inout_opt]] mbstate_t *mbs);

@@>> c32rtomb(3)
[[std, no_crt, preferred_alias("c32rtomb")]]
[[decl_include("<bits/crt/mbstate.h>", "<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), alias("wcrtomb")]]
[[if(defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wcrtomb")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_WCHAR_T__ == 4), bind_local_function(wcrtomb)]]
[[exposed_name("c32rtomb"), bind_local_function(uchar_c32rtomb)]]
size_t stdc_c32rtomb([[out_opt]] char *__restrict str, char32_t c32,
                     [[inout_opt]] mbstate_t *mbs);





/* The actual uchar-variants of these functions
 * These aren't exposed  because they'd be  using different  calling
 * conventions  for  individual bindings,  where-as  these functions
 * are actually exported from libc, using both LIBKCALL and LIBDCALL
 * calling conventions, meaning  they don't  impose the  requirement
 * of all of  the other  uchar-functions, in that  they require  the
 * caller  to deal  with the  possibility of  the calling convention
 * changing based on uchar character width.
 * NOTE: The actual requirement of different calling conventions
 *       is  the result from the fact that since libc is already
 *       implementing  DOS  compatibility, it  may as  well take
 *       advantage of  the fact  that DOS  uses 2-byte  wchar_t,
 *       while KOS uses 4-byte. So  with that in mind, libc  has
 *       to contain 2 versions  of every [[wchar]] function,  at
 *       which point it stands to reason to expose both.
 * However, since the 2-byte variants mainly exist to allow  for
 * DOS  compatibility, they obviously use the calling convention
 * required by DOS, meaning that when linking against them  from
 * KOS-mode, their declarations have  to reflect this (since  it
 * would be  too expensive  to have  4 variants  of every  wchar
 * function, for both wchar-sizes, and both calling conventions)
 *
 * The only  exception to  this rule  are these  four  functions,
 * which due the fact of being mandated by the C standard,  still
 * have to be  exported not only  by name, but  also be bound  to
 * in headers by-name, _and_ be exposed with a consistent calling
 * convention that matches `LIBCCALL'!
 */
[[ignore]] uchar_mbrtoc16(*) %{uchar16("mbrtowc")}
[[ignore]] uchar_mbrtoc32(*) %{uchar32("mbrtowc")}
[[ignore]] uchar_c16rtomb(*) %{uchar16("wcrtomb")}
[[ignore]] uchar_c32rtomb(*) %{uchar32("wcrtomb")}




%
%
%#ifdef __USE_KOS
%{
/* Simple functions to convert between single-byte and multi-byte  formats,
 * without having to worry about buffers (since all of these functions will
 * automatically allocate buffers on the heap) */

}

%[default:section(".text.crt{|.dos}.wchar.unicode.convert")]

[[requires_function(free)]]
void convert_freev(void *vector)
	[(/*utf-8*/ char **vector)]
	[(char16_t **vector)]
	[(char32_t **vector)]
{
	void **iter, *temp;
	if unlikely(!vector)
		return;
	for (iter = (void **)vector; (temp = *iter) != NULL; ++iter)
		free(temp);
	free(vector);
}

[[requires_function(free), decl_include("<hybrid/typecore.h>")]]
void convert_freevn(void *vector, $size_t count)
	[(/*utf-8*/ char **vector, $size_t count)]
	[(char16_t **vector, $size_t count)]
	[(char32_t **vector, $size_t count)]
{
	size_t i;
	if unlikely(!vector)
		return;
	for (i = 0; i < count; ++i)
		free(((void **)vector)[i]);
	free(vector);
}

[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(convert_wcstombsn), impl_include("<libc/errno.h>")]]
/*utf-8*/ char *convert_wcstombs([[in_opt]] $wchar_t const *str) {
	if unlikely(!str) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return NULL;
	}
	return convert_wcstombsn(str, wcslen(str), NULL);
}


[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(format_aprintf_printer, format_aprintf_pack)]]
[[impl_include("<libc/errno.h>", "<bits/crt/format-printer.h>")]]
/*utf-8*/ char *convert_wcstombsn([[in(len)]] $wchar_t const *__restrict str,
                                  $size_t len, [[out_opt]] $size_t *preslen) {
	struct __local_format_wto8_data {
		__pformatprinter fd_printer;   /* [1..1] Inner printer */
		void            *fd_arg;       /* Argument for `fd_printer' */
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
		char16_t         fd_surrogate; /* Pending high surrogate (or 0 if no surrogate is pending) */
@@pp_endif@@
	};
	struct __local_format_aprintf_data {
		char         *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ ap_used;  /* Used buffer size */
	};
	struct __local_format_aprintf_data printer_data = { NULL, 0, 0 };
	struct __local_format_wto8_data convert_data;
	convert_data.fd_printer   = &format_aprintf_printer;
	convert_data.fd_arg       = &printer_data;
@@pp_if __SIZEOF_WCHAR_T__ == 2@@
	convert_data.fd_surrogate = 0;
@@pp_endif@@
	if unlikely(format_wto8(&convert_data, str, len) < 0) {
@@pp_if $has_function(free)@@
		free(printer_data.ap_base);
@@pp_endif@@
		return NULL;
	}
	return format_aprintf_pack((struct @format_aprintf_data@ *)&printer_data, preslen);
}

[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(convert_wcstombsvn)]]
[[impl_include("<libc/errno.h>")]]
/*utf-8*/ char **convert_wcstombsv([[in_opt]] $wchar_t const *const *__restrict vector) {
	size_t count = 0;
	if unlikely(!vector) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return NULL;
	}
	for (count = 0; vector[count]; ++count)
		;
	return convert_wcstombsvn(vector, count);
}

[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(malloc, convert_wcstombs)]]
[[impl_include("<libc/errno.h>")]]
/*utf-8*/ char **convert_wcstombsvn([[in(count)]] $wchar_t const *const *__restrict vector, size_t count) {
	size_t i;
	char **result;
	result = (char **)malloc((count + 1) * sizeof(char *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			char *temp;
			temp = convert_wcstombs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
		result[i] = NULL;
	}
	return result;
err:
@@pp_if $has_function(free)@@
	while (i--)
		free(result[i]);
	free(result);
@@pp_endif@@
	return NULL;
}


[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(convert_mbstowcsn)]]
[[impl_include("<libc/errno.h>")]]
$wchar_t *convert_mbstowcs([[in_opt]] /*utf-8*/ char const *__restrict str) {
	if unlikely(!str) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return NULL;
	}
	return convert_mbstowcsn(str, strlen(str), NULL);
}

[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(format_waprintf_printer, format_waprintf_pack)]]
[[impl_include("<libc/errno.h>", "<bits/crt/wformat-printer.h>")]]
$wchar_t *convert_mbstowcsn([[in(len)]] /*utf-8*/ char const *__restrict str,
                            size_t len, [[out_opt]] size_t *preslen) {
	struct __local_format_waprintf_data {
		wchar_t      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
		__SIZE_TYPE__ ap_avail; /* Unused buffer size */
		__SIZE_TYPE__ ap_used;  /* Used buffer size */
	};
	struct __local_format_8tow_data {
		__pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		__UINT32_TYPE__   fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct __local_format_waprintf_data printer_data = { NULL, 0, 0 };
	struct __local_format_8tow_data convert_data;
	convert_data.fd_printer    = &format_waprintf_printer;
	convert_data.fd_arg        = &printer_data;
	convert_data.fd_incomplete = 0;
	if unlikely(format_8tow(&convert_data, str, len) < 0) {
@@pp_if $has_function(free)@@
		free(printer_data.ap_base);
@@pp_endif@@
		return NULL;
	}
	return format_waprintf_pack((struct format_waprintf_data *)&printer_data, preslen);
}


[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(convert_mbstowcsvn)]]
[[impl_include("<libc/errno.h>")]]
$wchar_t **convert_mbstowcsv([[in_opt]] /*utf-8*/ char const *const *__restrict vector) {
	size_t count = 0;
	if unlikely(!vector) {
@@pp_ifdef EINVAL@@
		(void)libc_seterrno(EINVAL);
@@pp_endif@@
		return NULL;
	}
	for (count = 0; vector[count]; ++count)
		;
	return convert_mbstowcsvn(vector, count);
}

[[wchar, ATTR_MALLOC, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_function(malloc, convert_mbstowcs)]]
[[impl_include("<libc/errno.h>")]]
$wchar_t **convert_mbstowcsvn([[in(count)]] /*utf-8*/ char const *const *__restrict vector, size_t count) {
	size_t i;
	$wchar_t **result;
	result = ($wchar_t **)malloc((count + 1) * sizeof($wchar_t *));
	if likely(result) {
		for (i = 0; i < count; ++i) {
			$wchar_t *temp;
			temp = convert_mbstowcs(vector[i]);
			if unlikely(!temp)
				goto err;
			result[i] = temp;
		}
		result[i] = NULL;
	}
	return result;
err:
@@pp_if $has_function(free)@@
	while (i--)
		free(result[i]);
	free(result);
@@pp_endif@@
	return NULL;
}


convert_c16tombs(*) %{uchar16("convert_wcstombs")}
convert_c32tombs(*) %{uchar32("convert_wcstombs")}
convert_c16tombsn(*) %{uchar16("convert_wcstombsn")}
convert_c32tombsn(*) %{uchar32("convert_wcstombsn")}
convert_c16tombsv(*) %{uchar16("convert_wcstombsv")}
convert_c32tombsv(*) %{uchar32("convert_wcstombsv")}
convert_c16tombsvn(*) %{uchar16("convert_wcstombsvn")}
convert_c32tombsvn(*) %{uchar32("convert_wcstombsvn")}
convert_mbstoc16(*) %{uchar16("convert_mbstowcs")}
convert_mbstoc32(*) %{uchar32("convert_mbstowcs")}
convert_mbstoc16n(*) %{uchar16("convert_mbstowcsn")}
convert_mbstoc32n(*) %{uchar32("convert_mbstowcsn")}
convert_mbstoc16v(*) %{uchar16("convert_mbstowcsv")}
convert_mbstoc32v(*) %{uchar32("convert_mbstowcsv")}
convert_mbstoc16vn(*) %{uchar16("convert_mbstowcsvn")}
convert_mbstoc32vn(*) %{uchar32("convert_mbstowcsvn")}

%#endif /* __USE_KOS */


%{

__SYSDECL_END
#endif /* __CC__ */


/* When  `#define _UTF_SOURCE' is  given, all  of KOS's  uchar variants are
 * exposed when both <uchar.h> and the header of origin have been included.
 *
 * For example:
 * >> #define _UTF_SOURCE
 * >> #include <string.h>  // Order of #includes doesn't matter; <string.h>
 * >> #include <uchar.h>   // also has a check if uchar was already included
 * >> // At this point, symbols `size_t c16slen(char16_t const *str)'
 * >> // have been defined (but be aware that calling conventions may
 * >> // not be identical between char16_t and char32_t variants of
 * >> // libc functions, and that utf-16 filesystem functions take
 * >> // DOS paths, rather than unix paths!)
 */
#ifdef __USE_UTF

#if defined(_CORECRT_WDIRECT_H) && !defined(_PARTS_UCHAR_DIRECT_H)
#include <parts/uchar/direct.h>
#endif /* _CORECRT_WDIRECT_H && !_PARTS_UCHAR_DIRECT_H */

#if defined(_FCNTL_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _FCNTL_H && !_PARTS_UCHAR_FCNTL_H */

#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_UCHAR_FORMATPRINTER_H)
#include <parts/uchar/format-printer.h>
#endif /* _FORMAT_PRINTER_H && !_PARTS_UCHAR_FORMATPRINTER_H */

#if defined(_INTTYPES_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _INTTYPES_H && !_PARTS_UCHAR_INTTYPES_H */

#if defined(_IO_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _IO_H && !_PARTS_UCHAR_IO_H */

#if defined(_PROCESS_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif /* _PROCESS_H && !_PARTS_UCHAR_PROCESS_H */

#if defined(_STDIO_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _STDIO_H && !_PARTS_UCHAR_STDIO_H */

#if defined(_STDLIB_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _STDLIB_H && !_PARTS_UCHAR_STDLIB_H */

#if defined(_STRING_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _STRING_H && !_PARTS_UCHAR_STRING_H */

#if defined(_SYS_MMAN_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif /* _SYS_MMAN_H && !_PARTS_UCHAR_SYS_MMAN_H */

#if defined(_SYS_STAT_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif /* _SYS_STAT_H && !_PARTS_UCHAR_SYS_STAT_H */

#if defined(_TIME_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _TIME_H && !_PARTS_UCHAR_TIME_H */

#if defined(_UNISTD_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif /* _UNISTD_H && !_PARTS_UCHAR_UNISTD_H */

#if defined(_UTIME_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif /* _UTIME_H && !_PARTS_UCHAR_UTIME_H */

#if defined(_WCHAR_H) && !defined(_PARTS_UCHAR_WCHAR_H)
#include <parts/uchar/wchar.h>
#endif /* _WCHAR_H && !_PARTS_UCHAR_WCHAR_H */

#if defined(_WCTYPE_H) && !defined(_PARTS_UCHAR_WCTYPE_H)
#include <parts/uchar/wctype.h>
#endif /* _WCTYPE_H && !_PARTS_UCHAR_WCTYPE_H */

#endif /* __USE_UTF */

}
