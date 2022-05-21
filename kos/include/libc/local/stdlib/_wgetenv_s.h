/* HASH CRC-32:0xa96f238 */
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
#ifndef __local__wgetenv_s_defined
#define __local__wgetenv_s_defined
#include <__crt.h>
#ifdef __CRT_HAVE__wgetenv
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__wgetenv_defined
#define __local___localdep__wgetenv_defined
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep__wgetenv,(__WCHAR_TYPE__ const *__varname),_wgetenv,(__varname))
#endif /* !__local___localdep__wgetenv_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_wcslen_defined
#define __local___localdep_wcslen_defined
#ifdef __CRT_HAVE_wcslen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcslen,(__WCHAR_TYPE__ const *__restrict __str),wcslen,(__str))
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
__LOCAL_LIBC(_wgetenv_s) __ATTR_NONNULL((1, 2, 4)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wgetenv_s))(__SIZE_TYPE__ *__preqsize, __WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __bufsize, __WCHAR_TYPE__ const *__varname) {
	__SIZE_TYPE__ __reqsize;
	__WCHAR_TYPE__ *__name = (__NAMESPACE_LOCAL_SYM __localdep__wgetenv)(__varname);
	if (!__name) {
		if (__preqsize)
			*__preqsize = 0;
		return __EOK;
	}
	__reqsize = ((__NAMESPACE_LOCAL_SYM __localdep_wcslen)(__name) + 1) * sizeof(__WCHAR_TYPE__);
	if (__preqsize)
		*__preqsize = __reqsize;
	if (__reqsize > __bufsize) {
#ifdef __ERANGE
		return __ERANGE;
#else /* __ERANGE */
		return 1;
#endif /* !__ERANGE */
	}
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__buf, __name, __reqsize);
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wgetenv_s_defined
#define __local___localdep__wgetenv_s_defined
#define __localdep__wgetenv_s __LIBC_LOCAL_NAME(_wgetenv_s)
#endif /* !__local___localdep__wgetenv_s_defined */
#else /* __CRT_HAVE__wgetenv */
#undef __local__wgetenv_s_defined
#endif /* !__CRT_HAVE__wgetenv */
#endif /* !__local__wgetenv_s_defined */
