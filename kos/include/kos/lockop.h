/* HASH CRC-32:0xefdac24d */
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
#ifndef _KOS_LOCKOP_H
#define _KOS_LOCKOP_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <hybrid/__atomic.h>
#include <kos/anno.h>
#include <kos/bits/lockop.h>
#include <kos/bits/shared-lock.h>
#include <kos/bits/shared-rwlock.h>

#ifndef __KERNEL__
#include <kos/syscalls.h>
#endif /* !__KERNEL__ */

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#ifndef __CRT_HAVE_XSC
#define __CRT_HAVE_XSC(name) 0
#endif /* !__CRT_HAVE_XSC */

#ifdef __CC__
__SYSDECL_BEGIN

/* Helper  structures to implement  general-purpose lock operation handling.
 * The basic idea here is to make it possible to enqueue a set of operations
 * that will be performed asynchronously once some kind of lock becomes
 * available:
 *
 * >> void _reap(void);
 * >> #define must_reap()   ...
 * >> #define reap()        (void)(!must_reap() || (_reap(), 0))
 * >> #define try_acquire() try_acquire_lock(&lock)
 * >> #define acquire()     acquire_lock(&lock)
 * >> #define release()     (release_lock(&lock), reap())
 * >>
 * >> ...
 * >>
 * >> void _reap(void) {
 * >>     do {
 * >>         if (!try_acquire())
 * >>             break;
 * >>         REAP_LOCK_OPS();
 * >>         release_lock(&lock);
 * >>         REAP_POST_LOCK_OPS();
 * >>     } while (must_reap());
 * >> }
 *
 * This kind of implementation is  sequentially consistent in that it  can
 * guaranty the execution of all  enqueued lock operations "at some  point
 * in  the future", so-long  as the user of  the locking functionality can
 * guaranty that locks  are not  held forever, but  are _always_  released
 * eventually. As such, the lockop mechanism works best with atomic locks,
 * since  the eventual release of an atomic lock following its acquisition
 * is  one of  the logical  consequences of  their semantical requirements
 * regarding the  non-blocking-ness of  anything  performed while  such  a
 * lock is held.
 *
 * Furthermore, lock operations can be used to perform otherwise  blocking
 * operations in  the context  of certain  locks being  held, making  them
 * perfect for augmenting and facilitating the non-blocking-ness of object
 * finalizers that need to acquire locks to other data structures, such as
 * lists,  in order  to remove (part  of) the object  being destroyed, and
 * making  this possible by trying to acquire  such a lock, and making use
 * of lock operations  if the  lock cannot be  acquired without  blocking.
 * This then allows for the part  of the object's finalization that  needs
 * a certain lock to be held, to be performed as an asynchronous operation
 * executed once said lock becomes available:
 *
 * >> struct myobj;
 * >> LIST_HEAD(myobj_list, myobj);
 * >> struct myobj {
 * >>     LIST_ENTRY(myobj) ent;
 * >>     union {
 * >>         struct lockop     lop;
 * >>         struct postlockop postlop;
 * >>     };
 * >> };
 * >>
 * >> PRIVATE struct myobj_list   list    = LIST_HEAD_INITIALIZER(list);
 * >> PRIVATE struct atomic_lock  lock    = ATOMIC_LOCK_INIT;
 * >> PRIVATE struct lockop_slist lockops = SLIST_HEAD_INITIALIZER(lockops);
 * >> #define _reap()      _lockop_reap(&lockops, &lock)
 * >> #define reap()       lockop_reap(&lockops, &lock)
 * >> #define tryacquire() atomic_lock_tryacquire(&lock)
 * >> #define acquire()    atomic_lock_acquire(&lock)
 * >> #define _release()   atomic_lock_release(&lock)
 * >> #define release()    (_release(), reap())
 * >>
 * >> PRIVATE NOBLOCK NONNULL((1)) void
 * >> NOTHROW(LOCKOP_CC myobj_destroy_postlop)(struct postlockop *__restrict self) {
 * >>     struct myobj *me = container_of(self, struct myobj, postlop);
 * >>     free(me);
 * >> }
 * >> PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
 * >> NOTHROW(LOCKOP_CC myobj_destroy_lop)(struct lockop *__restrict self) {
 * >>     struct myobj *me = container_of(self, struct myobj, lop);
 * >>     LIST_REMOVE(me, ent);
 * >>     // free() the object _after_ releasing the lock so the lock
 * >>     // itself can be released sonner than it could otherwise be.
 * >>     me->postlop.plo_func = &myobj_destroy_postlop;
 * >>     return &me->postlop;
 * >> }
 * >>
 * >> // Non-blocking async-remove-object-from-locked-list-and-free-object function.
 * >> PRIVATE NOBLOCK NONNULL((1)) void
 * >> NOTHROW(myobj_destroy)(struct myobj *self) {
 * >>     if (tryacquire()) {
 * >>         LIST_REMOVE(self, ent);
 * >>         release();
 * >>         free(self);
 * >>     } else {
 * >>         self->lop.lo_func = &myobj_destroy_lop;
 * >>         lockop_enqueue(&lockops, &self->lop); // or `SLIST_ATOMIC_INSERT(&lockops, &self->lop, lo_link)'
 * >>         _reap();
 * >>     }
 * >> }
 */

/* Calling convention for functions from the lockop API */
#ifndef LOCKOP_CC
#define LOCKOP_CC __LOCKOP_CC
#endif /* !LOCKOP_CC */


/* Callback prototype for an operation to-be performed once locks have been released. */
typedef __postlockop_callback_t postlockop_callback_t;
typedef __obpostlockop_callback_t obpostlockop_callback_t;
typedef __lockop_callback_t lockop_callback_t;
typedef __oblockop_callback_t oblockop_callback_t;

