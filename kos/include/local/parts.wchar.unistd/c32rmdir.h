/* HASH CRC-32:0x94b4d272 */
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
#ifndef __local_c32rmdir_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#define __local_c32rmdir_defined 1
/* Dependency: "wunlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_c32unlinkat_defined
#define ____localdep_c32unlinkat_defined 1
#if defined(__CRT_HAVE_wunlinkat) && (__SIZEOF_WCHAR_T__ == 4)
/* >> c32unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32unlinkat,(__fd_t __dfd, __CHAR32_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#else /* LIBC: wunlinkat */
#undef ____localdep_c32unlinkat_defined
#endif /* c32unlinkat... */
#endif /* !____localdep_c32unlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c32rmdir(2)
 * Remove a directory referred to by `PATH' */
__LOCAL_LIBC(c32rmdir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32rmdir))(__CHAR32_TYPE__ const *__path) {
#line 718 "kos/src/libc/magic/unistd.c"
	return __localdep_c32unlinkat(__CRT_AT_FDCWD, __path, 0x0200); /* AT_REMOVEDIR */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_wunlinkat */
#endif /* !__local_c32rmdir_defined */
