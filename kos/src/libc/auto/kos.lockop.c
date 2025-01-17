/* HASH CRC-32:0x6a85eb4b */
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
#ifndef GUARD_LIBC_AUTO_KOS_LOCKOP_C
#define GUARD_LIBC_AUTO_KOS_LOCKOP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "kos.lockop.h"
#include "kos.sched.shared-rwlock.h"

DECL_BEGIN

#include <hybrid/host.h>
#if defined(__OPTIMIZE_SIZE__) && defined(__x86_64__)
DEFINE_INTERN_ALIAS_P_VOID(libc_lockop_reap_ex,libc_oblockop_reap_ex,__NOBLOCK ATTR_INOUT(1) NONNULL((2, 3)),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, __BOOL (__LOCKOP_CC *trylock)(void *cookie), void (__LOCKOP_CC *unlock)(void *cookie), void *cookie),(self,trylock,unlock,cookie));
#else /* __OPTIMIZE_SIZE__ && __x86_64__ */
#include <kos/bits/lockop.h>
#include <hybrid/__atomic.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) NONNULL((2, 3)) void
NOTHROW(__LOCKOP_CC libc_lockop_reap_ex)(struct lockop_slist *__restrict self,
                                         __BOOL (__LOCKOP_CC *trylock)(void *cookie),
                                         void (__LOCKOP_CC *unlock)(void *cookie),
                                         void *cookie) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#undef __LOCAL_obj
#define __LOCAL_trylock() (*trylock)(cookie)
#define __LOCAL_unlock()  (*unlock)(cookie)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#endif /* !__OPTIMIZE_SIZE__ || !__x86_64__ */
#include <kos/bits/lockop.h>
#include <hybrid/__atomic.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) NONNULL((2, 3, 5)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_ex)(struct oblockop_slist *__restrict self,
                                           __BOOL (__LOCKOP_CC *trylock)(void *cookie),
                                           void (__LOCKOP_CC *unlock)(void *cookie),
                                           void *cookie,
                                           void *__restrict obj) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#define __LOCAL_obj       obj
#define __LOCAL_trylock() (*trylock)(cookie)
#define __LOCAL_unlock()  (*unlock)(cookie)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#if defined(__OPTIMIZE_SIZE__) && defined(__x86_64__)
DEFINE_INTERN_ALIAS_P_VOID(libc_lockop_reap_atomic_lock,libc_oblockop_reap_atomic_lock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct atomic_lock *__restrict lock),(self,lock));
#else /* __OPTIMIZE_SIZE__ && __x86_64__ */
#include <hybrid/sched/atomic-lock.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void
NOTHROW(__LOCKOP_CC libc_lockop_reap_atomic_lock)(struct lockop_slist *__restrict self,
                                                  struct atomic_lock *__restrict lock) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#undef __LOCAL_obj
#define __LOCAL_trylock() atomic_lock_tryacquire(lock)
#define __LOCAL_unlock()  atomic_lock_release(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#endif /* !__OPTIMIZE_SIZE__ || !__x86_64__ */
#include <hybrid/sched/atomic-lock.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_lock)(struct oblockop_slist *__restrict self,
                                                    struct atomic_lock *__restrict lock,
                                                    void *__restrict obj) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#define __LOCAL_obj       obj
#define __LOCAL_trylock() atomic_lock_tryacquire(lock)
#define __LOCAL_unlock()  atomic_lock_release(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#if defined(__OPTIMIZE_SIZE__) && defined(__x86_64__)
DEFINE_INTERN_ALIAS_P_VOID(libc_lockop_reap_atomic_rwlock,libc_oblockop_reap_atomic_rwlock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct atomic_rwlock *__restrict lock),(self,lock));
#else /* __OPTIMIZE_SIZE__ && __x86_64__ */
#include <hybrid/sched/atomic-rwlock.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void
NOTHROW(__LOCKOP_CC libc_lockop_reap_atomic_rwlock)(struct lockop_slist *__restrict self,
                                                    struct atomic_rwlock *__restrict lock) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#undef __LOCAL_obj
#define __LOCAL_trylock() atomic_rwlock_trywrite(lock)
#define __LOCAL_unlock()  atomic_rwlock_endwrite(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#endif /* !__OPTIMIZE_SIZE__ || !__x86_64__ */
#include <hybrid/sched/atomic-rwlock.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_rwlock)(struct oblockop_slist *__restrict self,
                                                      struct atomic_rwlock *__restrict lock,
                                                      void *__restrict obj) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#define __LOCAL_obj       obj