/* Helper template for copy+paste:
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(LOCKOP_CC mystruct_action_postlop)(Tobpostlockop(mystruct) *__restrict self,
                                           struct mystruct *__restrict obj);
PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mystruct) *
NOTHROW(LOCKOP_CC mystruct_action_lop)(Toblockop(mystruct) *__restrict self,
                                       struct mystruct *__restrict obj);
*/


/* Helpers to make object-based lockop callbacks easier to integrate */
#ifdef __cplusplus
extern "C++" {
#define Toblockop(type)                    _Toblockop<struct type>
#define Tobpostlockop(type)                _Tobpostlockop<struct type>
#define Toblockop_slist(type)              _Toblockop_slist<struct type>
#define Tobpostlockop_slist(type)          _Tobpostlockop_slist<struct type>
template<class __T> struct _Toblockop;
template<class __T> struct _Tobpostlockop;
#ifdef __COMPILER_HAVE_CXX_TEMPLATE_USING
#define Toblockop_callback_t(type)         _Toblockop_callback_t<struct type>
#define Tobpostlockop_callback_t(type)     _Tobpostlockop_callback_t<struct type>
#define Toblockop_callback_t_tpl(type)     _Toblockop_callback_t<struct type>
#define Tobpostlockop_callback_t_tpl(type) _Tobpostlockop_callback_t<struct type>
template<class __T> using _Toblockop_callback_t     = __NOBLOCK __ATTR_NONNULL_T((1)) _Tobpostlockop<__T> * __NOTHROW_T(LOCKOP_CC *)(_Toblockop<__T> *__restrict __self, __T *__restrict __obj);
template<class __T> using _Tobpostlockop_callback_t = __NOBLOCK __ATTR_NONNULL_T((1)) void __NOTHROW_T(LOCKOP_CC *)(_Tobpostlockop<__T> *__restrict __self, __T *__restrict __obj);
#else /* __COMPILER_HAVE_CXX_TEMPLATE_USING */
#define Toblockop_callback_t(type)         _Toblockop_callback_t<struct type>::__T
#define Tobpostlockop_callback_t(type)     _Tobpostlockop_callback_t<struct type>::__T
#define Toblockop_callback_t_tpl(type)     __CXX_DEDUCE_TYPENAME _Toblockop_callback_t<struct type>::__T
#define Tobpostlockop_callback_t_tpl(type) __CXX_DEDUCE_TYPENAME _Tobpostlockop_callback_t<struct type>::__T
template<class __T> struct _Toblockop_callback_t     { typedef __NOBLOCK __ATTR_NONNULL_T((1)) _Tobpostlockop<__T> * __NOTHROW_T(LOCKOP_CC *__T)(_Toblockop<__T> *__restrict __self, __T *__restrict __obj); };
template<class __T> struct _Tobpostlockop_callback_t { typedef __NOBLOCK __ATTR_NONNULL_T((1)) void __NOTHROW_T(LOCKOP_CC *__T)(_Tobpostlockop<__T> *__restrict __self, __T *__restrict __obj); };
#endif /* !__COMPILER_HAVE_CXX_TEMPLATE_USING */

template<class __T> struct _Toblockop {
/*	SLIST_ENTRY(_Toblockop<__T>)          olo_link;  * [0..1] Next lock operation. */
	struct { _Toblockop<__T> *sle_next; } olo_link; /* [0..1] Next lock operation. */
/*	_Toblockop_callback_t<__T>            olo_func;  * [1..1][const] Operation to perform. */
	__NOBLOCK __ATTR_NONNULL_T((1)) _Tobpostlockop<__T> * __NOTHROW_T(LOCKOP_CC *olo_func)(_Toblockop<__T> *__restrict __self, __T *__restrict __obj); /* [1..1][const] Operation to perform. */
};
template<class __T> struct _Tobpostlockop {
/*	SLIST_ENTRY(_Tobpostlockop<__T>)          oplo_link;  * [0..1] Next post-lock operation. */
	struct { _Tobpostlockop<__T> *sle_next; } oplo_link; /* [0..1] Next post-lock operation. */
/*	_Tobpostlockop_callback_t<__T>            oplo_func;  * [1..1][const] Callback to invoke. */
	__NOBLOCK __ATTR_NONNULL_T((1)) void __NOTHROW_T(LOCKOP_CC *oplo_func)(_Tobpostlockop<__T> *__restrict __self, __T *__restrict __obj); /* [1..1][const] Callback to invoke. */
};
/* template<class __T> SLIST_HEAD(_Toblockop_slist, _Toblockop<__T>); */
/* template<class __T> SLIST_HEAD(_Tobpostlockop_slist, _Tobpostlockop<__T>); */
template<class __T> struct _Toblockop_slist { struct _Toblockop<__T> *slh_first; /* [0..1] List head */ };
template<class __T> struct _Tobpostlockop_slist { struct _Tobpostlockop<__T> *slh_first; /* [0..1] List head */ };
} /* extern "C++" */
#else /* __cplusplus */
#define Toblockop(type)                    struct oblockop
#define Tobpostlockop(type)                struct obpostlockop
#define Toblockop_slist(type)              struct oblockop_slist
#define Tobpostlockop_slist(type)          struct obpostlockop_slist
#define Toblockop_callback_t(type)         oblockop_callback_t
#define Tobpostlockop_callback_t(type)     obpostlockop_callback_t
#define Toblockop_callback_t_tpl(type)     oblockop_callback_t
#define Tobpostlockop_callback_t_tpl(type) obpostlockop_callback_t
#endif /* !__cplusplus */

struct atomic_lock;
struct atomic_rwlock;
struct shared_lock;
struct shared_rwlock;


