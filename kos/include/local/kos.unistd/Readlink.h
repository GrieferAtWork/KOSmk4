/* HASH 0x518fb50b */
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
#ifndef __local_Readlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_ReadlinkAt)
#define __local_Readlink_defined 1
#include <kos/anno.h>
/* Dependency: "ReadlinkAt" */
#ifndef ____localdep_ReadlinkAt_defined
#define ____localdep_ReadlinkAt_defined 1
#if defined(__CRT_HAVE_ReadlinkAt)
/* >> readlinkat(2)
 * Read the text of a symbolic link under `DFD:PATH' into the provided buffer.
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE'. */
__CREDIRECT(__ATTR_NONNULL((2, 3)),__SIZE_TYPE__,,__localdep_ReadlinkAt,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, __SIZE_TYPE__ __buflen),ReadlinkAt,(__dfd,__path,__buf,__buflen)) __THROWS(...)
#else /* LIBC: ReadlinkAt */
#undef ____localdep_ReadlinkAt_defined
#endif /* ReadlinkAt... */
#endif /* !____localdep_ReadlinkAt_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> readlink(3)
 * Read the text of a symbolic link under `PATH' into the provided buffer.
 * Same as `readlinkat(AT_FDCWD, PATH, BUF, BUFLEN)'
 * WARNING: This function is badly designed and will neither append a trailing
 *          NUL-character to the buffer, nor will it return the required buffer
 *          size. Instead, it will return the written size, and the caller must
 *          keep on over allocating until the function indicates that it didn't
 *          make use of the buffer in its entirety.
 * When targeting KOS, consider using `freadlinkat(2)' with `AT_READLINK_REQSIZE' */
__LOCAL_LIBC(Readlink) __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(Readlink))(char const *__restrict __path,
                                         char *__restrict __buf,
                                         __SIZE_TYPE__ __buflen) __THROWS(...) {
#line 532 "kos/src/libc/magic/kos.unistd.c"
	__localdep_ReadlinkAt(__CRT_AT_FDCWD, __path, __buf, __buflen);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_ReadlinkAt) */
#endif /* !__local_Readlink_defined */
