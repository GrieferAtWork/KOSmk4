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
#ifndef _BITS_OS_KOS_SIGNALFD_SIGINFO_H
#define _BITS_OS_KOS_SIGNALFD_SIGINFO_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

struct signalfd_siginfo {
	__uint32_t ssi_signo;   /* s.a. `siginfo_t::si_signo' */
	__int32_t  ssi_errno;   /* s.a. `siginfo_t::si_errno' */
	__int32_t  ssi_code;    /* s.a. `siginfo_t::si_code' */
	__uint32_t ssi_pid;     /* s.a. `siginfo_t::si_pid' */
	__uint32_t ssi_uid;     /* s.a. `siginfo_t::si_uid' */
	__int32_t  ssi_fd;      /* s.a. `siginfo_t::si_fd' */
	__uint32_t ssi_tid;     /* s.a. `siginfo_t::si_timerid' */
	__uint32_t ssi_band;    /* s.a. `siginfo_t::si_band' */
	__uint32_t ssi_overrun; /* s.a. `siginfo_t::si_overrun' */
	__uint32_t ssi_trapno;  /* ??? */
	__int32_t  ssi_status;  /* s.a. `siginfo_t::si_status' */
	__int32_t  ssi_int;     /* s.a. `siginfo_t::si_int' */
	__uint64_t ssi_ptr;     /* s.a. `siginfo_t::si_ptr' */
	__uint64_t ssi_utime;   /* s.a. `siginfo_t::si_utime' */
	__uint64_t ssi_stime;   /* s.a. `siginfo_t::si_stime' */
	__uint64_t ssi_addr;    /* s.a. `siginfo_t::si_addr' */
	__uint8_t  __pad[48];
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_SIGNALFD_SIGINFO_H */
