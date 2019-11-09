/* HASH CRC-32:0x83d87ce1 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16readlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wreadlinkat)
#define __local_c16readlink_defined 1
/* Dependency: "wreadlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_c16readlinkat_defined
#define ____localdep_c16readlinkat_defined 1
#if defined(__CRT_HAVE_wreadlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c16readlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__restrict __path, __CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#elif defined(__CRT_HAVE_DOS$wreadlinkat)
/* >> c16readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT_DOS(__ATTR_NONNULL((2, 3)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_c16readlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__restrict __path, __CHAR16_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen),wreadlinkat,(__dfd,__path,__buf,__buflen))
#else /* LIBC: wreadlinkat */
#undef ____localdep_c16readlinkat_defined
#endif /* c16readlinkat... */
#endif /* !____localdep_c16readlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c16readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `c16readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `c16freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__LOCAL_LIBC(c16readlink) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16readlink))(__CHAR16_TYPE__ const *__restrict __path,
                                                         __CHAR16_TYPE__ *__restrict __buf,
                                                         __SIZE_TYPE__ __buflen) {
#line 1505 "kos/src/libc/magic/unistd.c"
	return __localdep_c16readlinkat(__CRT_AT_FDCWD, __path, __buf, __buflen);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wreadlinkat) */
#endif /* !__local_c16readlink_defined */
