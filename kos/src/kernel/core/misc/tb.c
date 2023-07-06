/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MISC_TB_C
#define GUARD_KERNEL_SRC_MISC_TB_C 1
#define DISABLE_BRANCH_PROFILING

#include <kernel/compiler.h>

#include <kernel/addr2line.h>
#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/mman/mnode.h>
#include <kernel/paging.h>
#include <kernel/syslog.h>
#include <kernel/tb.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/host.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <alloca.h>
#include <format-printer.h>
#include <string.h>

#include <libdebuginfo/unwind.h>
#include <libinstrlen/instrlen.h>
#include <libunwind/errno.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

DECL_BEGIN

PRIVATE ATTR_COLDTEXT WUNUSED bool
NOTHROW(FCALL try_read_pointer)(void **src, void **dst) {
	NESTED_TRY {
		*dst = *src;
	} EXCEPT {
		return false;
	}
	return true;
}

PRIVATE NOBLOCK ATTR_COLDTEXT bool
NOTHROW(FCALL is_pc)(void *pc) {
	bool result;
	struct mnode *node;
	if (!ADDR_ISKERN(pc))
		goto nope;
	if (!mman_lock_tryread(&mman_kernel))
		return true; /* Assume so we don't skip anything... */
	node   = mman_mappings_locate(&mman_kernel, pc);
	result = (node != NULL) &&
	         (node->mn_flags & MNODE_F_PEXEC) != 0;
	mman_lock_endread(&mman_kernel);
	return result;
nope:
	return false;
}


