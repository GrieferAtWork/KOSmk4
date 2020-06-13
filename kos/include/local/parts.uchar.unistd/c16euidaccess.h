/* HASH CRC-32:0xfb746915 */
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
#ifndef __local_c16euidaccess_defined
#define __local_c16euidaccess_defined 1
#include <__crt.h>
#include <asm/fcntl.h>
#if defined(__CRT_AT_FDCWD) && defined(__AT_EACCESS) && ((defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$wfaccessat))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16faccessat from parts.uchar.unistd */
#ifndef __local___localdep_c16faccessat_defined
#define __local___localdep_c16faccessat_defined 1
#if defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBDCALL,__localdep_c16faccessat,(__fd_t __dfd, __CHAR16_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_DOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c16faccessat,(__fd_t __dfd, __CHAR16_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#else /* ... */
#undef __local___localdep_c16faccessat_defined
#endif /* !... */
#endif /* !__local___localdep_c16faccessat_defined */
/* >> euidaccess(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE', using the effective filesystem ids */
__LOCAL_LIBC(c16euidaccess) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBDCALL __LIBC_LOCAL_NAME(c16euidaccess))(__CHAR16_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type) {
	return __localdep_c16faccessat(__CRT_AT_FDCWD, __file, __type, __AT_EACCESS);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16euidaccess_defined
#define __local___localdep_c16euidaccess_defined 1
#define __localdep_c16euidaccess __LIBC_LOCAL_NAME(c16euidaccess)
#endif /* !__local___localdep_c16euidaccess_defined */
#else /* __CRT_AT_FDCWD && __AT_EACCESS && ((__CRT_HAVE_wfaccessat && (__SIZEOF_WCHAR_T__ == 2) && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$wfaccessat) */
#undef __local_c16euidaccess_defined
#endif /* !__CRT_AT_FDCWD || !__AT_EACCESS || ((!__CRT_HAVE_wfaccessat || !(__SIZEOF_WCHAR_T__ == 2) || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$wfaccessat) */
#endif /* !__local_c16euidaccess_defined */
