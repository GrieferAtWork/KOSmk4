/* HASH CRC-32:0x90cc7ebe */
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
#ifndef __local_mkostemps_defined
#define __local_mkostemps_defined 1
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: system_mktemp from stdlib */
#ifndef __local___localdep_system_mktemp_defined
#define __local___localdep_system_mktemp_defined 1
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/system_mktemp.h>
__NAMESPACE_LOCAL_BEGIN
/* Internal implementation for creating temporary files.
 * @param: what: Select what kind of temporary object to create.
 *                  `0': Create a temporary file. (The handle of that file will be returned)
 *                       Creating mode used is 0600
 *                       This mode is only recognized when `$has_function(open)'
 *                  `1': Create a temporary directory. (0 is returned on success)
 *                       Creating mode used is 0700
 *                       This mode is only recognized when `$has_function(mkdir)'
 *                       NOTE: `flags' is ignored in this mode
 *                  `2': Braindead `mktemp(3)'-mode: Like `0', but don't actually create the
 *                       file. Instead, return `0' on success
 *                       This mode is only recognized when `$has_function(open) || $has_function(stat)'
 *                       NOTE: `flags' is ignored in this mode */
#define __localdep_system_mktemp __LIBC_LOCAL_NAME(system_mktemp)
#endif /* !__local___localdep_system_mktemp_defined */
__LOCAL_LIBC(mkostemps) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mkostemps))(char *__template_, __STDC_INT_AS_SIZE_T __suffixlen, __oflag_t __flags) {
	return __localdep_system_mktemp(0, __template_, __suffixlen, __flags);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mkostemps_defined
#define __local___localdep_mkostemps_defined 1
#define __localdep_mkostemps __LIBC_LOCAL_NAME(mkostemps)
#endif /* !__local___localdep_mkostemps_defined */
#else /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#undef __local_mkostemps_defined
#endif /* !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat)) */
#endif /* !__local_mkostemps_defined */
