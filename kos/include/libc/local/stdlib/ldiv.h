/* HASH CRC-32:0x788105a4 */
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
#ifndef __local_ldiv_defined
#define __local_ldiv_defined
#include <__crt.h>
#include <bits/crt/div.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ldiv) __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ldiv))(long __numer, long __denom) {
	struct __ldiv_struct __result;
	__result.quot = __numer / __denom;
	__result.rem  = __numer % __denom;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ldiv_defined
#define __local___localdep_ldiv_defined
#define __localdep_ldiv __LIBC_LOCAL_NAME(ldiv)
#endif /* !__local___localdep_ldiv_defined */
#endif /* !__local_ldiv_defined */
