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
#ifndef GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H
#define GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H 1

#include <hybrid/host.h>

/* Libc functions implemented  by arch-specific, optimized  functions.
 * Defining these macros causes libc's auto/user-system to not provide
 * the associated functions. */

/* memcpy() */
#define LIBC_ARCH_HAVE_MEMCPY   1
#define LIBC_ARCH_HAVE_MEMCPYW  1
#define LIBC_ARCH_HAVE_MEMCPYL  1
#define LIBC_ARCH_HAVE_MEMPCPY  1
#define LIBC_ARCH_HAVE_MEMPCPYW 1
#define LIBC_ARCH_HAVE_MEMPCPYL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMCPYQ  1
#define LIBC_ARCH_HAVE_MEMPCPYQ 1
#endif /* __x86_64__ */

/* memmove() */
#define LIBC_ARCH_HAVE_MEMMOVE       1
#define LIBC_ARCH_HAVE_MEMMOVEUP     1
#define LIBC_ARCH_HAVE_MEMMOVEDOWN   1
#define LIBC_ARCH_HAVE_MEMMOVEW      1
#define LIBC_ARCH_HAVE_MEMMOVEUPW    1
#define LIBC_ARCH_HAVE_MEMMOVEDOWNW  1
#define LIBC_ARCH_HAVE_MEMMOVEL      1
#define LIBC_ARCH_HAVE_MEMMOVEUPL    1
#define LIBC_ARCH_HAVE_MEMMOVEDOWNL  1
#define LIBC_ARCH_HAVE_MEMPMOVE      1
#define LIBC_ARCH_HAVE_MEMPMOVEUP    1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWN  1
#define LIBC_ARCH_HAVE_MEMPMOVEW     1
#define LIBC_ARCH_HAVE_MEMPMOVEUPW   1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWNW 1
#define LIBC_ARCH_HAVE_MEMPMOVEL     1
#define LIBC_ARCH_HAVE_MEMPMOVEUPL   1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWNL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMMOVEQ      1
#define LIBC_ARCH_HAVE_MEMMOVEUPQ    1
#define LIBC_ARCH_HAVE_MEMMOVEDOWNQ  1
#define LIBC_ARCH_HAVE_MEMPMOVEQ     1
#define LIBC_ARCH_HAVE_MEMPMOVEUPQ   1
#define LIBC_ARCH_HAVE_MEMPMOVEDOWNQ 1
#endif /* __x86_64__ */

/* memset() */
#define LIBC_ARCH_HAVE_MEMSET   1
#define LIBC_ARCH_HAVE_MEMSETW  1
#define LIBC_ARCH_HAVE_MEMSETL  1
#define LIBC_ARCH_HAVE_MEMPSET  1
#define LIBC_ARCH_HAVE_MEMPSETW 1
#define LIBC_ARCH_HAVE_MEMPSETL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMSETQ  1
#define LIBC_ARCH_HAVE_MEMPSETQ 1
#endif /* __x86_64__ */

/* bzero() */
#define LIBC_ARCH_HAVE_BZERO  1
#define LIBC_ARCH_HAVE_BZEROW 1
#define LIBC_ARCH_HAVE_BZEROL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_BZEROQ 1
#endif /* __x86_64__ */

/* memcmp() */
#define LIBC_ARCH_HAVE_MEMCMP  1
#define LIBC_ARCH_HAVE_MEMCMPW 1
#define LIBC_ARCH_HAVE_MEMCMPL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMCMPQ 1
#endif /* __x86_64__ */

/* bcmp() */
#define LIBC_ARCH_HAVE_BCMP  1
#define LIBC_ARCH_HAVE_BCMPW 1
#define LIBC_ARCH_HAVE_BCMPL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_BCMPQ 1
#endif /* __x86_64__ */

/* strlen() */
#define LIBC_ARCH_HAVE_STRLEN  1
#define LIBC_ARCH_HAVE_STREND  1
#define LIBC_ARCH_HAVE_STRNLEN 1
#define LIBC_ARCH_HAVE_STRNEND 1

