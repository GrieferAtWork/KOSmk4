/* HASH CRC-32:0x456b4a46 */
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
#ifndef __local_strtou64_r_defined
#define __local_strtou64_r_defined 1
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: isspace from ctype */
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined 1
#if __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#endif /* !__local___localdep_isspace_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/errno.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strto32_r(3), strtou32_r(3), strto64_r(3), strtou64_r(3)
 * Safely parse & return an integer from `nptr', and store any potential
 * errors in `*error' (if non-NULL). The following errors are defined:
 *  - 0:         Success
 *  - ECANCELED: Nothing was parsed.
 *               In this case, `*endptr' is set to the original `nptr'
 *               (iow: leading spaces are _not_ skipped in `*endptr'),
 *               and the returned integer is `0'
 *  - ERANGE:    Integer over- or under-flow while parsing.
 *               In this case, `*endptr' is still updated correctly, and
 *               the returned integer is the closest representable value
 *               to the integer given in `nptr' (i.e. `U?INTn_(MIN|MAX)')
 *               This error supercedes `EINVAL' if both conditions apply.
 *  - EINVAL:    Only when `endptr == NULL': The parsed number is followed
 *               by at least 1 additional non-whitespace character.
 *               The returned integer value is not affected by this error. */
__LOCAL_LIBC(strtou64_r) __ATTR_LEAF __ATTR_NONNULL((1)) __UINT64_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strtou64_r))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) {
	__UINT64_TYPE__ __result;
	char const *__num_start = __nptr;
	char const *__num_iter;
	while (__localdep_isspace(*__num_start))
		++__num_start;
	if (__base == 0) {
		/* Automatically deduce base. */
		if (*__num_start == '0') {
			++__num_start;
			if (*__num_start == 'x' || *__num_start == 'X') {
				__base = 16;
				++__num_start;
			} else if (*__num_start == 'b' || *__num_start == 'B') {
				__base = 2;
				++__num_start;
			} else {
				__base = 8;
				/* Don't  consume the `0',  but handle it implicitly.
				 * That way, we can just always check that the number
				 * part of the integer is non-empty! */
			}
		} else {
			__base = 10;
		}
	}
	__num_iter = __num_start;
	__result   = 0;
	for (;;) {
		__UINT8_TYPE__ __digit;
		char __ch = *__num_iter;
		if (__ch >= '0' && __ch <= '9')
			__digit = __ch - '0';
		else if (__ch >= 'a' && __ch <= 'z')
			__digit = 10 + (__ch - 'a');
		else if (__ch >= 'A' && __ch <= 'Z')
			__digit = 10 + (__ch - 'A');
		else {
			break;
		}
		if (__digit >= __base)
			break;
		++__num_iter;
		if __unlikely(__hybrid_overflow_umul(__result, (unsigned int)__base, &__result) ||
		            __hybrid_overflow_uadd(__result, __digit, &__result)) {
			/* Integer overflow. */
			if (__error) {
#ifdef __ERANGE
				*__error = __ERANGE;
#else /* __ERANGE */
				*__error = 1;
#endif /* !__ERANGE */
			}
			if (__endptr) {
				for (;;) {
					__ch = *__num_iter;
					if (__ch >= '0' && __ch <= '9')
						__digit = __ch - '0';
					else if (__ch >= 'a' && __ch <= 'z')
						__digit = 10 + (__ch - 'a');
					else if (__ch >= 'A' && __ch <= 'Z')
						__digit = 10 + (__ch - 'A');
					else {
						break;
					}
					if (__digit >= __base)
						break;
					++__num_iter;
				}
				*__endptr = (char *)__num_iter;
			}
			return (__UINT64_TYPE__)-1;
		}
	}
	if __unlikely(__num_iter == __num_start) {
		/* Empty number... */
		if (__error) {
#ifdef __ECANCELED
			*__error = __ECANCELED;
#else /* __ECANCELED */
			*__error = 1;
#endif /* !__ECANCELED */
		}
		/* Set endptr to the original `nptr' (_before_ leading spaces were skipped) */
		if (__endptr)
			*__endptr = (char *)__nptr;
	} else {
		if (__endptr) {
			*__endptr = (char *)__num_iter;
			if (__error)
				*__error = 0;
		} else if (__error) {
			*__error = 0;
			/* Check for `EINVAL' */
			if __unlikely(*__num_iter) {
				while (__localdep_isspace(*__num_iter))
					++__num_iter;
				if (*__num_iter) {
#ifdef __EINVAL
					*__error = __EINVAL;
#else /* __EINVAL */
					*__error = 1;
#endif /* !__EINVAL */
				}
			}
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strtou64_r_defined
#define __local___localdep_strtou64_r_defined 1
#define __localdep_strtou64_r __LIBC_LOCAL_NAME(strtou64_r)
#endif /* !__local___localdep_strtou64_r_defined */
#endif /* !__local_strtou64_r_defined */
