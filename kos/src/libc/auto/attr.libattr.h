/* HASH CRC-32:0x4f023e3c */
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
#ifndef GUARD_LIBC_AUTO_ATTR_LIBATTR_H
#define GUARD_LIBC_AUTO_ATTR_LIBATTR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <attr/libattr.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> attr_copy_file(3)
 * Copy attributes from `src_path' to `dst_path'. Only attributes for which `check()'
 * returns  non-zero (if  not given,  `attr_copy_check_permissions' is  used) will be
 * copied.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT_OPT(4) int NOTHROW_NCX(LIBCCALL libc_attr_copy_file)(char const *src_path, char const *dst_path, int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx), struct error_context *ctx);
/* >> attr_copy_fd(3)
 * Copy attributes from `src_fd' to `dst_fd'. Only attributes for which `check()'
 * returns non-zero (if not given, `attr_copy_check_permissions' is used) will be
 * copied.
 * @param: src_path: The name of `src_fd' (only used for error messages)
 * @param: dst_path: The name of `dst_fd' (only used for error messages)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
INTDEF ATTR_INOUT_OPT(6) ATTR_IN_OPT(1) ATTR_IN_OPT(3) int NOTHROW_NCX(LIBCCALL libc_attr_copy_fd)(char const *src_path, fd_t src_fd, char const *dst_path, fd_t dst_fd, int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx), struct error_context *ctx);
INTDEF ATTR_INOUT_OPT(6) ATTR_IN_OPT(1) ATTR_IN_OPT(3) int NOTHROW_NCX(LIBCCALL libc_attr_copy_impl)(char const *src_path, fd_t src_fd, char const *dst_path, fd_t dst_fd, int (LIBKCALL *check)(char const *attr_name, struct error_context *ctx), struct error_context *ctx);
/* >> attr_copy_check_permissions(3)
 * Returns non-zero if `attr_name' should be preserved (default handler
 * for `check' argument  of `attr_copy_file(3)' and  `attr_copy_fd(3)')
 * Same as `attr_copy_action(attr_name, ctx) == 0'
 * @return: == 0 : `attr_name' should not be copied
 * @return: != 0 : `attr_name' should be copied */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc_attr_copy_check_permissions)(char const *attr_name, struct error_context *ctx);
/* >> attr_copy_action(3)
 * Return the default action to-be taken for `attr_name'
 * @return: 0 : No special action
 * @return: * : One of `ATTR_ACTION_*' */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc_attr_copy_action)(char const *attr_name, struct error_context *ctx);
INTDEF ATTR_RETNONNULL WUNUSED ATTR_INOUT_OPT(1) char const *NOTHROW_NCX(LIBCCALL libc_attr_load_actions)(struct error_context *ctx);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ATTR_LIBATTR_H */
