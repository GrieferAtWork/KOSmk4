/* HASH CRC-32:0x7358ac0e */
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
#ifndef __local_mkstemp_defined
#define __local_mkstemp_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_mkstemps) || defined(__CRT_HAVE_mkstemps64) || defined(__CRT_HAVE_mkostemps) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: mkstemps from stdlib */
#ifndef __local___localdep_mkstemps_defined
#define __local___localdep_mkstemps_defined 1
#if defined(__CRT_HAVE_mkstemps64) && defined(__USE_FILE_OFFSET64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `TEMPLATE' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `TEMPLATE' will not
 * already exists. Then, create a new file with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The # of trailing characters to-be ignored
 *                    after the required 6 trailing 'X'-characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_mkstemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps64,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `TEMPLATE' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `TEMPLATE' will not
 * already exists. Then, create a new file with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The # of trailing characters to-be ignored
 *                    after the required 6 trailing 'X'-characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_mkstemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkstemps64)
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `TEMPLATE' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `TEMPLATE' will not
 * already exists. Then, create a new file with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The # of trailing characters to-be ignored
 *                    after the required 6 trailing 'X'-characters. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_NCX,__localdep_mkstemps,(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen),mkstemps64,(__template_,__suffixlen))
#elif defined(__CRT_HAVE_mkostemps) || defined(__CRT_HAVE_mkostemps64) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/mkstemps.h>
__NAMESPACE_LOCAL_BEGIN
/* >> mkstemps(3), mkstemps64(3)
 * Replace the last 6 characters of `TEMPLATE' (which are followed by exactly
 * `suffixlen' more characters that are left alone), which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1), with
 * random characters such that the filename described by `TEMPLATE' will not
 * already exists. Then, create a new file with `O_RDWR' and return the file
 * descriptor of that file.
 * @param: suffixlen: The # of trailing characters to-be ignored
 *                    after the required 6 trailing 'X'-characters. */
#define __localdep_mkstemps __LIBC_LOCAL_NAME(mkstemps)
#else /* ... */
#undef __local___localdep_mkstemps_defined
#endif /* !... */
#endif /* !__local___localdep_mkstemps_defined */
/* >> mkstemp(3), mkstemp64(3)
 * Replace the last 6 characters of `TEMPLATE', which must be filled with
 * all 'X'-characters before the call (else errno=EINVAL + return -1),
 * with random characters such that the filename described by `TEMPLATE'
 * will not already exists. Then, create a new file with `O_RDWR' and return
 * the file descriptor of that file. */
__LOCAL_LIBC(mkstemp) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(mkstemp))(char *__template_) {
	return __localdep_mkstemps(__template_, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkstemp_defined
#define __local___localdep_mkstemp_defined 1
#define __localdep_mkstemp __LIBC_LOCAL_NAME(mkstemp)
#endif /* !__local___localdep_mkstemp_defined */
#else /* __CRT_HAVE_mkstemps || __CRT_HAVE_mkstemps64 || __CRT_HAVE_mkostemps || __CRT_HAVE_mkostemps64 || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local_mkstemp_defined
#endif /* !__CRT_HAVE_mkstemps && !__CRT_HAVE_mkstemps64 && !__CRT_HAVE_mkostemps && !__CRT_HAVE_mkostemps64 && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !__local_mkstemp_defined */
