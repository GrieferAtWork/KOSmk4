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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

/************************************************************************/
/* WARNING: UTF-16 functions use DOS paths under `DOSFS_ENABLED'        */
/*          s.a. `dosfs_setenabled(3)'                                  */
/************************************************************************/

}

mbtoc16(*) %{uchar16("mbtowc")}
mbtoc32(*) %{uchar32("mbtowc")}
c16tomb(*) %{uchar16("wctomb")}
c32tomb(*) %{uchar32("wctomb")}
mbstoc16s(*) %{uchar16("mbstowcs")}
mbstoc32s(*) %{uchar32("mbstowcs")}
c16stombs(*) %{uchar16("wcstombs")}
c32stombs(*) %{uchar32("wcstombs")}


[[guard]] c16system(*) %{uchar16("wsystem")}
[[guard]] c32system(*) %{uchar32("wsystem")}

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
c16realpath(*) %{uchar16("wrealpath")}
c32realpath(*) %{uchar32("wrealpath")}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
c16frealpath(*) %{uchar16("wfrealpath")}
c32frealpath(*) %{uchar32("wfrealpath")}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

%
%#ifdef __USE_KOS
c16frealpath4(*) %{uchar16("wfrealpath4")}
c32frealpath4(*) %{uchar32("wfrealpath4")}
c16frealpathat(*) %{uchar16("wfrealpathat")}
c32frealpathat(*) %{uchar32("wfrealpathat")}
%#endif /* __USE_KOS */



%
%#ifdef __USE_KOS
c16sto32_r(*) %{uchar16("wcsto32_r")}
c32sto32_r(*) %{uchar32("wcsto32_r")}
c16stou32_r(*) %{uchar16("wcstou32_r")}
c32stou32_r(*) %{uchar32("wcstou32_r")}

c16sto32(*) %{uchar16("wcsto32")}
c32sto32(*) %{uchar32("wcsto32")}
c16stou32(*) %{uchar16("wcstou32")}
c32stou32(*) %{uchar32("wcstou32")}

%#ifdef __UINT64_TYPE__
c16sto64_r(*) %{uchar16("wcsto64_r")}
c32sto64_r(*) %{uchar32("wcsto64_r")}
c16stou64_r(*) %{uchar16("wcstou64_r")}
c32stou64_r(*) %{uchar32("wcstou64_r")}

c16sto64(*) %{uchar16("wcsto64")}
c32sto64(*) %{uchar32("wcsto64")}
c16stou64(*) %{uchar16("wcstou64")}
c32stou64(*) %{uchar32("wcstou64")}
%#endif /* __UINT64_TYPE__ */

c16stol_r(*) %{uchar16("wcstol_r")}
c32stol_r(*) %{uchar32("wcstol_r")}
c16stoul_r(*) %{uchar16("wcstoul_r")}
c32stoul_r(*) %{uchar32("wcstoul_r")}

%#ifdef __LONGLONG
c16stoll_r(*) %{uchar16("wcstoll_r")}
c32stoll_r(*) %{uchar32("wcstoll_r")}
c16stoull_r(*) %{uchar16("wcstoull_r")}
c32stoull_r(*) %{uchar32("wcstoull_r")}
%#endif /* __LONGLONG */

%
%#ifdef __USE_XOPEN2K8
c16sto32_l(*) %{uchar16("wcsto32_l")}
c32sto32_l(*) %{uchar32("wcsto32_l")}
c16stou32_l(*) %{uchar16("wcstou32_l")}
c32stou32_l(*) %{uchar32("wcstou32_l")}

%
%#ifdef __UINT64_TYPE__
c16sto64_l(*) %{uchar16("wcsto64_l")}
c32sto64_l(*) %{uchar32("wcsto64_l")}
c16stou64_l(*) %{uchar16("wcstou64_l")}
c32stou64_l(*) %{uchar32("wcstou64_l")}
%#endif /* __UINT64_TYPE__ */
%#endif /* __USE_XOPEN2K8 */

