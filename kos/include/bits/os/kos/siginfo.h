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
#ifndef _BITS_OS_KOS_SIGINFO_H
#define _BITS_OS_KOS_SIGINFO_H 1

/* File:
 *    <bits/os/kos/siginfo.h>
 *
 * Definitions:
 *    - struct __siginfo_struct { ... };
 *    - #define __SI_MAX_SIZE ...
 */

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/sigval.h>
#include <bits/types.h>

#define __SI_MAX_SIZE 128
#if __SIZEOF_POINTER__ > 4
#define __SI_PAD_SIZE ((__SI_MAX_SIZE / 4) - 4)
#else /* __SIZEOF_POINTER__ > 4 */
#define __SI_PAD_SIZE ((__SI_MAX_SIZE / 4) - 3)
#endif /* __SIZEOF_POINTER__ <= 4 */

#define __OFFSET_SIGINFO_SIGNO     0
#define __OFFSET_SIGINFO_ERRNO     4
#define __OFFSET_SIGINFO_CODE      (2 * 4)
#define __OFFSET_SIGINFO_PID       (4 * 4)
#define __OFFSET_SIGINFO_UID       (4 * 4 + __SIZEOF_PID_T__)
#define __OFFSET_SIGINFO_TIMERID   (4 * 4)
#define __OFFSET_SIGINFO_OVERRUN   (5 * 4)
#define __OFFSET_SIGINFO_VALUE     (6 * 4)
#define __OFFSET_SIGINFO_INT       (6 * 4)
#define __OFFSET_SIGINFO_PTR       (6 * 4)
#define __OFFSET_SIGINFO_STATUS    (4 * 4 + 2 * __SIZEOF_PID_T__)
#if __SIZEOF_CLOCK_T__ >= 8
#define __OFFSET_SIGINFO_UTIME     (4 * __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_STIME     (4 * __SIZEOF_POINTER__ + __SIZEOF_CLOCK_T__)
#else /* __SIZEOF_CLOCK_T__ >= 8 */
#define __OFFSET_SIGINFO_UTIME     (5 * 4 + 2 * __SIZEOF_PID_T__)
#define __OFFSET_SIGINFO_STIME     (5 * 4 + 2 * __SIZEOF_PID_T__ + __SIZEOF_CLOCK_T__)
#endif /* __SIZEOF_CLOCK_T__ < 8 */
#define __OFFSET_SIGINFO_ADDR      (4 * 4)
#define __OFFSET_SIGINFO_ADDR_LSB  (4 * 4 + __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_LOWER     (4 * 4 + 2 * __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_UPPER     (4 * 4 + 3 * __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_BAND      (4 * 4)
#define __OFFSET_SIGINFO_FD        (4 * 4 + __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_CALL_ADDR (4 * 4)
#define __OFFSET_SIGINFO_SYSCALL   (4 * 4 + __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_ARCH      (5 * 4 + __SIZEOF_POINTER__)
#define __SIZEOF_SIGINFO           __SI_MAX_SIZE


#ifdef __CC__
__DECL_BEGIN

