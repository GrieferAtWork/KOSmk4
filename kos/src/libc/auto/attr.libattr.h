/* HASH CRC-32:0xcf9cb2a1 */
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
#ifndef GUARD_LIBC_AUTO_ATTR_LIBATTR_H
#define GUARD_LIBC_AUTO_ATTR_LIBATTR_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <attr/libattr.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> attr_copy_check_permissions(3)
 * Returns non-zero if `attr_name' should be preserved (default handler
 * for `check' argument  of `attr_copy_file(3)' and  `attr_copy_fd(3)')
 * Same as `attr_copy_action(attr_name, ctx) == 0'
 * @return: == 0 : `attr_name' should not be copied
 * @return: != 0 : `attr_name' should be copied */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_attr_copy_check_permissions)(char const *attr_name, struct error_context *ctx);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> attr_copy_check_permissions(3)
 * Returns non-zero if `attr_name' should be preserved (default handler
 * for `check' argument  of `attr_copy_file(3)' and  `attr_copy_fd(3)')
 * Same as `attr_copy_action(attr_name, ctx) == 0'
 * @return: == 0 : `attr_name' should not be copied
 * @return: != 0 : `attr_name' should be copied */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc_attr_copy_check_permissions)(char const *attr_name, struct error_context *ctx);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> attr_copy_action(3)
 * Return the default action to-be taken for `attr_name'
 * @return: 0 : No special action
 * @return: * : One of `ATTR_ACTION_*' */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBDCALL libd_attr_copy_action)(char const *attr_name, struct error_context *ctx);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> attr_copy_action(3)
 * Return the default action to-be taken for `attr_name'
 * @return: 0 : No special action
 * @return: * : One of `ATTR_ACTION_*' */
INTDEF ATTR_IN(1) ATTR_INOUT_OPT(2) int NOTHROW_NCX(LIBCCALL libc_attr_copy_action)(char const *attr_name, struct error_context *ctx);
INTDEF ATTR_RETNONNULL WUNUSED ATTR_INOUT_OPT(1) char const *NOTHROW_NCX(LIBCCALL libc_attr_load_actions)(struct error_context *ctx);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ATTR_LIBATTR_H */
