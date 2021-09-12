/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(wint16_t = __WINT16_TYPE__)]
%[define_replacement(wint32_t = __WINT32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{
#ifndef _WCTYPE_H
#include <wctype.h>
#endif /* !_WCTYPE_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wint16_t_defined
#define __wint16_t_defined
typedef __WINT16_TYPE__ wint16_t;
typedef __WINT32_TYPE__ wint32_t;
#endif /* !__wint16_t_defined */

}

isucntrl16(*) %{uchar16("iswcntrl")}
isucntrl32(*) %{uchar32("iswcntrl")}
isuspace16(*) %{uchar16("iswspace")}
isuspace32(*) %{uchar32("iswspace")}
isuupper16(*) %{uchar16("iswupper")}
isuupper32(*) %{uchar32("iswupper")}
isulower16(*) %{uchar16("iswlower")}
isulower32(*) %{uchar32("iswlower")}
isualpha16(*) %{uchar16("iswalpha")}
isualpha32(*) %{uchar32("iswalpha")}
isudigit16(*) %{uchar16("iswdigit")}
isudigit32(*) %{uchar32("iswdigit")}
isuxdigit16(*) %{uchar16("iswxdigit")}
isuxdigit32(*) %{uchar32("iswxdigit")}
isualnum16(*) %{uchar16("iswalnum")}
isualnum32(*) %{uchar32("iswalnum")}
isupunct16(*) %{uchar16("iswpunct")}
isupunct32(*) %{uchar32("iswpunct")}
isugraph16(*) %{uchar16("iswgraph")}
isugraph32(*) %{uchar32("iswgraph")}
isuprint16(*) %{uchar16("iswprint")}
isuprint32(*) %{uchar32("iswprint")}

toulower16(*) %{uchar16("towlower")}
toulower32(*) %{uchar32("towlower")}
touupper16(*) %{uchar16("towupper")}
touupper32(*) %{uchar32("towupper")}

%#ifdef __USE_ISOC99
isublank16(*) %{uchar16("iswblank")}
isublank32(*) %{uchar32("iswblank")}
touctrans16(*) %{uchar16("towctrans")}
touctrans32(*) %{uchar32("towctrans")}
%#endif /* __USE_ISOC99 */

isuctype16(*) %{uchar16("iswctype")}
isuctype32(*) %{uchar32("iswctype")}

%
%#if defined(__USE_KOS) || defined(__USE_DOS)
isuascii16(*) %{uchar16("iswascii")}
isuascii32(*) %{uchar32("iswascii")}
%#endif /* __USE_KOS || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
isucntrl16_l(*) %{uchar16("iswcntrl_l")}
isucntrl32_l(*) %{uchar32("iswcntrl_l")}
isuspace16_l(*) %{uchar16("iswspace_l")}
isuspace32_l(*) %{uchar32("iswspace_l")}
isuupper16_l(*) %{uchar16("iswupper_l")}
isuupper32_l(*) %{uchar32("iswupper_l")}
isulower16_l(*) %{uchar16("iswlower_l")}
isulower32_l(*) %{uchar32("iswlower_l")}
isualpha16_l(*) %{uchar16("iswalpha_l")}
isualpha32_l(*) %{uchar32("iswalpha_l")}
isudigit16_l(*) %{uchar16("iswdigit_l")}
isudigit32_l(*) %{uchar32("iswdigit_l")}
isuxdigit16_l(*) %{uchar16("iswxdigit_l")}
isuxdigit32_l(*) %{uchar32("iswxdigit_l")}
isualnum16_l(*) %{uchar16("iswalnum_l")}
isualnum32_l(*) %{uchar32("iswalnum_l")}
isupunct16_l(*) %{uchar16("iswpunct_l")}
isupunct32_l(*) %{uchar32("iswpunct_l")}
isugraph16_l(*) %{uchar16("iswgraph_l")}
isugraph32_l(*) %{uchar32("iswgraph_l")}
isuprint16_l(*) %{uchar16("iswprint_l")}
isuprint32_l(*) %{uchar32("iswprint_l")}
isublank16_l(*) %{uchar16("iswblank_l")}
isublank32_l(*) %{uchar32("iswblank_l")}
toulower16_l(*) %{uchar16("towlower_l")}
toulower32_l(*) %{uchar32("towlower_l")}
touupper16_l(*) %{uchar16("towupper_l")}
touupper32_l(*) %{uchar32("towupper_l")}
isuctype16_l(*) %{uchar16("iswctype_l")}
isuctype32_l(*) %{uchar32("iswctype_l")}
touctrans16_l(*) %{uchar16("towctrans_l")}
touctrans32_l(*) %{uchar32("towctrans_l")}
%#endif /* __USE_XOPEN2K8 */


%#ifdef __USE_DOS
__isucsymf16(*) %{uchar16("__iswcsymf")}
__isucsymf32(*) %{uchar32("__iswcsymf")}
__isucsym16(*) %{uchar16("__iswcsym")}
__isucsym32(*) %{uchar32("__iswcsym")}

_isucsymf16_l(*) %{uchar16("_iswcsymf_l")}
_isucsymf32_l(*) %{uchar32("_iswcsymf_l")}
_isucsym16_l(*) %{uchar16("_iswcsym_l")}
_isucsym32_l(*) %{uchar32("_iswcsym_l")}
%#endif /* __USE_DOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