c16toi(*) %{uchar16("wtoi")}
c32toi(*) %{uchar32("wtoi")}
c16tol(*) %{uchar16("wtol")}
c32tol(*) %{uchar32("wtol")}
%#ifdef __LONGLONG
c16toll(*) %{uchar16("wtoll")}
c32toll(*) %{uchar32("wtoll")}
%#endif /* __LONGLONG */
%#endif /* __USE_KOS */




[[ignore]] __p___c16argv(*) %{uchar16("__p___wargv")}
[[ignore]] __p___c32argv(*) %{uchar32("__p___wargv")}
[[ignore]] __p__c16environ(*) %{uchar16("__p__wenviron")}
[[ignore]] __p__c32environ(*) %{uchar32("__p__wenviron")}
[[ignore]] __p__c16pgmptr(*) %{uchar16("__p__wpgmptr")}
[[ignore]] __p__c32pgmptr(*) %{uchar32("__p__wpgmptr")}

[[ignore]] _get_c16pgmptr(*) %{uchar16("_get_wpgmptr")}
[[ignore]] _get_c32pgmptr(*) %{uchar32("_get_wpgmptr")}

[[ignore]] _mbtoc16_l(*) %{uchar16("_mbtowc_l")}
[[ignore]] _mbtoc32_l(*) %{uchar32("_mbtowc_l")}
[[ignore]] _mbstoc16s_l(*) %{uchar16("_mbstowcs_l")}
[[ignore]] _mbstoc32s_l(*) %{uchar32("_mbstowcs_l")}
[[ignore]] _mbstoc16s_s(*) %{uchar16("_mbstowcs_s")}
[[ignore]] _mbstoc32s_s(*) %{uchar32("_mbstowcs_s")}
[[ignore]] _mbstoc16s_s_l(*) %{uchar16("_mbstowcs_s_l")}
[[ignore]] _mbstoc32s_s_l(*) %{uchar32("_mbstowcs_s_l")}

[[ignore]] c16tomb_s(*) %{uchar16("wctomb_s")}
[[ignore]] c32tomb_s(*) %{uchar32("wctomb_s")}
[[ignore]] _c16tomb_s_l(*) %{uchar16("_wctomb_s_l")}
[[ignore]] _c32tomb_s_l(*) %{uchar32("_wctomb_s_l")}
[[ignore]] _c16stombs_s_l(*) %{uchar16("_wcstombs_s_l")}
[[ignore]] _c32stombs_s_l(*) %{uchar32("_wcstombs_s_l")}
[[ignore]] _c16stombs_l(*) %{uchar16("_wcstombs_l")}
[[ignore]] _c32stombs_l(*) %{uchar32("_wcstombs_l")}
[[ignore]] c16stombs_s(*) %{uchar16("wcstombs_s")}
[[ignore]] c32stombs_s(*) %{uchar32("wcstombs_s")}

[[ignore]] _c16getenv(*) %{uchar16("_wgetenv")}
[[ignore]] _c32getenv(*) %{uchar32("_wgetenv")}
[[ignore]] _c16getenv_s(*) %{uchar16("_wgetenv_s")}
[[ignore]] _c32getenv_s(*) %{uchar32("_wgetenv_s")}
[[ignore]] _c16dupenv_s(*) %{uchar16("_wdupenv_s")}
[[ignore]] _c32dupenv_s(*) %{uchar32("_wdupenv_s")}
[[ignore]] _c16tof(*) %{uchar16("_wtof")}
[[ignore]] _c32tof(*) %{uchar32("_wtof")}
[[ignore]] _c16tof_l(*) %{uchar16("_wtof_l")}
[[ignore]] _c32tof_l(*) %{uchar32("_wtof_l")}

