/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: GNU C Library (/io/sys/sendfile.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sendfile.h) */
/* (#) Portability: diet libc     (/include/sys/sendfile.h) */
/* (#) Portability: musl libc     (/include/sys/sendfile.h) */
/* (#) Portability: uClibc        (/include/sys/sendfile.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(off_t = "__off_t")]
%[define_replacement(off32_t = __off32_t)]
%[define_replacement(off64_t = __off64_t)]
%[default:section(".text.crt{|.dos}.fs.statfs.statfs")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <hybrid/typecore.h>
)]%{

#ifdef __USE_GLIBC_BLOAT
#include <sys/types.h>
#endif /* __USE_GLIBC_BLOAT */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}

[[decl_include("<bits/types.h>")]]
[[doc_alias("sendfile"), ignore, nocrt, alias("sendfile")]]
ssize_t sendfile32([[fdwrite]] $fd_t out_fd, [[fdread]] $fd_t in_fd,
                   [[inout_opt]] $off32_t *offset,
                   size_t count);


[[decl_include("<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("sendfile")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("sendfile64")]]
[[userimpl, requires($has_function(sendfile32) || $has_function(sendfile64))]]
ssize_t sendfile([[fdwrite]] $fd_t out_fd, [[fdread]] $fd_t in_fd,
                 [[inout_opt]] $off_t *offset, size_t count) {
@@pp_if $has_function(sendfile64)@@
	ssize_t result;
	if (offset) {
		off64_t temp = *offset;
		result = sendfile64(out_fd, in_fd, &temp, count);
		*offset = (off_t)temp;
	} else {
		result = sendfile64(out_fd, in_fd, NULL, count);
	}
	return result;
@@pp_else@@
	ssize_t result;
	if (offset) {
		off32_t temp = (off32_t)*offset;
		result = sendfile32(out_fd, in_fd, &temp, count);
		*offset = (off_t)temp;
	} else {
		result = sendfile32(out_fd, in_fd, NULL, count);
	}
	return result;
@@pp_endif@@
}

%#ifdef __USE_LARGEFILE64
[[decl_include("<bits/types.h>")]]
[[preferred_off64_variant_of(sendfile), doc_alias("sendfile")]]
[[userimpl, requires_function(sendfile32)]]
ssize_t sendfile64([[fdwrite]] $fd_t out_fd, [[fdread]] $fd_t in_fd,
                   [[inout_opt]] $off64_t *offset, size_t count) {
	ssize_t result;
	if (offset) {
		off32_t temp = (off32_t)*offset;
		result = sendfile32(out_fd, in_fd, &temp, count);
		*offset = (off64_t)temp;
	} else {
		result = sendfile32(out_fd, in_fd, NULL, count);
	}
	return result;
}
%#endif /* __USE_LARGEFILE64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
