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

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

}

btoc16(*) %{uchar16("btowc")}
btoc32(*) %{uchar32("btowc")}

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
c16sto32(*) %{uchar16("wcsto32")}
c32sto32(*) %{uchar32("wcsto32")}
c16stou32(*) %{uchar16("wcstou32")}
c32stou32(*) %{uchar32("wcstou32")}

%#ifdef __UINT64_TYPE__
c16sto64(*) %{uchar16("wcsto64")}
c32sto64(*) %{uchar32("wcsto64")}
c16stou64(*) %{uchar16("wcstou64")}
c32stou64(*) %{uchar32("wcstou64")}
%#endif /* __UINT64_TYPE__ */

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


[[ignore]] _vscc16printf(*) %{uchar16("_vscwprintf")}
[[ignore]] _vscc32printf(*) %{uchar32("_vscwprintf")}
[[ignore]] _scc16printf(*) %{uchar16("_scwprintf")}
[[ignore]] _scc32printf(*) %{uchar32("_scwprintf")}
[[ignore]] _vscc16printf_p(*) %{uchar16("_vscwprintf_p")}
[[ignore]] _vscc32printf_p(*) %{uchar32("_vscwprintf_p")}
[[ignore]] _scc16printf_p(*) %{uchar16("_scwprintf_p")}
[[ignore]] _scc32printf_p(*) %{uchar32("_scwprintf_p")}
[[ignore]] _vscc16printf_l(*) %{uchar16("_vscwprintf_l")}
[[ignore]] _vscc32printf_l(*) %{uchar32("_vscwprintf_l")}
[[ignore]] _scc16printf_l(*) %{uchar16("_scwprintf_l")}
[[ignore]] _scc32printf_l(*) %{uchar32("_scwprintf_l")}
[[ignore]] _vscc16printf_p_l(*) %{uchar16("_vscwprintf_p_l")}
[[ignore]] _vscc32printf_p_l(*) %{uchar32("_vscwprintf_p_l")}
[[ignore]] _scc16printf_p_l(*) %{uchar16("_scwprintf_p_l")}
[[ignore]] _scc32printf_p_l(*) %{uchar32("_scwprintf_p_l")}
[[ignore]] _vsnc16printf_s(*) %{uchar16("_vsnwprintf_s")}
[[ignore]] _vsnc32printf_s(*) %{uchar32("_vsnwprintf_s")}
[[ignore]] _snc16printf_s(*) %{uchar16("_snwprintf_s")}
[[ignore]] _snc32printf_s(*) %{uchar32("_snwprintf_s")}
[[ignore]] _vfc16printf_p(*) %{uchar16("_vfwprintf_p")}
[[ignore]] _vfc32printf_p(*) %{uchar32("_vfwprintf_p")}
[[ignore]] _fc16printf_p(*) %{uchar16("_fwprintf_p")}
[[ignore]] _fc32printf_p(*) %{uchar32("_fwprintf_p")}
[[ignore]] _vc16printf_p(*) %{uchar16("_vwprintf_p")}
[[ignore]] _vc32printf_p(*) %{uchar32("_vwprintf_p")}
[[ignore]] _c16printf_p(*) %{uchar16("_wprintf_p")}
[[ignore]] _c32printf_p(*) %{uchar32("_wprintf_p")}
[[ignore]] _vsc16printf_p(*) %{uchar16("_vswprintf_p")}
[[ignore]] _vsc32printf_p(*) %{uchar32("_vswprintf_p")}
[[ignore]] _sc16printf_p(*) %{uchar16("_swprintf_p")}
[[ignore]] _sc32printf_p(*) %{uchar32("_swprintf_p")}
[[ignore]] _vc16printf_l(*) %{uchar16("_vwprintf_l")}
[[ignore]] _vc32printf_l(*) %{uchar32("_vwprintf_l")}
[[ignore]] _c16printf_l(*) %{uchar16("_wprintf_l")}
[[ignore]] _c32printf_l(*) %{uchar32("_wprintf_l")}
[[ignore]] _vc16printf_p_l(*) %{uchar16("_vwprintf_p_l")}
[[ignore]] _vc32printf_p_l(*) %{uchar32("_vwprintf_p_l")}
[[ignore]] _c16printf_p_l(*) %{uchar16("_wprintf_p_l")}
[[ignore]] _c32printf_p_l(*) %{uchar32("_wprintf_p_l")}
[[ignore]] _vc16printf_s_l(*) %{uchar16("_vwprintf_s_l")}
[[ignore]] _vc32printf_s_l(*) %{uchar32("_vwprintf_s_l")}
[[ignore]] _c16printf_s_l(*) %{uchar16("_wprintf_s_l")}
[[ignore]] _c32printf_s_l(*) %{uchar32("_wprintf_s_l")}
[[ignore]] _vfc16printf_l(*) %{uchar16("_vfwprintf_l")}
[[ignore]] _vfc32printf_l(*) %{uchar32("_vfwprintf_l")}
[[ignore]] _fc16printf_l(*) %{uchar16("_fwprintf_l")}
[[ignore]] _fc32printf_l(*) %{uchar32("_fwprintf_l")}
[[ignore]] _vfc16printf_p_l(*) %{uchar16("_vfwprintf_p_l")}
[[ignore]] _vfc32printf_p_l(*) %{uchar32("_vfwprintf_p_l")}
[[ignore]] _fc16printf_p_l(*) %{uchar16("_fwprintf_p_l")}
[[ignore]] _fc32printf_p_l(*) %{uchar32("_fwprintf_p_l")}
[[ignore]] _vfc16printf_s_l(*) %{uchar16("_vfwprintf_s_l")}
[[ignore]] _vfc32printf_s_l(*) %{uchar32("_vfwprintf_s_l")}
[[ignore]] _fc16printf_s_l(*) %{uchar16("_fwprintf_s_l")}
[[ignore]] _fc32printf_s_l(*) %{uchar32("_fwprintf_s_l")}
[[ignore]] _vsc16printf_c_l(*) %{uchar16("_vswprintf_c_l")}
[[ignore]] _vsc32printf_c_l(*) %{uchar32("_vswprintf_c_l")}
[[ignore]] _sc16printf_c_l(*) %{uchar16("_swprintf_c_l")}
[[ignore]] _sc32printf_c_l(*) %{uchar32("_swprintf_c_l")}
[[ignore]] _vsc16printf_p_l(*) %{uchar16("_vswprintf_p_l")}
[[ignore]] _vsc32printf_p_l(*) %{uchar32("_vswprintf_p_l")}
[[ignore]] _sc16printf_p_l(*) %{uchar16("_swprintf_p_l")}
[[ignore]] _sc32printf_p_l(*) %{uchar32("_swprintf_p_l")}
[[ignore]] _vsc16printf_s_l(*) %{uchar16("_vswprintf_s_l")}
[[ignore]] _vsc32printf_s_l(*) %{uchar32("_vswprintf_s_l")}
[[ignore]] _sc16printf_s_l(*) %{uchar16("_swprintf_s_l")}
[[ignore]] _sc32printf_s_l(*) %{uchar32("_swprintf_s_l")}
[[ignore]] _vsnc16printf_l(*) %{uchar16("_vsnwprintf_l")}
[[ignore]] _vsnc32printf_l(*) %{uchar32("_vsnwprintf_l")}
[[ignore]] _snc16printf_l(*) %{uchar16("_snwprintf_l")}
[[ignore]] _snc32printf_l(*) %{uchar32("_snwprintf_l")}
[[ignore]] _vsnc16printf_s_l(*) %{uchar16("_vsnwprintf_s_l")}
[[ignore]] _vsnc32printf_s_l(*) %{uchar32("_vsnwprintf_s_l")}
[[ignore]] _snc16printf_s_l(*) %{uchar16("_snwprintf_s_l")}
[[ignore]] _snc32printf_s_l(*) %{uchar32("_snwprintf_s_l")}
[[ignore]] _vfc16scanf_l(*) %{uchar16("_vfwscanf_l")}
[[ignore]] _vfc32scanf_l(*) %{uchar32("_vfwscanf_l")}
[[ignore]] _fc16scanf_l(*) %{uchar16("_fwscanf_l")}
[[ignore]] _fc32scanf_l(*) %{uchar32("_fwscanf_l")}
[[ignore]] _vsc16scanf_l(*) %{uchar16("_vswscanf_l")}
[[ignore]] _vsc32scanf_l(*) %{uchar32("_vswscanf_l")}
[[ignore]] _sc16scanf_l(*) %{uchar16("_swscanf_l")}
[[ignore]] _sc32scanf_l(*) %{uchar32("_swscanf_l")}
[[ignore]] _vsnc16scanf(*) %{uchar16("_vsnwscanf")}
[[ignore]] _vsnc32scanf(*) %{uchar32("_vsnwscanf")}
[[ignore]] _snc16scanf(*) %{uchar16("_snwscanf")}
[[ignore]] _snc32scanf(*) %{uchar32("_snwscanf")}
[[ignore]] _vsnc16scanf_l(*) %{uchar16("_vsnwscanf_l")}
[[ignore]] _vsnc32scanf_l(*) %{uchar32("_vsnwscanf_l")}
[[ignore]] _snc16scanf_l(*) %{uchar16("_snwscanf_l")}
[[ignore]] _snc32scanf_l(*) %{uchar32("_snwscanf_l")}
[[ignore]] _vsnc16scanf_s_l(*) %{uchar16("_vsnwscanf_s_l")}
[[ignore]] _vsnc32scanf_s_l(*) %{uchar32("_vsnwscanf_s_l")}
[[ignore]] _snc16scanf_s_l(*) %{uchar16("_snwscanf_s_l")}
[[ignore]] _snc32scanf_s_l(*) %{uchar32("_snwscanf_s_l")}
[[ignore]] _vc16scanf_l(*) %{uchar16("_vwscanf_l")}
[[ignore]] _vc32scanf_l(*) %{uchar32("_vwscanf_l")}
[[ignore]] _c16scanf_l(*) %{uchar16("_wscanf_l")}
[[ignore]] _c32scanf_l(*) %{uchar32("_wscanf_l")}