[[ignore]] _itoc16(*) %{uchar16("_itow")}
[[ignore]] _itoc32(*) %{uchar32("_itow")}
[[ignore]] _ltoc16(*) %{uchar16("_ltow")}
[[ignore]] _ltoc32(*) %{uchar32("_ltow")}
[[ignore]] _ultoc16(*) %{uchar16("_ultow")}
[[ignore]] _ultoc32(*) %{uchar32("_ultow")}
[[ignore]] _i64toc16(*) %{uchar16("_i64tow")}
[[ignore]] _i64toc32(*) %{uchar32("_i64tow")}
[[ignore]] _ui64toc16(*) %{uchar16("_ui64tow")}
[[ignore]] _ui64toc32(*) %{uchar32("_ui64tow")}
[[ignore]] _itoc16_s(*) %{uchar16("_itow_s")}
[[ignore]] _itoc32_s(*) %{uchar32("_itow_s")}
[[ignore]] _ltoc16_s(*) %{uchar16("_ltow_s")}
[[ignore]] _ltoc32_s(*) %{uchar32("_ltow_s")}
[[ignore]] _ultoc16_s(*) %{uchar16("_ultow_s")}
[[ignore]] _ultoc32_s(*) %{uchar32("_ultow_s")}
[[ignore]] _i64toc16_s(*) %{uchar16("_i64tow_s")}
[[ignore]] _i64toc32_s(*) %{uchar32("_i64tow_s")}
[[ignore]] _ui64toc16_s(*) %{uchar16("_ui64tow_s")}
[[ignore]] _ui64toc32_s(*) %{uchar32("_ui64tow_s")}
[[ignore]] _c16toi64(*) %{uchar16("_wtoi64")}
[[ignore]] _c32toi64(*) %{uchar32("_wtoi64")}
[[ignore]] _c16toi_l(*) %{uchar16("_wtoi_l")}
[[ignore]] _c32toi_l(*) %{uchar32("_wtoi_l")}
[[ignore]] _c16tol_l(*) %{uchar16("_wtol_l")}
[[ignore]] _c32tol_l(*) %{uchar32("_wtol_l")}
[[ignore]] _c16toi64_l(*) %{uchar16("_wtoi64_l")}
[[ignore]] _c32toi64_l(*) %{uchar32("_wtoi64_l")}
[[ignore]] _c16toll_l(*) %{uchar16("_wtoll_l")}
[[ignore]] _c32toll_l(*) %{uchar32("_wtoll_l")}

[[ignore]] _c16fullpath(*) %{uchar16("_wfullpath")}
[[ignore]] _c32fullpath(*) %{uchar32("_wfullpath")}
[[ignore]] _c16makepath_s(*) %{uchar16("_wmakepath_s")}
[[ignore]] _c32makepath_s(*) %{uchar32("_wmakepath_s")}
[[ignore]] _c16makepath(*) %{uchar16("_wmakepath")}
[[ignore]] _c32makepath(*) %{uchar32("_wmakepath")}
[[ignore]] _c16putenv(*) %{uchar16("_wputenv")}
[[ignore]] _c32putenv(*) %{uchar32("_wputenv")}
[[ignore]] _c16putenv_s(*) %{uchar16("_wputenv_s")}
[[ignore]] _c32putenv_s(*) %{uchar32("_wputenv_s")}
[[ignore]] _c16searchenv_s(*) %{uchar16("_wsearchenv_s")}
[[ignore]] _c32searchenv_s(*) %{uchar32("_wsearchenv_s")}
[[ignore]] _c16searchenv(*) %{uchar16("_wsearchenv")}
[[ignore]] _c32searchenv(*) %{uchar32("_wsearchenv")}
[[ignore]] _c16splitpath(*) %{uchar16("_wsplitpath")}
[[ignore]] _c32splitpath(*) %{uchar32("_wsplitpath")}
[[ignore]] _c16splitpath_s(*) %{uchar16("_wsplitpath_s")}
[[ignore]] _c32splitpath_s(*) %{uchar32("_wsplitpath_s")}

%{

__SYSDECL_END
#endif /* __CC__ */

}
