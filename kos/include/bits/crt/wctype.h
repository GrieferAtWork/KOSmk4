/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_WCTYPE_H
#define _BITS_CRT_WCTYPE_H 1

#include <__crt.h>
#include <hybrid/typecore.h>

#ifdef __CRT_DOS_PRIMARY
#define __SIZEOF_WCTYPE_T__  2
#define __SIZEOF_WCTRANS_T__ 2
#else /* __CRT_DOS_PRIMARY */
#define __SIZEOF_WCTYPE_T__  __SIZEOF_POINTER__
#define __SIZEOF_WCTRANS_T__ __SIZEOF_POINTER__
#endif /* !__CRT_DOS_PRIMARY */

#ifdef __CC__
__DECL_BEGIN

#ifdef __CRT_DOS_PRIMARY
typedef __UINT16_TYPE__ __wctype_t;
typedef __WCHAR16_TYPE__ __wctrans_t;
#else /* __CRT_DOS_PRIMARY */
typedef __ULONGPTR_TYPE__ __wctype_t;
typedef __int32_t const *__wctrans_t;
#endif /* !__CRT_DOS_PRIMARY */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_WCTYPE_H */
