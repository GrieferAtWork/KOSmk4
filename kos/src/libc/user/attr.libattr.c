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
#ifndef GUARD_LIBC_USER_ATTR_LIBATTR_C
#define GUARD_LIBC_USER_ATTR_LIBATTR_C 1

#include "../api.h"
/**/

#include "attr.libattr.h"

DECL_BEGIN

/*[[[head:libc_attr_copy_file,hash:CRC-32=0xd8e75a25]]]*/
/* >> attr_copy_file(3)
 * Copy attributes from `src_path' to `dst_path'. Only attributes for which `check()'
 * returns  non-zero (if  not given,  `attr_copy_check_permissions' is  used) will be
 * copied.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_IN(1) ATTR_IN(2) ATTR_INOUT_OPT(4) int
NOTHROW_NCX(LIBCCALL libc_attr_copy_file)(char const *src_path,
                                          char const *dst_path,
                                          int (LIBKCALL *check)(char const *, struct error_context *),
                                          struct error_context *ctx)
/*[[[body:libc_attr_copy_file]]]*/
/*AUTO*/{
	(void)src_path;
	(void)dst_path;
	(void)check;
	(void)ctx;
	CRT_UNIMPLEMENTEDF("attr_copy_file(src_path: %q, dst_path: %q, check: %p, ctx: %p)", src_path, dst_path, check, ctx); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_copy_file]]]*/

/*[[[head:libc_attr_copy_fd,hash:CRC-32=0xc5ac150b]]]*/
/* >> attr_copy_fd(3)
 * Copy attributes from `src_fd' to `dst_fd'. Only attributes for which `check()'
 * returns non-zero (if not given, `attr_copy_check_permissions' is used) will be
 * copied.
 * @param: src_path: The name of `src_fd' (only used for error messages)
 * @param: dst_path: The name of `dst_fd' (only used for error messages)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
INTERN ATTR_SECTION(".text.crt.libattr") ATTR_INOUT_OPT(6) ATTR_IN_OPT(1) ATTR_IN_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_attr_copy_fd)(char const *src_path,
                                        fd_t src_fd,
                                        char const *dst_path,
                                        fd_t dst_fd,
                                        int (LIBKCALL *check)(char const *, struct error_context *),
                                        struct error_context *ctx)
/*[[[body:libc_attr_copy_fd]]]*/
/*AUTO*/{
	(void)src_path;
	(void)src_fd;
	(void)dst_path;
	(void)dst_fd;
	(void)check;
	(void)ctx;
	CRT_UNIMPLEMENTEDF("attr_copy_fd(src_path: %q, src_fd: %" PRIxN(__SIZEOF_FD_T__) ", dst_path: %q, dst_fd: %" PRIxN(__SIZEOF_FD_T__) ", check: %p, ctx: %p)", src_path, src_fd, dst_path, dst_fd, check, ctx); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_attr_copy_fd]]]*/



/*[[[start:exports,hash:CRC-32=0x52cbbe8f]]]*/
DEFINE_PUBLIC_ALIAS(attr_copy_file, libc_attr_copy_file);
DEFINE_PUBLIC_ALIAS(attr_copy_fd, libc_attr_copy_fd);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_ATTR_LIBATTR_C */
