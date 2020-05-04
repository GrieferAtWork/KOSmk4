/* HASH CRC-32:0x38fff43c */
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
#ifndef __local_format_length_defined
#define __local_format_length_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Always re-return `datalen' and ignore all other arguments */
__LOCAL_LIBC(format_length) __ATTR_CONST __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_length))(void *__arg,
                                                           /*utf-8*/ char const *__restrict __data,
                                                           __SIZE_TYPE__ __datalen) {
#line 1064 "kos/src/libc/magic/format-printer.c"
	(void)__arg;
	(void)__data;
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_format_length_defined */
