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
/* (#) Portability: MinGW (/include/sys/bsdtypes.h) */
#ifndef _SYS_BSDTYPES_H
#define _SYS_BSDTYPES_H 1

#include <features.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __u_char_defined
#define __u_char_defined
typedef __u_char  u_char;
typedef __u_short u_short;
typedef __u_int   u_int;
typedef __u_long  u_long;
#endif /* !__u_char_defined */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_BSDTYPES_H */
