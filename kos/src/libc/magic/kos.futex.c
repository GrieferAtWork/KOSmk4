/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(lfutex_t = __uintptr_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]
%[default:section(".text.crt{|.dos}.sched.futex")]
%[default:nodos]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/asm/futex.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <bits/os/timespec.h>
)]%[insert:prefix(
#include <hybrid/__atomic.h>
)]%{
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __lfutex_t_defined
#define __lfutex_t_defined
typedef __uintptr_t lfutex_t;
#endif /* !__lfutex_t_defined */

/*
 * `lfutex() and select()' (or `poll()')
 *
 * On  KOS,  it  is  fairly  simple  to  use  any  of  the  available
 * `LFUTEX_WAIT_*' operations in conjunction with a call to `poll()'.
 *
 * Other than this, there exists 2  ways of polling for futex  objects
 * in parallel to polling any other  type of file descriptor, as  well
 * polling  for sleeping child processes (either through use of a file
 * descriptor created using `pidfd_open(pid) (similar to `signalfd()',
 * but  may be used to wait for processes  in a way that is similar to
 * the waitpid() function)', or through use of `kpoll()').
 *
 * - Using the `kpoll()' system call, which  allows for the use of  poll
 *   descriptors that describe any kind of user-space-visible handle  on
 *   which  a given process  can wait (a  regular `fd_t' (using `POLLIN|
 *   POLLOUT|...'),  a  `pid_t'  (using `waitpid()'),  or  an `lfutex_t'
 *   (using any of  the `LFUTEX_WAIT_*' operators  that are  available))
 *   When targeting KOS specifically, this is the preferred way of going
 *   about passively  waiting for  a futex,  as it  doesn't require  the
 *   creation of any additional kernel-space object.
 *   TODO: Implement the `kpoll()' system call
 *
 * - Using the regular `poll()' / `select()' family of system calls, after
 *   having created a futexfd handle.
 *
 */


}


