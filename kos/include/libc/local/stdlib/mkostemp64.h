/* HASH CRC-32:0x8c9a84e2 */
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
#ifndef __local_mkostemp64_defined
#define __local_mkostemp64_defined 1
#include <__crt.h>
#include <asm/os/oflags.h>
#include <features.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_mkostemps) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mkostemps64_defined
#define __local___localdep_mkostemps64_defined 1
#ifdef __CRT_HAVE_mkostemps64
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_mkostemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags),mkostemps64,(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps) && (!defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_mkostemps64,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags),mkostemps,(__template_,__suffixlen,__flags))
#elif defined(__CRT_HAVE_mkostemps) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mkostemps64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkostemps64 __LIBC_LOCAL_NAME(mkostemps64)
#else /* ... */
#undef __local___localdep_mkostemps64_defined
#endif /* !... */
#endif /* !__local___localdep_mkostemps64_defined */
__LOCAL_LIBC(mkostemp64) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mkostemp64))(char *__template_, __oflag_t __flags) {
	return (__NAMESPACE_LOCAL_SYM __localdep_mkostemps64)(__template_, 0, __flags);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkostemp64_defined
#define __local___localdep_mkostemp64_defined 1
#define __localdep_mkostemp64 __LIBC_LOCAL_NAME(mkostemp64)
#endif /* !__local___localdep_mkostemp64_defined */
#else /* __CRT_HAVE_mkostemps || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local_mkostemp64_defined
#endif /* !__CRT_HAVE_mkostemps && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !__local_mkostemp64_defined */
