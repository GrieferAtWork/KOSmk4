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
#ifndef _BITS_OS_GENERIC_SOCKADDR_COMMON_H
#define _BITS_OS_GENERIC_SOCKADDR_COMMON_H 1

#include <__stdinc.h>

#include <bits/types.h>

#define __SOCKADDR_COMMON(sa_prefix) \
	__sa_family_t sa_prefix##family
#define __SOCKADDR_COMMON_SIZE    __SIZEOF_SA_FAMILY_T__
#define __SOCKADDR_COMMON_ALIGN   __ALIGNOF_SA_FAMILY_T__
#define __SIZEOF_SOCKADDR_STORAGE 128

#endif /* !_BITS_OS_GENERIC_SOCKADDR_COMMON_H */
