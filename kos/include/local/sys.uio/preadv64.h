/* HASH CRC-32:0xbb5a71cd */
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
#ifndef __local_preadv64_defined
#ifdef __CRT_HAVE_preadv
#define __local_preadv64_defined 1
/* Dependency: "preadv32" from "sys.uio" */
#ifndef ____localdep_preadv32_defined
#define ____localdep_preadv32_defined 1
#ifdef __CRT_HAVE_preadv
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadv32,(__fd_t __fd, struct iovec const *__iovec, __STDC_INT_AS_SIZE_T __count, __off32_t __offset),preadv,(__fd,__iovec,__count,__offset))
#else /* LIBC: preadv */
#undef ____localdep_preadv32_defined
#endif /* preadv32... */
#endif /* !____localdep_preadv32_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(preadv64) __ATTR_WUNUSED __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(preadv64))(__fd_t __fd,
                                                      struct iovec const *__iovec,
                                                      __STDC_INT_AS_SIZE_T __count,
                                                      __off64_t __offset) {
#line 98 "kos/src/libc/magic/sys.uio.c"
	return __localdep_preadv32(__fd, __iovec, __count, (__off32_t)__offset);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_preadv */
#endif /* !__local_preadv64_defined */
