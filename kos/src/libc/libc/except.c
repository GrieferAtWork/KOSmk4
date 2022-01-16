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
#ifndef GUARD_LIBC_LIBC_EXCEPT_C
#define GUARD_LIBC_LIBC_EXCEPT_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <kos/debugtrap.h>
#include <kos/except-handler.h>
#include <kos/except.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/malloc.h>
#include <kos/rpc.h>
#include <kos/syscalls.h>
#include <sys/syslog.h>

#include <assert.h>
#include <malloc.h>
#include <sched.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

#include <libunwind/dwarf.h>
#include <libunwind/eh_frame.h>
#include <libunwind/except.h>
#include <libunwind/unwind.h>

#include "dl.h"
#include "except.h"
#include "sigreturn.h"
#include "tls.h"

DECL_BEGIN

STATIC_ASSERT(offsetof(struct exception_info, ei_state) == OFFSET_EXCEPTION_INFO_STATE);
#if EXCEPT_BACKTRACE_SIZE != 0
STATIC_ASSERT(offsetof(struct exception_info, ei_trace) == OFFSET_EXCEPTION_INFO_TRACE);
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
STATIC_ASSERT(offsetof(struct exception_info, ei_flags) == OFFSET_EXCEPTION_INFO_FLAGS);
STATIC_ASSERT(offsetof(struct exception_info, ei_code)  == OFFSET_EXCEPTION_INFO_CODE);
STATIC_ASSERT(offsetof(struct exception_info, ei_data) == OFFSET_EXCEPTION_INFO_DATA);
STATIC_ASSERT(offsetof(struct exception_info, ei_data.e_args.e_pointers) == OFFSET_EXCEPTION_INFO_POINTERS);


INTERN SECTION_EXCEPT_TEXT WUNUSED ATTR_CONST ATTR_RETNONNULL
struct exception_info *NOTHROW_NCX(LIBCCALL libc_error_info)(void) {
	return &current.pt_except;
}
INTERN SECTION_EXCEPT_TEXT WUNUSED ATTR_CONST ATTR_RETNONNULL
struct exception_data *NOTHROW_NCX(LIBCCALL libc_error_data)(void) {
	return &current.pt_except.ei_data;
}
INTERN SECTION_EXCEPT_TEXT WUNUSED ATTR_CONST ATTR_RETNONNULL
error_register_state_t *NOTHROW_NCX(LIBCCALL libc_error_register_state)(void) {
	return &current.pt_except.ei_state;
}
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED error_code_t
NOTHROW_NCX(LIBCCALL libc_error_code)(void) {
	return current.pt_except.ei_code;
}
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED bool
NOTHROW_NCX(LIBCCALL libc_error_active)(void) {
	return current.pt_except.ei_code != E_OK;
}
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED error_class_t
NOTHROW_NCX(LIBCCALL libc_error_class)(void) {
	return ERROR_CLASS(current.pt_except.ei_code);
}
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED error_subclass_t
NOTHROW_NCX(LIBCCALL libc_error_subclass)(void) {
	return ERROR_SUBCLASS(current.pt_except.ei_code);
}

#undef error_info
#undef error_data
#undef error_register_state
#undef error_code
#undef error_active
#undef error_class
#undef error_subclass

DEFINE_PUBLIC_ALIAS(error_info, libc_error_info);
DEFINE_PUBLIC_ALIAS(error_data, libc_error_data);
DEFINE_PUBLIC_ALIAS(error_register_state, libc_error_register_state);
DEFINE_PUBLIC_ALIAS(error_code, libc_error_code);
DEFINE_PUBLIC_ALIAS(error_active, libc_error_active);
DEFINE_PUBLIC_ALIAS(error_class, libc_error_class);
DEFINE_PUBLIC_ALIAS(error_subclass, libc_error_subclass);

/* Exception support. */

/* Dynamically loaded dependencies to libunwind.so */
INTERN SECTION_EXCEPT_BSS void /*                          */ *pdyn_libunwind                          = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_FDE_FIND /*              */ pdyn_unwind_fde_find                    = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_GETREG_ERROR_REGISTER_STATE pdyn_unwind_getreg_error_register_state = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_SETREG_ERROR_REGISTER_STATE pdyn_unwind_setreg_error_register_state = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_FDE_EXEC /*              */ pdyn_unwind_fde_exec                    = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_CFA_APPLY /*             */ pdyn_unwind_cfa_apply                   = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_FDE_EXEC_CFA /*          */ pdyn_unwind_fde_exec_cfa                = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_FDE_CALCULATE_CFA /*     */ pdyn_unwind_fde_calculate_cfa           = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_FDE_LANDING_EXEC /*      */ pdyn_unwind_fde_landing_exec            = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_CFA_LANDING_APPLY /*     */ pdyn_unwind_cfa_landing_apply           = NULL;
PRIVATE SECTION_EXCEPT_BSS PDWARF_DECODE_POINTER /*         */ pdyn_dwarf_decode_pointer               = NULL;
PRIVATE SECTION_EXCEPT_BSS PDWARF_DECODE_ULEB128 /*         */ pdyn_dwarf_decode_uleb128               = NULL;
#ifndef CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS
PRIVATE SECTION_EXCEPT_BSS PUNWIND_FDE_SIGFRAME_EXEC /*     */ pdyn_unwind_fde_sigframe_exec  = NULL;
PRIVATE SECTION_EXCEPT_BSS PUNWIND_CFA_SIGFRAME_APPLY /*    */ pdyn_unwind_cfa_sigframe_apply = NULL;
#endif /* !CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */
#define ENSURE_LIBUNWIND_LOADED() \
	(ATOMIC_READ(pdyn_libunwind) != NULL || (initialize_libunwind(), 0))

PRIVATE SECTION_EXCEPT_STRING char const name_libunwind_so[] = LIBUNWIND_LIBRARY_NAME;
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_fde_find[]                    = "unwind_fde_find";
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_getreg_error_register_state[] = UNWIND_GETREG_ERROR_REGISTER_STATE_NAME;
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_setreg_error_register_state[] = UNWIND_SETREG_ERROR_REGISTER_STATE_NAME;
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_fde_exec[]                    = "unwind_fde_exec";
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_cfa_apply[]                   = "unwind_cfa_apply";
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_fde_exec_cfa[]                = "unwind_fde_exec_cfa";
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_fde_calculate_cfa[]           = "unwind_fde_calculate_cfa";
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_fde_landing_exec[]            = "unwind_fde_landing_exec";
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_cfa_landing_apply[]           = "unwind_cfa_landing_apply";
PRIVATE SECTION_EXCEPT_STRING char const name_dwarf_decode_pointer[]               = "dwarf_decode_pointer";
PRIVATE SECTION_EXCEPT_STRING char const name_dwarf_decode_uleb128[]               = "dwarf_decode_uleb128";
#ifndef CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_fde_sigframe_exec[]  = "unwind_fde_sigframe_exec";
PRIVATE SECTION_EXCEPT_STRING char const name_unwind_cfa_sigframe_apply[] = "unwind_cfa_sigframe_apply";
#endif /* !CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */

PRIVATE SECTION_EXCEPT_TEXT ATTR_NORETURN
void LIBCCALL libunwind_init_failed(void) {
	PRIVATE SECTION_EXCEPT_STRING char const
	message_libunwind_init_failed[] = "Failed to initialize libunwind: %s\n";
	syslog(LOG_ERR, message_libunwind_init_failed, dlerror());
	exit(EXIT_FAILURE);
}