// TODO: C++ syntax sugar
//extern "C++" {
//class futex_t;
//__NAMESPACE_INT_BEGIN
//class    __LFutexOpEquals;
//class __LFutexOpNotEquals;
//class     __LFutexOpAbove;
//class     __LFutexOpBelow;
//class __LFutexOpAboveEqual;
//class __LFutexOpBelowEqual;
//class    __LFutexOpBitmask;
//class __LFutexOpNotBitmask;
//class __LFutexOpAnd;
//__NAMESPACE_INT_END
//
//struct timespec;
//
//__FORCELOCAL  int __NOTHROW_NCX(__LIBCCALL  waitif)(__NAMESPACE_INT_SYM __LFutexOpEquals const  &__expr, struct timespec  const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpNotEquals const &__expr, struct timespec const *timeout  __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL  waitif)(__NAMESPACE_INT_SYM __LFutexOpAbove  const &__expr,  struct timespec  const *timeout  __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL  waitif)(__NAMESPACE_INT_SYM __LFutexOpBelow  const &__expr,  struct timespec  const *timeout  __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpAboveEqual const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpBelowEqual const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL  int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM  __LFutexOpBitmask const &__expr, struct  timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpNotBitmask const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpAnd const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//
//__NAMESPACE_INT_BEGIN
//#define __DEFINE_BINARY_WRAPPER(name, op) \
//	class name {                                                                   \
//		friend int ::waitif(name const &__expr, struct ::timespec const *timeout); \
//	private:                                                                       \
//		lfutex_t const &__m_futex;                                                 \
//		__syscall_ulong_t __m_val;                                                 \
//	public:                                                                        \
//		__CXX_CLASSMEMBER name(lfutex_t const &__futex,                            \
//		                       __syscall_ulong_t __val) __CXX_NOEXCEPT             \
//		    : __m_futex(__futex)                                                   \
//		    , __m_val(__val) {}                                                    \
//		__CXX_CLASSMEMBER operator bool() const __CXX_NOEXCEPT {                   \
//			return __m_futex op __m_val;                                           \
//		}                                                                          \
//		__CXX_CLASSMEMBER bool operator!() const __CXX_NOEXCEPT {                  \
//			return !(__m_futex op __m_val);                                        \
//		}                                                                          \
//	}
//#define __DEFINE_TRINARY_WRAPPER(name, op1, op2) \
//	class name {                                                                   \
//		friend int ::waitif(name const &__expr, struct ::timespec const *timeout); \
//	private:                                                                       \
//		lfutex_t const &__m_futex;                                                 \
//		__syscall_ulong_t __m_val;                                                 \
//		__syscall_ulong_t __m_val2;                                                \
//	public:                                                                        \
//		__CXX_CLASSMEMBER name(lfutex_t const &__futex,                            \
//		                       __syscall_ulong_t __val,                            \
//		                       __syscall_ulong_t __val2) __CXX_NOEXCEPT            \
//		    : __m_futex(__futex)                                                   \
//		    , __m_val(__val)                                                       \
//		    , __m_val2(__val2) {}                                                  \
//		__CXX_CLASSMEMBER operator bool() const __CXX_NOEXCEPT {                   \
//			return (__m_futex op1 __m_val)op2 __m_val2;                            \
//		}                                                                          \
//		__CXX_CLASSMEMBER bool operator!() const __CXX_NOEXCEPT {                  \
//			return !((__m_futex op1 __m_val)op2 __m_val2);                         \
//		}                                                                          \
//	}
//__DEFINE_BINARY_WRAPPER(__LFutexOpEquals,         ==);
//__DEFINE_BINARY_WRAPPER(__LFutexOpNotEquals,      !=);
//__DEFINE_BINARY_WRAPPER(__LFutexOpAbove,           >);
//__DEFINE_BINARY_WRAPPER(__LFutexOpBelow,           <);
//__DEFINE_BINARY_WRAPPER(__LFutexOpAboveEqual,     >=);
//__DEFINE_BINARY_WRAPPER(__LFutexOpBelowEqual,     <=);
//__DEFINE_TRINARY_WRAPPER(__LFutexOpBitmask,  &,   ==);
//__DEFINE_TRINARY_WRAPPER(__LFutexOpNotBitmask, &, !=);
//#undef __DEFINE_TRINARY_WRAPPER
//#undef __DEFINE_BINARY_WRAPPER
//
//class __LFutexOpAnd {
//	friend int ::waitif(__LFutexOpAnd const &__expr, struct ::timespec const *timeout);
//private:
//	lfutex_t const &__m_futex;
//	__syscall_ulong_t __m_val;
//public:
//	__CXX_CLASSMEMBER __LFutexOpAnd(lfutex_t const &__futex, __syscall_ulong_t __val) __CXX_NOEXCEPT
//	    : __m_futex(__futex)
//	    , __m_val(__val) {}
//	__CXX_CLASSMEMBER operator bool() const __CXX_NOEXCEPT {
//		return (__m_futex & __m_val) != 0;
//	}
//	__CXX_CLASSMEMBER bool operator!() const __CXX_NOEXCEPT {
//		return (__m_futex & __m_val) == 0;
//	}
//	__CXX_CLASSMEMBER __LFutexOpBitmask operator == (__syscall_ulong_t __setmask) const __CXX_NOEXCEPT {
//		return __LFutexOpBitmask(__m_futex, __m_val, __setmask);
//	}
//	__CXX_CLASSMEMBER __LFutexOpNotBitmask operator != (__syscall_ulong_t __setmask) const __CXX_NOEXCEPT {
//		return __LFutexOpNotBitmask(__m_futex, __m_val, __setmask);
//	}
//};
//
//__NAMESPACE_INT_END
//class   futex_t   {
//private:
//	lfutex_t __m_futex; /* The underlying futex. */
//public:
//	__CXX_CLASSMEMBER operator lfutex_t() const __CXX_NOEXCEPT {
//		return __m_futex;
//	}
//	__CXX_CLASSMEMBER __NAMESPACE_INT_SYM __LFutexOpEquals operator==(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
//		return __NAMESPACE_INT_SYM __LFutexOpEquals(__m_futex, __val);
//	}
//	__CXX_CLASSMEMBER __NAMESPACE_INT_SYM __LFutexOpNotEquals operator!=(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
//		return __NAMESPACE_INT_SYM __LFutexOpNotEquals(__m_futex, __val);
//	}
//	__CXX_CLASSMEMBER __NAMESPACE_INT_SYM __LFutexOpBelow operator<(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
//		return __NAMESPACE_INT_SYM __LFutexOpBelow(__m_futex, __val);
//	}
//	__CXX_CLASSMEMBER __NAMESPACE_INT_SYM __LFutexOpAbove operator>(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
//		return __NAMESPACE_INT_SYM __LFutexOpAbove(__m_futex, __val);
//	}
//	__CXX_CLASSMEMBER __NAMESPACE_INT_SYM __LFutexOpBelowEqual operator<=(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
//		return __NAMESPACE_INT_SYM __LFutexOpBelowEqual(__m_futex, __val);
//	}
//	__CXX_CLASSMEMBER __NAMESPACE_INT_SYM __LFutexOpAboveEqual operator>=(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
//		return __NAMESPACE_INT_SYM __LFutexOpAboveEqual(__m_futex, __val);
//	}
//	__CXX_CLASSMEMBER __NAMESPACE_INT_SYM __LFutexOpAnd operator&(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
//		return __NAMESPACE_INT_SYM __LFutexOpAnd(__m_futex, __val);
//	}
//};
//
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpEquals const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_equal((lfutex_t *)&__expr.__m_futex, __expr.__m_val);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpNotEquals const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_notequal((lfutex_t *)&__expr.__m_futex, __expr.__m_val);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpAbove const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_above((lfutex_t *)&__expr.__m_futex, __expr.__m_val);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpBelow const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_below((lfutex_t *)&__expr.__m_futex, __expr.__m_val);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpAboveEqual const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_aboveequal((lfutex_t *)&__expr.__m_futex, __expr.__m_val);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpBelowEqual const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_belowequal((lfutex_t *)&__expr.__m_futex, __expr.__m_val);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpBitmask const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_exactbits((lfutex_t *)&__expr.__m_futex, __expr.__m_val, __expr.__m_val2);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpNotBitmask const &__expr, struct timespec const *timeout) {
//	return futex_waituntil_exactbits((lfutex_t *)&__expr.__m_futex, __expr.__m_val, __expr.__m_val2);
//}
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpAnd const &__expr, struct timespec const *timeout) {
//	return futex_waitwhile_anybit((lfutex_t *)&__expr.__m_futex, __expr.__m_val);
//}
//
//}


[[cp, doc_alias("lfutex"), ignore, vartypes($uintptr_t, $uintptr_t)]]
[[decl_include("<bits/types.h>"), nocrt, alias("lfutex")]]
$ssize_t lfutex32([[nonnull]] lfutex_t *uaddr, $syscall_ulong_t futex_op,
                  lfutex_t val, /*struct timespec const *timeout, lfutex_t val2*/...);


@@>> lfutex(2)
@@Provide the bottom-most API for implementing user-space synchronization on KOS
@@@param: futex_op: One of:
@@   - LFUTEX_WAKE:                (lfutex_t *uaddr, LFUTEX_WAKE, size_t count)
@@   - LFUTEX_WAKEMASK:            (lfutex_t *uaddr, LFUTEX_WAKEMASK, size_t count, lfutex_t mask_and, lfutex_t mask_or)
@@   - LFUTEX_WAIT_WHILE:          (lfutex_t *uaddr, LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_UNTIL:          (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_ABOVE:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_BELOW:    (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
@@   - LFUTEX_WAIT_UNTIL_BITMASK:  (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
@@   - LFUTEX_WAIT_WHILE_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
@@   - LFUTEX_WAIT_UNTIL_EX:       (lfutex_t *uaddr, LFUTEX_WAIT_UNTIL_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
@@   - LFUTEX_WAIT_WHILE_ABOVE_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_ABOVE_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
@@   - LFUTEX_WAIT_WHILE_BELOW_EX: (lfutex_t *uaddr, LFUTEX_WAIT_WHILE_BELOW_EX, void const *rhs, struct timespec const *timeout, size_t num_bytes)
@@@param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
@@@return: * : Depending on `futex_op'
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINVAL:    The given `futex_op' is invalid
@@@return: -1:EINTR:     A blocking futex-wait operation was interrupted
@@@return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out
[[cp, vartypes(void *, $uintptr_t), decl_include("<bits/types.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("lfutex")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("lfutex64")]]
[[impl_include("<bits/os/timespec.h>")]]
[[userimpl, requires($has_function(lfutex32) || $has_function(lfutex64))]]
$ssize_t lfutex([[nonnull]] lfutex_t *uaddr, $syscall_ulong_t futex_op,
                lfutex_t val, /*struct timespec const *timeout, lfutex_t val2*/...) {
@@pp_if $has_function(lfutex32)@@
	va_list args;
	lfutex_t val2;
	struct timespec32 tms32;
	struct timespec64 const *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 const *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutex32(uaddr, futex_op, val, (struct timespec32 *)NULL, val2);
	tms32.tv_sec  = (__time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return lfutex32(uaddr, futex_op, val, &tms32, val2);
@@pp_else@@
	va_list args;
	lfutex_t val2;
	struct timespec64 tms64;
	struct timespec32 *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec32 *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutex64(uaddr, futex_op, val, (struct timespec64 const *)NULL, val2);
	tms64.tv_sec  = (__time64_t)timeout->tv_sec;
	tms64.tv_nsec = timeout->tv_nsec;
	return lfutex64(uaddr, futex_op, val, &tms64, val2);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[cp, vartypes(void *, $uintptr_t), decl_include("<bits/types.h>")]]
[[preferred_time64_variant_of(lfutex), doc_alias("lfutex")]]
[[userimpl, requires_function(lfutex32)]]
[[impl_include("<bits/os/timespec.h>")]]
$ssize_t lfutex64([[nonnull]] lfutex_t *uaddr, $syscall_ulong_t futex_op,
                  lfutex_t val, /*struct timespec64 const *timeout, lfutex_t val2*/...) {
	va_list args;
	lfutex_t val2;
	struct timespec32 tms32;
	struct timespec64 const *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 const *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutex32(uaddr, futex_op, val, (struct timespec32 *)NULL, val2);
	tms32.tv_sec  = (__time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return lfutex32(uaddr, futex_op, val, &tms32, val2);
}
%#endif /* __USE_TIME64 */

@@Wake up to `MAX_WAKE' threads waiting for `*UADDR'
@@@return: * : The number of woken threads
@@@return: -1:EFAULT: A faulty pointer was given
[[decl_include("<bits/types.h>"), impl_include("<kos/asm/futex.h>")]]
[[userimpl, requires_function(lfutex64)]]
$ssize_t futex_wake([[nonnull]] lfutex_t *uaddr, $size_t max_wake) {
	return lfutex64(uaddr, @LFUTEX_WAKE@, max_wake);
}

@@Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
@@@return: * : The number of woken threads
@@@return: -1:EFAULT: A faulty pointer was given
[[decl_include("<bits/types.h>")]]
[[userimpl, requires($has_function(futex_wake))]]
$ssize_t futex_wakeall([[nonnull]] lfutex_t *uaddr) {
	return futex_wake(uaddr, ($size_t)-1);
}

@@Similar to `futex_wake()', however once there are no more threads that
@@can be awoken, perform the following operation: `*uaddr = (*uaddr & mask_and) | mask_or'
@@@return: * : The number of woken threads
@@@return: -1:EFAULT: A faulty pointer was given
[[decl_include("<bits/types.h>")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex64)]]
$ssize_t futex_wakemask([[nonnull]] lfutex_t *uaddr, $size_t max_wake,
                        lfutex_t mask_and, lfutex_t mask_or) {
	return lfutex64(uaddr, @LFUTEX_WAKEMASK@, max_wake, mask_and, mask_or);
}


@@Wait if `*uaddr == equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex64)]]
int futex_waitwhile([[in]] lfutex_t *uaddr, lfutex_t equal_to_value) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, (struct timespec64 const *)NULL);
}

@@Wait if `*uaddr != not_equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex64)]]
int futex_waituntil([[in]] lfutex_t *uaddr, lfutex_t not_equal_to_value) {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, (struct timespec64 const *)NULL);
}

futex_waitwhile_equal(*) = futex_waitwhile;
futex_waitwhile_notequal(*) = futex_waituntil;

@@Wait if `*uaddr > above_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>")]]
[[userimpl, requires_function(lfutex64)]]
int futex_waitwhile_above([[in]] lfutex_t *uaddr, lfutex_t above_value) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, (struct timespec64 const *)NULL);
}

@@Wait if `*uaddr < below_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>")]]
[[userimpl, requires_function(lfutex64)]]
int futex_waitwhile_below([[in]] lfutex_t *uaddr, lfutex_t below_value) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, (struct timespec64 const *)NULL);
}

@@Wait if `*uaddr >= above_or_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>", "<hybrid/__assert.h>")]]
[[userimpl, requires_function(lfutex64)]]
int futex_waitwhile_aboveequal([[in]] lfutex_t *uaddr, lfutex_t above_or_equal_value) {
	__hybrid_assert(above_or_equal_value != 0);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_or_equal_value - 1, (struct timespec64 const *)NULL);
}

@@Wait if `*uaddr <= below_or_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>", "<hybrid/__assert.h>")]]
[[userimpl, requires_function(lfutex64)]]
int futex_waitwhile_belowequal([[in]] lfutex_t *uaddr, lfutex_t below_or_equal_value) {
	__hybrid_assert(above_or_equal_value != (lfutex_t)-1);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_or_equal_value + 1, (struct timespec64 const *)NULL);
}

@@Wait if `(*uaddr & bitmask) == setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, userimpl, requires_function(lfutex64)]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>")]]
int futex_waitwhile_exactbits([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, (struct timespec64 const *)NULL, setmask);
}

@@Wait if `(*uaddr & bitmask) != setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, userimpl, requires_function(lfutex64)]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>")]]
int futex_waituntil_exactbits([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask) {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, (struct timespec64 const *)NULL, setmask);
}

@@Wait if `(*uaddr & bitmask) != 0'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, userimpl, requires_function(lfutex64)]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>")]]
int futex_waitwhile_anybit([[in]] lfutex_t *uaddr, lfutex_t bitmask) {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, (struct timespec64 const *)NULL, 0);
}

@@Wait if `(*uaddr & bitmask) == bitmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, userimpl, requires_function(lfutex64)]]
[[decl_include("<bits/types.h>")]]
[[impl_include("<bits/os/timespec.h>", "<kos/asm/futex.h>")]]
int futex_waitwhile_allbits([[in]] lfutex_t *uaddr, lfutex_t bitmask) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, (struct timespec64 const *)NULL, bitmask);
}