/* >> void lockop_enqueue(struct lockop_slist *__restrict self, struct lockop *__restrict lop);
 * >> void oblockop_enqueue(struct oblockop_slist *__restrict self, struct oblockop *__restrict lop);
 * >> void oblockop_enqueue(struct Toblockop_slist(T) *__restrict self, struct Toblockop(T) *__restrict lop);
 * NOTE: To add lock ops to a pending list, use `lockop_enqueue(self, lop)',
 *       which is  equivalent  to  `SLIST_ATOMIC_INSERT(self, lop, lo_link)' */
#define lockop_enqueue(self, lop)   __lockop_enqueue(self, lop, (lop)->lo_link)
#define oblockop_enqueue(self, lop) __lockop_enqueue(self, lop, (lop)->olo_link)
#define __lockop_enqueue(self, lop, lop_link)                                           \
	do {                                                                                \
		lop_link.sle_next = __hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE); \
		__COMPILER_WRITE_BARRIER();                                                     \
	} while (!__hybrid_atomic_cmpxch(&(self)->slh_first, lop_link.sle_next, lop,        \
	                                 __ATOMIC_RELEASE, __ATOMIC_RELAXED))




/* >> ATTR_PURE WUNUSED bool lockop_mustreap(struct lockop_slist const *__restrict self);
 * >> ATTR_PURE WUNUSED bool lockop_mustreap(struct oblockop_slist const *__restrict self);
 * >> ATTR_PURE WUNUSED bool lockop_mustreap(struct Toblockop_slist(T) const *__restrict self);
 * Check if the given lockop-list `self' must  be reaped (that is: contains pending  callbacks) */
#define lockop_mustreap(self) \
	(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#define oblockop_mustreap(self) lockop_mustreap(self)

/* >> void lockop_reap_ex(struct lockop_slist *__restrict self, bool (LOCKOP_CC *trylock)(void *cookie), void (LOCKOP_CC *unlock)(void *cookie), void *cookie);
 * >> void oblockop_reap_ex(struct oblockop_slist *__restrict self, bool (LOCKOP_CC *trylock)(void *cookie), void (LOCKOP_CC *unlock)(void *cookie), void *cookie, void *obj);
 * >> void oblockop_reap_ex(struct Toblockop_slist(T) *__restrict self, bool (LOCKOP_CC *trylock)(void *cookie), void (LOCKOP_CC *unlock)(void *cookie), void *cookie, T *obj);
 * Functions to reap pending lock operations. */
#ifdef __OPTIMIZE_SIZE__
#define lockop_reap_ex(self, trylock, unlock, cookie) \
	_lockop_reap_ex(self, trylock, unlock, cookie)
#define oblockop_reap_ex(self, trylock, unlock, cookie, obj) \
	_oblockop_reap_ex(self, trylock, unlock, cookie, obj)
#else /* __OPTIMIZE_SIZE__ */
#define lockop_reap_ex(self, trylock, unlock, cookie) \
	(void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_lockop_reap_ex(self, trylock, unlock, cookie), 0))
#define oblockop_reap_ex(self, trylock, unlock, cookie, obj) \
	(void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_ex(self, trylock, unlock, cookie, obj), 0))
#endif /* !__OPTIMIZE_SIZE__ */

#ifdef __CRT_HAVE_lockop_reap_ex
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_NONNULL((2, 3)),__NOTHROW,__LOCKOP_CC,_lockop_reap_ex,(struct lockop_slist *__restrict __self, __BOOL (__LOCKOP_CC *__trylock)(void *__cookie), void (__LOCKOP_CC *__unlock)(void *__cookie), void *__cookie),lockop_reap_ex,(__self,__trylock,__unlock,__cookie))
#else /* __CRT_HAVE_lockop_reap_ex */
#include <libc/local/kos.lockop/_lockop_reap_ex.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lockop_reap_ex, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_NONNULL((2, 3)) void __NOTHROW(__LOCKOP_CC _lockop_reap_ex)(struct lockop_slist *__restrict __self, __BOOL (__LOCKOP_CC *__trylock)(void *__cookie), void (__LOCKOP_CC *__unlock)(void *__cookie), void *__cookie) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_ex))(__self, __trylock, __unlock, __cookie); })
#endif /* !__CRT_HAVE_lockop_reap_ex */
#ifdef __CRT_HAVE_oblockop_reap_ex
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_NONNULL((2, 3, 5)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_ex,(struct oblockop_slist *__restrict __self, __BOOL (__LOCKOP_CC *__trylock)(void *__cookie), void (__LOCKOP_CC *__unlock)(void *__cookie), void *__cookie, void *__restrict __obj),oblockop_reap_ex,(__self,__trylock,__unlock,__cookie,__obj))
#else /* __CRT_HAVE_oblockop_reap_ex */
#include <libc/local/kos.lockop/_oblockop_reap_ex.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_ex, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_NONNULL((2, 3, 5)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_ex)(struct oblockop_slist *__restrict __self, __BOOL (__LOCKOP_CC *__trylock)(void *__cookie), void (__LOCKOP_CC *__unlock)(void *__cookie), void *__cookie, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_ex))(__self, __trylock, __unlock, __cookie, __obj); })
#endif /* !__CRT_HAVE_oblockop_reap_ex */

/* >> void lockop_reap_atomic_lock(struct lockop_slist *__restrict self, struct atomic_lock *__restrict lock);
 * >> void lockop_reap_shared_lock(struct lockop_slist *__restrict self, struct shared_lock *__restrict lock);
 * >> void lockop_reap_atomic_rwlock(struct lockop_slist *__restrict self, struct atomic_rwlock *__restrict lock);
 * >> void lockop_reap_shared_rwlock(struct lockop_slist *__restrict self, struct shared_rwlock *__restrict lock);
 * >> void oblockop_reap_atomic_lock(struct oblockop_slist *__restrict self, struct atomic_lock *__restrict lock, void *obj);
 * >> void oblockop_reap_shared_lock(struct oblockop_slist *__restrict self, struct shared_lock *__restrict lock, void *obj);
 * >> void oblockop_reap_atomic_rwlock(struct oblockop_slist *__restrict self, struct atomic_rwlock *__restrict lock, void *obj);
 * >> void oblockop_reap_shared_rwlock(struct oblockop_slist *__restrict self, struct shared_rwlock *__restrict lock, void *obj);
 * Functions to reap pending lock operations. */
