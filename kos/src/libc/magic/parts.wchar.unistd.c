/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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

[[wchar]] wttyname(*) %{generate(str2wcs("ttyname"))}
[[wchar, userimpl]] wttyname_r(*) %{generate(str2wcs("ttyname_r"))}

//[[wchar, userimpl]] wgetlogin(*) %{generate(str2wcs("getlogin"))}

[[wchar, cp, decl_include("<bits/types.h>"), section(".text.crt{|.dos}.wchar.fs.modify")]]
[[requires((defined(__AT_FDCWD) && $has_function(wfchownat)) ||
           $has_function(chown, convert_wcstombs))]]
int wchown([[nonnull]] wchar_t const *file, $uid_t owner, $gid_t group) {
@@pp_if defined(__AT_FDCWD) && $has_function(wfchownat)@@
	return wfchownat(__AT_FDCWD, file, owner, group, 0);
@@pp_else@@
	longptr_t result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = chown(utf8_file, owner, group);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_endif@@
}


[[requires_function(pathconf, convert_wcstombs)]]
[[wchar, cp, section(".text.crt{|.dos}.wchar.fs.property"), decl_include("<features.h>")]]
$longptr_t wpathconf([[nonnull]] wchar_t const *path, __STDC_INT_AS_UINT_T name) {
	longptr_t result;
	char *utf8_path;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = pathconf(utf8_path, name);
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
	return result;
}


[[requires_include("<asm/os/fcntl.h>"), impl_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(wlinkat)) ||
           $has_function(link, convert_wcstombs))]]
[[wchar, cp, section(".text.crt{|.dos}.wchar.fs.modify")]]
int wlink([[nonnull]] wchar_t const *from, [[nonnull]] wchar_t const *to) {
@@pp_if defined(__AT_FDCWD) && $has_function(wlinkat)@@
	return wlinkat(__AT_FDCWD, from, __AT_FDCWD, to, 0);
@@pp_else@@
	int result = -1;
	char *utf8_from, *utf8_to;
	utf8_from = convert_wcstombs(from);
	if unlikely(!utf8_from)
		goto done;
	utf8_to = convert_wcstombs(to);
	if unlikely(!utf8_to)
		goto done_from;
	result = link(utf8_from, utf8_to);
@@pp_if $has_function(free)@@
	free(utf8_to);
@@pp_endif@@
done_from:
@@pp_if $has_function(free)@@
	free(utf8_from);
@@pp_endif@@
done:
	return result;
@@pp_endif@@
}

[[wchar, cp, wunused, decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.wchar.fs.property")]]
[[requires_include("<asm/os/fcntl.h>"), dos_export_alias("_waccess")]]
[[requires((defined(__AT_FDCWD) && $has_function(wfaccessat)) ||
           $has_function(access, convert_wcstombs))]]
int waccess([[nonnull]] wchar_t const *file, __STDC_INT_AS_UINT_T type) {
@@pp_if defined(__AT_FDCWD) && $has_function(wfaccessat)@@
	return wfaccessat(__AT_FDCWD, file, type, 0);
@@pp_else@@
	longptr_t result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = access(utf8_file, type);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_endif@@
}

[[section(".text.crt{|.dos}.wchar.fs.basic_property")]]
[[wchar, cp, dos_export_alias("_wchdir")]]
[[requires($has_function(chdir, convert_wcstombs))]]
int wchdir([[nonnull]] wchar_t const *path) {
	longptr_t result;
	char *utf8_path;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = chdir(utf8_path);
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
	return result;
}


[[wchar, cp, guard, dos_export_alias("_wgetcwd")]]
[[section(".text.crt{|.dos}.wchar.fs.basic_property")]]
[[requires($has_function(getcwd, convert_mbstowcs))]]
[[impl_include("<hybrid/typecore.h>", "<libc/errno.h>")]]
wchar_t *wgetcwd([[outp_opt(bufsize)]] wchar_t *buf, size_t bufsize) {
	char *utf8_result;
	wchar_t *result;
	size_t result_len;
	utf8_result = getcwd(NULL, 0);
	if unlikely(!utf8_result)
		return NULL;
	result = convert_mbstowcs(utf8_result);
	free(utf8_result);
	if unlikely(!result)
		return NULL;
	result_len = wcslen(result) + 1;
	if (!buf) {
		wchar_t *new_result;
		if (!bufsize)
			return result;
		if (bufsize < result_len) {
@@pp_ifdef ERANGE@@
			(void)libc_seterrno(ERANGE);
@@pp_else@@
			(void)libc_seterrno(1);
@@pp_endif@@
			buf = NULL;
			goto done;
		}
@@pp_if $has_function(realloc)@@
		new_result = (wchar_t *)realloc(result, bufsize * __SIZEOF_WCHAR_T__);
		if unlikely(!new_result) {
			buf = NULL;
			goto done;
		}
@@pp_else@@
		new_result = result;
@@pp_endif@@
		return new_result;
	}
	if (bufsize < result_len) {
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		buf = NULL;
		goto done;
	}
	wmemcpy(buf, result, result_len);
done:
@@pp_if $has_function(free)@@
	free(result);
@@pp_endif@@
	return buf;
}



[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, dos_export_alias("_wunlink")]]
[[requires((defined(__AT_FDCWD) && $has_function(wunlinkat)) ||
           $has_function(unlink, convert_wcstombs))]]
int wunlink([[nonnull]] wchar_t const *file) {
@@pp_if defined(__AT_FDCWD) && $has_function(wunlinkat)@@
	return wunlinkat(__AT_FDCWD, file, 0);
@@pp_else@@
	longptr_t result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = unlink(utf8_file);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_endif@@
}

[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, dos_export_alias("_wrmdir")]]
[[requires((defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && $has_function(wunlinkat)) ||
           $has_function(rmdir, convert_wcstombs))]]
