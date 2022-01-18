/* HASH CRC-32:0xd7480957 */
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
#ifndef __local_c32readlinkat_defined
#define __local_c32readlinkat_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wfreadlinkat)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32freadlinkat_defined
#define __local___localdep_c32freadlinkat_defined
#if defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c32freadlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__path, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_KOS$wfreadlinkat)
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c32freadlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__path, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#else /* ... */
#undef __local___localdep_c32freadlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c32freadlinkat_defined */
__LOCAL_LIBC(c32readlinkat) __ATTR_NONNULL((2, 3)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32readlinkat))(__fd_t __dfd, __CHAR32_TYPE__ const *__path, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __buflen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c32freadlinkat)(__dfd, __path, __buf, __buflen, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32readlinkat_defined
#define __local___localdep_c32readlinkat_defined
#define __localdep_c32readlinkat __LIBC_LOCAL_NAME(c32readlinkat)
#endif /* !__local___localdep_c32readlinkat_defined */
#else /* (__CRT_HAVE_wfreadlinkat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wfreadlinkat */
#undef __local_c32readlinkat_defined
#endif /* (!__CRT_HAVE_wfreadlinkat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wfreadlinkat */
#endif /* !__local_c32readlinkat_defined */
