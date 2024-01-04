/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(char16_t = __CHAR16_TYPE__)]
%[define_replacement(char32_t = __CHAR32_TYPE__)]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _FCNTL_H
#include <fcntl.h>
#endif /* !_FCNTL_H */
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

c16open(*) %{uchar16("wopen")}
c32open(*) %{uchar32("wopen")}
c16creat(*) %{uchar16("wcreat")}
c32creat(*) %{uchar32("wcreat")}

%
%#ifdef __USE_LARGEFILE64
c16open64(*) %{uchar16("wopen64")}
c32open64(*) %{uchar32("wopen64")}
c16creat64(*) %{uchar16("wcreat64")}
c32creat64(*) %{uchar32("wcreat64")}
%#endif /* __USE_LARGEFILE64 */

%
%#ifdef __USE_ATFILE
c16openat(*) %{uchar16("wopenat")}
c32openat(*) %{uchar32("wopenat")}
%#ifdef __USE_LARGEFILE64
c16openat64(*) %{uchar16("wopenat64")}
c32openat64(*) %{uchar32("wopenat64")}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */

%{

__SYSDECL_END
#endif /* __CC__ */

}