@@Wait if `*uaddr == equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile64")]]
[[impl_include("<kos/asm/futex.h>")]]
[[userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile([[in]] lfutex_t *uaddr, lfutex_t equal_to_value,
                         [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, rel_timeout);
}

@@Wait if `*uaddr != not_equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[[cp, decl_include("<bits/types.h>"), decl_include("<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaituntil")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaituntil64")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaituntil([[in]] lfutex_t *uaddr, lfutex_t not_equal_to_value,
                         [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, rel_timeout);
}

futex_timedwaitwhile_equal(*) = futex_timedwaitwhile;
futex_timedwaitwhile_notequal(*) = futex_timedwaituntil;

@@Wait if `*uaddr > above_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_above")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_above64")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile_above([[in]] lfutex_t *uaddr, lfutex_t above_value,
                               [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, rel_timeout);
}

@@Wait if `*uaddr < below_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_below")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_below64")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile_below([[in]] lfutex_t *uaddr, lfutex_t below_value,
                               [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, rel_timeout);
}

@@Wait if `*uaddr >= above_or_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_aboveequal64")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_aboveequal")]]
[[impl_include("<kos/asm/futex.h>", "<hybrid/__assert.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile_aboveequal([[in]] lfutex_t *uaddr, lfutex_t above_or_equal_value,
                                    [[in_opt]] struct timespec const *rel_timeout) {
	__hybrid_assert(above_or_equal_value != 0);
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_or_equal_value - 1, rel_timeout);
}

@@Wait if `*uaddr <= below_or_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_belowequal")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_belowequal64")]]
[[impl_include("<kos/asm/futex.h>", "<hybrid/__assert.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile_belowequal([[in]] lfutex_t *uaddr, lfutex_t below_or_equal_value,
                                    [[in_opt]] struct timespec const *rel_timeout) {
	__hybrid_assert(above_or_equal_value != (lfutex_t)-1);
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_or_equal_value + 1, rel_timeout);
}

@@Wait if `(*uaddr & bitmask) == setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_exactbits")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_exactbits64")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile_exactbits([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask,
                                   [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, setmask);
}

@@Wait if `(*uaddr & bitmask) != setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaituntil_exactbits")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaituntil_exactbits64")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaituntil_exactbits([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask,
                                   [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, setmask);
}

@@Wait if `(*uaddr & bitmask) != 0'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_anybit")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_anybit64")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile_anybit([[in]] lfutex_t *uaddr, lfutex_t bitmask,
                                [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, 0);
}

@@Wait if `(*uaddr & bitmask) == bitmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_allbits")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("futex_timedwaitwhile_allbits64")]]
[[impl_include("<kos/asm/futex.h>"), userimpl, requires_function(lfutex)]]
int futex_timedwaitwhile_allbits([[in]] lfutex_t *uaddr, lfutex_t bitmask,
                                 [[in_opt]] struct timespec const *rel_timeout) {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, bitmask);
}




