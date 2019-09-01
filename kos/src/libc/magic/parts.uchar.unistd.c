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

[attribute(*)] c16ttyname:(*) %{uchar(wttyname)}
[attribute(*)] c32ttyname:(*) %{uchar(wttyname)}
[attribute(*)] c16ttyname_r:(*) %{uchar(wttyname_r)}
[attribute(*)] c32ttyname_r:(*) %{uchar(wttyname_r)}
[attribute(*)] c16getlogin:(*) %{uchar(wgetlogin)}
[attribute(*)] c32getlogin:(*) %{uchar(wgetlogin)}
[attribute(*)] c16chown:(*) %{uchar(wchown)}
[attribute(*)] c32chown:(*) %{uchar(wchown)}
[attribute(*)] c16pathconf:(*) %{uchar(wpathconf)}
[attribute(*)] c32pathconf:(*) %{uchar(wpathconf)}
[attribute(*)] c16link:(*) %{uchar(wlink)}
[attribute(*)] c32link:(*) %{uchar(wlink)}
[attribute(*)] c16access:(*) %{uchar(waccess)}
[attribute(*)] c32access:(*) %{uchar(waccess)}
[attribute(*)] c16chdir:(*) %{uchar(wchdir)}
[attribute(*)] c32chdir:(*) %{uchar(wchdir)}
[attribute(*)] c16getcwd:(*) %{uchar(wgetcwd)}
[attribute(*)] c32getcwd:(*) %{uchar(wgetcwd)}
[attribute(*)] c16unlink:(*) %{uchar(wunlink)}
[attribute(*)] c32unlink:(*) %{uchar(wunlink)}
[attribute(*)] c16rmdir:(*) %{uchar(wrmdir)}
[attribute(*)] c32rmdir:(*) %{uchar(wrmdir)}

%#ifdef __USE_GNU
[attribute(*)] c16euidaccess:(*) %{uchar(weuidaccess)}
[attribute(*)] c32euidaccess:(*) %{uchar(weuidaccess)}
//TODO:This is broken:[attribute(*)][alias(*)] c16eaccess:(*) = c16euidaccess;
//TODO:This is broken:[attribute(*)][alias(*)] c32eaccess:(*) = c32euidaccess;
[attribute(*)] c16get_current_dir_name:(*) %{uchar(wget_current_dir_name)}
[attribute(*)] c32get_current_dir_name:(*) %{uchar(wget_current_dir_name)}
%#endif /* __USE_GNU */


%#ifdef __USE_ATFILE
[attribute(*)] c16faccessat:(*) %{uchar(wfaccessat)}
[attribute(*)] c32faccessat:(*) %{uchar(wfaccessat)}
[attribute(*)] c16fchownat:(*) %{uchar(wfchownat)}
[attribute(*)] c32fchownat:(*) %{uchar(wfchownat)}
[attribute(*)] c16linkat:(*) %{uchar(wlinkat)}
[attribute(*)] c32linkat:(*) %{uchar(wlinkat)}
[attribute(*)] c16symlinkat:(*) %{uchar(wsymlinkat)}
[attribute(*)] c32symlinkat:(*) %{uchar(wsymlinkat)}
[attribute(*)] c16readlinkat:(*) %{uchar(wreadlinkat)}
[attribute(*)] c32readlinkat:(*) %{uchar(wreadlinkat)}
%#ifdef __USE_KOS
[attribute(*)] c16freadlinkat:(*) %{uchar(wfreadlinkat)}
[attribute(*)] c32freadlinkat:(*) %{uchar(wfreadlinkat)}
%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */

[attribute(*)] c16lchown:(*) %{uchar(wlchown)}
[attribute(*)] c32lchown:(*) %{uchar(wlchown)}

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
%{
#ifndef __PIO_OFFSET
#ifdef __USE_KOS
#define __PIO_OFFSET     __FS_TYPE(pos)
#define __PIO_OFFSET64   __pos64_t
#else
#define __PIO_OFFSET     __FS_TYPE(off)
#define __PIO_OFFSET64   __off64_t
#endif
#endif /* !__PIO_OFFSET */
}

[if(defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 2), preferred_alias(wtruncate64)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(DOS$wtruncate64)]
[if(!defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 2), preferred_alias(wtruncate)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(DOS$wtruncate)]
[attribute(*)] c16truncate:(*) %{uchar(wtruncate)}

[if(defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 4), preferred_alias(wtruncate64)]
[if(!defined(__USE_FILE_OFFSET64) && __SIZEOF_WCHAR_T__ == 4), preferred_alias(wtruncate)]
[attribute(*)] c32truncate:(*) %{uchar(wtruncate)}


[ignore][attribute(*)] c16truncate32:(*) %{uchar16(wtruncate32)}
[ignore][attribute(*)] c32truncate32:(*) %{uchar32(wtruncate32)}

%#ifdef __USE_LARGEFILE64
[attribute(*)] c16truncate64:(*) %{uchar(wtruncate64)}
[attribute(*)] c32truncate64:(*) %{uchar(wtruncate64)}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[attribute(*)] c16symlink:(*) %{uchar(wsymlink)}
[attribute(*)] c32symlink:(*) %{uchar(wsymlink)}
[attribute(*)] c16readlink:(*) %{uchar(wreadlink)}
[attribute(*)] c32readlink:(*) %{uchar(wreadlink)}
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
[attribute(*)] c16getlogin_r:(*) %{uchar(wgetlogin_r)}
[attribute(*)] c32getlogin_r:(*) %{uchar(wgetlogin_r)}
%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
[attribute(*)] c16gethostname:(*) %{uchar(wgethostname)}
[attribute(*)] c32gethostname:(*) %{uchar(wgethostname)}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%#ifdef __USE_MISC
[attribute(*)] c16setlogin:(*) %{uchar(wsetlogin)}
[attribute(*)] c32setlogin:(*) %{uchar(wsetlogin)}
[attribute(*)] c16sethostname:(*) %{uchar(wsethostname)}
[attribute(*)] c32sethostname:(*) %{uchar(wsethostname)}
[attribute(*)] c16getdomainname:(*) %{uchar(wgetdomainname)}
[attribute(*)] c32getdomainname:(*) %{uchar(wgetdomainname)}
[attribute(*)] c16setdomainname:(*) %{uchar(wsetdomainname)}
[attribute(*)] c32setdomainname:(*) %{uchar(wsetdomainname)}
%#endif /* __USE_MISC */

%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
[attribute(*)] c16chroot:(*) %{uchar(wchroot)}
[attribute(*)] c32chroot:(*) %{uchar(wchroot)}
%#endif /* ... */

%
%#if defined(_ALL_SOURCE) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
[attribute(*)] c16ctermid:(*) %{uchar(wctermid)}
[attribute(*)] c32ctermid:(*) %{uchar(wctermid)}
%#endif /* _ALL_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */



%{

#endif /* __CC__ */

__SYSDECL_END

}

