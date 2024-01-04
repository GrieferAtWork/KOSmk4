/* HASH CRC-32:0x41d4e48b */
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
#ifndef __local_cthread_set_errno_self_defined
#define __local_cthread_set_errno_self_defined
#include <__crt.h>
#include <libc/errno.h>
#ifdef __libc_seterrno
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cthread_set_errno_self) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cthread_set_errno_self))(__errno_t __val) {
	(void)__libc_seterrno(__val);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cthread_set_errno_self_defined
#define __local___localdep_cthread_set_errno_self_defined
#define __localdep_cthread_set_errno_self __LIBC_LOCAL_NAME(cthread_set_errno_self)
#endif /* !__local___localdep_cthread_set_errno_self_defined */
#else /* __libc_seterrno */
#undef __local_cthread_set_errno_self_defined
#endif /* !__libc_seterrno */
#endif /* !__local_cthread_set_errno_self_defined */