%
%#ifdef __USE_TIME64
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile), doc_alias("futex_timedwaitwhile")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaitwhile64([[in]] lfutex_t *uaddr, lfutex_t equal_to_value,
                           [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, rel_timeout);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaituntil), doc_alias("futex_timedwaituntil")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaituntil64([[in]] lfutex_t *uaddr, lfutex_t not_equal_to_value,
                           [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, rel_timeout);
}

futex_timedwaitwhile_equal64(*) = futex_timedwaitwhile64;
futex_timedwaitwhile_notequal64(*) = futex_timedwaituntil64;

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile_above), doc_alias("futex_timedwaitwhile_above")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaitwhile_above64([[in]] lfutex_t *uaddr, lfutex_t above_value,
                                 [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, rel_timeout);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile_below), doc_alias("futex_timedwaitwhile_below")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaitwhile_below64([[in]] lfutex_t *uaddr, lfutex_t below_value,
                                 [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, rel_timeout);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile_aboveequal), doc_alias("futex_timedwaitwhile_aboveequal")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>", "<hybrid/__assert.h>")]]
int futex_timedwaitwhile_aboveequal64([[in]] lfutex_t *uaddr, lfutex_t above_or_equal_value,
                                      [[in_opt]] struct timespec64 const *rel_timeout) {
	__hybrid_assert(above_or_equal_value != 0);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_or_equal_value - 1, rel_timeout);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile_belowequal), doc_alias("futex_timedwaitwhile_belowequal")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>", "<hybrid/__assert.h>")]]
