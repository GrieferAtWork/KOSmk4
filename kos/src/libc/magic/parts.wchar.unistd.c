/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */
#ifndef _PARTS_WCHAR_PROCESS_H
#include <parts/wchar/process.h>
#endif /* !_PARTS_WCHAR_PROCESS_H */

#ifdef __CC__
__SYSDECL_BEGIN

}

[[wchar, userimpl]] wttyname(*) %{generate(str2wcs("ttyname"))}
[[wchar, userimpl]] wttyname_r(*) %{generate(str2wcs("ttyname_r"))}
//[[wchar, userimpl]] wgetlogin(*) %{generate(str2wcs("getlogin"))}
[[wchar, userimpl]] wchown(*) %{generate(str2wcs("chown"))}
[[wchar, userimpl]] wpathconf(*) %{generate(str2wcs("pathconf"))}
[[wchar, userimpl]] wlink(*) %{generate(str2wcs("link"))}
[[wchar, userimpl]] waccess(*) %{generate(str2wcs("access"))}

[[wchar, userimpl, dos_export_alias("_wchdir")]]  wchdir(*) %{generate(str2wcs("chdir"))}
[[wchar, userimpl, dos_export_alias("_wgetcwd")]] wgetcwd(*) %{generate(str2wcs("getcwd"))}
[[wchar, userimpl, dos_export_alias("_wunlink")]] wunlink(*) %{generate(str2wcs("unlink"))}
[[wchar, userimpl, dos_export_alias("_wrmdir")]]  wrmdir(*) %{generate(str2wcs("rmdir"))}



%#ifdef __USE_GNU
[[wchar, userimpl]]
weuidaccess(*)
	%{generate(str2wcs("euidaccess"))}

weaccess(*) = weuidaccess;

[[wchar, userimpl]]
wget_current_dir_name(*)
	%{generate(str2wcs("get_current_dir_name"))}
%#endif /* __USE_GNU */

%#ifdef __USE_ATFILE
[[wchar, userimpl]] wfaccessat(*) %{generate(str2wcs("faccessat"))}
[[wchar, userimpl]] wfchownat(*) %{generate(str2wcs("fchownat"))}
[[wchar, userimpl]] wlinkat(*) %{generate(str2wcs("linkat"))}
[[wchar, userimpl]] wsymlinkat(*) %{generate(str2wcs("symlinkat"))}
[[wchar, userimpl]] wreadlinkat(*) %{generate(str2wcs("readlinkat"))}
%#ifdef __USE_KOS
[[wchar, userimpl]] wfreadlinkat(*) %{generate(str2wcs("freadlinkat"))}
%#endif /* __USE_KOS */
[[wchar, userimpl]] wunlinkat(*) %{generate(str2wcs("unlinkat"))}
%#endif /* __USE_ATFILE */
[[wchar, userimpl]] wlchown(*) %{generate(str2wcs("lchown"))}

%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K8)
%{
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __FS_TYPE(pos)
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __FS_TYPE(off)
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
}

[[wchar, userimpl, no_crt_self_import]]
[[if($extended_include_prefix("<features.h>") defined(__USE_FILE_OFFSET64)), preferred_alias("wtruncate64")]]
[[if($extended_include_prefix("<features.h>")!defined(__USE_FILE_OFFSET64)), preferred_alias("wtruncate")]]
wtruncate(*) %{generate(str2wcs("truncate"))}

[[wchar, ignore, nocrt, alias("wtruncate")]]
wtruncate32(*) %{generate(str2wcs("truncate32"))}

%#ifdef __USE_LARGEFILE64
[[wchar, userimpl, off64_variant_of(wtruncate)]]
wtruncate64(*) %{generate(str2wcs("truncate64"))}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
[[wchar, userimpl]] wsymlink(*) %{generate(str2wcs("symlink"))}
[[wchar, userimpl]] wreadlink(*) %{generate(str2wcs("readlink"))}
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

//%
//%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
//[[wchar, userimpl]] wgetlogin_r(*) %{generate(str2wcs("getlogin_r"))}
//%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
[[wchar, userimpl]] wgethostname(*) %{generate(str2wcs("gethostname"))}
%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%#ifdef __USE_MISC
[[wchar, userimpl]] wsetlogin(*) %{generate(str2wcs("setlogin"))}
[[wchar, userimpl]] wsethostname(*) %{generate(str2wcs("sethostname"))}
[[wchar, userimpl]] wgetdomainname(*) %{generate(str2wcs("getdomainname"))}
[[wchar, userimpl]] wsetdomainname(*) %{generate(str2wcs("setdomainname"))}
%#endif /* __USE_MISC */

%
%#if (defined(__USE_MISC) || \
%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
[[wchar, userimpl]] wchroot(*) %{generate(str2wcs("chroot"))}
%#endif /* ... */

//%
//%#if (defined(_EVERY_SOURCE) || \
//%     (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K)))
//[[wchar, userimpl]] wctermid(*) %{generate(str2wcs("ctermid"))}
//%#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */



%{

__SYSDECL_END
#endif /* __CC__ */

}
