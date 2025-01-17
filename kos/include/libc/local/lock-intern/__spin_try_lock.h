/* HASH CRC-32:0xed1c4af7 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local___spin_try_lock_defined
#define __local___spin_try_lock_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_tryacquire_defined
#define __local___localdep_shared_lock_tryacquire_defined
#ifdef __CRT_HAVE_shared_lock_tryacquire
__NAMESPACE_LOCAL_END
#include <kos/bits/shared-lock.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INOUT(1),__BOOL,__NOTHROW_NCX,__FCALL,__localdep_shared_lock_tryacquire,(struct shared_lock *__restrict __self),shared_lock_tryacquire,(__self))
#else /* __CRT_HAVE_shared_lock_tryacquire */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_tryacquire.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_shared_lock_tryacquire __LIBC_LOCAL_NAME(shared_lock_tryacquire)
#endif /* !__CRT_HAVE_shared_lock_tryacquire */
#endif /* !__local___localdep_shared_lock_tryacquire_defined */
__NAMESPACE_LOCAL_END
#include <kos/bits/shared-lock.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__spin_try_lock) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__spin_try_lock))(unsigned int *__lock) {
	return (__NAMESPACE_LOCAL_SYM __localdep_shared_lock_tryacquire)((struct shared_lock *)__lock);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___spin_try_lock_defined
#define __local___localdep___spin_try_lock_defined
#define __localdep___spin_try_lock __LIBC_LOCAL_NAME(__spin_try_lock)
#endif /* !__local___localdep___spin_try_lock_defined */
#endif /* !__local___spin_try_lock_defined */
