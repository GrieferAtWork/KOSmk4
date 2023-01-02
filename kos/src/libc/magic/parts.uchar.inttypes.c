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
#ifndef _INTTYPES_H
#include <inttypes.h>
#endif /* !_INTTYPES_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

c16stoimax:(*) %{uchar16("wcstoimax")}
c32stoimax:(*) %{uchar32("wcstoimax")}
c16stoumax:(*) %{uchar16("wcstoumax")}
c32stoumax:(*) %{uchar32("wcstoumax")}

%
%#ifdef __USE_XOPEN2K8
c16stoimax_l:(*) %{uchar16("wcstoimax_l")}
c32stoimax_l:(*) %{uchar32("wcstoimax_l")}
c16stoumax_l:(*) %{uchar16("wcstoumax_l")}
c32stoumax_l:(*) %{uchar32("wcstoumax_l")}
%#endif /* __USE_XOPEN2K8 */

%
%#ifdef __USE_KOS
/************************************************************************/
/* WARNING: The following functions aren't exported by-name from libc!  */
/************************************************************************/
c16stoimax_r:(*) %{uchar16("wcstoimax_r")}
c32stoimax_r:(*) %{uchar32("wcstoimax_r")}
c16stoumax_r:(*) %{uchar16("wcstoumax_r")}
c32stoumax_r:(*) %{uchar32("wcstoumax_r")}
/************************************************************************/
%#endif /* __USE_KOS */


%{

__SYSDECL_END
#endif /* __CC__ */

}
