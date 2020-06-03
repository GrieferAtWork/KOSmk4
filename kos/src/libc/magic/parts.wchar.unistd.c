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
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#ifndef _PARTS_WCHAR_PROCESS_H
#include <parts/wchar/process.h>
#endif /* !_PARTS_WCHAR_PROCESS_H */

__SYSDECL_BEGIN

#ifdef __CC__

}

[wchar][attribute(*)] wttyname:(*) %{copy(ttyname, str2wcs)}
[wchar][attribute(*)] wttyname_r:(*) %{copy(ttyname_r, str2wcs)}
[wchar][attribute(*)] wgetlogin:(*) %{copy(getlogin, str2wcs)}
[wchar][attribute(*)] wchown:(*) %{copy(chown, str2wcs)}
[wchar][attribute(*)] wpathconf:(*) %{copy(pathconf, str2wcs)}
[wchar][attribute(*)] wlink:(*) %{copy(link, str2wcs)}
[wchar][attribute(*)] waccess:(*) %{copy(access, str2wcs)}

[wchar][attribute(*)][dosname(_wchdir)] wchdir:(*) %{copy(chdir, str2wcs)}
[wchar][attribute(*)][dosname(_wgetcwd)] wgetcwd:(*) %{copy(getcwd, str2wcs)}
[wchar][attribute(*)][dosname(_wunlink)] wunlink:(*) %{copy(unlink, str2wcs)}
[wchar][attribute(*)][dosname(_wrmdir)] wrmdir:(*) %{copy(rmdir, str2wcs)}



%#ifdef __USE_GNU
[wchar][attribute(*)] weuidaccess:(*) %{copy(euidaccess, str2wcs)}
[wchar][attribute(*)] weaccess:(*) = weuidaccess;
[wchar][attribute(*)] wget_current_dir_name:(*) %{copy(get_current_dir_name, str2wcs)}
%#endif /* __USE_GNU */

%#ifdef __USE_ATFILE
[wchar][attribute(*)] wfaccessat:(*) %{copy(faccessat, str2wcs)}
[wchar][attribute(*)] wfchownat:(*) %{copy(fchownat, str2wcs)}
[wchar][attribute(*)] wlinkat:(*) %{copy(linkat, str2wcs)}
[wchar][attribute(*)] wsymlinkat:(*) %{copy(symlinkat, str2wcs)}
[wchar][attribute(*)] wreadlinkat:(*) %{copy(readlinkat, str2wcs)}
%#ifdef __USE_KOS
[wchar][attribute(*)] wfreadlinkat:(*) %{copy(freadlinkat, str2wcs)}
%#endif /* __USE_KOS */
[wchar][attribute(*)] wunlinkat:(*) %{copy(unlinkat, str2wcs)}
%#endif /* __USE_ATFILE */

[wchar][attribute(*)] wlchown:(*) %{copy(lchown, str2wcs)}

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

[[wchar, no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias(wtruncate64)]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(wtruncate)]]
wtruncate(*) %{copy(truncate, str2wcs)}

[[doc_alias(truncate), wchar, ignore, nocrt, alias(wtruncate)]]
int wtruncate32($wchar_t const *file, $pos32_t length);

%[define_str2wcs_replacement(truncate32 = wtruncate32)]


%#ifdef __USE_LARGEFILE64
[[wchar, off64_variant_of(wtruncate)]]
wtruncate64(*) %{generate(str2wcs(truncate64))}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[wchar][attribute(*)] wsymlink:(*) %{copy(symlink, str2wcs)}
[wchar][attribute(*)] wreadlink:(*) %{copy(readlink, str2wcs)}
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
[wchar][attribute(*)] wgetlogin_r:(*) %{copy(getlogin_r, str2wcs)}
%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
[wchar][attribute(*)] wgethostname:(*) %{copy(gethostname, str2wcs)}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%#ifdef __USE_MISC
[wchar][attribute(*)] wsetlogin:(*) %{copy(setlogin, str2wcs)}
[wchar][attribute(*)] wsethostname:(*) %{copy(sethostname, str2wcs)}
[wchar][attribute(*)] wgetdomainname:(*) %{copy(getdomainname, str2wcs)}
[wchar][attribute(*)] wsetdomainname:(*) %{copy(setdomainname, str2wcs)}
%#endif /* __USE_MISC */

%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
[wchar][attribute(*)] wchroot:(*) %{copy(chroot, str2wcs)}
%#endif /* ... */

%
%#if (defined(_EVERY_SOURCE) || \
%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
[wchar][attribute(*)] wctermid:(*) %{copy(ctermid, str2wcs)}
%#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */



%{

#endif /* __CC__ */

__SYSDECL_END

}

