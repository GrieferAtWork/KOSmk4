/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_LOCALE_H
#define _BITS_CRT_LOCALE_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

struct __locale_struct {
#ifdef __CRT_GLC
#undef __locales
#undef __ctype_b
#undef __ctype_tolower
#undef __ctype_toupper
#undef __names
	struct __locale_data  *__locales[13]; /* 13 = __LC_LAST. */
	__UINT16_TYPE__ const *__ctype_b;
	__INT32_TYPE__ const  *__ctype_tolower;
	__INT32_TYPE__ const  *__ctype_toupper;
	char const            *__names[13];
#else /* __CRT_GLC */
	int __placeholder;
#endif /* !__CRT_GLC */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_LOCALE_H */
