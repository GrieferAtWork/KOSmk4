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
/* (#) Portability: DragonFly BSD (/sys/sys/_iovec.h) */
/* (#) Portability: FreeBSD       (/sys/sys/_iovec.h) */
#ifndef _SYS__IOVEC_H
#define _SYS__IOVEC_H 1

#include <__stdinc.h>
#include <sys/_types.h>
#include <bits/os/iovec.h>

#ifndef __size_t_defined
#include <hybrid/typecore.h>
#ifndef __size_t_defined
#define __size_t_defined
#ifdef __CC__
__DECL_BEGIN
typedef __SIZE_TYPE__ size_t;
__DECL_END
#endif /* __CC__ */
#endif /* !__size_t_defined */
#endif /* !__size_t_defined */

#endif /* !_SYS__IOVEC_H */
