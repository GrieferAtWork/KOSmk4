/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _TIME_H
#include <time.h>
#endif /* !_TIME_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

}

c16ftime(*) %{uchar16("wcsftime")}
c32ftime(*) %{uchar32("wcsftime")}

%
%#ifdef __USE_GNU
c16ftime_l(*) %{uchar16("wcsftime_l")}
c32ftime_l(*) %{uchar32("wcsftime_l")}
%#endif /* __USE_GNU */

%
%#ifdef __USE_DOS
_c16asctime(*) %{uchar16("_wasctime")}
_c32asctime(*) %{uchar32("_wasctime")}
_c16asctime_s(*) %{uchar16("_wasctime_s")}
_c32asctime_s(*) %{uchar32("_wasctime_s")}
_c16ctime32(*) %{uchar16("_wctime32")}
_c32ctime32(*) %{uchar32("_wctime32")}
_c16ctime64(*) %{uchar16("_wctime64")}
_c32ctime64(*) %{uchar32("_wctime64")}
_c16ctime32_s(*) %{uchar16("_wctime32_s")}
_c32ctime32_s(*) %{uchar32("_wctime32_s")}
_c16ctime64_s(*) %{uchar16("_wctime64_s")}
_c32ctime64_s(*) %{uchar32("_wctime64_s")}
_c16strtime(*) %{uchar16("_wstrtime")}
_c32strtime(*) %{uchar32("_wstrtime")}
_c16strtime_s(*) %{uchar16("_wstrtime_s")}
_c32strtime_s(*) %{uchar32("_wstrtime_s")}
_c16strdate(*) %{uchar16("_wstrdate")}
_c32strdate(*) %{uchar32("_wstrdate")}
_c16strdate_s(*) %{uchar16("_wstrdate_s")}
_c32strdate_s(*) %{uchar32("_wstrdate_s")}


%
%
%{
#ifdef __USE_TIME_BITS64
#define _c16ctime   _c16ctime64
#define _c32ctime   _c32ctime64
#define _c16ctime_s _c16ctime64_s
#define _c32ctime_s _c32ctime64_s
#else /* __USE_TIME_BITS64 */
#define _c16ctime   _c16ctime32
#define _c32ctime   _c32ctime32
#define _c16ctime_s _c16ctime32_s
#define _c32ctime_s _c32ctime32_s
#endif /* !__USE_TIME_BITS64 */
}

%#endif /* __USE_DOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
