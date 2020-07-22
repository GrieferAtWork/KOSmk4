/* HASH CRC-32:0xbfd2397a */
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
#ifndef __local_strftime_defined
#define __local_strftime_defined 1
#include <__crt.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: crt_strftime_l from time */
#ifndef __local___localdep_crt_strftime_l_defined
#define __local___localdep_crt_strftime_l_defined 1
#ifdef __CRT_HAVE_strftime_l
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_crt_strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE__strftime_l)
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_crt_strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),_strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#elif defined(__CRT_HAVE___strftime_l)
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_crt_strftime_l,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale),__strftime_l,(__buf,__bufsize,__format,__tp,__locale))
#else /* ... */
#undef __local___localdep_crt_strftime_l_defined
#endif /* !... */
#endif /* !__local___localdep_crt_strftime_l_defined */
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__LOCAL_LIBC(strftime) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strftime))(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp) {








#if defined(__CRT_HAVE_strftime_l) || defined(__CRT_HAVE__strftime_l) || defined(__CRT_HAVE___strftime_l)
	return __localdep_crt_strftime_l(__buf, __bufsize, __format, __tp, __NULLPTR);
#else /* __CRT_HAVE_strftime_l || __CRT_HAVE__strftime_l || __CRT_HAVE___strftime_l */
	/* TODO */
	(void)__buf;
	(void)__bufsize;
	(void)__format;
	(void)__tp;
	__COMPILER_IMPURE();
	return 0;
#endif /* !__CRT_HAVE_strftime_l && !__CRT_HAVE__strftime_l && !__CRT_HAVE___strftime_l */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strftime_defined
#define __local___localdep_strftime_defined 1
#define __localdep_strftime __LIBC_LOCAL_NAME(strftime)
#endif /* !__local___localdep_strftime_defined */
#endif /* !__local_strftime_defined */
