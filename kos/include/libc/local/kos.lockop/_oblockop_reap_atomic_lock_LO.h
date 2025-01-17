/* HASH CRC-32:0xd9f6c6de */
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
#ifndef __local__oblockop_reap_atomic_lock_LO_defined
#define __local__oblockop_reap_atomic_lock_LO_defined
#include <__crt.h>
#include <kos/anno.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__oblockop_reap_atomic_lock_defined
#define __local___localdep__oblockop_reap_atomic_lock_defined
#ifdef __CRT_HAVE_oblockop_reap_atomic_lock
__NAMESPACE_LOCAL_END
#include <kos/bits/lockop.h>
struct atomic_lock;
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,__localdep__oblockop_reap_atomic_lock,(struct oblockop_slist *__restrict __self, struct atomic_lock *__restrict __lock, void *__restrict __obj),oblockop_reap_atomic_lock,(__self,__lock,__obj))
#else /* __CRT_HAVE_oblockop_reap_atomic_lock */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.lockop/_oblockop_reap_atomic_lock.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__oblockop_reap_atomic_lock __LIBC_LOCAL_NAME(_oblockop_reap_atomic_lock)
#endif /* !__CRT_HAVE_oblockop_reap_atomic_lock */
#endif /* !__local___localdep__oblockop_reap_atomic_lock_defined */
__NAMESPACE_LOCAL_END
#include <kos/bits/lockop.h>
#include <hybrid/sched/atomic-lock.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_oblockop_reap_atomic_lock_LO) __NOBLOCK __ATTR_NONNULL((1)) void
__NOTHROW(__LOCKOP_CC __LIBC_LOCAL_NAME(_oblockop_reap_atomic_lock_LO))(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_atomic_lock) {
	struct __LOCAL_tobj {
		struct atomic_lock    __lto_lock;
#if __SIZEOF_ATOMIC_LOCK < __SIZEOF_POINTER__
		__BYTE_TYPE__         __lto_pad[__SIZEOF_POINTER__ - __SIZEOF_ATOMIC_LOCK];
#endif /* __SIZEOF_ATOMIC_LOCK < __SIZEOF_POINTER__ */
		struct oblockop_slist __lto_self;
	} *__tobj = (struct __LOCAL_tobj *)((__BYTE_TYPE__ *)__obj + __offsetof_atomic_lock);
	(__NAMESPACE_LOCAL_SYM __localdep__oblockop_reap_atomic_lock)(&__tobj->__lto_self, &__tobj->__lto_lock, __obj);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__oblockop_reap_atomic_lock_LO_defined
#define __local___localdep__oblockop_reap_atomic_lock_LO_defined
#define __localdep__oblockop_reap_atomic_lock_LO __LIBC_LOCAL_NAME(_oblockop_reap_atomic_lock_LO)
#endif /* !__local___localdep__oblockop_reap_atomic_lock_LO_defined */
#endif /* !__local__oblockop_reap_atomic_lock_LO_defined */
