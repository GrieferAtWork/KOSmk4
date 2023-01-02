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

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{
#ifndef _STDLIB_H
#include <stdlib.h>
#endif /* !_STDLIB_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[define_str2wcs_replacement(system = wsystem)]

[[decl_include("<hybrid/typecore.h>")]]
[[cp, guard, wchar, dos_export_alias("_wsystem")]]
[[section(".text.crt{|.dos}.wchar.fs.exec.system")]]
[[requires_function(system, convert_wcstombs)]]
int wsystem([[nullable]] wchar_t const *cmd) {
	int result;
	char *used_cmd;
	if (!cmd) {
		result = system(NULL);
	} else {
		used_cmd = convert_wcstombs(cmd);
		if unlikely(!used_cmd)
			return -1;
		result = system(used_cmd);
@@pp_if $has_function(free)@@
		free(used_cmd);
@@pp_endif@@
	}
	return result;
}


%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
%[define_str2wcs_replacement(realpath = wrealpath)]

[[wchar, cp, wunused, decl_include("<hybrid/typecore.h>")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(wfrealpathat)) ||
           $has_function(realpath, convert_wcstombs, convert_mbstowcs))]]
[[impl_include("<asm/os/fcntl.h>", "<asm/os/limits.h>", "<libc/errno.h>")]]
[[section(".text.crt{|.dos}.wchar.fs.property")]]
wchar_t *wrealpath([[in]] wchar_t const *filename, [[out_opt]] wchar_t *resolved) {
@@pp_if defined(__AT_FDCWD) && $has_function(wfrealpathat)@@
@@pp_if   defined(__PATH_MAX)   &&   __PATH_MAX   !=    -1@@
	return wfrealpathat(__AT_FDCWD, filename, resolved, resolved ? __PATH_MAX : 0, 0);
@@pp_else@@
	return wfrealpathat(__AT_FDCWD, filename, resolved, resolved ? _POSIX_PATH_MAX : 0, 0);
@@pp_endif@@
@@pp_else@@
	char *utf8_filename, *utf8_resolved;
	wchar_t *wcs_resolved;
	size_t resolved_length;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return NULL;
	utf8_resolved = realpath(utf8_filename, NULL);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = convert_mbstowcs(utf8_resolved);
@@pp_if $has_function(free)@@
	free(utf8_resolved);
@@pp_endif@@
	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = wcslen(wcs_resolved) + 1;
@@pp_if defined(__PATH_MAX) && __PATH_MAX != -1@@
	if (resolved_length > __PATH_MAX)
@@pp_else@@
	if (resolved_length > _POSIX_PATH_MAX)
@@pp_endif@@
	{
@@pp_if $has_function(free)@@
		free(wcs_resolved);
@@pp_endif@@
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		return NULL;
	}
	resolved = wmemcpy(resolved, wcs_resolved, resolved_length);
@@pp_if $has_function(free)@@
	free(wcs_resolved);
@@pp_endif@@
	return resolved;
@@pp_endif@@
}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

%
%#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_KOS)
%[define_str2wcs_replacement(frealpath = wfrealpath)]

[[wchar, cp, wunused, section(".text.crt{|.dos}.wchar.fs.property")]]
[[decl_include("<bits/types.h>")]]
[[requires($has_function(wfrealpath4) ||
           $has_function(frealpath, convert_mbstowcs))]]
wchar_t *wfrealpath($fd_t fd, [[out(? <= buflen)]] wchar_t *resolved, $size_t buflen) {
@@pp_if $has_function(wfrealpath4)@@
	return wfrealpath4(fd, resolved, buflen, 0);
@@pp_else@@
	char *utf8_resolved;
	wchar_t *wcs_resolved;
	size_t resolved_length;
	utf8_resolved = frealpath(fd, NULL, 0);
	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = convert_mbstowcs(utf8_resolved);
@@pp_if $has_function(free)@@
	free(utf8_resolved);
@@pp_endif@@
	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = wcslen(wcs_resolved) + 1;
	if (resolved_length > buflen) {
@@pp_if $has_function(free)@@
		free(wcs_resolved);
@@pp_endif@@
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		return NULL;
	}
	resolved = wmemcpy(resolved, wcs_resolved, resolved_length);
@@pp_if $has_function(free)@@
	free(wcs_resolved);
@@pp_endif@@
	return resolved;
@@pp_endif@@
}
%#endif /* __USE_MISC || __USE_XOPEN_EXTENDED || __USE_KOS */

