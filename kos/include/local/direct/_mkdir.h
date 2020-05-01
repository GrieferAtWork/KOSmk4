/* HASH CRC-32:0x8a872e4e */
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
#ifndef __local__mkdir_defined
#ifdef __CRT_HAVE_mkdir
#define __local__mkdir_defined 1
#include <__crt.h>
/* Dependency: "mkdir" from "sys.stat" */
#ifndef ____localdep_mkdir_defined
#define ____localdep_mkdir_defined 1
#ifdef __CRT_HAVE_mkdir
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,__localdep_mkdir,(char const *__pathname, __mode_t __mode),mkdir,(__pathname,__mode))
#elif defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)
#include <local/sys.stat/mkdir.h>
#define __localdep_mkdir (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkdir))
#else /* CUSTOM: mkdir */
#undef ____localdep_mkdir_defined
#endif /* mkdir... */
#endif /* !____localdep_mkdir_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_mkdir) __ATTR_NONNULL((1)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_mkdir))(char const *__path) {
#line 72 "kos/src/libc/magic/direct.c"
	return __localdep_mkdir(__path, 0755);
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_mkdir */
#endif /* !__local__mkdir_defined */
