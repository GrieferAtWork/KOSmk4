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
#ifdef __INTELLISENSE__
#include "except-handler.c"
//#define DEFINE_userexcept_handler
#define DEFINE_userexcept_handler_with_sigmask
//#define DEFINE_userexcept_sysret
#endif /* __INTELLISENSE__ */

#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_KERNEL_USERPROCMASK */
#include <sched/group.h>
#include <sched/sigmask.h>

#include <stdalign.h>

#if (defined(DEFINE_userexcept_handler) +              \
     defined(DEFINE_userexcept_handler_with_sigmask) + \
     defined(DEFINE_userexcept_sysret)) != 1
#error "Must #define exactly one of `DEFINE_userexcept_handler' or `DEFINE_userexcept_sysret'"
#endif /* ... */

DECL_BEGIN


#ifdef DEFINE_userexcept_handler
/* High-level exception handler that must be called by _all_ interrupts
 * and system call invocation wrappers.  This function is very  special
 * in that it _only_ returns when the associated interrupt/syscall must
 * be restarted immediately (for whatever reason).
 *
 * When  anything else needs to be done  in order to handle the currently
 * set exception, then this function won't return normally, but will load
 * the (at that point modified) `state' directly (via `cpu_apply(3)')
 *
 * The implementation of this function serves the function  documented
 * in <kos/rpc.md> under the name `generic_interrupt_or_system_call()'
 *
 * WARNING: When this function returns, it will have cleared the current
 *          exception, as it is also capable of handling (some)  errors,
 *          most notably `E_INTERRUPT_USER_RPC'! */
PUBLIC ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_handler)(struct icpustate *__restrict state,
                                  struct rpc_syscall_info const *sc_info)
#undef LOCAL_IS_SYSRET
#undef LOCAL_HAVE_SIGMASK
#elif defined(DEFINE_userexcept_handler_with_sigmask)
/* Same as `userexcept_handler()', but use the given `sigmask'
 * instead   of   the  calling   thread's   thread-local  one. */
PUBLIC ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct icpustate *
NOTHROW(FCALL userexcept_handler_with_sigmask)(struct icpustate *__restrict state,
                                               struct rpc_syscall_info const *sc_info,
                                               sigset_t const *__restrict sigmask)
#undef LOCAL_IS_SYSRET
#define LOCAL_HAVE_SIGMASK
#else /* ... */
/* This is the function that is injected by `userexcept_sysret_inject_nopr()',
 * as well as related functions.
 *
 * The   implementation  of  this  function  serves  the  function
 * documented in <kos/rpc.md> under the name `handle_sysret_rpc()' */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_sysret)(struct icpustate *__restrict state)