%
%#ifdef __USE_KOS
%[define_str2wcs_replacement(frealpath4 = wfrealpath4)]

[[wchar, cp, wunused, section(".text.crt{|.dos}.wchar.fs.property")]]
[[decl_include("<bits/types.h>"), requires_function(frealpath4, convert_mbstowcs)]]
wchar_t *wfrealpath4($fd_t fd, [[out(? <= buflen)]] wchar_t *resolved,
                     $size_t buflen, $atflag_t flags) {
	char *utf8_resolved;
	wchar_t *wcs_resolved;
	size_t resolved_length;
	utf8_resolved = frealpath4(fd, NULL, 0, flags);
	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = convert_mbstowcs(utf8_resolved);
@@pp_if $has_function(free)@@
	free(utf8_resolved);
@@pp_endif@@
	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = wcslen(wcs_resolved) + 1;
	if (resolved_length > buflen) {
@@pp_if $has_function(free)@@
		free(wcs_resolved);
@@pp_endif@@
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		return NULL;
	}
	resolved = wmemcpy(resolved, wcs_resolved, resolved_length);
@@pp_if $has_function(free)@@
	free(wcs_resolved);
@@pp_endif@@
	return resolved;
}

%[define_str2wcs_replacement(frealpathat = wfrealpathat)]

[[wchar, cp, wunused, section(".text.crt{|.dos}.wchar.fs.property")]]
[[decl_include("<bits/types.h>"), requires_function(frealpathat, convert_wcstombs, convert_mbstowcs)]]
wchar_t *wfrealpathat($fd_t dirfd, [[in]] wchar_t const *filename,
                      [[out(? <= buflen)]] wchar_t *resolved,
                      $size_t buflen, $atflag_t flags) {
	char *utf8_filename, *utf8_resolved;
	wchar_t *wcs_resolved;
	size_t resolved_length;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return NULL;
	utf8_resolved = frealpathat(dirfd, utf8_filename, NULL, 0, flags);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	if unlikely(!utf8_resolved)
		return NULL;
	wcs_resolved = convert_mbstowcs(utf8_resolved);
@@pp_if $has_function(free)@@
	free(utf8_resolved);
@@pp_endif@@
	if unlikely(!wcs_resolved)
		return NULL;
	if (!resolved)
		return wcs_resolved;
	resolved_length = wcslen(wcs_resolved) + 1;
	if (resolved_length > buflen) {
@@pp_if $has_function(free)@@
		free(wcs_resolved);
@@pp_endif@@
@@pp_ifdef ERANGE@@
		(void)libc_seterrno(ERANGE);
@@pp_else@@
		(void)libc_seterrno(1);
@@pp_endif@@
		return NULL;
	}
	resolved = wmemcpy(resolved, wcs_resolved, resolved_length);
@@pp_if $has_function(free)@@
	free(wcs_resolved);
@@pp_endif@@
	return resolved;
}

%[default:section(".text.crt{|.dos}.wchar.unicode.static.convert")]
[[wchar, pure, wunused, dos_export_alias("_wtoi"), decl_include("<hybrid/typecore.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("wtol", "_wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG_LONG__), alias("wtoll", "_wtoll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == 8), alias("_wtoi64")]]
int wtoi([[in]] wchar_t const *nptr) %{generate(str2wcs("atoi"))}

[[wchar, pure, wunused, dos_export_alias("_wtol"), decl_include("<hybrid/typecore.h>")]]
[[alt_variant_of(__SIZEOF_LONG__ == __SIZEOF_INT__, wtoi)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_INT__), alias("_wtoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("wtoll", "_wtoll")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == 8), alias("_wtoi64")]]
long wtol([[in]] wchar_t const *nptr) %{generate(str2wcs("atol"))}

%#ifdef __LONGLONG
[[wchar, pure, wunused, dos_export_alias("_wtoll"), decl_include("<hybrid/typecore.h>")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_INT__, "wtoi")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_INT__), alias("_wtoi")]]
[[alt_variant_of(__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__, "wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == __SIZEOF_LONG__), alias("_wtol")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG_LONG__ == 8), alias("_wtoi64")]]
__LONGLONG wtoll([[in]] wchar_t const *nptr) %{generate(str2wcs("atoll"))}
%#endif /* __LONGLONG */
%#endif /* __USE_KOS */

%{

__SYSDECL_END
#endif /* __CC__ */

}
