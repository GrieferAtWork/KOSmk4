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
#ifndef _ASM_CRT_MALLOC_H
#define _ASM_CRT_MALLOC_H 1

#include <__stdinc.h>
#include <__crt.h>

#if defined(__CRT_KOS) || defined(__CRT_GLC)
/* malloc behavior attributes. */
#ifndef __clang_tidy__
#define __MALLOC_ZERO_IS_NONNULL  1
#define __REALLOC_ZERO_IS_NONNULL 1
#endif /* !__clang_tidy__ */

#define __M_TRIM_THRESHOLD     (-1)
#define __M_GRANULARITY        (-2)
#define __M_MMAP_THRESHOLD     (-3)
#endif /* __CRT_KOS || __CRT_GLC */

#endif /* !_ASM_CRT_MALLOC_H */