/* Initialize libunwind bindings. */
INTERN SECTION_EXCEPT_TEXT ATTR_NOINLINE
void LIBCCALL initialize_libunwind(void) {
	void *handle;
	handle = dlopen(name_libunwind_so, RTLD_LOCAL);
	if unlikely(!handle)
		goto err_init_failed;
	/* Dynamically bind functions. */
#define BIND(func, name)                                         \
	if unlikely((*(void **)&func = dlsym(handle, name)) == NULL) \
		goto err_init_failed
	BIND(pdyn_unwind_fde_find, name_unwind_fde_find);
	BIND(pdyn_unwind_getreg_error_register_state, name_unwind_getreg_error_register_state);
	BIND(pdyn_unwind_setreg_error_register_state, name_unwind_setreg_error_register_state);
	BIND(pdyn_unwind_fde_exec, name_unwind_fde_exec);
	BIND(pdyn_unwind_cfa_apply, name_unwind_cfa_apply);
	BIND(pdyn_unwind_fde_exec_cfa, name_unwind_fde_exec_cfa);
	BIND(pdyn_unwind_fde_calculate_cfa, name_unwind_fde_calculate_cfa);
	BIND(pdyn_unwind_fde_landing_exec, name_unwind_fde_landing_exec);
	BIND(pdyn_unwind_cfa_landing_apply, name_unwind_cfa_landing_apply);
	BIND(pdyn_dwarf_decode_pointer, name_dwarf_decode_pointer);
	BIND(pdyn_dwarf_decode_uleb128, name_dwarf_decode_uleb128);
#ifndef CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS
	/* We can substitute the sigframe variants with the regular ones. */
	*(void **)&pdyn_unwind_fde_sigframe_exec  = dlsym(handle, name_unwind_fde_sigframe_exec);
	*(void **)&pdyn_unwind_cfa_sigframe_apply = dlsym(handle, name_unwind_cfa_sigframe_apply);
	if unlikely(!pdyn_unwind_fde_sigframe_exec || !pdyn_unwind_cfa_sigframe_apply) {
		STATIC_ASSERT_MSG(sizeof(unwind_cfa_sigframe_state_t) >= sizeof(unwind_cfa_state_t),
		                  "This is a requirement for this substitution (see usage of these functions)");
		pdyn_unwind_fde_sigframe_exec  = (PUNWIND_FDE_SIGFRAME_EXEC)pdyn_unwind_fde_exec;
		pdyn_unwind_cfa_sigframe_apply = (PUNWIND_CFA_SIGFRAME_APPLY)pdyn_unwind_cfa_apply;
	}
#endif /* !CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */
#undef BIND
	COMPILER_WRITE_BARRIER();
	pdyn_libunwind = handle;
	COMPILER_WRITE_BARRIER();
	return;
err_init_failed:
	libunwind_init_failed();
}


#define unwind_fde_find                    (*pdyn_unwind_fde_find)
#define unwind_getreg_error_register_state (*pdyn_unwind_getreg_error_register_state)
#define unwind_setreg_error_register_state (*pdyn_unwind_setreg_error_register_state)
#define unwind_fde_exec                    (*pdyn_unwind_fde_exec)
#define unwind_cfa_apply                   (*pdyn_unwind_cfa_apply)
#define unwind_fde_exec_cfa                (*pdyn_unwind_fde_exec_cfa)
#define unwind_fde_calculate_cfa           (*pdyn_unwind_fde_calculate_cfa)
#define unwind_fde_landing_exec            (*pdyn_unwind_fde_landing_exec)
#define unwind_cfa_landing_apply           (*pdyn_unwind_cfa_landing_apply)
#define unwind_fde_sigframe_exec           (*pdyn_unwind_fde_sigframe_exec)
#define unwind_cfa_sigframe_apply          (*pdyn_unwind_cfa_sigframe_apply)
#define dwarf_decode_pointer               (*pdyn_dwarf_decode_pointer)
#define dwarf_decode_uleb128               (*pdyn_dwarf_decode_uleb128)

PRIVATE SECTION_EXCEPT_TEXT void LIBCCALL
kos_unwind_exception_cleanup(_Unwind_Reason_Code UNUSED(reason),
                             struct _Unwind_Exception *UNUSED(exc)) {
	/* Clear the active error code */
	current.pt_except.ei_code = ERROR_CODEOF(E_OK);
}

PRIVATE SECTION_EXCEPT_DATA struct _Unwind_Exception kos_unwind_exception = {
	.exception_class   = _UEC_KERNKOS,
	.exception_cleanup = NULL, /* Filled in lazily */
};

PRIVATE ATTR_RETNONNULL SECTION_EXCEPT_TEXT WUNUSED struct _Unwind_Exception *LIBCCALL
libc_get_kos_unwind_exception(void) {
	if (!kos_unwind_exception.exception_cleanup)
		kos_unwind_exception.exception_cleanup = &kos_unwind_exception_cleanup;
	return &kos_unwind_exception;
}




/* NOTE: These functions _have_ to be exported weakly!
 *       Otherwise, they might accidentally override the same functions
 *       exported from `libstdc++.so'
 *       The idea in  exporting these  from libc.so  as well  is that  libc.so
 *       should provide a minimal, self-contained implementation of everything
 *       that is required to get the KOS-specific exception handling  provided
 *       by the <kos/except.h> header working.
 *       Additionally, then  libstdc++.so is  loaded,  we must  remain  compatible
 *       with its API, in that kos exceptions should show up as foreign exceptions
 *       when interfaced with the standard c++ API (which they do) */
DEFINE_PUBLIC_WEAK_ALIAS(__gxx_personality_v0, libc_gxx_personality_v0);
DEFINE_PUBLIC_WEAK_ALIAS(__gcc_personality_v0, libc_gxx_personality_v0);


INTERN SECTION_EXCEPT_TEXT _Unwind_Reason_Code LIBCCALL
libc_gxx_personality_kernexcept(struct _Unwind_Context *__restrict context, bool phase_2) {
	u8 temp, callsite_encoding;
	byte_t const *landingpad, *pc;
	byte_t const *reader, *callsite_end;
	size_t callsite_size;
	ENSURE_LIBUNWIND_LOADED();

	reader     = (byte_t const *)context->uc_fde.f_lsdaaddr;
	landingpad = (byte_t const *)context->uc_fde.f_pcstart;
	pc         = (byte_t const *)__ERROR_REGISTER_STATE_TYPE_RDPC(*context->uc_state);

	/* HINT: `reader' points to a `struct gcc_lsda' */
	temp = *reader++; /* gl_landing_enc */
	if (temp != DW_EH_PE_omit) {
		/* gl_landing_pad */
		landingpad = dwarf_decode_pointer((byte_t const **)&reader, temp, sizeof(void *),
		                                  &context->uc_fde.f_bases);
	}
	temp = *reader++; /* gl_typetab_enc */
	if (temp != DW_EH_PE_omit) {
		dwarf_decode_uleb128((byte_t const **)&reader); /* gl_typetab_off */
	}
	callsite_encoding = *reader++; /* gl_callsite_enc */
	callsite_size     = dwarf_decode_uleb128((byte_t const **)&reader);
	callsite_end      = reader + callsite_size;
	while (reader < callsite_end) {
		uintptr_t start, size, handler, action;
		byte_t const *startpc, *endpc;
		start   = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &context->uc_fde.f_bases); /* gcs_start */
		size    = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &context->uc_fde.f_bases); /* gcs_size */
		handler = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &context->uc_fde.f_bases); /* gcs_handler */
		action  = (uintptr_t)dwarf_decode_pointer((byte_t const **)&reader, callsite_encoding, sizeof(void *), &context->uc_fde.f_bases); /* gcs_action */
		startpc = landingpad + start;
		endpc   = startpc + size;

#if 1 /* Compare  pointers  like  this,  as  `pc'  is  the  _RETURN_  address\
       * (i.e. the address after the piece of code that caused the exception) */
		if (pc > startpc && pc <= endpc)
#else
		if (pc >= startpc && pc < endpc)
#endif
		{
			if (handler == 0)
				return _URC_CONTINUE_UNWIND; /* No handler -> exception should be propagated. */
			if (!phase_2)
				return _URC_HANDLER_FOUND;
			/* Jump to the associated handler */
			__ERROR_REGISTER_STATE_TYPE_WRPC(*context->uc_state, landingpad + handler);
			if (action != 0) {
				__ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(*context->uc_state,
				                                                (uintptr_t)libc_get_kos_unwind_exception());
			}
			return _URC_INSTALL_CONTEXT;
		}
	}
	/* Default behavior: abort exception handling (this function was marked as NOTHROW) */
	return _URC_END_OF_STACK;
}

