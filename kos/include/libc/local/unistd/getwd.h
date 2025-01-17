/* HASH CRC-32:0x2ffb939f */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getwd_defined
#define __local_getwd_defined
#include <__crt.h>
#if defined(__CRT_HAVE_getcwd) || defined(__CRT_HAVE__getcwd)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getcwd_defined
#define __local___localdep_getcwd_defined
#ifdef __CRT_HAVE_getcwd
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),getcwd,(__buf,__bufsize))
#elif defined(__CRT_HAVE__getcwd)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT_OPT(1),char *,__NOTHROW_RPC,__localdep_getcwd,(char *__buf, __SIZE_TYPE__ __bufsize),_getcwd,(__buf,__bufsize))
#else /* ... */
#undef __local___localdep_getcwd_defined
#endif /* !... */
#endif /* !__local___localdep_getcwd_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getwd) __ATTR_OUT(1) char *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(getwd))(char *__buf) {
	return (__NAMESPACE_LOCAL_SYM __localdep_getcwd)(__buf, (__SIZE_TYPE__)-1);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getwd_defined
#define __local___localdep_getwd_defined
#define __localdep_getwd __LIBC_LOCAL_NAME(getwd)
#endif /* !__local___localdep_getwd_defined */
#else /* __CRT_HAVE_getcwd || __CRT_HAVE__getcwd */
#undef __local_getwd_defined
#endif /* !__CRT_HAVE_getcwd && !__CRT_HAVE__getcwd */
#endif /* !__local_getwd_defined */
