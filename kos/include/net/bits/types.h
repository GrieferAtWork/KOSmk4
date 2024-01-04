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
#ifndef _NET_BITS_TYPES_H
#define _NET_BITS_TYPES_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __USE_KOS_ALTERATIONS
typedef __be16 __u_net16_t;
typedef __be32 __u_net32_t;
#ifdef __UINT64_TYPE__
typedef __be64 __u_net64_t;
#endif /* __UINT64_TYPE__ */
#else /* __USE_KOS_ALTERATIONS */
typedef __UINT16_TYPE__ __u_net16_t;
typedef __UINT32_TYPE__ __u_net32_t;
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ __u_net64_t;
#endif /* __UINT64_TYPE__ */
#endif /* !__USE_KOS_ALTERATIONS */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NET_BITS_TYPES_H */