int futex_timedwaitwhile_belowequal64([[in]] lfutex_t *uaddr, lfutex_t below_or_equal_value,
                                      [[in_opt]] struct timespec64 const *rel_timeout) {
	__hybrid_assert(above_or_equal_value != (lfutex_t)-1);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_or_equal_value + 1, rel_timeout);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile_exactbits), doc_alias("futex_timedwaitwhile_exactbits")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaitwhile_exactbits64([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask,
                                     [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, setmask);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaituntil_exactbits), doc_alias("futex_timedwaituntil_exactbits")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaituntil_exactbits64([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask,
                                     [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, setmask);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile_anybit), doc_alias("futex_timedwaitwhile_anybit")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaitwhile_anybit64([[in]] lfutex_t *uaddr, lfutex_t bitmask,
                                  [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, 0);
}

[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>")]]
[[preferred_time64_variant_of(futex_timedwaitwhile_allbits), doc_alias("futex_timedwaitwhile_allbits")]]
[[userimpl, requires_function(lfutex64), impl_include("<kos/asm/futex.h>")]]
int futex_timedwaitwhile_allbits64([[in]] lfutex_t *uaddr, lfutex_t bitmask,
                                   [[in_opt]] struct timespec64 const *rel_timeout) {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, bitmask);
}

%#endif /* __USE_TIME64 */

%
%
%
%

@@Check if `futex_waitwhile()' would block
@@@return: 0: `futex_waitwhile()' would block
@@@return: 1: `futex_waitwhile()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile([[in]] lfutex_t *uaddr, lfutex_t equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) == equal_to_value ? 0 : 1;
}

@@Check if `futex_waituntil()' would block
@@@return: 0: `futex_waituntil()' would block
@@@return: 1: `futex_waituntil()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaituntil([[in]] lfutex_t *uaddr, lfutex_t not_equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) != not_equal_to_value ? 0 : 1;
}

@@Check if `futex_waitwhile_equal()' would block
@@@return: 0: `futex_waitwhile_equal()' would block
@@@return: 1: `futex_waitwhile_equal()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_equal([[in]] lfutex_t *uaddr, lfutex_t equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) == equal_to_value ? 0 : 1;
}

@@Check if `futex_waitwhile_notequal()' would block
@@@return: 0: `futex_waitwhile_notequal()' would block
@@@return: 1: `futex_waitwhile_notequal()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_notequal([[in]] lfutex_t *uaddr, lfutex_t not_equal_to_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) != not_equal_to_value ? 0 : 1;
}

