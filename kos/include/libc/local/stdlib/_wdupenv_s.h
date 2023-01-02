/* HASH CRC-32:0xac0ef082 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__wdupenv_s_defined
#define __local__wdupenv_s_defined
#include <__crt.h>
#if defined(__CRT_HAVE__wgetenv) && (defined(__CRT_HAVE_wcsdup) || defined(__CRT_HAVE__wcsdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__wgetenv_defined
#define __local___localdep__wgetenv_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep__wgetenv,(__WCHAR_TYPE__ const *__varname),_wgetenv,(__varname))
#endif /* !__local___localdep__wgetenv_defined */
#ifndef __local___localdep_wcsdup_defined
#define __local___localdep_wcsdup_defined
#ifdef __CRT_HAVE_wcsdup
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsdup,(__WCHAR_TYPE__ const *__restrict __string),wcsdup,(__string))
#elif defined(__CRT_HAVE__wcsdup)
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_IN(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsdup,(__WCHAR_TYPE__ const *__restrict __string),_wcsdup,(__string))
#elif defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsdup.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsdup __LIBC_LOCAL_NAME(wcsdup)
#else /* ... */
#undef __local___localdep_wcsdup_defined
#endif /* !... */
#endif /* !__local___localdep_wcsdup_defined */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined
#ifdef __CRT_HAVE_wcslen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __str),wcslen,(__str))
#else /* __CRT_HAVE_wcslen */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcslen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcslen __LIBC_LOCAL_NAME(wcslen)
#endif /* !__CRT_HAVE_wcslen */
#endif /* !__local___localdep_wcslen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_wdupenv_s) __ATTR_IN(3) __ATTR_OUT(1) __ATTR_OUT(2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wdupenv_s))(__WCHAR_TYPE__ **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, __WCHAR_TYPE__ const *__varname) {
	__WCHAR_TYPE__ *__name = (__NAMESPACE_LOCAL_SYM __localdep__wgetenv)(__varname);
	if (!__name) {
		*__pbuf    = __NULLPTR;
		*__pbuflen = 0;
		return __EOK;
	}
	__name = (__NAMESPACE_LOCAL_SYM __localdep_wcsdup)(__name);
	if (!__name) {
#ifdef __ENOMEM
		return __ENOMEM;
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	*__pbuf    = __name;
	*__pbuflen = ((__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__name) + 1) * sizeof(__WCHAR_TYPE__);
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wdupenv_s_defined
#define __local___localdep__wdupenv_s_defined
#define __localdep__wdupenv_s __LIBC_LOCAL_NAME(_wdupenv_s)
#endif /* !__local___localdep__wdupenv_s_defined */
#else /* __CRT_HAVE__wgetenv && (__CRT_HAVE_wcsdup || __CRT_HAVE__wcsdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) */
#undef __local__wdupenv_s_defined
#endif /* !__CRT_HAVE__wgetenv || (!__CRT_HAVE_wcsdup && !__CRT_HAVE__wcsdup && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) */
#endif /* !__local__wdupenv_s_defined */
