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
#ifndef __LOCAL_itoa_digits
#include <__crt.h>

/* >> char __LOCAL_itoa_digit(bool upper, uint8_t digit); */
#define __LOCAL_itoa_digit(upper, digit) \
	__LOCAL_itoa_digits[(digit) + (!!(upper) << 6)]

/* >> char __LOCAL_itoa_decimal(uint8_t digit);
 * Same as `__LOCAL_itoa_digit()', but weak undefined behavior when `digit >= 10' */
#define __LOCAL_itoa_decimal(digit) \
	(char)('0' + (digit))

/* >> char const __LOCAL_itoa_digits[101] =
 * >> "0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
 * >> "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // << offset from base: 64 */
#ifndef __LOCAL_itoa_digits
#ifdef _itoa_digits
#define __LOCAL_itoa_digits _itoa_digits
#elif defined(__CRT_HAVE__itoa_digits)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const __LOCAL_itoa_digits[101],__LOCAL_itoa_digits,_itoa_digits)
#define __LOCAL_itoa_digits __LOCAL_itoa_digits
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,char const _itoa_digits[101],_itoa_digits)
#define _itoa_digits        _itoa_digits
#define __LOCAL_itoa_digits _itoa_digits
#endif /* __NO_COMPILER_SREDIRECT */
#elif defined(__cplusplus) || !defined(__NO_ATTR_FORCEINLINE)
#define __LOCAL_itoa_digits __LOCAL_itoa_digits_fp()
__ATTR_FORCEINLINE __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
char const *__NOTHROW(__LOCAL_itoa_digits_fp)(void) {
	__ATTR_VISIBILITY("hidden")
	static __LOCAL_LIBC_CONST_DATA_SECTION(_itoa_digits) char const ___itoa_digits_p[101] =
	"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return ___itoa_digits_p;
}
#else /* ... */
__LOCAL_LIBC_CONST_DATA(_itoa_digits) char const _itoa_digits[101] =
"0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define _itoa_digits        _itoa_digits
#define __LOCAL_itoa_digits _itoa_digits
#endif /* !... */
#endif /* !__LOCAL_itoa_digits */


/* >> char const __LOCAL_itoa_lower_digits[37] = "0123456789abcdefghijklmnopqrstuvwxyz"; */
#ifndef __LOCAL_itoa_lower_digits
#ifdef _itoa_lower_digits
#define __LOCAL_itoa_lower_digits _itoa_lower_digits
#elif defined(__CRT_HAVE__itoa_lower_digits)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const __LOCAL_itoa_lower_digits[37],__LOCAL_itoa_lower_digits,_itoa_lower_digits)
#define __LOCAL_itoa_lower_digits __LOCAL_itoa_lower_digits
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,char const _itoa_lower_digits[37],_itoa_lower_digits)
#define _itoa_lower_digits        _itoa_lower_digits
#define __LOCAL_itoa_lower_digits _itoa_lower_digits
#endif /* __NO_COMPILER_SREDIRECT */
#else /* ... */
#define __LOCAL_itoa_lower_digits (__LOCAL_itoa_digits + 0)
#endif /* !... */
#endif /* !__LOCAL_itoa_lower_digits */

/* >> char const __LOCAL_itoa_upper_digits[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; */
#ifndef __LOCAL_itoa_upper_digits
#ifdef _itoa_upper_digits
#define __LOCAL_itoa_upper_digits _itoa_upper_digits
#elif defined(__CRT_HAVE__itoa_upper_digits)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,char const __LOCAL_itoa_upper_digits[37],__LOCAL_itoa_upper_digits,_itoa_upper_digits)
#define __LOCAL_itoa_upper_digits __LOCAL_itoa_upper_digits
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,char const _itoa_upper_digits[37],_itoa_upper_digits)
#define _itoa_upper_digits        _itoa_upper_digits
#define __LOCAL_itoa_upper_digits _itoa_upper_digits
#endif /* __NO_COMPILER_SREDIRECT */
#else /* ... */
#define __LOCAL_itoa_upper_digits (__LOCAL_itoa_digits + 64)
#endif /* !... */
#endif /* !__LOCAL_itoa_upper_digits */

#endif /* !__LOCAL_itoa_digits */
