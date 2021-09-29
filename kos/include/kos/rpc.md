
### KOS RPC flags

- Kernel-private flags:
	- `RPC_CONTEXT_KERN`: Kernel-level (function-style) RPC. This flag cannot be set by user-space (the `rpc_schedule(2)` system call treats it as an unknown flag)
	- `RPC_CONTEXT_NOEXCEPT`: May only be used with `RPC_CONTEXT_KERN`: indicates that the accompanying function will never throw an exception, and may be invoked from `task_serve_nx()`
	- `_RPC_CONTEXT_INACTIVE`: Used internally to mark RPCs that are set to inactive, which is a mechanism used to prevent `RPC_SYNCMODE_F_REQUIRE_CP` RPCs from continuously aborting a non-cancellation-point system call, even when that system call invokes `task_serve()`.  
	  This flag must never be set when enqueueing an RPC
	- `RPC_SYNCMODE_F_USER`: The RPC may only be served in the context of returning to user-space:
		- `RPC_REASONCTX_SYSRET`     (Return to user-space location)
		- `RPC_REASONCTX_INTERRUPT`  (Interrupt was unwound)
		- `RPC_REASONCTX_SYSCALL`    (Syscall was unwound)
		- `RPC_REASONCTX_SHUTDOWN`   (Thread is exiting)
	- `RPC_SYNCMODE_F_SYSRET`: The RPC must be served **after** an associated interrupt/syscall has been completed without errors (s.a. [`handle_sysret_rpc()`](#handle_sysret_rpc))

- User-RPC-specific flags:
	- TODO



### KOS RPC implementation

The kernel defines an internal structure that is used for keeping track of scheduled RPCs (with the exception of kernel-level ASYNC RPCs, which are always immediately pushed onto the kernel stack)

```c
struct pending_rpc {
	SLIST_ENTRY(pending_rpc) pr_link;  /* [0..1][lock(ATOMIC)] Link in the list of pending RPCs */
	uintptr_t                pr_flags; /* [const] RPC flags: RPC_CONTEXT_KERN, ...
	                                    * NOTE: When `RPC_CONTEXT_INACTIVE' is set, then the RPC is inactive. */
	union {
		struct {
			prpc_exec_callback_t k_func;   /* [1..1][const] Function to invoke. */
			void                *k_cookie; /* [?..?][const] Cookie argument for `k_func' */
		}                       pr_kern;   /* [RPC_CONTEXT_KERN] Kernel-mode RPC */
		struct pending_user_rpc pr_user;   /* [!RPC_CONTEXT_KERN] User-mode RPC */
	};
};
```

Additionally, every thread has a TLS variable that represents a linked list to which other threads can enqueue RPCs to-be executed (for synchronisation, `SLIST_ATOMIC_INSERT()` is used for this):

```c
/* [0..n][lock(INSERT(ATOMIC), CLEAR(ATOMIC && THIS_TASK))] */
DATDEF ATTR_PERTASK struct pending_rpc_slist this_rpcs;
```

Finally, there exists a flag `TASK_FRPC` that is set when `this_rpcs` (may) contains RPCs that require the attention of the thread in question. Note that this flag is cleared by the thread itself, but may be set by anyone on the entire system. Also note that the thread may clear `TASK_FRPC`, but then end up keeping certain RPCs within the `this_rpcs` (for a period of time). This is intentional and the situations when (and why) this is done should become obvious as you continue reading this file.

### RPC Basics

On the kernel-level, 2 kinds of RPCs exist: synchronous RPCs, and asynchronous RPCs. The later only exists when using the flags `RPC_CONTEXT_KERN | RPC_SYNCMODE_F_ALLOW_ASYNC`, which causes the given RPC function to be called as the first thing to do once the target thread gets another quantum.

All other RPCs are handled by (in order):

- Enqueueing the RPC in the `this_rpcs` list of the target thread (using `SLIST_ATOMIC_INSERT`, but also checking that `this_rpcs` hasn't been set to `THIS_RPCS_TERMINATED`)
	- When `THIS_RPCS_TERMINATED` was already set, RPC scheduling functions may indicate to their caller that the targeted thread has already terminated.
- Setting the `TASK_FRPC` flag (using `ATOMIC_OR(thread->t_flags, TASK_FRPC)`)
- Sending a sporadic interrupt to the thread (using `task_redirect_usercode_rpc(thread)`, which both wakes the thread and forces it back into kernel-space if it was currently in user-space)

The rest of the work is the done in the context of the thread. Assuming a thread that sleeps by following the suggested sleeping method (which is also implemented by `task_waitfor()`):

```c
for (;;) {
	PREEMPTION_DISABLE();
	if (!SHOULD_SLEEP) {
		PREEMPTION_ENABLE();
		return EVENT_HAPPENED;
	}
	if (task_serve()) /* This handles RPCs */
		continue;
	if (!task_sleep(TIMEOUT))
		return TIMEOUT_EXPIRED;
	/* We get here in case of a sporadic interrupt */
}
```

With this in mind, let's move on to how this *magic* `task_serve()` function is implemented:


### The implementation of `task_serve()`

The `task_serve()` functions returns `true` when it re-enabled preemption and (possibly) invoked some RPC function. It will throw an exception `E_INTERRUPT_USER_RPC` when the calling thread needs to be unwound for the purpose of handling special RPCs that can only be executed just before returning to userspace.

```c
bool task_serve(void) THROWS(E_INTERRUPT_USER_RPC, ...) {
	bool result;
	struct icpustate *state;
	if (!(PERTASK_GET(this_task.t_flags) & TASK_FRPC))
		return false;
	state = ...; /* Custom assembly */
	state = task_serve_with_icpustate(state);
	if (state == NULL)
		return false;
	state->FUNCTION_RETURN_AS_BOOL = true;
	cpu_apply_icpustate(state);
}
```

Obviously, most of the actual work is done by `task_serve_with_icpustate()`, which is implemented as follows:

```c
/* Returns `NULL' if nothing got served. */
struct icpustate *task_serve_with_icpustate(struct icpustate *__restrict state) THROWS(E_INTERRUPT_USER_RPC, ...) {
	struct exception_info error;
	struct pending_rpc_slist pending; /* Pending RPCs */
	struct pending_rpc_slist runnow;  /* RPCs that should be executed now */
	struct pending_rpc_slist restore; /* RPCs that must be restored */
	struct pending_rpc **restore_plast;
	struct rpc_context ctx;
	bool did_serve_rpcs;
	bool must_unwind;
	ctx.rc_context    = RPC_REASONCTX_SYNC;
	ctx.rc_state      = state;
	error.ei_code     = ERROR_CODEOF(E_OK);
	pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	restore_plast     = SLIST_PFIRST(&restore);
	did_serve_rpcs    = false;
	must_unwind       = false;
handle_pending:
	ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
	while (!SLIST_EMPTY(&pending)) {
		struct pending_rpc *rpc = SLIST_FIRST(&pending);
		SLIST_REMOVE_HEAD(&pending, pr_link);
		if ((rpc->pr_flags & (RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER | _RPC_CONTEXT_INACTIVE)) == RPC_CONTEXT_KERN) {
			/* Enabling interrupts when RPCs get served is part of the ABI! */
			PREEMPTION_ENABLE();

			/* Execute synchronous kernel RPC immediately. */
			SLIST_INSERT_HEAD(&runnow, rpc, pr_link);
			did_serve_rpcs = true;
		} else {
			/* user-level-, or inactive RPC (restore) */
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
			if (!(rpc->pr_flags & _RPC_CONTEXT_INACTIVE)) {
				if (!(rpc->pr_flags & RPC_CONTEXT_KERN)) {
					/* NOTE: `sigmask_ismasked_chk_nopf()' returns one of:
					 *  - SIGMASK_ISMASKED_NOPF_YES:   Signal is masked
					 *  - SIGMASK_ISMASKED_NOPF_NO:    Signal isn't masked
					 *  - SIGMASK_ISMASKED_NOPF_FAULT: Unable to access userprocmask */
					int status = sigmask_ismasked_nopf(_RPC_GETSIGNO(rpc->pr_flags));
					if (status == SIGMASK_ISMASKED_NOPF_YES)
						continue; /* Signal is known to be masked! (so skip) */
				}

				/* Enabling interrupts when RPCs get served is part of the ABI! */
				PREEMPTION_ENABLE();
				must_unwind = true;
			}
		}
	}

	/* Execute kernel RPCs. */
	while (!SLIST_EMPTY(&runnow)) {
		prpc_exec_callback_t func;
		void *cookie;
		struct pending_rpc *rpc = SLIST_FIRST(&runnow);
		SLIST_REMOVE_HEAD(&runnow, pr_link);
		assert(rpc->pr_flags & RPC_CONTEXT_KERN);
		assert(!(rpc->pr_flags & RPC_SYNCMODE_F_USER));
		func   = rpc->pr_kern.k_func;
		cookie = rpc->pr_kern.k_cookie;
		pending_rpc_free(rpc);
		TRY {
			(*func)(&ctx, cookie);
		} EXCEPT {
			struct exception_info *tls = error_info();
			if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
				/* Load additional RPCs, but discard this new exception */
				ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
				pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
				goto handle_pending;
			}
			/* Prioritize errors. */
			if (error_priority(error.ei_code) < error_priority(tls->ei_code))
				memcpy(&error, tls, sizeof(error));
		}
		assert(ctx.rc_context == RPC_REASONCTX_SYNC);
	}

	/* Restore RPCs that can't be served right now. */
	if (restore_plast != SLIST_PFIRST(&restore)) {
		*restore_plast = NULL;
		restore_pending_rpcs(SLIST_FIRST(&restore));
	}

	/* Check if we must throw a new exception. */
	if (error.ei_code != ERROR_CODEOF(E_OK)) {
		memcpy(error_info(), &error, sizeof(error));
		_Unwind_Resume(ctx.rc_state);
	}

	/* Unmasked posix signals also require that we unwind the system call. */
	if (!must_unwind && ARE_UNMASKED_POSIX_SIGNALS_PENDING)
		must_unwind = true;
	if (must_unwind)
		THROW(E_INTERRUPT_USER_RPC);
	if (did_serve_rpcs)
		return ctx.rc_state;
	return NULL;
}
```



### The handling of `E_INTERRUPT_USER_RPC`

It should be obvious that there also needs to be some piece of code that is capable of handling the `E_INTERRUPT_USER_RPC` exceptions thrown by `task_serve()`. This piece of code takes the form of a mandatory exception handler for not only `E_INTERRUPT_USER_RPC`, but **all** exceptions. This special handler is required for any kernel interrupt handler, as well as all system call entry points / routers that might potentially call `task_serve()`

```c
/* This is how all system calls, and all interrupts (that may call `task_serve()') look like */
struct icpustate *generic_interrupt_or_system_call(struct icpustate *state,
                                                   struct rpc_syscall_info *sc_info) {
	struct pending_rpc_slist pending;
	struct pending_rpc_slist restore;
	struct pending_rpc **restore_plast;
	struct pending_rpc_slist kernel_rpcs;
	struct rpc_context ctx;
	struct exception_info error;
again:
	TRY {
		/* When this operation calls `task_serve()', the
		 * produced exception  will  be  handled  below! */
		return DO_INTERRUPT_OR_SYSTEM_CALL(state, sc_info);
		/* Notice that _everything_ below is _just_ there to handle exceptions! */
	} EXCEPT {
		struct exception_info *tls = error_info();
		if (!icpustate_isuser(state))
			RETHROW();
		if (tls->ei_code != ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
			memcpy(&error, &tls, sizeof(error));
			goto handle_rpc;
		}
		/* Fallthru to `E_OK' when `E_INTERRUPT_USER_RPC' was thrown! */
	}
	error.ei_code = ERROR_CODEOF(E_OK);
handle_rpc:
	ctx.rc_state = state;
	if (sc_info) {
		ctx.rc_context = RPC_REASONCTX_SYSCALL;
		ctx.rc_scinfo  = *sc_info;
	} else {
		ctx.rc_context = RPC_REASONCTX_INTERRUPT;
	}
	ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
	pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	restore_plast = SLIST_PFIRST(&restore);
	SLIST_INIT(&kernel_rpcs);
handle_pending:
	for (;;) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&pending);
		if (!rpc)
			break;
		SLIST_REMOVE_HEAD(&pending, pr_link);
		/* Here, kernel RPCs are executed _after_ user RPCs. */
		if (rpc->pr_flags & RPC_CONTEXT_KERN) {
			/* Check if this system call _must_ be handled during SYSRET. */
			if (rpc->pr_flags & RPC_SYNCMODE_F_SYSRET) {
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
				rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
			} else {
				/* NOTE: This also inverts the order back to first-scheduled-first-run */
				SLIST_INSERT_HEAD(&kernel_rpcs, rpc, pr_link);
			}
		} else if (rpc->pr_flags & _RPC_CONTEXT_INACTIVE) {
			/* RPC was disabled in an earlier pass. */
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
		} else {
			/* User-space RPC
			 * NOTE: These are executed in reverse  order, since each one  executed
			 *       will return to the context loaded by the one that was executed
			 *       before, meaning that the last one executed (iow: the first one
			 *       originally scheduled) will have the last word when it comes to
			 *       where execution should continue. */
			struct pending_user_rpc user_rpc_info;
			unsigned int user_rpc_reason;
			bool is_masked;
			TRY {
				is_masked = sigmask_ismasked_chk(_RPC_GETSIGNO(rpc->pr_flags));
			} EXCEPT {
				/* Prioritize errors. */
				struct exception_info *tls = error_info();
				if (error_priority(error.ei_code) < error_priority(tls->ei_code))
					memcpy(&error, tls, sizeof(error));
				pending_user_rpc_fini(&rpc->pr_user);
				pending_rpc_free(rpc);
				continue;
			}
			if (is_masked) {
				/* User-space RPCs are currently masked. */
make_inactive:
				*restore_plast = rpc;
				restore_plast  = &rpc->pr_link.sle_next;
				rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
				continue;
			}
			/* Figure out the reason we want to tell user-space.
			 * NOTE: Yes: this checks for  the original `sc_info'  (and
			 *       not for `ctx.rc_context == RPC_REASONCTX_SYSCALL') */
			user_rpc_reason = _RPC_REASONCTX_SYNC;
			if (sc_info != NULL) {
				if ((rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_CP) &&
				    !kernel_syscall_iscp(sc_info->rsi_sysno))
					goto make_inactive;
				/* If the system call  */
				if (ctx.rc_context == RPC_REASONCTX_SYSCALL)
					user_rpc_reason = _RPC_REASONCTX_SYSCALL;
			} else {
				if ((rpc->pr_flags & RPC_SYNCMODE_F_REQUIRE_SC))
					goto make_inactive;
			}
			user_rpc_info = rpc->pr_user;
			pending_rpc_free(rpc);
			/* Execute the program associated with this RPC */
			TRY {
				ctx.rc_state = EXECUTE_RPC_PROGRAM(&user_rpc_info, ctx.rc_state,
				                                   user_rpc_reason, &ctx.rc_scinfo);
			} EXCEPT {
				/* Prioritize errors. */
				struct exception_info *tls = error_info();
				if (error_priority(error.ei_code) < error_priority(tls->ei_code))
					memcpy(&error, tls, sizeof(error));
			}
			/* User-space RPCs are _always_ required (or at least expected) to
			 * restart system calls, meaning that */
			ctx.rc_context = RPC_REASONCTX_SYSRET;
			pending_user_rpc_fini(&user_rpc_info);
		}
	}

	/* Service POSIX signals. */
	TRY {
		ctx.rc_state = sigmask_check_s(ctx.rc_state,
		                               ctx.rc_context == RPC_REASONCTX_SYSCALL
		                               ? &ctx.rc_scinfo
		                               : NULL);
	} EXCEPT {
		/* Prioritize errors. */
		struct exception_info *tls = error_info();
		if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
			/* Load additional RPCs, but discard this new exception */
			ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
			pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
			goto handle_pending;
		}
		if (error_priority(error.ei_code) < error_priority(tls->ei_code))
			memcpy(&error, tls, sizeof(error));
	}

	/* Kernel RPCs are handled before user-space RPCs. This is needed so that
	 * user-space RPCs have higher priority  when it executing code before  a
	 * system call can be  performed in a situation  where the system all  is
	 * implemented by a thread sending an RPC to itself (as is the  suggested
	 * method of gaining access of one's own register state) */
	while (!SLIST_EMPTY(&kernel_rpcs)) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&kernel_rpcs);
		SLIST_REMOVE_HEAD(&kernel_rpcs, pr_link);
		assert(rpc->pr_flags & RPC_CONTEXT_KERN);
		assert(!(rpc->pr_flags & RPC_SYNCMODE_F_SYSRET));
		if (rpc->pr_flags & RPC_SYNCMODE_F_SYSRET) {
			*restore_plast = rpc;
			restore_plast  = &rpc->pr_link.sle_next;
			rpc->pr_flags |= _RPC_CONTEXT_INACTIVE;
		} else {
			prpc_exec_callback_t func;
			void *cookie;
			func   = rpc->pr_kern.k_func;
			cookie = rpc->pr_kern.k_cookie;
			pending_rpc_free(rpc);
			TRY {
				(*func)(&ctx, cookie);
			} EXCEPT {
				struct exception_info *tls = error_info();
				if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
					/* Load additional RPCs, but discard this new exception */
					ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
					pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
					goto handle_pending;
				}
				/* Prioritize errors. */
				if (error_priority(error.ei_code) < error_priority(tls->ei_code))
					memcpy(&error, tls, sizeof(error));
			}
			assert(ctx.rc_context == RPC_REASONCTX_SYSRET ||
			       ctx.rc_context == (sc_info ? RPC_REASONCTX_SYSCALL
			                                  : RPC_REASONCTX_INTERRUPT));
		}
	}

	/* Restore interrupts that could not be handled right now.
	 * In case we don't restart the interrupt/syscall, we must
	 * also handle SYSRET RPCs (as those must be invoked  just
	 * before  returning to user-space,  which is what's about
	 * to happen) */
	if (restore_plast != SLIST_PFIRST(&restore)) {
		*restore_plast = NULL; /* NULL-terminate list */
		if (error.ei_code != ERROR_CODEOF(E_OK) || ctx.rc_context == RPC_REASONCTX_SYSRET) {
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
				prpc_exec_callback_t func;
				void *cookie;
				rpc = SLIST_FIRST(&kernel_rpcs);
				SLIST_REMOVE_HEAD(&kernel_rpcs, pr_link);
				assert(rpc->pr_flags & RPC_SYNCMODE_F_SYSRET);
				func   = rpc->pr_kern.k_func;
				cookie = rpc->pr_kern.k_cookie;
				pending_rpc_free(rpc);
				TRY {
					(*func)(&ctx, cookie);
				} EXCEPT {
					struct exception_info *tls = error_info();
					if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
						/* Load additional RPCs, but discard this new exception */
						ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
						pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
						goto handle_pending;
					}
					/* Prioritize errors. */
					if (error_priority(error.ei_code) < error_priority(tls->ei_code))
						memcpy(&error, tls, sizeof(error));
				}
				assert(ctx.rc_context == RPC_REASONCTX_SYSRET ||
				       ctx.rc_context == (sc_info ? RPC_REASONCTX_SYSCALL
				                                  : RPC_REASONCTX_INTERRUPT));
			}
		}
		if (!SLIST_EMPTY(&restore)) {
			restore_pending_rpcs(SLIST_FIRST(&restore));
			ATOMIC_OR(PERTASK(this_task.t_flags), TASK_FRPC);
		}
	}

	/* Check if we must throw a new exception. */
	if (error.ei_code != ERROR_CODEOF(E_OK)) {
		/* This will unwind into user-space! */
		memcpy(error_info(), &error, sizeof(error));
		_Unwind_Resume(ctx.rc_state);
	}

	/* If the return context was  altered such that (logically  speaking),
	 * it points into async user-space  (iow: the interrupted system  call
	 * should not be restarted, or will be restored by user-space itself),
	 * then we mustn't try to restart  it ourselves, but rather load  back
	 * all RPCs that  are still pending  before resuming normal  execution
	 * in user-space. */
	if (ctx.rc_context == RPC_REASONCTX_SYSRET)
		return ctx.rc_state;

	/* Must restart a previously aborted interrupt/syscall with all of
	 * the RPCs that can't be handled in the context of said interrupt
	 * or  syscall marked as  INACTIVE (thus preventing `task_serve()'
	 * from trying to unwind for them)
	 *
	 * Once the interrupt/syscall completes as normal, all of them will
	 * be re-enabled once again. */
	if (SLIST_EMPTY(&restore)) {
		/* Nothing to restore. -  Just restart the system  call
		 * without any post-system-all-completion RPC handling. */
		state = ctx.rc_state;
		goto again;
	}

	/* The following call causes `handle_sysret_rpc()' to be
	 * invoked before we'll eventually return to user-space. */
	state = ctx.rc_state;
	assert(PREEMPTION_ENABLED());
	PREEMPTION_DISABLE();
	state = userexcept_sysret_inject_with_state(state);
	/* userexcept_sysret_inject(THIS_TASK); // Same as `userexcept_sysret_inject_with_state()' */
	PREEMPTION_ENABLE();

	/* Restart the interrupt/syscall */
	goto again;
}
```

<a name="handle_sysret_rpc"></a>
The referenced `handle_sysret_rpc()` function looks very similar and is implemented as follows:

```c
/* This function is called when any (even just inactive) RPCs are scheduled
 * just before returning to user-space. The given `state' points to the
 * target user-space location. */
