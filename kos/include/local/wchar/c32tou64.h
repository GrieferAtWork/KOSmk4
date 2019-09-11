/* HASH 0xcc23894c */
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
#ifndef __local_c32tou64_defined
#define __local_c32tou64_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32tou64) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32tou64))(__CHAR32_TYPE__ const *__restrict __nptr,
                                                      __CHAR32_TYPE__ **__endptr,
                                                      int __base) {
#line 853 "kos/src/libc/magic/stdlib.c"
	__UINT64_TYPE__ __result, __temp;
	if (!__base) {
		if (*__nptr == '0') {
			++__nptr;
			if (*__nptr == 'x' || *__nptr == 'X') {
				++__nptr;
				__base = 16;
			} else if (*__nptr == 'b' || *__nptr == 'B') {
				++__nptr;
				__base = 2;
			} else {
				__base = 8;
			}
		} else {
			__base = 10;
		}
	}
	__result = 0;
	for (;;) {
		__CHAR32_TYPE__ __ch = *__nptr;
		if (__ch >= '0' && __ch <= '9')
			__temp = (__UINT64_TYPE__)(__ch-'0');
		else if (__ch >= 'a' && __ch <= 'z')
			__temp = (__UINT64_TYPE__)(10+(__ch-'a'));
		else if (__ch >= 'A' && __ch <= 'Z')
			__temp = (__UINT64_TYPE__)(10+(__ch-'A'));
		else {
			break;
		}
		if (__temp >= (unsigned int)__base)
			break;
		++__nptr;
		__result *= __base;
		__result += __temp;
	}
	if (__endptr)
		*__endptr = (__CHAR32_TYPE__ *)__nptr;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32tou64_defined */