#ifdef __OPTIMIZE_SIZE__
#define lockop_reap_atomic_lock(self, lock)          _lockop_reap_atomic_lock(self, lock)
#define lockop_reap_atomic_rwlock(self, lock)        _lockop_reap_atomic_rwlock(self, lock)
#define oblockop_reap_atomic_lock(self, lock, obj)   _oblockop_reap_atomic_lock(self, lock, obj)
#define oblockop_reap_atomic_rwlock(self, lock, obj) _oblockop_reap_atomic_rwlock(self, lock, obj)
#define lockop_reap_shared_lock(self, lock)          _lockop_reap_shared_lock(self, lock)
#define lockop_reap_shared_rwlock(self, lock)        _lockop_reap_shared_rwlock(self, lock)
#define oblockop_reap_shared_lock(self, lock, obj)   _oblockop_reap_shared_lock(self, lock, obj)
#define oblockop_reap_shared_rwlock(self, lock, obj) _oblockop_reap_shared_rwlock(self, lock, obj)
#else /* __OPTIMIZE_SIZE__ */
#define lockop_reap_atomic_lock(self, lock)          (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_lockop_reap_atomic_lock(self, lock), 0))
#define lockop_reap_atomic_rwlock(self, lock)        (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_lockop_reap_atomic_rwlock(self, lock), 0))
#define oblockop_reap_atomic_lock(self, lock, obj)   (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_atomic_lock(self, lock, obj), 0))
#define oblockop_reap_atomic_rwlock(self, lock, obj) (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_atomic_rwlock(self, lock, obj), 0))
#define lockop_reap_shared_lock(self, lock)          (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_lockop_reap_shared_lock(self, lock), 0))
#define lockop_reap_shared_rwlock(self, lock)        (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_lockop_reap_shared_rwlock(self, lock), 0))
#define oblockop_reap_shared_lock(self, lock, obj)   (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_shared_lock(self, lock, obj), 0))
#define oblockop_reap_shared_rwlock(self, lock, obj) (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_shared_rwlock(self, lock, obj), 0))
#endif /* !__OPTIMIZE_SIZE__ */

#ifdef __CRT_HAVE_lockop_reap_atomic_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap_atomic_lock,(struct lockop_slist *__restrict __self, struct atomic_lock *__restrict __lock),lockop_reap_atomic_lock,(__self,__lock))
#else /* __CRT_HAVE_lockop_reap_atomic_lock */
#include <libc/local/kos.lockop/_lockop_reap_atomic_lock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lockop_reap_atomic_lock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap_atomic_lock)(struct lockop_slist *__restrict __self, struct atomic_lock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_atomic_lock))(__self, __lock); })
#endif /* !__CRT_HAVE_lockop_reap_atomic_lock */
#ifdef __CRT_HAVE_oblockop_reap_atomic_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_atomic_lock,(struct oblockop_slist *__restrict __self, struct atomic_lock *__restrict __lock, void *__restrict __obj),oblockop_reap_atomic_lock,(__self,__lock,__obj))
#else /* __CRT_HAVE_oblockop_reap_atomic_lock */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_lock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_atomic_lock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_lock)(struct oblockop_slist *__restrict __self, struct atomic_lock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_lock))(__self, __lock, __obj); })
#endif /* !__CRT_HAVE_oblockop_reap_atomic_lock */
#ifdef __CRT_HAVE_lockop_reap_atomic_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap_atomic_rwlock,(struct lockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock),lockop_reap_atomic_rwlock,(__self,__lock))
#else /* __CRT_HAVE_lockop_reap_atomic_rwlock */
#include <libc/local/kos.lockop/_lockop_reap_atomic_rwlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lockop_reap_atomic_rwlock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap_atomic_rwlock)(struct lockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_atomic_rwlock))(__self, __lock); })
#endif /* !__CRT_HAVE_lockop_reap_atomic_rwlock */
#ifdef __CRT_HAVE_oblockop_reap_atomic_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_atomic_rwlock,(struct oblockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock, void *__restrict __obj),oblockop_reap_atomic_rwlock,(__self,__lock,__obj))
#else /* __CRT_HAVE_oblockop_reap_atomic_rwlock */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_rwlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_atomic_rwlock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_rwlock)(struct oblockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_rwlock))(__self, __lock, __obj); })
#endif /* !__CRT_HAVE_oblockop_reap_atomic_rwlock */
#ifdef __CRT_HAVE_lockop_reap_shared_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap_shared_lock,(struct lockop_slist *__restrict __self, struct shared_lock *__restrict __lock),lockop_reap_shared_lock,(__self,__lock))
#elif __CRT_HAVE_XSC(lfutex)
#include <libc/local/kos.lockop/_lockop_reap_shared_lock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lockop_reap_shared_lock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap_shared_lock)(struct lockop_slist *__restrict __self, struct shared_lock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_shared_lock))(__self, __lock); })
#endif /* ... */
#ifdef __CRT_HAVE_oblockop_reap_shared_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_shared_lock,(struct oblockop_slist *__restrict __self, struct shared_lock *__restrict __lock, void *__restrict __obj),oblockop_reap_shared_lock,(__self,__lock,__obj))
#elif __CRT_HAVE_XSC(lfutex)
#include <libc/local/kos.lockop/_oblockop_reap_shared_lock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_shared_lock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_shared_lock)(struct oblockop_slist *__restrict __self, struct shared_lock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_shared_lock))(__self, __lock, __obj); })
#endif /* ... */
#ifdef __CRT_HAVE_lockop_reap_shared_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap_shared_rwlock,(struct lockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock),lockop_reap_shared_rwlock,(__self,__lock))
#elif defined(__CRT_HAVE_shared_rwlock_endwrite) || defined(__shared_rwlock_wrwait_send)
#include <libc/local/kos.lockop/_lockop_reap_shared_rwlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_lockop_reap_shared_rwlock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap_shared_rwlock)(struct lockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_shared_rwlock))(__self, __lock); })
#endif /* ... */
#ifdef __CRT_HAVE_oblockop_reap_shared_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_shared_rwlock,(struct oblockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock, void *__restrict __obj),oblockop_reap_shared_rwlock,(__self,__lock,__obj))
#elif defined(__CRT_HAVE_shared_rwlock_endwrite) || defined(__shared_rwlock_wrwait_send)
#include <libc/local/kos.lockop/_oblockop_reap_shared_rwlock.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_shared_rwlock, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_shared_rwlock)(struct oblockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_shared_rwlock))(__self, __lock, __obj); })
#endif /* ... */

