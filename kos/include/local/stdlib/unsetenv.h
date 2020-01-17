/* HASH CRC-32:0x6f5a49bf */
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
#ifndef __local_unsetenv_defined
#if defined(__CRT_HAVE_putenv) || defined(__CRT_HAVE__putenv)
#define __local_unsetenv_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/malloca.h>
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

/* Dependency: "memcpyc" from "string" */
#ifndef ____localdep_memcpyc_defined
#define ____localdep_memcpyc_defined 1
#ifdef __fast_memcpyc_defined
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpyc))
#elif defined(__CRT_HAVE_memcpyc)
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* LIBC: memcpyc */
#include <local/string/memcpyc.h>
/* Copy memory between non-overlapping memory blocks.
 * @return: * : Always re-returns `dst' */
#define __localdep_memcpyc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpyc))
#endif /* memcpyc... */
#endif /* !____localdep_memcpyc_defined */

/* Dependency: "putenv" */
#ifndef ____localdep_putenv_defined
#define ____localdep_putenv_defined 1
#ifdef __CRT_HAVE_putenv
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_putenv,(char *__string),putenv,(__string))
#elif defined(__CRT_HAVE__putenv)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_putenv,(char *__string),_putenv,(__string))
#else /* LIBC: putenv */
#undef ____localdep_putenv_defined
#endif /* putenv... */
#endif /* !____localdep_putenv_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(unsetenv) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(unsetenv))(char const *__varname) {
#line 1508 "kos/src/libc/magic/stdlib.c"
	int __result;
	char *__copy;
	__SIZE_TYPE__ __namelen;
	if (!__varname)
		return -1;
	__namelen = __localdep_strlen(__varname);
	__copy = (char *)__malloca((__namelen + 2) * sizeof(char));
	if __unlikely(!__copy)
		return -1;
	__localdep_memcpyc(__copy, __varname, __namelen, sizeof(char));
	__copy[__namelen] = '=';
	__copy[__namelen + 1] = '\0';
	__result = __localdep_putenv(__copy);
	__freea(__copy);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_putenv || __CRT_HAVE__putenv */
#endif /* !__local_unsetenv_defined */
