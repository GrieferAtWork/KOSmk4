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
#ifndef _UNISTD_H
#include <unistd.h>
#endif /* !_UNISTD_H */
#ifndef _UCHAR_H
#include <uchar.h>
#endif /* !_UCHAR_H */
#ifndef _PARTS_UCHAR_PROCESS_H
#include <parts/uchar/process.h>
#endif /* !_PARTS_UCHAR_PROCESS_H */

__SYSDECL_BEGIN

#ifdef __CC__

}

c16ttyname:(*) %{uchar(wttyname)}
c32ttyname:(*) %{uchar(wttyname)}
c16ttyname_r:(*) %{uchar(wttyname_r)}
c32ttyname_r:(*) %{uchar(wttyname_r)}
c16getlogin:(*) %{uchar(wgetlogin)}
c32getlogin:(*) %{uchar(wgetlogin)}
c16chown:(*) %{uchar(wchown)}
c32chown:(*) %{uchar(wchown)}
c16pathconf:(*) %{uchar(wpathconf)}
c32pathconf:(*) %{uchar(wpathconf)}
c16link:(*) %{uchar(wlink)}
c32link:(*) %{uchar(wlink)}
c16access:(*) %{uchar(waccess)}
c32access:(*) %{uchar(waccess)}
c16chdir:(*) %{uchar(wchdir)}
c32chdir:(*) %{uchar(wchdir)}
c16getcwd:(*) %{uchar(wgetcwd)}
c32getcwd:(*) %{uchar(wgetcwd)}
c16unlink:(*) %{uchar(wunlink)}
c32unlink:(*) %{uchar(wunlink)}
c16rmdir:(*) %{uchar(wrmdir)}
c32rmdir:(*) %{uchar(wrmdir)}

%#ifdef __USE_GNU
c16euidaccess:(*) %{uchar(weuidaccess)}
c32euidaccess:(*) %{uchar(weuidaccess)}
c16eaccess:(*) = c16euidaccess;
c32eaccess:(*) = c32euidaccess;
c16get_current_dir_name:(*) %{uchar(wget_current_dir_name)}
c32get_current_dir_name:(*) %{uchar(wget_current_dir_name)}
%#endif /* __USE_GNU */


%#ifdef __USE_ATFILE
c16faccessat:(*) %{uchar(wfaccessat)}
c32faccessat:(*) %{uchar(wfaccessat)}
c16fchownat:(*) %{uchar(wfchownat)}
c32fchownat:(*) %{uchar(wfchownat)}
c16linkat:(*) %{uchar(wlinkat)}
c32linkat:(*) %{uchar(wlinkat)}
c16symlinkat:(*) %{uchar(wsymlinkat)}
c32symlinkat:(*) %{uchar(wsymlinkat)}
c16readlinkat:(*) %{uchar(wreadlinkat)}
c32readlinkat:(*) %{uchar(wreadlinkat)}
%#ifdef __USE_KOS
c16freadlinkat:(*) %{uchar(wfreadlinkat)}
c32freadlinkat:(*) %{uchar(wfreadlinkat)}
%#endif /* __USE_KOS */
c16unlinkat:(*) %{uchar(wunlinkat)}
c32unlinkat:(*) %{uchar(wunlinkat)}
%#endif /* __USE_ATFILE */

c16lchown:(*) %{uchar(wlchown)}
c32lchown:(*) %{uchar(wlchown)}

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
%{
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else /* __USE_KOS */
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif /* !__USE_KOS */
#endif /* !__PIO_OFFSET */
}

c16truncate:(*) %{uchar(wtruncate)}
c32truncate:(*) %{uchar(wtruncate)}

[[ignore]] c16truncate32:(*) %{uchar16(wtruncate32)}
[[ignore]] c32truncate32:(*) %{uchar32(wtruncate32)}

%#ifdef __USE_LARGEFILE64
c16truncate64:(*) %{uchar(wtruncate64)}
c32truncate64:(*) %{uchar(wtruncate64)}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
c16symlink:(*) %{uchar(wsymlink)}
c32symlink:(*) %{uchar(wsymlink)}
c16readlink:(*) %{uchar(wreadlink)}
c32readlink:(*) %{uchar(wreadlink)}
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
c16getlogin_r:(*) %{uchar(wgetlogin_r)}
c32getlogin_r:(*) %{uchar(wgetlogin_r)}
%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
c16gethostname:(*) %{uchar(wgethostname)}
c32gethostname:(*) %{uchar(wgethostname)}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%#ifdef __USE_MISC
c16setlogin:(*) %{uchar(wsetlogin)}
c32setlogin:(*) %{uchar(wsetlogin)}
c16sethostname:(*) %{uchar(wsethostname)}
c32sethostname:(*) %{uchar(wsethostname)}
c16getdomainname:(*) %{uchar(wgetdomainname)}
c32getdomainname:(*) %{uchar(wgetdomainname)}
c16setdomainname:(*) %{uchar(wsetdomainname)}
c32setdomainname:(*) %{uchar(wsetdomainname)}
%#endif /* __USE_MISC */

%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
c16chroot:(*) %{uchar(wchroot)}
c32chroot:(*) %{uchar(wchroot)}
%#endif /* ... */

%
%#if (defined(_EVERY_SOURCE) || \
%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
c16ctermid:(*) %{uchar(wctermid)}
c32ctermid:(*) %{uchar(wctermid)}
%#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */



%{

#endif /* __CC__ */

__SYSDECL_END

}

