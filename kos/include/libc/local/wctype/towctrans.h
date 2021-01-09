/* HASH CRC-32:0xd60639b2 */
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
#ifndef __local_towctrans_defined
#define __local_towctrans_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(towctrans) __ATTR_CONST __ATTR_WUNUSED __WINT_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(towctrans))(__WINT_TYPE__ __wc, __wctrans_t __desc) {
	/* TODO */
	(void)__wc;
	(void)__desc;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_towctrans_defined
#define __local___localdep_towctrans_defined 1
#define __localdep_towctrans __LIBC_LOCAL_NAME(towctrans)
#endif /* !__local___localdep_towctrans_defined */
#endif /* !__local_towctrans_defined */
