/* HASH CRC-32:0xf53a0f56 */
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
#ifndef __local_c16ftime_defined
#define __local_c16ftime_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16ftime) __ATTR_NONNULL((1, 3, 4)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16ftime))(__CHAR16_TYPE__ *__restrict __buf,
                                                      __SIZE_TYPE__ __buflen,
                                                      __CHAR16_TYPE__ const *__restrict __format,
                                                      struct __NAMESPACE_STD_SYM tm const *__restrict __tp) {
#line 594 "kos/src/libc/magic/wchar.c"
	if (__buflen)
		*__buf = 0;
	/* TODO */
	(void)__format;
	(void)__tp;
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16ftime_defined */
