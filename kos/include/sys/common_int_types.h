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
/* (#) Portability: NetBSD (/sys/sys/common_int_types.h) */
#ifndef _SYS_COMMON_INT_TYPES_H
#define _SYS_COMMON_INT_TYPES_H 1

#include <__stdinc.h>

/* Only (really) need:
 * >> #define __int8_t    __INT8_TYPE__
 * >> #define __int16_t   __INT16_TYPE__
 * >> #define __int32_t   __INT32_TYPE__
 * >> #define __uint8_t   __UINT8_TYPE__
 * >> #define __uint16_t  __UINT16_TYPE__
 * >> #define __uint32_t  __UINT32_TYPE__
 * >> #define __intptr_t  __INTPTR_TYPE__
 * >> #define __uintptr_t __UINTPTR_TYPE__
 * >> #ifdef __UINT64_TYPE__
 * >> #define __int64_t   __INT64_TYPE__
 * >> #define __uint64_t  __UINT64_TYPE__
 * >> #endif
 */
#include <bits/types.h>

#endif /* !_SYS_COMMON_INT_TYPES_H */
