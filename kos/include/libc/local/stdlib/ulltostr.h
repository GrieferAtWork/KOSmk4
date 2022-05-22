/* HASH CRC-32:0x9ce349a9 */
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
#ifndef __local_ulltostr_defined
#define __local_ulltostr_defined
#include <__crt.h>
#include <libc/template/itoa_digits.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ulltostr) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_OUT(2) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(ulltostr))(__ULONGLONG ___value, char *__buf) {
	do {
		*--__buf = __LOCAL_itoa_decimal(___value % 10);
	} while ((___value /= 10) != 0);
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ulltostr_defined
#define __local___localdep_ulltostr_defined
#define __localdep_ulltostr __LIBC_LOCAL_NAME(ulltostr)
#endif /* !__local___localdep_ulltostr_defined */
#endif /* !__local_ulltostr_defined */