int wrmdir([[nonnull]] wchar_t const *path) {
@@pp_if defined(__AT_FDCWD) && defined(__AT_REMOVEDIR) && $has_function(wunlinkat)@@
	return wunlinkat(__AT_FDCWD, path, __AT_REMOVEDIR);
@@pp_else@@
	longptr_t result;
	char *utf8_path;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = rmdir(utf8_path);
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
	return result;
@@pp_endif@@
}


%#ifdef __USE_GNU
[[wchar, cp, wunused, decl_include("<features.h>")]]
[[section(".text.crt{|.dos}.wchar.fs.property")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && defined(__AT_EACCESS) && $has_function(wfaccessat)) ||
           $has_function(euidaccess, convert_wcstombs))]]
int weuidaccess([[nonnull]] wchar_t const *file, __STDC_INT_AS_UINT_T type) {
@@pp_if defined(__AT_FDCWD) && defined(__AT_EACCESS) && $has_function(wfaccessat)@@
	return wfaccessat(__AT_FDCWD, file, type, __AT_EACCESS);
@@pp_else@@
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = euidaccess(utf8_file, type);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_endif@@
}


weaccess(*) = weuidaccess;

[[wchar, cp, wunused, ATTR_MALLOC]]
[[section(".text.crt{|.dos}.wchar.fs.basic_property")]]
[[requires_function(get_current_dir_name, convert_mbstowcs)]]
wchar_t *wget_current_dir_name(void) {
	char *utf8_path;
	wchar_t *result;
	utf8_path = get_current_dir_name();
	if unlikely(!utf8_path)
		return NULL;
	result = convert_mbstowcs(utf8_path);
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
	return result;
}

%#endif /* __USE_GNU */

%#ifdef __USE_ATFILE
[[section(".text.crt{|.dos}.wchar.fs.property")]]
[[wchar, cp, decl_include("<features.h>", "<bits/types.h>")]]
[[requires_function(faccessat, convert_wcstombs)]]
int wfaccessat($fd_t dfd, [[nonnull]] wchar_t const *file,
               __STDC_INT_AS_UINT_T type, $atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = faccessat(dfd, utf8_file, type, flags);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
}


[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_function(fchownat, convert_wcstombs)]]
int wfchownat($fd_t dfd, [[nonnull]] wchar_t const *file,
              $uid_t owner, $gid_t group, $atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = fchownat(dfd, utf8_file, owner, group, flags);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
}


[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_function(convert_wcstombs, linkat)]]
int wlinkat($fd_t fromfd, [[nonnull]] wchar_t const *from,
            $fd_t tofd, [[nonnull]] wchar_t const *to, $atflag_t flags) {
	int result = -1;
	char *utf8_from, *utf8_to;
	utf8_from = convert_wcstombs(from);
	if unlikely(!utf8_from)
		goto done;
	utf8_to = convert_wcstombs(to);
	if unlikely(!utf8_to)
		goto done_from;
	result = linkat(fromfd, utf8_from, tofd, utf8_to, flags);
@@pp_if $has_function(free)@@
	free(utf8_to);
@@pp_endif@@
done_from:
@@pp_if $has_function(free)@@
	free(utf8_from);
@@pp_endif@@
done:
	return result;
}

[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires($has_function(wfsymlinkat) ||
           $has_function(symlinkat, convert_wcstombs))]]
