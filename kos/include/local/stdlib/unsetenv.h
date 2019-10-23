/* HASH CRC-32:0x186d8b6c */
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
#ifndef __local_unsetenv_defined
#if (defined(__CRT_HAVE_putenv) || defined(__CRT_HAVE__putenv))
#define __local_unsetenv_defined 1
#ifdef __LIBC_BIND_OPTIMIZATIONS
#include <optimized/string.h>
#endif /* __LIBC_BIND_OPTIMIZATIONS */
#include <parts/malloca.h>
/* Dependency: "strlen" from "string" */
#ifndef ____localdep_strlen_defined
#define ____localdep_strlen_defined 1
#if defined(__CRT_HAVE_strlen)
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* LIBC: strlen */
#include <local/string/strlen.h>
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strlen))
#endif /* strlen... */
#endif /* !____localdep_strlen_defined */

/* Dependency: "memcpy" from "string" */
#ifndef ____localdep_memcpy_defined
#define ____localdep_memcpy_defined 1
#if defined(__fast_memcpy_defined)
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpy (__NAMESPACE_FAST_SYM __LIBC_FAST_NAME(memcpy))
#elif defined(__CRT_HAVE_memcpy)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* LIBC: memcpy */
#include <local/string/memcpy.h>
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy))
#endif /* memcpy... */
#endif /* !____localdep_memcpy_defined */

/* Dependency: "putenv" */
#ifndef ____localdep_putenv_defined
#define ____localdep_putenv_defined 1
#if defined(__CRT_HAVE_putenv)
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
#line 1343 "kos/src/libc/magic/stdlib.c"
	int __result;
	char *__copy;
	__SIZE_TYPE__ __namelen;
	if (!__varname)
		return -1;
	__namelen = __localdep_strlen(__varname);
	__copy = (char *)__malloca((__namelen + 2) * sizeof(char));
	if __unlikely(!__copy)
		return -1;
	__localdep_memcpy(__copy, __varname, __namelen * sizeof(char));
	__copy[__namelen] = '=';
	__copy[__namelen + 1] = '\0';
	__result = __localdep_putenv(__copy);
	__freea(__copy);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_putenv) || defined(__CRT_HAVE__putenv)) */
#endif /* !__local_unsetenv_defined */
