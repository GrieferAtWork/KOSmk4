/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (>) Standard: ISO C11 (ISO/IEC 9899:2011) */
/* (#) Portability: FreeBSD       (/include/uchar.h) */
/* (#) Portability: GNU C Library (/wcsmbs/uchar.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/uchar.h) */
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

%[declare_known_section(".text.crt{|.dos}.wchar.unicode.convert")]
%[declare_known_section(".text.crt.dos.wchar.unicode.convert")]


%{
#include <features.h>
#include <hybrid/typecore.h>
#include <bits/crt/mbstate.h>

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __std_mbstate_t_defined
#define __std_mbstate_t_defined 1
__NAMESPACE_STD_BEGIN
typedef struct __mbstate mbstate_t;
__NAMESPACE_STD_END
#endif /* !__std_mbstate_t_defined */

#ifndef __CXX_SYSTEM_HEADER
}%(c,ccompat){
#ifndef __mbstate_t_defined
#define __mbstate_t_defined 1
__NAMESPACE_STD_USING(mbstate_t)
#endif /* !__mbstate_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */


/* Define `size_t' */
#ifndef __std_size_t_defined
#define __std_size_t_defined 1
__NAMESPACE_STD_BEGIN
typedef __SIZE_TYPE__ size_t;
__NAMESPACE_STD_END
#endif /* !__std_size_t_defined */
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifndef __size_t_defined
#define __size_t_defined 1
__NAMESPACE_STD_USING(size_t)
#endif /* !__size_t_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __char16_t_defined
#define __char16_t_defined 1
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

/* Libc uses utf16/utf32 to encode/decode char16_t and char32_t */
#define __STD_UTF_16__ 1
#define __STD_UTF_32__ 1

}

%[insert:std]

