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
#ifndef _ASM_CRT_LOCALE_H
#define _ASM_CRT_LOCALE_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __CRT_DOS_PRIMARY
#define __LC_ALL      0
#define __LC_COLLATE  1
#define __LC_CTYPE    2
#define __LC_MONETARY 3
#define __LC_NUMERIC  4
#define __LC_TIME     5
#else /* __CRT_DOS_PRIMARY */
#define __LC_CTYPE          0
#define __LC_NUMERIC        1
#define __LC_TIME           2
#define __LC_COLLATE        3
#define __LC_MONETARY       4
#define __LC_MESSAGES       5
#define __LC_ALL            6
#define __LC_PAPER          7
#define __LC_NAME           8
#define __LC_ADDRESS        9
#define __LC_TELEPHONE      10
#define __LC_MEASUREMENT    11
#define __LC_IDENTIFICATION 12
#endif /* !__CRT_DOS_PRIMARY */

#endif /* !_ASM_CRT_LOCALE_H */
