/* HASH CRC-32:0xac14e486 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__splitpath_s_defined
#define __local__splitpath_s_defined 1
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_splitpath_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_splitpath_s))(char const *__restrict __abspath,
                                                          char *__drive,
                                                          __SIZE_TYPE__ __drivelen,
                                                          char *__dir,
                                                          __SIZE_TYPE__ __dirlen,
                                                          char *__file,
                                                          __SIZE_TYPE__ __filelen,
                                                          char *__ext,
                                                          __SIZE_TYPE__ __extlen) {
#line 2469 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__splitpath_s_defined */
