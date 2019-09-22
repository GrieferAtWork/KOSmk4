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
#ifndef _I386_KOS_BITS_SIGINFO32_H
#define _I386_KOS_BITS_SIGINFO32_H 1

#include <__stdinc.h>
#include <__crt.h>            /* __CRT_CYG_PRIMARY */
#include <features.h>         /* __USE_KOS */
#include <hybrid/host.h>      /* __x86_64__ */
#include <hybrid/typecore.h>  /* __INT32_TYPE__ */
#include <hybrid/__pointer.h> /* __HYBRID_PTR32 */
#include <bits/sigval32.h>    /* union sigval32 */

__SYSDECL_BEGIN

#if !defined(__CRT_CYG_PRIMARY) && !defined(__x86_64__)
#define __SI_KERNEL_MAX_SIZE       __SI32_KERNEL_MAX_SIZE
#define __SI_USER_MAX_SIZE         __SI32_USER_MAX_SIZE
#define __SI_MAX_SIZE              __SI32_MAX_SIZE
#define __OFFSET_SIGINFO_SIGNO     __OFFSET_SIGINFO32_SIGNO
#define __OFFSET_SIGINFO_ERRNO     __OFFSET_SIGINFO32_ERRNO
#define __OFFSET_SIGINFO_CODE      __OFFSET_SIGINFO32_CODE
#define __OFFSET_SIGINFO_DATA      __OFFSET_SIGINFO32_DATA
#define __OFFSET_SIGINFO_PID       __OFFSET_SIGINFO32_PID
#define __OFFSET_SIGINFO_UID       __OFFSET_SIGINFO32_UID
#define __OFFSET_SIGINFO_TIMERID   __OFFSET_SIGINFO32_TIMERID
#define __OFFSET_SIGINFO_OVERRUN   __OFFSET_SIGINFO32_OVERRUN
#define __OFFSET_SIGINFO_VALUE     __OFFSET_SIGINFO32_VALUE
#define __OFFSET_SIGINFO_INT       __OFFSET_SIGINFO32_INT
#define __OFFSET_SIGINFO_PTR       __OFFSET_SIGINFO32_PTR
#define __OFFSET_SIGINFO_STATUS    __OFFSET_SIGINFO32_STATUS
#define __OFFSET_SIGINFO_UTIME     __OFFSET_SIGINFO32_UTIME
#define __OFFSET_SIGINFO_STIME     __OFFSET_SIGINFO32_STIME
#define __OFFSET_SIGINFO_ADDR      __OFFSET_SIGINFO32_ADDR
#define __OFFSET_SIGINFO_ADDR_LSB  __OFFSET_SIGINFO32_ADDR_LSB
#define __OFFSET_SIGINFO_LOWER     __OFFSET_SIGINFO32_LOWER
#define __OFFSET_SIGINFO_UPPER     __OFFSET_SIGINFO32_UPPER
#define __OFFSET_SIGINFO_BAND      __OFFSET_SIGINFO32_BAND
#define __OFFSET_SIGINFO_FD        __OFFSET_SIGINFO32_FD
#define __OFFSET_SIGINFO_CALL_ADDR __OFFSET_SIGINFO32_CALL_ADDR
#define __OFFSET_SIGINFO_SYSCALL   __OFFSET_SIGINFO32_SYSCALL
#define __OFFSET_SIGINFO_ARCH      __OFFSET_SIGINFO32_ARCH
#define __SIZEOF_SIGINFO           __SIZEOF_SIGINFO32
#define __siginfo32_struct         __siginfo_struct
#define siginfo32_t                siginfo_t
#endif /* !__CRT_CYG_PRIMARY && !__x86_64__ */


#define __SI32_KERNEL_MAX_SIZE 32
#define __SI32_USER_MAX_SIZE   128
#ifdef __KERNEL__
#define __SI32_MAX_SIZE        __SI32_KERNEL_MAX_SIZE
#else /* __KERNEL__ */
#define __SI32_MAX_SIZE        __SI32_USER_MAX_SIZE
#endif /* !__KERNEL__ */

