/* HASH CRC-32:0x4a631100 */
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
#ifndef __local_c16readlink_defined
#define __local_c16readlink_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && ((defined(__CRT_HAVE_wreadlinkat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wreadlinkat))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16readlinkat from parts.uchar.unistd */
#ifndef __local___localdep_c16readlinkat_defined
#define __local___localdep_c16readlinkat_defined 1
#if defined(__CRT_HAVE_wreadlinkat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__LIBDCALL,__localdep_c16readlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__restrict __path, __CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c16readlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__restrict __path, __CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#else /* ... */
#undef __local___localdep_c16readlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c16readlinkat_defined */
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__LOCAL_LIBC(c16readlink) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16readlink))(__CHAR16_TYPE__ const *__restrict __path, __CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen) {
	return __localdep_c16readlinkat(__CRT_AT_FDCWD, __path, __buf, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16readlink_defined
#define __local___localdep_c16readlink_defined 1
#define __localdep_c16readlink __LIBC_LOCAL_NAME(c16readlink)
#endif /* !__local___localdep_c16readlink_defined */
#else /* __CRT_AT_FDCWD && ((__CRT_HAVE_wreadlinkat && (__SIZEOF_WCHAR_T__ == 2) && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wreadlinkat) */
#undef __local_c16readlink_defined
#endif /* !__CRT_AT_FDCWD || ((!__CRT_HAVE_wreadlinkat || !(__SIZEOF_WCHAR_T__ == 2) || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wreadlinkat) */
#endif /* !__local_c16readlink_defined */
