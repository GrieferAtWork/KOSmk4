/* HASH CRC-32:0x93983c2d */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_scandir64_defined
#define __local_scandir64_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <bits/os/dirent.h>
#if defined(__AT_FDCWD) && ((defined(__CRT_HAVE_scandiratk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_scandiratk64) && defined(__CRT_KOS)) || (defined(__CRT_HAVE_scandirat) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)) || (defined(__CRT_HAVE_scandirat64) && !defined(__CRT_KOS)))
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_scandirat64_defined
#define __local___localdep_scandirat64_defined
#if defined(__CRT_HAVE_scandiratk) && defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct __dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct __dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct __dirent64 const **__a, struct __dirent64 const **__b)),scandiratk,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandiratk64) && defined(__CRT_KOS)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct __dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct __dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct __dirent64 const **__a, struct __dirent64 const **__b)),scandiratk64,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat) && !defined(__CRT_KOS) && defined(_DIRENT_MATCHES_DIRENT64)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct __dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct __dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct __dirent64 const **__a, struct __dirent64 const **__b)),scandirat,(__dirfd,__dir,__namelist,__selector,__cmp))
#elif defined(__CRT_HAVE_scandirat64) && !defined(__CRT_KOS)
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),__STDC_INT_AS_SSIZE_T,__NOTHROW_RPC,__localdep_scandirat64,(__fd_t __dirfd, char const *__restrict __dir, struct __dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct __dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct __dirent64 const **__a, struct __dirent64 const **__b)),scandirat64,(__dirfd,__dir,__namelist,__selector,__cmp))
#else /* ... */
#undef __local___localdep_scandirat64_defined
#endif /* !... */
#endif /* !__local___localdep_scandirat64_defined */
__LOCAL_LIBC(scandir64) __ATTR_IN(1) __ATTR_OUT(2) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(scandir64))(char const *__restrict __dir, struct __dirent64 ***__restrict __namelist, int (__LIBKCALL *__selector)(struct __dirent64 const *__entry), int (__LIBKCALL *__cmp)(struct __dirent64 const **__a, struct __dirent64 const **__b)) {
	return (__NAMESPACE_LOCAL_SYM __localdep_scandirat64)(__AT_FDCWD, __dir, __namelist, __selector, __cmp);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_scandir64_defined
#define __local___localdep_scandir64_defined
#define __localdep_scandir64 __LIBC_LOCAL_NAME(scandir64)
#endif /* !__local___localdep_scandir64_defined */
#else /* __AT_FDCWD && ((__CRT_HAVE_scandiratk && __CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_scandiratk64 && __CRT_KOS) || (__CRT_HAVE_scandirat && !__CRT_KOS && _DIRENT_MATCHES_DIRENT64) || (__CRT_HAVE_scandirat64 && !__CRT_KOS)) */
#undef __local_scandir64_defined
#endif /* !__AT_FDCWD || ((!__CRT_HAVE_scandiratk || !__CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_scandiratk64 || !__CRT_KOS) && (!__CRT_HAVE_scandirat || __CRT_KOS || !_DIRENT_MATCHES_DIRENT64) && (!__CRT_HAVE_scandirat64 || __CRT_KOS)) */
#endif /* !__local_scandir64_defined */
