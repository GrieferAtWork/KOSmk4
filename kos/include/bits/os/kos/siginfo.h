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

#define __SI_USER_MAX_SIZE 128
#if __SIZEOF_POINTER__ > 4
#define __SI_KERNEL_MAX_SIZE 48
#else /* __SIZEOF_POINTER__ > 4 */
#define __SI_KERNEL_MAX_SIZE 32
#endif /* __SIZEOF_POINTER__ <= 4 */
#ifdef __KERNEL__
#define __SI_MAX_SIZE __SI_KERNEL_MAX_SIZE
#else /* __KERNEL__ */
#define __SI_MAX_SIZE __SI_USER_MAX_SIZE
#endif /* !__KERNEL__ */



#define __OFFSET_SIGINFO_SIGNO     0
#define __OFFSET_SIGINFO_ERRNO     4
#define __OFFSET_SIGINFO_CODE      8
#if __ALIGNOF_POINTER__ > 4
#define __OFFSET_SIGINFO_PID       16
#else /* __ALIGNOF_POINTER__ > 4 */
#define __OFFSET_SIGINFO_PID       12
#endif /* __ALIGNOF_POINTER__ <= 4 */
#define __OFFSET_SIGINFO_UID       (__OFFSET_SIGINFO_PID + __SIZEOF_PID_T__)
#define __OFFSET_SIGINFO_TIMERID   __OFFSET_SIGINFO_PID
#define __OFFSET_SIGINFO_OVERRUN   (__OFFSET_SIGINFO_PID + 4)
#define __OFFSET_SIGINFO_VALUE     (__OFFSET_SIGINFO_PID + 8)
#define __OFFSET_SIGINFO_INT       (__OFFSET_SIGINFO_PID + 8)
#define __OFFSET_SIGINFO_PTR       (__OFFSET_SIGINFO_PID + 8)
#define __OFFSET_SIGINFO_STATUS    (__OFFSET_SIGINFO_PID + __SIZEOF_PID_T__ + __SIZEOF_UID_T__)
#define __OFFSET_SIGINFO_UTIME     (__OFFSET_SIGINFO_PID + __SIZEOF_PID_T__ + __SIZEOF_UID_T__ + 4)
#define __OFFSET_SIGINFO_STIME     (__OFFSET_SIGINFO_PID + __SIZEOF_PID_T__ + __SIZEOF_UID_T__ + 4 + __SIZEOF_CLOCK_T__)
#define __OFFSET_SIGINFO_ADDR      __OFFSET_SIGINFO_PID
#define __OFFSET_SIGINFO_ADDR_LSB  (__OFFSET_SIGINFO_PID + __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_LOWER     (__OFFSET_SIGINFO_PID + 2 * __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_UPPER     (__OFFSET_SIGINFO_PID + 3 * __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_BAND      __OFFSET_SIGINFO_PID
#define __OFFSET_SIGINFO_FD        (__OFFSET_SIGINFO_PID + __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_CALL_ADDR __OFFSET_SIGINFO_PID
#define __OFFSET_SIGINFO_SYSCALL   (__OFFSET_SIGINFO_PID + __SIZEOF_POINTER__)
#define __OFFSET_SIGINFO_ARCH      (__OFFSET_SIGINFO_PID + __SIZEOF_POINTER__ + 4)
#define __SIZEOF_SIGINFO           __SI_MAX_SIZE
#define __ALIGNOF_SIGINFO          __ALIGNOF_POINTER__

#ifdef __CC__
__DECL_BEGIN

#ifdef _si_data
#define __PRIVATE_WAS_DEFINED__si_data
#endif /* _si_data */
#undef _si_data
#undef __sig_si_pid
#undef __sig_si_uid
#undef __sig_si_sigval
#undef __cld_si_pid
#undef __cld_si_uid
#undef si_pid
#undef si_uid
#undef si_timerid
#undef si_overrun
#undef si_status
#undef si_utime
#undef si_stime
#undef si_value
#undef si_int
#undef si_ptr
#undef si_addr
#undef si_addr_lsb
#undef si_lower
#undef si_upper
#undef si_band
#undef si_fd
#undef si_call_addr
#undef si_syscall
#undef si_arch

