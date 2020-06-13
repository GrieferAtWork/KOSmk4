/* HASH CRC-32:0x3c87363d */
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
#ifndef __local_c32access_defined
#define __local_c32access_defined 1
#include <__crt.h>
#if defined(__CRT_AT_FDCWD) && ((defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)) || (defined(__CRT_HAVE_DOS$wfaccessat) && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_DOS$KOS$wfaccessat))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32faccessat from parts.uchar.unistd */
#ifndef __local___localdep_c32faccessat_defined
#define __local___localdep_c32faccessat_defined 1
#if defined(__CRT_HAVE_wfaccessat) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__LIBKCALL,__localdep_c32faccessat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$wfaccessat) && defined(__LIBCCALL_IS_LIBKCALL)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32faccessat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),wfaccessat,(__dfd,__file,__type,__flags))
#elif defined(__CRT_HAVE_DOS$KOS$wfaccessat)
/* >> faccessat(2)
 * @param: TYPE: Set of `X_OK | W_OK | R_OK'
 * Test for access to the specified file `DFD:FILE', testing for `TYPE' */
__CREDIRECT_KOS(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,__localdep_c32faccessat,(__fd_t __dfd, __CHAR32_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type, __atflag_t __flags),KOS$wfaccessat,(__dfd,__file,__type,__flags))
#else /* ... */
#undef __local___localdep_c32faccessat_defined
#endif /* !... */
#endif /* !__local___localdep_c32faccessat_defined */
/* >> access(2)
 * @param: TYPE: Set of `X_OK|W_OK|R_OK'
 * Test for access to the specified file `FILE', testing for `TYPE' */
__LOCAL_LIBC(c32access) __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBKCALL __LIBC_LOCAL_NAME(c32access))(__CHAR32_TYPE__ const *__file, __STDC_INT_AS_UINT_T __type) {
	return __localdep_c32faccessat(__CRT_AT_FDCWD, __file, __type, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32access_defined
#define __local___localdep_c32access_defined 1
#define __localdep_c32access __LIBC_LOCAL_NAME(c32access)
#endif /* !__local___localdep_c32access_defined */
#else /* __CRT_AT_FDCWD && ((__CRT_HAVE_wfaccessat && (__SIZEOF_WCHAR_T__ == 4) && __LIBCCALL_IS_LIBKCALL) || (__CRT_HAVE_DOS$wfaccessat && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_DOS$KOS$wfaccessat) */
#undef __local_c32access_defined
#endif /* !__CRT_AT_FDCWD || ((!__CRT_HAVE_wfaccessat || !(__SIZEOF_WCHAR_T__ == 4) || !__LIBCCALL_IS_LIBKCALL) && (!__CRT_HAVE_DOS$wfaccessat || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_DOS$KOS$wfaccessat) */
#endif /* !__local_c32access_defined */
