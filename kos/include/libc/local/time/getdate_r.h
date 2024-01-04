/* HASH CRC-32:0xe29037a7 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getdate_r_defined
#define __local_getdate_r_defined
#include <__crt.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getdate_r) __ATTR_IN(1) __ATTR_OUT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getdate_r))(char const *__restrict __string, struct __NAMESPACE_STD_SYM tm *__restrict __resbufp) {
	/* TODO */
	(void)__string;
	(void)__resbufp;
	__COMPILER_IMPURE();
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getdate_r_defined
#define __local___localdep_getdate_r_defined
#define __localdep_getdate_r __LIBC_LOCAL_NAME(getdate_r)
#endif /* !__local___localdep_getdate_r_defined */
#endif /* !__local_getdate_r_defined */