INTERN SECTION_EXCEPT_TEXT _Unwind_Reason_Code LIBCCALL
libc_gxx_personality_v0(int version /* = 1 */,
                        _Unwind_Action actions,
                        _Unwind_Exception_Class exception_class,
                        struct _Unwind_Exception *ue_header,
                        struct _Unwind_Context *context) {
	if unlikely(version != 1)
		return _URC_FATAL_PHASE1_ERROR;
	if likely(exception_class == _UEC_KERNKOS)
		return libc_gxx_personality_kernexcept(context, (actions & _UA_FORCE_UNWIND) != 0);
	/* This implementation only support KOS exceptions.
	 * When linking against libstdc++.so, this function gets overridden by its implementation. */
	(void)actions;
	(void)exception_class;
	(void)ue_header;
	(void)context;
	return _URC_FATAL_PHASE1_ERROR;
}


PRIVATE SECTION_EXCEPT_TEXT unsigned int __ERROR_UNWIND_CC
unwind_fde(unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
           error_register_state_t *__restrict new_state,
           error_register_state_t const *__restrict old_state,
           void const *pc) {
	unsigned int unwind_error;
	/* Execute the CFA program to generate the row of rules for our current source location. */
#ifndef CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS
	if (fde->f_sigframe) {
		/* Special optimization when signal frames are available. */
		unwind_cfa_sigframe_state_t cfa;
		unwind_error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(unwind_error != UNWIND_SUCCESS)
			goto done;
		/* Apply the rules to our register state to unwind the stack to that function's call-site. */
		unwind_error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                         &unwind_getreg_error_register_state, old_state,
		                                         &unwind_setreg_error_register_state, new_state);
	} else
#endif /* !CFI_UNWIND_NO_SIGFRAME_COMMON_UNCOMMON_REGISTERS */
	{
		unwind_cfa_state_t cfa;
		unwind_error = unwind_fde_exec(fde, &cfa, pc);
		if unlikely(unwind_error != UNWIND_SUCCESS)
			goto done;
		/* Apply the rules to our register state to unwind the stack to that function's call-site. */
		unwind_error = unwind_cfa_apply(&cfa, fde, pc,
		                                &unwind_getreg_error_register_state, old_state,
		                                &unwind_setreg_error_register_state, new_state);
	}
	if (unwind_error == UNWIND_INVALID_REGISTER) {
		/* TODO: Try again, but this time include the current FPU context. */
	}
done:
	return unwind_error;
}


PRIVATE SECTION_EXCEPT_TEXT unsigned int __FCALL
unwind_landingpad(unwind_fde_t *__restrict fde, /* Only non-const for lazy initialized fields! */
                  error_register_state_t *__restrict state,
                  void const *except_pc) {
	void const *landing_pad_pc;
	unwind_cfa_landing_state_t cfa;
	error_register_state_t new_state;
	unsigned int unwind_error;
	landing_pad_pc = __ERROR_REGISTER_STATE_TYPE_RDPC(*state);
	unwind_error   = unwind_fde_landing_exec(fde, &cfa, except_pc, landing_pad_pc);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto done;
	/* Apply landing-pad transformations. */
	memcpy(&new_state, state, sizeof(new_state));
	unwind_error = unwind_cfa_landing_apply(&cfa, fde, except_pc,
	                                        &unwind_getreg_error_register_state, state,
	                                        &unwind_setreg_error_register_state, &new_state);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto done;
	/* Write-back the new register state. */
	memcpy(state, &new_state, sizeof(new_state));
	return UNWIND_SUCCESS;
done:
	if (unwind_error == UNWIND_NO_FRAME) {
		/* Directly jump to the landing pad. */
		__ERROR_REGISTER_STATE_TYPE_WRPC(*state, (uintptr_t)landing_pad_pc);
		unwind_error = UNWIND_SUCCESS;
	}
	return unwind_error;
}





PRIVATE SECTION_EXCEPT_TEXT error_register_state_t *LIBCCALL
handle_special_exception(error_register_state_t *__restrict state,
                         struct exception_data *__restrict error) {
	(void)state;
	switch (error->e_code) {

	case ERROR_CODEOF(E_EXIT_THREAD):
		exit_thread((int)error->e_args.e_exit_thread.et_exit_code);
		break;

	case ERROR_CODEOF(E_EXIT_PROCESS):
		exit((int)error->e_args.e_exit_process.ep_exit_code);
		break;

	default:
		break;
	}
	/* No special handling required. */
	return NULL;
}

#define error_register_state_to_ucpustate kcpustate_to_ucpustate
#define error_register_state_getpc        kcpustate_getpc
#define error_register_state_setpc        kcpustate_setpc

PRIVATE SECTION_EXCEPT_TEXT ATTR_NOINLINE void LIBCCALL
trigger_debugtrap(struct ucpustate *__restrict state,
                  struct exception_data *__restrict error) {
	siginfo_t si;
	struct debugtrap_reason r;
	if (!error_as_signal(error, &si))
		si.si_signo = SIGABRT;
	r.dtr_signo  = si.si_signo;
	r.dtr_reason = DEBUGTRAP_REASON_NONE;
	sys_debugtrap(state, &r);
}

PRIVATE SECTION_EXCEPT_TEXT ATTR_NOINLINE ATTR_NORETURN NONNULL((1, 2)) void LIBCCALL
trigger_coredump(error_register_state_t *curr_state,
                 error_register_state_t *orig_state,
                 struct exception_data *exc,
                 void const **unwind_tracevector,
                 unsigned int unwind_tracelength,
                 unsigned int unwind_error) {
	struct ucpustate curr_ust, orig_ust;
	error_register_state_to_ucpustate(curr_state, &curr_ust);
	error_register_state_to_ucpustate(orig_state, &orig_ust);

	/* Try  to trigger a  coredump including all  of the information needed
	 * to re-construct (up to `EXCEPT_BACKTRACE_SIZE' frames) of the unwind
	 * path, as well as the remainder of the stack that didn't get unwound. */
	sys_coredump(&curr_ust,
	             &orig_ust,
	             unwind_tracevector,
	             unwind_tracelength,
	             container_of(exc, union coredump_info, ci_except),
	             unwind_error);
	/* There really shouldn't be a reason to get here, but just in case... */

	/* Shouldn't get here, but if something went wrong,
	 * also   try  to  trigger  a  legacy  debug  trap. */
	error_register_state_to_ucpustate(curr_state, &curr_ust);
	trigger_debugtrap(&curr_ust, exc);

	/* As a fallback: just abort execution. */
	abort();
}


PRIVATE SECTION_EXCEPT_TEXT ATTR_NOINLINE NONNULL((1, 2)) void LIBCCALL
try_raise_signal_from_exception(error_register_state_t *__restrict state,
                                struct exception_data *__restrict error) {
	siginfo_t si;
	if (error_as_signal(error, &si)) {
		/* raise a signal `si' at `*state' */
		struct ucpustate uc;
		struct rpc_syscall_info sc_info;
		error_register_state_to_ucpustate(state, &uc);

		/* Use sigreturn(2) to execute a call to `rt_tgsigqueueinfo(2)' from `uc' */
		bzero(&sc_info, sizeof(sc_info));
		sc_info.rsi_sysno = SYS_rt_tgsigqueueinfo;
		sc_info.rsi_flags = RPC_SYSCALL_INFO_METHOD_OTHER | RPC_SYSCALL_INFO_FEXCEPT |
		                    RPC_SYSCALL_INFO_FREGVALID(1) | RPC_SYSCALL_INFO_FREGVALID(2) |
		                    RPC_SYSCALL_INFO_FREGVALID(3) | RPC_SYSCALL_INFO_FREGVALID(4);
		sc_info.rsi_regs[0] = (syscall_ulong_t)getpid();
		sc_info.rsi_regs[1] = (syscall_ulong_t)gettid();
		sc_info.rsi_regs[2] = (syscall_ulong_t)si.si_signo;
		sc_info.rsi_regs[3] = (syscall_ulong_t)&si;
		libc_sys_sigreturn(&uc, NULL, NULL, &sc_info);
		__builtin_unreachable();
	}
}



