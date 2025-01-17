/* HASH CRC-32:0x4e358c35 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_except_as_signal_defined
#define __local_except_as_signal_defined
#include <__crt.h>
#include <kos/bits/exception_data.h>
#include <bits/os/siginfo.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzero_defined
#define __local___localdep_bzero_defined
#ifdef __CRT_HAVE_bzero
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE___bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),__bzero,(__dst,__num_bytes))
#elif defined(__CRT_HAVE_explicit_bzero)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_OUTS(1, 2),__NOTHROW_NCX,__localdep_bzero,(void *__restrict __dst, __SIZE_TYPE__ __num_bytes),explicit_bzero,(__dst,__num_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzero.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzero __LIBC_LOCAL_NAME(bzero)
#endif /* !... */
#endif /* !__local___localdep_bzero_defined */
#ifndef __local___localdep_except_as_errno_defined
#define __local___localdep_except_as_errno_defined
#ifdef __CRT_HAVE_except_as_errno
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__errno_t,__NOTHROW_NCX,__LIBKCALL,__localdep_except_as_errno,(struct exception_data const *__restrict __self),except_as_errno,(__self))
#else /* __CRT_HAVE_except_as_errno */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/except_as_errno.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_except_as_errno __LIBC_LOCAL_NAME(except_as_errno)
#endif /* !__CRT_HAVE_except_as_errno */
#endif /* !__local___localdep_except_as_errno_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
#include <asm/os/siginfo.h>
#include <asm/os/signal.h>
#include <kos/except/codes.h>
#include <kos/kernel/handle.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(except_as_signal) __ATTR_WUNUSED __ATTR_IN(1) __ATTR_OUT(2) __BOOL
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(except_as_signal))(struct exception_data const *__restrict __self, struct __siginfo_struct *__restrict __result) {
	__except_code_t __code = __self->e_code;
	(__NAMESPACE_LOCAL_SYM __localdep_bzero)(__result, sizeof(*__result));
	/* TODO: Make sure that this matches the sysv abi386 requirements:
	 *       Figure    3-27:    Hardware   Exceptions    and   Signals
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
	switch (EXCEPT_CLASS(__code)) {

#ifdef __SIGQUIT
	case E_EXIT_THREAD:
	case E_EXIT_PROCESS:
		__result->si_signo = __SIGQUIT;
		break;
#endif /* __SIGQUIT */

#if defined(__SIGBUS) && defined(__BUS_OBJERR)
	case E_IOERROR:
		__result->si_signo = __SIGBUS;
		__result->si_code  = __BUS_OBJERR;
		break;
#endif /* __SIGBUS && __BUS_OBJERR */

#ifdef __SIGSYS
	case E_UNKNOWN_SYSTEMCALL:
		__result->si_signo   = __SIGSYS;
		__result->si_syscall = __self->e_args.e_unknown_systemcall.us_sysno;
		/* TODO: `si_arch' could be determined by
		 *       `self->e_args.e_unknown_systemcall.us_flags & RPC_SYSCALL_INFO_FMETHOD'! */
		break;
#endif /* __SIGSYS */

#if defined(__SIGFPE) && defined(__FPE_INTDIV)
	case E_DIVIDE_BY_ZERO:
		__result->si_signo = __SIGFPE;
		__result->si_code  = __FPE_INTDIV;
		break;
#endif /* __SIGFPE && __FPE_INTDIV */

#if defined(__SIGFPE) && defined(__FPE_INTOVF)
	case E_OVERFLOW:
		__result->si_signo = __SIGFPE;
		__result->si_code  = __FPE_INTOVF;
		break;
#endif /* __SIGFPE && __FPE_INTOVF */

#if defined(__SIGTRAP) && defined(__TRAP_BRKPT)
	case E_BREAKPOINT:
		__result->si_signo = __SIGTRAP;
		__result->si_code  = __TRAP_BRKPT;
		break;
#endif /* __SIGTRAP && __TRAP_BRKPT */

#ifdef __SIGINT
	case E_INTERRUPT:
		__result->si_signo = __SIGINT;
		break;
#endif /* __SIGINT */

#if defined(__SIGFPE) && defined(__FPE_FLTSUB)
	case E_INDEX_ERROR:
		__result->si_signo = __SIGFPE;
		__result->si_code  = __FPE_FLTSUB;
		break;
#endif /* __SIGFPE && __FPE_FLTSUB */

#if defined(__SIGSEGV) && defined(__SEGV_MAPERR)
	case E_SEGFAULT:
	case E_STACK_OVERFLOW:
		__result->si_signo = __SIGSEGV;
		__result->si_code  = __SEGV_MAPERR;
		switch (__code) {

#ifdef __SEGV_ACCERR
		case EXCEPT_CODEOF(E_SEGFAULT_READONLY):
		case EXCEPT_CODEOF(E_SEGFAULT_NOTREADABLE):
		case EXCEPT_CODEOF(E_SEGFAULT_NOTEXECUTABLE):
			__result->si_code = __SEGV_ACCERR;
			break;
#endif /* __SEGV_ACCERR */

#if defined(__SIGBUS) && defined(__BUS_OBJERR)
		case EXCEPT_CODEOF(E_SEGFAULT_NOTATOMIC):
			__result->si_signo = __SIGBUS;
			__result->si_code  = __BUS_OBJERR;
			break;
#endif /* __SIGBUS && __BUS_OBJERR */

#if defined(__SIGBUS) && defined(__BUS_ADRALN)
		case EXCEPT_CODEOF(E_SEGFAULT_UNALIGNED):
			__result->si_signo = __SIGBUS;
			__result->si_code  = __BUS_ADRALN;
			break;
#endif /* __SIGBUS && __BUS_ADRALN */

		default: break;
		}
		__result->si_addr  = (void *)__self->e_args.e_segfault.s_addr;
		__result->si_lower = __result->si_addr;
		__result->si_upper = __result->si_addr;
		break;
#endif /* __SIGSEGV && __SEGV_MAPERR */

#ifdef __SIGILL
	case E_ILLEGAL_INSTRUCTION:
		__result->si_signo = __SIGILL;
		switch (__code) {

#ifdef __ILL_ILLOPN
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND):
			__result->si_code = __ILL_ILLOPN;
#ifdef __ILL_ILLADR
			if (__self->e_args.e_illegal_instruction.ii_bad_operand.bo_what == E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_MEMORY ||
			    __self->e_args.e_illegal_instruction.ii_bad_operand.bo_what == E_ILLEGAL_INSTRUCTION_BAD_OPERAND_UNEXPECTED_REGISTER)
				__result->si_code = __ILL_ILLADR;
#endif /* __ILL_ILLADR */
			break;
#endif /* __ILL_ILLOPN */

#ifdef __ILL_PRVOPC
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE):
			__result->si_code = __ILL_PRVOPC;
			break;
