/* HASH CRC-32:0x2e967578 */
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
#ifndef __local_error_priority_defined
#define __local_error_priority_defined 1
#include <__crt.h>
#include <kos/bits/exception_data.h>
#include <kos/except/codes.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the priority for a given error code, where exceptions
 * with greater priorities should take the place of ones with
 * lower priorities in situations where multiple simultanious
 * errors can't be prevented. */
__LOCAL_LIBC(error_priority) __ATTR_CONST __ATTR_WUNUSED unsigned int
__NOTHROW(__LIBKCALL __LIBC_LOCAL_NAME(error_priority))(__error_code_t __code) {
	__error_class_t __code_class = ERROR_CLASS(__code);
	if (ERRORCLASS_ISRTLPRIORITY(__code_class))
		return 4 + (__code_class - ERRORCLASS_RTL_MIN);
	if (ERRORCLASS_ISHIGHPRIORITY(__code_class))
		return 3;
	if (!ERRORCLASS_ISLOWPRIORITY(__code_class))
		return 2;
	if (__code_class != ERROR_CLASS(ERROR_CODEOF(E_OK)))
		return 1;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_error_priority_defined
#define __local___localdep_error_priority_defined 1
#define __localdep_error_priority __LIBC_LOCAL_NAME(error_priority)
#endif /* !__local___localdep_error_priority_defined */
#endif /* !__local_error_priority_defined */
