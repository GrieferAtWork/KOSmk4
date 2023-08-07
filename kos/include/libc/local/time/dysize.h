/* HASH CRC-32:0xf5000e4f */
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
#ifndef __local_dysize_defined
#define __local_dysize_defined
#include <__crt.h>
#include <features.h>
#ifndef __isleap
#define __isleap(__year) ((__year) % 4 == 0 && ((__year) % 100 != 0 || (__year) % 400 == 0))
#endif /* !__isleap */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(dysize) __ATTR_CONST __ATTR_WUNUSED int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(dysize))(__STDC_INT_AS_UINT_T __year) {
	return __isleap(__year) ? 366 : 365;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dysize_defined
#define __local___localdep_dysize_defined
#define __localdep_dysize __LIBC_LOCAL_NAME(dysize)
#endif /* !__local___localdep_dysize_defined */
#endif /* !__local_dysize_defined */
