/* HASH CRC-32:0xa680416 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ns_name_compress_defined
#define __local_ns_name_compress_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ns_name_compress) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ns_name_compress))(char const *__srcbuf, unsigned char *__dstbuf, __SIZE_TYPE__ __dstbufsize, unsigned char const **__d, unsigned char const **__e) {
	__COMPILER_IMPURE();
	(void)__srcbuf;
	(void)__dstbuf;
	(void)__dstbufsize;
	(void)__d;
	(void)__e;
	/* TODO */
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ns_name_compress_defined
#define __local___localdep_ns_name_compress_defined
#define __localdep_ns_name_compress __LIBC_LOCAL_NAME(ns_name_compress)
#endif /* !__local___localdep_ns_name_compress_defined */
#endif /* !__local_ns_name_compress_defined */
