/* HASH CRC-32:0xfdd0a18b */
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
#ifndef __local_getsubopt_defined
#define __local_getsubopt_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memcmp from string */
#ifndef __local___localdep_memcmp_defined
#define __local___localdep_memcmp_defined 1
#ifdef __CRT_HAVE_memcmp
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),memcmp,(__s1,__s2,__n_bytes))
#elif defined(__CRT_HAVE_bcmp)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_memcmp,(void const *__s1, void const *__s2, __SIZE_TYPE__ __n_bytes),bcmp,(__s1,__s2,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmp.h>
__NAMESPACE_LOCAL_BEGIN
/* >> memcmp(3)
 * Compare memory buffers and return the difference of the first non-matching byte
 * @return:  < 0: `s1...+=n_bytes'  < `s2...+=n_bytes'
 * @return: == 0: `s1...+=n_bytes' == `s2...+=n_bytes'
 * @return:  > 0: `s1...+=n_bytes'  > `s2...+=n_bytes' */
#define __localdep_memcmp __LIBC_LOCAL_NAME(memcmp)
#endif /* !... */
#endif /* !__local___localdep_memcmp_defined */
/* Dependency: strchr from string */
#ifndef __local___localdep_strchr_defined
#define __local___localdep_strchr_defined 1
#if __has_builtin(__builtin_strchr) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strchr)
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,{ return __builtin_strchr(__haystack, __needle); })
#elif defined(__CRT_HAVE_strchr)
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchr,(char const *__restrict __haystack, int __needle),strchr,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strchr.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strchr(3)
 * Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strchr __LIBC_LOCAL_NAME(strchr)
#endif /* !... */
#endif /* !__local___localdep_strchr_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strlen(3)
 * Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(getsubopt) __ATTR_WUNUSED __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getsubopt))(char **__restrict __optionp, char *const *__restrict __tokens, char **__restrict __valuep) {
	unsigned int __i;
	char *__option, *__nextopt;
	__SIZE_TYPE__ __option_len;
	__option  = *__optionp;
	*__valuep = __NULLPTR;
	/* Find the next option */
	__nextopt = __localdep_strchr(__option, ',');
	if (__nextopt) {
		__option_len = (__SIZE_TYPE__)(__nextopt - __option);
		*__nextopt++ = '\0';
	} else {
		__option_len = __localdep_strlen(__option);
		__nextopt = __option + __option_len;
	}
	*__optionp = __nextopt;
	for (__i = 0; __tokens[__i]; ++__i) {
		__SIZE_TYPE__ __toklen = __localdep_strlen(__tokens[__i]);
		/* Check if this token is matches the found option */
		if (__localdep_memcmp(__tokens[__i], __option, __toklen * sizeof(char)) != 0)
			continue;
		/* Deal with a potential option value. */
		if (__option[__toklen] == '=') {
			*__valuep = __option + __toklen + 1;
		} else {
			/* Make sure that the option doesn't keep on going */
			if (__option[__toklen] != 0)
				continue;
		}
		return (int)__i;
	}
	/* Not found (return the whole `name[=value]' string) */
	*__valuep = __option;
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getsubopt_defined
#define __local___localdep_getsubopt_defined 1
#define __localdep_getsubopt __LIBC_LOCAL_NAME(getsubopt)
#endif /* !__local___localdep_getsubopt_defined */
#endif /* !__local_getsubopt_defined */