[[std, no_crt, preferred_alias("mbrtoc16")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("mbrtowc", "__mbrtowc")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$mbrtowc")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(mbrtowc)]]
[[exposed_name("mbrtoc16"), bind_local_function(uchar_mbrtoc16)]]
[[decl_include("<bits/crt/mbstate.h>")]]
size_t stdc_mbrtoc16([[nullable]] char16_t *pc16,
                     [[inp_opt(maxlen)]] char const *__restrict str,
                     size_t maxlen, [[nullable]] mbstate_t *mbs);

[[std, no_crt, preferred_alias("mbrtoc32")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("mbrtowc", "__mbrtowc")]]
[[if(defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$mbrtowc")]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(mbrtowc)]]
[[exposed_name("mbrtoc32"), bind_local_function(uchar_mbrtoc32)]]
[[decl_include("<bits/crt/mbstate.h>")]]
size_t stdc_mbrtoc32([[nullable]] char32_t *pc32,
                     [[inp_opt(maxlen)]] char const *__restrict str,
                     size_t maxlen, [[nullable]] mbstate_t *mbs);

[[std, no_crt, preferred_alias("c16rtomb")]]
[[if(__SIZEOF_WCHAR_T__ == 2), alias("wcrtomb")]]
[[if(defined(__LIBCCALL_IS_LIBDCALL)), alias("DOS$wcrtomb")]]
[[if(__SIZEOF_WCHAR_T__ == 2), bind_local_function(wcrtomb)]]
[[exposed_name("c16rtomb"), bind_local_function(uchar_c16rtomb)]]
[[decl_include("<bits/crt/mbstate.h>")]]
size_t stdc_c16rtomb(char *__restrict str, char16_t c16,
                     [[nullable]] mbstate_t *mbs);

[[std, no_crt, preferred_alias("c32rtomb")]]
[[if(__SIZEOF_WCHAR_T__ == 4), alias("wcrtomb")]]
[[if(defined(__PE__) && defined(__LIBCCALL_IS_LIBKCALL)), alias("KOS$wcrtomb")]]
[[if(__SIZEOF_WCHAR_T__ == 4), bind_local_function(wcrtomb)]]
[[exposed_name("c32rtomb"), bind_local_function(uchar_c32rtomb)]]
[[decl_include("<bits/crt/mbstate.h>")]]
size_t stdc_c32rtomb(char *__restrict str, char32_t c32,
                     [[nullable]] mbstate_t *mbs);





/* The actual uchar-variants of these functions
 * These aren't exposed because they'd be using different calling
 * conventions for individual bindings, where-as these functions
 * are actually exported from libc, using both LIBKCALL and LIBDCALL
 * calling conventions, meaning they don't impose the requirement
 * of all of the other uchar-functions, in that they require the
 * caller to deal with the possibility of the calling convention
 * changing based on uchar character width.
 * NOTE: The actual requirement of different calling conventions
 *       is the result from the fact that since libc is already
 *       implementing DOS compatibility, it may as well take
 *       advantage of the fact that DOS uses 2-byte wchar_t,
 *       while KOS uses 4-byte. So with that in mind, libc has
 *       to contain 2 versions of every [[wchar]] function, at
 *       which point it stands to reason to expose both.
 * However, since the 2-byte variants mainly exist to allow for
 * DOS compatibility, they obviously use the calling convention
 * required by DOS, meaning that when linking against them from
 * KOS-mode, their declarations have to reflect this (since it
 * would be too expensive to have 4 variants of every wchar
 * function, for both wchar-sizes, and both calling conventions)
 *
 * The only exception to this rule are these four functions,
 * which due the fact of being mandated by the C standard, still
 * have to be exported not only by name, but also by be bound to
 * in headers by-name, _and_ be exposed with a consistent calling
 * convention that matches `LIBCCALL'!
 */
[[ignore]] uchar_mbrtoc16(*) %{uchar16("mbrtowc")}
[[ignore]] uchar_mbrtoc32(*) %{uchar32("mbrtowc")}
[[ignore]] uchar_c16rtomb(*) %{uchar16("wcrtomb")}
[[ignore]] uchar_c32rtomb(*) %{uchar32("wcrtomb")}


%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_STRING_H) && !defined(_PARTS_UCHAR_STRING_H)
#include <parts/uchar/string.h>
#endif /* _STRING_H && !_PARTS_UCHAR_STRING_H */

#if defined(_PROCESS_H) && !defined(_PARTS_UCHAR_PROCESS_H)
#include <parts/uchar/process.h>
#endif /* _PROCESS_H && !_PARTS_UCHAR_PROCESS_H */

#if defined(_STDLIB_H) && !defined(_PARTS_UCHAR_STDLIB_H)
#include <parts/uchar/stdlib.h>
#endif /* _STDLIB_H && !_PARTS_UCHAR_STDLIB_H */

#if defined(_FCNTL_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _FCNTL_H && !_PARTS_UCHAR_FCNTL_H */

#if defined(_UNISTD_H) && !defined(_PARTS_UCHAR_UNISTD_H)
#include <parts/uchar/unistd.h>
#endif /* _UNISTD_H && !_PARTS_UCHAR_UNISTD_H */

#if defined(_UTIME_H) && !defined(_PARTS_UCHAR_UTIME_H)
#include <parts/uchar/utime.h>
#endif /* _UTIME_H && !_PARTS_UCHAR_UTIME_H */

#if defined(_FORMAT_PRINTER_H) && !defined(_PARTS_UCHAR_FORMATPRINTER_H)
#include <parts/uchar/format-printer.h>
#endif /* _FORMAT_PRINTER_H && !_PARTS_UCHAR_FORMATPRINTER_H */

#if defined(_IO_H) && !defined(_PARTS_UCHAR_IO_H)
#include <parts/uchar/io.h>
#endif /* _IO_H && !_PARTS_UCHAR_IO_H */

#if defined(_STDIO_H) && !defined(_PARTS_UCHAR_STDIO_H)
#include <parts/uchar/stdio.h>
#endif /* _STDIO_H && !_PARTS_UCHAR_STDIO_H */

#if defined(_TIME_H) && !defined(_PARTS_UCHAR_TIME_H)
#include <parts/uchar/time.h>
#endif /* _TIME_H && !_PARTS_UCHAR_TIME_H */

#if defined(_SYS_STAT_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif /* _SYS_STAT_H && !_PARTS_UCHAR_SYS_STAT_H */

#if defined(_SYS_MMAN_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif /* _SYS_MMAN_H && !_PARTS_UCHAR_SYS_MMAN_H */

#if defined(_INTTYPES_H) && !defined(_PARTS_UCHAR_INTTYPES_H)
#include <parts/uchar/inttypes.h>
#endif /* _INTTYPES_H && !_PARTS_UCHAR_INTTYPES_H */

#if defined(_WCHAR_H) && !defined(_PARTS_UCHAR_WCHAR_H)
#include <parts/uchar/wchar.h>
#endif /* _WCHAR_H && !_PARTS_UCHAR_WCHAR_H */
#endif /* __USE_UTF */

}

