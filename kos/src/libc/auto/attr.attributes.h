/* HASH CRC-32:0x66ae1991 */
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
#ifndef GUARD_LIBC_AUTO_ATTR_ATTRIBUTES_H
#define GUARD_LIBC_AUTO_ATTR_ATTRIBUTES_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <attr/attributes.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_DEPRECATED("Use getxattr(2) or lgetxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_get)(char const *path, char const *attrname, char *attrvalue, int *valuelength, int flags);
INTDEF ATTR_DEPRECATED("Use fgetxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_getf)(fd_t fd, char const *attrname, char *attrvalue, int *valuelength, int flags);
INTDEF ATTR_DEPRECATED("Use setxattr(2) or lsetxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_set)(char const *path, char const *attrname, char const *attrvalue, int valuelength, int flags);
INTDEF ATTR_DEPRECATED("Use fsetxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_setf)(fd_t fd, char const *attrname, char const *attrvalue, int valuelength, int flags);
INTDEF ATTR_DEPRECATED("Use removexattr(2) or lremovexattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_remove)(char const *path, char const *attrname, int flags);
INTDEF ATTR_DEPRECATED("Use fremovexattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_removef)(fd_t fd, char const *attrname, int flags);
INTDEF ATTR_DEPRECATED("Use listxattr(2) or llistxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_list)(char const *path, char *buffer, int buffersize, int flags, struct attrlist_cursor *cursor);
INTDEF ATTR_DEPRECATED("Use flistxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_listf)(fd_t fd, char *buffer, int buffersize, int flags, struct attrlist_cursor *cursor);
INTDEF ATTR_DEPRECATED("Use getxattr(2), setxattr(2), removexattr(2) and listxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_multi)(char const *path, struct attr_multiop *oplist, int count, int flags);
INTDEF ATTR_DEPRECATED("Use getxattr(2), setxattr(2), removexattr(2) and listxattr(2) instead") int NOTHROW_NCX(LIBDCALL libd_attr_multif)(fd_t fd, struct attr_multiop *oplist, int count, int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_ATTR_ATTRIBUTES_H */