#define __LOCAL_trylock() atomic_rwlock_trywrite(lock)
#define __LOCAL_unlock()  atomic_rwlock_endwrite(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#if defined(__OPTIMIZE_SIZE__) && defined(__x86_64__)
DEFINE_INTERN_ALIAS_P_VOID(libc_lockop_reap_shared_lock,libc_oblockop_reap_shared_lock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct shared_lock *__restrict lock),(self,lock));
#else /* __OPTIMIZE_SIZE__ && __x86_64__ */
#include <kos/sched/shared-lock.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void
NOTHROW(__LOCKOP_CC libc_lockop_reap_shared_lock)(struct lockop_slist *__restrict self,
                                                  struct shared_lock *__restrict lock) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#undef __LOCAL_obj
#define __LOCAL_trylock() shared_lock_tryacquire(lock)
#define __LOCAL_unlock()  shared_lock_release(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#endif /* !__OPTIMIZE_SIZE__ || !__x86_64__ */
#include <kos/sched/shared-lock.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_shared_lock)(struct oblockop_slist *__restrict self,
                                                    struct shared_lock *__restrict lock,
                                                    void *__restrict obj) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#define __LOCAL_obj       obj
#define __LOCAL_trylock() shared_lock_tryacquire(lock)
#define __LOCAL_unlock()  shared_lock_release(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#if defined(__OPTIMIZE_SIZE__) && defined(__x86_64__)
DEFINE_INTERN_ALIAS_P_VOID(libc_lockop_reap_shared_rwlock,libc_oblockop_reap_shared_rwlock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct shared_rwlock *__restrict lock),(self,lock));
#else /* __OPTIMIZE_SIZE__ && __x86_64__ */
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) void
NOTHROW(__LOCKOP_CC libc_lockop_reap_shared_rwlock)(struct lockop_slist *__restrict self,
                                                    struct shared_rwlock *__restrict lock) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#undef __LOCAL_obj
