/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_LOCKOP_H
#define GUARD_KERNEL_INCLUDE_SCHED_LOCKOP_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/sequence/list.h>

/* Helper  structures to implement  general-purpose lock operation handling.
 * The basic idea here is to make it possible to enqueue a set of operations
 * that will be performed asynchronously once some kind of lock becomes
 * available:
 *
 * >> void _service(void);
 * >> #define must_service() ...
 * >> #define service() (void)(!must_service() || (_service(), 0))
 * >> #define acquire() acquire_lock(&lock)
 * >> #define release() (release_lock(&lock), service())
 * >>
 * >> ...
 * >>
 * >> void _service(void) {
 * >>     do {
 * >>         if (!try_acquire())
 * >>             break;
 * >>         SERVICE_LOCK_OPS();
 * >>         release_lock(&lock);
 * >>         SERVICE_POST_LOCK_OPS();
 * >>     } while (must_service());
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
 * operations in  the context  of contain  locks being  held, making  them
 * perfect for augmenting and facilitating the non-blocking-ness of object
 * finalizers that need to acquire locks to other data structures, such as
 * lists,  in order  to remove (part  of) the object  being destroyed, and
 * making  this possible by trying to acquire  such a lock, and making use
 * of lock operations  if the  lock cannot be  acquired without  blocking.
 * This then allows for the part  of the object's finalization that  needs
 * a certain lock to be held, to be performed as an asynchronous operation
 * executed once said lock becomes available.
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
 * >> static struct myobj_list   list    = LIST_HEAD_INITIALIZER(list);
 * >> static struct atomic_lock  lock    = ATOMIC_LOCK_INIT;
 * >> static struct lockop_slist lockops = SLIST_HEAD_INITIALIZER(lockops);
 * >> #define _service()   _lockop_reap(&lockops, &lock)
 * >> #define service()    lockop_reap(&lockops, &lock)
 * >> #define tryacquire() atomic_lock_tryacquire(&lock)
 * >> #define acquire()    atomic_lock_acquire(&lock)
 * >> #define _release()   atomic_lock_release(&lock)
 * >> #define release()    (_release(), service())
 * >>
 * >> static NOBLOCK NONNULL((1)) void
 * >> NOTHROW(FCALL myobj_destroy_postlop)(struct postlockop *__restrict self) {
 * >>     struct myobj *me = container_of(self, struct myobj, postlop);
 * >>     kfree(me);
 * >> }
 * >> static NOBLOCK NONNULL((1)) struct postlockop *
 * >> NOTHROW(FCALL myobj_destroy_lop)(struct lockop *__restrict self) {
 * >>     struct myobj *me = container_of(self, struct myobj, lop);
 * >>     LIST_REMOVE(me, ent);
 * >>     // kfree() the object _after_ releasing the lock so the lock
 * >>     // itself can be released sonner than it could otherwise be.
 * >>     me->postlop.plo_func = &myobj_destroy_postlop;
 * >>     return &me->postlop;
 * >> }
 * >>
 * >> // Non-blocking async-remove-object-from-locked-list-and-kfree-object function.
 * >> static NOBLOCK NONNULL((1)) void
 * >> NOTHROW(KCALL myobj_destroy)(struct myobj *self) {
 * >>     if (tryacquire()) {
 * >>         LIST_REMOVE(self, ent);
 * >>         _release();
 * >>         kfree(self);
 * >>         service();
 * >>     } else {
 * >>         self->lop.lo_func = &myobj_destroy_lop;
 * >>         SLIST_ATOMIC_INSERT(&lockops, &self->lop, lo_link);
 * >>         _service();
 * >>     }
 * >> }
 */

#ifdef __CC__
DECL_BEGIN

/* TODO: Go  through all  of the  different uses  of lockop mechanics
 *       and change APIs to make use of the general-purpose interface
 *       exposed by this header! */

struct postlockop;
struct lockop;
struct obpostlockop;
struct oblockop;

/* Callback prototype for an operation to-be performed once locks have been released. */
typedef NOBLOCK NONNULL((1)) void
/*NOTHROW*/ (FCALL *postlockop_callback_t)(struct postlockop *__restrict self);
typedef NOBLOCK NONNULL((1, 2)) void
/*NOTHROW*/ (FCALL *obpostlockop_callback_t)(struct obpostlockop *__restrict self, void *__restrict obj);

/* Callback prototype for pending locked operations.
 * @return: NULL: Completed.
 * @return: * :   A descriptor for an operation to perform after the lock has been released. */
typedef NOBLOCK NONNULL((1)) struct postlockop *
/*NOTHROW*/ (FCALL *lockop_callback_t)(struct lockop *__restrict self);
typedef NOBLOCK NONNULL((1, 2)) struct obpostlockop *
/*NOTHROW*/ (FCALL *oblockop_callback_t)(struct oblockop *__restrict self, void *__restrict obj);

struct postlockop {
	SLIST_ENTRY(postlockop) plo_link; /* [0..1] Next post-lock operation. */
	postlockop_callback_t   plo_func; /* [1..1][const] Callback to invoke. */
};
struct obpostlockop {
	SLIST_ENTRY(obpostlockop) oplo_link; /* [0..1] Next post-lock operation. */
	obpostlockop_callback_t   oplo_func; /* [1..1][const] Callback to invoke. */
};