#ifdef __cplusplus

/* >> void lockop_reap(struct lockop_slist *__restrict self, struct atomic_lock *__restrict lock);
 * >> void lockop_reap(struct lockop_slist *__restrict self, struct shared_lock *__restrict lock);
 * >> void lockop_reap(struct lockop_slist *__restrict self, struct atomic_rwlock *__restrict lock);
 * >> void lockop_reap(struct lockop_slist *__restrict self, struct shared_rwlock *__restrict lock);
 * >> void oblockop_reap(struct oblockop_slist *__restrict self, struct atomic_lock *__restrict lock, void *obj);
 * >> void oblockop_reap(struct oblockop_slist *__restrict self, struct shared_lock *__restrict lock, void *obj);
 * >> void oblockop_reap(struct oblockop_slist *__restrict self, struct atomic_rwlock *__restrict lock, void *obj);
 * >> void oblockop_reap(struct oblockop_slist *__restrict self, struct shared_rwlock *__restrict lock, void *obj);
 * Functions to reap pending lock operations. */
#ifdef __OPTIMIZE_SIZE__
#define lockop_reap(self, lock)        _lockop_reap(self, lock)
#define oblockop_reap(self, lock, obj) _oblockop_reap(self, lock, obj)
#else /* __OPTIMIZE_SIZE__ */
#define lockop_reap(self, lock)        (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_lockop_reap(self, lock), 0))
#define oblockop_reap(self, lock, obj) (void)(__likely(__hybrid_atomic_load(&(self)->slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap(self, lock, obj), 0))
#endif /* !__OPTIMIZE_SIZE__ */

extern "C++" {
#ifdef __CRT_HAVE_lockop_reap_atomic_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap,(struct lockop_slist *__restrict __self, struct atomic_lock *__restrict __lock),lockop_reap_atomic_lock,(__self,__lock))
#else /* __CRT_HAVE_lockop_reap_atomic_lock */
} /* extern "C++" */
#include <libc/local/kos.lockop/_lockop_reap_atomic_lock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap)(struct lockop_slist *__restrict __self, struct atomic_lock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_atomic_lock))(__self, __lock); }
#endif /* !__CRT_HAVE_lockop_reap_atomic_lock */
#ifdef __CRT_HAVE_lockop_reap_atomic_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap,(struct lockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock),lockop_reap_atomic_rwlock,(__self,__lock))
#else /* __CRT_HAVE_lockop_reap_atomic_rwlock */
} /* extern "C++" */
#include <libc/local/kos.lockop/_lockop_reap_atomic_rwlock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap)(struct lockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_atomic_rwlock))(__self, __lock); }
#endif /* !__CRT_HAVE_lockop_reap_atomic_rwlock */
#ifdef __CRT_HAVE_oblockop_reap_atomic_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap,(struct oblockop_slist *__restrict __self, struct atomic_lock *__restrict __lock, void *__restrict __obj),oblockop_reap_atomic_lock,(__self,__lock,__obj))
#else /* __CRT_HAVE_oblockop_reap_atomic_lock */
} /* extern "C++" */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_lock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap)(struct oblockop_slist *__restrict __self, struct atomic_lock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_lock))(__self, __lock, __obj); }
#endif /* !__CRT_HAVE_oblockop_reap_atomic_lock */
#ifdef __CRT_HAVE_oblockop_reap_atomic_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap,(struct oblockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock, void *__restrict __obj),oblockop_reap_atomic_rwlock,(__self,__lock,__obj))
#else /* __CRT_HAVE_oblockop_reap_atomic_rwlock */
} /* extern "C++" */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_rwlock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap)(struct oblockop_slist *__restrict __self, struct atomic_rwlock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_rwlock))(__self, __lock, __obj); }
#endif /* !__CRT_HAVE_oblockop_reap_atomic_rwlock */
#ifdef __CRT_HAVE_lockop_reap_shared_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap,(struct lockop_slist *__restrict __self, struct shared_lock *__restrict __lock),lockop_reap_shared_lock,(__self,__lock))
#elif __CRT_HAVE_XSC(lfutex)
} /* extern "C++" */
#include <libc/local/kos.lockop/_lockop_reap_shared_lock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap)(struct lockop_slist *__restrict __self, struct shared_lock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_shared_lock))(__self, __lock); }
#endif /* ... */
#ifdef __CRT_HAVE_lockop_reap_shared_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2),__NOTHROW,__LOCKOP_CC,_lockop_reap,(struct lockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock),lockop_reap_shared_rwlock,(__self,__lock))
#elif defined(__CRT_HAVE_shared_rwlock_endwrite) || defined(__shared_rwlock_wrwait_send)
} /* extern "C++" */
#include <libc/local/kos.lockop/_lockop_reap_shared_rwlock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) void __NOTHROW(__LOCKOP_CC _lockop_reap)(struct lockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_lockop_reap_shared_rwlock))(__self, __lock); }
#endif /* ... */
#ifdef __CRT_HAVE_oblockop_reap_shared_lock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap,(struct oblockop_slist *__restrict __self, struct shared_lock *__restrict __lock, void *__restrict __obj),oblockop_reap_shared_lock,(__self,__lock,__obj))
#elif __CRT_HAVE_XSC(lfutex)
} /* extern "C++" */
#include <libc/local/kos.lockop/_oblockop_reap_shared_lock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap)(struct oblockop_slist *__restrict __self, struct shared_lock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_shared_lock))(__self, __lock, __obj); }
#endif /* ... */
#ifdef __CRT_HAVE_oblockop_reap_shared_rwlock
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)),__NOTHROW,__LOCKOP_CC,_oblockop_reap,(struct oblockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock, void *__restrict __obj),oblockop_reap_shared_rwlock,(__self,__lock,__obj))
#elif defined(__CRT_HAVE_shared_rwlock_endwrite) || defined(__shared_rwlock_wrwait_send)
} /* extern "C++" */
#include <libc/local/kos.lockop/_oblockop_reap_shared_rwlock.h>
extern "C++" {
__FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void __NOTHROW(__LOCKOP_CC _oblockop_reap)(struct oblockop_slist *__restrict __self, struct shared_rwlock *__restrict __lock, void *__restrict __obj) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_shared_rwlock))(__self, __lock, __obj); }
#endif /* ... */
} /* extern "C++" */