/* c16slen() */
#define LIBC_ARCH_HAVE_C16SLEN  1
#define LIBC_ARCH_HAVE_C16SEND  1
#define LIBC_ARCH_HAVE_C16SNLEN 1
#define LIBC_ARCH_HAVE_C16SNEND 1

/* c32slen() */
#define LIBC_ARCH_HAVE_C32SLEN  1
#define LIBC_ARCH_HAVE_C32SEND  1
#define LIBC_ARCH_HAVE_C32SNLEN 1
#define LIBC_ARCH_HAVE_C32SNEND 1

/* Misc string/memory functions */
#define LIBC_ARCH_HAVE_RAWMEMCHR  1
#define LIBC_ARCH_HAVE_RAWMEMCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_RAWMEMRCHR  1
#define LIBC_ARCH_HAVE_RAWMEMRCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMRCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMRCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMCHR  1
#define LIBC_ARCH_HAVE_MEMCHRW 1
#define LIBC_ARCH_HAVE_MEMCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMRCHR  1
#define LIBC_ARCH_HAVE_MEMRCHRW 1
#define LIBC_ARCH_HAVE_MEMRCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMEND  1
#define LIBC_ARCH_HAVE_MEMENDW 1
#define LIBC_ARCH_HAVE_MEMENDL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMENDQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMREND  1
#define LIBC_ARCH_HAVE_MEMRENDW 1
#define LIBC_ARCH_HAVE_MEMRENDL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRENDQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMLEN  1
#define LIBC_ARCH_HAVE_MEMLENW 1
#define LIBC_ARCH_HAVE_MEMLENL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMLENQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMRLEN  1
#define LIBC_ARCH_HAVE_MEMRLENW 1
#define LIBC_ARCH_HAVE_MEMRLENL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRLENQ 1
#endif /* __x86_64__ */
#ifndef __KERNEL__
#define LIBC_ARCH_HAVE_RAWMEMXCHR  1
#define LIBC_ARCH_HAVE_RAWMEMXCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMXCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_RAWMEMRXCHR  1
#define LIBC_ARCH_HAVE_RAWMEMRXCHRW 1
#define LIBC_ARCH_HAVE_RAWMEMRXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_RAWMEMRXCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMXCHR  1
#define LIBC_ARCH_HAVE_MEMXCHRW 1
#define LIBC_ARCH_HAVE_MEMXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMXCHRQ 1
#endif /* __x86_64__ */
#define LIBC_ARCH_HAVE_MEMRXCHR  1
#define LIBC_ARCH_HAVE_MEMRXCHRW 1
#define LIBC_ARCH_HAVE_MEMRXCHRL 1
#ifdef __x86_64__
#define LIBC_ARCH_HAVE_MEMRXCHRQ 1
#endif /* __x86_64__ */
#endif /* !__KERNEL__ */

/* abort() */
#define LIBC_ARCH_HAVE_ABORT 1
#define LIBC_ARCH_HAVE_ABORTF 1


#ifndef __KERNEL__
/* void ASMCALL libc_sig_restore(void); */
#define LIBC_ARCH_HAVE_SIG_RESTORE 1

/* void *LIBCCALL libc_handle(void); */
#define LIBC_ARCH_HAVE_LIBC_HANDLE 1

/* ATTR_NORETURN void libc_sys_sigreturn(cpu, fpu, sigmask, sc_info); */
#define LIBC_ARCH_HAVE_LIBC_SYS_SIGRETURN 1

#ifdef __CC__
#include <bits/types.h>
#include <kos/asm/syscall.h>
#ifndef __NR_ksigreturn
#include <asm/syscalls.h>
#endif /* !__NR_ksigreturn */

DECL_BEGIN