struct icpustate *handle_sysret_rpc(struct icpustate *state) {
	struct pending_rpc_slist sysret_pending;
	struct pending_rpc_slist sysret_restore;
	struct pending_rpc **sysret_restore_plast;
	struct pending_rpc_slist sysret_kernel_rpcs;
	struct rpc_context sysret_ctx;
	struct exception_info sysret_error;
	/* Re-enable disabled RPCs and serve kernel RPCs with `RPC_REASONCTX_SYSRET' */
	sysret_ctx.rc_state      = state;
	sysret_ctx.rc_context    = RPC_REASONCTX_SYSRET;
	sysret_error.ei_code     = ERROR_CODEOF(E_OK);
	sysret_pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
	ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
	sysret_restore_plast = SLIST_PFIRST(&sysret_restore);
	SLIST_INIT(&sysret_kernel_rpcs);
sysret_handle_pending:
	for (;;) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&sysret_pending);
		if (!rpc)
			break;
		SLIST_REMOVE_HEAD(&sysret_pending, pr_link);
		if (rpc->pr_flags & RPC_CONTEXT_KERN) {
			/* Here, kernel RPCs are executed _after_ user RPCs.
			 * NOTE: This also inverts the order back to first-scheduled-first-run */
			SLIST_INSERT_HEAD(&sysret_kernel_rpcs, rpc, pr_link);
		} else {
			rpc->pr_flags &= ~_RPC_CONTEXT_INACTIVE;
			if (!(rpc->pr_flags & RPC_SYNCMODE_F_ALLOW_ASYNC)) {
				*sysret_restore_plast = rpc;
				sysret_restore_plast  = &rpc->pr_link.sle_next;
			} else {
				/* User-space RPC */
				struct pending_user_rpc user_rpc_info;
				unsigned int user_rpc_reason;
				bool is_masked;
				TRY {
					is_masked = sigmask_ismasked(_RPC_GETSIGNO(rpc->pr_flags));
				} EXCEPT {
					/* Prioritize errors. */
					struct exception_info *tls = error_info();
					if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
						memcpy(&sysret_error, tls, sizeof(sysret_error));
					pending_user_rpc_fini(&rpc->pr_user);
					pending_rpc_free(rpc);
					continue;
				}
				if (is_masked) {
					/* User-space RPCs are currently masked. */
sysret_make_inactive:
					*sysret_restore_plast = rpc;
					sysret_restore_plast  = &rpc->pr_link.sle_next;
					continue;
				}
				/* Figure out the reason we want to tell user-space.
				 * NOTE: Yes: this checks for  the original `sc_info'  (and
				 *       not for `ctx.rc_context == RPC_REASONCTX_SYSCALL') */
				user_rpc_info = rpc->pr_user;
				pending_rpc_free(rpc);
				/* Execute the program associated with this RPC */
				TRY {
					sysret_ctx.rc_state = EXECUTE_RPC_PROGRAM(&user_rpc_info, sysret_ctx.rc_state,
					                                          _RPC_REASONCTX_ASYNC, NULL);
				} EXCEPT {
					/* Prioritize errors. */
					struct exception_info *tls = error_info();
					if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
						memcpy(&sysret_error, tls, sizeof(sysret_error));
				}
				pending_user_rpc_fini(&user_rpc_info);
			}
		}
	}

	/* Service POSIX signals. */
	TRY {
		sysret_ctx.rc_state = sigmask_check_s(sysret_ctx.rc_state, NULL);
	} EXCEPT {
		/* Prioritize errors. */
		struct exception_info *tls = error_info();
		if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
			/* Load additional RPCs, but discard this new exception */
			ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
			sysret_pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
			goto sysret_handle_pending;
		}
		if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
			memcpy(&sysret_error, tls, sizeof(sysret_error));
	}

	/* Invoke kernel RPC handlers */
	while (!SLIST_EMPTY(&sysret_kernel_rpcs)) {
		struct pending_rpc *rpc;
		rpc = SLIST_FIRST(&sysret_kernel_rpcs);
		SLIST_REMOVE_HEAD(&sysret_kernel_rpcs, pr_link);
		TRY {
			prpc_exec_callback_t func;
			void *cookie;
			func   = rpc->pr_kern.k_func;
			cookie = rpc->pr_kern.k_cookie;
			pending_rpc_free(rpc);
			(*func)(&sysret_ctx, cookie);
			assert(sysret_ctx.rc_context == RPC_REASONCTX_SYSRET);
		} EXCEPT {
			struct exception_info *tls = error_info();
			if (tls->ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
				/* Load additional RPCs, but discard this new exception */
				ATOMIC_AND(PERTASK(this_task.t_flags), ~TASK_FRPC);
				sysret_pending.slh_first = SLIST_ATOMIC_CLEAR(&PERTASK(this_rpcs));
				goto sysret_handle_pending;
			}
			/* Prioritize errors. */
			if (error_priority(sysret_error.ei_code) < error_priority(tls->ei_code))
				memcpy(&sysret_error, tls, sizeof(sysret_error));
		}
	}

	/* If there are any RPCs that could not be handled, restore them now! */
	if (sysret_restore_plast != SLIST_PFIRST(&sysret_restore)) {
		*sysret_restore_plast = NULL;
		restore_pending_rpcs(SLIST_FIRST(&sysret_restore));
		ATOMIC_OR(PERTASK(this_task.t_flags), TASK_FRPC);
	}

	/* Check if we must throw a new exception. */
	if (sysret_error.ei_code != ERROR_CODEOF(E_OK)) {
		memcpy(error_info(), &sysret_error, sizeof(sysret_error));
		/* This will unwind into user-space! */
		_Unwind_Resume(ctx.rc_state);
	}

	/* Resume normal execution. */
	state = sysret_ctx.rc_state;
	return state;
}
```




### High-level scheduling of RPCs (in kernel-space)

RPCs that are packaged into a `struct pending_rpc` can be scheduled for arbitrary threads by making use of the function `task_rpc_schedule()`, which is implemented as follows:

```c
/* Schedule the given `rpc' for execution on `thread'.
 * NOTE: Be mindful of the scenario  where `thread == THIS_TASK', in which  case
 *       this function will return like normal, and the RPC will only be noticed
 *       the next time you make a call to `task_serve()'!
 * @return: true:  Success. (Even if the thread terminates before the RPC can be served
 *                 normally, it will still  be served as `RPC_REASONCTX_SHUTDOWN'  when
 *                 true has been returned here)
 * @return: false: The target thread has already terminated. */
