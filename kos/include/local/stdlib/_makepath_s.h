/* HASH 0xc18b41c7 */
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
#ifndef __local__makepath_s_defined
#define __local__makepath_s_defined 1
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_makepath_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_makepath_s))(char *__buf,
                                                         __SIZE_TYPE__ __buflen,
                                                         char const *__drive,
                                                         char const *__dir,
                                                         char const *__file,
                                                         char const *__ext) {
#line 2464 "kos/src/libc/magic/stdlib.c"
	/* TODO */
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* !__local__makepath_s_defined */
