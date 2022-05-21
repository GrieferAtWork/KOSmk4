/* HASH CRC-32:0x661a1d6b */
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
#ifndef __local___stdio_common_vsc32scanf_defined
#define __local___stdio_common_vsc32scanf_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__stdio_common_vsc32scanf) __ATTR_ACCESS_RO(4) __ATTR_ACCESS_ROS(2, 3) __ATTR_LIBC_C32SCANF(4, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(__stdio_common_vsc32scanf))(__UINT64_TYPE__ __options, __CHAR32_TYPE__ const *__buf, __SIZE_TYPE__ __bufsize, __CHAR32_TYPE__ const *__format, __locale_t __locale, __builtin_va_list __args) {
	/* TODO: format_wscanf() */
	(void)__options;
	(void)__buf;
	(void)__bufsize;
	(void)__format;
	(void)__locale;
	(void)__args;
	__COMPILER_IMPURE();
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___stdio_common_vsc32scanf_defined
#define __local___localdep___stdio_common_vsc32scanf_defined
#define __localdep___stdio_common_vsc32scanf __LIBC_LOCAL_NAME(__stdio_common_vsc32scanf)
#endif /* !__local___localdep___stdio_common_vsc32scanf_defined */
#endif /* !__local___stdio_common_vsc32scanf_defined */
