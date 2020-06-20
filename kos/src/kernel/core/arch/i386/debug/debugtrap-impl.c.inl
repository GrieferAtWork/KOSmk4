/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "debugtrap.c"
#endif /* __INTELLISENSE__ */

#ifndef DEFINE_DEBUGTRAP_WIDTH
#define DEFINE_DEBUGTRAP_WIDTH __SIZEOF_POINTER__
#endif /* !DEFINE_DEBUGTRAP_WIDTH */

DECL_BEGIN

#if DEFINE_DEBUGTRAP_WIDTH == 4
#define IFELSE3264(i32, i64) i32
#else /* DEFINE_DEBUGTRAP_WIDTH == 4 */
#define IFELSE3264(i32, i64) i64
#endif /* DEFINE_DEBUGTRAP_WIDTH != 4 */


#if DEFINE_DEBUGTRAP_WIDTH == 4
#define DEBUGTRAP_REASON64_STRUCT  struct debugtrap_reason32
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_debugtrap32_impl(struct icpustate *__restrict return_state,
                     USER UNCHECKED struct ucpustate32 const *ustate,
                     USER UNCHECKED struct debugtrap_reason32 const *ureason)
#else /* DEFINE_DEBUGTRAP_WIDTH == 4 */
#define DEBUGTRAP_REASON64_STRUCT  struct debugtrap_reason64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_debugtrap64_impl(struct icpustate *__restrict return_state,
                     USER UNCHECKED struct ucpustate64 const *ustate,
                     USER UNCHECKED struct debugtrap_reason64 const *ureason)
#endif /* DEFINE_DEBUGTRAP_WIDTH != 4 */
{
	struct debugtrap_reason reason;
	if (!kernel_debugtrap_enabled()) {
		/* Debug traps are disabled. */
		gpregs_setpax(&return_state->ics_gpregs, (uintptr_t)-ENOENT);
		return return_state;
	}
	if (ureason) {
		validate_readable(ureason, sizeof(*ureason));
		COMPILER_READ_BARRIER();
		reason.dtr_signo  = ureason->dtr_signo;
		reason.dtr_reason = ureason->dtr_reason;
		reason.dtr_intarg = ureason->dtr_intarg;
		COMPILER_READ_BARRIER();
		if (reason.dtr_reason > DEBUGTRAP_REASON_MAX)
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_DEBUG_REASON,
			      reason.dtr_reason);
		switch (reason.dtr_reason) {

		case DEBUGTRAP_REASON_MESSAGE:
			/* Debug message event. */
			validate_readable(reason.dtr_strarg, reason.dtr_signo);
			return_state = IFELSE3264(sys_do_debugtrap32_impl(return_state, ustate, &reason),
			                          sys_do_debugtrap64_impl(return_state, ustate, &reason));
			((DEBUGTRAP_REASON64_STRUCT *)ureason)->dtr_signo = reason.dtr_signo;
			goto done;

		case DEBUGTRAP_REASON_FORK:
		case DEBUGTRAP_REASON_VFORK:
		case DEBUGTRAP_REASON_TEXITED:
		case DEBUGTRAP_REASON_PEXITED: {
			REF struct task *thread;
			cred_require_debugtrap();
			thread = pidns_lookup_task(THIS_PIDNS, (upid_t)reason.dtr_intarg);
			FINALLY_DECREF_UNLIKELY(thread);
			reason.dtr_ptrarg = thread;
			return_state = IFELSE3264(sys_do_debugtrap32_impl(return_state, ustate, &reason),
			                          sys_do_debugtrap64_impl(return_state, ustate, &reason));
			goto done;
		}	break;

		case DEBUGTRAP_REASON_EXEC: {
			char *namebuf;
			size_t namelen;
			enum { MAXLEN = 4096 };
			validate_readable(reason.dtr_strarg, 1);
			namelen = strlen(reason.dtr_strarg);
			if (namelen > MAXLEN)
				THROW(E_BUFFER_TOO_SMALL, MAXLEN, namelen);
			namebuf = (char *)malloca((namelen + 1) * sizeof(char));
			TRY {
				memcpy(namebuf, reason.dtr_strarg, namelen, sizeof(char));
				namebuf[namelen]  = '\0';
				reason.dtr_strarg = namebuf;
				return_state = IFELSE3264(sys_do_debugtrap32_impl(return_state, ustate, &reason),
				                          sys_do_debugtrap64_impl(return_state, ustate, &reason));
			} EXCEPT {
				freea(namebuf);
				RETHROW();
			}
			freea(namebuf);
			goto done;
		}	break;

		case DEBUGTRAP_REASON_VFORKDONE:
		case DEBUGTRAP_REASON_SC_ENTRY:
		case DEBUGTRAP_REASON_SC_EXIT:
		case DEBUGTRAP_REASON_CLONE:
		case DEBUGTRAP_REASON_SWBREAK:
		case DEBUGTRAP_REASON_HWBREAK:
			cred_require_debugtrap();
			reason.dtr_intarg = 0;
			break;

		default:
			reason.dtr_intarg = 0;
			break;
		}
		if (reason.dtr_reason != DEBUGTRAP_REASON_TEXITED &&
		    reason.dtr_reason != DEBUGTRAP_REASON_PEXITED) {
			/* Verify a valid signal number.
			 * NOTE: The (T|P)EXITED reason use the SIGNO field as the exit status. */
			if (reason.dtr_signo <= 0 || reason.dtr_signo >= NSIG)
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO,
				      reason.dtr_signo);
		}
	} else {
		reason.dtr_signo  = SIGTRAP;
		reason.dtr_reason = DEBUGTRAP_REASON_NONE;
		reason.dtr_intarg = 0;
	}
	return_state = IFELSE3264(sys_do_debugtrap32_impl(return_state, ustate, &reason),
	                          sys_do_debugtrap64_impl(return_state, ustate, &reason));
done:
	return return_state;
}

#undef IFELSE3264
#undef DEBUGTRAP_REASON64_STRUCT
#undef DEFINE_DEBUGTRAP_WIDTH

DECL_END
