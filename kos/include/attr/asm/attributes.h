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
#ifndef _ATTR_ASM_ATTRIBUTES_H
#define _ATTR_ASM_ATTRIBUTES_H 1

#include <__stdinc.h>

/* Max size for attribute values */
#define __ATTR_MAX_VALUELEN (64 * 1024) /* Max size for attribute values */

/* Possible values for the `flags' arguments of functions from `<attr/attributes.h>' */
#define __ATTR_DONTFOLLOW 0x0001 /* Don't follow symbolic links */
#define __ATTR_ROOT       0x0002 /* Prefix attribute names with "trusted." or "xfsroot." (else: ATTR_SECURE) */
#define __ATTR_TRUST      0x0004 /* Ignored... */
#define __ATTR_SECURE     0x0008 /* Prefix attribute names with "security." (else: prefix with "user.") */
#define __ATTR_CREATE     0x0010 /* Create new attribute, fail if attribute already exists (s.a. `XATTR_CREATE') */
#define __ATTR_REPLACE    0x0020 /* Replace existing attribute, fail if attribute doesn't already exists (s.a. `XATTR_REPLACE') */

/* Max allowed value for `attr_multi[f]::count' */
#define __ATTR_MAX_MULTIOPS 128 /* Max allowed value for `attr_multi[f]::count' */

/* Possible values for `struct attr_multiop::am_opcode' */
#define __ATTR_OP_GET    1 /* Perform a call to `attr_get(3)' or `attr_getf(3)' */
#define __ATTR_OP_SET    2 /* Perform a call to `attr_set(3)' or `attr_setf(3)' */
#define __ATTR_OP_REMOVE 3 /* Perform a call to `attr_remove(3)' or `attr_removef(3)' */

#endif /* !_ATTR_ASM_ATTRIBUTES_H */
