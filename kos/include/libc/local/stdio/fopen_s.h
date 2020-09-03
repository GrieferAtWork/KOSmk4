/* HASH CRC-32:0x8fd1ff20 */
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
#ifndef __local_fopen_s_defined
#define __local_fopen_s_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE__IO_fopen) || defined(__CRT_HAVE_fopen64)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fopen64 from stdio */
#ifndef __local___localdep_fopen64_defined
#define __local___localdep_fopen64_defined 1
#ifdef __CRT_HAVE_fopen64
/* 64-bit variant of `fopen' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen64,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen)
/* 64-bit variant of `fopen' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen64,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE__IO_fopen)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fopen64.h>
__NAMESPACE_LOCAL_BEGIN
/* 64-bit variant of `fopen' */
#define __localdep_fopen64 __LIBC_LOCAL_NAME(fopen64)
#else /* ... */
#undef __local___localdep_fopen64_defined
#endif /* !... */
#endif /* !__local___localdep_fopen64_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fopen_s) __ATTR_NONNULL((1, 2, 3)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fopen_s))(__FILE **__pstream, char const *__filename, char const *__modes) {
	__FILE *__result;
	if __unlikely(!__pstream || !__filename || !__modes) {
#ifdef __EINVAL
		return __EINVAL;
#else /* __EINVAL */
		return 1;
#endif /* !__EINVAL */
	}
	__result = __localdep_fopen64(__filename, __modes);
	if __unlikely(!__result) {
#ifdef __ENOMEM
		return __libc_geterrno_or(__ENOMEM);
#else /* __ENOMEM */
		return 1;
#endif /* !__ENOMEM */
	}
	*__pstream = __result;
	return __EOK;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fopen_s_defined
#define __local___localdep_fopen_s_defined 1
#define __localdep_fopen_s __LIBC_LOCAL_NAME(fopen_s)
#endif /* !__local___localdep_fopen_s_defined */
#else /* __CRT_HAVE_fopen || __CRT_HAVE__IO_fopen || __CRT_HAVE_fopen64 */
#undef __local_fopen_s_defined
#endif /* !__CRT_HAVE_fopen && !__CRT_HAVE__IO_fopen && !__CRT_HAVE_fopen64 */
#endif /* !__local_fopen_s_defined */
