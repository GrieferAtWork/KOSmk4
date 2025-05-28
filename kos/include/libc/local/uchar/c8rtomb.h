/* HASH CRC-32:0x21de77f0 */
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
#ifndef __local_c8rtomb_defined
#define __local_c8rtomb_defined
#include <__crt.h>
#include <bits/crt/mbstate.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c8rtomb) __ATTR_INOUT_OPT(3) __ATTR_OUT_OPT(1) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c8rtomb))(char *__restrict __str, __CHAR8_TYPE__ __c8, struct __mbstate *__mbs) {
	/* We only support UTF-8 locales, so this function is pretty
	 * much  just a  no-op that  simply forwards  data from `c8'
	 * into `*str' */
	if (__str == __NULLPTR) {




		if (__mbs)

		{
			__mbstate_init(__mbs);
		}
	} else {
		*__str = __c8;
	}
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c8rtomb_defined
#define __local___localdep_c8rtomb_defined
#define __localdep_c8rtomb __LIBC_LOCAL_NAME(c8rtomb)
#endif /* !__local___localdep_c8rtomb_defined */
#endif /* !__local_c8rtomb_defined */
