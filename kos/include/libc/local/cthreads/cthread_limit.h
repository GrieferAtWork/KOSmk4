/* HASH CRC-32:0xad8c91d */
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
#ifndef __local_cthread_limit_defined
#define __local_cthread_limit_defined
#include <__crt.h>
#include <hybrid/limitcore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cthread_limit) __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cthread_limit))(void) {
	__COMPILER_IMPURE();
	return __INT_MAX__;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cthread_limit_defined
#define __local___localdep_cthread_limit_defined
#define __localdep_cthread_limit __LIBC_LOCAL_NAME(cthread_limit)
#endif /* !__local___localdep_cthread_limit_defined */
#endif /* !__local_cthread_limit_defined */
