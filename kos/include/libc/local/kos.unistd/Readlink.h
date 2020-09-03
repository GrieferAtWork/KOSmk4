/* HASH CRC-32:0x7cd0ae21 */
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
#ifndef __local_Readlink_defined
#define __local_Readlink_defined 1
#include <__crt.h>
#include <asm/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_ReadlinkAt)
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: ReadlinkAt from kos.unistd */
#ifndef __local___localdep_ReadlinkAt_defined
#define __local___localdep_ReadlinkAt_defined 1
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
__CREDIRECT(__ATTR_NONNULL((2, 3)),__SIZE_TYPE__,__THROWING,__localdep_ReadlinkAt,(__fd_t __dfd, char const *__restrict __path, char *__restrict __buf, __SIZE_TYPE__ __buflen),ReadlinkAt,(__dfd,__path,__buf,__buflen))
#endif /* !__local___localdep_ReadlinkAt_defined */
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
(__LIBCCALL __LIBC_LOCAL_NAME(Readlink))(char const *__restrict __path, char *__restrict __buf, __SIZE_TYPE__ __buflen) __THROWS(...) {
	__localdep_ReadlinkAt(__AT_FDCWD, __path, __buf, __buflen);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Readlink_defined
#define __local___localdep_Readlink_defined 1
#define __localdep_Readlink __LIBC_LOCAL_NAME(Readlink)
#endif /* !__local___localdep_Readlink_defined */
#else /* __AT_FDCWD && __CRT_HAVE_ReadlinkAt */
#undef __local_Readlink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_ReadlinkAt */
#endif /* !__local_Readlink_defined */
