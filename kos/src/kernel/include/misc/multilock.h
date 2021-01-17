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
#ifndef GUARD_KERNEL_INCLUDE_MISC_MULTILOCK_H
#define GUARD_KERNEL_INCLUDE_MISC_MULTILOCK_H 1

#include <kernel/compiler.h>

#ifdef __CC__
DECL_BEGIN

/* Helper macros to lock/unlock multiple locks at once. */


/************************************************************************/
/* 1 lock                                                               */
/************************************************************************/
#define multilock_acquire1(trylock_a, yield) \
	do {                                     \
		while (!(trylock_a))                 \
			yield;                           \
	}	__WHILE0
#define multilock_release1(unlock_a) \
	do {                             \
		unlock_a;                    \
	}	__WHILE0


/************************************************************************/
/* 2 locks                                                              */
/************************************************************************/
#define multilock_acquire2(trylock_a, unlock_a, \
                           trylock_b, unlock_b, \
                           yield)               \
	do {                                        \
		for (;;) {                              \
			if (trylock_a) {                    \
				if (trylock_b)                  \
					break;                      \
				unlock_a;                       \
			}                                   \
			yield;                              \
		}                                       \
	}	__WHILE0
#define multilock_release2(unlock_a, unlock_b) \
	do {                                       \
		unlock_b;                              \
		unlock_a;                              \
	}	__WHILE0


/************************************************************************/
/* SMP-lock helpers                                                     */
/************************************************************************/
#ifdef CONFIG_NO_SMP
#define smp_multilock_acquire1_nopr(trylock_a)                                (void)0
#define smp_multilock_release1_nopr(unlock_a)                                 (void)0
#define smp_multilock_acquire2_nopr(trylock_a, unlock_a, trylock_b, unlock_b) (void)0
#define smp_multilock_release2_nopr(unlock_a, unlock_b)                       (void)0
#else /* CONFIG_NO_SMP */
#define smp_multilock_acquire1_nopr(trylock_a) multilock_acquire1(trylock_a, task_pause())
#define smp_multilock_release1_nopr(unlock_a)  multilock_release1(unlock_a)
#define smp_multilock_acquire2_nopr(trylock_a, unlock_a, trylock_b, unlock_b) \
	multilock_acquire2(trylock_a, unlock_a, trylock_b, unlock_b, task_pause())
#define smp_multilock_release2_nopr(unlock_a, unlock_b) \
	multilock_release2(unlock_a, unlock_b)
#endif /* !CONFIG_NO_SMP */
#define _smp_multilock_acquire_begin do { pflag_t __smp_ml_was = PREEMPTION_PUSHOFF()
#define _smp_multilock_acquire_end   PREEMPTION_POP(__smp_ml_was); } __WHILE0
#define smp_multilock_acquire2(trylock_a, unlock_a, trylock_b, unlock_b) \
	_smp_multilock_acquire_begin;                                        \
	smp_multilock_acquire2_nopr(trylock_a, unlock_a, trylock_b, unlock_b)
#define smp_multilock_release2(unlock_a, unlock_b)   \
	smp_multilock_release2_nopr(unlock_a, unlock_b); \
	_smp_multilock_acquire_end
#define smp_multilock_acquire1(trylock_a) \
	_smp_multilock_acquire_begin;         \
	smp_multilock_acquire1_nopr(trylock_a)
#define smp_multilock_release1(unlock_a)   \
	smp_multilock_release1_nopr(unlock_a); \
	_smp_multilock_acquire_end


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_MISC_MULTILOCK_H */