#define LOCAL_IS_SYSRET
#undef LOCAL_HAVE_SIGMASK
#endif /* !... */
{
	struct pending_rpc_slist pending;
	struct pending_rpc_slist restore;
	struct pending_rpc_slist repeat;
	struct pending_rpc **restore_plast;
	struct pending_rpc_slist kernel_rpcs;
	struct exception_info error;
	uint32_t pending_bitset;
	uint32_t restore_bitset;
	uint32_t repeat_bitset;
#ifndef LOCAL_IS_SYSRET
	struct rpc_context ctx;
#else /* !LOCAL_IS_SYSRET */
	alignas(alignof(struct rpc_context))
	byte_t _ctxbuf[offsetof(struct rpc_context, rc_scinfo)];
#define ctx (*(struct rpc_context *)_ctxbuf)
#endif /* !LOCAL_IS_SYSRET */

	assertf(PERTASK_EQ(this_exception_info.ei_flags, EXCEPT_FNORMAL),
	        "Unexpected exception flags");
	assertf(PERTASK_EQ(this_exception_info.ei_nesting, 0),
	        "There are still saved, nested exception somewhere on our stack");
	assertf(PREEMPTION_ENABLED(),
	        "Preemption must be enabled to propagate exceptions to user-space.");
	assertf(icpustate_isuser(state),
	        "In user exception handler, but return state points to kernel-space");

#ifndef LOCAL_IS_SYSRET

	/* Load exception information. */
	memcpy(&error, except_info(), sizeof(error));
	assertf(error.ei_code != EXCEPT_CODEOF(E_OK),
	        "In user exception handler, but no exception was thrown");

	/* Assert that there are no active task connections. */
#ifndef NDEBUG
	{
		struct task_connections *self = THIS_CONNECTIONS;
		struct task_connection *con   = self->tcs_con;
		assertf(con == NULL, "con = %p", con);
	}
#endif /* !NDEBUG */

	/* Consume the current exception. */
	PERTASK_SET(this_exception_code, EXCEPT_CODEOF(E_OK));

	/* Handle the `E_INTERRUPT_USER_RPC' exception now. */
	if (error.ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
		DBG_memset(&error, 0xcc, sizeof(error));
		error.ei_code = EXCEPT_CODEOF(E_OK);
	}
	if (sc_info) {
		ctx.rc_context = RPC_REASONCTX_SYSCALL;
		ctx.rc_scinfo  = *sc_info;
	} else {
		ctx.rc_context = RPC_REASONCTX_INTERRUPT;
	}
	if (error.ei_code != EXCEPT_CODEOF(E_OK))
		ctx.rc_context = RPC_REASONCTX_SYSRET; /* Will need to return to user-space to handle this exception */
#else /* !LOCAL_IS_SYSRET */
	/* Re-enable disabled RPCs and serve kernel RPCs with `RPC_REASONCTX_SYSRET' */
	ctx.rc_context = RPC_REASONCTX_SYSRET;
	error.ei_code  = EXCEPT_CODEOF(E_OK);
#endif /* !LOCAL_IS_SYSRET */

	ctx.rc_state = state;
	restore_plast = SLIST_PFIRST(&restore);
	restore_bitset = 0;
	SLIST_INIT(&kernel_rpcs);
	SLIST_INIT(&repeat);
	repeat_bitset = 0;

#ifdef LOCAL_IS_SYSRET
	/* Also  clear the `TASK_FWAKEONMSKRPC'  during sysret, thus making
	 * it possible to implement poll support for receiving signals that
	 * are  currently masked (polling  is done by  setting the flag, as
	 * well as calling  `userexcept_sysret_inject_self()' to make  sure
	 * that sysret is invoked before user-space return).
	 *
	 * Because there is no way to  define custom operations to be  done
	 * during disconnect, this is the best way of making it possible to
	 * do normal polling for signals  (especially since RPCs don't  use
	 * the normal  sig_send mechanisms, meaning that it's impossible to
	 * wait for a thread other than THIS_TASK to receive RPCs) */
	ATOMIC_AND(PERTASK(this_task.t_flags), ~(TASK_FRPC | TASK_FWAKEONMSKRPC));
#else /* LOCAL_IS_SYSRET */
	ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
#endif /* !LOCAL_IS_SYSRET */

	/* Load RPC functions. This must happen _AFTER_ we clear
	 * the  pending-RPC  flag to  prevent a  race condition. */
	pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	pending_bitset    = ATOMIC_READ(PERTASK(this_rpcs_sigpend));

handle_pending:
	for (;;) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&pending);
		if (!rpc)
			break;
		SLIST_REMOVE_HEAD(&pending, pr_link);
		/* Here, kernel RPCs are executed _after_ user RPCs. */
		if (rpc->pr_flags & RPC_CONTEXT_KERN) {
#ifndef LOCAL_IS_SYSRET
			/* Check if this system call _must_ be handled during SYSRET. */
			if (rpc->pr_flags & RPC_SYNCMODE_F_SYSRET) {
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
				rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
			} else
#endif /* !LOCAL_IS_SYSRET */
			{
				/* NOTE: This also inverts the order back to first-scheduled-first-run */
				SLIST_INSERT_HEAD(&kernel_rpcs, rpc, pr_link);
			}
		} else {
#ifdef LOCAL_IS_SYSRET
			rpc->pr_flags &= ~_RPC_CONTEXT_INACTIVE;
#endif /* LOCAL_IS_SYSRET */

#ifndef LOCAL_IS_SYSRET
			if (rpc->pr_flags & _RPC_CONTEXT_INACTIVE) {
				/* RPC was disabled in an earlier pass. */
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
			} else
#endif /* !LOCAL_IS_SYSRET */

#ifdef LOCAL_IS_SYSRET
			if (!(rpc->pr_flags & RPC_SYNCMODE_F_ALLOW_ASYNC)) {
				/* RPC isn't allowed in an async context. */
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
			} else
#endif /* LOCAL_IS_SYSRET */
			{
				/* User-space RPC
				 * NOTE: These are executed in reverse  order, since each one  executed
				 *       will return to the context loaded by the one that was executed
				 *       before, meaning that the last one executed (iow: the first one
				 *       originally scheduled) will have the last word when it comes to
				 *       where execution should continue. */
#if !defined(LOCAL_HAVE_SIGMASK) && defined(CONFIG_HAVE_KERNEL_USERPROCMASK)
				bool is_masked;
				TRY {
					is_masked = sigmask_ismasked(_RPC_GETSIGNO(rpc->pr_flags));
				} EXCEPT {
					/* Prioritize errors. */
					struct exception_info *tls = except_info();
					if (except_priority(error.ei_code) < except_priority(tls->ei_code)) {
						memcpy(&error, tls, sizeof(error));
						ctx.rc_context = RPC_REASONCTX_SYSRET; /* Will need to return to user-space to handle this exception */
					}
					assert(!(rpc->pr_flags & _RPC_CONTEXT_DONTFREE));
					if (rpc->pr_flags & RPC_CONTEXT_SIGNAL) {
						pending_rpc_free(rpc);
					} else {
						decref(&rpc->pr_user);
					}
					continue;
				}
				if (is_masked)
#elif !defined(LOCAL_HAVE_SIGMASK)
				if (sigmask_ismasked(_RPC_GETSIGNO(rpc->pr_flags)))
#else /* !... */
				if (sigismember(sigmask, _RPC_GETSIGNO(rpc->pr_flags)))
#endif /* ... */
				{
					/* User-space RPCs are currently masked. */
#ifndef LOCAL_IS_SYSRET
make_inactive:
#endif /* !LOCAL_IS_SYSRET */
					*restore_plast = rpc;
					restore_plast  = &rpc->pr_link.sle_next;
#ifndef LOCAL_IS_SYSRET
					rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
#endif /* !LOCAL_IS_SYSRET */
					continue;
				}

#ifndef LOCAL_IS_SYSRET
				if (sc_info != NULL) {
					if ((rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_CP) &&
					    !kernel_syscall_iscp(sc_info))
						goto make_inactive;
				} else {
					if ((rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_SC))
						goto make_inactive;
				}
#endif /* !LOCAL_IS_SYSRET */

				/* Do everything necessary to handle the USER-rpc. */
				if (!userexcept_exec_user_rpc(&ctx, &error, rpc))
					SLIST_INSERT(&repeat, rpc, pr_link);
#ifdef LOCAL_IS_SYSRET
				else {
					assert(ctx.rc_context == RPC_REASONCTX_SYSRET);
				}
#endif /* !LOCAL_IS_SYSRET */
			}
		}
	}

	if (pending_bitset) {
#ifndef LOCAL_IS_SYSRET
		uint32_t inactive = PERTASK_GET(this_rpcs_sigpend_inactive);
#endif /* LOCAL_IS_SYSRET */
		signo_t signo;
		pending_bitset = ATOMIC_XCH(PERTASK(this_rpcs_sigpend), 0);
#ifdef LOCAL_IS_SYSRET
		PERTASK_SET(this_rpcs_sigpend_inactive, 0);
#endif /* LOCAL_IS_SYSRET */
		for (signo = 1; signo <= 31; ++signo) {
			uint32_t signo_mask = (uint32_t)1 << signo;
			if (!(pending_bitset & signo_mask))
				continue;
#ifndef LOCAL_IS_SYSRET
			if (inactive & signo_mask) {
				/* RPC was disabled in an earlier pass. */
				restore_bitset |= signo_mask;
			} else
#endif /* !LOCAL_IS_SYSRET */
			{
				/* User-space RPC
				 * NOTE: These are executed in reverse  order, since each one  executed
				 *       will return to the context loaded by the one that was executed
				 *       before, meaning that the last one executed (iow: the first one
				 *       originally scheduled) will have the last word when it comes to
				 *       where execution should continue. */
#if !defined(LOCAL_HAVE_SIGMASK) && defined(CONFIG_HAVE_KERNEL_USERPROCMASK)
				bool is_masked;
				TRY {
					is_masked = sigmask_ismasked(signo);
				} EXCEPT {
					/* Prioritize errors. */
					struct exception_info *tls = except_info();
					if (except_priority(error.ei_code) < except_priority(tls->ei_code)) {
						memcpy(&error, tls, sizeof(error));
						ctx.rc_context = RPC_REASONCTX_SYSRET; /* Will need to return to user-space to handle this exception */
					}
					continue;
				}
				if (is_masked)
#elif !defined(LOCAL_HAVE_SIGMASK)
				if (sigmask_ismasked(signo))
#else /* !... */
				if (sigismember(sigmask, signo))
#endif /* ... */
				{
					/* User-space RPCs are currently masked. */
					restore_bitset |= signo_mask;
#ifndef LOCAL_IS_SYSRET
					inactive |= signo_mask;
					PERTASK_SET(this_rpcs_sigpend_inactive, inactive);
#endif /* !LOCAL_IS_SYSRET */
					continue;
				}

				/* Do everything necessary to handle the USER-rpc. */
				if (!userexcept_exec_user_signo_rpc(&ctx, &error, signo))
					repeat_bitset |= signo_mask;
#ifdef LCAL_IS_SYSRET
				else {
					assert(ctx.rc_context == RPC_REASONCTX_SYSRET);
				}
#endif /* !LOCAL_IS_SYSRET */
			}
		}
	}

	/* Service process-directed RPCs.
	 * NOTE: Handling of these special process-directed RPCs functions the
	 *       same like thread-directed ones (the handling of which can  be
	 *       seen above)
	 * NOTE: Additionally, this part is only done so-long as no exception
	 *       has been set (iow:  `error.ei_code == EXCEPT_CODEOF(E_OK)'). */
	if (error.ei_code == EXCEPT_CODEOF(E_OK)) {
		struct procctl *proc = task_getprocctl();
		struct pending_rpc *rpc;
		uint32_t pending_bitset;
		rpc            = ATOMIC_READ(proc->pc_sig_list.slh_first);
		pending_bitset = ATOMIC_READ(proc->pc_sig_pend);
		if ((rpc != NULL && rpc != THIS_RPCS_TERMINATED) || pending_bitset) {
			struct pending_rpc **p_rpc;
			bool has_write_lock;
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
			sigset_t known_unmasked_signals;
			sigset_t known_masked_signals;
			sigemptyset(&known_unmasked_signals);
			sigemptyset(&known_masked_signals);
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */
again_lock_proc_rpcs:
			has_write_lock = false;
			procctl_sig_read(proc);
again_scan_proc_rpcs:
			p_rpc = SLIST_PFIRST(&proc->pc_sig_list);
			rpc   = *p_rpc;
			if likely(rpc != NULL && rpc != THIS_RPCS_TERMINATED) {
				for (;;) {
					/* Figure out if we should handle this RPC. */
					if (rpc->pr_flags & RPC_CONTEXT_KERN) {
#ifndef LOCAL_IS_SYSRET
						if (rpc->pr_flags & RPC_SYNCMODE_F_SYSRET)
							goto check_next_proc_rpc;
#endif /* !LOCAL_IS_SYSRET */
					} else {
						signo_t signo;
						assertf(!(rpc->pr_flags & _RPC_CONTEXT_INACTIVE), "How did this get set?");
						assertf(!(rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_SC), "Flag not allowed for process RPCs");
						assertf(!(rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_CP), "Flag not allowed for process RPCs");
#ifdef LOCAL_IS_SYSRET
						if (!(rpc->pr_flags & RPC_SYNCMODE_F_ALLOW_ASYNC))
							goto check_next_proc_rpc; /* Not allowed in ASYNC context */
#endif /* LOCAL_IS_SYSRET */

						/* Check if the signal number used by this RPC is currently masked. */
						signo = _RPC_GETSIGNO(rpc->pr_flags);
#if !defined(LOCAL_HAVE_SIGMASK) && defined(CONFIG_HAVE_KERNEL_USERPROCMASK)
						if (sigismember(&known_masked_signals, signo))
							goto check_next_proc_rpc; /* Known-masked signal */
						if (!sigismember(&known_unmasked_signals, signo)) {
							/* Signal isn't known to be unmasked. */
							int status = sigmask_ismasked_nopf(signo);
							if (status == SIGMASK_ISMASKED_NOPF_YES) {
								sigaddset(&known_masked_signals, signo);
								goto check_next_proc_rpc; /* Known-masked signal */
							}
							if (status == SIGMASK_ISMASKED_NOPF_FAULT) {
								/* Must do this the hard way... */
								if (has_write_lock) {
									procctl_sig_endwrite(proc);
								} else {
									procctl_sig_endread(proc);
								}
								TRY {
									status = sigmask_ismasked(signo);
								} EXCEPT {
									/* Prioritize errors. */
									struct exception_info *tls = except_info();
									if (except_priority(error.ei_code) < except_priority(tls->ei_code))
										memcpy(&error, tls, sizeof(error));
									status = 1; /* Assume masked, so we don't consume RPCs for this signal! */
								}
								/* Remember what we learned about this signal number. */
								if (status) {
									sigaddset(&known_masked_signals, signo);
								} else {
									sigaddset(&known_unmasked_signals, signo);
								}
								goto again_lock_proc_rpcs;
							}
							/* Unmasked signal */
							sigaddset(&known_unmasked_signals, signo);
						}
#elif !defined(LOCAL_HAVE_SIGMASK)
						if (sigmask_ismasked(signo))
							goto check_next_proc_rpc; /* Masked signal */
#else /* ... */
						if (sigismember(sigmask, signo))
							goto check_next_proc_rpc; /* Masked signal */
#endif /* !... */
					}
					/* Yes: we _are_ allowed to handle this RPC! */

					/* If necessary, upgrade to a write-lock. */
					if (!has_write_lock) {
						if (!procctl_sig_tryupgrade(proc)) {
							procctl_sig_endread(proc);
							procctl_sig_write(proc);
							has_write_lock = true;
							goto again_scan_proc_rpcs;
						}
						has_write_lock = true;
					}

					/* Remove `rpc' from the list */
					if (p_rpc == &proc->pc_sig_list.slh_first) {
						/* Check for race condition: new RPCs were added in the mean time. */
						if (!ATOMIC_CMPXCH(*p_rpc, rpc, rpc->pr_link.sle_next))
							goto again_scan_proc_rpcs;
					} else {
						assert(*p_rpc == rpc);
						*p_rpc = rpc->pr_link.sle_next;
					}

					COMPILER_BARRIER();
					procctl_sig_endwrite(proc);
					/* At this point, we've taken ownership of `rpc', and won't ever give it back! */
					if (rpc->pr_flags & RPC_CONTEXT_KERN) {
						/* Handle this RPC later. */
						SLIST_INSERT_HEAD(&kernel_rpcs, rpc, pr_link);
					} else {
						/* User-space RPC */
						if (!userexcept_exec_user_rpc(&ctx, &error, rpc))
							SLIST_INSERT(&repeat, rpc, pr_link);
#ifdef LOCAL_IS_SYSRET
						else {
							assert(ctx.rc_context == RPC_REASONCTX_SYSRET);
						}
#endif /* LOCAL_IS_SYSRET */
					}
					goto again_lock_proc_rpcs;
check_next_proc_rpc:
					p_rpc = &rpc->pr_link.sle_next;
					rpc   = *p_rpc;
					if (!rpc)
						break;
				}
			}
			pending_bitset = ATOMIC_READ(proc->pc_sig_pend);
			if (pending_bitset) {
				signo_t signo;
				for (signo = 1; signo <= 31; ++signo) {
					uint32_t signo_mask = (uint32_t)1 << signo;
					if (!(pending_bitset & signo_mask))
						continue;
					/* Figure out if we should handle this RPC. */
#if !defined(LOCAL_HAVE_SIGMASK) && defined(CONFIG_HAVE_KERNEL_USERPROCMASK)
					if (sigismember(&known_masked_signals, signo))
						continue; /* Known-masked signal */
					if (!sigismember(&known_unmasked_signals, signo)) {
						/* Signal isn't known to be unmasked. */
						int status = sigmask_ismasked_nopf(signo);
						if (status == SIGMASK_ISMASKED_NOPF_YES) {
							sigaddset(&known_masked_signals, signo);
							continue; /* Known-masked signal */
						}
						if (status == SIGMASK_ISMASKED_NOPF_FAULT) {
							/* Must do this the hard way... */
							if (has_write_lock) {
								procctl_sig_endwrite(proc);
							} else {
								procctl_sig_endread(proc);
							}
							TRY {
								status = sigmask_ismasked(signo);
							} EXCEPT {
								/* Prioritize errors. */
								struct exception_info *tls = except_info();
								if (except_priority(error.ei_code) < except_priority(tls->ei_code))
									memcpy(&error, tls, sizeof(error));
								status = 1; /* Assume masked, so we don't consume RPCs for this signal! */
							}
							/* Remember what we learned about this signal number. */
							if (status) {
								sigaddset(&known_masked_signals, signo);
							} else {
								sigaddset(&known_unmasked_signals, signo);
							}
							goto again_lock_proc_rpcs;
						}
						/* Unmasked signal */
						sigaddset(&known_unmasked_signals, signo);
					}
#elif !defined(LOCAL_HAVE_SIGMASK)
					if (sigmask_ismasked(signo))
						continue; /* Masked signal */
#else /* ... */
					if (sigismember(sigmask, signo))
						continue; /* Masked signal */
#endif /* !... */
					/* Yes: we _are_ allowed to handle this RPC! */

					/* If necessary, upgrade to a write-lock. */
					if (!has_write_lock) {
						if (!procctl_sig_tryupgrade(proc)) {
							procctl_sig_endread(proc);
							procctl_sig_write(proc);
							has_write_lock = true;
							goto again_scan_proc_rpcs;
						}
						has_write_lock = true;
					}
					/* Remove `signo' from the list */
					if (!(ATOMIC_FETCHAND(proc->pc_sig_pend, ~signo_mask) & signo_mask))
						goto again_scan_proc_rpcs;
					procctl_sig_endwrite(proc);
					/* At this point, we've taken ownership of `rpc', and won't ever give it back! */
					/* User-space RPC */
					if (!userexcept_exec_user_signo_rpc(&ctx, &error, signo))
						repeat_bitset |= signo_mask;
#ifdef LOCAL_IS_SYSRET
					else {
						assert(ctx.rc_context == RPC_REASONCTX_SYSRET);
					}
#endif /* LOCAL_IS_SYSRET */
					goto again_lock_proc_rpcs;
				}
			}

			/* Release our lock. */
			if (has_write_lock) {
				procctl_sig_endwrite(proc);
			} else {
				procctl_sig_endread(proc);
			}
		}
	}


	/* Kernel RPCs are handled after user-space RPCs. This is needed so that
	 * user-space  RPCs have higher priority when it executing code before a
	 * system call can be performed in a situation where the system call  is
	 * implemented by a thread sending an RPC to itself (as is the suggested
	 * method of gaining access of one's own register state) */
	while (!SLIST_EMPTY(&kernel_rpcs)) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&kernel_rpcs);
		SLIST_REMOVE_HEAD(&kernel_rpcs, pr_link);
		assert(rpc->pr_flags & RPC_CONTEXT_KERN);
