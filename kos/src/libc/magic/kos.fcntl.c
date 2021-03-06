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
%[default:section(".text.crt{|.dos}.except.io.utility")]


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <fcntl.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

}

[[decl_include("<features.h>", "<bits/types.h>")]]
[[throws, guard, vartypes(void *)]]
__STDC_INT_AS_SSIZE_T Fcntl($fd_t fd, int cmd, ...);

%[default:section(".text.crt{|.dos}.except.io.access")]

[[ignore, nocrt, alias("Open")]]
[[cp, wunused, vartypes($mode_t), throws, decl_include("<bits/types.h>")]]
$fd_t Open32([[nonnull]] char const *filename, $oflag_t oflags, ...);


[[decl_include("<bits/types.h>"), no_crt_self_import]]
[[cp, throws, guard, wunused, vartypes($mode_t)]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("Open64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("Open")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires($has_function(Open64) || (defined(__AT_FDCWD) && $has_function(OpenAt)))]]
$fd_t Open([[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
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

[[decl_include("<bits/types.h>")]]
[[cp, throws, guard, wunused, no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("Creat64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("Creat")]]
[[impl_include("<asm/os/oflags.h>"), userimpl, requires_function(Open)]]
$fd_t Creat([[nonnull]] char const *filename, $mode_t mode) {
	return Open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}

%
%#ifdef __USE_LARGEFILE64
[[cp, throws, vartypes($mode_t), decl_include("<bits/types.h>")]]
[[wunused, largefile64_variant_of(Open), impl_include("<asm/os/fcntl.h>")]]
[[userimpl, requires_include("<asm/os/fcntl.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(OpenAt64)) || $has_function(Open32))]]
$fd_t Open64([[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
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

[[cp, throws, guard, decl_include("<bits/types.h>")]]
[[wunused, largefile64_variant_of(Creat)]]
[[impl_include("<asm/os/oflags.h>"), userimpl, requires_function(Open64)]]
$fd_t Creat64([[nonnull]] char const *filename, $mode_t mode) {
	return Open64(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}
%#endif /* __USE_LARGEFILE64 */
%
%#ifdef __USE_ATFILE

[[cp, throws, wunused, vartypes($mode_t)]]
[[ignore, nocrt, alias("OpenAt")]]
[[decl_include("<bits/types.h>")]]
$fd_t OpenAt32($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...);

[[decl_include("<bits/types.h>")]]
[[cp, throws, guard, wunused, vartypes($mode_t), no_crt_self_import]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("OpenAt64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("OpenAt")]]
[[userimpl, requires($has_function(OpenAt32) || $has_function(OpenAt64))]]
$fd_t OpenAt($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
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
[[cp, throws, guard, wunused, vartypes($mode_t)]]
[[largefile64_variant_of(OpenAt), doc_alias("OpenAt")]]
[[decl_include("<bits/types.h>"), impl_include("<asm/os/oflags.h>")]]
[[userimpl, requires_function(OpenAt32)]]
$fd_t OpenAt64($fd_t dirfd, [[nonnull]] char const *filename, $oflag_t oflags, ...) {
	$fd_t result;
	va_list args;
	va_start(args, oflags);
@@pp_ifdef __O_LARGEFILE@@
	result = OpenAt32(dirfd, filename, oflags | __O_LARGEFILE, va_arg(args, mode_t));
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
