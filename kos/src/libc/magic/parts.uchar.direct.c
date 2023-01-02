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
%[define_replacement(pid_t = __pid_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifndef _DIRECT_H
#include <direct.h>
#endif /* !_DIRECT_H */
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

%[insert:function(_c16getcwd = c16getcwd)]
%[insert:function(_c32getcwd = c32getcwd)]

_c16getdcwd(*) %{uchar16("_wgetdcwd")}
_c32getdcwd(*) %{uchar32("_wgetdcwd")}

%[insert:pp_if($has_function(_c16getdcwd))]
%#define _c16getdcwd_nolock _c16getdcwd
%[insert:pp_endif]
%[insert:pp_if($has_function(_c32getdcwd))]
%#define _c32getdcwd_nolock _c32getdcwd
%[insert:pp_endif]

%[insert:function(_c16chdir = c16chdir)]
%[insert:function(_c32chdir = c32chdir)]
%[insert:function(_c16rmdir = c16rmdir)]
%[insert:function(_c32rmdir = c32rmdir)]

_c16mkdir(*) %{uchar16("_wmkdir")}
_c32mkdir(*) %{uchar32("_wmkdir")}

%{

__SYSDECL_END
#endif /* __CC__ */

}
