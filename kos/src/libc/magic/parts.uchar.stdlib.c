/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

__SYSDECL_BEGIN

#ifdef __CC__

}

[alias(*)][attribute(*)] c16stol:(*) %{uchar(wcstol)}
[alias(*)][attribute(*)] c32stol:(*) %{uchar(wcstol)}
[alias(*)][attribute(*)] c16stoul:(*) %{uchar(wcstoul)}
[alias(*)][attribute(*)] c32stoul:(*) %{uchar(wcstoul)}

[alias(*)][attribute(*)] c16stoll:(*) %{uchar(wcstoll)}
[alias(*)][attribute(*)] c32stoll:(*) %{uchar(wcstoll)}
[alias(*)][attribute(*)] c16stoull:(*) %{uchar(wcstoull)}
[alias(*)][attribute(*)] c32stoull:(*) %{uchar(wcstoull)}

%#ifndef __NO_FPU
[alias(*)][attribute(*)] c16stod:(*) %{uchar(wcstod)}
[alias(*)][attribute(*)] c32stod:(*) %{uchar(wcstod)}
%#ifdef __USE_ISOC99
[alias(*)][attribute(*)] c16stof:(*) %{uchar(wcstof)}
[alias(*)][attribute(*)] c32stof:(*) %{uchar(wcstof)}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[alias(*)][attribute(*)] c16stold:(*) %{uchar(wcstold)}
[alias(*)][attribute(*)] c32stold:(*) %{uchar(wcstold)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__USE_ISOC99 */
%#endif /* !__NO_FPU */


%
%#ifdef __USE_GNU
[alias(*)][attribute(*)] c16stoq:(*) %{uchar(wcstoq)}
[alias(*)][attribute(*)] c32stoq:(*) %{uchar(wcstoq)}
[alias(*)][attribute(*)] c16stouq:(*) %{uchar(wcstouq)}
[alias(*)][attribute(*)] c32stouq:(*) %{uchar(wcstouq)}
[alias(*)][attribute(*)] c16stol_l:(*) %{uchar(wcstol_l)}
[alias(*)][attribute(*)] c32stol_l:(*) %{uchar(wcstol_l)}
[alias(*)][attribute(*)] c16stoul_l:(*) %{uchar(wcstoul_l)}
[alias(*)][attribute(*)] c32stoul_l:(*) %{uchar(wcstoul_l)}
[alias(*)][attribute(*)] c16stoll_l:(*) %{uchar(wcstoll_l)}
[alias(*)][attribute(*)] c32stoll_l:(*) %{uchar(wcstoll_l)}
[alias(*)][attribute(*)] c16stoull_l:(*) %{uchar(wcstoull_l)}
[alias(*)][attribute(*)] c32stoull_l:(*) %{uchar(wcstoull_l)}

%#ifndef __NO_FPU
[alias(*)][attribute(*)] c16stof_l:(*) %{uchar(wcstof_l)}
[alias(*)][attribute(*)] c32stof_l:(*) %{uchar(wcstof_l)}
[alias(*)][attribute(*)] c16stod_l:(*) %{uchar(wcstod_l)}
[alias(*)][attribute(*)] c32stod_l:(*) %{uchar(wcstod_l)}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[alias(*)][attribute(*)] c16stold_l:(*) %{uchar(wcstold_l)}
[alias(*)][attribute(*)] c32stold_l:(*) %{uchar(wcstold_l)}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* !__NO_FPU */
%#endif /* __USE_GNU */


%
%#ifdef __USE_KOS
[attribute(*)] c16sto32:(*) %{uchar16(wcsto32)}
[attribute(*)] c32sto32:(*) %{uchar32(wcsto32)}
[attribute(*)] c16stou32:(*) %{uchar16(wcstou32)}
[attribute(*)] c32stou32:(*) %{uchar32(wcstou32)}
[attribute(*)] c16sto64:(*) %{uchar16(wcsto64)}
[attribute(*)] c32sto64:(*) %{uchar32(wcsto64)}
[attribute(*)] c16stou64:(*) %{uchar16(wcstou64)}
[attribute(*)] c32stou64:(*) %{uchar32(wcstou64)}
%#endif /* __USE_KOS */



%{

#endif /* __CC__ */

__SYSDECL_END

}