int wsymlinkat([[nonnull]] wchar_t const *link_text, $fd_t tofd,
               [[nonnull]] wchar_t const *target_path) {
@@pp_if $has_function(wfsymlinkat)@@
	return wfsymlinkat(link_text, tofd, target_path, 0);
@@pp_else@@
	int result = -1;
	char *utf8_link_text, *utf8_target_path;
	utf8_link_text = convert_wcstombs(link_text);
	if unlikely(!utf8_link_text)
		goto done;
	utf8_target_path = convert_wcstombs(target_path);
	if unlikely(!utf8_target_path)
		goto done_from;
	result = symlinkat(utf8_link_text, tofd, utf8_target_path);
@@pp_if $has_function(free)@@
	free(utf8_target_path);
@@pp_endif@@
done_from:
@@pp_if $has_function(free)@@
	free(utf8_link_text);
@@pp_endif@@
done:
	return result;
@@pp_endif@@
}

[[section(".text.crt{|.dos}.wchar.fs.property")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
ssize_t wreadlinkat($fd_t dfd, [[nonnull]] wchar_t const *path,
                    [[outp(buflen)]] wchar_t *buf, size_t buflen); /* TODO */


%#ifdef __USE_KOS
[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires($has_function(fsymlinkat, convert_wcstombs))]]
int wfsymlinkat([[nonnull]] wchar_t const *link_text, $fd_t tofd,
                [[nonnull]] wchar_t const *target_path, $atflag_t flags) {
	int result = -1;
	char *utf8_link_text, *utf8_target_path;
	utf8_link_text = convert_wcstombs(link_text);
	if unlikely(!utf8_link_text)
		goto done;
	utf8_target_path = convert_wcstombs(target_path);
	if unlikely(!utf8_target_path)
		goto done_from;
	result = fsymlinkat(utf8_link_text, tofd, utf8_target_path, flags);
@@pp_if $has_function(free)@@
	free(utf8_target_path);
@@pp_endif@@
done_from:
@@pp_if $has_function(free)@@
	free(utf8_link_text);
@@pp_endif@@
done:
	return result;
}

[[section(".text.crt{|.dos}.wchar.fs.property")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
ssize_t wfreadlinkat($fd_t dfd, [[nonnull]] wchar_t const *path,
                     [[outp(buflen)]] wchar_t *buf, size_t buflen,
                     $atflag_t flags); /* TODO */

%#endif /* __USE_KOS */

[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires($has_function(unlinkat, convert_wcstombs))]]
int wunlinkat($fd_t dfd, [[nonnull]] wchar_t const *file, $atflag_t flags) {
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = unlinkat(dfd, utf8_file, flags);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
}


%#endif /* __USE_ATFILE */

[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[cp, decl_include("<bits/types.h>"), impl_include("<asm/os/fcntl.h>")]]
[[wchar, requires_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && $has_function(wfchownat)) ||
           $has_function(lchown, convert_wcstombs))]]
int wlchown([[nonnull]] wchar_t const *file, $uid_t owner, $gid_t group) {
@@pp_if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && $has_function(wfchownat)@@
	return wfchownat(__AT_FDCWD, file, owner, group, __AT_SYMLINK_NOFOLLOW);
@@pp_else@@
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = lchown(utf8_file, owner, group);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_endif@@
}

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

[[wchar, ignore, nocrt, alias("wtruncate"), decl_include("<bits/types.h>")]]
int crt_wtruncate32([[nonnull]] wchar_t const *file, $pos32_t length);
[[wchar, ignore, nocrt, alias("wtruncate64"), decl_include("<bits/types.h>")]]
int crt_wtruncate64([[nonnull]] wchar_t const *file, $pos32_t length);

[[ignore]] crt_c16truncate32(*) %{uchar16("crt_wtruncate32")}
[[ignore]] crt_c32truncate32(*) %{uchar32("crt_wtruncate32")}
[[ignore]] crt_c16truncate64(*) %{uchar16("crt_wtruncate64")}
[[ignore]] crt_c32truncate64(*) %{uchar32("crt_wtruncate64")}


[[wchar, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("wtruncate")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("wtruncate64")]]
[[section(".text.crt{|.dos}.wchar.fs.modify"), decl_include("<bits/types.h>")]]
[[requires($has_function(crt_wtruncate64) ||
           $has_function(crt_wtruncate32) ||
           $has_function(truncate, convert_wcstombs))]]
