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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%{
#include <features.h>
#ifndef _INTTYPES_H
#include <inttypes.h>
#endif /* !_INTTYPES_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __CC__

}

[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstol)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoll,wcstoq)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 8),alias(wcsto64)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 4),alias(wcsto32)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(DOS$wcstol)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(DOS$wcstoll,DOS$wcstoq)]
[if(__SIZEOF_INTMAX_T__ == 8),alias(DOS$wcsto64)]
[if(__SIZEOF_INTMAX_T__ == 4),alias(DOS$wcsto32)]
[attribute(*)] c16toimax:(*) %{uchar(wcstoimax)}

[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstol)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoll,wcstoq)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 8),alias(wcsto64)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 4),alias(wcsto32)]
[attribute(*)] c32toimax:(*) %{uchar(wcstoimax)}

[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstoul)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoull,wcstouq)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 8),alias(wcstou64)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 4),alias(wcstou32)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(DOS$wcstoul)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(DOS$wcstoull,DOS$wcstouq)]
[if(__SIZEOF_INTMAX_T__ == 8),alias(DOS$wcstou64)]
[if(__SIZEOF_INTMAX_T__ == 4),alias(DOS$wcstou32)]
[attribute(*)] c16toumax:(*) %{uchar(wcstoumax)}

[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstoul)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoull,wcstouq)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 8),alias(wcstou64)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 4),alias(wcstou32)]
[attribute(*)] c32toumax:(*) %{uchar(wcstoumax)}


%#ifdef __USE_XOPEN2K8

[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstol_l,_wcstol_l)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoll_l,_wcstoll_l)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 8),alias(wcsto64_l,_wcstoi64_l)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 4),alias(wcsto32_l)]
[if(__SIZEOF_WCHAR_T__ == 2),alias(_wcstoimax_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(DOS$_wcstol_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(DOS$_wcstoll_l)]
[if(__SIZEOF_INTMAX_T__ == 8),alias(DOS$_wcstoi64_l)][alias(DOS$_wcstoimax_l)]
[attribute(*)] c16toimax_l:(*) %{uchar(wcstoimax_l)}

[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstol_l,_wcstol_l)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoll_l,_wcstoll_l)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 8),alias(wcsto64_l,_wcstoi64_l)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 4),alias(wcsto32_l)]
[if(__SIZEOF_WCHAR_T__ == 4),alias(_wcstoimax_l)]
[attribute(*)] c32toimax_l:(*) %{uchar(wcstoimax_l)}

[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstoul_l,_wcstoul_l)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoull_l,_wcstoull_l)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 8),alias(wcstou64_l,_wcstoui64_l)]
[if(__SIZEOF_WCHAR_T__ == 2 && __SIZEOF_INTMAX_T__ == 4),alias(wcstou32_l)]
[if(__SIZEOF_WCHAR_T__ == 2),alias(DOS$_wcstoumax_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(DOS$_wcstoul_l)]
[if(__SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(DOS$_wcstoull_l)]
[if(__SIZEOF_INTMAX_T__ == 8),alias(DOS$_wcstoui64_l)][alias(DOS$_wcstoumax_l)]
[attribute(*)] c16toumax_l:(*) %{uchar(wcstoumax_l)}

[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG__),alias(wcstoul_l,_wcstoul_l)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == __SIZEOF_LONG_LONG__),alias(wcstoull_l,_wcstoull_l)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 8),alias(wcstou64_l,_wcstoui64_l)]
[if(__SIZEOF_WCHAR_T__ == 4 && __SIZEOF_INTMAX_T__ == 4),alias(wcstou32_l)]
[if(__SIZEOF_WCHAR_T__ == 4),alias(_wcstoumax_l)]
[attribute(*)] c32toumax_l:(*) %{uchar(wcstoumax_l)}

%#endif /* __USE_XOPEN2K8 */


%{

#endif /* __CC__ */

__SYSDECL_END

}

