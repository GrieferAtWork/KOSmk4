/* HASH CRC-32:0x80352a08 */
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
#ifndef __local_pwritev64_defined
#if defined(__CRT_HAVE_pwritev)
#define __local_pwritev64_defined 1
/* Dependency: "pwritev32" from "sys.uio" */
#ifndef ____localdep_pwritev32_defined
#define ____localdep_pwritev32_defined 1
#if defined(__CRT_HAVE_pwritev)
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_pwritev32,(__fd_t __fd, struct iovec const *__iovec, __STDC_INT_AS_SIZE_T __count, __off32_t __offset),pwritev,(__fd,__iovec,__count,__offset))
#else /* LIBC: pwritev */
#undef ____localdep_pwritev32_defined
#endif /* pwritev32... */
#endif /* !____localdep_pwritev32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pwritev64) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(pwritev64))(__fd_t __fd,
                                                       struct iovec const *__iovec,
                                                       __STDC_INT_AS_SIZE_T __count,
                                                       __off64_t __offset) {
#line 103 "kos/src/libc/magic/sys.uio.c"
	return __localdep_pwritev32(__fd, __iovec, __count, (__off32_t)__offset);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_pwritev) */
#endif /* !__local_pwritev64_defined */
