/* HASH CRC-32:0xe1b8e1dc */
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
#ifndef __local__open_osfhandle_defined
#ifndef __CRT_DOS
#define __local__open_osfhandle_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_open_osfhandle) __ATTR_WUNUSED __fd_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_open_osfhandle))(__INTPTR_TYPE__ __osfd,
                                                             __oflag_t __flags) {
#line 335 "kos/src/libc/magic/io.c"
	(void)__flags;
	__COMPILER_IMPURE();
	return (__fd_t)__osfd;
}
__NAMESPACE_LOCAL_END
#endif /* !__CRT_DOS */
#endif /* !__local__open_osfhandle_defined */