PRIVATE ATTR_COLDTEXT NONNULL((1, 3, 5, 6)) ssize_t FCALL
do_print_traceback(pformatprinter printer, void *arg,
                   void *__restrict state, size_t state_size,
                   unwind_getreg_t reg_getter,
                   unwind_setreg_t reg_setter,
                   unsigned int n_skip) {
	ssize_t temp, result;
	unwind_errno_t error;
	void *old_state;
	void *pc, *sp, *last_good_sp;
	old_state = alloca(state_size);
	(*reg_getter)(state, CFI_UNWIND_REGISTER_PC(sizeof(void *)), &pc);
	(*reg_getter)(state, CFI_UNWIND_REGISTER_SP(sizeof(void *)), &sp);
	last_good_sp = sp;
	if (n_skip) {
		--n_skip;
		result = 0;
	} else {
		isa_t isa;
		isa = unwind_getreg_getisa(reg_getter, state);
		result = addr2line_printf(printer, arg,
		                          instruction_trypred(pc, isa),
		                          pc, "sp=%p", sp);
		if unlikely(result < 0)
			goto done;
	}
	for (;;) {
		memcpy(old_state, state, state_size);
		error = unwind_for_debug((byte_t *)pc - 1,
		                         reg_getter, old_state,
		                         reg_setter, state);
		if (error != UNWIND_SUCCESS)
			break;
		(*reg_getter)(state, CFI_UNWIND_REGISTER_PC(sizeof(void *)), &pc);
		(*reg_getter)(state, CFI_UNWIND_REGISTER_SP(sizeof(void *)), &sp);
		if (n_skip) {
			--n_skip;
		} else {
			isa_t isa;
			isa = unwind_getreg_getisa(reg_getter, state);
			temp = addr2line_printf(printer, arg,
			                        instruction_trypred(pc, isa),
			                        pc, "sp=%p", sp);
			if unlikely(temp < 0)
				goto err;
			result += temp;
		}
		last_good_sp = sp;
	}
	if (error != UNWIND_NO_FRAME) {
		temp = format_printf(printer, arg,
		                     "Unwind failure: %u\n",
		                     error);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	if (ADDR_ISKERN(last_good_sp)) {
		void *minaddr, *endaddr;
		get_stack_for(&minaddr, &endaddr, (void *)last_good_sp);
		if ((byte_t *)last_good_sp >= (byte_t *)minaddr &&
		    (byte_t *)last_good_sp < (byte_t *)endaddr) {
			bool is_first = true;
			isa_t isa;
			isa = unwind_getreg_getisa(reg_getter, state);
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			uintptr_t iter;
			iter = FLOOR_ALIGN((uintptr_t)last_good_sp, sizeof(void *));
			for (; iter < (uintptr_t)endaddr; iter += sizeof(void *))
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			uintptr_t iter;
			iter  = CEIL_ALIGN((uintptr_t)last_good_sp, sizeof(void *));
			while (iter > (uintptr_t)minaddr)
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
			{
				void *pc;
#ifndef __ARCH_STACK_GROWS_DOWNWARDS
				iter -= sizeof(void *);
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
				if (!try_read_pointer((void **)iter, &pc))
					break;
				if (!is_pc(pc))
					continue;
				if (is_first) {
#define MESSAGE "Analyzing remainder of stack:\n"
					temp = (*printer)(arg, MESSAGE, COMPILER_STRLEN(MESSAGE));
#undef MESSAGE
					if unlikely(temp < 0)
						goto err;
					result += temp;
					is_first = false;
				}
				if (n_skip) {
					--n_skip;
				} else {
					temp = addr2line_printf(printer, arg,
					                        instruction_trypred(pc, isa),
					                        pc, "pc@%p", iter);
					if unlikely(temp < 0)
						goto err;
					result += temp;
				}
			}
		}
	}
done:
	return result;
err:
	return temp;
}


/* Dump   a  traceback  for  the  given  cpu  state.
 * Tracebacks are printed using `addr2line_printf()' */
PUBLIC ATTR_NOINLINE ATTR_WEAK ATTR_SECTION(".text.kernel.print_traceback") NONNULL((1))
ssize_t FCALL print_traceback(pformatprinter printer, void *arg,
                              unsigned int n_skip) {
	struct ucpustate st;
	ucpustate_current(&st);
	return do_print_traceback(printer, arg, &st, sizeof(st),
	                          &unwind_getreg_ucpustate,
	                          &unwind_setreg_ucpustate,
	                          n_skip + 1);
}

PRIVATE ATTR_COLDTEXT NONNULL((1, 3, 5, 6)) ssize_t FCALL
do_print_traceback_copy(pformatprinter printer, void *arg,
                        void const *__restrict state, size_t state_size,
                        unwind_getreg_t reg_getter,
                        unwind_setreg_t reg_setter,
                        unsigned int n_skip) {
	void *old_state;
	old_state = alloca(state_size);
	memcpy(old_state, state, state_size);
	return do_print_traceback(printer, arg,
	                          old_state, state_size,
	                          reg_getter, reg_setter,
	                          n_skip);
}

PUBLIC ATTR_COLDTEXT NONNULL((1, 3)) ssize_t FCALL
print_traceback_ucpustate(pformatprinter printer, void *arg,
                          struct ucpustate const *__restrict state,
                          unsigned int n_skip) {
	return do_print_traceback_copy(printer, arg, state, sizeof(*state),
	                               &unwind_getreg_ucpustate,
	                               &unwind_setreg_ucpustate,
	                               n_skip);
}

#ifndef LCPUSTATE_ALIAS
PUBLIC ATTR_COLDTEXT NONNULL((1, 3)) ssize_t FCALL
print_traceback_lcpustate(pformatprinter printer, void *arg,
                          struct lcpustate const *__restrict state,
                          unsigned int n_skip) {
	struct kcpustate kst;
	lcpustate_to_kcpustate(state, &kst);
	return print_traceback_kcpustate(printer, arg, &kst, n_skip);
}
#endif /* !LCPUSTATE_ALIAS */

#ifndef KCPUSTATE_ALIAS
PUBLIC ATTR_COLDTEXT NONNULL((1, 3)) ssize_t FCALL
print_traceback_kcpustate(pformatprinter printer, void *arg,
                          struct kcpustate const *__restrict state,
                          unsigned int n_skip) {
	return do_print_traceback_copy(printer, arg, state, sizeof(*state),
	                               &unwind_getreg_kcpustate,
	                               &unwind_setreg_kcpustate,
	                               n_skip);
}
#endif /* !KCPUSTATE_ALIAS */

#ifndef ICPUSTATE_ALIAS
PUBLIC ATTR_COLDTEXT NONNULL((1, 3)) ssize_t FCALL
print_traceback_icpustate(pformatprinter printer, void *arg,
                          struct icpustate const *__restrict state,
                          unsigned int n_skip) {
	struct ucpustate ust;
	icpustate_to_ucpustate(state, &ust);
	return print_traceback_ucpustate(printer, arg, &ust, n_skip);
}
#endif /* !ICPUSTATE_ALIAS */

#ifndef SCPUSTATE_ALIAS
PUBLIC ATTR_COLDTEXT NONNULL((1, 3)) ssize_t FCALL
print_traceback_scpustate(pformatprinter printer, void *arg,
                          struct scpustate const *__restrict state,
                          unsigned int n_skip) {
	struct ucpustate ust;
	scpustate_to_ucpustate(state, &ust);
	return print_traceback_ucpustate(printer, arg, &ust, n_skip);
}
#endif /* !SCPUSTATE_ALIAS */

#ifndef FCPUSTATE_ALIAS
PUBLIC ATTR_COLDTEXT NONNULL((1, 3)) ssize_t FCALL
print_traceback_fcpustate(pformatprinter printer, void *arg,
                          struct fcpustate const *__restrict state,
                          unsigned int n_skip) {
	return do_print_traceback_copy(printer, arg, state, sizeof(*state),
	                               &unwind_getreg_fcpustate,
	                               &unwind_setreg_fcpustate,
	                               n_skip);
}
#endif /* !FCPUSTATE_ALIAS */

/* Print a traceback to the system log, using `KERN_RAW' */
PUBLIC ATTR_NOINLINE ATTR_WEAK ATTR_SECTION(".text.kernel.tbn")
void FCALL tbn(unsigned int n_skip) {
	print_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, n_skip + 1);
	__asm__ __volatile__(""); /* Prevent `print_traceback()' being turned into a tail-call */
}

PUBLIC ATTR_NOINLINE ATTR_WEAK ATTR_SECTION(".text.kernel.tb")
void FCALL tb(void) {
	print_traceback(&syslog_printer, SYSLOG_LEVEL_RAW, 1);
	__asm__ __volatile__(""); /* Prevent `print_traceback()' being turned into a tail-call */
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_TB_C */
