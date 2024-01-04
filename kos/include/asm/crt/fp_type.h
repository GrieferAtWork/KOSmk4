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
#ifndef _ASM_FP_TYPE_H
#define _ASM_FP_TYPE_H 1

#include <__crt.h>

#ifdef __CRT_DOS_PRIMARY

#define __FP_NAN       2
#define __FP_INFINITE  1
#define __FP_ZERO      0
#define __FP_SUBNORMAL (-2)
#define __FP_NORMAL    (-1)

#else /* __CRT_DOS_PRIMARY */

#define __FP_NAN       0 /* ... */
#define __FP_INFINITE  1 /* ... */
#define __FP_ZERO      2 /* ... */
#define __FP_SUBNORMAL 3 /* ... */
#define __FP_NORMAL    4 /* ... */

#endif /* !__CRT_DOS_PRIMARY */

#endif /* !_ASM_FP_TYPE_H */