#define __OFFSET_SIGINFO32_SIGNO     0
#define __OFFSET_SIGINFO32_ERRNO     4
#define __OFFSET_SIGINFO32_CODE      8
#define __OFFSET_SIGINFO32_DATA      12 /* [FIELD(_si_data, _sifields._data)] */
#define __OFFSET_SIGINFO32_PID       12 /* [FIELD(si_pid, __sig_si_pid, __cld_si_pid, _sifields._kill._si_pid, _sifields._rt._si_pid, _sifields._sigchld._si_pid)] */
#define __OFFSET_SIGINFO32_UID       16 /* [FIELD(si_uid, __sig_si_uid, __cld_si_uid, _sifields._kill._si_uid, _sifields._rt._si_uid, _sifields._sigchld._si_uid)] */
#define __OFFSET_SIGINFO32_TIMERID   12 /* [FIELD(si_timerid, _sifields._timer._si_tid)] */
#define __OFFSET_SIGINFO32_OVERRUN   16 /* [FIELD(si_overrun, _sifields._timer._si_overrun)] */
#define __OFFSET_SIGINFO32_VALUE     20 /* [FIELD(si_value, __sig_si_sigval, _sifields._rt.si_sigval, _sifields._timer.si_sigval)] */
#define __OFFSET_SIGINFO32_INT       20 /* [FIELD(si_int, _sifields._timer.si_sigval.sival_int)] */
#define __OFFSET_SIGINFO32_PTR       20 /* [FIELD(si_ptr, _sifields._timer.si_sigval.sival_ptr)] */
#define __OFFSET_SIGINFO32_STATUS    20 /* [FIELD(si_status, _sifields._sigchld._si_status)] */
#define __OFFSET_SIGINFO32_UTIME     24 /* [FIELD(si_utime, _sifields._sigchld._si_utime)] */
#define __OFFSET_SIGINFO32_STIME     28 /* [FIELD(si_stime, _sifields._sigchld._si_stime)] */
#define __OFFSET_SIGINFO32_ADDR      12 /* [FIELD(si_addr, _sifields._sigfault._si_addr)] */
#define __OFFSET_SIGINFO32_ADDR_LSB  16 /* [FIELD(si_addr_lsb, _sifields._sigfault._si_addr_lsb)] */
#define __OFFSET_SIGINFO32_LOWER     20 /* [FIELD(si_lower, _sifields._sigfault.si_addr_bnd._lower)] */
#define __OFFSET_SIGINFO32_UPPER     24 /* [FIELD(si_upper, _sifields._sigfault.si_addr_bnd._upper)] */
#define __OFFSET_SIGINFO32_BAND      12 /* [FIELD(si_band, _sifields._sigpoll._si_band)] */
#define __OFFSET_SIGINFO32_FD        16 /* [FIELD(si_fd, _sifields._sigpoll._si_fd)] */
#define __OFFSET_SIGINFO32_CALL_ADDR 12 /* [FIELD(si_call_addr, _sifields._sigsys._call_addr)] */
#define __OFFSET_SIGINFO32_SYSCALL   16 /* [FIELD(si_syscall, _sifields._sigsys._syscall)] */
#define __OFFSET_SIGINFO32_ARCH      20 /* [FIELD(si_arch, _sifields._sigsys._arch)] */
#define __SIZEOF_SIGINFO32           __SI32_MAX_SIZE


