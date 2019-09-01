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
#ifndef GUARD_LIBC_HYBRID_EXCEPT_TO_POSIX_C
#define GUARD_LIBC_HYBRID_EXCEPT_TO_POSIX_C 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/except.h>

#include <signal.h>
#include <stdbool.h>
#include <string.h>

#include "except_to_posix.h"


DECL_BEGIN

struct __siginfo_struct;

/* Transform the given exception into a posix errno value. */
DEFINE_PUBLIC_ALIAS(error_as_errno, libc_error_as_errno);
INTERN WUNUSED errno_t
NOTHROW_NCX_KERNEL(LIBCCALL libc_error_as_errno)(struct exception_data const *__restrict data) {
	errno_t result    = EPERM;
	error_code_t code = data->e_code;
#undef END
#undef CLASS
#undef SUBCLASS
	switch (ERROR_CLASS(code)) {
#define SET_ERRNO_NO_ERRNO /* nothing */
#define SET_ERRNO_ERRNO(x) result = x;
#define SET_ERRNO(x) SET_ERRNO_##x
#define CLASS(name, message, errno, members) \
	case name:                               \
		SET_ERRNO(errno)                     \
		switch (ERROR_SUBCLASS(code)) {
#define SUBCLASS(name, message, errno, members) \
	case ERROR_SUBCLASS(ERROR_CODE name):       \
		SET_ERRNO(errno)                        \
		break;
#define END         \
	default: break; \
		}           \
		break;
#define GET_EXCEPTION_POINTER(i) data->e_pointers[i]
#ifndef __INTELLISENSE__
#include <kos/except-codes.def>
#endif
#undef GET_EXCEPTION_POINTER
#undef SUBCLASS
#undef CLASS
#undef END
	}
	return result;
}

/* Transform the currently thrown exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
DEFINE_PUBLIC_ALIAS(error_as_signal, libc_error_as_signal);
INTERN WUNUSED bool 
NOTHROW_NCX_KERNEL(LIBCCALL libc_error_as_signal)(struct exception_data const *__restrict data,
                                                  struct __siginfo_struct *__restrict result) {
	error_code_t code = data->e_code;
	memset(result, 0, sizeof(*result));

	/* TODO: Make sure that this matches the sysv abi386 requirements:
	 *       Figure 3-27:  Hardware Exceptions and Signals
	 *       0   divide error fault             SIGFPE
	 *       1   single step trap/fault         SIGTRAP
	 *       2   nonmaskable interrupt          none
	 *       3   breakpoint trap                SIGTRAP
	 *       4   overflow trap                  SIGSEGV
	 *       5   bounds check fault             SIGSEGV
	 *       6   invalid opcode fault           SIGILL
	 *       7   no coprocessor fault           SIGFPE
	 *       8   double fault abort             none
	 *       9   coprocessor overrun abort      SIGSEGV
	 *       10  invalid TSS fault              none
	 *       11  segment not present fault      none
	 *       12  stack exception fault          SIGSEGV
	 *       13  general protection fault/abort SIGSEGV
	 *       14  page fault                     SIGSEGV
	 *       15 (reserved)
	 *       16 coprocessor error fault         SIGFPE
	 *       other (unspecified)                SIGILL */
	/* TODO: Finally add an FPU emulation library! */

	switch (ERROR_CLASS(code)) {

	case E_EXIT_THREAD:
	case E_EXIT_PROCESS:
		result->si_signo = SIGQUIT;
		break;

	case E_UNKNOWN_SYSTEMCALL:
		result->si_signo   = SIGSYS;
		result->si_errno   = ENOSYS;
		result->si_syscall = data->e_pointers[0];
		break;

	case E_DIVIDE_BY_ZERO:
		result->si_signo = SIGFPE;
		result->si_code  = FPE_INTDIV;
		break;

	case E_OVERFLOW:
		result->si_signo = SIGFPE;
		result->si_code  = FPE_INTOVF;
		break;

	case E_INVALID_ALIGNMENT:
		result->si_signo = SIGBUS;
		result->si_code  = BUS_ADRALN;
		break;

	case E_BREAKPOINT:
		result->si_signo = SIGTRAP;
		result->si_code  = TRAP_BRKPT;
		break;

	case E_INTERRUPT:
		result->si_signo = SIGINT;
		break;

	case E_INDEX_ERROR:
		result->si_signo = SIGFPE;
		result->si_code  = FPE_FLTSUB;
		break;

	case E_SEGFAULT:
	case E_STACK_OVERFLOW:
		result->si_signo = SIGSEGV;
		result->si_code  = SEGV_MAPERR;
		switch (code) {
		case ERROR_CODEOF(E_SEGFAULT_READONLY):
		case ERROR_CODEOF(E_SEGFAULT_NOTREADABLE):
		case ERROR_CODEOF(E_SEGFAULT_NOTEXECUTABLE):
			result->si_code = SEGV_ACCERR;
			break;
		default: break;
		}
		result->si_addr  = (void *)data->e_pointers[0];
		result->si_lower = result->si_addr;
		result->si_upper = result->si_addr;
		break;

	case E_ILLEGAL_INSTRUCTION:
		result->si_signo = SIGILL;
		switch (code) {

		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND):
			result->si_code = ILL_ILLOPN;
			if (data->e_pointers[1] == E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE)
				result->si_code = ILL_ILLADR;
			break;

#ifdef E_ILLEGAL_INSTRUCTION_X86_INTERRUPT
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT):
			result->si_code = ILL_ILLADR;
			break;
#endif /* E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */

		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE):
			result->si_code = ILL_PRVOPC;
			break;

		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER):
			switch (data->e_pointers[1]) {
			case E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV:
			case E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV:
				result->si_code = ILL_PRVREG;
				break;
			default:
				result->si_code = ILL_ILLOPN;
				break;
			}
			break;

		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE):
#ifdef E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX):
#endif /* E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX */
#ifdef E_ILLEGAL_INSTRUCTION_X86_TOO_LONG
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_TOO_LONG):
#endif /* E_ILLEGAL_INSTRUCTION_X86_TOO_LONG */
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE):
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_VIO_UNRECOGNIZED):
			result->si_code = ILL_ILLOPC;
			break;

		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_VIO_NONATOMIC_OPERAND):
		case ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_VIO_INVALID_KERNEL_SP):
			result->si_code = ILL_ILLADR;
			break;

		default:
			break;
		}
		break;

	default:
		return false;
	}
	return true;
}



DECL_END

#endif /* !GUARD_LIBC_HYBRID_EXCEPT_TO_POSIX_C */
