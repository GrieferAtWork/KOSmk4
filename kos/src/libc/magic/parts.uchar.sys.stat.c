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
#ifndef _SYS_STAT_H
#include <sys/stat.h>
#endif /* !_SYS_STAT_H */
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

c16mkdir(*) %{uchar16("wmkdir")}
c32mkdir(*) %{uchar32("wmkdir")}
c16chmod(*) %{uchar16("wchmod")}
c32chmod(*) %{uchar32("wchmod")}

%
%#ifdef __USE_MISC
c16lchmod(*) %{uchar16("wlchmod")}
c32lchmod(*) %{uchar32("wlchmod")}
%#endif /* __USE_MISC */


%
%#if defined(__USE_KOS) && defined(__USE_ATFILE)
c16fmkdirat(*) %{uchar16("wfmkdirat")}
c32fmkdirat(*) %{uchar32("wfmkdirat")}
c16fmknodat(*) %{uchar16("wfmknodat")}
c32fmknodat(*) %{uchar32("wfmknodat")}
%#endif /* __USE_KOS && __USE_ATFILE */

c16mkfifo(*) %{uchar16("wmkfifo")}
c32mkfifo(*) %{uchar32("wmkfifo")}

%
%#ifdef __USE_ATFILE
c16fchmodat(*) %{uchar16("wfchmodat")}
c32fchmodat(*) %{uchar32("wfchmodat")}
c16mkdirat(*) %{uchar16("wmkdirat")}
c32mkdirat(*) %{uchar32("wmkdirat")}
c16mkfifoat(*) %{uchar16("wmkfifoat")}
c32mkfifoat(*) %{uchar32("wmkfifoat")}
%#endif /* __USE_ATFILE */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
c16mknod(*) %{uchar16("wmknod")}
c32mknod(*) %{uchar32("wmknod")}

%#ifdef __USE_ATFILE
c16mknodat(*) %{uchar16("wmknodat")}
c32mknodat(*) %{uchar32("wmknodat")}
%#endif /* __USE_ATFILE */
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#ifdef __USE_ATFILE
c16utimensat(*) %{uchar16("wutimensat")}
c32utimensat(*) %{uchar32("wutimensat")}

%#ifdef __USE_TIME64
c16utimensat64(*) %{uchar16("wutimensat64")}
c32utimensat64(*) %{uchar32("wutimensat64")}
%#endif /* __USE_TIME64 */
%#endif /* __USE_ATFILE */

%{

__SYSDECL_END
#endif /* __CC__ */

}
