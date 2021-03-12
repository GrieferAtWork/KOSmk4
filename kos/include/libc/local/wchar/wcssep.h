/* HASH CRC-32:0x1cf9d765 */
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
#ifndef __local_wcssep_defined
#define __local_wcssep_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: wcschr from wchar */
#ifndef __local___localdep_wcschr_defined
#define __local___localdep_wcschr_defined 1
#ifdef __CRT_HAVE_wcschr
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcschr,(__WCHAR_TYPE__ const *__restrict __haystack, __WCHAR_TYPE__ __needle),wcschr,(__haystack,__needle))
#else /* __CRT_HAVE_wcschr */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcschr.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strchr(3)
 * Return the pointer of the first instance of `needle', or `NULL' if `needle' wasn't found. */
#define __localdep_wcschr __LIBC_LOCAL_NAME(wcschr)
#endif /* !__CRT_HAVE_wcschr */
#endif /* !__local___localdep_wcschr_defined */
__LOCAL_LIBC(wcssep) __ATTR_LEAF __ATTR_NONNULL((1, 2)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcssep))(__WCHAR_TYPE__ **__restrict __stringp, __WCHAR_TYPE__ const *__restrict __delim) {
	__WCHAR_TYPE__ *__result, *__iter;
	if ((__result = *__stringp) == __NULLPTR || !*__result)
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
