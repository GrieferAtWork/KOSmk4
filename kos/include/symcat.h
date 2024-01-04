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
/* (#) Portability: EMX kLIBC (/libc/include/symcat.h) */
/* (#) Portability: libiberty (/include/symcat.h) */
#ifndef _SYMCAT_H
#define _SYMCAT_H 1

#include <__stdinc.h>

#ifdef __PREPROCESSOR_HAVE_CAT
#define CONCAT2(a, b)             a##b
#define CONCAT3(a, b, c)          a##b##c
#define CONCAT4(a, b, c, d)       a##b##c##d
#define CONCAT5(a, b, c, d, e)    a##b##c##d##e
#define CONCAT6(a, b, c, d, e, f) a##b##c##d##e##f
#else /* __PREPROCESSOR_HAVE_CAT */
/* clang-format off */
#define CONCAT2(a, b)             a/**/b
#define CONCAT3(a, b, c)          a/**/b/**/c
#define CONCAT4(a, b, c, d)       a/**/b/**/c/**/d
#define CONCAT5(a, b, c, d, e)    a/**/b/**/c/**/d/**/e
#define CONCAT6(a, b, c, d, e, f) a/**/b/**/c/**/d/**/e/**/f
/* clang-format on */
#endif /* !__PREPROCESSOR_HAVE_CAT */

#define XCONCAT2(a, b)             CONCAT2(a, b)
#define XCONCAT3(a, b, c)          CONCAT3(a, b, c)
#define XCONCAT4(a, b, c, d)       CONCAT4(a, b, c, d)
#define XCONCAT5(a, b, c, d, e)    CONCAT5(a, b, c, d, e)
#define XCONCAT6(a, b, c, d, e, f) CONCAT6(a, b, c, d, e, f)

#define STRINGX __PP_PRIVATE_STR
#define XSTRING __PP_STR

#endif /* !_SYMCAT_H */
