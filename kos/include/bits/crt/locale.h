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
#ifndef _BITS_CRT_LOCALE_H
#define _BITS_CRT_LOCALE_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __CRT_GLC
struct __locale_struct {
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
};
#elif defined(__CRT_DOS)
struct __crt_locale_data;
struct __crt_multibyte_data;
struct __locale_struct {
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("locinfo")
#pragma push_macro("mbcinfo")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef locinfo
#undef mbcinfo
	struct __crt_locale_data    *locinfo;
	struct __crt_multibyte_data *mbcinfo;
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("mbcinfo")
#pragma pop_macro("locinfo")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
};
#else /* ... */
struct __locale_struct {
	int __placeholder;
};
#endif /* !... */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_LOCALE_H */
