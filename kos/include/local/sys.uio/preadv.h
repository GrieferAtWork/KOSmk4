/* HASH CRC-32:0x88a43493 */
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
#ifndef __local_preadv_defined
#if defined(__CRT_HAVE_preadv) || defined(__CRT_HAVE_preadv64)
#define __local_preadv_defined 1
/* Dependency: "preadv64" from "sys.uio" */
#ifndef ____localdep_preadv64_defined
#define ____localdep_preadv64_defined 1
#ifdef __CRT_HAVE_preadv64
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadv64,(__fd_t __fd, struct iovec const *__iovec, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),preadv64,(__fd,__iovec,__count,__offset))
#elif defined(__CRT_HAVE_preadv) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_preadv64,(__fd_t __fd, struct iovec const *__iovec, __STDC_INT_AS_SIZE_T __count, __off64_t __offset),preadv,(__fd,__iovec,__count,__offset))
#elif defined(__CRT_HAVE_preadv)
#include <local/sys.uio/preadv64.h>
#define __localdep_preadv64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(preadv64))
#else /* CUSTOM: preadv64 */
#undef ____localdep_preadv64_defined
#endif /* preadv64... */
#endif /* !____localdep_preadv64_defined */

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
__LOCAL_LIBC(preadv) __ATTR_WUNUSED __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(preadv))(__fd_t __fd,
                                                    struct iovec const *__iovec,
                                                    __STDC_INT_AS_SIZE_T __count,
                                                    __FS_TYPE(off) __offset) {
#line 75 "kos/src/libc/magic/sys.uio.c"
#ifdef __CRT_HAVE_preadv64
	return __localdep_preadv64(__fd, __iovec, __count, (__off64_t)__offset);
#else
	return __localdep_preadv32(__fd, __iovec, __count, (__off32_t)__offset);
#endif
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_preadv || __CRT_HAVE_preadv64 */
#endif /* !__local_preadv_defined */
