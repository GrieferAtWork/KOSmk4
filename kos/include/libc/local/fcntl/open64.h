/* HASH CRC-32:0xd01f78dc */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_open64_defined
#define __local_open64_defined
#include <__crt.h>
#if defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_open32_defined
#define __local___localdep_open32_defined
#ifdef __CRT_HAVE_open
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open32,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open32,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open32,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open32,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
#undef __local___localdep_open32_defined
#endif /* !... */
#endif /* !__local___localdep_open32_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/oflags.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(open64) __ATTR_WUNUSED __ATTR_IN(1) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(open64))(char const *__filename, __oflag_t __oflags, ...) {
	__fd_t __result;
	__builtin_va_list __args;
	__mode_t __mode;
	__builtin_va_start(__args, __oflags);
	__mode = __builtin_va_arg(__args, __mode_t);
#ifdef __O_LARGEFILE
	__result = (__NAMESPACE_LOCAL_SYM __localdep_open32)(__filename, __oflags | __O_LARGEFILE, __mode);
#else /* __O_LARGEFILE */
	__result = (__NAMESPACE_LOCAL_SYM __localdep_open32)(__filename, __oflags, __mode);
#endif /* !__O_LARGEFILE */
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_open64_defined
#define __local___localdep_open64_defined
#define __localdep_open64 __LIBC_LOCAL_NAME(open64)
#endif /* !__local___localdep_open64_defined */
#else /* __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || __CRT_HAVE___libc_open */
#undef __local_open64_defined
#endif /* !__CRT_HAVE_open && !__CRT_HAVE__open && !__CRT_HAVE___open && !__CRT_HAVE___libc_open */
#endif /* !__local_open64_defined */
