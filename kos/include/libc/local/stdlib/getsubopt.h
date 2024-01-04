/* HASH CRC-32:0x46d1e86a */
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
#ifndef __local_getsubopt_defined
#define __local_getsubopt_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif __has_builtin(__builtin_index) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_index)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,{ return __builtin_index(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#elif defined(__CRT_HAVE_index)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),index,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
#ifndef __local___localdep_strcmp_defined
#define __local___localdep_strcmp_defined
#if __has_builtin(__builtin_strcmp) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strcmp)
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,{ return __builtin_strcmp(__s1, __s2); })
#elif defined(__CRT_HAVE_strcmp)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_strcmp,(char const *__s1, char const *__s2),strcmp,(__s1,__s2))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strcmp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strcmp __LIBC_LOCAL_NAME(strcmp)
#endif /* !... */
#endif /* !__local___localdep_strcmp_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <libc/template/suboptarg.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getsubopt) __ATTR_WUNUSED __ATTR_IN(2) __ATTR_INOUT_OPT(1) __ATTR_OUT(3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getsubopt))(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep) {
	unsigned int __i;
	char *__option, *__nextopt, *__eq;
	*__valuep = __NULLPTR;
	if __unlikely(!__optionp)
		goto __err_noopt;
	__option = *__optionp;
	if __unlikely(!__option)
		goto __err_noopt;

	/* Skip leading whitespace and commas */
#define __GETSUBOPT_ISSPACE(__ch) ((__NAMESPACE_LOCAL_SYM __localdep_strchr)(", \t", __ch) != __NULLPTR)
	while (__GETSUBOPT_ISSPACE(*__option))
		++__option;
	if __unlikely(!*__option)
		goto __err_noopt;

	/* Save the starting pointer to the sub-option. */
#ifdef __LOCAL_suboptarg
	__LOCAL_suboptarg = __option;
#endif /* __LOCAL_suboptarg */

	/* Find the next option */
	__nextopt = __option;
	while (*__nextopt != '\0' && !__GETSUBOPT_ISSPACE(*__nextopt))
		++__nextopt;
	if (*__nextopt != '\0')
		*__nextopt++ = '\0';
	while (__GETSUBOPT_ISSPACE(*__nextopt))
		++__nextopt;
	*__optionp = __nextopt;
#undef __GETSUBOPT_ISSPACE

	/* Check if this option has a value-part */
	__eq = (__NAMESPACE_LOCAL_SYM __localdep_strchr)(__option, '=');
	if (__eq != __NULLPTR) {
		*__eq++   = '\0';
		*__valuep = __eq;
	}

	/* Find the referenced token. */
	for (__i = 0; __tokens[__i]; ++__i) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_strcmp)(__tokens[__i], __option) == 0)
			return (int)__i;
	}

	/* Not found (return the whole `name[=value]' string) */
	*__valuep = __option;
	/* Restore the '=' since we want to return the whole string */
	if (__eq != __NULLPTR)
		__eq[-1] = '=';
	return -1;
__err_noopt:
#ifdef __LOCAL_suboptarg
	__LOCAL_suboptarg = __NULLPTR;
#endif /* __LOCAL_suboptarg */
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getsubopt_defined
#define __local___localdep_getsubopt_defined
#define __localdep_getsubopt __LIBC_LOCAL_NAME(getsubopt)
#endif /* !__local___localdep_getsubopt_defined */
#endif /* !__local_getsubopt_defined */
