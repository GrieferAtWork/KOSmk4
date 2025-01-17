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
#ifndef _UNISTD_H
#include <unistd.h>
#endif /* !_UNISTD_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */
#ifndef _PARTS_UCHAR_PROCESS_H
#include <parts/uchar/process.h>
#endif /* !_PARTS_UCHAR_PROCESS_H */

#ifdef __CC__
__SYSDECL_BEGIN

/************************************************************************/
/* WARNING: UTF-16 functions use DOS paths under `DOSFS_ENABLED'        */
/*          s.a. `dosfs_setenabled(3)'                                  */
/************************************************************************/

}

c16ttyname(*) %{uchar16("wttyname")}
c32ttyname(*) %{uchar32("wttyname")}
c16ttyname_r(*) %{uchar16("wttyname_r")}
c32ttyname_r(*) %{uchar32("wttyname_r")}
//c16getlogin(*) %{uchar16("wgetlogin")}
//c32getlogin(*) %{uchar32("wgetlogin")}
c16chown(*) %{uchar16("wchown")}
c32chown(*) %{uchar32("wchown")}
c16pathconf(*) %{uchar16("wpathconf")}
c32pathconf(*) %{uchar32("wpathconf")}
c16link(*) %{uchar16("wlink")}
c32link(*) %{uchar32("wlink")}
c16access(*) %{uchar16("waccess")}
c32access(*) %{uchar32("waccess")}
c16chdir(*) %{uchar16("wchdir")}
c32chdir(*) %{uchar32("wchdir")}
c16getcwd(*) %{uchar16("wgetcwd")}
c32getcwd(*) %{uchar32("wgetcwd")}
c16unlink(*) %{uchar16("wunlink")}
c32unlink(*) %{uchar32("wunlink")}
c16rmdir(*) %{uchar16("wrmdir")}
c32rmdir(*) %{uchar32("wrmdir")}

%#ifdef __USE_GNU
c16euidaccess(*) %{uchar16("weuidaccess")}
c32euidaccess(*) %{uchar32("weuidaccess")}
c16eaccess(*) = c16euidaccess;
c32eaccess(*) = c32euidaccess;
c16get_current_dir_name(*) %{uchar16("wget_current_dir_name")}
c32get_current_dir_name(*) %{uchar32("wget_current_dir_name")}
%#endif /* __USE_GNU */


%#ifdef __USE_ATFILE
c16faccessat(*) %{uchar16("wfaccessat")}
c32faccessat(*) %{uchar32("wfaccessat")}
c16fchownat(*) %{uchar16("wfchownat")}
c32fchownat(*) %{uchar32("wfchownat")}
c16linkat(*) %{uchar16("wlinkat")}
c32linkat(*) %{uchar32("wlinkat")}
c16symlinkat(*) %{uchar16("wsymlinkat")}
c32symlinkat(*) %{uchar32("wsymlinkat")}
c16readlinkat(*) %{uchar16("wreadlinkat")}
c32readlinkat(*) %{uchar32("wreadlinkat")}
%#ifdef __USE_KOS
c16fsymlinkat(*) %{uchar16("wfsymlinkat")}
c32fsymlinkat(*) %{uchar32("wfsymlinkat")}
c16freadlinkat(*) %{uchar16("wfreadlinkat")}
c32freadlinkat(*) %{uchar32("wfreadlinkat")}
%#endif /* __USE_KOS */
c16unlinkat(*) %{uchar16("wunlinkat")}
c32unlinkat(*) %{uchar32("wunlinkat")}
%#endif /* __USE_ATFILE */

c16lchown(*) %{uchar16("wlchown")}
c32lchown(*) %{uchar32("wlchown")}

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
%{
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
}

c16truncate(*) %{uchar16("wtruncate")}
c32truncate(*) %{uchar32("wtruncate")}

%#ifdef __USE_LARGEFILE64
c16truncate64(*) %{uchar16("wtruncate64")}
c32truncate64(*) %{uchar32("wtruncate64")}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
c16symlink(*) %{uchar16("wsymlink")}
c32symlink(*) %{uchar32("wsymlink")}
c16readlink(*) %{uchar16("wreadlink")}
c32readlink(*) %{uchar32("wreadlink")}
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

//%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
//c16getlogin_r(*) %{uchar16("wgetlogin_r")}
//c32getlogin_r(*)         %{uchar32("wgetlogin_r")}
//%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
c16gethostname(*) %{uchar16("wgethostname")}
c32gethostname(*) %{uchar32("wgethostname")}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%#ifdef __USE_MISC
c16setlogin(*) %{uchar16("wsetlogin")}
c32setlogin(*) %{uchar32("wsetlogin")}
c16sethostname(*) %{uchar16("wsethostname")}
c32sethostname(*) %{uchar32("wsethostname")}
c16getdomainname(*) %{uchar16("wgetdomainname")}
c32getdomainname(*) %{uchar32("wgetdomainname")}
c16setdomainname(*) %{uchar16("wsetdomainname")}
c32setdomainname(*) %{uchar32("wsetdomainname")}
%#endif /* __USE_MISC */

%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
c16chroot(*) %{uchar16("wchroot")}
c32chroot(*) %{uchar32("wchroot")}
%#endif /* ... */

//%
//%#if (defined(_EVERY_SOURCE) || \
//%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
//c16ctermid(*) %{uchar16("wctermid")}
//c32ctermid(*) %{uchar32("wctermid")}
//%#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */



%{

__SYSDECL_END
#endif /* __CC__ */

}
