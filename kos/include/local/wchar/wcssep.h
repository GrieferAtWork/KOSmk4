/* HASH CRC-32:0xfc606259 */
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
#ifndef __local_wcssep_defined
#define __local_wcssep_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcschr from wchar */
#ifndef __local___localdep_wcschr_defined
#define __local___localdep_wcschr_defined 1
#ifdef __CRT_HAVE_wcschr
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcschr,(__WCHAR_TYPE__ const *__restrict __haystack, __WCHAR_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcschr) && __SIZEOF_WCHAR_T__ == 4
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcschr,(__WCHAR_TYPE__ const *__restrict __haystack, __WCHAR_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcschr) && __SIZEOF_WCHAR_T__ == 2
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcschr,(__WCHAR_TYPE__ const *__restrict __haystack, __WCHAR_TYPE__ __needle),wcschr,(__haystack,__needle))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wchar/wcschr.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_wcschr __LIBC_LOCAL_NAME(wcschr)
#endif /* !... */
#endif /* !__local___localdep_wcschr_defined */
__LOCAL_LIBC(wcssep) __ATTR_LEAF __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcssep))(__WCHAR_TYPE__ **__restrict __stringp, __WCHAR_TYPE__ const *__restrict __delim) {
	__WCHAR_TYPE__ *__result, *__iter;
	if (!__stringp || (__result = *__stringp) == __NULLPTR || !*__result)
		return __NULLPTR;
	for (__iter = __result; *__iter && !__localdep_wcschr(__delim, *__iter); ++__iter)
		;
	if (*__iter)
		*__iter++ = '\0';
	*__stringp = __iter;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcssep_defined
#define __local___localdep_wcssep_defined 1
#define __localdep_wcssep __LIBC_LOCAL_NAME(wcssep)
#endif /* !__local___localdep_wcssep_defined */
#endif /* !__local_wcssep_defined */