extern "C++" {

template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_lock)(_Toblockop_slist<__T> *__restrict __self,
                                                  struct atomic_lock *__restrict __lock,
                                                  __T *__restrict __obj) {
	(_oblockop_reap_atomic_lock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}
template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_rwlock)(_Toblockop_slist<__T> *__restrict __self,
                                                    struct atomic_rwlock *__restrict __lock,
                                                    __T *__restrict __obj) {
	(_oblockop_reap_atomic_rwlock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}
template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap)(_Toblockop_slist<__T> *__restrict __self,
                                      struct atomic_lock *__restrict __lock,
                                      __T *__restrict __obj) {
	(_oblockop_reap_atomic_lock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}
template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap)(_Toblockop_slist<__T> *__restrict __self,
                                      struct atomic_rwlock *__restrict __lock,
                                      __T *__restrict __obj) {
	(_oblockop_reap_atomic_rwlock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}

#if defined(__CRT_HAVE_oblockop_reap_shared_lock) || __CRT_HAVE_XSC(lfutex)
template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap_shared_lock)(_Toblockop_slist<__T> *__restrict __self,
                                                  struct shared_lock *__restrict __lock,
                                                  __T *__restrict __obj) {
	(_oblockop_reap_shared_lock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}
template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap)(_Toblockop_slist<__T> *__restrict __self,
                                      struct shared_lock *__restrict __lock,
                                      __T *__restrict __obj) {
	(_oblockop_reap_shared_lock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}
#endif /* __CRT_HAVE_oblockop_reap_shared_lock || __CRT_HAVE_XSC(lfutex) */
#if defined(__CRT_HAVE_oblockop_reap_shared_rwlock) || defined(__CRT_HAVE_shared_rwlock_endwrite) || defined(__shared_rwlock_wrwait_send)
template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap_shared_rwlock)(_Toblockop_slist<__T> *__restrict __self,
                                                    struct shared_rwlock *__restrict __lock,
                                                    __T *__restrict __obj) {
	(_oblockop_reap_shared_rwlock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}
template<class __T> __FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_NONNULL((3)) void
__NOTHROW(__LOCKOP_CC _oblockop_reap)(_Toblockop_slist<__T> *__restrict __self,
                                      struct shared_rwlock *__restrict __lock,
                                      __T *__restrict __obj) {
	(_oblockop_reap_shared_rwlock)((struct oblockop_slist *)__self, __lock, (void *)__obj);
}
#endif /* __CRT_HAVE_oblockop_reap_shared_rwlock || __CRT_HAVE_shared_rwlock_endwrite || __shared_rwlock_wrwait_send */
} /* extern "C++" */
#endif /* __cplusplus */


/* Reap helpers that are optimized  for- and operate under the  assumption
 * of specific memory layouts. You shouldn't use these functions directly.
 *
 * Instead, you should use:
 * >> struct my_struct {
 * >>     struct atomic_lock         ms_lock;
 * >>     Toblockop_slist(my_struct) ms_lops;
 * >> };
 * >> #define my_struct_reap(self)  oblockop_reap_atomic_lockT2(self, struct my_struct, ms_lops, ms_lock)
 * >> #define _my_struct_reap(self) _oblockop_reap_atomic_lockT2(self, struct my_struct, ms_lops, ms_lock)
 *
 * Or if you know that all compilers you intend to target support `typeof()', you can also use:
 * >> #define my_struct_reap(self)  oblockop_reap_atomic_lockT(self, ms_lops, ms_lock)
 * >> #define _my_struct_reap(self) _oblockop_reap_atomic_lockT(self, ms_lops, ms_lock)
 *
 * The relevant macros will then take a look at the offsets of  `ms_lock'
 * and `ms_lops' in relation to each other, and if it is found that there
 * exists a dedicated optimization for  their relation, then that is  the
 * call  that will be used (thus reducing the size of the call that needs
 * to be made in order to perform the reap operation).
 */

