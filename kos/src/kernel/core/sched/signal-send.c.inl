/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "signal.c"
#define DEFINE_SINGLE    1
#define DEFINE_ALTERNATE 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

#if defined(DEFINE_SINGLE) && defined(DEFINE_ALTERNATE)
PUBLIC NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL sig_altsend)(struct sig *__restrict self, struct sig *sender)
#elif defined(DEFINE_SINGLE)
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL sig_send)(struct sig *__restrict self)
#elif defined(DEFINE_ALTERNATE)
PUBLIC NOBLOCK NONNULL((1, 2)) size_t
NOTHROW(KCALL sig_altbroadcast)(struct sig *__restrict self, struct sig *sender)
#else
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL sig_broadcast)(struct sig *__restrict self)
#endif
{
#ifndef DEFINE_SINGLE
	size_t result = 0;
#endif /* !DEFINE_SINGLE */
	struct task_connection *c;
#ifdef DEFINE_SINGLE
	{
		pflag_t was;
again:
#ifndef CONFIG_NO_SMP
		for (;;) {
			c = ATOMIC_READ(self->s_ptr);
			if (c == NULL)
				return false;
			if unlikely(c == SIG_TEMPLOCK) {
				task_pause();
				continue;
			}
			/* Disable preemption to we don't get interrupted by other code that may try
			 * to do the same thing we're trying to do: Send/broadcast this signal. */
			was = PREEMPTION_PUSHOFF();
			if likely(ATOMIC_CMPXCH_WEAK(self->s_ptr, c, SIG_TEMPLOCK))
				break;
			PREEMPTION_POP(was);
		}
		assert(c->tc_signext != SIG_TEMPLOCK);
		ATOMIC_WRITE(self->s_ptr, c->tc_signext);
		PREEMPTION_POP(was);
#else /* !CONFIG_NO_SMP */
		was = PREEMPTION_PUSHOFF();
		c   = ATOMIC_READ(self->s_ptr);
		if (c == NULL) {
			PREEMPTION_POP(was);
			return false;
		}
		ATOMIC_WRITE(self->s_ptr, c->tc_signext);
		PREEMPTION_POP(was);
#endif /* CONFIG_NO_SMP */
	}
#else /* DEFINE_SINGLE */
#ifdef SIG_TEMPLOCK
	do {
		c = ATOMIC_READ(self->s_ptr);
		if unlikely(c == SIG_TEMPLOCK) {
			task_pause();
			continue;
		}
	} while (!ATOMIC_CMPXCH_WEAK(self->s_ptr, c, NULL));
#else /* SIG_TEMPLOCK */
	c = ATOMIC_XCH(self->s_ptr, NULL);
#endif /* !SIG_TEMPLOCK */
#endif /* !DEFINE_SINGLE */

#ifndef DEFINE_SINGLE
	while (c)
#endif /* !DEFINE_SINGLE */
	{
#ifndef DEFINE_SINGLE
		struct task_connection *n;
		n = c->tc_signext;
#endif /* !DEFINE_SINGLE */
		for (;;) {
			struct sig *constate;
			constate = ATOMIC_READ(c->tc_signal);
			if (constate == TASK_CONNECTION_DISCONNECTING) {
				if unlikely(!ATOMIC_CMPXCH_WEAK(c->tc_signal,
				                                TASK_CONNECTION_DISCONNECTING,
				                                TASK_CONNECTION_DELIVERED))
					continue;
#ifdef DEFINE_SINGLE
				goto again;
#else /* DEFINE_SINGLE */
				break; /* wake_next_thread */
#endif /* !DEFINE_SINGLE */
			}
			if (((uintptr_t)constate & ~1) == (uintptr_t)self) {
				struct task_sigset *set;
				if (!ATOMIC_CMPXCH_WEAK(c->tc_signal, constate, TASK_CONNECTION_DELIVERING))
					continue;
				COMPILER_READ_BARRIER();
				set = ATOMIC_XCH(c->tc_cons, NULL);
				if (set) {
					if (ATOMIC_CMPXCH(set->ts_dlvr, NULL, self)) {
						struct task *thread;
						thread = set->ts_thread;
						if (!thread || task_wake(thread)) {
							if (!((uintptr_t)constate & 1)) {
								/* Don't track ghosts */
#ifdef DEFINE_SINGLE
								ATOMIC_WRITE(c->tc_signal, TASK_CONNECTION_DELIVERED);
								return true;
#else /* DEFINE_SINGLE */
								++result;
#endif /* !DEFINE_SINGLE */
							}
						}
					}
				}
				ATOMIC_WRITE(c->tc_signal, TASK_CONNECTION_DELIVERED);
#ifdef DEFINE_SINGLE
				goto again;
#else /* DEFINE_SINGLE */
				break; /* wake_next_thread */
#endif /* !DEFINE_SINGLE */
			}
		}
#ifndef DEFINE_SINGLE
		c = n;
#endif /* !DEFINE_SINGLE */
	}
#ifndef DEFINE_SINGLE
	return result;
#endif /* !DEFINE_SINGLE */
}

DECL_END

#undef DEFINE_SINGLE
#undef DEFINE_ALTERNATE

