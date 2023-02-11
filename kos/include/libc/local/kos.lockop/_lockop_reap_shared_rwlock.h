/* HASH CRC-32:0x924e2517 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__lockop_reap_shared_rwlock_defined
#define __local__lockop_reap_shared_rwlock_defined
#include <__crt.h>
#include <kos/bits/shared-rwlock.h>
#if defined(__CRT_HAVE_shared_rwlock_endwrite) || defined(__shared_rwlock_wrwait_send)
#include <kos/anno.h>
#include <kos/bits/lockop.h>
struct shared_rwlock;
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_shared_rwlock_endwrite_defined
#define __local___localdep_shared_rwlock_endwrite_defined
#if defined(__CRT_HAVE_shared_rwlock_endwrite) && defined(__shared_rwlock_wrwait_send)
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
#include <hybrid/__assert.h>
#include <kos/asm/futex.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__NOBLOCK __ATTR_INOUT(1),void,__NOTHROW,__FCALL,__localdep_shared_rwlock_endwrite,(struct shared_rwlock *__restrict __self),shared_rwlock_endwrite,{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(&__self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(__self))
		__shared_rwlock_rdwait_broadcast(__self);
})
#elif defined(__CRT_HAVE_shared_rwlock_endwrite)
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1),__NOTHROW,__FCALL,__localdep_shared_rwlock_endwrite,(struct shared_rwlock *__restrict __self),shared_rwlock_endwrite,(__self))
#elif defined(__shared_rwlock_wrwait_send)
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
#include <hybrid/__assert.h>
#include <kos/asm/futex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __NOBLOCK __ATTR_INOUT(1) void __NOTHROW(__FCALL __localdep_shared_rwlock_endwrite)(struct shared_rwlock *__restrict __self) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	__COMPILER_BARRIER();
	__hybrid_assertf(__self->sl_lock == (__UINTPTR_TYPE__)-1, "Lock isn't in write-mode (%x)", __self->sl_lock);
	__hybrid_atomic_store(&__self->sl_lock, 0, __ATOMIC_RELEASE);
	if (!__shared_rwlock_wrwait_send(__self))
		__shared_rwlock_rdwait_broadcast(__self);
}
#else /* ... */
#undef __local___localdep_shared_rwlock_endwrite_defined
#endif /* !... */
#endif /* !__local___localdep_shared_rwlock_endwrite_defined */
#ifndef __local___localdep_shared_rwlock_trywrite_defined
#define __local___localdep_shared_rwlock_trywrite_defined
#ifdef __CRT_HAVE_shared_rwlock_trywrite
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT(1),__BOOL,__NOTHROW,__FCALL,__localdep_shared_rwlock_trywrite,(struct shared_rwlock *__restrict __self),shared_rwlock_trywrite,{
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (!__hybrid_atomic_cmpxch(&__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
})
#else /* __CRT_HAVE_shared_rwlock_trywrite */
__NAMESPACE_LOCAL_END
#include <hybrid/__atomic.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT(1) __BOOL __NOTHROW(__FCALL __localdep_shared_rwlock_trywrite)(struct shared_rwlock *__restrict __self) {
	__COMPILER_WORKAROUND_GCC_105689(__self);
	if (!__hybrid_atomic_cmpxch(&__self->sl_lock, 0, (__UINTPTR_TYPE__)-1,
	                            __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
		return 0;
	__COMPILER_BARRIER();
	return 1;
}
#endif /* !__CRT_HAVE_shared_rwlock_trywrite */
#endif /* !__local___localdep_shared_rwlock_trywrite_defined */
__LOCAL_LIBC(_lockop_reap_shared_rwlock) __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void
__NOTHROW(__LOCKOP_CC __LIBC_LOCAL_NAME(_lockop_reap_shared_rwlock))(struct lockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      __self
#undef __LOCAL_obj
#define __LOCAL_trylock() (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_trywrite)(__lock)
#define __LOCAL_unlock()  (__NAMESPACE_LOCAL_SYM __localdep_shared_rwlock_endwrite)(__lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__lockop_reap_shared_rwlock_defined
#define __local___localdep__lockop_reap_shared_rwlock_defined
#define __localdep__lockop_reap_shared_rwlock __LIBC_LOCAL_NAME(_lockop_reap_shared_rwlock)
#endif /* !__local___localdep__lockop_reap_shared_rwlock_defined */
#else /* __CRT_HAVE_shared_rwlock_endwrite || __shared_rwlock_wrwait_send */
#undef __local__lockop_reap_shared_rwlock_defined
#endif /* !__CRT_HAVE_shared_rwlock_endwrite && !__shared_rwlock_wrwait_send */
#endif /* !__local__lockop_reap_shared_rwlock_defined */
