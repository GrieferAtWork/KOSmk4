/* HASH CRC-32:0xb31ceca5 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wmemmove_s_defined
#define __local_wmemmove_s_defined
#include <__crt.h>
#include <bits/types.h>
#include <libc/errno.h>
#include <libc/string.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wmemmove_s) __ATTR_INS(3, 4) __ATTR_OUTS(1, 2) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wmemmove_s))(__WCHAR_TYPE__ *__dst, __SIZE_TYPE__ __dstlength, __WCHAR_TYPE__ const *__src, __SIZE_TYPE__ __srclength) {
	if (!__srclength)
		return 0;
	if (!__dst || !__src)
		return 22;
	if (__dstlength < __srclength)
		return 34;
	__libc_memmovec(__dst, __src, __srclength, __SIZEOF_WCHAR_T__);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wmemmove_s_defined
#define __local___localdep_wmemmove_s_defined
#define __localdep_wmemmove_s __LIBC_LOCAL_NAME(wmemmove_s)
#endif /* !__local___localdep_wmemmove_s_defined */
#endif /* !__local_wmemmove_s_defined */
