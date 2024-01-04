/* HASH CRC-32:0xd8f80b79 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_except_priority_defined
#define __local_except_priority_defined
#include <__crt.h>
#include <kos/bits/exception_data.h>
#include <kos/except/codes.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(except_priority) __ATTR_CONST __ATTR_WUNUSED unsigned int
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(except_priority))(__except_code_t __code) {
	__except_class_t __code_class = EXCEPT_CLASS(__code);
	if (EXCEPTCLASS_ISRTLPRIORITY(__code_class))
		return 4 + (__code_class - EXCEPTCLASS_RTL_MIN);
	if (EXCEPTCLASS_ISHIGHPRIORITY(__code_class))
		return 3;
	if (__code_class != EXCEPT_CLASS(EXCEPT_CODEOF(E_OK))) {
		if (!EXCEPTCLASS_ISLOWPRIORITY(__code_class))
			return 2;
		return 1;
	}
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_except_priority_defined
#define __local___localdep_except_priority_defined
#define __localdep_except_priority __LIBC_LOCAL_NAME(except_priority)
#endif /* !__local___localdep_except_priority_defined */
#endif /* !__local_except_priority_defined */
