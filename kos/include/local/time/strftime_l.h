/* HASH CRC-32:0xe4783e2e */
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
#ifndef __local_strftime_l_defined
#define __local_strftime_l_defined 1
#include <__crt.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: strftime from time */
#ifndef __local___localdep_strftime_defined
#define __local___localdep_strftime_defined 1
#if __has_builtin(__builtin_strftime) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CEIREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strftime,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),strftime,{ return __builtin_strftime(__buf, __bufsize, __format, __tp); })
#elif defined(__CRT_HAVE_strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strftime,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),strftime,(__buf,__bufsize,__format,__tp))
#elif defined(__CRT_HAVE__Strftime)
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
__CREDIRECT(__ATTR_NONNULL((1, 3, 4)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strftime,(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp),_Strftime,(__buf,__bufsize,__format,__tp))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/time/strftime.h>
__NAMESPACE_LOCAL_BEGIN
/* Format TP into S according to FORMAT.
 * Write no more than MAXSIZE characters and return the number
 * of characters written, or 0 if it would exceed MAXSIZE */
#define __localdep_strftime __LIBC_LOCAL_NAME(strftime)
#endif /* !... */
#endif /* !__local___localdep_strftime_defined */
/* Similar to `strftime' but take the information from
 * the provided locale and not the global locale */
__LOCAL_LIBC(strftime_l) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strftime_l))(char *__restrict __buf, __SIZE_TYPE__ __bufsize, char const *__restrict __format, struct __NAMESPACE_STD_SYM tm const *__restrict __tp, __locale_t __locale) {
	(void)__locale;
	return __localdep_strftime(__buf, __bufsize, __format, __tp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strftime_l_defined
#define __local___localdep_strftime_l_defined 1
#define __localdep_strftime_l __LIBC_LOCAL_NAME(strftime_l)
#endif /* !__local___localdep_strftime_l_defined */
#endif /* !__local_strftime_l_defined */