struct __siginfo_struct /*[NAME(siginfo)][PREFIX(si_)]*/ {
	__INT32_TYPE__ si_signo; /* Signal number. */
	__INT32_TYPE__ si_errno; /* If non-zero, an errno value associated with this signal, as defined in <errno.h>. */
	__INT32_TYPE__ si_code;  /* Signal code. */
#if __SIZEOF_POINTER__ > 4
	__INT32_TYPE__ __si_pad; /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
#ifndef __USE_KOS_ALTERATIONS
	struct {
#endif /* !__USE_KOS_ALTERATIONS */
	union {
		__INT32_TYPE__ _pad[__SI_PAD_SIZE];
		struct { /* kill(). */
			__pid_t si_pid; /* Sending process ID. */
			__uid_t si_uid; /* Real user ID of sending process. */
		};
		struct { /* POSIX.1b timers. */
			__INT32_TYPE__ si_timerid; /* Timer ID. */
			__INT32_TYPE__ si_overrun; /* Overrun count. */
			union {
				union sigval   si_value;   /* Signal value. */
				__INT32_TYPE__ si_int;
				void          *si_ptr;
			};
		};
		struct { /* POSIX.1b signals. */
			__pid_t      __sig_si_pid;    /* Sending process ID. */
			__uid_t      __sig_si_uid;    /* Real user ID of sending process. */
			union sigval __sig_si_sigval; /* Signal value. */
		};
		struct { /* SIGCHLD. */
			__pid_t      __cld_si_pid;    /* Which child. */
			__uid_t      __cld_si_uid;    /* Real user ID of sending process. */
			__INT32_TYPE__     si_status; /* Exit value or signal. */
			__clock_t  si_utime;
			__clock_t  si_stime;
		};
		struct { /* SIGILL, SIGFPE, SIGSEGV, SIGBUS. */
			void          *si_addr;     /* Faulting insn/memory ref. */
			__INT16_TYPE__ si_addr_lsb; /* Valid LSB of the reported address. */
			__INT16_TYPE__ __si_pad2[(sizeof(void *)-2)/2];
			void          *si_lower;
			void          *si_upper;
		};
		struct { /* SIGPOLL. */
			__LONGPTR_TYPE__ si_band; /* Band event for SIGPOLL. */
			__INT32_TYPE__   si_fd;
		};
		struct { /* SIGSYS. */
			void           *si_call_addr; /* Calling user insn. */
			__INT32_TYPE__  si_syscall;   /* Triggering system call number. */
			__UINT32_TYPE__ si_arch;      /* AUDIT_ARCH_* of syscall. */
		};
	};
#endif /* Transparent struct/union */
#if (!defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) || \
     !defined(__COMPILER_HAVE_TRANSPARENT_UNION) ||  \
     !defined(__USE_KOS_ALTERATIONS))
	union {
		__INT32_TYPE__ _pad[__SI_PAD_SIZE];
		struct { /* kill(). */
			__pid_t si_pid; /* Sending process ID. */
			__uid_t si_uid; /* Real user ID of sending process. */
		} _kill;
		struct { /* POSIX.1b timers. */
			__INT32_TYPE__ si_tid;     /* Timer ID. */
			__INT32_TYPE__ si_overrun; /* Overrun count. */
			union sigval   si_sigval;  /* Signal value. */
		} _timer;
		struct { /* POSIX.1b signals. */
			__pid_t      si_pid;    /* Sending process ID. */
			__uid_t      si_uid;    /* Real user ID of sending process. */
			union sigval si_sigval; /* Signal value. */
		} _rt;
		struct { /* SIGCHLD. */
			__pid_t        si_pid;    /* Which child. */
			__uid_t        si_uid;    /* Real user ID of sending process. */
			__INT32_TYPE__ si_status; /* Exit value or signal. */
			__clock_t      si_utime;
			__clock_t      si_stime;
		} _sigchld;
		struct { /* SIGILL, SIGFPE, SIGSEGV, SIGBUS. */
			void          *si_addr;     /* Faulting insn/memory ref. */
			__INT16_TYPE__ si_addr_lsb; /* Valid LSB of the reported address. */
			__INT16_TYPE__ __si_pad2[(sizeof(void *)-2)/2];
			struct {
				void *_lower;
				void *_upper;
			} si_addr_bnd;
		} _sigfault;
		struct { /* SIGPOLL. */
			__LONGPTR_TYPE__ si_band; /* Band event for SIGPOLL. */
			__INT32_TYPE__   si_fd;
		} _sigpoll;
		struct { /* SIGSYS. */
			void           *_call_addr; /* Calling user insn. */
			__INT32_TYPE__  _syscall;   /* Triggering system call number. */
			__UINT32_TYPE__ _arch;      /* AUDIT_ARCH_* of syscall. */
		} _sigsys;
	} _sifields;
#endif /* ... */
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
#ifndef __USE_KOS_ALTERATIONS
	};
#endif /* !__USE_KOS_ALTERATIONS */
#else
#define si_pid       _sifields._kill.si_pid
#define si_uid       _sifields._kill.si_uid
#define si_timerid   _sifields._timer.si_tid
#define si_overrun   _sifields._timer.si_overrun
#define si_status    _sifields._sigchld.si_status
#define si_utime     _sifields._sigchld.si_utime
#define si_stime     _sifields._sigchld.si_stime
#define si_value     _sifields._rt.si_sigval
#define si_int       _sifields._rt.si_sigval.sival_int
#define si_ptr       _sifields._rt.si_sigval.sival_ptr
#define si_addr      _sifields._sigfault.si_addr
#define si_addr_lsb  _sifields._sigfault.si_addr_lsb
#define si_lower     _sifields._sigfault.si_addr_bnd._lower
#define si_upper     _sifields._sigfault.si_addr_bnd._upper
#define si_band      _sifields._sigpoll.si_band
#define si_fd        _sifields._sigpoll.si_fd
#define si_call_addr _sifields._sigsys._call_addr
#define si_syscall   _sifields._sigsys._syscall
#define si_arch      _sifields._sigsys._arch
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_SIGINFO_H */
