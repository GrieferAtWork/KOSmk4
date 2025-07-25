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
/* (#) Portability: MSVC         (/include/minmax.h) */
/* (#) Portability: MinGW        (/mingw-w64-headers/include/minmax.h) */
/* (#) Portability: Windows Kits (/ucrt/minmax.h) */
#ifndef _MINMAX_H
#define _MINMAX_H 1

#include "__stdinc.h"
#include <hybrid/__minmax.h>

#ifndef min
#define min(a, b) __hybrid_min2(a, b)
#define max(a, b) __hybrid_max2(a, b)
#endif /* !min */

#endif /* !_MINMAX_H */
