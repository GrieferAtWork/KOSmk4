/* HASH CRC-32:0x3dae34d */
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
#ifndef __local__wsplitpath_defined
#define __local__wsplitpath_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: _wsplitpath_s from stdlib */
#ifndef __local___localdep__wsplitpath_s_defined
#define __local___localdep__wsplitpath_s_defined 1
#ifdef __CRT_HAVE__wsplitpath_s
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1)),__errno_t,__NOTHROW_NCX,__localdep__wsplitpath_s,(__WCHAR_TYPE__ const *__restrict __abspath, __WCHAR_TYPE__ *__drive, __SIZE_TYPE__ __drivelen, __WCHAR_TYPE__ *__dir, __SIZE_TYPE__ __dirlen, __WCHAR_TYPE__ *__file, __SIZE_TYPE__ __filelen, __WCHAR_TYPE__ *__ext, __SIZE_TYPE__ __extlen),_wsplitpath_s,(__abspath,__drive,__drivelen,__dir,__dirlen,__file,__filelen,__ext,__extlen))
#else /* __CRT_HAVE__wsplitpath_s */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_wsplitpath_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__wsplitpath_s __LIBC_LOCAL_NAME(_wsplitpath_s)
#endif /* !__CRT_HAVE__wsplitpath_s */
#endif /* !__local___localdep__wsplitpath_s_defined */
__LOCAL_LIBC(_wsplitpath) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wsplitpath))(__WCHAR_TYPE__ const *__restrict __abspath, __WCHAR_TYPE__ *__drive, __WCHAR_TYPE__ *__dir, __WCHAR_TYPE__ *__file, __WCHAR_TYPE__ *__ext) {
	__localdep__wsplitpath_s(__abspath,
	             __drive, __drive ? 3 : 0,
	             __dir, __dir ? 256 : 0,
	             __file, __file ? 256 : 0,
	             __ext, __ext ? 256 : 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wsplitpath_defined
#define __local___localdep__wsplitpath_defined 1
#define __localdep__wsplitpath __LIBC_LOCAL_NAME(_wsplitpath)
#endif /* !__local___localdep__wsplitpath_defined */
#endif /* !__local__wsplitpath_defined */
