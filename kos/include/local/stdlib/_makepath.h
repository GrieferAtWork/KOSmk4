/* HASH CRC-32:0x2413f0ff */
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
#ifndef __local__makepath_defined
#define __local__makepath_defined 1
/* Dependency: "_makepath_s" from "stdlib" */
#ifndef ____localdep__makepath_s_defined
#define ____localdep__makepath_s_defined 1
#ifdef __CRT_HAVE__makepath_s
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep__makepath_s,(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext),_makepath_s,(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* LIBC: _makepath_s */
#include <local/stdlib/_makepath_s.h>
#define __localdep__makepath_s (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_makepath_s))
#endif /* _makepath_s... */
#endif /* !____localdep__makepath_s_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_makepath) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_makepath))(char *__restrict __buf,
                                                       char const *__drive,
                                                       char const *__dir,
                                                       char const *__file,
                                                       char const *__ext) {
#line 2904 "kos/src/libc/magic/stdlib.c"
	__localdep__makepath_s(__buf, (__SIZE_TYPE__)-1, __drive, __dir, __file, __ext);
}
__NAMESPACE_LOCAL_END
#endif /* !__local__makepath_defined */
