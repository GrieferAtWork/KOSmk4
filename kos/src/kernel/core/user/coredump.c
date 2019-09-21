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
#ifndef GUARD_KERNEL_SRC_USER_COREDUMP_C
#define GUARD_KERNEL_SRC_USER_COREDUMP_C 1

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/printk.h>

#include <assert.h>
#include <format-printer.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* TODO: These 2 functions are current implemented as arch-specific. - Change that! */
INTDEF char const *NOTHROW(FCALL get_exception_name)(error_code_t code);
INTDEF void NOTHROW(KCALL print_exception_desc_of)(struct exception_data const *__restrict data,
                                                   pformatprinter printer, void *arg);


/* Main entry point for creating coredumps of the calling process.
 * When this function returns, the caller will usually throw an `E_EXIT_PROCESS' exception
 * in order to terminate the calling process.
 * @param: curr_ustate:       The current CPU state after unwinding (points to the call-site
 *                            of the last use of `RETHROW()' before an exception could no
 *                            longer be handled)
 * @param: orig_ustate:       The original CPU state that caused the exception/signal
 *                            When unwinding was not performed at any point, or if the coredump
 *                            is the result of an unhandled signal, the contents of this structure
 *                            are identical to `curr_ustate'
 *                            Note that in the later case, the caller must ensure that
 *                            `traceback_vector' is `NULL', and that `traceback_length'
 * @param: traceback_vector:  A selection of known traceback instruction points that were traversed
 *                            by the user-space unwind process between `orig_ustate' and `curr_ustate'
 *                            Note that this vector may be incomplete and therefor is only useful
 *                            for the purposes of being displayed to a human as part of a traceback
 *                            listing.
 *                            Note that when `traceback_length != 0 && traceback_vector[traceback_length-1] ==
 *                            UCPUSTATE_PC(*curr_ustate)', it can be assumed that the traceback is
 *                            complete and contains all traversed instruction locations. In this case,
 *                            a traceback displayed to a human should not include the text location
 *                            at `traceback_vector[traceback_length-1]', since that location would
 *                            also be printed when unwinding is completed for the purposes of
 *                            displaying a traceback.
 * @param: traceback_length:  The number of instruction pointers within `traceback_vector'
 * @param: reason_error:      The error that brought forth the coredump.
 *                            without any explicit error (or if the coredump was only signal-related),
 *                            this argument is `NULL'
 * @param: reason_signal:     The signal that was the reason for the coredump.
 *                            When the coredump was triggered by an exception, this is the result
 *                            of `error_as_signal(reason_error)', or NULL if the exception could not
 *                            be translated into a signal.
 *                            Alternatively, if the coredump was only caused by a posix signal, this
 *                            argument points to the information concerning that signal.
 * @param: unwind_error:      The unwind error that caused user-space to halt exception handling,
 *                            or `UNWIND_SUCCESS' if the coredump was triggered by a signal and
 *                            never caused any unwinding to be done.
 *                            In the former, it is more likely that `unwind_error == UNWIND_NOTHROW',
 *                            which happens when an exception is propagated through a function marked
 *                            as `NOTHROW()' (or `noexcept' if you prefer that one), however any other
 *                            error can also be indicate such as `UNWIND_RECURSION' in case an exception
 *                            was triggered whilst user-space was already in the process of handling two
 *                            others, and `UNWIND_DISABLED' in case user-space exception handling never
 *                            even got triggered.
 * @param: orig_kstate:       The kernel-space CPU state where the exception originally got thrown
 * @param: ktraceback_vector: The vector of kernel-space program pointers traversed during unwinding.
 *                            Always `NULL' when `orig_kstate' is also `NULL'
 * @param: ktraceback_length: The number of program pointers found within `ktraceback_vector'
 * The complete traceback of any given coredump looks like this (from least-recent address, to most-recent,
 * with program pointer information which may not necessarily be known written in [brackets]):
 *
 *             [orig_kstate]
 *             [ktraceback_vector[0]]
 *             [ktraceback_vector[1]]
 *             [...]
 *             [ktraceback_vector[ktraceback_length - 1]]
 *             orig_ustate
 *             [traceback_vector[0]]
 *             [traceback_vector[1]]
 *             [...]
 *             [traceback_vector[traceback_length - 1]]    // May be identical to `curr_ustate'
 *             curr_ustate                                 // May be identical to `orig_ustate'
 *             [unwind(curr_ustate)]                       // In theory, unwinding would continue here
 *             [unwind(unwind(curr_ustate))]
 *             [...]
 *
 */
