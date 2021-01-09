/* HASH CRC-32:0x86c07cf7 */
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
#ifndef __local_c32unlink_defined
#define __local_c32unlink_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wunlinkat))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32unlinkat from parts.uchar.unistd */
#ifndef __local___localdep_c32unlinkat_defined
#define __local___localdep_c32unlinkat_defined 1
#if defined(__CRT_HAVE_wunlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32unlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_KOS$wunlinkat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32unlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#else /* ... */
#undef __local___localdep_c32unlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c32unlinkat_defined */
/* >> unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__LOCAL_LIBC(c32unlink) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32unlink))(__CHAR32_TYPE__ const *__file) {
	return __localdep_c32unlinkat(__AT_FDCWD, __file, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32unlink_defined
#define __local___localdep_c32unlink_defined 1
#define __localdep_c32unlink __LIBC_LOCAL_NAME(c32unlink)
#endif /* !__local___localdep_c32unlink_defined */
#else /* __AT_FDCWD && ((__CRT_HAVE_wunlinkat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wunlinkat) */
#undef __local_c32unlink_defined
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wunlinkat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wunlinkat) */
#endif /* !__local_c32unlink_defined */
