/* HASH CRC-32:0x889f5146 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_creat64_defined
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open)
#define __local_creat64_defined 1
#include <bits/types.h>
#include <bits/types.h>
#include <bits/fcntl.h>
/* Dependency: "open64" from "fcntl" */
#ifndef ____localdep_open64_defined
#define ____localdep_open64_defined 1
#ifdef __CRT_HAVE_open64
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,__localdep_open64,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open)
#include <local/fcntl/open64.h>
#define __localdep_open64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open64))
#else /* CUSTOM: open64 */
#undef ____localdep_open64_defined
#endif /* open64... */
#endif /* !____localdep_open64_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(creat64) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(creat64))(char const *__filename,
                                                     __mode_t __mode) {
#line 246 "kos/src/libc/magic/fcntl.c"
	return __localdep_open64(__filename, O_CREAT|O_WRONLY|O_TRUNC, __mode);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) */
#endif /* !__local_creat64_defined */
