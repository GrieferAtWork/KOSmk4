/* HASH CRC-32:0xbffa9e51 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_ldiv_defined
#define __local_ldiv_defined 1
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ldiv) __ATTR_CONST __ATTR_WUNUSED struct __ldiv_struct
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ldiv))(long __numer,
                                                  long __denom) {
#line 536 "kos/src/libc/magic/stdlib.c"
	struct __ldiv_struct __result;
	__result.quot = __numer / __denom;
	__result.rem  = __numer % __denom;
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_ldiv_defined */