#ifndef LOCAL_IS_SYSRET
		if (rpc->pr_flags & RPC_SYNCMODE_F_SYSRET) {
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
			rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
		} else
#endif /* !LOCAL_IS_SYSRET */
		{
#ifndef LOCAL_IS_SYSRET
			if (ctx.rc_context != RPC_REASONCTX_SYSRET) {
				/* Indicate to the RPC that they're allowed to implement
				 * the actual work  of an interrupt/syscall.  This is  a
				 * very special case since in  this context, the RPC  is
				 * allowed to do  a longjmp (iow:  not return  normally,
				 * and not return by throwing an exception)
				 *
				 * Because of this, we have  to do all possible  cleanup
				 * beforehand, meaning that we have to restore all other
				 * RPCs that may still be pending. */
				prpc_exec_callback_t func;
				void *cookie;
				func   = rpc->pr_kern.k_func;
				cookie = rpc;
				if (!(rpc->pr_flags & _RPC_CONTEXT_DONTFREE)) {
					cookie = rpc->pr_kern.k_cookie;
					pending_rpc_free(rpc);
				}
				*restore_plast = SLIST_FIRST(&kernel_rpcs);
				while (!SLIST_EMPTY(&repeat)) {
					struct pending_rpc *repeat_rpc;
					repeat_rpc = SLIST_FIRST(&repeat);
					SLIST_REMOVE_HEAD(&repeat, pr_link);
					SLIST_INSERT_HEAD(&restore, repeat_rpc, pr_link);
				}
				if (!SLIST_EMPTY(&restore) || repeat_bitset) {
					/* WARNING: User-space RPCs in `restore' may still be marked as INACTIVE
					 *          at this point. This is normally  OK, but in case the  system
					 *          call doesn't want that, it  has to clear the INACTIVE  flags
					 *          itself. -- This has to be done in the case of  sigsuspend()! */
					restore_pending_rpcs(SLIST_FIRST(&restore));
					ATOMIC_OR(PERTASK(this_rpcs_sigpend), repeat_bitset);
					ATOMIC_OR(PERTASK(this_task.t_flags), TASK_FRPC);
					assert(PREEMPTION_ENABLED());
					PREEMPTION_DISABLE();
					ctx.rc_state = userexcept_sysret_inject_with_state_nopr(ctx.rc_state);
					PREEMPTION_ENABLE();
				}
				/* The following call is allowed not to return at all (neither
				 * normally, or by throwing an exception), as it is allowed to
				 * emulate a system call in whatever way it deems suitable! */
				TRY {
					(*func)(&ctx, cookie);
				} EXCEPT {
					struct exception_info *tls = except_info();
					/* Prioritize errors. */
					if (except_priority(error.ei_code) < except_priority(tls->ei_code) &&
					    tls->ei_code != EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
						memcpy(&error, tls, sizeof(error));
						ctx.rc_context = RPC_REASONCTX_SYSRET; /* Will need to return to user-space to handle this exception */
					}
				}
				restore_plast = SLIST_PFIRST(&restore);
				SLIST_INIT(&kernel_rpcs);
				ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
				pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
				DBG_memset(&restore, 0xcc, sizeof(restore));
				goto handle_pending;
			} else {
				uintptr_t rpc_flags = rpc->pr_flags;
				TRY {
					void *cookie = rpc;
					if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
						cookie = rpc->pr_kern.k_cookie;
					(*rpc->pr_kern.k_func)(&ctx, cookie);
				} EXCEPT {
					struct exception_info *tls = except_info();
					if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
						if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
							pending_rpc_free(rpc);
						/* Load additional RPCs, but discard this new exception */
						ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
						pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
						goto handle_pending;
					}
					/* Prioritize errors. */
					if (except_priority(error.ei_code) < except_priority(tls->ei_code))
						memcpy(&error, tls, sizeof(error));
				}
				if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
					pending_rpc_free(rpc);
			}
			assert(ctx.rc_context == RPC_REASONCTX_SYSRET ||
			       ctx.rc_context == (sc_info ? RPC_REASONCTX_SYSCALL
			                                  : RPC_REASONCTX_INTERRUPT));
