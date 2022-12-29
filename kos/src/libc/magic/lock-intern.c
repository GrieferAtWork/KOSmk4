/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
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
#include <kos/sched/shared-lock.h>
)]%[insert:prefix(
#include <hybrid/sched/__yield.h>
)]%{

#ifdef __CC__
__SYSDECL_BEGIN

typedef unsigned int __spin_lock_t;
#define __SPIN_LOCK_INITIALIZER 0

#ifndef __mutex_defined
#define __mutex_defined
struct mutex {
	__spin_lock_t __held;   /* The actually used lock */
	__spin_lock_t __lock;   /* unused */
	const char   *__name;   /* unused */
	void         *__head;   /* unused */
	void         *__tail;   /* unused */
	void         *__holder; /* unused */
};
#define MUTEX_INITIALIZER { 0, 0, __NULLPTR, __NULLPTR, __NULLPTR, __NULLPTR }
#endif /* !__mutex_defined */

}

%[define_replacement(__spin_lock_t = "unsigned int")]

[[extern_inline]]
void __spin_lock_init([[out]] __spin_lock_t *lock) {
	*lock = 0;
}

[[extern_inline]]
[[requires_include("<kos/sched/shared-lock.h>")]]
[[requires(defined(shared_lock_tryacquire))]]
[[impl_include("<kos/sched/shared-lock.h>")]]
[[impl_include("<hybrid/sched/__yield.h>")]]
void __spin_lock_solid([[inout]] __spin_lock_t *lock) {
	while (!shared_lock_tryacquire((struct shared_lock *)lock))
		__hybrid_yield();
}


[[nocrt, alias("__spin_lock", "shared_lock_acquire")]]
[[bind_local_function(shared_lock_acquire)]]
void __spin_lock([[inout]] __spin_lock_t *lock);


[[extern_inline]]
[[requires_include("<kos/sched/shared-lock.h>")]]
[[requires(defined(shared_lock_release))]]
[[impl_include("<kos/sched/shared-lock.h>")]]
void __spin_unlock([[inout]] __spin_lock_t *lock) {
	shared_lock_release((struct shared_lock *)lock);
}


[[extern_inline]]
[[requires_include("<kos/sched/shared-lock.h>")]]
[[requires(defined(shared_lock_tryacquire))]]
[[impl_include("<kos/sched/shared-lock.h>")]]
int __spin_try_lock([[inout]] __spin_lock_t *lock) {
	return shared_lock_tryacquire((struct shared_lock *)lock);
}

[[extern_inline]]
[[decl_include("<features.h>")]]
[[requires_include("<kos/sched/shared-lock.h>")]]
[[requires(defined(shared_lock_acquired))]]
[[impl_include("<kos/sched/shared-lock.h>")]]
int __spin_lock_locked([[in]] __spin_lock_t __KOS_FIXED_CONST *lock) {
	return shared_lock_acquired((struct shared_lock *)lock);
}



%{



/************************************************************************/
/* """Mutex""" API                                                      */
/************************************************************************/

}

[[extern_inline]]
[[crt_intern_alias(__spin_lock_init)]]
void __mutex_init([[out]] void *lock) {
	*(unsigned int *)lock = 0;
}

[[nocrt, alias("__mutex_lock", "shared_lock_acquire")]]
[[bind_local_function(shared_lock_acquire)]]
void __mutex_lock([[out]] void *lock);

[[extern_inline]]
[[requires_include("<kos/sched/shared-lock.h>")]]
[[requires(defined(shared_lock_release))]]
[[impl_include("<kos/sched/shared-lock.h>")]]
[[crt_intern_alias(__spin_unlock)]]
void __mutex_unlock([[out]] void *lock) {
	shared_lock_release((struct shared_lock *)lock);
}

[[extern_inline]]
[[requires_include("<kos/sched/shared-lock.h>")]]
[[requires(defined(shared_lock_tryacquire))]]
[[impl_include("<kos/sched/shared-lock.h>")]]
[[crt_intern_alias(__spin_try_lock)]]
int __mutex_trylock([[out]] void *lock) {
	return shared_lock_tryacquire((struct shared_lock *)lock);
}



%{

__SYSDECL_END
#endif /* __CC__ */

}
