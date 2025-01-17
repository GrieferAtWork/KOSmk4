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
#ifndef _STDIO_H
#include <stdio.h>
#endif /* !_STDIO_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

}%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

%[default:section(".text.crt{|.dos}.wchar.fs.modify")]

[[wchar, cp, dos_export_alias("_wremove")]]
[[requires_include("<asm/os/fcntl.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(wremoveat)) ||
           $has_function(remove, convert_wcstombs))]]
int wremove([[in]] wchar_t const *filename) {
@@pp_if defined(__AT_FDCWD) && $has_function(wremoveat)@@
	return wremoveat(__AT_FDCWD, filename);
@@pp_else@@
	char *utf8_filename;
	int result;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = remove(utf8_filename);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_endif@@
}

[[wchar, cp, dos_export_alias("_wrename")]]
[[requires_include("<asm/os/fcntl.h>"), decl_include("<hybrid/typecore.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(wrenameat)) ||
           $has_function(renameat, convert_wcstombs))]]
int wrename([[in]] wchar_t const *oldname,
            [[in]] wchar_t const *newname_or_path) {
@@pp_if defined(__AT_FDCWD) && $has_function(wrenameat)@@
	return wrenameat(__AT_FDCWD, oldname, __AT_FDCWD, newname_or_path);
@@pp_else@@
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {
@@pp_if $has_function(free)@@
		free(utf8_oldname);
@@pp_endif@@
		return -1;
	}
	result = rename(utf8_oldname, utf8_newname_or_path);
@@pp_if $has_function(free)@@
	free(utf8_newname_or_path);
	free(utf8_oldname);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_ATFILE
[[wchar, cp, decl_include("<bits/types.h>")]]
[[requires($has_function(wrenameat2) ||
           $has_function(renameat, convert_wcstombs))]]
int wrenameat([[dirfd]] $fd_t oldfd, [[in]] wchar_t const *oldname,
              [[dirfd]] $fd_t newfd, [[in]] wchar_t const *newname_or_path) {
@@pp_if $has_function(wrenameat2)@@
	return wrenameat2(oldfd, oldname, newfd, newname_or_path, 0);
@@pp_else@@
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {
@@pp_if $has_function(free)@@
		free(utf8_oldname);
@@pp_endif@@
		return -1;
	}
	result = renameat(oldfd, utf8_oldname, newfd, utf8_newname_or_path);
@@pp_if $has_function(free)@@
	free(utf8_newname_or_path);
	free(utf8_oldname);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_KOS
[[wchar, cp, requires_function(removeat, convert_wcstombs)]]
[[impl_include("<asm/os/fcntl.h>"), decl_include("<bits/types.h>")]]
int wremoveat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename) {
@@pp_if $has_function(wunlinkat) && defined(__AT_REMOVEREG) && defined(__AT_REMOVEDIR)@@
	return wunlinkat(dirfd, filename, __AT_REMOVEREG | __AT_REMOVEDIR);
@@pp_else@@
	char *utf8_filename;
	int result;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = removeat(dirfd, utf8_filename);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_endif@@
}
%#endif /* __USE_KOS */
%#endif /* __USE_ATFILE */


%#ifdef __USE_GNU
[[decl_include("<bits/types.h>")]]
[[wchar, cp, requires_function(renameat2, convert_wcstombs)]]
int wrenameat2([[dirfd]] $fd_t oldfd, [[in]] wchar_t const *oldname,
               [[dirfd]] $fd_t newfd, [[in]] wchar_t const *newname_or_path,
               $atflag_t flags) {
	char *utf8_oldname;
	char *utf8_newname_or_path;
	int result;
	utf8_oldname = convert_wcstombs(oldname);
	if unlikely(!utf8_oldname)
		return -1;
	utf8_newname_or_path = convert_wcstombs(newname_or_path);
	if unlikely(!utf8_newname_or_path) {
@@pp_if $has_function(free)@@
		free(utf8_oldname);
@@pp_endif@@
		return -1;
	}
	result = renameat2(oldfd, utf8_oldname, newfd, utf8_newname_or_path, flags);
@@pp_if $has_function(free)@@
	free(utf8_newname_or_path);
	free(utf8_oldname);
@@pp_endif@@
	return result;
}
%#endif /* __USE_GNU */



[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, dos_export_alias("_wfopen")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
[[requires_function(fopen, convert_wcstombs)]]
$FILE *wfopen([[in]] wchar_t const *filename,
              [[in]] wchar_t const *mode) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_filename;
	result = fopen(utf8_filename, utf8_mode);
@@pp_if $has_function(free)@@
	free(utf8_mode);
@@pp_endif@@
done_utf8_filename:
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
done:
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[wchar, wunused, dos_export_alias("_wfreopen")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
[[requires_function(freopen, convert_wcstombs)]]
$FILE *wfreopen([[in]] wchar_t const *filename,
                [[in]] wchar_t const *mode,
                [[inout]] $FILE *stream) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_filename;
	/*utf-8*/ char *utf8_mode;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		goto done;
	utf8_mode = convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_filename;
	result = freopen(utf8_filename, utf8_mode, stream);
@@pp_if $has_function(free)@@
	free(utf8_mode);
@@pp_endif@@
done_utf8_filename:
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
done:
	return result;
}

[[decl_include("<hybrid/typecore.h>")]]
[[guard, wchar, wunused, dos_export_alias("_wpopen")]]
[[section(".text.crt{|.dos}.wchar.FILE.locked.access")]]
[[requires_function(popen, convert_wcstombs)]]
$FILE *wpopen([[in]] wchar_t const *command,
              [[in]] wchar_t const *mode) {
	FILE *result = NULL;
	/*utf-8*/ char *utf8_command;
	/*utf-8*/ char *utf8_mode;
	utf8_command = convert_wcstombs(command);
	if unlikely(!utf8_command)
		goto done;
	utf8_mode = convert_wcstombs(mode);
	if unlikely(!utf8_mode)
		goto done_utf8_command;
	result = popen(utf8_command, utf8_mode);
@@pp_if $has_function(free)@@
	free(utf8_mode);
@@pp_endif@@
done_utf8_command:
@@pp_if $has_function(free)@@
	free(utf8_command);
@@pp_endif@@
done:
	return result;
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