#endif /* __ILL_PRVOPC */

#ifdef __ILL_ILLOPN
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER):
			__result->si_code = __ILL_ILLOPN;
#ifdef __ILL_PRVREG
			if (__self->e_args.e_illegal_instruction.ii_register.r_how == E_ILLEGAL_INSTRUCTION_REGISTER_RDPRV ||
			    __self->e_args.e_illegal_instruction.ii_register.r_how == E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV)
				__result->si_code = __ILL_PRVREG;
#endif /* __ILL_PRVREG */
			break;
#endif /* __ILL_ILLOPN */

#if defined(__ILL_ILLADR) && defined(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT)
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT):
			__result->si_code = __ILL_ILLADR;
			break;
#endif /* __ILL_ILLADR && E_ILLEGAL_INSTRUCTION_X86_INTERRUPT */

#ifdef __ILL_ILLOPC
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE):
#ifdef E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX):
#endif /* E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX */
#ifdef E_ILLEGAL_INSTRUCTION_X86_TOO_LONG
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_X86_TOO_LONG):
#endif /* E_ILLEGAL_INSTRUCTION_X86_TOO_LONG */
		case EXCEPT_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE):
			__result->si_code = __ILL_ILLOPC;
			break;
#endif /* __ILL_ILLOPC */

		default:
			break;
		}
		break;
#endif /* __SIGILL */

	default:
		return 0;
	}
	__result->si_errno = (__NAMESPACE_LOCAL_SYM __localdep_except_as_errno)(__self);
	return 1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_except_as_signal_defined
#define __local___localdep_except_as_signal_defined
#define __localdep_except_as_signal __LIBC_LOCAL_NAME(except_as_signal)
#endif /* !__local___localdep_except_as_signal_defined */
#endif /* !__local_except_as_signal_defined */
