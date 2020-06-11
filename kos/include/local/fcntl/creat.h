/* HASH CRC-32:0x1db237aa */
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
#ifndef __local_creat_defined
#define __local_creat_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_creat64) || (defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)) || (defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: open from fcntl */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined 1
#ifdef __open_defined
#ifdef __cplusplus
__NAMESPACE_GLB_USING(open)
#else /* __cplusplus */
#define __localdep_open open
#endif /* !__cplusplus */
#elif defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* ... */
#undef __local___localdep_open_defined
#endif /* !... */
#endif /* !__local___localdep_open_defined */
/* Dependency: creat64 from fcntl */
#ifndef __local___localdep_creat64_defined
#define __local___localdep_creat64_defined 1
#ifdef __creat64_defined
__NAMESPACE_GLB_USING(creat64)
#define __localdep_creat64 creat64
#elif defined(__CRT_HAVE_creat64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_creat64,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)
__NAMESPACE_LOCAL_END
#include <local/fcntl/creat64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_creat64 __LIBC_LOCAL_NAME(creat64)
#else /* ... */
#undef __local___localdep_creat64_defined
#endif /* !... */
#endif /* !__local___localdep_creat64_defined */
__NAMESPACE_LOCAL_END
#include <bits/fcntl.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(creat) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(creat))(char const *__filename, __mode_t __mode) {
#if defined(__CRT_HAVE_creat64) || (defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)) || (defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)
	return __localdep_creat64(__filename, __mode);
#else /* __CRT_HAVE_creat64 || (__CRT_HAVE_creat && (!__O_LARGEFILE || (__O_LARGEFILE+0) == 0)) || (__CRT_HAVE__creat && (!__O_LARGEFILE || (__O_LARGEFILE+0) == 0)) || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open */
	return __localdep_open(__filename, __O_CREAT | __O_WRONLY | __O_TRUNC, __mode);
#endif /* !__CRT_HAVE_creat64 && (!__CRT_HAVE_creat || (__O_LARGEFILE && !(__O_LARGEFILE+0) == 0)) && (!__CRT_HAVE__creat || (__O_LARGEFILE && !(__O_LARGEFILE+0) == 0)) && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_creat_defined
#define __local___localdep_creat_defined 1
#define __localdep_creat __LIBC_LOCAL_NAME(creat)
#endif /* !__local___localdep_creat_defined */
#else /* (__CRT_HAVE_creat64 || (__CRT_HAVE_creat && (!__O_LARGEFILE || (__O_LARGEFILE+0) == 0)) || (__CRT_HAVE__creat && (!__O_LARGEFILE || (__O_LARGEFILE+0) == 0)) || __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open) && (__CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__CRT_AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat))) */
#undef __local_creat_defined
#endif /* (!__CRT_HAVE_creat64 && (!__CRT_HAVE_creat || (__O_LARGEFILE && !(__O_LARGEFILE+0) == 0)) && (!__CRT_HAVE__creat || (__O_LARGEFILE && !(__O_LARGEFILE+0) == 0)) && !__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open) || (!__CRT_HAVE_open64 && !__CRT_HAVE___open64 && !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && (!__CRT_AT_FDCWD || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat))) */
#endif /* !__local_creat_defined */