DEFINE_PUBLIC_ALIAS(error_unwind, libc_error_unwind);
INTERN SECTION_EXCEPT_TEXT WUNUSED error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_error_unwind)(error_register_state_t *__restrict state) {
	unsigned int unwind_error;
	struct _Unwind_Context context;
	error_register_state_t orig_state;
	error_register_state_t oldstate;
	void const *pc;
#if EXCEPT_BACKTRACE_SIZE != 0
	unsigned int orig_tracecount;
	for (orig_tracecount = 0; orig_tracecount < EXCEPT_BACKTRACE_SIZE - 1; ++orig_tracecount) {
		if (!current.pt_except.ei_trace[orig_tracecount])
			break;
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */

	/* Make sure that libunwind has been loaded. */
	ENSURE_LIBUNWIND_LOADED();
	memcpy(&orig_state, state, sizeof(*state));
search_fde:
	/* unwind `state' until the nearest exception handler,  or until the end of the  stack.
	 * If the later happens, then we check for an exit-thread exception, but will terminate
	 * the process due to an unhandled exception if something else went wrong.
	 * NOTE: PC-1 because the state we're being given has its PC pointer
	 *       set   to  be  directed   after  the  faulting  instruction. */
	memcpy(&oldstate, state, sizeof(*state));
	pc           = __ERROR_REGISTER_STATE_TYPE_RDPC(oldstate) - 1;
	unwind_error = unwind_fde_find(pc, &context.uc_fde);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto err;
	if (context.uc_fde.f_persofun) {
		/* Invoke the personality function */
		_Unwind_Reason_Code reason;
		context.uc_state = state;
		if ((_Unwind_Personality_Fn)context.uc_fde.f_persofun == &libc_gxx_personality_v0) {
			reason = libc_gxx_personality_kernexcept(&context, true);
		} else {
			reason = (*(_Unwind_Personality_Fn)context.uc_fde.f_persofun)(1,
			                                                              _UA_CLEANUP_PHASE | _UA_FORCE_UNWIND,
			                                                              _UEC_KERNKOS,
			                                                              libc_get_kos_unwind_exception(),
			                                                              &context);
		}
		if (reason == _URC_INSTALL_CONTEXT) {
			/* Unwind to the landing pad. */
			unwind_error = unwind_landingpad(&context.uc_fde, state, pc);
			if unlikely(unwind_error != UNWIND_SUCCESS)
				goto err;
			return state;
		}
		if unlikely(reason != _URC_CONTINUE_UNWIND) {
			unwind_error = reason == _URC_END_OF_STACK
			               ? UNWIND_USER_NOTHROW
			               : UNWIND_PERSONALITY_ERROR;
			goto err;
		}
	}
	unwind_error = unwind_fde(&context.uc_fde, state, &oldstate, pc);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto err;

#if EXCEPT_BACKTRACE_SIZE != 0
	/* Remember the current state PC as a new entry in the exception's traceback. */
	if (current.pt_except.ei_trace[EXCEPT_BACKTRACE_SIZE - 1] == NULL) {
#if EXCEPT_BACKTRACE_SIZE > 1
		unsigned int i;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE - 1; ++i) {
			if (!current.pt_except.ei_trace[i])
				break;
		}
		current.pt_except.ei_trace[i] = __ERROR_REGISTER_STATE_TYPE_RDPC(*state);
#else /* EXCEPT_BACKTRACE_SIZE > 1 */
		current.pt_except.ei_trace[0] = __ERROR_REGISTER_STATE_TYPE_RDPC(*state);
#endif /* EXCEPT_BACKTRACE_SIZE <= 1 */
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	/* Continue searching for handlers. */
	goto search_fde;
err:
	{
		struct exception_info *info = &current.pt_except;
		if (unwind_error == UNWIND_NO_FRAME || unwind_error == UNWIND_USER_NOTHROW) {
			error_register_state_t *new_state;
			/* Try to handle special exceptions (E_EXIT_THREAD and E_EXIT_PROCESS) */
			new_state = handle_special_exception(state, &info->ei_data);
			if (new_state != NULL)
				return new_state;
			/* Try to convert the exception into a signal. */
			if (info->ei_flags & EXCEPT_FMAYSIGNAL)
				try_raise_signal_from_exception(state, &info->ei_data);
		}
		{
			PRIVATE SECTION_EXCEPT_STRING char const message_unwind_failed[] =
				"[libc] Failed to unwind stack at %p [error=%u]\n";
			syslog(LOG_ERR, message_unwind_failed,
			       __ERROR_REGISTER_STATE_TYPE_RDPC(oldstate),
			       unwind_error);
		}
		/* Use the original state that the caller of `libc_error_unwind()' provided
		 * in order to minimize the stack portion which can only be  re-constructed
		 * by walking the stack trace stored in `&current.pt_except->ei_trace' */
#if EXCEPT_BACKTRACE_SIZE != 0
		if (orig_tracecount < EXCEPT_BACKTRACE_SIZE) {
			/* Mark the traceback as complete by setting LAST_PC == CURR_PC */
			info->ei_trace[orig_tracecount] = error_register_state_getpc(&orig_state);
			++orig_tracecount;
		}
#endif /* EXCEPT_BACKTRACE_SIZE == 0 */
		trigger_coredump(&orig_state,
		                 &info->ei_state,
		                 &info->ei_data,
#if EXCEPT_BACKTRACE_SIZE != 0
		                 info->ei_trace,
		                 orig_tracecount,
#else /* EXCEPT_BACKTRACE_SIZE != 0 */
		                 NULL,
		                 0,
#endif /* EXCEPT_BACKTRACE_SIZE == 0 */
		                 unwind_error);
	}
}





LOCAL SECTION_EXCEPT_TEXT ATTR_PURE NONNULL((1)) _Unwind_Word __ERROR_UNWIND_CC
_Unwind_Context_Identify(struct _Unwind_Context *__restrict self) { /* Only non-const for lazy initialized fields! */
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
	return libc_Unwind_GetCFA(self) - self->uc_fde.f_sigframe;
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
	return libc_Unwind_GetCFA(self) + self->uc_fde.f_sigframe;
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
}


LOCAL ATTR_NOINLINE SECTION_EXCEPT_TEXT NONNULL((1)) error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_exception_raise_phase_2)(error_register_state_t *__restrict state,
                                                            struct _Unwind_Exception *__restrict exception_object) {
	struct _Unwind_Context context;
	error_register_state_t oldstate, newstate;
	unsigned int unwind_error;
	void const *pc;
	ENSURE_LIBUNWIND_LOADED();
	memcpy(&newstate, state, sizeof(newstate));
	context.uc_state = &newstate;
	for (;;) {
		int actions;
		memcpy(&oldstate, &newstate, sizeof(newstate));
		pc = __ERROR_REGISTER_STATE_TYPE_RDPC(oldstate) - 1;
		unwind_error = unwind_fde_find(pc, &context.uc_fde);
		if unlikely(unwind_error != UNWIND_SUCCESS)
			goto err_unwind__URC_FATAL_PHASE2_ERROR;
		actions = _Unwind_Context_Identify(&context) == exception_object->private_2
		          ? _UA_CLEANUP_PHASE | _UA_HANDLER_FRAME
		          : _UA_CLEANUP_PHASE | 0;
		if (context.uc_fde.f_persofun) {
			_Unwind_Reason_Code reason;
			reason = (*(_Unwind_Personality_Fn)context.uc_fde.f_persofun)(1, _UA_FORCE_UNWIND | _UA_CLEANUP_PHASE,
			                                                              exception_object->exception_class,
			                                                              exception_object, &context);
			if (reason == _URC_INSTALL_CONTEXT)
				break;
			if (reason != _URC_CONTINUE_UNWIND)
				goto err_unwind__URC_FATAL_PHASE2_ERROR;
		}
		/* Don't let us unwind past the handler context.  */
		assert(actions == _UA_CLEANUP_PHASE);
		/* Unwind the stack. */
		unwind_error = unwind_fde(&context.uc_fde, &newstate, &oldstate, pc);
		if unlikely(unwind_error != UNWIND_SUCCESS)
			goto err_unwind__URC_FATAL_PHASE2_ERROR;
	}
	/* Apply landing pad transformations. */
	unwind_error = unwind_landingpad(&context.uc_fde, &newstate, pc);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto err_unwind__URC_FATAL_PHASE2_ERROR;
	/* Write-back the register state. */
	memcpy(state, &newstate, sizeof(newstate));
	return state;
err_unwind__URC_FATAL_PHASE2_ERROR:
	__ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(*state, (uintptr_t)_URC_FATAL_PHASE2_ERROR);
	return state;
}

