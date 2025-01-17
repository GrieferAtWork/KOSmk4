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
%[default:section(".text.crt{|.dos}.except.io.utility")]
%[default:nodos]


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <fcntl.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <asm/os/oflags.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

[[decl_include("<features.h>", "<bits/types.h>")]]
[[throws, vartypes(void *), doc_alias("fcntl")]]
__STDC_INT_AS_SSIZE_T Fcntl([[fdarg]] $fd_t fd, int cmd, ...);

%[default:section(".text.crt{|.dos}.except.io.access")]

[[ignore, nocrt, alias("Open"), doc_alias("Open")]]
[[cp, wunused, vartypes($mode_t), throws, decl_include("<bits/types.h>")]]
$fd_t Open32([[in]] char const *filename, $oflag_t oflags, ...);


[[cp, throws, wunused, vartypes($mode_t), decl_include("<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("Open")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>") defined(__USE_FILE_OFFSET64) || (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("Open64")]]
[[userimpl, requires_include("<asm/os/fcntl.h>"), doc_alias("open")]]
[[requires($has_function(Open64) || (defined(__AT_FDCWD) && $has_function(OpenAt)))]]
$fd_t Open([[in]] char const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	va_start(args, oflags);
@@pp_if $has_function(Open64)@@
	result = Open64(filename, oflags, va_arg(args, mode_t));
@@pp_else@@
	result = OpenAt(__AT_FDCWD, filename, oflags, va_arg(args, mode_t));
@@pp_endif@@
	va_end(args);
	return result;
}

[[cp, throws, wunused, decl_include("<bits/types.h>"), no_crt_self_import, doc_alias("creat")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("Creat")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>") defined(__USE_FILE_OFFSET64) || (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("Creat64")]]
[[userimpl, requires_function(Open), impl_include("<asm/os/oflags.h>")]]
$fd_t Creat([[in]] char const *filename, $mode_t mode) {
	return Open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}

%
%#ifdef __USE_LARGEFILE64
[[cp, wunused, throws, vartypes($mode_t), decl_include("<bits/types.h>")]]
[[preferred_largefile64_variant_of(Open), doc_alias("Open")]]
[[requires_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(OpenAt64)) || $has_function(Open32))]]
[[userimpl, impl_include("<asm/os/fcntl.h>", "<asm/os/oflags.h>")]]
$fd_t Open64([[in]] char const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	va_start(args, oflags);
@@pp_if defined(__AT_FDCWD) && $has_function(OpenAt64)@@
	result = OpenAt64(__AT_FDCWD, filename, oflags, va_arg(args, mode_t));
@@pp_else@@
@@pp_ifdef O_LARGEFILE@@
	result = Open32(filename, oflags | O_LARGEFILE, va_arg(args, mode_t));
@@pp_else@@
	result = Open32(filename, oflags, va_arg(args, mode_t));
@@pp_endif@@
@@pp_endif@@
	va_end(args);
	return result;
}

[[cp, wunused, throws, decl_include("<bits/types.h>")]]
[[preferred_largefile64_variant_of(Creat), doc_alias("Creat")]]
[[userimpl, requires_function(Open64), impl_include("<asm/os/oflags.h>")]]
$fd_t Creat64([[in]] char const *filename, $mode_t mode) {
	return Open64(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}
%#endif /* __USE_LARGEFILE64 */
%
%#ifdef __USE_ATFILE

[[cp, throws, wunused, vartypes($mode_t), decl_include("<bits/types.h>")]]
[[ignore, nocrt, alias("OpenAt"), doc_alias("OpenAt")]]
$fd_t OpenAt32([[dirfd]] $fd_t dirfd, [[in]] char const *filename, $oflag_t oflags, ...);

[[cp, throws, wunused, vartypes($mode_t), decl_include("<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>")!defined(__USE_FILE_OFFSET64) || (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("OpenAt")]]
[[if($extended_include_prefix("<features.h>", "<asm/os/oflags.h>") defined(__USE_FILE_OFFSET64) || (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)), alias("OpenAt64")]]
[[userimpl, requires($has_function(OpenAt32) || $has_function(OpenAt64)), doc_alias("openat")]]
$fd_t OpenAt([[dirfd]] $fd_t dirfd, [[in]] char const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	va_start(args, oflags);
@@pp_if $has_function(OpenAt64)@@
	result = OpenAt64(dirfd, filename, oflags, va_arg(args, mode_t));
@@pp_else@@
	result = OpenAt32(dirfd, filename, oflags, va_arg(args, mode_t));
@@pp_endif@@
	va_end(args);
	return result;
}

%#ifdef __USE_LARGEFILE64
[[cp, throws, wunused, vartypes($mode_t), decl_include("<bits/types.h>")]]
[[preferred_largefile64_variant_of(OpenAt), doc_alias("OpenAt")]]
[[userimpl, requires_function(OpenAt32), impl_include("<asm/os/oflags.h>")]]
$fd_t OpenAt64([[dirfd]] $fd_t dirfd, [[in]] char const *filename, $oflag_t oflags, ...) {
	fd_t result;
	va_list args;
	va_start(args, oflags);
@@pp_ifdef O_LARGEFILE@@
	result = OpenAt32(dirfd, filename, oflags | O_LARGEFILE, va_arg(args, mode_t));
@@pp_else@@
	result = OpenAt32(dirfd, filename, oflags, va_arg(args, mode_t));
@@pp_endif@@
	va_end(args);
	return result;
}
%#endif /* __USE_LARGEFILE64 */
%#endif /* __USE_ATFILE */
%

%{

__SYSDECL_END
#endif /* __CC__ */

}
