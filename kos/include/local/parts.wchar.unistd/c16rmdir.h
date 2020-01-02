/* HASH CRC-32:0x24a5dd24 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16rmdir_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_wunlinkat)
#define __local_c16rmdir_defined 1
/* Dependency: "wunlinkat" from "parts.wchar.unistd" */
#ifndef ____localdep_c16unlinkat_defined
#define ____localdep_c16unlinkat_defined 1
#if defined(__CRT_HAVE_wunlinkat) && (__SIZEOF_WCHAR_T__ == 2)
/* >> c16unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c16unlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#elif defined(__CRT_HAVE_DOS$wunlinkat)
/* >> c16unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c16unlinkat,(__fd_t __dfd, __CHAR16_TYPE__ const *__name, __atflag_t __flags),wunlinkat,(__dfd,__name,__flags))
#else /* LIBC: wunlinkat */
#undef ____localdep_c16unlinkat_defined
#endif /* c16unlinkat... */
#endif /* !____localdep_c16unlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c16rmdir(2)
 * Remove a directory referred to by `PATH' */
__LOCAL_LIBC(c16rmdir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16rmdir))(__CHAR16_TYPE__ const *__path) {
#line 718 "kos/src/libc/magic/unistd.c"
	return __localdep_c16unlinkat(__CRT_AT_FDCWD, __path, 0x0200); /* AT_REMOVEDIR */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_AT_FDCWD && __CRT_HAVE_wunlinkat */
#endif /* !__local_c16rmdir_defined */
