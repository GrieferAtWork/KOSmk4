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
/*!replace_with_include <stdint.h>*/
#ifndef __uint8_t_defined
#include <hybrid/typecore.h>
#ifndef __uint8_t_defined
#define __uint8_t_defined
#ifdef __CC__
__DECL_BEGIN
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif /* __UINT64_TYPE__ */
__DECL_END
#endif /* __CC__ */
#endif /* !__uint8_t_defined */
#endif /* !__uint8_t_defined */
