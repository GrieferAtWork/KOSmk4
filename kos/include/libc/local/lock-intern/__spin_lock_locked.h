/* HASH CRC-32:0xa449d8e8 */
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
#ifndef __local___spin_lock_locked_defined
#define __local___spin_lock_locked_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#ifdef __shared_lock_available
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__spin_lock_locked) __ATTR_IN(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__spin_lock_locked))(unsigned int __KOS_FIXED_CONST *__lock) {
	return !__shared_lock_available((struct shared_lock *)__lock);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___spin_lock_locked_defined
#define __local___localdep___spin_lock_locked_defined
#define __localdep___spin_lock_locked __LIBC_LOCAL_NAME(__spin_lock_locked)
#endif /* !__local___localdep___spin_lock_locked_defined */
#else /* __shared_lock_available */
#undef __local___spin_lock_locked_defined
#endif /* !__shared_lock_available */
#endif /* !__local___spin_lock_locked_defined */
