/* HASH CRC-32:0x41784f77 */
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
#ifndef __local_lockf64_defined
#if defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE__locking) || defined(__CRT_HAVE_locking)
#define __local_lockf64_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/types.h>
/* Dependency: "lockf32" from "fcntl" */
#ifndef ____localdep_lockf32_defined
#define ____localdep_lockf32_defined 1
#ifdef __CRT_HAVE_lockf
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_lockf32,(__fd_t __fd, int __cmd, __off32_t __length),lockf,(__fd,__cmd,__length))
#else /* LIBC: lockf */
#undef ____localdep_lockf32_defined
#endif /* lockf32... */
#endif /* !____localdep_lockf32_defined */

/* Dependency: "crt_locking" from "fcntl" */
#ifndef ____localdep_crt_locking_defined
#define ____localdep_crt_locking_defined 1
#ifdef __CRT_HAVE__locking
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_crt_locking,(__fd_t __fd, int __cmd, __off32_t __length),_locking,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_locking)
__CREDIRECT(,int,__NOTHROW_RPC,__localdep_crt_locking,(__fd_t __fd, int __cmd, __off32_t __length),locking,(__fd,__cmd,__length))
#else /* LIBC: _locking */
#undef ____localdep_crt_locking_defined
#endif /* crt_locking... */
#endif /* !____localdep_crt_locking_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(lockf64) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(lockf64))(__fd_t __fd,
                                                     int __cmd,
                                                     __off64_t __length) {
#line 442 "kos/src/libc/magic/fcntl.c"
#ifdef __CRT_HAVE_lockf
	return __localdep_lockf32(__fd, __cmd, (__off64_t)__length);
#else /* __CRT_HAVE_lockf */
	return __localdep_crt_locking(__fd, __cmd, (__off32_t)__length);
#endif /* !__CRT_HAVE_lockf */
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_lockf || __CRT_HAVE__locking || __CRT_HAVE_locking */
#endif /* !__local_lockf64_defined */
