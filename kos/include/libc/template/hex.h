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
#ifndef _LIBC_TEMPLATE_HEX_H
#define _LIBC_TEMPLATE_HEX_H 1

#ifndef __LOCAL__hex_value
#ifdef _hex_value
#define __LOCAL__hex_value _hex_value
#else /* _hex_value */
#include <__crt.h>
#include <hybrid/typecore.h>
#ifndef __LOCAL__hex_value
#ifdef _hex_value
#define __LOCAL__hex_value _hex_value
#elif defined(__CRT_HAVE__hex_value)
#ifndef __NO_COMPILER_SREDIRECT
__CSREDIRECT2(,unsigned char const __LOCAL__hex_value[256],__LOCAL__hex_value,_hex_value)
#define __LOCAL__hex_value __LOCAL__hex_value
#else /* !__NO_COMPILER_SREDIRECT */
__CSDECLARE2(,unsigned char const _hex_value[256],_hex_value)
#define _hex_value         _hex_value
#define __LOCAL__hex_value _hex_value
#endif /* __NO_COMPILER_SREDIRECT */
#endif /* ... */
#endif /* !__LOCAL__hex_value */
#endif /* !_hex_value */
#endif /* !__LOCAL__hex_value */

/* >> bool __libc_hex2int(char ch, T *p_result);
 * Returns `true' if `ch' is a valid hex-character, in which case `*p_result'
 * is filled with that character's value. Else, `false' is returned, and  the
 * contents of `*p_result' are undefined.
 *
 * NOTE: Unicode decimal characters are _NOT_ supported! */
#ifdef __LOCAL__hex_value
#ifdef __NO_builtin_choose_expr
#define __libc_hex2int(ch, p_result)                                       \
	(sizeof(ch) <= __SIZEOF_CHAR__                                         \
	 ? (*(p_result) = __LOCAL__hex_value[(unsigned char)(char)(ch)]) != 99 \
	 : ((ch) <= 0xff && (*(p_result) = __LOCAL__hex_value[(unsigned char)(char)(ch)]) != 99))
#else /* __NO_builtin_choose_expr */
#define __libc_hex2int(ch, p_result)                                     \
	__builtin_choose_expr(                                               \
	sizeof(ch) <= __SIZEOF_CHAR__,                                       \
	(*(p_result) = __LOCAL__hex_value[(unsigned char)(char)(ch)]) != 99, \
	((ch) <= 0xff && (*(p_result) = __LOCAL__hex_value[(unsigned char)(char)(ch)]) != 99))
#endif /* !__NO_builtin_choose_expr */
#else /* __LOCAL__hex_value */
#define __libc_hex2int(ch, p_result)                           \
	(((ch) >= '0' && (ch) <= '9')                              \
	 ? (*(p_result) = (unsigned char)((ch) - '0'), 1)          \
	 : ((ch) >= 'A' && (ch) <= 'F')                            \
	   ? (*(p_result) = (unsigned char)(10 + (ch) - 'A'), 1)   \
	   : ((ch) >= 'a' && (ch) <= 'f')                          \
	     ? (*(p_result) = (unsigned char)(10 + (ch) - 'a'), 1) \
	     : 0)
#endif /* !__LOCAL__hex_value */


/* >> bool __libc_ishex(char ch);
 * Check if `ch' is a hex-character (0-9, A-F, a-f) */
#ifdef __LOCAL__hex_value
#ifdef __NO_builtin_choose_expr
#define __libc_ishex(ch)                                   \
	(sizeof(ch) <= __SIZEOF_CHAR__                         \
	 ? __LOCAL__hex_value[(unsigned char)(char)(ch)] != 99 \
	 : ((ch) <= 0xff && __LOCAL__hex_value[(unsigned char)(char)(ch)] != 99))
#else /* __NO_builtin_choose_expr */
#define __libc_ishex(ch)                                 \
	__builtin_choose_expr(                               \
	sizeof(ch) <= __SIZEOF_CHAR__,                       \
	__LOCAL__hex_value[(unsigned char)(char)(ch)] != 99, \
	((ch) <= 0xff && __LOCAL__hex_value[(unsigned char)(char)(ch)] != 99))
#endif /* !__NO_builtin_choose_expr */
#else /* __LOCAL__hex_value */
#define __libc_ishex(ch)             \
	(((ch) >= '0' && (ch) <= '9') || \
	 ((ch) >= 'A' && (ch) <= 'F') || \
	 ((ch) >= 'a' && (ch) <= 'f'))
#endif /* !__LOCAL__hex_value */

#endif /* !_LIBC_TEMPLATE_HEX_H */
