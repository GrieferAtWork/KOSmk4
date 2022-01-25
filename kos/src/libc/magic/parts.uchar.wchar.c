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

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]
%[define_replacement(wint16_t = __WINT16_TYPE__)]
%[define_replacement(wint32_t = __WINT32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifndef WEOF16
#define WEOF16 __WEOF16
#define WEOF32 __WEOF32
#endif /* !WEOF16 */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __wint16_t_defined
#define __wint16_t_defined
typedef __WINT16_TYPE__ wint16_t;
typedef __WINT32_TYPE__ wint32_t;
#endif /* !__wint16_t_defined */

}

btoc16(*) %{uchar16("btowc")}
btoc32(*) %{uchar32("btowc")}

c16tob(*) %{uchar16("wctob")}
c32tob(*) %{uchar32("wctob")}

c16rlen(*) %{uchar16("mbrlen")}
c32rlen(*) %{uchar32("mbrlen")}

mbsrtoc16(*) %{uchar16("mbsrtowcs")}
mbsrtoc32(*) %{uchar32("mbsrtowcs")}

c16rtombs(*) %{uchar16("wcsrtombs")}
c32rtombs(*) %{uchar32("wcsrtombs")}

c16stol(*) %{uchar16("wcstol")}
c32stol(*) %{uchar32("wcstol")}
c16stoul(*) %{uchar16("wcstoul")}
c32stoul(*) %{uchar32("wcstoul")}

c16stoll(*) %{uchar16("wcstoll")}
c32stoll(*) %{uchar32("wcstoll")}
c16stoull(*) %{uchar16("wcstoull")}
c32stoull(*) %{uchar32("wcstoull")}

%#ifndef __NO_FPU
c16stod(*) %{uchar16("wcstod")}
c32stod(*) %{uchar32("wcstod")}
%#ifdef __USE_ISOC99
c16stof(*) %{uchar16("wcstof")}
c32stof(*) %{uchar32("wcstof")}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
c16stold(*) %{uchar16("wcstold")}
c32stold(*) %{uchar32("wcstold")}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__USE_ISOC99 */
%#endif /* !__NO_FPU */


%
%#ifdef __USE_GNU
%[insert:function(c16stoq = c16stoll)]
%[insert:function(c32stoq = c32stoll)]
%[insert:function(c16stouq = c16stoull)]
%[insert:function(c32stouq = c32stoull)]
c16stol_l(*) %{uchar16("wcstol_l")}
c32stol_l(*) %{uchar32("wcstol_l")}
c16stoul_l(*) %{uchar16("wcstoul_l")}
c32stoul_l(*) %{uchar32("wcstoul_l")}
c16stoll_l(*) %{uchar16("wcstoll_l")}
c32stoll_l(*) %{uchar32("wcstoll_l")}
c16stoull_l(*) %{uchar16("wcstoull_l")}
c32stoull_l(*) %{uchar32("wcstoull_l")}

%#ifndef __NO_FPU
c16stof_l(*) %{uchar16("wcstof_l")}
c32stof_l(*) %{uchar32("wcstof_l")}
c16stod_l(*) %{uchar16("wcstod_l")}
c32stod_l(*) %{uchar32("wcstod_l")}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
c16stold_l(*) %{uchar16("wcstold_l")}
c32stold_l(*) %{uchar32("wcstold_l")}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */
%#endif /* __USE_GNU */

%#ifdef __USE_XOPEN
c16width(*) %{uchar16("wcwidth")}
c32width(*) %{uchar32("wcwidth")}
%#endif /* __USE_XOPEN */

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
c16toll(*) %{uchar16("wtoll")}
c32toll(*) %{uchar32("wtoll")}
%#endif /* __USE_KOS */

%
%#ifdef __USE_BSD
fgetc16ln(*) %{uchar16("fgetwln")}
fgetc32ln(*) %{uchar32("fgetwln")}

c16lcat(*) %{uchar16("wcslcat")}
c32lcat(*) %{uchar32("wcslcat")}
c16lcpy(*) %{uchar16("wcslcpy")}
c32lcpy(*) %{uchar32("wcslcpy")}
%#endif /* __USE_BSD */


%{

__SYSDECL_END
#endif /* __CC__ */

}
