/* HASH CRC-32:0xf3decaa0 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_strto32_r_defined
#define __local_strto32_r_defined
#include <__crt.h>
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isspace) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __crt_isspace(__ch); })
#elif defined(__crt_isspace)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isspace)(int __ch) { return __crt_isspace(__ch); }
#elif __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
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
#include <hybrid/limitcore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strto32_r) __ATTR_LEAF __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(4) __INT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strto32_r))(char const *__restrict __nptr, char **__endptr, __STDC_INT_AS_UINT_T __base, __errno_t *__error) {
	__INT32_TYPE__ __result;
	char __sign;
	char const *__num_start = __nptr;
	char const *__num_iter;
	while ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__num_start))
		++__num_start;
	__sign = *__num_start;
	if (__sign == '-' || __sign == '+')
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
				--__num_start;
			}
		} else {
			__base = 10;
		}
	}
	__num_iter = __num_start;
	__result   = 0;
	for (;;) {
		__UINT8_TYPE__ __digit;
		char __ch;
		__ch = *__num_iter;
		if (__ch >= '0' && __ch <= '9')
			__digit = (__UINT8_TYPE__)(__ch - '0');
		else if (__ch >= 'a' && __ch <= 'z')
			__digit = (__UINT8_TYPE__)(10 + __ch - 'a');
		else if (__ch >= 'A' && __ch <= 'Z')
			__digit = (__UINT8_TYPE__)(10 + __ch - 'A');
		else {
			break;
		}
		if (__digit >= __base)
			break;
		++__num_iter;
		if __unlikely(__hybrid_overflow_smul(__result, (unsigned int)__base, &__result) ||
		            __hybrid_overflow_sadd(__result, __digit, &__result)) {
__handle_overflow:
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
						__digit = (__UINT8_TYPE__)(__ch - '0');
					else if (__ch >= 'a' && __ch <= 'z')
						__digit = (__UINT8_TYPE__)(10 + __ch - 'a');
					else if (__ch >= 'A' && __ch <= 'Z')
						__digit = (__UINT8_TYPE__)(10 + __ch - 'A');
					else {
						break;
					}
					if (__digit >= __base)
						break;
					++__num_iter;
				}
				*__endptr = (char *)__num_iter;
			}
			if (__sign == '-')
				return __INT32_MIN__;
			return __INT32_MAX__;
		}
	}
	if (__sign == '-') {
		if (__hybrid_overflow_sneg_p2n(__result, &__result)) /* NOLINT */
			goto __handle_overflow; /* Overflow... */
	}
	if __unlikely(__num_iter == __num_start) {
		/* Check for special case: `0xGARBAGE'.
		 * -> In this case, return `0' and set `endptr' to `x' */
		if ((__base == 16 || __base == 2) && __num_start > __nptr) {
			char const *__nptr_ps = __nptr;
			while ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__nptr_ps))
				++__nptr_ps;
			if (__num_start > __nptr_ps && *__nptr_ps == '0') {
				if (__endptr)
					*__endptr = (char *)__nptr_ps + 1;
				if (__error)
					*__error = 0;
				return 0;
			}
		}

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
				while ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(*__num_iter))
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
#ifndef __local___localdep_strto32_r_defined
#define __local___localdep_strto32_r_defined
#define __localdep_strto32_r __LIBC_LOCAL_NAME(strto32_r)
#endif /* !__local___localdep_strto32_r_defined */
#endif /* !__local_strto32_r_defined */
