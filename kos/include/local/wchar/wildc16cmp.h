/* HASH CRC-32:0x70d00136 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wildc16cmp_defined
#define __local_wildc16cmp_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wildc16cmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(wildc16cmp))(__CHAR16_TYPE__ const *__pattern,
                                                        __CHAR16_TYPE__ const *__string) {
#line 4099 "kos/src/libc/magic/string.c"
	__CHAR16_TYPE__ __card_post;
	for (;;) {
		if (!*__string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*__pattern == '*')
				++__pattern;
			return -(int)(__CHAR16_TYPE__)*__pattern;
		}
		if (!*__pattern)
			return (int)(__CHAR16_TYPE__)*__string; /* Pattern end doesn't match */
		if (*__pattern == '*') {
			/* Skip stars */
			do {
				++__pattern;
			} while (*__pattern == '*');
			if ((__card_post = *__pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (__card_post == '?')
				goto __next; /* Match any --> already found */
			for (;;) {
				__CHAR16_TYPE__ __ch = *__string++;
				if (__ch == __card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!__LIBC_LOCAL_NAME(wildc16cmp)(__string, __pattern))
						return 0;
				} else if (!__ch) {
					return -(int)(__CHAR16_TYPE__)__card_post; /* Wildcard suffix not found */
				}
			}
		}
		if (*__pattern == *__string || *__pattern == '?') {
__next:
			++__string;
			++__pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((__CHAR16_TYPE__)*__string - (__CHAR16_TYPE__)*__pattern);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wildc16cmp_defined */
