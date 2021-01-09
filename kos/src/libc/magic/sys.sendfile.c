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
%(c_prefix){
/* (#) Portability: GNU C Library (/io/sys/sendfile.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/sendfile.h) */
/* (#) Portability: diet libc     (/include/sys/sendfile.h) */
/* (#) Portability: musl libc     (/include/sys/sendfile.h) */
/* (#) Portability: uClibc        (/include/sys/sendfile.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(off_t = "__FS_TYPE(off)")]
%[define_replacement(off32_t = __off32_t)]
%[define_replacement(off64_t = __off64_t)]
%[default:section(".text.crt{|.dos}.fs.statfs.statfs")]

%{
#include <features.h>
#include <sys/types.h>

/* Documentation taken from GLibc /usr/include/i386-linux-gnu/sys/sendfile.h */
/* sendfile -- copy data directly from one file descriptor to another
   Copyright (C) 1998-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

__SYSDECL_BEGIN

#ifdef __CC__

};

[[decl_include("<bits/types.h>")]]
[[doc_alias("sendfile"), ignore, nocrt, alias("sendfile")]]
ssize_t sendfile32($fd_t out_fd, $fd_t in_fd,
                   [[nullable]] $off32_t *offset,
                   size_t count);


@@Send up to COUNT bytes from file associated with IN_FD starting at *OFFSET
@@to descriptor OUT_FD. Set *OFFSET to the IN_FD's file position following the
@@read bytes. If OFFSET is a null pointer, use the normal file position instead.
@@Return the number of written bytes, or -1 in case of error
[[no_crt_self_import, decl_include("<bits/types.h>")]]
[[if(defined(__USE_FILE_OFFSET64)), preferred_alias("sendfile64")]]
[[if(!defined(__USE_FILE_OFFSET64)), preferred_alias("sendfile")]]
[[userimpl, requires($has_function(sendfile32) || $has_function(sendfile64))]]
ssize_t sendfile($fd_t out_fd, $fd_t in_fd,
                 [[nullable]] off_t *offset, size_t count) {
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
[[doc_alias("sendfile"), off64_variant_of(sendfile)]]
[[userimpl, requires_function(sendfile32)]]
ssize_t sendfile64($fd_t out_fd, $fd_t in_fd,
                   [[nullable]] $off64_t *offset, size_t count) {
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
#endif /* __CC__ */

__SYSDECL_END

}
