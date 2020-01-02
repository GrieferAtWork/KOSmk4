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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_SIGINFO_CONVERT_H
#define _I386_KOS_BITS_SIGINFO_CONVERT_H 1

#include <__stdinc.h>

#include <hybrid/__minmax.h>
#include <hybrid/host.h>

#include <bits/signum-values.h>

#include <libc/string.h>

#include "siginfo-struct32.h"
#include "siginfo-struct64.h"

#ifdef __CC__
__DECL_BEGIN

/* Convert between 32-bit and 64-bit siginfo_t structures */
#define siginfo32_to_siginfo32(self, result)                     \
	__libc_memcpy(__COMPILER_REQTYPE(siginfo32_t *, result),     \
	              __COMPILER_REQTYPE(siginfo32_t const *, self), \
	              sizeof(siginfo32_t))
#define siginfo64_to_siginfo64(self, result)                     \
	__libc_memcpy(__COMPILER_REQTYPE(siginfo64_t *, result),     \
	              __COMPILER_REQTYPE(siginfo64_t const *, self), \
	              sizeof(siginfo64_t))
__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(siginfo32_to_siginfo64)(siginfo32_t const *__restrict __self,
                                      siginfo64_t *__restrict __result) {
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
		__result->si_addr     = __self->si_addr;
		__result->si_addr_lsb = __self->si_addr_lsb;
		__result->si_lower    = __self->si_lower;
		__result->si_upper    = __self->si_upper;
		break;

	case __SIGPOLL:
		__result->si_band = __self->si_band;
		__result->si_fd   = __self->si_fd;
		break;

	case __SIGSYS:
		__result->si_call_addr = __self->si_call_addr;
		__result->si_syscall   = __self->si_syscall;
		__result->si_arch      = __self->si_arch;
		break;

	default:
		__libc_memcpy(__result->_si_data, __self->_si_data,
		              __hybrid_min(sizeof(__result->_si_data),
		                           sizeof(__self->_si_data)));
		break;
	}
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(siginfo64_to_siginfo32)(siginfo64_t const *__restrict __self,
                                      siginfo32_t *__restrict __result) {
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
		__result->si_addr     = __self->si_addr;
		__result->si_addr_lsb = __self->si_addr_lsb;
		__result->si_lower    = __self->si_lower;
		__result->si_upper    = __self->si_upper;
		break;

	case __SIGPOLL:
		__result->si_band = __self->si_band;
		__result->si_fd   = __self->si_fd;
		break;

	case __SIGSYS:
		__result->si_call_addr = __self->si_call_addr;
		__result->si_syscall   = __self->si_syscall;
		__result->si_arch      = __self->si_arch;
		break;

	default:
		__libc_memcpy(__result->_si_data, __self->_si_data,
		              __hybrid_min(sizeof(__result->_si_data),
		                           sizeof(__self->_si_data)));
		break;
	}
}

#ifdef __x86_64__
#define siginfo64_to_siginfo siginfo64_to_siginfo64
#define siginfo32_to_siginfo siginfo32_to_siginfo64
#define siginfo_to_siginfo32 siginfo64_to_siginfo32
#define siginfo_to_siginfo64 siginfo64_to_siginfo64
#else /* __x86_64__ */
#define siginfo64_to_siginfo siginfo64_to_siginfo32
#define siginfo32_to_siginfo siginfo32_to_siginfo32
#define siginfo_to_siginfo32 siginfo32_to_siginfo32
#define siginfo_to_siginfo64 siginfo32_to_siginfo64
#endif /* !__x86_64__ */


__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_SIGINFO_CONVERT_H */
