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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%{
#include <features.h>
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

}

mbtoc16(*) %{uchar16("mbtowc")}
mbtoc32(*) %{uchar32("mbtowc")}
c16tomb(*) %{uchar16("wctomb")}
c32tomb(*) %{uchar32("wctomb")}
mbstoc16s(*) %{uchar16("mbstowcs")}
mbstoc32s(*) %{uchar32("mbstowcs")}
c16stombs(*) %{uchar16("wcstombs")}
c32stombs(*) %{uchar32("wcstombs")}


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

#endif /* __CC__ */

__SYSDECL_END

}