struct __siginfo_struct /*[NAME(siginfo)][PREFIX(si_)]*/ {
	__INT32_TYPE__ si_signo; /* Signal number. */
	__INT32_TYPE__ si_errno; /* If non-zero, an errno value associated with this signal, as defined in <errno.h>. */
	__INT32_TYPE__ si_code;  /* Signal code. */
#if __ALIGNOF_POINTER__ > 4
	__INT32_TYPE__ __si_pad; /* ... */
#endif /* __ALIGNOF_POINTER__ > 4 */
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	union {
		union {
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
#if __ALIGNOF_CLOCK_T__ > 4 && __ALIGNOF_POINTER__ <= 4
				__ATTR_ALIGNED(4) __clock_t si_utime;
				__ATTR_ALIGNED(4) __clock_t si_stime;
#else /* __ALIGNOF_CLOCK_T__ > 4 && __ALIGNOF_POINTER__ <= 4 */
				__clock_t          si_utime;
				__clock_t          si_stime;
#endif /* __ALIGNOF_CLOCK_T__ <= 4 || __ALIGNOF_POINTER__ > 4 */
			};
			struct { /* SIGILL, SIGFPE, SIGSEGV, SIGBUS. */
				void          *si_addr;     /* Faulting insn/memory ref. */
				__INT16_TYPE__ si_addr_lsb; /* Valid LSB of the reported address. */
				__INT16_TYPE__ __si_pad2[(sizeof(void *) - 2) / 2];
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
		union {
			__INTPTR_TYPE__ _pad[(__SI_MAX_SIZE - __OFFSET_SIGINFO_PID) / __SIZEOF_POINTER__];
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
#if __ALIGNOF_CLOCK_T__ > 4 && __ALIGNOF_POINTER__ <= 4
				__ATTR_ALIGNED(4) __clock_t si_utime;
				__ATTR_ALIGNED(4) __clock_t si_stime;
#else /* __ALIGNOF_CLOCK_T__ > 4 && __ALIGNOF_POINTER__ <= 4 */
				__clock_t      si_utime;
				__clock_t      si_stime;
#endif /* __ALIGNOF_CLOCK_T__ <= 4 || __ALIGNOF_POINTER__ > 4 */
			} _sigchld;
			struct { /* SIGILL, SIGFPE, SIGSEGV, SIGBUS. */
				void          *si_addr;     /* Faulting insn/memory ref. */
				__INT16_TYPE__ si_addr_lsb; /* Valid LSB of the reported address. */
				__INT16_TYPE__ __si_pad2[(sizeof(void *) - 2) / 2];
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
#if (defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
     defined(__COMPILER_HAVE_TRANSPARENT_UNION))
	};
#endif /* ... */
#if (defined(__PRIVATE_WAS_DEFINED__si_data) ||      \
     !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) || \
     !defined(__COMPILER_HAVE_TRANSPARENT_UNION))
#undef __PRIVATE_WAS_DEFINED__si_data
#define _si_data        _sifields._data
#define __sig_si_pid    _sifields._rt._si_pid
#define __sig_si_uid    _sifields._rt._si_uid
#define __sig_si_sigval _sifields._rt.si_sigval
#define __cld_si_pid    _sifields._sigchld._si_pid
#define __cld_si_uid    _sifields._sigchld._si_uid
#define si_pid          _sifields._kill._si_pid
#define si_uid          _sifields._kill._si_uid
#define si_timerid      _sifields._timer._si_tid
#define si_overrun      _sifields._timer._si_overrun
#define si_status       _sifields._sigchld._si_status
#define si_utime        _sifields._sigchld._si_utime
#define si_stime        _sifields._sigchld._si_stime
#define si_value        _sifields._rt.si_sigval
#define si_int          _sifields._rt.si_sigval.sival_int
#define si_ptr          _sifields._rt.si_sigval.sival_ptr
#define si_addr         _sifields._sigfault._si_addr
#define si_addr_lsb     _sifields._sigfault._si_addr_lsb
#define si_lower        _sifields._sigfault.si_addr_bnd._lower
#define si_upper        _sifields._sigfault.si_addr_bnd._upper
#define si_band         _sifields._sigpoll._si_band
#define si_fd           _sifields._sigpoll._si_fd
#define si_call_addr    _sifields._sigsys._call_addr
#define si_syscall      _sifields._sigsys._syscall
#define si_arch         _sifields._sigsys._arch
#endif /* ... */
};

__DECL_END
#endif /* __CC__ */


#endif /* !_BITS_OS_KOS_SIGINFO_H */
