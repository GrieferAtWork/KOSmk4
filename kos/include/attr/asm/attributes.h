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
#ifndef _ATTR_ASM_ATTRIBUTES_H
#define _ATTR_ASM_ATTRIBUTES_H 1

#include <__stdinc.h>

/* ??? */
#define __ATTR_MAX_VALUELEN (64 * 1024) /* ??? */

/* ??? */
#define __ATTR_DONTFOLLOW 0x0001 /* ??? */
#define __ATTR_ROOT       0x0002 /* ??? */
#define __ATTR_TRUST      0x0004 /* ??? */
#define __ATTR_SECURE     0x0008 /* ??? */
#define __ATTR_CREATE     0x0010 /* ??? */
#define __ATTR_REPLACE    0x0020 /* ??? */

/* ??? */
#define __ATTR_MAX_MULTIOPS 128

/* ??? */
#define __ATTR_OP_GET    1 /* ??? */
#define __ATTR_OP_SET    2 /* ??? */
#define __ATTR_OP_REMOVE 3 /* ??? */

#endif /* !_ATTR_ASM_ATTRIBUTES_H */