struct lockop {
	SLIST_ENTRY(lockop) lo_link; /* [0..1] Next lock operation. */
	lockop_callback_t   lo_func; /* [1..1][const] Operation to perform. */
};
struct oblockop {
	SLIST_ENTRY(oblockop) olo_link; /* [0..1] Next lock operation. */
	oblockop_callback_t   olo_func; /* [1..1][const] Operation to perform. */
};


/* NOTE: To add lock ops to a pending list, use `SLIST_ATOMIC_INSERT()'! */

#ifndef __lockop_slist_defined
#define __lockop_slist_defined 1
SLIST_HEAD(lockop_slist, lockop);
#endif /* !__lockop_slist_defined */

#ifndef __postlockop_slist_defined
#define __postlockop_slist_defined 1
SLIST_HEAD(postlockop_slist, postlockop);
#endif /* !__postlockop_slist_defined */

#ifndef __oblockop_slist_defined
#define __oblockop_slist_defined 1
SLIST_HEAD(oblockop_slist, oblockop);
#endif /* !__oblockop_slist_defined */

#ifndef __obpostlockop_slist_defined
#define __obpostlockop_slist_defined 1
SLIST_HEAD(obpostlockop_slist, obpostlockop);
#endif /* !__obpostlockop_slist_defined */

#ifdef __cplusplus
extern "C++" {
#define Tobpostlockop(T)            _Tobpostlockop<T>
#define Toblockop(T)                _Toblockop<T>
#define Toblockop_slist(T)          _Toblockop_slist<T>
#define Tobpostlockop_slist(T)      _Tobpostlockop_slist<T>
#define Tobpostlockop_callback_t(T) _Tobpostlockop_callback_t<T>
#define Toblockop_callback_t(T)     _Toblockop_callback_t<T>
template<class T> struct _Tobpostlockop;
template<class T> struct _Toblockop;
template<class T> using _Tobpostlockop_callback_t = NOBLOCK NONNULL((1)) void /*NOTHROW*/ (FCALL *)(_Tobpostlockop<T> *__restrict self, T *__restrict obj);
template<class T> using _Toblockop_callback_t     = NOBLOCK NONNULL((1)) _Tobpostlockop<T> * /*NOTHROW*/ (FCALL *)(_Toblockop<T> *__restrict self, T *__restrict obj);
template<class T> struct _Tobpostlockop {
	SLIST_ENTRY(_Tobpostlockop<T>) oplo_link; /* [0..1] Next post-lock operation. */
	_Tobpostlockop_callback_t<T>   oplo_func; /* [1..1][const] Callback to invoke. */
};
template<class T> struct _Toblockop {
	SLIST_ENTRY(_Toblockop<T>) olo_link; /* [0..1] Next lock operation. */
	_Toblockop_callback_t<T>   olo_func; /* [1..1][const] Operation to perform. */
};
template<class T> SLIST_HEAD(_Toblockop_slist, _Toblockop<T>);
template<class T> SLIST_HEAD(_Tobpostlockop_slist, _Tobpostlockop<T>);
} /* extern "C++" */
#else /* __cplusplus */
#define Tobpostlockop(T)            struct obpostlockop
#define Toblockop(T)                struct oblockop
#define Toblockop_slist(T)          struct oblockop_slist
#define Tobpostlockop_slist(T)      struct obpostlockop_slist
#define Tobpostlockop_callback_t(T) obpostlockop_callback_t
#define Toblockop_callback_t(T)     oblockop_callback_t
#endif /* !__cplusplus */


struct atomic_lock;
struct atomic_rwlock;

/* Functions to reap pending lock operations. */

#ifdef __OPTIMIZE_SIZE__
#define lockop_reap_ex(self, trylock, unlock, cookie)        _lockop_reap_ex(self, trylock, unlock, cookie)
#define oblockop_reap_ex(self, trylock, unlock, cookie, obj) _oblockop_reap_ex(self, trylock, unlock, cookie, obj)
#else /* __OPTIMIZE_SIZE__ */
#define lockop_reap_ex(self, trylock, unlock, cookie)        (void)(SLIST_EMPTY(self) || (_lockop_reap_ex(self, trylock, unlock, cookie), 0))
#define oblockop_reap_ex(self, trylock, unlock, cookie, obj) (void)(SLIST_EMPTY(self) || (_oblockop_reap_ex(self, trylock, unlock, cookie, obj), 0))
#endif /* !__OPTIMIZE_SIZE__ */
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _lockop_reap_ex)(struct lockop_slist *__restrict self,
                               __BOOL (FCALL *trylock)(void *cookie),
                               void (FCALL *unlock)(void *cookie),
                               void *cookie)
	ASMNAME("lockop_reap_ex");
FUNDEF NOBLOCK NONNULL((1, 2, 3, 4)) void
NOTHROW(FCALL _oblockop_reap_ex)(struct oblockop_slist *__restrict self,
                                 __BOOL (FCALL *trylock)(void *cookie),
                                 void (FCALL *unlock)(void *cookie),
                                 void *cookie, void *__restrict obj)
	ASMNAME("oblockop_reap_ex");


