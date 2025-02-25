/* HASH CRC-32:0xc2b8267 */
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
#ifndef __local__open_osfhandle_defined
#define __local__open_osfhandle_defined
#include <__crt.h>
#ifndef __CRT_DOS_PRIMARY
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_open_osfhandle) __ATTR_WUNUSED __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_open_osfhandle))(__INTPTR_TYPE__ __osfd, __oflag_t __flags) {
	(void)__flags;
	__COMPILER_IMPURE();
	return (__fd_t)__osfd;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__open_osfhandle_defined
#define __local___localdep__open_osfhandle_defined
#define __localdep__open_osfhandle __LIBC_LOCAL_NAME(_open_osfhandle)
#endif /* !__local___localdep__open_osfhandle_defined */
#else /* !__CRT_DOS_PRIMARY */
#undef __local__open_osfhandle_defined
#endif /* __CRT_DOS_PRIMARY */
#endif /* !__local__open_osfhandle_defined */
