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
%[default:section(".text.crt{|.dos}.wchar.io.utility")]

%[insert:prefix(
#include <features.h>
)]%{
#ifndef _FCNTL_H
#include <fcntl.h>
#endif /* !_FCNTL_H */
#ifndef _WCHAR_H
#include <wchar.h>
#endif /* !_WCHAR_H */

#ifdef __CC__
__SYSDECL_BEGIN

}


[[wchar, ignore, vartypes($mode_t), decl_include("<bits/types.h>")]]
[[nocrt, doc_alias("wopen"), alias("wopen", "_wopen"), cp, wunused]]
$fd_t wopen32([[in]] wchar_t const *filename, $oflag_t oflags, ...);

[[ignore]] c16open32(*) %{uchar16("wopen32")}
[[ignore]] c32open32(*) %{uchar32("wopen32")}


[[wchar, cp, wunused, vartypes($mode_t), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("wopen", "_wopen")]]
[[                                                                                                                                                     alias("wopen64")]]
[[decl_include("<bits/types.h>")]]
[[dos_export_as("DOS$_wopen", /*"DOS$"*/ "?_wopen@@YAHPB_WHH@Z"), requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(wopen64) || (defined(__AT_FDCWD) && $has_function(wopenat)) ||
           $has_function(open, convert_wcstombs))]]
$fd_t wopen([[in]] wchar_t const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
	va_end(args);
@@pp_if defined(__AT_FDCWD) && $has_function(wopenat)@@
	result = wopenat(__AT_FDCWD, filename, oflags, mode);
@@pp_elif $has_function(wopen64) && !defined(__BUILDING_LIBC)@@
	result = wopen64(filename, oflags, mode);
@@pp_else@@
	{
		char *utf8_filename;
		utf8_filename = convert_wcstombs(filename);
		if unlikely(!utf8_filename)
			return -1;
		result = open(utf8_filename, oflags, mode);
@@pp_if $has_function(free)@@
		free(utf8_filename);
@@pp_endif@@
	}
@@pp_endif@@
	return result;
}

[[wchar, cp, wunused, no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("wcreat", "_wcreat")]]
[[                                                                                                                                                     alias("wcreat64")]]
[[dos_export_as("DOS$_wcreat"), requires_include("<asm/os/fcntl.h>")]]
[[requires((defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && $has_function(wopen)) ||
           $has_function(creat, convert_wcstombs))]]
[[impl_include("<asm/os/fcntl.h>"), decl_include("<bits/types.h>")]]
$fd_t wcreat([[in]] wchar_t const *filename, $mode_t mode) {
@@pp_if defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && $has_function(wopen)@@
	return wopen(filename, __O_CREAT | __O_WRONLY | __O_TRUNC, mode);
@@pp_else@@
	fd_t result;
	char *utf8_filename;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = creat(utf8_filename, mode);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_endif@@
}

%
%#ifdef __USE_LARGEFILE64
[[wchar, vartypes($mode_t), preferred_largefile64_variant_of(wopen), doc_alias("wopen")]]
[[if($extended_include_prefix("<asm/os/oflags.h>")!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), preferred_alias("_wopen")]]
[[decl_include("<bits/types.h>"), impl_include("<asm/os/oflags.h>")]]
[[cp, wunused, requires($has_function(wopen32) || $has_function(open64, convert_wcstombs))]]
$fd_t wopen64([[in]] wchar_t const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
	va_end(args);
@@pp_if $has_function(wopen) && defined(__BUILDING_LIBC)@@
	result = wopen(filename, oflags | __O_LARGEFILE, mode);
@@pp_elif $has_function(wopen32)@@
@@pp_ifdef __O_LARGEFILE@@
	result = wopen32(filename, oflags | __O_LARGEFILE, mode);
@@pp_else@@
	result = wopen32(filename, oflags, mode);
@@pp_endif@@
@@pp_else@@
	{
		char *utf8_filename;
		utf8_filename = convert_wcstombs(filename);
		if unlikely(!utf8_filename)
			return -1;
		result = open64(utf8_filename, oflags, mode);
@@pp_if $has_function(free)@@
		free(utf8_filename);
@@pp_endif@@
	}
@@pp_endif@@
	return result;
}

