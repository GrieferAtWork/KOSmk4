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
/* (#) Portability: Cygwin (/newlib/libc/include/ssp/ssp.h) */
/* (#) Portability: NetBSD (/include/ssp/ssp.h) */
/* (#) Portability: Newlib (/newlib/libc/include/ssp/ssp.h) */
#ifndef _SSP_SSP_H
#define _SSP_SSP_H 1

#include <__crt.h>

#ifdef __SSP_FORTIFY_LEVEL
#if __SSP_FORTIFY_LEVEL > 1
#define __ssp_bos(ptr) __builtin_object_size(ptr, 1)
#else /* __SSP_FORTIFY_LEVEL > 1 */
#define __ssp_bos(ptr) __builtin_object_size(ptr, 0)
#endif /* __SSP_FORTIFY_LEVEL <= 1 */
#define __ssp_bos0(ptr) __builtin_object_size(ptr, 0)
#endif /* __SSP_FORTIFY_LEVEL */

#endif /* !_SSP_SSP_H */