@@Check if `futex_waitwhile_above()' would block
@@@return: 0: `futex_waitwhile_above()' would block
@@@return: 1: `futex_waitwhile_above()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_above([[in]] lfutex_t *uaddr, lfutex_t above_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) > above_value ? 0 : 1;
}

@@Check if `futex_waitwhile_below()' would block
@@@return: 0: `futex_waitwhile_below()' would block
@@@return: 1: `futex_waitwhile_below()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_below([[in]] lfutex_t *uaddr, lfutex_t below_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) < below_value ? 0 : 1;
}

@@Check if `futex_waitwhile_aboveequal()' would block
@@@return: 0: `futex_waitwhile_aboveequal()' would block
@@@return: 1: `futex_waitwhile_aboveequal()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_aboveequal([[in]] lfutex_t *uaddr, lfutex_t above_or_equal_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) >= above_or_equal_value ? 0 : 1;
}

@@Check if `futex_waitwhile_belowequal()' would block
@@@return: 0: `futex_waitwhile_belowequal()' would block
@@@return: 1: `futex_waitwhile_belowequal()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_belowequal([[in]] lfutex_t *uaddr, lfutex_t below_or_equal_value) {
	return __hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) <= below_or_equal_value ? 0 : 1;
}

@@Check if `futex_waitwhile_exactbits()' would block
@@@return: 0: `futex_waitwhile_exactbits()' would block
@@@return: 1: `futex_waitwhile_exactbits()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_exactbits([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) == setmask ? 0 : 1;
}

@@Check if `futex_waituntil_exactbits()' would block
@@@return: 0: `futex_waituntil_exactbits()' would block
@@@return: 1: `futex_waituntil_exactbits()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaituntil_exactbits([[in]] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) != setmask ? 0 : 1;
}

