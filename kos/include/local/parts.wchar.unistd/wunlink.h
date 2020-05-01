/* HASH CRC-32:0x8a1fb303 */
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
#ifndef __local_wunlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#define __local_wunlink_defined 1
#include <__crt.h>
/* Dependency: "wunlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_wunlinkat_defined
#define ____localdep_wunlinkat_defined 1
#ifdef __CRT_HAVE_wunlinkat
/* >> wunlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_wunlinkat,(__fd_t __dfd, __WCHAR_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#else /* LIBC: wunlinkat */
#undef ____localdep_wunlinkat_defined
#endif /* wunlinkat... */
#endif /* !____localdep_wunlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> wunlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__LOCAL_LIBC(wunlink) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(wunlink))(__WCHAR_TYPE__ const *__file) {
#line 709 "kos/src/libc/magic/unistd.c"
	return __localdep_wunlinkat(__CRT_AT_FDCWD, __file, 0);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_wunlinkat */
#endif /* !__local_wunlink_defined */
