/* HASH CRC-32:0x95501ffc */
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
#ifndef __local_c16readlinkat_defined
#define __local_c16readlinkat_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfreadlinkat)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16freadlinkat_defined
#define __local___localdep_c16freadlinkat_defined
#if defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c16freadlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__path, __CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#elif defined(__CRT_HAVE_DOS$wfreadlinkat)
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c16freadlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__path, __CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __atflag_t __flags),wfreadlinkat,(__dfd,__path,__buf,__buflen,__flags))
#else /* ... */
#undef __local___localdep_c16freadlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c16freadlinkat_defined */
__LOCAL_LIBC(c16readlinkat) __ATTR_NONNULL((2, 3)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16readlinkat))(__fd_t __dfd, __CHAR16_TYPE__ const *__path, __CHAR16_TYPE__ *__buf, __SIZE_TYPE__ __buflen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c16freadlinkat)(__dfd, __path, __buf, __buflen, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16readlinkat_defined
#define __local___localdep_c16readlinkat_defined
#define __localdep_c16readlinkat __LIBC_LOCAL_NAME(c16readlinkat)
#endif /* !__local___localdep_c16readlinkat_defined */
#else /* (__CRT_HAVE_wfreadlinkat && __SIZEOF_WCHAR_T__ == 2 && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wfreadlinkat */
#undef __local_c16readlinkat_defined
#endif /* (!__CRT_HAVE_wfreadlinkat || __SIZEOF_WCHAR_T__ != 2 || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wfreadlinkat */
#endif /* !__local_c16readlinkat_defined */