#ifdef __CC__
typedef struct __siginfo32_struct /*[NAME(siginfo32)][PREFIX(si_)]*/ {
	__INT32_TYPE__ si_signo; /* Signal number. */
	__INT32_TYPE__ si_errno; /* If non-zero, an errno value associated with this signal, as defined in <errno.h>. */
	__INT32_TYPE__ si_code;  /* Signal code. */
#if defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
	defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#if !defined(__USE_KOS) || defined(GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C)
	union {
#endif /* !__USE_KOS || GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C */
	union {
		__INT32_TYPE__ _si_data[(__SI32_MAX_SIZE / 4) - 3];
		struct { /* kill(). */
			__UINT32_TYPE__  si_pid; /* Sending process ID. */
			__UINT32_TYPE__  si_uid; /* Real user ID of sending process. */
		};
		struct { /* POSIX.1b timers. */
			__INT32_TYPE__ si_timerid; /* Timer ID. */
			__INT32_TYPE__ si_overrun; /* Overrun count. */
			union {
				union sigval32       si_value;   /* Signal value. */
				__INT32_TYPE__       si_int;
				__HYBRID_PTR32(void) si_ptr;
			};
		};
		struct { /* POSIX.1b signals. */
			__INT32_TYPE__   __sig_si_pid;    /* Sending process ID. */
			__UINT32_TYPE__  __sig_si_uid;    /* Real user ID of sending process. */
			union sigval32   __sig_si_sigval; /* Signal value. */
		};
		struct { /* SIGCHLD. */
			__INT32_TYPE__   __cld_si_pid;    /* Which child. */
			__UINT32_TYPE__  __cld_si_uid;    /* Real user ID of sending process. */
			__INT32_TYPE__     si_status;     /* Exit value or signal. */
			__UINT32_TYPE__    si_utime;
			__UINT32_TYPE__    si_stime;
		};
		struct { /* SIGILL, SIGFPE, SIGSEGV, SIGBUS. */
			__HYBRID_PTR32(void) si_addr;     /* Faulting insn/memory ref. */
			__INT16_TYPE__       si_addr_lsb; /* Valid LSB of the reported address. */
			__INT16_TYPE__     __si_pad2[1];
			__HYBRID_PTR32(void) si_lower;
			__HYBRID_PTR32(void) si_upper;
		};
		struct { /* SIGPOLL. */
			__LONG32_TYPE__  si_band; /* Band event for SIGPOLL. */
			__INT32_TYPE__   si_fd;
		};
		struct { /* SIGSYS. */
			__HYBRID_PTR32(void) si_call_addr; /* Calling user insn. */
			__INT32_TYPE__       si_syscall;   /* Triggering system call number. */
			__UINT32_TYPE__      si_arch;      /* AUDIT_ARCH_* of syscall. */
		};
	};
#endif /* Transparent struct/union */
#if !defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) || \
	!defined(__COMPILER_HAVE_TRANSPARENT_UNION) || \
	!defined(__USE_KOS) || defined(GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C)
	union {
		__INT32_TYPE__ _data[(__SI32_MAX_SIZE / 4) - 3];
		struct { /* kill(). */
			__INT32_TYPE__  _si_pid; /* Sending process ID. */
			__UINT32_TYPE__ _si_uid; /* Real user ID of sending process. */
		} _kill;
		struct { /* POSIX.1b timers. */
			__INT32_TYPE__ _si_tid;     /* Timer ID. */
			__INT32_TYPE__ _si_overrun; /* Overrun count. */
			union sigval32 si_sigval;   /* Signal value. */
		} _timer;
		struct { /* POSIX.1b signals. */
			__INT32_TYPE__  _si_pid;   /* Sending process ID. */
			__UINT32_TYPE__ _si_uid;   /* Real user ID of sending process. */
			union sigval32  si_sigval; /* Signal value. */
		} _rt;
		struct { /* SIGCHLD. */
			__INT32_TYPE__  _si_pid;    /* Which child. */
			__UINT32_TYPE__ _si_uid;    /* Real user ID of sending process. */
			__INT32_TYPE__  _si_status; /* Exit value or signal. */
			__UINT32_TYPE__ _si_utime;
			__UINT32_TYPE__ _si_stime;
		} _sigchld;
		struct { /* SIGILL, SIGFPE, SIGSEGV, SIGBUS. */
			__HYBRID_PTR32(void) _si_addr;     /* Faulting insn/memory ref. */
			__INT16_TYPE__       _si_addr_lsb; /* Valid LSB of the reported address. */
			__INT16_TYPE__      __si_pad2[1];
			struct {
				__HYBRID_PTR32(void) _lower;
				__HYBRID_PTR32(void) _upper;
			} si_addr_bnd;
		} _sigfault;
		struct { /* SIGPOLL. */
			__LONG32_TYPE__  _si_band; /* Band event for SIGPOLL. */
			__INT32_TYPE__   _si_fd;
		} _sigpoll;
		struct { /* SIGSYS. */
			__HYBRID_PTR32(void) _call_addr; /* Calling user insn. */
			__INT32_TYPE__       _syscall;   /* Triggering system call number. */
			__UINT32_TYPE__      _arch;      /* AUDIT_ARCH_* of syscall. */
		} _sigsys;
	} _sifields;
#endif /* ... */
#if defined(__COMPILER_HAVE_TRANSPARENT_STRUCT) && \
	defined(__COMPILER_HAVE_TRANSPARENT_UNION)
#if !defined(__USE_KOS) || defined(GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C)
	};
#endif /* !__USE_KOS || GUARD__VERIFY_ARCH_I386_ASSERT_OFFSETS_C */
#else
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
#endif /* !__COMPILER_HAVE_TRANSPARENT_UNION */
} siginfo32_t;
#endif /* __CC__ */


__SYSDECL_END

#endif /* !_I386_KOS_BITS_SIGINFO32_H */