#ifdef __CRT_HAVE_oblockop_reap_atomic_lock_OL
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_atomic_lock_OL,(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_lockop_slist),oblockop_reap_atomic_lock_OL,(__obj,__offsetof_lockop_slist))
#else /* __CRT_HAVE_oblockop_reap_atomic_lock_OL */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_lock_OL.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_atomic_lock_OL, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_lock_OL)(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_lockop_slist) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_lock_OL))(__obj, __offsetof_lockop_slist); })
#endif /* !__CRT_HAVE_oblockop_reap_atomic_lock_OL */
#ifdef __CRT_HAVE_oblockop_reap_atomic_lock_LO
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_atomic_lock_LO,(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_atomic_lock),oblockop_reap_atomic_lock_LO,(__obj,__offsetof_atomic_lock))
#else /* __CRT_HAVE_oblockop_reap_atomic_lock_LO */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_lock_LO.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_atomic_lock_LO, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_lock_LO)(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_atomic_lock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_lock_LO))(__obj, __offsetof_atomic_lock); })
#endif /* !__CRT_HAVE_oblockop_reap_atomic_lock_LO */
#ifdef __CRT_HAVE_oblockop_reap_atomic_rwlock_OL
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_atomic_rwlock_OL,(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_lockop_slist),oblockop_reap_atomic_rwlock_OL,(__obj,__offsetof_lockop_slist))
#else /* __CRT_HAVE_oblockop_reap_atomic_rwlock_OL */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_rwlock_OL.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_atomic_rwlock_OL, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_rwlock_OL)(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_lockop_slist) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_rwlock_OL))(__obj, __offsetof_lockop_slist); })
#endif /* !__CRT_HAVE_oblockop_reap_atomic_rwlock_OL */
#ifdef __CRT_HAVE_oblockop_reap_atomic_rwlock_LO
__COMPILER_CREDIRECT_VOID(__LIBC,__NOBLOCK __ATTR_NONNULL((1)),__NOTHROW,__LOCKOP_CC,_oblockop_reap_atomic_rwlock_LO,(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_atomic_rwlock),oblockop_reap_atomic_rwlock_LO,(__obj,__offsetof_atomic_rwlock))
#else /* __CRT_HAVE_oblockop_reap_atomic_rwlock_LO */
#include <libc/local/kos.lockop/_oblockop_reap_atomic_rwlock_LO.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(_oblockop_reap_atomic_rwlock_LO, __FORCELOCAL __ATTR_ARTIFICIAL __NOBLOCK __ATTR_NONNULL((1)) void __NOTHROW(__LOCKOP_CC _oblockop_reap_atomic_rwlock_LO)(void *__restrict __obj, __PTRDIFF_TYPE__ __offsetof_atomic_rwlock) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(_oblockop_reap_atomic_rwlock_LO))(__obj, __offsetof_atomic_rwlock); })
#endif /* !__CRT_HAVE_oblockop_reap_atomic_rwlock_LO */

#ifdef __INTELLISENSE__ /* To improve syntax highlighting */
#define _oblockop_reapT2(obj, Tobj, lockops_field, lock_field)               _oblockop_reap(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_atomic_lockT2(obj, Tobj, lockops_field, lock_field)   _oblockop_reap_atomic_lock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_atomic_rwlockT2(obj, Tobj, lockops_field, lock_field) _oblockop_reap_atomic_rwlock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_shared_lockT2(obj, Tobj, lockops_field, lock_field)   _oblockop_reap_shared_lock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_shared_rwlockT2(obj, Tobj, lockops_field, lock_field) _oblockop_reap_shared_rwlock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#else /* __INTELLISENSE__ */
#if defined(__COMPILER_HAVE_TYPEOF) && defined(__NO_builtin_types_compatible_p)
#define _oblockop_reapT2(obj, Tobj, lockops_field, lock_field)                                               \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((obj)->lock_field), struct atomic_lock),   \
	                      _oblockop_reap_atomic_lockT2(obj, Tobj, lockops_field, lock_field),                \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((obj)->lock_field), struct atomic_rwlock), \
	                      _oblockop_reap_atomic_rwlockT2(obj, Tobj, lockops_field, lock_field),              \
	                      _oblockop_reap(&(obj)->lockops_field, &(obj)->lock_field, obj)))
#else /* __COMPILER_HAVE_TYPEOF && !__NO_builtin_types_compatible_p */
#define _oblockop_reapT2(obj, Tobj, lockops_field, lock_field) \
	_oblockop_reap(&(obj)->lockops_field, &(obj)->lock_field, obj)
#endif /* !__COMPILER_HAVE_TYPEOF || __NO_builtin_types_compatible_p */
#define __oblockop_reapT2_select(_oblockop_reap, obj, Tobj, lockops_field, lock_field)                                           \
	__builtin_choose_expr(__builtin_offsetof(Tobj, lockops_field) + __SIZEOF_POINTER__ == __builtin_offsetof(Tobj, lock_field), \
	                      _oblockop_reap##_OL(obj, __builtin_offsetof(Tobj, lockops_field)),                                    \
	__builtin_choose_expr(__builtin_offsetof(Tobj, lock_field) + __SIZEOF_POINTER__ == __builtin_offsetof(Tobj, lockops_field), \
	                      _oblockop_reap##_LO(obj, __builtin_offsetof(Tobj, lock_field)),                                       \
	                      _oblockop_reap(&(obj)->lockops_field, &(obj)->lock_field, obj)))
