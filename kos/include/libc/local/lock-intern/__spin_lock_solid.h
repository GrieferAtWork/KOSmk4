/* HASH CRC-32:0x2953507e */
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
#ifndef __local___spin_lock_solid_defined
#define __local___spin_lock_solid_defined
#include <__crt.h>
#include <kos/bits/shared-lock.h>
#if defined(__CRT_HAVE_shared_lock_acquire) || defined(__KERNEL__) || defined(__shared_lock_wait_impl)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_lock_acquire_defined
#define __local___localdep_shared_lock_acquire_defined
#ifdef __CRT_HAVE_shared_lock_acquire
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT_VOID(__LIBC,__BLOCKING __ATTR_INOUT(1),__THROWING(E_WOULDBLOCK, E_INTERRUPT),__FCALL,__localdep_shared_lock_acquire,(struct shared_lock *__restrict __self),shared_lock_acquire,(__self))
#elif defined(__KERNEL__) || defined(__shared_lock_wait_impl)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.sched.shared-lock/shared_lock_acquire.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_shared_lock_acquire __LIBC_LOCAL_NAME(shared_lock_acquire)
#else /* ... */
#undef __local___localdep_shared_lock_acquire_defined
#endif /* !... */
#endif /* !__local___localdep_shared_lock_acquire_defined */
__LOCAL_LIBC(__spin_lock_solid) __ATTR_INOUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(__spin_lock_solid))(unsigned int *__lock) {
	(__NAMESPACE_LOCAL_SYM __localdep_shared_lock_acquire)((struct shared_lock *)__lock);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep___spin_lock_solid_defined
#define __local___localdep___spin_lock_solid_defined
#define __localdep___spin_lock_solid __LIBC_LOCAL_NAME(__spin_lock_solid)
#endif /* !__local___localdep___spin_lock_solid_defined */
#else /* __CRT_HAVE_shared_lock_acquire || __KERNEL__ || __shared_lock_wait_impl */
#undef __local___spin_lock_solid_defined
#endif /* !__CRT_HAVE_shared_lock_acquire && !__KERNEL__ && !__shared_lock_wait_impl */
#endif /* !__local___spin_lock_solid_defined */