#ifdef __x86_64__
#define LIBC_PTHREAD_MAIN_CC __ATTR_SYSVABI
#define LIBC_PTHREAD_MAIN_ARGS                \
	uintptr_t UNUSED(__ignored_Pdi),          \
	uintptr_t UNUSED(__ignored_Psi),          \
	struct pthread *__restrict me, /* %Pdx */ \
	uintptr_t UNUSED(__ignored_Pcx),          \
	void *(LIBCCALL *start)(void *arg) /* %r8 */
#else /* __x86_64__ */
#define LIBC_PTHREAD_MAIN_CC __FCALL
#define LIBC_PTHREAD_MAIN_ARGS                     \
	void *(LIBCCALL *start)(void *arg), /* %Pcx */ \
	struct pthread *__restrict me       /* %Pdx */
#endif /* !__x86_64__ */


struct ucpustate;
struct fpustate;
struct rpc_syscall_info;
struct sigset_with_size;

/* Need special handling for sys_sigreturn() */
LOCAL ATTR_NORETURN NONNULL((1)) void
NOTHROW(libc_sys_sigreturn)(struct ucpustate const *restore_cpu,
                            struct fpustate const *restore_fpu,
                            struct sigset_with_size const *restore_sigmask,
                            struct rpc_syscall_info const *restart_sc_info) {
#ifdef __x86_64__
	__register __syscall_ulong_t __r12 __asm__("%r12") = (__syscall_ulong_t)restore_sigmask;
	__register __syscall_ulong_t __r13 __asm__("%r13") = (__syscall_ulong_t)restart_sc_info;
	__asm__ __volatile__("movq %q1, %%rbp\n\t"
	                     "syscall"
	                     :
	                     : "a" (__NR_ksigreturn)
	                     , "g" (restore_cpu)
	                     , "b" (restore_fpu)
	                     , "r" (__r12)
	                     , "r" (__r13)
	                     : "memory");
#else /* __x86_64__ */
	__asm__ __volatile__("movl %k1, %%ebp\n\t"
	                     "call libc___i386_syscall"
	                     :
	                     : "a" (__NR_ksigreturn)
	                     , "g" (restore_cpu)
	                     , "b" (restore_fpu)
	                     , "S" (restore_sigmask)
	                     , "D" (restart_sc_info)
	                     : "memory", "cc");
#endif /* !__x86_64__ */
	__builtin_unreachable();
}


#ifdef __x86_64__
#define libc_handle libc_handle
LOCAL ATTR_CONST ATTR_RETNONNULL WUNUSED void *
NOTHROW(libc_handle)(void) {
	void *result;
	/* The  `current@tlsgd' symbol points to a `tls_index' structure,
	 * which consists of 16 bytes total, where the first 8 are filled
	 * with a module handle pointer by libdl.
	 * Note that this is a KOS-specific implementation detail. As far
	 * as the standard is concerned, libdl is allowed to make up some
	 * arbitrary module index for those 8 bytes, however KOS's  libdl
	 * simply re-uses  the regular  module handle  for this  purpose,
	 * meaning that we can simply (ab-)use that fact to quickly get a
	 * handle for libc itself. */
	__asm__("movq current@tlsgd(%%rip), %0" : "=r" (result));
	return result;
}
#endif /* __x86_64__ */

DECL_END
#endif /* __CC__ */

/* Arch-specific RTM optimizations do exist on x86
 * (in the form  of a  dedicated instruction  set) */
#define LIBC_ARCH_HAVE_RTM_BEGIN 1
#define LIBC_ARCH_HAVE_RTM_END   1
#define LIBC_ARCH_HAVE_RTM_ABORT 1
#define LIBC_ARCH_HAVE_RTM_TEST  1

#define LIBC_ARCH_HAVE_GETCONTEXT  1
#define LIBC_ARCH_HAVE_SETCONTEXT  1
#define LIBC_ARCH_HAVE_SWAPCONTEXT 1
#define LIBC_ARCH_HAVE_MAKECONTEXT 1

#define LIBC_ARCH_HAVE_CRTDBGBREAK 1
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_HYBRID_ARCH_I386_CONFIG_H */