int wtruncate([[nonnull]] wchar_t const *file, __PIO_OFFSET length) {
@@pp_if $has_function(crt_wtruncate32) && !defined(__BUILDING_LIBC)@@
	return crt_wtruncate32(file, (pos32_t)length);
@@pp_elif $has_function(crt_wtruncate64) && (!defined(__BUILDING_LIBC) || __SIZEOF_OFF32_T__ != __SIZEOF_OFF64_T__)@@
	return wtruncate64(file, (__PIO_OFFSET64)length);
@@pp_else@@
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = truncate(utf8_file, length);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[wchar, section(".text.crt{|.dos}.wchar.fs.modify"), decl_include("<bits/types.h>")]]
[[crt_dos_variant, preferred_off64_variant_of(wtruncate), doc_alias("wtruncate")]]
[[impl_include("<features.h>"), impl_prefix(DEFINE_PIO_OFFSET)]]
[[requires($has_function(truncate64, convert_wcstombs) ||
           $has_function(crt_wtruncate32))]]
int wtruncate64([[nonnull]] wchar_t const *file, __PIO_OFFSET64 length) {
@@pp_if $has_function(truncate64, convert_wcstombs)@@
	int result;
	char *utf8_file;
	utf8_file = convert_wcstombs(file);
	if unlikely(!utf8_file)
		return -1;
	result = truncate64(utf8_file, length);
@@pp_if $has_function(free)@@
	free(utf8_file);
@@pp_endif@@
	return result;
@@pp_else@@
	return crt_wtruncate32(file, (pos32_t)length);
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K8 */

%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)

[[section(".text.crt{|.dos}.wchar.fs.modify")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(wsymlinkat)) ||
           $has_function(symlink, convert_wcstombs))]]
int wsymlink([[nonnull]] wchar_t const *link_text,
             [[nonnull]] wchar_t const *target_path) {
@@pp_if defined(__AT_FDCWD) && $has_function(wfsymlinkat)@@
	return wfsymlinkat(link_text, __AT_FDCWD, target_path, 0);
@@pp_elif defined(__AT_FDCWD) && $has_function(wsymlinkat)@@
	return wsymlinkat(link_text, __AT_FDCWD, target_path);
@@pp_else@@
	int result = -1;
	char *utf8_link_text, *utf8_target_path;
	utf8_link_text = convert_wcstombs(link_text);
	if unlikely(!utf8_link_text)
		goto done;
	utf8_target_path = convert_wcstombs(target_path);
	if unlikely(!utf8_target_path)
		goto done_from;
	result = symlink(utf8_link_text, utf8_target_path);
@@pp_if $has_function(free)@@
	free(utf8_target_path);
@@pp_endif@@
done_from:
@@pp_if $has_function(free)@@
	free(utf8_link_text);
@@pp_endif@@
done:
	return result;
@@pp_endif@@
}

[[section(".text.crt{|.dos}.wchar.fs.property")]]
[[wchar, cp, decl_include("<bits/types.h>")]]
ssize_t wreadlink([[nonnull]] wchar_t const *path,
                  [[outp(buflen)]] wchar_t *buf,
                  size_t buflen); /* TODO */

%#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

//%
//%#if defined(__USE_REENTRANT) || defined(__USE_POSIX199506)
//[[wchar, userimpl]] wgetlogin_r(*) %{generate(str2wcs("getlogin_r"))}
//%#endif /* __USE_REENTRANT || __USE_POSIX199506 */