[[cp, wunused, wchar, preferred_largefile64_variant_of(wcreat), doc_alias("wcreat")]]
[[decl_include("<bits/types.h>"), impl_include("<asm/os/oflags.h>")]]
[[if($extended_include_prefix("<asm/os/oflags.h>")!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), preferred_alias("_wcreat")]]
[[requires_include("<asm/os/oflags.h>")]]
[[requires((defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && $has_function(wopen64)) ||
           $has_function(creat64, convert_wcstombs))]]
$fd_t wcreat64([[in]] wchar_t const *filename, $mode_t mode) {
@@pp_if defined(__O_CREAT) && defined(__O_WRONLY) && defined(__O_TRUNC) && $has_function(wopen64)@@
	return wopen64(filename, __O_CREAT | __O_WRONLY | __O_TRUNC, mode);
@@pp_else@@
	fd_t result;
	char *utf8_filename;
	utf8_filename = convert_wcstombs(filename);
	if unlikely(!utf8_filename)
		return -1;
	result = creat64(utf8_filename, mode);
@@pp_if $has_function(free)@@
	free(utf8_filename);
@@pp_endif@@
	return result;
@@pp_endif@@
}
%#endif /* __USE_LARGEFILE64 */
%
%#ifdef __USE_ATFILE

[[wchar, cp, ignore, nocrt, alias("wopenat"), doc_alias("wopenat")]]
[[wunused, vartypes($mode_t), decl_include("<bits/types.h>")]]
$fd_t wopenat32([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename, $oflag_t oflags, ...);

[[ignore]] c16openat32(*) %{uchar16("wopenat32")}
[[ignore]] c32openat32(*) %{uchar32("wopenat32")}


[[wchar, decl_include("<bits/types.h>"), doc_alias("wopen")]]
[[cp, guard, wunused, vartypes($mode_t), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0), alias("wopenat")]]
[[                                                                                                                                                     alias("wopenat64")]]
[[requires($has_function(wopenat64) || $has_function(openat, convert_wcstombs))]]
$fd_t wopenat([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
	va_end(args);
@@pp_if $has_function(wopenat64) && !defined(__BUILDING_LIBC)@@
	result = wopenat64(dirfd, filename, oflags, mode);
@@pp_else@@
	{
		char *utf8_filename;
		utf8_filename = convert_wcstombs(filename);
		if unlikely(!utf8_filename)
			return -1;
		result = openat(dirfd, utf8_filename, oflags, mode);
@@pp_if $has_function(free)@@
		free(utf8_filename);
@@pp_endif@@
	}
@@pp_endif@@
	return result;
}

%#ifdef __USE_LARGEFILE64
[[wchar, cp, guard, wunused, vartypes($mode_t), doc_alias("wopenat")]]
[[decl_include("<bits/types.h>"), preferred_largefile64_variant_of(wopenat)]]
[[cp, wunused, requires($has_function(wopenat32) || $has_function(openat64, convert_wcstombs))]]
$fd_t wopenat64([[dirfd]] $fd_t dirfd, [[in]] wchar_t const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	mode_t mode;
	va_start(args, oflags);
	mode = va_arg(args, mode_t);
	va_end(args);
@@pp_if $has_function(wopenat) && defined(__BUILDING_LIBC)@@
	result = wopenat(dirfd, filename, oflags | __O_LARGEFILE, mode);
@@pp_elif $has_function(wopenat32)@@
@@pp_ifdef __O_LARGEFILE@@
	result = wopenat32(dirfd, filename, oflags | __O_LARGEFILE, mode);
@@pp_else@@
	result = wopenat32(dirfd, filename, oflags, mode);
@@pp_endif@@
@@pp_else@@
	{
		char *utf8_filename;
		utf8_filename = convert_wcstombs(filename);
		if unlikely(!utf8_filename)
			return -1;
		result = openat(dirfd, utf8_filename, oflags, mode);
@@pp_if $has_function(free)@@
		free(utf8_filename);
@@pp_endif@@
	}
@@pp_endif@@
	return result;
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */


%{

__SYSDECL_END
#endif /* __CC__ */

}