bool NOTHROW(task_rpc_schedule)(struct task *__restrict thread,
                                /*inherit(on_success)*/ struct pending_rpc *__restrict rpc) {
	struct pending_rpc_slist *list;
	struct pending_rpc *head;

	/* Insert into `thread's pending RPC list. */
	list = &FORTASK(thread, this_rpcs);
	do {
		head = ATOMIC_READ(list->slh_first);
		if unlikely(head == THIS_RPCS_TERMINATED)
			return false; /* Already terminated */
		rpc->pr_link.sle_next = head;
		COMPILER_WRITE_BARRIER();
	} while (!ATOMIC_CMPXCH_WEAK(list->slh_first, head, rpc));

	/* Set the thread's `TASK_FRPC' flag to indicate that it's got work to do */
	ATOMIC_OR(thread->t_flags, TASK_FRPC);

	/* Deal  with the case where `thread' is currently running in user-space,
	 * which requires us to temporarily move its execution into kernel-space,
	 * such that it executes `handle_sysret_rpc()'  the next time it  returns
	 * back to user-space.
	 *
	 * This  is normally done  by `userexcept_sysret_inject()', however that
	 * function only  works correctly  when the  thread is  being hosted  by
	 * the same CPU as  the calling thread. But  there's also a wrapper  for
	 * that low-level function `userexcept_sysret_inject_safe()', which does
	 * the same thing, but also works then the thread hosted by another CPU. */
	userexcept_sysret_inject_safe(thread);

	return true;
}
```









#### Misc. helper functions

These functions are referenced by above (near-pseudo) code:

```c
void NOTHROW(restore_pending_rpcs)(struct pending_rpc *restore) {
	if (restore) {
		struct pending_rpc_slist *list;
		struct pending_rpc *last;
		list = &PERTASK(this_rpcs);
again:
		last = ATOMIC_READ(list->slh_first);
		if (!last) {
			if (!ATOMIC_CMPXCH_WEAK(list->slh_first, NULL, restore))
				goto again;
		} else {
			while (SLIST_NEXT(last, pr_link))
				last = SLIST_NEXT(last, pr_link);
			last->pr_link.sle_next = restore;
		}
	}
}
```