#define __LOCAL_trylock() libc_shared_rwlock_trywrite(lock)
#define __LOCAL_unlock()  libc_shared_rwlock_endwrite(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#endif /* !__OPTIMIZE_SIZE__ || !__x86_64__ */
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_shared_rwlock)(struct oblockop_slist *__restrict self,
                                                      struct shared_rwlock *__restrict lock,
                                                      void *__restrict obj) {
#ifndef __INTELLISENSE__
#define __LOCAL_self      self
#define __LOCAL_obj       obj
#define __LOCAL_trylock() libc_shared_rwlock_trywrite(lock)
#define __LOCAL_unlock()  libc_shared_rwlock_endwrite(lock)
#include <libc/template/lockop.h>
#endif /* !__INTELLISENSE__ */
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK NONNULL((1)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_lock_OL)(void *__restrict obj,
                                                       ptrdiff_t offsetof_lockop_slist) {
	struct __LOCAL_tobj {
		struct oblockop_slist lto_self;
		struct atomic_lock    lto_lock;
	} *tobj = (struct __LOCAL_tobj *)((byte_t *)obj + offsetof_lockop_slist);
	libc_oblockop_reap_atomic_lock(&tobj->lto_self, &tobj->lto_lock, obj);
}
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK NONNULL((1)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_lock_LO)(void *__restrict obj,
                                                       ptrdiff_t offsetof_atomic_lock) {
	struct __LOCAL_tobj {
		struct atomic_lock    lto_lock;
#if __SIZEOF_ATOMIC_LOCK < __SIZEOF_POINTER__
		__BYTE_TYPE__         __lto_pad[__SIZEOF_POINTER__ - __SIZEOF_ATOMIC_LOCK];
#endif /* __SIZEOF_ATOMIC_LOCK < __SIZEOF_POINTER__ */
		struct oblockop_slist lto_self;
	} *tobj = (struct __LOCAL_tobj *)((byte_t *)obj + offsetof_atomic_lock);
	libc_oblockop_reap_atomic_lock(&tobj->lto_self, &tobj->lto_lock, obj);
}
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK NONNULL((1)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_rwlock_OL)(void *__restrict obj,
                                                         ptrdiff_t offsetof_lockop_slist) {
	struct __LOCAL_tobj {
		struct oblockop_slist lto_self;
		struct atomic_rwlock  lto_lock;
	} *tobj = (struct __LOCAL_tobj *)((byte_t *)obj + offsetof_lockop_slist);
	libc_oblockop_reap_atomic_rwlock(&tobj->lto_self, &tobj->lto_lock, obj);
}
INTERN ATTR_SECTION(".text.crt.sched.lockop") __NOBLOCK NONNULL((1)) void
NOTHROW(__LOCKOP_CC libc_oblockop_reap_atomic_rwlock_LO)(void *__restrict obj,
                                                         ptrdiff_t offsetof_atomic_rwlock) {
	struct __LOCAL_tobj {
		struct atomic_rwlock  lto_lock;
#if __SIZEOF_ATOMIC_RWLOCK < __SIZEOF_POINTER__
		__BYTE_TYPE__         __lto_pad[__SIZEOF_POINTER__ - __SIZEOF_ATOMIC_RWLOCK];
#endif /* __SIZEOF_ATOMIC_RWLOCK < __SIZEOF_POINTER__ */
		struct oblockop_slist lto_self;
	} *tobj = (struct __LOCAL_tobj *)((byte_t *)obj + offsetof_atomic_rwlock);
	libc_oblockop_reap_atomic_rwlock(&tobj->lto_self, &tobj->lto_lock, obj);
}

DECL_END

DEFINE_PUBLIC_ALIAS_P_VOID(lockop_reap_ex,libc_lockop_reap_ex,__NOBLOCK ATTR_INOUT(1) NONNULL((2, 3)),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, __BOOL (__LOCKOP_CC *trylock)(void *cookie), void (__LOCKOP_CC *unlock)(void *cookie), void *cookie),(self,trylock,unlock,cookie));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_ex,libc_oblockop_reap_ex,__NOBLOCK ATTR_INOUT(1) NONNULL((2, 3, 5)),NOTHROW,__LOCKOP_CC,(struct oblockop_slist *__restrict self, __BOOL (__LOCKOP_CC *trylock)(void *cookie), void (__LOCKOP_CC *unlock)(void *cookie), void *cookie, void *__restrict obj),(self,trylock,unlock,cookie,obj));
DEFINE_PUBLIC_ALIAS_P_VOID(lockop_reap_atomic_lock,libc_lockop_reap_atomic_lock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct atomic_lock *__restrict lock),(self,lock));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_atomic_lock,libc_oblockop_reap_atomic_lock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)),NOTHROW,__LOCKOP_CC,(struct oblockop_slist *__restrict self, struct atomic_lock *__restrict lock, void *__restrict obj),(self,lock,obj));
DEFINE_PUBLIC_ALIAS_P_VOID(lockop_reap_atomic_rwlock,libc_lockop_reap_atomic_rwlock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct atomic_rwlock *__restrict lock),(self,lock));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_atomic_rwlock,libc_oblockop_reap_atomic_rwlock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)),NOTHROW,__LOCKOP_CC,(struct oblockop_slist *__restrict self, struct atomic_rwlock *__restrict lock, void *__restrict obj),(self,lock,obj));
DEFINE_PUBLIC_ALIAS_P_VOID(lockop_reap_shared_lock,libc_lockop_reap_shared_lock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct shared_lock *__restrict lock),(self,lock));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_shared_lock,libc_oblockop_reap_shared_lock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)),NOTHROW,__LOCKOP_CC,(struct oblockop_slist *__restrict self, struct shared_lock *__restrict lock, void *__restrict obj),(self,lock,obj));
DEFINE_PUBLIC_ALIAS_P_VOID(lockop_reap_shared_rwlock,libc_lockop_reap_shared_rwlock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2),NOTHROW,__LOCKOP_CC,(struct lockop_slist *__restrict self, struct shared_rwlock *__restrict lock),(self,lock));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_shared_rwlock,libc_oblockop_reap_shared_rwlock,__NOBLOCK ATTR_INOUT(1) ATTR_INOUT(2) NONNULL((3)),NOTHROW,__LOCKOP_CC,(struct oblockop_slist *__restrict self, struct shared_rwlock *__restrict lock, void *__restrict obj),(self,lock,obj));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_atomic_lock_OL,libc_oblockop_reap_atomic_lock_OL,__NOBLOCK NONNULL((1)),NOTHROW,__LOCKOP_CC,(void *__restrict obj, ptrdiff_t offsetof_lockop_slist),(obj,offsetof_lockop_slist));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_atomic_lock_LO,libc_oblockop_reap_atomic_lock_LO,__NOBLOCK NONNULL((1)),NOTHROW,__LOCKOP_CC,(void *__restrict obj, ptrdiff_t offsetof_atomic_lock),(obj,offsetof_atomic_lock));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_atomic_rwlock_OL,libc_oblockop_reap_atomic_rwlock_OL,__NOBLOCK NONNULL((1)),NOTHROW,__LOCKOP_CC,(void *__restrict obj, ptrdiff_t offsetof_lockop_slist),(obj,offsetof_lockop_slist));
DEFINE_PUBLIC_ALIAS_P_VOID(oblockop_reap_atomic_rwlock_LO,libc_oblockop_reap_atomic_rwlock_LO,__NOBLOCK NONNULL((1)),NOTHROW,__LOCKOP_CC,(void *__restrict obj, ptrdiff_t offsetof_atomic_rwlock),(obj,offsetof_atomic_rwlock));

#endif /* !GUARD_LIBC_AUTO_KOS_LOCKOP_C */
