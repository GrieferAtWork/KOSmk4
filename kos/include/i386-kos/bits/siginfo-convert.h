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
#ifndef _I386_KOS_BITS_SIGINFO_CONVERT_H
#define _I386_KOS_BITS_SIGINFO_CONVERT_H 1

#include <__stdinc.h>
#include "siginfo-struct32.h"
#include "siginfo-struct64.h"
#include <bits/signum-values.h>
#include <libc/string.h>
#include <hybrid/__minmax.h>

__SYSDECL_BEGIN

/* Convert between 32-bit and 64-bit siginfo_t structures */
#ifdef __CC__

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(siginfo32_to_siginfo64)(siginfo64_t *__restrict dst,
                                      siginfo32_t const *__restrict src) {
	__INT32_TYPE__ signo;
	dst->si_signo = signo = src->si_signo;
	dst->si_errno = src->si_errno;
	dst->si_code  = src->si_code;
	switch (signo) {

	case __SIGCHLD:
		dst->si_pid    = src->si_pid;
		dst->si_uid    = src->si_uid;
		dst->si_status = src->si_status;
		dst->si_utime  = src->si_utime;
		dst->si_stime  = src->si_stime;
		break;

	case __SIGILL:
	case __SIGFPE:
	case __SIGSEGV:
	case __SIGBUS:
		dst->si_addr     = src->si_addr;
		dst->si_addr_lsb = src->si_addr_lsb;
		dst->si_lower    = src->si_lower;
		dst->si_upper    = src->si_upper;
		break;

	case __SIGPOLL:
		dst->si_band = dst->si_band;
		dst->si_fd   = dst->si_fd;
		break;

	case __SIGSYS:
		dst->si_call_addr = src->si_call_addr;
		dst->si_syscall   = src->si_syscall;
		dst->si_arch      = src->si_arch;
		break;

	default:
		__libc_memcpy(dst->_si_data, src->_si_data,
		              __hybrid_min(sizeof(dst->_si_data),
		                           sizeof(src->_si_data)));
		break;
	}
}

__LOCAL __ATTR_LEAF __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(siginfo64_to_siginfo32)(siginfo32_t *__restrict dst,
                                      siginfo64_t const *__restrict src) {
	__INT32_TYPE__ signo;
	dst->si_signo = signo = src->si_signo;
	dst->si_errno = src->si_errno;
	dst->si_code  = src->si_code;
	switch (signo) {

	case __SIGCHLD:
		dst->si_pid    = src->si_pid;
		dst->si_uid    = src->si_uid;
		dst->si_status = src->si_status;
		dst->si_utime  = (__UINT32_TYPE__)src->si_utime;
		dst->si_stime  = (__UINT32_TYPE__)src->si_stime;
		break;

	case __SIGILL:
	case __SIGFPE:
	case __SIGSEGV:
	case __SIGBUS:
		dst->si_addr     = src->si_addr;
		dst->si_addr_lsb = src->si_addr_lsb;
		dst->si_lower    = src->si_lower;
		dst->si_upper    = src->si_upper;
		break;

	case __SIGPOLL:
		dst->si_band = dst->si_band;
		dst->si_fd   = dst->si_fd;
		break;

	case __SIGSYS:
		dst->si_call_addr = src->si_call_addr;
		dst->si_syscall   = src->si_syscall;
		dst->si_arch      = src->si_arch;
		break;

	default:
		__libc_memcpy(dst->_si_data, src->_si_data,
		              __hybrid_min(sizeof(dst->_si_data),
		                           sizeof(src->_si_data)));
		break;
	}
}

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BITS_SIGINFO_CONVERT_H */
