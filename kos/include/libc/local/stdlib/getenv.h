/* HASH CRC-32:0x478c4b2e */
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
#ifndef __local_getenv_defined
#define __local_getenv_defined
#include <__crt.h>
#include <libc/template/environ.h>
#ifdef __LOCAL_environ
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined
#ifdef __CRT_HAVE_memcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE___gcc_bcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_INS(1, 3) __ATTR_INS(2, 3) __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),__gcc_bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#ifndef __OPTIMIZE_SIZE__
#include <hybrid/__unaligned.h>
#endif /* !__OPTIMIZE_SIZE__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getenv) __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getenv))(char const *__varname) {
	char *__result, **___envp;
	if __unlikely(!__varname)
		return __NULLPTR;
	___envp = __LOCAL_environ;
	if __unlikely(!___envp)
		__result = __NULLPTR;
	else {
		__SIZE_TYPE__ __namelen = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__varname);
#ifdef __OPTIMIZE_SIZE__
		for (; (__result = *___envp) != __NULLPTR; ++___envp) {
			if ((__NAMESPACE_LOCAL_SYM __localdep_memcmp)(__result, __varname, __namelen * sizeof(char)) != 0)
				continue;
			if (__result[__namelen] != '=')
				continue;
			__result += __namelen + 1;
			break;
		}
#else /* __OPTIMIZE_SIZE__ */
		union {
			__UINT16_TYPE__      __word;
			unsigned char __chr[2];
		} __pattern;

		/* Following the assumption that no environment variable string
		 * (should)  ever consist of an empty string, we can infer that
		 * all  variable strings  should consist  of at  least 2 bytes,
		 * namely the first character of the name, followed by at least
		 * the terminating NUL character.
		 *
		 * As such, when walking the  table of strings, we can  speed
		 * up operation via an initial dismissal check that  compares
		 * the first 2 characters from the environ-string against the
		 * expected pattern based on the caller's `varname'.
		 *
		 * As far as portability goes, gLibc makes the same assumption. */
		if __unlikely(!__namelen) {
			__result = __NULLPTR;
		} else {
			__pattern.__word = __hybrid_unaligned_get16((__UINT16_TYPE__ const *)__varname);
			if __unlikely(__namelen == 1) {
				/* Single-character variable name -> Only need to search for
				 * that specific character,  as well as  the follow-up  '='! */
				__pattern.__chr[1] = '=';
				for (; (__result = *___envp) != __NULLPTR; ++___envp) {
					if (__hybrid_unaligned_get16((__UINT16_TYPE__ const *)__result) != __pattern.__word)
						continue;
					__result += 2;
					break;
				}
			} else {
				__SIZE_TYPE__ __tail_namelen;
				__varname += 2;
				__tail_namelen = __namelen - 2;
				for (; (__result = *___envp) != __NULLPTR; ++___envp) {
					if (__hybrid_unaligned_get16((__UINT16_TYPE__ const *)__result) != __pattern.__word)
						continue; /* First 2 characters don't match. */
					if ((__NAMESPACE_LOCAL_SYM __localdep_memcmp)(__result + 2, __varname, __tail_namelen * sizeof(char)) != 0)
						continue; /* Rest of string didn't match */
					if (__result[__namelen] != '=')
						continue; /* It's not the complete string. */
					__result += __namelen + 1;
					break;
				}
			}
		}
#endif /* !__OPTIMIZE_SIZE__ */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#endif /* !__local___localdep_getenv_defined */
#else /* __LOCAL_environ */
#undef __local_getenv_defined
#endif /* !__LOCAL_environ */
#endif /* !__local_getenv_defined */
