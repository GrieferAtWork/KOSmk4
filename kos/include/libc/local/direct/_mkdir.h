/* HASH CRC-32:0x2a20f7c */
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
#ifndef __local__mkdir_defined
#define __local__mkdir_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_mkdir) || (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mkdir_defined
#define __local___localdep_mkdir_defined 1
#ifdef __CRT_HAVE_mkdir
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),mkdir,(__pathname,__mode))
#elif defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/mkdir.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mkdir __LIBC_LOCAL_NAME(mkdir)
#else /* ... */
#undef __local___localdep_mkdir_defined
#endif /* !... */
#endif /* !__local___localdep_mkdir_defined */
__LOCAL_LIBC(_mkdir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_mkdir))(char const *__path) {
	return __NAMESPACE_LOCAL_SYM __localdep_mkdir(__path, 0755);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mkdir_defined
#define __local___localdep__mkdir_defined 1
#define __localdep__mkdir __LIBC_LOCAL_NAME(_mkdir)
#endif /* !__local___localdep__mkdir_defined */
#else /* __CRT_HAVE_mkdir || (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) */
#undef __local__mkdir_defined
#endif /* !__CRT_HAVE_mkdir && (!__CRT_DOS_PRIMARY || !__CRT_HAVE__mkdir) */
#endif /* !__local__mkdir_defined */