#ifdef __OPTIMIZE_SIZE__
#define lockop_reap_atomic_lock(self, lock)          _lockop_reap_atomic_lock(self, lock)
#define lockop_reap_atomic_rwlock(self, lock)        _lockop_reap_atomic_rwlock(self, lock)
#define oblockop_reap_atomic_lock(self, lock, obj)   _oblockop_reap_atomic_lock(self, lock, obj)
#define oblockop_reap_atomic_rwlock(self, lock, obj) _oblockop_reap_atomic_rwlock(self, lock, obj)
#else /* __OPTIMIZE_SIZE__ */
#define lockop_reap_atomic_lock(self, lock)          (void)(SLIST_EMPTY(self) || (_lockop_reap_atomic_lock(self, lock), 0))
#define lockop_reap_atomic_rwlock(self, lock)        (void)(SLIST_EMPTY(self) || (_lockop_reap_atomic_rwlock(self, lock), 0))
#define oblockop_reap_atomic_lock(self, lock, obj)   (void)(SLIST_EMPTY(self) || (_oblockop_reap_atomic_lock(self, lock, obj), 0))
#define oblockop_reap_atomic_rwlock(self, lock, obj) (void)(SLIST_EMPTY(self) || (_oblockop_reap_atomic_rwlock(self, lock, obj), 0))
#endif /* !__OPTIMIZE_SIZE__ */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _lockop_reap_atomic_lock)(struct lockop_slist *__restrict self,
                                        struct atomic_lock *__restrict lock)
	ASMNAME("lockop_reap_atomic_lock");
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _lockop_reap_atomic_rwlock)(struct lockop_slist *__restrict self,
                                          struct atomic_rwlock *__restrict lock)
	ASMNAME("lockop_reap_atomic_rwlock");
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap_atomic_lock)(struct oblockop_slist *__restrict self,
                                          struct atomic_lock *__restrict lock, void *__restrict obj)
	ASMNAME("oblockop_reap_atomic_lock");
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap_atomic_rwlock)(struct oblockop_slist *__restrict self,
                                            struct atomic_rwlock *__restrict lock, void *__restrict obj)
	ASMNAME("oblockop_reap_atomic_rwlock");


#ifdef __cplusplus
#ifdef __OPTIMIZE_SIZE__
#define lockop_reap(self, lock)        _lockop_reap(self, lock)
#define oblockop_reap(self, lock, obj) _oblockop_reap(self, lock, obj)
#else /* __OPTIMIZE_SIZE__ */
#define lockop_reap(self, lock)        (void)(SLIST_EMPTY(self) || (_lockop_reap(self, lock), 0))
#define oblockop_reap(self, lock, obj) (void)(SLIST_EMPTY(self) || (_oblockop_reap(self, lock, obj), 0))
#endif /* !__OPTIMIZE_SIZE__ */
extern "C++" {
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _lockop_reap)(struct lockop_slist *__restrict self,
                            struct atomic_lock *__restrict lock)
	ASMNAME("lockop_reap_atomic_lock");
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL _lockop_reap)(struct lockop_slist *__restrict self,
                            struct atomic_rwlock *__restrict lock)
	ASMNAME("lockop_reap_atomic_rwlock");
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap)(struct oblockop_slist *__restrict self,
                              struct atomic_lock *__restrict lock, void *__restrict obj)
	ASMNAME("oblockop_reap_atomic_lock");
FUNDEF NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap)(struct oblockop_slist *__restrict self,
                              struct atomic_rwlock *__restrict lock, void *__restrict obj)
	ASMNAME("oblockop_reap_atomic_rwlock");
template<class T> FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap_atomic_lock)(_Toblockop_slist<T> *__restrict self,
                                          struct atomic_lock *__restrict lock,
                                          T *__restrict obj) {
	_oblockop_reap_atomic_lock((struct oblockop_slist *)self, lock, (void *)obj);
}
template<class T> FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap_atomic_rwlock)(_Toblockop_slist<T> *__restrict self,
                                            struct atomic_rwlock *__restrict lock,
                                            T *__restrict obj) {
	_oblockop_reap_atomic_rwlock((struct oblockop_slist *)self, lock, (void *)obj);
}
template<class T> FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap)(_Toblockop_slist<T> *__restrict self,
                              struct atomic_lock *__restrict lock,
                              T *__restrict obj) {
	_oblockop_reap_atomic_lock((struct oblockop_slist *)self, lock, (void *)obj);
}
template<class T> FORCELOCAL ATTR_ARTIFICIAL NOBLOCK NONNULL((1, 2, 3)) void
NOTHROW(FCALL _oblockop_reap)(_Toblockop_slist<T> *__restrict self,
                              struct atomic_rwlock *__restrict lock,
                              T *__restrict obj) {
	_oblockop_reap_atomic_rwlock((struct oblockop_slist *)self, lock, (void *)obj);
}
} /* extern "C++" */
#endif /* __cplusplus */






DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_LOCKOP_H */
