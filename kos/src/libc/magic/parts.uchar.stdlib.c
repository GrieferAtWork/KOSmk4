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

c16stol(*) %{uchar("wcstol")}
c32stol(*) %{uchar("wcstol")}
c16stoul(*) %{uchar("wcstoul")}
c32stoul(*) %{uchar("wcstoul")}

c16stoll(*) %{uchar("wcstoll")}
c32stoll(*) %{uchar("wcstoll")}
c16stoull(*) %{uchar("wcstoull")}
c32stoull(*) %{uchar("wcstoull")}

%#ifndef __NO_FPU
c16stod(*) %{uchar("wcstod")}
c32stod(*) %{uchar("wcstod")}
%#ifdef __USE_ISOC99
c16stof(*) %{uchar("wcstof")}
c32stof(*) %{uchar("wcstof")}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
c16stold(*) %{uchar("wcstold")}
c32stold(*) %{uchar("wcstold")}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__USE_ISOC99 */
%#endif /* !__NO_FPU */


%
%#ifdef __USE_GNU
c16stoq(*) = c16stoll;
c32stoq(*) = c32stoll;
c16stouq(*) = c16stoull;
c32stouq(*) = c32stoull;
c16stol_l(*) %{uchar("wcstol_l")}
c32stol_l(*) %{uchar("wcstol_l")}
c16stoul_l(*) %{uchar("wcstoul_l")}
c32stoul_l(*) %{uchar("wcstoul_l")}
c16stoll_l(*) %{uchar("wcstoll_l")}
c32stoll_l(*) %{uchar("wcstoll_l")}
c16stoull_l(*) %{uchar("wcstoull_l")}
c32stoull_l(*) %{uchar("wcstoull_l")}

%#ifndef __NO_FPU
c16stof_l(*) %{uchar("wcstof_l")}
c32stof_l(*) %{uchar("wcstof_l")}
c16stod_l(*) %{uchar("wcstod_l")}
c32stod_l(*) %{uchar("wcstod_l")}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
c16stold_l(*) %{uchar("wcstold_l")}
c32stold_l(*) %{uchar("wcstold_l")}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */
%#endif /* __USE_GNU */


%
%#ifdef __USE_KOS
c16sto32(*) %{uchar16("wcsto32")}
c32sto32(*) %{uchar32("wcsto32")}
c16stou32(*) %{uchar16("wcstou32")}
c32stou32(*) %{uchar32("wcstou32")}
c16sto64(*) %{uchar16("wcsto64")}
c32sto64(*) %{uchar32("wcsto64")}
c16stou64(*) %{uchar16("wcstou64")}
c32stou64(*) %{uchar32("wcstou64")}

c16toi(*) %{uchar16("wtoi")}
c32toi(*) %{uchar32("wtoi")}
c16tol(*) %{uchar16("wtol")}
c32tol(*) %{uchar32("wtol")}
c16toll(*) %{uchar16("wtoll")}
c32toll(*) %{uchar32("wtoll")}
%#endif /* __USE_KOS */



%{

#endif /* __CC__ */

__SYSDECL_END

}

