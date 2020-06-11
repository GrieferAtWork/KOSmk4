/* HASH CRC-32:0x65f8ea1 */
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
#ifndef __local_lockf_defined
#define __local_lockf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: lockf32 from fcntl */
#if !defined(__local___localdep_lockf32_defined) && defined(__CRT_HAVE_lockf)
#define __local___localdep_lockf32_defined 1
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_lockf32,(__fd_t __fd, int __cmd, __off32_t __length),lockf,(__fd,__cmd,__length))
#endif /* !__local___localdep_lockf32_defined && __CRT_HAVE_lockf */
/* Dependency: lockf64 from fcntl */
#ifndef __local___localdep_lockf64_defined
#define __local___localdep_lockf64_defined 1
#ifdef __lockf64_defined
__NAMESPACE_GLB_USING(lockf64)
#define __localdep_lockf64 lockf64
#elif defined(__CRT_HAVE_lockf64)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_lockf64,(__fd_t __fd, int __cmd, __off64_t __length),lockf64,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_lockf64,(__fd_t __fd, int __cmd, __off64_t __length),lockf,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
__NAMESPACE_LOCAL_END
#include <local/fcntl/lockf64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_lockf64 __LIBC_LOCAL_NAME(lockf64)
#else /* ... */
#undef __local___localdep_lockf64_defined
#endif /* !... */
#endif /* !__local___localdep_lockf64_defined */
/* Dependency: crt_locking from fcntl */
#ifndef __local___localdep_crt_locking_defined
#define __local___localdep_crt_locking_defined 1
#ifdef __CRT_HAVE_locking
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_crt_locking,(__fd_t __fd, int __cmd, __off32_t __length),locking,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE__locking)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_crt_locking,(__fd_t __fd, int __cmd, __off32_t __length),_locking,(__fd,__cmd,__length))
#else /* ... */
#undef __local___localdep_crt_locking_defined
#endif /* !... */
#endif /* !__local___localdep_crt_locking_defined */
__LOCAL_LIBC(lockf) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lockf))(__fd_t __fd, int __cmd, __FS_TYPE(off) __length) {
#if defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
	return __localdep_lockf64(__fd, __cmd, (__off64_t)__length);
#elif defined(__CRT_HAVE_lockf)
	return __localdep_lockf32(__fd, __cmd, (__off32_t)__length);
#elif defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
	return __localdep_crt_locking(__fd, __cmd, (__off32_t)__length);
#endif /* ... */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_lockf_defined
#define __local___localdep_lockf_defined 1
#define __localdep_lockf __LIBC_LOCAL_NAME(lockf)
#endif /* !__local___localdep_lockf_defined */
#else /* __CRT_HAVE_lockf64 || __CRT_HAVE_lockf || __CRT_HAVE_locking || __CRT_HAVE__locking */
#undef __local_lockf_defined
#endif /* !__CRT_HAVE_lockf64 && !__CRT_HAVE_lockf && !__CRT_HAVE_locking && !__CRT_HAVE__locking */
#endif /* !__local_lockf_defined */
