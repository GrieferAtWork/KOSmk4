/* HASH CRC-32:0x1093a49 */
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
#ifndef __local__get_osfhandle_defined
#define __local__get_osfhandle_defined
#include <__crt.h>
#ifndef __CRT_DOS_PRIMARY
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_get_osfhandle) __ATTR_PURE __ATTR_WUNUSED __ATTR_FDARG(1) __INTPTR_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_get_osfhandle))(__fd_t __fd) {
	__COMPILER_IMPURE();
	return (__INTPTR_TYPE__)__fd;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__get_osfhandle_defined
#define __local___localdep__get_osfhandle_defined
#define __localdep__get_osfhandle __LIBC_LOCAL_NAME(_get_osfhandle)
#endif /* !__local___localdep__get_osfhandle_defined */
#else /* !__CRT_DOS_PRIMARY */
#undef __local__get_osfhandle_defined
#endif /* __CRT_DOS_PRIMARY */
#endif /* !__local__get_osfhandle_defined */
