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
/*!replace_with_include <bits/os/siginfo-convert.h>*/
#ifndef _I386_KOS_BITS_OS_KOS_SIGINFO_CONVERT_H
#define _I386_KOS_BITS_OS_KOS_SIGINFO_CONVERT_H 1

/* File:
 *    <i386-kos/bits/os/kos/siginfo-convert.h>
 *
 * Definitions:
 *    - void siginfox32_to_siginfox32(struct __siginfox32_struct const *self, struct __siginfox32_struct *result);
 *    - void siginfox64_to_siginfox64(struct __siginfox64_struct const *self, struct __siginfox64_struct *result);
 *    - void siginfox32_to_siginfox64(struct __siginfox32_struct const *self, struct __siginfox64_struct *result);
 *    - void siginfox64_to_siginfox32(struct __siginfox64_struct const *self, struct __siginfox32_struct *result);
 *    - void siginfox64_to_siginfo(struct __siginfox32_struct const *self, struct __siginfo_struct *result);
 *    - void siginfox32_to_siginfo(struct __siginfox64_struct const *self, struct __siginfo_struct *result);
 *    - void siginfo_to_siginfox32(struct __siginfo_struct const *self, struct __siginfox64_struct *result);
 *    - void siginfo_to_siginfox64(struct __siginfo_struct const *self, struct __siginfox32_struct *result);
 */

#include <__stdinc.h>

#include <hybrid/__minmax.h>
#include <hybrid/host.h>

#include <asm/os/signal.h>

#include <libc/string.h>

#include "siginfo32.h"
#include "siginfo64.h"

#ifdef __CC__
__DECL_BEGIN

/* Convert between 32-bit and 64-bit siginfo_t structures */
#define siginfox32_to_siginfox32(self, result)                                  \
	__libc_memcpy(__COMPILER_REQTYPE(struct __siginfox32_struct *, result),     \
	              __COMPILER_REQTYPE(struct __siginfox32_struct const *, self), \
	              sizeof(struct __siginfox32_struct))
#define siginfox64_to_siginfox64(self, result)                                  \
	__libc_memcpy(__COMPILER_REQTYPE(struct __siginfox64_struct *, result),     \
	              __COMPILER_REQTYPE(struct __siginfox64_struct const *, self), \
	              sizeof(struct __siginfox64_struct))
__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(siginfox32_to_siginfox64)(struct __siginfox32_struct const *__restrict __self,
                                        struct __siginfox64_struct *__restrict __result) {
	__INT32_TYPE__ __signo;
	__result->si_signo = __signo = __self->si_signo;
	__result->si_errno = __self->si_errno;
	__result->si_code  = __self->si_code;
	switch (__signo) {

	case __SIGCHLD:
		__result->si_pid    = __self->si_pid;
		__result->si_uid    = __self->si_uid;
		__result->si_status = __self->si_status;
		__result->si_utime  = __self->si_utime;
		__result->si_stime  = __self->si_stime;
		break;

	case __SIGILL:
	case __SIGFPE:
	case __SIGSEGV:
	case __SIGBUS:
		__result->si_addr     = (__HYBRID_PTR64(void))__self->si_addr;
		__result->si_addr_lsb = __self->si_addr_lsb;
		__result->si_lower    = (__HYBRID_PTR64(void))__self->si_lower;
		__result->si_upper    = (__HYBRID_PTR64(void))__self->si_upper;
		break;

	case __SIGPOLL:
		__result->si_band = __self->si_band;
		__result->si_fd   = __self->si_fd;
		break;

	case __SIGSYS:
		__result->si_call_addr = (__HYBRID_PTR64(void))__self->si_call_addr;
		__result->si_syscall   = __self->si_syscall;
		__result->si_arch      = __self->si_arch;
		break;

	default:
		__libc_memcpy(__result->_si_data, __self->_si_data,
		              __hybrid_min_c(sizeof(__result->_si_data),
		                             sizeof(__self->_si_data)));
		break;
	}
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(siginfox64_to_siginfox32)(struct __siginfox64_struct const *__restrict __self,
                                        struct __siginfox32_struct *__restrict __result) {
	__INT32_TYPE__ __signo;
	__result->si_signo = __signo = __self->si_signo;
	__result->si_errno = __self->si_errno;
	__result->si_code  = __self->si_code;
	switch (__signo) {

	case __SIGCHLD:
		__result->si_pid    = __self->si_pid;
		__result->si_uid    = __self->si_uid;
		__result->si_status = __self->si_status;
		__result->si_utime  = (__UINT32_TYPE__)__self->si_utime;
		__result->si_stime  = (__UINT32_TYPE__)__self->si_stime;
		break;

	case __SIGILL:
	case __SIGFPE:
	case __SIGSEGV:
	case __SIGBUS:
		__result->si_addr     = (__HYBRID_PTR32(void))__self->si_addr;
		__result->si_addr_lsb = __self->si_addr_lsb;
		__result->si_lower    = (__HYBRID_PTR32(void))__self->si_lower;
		__result->si_upper    = (__HYBRID_PTR32(void))__self->si_upper;
		break;

	case __SIGPOLL:
		__result->si_band = __self->si_band;
		__result->si_fd   = __self->si_fd;
		break;

	case __SIGSYS:
		__result->si_call_addr = (__HYBRID_PTR32(void))__self->si_call_addr;
		__result->si_syscall   = __self->si_syscall;
		__result->si_arch      = __self->si_arch;
		break;

	default:
		__libc_memcpy(__result->_si_data, __self->_si_data,
		              __hybrid_min_c(sizeof(__result->_si_data),
		                             sizeof(__self->_si_data)));
		break;
	}
}

#ifdef __x86_64__
#define siginfox64_to_siginfo siginfox64_to_siginfox64
#define siginfox32_to_siginfo siginfox32_to_siginfox64
#define siginfo_to_siginfox32 siginfox64_to_siginfox32
#define siginfo_to_siginfox64 siginfox64_to_siginfox64
#else /* __x86_64__ */
#define siginfox64_to_siginfo siginfox64_to_siginfox32
#define siginfox32_to_siginfo siginfox32_to_siginfox32
#define siginfo_to_siginfox32 siginfox32_to_siginfox32
#define siginfo_to_siginfox64 siginfox32_to_siginfox64
#endif /* !__x86_64__ */


__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_OS_KOS_SIGINFO_CONVERT_H */