LOCAL ATTR_NOINLINE SECTION_EXCEPT_TEXT NONNULL((1)) error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_exception_forceunwind_phase_2)(error_register_state_t *__restrict state,
                                                                  struct _Unwind_Exception *__restrict exception_object) {
	struct _Unwind_Context context;
	error_register_state_t oldstate, newstate;
	unsigned int unwind_error;
	_Unwind_Stop_Fn stop;
	void *stop_argument;
	void const *pc;
	ENSURE_LIBUNWIND_LOADED();
	stop             = (_Unwind_Stop_Fn)(_Unwind_Ptr)exception_object->private_1;
	stop_argument    = (void *)(_Unwind_Ptr)exception_object->private_2;
	memcpy(&newstate, state, sizeof(newstate));
	context.uc_state = &newstate;
	for (;;) {
		_Unwind_Reason_Code reason;
		int action;
		memcpy(&oldstate, &newstate, sizeof(newstate));
		pc = __ERROR_REGISTER_STATE_TYPE_RDPC(oldstate) - 1;
		unwind_error = unwind_fde_find(pc, &context.uc_fde);
		if unlikely(unwind_error != UNWIND_SUCCESS && unwind_error != UNWIND_NO_FRAME)
			goto err_unwind__URC_FATAL_PHASE2_ERROR;
		/* Unwind successful.  */
		action = _UA_FORCE_UNWIND | _UA_CLEANUP_PHASE;
		if (unwind_error == UNWIND_NO_FRAME)
			action |= _UA_END_OF_STACK;
		reason = (*stop)(1, action, exception_object->exception_class,
		                 exception_object, &context, stop_argument);
		if (reason != _URC_NO_REASON)
			goto err_unwind__URC_FATAL_PHASE2_ERROR;
		/* stop() didn't want to do anything.
		 * Invoke the personality handler, if applicable, to run cleanups. */
		if (unwind_error == UNWIND_NO_FRAME)
			break;
		if (context.uc_fde.f_persofun) {
			reason = (*(_Unwind_Personality_Fn)context.uc_fde.f_persofun)(1, _UA_FORCE_UNWIND | _UA_CLEANUP_PHASE,
			                                                              exception_object->exception_class,
			                                                              exception_object, &context);
			if (reason == _URC_INSTALL_CONTEXT)
				break;
			if (reason != _URC_CONTINUE_UNWIND)
				goto err_unwind__URC_FATAL_PHASE2_ERROR;
		}
		/* Unwind the stack. */
		unwind_error = unwind_fde(&context.uc_fde, &newstate, &oldstate, pc);
		if unlikely(unwind_error != UNWIND_SUCCESS) {
			if (unwind_error == UNWIND_NO_FRAME)
				break;
			goto err_unwind__URC_FATAL_PHASE2_ERROR;
		}
	}
	/* Apply landing pad transformations. */
	unwind_error = unwind_landingpad(&context.uc_fde, &newstate, pc);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		goto err_unwind__URC_FATAL_PHASE2_ERROR;
	/* Write-back the register state. */
	memcpy(state, &newstate, sizeof(newstate));
	return state;
err_unwind__URC_FATAL_PHASE2_ERROR:
	__ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(*state, (uintptr_t)_URC_FATAL_PHASE2_ERROR);
	return state;
}

INTERN SECTION_EXCEPT_TEXT WUNUSED NONNULL((1)) error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_Resume_impl)(error_register_state_t *__restrict state,
                                                       struct _Unwind_Exception *exception_object) {
	/* Special case: Unwind a KERNKOS exception. */
	if (!exception_object || exception_object->exception_class == _UEC_KERNKOS)
		return libc_error_unwind(state);
	return exception_object->private_1 == 0
	       ? libc_exception_raise_phase_2(state, exception_object)
	       : libc_exception_forceunwind_phase_2(state, exception_object);
}

INTERN SECTION_EXCEPT_TEXT NONNULL((1, 2)) error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_RaiseException_impl)(error_register_state_t *__restrict state,
                                                                  struct _Unwind_Exception *exception_object) {
	unsigned int unwind_error;
	struct _Unwind_Context context;
	error_register_state_t oldstate, newstate;
	void const *pc;
	/* Special case: Raise a KERNKOS exception (with information already stored in `tls.t_except') */
	if unlikely(!exception_object || exception_object->exception_class == _UEC_KERNKOS)
		return libc_error_unwind(state);
	/* Make sure that libunwind has been loaded. */
	ENSURE_LIBUNWIND_LOADED();
	memcpy(&newstate, state, sizeof(newstate));
	context.uc_state = &newstate;
	/* Phase #1: Search for a viable exception handler. */
	for (;;) {
		memcpy(&oldstate, &newstate, sizeof(newstate));
		pc = __ERROR_REGISTER_STATE_TYPE_RDPC(oldstate) - 1;
		unwind_error = unwind_fde_find(pc, &context.uc_fde);
		if unlikely(unwind_error != UNWIND_SUCCESS)
			goto err_unwind;
		if (context.uc_fde.f_persofun) {
			_Unwind_Reason_Code reason;
			/* Invoke the custom personality function. */
			reason = (*(_Unwind_Personality_Fn)context.uc_fde.f_persofun)(1, _UA_SEARCH_PHASE,
			                                                              exception_object->exception_class,
			                                                              exception_object, &context);
			if (reason == _URC_HANDLER_FOUND)
				break;
			if (reason != _URC_CONTINUE_UNWIND)
				goto err_unwind__URC_FATAL_PHASE1_ERROR;
		}
		/* Unwind the stack. */
		unwind_error = unwind_fde(&context.uc_fde, &newstate, &oldstate, pc);
		if unlikely(unwind_error != UNWIND_SUCCESS)
			goto err_unwind;
	}
	/* Phase #2 */
	exception_object->private_1 = 0;
	exception_object->private_2 = _Unwind_Context_Identify(&context);
	return libc_exception_raise_phase_2(state, exception_object);
err_unwind:
	/* NOTE: This is how we must propagate errors! */
	if (unwind_error == UNWIND_NO_FRAME) {
		__ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(*state, (uintptr_t)_URC_END_OF_STACK);
	} else {
err_unwind__URC_FATAL_PHASE1_ERROR:
		__ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(*state, (uintptr_t)_URC_FATAL_PHASE1_ERROR);
	}
	return state;
}


INTERN SECTION_EXCEPT_TEXT NONNULL((1, 2)) error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_Resume_or_Rethrow_impl)(error_register_state_t *__restrict state,
                                                                  struct _Unwind_Exception *__restrict exception_object) {
	/* Choose between continuing to process _Unwind_RaiseException or _Unwind_ForcedUnwind.  */
	if unlikely(!exception_object || exception_object->exception_class == _UEC_KERNKOS)
		return libc_error_unwind(state);
	if (exception_object->private_1 == 0)
		return libc_Unwind_RaiseException_impl(state, exception_object);
	return libc_exception_forceunwind_phase_2(state, exception_object);
}

INTERN SECTION_EXCEPT_TEXT NONNULL((1, 2, 3)) error_register_state_t *
NOTHROW_NCX(__ERROR_UNWIND_CC libc_Unwind_ForcedUnwind_impl)(error_register_state_t *__restrict state,
                                                             struct _Unwind_Exception *__restrict exception_object,
                                                             _Unwind_Stop_Fn stop, void *stop_arg) {
	exception_object->private_1 = (_Unwind_Ptr)stop;
	exception_object->private_2 = (_Unwind_Ptr)stop_arg;
	return libc_exception_forceunwind_phase_2(state, exception_object);
}