#define __oblockop_reapT2_select_unsup(_oblockop_reap, obj, Tobj, lockops_field, lock_field) \
	_oblockop_reap(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_atomic_lockT2(obj, Tobj, lockops_field, lock_field)   __oblockop_reapT2_select(_oblockop_reap_atomic_lock, obj, Tobj, lockops_field, lock_field)
#define _oblockop_reap_atomic_rwlockT2(obj, Tobj, lockops_field, lock_field) __oblockop_reapT2_select(_oblockop_reap_atomic_rwlock, obj, Tobj, lockops_field, lock_field)
#define _oblockop_reap_shared_lockT2(obj, Tobj, lockops_field, lock_field)   __oblockop_reapT2_select_unsup(_oblockop_reap_shared_lock, obj, Tobj, lockops_field, lock_field)
#define _oblockop_reap_shared_rwlockT2(obj, Tobj, lockops_field, lock_field) __oblockop_reapT2_select_unsup(_oblockop_reap_shared_rwlock, obj, Tobj, lockops_field, lock_field)
#endif /* !__INTELLISENSE__ */


#ifdef __COMPILER_HAVE_TYPEOF
#define _oblockop_reapT(obj, lockops_field, lock_field)               _oblockop_reapT2(obj, __typeof__(*(obj)), lockops_field, lock_field)
#define _oblockop_reap_atomic_lockT(obj, lockops_field, lock_field)   _oblockop_reap_atomic_lockT2(obj, __typeof__(*(obj)), lockops_field, lock_field)
#define _oblockop_reap_atomic_rwlockT(obj, lockops_field, lock_field) _oblockop_reap_atomic_rwlockT2(obj, __typeof__(*(obj)), lockops_field, lock_field)
#define _oblockop_reap_shared_lockT(obj, lockops_field, lock_field)   _oblockop_reap_shared_lockT2(obj, __typeof__(*(obj)), lockops_field, lock_field)
#define _oblockop_reap_shared_rwlockT(obj, lockops_field, lock_field) _oblockop_reap_shared_rwlockT2(obj, __typeof__(*(obj)), lockops_field, lock_field)
#else /* __COMPILER_HAVE_TYPEOF */
#define _oblockop_reapT(obj, lockops_field, lock_field)               _oblockop_reap(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_atomic_lockT(obj, lockops_field, lock_field)   _oblockop_reap_atomic_lock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_atomic_rwlockT(obj, lockops_field, lock_field) _oblockop_reap_atomic_rwlock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_shared_lockT(obj, lockops_field, lock_field)   _oblockop_reap_shared_lock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#define _oblockop_reap_shared_rwlockT(obj, lockops_field, lock_field) _oblockop_reap_shared_rwlock(&(obj)->lockops_field, &(obj)->lock_field, obj)
#endif /* !__COMPILER_HAVE_TYPEOF */

#ifdef __OPTIMIZE_SIZE__
#define oblockop_reapT2(obj, Tobj, lockops_field, lock_field)               _oblockop_reapT2(obj, Tobj, lockops_field, lock_field)
#define oblockop_reap_atomic_lockT2(obj, Tobj, lockops_field, lock_field)   _oblockop_reap_atomic_lockT2(obj, Tobj, lockops_field, lock_field)
#define oblockop_reap_atomic_rwlockT2(obj, Tobj, lockops_field, lock_field) _oblockop_reap_atomic_rwlockT2(obj, Tobj, lockops_field, lock_field)
#define oblockop_reap_shared_lockT2(obj, Tobj, lockops_field, lock_field)   _oblockop_reap_shared_lockT2(obj, Tobj, lockops_field, lock_field)
#define oblockop_reap_shared_rwlockT2(obj, Tobj, lockops_field, lock_field) _oblockop_reap_shared_rwlockT2(obj, Tobj, lockops_field, lock_field)
#define oblockop_reapT(obj, lockops_field, lock_field)                      _oblockop_reapT(obj, lockops_field, lock_field)
#define oblockop_reap_atomic_lockT(obj, lockops_field, lock_field)          _oblockop_reap_atomic_lockT(obj, lockops_field, lock_field)
#define oblockop_reap_atomic_rwlockT(obj, lockops_field, lock_field)        _oblockop_reap_atomic_rwlockT(obj, lockops_field, lock_field)
#define oblockop_reap_shared_lockT(obj, lockops_field, lock_field)          _oblockop_reap_shared_lockT(obj, lockops_field, lock_field)
#define oblockop_reap_shared_rwlockT(obj, lockops_field, lock_field)        _oblockop_reap_shared_rwlockT(obj, lockops_field, lock_field)
#else /* __OPTIMIZE_SIZE__ */
#define oblockop_reapT2(obj, Tobj, lockops_field, lock_field)               (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reapT2(obj, Tobj, lockops_field, lock_field), 0))
#define oblockop_reap_atomic_lockT2(obj, Tobj, lockops_field, lock_field)   (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_atomic_lockT2(obj, Tobj, lockops_field, lock_field), 0))
#define oblockop_reap_atomic_rwlockT2(obj, Tobj, lockops_field, lock_field) (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_atomic_rwlockT2(obj, Tobj, lockops_field, lock_field), 0))
#define oblockop_reap_shared_lockT2(obj, Tobj, lockops_field, lock_field)   (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_shared_lockT2(obj, Tobj, lockops_field, lock_field), 0))
#define oblockop_reap_shared_rwlockT2(obj, Tobj, lockops_field, lock_field) (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_shared_rwlockT2(obj, Tobj, lockops_field, lock_field), 0))
#define oblockop_reapT(obj, lockops_field, lock_field)                      (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reapT(obj, lockops_field, lock_field), 0))
#define oblockop_reap_atomic_lockT(obj, lockops_field, lock_field)          (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_atomic_lockT(obj, lockops_field, lock_field), 0))
#define oblockop_reap_atomic_rwlockT(obj, lockops_field, lock_field)        (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_atomic_rwlockT(obj, lockops_field, lock_field), 0))
#define oblockop_reap_shared_lockT(obj, lockops_field, lock_field)          (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_shared_lockT(obj, lockops_field, lock_field), 0))
#define oblockop_reap_shared_rwlockT(obj, lockops_field, lock_field)        (void)(__likely(__hybrid_atomic_load(&(obj)->lockops_field.slh_first, __ATOMIC_ACQUIRE) == __NULLPTR) || (_oblockop_reap_shared_rwlockT(obj, lockops_field, lock_field), 0))
#endif /* !__OPTIMIZE_SIZE__ */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_LOCKOP_H */
