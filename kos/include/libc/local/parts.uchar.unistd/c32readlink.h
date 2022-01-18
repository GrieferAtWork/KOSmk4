/* HASH CRC-32:0x5a946393 */
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
#ifndef __local_c32readlink_defined
#define __local_c32readlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wreadlinkat) || (defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 4) || defined(__CRT_HAVE_KOS$wfreadlinkat))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32readlinkat_defined
#define __local___localdep_c32readlinkat_defined
#if defined(__CRT_HAVE_wreadlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c32readlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__path, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_KOS$wreadlinkat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c32readlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__path, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_wfreadlinkat) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.unistd/wreadlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32readlinkat __NAMESPACE_LOCAL_TYPEHAX(__SSIZE_TYPE__(__LIBKCALL*)(__fd_t,__CHAR32_TYPE__ const *,__CHAR32_TYPE__ *,__SIZE_TYPE__),__SSIZE_TYPE__(__LIBKCALL&)(__fd_t,__CHAR32_TYPE__ const *,__CHAR32_TYPE__ *,__SIZE_TYPE__),wreadlinkat)
#elif defined(__CRT_HAVE_KOS$wfreadlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.unistd/c32readlinkat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32readlinkat __LIBC_LOCAL_NAME(c32readlinkat)
#else /* ... */
#undef __local___localdep_c32readlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c32readlinkat_defined */
__LOCAL_LIBC(c32readlink) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32readlink))(__CHAR32_TYPE__ const *__path, __CHAR32_TYPE__ *__buf, __SIZE_TYPE__ __buflen) {
	return (__NAMESPACE_LOCAL_SYM __localdep_c32readlinkat)(__AT_FDCWD, __path, __buf, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32readlink_defined
#define __local___localdep_c32readlink_defined
#define __localdep_c32readlink __LIBC_LOCAL_NAME(c32readlink)
#endif /* !__local___localdep_c32readlink_defined */
#else /* __AT_FDCWD && ((__CRT_HAVE_wreadlinkat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wreadlinkat || (__CRT_HAVE_wfreadlinkat && __SIZEOF_WCHAR_T__ == 4) || __CRT_HAVE_KOS$wfreadlinkat) */
#undef __local_c32readlink_defined
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wreadlinkat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wreadlinkat && (!__CRT_HAVE_wfreadlinkat || __SIZEOF_WCHAR_T__ != 4) && !__CRT_HAVE_KOS$wfreadlinkat) */
#endif /* !__local_c32readlink_defined */
