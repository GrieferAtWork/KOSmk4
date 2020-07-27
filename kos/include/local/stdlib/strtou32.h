/* HASH CRC-32:0x38cafcb1 */
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
#ifndef __local_strtou32_defined
#define __local_strtou32_defined 1
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strtou32) __ATTR_LEAF __ATTR_NONNULL((1)) __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtou32))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) {
	__UINT32_TYPE__ __result, __temp;
	if (!__base) {
		if (*__nptr == '0') {
			char __ch = *++__nptr;
			if (__ch == 'x' || __ch == 'X') {
				++__nptr;
				__base = 16;
			} else if (__ch == 'b' || __ch == 'B') {
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
		char __ch = *__nptr;
		if (__ch >= '0' && __ch <= '9')
			__temp = (__UINT64_TYPE__)(__ch - '0');
		else if (__ch >= 'a' && __ch <= 'z')
			__temp = (__UINT64_TYPE__)10 + (__ch - 'a');
		else if (__ch >= 'A' && __ch <= 'Z')
			__temp = (__UINT64_TYPE__)10 + (__ch - 'A');
		else {
			/* TODO: Support for unicode decimals, and multi-byte characters.
			 *       But only do this if libc supports it (i.e. don't do this
			 *       in kernel-space) */
			break;
		}
		if (__temp >= (unsigned int)__base)
			break;
		++__nptr;
		/* XXX: Check for overflow when we have a non-noop __libc_seterrno(ERANGE) */
		__result *= (unsigned int)__base;
		__result += __temp;
	}
	if (__endptr)
		*__endptr = (char *)__nptr;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtou32_defined
#define __local___localdep_strtou32_defined 1
#define __localdep_strtou32 __LIBC_LOCAL_NAME(strtou32)
#endif /* !__local___localdep_strtou32_defined */
#endif /* !__local_strtou32_defined */