INTERN SECTION_EXCEPT_TEXT NONNULL((1, 2)) _Unwind_Reason_Code __ERROR_UNWIND_CC
libc_Unwind_Backtrace_impl(error_register_state_t *__restrict state,
                           _Unwind_Trace_Fn func, void *arg) {
	struct _Unwind_Context context;
	error_register_state_t oldstate;
	_Unwind_Reason_Code reason;
	unsigned int unwind_error;
	context.uc_state = state;
	for (;;) {
		void const *pc;
		memcpy(&oldstate, state, sizeof(oldstate));
		pc = __ERROR_REGISTER_STATE_TYPE_RDPC(oldstate) - 1;
		unwind_error = unwind_fde_find(pc, &context.uc_fde);
		if (unwind_error != UNWIND_SUCCESS) {
			if unlikely(unwind_error != UNWIND_NO_FRAME)
				goto err_unwind;
		}
		/* Call trace function.  */
		reason = (*func)(&context, arg);
		if (reason != _URC_NO_REASON)
			break;
		if (unwind_error == UNWIND_NO_FRAME)
			break;
		memcpy(state, &oldstate, sizeof(oldstate));
	}
	return reason;
err_unwind:
	if (unwind_error == UNWIND_NO_FRAME)
		return _URC_END_OF_STACK;
	return _URC_FATAL_PHASE1_ERROR;
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetCFA, libc_Unwind_GetCFA);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1)) _Unwind_Word
NOTHROW_NCX(LIBCCALL libc_Unwind_GetCFA)(struct _Unwind_Context *__restrict self) { /* Only non-const for lazy initialized fields! */
	unsigned int unwind_error;
	unwind_cfa_value_t cfa;
	uintptr_t result;
	ENSURE_LIBUNWIND_LOADED();
	unwind_error = unwind_fde_exec_cfa(&self->uc_fde, &cfa,
	                                   __ERROR_REGISTER_STATE_TYPE_RDPC(*self->uc_state));
	if unlikely(unwind_error != UNWIND_SUCCESS)
		return 0;
	unwind_error = unwind_fde_calculate_cfa(&self->uc_fde, &cfa,
	                                        &unwind_getreg_error_register_state,
	                                        &self->uc_state, &result);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		return 0;
	return (_Unwind_Word)result;
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetDataRelBase, libc_Unwind_GetDataRelBase);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1)) _Unwind_Ptr
NOTHROW_NCX(LIBCCALL libc_Unwind_GetDataRelBase)(struct _Unwind_Context *__restrict self) { /* Only non-const for lazy initialized fields! */
	void const *result = self->uc_fde.f_bases.ub_dbase;
	if (!result) {
		result = dlgethandle(self->uc_fde.f_pcstart, DLGETHANDLE_FNORMAL);
		if (result) {
			result = dlauxctrl((void *)result, DLAUXCTRL_GET_DATABASE);
			self->uc_fde.f_bases.ub_dbase = result;
		}
	}
	return (_Unwind_Ptr)result;
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetTextRelBase, libc_Unwind_GetTextRelBase);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1)) _Unwind_Ptr
NOTHROW_NCX(LIBCCALL libc_Unwind_GetTextRelBase)(struct _Unwind_Context *__restrict self) { /* Only non-const for lazy initialized fields! */
	void const *result = self->uc_fde.f_bases.ub_tbase;
	if (!result) {
		result = dlgethandle(self->uc_fde.f_pcstart, DLGETHANDLE_FNORMAL);
		if (result) {
			result = dlauxctrl((void *)result, DLAUXCTRL_GET_TEXTBASE);
			self->uc_fde.f_bases.ub_tbase = result;
		}
	}
	return (_Unwind_Ptr)result;
}

DEFINE_PUBLIC_ALIAS(_Unwind_FindEnclosingFunction, libc_Unwind_FindEnclosingFunction);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED void *
NOTHROW_NCX(LIBCCALL libc_Unwind_FindEnclosingFunction)(void const *pc) {
	unsigned int unwind_error;
	unwind_fde_t fde;
	ENSURE_LIBUNWIND_LOADED();
	unwind_error = unwind_fde_find(pc, &fde);
	if unlikely(unwind_error != UNWIND_SUCCESS)
		return NULL;
	return (void *)fde.f_pcstart;
}






DEFINE_PUBLIC_ALIAS(_Unwind_DeleteException, libc_Unwind_DeleteException);
INTERN SECTION_EXCEPT_TEXT NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_Unwind_DeleteException)(struct _Unwind_Exception *__restrict exception_object) {
	if (exception_object->exception_cleanup)
		(*exception_object->exception_cleanup)(_URC_FOREIGN_EXCEPTION_CAUGHT, exception_object);
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetGR, libc_Unwind_GetGR);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW_NCX(LIBCCALL libc_Unwind_GetGR)(struct _Unwind_Context const *__restrict context, int index) {
	uintptr_t result = 0;
	if likely(CFI_REGISTER_SIZE(sizeof(void *), (unwind_regno_t)index) <= sizeof(result)) {
		ENSURE_LIBUNWIND_LOADED();
		unwind_getreg_error_register_state(context->uc_state,
		                                   (unwind_regno_t)index,
		                                   &result);
	}
	return result;
}

DEFINE_PUBLIC_ALIAS(_Unwind_SetGR, libc_Unwind_SetGR);
INTERN SECTION_EXCEPT_TEXT ATTR_LEAF NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_Unwind_SetGR)(struct _Unwind_Context *__restrict context,
                                        int index, uintptr_t value) {
	if likely(CFI_REGISTER_SIZE(sizeof(void *), (unwind_regno_t)index) <= sizeof(value)) {
		ENSURE_LIBUNWIND_LOADED();
		unwind_setreg_error_register_state(context->uc_state,
		                                   (unwind_regno_t)index,
		                                   &value);
	}
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetIP, libc_Unwind_GetIP);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW_NCX(LIBCCALL libc_Unwind_GetIP)(struct _Unwind_Context const *__restrict context) {
	return (uintptr_t)__ERROR_REGISTER_STATE_TYPE_RDPC(*context->uc_state);
}

DEFINE_PUBLIC_ALIAS(_Unwind_SetIP, libc_Unwind_SetIP);
INTERN SECTION_EXCEPT_TEXT ATTR_LEAF NONNULL((1)) void
NOTHROW_NCX(LIBCCALL libc_Unwind_SetIP)(struct _Unwind_Context *__restrict context, uintptr_t value) {
	__ERROR_REGISTER_STATE_TYPE_WRPC(*context->uc_state, value);
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetLanguageSpecificData, libc_Unwind_GetLanguageSpecificData);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW_NCX(LIBCCALL libc_Unwind_GetLanguageSpecificData)(struct _Unwind_Context const *__restrict context) {
	return (uintptr_t)context->uc_fde.f_lsdaaddr;
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetRegionStart, libc_Unwind_GetRegionStart);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1)) uintptr_t
NOTHROW_NCX(LIBCCALL libc_Unwind_GetRegionStart)(struct _Unwind_Context const *__restrict context) {
	return (uintptr_t)context->uc_fde.f_pcstart;
}

DEFINE_PUBLIC_ALIAS(_Unwind_GetIPInfo, libc_Unwind_GetIPInfo);
INTERN SECTION_EXCEPT_TEXT ATTR_PURE WUNUSED NONNULL((1, 2)) uintptr_t
NOTHROW_NCX(LIBCCALL libc_Unwind_GetIPInfo)(struct _Unwind_Context const *__restrict context,
                                            int *__restrict ip_before_insn) {
	*ip_before_insn = (int)context->uc_fde.f_sigframe;
	return (uintptr_t)__ERROR_REGISTER_STATE_TYPE_RDPC(*context->uc_state);
}




INTERN SECTION_EXCEPT_TEXT error_register_state_t *__EXCEPT_HANDLER_CC
libc_except_handler3_impl(error_register_state_t *__restrict state,
                          struct exception_data *__restrict error) {
	struct exception_info *info;
	uintptr_t recursion_flag = EXCEPT_FINEXCEPT;
	info = &current.pt_except;
	/* Prevent recursion if we're already within the kernel-level exception handler. */
	if unlikely(info->ei_flags & EXCEPT_FINEXCEPT) {
		if unlikely(info->ei_flags & EXCEPT_FINEXCEPT2)
			trigger_coredump(state, state, error, NULL, 0, UNWIND_USER_RECURSION);
		recursion_flag = EXCEPT_FINEXCEPT2;
	}
	COMPILER_BARRIER();
	/* Fill in the thread-local exception information descriptor. */
	info->ei_flags |= recursion_flag;
	COMPILER_WRITE_BARRIER();
	memcpy(&info->ei_state, state, sizeof(error_register_state_t));
	memcpy(&info->ei_data, error, sizeof(struct exception_data));
#if EXCEPT_BACKTRACE_SIZE != 0
	bzero(info->ei_trace, sizeof(info->ei_trace));
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	COMPILER_BARRIER();
	/* Perform exception unwinding */
	state = libc_error_unwind(state);
	/* Unset the in-except flag once we've successfully
	 * unwound  the  stack  up until  a  valid handler. */
	COMPILER_BARRIER();
	info->ei_flags &= ~recursion_flag;
	COMPILER_BARRIER();
	return state;
}

