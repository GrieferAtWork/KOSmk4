/* HASH CRC-32:0xfe859634 */
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
#ifndef __local_wcscmp_defined
#define __local_wcscmp_defined 1
__NAMESPACE_LOCAL_BEGIN
/* Compare 2 strings and return the difference of the first non-matching character, or `0' if they are identical */
__LOCAL_LIBC(wcscmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcscmp))(__WCHAR_TYPE__ const *__s1,
                                                    __WCHAR_TYPE__ const *__s2) {
#line 244 "kos/src/libc/magic/string.c"
	__WCHAR_TYPE__ __c1, __c2;
	do {
		if __unlikely((__c1 = *__s1++) != (__c2 = *__s2++))
			return (int)((__WCHAR_TYPE__)__c1 - (__WCHAR_TYPE__)__c2);
	} while (__c1);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcscmp_defined */