@@Check if `futex_waitwhile_anybit()' would block
@@@return: 0: `futex_waitwhile_anybit()' would block
@@@return: 1: `futex_waitwhile_anybit()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_anybit([[in]] lfutex_t *uaddr, lfutex_t bitmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) != 0 ? 0 : 1;
}

@@Check if `futex_waitwhile_allbits()' would block
@@@return: 0: `futex_waitwhile_allbits()' would block
@@@return: 1: `futex_waitwhile_allbits()' wouldn't block
[[extern_inline, decl_include("<bits/types.h>"), impl_include("<hybrid/__atomic.h>")]]
int futex_trywaitwhile_allbits([[in]] lfutex_t *uaddr, lfutex_t bitmask) {
	return (__hybrid_atomic_load(uaddr, __ATOMIC_ACQUIRE) & bitmask) == bitmask ? 0 : 1;
}

%
%
%


@@Get/Set the number of times to spin the following futex operations without
@@entering  kernel-space,  setting  waiter-bits,  and  entering  sleep mode:
@@  - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
@@  - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
@@  - ...
@@Futex spinning improves  performance by bypassing  expensive blocking  operations
@@when associated locks  are often only  held for a  couple of moments  at a  time.
@@Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferably `futex_waitwhile()'),
@@which is wrapped like this:
@@>> unsigned int spins;
@@>> spins = futex_getspin();
@@>> while (spins--) {
@@>> 	if (*uaddr != val)
@@>> 		return 0;
@@>> 	if (sched_yield())
@@>> 		break; // If there was nothing to switch to, sched_yield() returns non-zero
@@>> }
@@>> return lfutex(uaddr, LFUTEX_WAIT_WHILE, val, (struct timespec const *)NULL);
@@Upon startup, `futex_getspin()' is pre-initialized to `4'.
@@@return: * : The current (get) / old (set) spin value
[[wunused, nothrow]]
unsigned int futex_getspin();

[[nothrow, doc_alias("futex_getspin")]]
unsigned int futex_setspin(unsigned int new_spin);

%
%
%
%{
/* Provide overloads for the non-timed functions add an optional `rel_timeout'
 * argument   that   re-directly    to   the    function's   timed    variant.
 * Because  this overload  is purely based  on argument count,  we can emulate
 * this  portably  both  in   C++  and  C  (using   `__HYBRID_PP_VA_OVERLOAD') */
}
%#ifdef __cplusplus
%[insert:function(futex_wake = futex_wakeall, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile = futex_timedwaitwhile, externLinkageOverride: "C++")]
%[insert:function(futex_waituntil = futex_timedwaituntil, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_equal = futex_timedwaitwhile, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_notequal = futex_timedwaituntil, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_above = futex_timedwaitwhile_above, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_below = futex_timedwaitwhile_below, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_aboveequal = futex_timedwaitwhile_aboveequal, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_belowequal = futex_timedwaitwhile_belowequal, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_exactbits = futex_timedwaitwhile_exactbits, externLinkageOverride: "C++")]
%[insert:function(futex_waituntil_exactbits = futex_timedwaituntil_exactbits, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_anybit = futex_timedwaitwhile_anybit, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_allbits = futex_timedwaitwhile_allbits, externLinkageOverride: "C++")]
%#if defined(__USE_TIME64) && !((defined(__USE_TIME_BITS64) || defined(_TIMESPEC_MATCHES_TIMESPEC64)) && defined(__USE_STRUCT64_MACRO))
%[insert:function(futex_waitwhile = futex_timedwaitwhile64, externLinkageOverride: "C++")]
%[insert:function(futex_waituntil = futex_timedwaituntil64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_equal = futex_timedwaitwhile64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_notequal = futex_timedwaituntil64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_above = futex_timedwaitwhile_above64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_below = futex_timedwaitwhile_below64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_aboveequal = futex_timedwaitwhile_aboveequal64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_belowequal = futex_timedwaitwhile_belowequal64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_exactbits = futex_timedwaitwhile_exactbits64, externLinkageOverride: "C++")]
%[insert:function(futex_waituntil_exactbits = futex_timedwaituntil_exactbits64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_anybit = futex_timedwaitwhile_anybit64, externLinkageOverride: "C++")]
%[insert:function(futex_waitwhile_allbits = futex_timedwaitwhile_allbits64, externLinkageOverride: "C++")]
%#endif /* __USE_TIME64 && !((__USE_TIME_BITS64 || _TIMESPEC_MATCHES_TIMESPEC64) && __USE_STRUCT64_MACRO) */

