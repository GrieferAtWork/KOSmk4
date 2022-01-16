/* HASH CRC-32:0xd3ef6b44 */
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
#ifndef __local_wunlink_defined
#define __local_wunlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wunlinkat_defined
#define __local___localdep_wunlinkat_defined
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_wunlinkat,(__fd_t __dfd, __WCHAR_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#endif /* !__local___localdep_wunlinkat_defined */
__LOCAL_LIBC(wunlink) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wunlink))(__WCHAR_TYPE__ const *__file) {
	return (__NAMESPACE_LOCAL_SYM __localdep_wunlinkat)(__AT_FDCWD, __file, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wunlink_defined
#define __local___localdep_wunlink_defined
#define __localdep_wunlink __LIBC_LOCAL_NAME(wunlink)
#endif /* !__local___localdep_wunlink_defined */
#else /* __AT_FDCWD && __CRT_HAVE_wunlinkat */
#undef __local_wunlink_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_wunlinkat */
#endif /* !__local_wunlink_defined */
