/* HASH CRC-32:0x71210066 */
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
#ifndef __local_strcat_s_defined
#define __local_strcat_s_defined 1
#include <__crt.h>
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strcat_s) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strcat_s))(char *__dst,
                                                      __SIZE_TYPE__ __dstsize,
                                                      char const *__src) {
#line 5005 "kos/src/libc/magic/string.c"
	if (!__dst || !__src)
		return __EINVAL;
	while (__dstsize && *__dst) {
		++__dst;
		--__dstsize;
	}
	if (!__dstsize)
		return __EINVAL;
	while ((*__dst++ = *__src++) != 0 && --__dstsize)
		;
	if (!__dstsize)
		return __ERANGE;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_strcat_s_defined */
