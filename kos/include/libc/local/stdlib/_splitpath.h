/* HASH CRC-32:0x7b83e156 */
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
#ifndef __local__splitpath_defined
#define __local__splitpath_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__splitpath_s_defined
#define __local___localdep__splitpath_s_defined
#ifdef __CRT_HAVE__splitpath_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1) __ATTR_OUTS(2, 3) __ATTR_OUTS(4, 5) __ATTR_OUTS(6, 7) __ATTR_OUTS(8, 9),__errno_t,__NOTHROW_NCX,__localdep__splitpath_s,(char const *__restrict __abspath, char *__drive, __SIZE_TYPE__ __drivelen, char *__dir, __SIZE_TYPE__ __dirlen, char *__file, __SIZE_TYPE__ __filelen, char *__ext, __SIZE_TYPE__ __extlen),_splitpath_s,(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* __CRT_HAVE__splitpath_s */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_splitpath_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__splitpath_s __LIBC_LOCAL_NAME(_splitpath_s)
#endif /* !__CRT_HAVE__splitpath_s */
#endif /* !__local___localdep__splitpath_s_defined */
__LOCAL_LIBC(_splitpath) __ATTR_IN(1) __ATTR_OUT_OPT(2) __ATTR_OUT_OPT(3) __ATTR_OUT_OPT(4) __ATTR_OUT_OPT(5) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_splitpath))(char const *__restrict __abspath, char *__drive, char *__dir, char *__file, char *__ext) {
	(__NAMESPACE_LOCAL_SYM __localdep__splitpath_s)(__abspath,
	             __drive, __drive ? 3 : 0,
	             __dir, __dir ? 256 : 0,
	             __file, __file ? 256 : 0,
	             __ext, __ext ? 256 : 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__splitpath_defined
#define __local___localdep__splitpath_defined
#define __localdep__splitpath __LIBC_LOCAL_NAME(_splitpath)
#endif /* !__local___localdep__splitpath_defined */
#endif /* !__local__splitpath_defined */
