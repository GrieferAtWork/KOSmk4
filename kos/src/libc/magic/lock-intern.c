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
%(c_prefix){
/* (#) Portability: GNU C Library (/mach/lock-intern.h) */
/* (#) Portability: GNU Hurd      (/usr/include/lock-intern.h) */
}

%[default:section(".text.crt{|.dos}.compat.hurd.futex")]
%[default:nodos]

%(auto_source){
#ifndef __KERNEL__
#include <stdalign.h>
#include <assert.h>
#include <kos/sched/shared-lock.h>
static_assert(sizeof(__spin_lock_t) == sizeof(struct shared_lock));
static_assert(alignof(__spin_lock_t) == alignof(struct shared_lock));
#endif /* !__KERNEL__ */
}

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/bits/shared-lock.h>
)]%[insert:prefix(
#include <kos/sched/shared-lock.h>
)]%[insert:prefix(
#include <hybrid/sched/__yield.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

typedef unsigned int __spin_lock_t;
#define __SPIN_LOCK_INITIALIZER 0

}

%[define_replacement(__spin_lock_t = "unsigned int")]

[[extern_inline]]
[[export_as("__mutex_init")]]
void __spin_lock_init([[out]] __spin_lock_t *lock) {
	*lock = 0;
}

[[export_alias("__spin_lock", "__mutex_lock", "__mutex_lock_solid", "mutex_wait_lock")]]
[[requires_function(shared_lock_acquire)]]
[[impl_include("<kos/bits/shared-lock.h>")]]
void __spin_lock_solid([[inout]] __spin_lock_t *lock) {
	shared_lock_acquire((struct shared_lock *)lock);
}

[[nocrt, alias("__spin_lock", "__spin_lock_solid", "__mutex_lock", "__mutex_lock_solid", "mutex_wait_lock")]]
[[if($has_function(shared_lock_acquire)), bind_local_function(__spin_lock_solid)]]
void __spin_lock([[inout]] __spin_lock_t *lock);

[[export_alias("__mutex_unlock", "mutex_unlock")]]
[[requires_function(shared_lock_release_ex)]]
[[impl_include("<kos/bits/shared-lock.h>")]]
void __spin_unlock([[inout]] __spin_lock_t *lock) {
	shared_lock_release_ex((struct shared_lock *)lock);
}

[[export_alias("__mutex_trylock")]]
[[requires_function(shared_lock_tryacquire)]]
[[impl_include("<kos/bits/shared-lock.h>")]]
int __spin_try_lock([[inout]] __spin_lock_t *lock) {
	return shared_lock_tryacquire((struct shared_lock *)lock);
}

%[define_c_language_keyword(__KOS_FIXED_CONST)]

[[decl_include("<features.h>")]]
[[requires_include("<kos/bits/shared-lock.h>")]]
[[requires(defined(__shared_lock_available))]]
[[impl_include("<kos/bits/shared-lock.h>")]]
int __spin_lock_locked([[in]] __spin_lock_t __KOS_FIXED_CONST *lock) {
	return !__shared_lock_available((struct shared_lock *)lock);
}



%{



/************************************************************************/
/* """Mutex""" API                                                      */
/************************************************************************/

#if 0
/* Hurd defines this struct here, but then it also defines it once  again
 * in `<cthreads.h>', which in turn also includes this header right here.
 *
 * So I have no idea how they're able to get gcc to compile a header that
 * effectively defines the same `struct mutex' 2 times (and even more so:
 * with differing field names).
 *
 * Anyways: KOS's Hurd emulation only defines this one in `<cthreads.h>' */
struct mutex {
	__spin_lock_t __held;   /* The actually used lock */
	__spin_lock_t __lock;   /* unused */
	const char   *__name;   /* unused */
	void         *__head;   /* unused */
	void         *__tail;   /* unused */
	void         *__holder; /* unused */
};
#define MUTEX_INITIALIZER { 0, 0, __NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR }
#endif

}

[[nocrt, alias("__mutex_init", "__spin_lock_init")]]
[[inline({ *(unsigned int *)lock = 0; })]]
void __mutex_init([[out]] void *lock);

[[nocrt, alias("__mutex_lock", "__mutex_lock_solid", "mutex_wait_lock", "__spin_lock", "__spin_lock_solid")]]
[[if($has_function(shared_lock_acquire)), bind_local_function(__spin_lock_solid)]]
void __mutex_lock([[inout]] void *lock);

[[nocrt, alias("__mutex_lock_solid", "__mutex_lock", "mutex_wait_lock", "__spin_lock", "__spin_lock_solid")]]
[[if($has_function(shared_lock_acquire)), bind_local_function(__spin_lock_solid)]]
void __mutex_lock_solid([[inout]] void *lock);

[[nocrt, alias("__mutex_unlock", "mutex_unlock", "__spin_unlock")]]
[[if($has_function(shared_lock_release_ex)), bind_local_function(__spin_unlock)]]
void __mutex_unlock([[inout]] void *lock);

[[requires_function(shared_lock_waitfor)]]
[[impl_include("<kos/bits/shared-lock.h>")]]
void __mutex_unlock_solid([[inout]] void *lock) {
	shared_lock_waitfor((struct shared_lock *)lock);
}

[[nocrt, alias("__mutex_trylock", "__spin_try_lock")]]
[[if($has_function(shared_lock_tryacquire)), bind_local_function(__spin_try_lock)]]
int __mutex_trylock([[inout]] void *lock);



%{

__SYSDECL_END
#endif /* __CC__ */

}
