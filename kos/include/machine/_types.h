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
/* (#) Portability: Cygwin    (/newlib/libc/include/machine/_types.h) */
/* (#) Portability: EMX kLIBC (/libc/include/machine/_types.h) */
/* (#) Portability: Newlib    (/newlib/libc/include/machine/_types.h) */
#ifndef _MACHINE__TYPES_H
#define _MACHINE__TYPES_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <machine/_default_types.h>

__DECL_BEGIN

#ifdef __CC__

/* Many other types were already defined in <bits/types.h> */
typedef __int16_t  __dev16_t;
typedef __uint16_t __uid16_t;
typedef __uint16_t __gid16_t;
#define __machine_blkcnt_t_defined
#define __machine_blksize_t_defined
#define __machine_dev_t_defined
#define __machine_fsblkcnt_t_defined
#define __machine_fsfilcnt_t_defined
#define __machine_uid_t_defined
#define __machine_gid_t_defined
#define __machine_ino_t_defined
#define __machine_key_t_defined
#define __machine_sa_family_t_defined
#define __machine_socklen_t_defined

#endif /* __CC__ */

__DECL_END

#endif /* !_MACHINE__TYPES_H */
