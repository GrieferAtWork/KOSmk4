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
#ifndef __LOCAL__hex_value
#ifdef _hex_value
#define __LOCAL__hex_value _hex_value
#else /* _hex_value */
#include <__crt.h>
#include <hybrid/typecore.h>
#ifdef _hex_value
#define __LOCAL__hex_value _hex_value
#else /* _hex_value */
#ifdef __CRT_HAVE__hex_value
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,unsigned char const __LOCAL__hex_value[256],__LOCAL__hex_value,_hex_value)
#define __LOCAL__hex_value __LOCAL__hex_value
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,unsigned char const _hex_value[256],_hex_value)
#define _hex_value         _hex_value
#define __LOCAL__hex_value _hex_value
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__cplusplus) || !defined(__NO_ATTR_FORCEINLINE)
#define __LOCAL__hex_value (__LOCAL__hex_value_p())
__ATTR_FORCEINLINE __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
unsigned char const *(__LOCAL__hex_value_p)(void) {
	__ATTR_VISIBILITY("hidden")
	static __LOCAL_LIBC_CONST_DATA_SECTION(_hex_value)
	unsigned char const ___hex_value_p[256] =
#include "_hex-values.h"
	;
	return ___hex_value_p;
}
#else /* ... */
#define __LOCAL__hex_value _hex_value
__LOCAL_LIBC_CONST_DATA(_hex_value)
unsigned char const _hex_value[256] =
#include "_hex-values.h"
;
#endif /* !... */
#endif /* !_hex_value */
#endif /* !_hex_value */
#endif /* !__LOCAL__hex_value */
