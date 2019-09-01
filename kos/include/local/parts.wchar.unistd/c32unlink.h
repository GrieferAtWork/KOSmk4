/* HASH 0x3b206a31 */
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
#ifndef __local_c32unlink_defined
#if defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
#define __local_c32unlink_defined 1
/* Dependency: "unlinkat" */
#ifndef ____localdep_unlinkat_defined
#define ____localdep_unlinkat_defined 1
#if defined(__CRT_HAVE_unlinkat)
/* >> unlinkat(2)
 * Remove a file, symbolic link, device or FIFO referred to by `DFD:NAME' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_unlinkat,(__fd_t __dfd, char const *__name, __atflag_t __flags),unlinkat,(__dfd,__name,__flags))
#else /* LIBC: unlinkat */
#undef ____localdep_unlinkat_defined
#endif /* unlinkat... */
#endif /* !____localdep_unlinkat_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> c32unlink(2)
 * Remove a file, symbolic link, device or FIFO referred to by `FILE' */
__LOCAL_LIBC(c32unlink) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(c32unlink))(__CHAR32_TYPE__ const *__file) {
#line 678 "kos/src/libc/magic/unistd.c"
	return __localdep_unlinkat(__CRT_AT_FDCWD, __file, 0);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_AT_FDCWD) && defined(__CRT_HAVE_unlinkat) */
#endif /* !__local_c32unlink_defined */
