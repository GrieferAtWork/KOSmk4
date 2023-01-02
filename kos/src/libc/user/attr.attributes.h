/* HASH CRC-32:0xa1e0d6fc */
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
#ifndef GUARD_LIBC_USER_ATTR_ATTRIBUTES_H
#define GUARD_LIBC_USER_ATTR_ATTRIBUTES_H 1

#include "../api.h"
#include "../auto/attr.attributes.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <attr/attributes.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> attr_get(3), attr_getf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(4) int NOTHROW_NCX(LIBCCALL libc_attr_get)(char const *path, char const *attrname, char *attrvalue, int *valuelength, int flags);
/* >> attr_get(3), attr_getf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(2) ATTR_INOUT(4) int NOTHROW_NCX(LIBCCALL libc_attr_getf)(fd_t fd, char const *attrname, char *attrvalue, int *valuelength, int flags);
/* >> attr_set(3), attr_setf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_CREATE | ATTR_REPLACE | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_IN(2) ATTR_INS(3, 4) int NOTHROW_NCX(LIBCCALL libc_attr_set)(char const *path, char const *attrname, char const *attrvalue, int valuelength, int flags);
/* >> attr_set(3), attr_setf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_CREATE | ATTR_REPLACE | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(2) ATTR_INS(3, 4) int NOTHROW_NCX(LIBCCALL libc_attr_setf)(fd_t fd, char const *attrname, char const *attrvalue, int valuelength, int flags);
/* >> attr_remove(3), attr_removef(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_attr_remove)(char const *path, char const *attrname, int flags);
/* >> attr_remove(3), attr_removef(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(2) int NOTHROW_NCX(LIBCCALL libc_attr_removef)(fd_t fd, char const *attrname, int flags);
/* >> attr_list(3), attr_listf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_IN(1) ATTR_INOUT(5) ATTR_OUTS(2, 3) int NOTHROW_NCX(LIBCCALL libc_attr_list)(char const *path, char *buffer, int buffersize, int flags, struct attrlist_cursor *cursor);
/* >> attr_list(3), attr_listf(3)
 * @param: flags: Set of `0 | ATTR_DONTFOLLOW | ATTR_SECURE | ATTR_ROOT'
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno') */
INTDEF ATTR_INOUT(5) ATTR_OUTS(2, 3) int NOTHROW_NCX(LIBCCALL libc_attr_listf)(fd_t fd, char *buffer, int buffersize, int flags, struct attrlist_cursor *cursor);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_ATTR_ATTRIBUTES_H */