[[ignore]] _c16fsopen(*) %{uchar16("_wfsopen")}
[[ignore]] _c32fsopen(*) %{uchar32("_wfsopen")}
[[ignore]] _c16fdopen(*) %{uchar16("_wfdopen")}
[[ignore]] _c32fdopen(*) %{uchar32("_wfdopen")}
[[ignore]] _c16fopen_s(*) %{uchar16("_wfopen_s")}
[[ignore]] _c32fopen_s(*) %{uchar32("_wfopen_s")}
[[ignore]] _c16freopen_s(*) %{uchar16("_wfreopen_s")}
[[ignore]] _c32freopen_s(*) %{uchar32("_wfreopen_s")}

[[ignore]] _getc16s_s(*) %{uchar16("_getws_s")}
[[ignore]] _getc32s_s(*) %{uchar32("_getws_s")}
[[ignore]] _putc16s(*) %{uchar16("_putws")}
[[ignore]] _putc32s(*) %{uchar32("_putws")}
[[ignore]] _c16tempnam(*) %{uchar16("_wtempnam")}
[[ignore]] _c32tempnam(*) %{uchar32("_wtempnam")}
[[ignore]] _c16tmpnam_s(*) %{uchar16("_wtmpnam_s")}
[[ignore]] _c32tmpnam_s(*) %{uchar32("_wtmpnam_s")}



%{

__SYSDECL_END
#endif /* __CC__ */

}
