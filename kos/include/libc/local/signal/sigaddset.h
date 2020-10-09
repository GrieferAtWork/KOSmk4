/* HASH CRC-32:0x35353ead */
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
#ifndef __local_sigaddset_defined
#define __local_sigaddset_defined 1
#include <__crt.h>
#include <bits/types.h>
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* >> sigaddset(3)
 * Add only the given `signo' to the given signal set
 * @return: 0: Always returns `0' */
__LOCAL_LIBC(sigaddset) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigaddset))(struct __sigset_struct *__set, __signo_t __signo) {
	__ULONGPTR_TYPE__ __mask = __sigset_mask(__signo);
	__ULONGPTR_TYPE__ __word = __sigset_word(__signo);
	__set->__val[__word] |= __mask;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigaddset_defined
#define __local___localdep_sigaddset_defined 1
#define __localdep_sigaddset __LIBC_LOCAL_NAME(sigaddset)
#endif /* !__local___localdep_sigaddset_defined */
#endif /* !__local_sigaddset_defined */
