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

iscntrl16(*) %{uchar16("iswcntrl")}
iscntrl32(*) %{uchar32("iswcntrl")}
isspace16(*) %{uchar16("iswspace")}
isspace32(*) %{uchar32("iswspace")}
isupper16(*) %{uchar16("iswupper")}
isupper32(*) %{uchar32("iswupper")}
islower16(*) %{uchar16("iswlower")}
islower32(*) %{uchar32("iswlower")}
isalpha16(*) %{uchar16("iswalpha")}
isalpha32(*) %{uchar32("iswalpha")}
isdigit16(*) %{uchar16("iswdigit")}
isdigit32(*) %{uchar32("iswdigit")}
isxdigit16(*) %{uchar16("iswxdigit")}
isxdigit32(*) %{uchar32("iswxdigit")}
isalnum16(*) %{uchar16("iswalnum")}
isalnum32(*) %{uchar32("iswalnum")}
ispunct16(*) %{uchar16("iswpunct")}
ispunct32(*) %{uchar32("iswpunct")}
isgraph16(*) %{uchar16("iswgraph")}
isgraph32(*) %{uchar32("iswgraph")}
isprint16(*) %{uchar16("iswprint")}
isprint32(*) %{uchar32("iswprint")}

tolower16(*) %{uchar16("towlower")}
tolower32(*) %{uchar32("towlower")}
toupper16(*) %{uchar16("towupper")}
toupper32(*) %{uchar32("towupper")}

%#ifdef __USE_ISOC99
isblank16(*) %{uchar16("iswblank")}
isblank32(*) %{uchar32("iswblank")}
toctrans16(*) %{uchar16("towctrans")}
toctrans32(*) %{uchar32("towctrans")}
%#endif /* __USE_ISOC99 */

isctype16(*) %{uchar16("iswctype")}
isctype32(*) %{uchar32("iswctype")}

%
%#if defined(__USE_KOS) || defined(__USE_DOS)
isascii16(*) %{uchar16("iswascii")}
isascii32(*) %{uchar32("iswascii")}
%#endif /* __USE_KOS || __USE_DOS */


%
%#ifdef __USE_XOPEN2K8
iscntrl16_l(*) %{uchar16("iswcntrl_l")}
iscntrl32_l(*) %{uchar32("iswcntrl_l")}
isspace16_l(*) %{uchar16("iswspace_l")}
isspace32_l(*) %{uchar32("iswspace_l")}
isupper16_l(*) %{uchar16("iswupper_l")}
isupper32_l(*) %{uchar32("iswupper_l")}
islower16_l(*) %{uchar16("iswlower_l")}
islower32_l(*) %{uchar32("iswlower_l")}
isalpha16_l(*) %{uchar16("iswalpha_l")}
isalpha32_l(*) %{uchar32("iswalpha_l")}
isdigit16_l(*) %{uchar16("iswdigit_l")}
isdigit32_l(*) %{uchar32("iswdigit_l")}
isxdigit16_l(*) %{uchar16("iswxdigit_l")}
isxdigit32_l(*) %{uchar32("iswxdigit_l")}
isalnum16_l(*) %{uchar16("iswalnum_l")}
isalnum32_l(*) %{uchar32("iswalnum_l")}
ispunct16_l(*) %{uchar16("iswpunct_l")}
ispunct32_l(*) %{uchar32("iswpunct_l")}
isgraph16_l(*) %{uchar16("iswgraph_l")}
isgraph32_l(*) %{uchar32("iswgraph_l")}
isprint16_l(*) %{uchar16("iswprint_l")}
isprint32_l(*) %{uchar32("iswprint_l")}
isblank16_l(*) %{uchar16("iswblank_l")}
isblank32_l(*) %{uchar32("iswblank_l")}
tolower16_l(*) %{uchar16("towlower_l")}
tolower32_l(*) %{uchar32("towlower_l")}
toupper16_l(*) %{uchar16("towupper_l")}
toupper32_l(*) %{uchar32("towupper_l")}
isctype16_l(*) %{uchar16("iswctype_l")}
isctype32_l(*) %{uchar32("iswctype_l")}
toctrans16_l(*) %{uchar16("towctrans_l")}
toctrans32_l(*) %{uchar32("towctrans_l")}
%#endif /* __USE_XOPEN2K8 */


%#ifdef __USE_KOS
issymstrt16(*) %{uchar16("iswsymstrt")}
issymstrt32(*) %{uchar32("iswsymstrt")}
issymcont16(*) %{uchar16("iswsymcont")}
issymcont32(*) %{uchar32("iswsymcont")}

issymstrt16_l(*) %{uchar16("iswsymstrt_l")}
issymstrt32_l(*) %{uchar32("iswsymstrt_l")}
issymcont16_l(*) %{uchar16("iswsymcont_l")}
issymcont32_l(*) %{uchar32("iswsymcont_l")}
%#endif /* __USE_KOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