#else /* !LOCAL_IS_SYSRET */
			uintptr_t rpc_flags = rpc->pr_flags;
			TRY {
				void *cookie = rpc;
				if (!(rpc_flags &_RPC_CONTEXT_DONTFREE))
					cookie = rpc->pr_kern.k_cookie;
				(*rpc->pr_kern.k_func)(&ctx, cookie);
			} EXCEPT {
				struct exception_info *tls = except_info();
				if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
					if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
						pending_rpc_free(rpc);
					/* Load additional RPCs, but discard this new exception */
					ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
					pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
					goto handle_pending;
				}
				/* Prioritize errors. */
				if (except_priority(error.ei_code) < except_priority(tls->ei_code))
					memcpy(&error, tls, sizeof(error));
			}
			assert(ctx.rc_context == RPC_REASONCTX_SYSRET);
			if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
				pending_rpc_free(rpc);
#endif /* !LOCAL_IS_SYSRET */
		}
	}

	/* Check if there are RPCs that need to be repeated. */
	if unlikely(!SLIST_EMPTY(&repeat) || repeat_bitset != 0) {
		struct pending_rpc **plast_pending, *repeat_rpc;
		ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
		pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
		plast_pending     = SLIST_PFIRST(&pending);
		while ((repeat_rpc = *plast_pending) != NULL)
			plast_pending = SLIST_PNEXT(repeat_rpc, pr_link);
		while (!SLIST_EMPTY(&repeat)) {
			repeat_rpc = SLIST_FIRST(&repeat);
			SLIST_REMOVE_HEAD(&repeat, pr_link);
			*plast_pending = repeat_rpc;
			plast_pending  = &repeat_rpc->pr_link.sle_next;
		}
		*plast_pending = NULL;
		pending_bitset = ATOMIC_READ(PERTASK(this_rpcs_sigpend)) | repeat_bitset;
		repeat_bitset  = 0;
		goto handle_pending;
	}

	/* Restore interrupts that could not be handled right now.
	 *
	 * #ifndef LOCAL_IS_SYSRET
	 * In case we don't restart the interrupt/syscall, we must
	 * also handle SYSRET RPCs (as those must be invoked  just
	 * before  returning to user-space,  which is what's about
	 * to happen)
	 * #endif */
	if (restore_plast != SLIST_PFIRST(&restore) || restore_bitset != 0) {
		*restore_plast = NULL; /* NULL-terminate list */

#ifndef LOCAL_IS_SYSRET
		/* When there's an unhandled exception, then it's impossible to
		 * restart the interrupt. Thus, we must indicate SYSRET status,
		 * or in other words: an  async user-space location to  kernel-
		 * level RPC functions. */
		if (error.ei_code != EXCEPT_CODEOF(E_OK)) {
			assert(ctx.rc_context == RPC_REASONCTX_SYSRET ||
			       ctx.rc_context == (sc_info ? RPC_REASONCTX_SYSCALL
			                                  : RPC_REASONCTX_INTERRUPT));
			ctx.rc_context = RPC_REASONCTX_SYSRET;
		}
		if (ctx.rc_context == RPC_REASONCTX_SYSRET) {
			/* When  the system call won't be restarted, then we must still
			 * serve kernel RPCS with the `RPC_SYNCMODE_F_SYSRET' flag set. */
			struct pending_rpc **piter;
			assert(SLIST_EMPTY(&kernel_rpcs));
			piter = SLIST_PFIRST(&restore);
			for (;;) {
				struct pending_rpc *rpc;
				rpc = *piter;
				if (!rpc)
					break;
				/* Because we won't restart, we must also clear the
				 * INACTIVE flag for all  RPCs that we're about  to
				 * restore. */
				rpc->pr_flags &= ~_RPC_CONTEXT_INACTIVE;
				if (rpc->pr_flags & RPC_CONTEXT_KERN) {
					*piter = rpc->pr_link.sle_next; /* Remove from restore list. */
					/* Insert into the `kernel_rpcs' list */
					SLIST_INSERT(&kernel_rpcs, rpc, pr_link);
				} else {
					piter = &rpc->pr_link.sle_next;
				}
			}
			while (!SLIST_EMPTY(&kernel_rpcs)) {
				struct pending_rpc *rpc;
				uintptr_t rpc_flags;
				rpc = SLIST_FIRST(&kernel_rpcs);
				SLIST_REMOVE_HEAD(&kernel_rpcs, pr_link);
				assert(rpc->pr_flags & RPC_SYNCMODE_F_SYSRET);
				rpc_flags = rpc->pr_flags;
				TRY {
					void *cookie = rpc;
					if (!(rpc_flags &_RPC_CONTEXT_DONTFREE))
						cookie = rpc->pr_kern.k_cookie;
					(*rpc->pr_kern.k_func)(&ctx, cookie);
				} EXCEPT {
					struct exception_info *tls = except_info();
					if (tls->ei_code == EXCEPT_CODEOF(E_INTERRUPT_USER_RPC)) {
						if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
							pending_rpc_free(rpc);
						/* Load additional RPCs, but discard this new exception */
						ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
						pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
						goto handle_pending;
					}
					/* Prioritize errors. */
					if (except_priority(error.ei_code) < except_priority(tls->ei_code))
						memcpy(&error, tls, sizeof(error));
				}
				assert(ctx.rc_context == RPC_REASONCTX_SYSRET);
				if (!(rpc_flags & _RPC_CONTEXT_DONTFREE))
					pending_rpc_free(rpc);
			}
		}
		if (!SLIST_EMPTY(&restore))
#endif /* !LOCAL_IS_SYSRET */
		{
			restore_pending_rpcs(SLIST_FIRST(&restore));
			ATOMIC_OR(PERTASK(this_task.t_flags), TASK_FRPC);
		}
		if (restore_bitset) {
			ATOMIC_OR(PERTASK(this_rpcs_sigpend), restore_bitset);
			/* Clear INACTIVE bits for all restored signals. */
			PERTASK_SET(this_rpcs_sigpend_inactive, PERTASK_GET(this_rpcs_sigpend_inactive) & ~restore_bitset);
		}
	}

	/* Check if we must throw a new exception. */
	if (error.ei_code != EXCEPT_CODEOF(E_OK)) {
		/* This will unwind into user-space!
		 * NOTE: This also handles `_E_STOP_PROCESS' and `_E_CORE_PROCESS'! */
#ifndef LOCAL_IS_SYSRET
		ctx.rc_state = userexcept_unwind(ctx.rc_state, &error, sc_info);
		cpu_apply_icpustate(ctx.rc_state);
#else /* !LOCAL_IS_SYSRET */
		ctx.rc_state = userexcept_unwind(ctx.rc_state, &error, NULL);
#endif /* LOCAL_IS_SYSRET */
	}

