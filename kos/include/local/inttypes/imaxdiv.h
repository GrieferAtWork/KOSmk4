/* HASH CRC-32:0x2aa7c3e1 */
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
#ifndef __local_imaxdiv_defined
#define __local_imaxdiv_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(imaxdiv) __ATTR_CONST struct __imaxdiv_struct
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(imaxdiv))(__INTMAX_TYPE__ __numer,
                                                 __INTMAX_TYPE__ __denom) {
#line 499 "kos/src/libc/magic/inttypes.c"
	struct __imaxdiv_struct __result;
	__result.quot = __numer / __denom;
	__result.rem  = __numer % __denom;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_imaxdiv_defined */