%
%#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K)
[[wchar, section(".text.crt{|.dos}.wchar.system.configuration")]]
[[impl_include("<bits/crt/wformat-printer.h>", "<bits/crt/mbstate.h>", "<libc/errno.h>")]]
[[requires($has_function(uname))]]
int wgethostname([[outp(buflen)]] wchar_t *name, size_t buflen) {
	struct __LOCAL_format_wsnprintf_data {
		wchar_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct __LOCAL_format_8tow_data {
		__pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate  fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct utsname uts;
	int result = uname(&uts);
	if likely(result == 0) {
		struct __LOCAL_format_wsnprintf_data printer_data;
		struct __LOCAL_format_8tow_data convert_data;
		size_t len = strnlen(uts.@nodename@, COMPILER_LENOF(uts.@nodename@));
		ssize_t width;
		printer_data.sd_buffer  = name;
		printer_data.sd_bufsiz  = buflen;
		convert_data.fd_arg     = &printer_data;
		convert_data.fd_printer = &format_wsnprintf_printer;
		__mbstate_init(&convert_data.fd_incomplete);
		width = format_8tow(&convert_data, uts.@nodename@, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {
@@pp_ifdef ERANGE@@
			return libc_seterrno(ERANGE);
@@pp_else@@
			return libc_seterrno(1);
@@pp_endif@@
		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}

%#endif /* __USE_UNIX98 || __USE_XOPEN2K */

%
%#ifdef __USE_MISC
[[wchar, section(".text.crt{|.dos}.wchar.io.tty")]]
[[requires($has_function(setlogin, convert_wcstombs))]]
int wsetlogin([[nonnull]] wchar_t const *name) {
	int result;
	char *utf8_name;
	utf8_name = convert_wcstombs(name);
	if unlikely(!utf8_name)
		return -1;
	result = setlogin(utf8_name);
@@pp_if $has_function(free)@@
	free(utf8_name);
@@pp_endif@@
	return result;
}

[[section(".text.crt{|.dos}.wchar.system.configuration")]]
[[wchar, decl_include("<hybrid/typecore.h>")]]
[[requires($has_function(sethostname, convert_wcstombsn))]]
int wsethostname([[inp(len)]] wchar_t const *name, size_t len) {
	int result;
	char *utf8_name;
	size_t utf8_len;
	utf8_name = convert_wcstombsn(name, len, &utf8_len);
	if unlikely(!utf8_name)
		return -1;
	result = sethostname(utf8_name, utf8_len);
@@pp_if $has_function(free)@@
	free(utf8_name);
@@pp_endif@@
	return result;
}

[[wchar, section(".text.crt{|.dos}.wchar.system.configuration")]]
[[impl_include("<bits/crt/wformat-printer.h>", "<bits/crt/mbstate.h>", "<libc/errno.h>")]]
[[requires($has_function(uname))]]
int wgetdomainname([[outp(buflen)]] wchar_t *name, size_t buflen) {
	struct __LOCAL_format_wsnprintf_data {
		wchar_t      *sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ sd_bufsiz; /* Remaining buffer size. */
	};
	struct __LOCAL_format_8tow_data {
		__pwformatprinter fd_printer;    /* [1..1] Inner printer */
		void             *fd_arg;        /* Argument for `fd_printer' */
		struct __mbstate  fd_incomplete; /* Incomplete utf-8 sequence part (initialize to 0) */
	};
	struct utsname uts;
	int result = uname(&uts);
	if likely(result == 0) {
		struct __LOCAL_format_wsnprintf_data printer_data;
		struct __LOCAL_format_8tow_data convert_data;
		size_t len = strnlen(uts.@domainname@, COMPILER_LENOF(uts.@domainname@));
		ssize_t width;
		printer_data.sd_buffer  = name;
		printer_data.sd_bufsiz  = buflen;
		convert_data.fd_arg     = &printer_data;
		convert_data.fd_printer = &format_wsnprintf_printer;
		__mbstate_init(&convert_data.fd_incomplete);
		width = format_8tow(&convert_data, uts.@domainname@, len);
		if unlikely(width < 0)
			return -1;
		if ((size_t)width >= buflen) {
@@pp_ifdef ERANGE@@
			return libc_seterrno(ERANGE);
@@pp_else@@
			return libc_seterrno(1);
@@pp_endif@@
		}
		*printer_data.sd_buffer = '\0'; /* NUL-terminate */
	}
	return result;
}

[[section(".text.crt{|.dos}.wchar.system.configuration")]]
[[wchar, decl_include("<hybrid/typecore.h>")]]
[[requires($has_function(setdomainname, convert_wcstombsn))]]
int wsetdomainname([[inp(len)]] wchar_t const *name, size_t len) {
	int result;
	char *utf8_name;
	size_t utf8_len;
	utf8_name = convert_wcstombsn(name, len, &utf8_len);
	if unlikely(!utf8_name)
		return -1;
	result = setdomainname(utf8_name, utf8_len);
@@pp_if $has_function(free)@@
	free(utf8_name);
@@pp_endif@@
	return result;
}


%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
[[section(".text.crt{|.dos}.wchar.fs.utility")]]
[[wchar, cp, requires($has_function(chroot, convert_wcstombs))]]
int wchroot([[nonnull]] wchar_t const *path) {
	longptr_t result;
	char *utf8_path;
	utf8_path = convert_wcstombs(path);
	if unlikely(!utf8_path)
		return -1;
	result = chroot(utf8_path);
@@pp_if $has_function(free)@@
	free(utf8_path);
@@pp_endif@@
	return result;
}

%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

//%
//%#if defined(_EVERY_SOURCE) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
//[[wchar, userimpl]] wctermid(*) %{generate(str2wcs("ctermid"))}
//%#endif /* _EVERY_SOURCE || (__USE_XOPEN && !__USE_XOPEN2K) */


%{

__SYSDECL_END
#endif /* __CC__ */

}