PUBLIC NONNULL((1, 4)) void KCALL
coredump_create(struct ucpustate const *curr_ustate,
                void const *const *traceback_vector, size_t traceback_length,
                struct ucpustate const *orig_ustate,
                void const *const *ktraceback_vector, size_t ktraceback_length,
                struct kcpustate const *orig_kstate,
                struct exception_data const *reason_error,
                struct __siginfo_struct const *reason_signal,
                unsigned int unwind_error)
		THROWS(...) {
	size_t i;
	assert(curr_ustate != NULL);
	assert(orig_ustate != NULL);
	assert(memcmp(curr_ustate, orig_ustate, sizeof(ucpustate)) == 0
	       ? (traceback_vector == NULL && traceback_length == 0)
	       : 1);
	assert(orig_kstate == NULL
	       ? (ktraceback_vector == NULL && ktraceback_length == 0)
	       : 1);
	printk(KERN_ERR "[coredump] Creating coredump...\n");
	if (reason_error) {
		unsigned int i;
		char const *name;
		printk(KERN_ERR "exception %#x:%#x",
		       reason_error->e_class, reason_error->e_subclass);
		name = get_exception_name(reason_error->e_code);
		if (name)
			printk(KERN_ERR " [%s]", name);
		print_exception_desc_of(reason_error, &kprinter, (void *)KERN_ERR);
		printk(KERN_ERR "\n");
		for (i = 0; i < EXCEPTION_DATA_POINTERS; ++i) {
			if (!reason_error->e_pointers[i])
				continue;
			printk(KERN_ERR "\tpointer[%u] = %p\n",
			       i, reason_error->e_pointers[i]);
		}
	}
	if (reason_signal) {
		printk(KERN_ERR "signal %u\n", reason_signal->si_signo);
		if (reason_signal->si_code != 0)
			printk(KERN_ERR "\tcode:  %u\n", reason_signal->si_code);
		if (reason_signal->si_errno != 0)
			printk(KERN_ERR "\terrno: %u\n", reason_signal->si_errno);
	}
#define VINFO_FORMAT  "%[vinfo:%p [%Rf:%l,%c:%n]]"
	if (orig_kstate)
		printk(KERN_RAW VINFO_FORMAT " orig_kstate\n", KCPUSTATE_PC(*orig_kstate));
	for (i = 0; i < ktraceback_length; ++i) {
		printk(KERN_RAW VINFO_FORMAT " ktraceback_vector[%Iu]\n",
		       ktraceback_vector[i], i);
	}
	printk(KERN_RAW VINFO_FORMAT " orig_ustate\n", UCPUSTATE_PC(*orig_ustate));
	for (i = 0; i < traceback_length; ++i) {
		printk(KERN_RAW VINFO_FORMAT " traceback_vector[%Iu]\n",
		       traceback_vector[i], i);
	}
	if (UCPUSTATE_PC(*curr_ustate) != UCPUSTATE_PC(*orig_ustate) &&
	    (traceback_length == 0 || UCPUSTATE_PC(*curr_ustate) != (uintptr_t)traceback_vector[traceback_length - 1])) {
		printk(KERN_RAW VINFO_FORMAT " curr_ustate\n", UCPUSTATE_PC(*curr_ustate));
	}

	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_COREDUMP)) {
		siginfo_t siginfo;
		if (!error_as_signal(error_data(), &siginfo))
			siginfo.si_signo = SIGABRT;
		/* Trigger a debugger trap at last valid text location. */
		curr_ustate = kernel_debugtrap_r((struct ucpustate *)curr_ustate, siginfo.si_signo);
	}
	/* TODO */
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_COREDUMP_C */
