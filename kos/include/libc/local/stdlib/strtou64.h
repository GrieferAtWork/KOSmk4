/* HASH CRC-32:0xae95e7e9 */
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
#ifndef __local_strtou64_defined
#define __local_strtou64_defined 1
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
#include <libc/errno.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32(3), strto64(3), strtou32(3), strtou64(3)
 * Convert a string (radix=`base') from `nptr' into an integer,
 * and store a pointer to the end of the number in `*endptr'.
 * If `errno(3)' support is available, integer overflow is handled
 * by setting `errno=ERANGE', and returning the greatest or lowest
 * valid integer (`U?INTn_(MIN|MAX))'. (though note that
 * `endptr' (if non-NULL) is still updated in this case!)
 * Upon success, `errno' is left unchanged, and the integer repr
 * of the parsed number is returned. When no integer was parsed,
 * then `0' is returned, `*endptr' is set to `nptr', but `errno'
 * will not have been modified.
 * @return: * :         Success: The parsed integer
 * @return: 0 :         [*endptr=nptr] error: Nothing was parsed
 * @return: INTn_MIN:   [errno=ERANGE] error: Value to low to represent
 * @return: U?INTn_MAX: [errno=ERANGE] error: Value to great to represent */
__LOCAL_LIBC(strtou64) __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtou64))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base) {
	__UINT64_TYPE__ __result, __temp;
	/* TODO: STDC says that we should skip leading space characters! */
	if (!__base) {
		if (*__nptr == '0') {
			char __ch = *++__nptr;
			if (__ch == 'x' || __ch == 'X') {
				++__nptr;
				__base = 16;
				/* TODO: Require that at least 1 more character be read! */
			} else if (__ch == 'b' || __ch == 'B') {
				++__nptr;
				__base = 2;
				/* TODO: Require that at least 1 more character be read! */
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

		/* Check for overflow when we have a non-noop __libc_seterrno(ERANGE) */
#if defined(__libc_geterrno) && defined(__ERANGE)
		if (__hybrid_overflow_umul(__result, (unsigned int)__base, &__result) ||
		    __hybrid_overflow_uadd(__result, __temp, &__result))
			__libc_seterrno(__ERANGE);
#else /* __libc_geterrno && __ERANGE */
		__result *= (unsigned int)__base;
		__result += __temp;
#endif /* !__libc_geterrno || !__ERANGE */
	}
	if (__endptr)
		*__endptr = (char *)__nptr;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtou64_defined
#define __local___localdep_strtou64_defined 1
#define __localdep_strtou64 __LIBC_LOCAL_NAME(strtou64)
#endif /* !__local___localdep_strtou64_defined */
#endif /* !__local_strtou64_defined */