INTERN SECTION_EXCEPT_TEXT error_register_state_t *__EXCEPT_HANDLER_CC
libc_except_handler4_impl(error_register_state_t *__restrict state,
                          struct exception_data *__restrict error) {
	/* HINT: `libc_except_handler4()' is bound in `init.c:libc_init()' */
	unsigned int unwind_error;
	struct _Unwind_Context context;
	error_register_state_t oldstate, newstate;
	error_register_state_t first_handler;
	struct exception_info *info, saved_info;
	bool got_first_handler;
	uintptr_t recursion_flag = EXCEPT_FINEXCEPT;
	void const *pc;
	info = &current.pt_except;
	/* Prevent recursion if we're already within the kernel-level exception handler. */
	if unlikely(info->ei_flags & EXCEPT_FINEXCEPT) {
		if unlikely(info->ei_flags & EXCEPT_FINEXCEPT2)
			trigger_coredump(state, state, error, NULL, 0, UNWIND_USER_RECURSION);
		recursion_flag = EXCEPT_FINEXCEPT2;
	}
	COMPILER_BARRIER();
	/* Check if the base module is exception aware.
	 * If it is, handle the exception using mode #3 */
	if (dlexceptaware(dlopen(NULL, 0)) > 0)
		goto handle_mode_3;
	/* Check for special exceptions that are always handled in mode #3 */
	if (ERRORCLASS_ISRTLPRIORITY(error->e_class))
		goto handle_mode_3;
	COMPILER_BARRIER();
	memcpy(&saved_info, info, sizeof(*info));
	COMPILER_BARRIER();
	info->ei_flags |= recursion_flag | EXCEPT_FMAYSIGNAL;
	COMPILER_BARRIER();
	memcpy(&info->ei_data, error, sizeof(struct exception_data));
	memcpy(&info->ei_state, state, sizeof(error_register_state_t));
#if EXCEPT_BACKTRACE_SIZE != 0
	bzero(info->ei_trace, sizeof(info->ei_trace));
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	COMPILER_BARRIER();
	/* Make sure that libunwind has been loaded. */
	ENSURE_LIBUNWIND_LOADED();
	memcpy(&oldstate, state, sizeof(*state));
	context.uc_state  = &oldstate;
	got_first_handler = false;
	for (;;) {
		memcpy(&newstate, &oldstate, sizeof(oldstate));
		pc = __ERROR_REGISTER_STATE_TYPE_RDPC(newstate) - 1;
		unwind_error = unwind_fde_find(pc, &context.uc_fde);
		if unlikely(unwind_error != UNWIND_SUCCESS) {
			if (unwind_error == UNWIND_NO_FRAME)
				goto raise_signal; /* end-of-stack */
			goto do_coredump_with_unwind_error;
		}
		if (context.uc_fde.f_persofun) {
			/* Invoke the personality function */
			_Unwind_Reason_Code reason;
			reason = (*(_Unwind_Personality_Fn)context.uc_fde.f_persofun)(1, _UA_SEARCH_PHASE, _UEC_KERNKOS,
			                                                              libc_get_kos_unwind_exception(), &context);
			if (reason == _URC_HANDLER_FOUND) {
				void *handle;
				int is_aware;
				if (!got_first_handler) {
					/* Calculate the landing pad adjustment */
					memcpy(&first_handler, &oldstate, sizeof(oldstate));
					unwind_error = unwind_landingpad(&context.uc_fde, &first_handler, pc);
					if unlikely(unwind_error != UNWIND_SUCCESS)
						goto do_coredump_with_unwind_error;
					got_first_handler = true;
				}
				/* Check if the associated module is exception aware. */
				handle = dlgethandle(context.uc_fde.f_pcstart,
				                     DLGETHANDLE_FINCREF);
				if unlikely(!handle)
					goto do_coredump_with_dlerror;
				is_aware = dlexceptaware(handle);
				dlclose(handle);
				if unlikely(is_aware < 0)
					goto do_coredump_with_dlerror;
				if (is_aware) /* Found an exception aware handler! */
					goto install_first_handler;
			}
			if (reason != _URC_NO_REASON && reason != _URC_CONTINUE_UNWIND) {
				unwind_error = UNWIND_NO_FRAME;
				if (reason == _URC_FATAL_PHASE1_ERROR ||
				    reason == _URC_FATAL_PHASE2_ERROR)
					goto do_coredump_with_unwind_error;
				goto raise_signal;
			}
		}
		/* Unwind to the calling frame. */
		unwind_error = unwind_fde(&context.uc_fde, &newstate, &oldstate, pc);
		if unlikely(unwind_error != UNWIND_SUCCESS)
			goto do_coredump_with_unwind_error;
#if EXCEPT_BACKTRACE_SIZE != 0
		/* Remember the current state PC as a new entry in the exception's traceback. */
		if (info->ei_trace[EXCEPT_BACKTRACE_SIZE - 1] == NULL) {
#if EXCEPT_BACKTRACE_SIZE > 1
			unsigned int i;
			for (i = 0; i < EXCEPT_BACKTRACE_SIZE - 1; ++i) {
				if (!info->ei_trace[i])
					break;
			}
			info->ei_trace[i] = __ERROR_REGISTER_STATE_TYPE_RDPC(newstate);
#else /* EXCEPT_BACKTRACE_SIZE > 1 */
			info->ei_trace[0] = __ERROR_REGISTER_STATE_TYPE_RDPC(newstate);
#endif /* EXCEPT_BACKTRACE_SIZE <= 1 */
		}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	}
install_first_handler:
	/* Load the first found exception handler. */
	info->ei_flags &= ~recursion_flag;
	/* Pass the placeholder exception object for KOS exceptions. */
	__ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(first_handler, (uintptr_t)libc_get_kos_unwind_exception());
	memcpy(state, &first_handler, sizeof(*state));
	return state;
handle_mode_3:
	return libc_except_handler3_impl(state, error);
raise_signal:
	/* Restore the old exception */
	memcpy(info, &saved_info, sizeof(*info));
	/* raise the exception as a signal. */
	try_raise_signal_from_exception(state, error);
	/* Fallthrough  to  a regular  coredump  if the
	 * exception cannot be translated into a signal */
do_coredump_with_unwind_error:
	memcpy(info, &saved_info, sizeof(*info));
	trigger_coredump(state, state, error, NULL, 0, unwind_error);
do_coredump_with_dlerror:
	unwind_error = UNWIND_USER_DLERROR;
	goto do_coredump_with_unwind_error;
}


/* For ABI compatibility with linux (used to register .eh_frame sections)
 * On KOS, all  of this is  done automatically by  libdl which exports  a
 * functions that allows us to load the ".eh_frame" section of a  module.
 *
 * As such, we need support for an auxiliary table of eh_frame information
 * that  can  be added  to  or removed  from  by use  of  these functions.
 *
 * Also note that even though these functions need to go into libc (so that
 * programs can use  them without needing  to specify additional  libraries
 * during link), the actual implementations need to go into `libunwind.so'! */
struct rf_object {
	void *_data[6];
};

/* NOTE: In the original version, malloc() failing at this point is entirely undefined! */
#define rf_object_malloc() ((struct rf_object *)Malloc(sizeof(struct rf_object)))