#ifndef LOCAL_IS_SYSRET
	/* If the return context was  altered such that (logically  speaking),
	 * it points into async user-space  (iow: the interrupted system  call
	 * should not be restarted, or will be restored by user-space itself),
	 * then we mustn't try to restart  it ourselves, but rather load  back
	 * all RPCs that  are still pending  before resuming normal  execution
	 * in user-space. */
	if (ctx.rc_context == RPC_REASONCTX_SYSRET)
		cpu_apply_icpustate(ctx.rc_state);

	/* Must restart a previously aborted interrupt/syscall with all of
	 * the RPCs that can't be handled in the context of said interrupt
	 * or  syscall marked as  INACTIVE (thus preventing `task_serve()'
	 * from trying to unwind for them)
	 *
	 * Once the interrupt/syscall completes as normal, all of them will
	 * be re-enabled once again. */
	if (!SLIST_EMPTY(&restore) || restore_bitset != 0) {
		/* The following call causes `handle_sysret_rpc()' to be
		 * invoked before we'll eventually return to user-space. */
		assert(PREEMPTION_ENABLED());
		PREEMPTION_DISABLE();
		ctx.rc_state = userexcept_sysret_inject_with_state_nopr(ctx.rc_state);
		/* userexcept_sysret_inject_nopr(THIS_TASK); // Same as `userexcept_sysret_inject_with_state_nopr()' */
		PREEMPTION_ENABLE();
	}
#endif /* !LOCAL_IS_SYSRET */

	/* [!LOCAL_IS_SYSRET]: Restart the interrupt/syscall.
	 * [LOCAL_IS_SYSRET]:  Resume normal execution. */
	return ctx.rc_state;
#undef ctx
}

#undef LOCAL_IS_SYSRET
#undef LOCAL_HAVE_SIGMASK

DECL_END

#undef DEFINE_userexcept_handler
#undef DEFINE_userexcept_handler_with_sigmask
#undef DEFINE_userexcept_sysret
