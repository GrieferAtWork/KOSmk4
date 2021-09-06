/* HASH CRC-32:0x4d698c7e */
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
#ifndef __local_c32symlink_defined
#define __local_c32symlink_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$wsymlinkat))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32symlinkat_defined
#define __local___localdep_c32symlinkat_defined 1
#if defined(__CRT_HAVE_wsymlinkat) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_c32symlinkat,(__CHAR32_TYPE__ const *__link_text, __fd_t __tofd, __CHAR32_TYPE__ const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#elif defined(__CRT_HAVE_KOS$wsymlinkat)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_NONNULL((1, 3)),int,__NOTHROW_RPC,__localdep_c32symlinkat,(__CHAR32_TYPE__ const *__link_text, __fd_t __tofd, __CHAR32_TYPE__ const *__target_path),wsymlinkat,(__link_text,__tofd,__target_path))
#else /* ... */
#undef __local___localdep_c32symlinkat_defined
#endif /* !... */
#endif /* !__local___localdep_c32symlinkat_defined */
__LOCAL_LIBC(c32symlink) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32symlink))(__CHAR32_TYPE__ const *__link_text, __CHAR32_TYPE__ const *__target_path) {
	/* TODO: Header-implementation for `symlink()' on DOS (using the windows API) */
	return __localdep_c32symlinkat(__link_text, __AT_FDCWD, __target_path);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32symlink_defined
#define __local___localdep_c32symlink_defined 1
#define __localdep_c32symlink __LIBC_LOCAL_NAME(c32symlink)
#endif /* !__local___localdep_c32symlink_defined */
#else /* __AT_FDCWD && ((__CRT_HAVE_wsymlinkat && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$wsymlinkat) */
#undef __local_c32symlink_defined
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_wsymlinkat || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$wsymlinkat) */
#endif /* !__local_c32symlink_defined */