typedef NONNULL((1, 2)) void (LIBCCALL *P__REGISTER_FRAME_INFO_BASES)(void const *begin, struct rf_object *__restrict ob, void const *tbase, void const *dbase);
typedef NONNULL((1, 2)) void (LIBCCALL *P__REGISTER_FRAME_INFO_TABLE_BASES)(void const *const *begin, struct rf_object *__restrict ob, void const *tbase, void const *dbase);
typedef NONNULL((1)) struct rf_object * /*NOTHROW*/ (LIBCCALL *P__DEREGISTER_FRAME_INFO)(void const *begin);
typedef NONNULL((2)) void const * /*NOTHROW_NCX*/ (LIBCCALL *P_UNWIND_FIND_FDE)(void const *pc, struct dwarf_eh_bases *__restrict bases);

PRIVATE ATTR_SECTION(".bss.crt.compat.linux.__register_frame") P__REGISTER_FRAME_INFO_BASES /*      */ pdyn___register_frame_info_bases       = NULL;
PRIVATE ATTR_SECTION(".bss.crt.compat.linux.__register_frame") P__REGISTER_FRAME_INFO_TABLE_BASES /**/ pdyn___register_frame_info_table_bases = NULL;
PRIVATE ATTR_SECTION(".bss.crt.compat.linux.__register_frame") P__DEREGISTER_FRAME_INFO /*          */ pdyn___deregister_frame_info           = NULL;
PRIVATE ATTR_SECTION(".bss.crt.compat.linux.__register_frame") P_UNWIND_FIND_FDE /*                 */ pdyn__Unwind_Find_FDE                  = NULL;

PRIVATE ATTR_SECTION(".rodata.crt.compat.linux.__register_frame") char const name___register_frame_info_bases[]       = "__register_frame_info_bases";
PRIVATE ATTR_SECTION(".rodata.crt.compat.linux.__register_frame") char const name___register_frame_info_table_bases[] = "__register_frame_info_table_bases";
PRIVATE ATTR_SECTION(".rodata.crt.compat.linux.__register_frame") char const name___deregister_frame_info[]           = "__deregister_frame_info";
PRIVATE ATTR_SECTION(".rodata.crt.compat.linux.__register_frame") char const name__Unwind_Find_FDE[]                  = "_Unwind_Find_FDE";

/* Initialize RegisterFrame-bindings implemented in libunwind. */
#define ENSURE_LIBUNWIND_LOADED_RF() \
	(ATOMIC_READ(pdyn__Unwind_Find_FDE) != NULL || (initialize_libunwind_rf(), 0))
INTERN ATTR_NOINLINE ATTR_SECTION(".text.crt.compat.linux.__register_frame")
void LIBCCALL initialize_libunwind_rf(void) {
	ENSURE_LIBUNWIND_LOADED();
	/* Dynamically bind functions. */
#define BIND(func, name)                                                 \
	if unlikely((*(void **)&func = dlsym(pdyn_libunwind, name)) == NULL) \
		goto err_init_failed
	BIND(pdyn___register_frame_info_bases, name___register_frame_info_bases);
	BIND(pdyn___register_frame_info_table_bases, name___register_frame_info_table_bases);
	BIND(pdyn___deregister_frame_info, name___deregister_frame_info);
	COMPILER_WRITE_BARRIER();
	BIND(pdyn__Unwind_Find_FDE, name__Unwind_Find_FDE);
	COMPILER_WRITE_BARRIER();
#undef BIND
	return;
err_init_failed:
	libunwind_init_failed();
}

/* Register-frame ABI (as normally defined by libgcc,  but on KOS is defined in  libc
 * as a couple of proxy functions that call forward to a smaller set of equalls named
 * functions found in libunwind) */
INTDEF NONNULL((2)) void LIBCCALL libc___register_frame_info_bases(/*nullable*/ void const *begin, struct rf_object *__restrict ob, void const *tbase, void const *dbase);
INTDEF NONNULL((2)) void LIBCCALL libc___register_frame_info(/*nullable*/ void const *begin, struct rf_object *__restrict ob);
INTDEF NONNULL((1)) void LIBCCALL libc___register_frame(void const *begin);
INTDEF NONNULL((1, 2)) void LIBCCALL libc___register_frame_info_table_bases(void const *const *begin, struct rf_object *__restrict ob, void const *tbase, void const *dbase);
INTDEF NONNULL((1, 2)) void LIBCCALL libc___register_frame_info_table(void const *const *begin, struct rf_object *__restrict ob);
INTDEF NONNULL((1)) void LIBCCALL libc___register_frame_table(void const *const *begin);
INTDEF struct rf_object *NOTHROW(LIBCCALL libc___deregister_frame_info)(/*nullable*/ void const *begin);
INTDEF NONNULL((1)) void NOTHROW(LIBCCALL libc___deregister_frame)(void const *begin);
INTDEF NONNULL((2)) void const *NOTHROW_NCX(LIBCCALL libc__Unwind_Find_FDE)(void const *pc, struct dwarf_eh_bases *__restrict bases);

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((2)) void LIBCCALL
libc___register_frame_info_bases(/*nullable*/ void const *begin, struct rf_object *__restrict ob,
                                 void const *tbase, void const *dbase) {
	ENSURE_LIBUNWIND_LOADED_RF();
	(*pdyn___register_frame_info_bases)(begin, ob, tbase, dbase);
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((1, 2)) void LIBCCALL
libc___register_frame_info_table_bases(void const *const *begin, struct rf_object *__restrict ob,
                                       void const *tbase, void const *dbase) {
	ENSURE_LIBUNWIND_LOADED_RF();
	(*pdyn___register_frame_info_table_bases)(begin, ob, tbase, dbase);
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") struct rf_object *
NOTHROW(LIBCCALL libc___deregister_frame_info)(/*nullable*/ void const *begin) {
	ENSURE_LIBUNWIND_LOADED_RF();
	return (*pdyn___deregister_frame_info)(begin);
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((2)) void const *
NOTHROW_NCX(LIBCCALL libc__Unwind_Find_FDE)(void const *pc, struct dwarf_eh_bases *__restrict bases) {
	ENSURE_LIBUNWIND_LOADED_RF();
	return (*pdyn__Unwind_Find_FDE)(pc, bases);
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((2)) void LIBCCALL
libc___register_frame_info(/*nullable*/ void const *begin, struct rf_object *__restrict ob) {
	libc___register_frame_info_bases(begin, ob, NULL, NULL);
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((1)) void LIBCCALL
libc___register_frame(void const *begin) {
	if (*(uint32_t const *)begin != 0)
		libc___register_frame_info(begin, rf_object_malloc());
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((1, 2)) void LIBCCALL
libc___register_frame_info_table(void const *const *begin, struct rf_object *__restrict ob) {
	libc___register_frame_info_table_bases(begin, ob, NULL, NULL);
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((1)) void LIBCCALL
libc___register_frame_table(void const *const *begin) {
	libc___register_frame_info_table(begin, rf_object_malloc());
}

INTERN ATTR_SECTION(".text.crt.compat.linux.__register_frame") NONNULL((1)) void
NOTHROW(LIBCCALL libc___deregister_frame)(void const *begin) {
	if (*(uint32_t const *)begin != 0)
		free(libc___deregister_frame_info(begin));
}



DEFINE_PUBLIC_ALIAS(__register_frame_info_bases, libc___register_frame_info_bases);
DEFINE_PUBLIC_ALIAS(__register_frame_info, libc___register_frame_info);
DEFINE_PUBLIC_ALIAS(__register_frame, libc___register_frame);
DEFINE_PUBLIC_ALIAS(__register_frame_info_table_bases, libc___register_frame_info_table_bases);
DEFINE_PUBLIC_ALIAS(__register_frame_info_table, libc___register_frame_info_table);
DEFINE_PUBLIC_ALIAS(__register_frame_table, libc___register_frame_table);
DEFINE_PUBLIC_ALIAS(__deregister_frame_info_bases, libc___deregister_frame_info);
DEFINE_PUBLIC_ALIAS(__deregister_frame_info, libc___deregister_frame_info);
DEFINE_PUBLIC_ALIAS(__deregister_frame, libc___deregister_frame);
DEFINE_PUBLIC_ALIAS(_Unwind_Find_FDE, libc__Unwind_Find_FDE);

DECL_END

#endif /* !GUARD_LIBC_LIBC_EXCEPT_C */
