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
/*!included_by <glob.h>*/
#ifndef _ASM_CRT_GLOB_H
#define _ASM_CRT_GLOB_H 1

#include <__stdinc.h>

/* Flags accepted by the `flags' argument of `glob(3)' */
#define __GLOB_ERR         0x0001 /* ??? */
#define __GLOB_MARK        0x0002 /* ??? */
#define __GLOB_NOSORT      0x0004 /* ??? */
#define __GLOB_DOOFFS      0x0008 /* ??? */
#define __GLOB_NOCHECK     0x0010 /* ??? */
#define __GLOB_APPEND      0x0020 /* ??? */
#define __GLOB_NOESCAPE    0x0040 /* ??? */
#define __GLOB_PERIOD      0x0080 /* ??? */
#define __GLOB_MAGCHAR     0x0100 /* ??? */
#define __GLOB_ALTDIRFUNC  0x0200 /* ??? */
#define __GLOB_BRACE       0x0400 /* ??? */
#define __GLOB_NOMAGIC     0x0800 /* ??? */
#define __GLOB_TILDE       0x1000 /* ??? */
#define __GLOB_ONLYDIR     0x2000 /* ??? */
#define __GLOB_TILDE_CHECK 0x4000 /* ??? */

/* Returns values for `glob(3)' */
#define __GLOB_NOSPACE 1 /* ??? */
#define __GLOB_ABORTED 2 /* ??? */
#define __GLOB_NOMATCH 3 /* ??? */
#define __GLOB_NOSYS   4 /* ??? */

#endif /* !_ASM_CRT_GLOB_H */
