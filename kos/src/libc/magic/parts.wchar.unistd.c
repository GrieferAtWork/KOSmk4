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

[[wchar]] wttyname(*) %{generate(str2wcs("ttyname"))}
[[wchar]] wttyname_r(*) %{generate(str2wcs("ttyname_r"))}
[[wchar]] wgetlogin(*) %{generate(str2wcs("getlogin"))}
[[wchar]] wchown(*) %{generate(str2wcs("chown"))}
[[wchar]] wpathconf(*) %{generate(str2wcs("pathconf"))}
[[wchar]] wlink(*) %{generate(str2wcs("link"))}
[[wchar]] waccess(*) %{generate(str2wcs("access"))}

[[wchar, crt_dosname("_wchdir")]] wchdir(*) %{generate(str2wcs("chdir"))}
[[wchar, crt_dosname("_wgetcwd")]] wgetcwd(*) %{generate(str2wcs("getcwd"))}
[[wchar, crt_dosname("_wunlink")]] wunlink(*) %{generate(str2wcs("unlink"))}
[[wchar, crt_dosname("_wrmdir")]] wrmdir(*) %{generate(str2wcs("rmdir"))}



%#ifdef __USE_GNU
[[wchar]] weuidaccess:(*) %{generate(str2wcs("euidaccess"))}
weaccess(*) = weuidaccess;
[[wchar]] wget_current_dir_name:(*) %{generate(str2wcs("get_current_dir_name"))}
%#endif /* __USE_GNU */

%#ifdef __USE_ATFILE
[[wchar]] wfaccessat:(*) %{generate(str2wcs("faccessat"))}
[[wchar]] wfchownat:(*) %{generate(str2wcs("fchownat"))}
[[wchar]] wlinkat:(*) %{generate(str2wcs("linkat"))}
[[wchar]] wsymlinkat:(*) %{generate(str2wcs("symlinkat"))}
[[wchar]] wreadlinkat:(*) %{generate(str2wcs("readlinkat"))}
%#ifdef __USE_KOS
[[wchar]] wfreadlinkat:(*) %{generate(str2wcs("freadlinkat"))}
%#endif /* __USE_KOS */
[[wchar]] wunlinkat:(*) %{generate(str2wcs("unlinkat"))}
%#endif /* __USE_ATFILE */

[[wchar]] wlchown:(*) %{generate(str2wcs("lchown"))}

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
wtruncate(*) %{generate(str2wcs("truncate"))}

[[doc_alias(truncate), wchar, ignore, nocrt, alias(wtruncate)]]
int wtruncate32($wchar_t const *file, $pos32_t length);

%[define_str2wcs_replacement(truncate32 = wtruncate32)]


%#ifdef __USE_LARGEFILE64
[[wchar, off64_variant_of(wtruncate)]]
wtruncate64(*) %{generate(str2wcs(truncate64))}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[wchar]] wsymlink:(*) %{generate(str2wcs("symlink"))}
[[wchar]] wreadlink:(*) %{generate(str2wcs("readlink"))}
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

%
%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
[[wchar]] wgetlogin_r:(*) %{generate(str2wcs("getlogin_r"))}
%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
[[wchar]] wgethostname:(*) %{generate(str2wcs("gethostname"))}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%#ifdef __USE_MISC
[[wchar]] wsetlogin:(*) %{generate(str2wcs("setlogin"))}
[[wchar]] wsethostname:(*) %{generate(str2wcs("sethostname"))}
[[wchar]] wgetdomainname:(*) %{generate(str2wcs("getdomainname"))}
[[wchar]] wsetdomainname:(*) %{generate(str2wcs("setdomainname"))}
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || \
%   (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
[[wchar]] wchroot:(*) %{generate(str2wcs("chroot"))}
%#endif /* ... */

%
%#if (defined(_EVERY_SOURCE) || \
%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
[[wchar]] wctermid:(*) %{generate(str2wcs("ctermid"))}
%#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */



%{

#endif /* __CC__ */

__SYSDECL_END

}

