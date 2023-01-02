/* HASH CRC-32:0xc6aea47f */
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
#ifndef __local__makepath_defined
#define __local__makepath_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__makepath_s_defined
#define __local___localdep__makepath_s_defined
#ifdef __CRT_HAVE__makepath_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_IN_OPT(5) __ATTR_IN_OPT(6) __ATTR_OUTS(1, 2),__errno_t,__NOTHROW_NCX,__localdep__makepath_s,(char *__buf, __SIZE_TYPE__ __buflen, char const *__drive, char const *__dir, char const *__file, char const *__ext),_makepath_s,(__buf,__buflen,__drive,__dir,__file,__ext))
#else /* __CRT_HAVE__makepath_s */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_makepath_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__makepath_s __LIBC_LOCAL_NAME(_makepath_s)
#endif /* !__CRT_HAVE__makepath_s */
#endif /* !__local___localdep__makepath_s_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_makepath) __ATTR_IN_OPT(2) __ATTR_IN_OPT(3) __ATTR_IN_OPT(4) __ATTR_IN_OPT(5) __ATTR_OUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_makepath))(char *__restrict __buf, char const *__drive, char const *__dir, char const *__file, char const *__ext) {
	(__NAMESPACE_LOCAL_SYM __localdep__makepath_s)(__buf, (__SIZE_TYPE__)-1, __drive, __dir, __file, __ext);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__makepath_defined
#define __local___localdep__makepath_defined
#define __localdep__makepath __LIBC_LOCAL_NAME(_makepath)
#endif /* !__local___localdep__makepath_defined */
#endif /* !__local__makepath_defined */