%#else /* __cplusplus */
%{
#define __PRIVATE_futex_wake_1(uaddr)                                                 futex_wakeall(uaddr)
#define __PRIVATE_futex_wake_2(uaddr, max_wake)                                       futex_wake(uaddr, max_wake)
#define __PRIVATE_futex_waitwhile_2(uaddr, equal_to_value)                            futex_waitwhile(uaddr, equal_to_value)
#define __PRIVATE_futex_waitwhile_3(uaddr, equal_to_value, rel_timeout)               futex_timedwaitwhile(uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futex_waituntil_2(uaddr, not_equal_to_value)                        futex_waituntil(uaddr, not_equal_to_value)
#define __PRIVATE_futex_waituntil_3(uaddr, not_equal_to_value, rel_timeout)           futex_timedwaituntil(uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_equal_2(uaddr, equal_to_value)                      futex_waitwhile_equal(uaddr, equal_to_value)
#define __PRIVATE_futex_waitwhile_equal_3(uaddr, equal_to_value, rel_timeout)         futex_timedwaitwhile_equal(uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_notequal_2(uaddr, not_equal_to_value)               futex_waitwhile_notequal(uaddr, not_equal_to_value)
#define __PRIVATE_futex_waitwhile_notequal_3(uaddr, not_equal_to_value, rel_timeout)  futex_timedwaitwhile_notequal(uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_above_2(uaddr, above_value)                         futex_waitwhile_above(uaddr, above_value)
#define __PRIVATE_futex_waitwhile_above_3(uaddr, above_value, rel_timeout)            futex_timedwaitwhile_above(uaddr, above_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_below_2(uaddr, below_value)                         futex_waitwhile_below(uaddr, below_value)
#define __PRIVATE_futex_waitwhile_below_3(uaddr, below_value, rel_timeout)            futex_timedwaitwhile_below(uaddr, below_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_aboveequal_2(uaddr, above_or_equal_value)              futex_waitwhile_aboveequal(uaddr, above_or_equal_value)
#define __PRIVATE_futex_waitwhile_aboveequal_3(uaddr, above_or_equal_value, rel_timeout) futex_timedwaitwhile_aboveequal(uaddr, above_or_equal_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_belowequal_2(uaddr, below_or_equal_value)              futex_waitwhile_belowequal(uaddr, below_or_equal_value)
#define __PRIVATE_futex_waitwhile_belowequal_3(uaddr, below_or_equal_value, rel_timeout) futex_timedwaitwhile_belowequal(uaddr, below_or_equal_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_exactbits_3(uaddr, bitmask, setmask)                futex_waitwhile_exactbits(uaddr, bitmask, setmask)
#define __PRIVATE_futex_waitwhile_exactbits_4(uaddr, bitmask, setmask, rel_timeout)   futex_timedwaitwhile_exactbits(uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futex_waituntil_exactbits_3(uaddr, bitmask, setmask)                futex_waituntil_exactbits(uaddr, bitmask, setmask)
#define __PRIVATE_futex_waituntil_exactbits_4(uaddr, bitmask, setmask, rel_timeout)   futex_timedwaituntil_exactbits(uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futex_waitwhile_anybit_2(uaddr, bitmask)                            futex_waitwhile_anybit(uaddr, bitmask)
#define __PRIVATE_futex_waitwhile_anybit_3(uaddr, bitmask, rel_timeout)               futex_timedwaitwhile_anybit(uaddr, bitmask, rel_timeout)
#define __PRIVATE_futex_waitwhile_allbits_2(uaddr, bitmask)                           futex_waitwhile_allbits(uaddr, bitmask)
#define __PRIVATE_futex_waitwhile_allbits_3(uaddr, bitmask, rel_timeout)              futex_timedwaitwhile_allbits(uaddr, bitmask, rel_timeout)
#define futex_wake(...)                           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_wake_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waituntil(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waituntil_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_equal(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_equal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_notequal(...)             __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_notequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_above(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_above_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_below(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_below_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_aboveequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_aboveequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_belowequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_belowequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waituntil_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waituntil_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_anybit(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_anybit_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_allbits(...)              __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_allbits_, (__VA_ARGS__))(__VA_ARGS__)
}
%#endif /* !__cplusplus */


%{

__SYSDECL_END
#endif /* __CC__ */

}
