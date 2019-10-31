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

%[define_replacement(lfutex_t = __uintptr_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]
%[default_impl_section(.text.crt.sched.futex)]

%{
#include <features.h>
#include <kos/bits/futex.h>
#include <bits/types.h>
#include <bits/timespec.h>
#include <hybrid/__atomic.h>
#ifndef __cplusplus
#include <hybrid/pp/__va_nargs.h>
#endif /* !__cplusplus */

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __lfutex_t_defined
#define __lfutex_t_defined 1
typedef __uintptr_t lfutex_t;
#endif /* !__lfutex_t_defined */

/*
 * `lfutex() and select()' (or `poll()')
 *
 * On KOS, it is fairly simple to use any of the available `LFUTEX_WAIT_*' operations
 * in conjunction with a call to `poll()' (though note that the `LFUTEX_WAIT_WHILE_CMPXCH()'
 * and `LFUTEX_WAIT_UNTIL_CMPXCH()' operators will possibly modify pointed-to memory in
 * a way that makes repeated polling behave unexpectedly, requiring user-space to take
 * proper case that the behavior will be what is actually intended)
 *
 * Other than this, there exists 2 ways of polling for futex objects
 * in parallel to polling any other type of file descriptor, as well
 * polling for sleeping child processes (either through use of a file
 * descriptor created using `TODO:waitfd(pid) (similar to `signalfd()',
 * but may be used to wait for processes in a way that is similar to
 * the waitpid() function)', or through use of `kpoll()').
 *
 * - Using the `kpoll()' system call, which allows for the use of poll
 *   descriptors that describe any kind of user-space-visible handle on
 *   which a given process can wait (a regular `fd_t' (using `POLLIN|
 *   POLLOUT|...'), a `pid_t' (using `waitpid()'), or an `lfutex_t'
 *   (using any of the `LFUTEX_WAIT_*' operators that are available))
 *   When targeting KOS specifically, this is the preferred way of going
 *   about passively waiting for a futex, as it doesn't require the
 *   creation of any additional kernel-space object.
 *   TODO: Implement the `kpoll()' system call
 *
 * - Using the regular `poll()' / `select()' family of system calls, after
 *   having created 
 *
 */


}


// TODO: C++ syntax sugar
//extern "C++" {
//class futex_t;
//__NAMESPACE_INT_BEGIN
//class __LFutexOpEquals;
//class __LFutexOpNotEquals;
//class __LFutexOpAbove;
//class __LFutexOpBelow;
//class __LFutexOpAboveEqual;
//class __LFutexOpBelowEqual;
//class __LFutexOpBitmask;
//class __LFutexOpNotBitmask;
//class __LFutexOpAnd;
//__NAMESPACE_INT_END
//
//struct timespec;
//
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpEquals const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpNotEquals const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpAbove const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpBelow const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpAboveEqual const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpBelowEqual const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
//__FORCELOCAL int __NOTHROW_NCX(__LIBCCALL waitif)(__NAMESPACE_INT_SYM __LFutexOpBitmask const &__expr, struct timespec const *timeout __DFL(__NULLPTR));
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
//__DEFINE_BINARY_WRAPPER(__LFutexOpEquals, ==);
//__DEFINE_BINARY_WRAPPER(__LFutexOpNotEquals, !=);
//__DEFINE_BINARY_WRAPPER(__LFutexOpAbove, >);
//__DEFINE_BINARY_WRAPPER(__LFutexOpBelow, <);
//__DEFINE_BINARY_WRAPPER(__LFutexOpAboveEqual, >=);
//__DEFINE_BINARY_WRAPPER(__LFutexOpBelowEqual, <=);
//__DEFINE_TRINARY_WRAPPER(__LFutexOpBitmask, &, ==);
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
//class futex_t {
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


[cp][doc_alias(lfutex)][ignore][vartypes($uintptr_t, $uintptr_t)]
lfutex32:([nonnull] lfutex_t *uaddr, $syscall_ulong_t futex_op, lfutex_t val, /*struct timespec const *timeout, lfutex_t val2*/...) -> $ssize_t = lfutex?;


@@>> lfutex(2)
@@Provide the bottom-most API for implementing user-space synchronization on KOS
@@@param: futex_op: One of:
@@   - LFUTEX_WAKE:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAKE, size_t count)
@@   - LFUTEX_NOP:                (lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t ignored)
@@   - LFUTEX_WAIT:               (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex ignored, struct timespec const *timeout)
@@   - LFUTEX_WAIT_LOCK:          (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t lock_value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_UNTIL:         (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
@@   - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t bitmask, struct timespec const *timeout, lfutex_t setmask)
@@   - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
@@   - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t oldval, struct timespec const *timeout, lfutex_t newval)
@@@param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
@@@return: * : Depending on `futex_op'
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINVAL:    The given `futex_op' is invalid
@@@return: -1:EINTR:     A blocking futex-wait operation was interrupted
@@@return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out
[cp][vartypes(void *, $uintptr_t)]
[requires(defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_lfutex64))]
[dependency_string(defined(__CRT_HAVE_lfutex) || defined(__CRT_HAVE_lfutex64))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(lfutex64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(lfutex)]
lfutex:([nonnull] lfutex_t *uaddr, $syscall_ulong_t futex_op, lfutex_t val, /*struct timespec const *timeout, lfutex_t val2*/...) -> $ssize_t {
#ifdef __CRT_HAVE_lfutex
	va_list args;
	lfutex_t val2;
	struct timespec32 tms32;
	struct timespec64 *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutex32(uaddr, futex_op, val, (struct timespec32 *)NULL, val2);
	tms32.@tv_sec@  = (__time32_t)timeout->@tv_sec@;
	tms32.@tv_nsec@ = timeout->@tv_nsec@;
	return lfutex32(uaddr, futex_op, val, &tms32, val2);
#else /* __CRT_HAVE_lfutex */
	va_list args;
	lfutex_t val2;
	struct timespec64 tms64;
	struct timespec32 *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec32 *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutex64(uaddr, futex_op, val, (struct timespec64 *)NULL, val2);
	tms64.@tv_sec@  = (__time64_t)timeout->@tv_sec@;
	tms64.@tv_nsec@ = timeout->@tv_nsec@;
	return lfutex64(uaddr, futex_op, val, &tms64, val2);
#endif /* !__CRT_HAVE_lfutex */
}

%
%#ifdef __USE_TIME64
[cp][time64_variant_of(lfutex)][vartypes(void *, $uintptr_t)]
[requires(defined(__CRT_HAVE_lfutex))]
[dependency_string(defined(__CRT_HAVE_lfutex64) || defined(__CRT_HAVE_lfutex))]
lfutex64:([nonnull] lfutex_t *uaddr, $syscall_ulong_t futex_op, lfutex_t val, /*struct timespec64 const *timeout, lfutex_t val2*/...) -> $ssize_t {
	va_list args;
	lfutex_t val2;
	struct timespec32 tms32;
	struct timespec64 *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutex32(uaddr, futex_op, val, (struct timespec32 *)NULL, val2);
	tms32.@tv_sec@  = (__time32_t)timeout->@tv_sec@;
	tms32.@tv_nsec@ = timeout->@tv_nsec@;
	return lfutex32(uaddr, futex_op, val, &tms32, val2);
}
%#endif /* __USE_TIME64 */

@@Wake up to `MAX_WAKE' threads waiting for `*UADDR'
@@@return: * : The number of woken threads
@@@return: -1:EFAULT: A faulty pointer was given
[requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_wake:([nonnull] lfutex_t *uaddr, $size_t max_wake) -> $ssize_t {
	return lfutex64(uaddr, @LFUTEX_WAKE@, max_wake);
}

@@Wake all threads waiting for `*UADDR' (same as `futex_wake(uaddr, (size_t)-1)')
@@@return: * : The number of woken threads
@@@return: -1:EFAULT: A faulty pointer was given
[requires(defined(__CRT_HAVE_futex_wake) || $has_function(lfutex64))]
futex_wakeall:([nonnull] lfutex_t *uaddr) -> $ssize_t {
	return futex_wake(uaddr, ($size_t)-1);
}

@@Wait if `*uaddr == equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, (struct timespec64 *)NULL);
}

@@Wait if `*uaddr != not_equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waituntil:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, (struct timespec64 *)NULL);
}

[cp][nocrt][nouser][noexport]
futex_waitwhile_equal:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value) -> int = futex_waitwhile;
[cp][nocrt][nouser][noexport]
futex_waitwhile_notequal:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value) -> int = futex_waituntil;

@@Wait if `*uaddr > above_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_above:([nonnull] lfutex_t *uaddr, lfutex_t above_value) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, (struct timespec64 *)NULL);
}

@@Wait if `*uaddr < below_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_below:([nonnull] lfutex_t *uaddr, lfutex_t below_value) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, (struct timespec64 *)NULL);
}

@@Wait if `*uaddr >= above_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_aboveequal:([nonnull] lfutex_t *uaddr, lfutex_t above_equal_value) -> int {
	if unlikely(!above_equal_value)
		return lfutex64(uaddr, @LFUTEX_WAIT@, 0, (struct timespec64 *)NULL);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_equal_value - 1, (struct timespec64 *)NULL);
}

@@Wait if `*uaddr <= below_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_belowequal:([nonnull] lfutex_t *uaddr, lfutex_t below_equal_value) -> int {
	if unlikely(below_equal_value == (lfutex_t)-1)
		return lfutex64(uaddr, @LFUTEX_WAIT@, 0, (struct timespec64 *)NULL);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_equal_value + 1, (struct timespec64 *)NULL);
}

@@Wait if `*uaddr == old_value', and set `*uaddr = new_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value)
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_cmpxch:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_CMPXCH@, old_value, (struct timespec64 *)NULL, new_value);
}

@@Wait if `*uaddr != old_value', and set `*uaddr = new_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value)
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waituntil_cmpxch:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_CMPXCH@, old_value, (struct timespec64 *)NULL, new_value);
}

@@Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted (*uaddr was still set to new_value)
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitlock:([nonnull] lfutex_t *uaddr) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_LOCK@, 0, (struct timespec64 *)NULL);
}


@@Wait if `(*uaddr & bitmask) == setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_exactbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, (struct timespec64 *)NULL, setmask);
}

@@Wait if `(*uaddr & bitmask) != setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waituntil_exactbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, (struct timespec64 *)NULL, setmask);
}

@@Wait if `(*uaddr & bitmask) != 0'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_anybit:([nonnull] lfutex_t *uaddr, lfutex_t bitmask) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, (struct timespec64 *)NULL, 0);
}

@@Wait if `(*uaddr & bitmask) == bitmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex64))]
[dependency_include(<kos/bits/futex.h>)]
futex_waitwhile_allbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, (struct timespec64 *)NULL, bitmask);
}












@@Wait if `*uaddr == equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, rel_timeout);
}

@@Wait if `*uaddr != not_equal_to_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaituntil:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, rel_timeout);
}

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile)]
futex_timedwaitwhile_equal:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil)]
futex_timedwaitwhile_notequal:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec *rel_timeout) -> int = futex_timedwaituntil;

@@Wait if `*uaddr > above_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_above64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_above)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_above:([nonnull] lfutex_t *uaddr, lfutex_t above_value, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, rel_timeout);
}

@@Wait if `*uaddr < below_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_below64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_below)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_below:([nonnull] lfutex_t *uaddr, lfutex_t below_value, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, rel_timeout);
}

@@Wait if `*uaddr >= above_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_aboveequal64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_aboveequal)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_aboveequal:([nonnull] lfutex_t *uaddr, lfutex_t above_equal_value, struct timespec *rel_timeout) -> int {
	if unlikely(!above_equal_value)
		return lfutex(uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_equal_value - 1, rel_timeout);
}

@@Wait if `*uaddr <= below_equal_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_belowequal64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_belowequal)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_belowequal:([nonnull] lfutex_t *uaddr, lfutex_t below_equal_value, struct timespec *rel_timeout) -> int {
	if unlikely(below_equal_value == (lfutex_t)-1)
		return lfutex(uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_equal_value + 1, rel_timeout);
}

@@Wait if `*uaddr == old_value', and set `*uaddr = new_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_cmpxch64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_cmpxch)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_cmpxch:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_CMPXCH@, old_value, rel_timeout, new_value);
}

@@Wait if `*uaddr != old_value', and set `*uaddr = new_value'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil_cmpxch64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil_cmpxch)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaituntil_cmpxch:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_UNTIL_CMPXCH@, old_value, rel_timeout, new_value);
}

@@Acquire a managed futex lock (s.a. `LFUTEX_WAIT_LOCK')
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINTR:     Operation was interrupted (*uaddr was still set to new_value)
@@@return: -1:ETIMEDOUT: The given `rel_timeout' has expired
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitlock64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitlock)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitlock:([nonnull] lfutex_t *uaddr, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_LOCK@, 0, rel_timeout);
}


@@Wait if `(*uaddr & bitmask) == setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_exactbits64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_exactbits)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_exactbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, setmask);
}

@@Wait if `(*uaddr & bitmask) != setmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil_exactbits64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil_exactbits)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaituntil_exactbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, setmask);
}

@@Wait if `(*uaddr & bitmask) != 0'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_anybit64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_anybit)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_anybit:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, 0);
}

@@Wait if `(*uaddr & bitmask) == bitmask'
@@@return: 0: Did wait
@@@return: 1: Didn't wait
@@@return: -1:EFAULT: A faulty pointer was given
@@@return: -1:EINTR:  Operation was interrupted
[cp][requires($has_function(lfutex))]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_allbits64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_allbits)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_allbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, struct timespec *rel_timeout) -> int {
	return lfutex(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, bitmask);
}




%
%#ifdef __USE_TIME64
[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile64:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, rel_timeout);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaituntil)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaituntil64:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, rel_timeout);
}

[cp][nocrt][nouser][noexport][time64_variant_of(futex_timedwaitwhile_equal)]
futex_timedwaitwhile_equal64:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec64 *rel_timeout) -> int = futex_timedwaitwhile64;

[cp][nocrt][nouser][noexport][time64_variant_of(futex_timedwaitwhile_notequal)]
futex_timedwaitwhile_notequal64:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec64 *rel_timeout) -> int = futex_timedwaituntil64;

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_above)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_above64:([nonnull] lfutex_t *uaddr, lfutex_t above_value, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, rel_timeout);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_below)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_below64:([nonnull] lfutex_t *uaddr, lfutex_t below_value, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, rel_timeout);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_aboveequal)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_aboveequal64:([nonnull] lfutex_t *uaddr, lfutex_t above_equal_value, struct timespec64 *rel_timeout) -> int {
	if unlikely(!above_equal_value)
		return lfutex64(uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_equal_value - 1, rel_timeout);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_belowequal)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_belowequal64:([nonnull] lfutex_t *uaddr, lfutex_t below_equal_value, struct timespec64 *rel_timeout) -> int {
	if unlikely(below_equal_value == (lfutex_t)-1)
		return lfutex64(uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_equal_value + 1, rel_timeout);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_cmpxch)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_cmpxch64:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_CMPXCH@, old_value, rel_timeout, new_value);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaituntil_cmpxch)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaituntil_cmpxch64:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_CMPXCH@, old_value, rel_timeout, new_value);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitlock)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitlock64:([nonnull] lfutex_t *uaddr, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_LOCK@, 0, rel_timeout);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_exactbits)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_exactbits64:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, setmask);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaituntil_exactbits)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaituntil_exactbits64:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, setmask);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_anybit)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_anybit64:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, 0);
}

[cp][requires($has_function(lfutex64))][time64_variant_of(futex_timedwaitwhile_allbits)]
[dependency_include(<kos/bits/futex.h>)]
futex_timedwaitwhile_allbits64:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, struct timespec64 *rel_timeout) -> int {
	return lfutex64(uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, bitmask);
}

%#endif /* __USE_TIME64 */


[guard][ATTR_WUNUSED][noexport][nocrt][nouser] __os_gettid:() -> $pid_t = gettid;

%
%
%
%{
/* Check if `futex_waitwhile()' would block
 * @return: 0: `futex_waitwhile()' would block
 * @return: 1: `futex_waitwhile()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile)(lfutex_t *__uaddr, lfutex_t __equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) == __equal_to_value ? 0 : 1;
}

/* Check if `futex_waituntil()' would block
 * @return: 0: `futex_waituntil()' would block
 * @return: 1: `futex_waituntil()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaituntil)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) != __not_equal_to_value ? 0 : 1;
}

/* Check if `futex_waitwhile_equal()' would block
 * @return: 0: `futex_waitwhile_equal()' would block
 * @return: 1: `futex_waitwhile_equal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_equal)(lfutex_t *__uaddr, lfutex_t __equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) == __equal_to_value ? 0 : 1;
}

/* Check if `futex_waitwhile_notequal()' would block
 * @return: 0: `futex_waitwhile_notequal()' would block
 * @return: 1: `futex_waitwhile_notequal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_notequal)(lfutex_t *__uaddr, lfutex_t __not_equal_to_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) != __not_equal_to_value ? 0 : 1;
}

/* Check if `futex_waitwhile_above()' would block
 * @return: 0: `futex_waitwhile_above()' would block
 * @return: 1: `futex_waitwhile_above()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_above)(lfutex_t *__uaddr, lfutex_t __above_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) > __above_value ? 0 : 1;
}

/* Check if `futex_waitwhile_below()' would block
 * @return: 0: `futex_waitwhile_below()' would block
 * @return: 1: `futex_waitwhile_below()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_below)(lfutex_t *__uaddr, lfutex_t __below_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) < __below_value ? 0 : 1;
}

/* Check if `futex_waitwhile_aboveequal()' would block
 * @return: 0: `futex_waitwhile_aboveequal()' would block
 * @return: 1: `futex_waitwhile_aboveequal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_aboveequal)(lfutex_t *__uaddr, lfutex_t __above_equal_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) >= __above_equal_value ? 0 : 1;
}

/* Check if `futex_waitwhile_belowequal()' would block
 * @return: 0: `futex_waitwhile_belowequal()' would block
 * @return: 1: `futex_waitwhile_belowequal()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_belowequal)(lfutex_t *__uaddr, lfutex_t __below_equal_value) {
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) <= __below_equal_value ? 0 : 1;
}

/* This one probably isn't that useful, considering that `NEW_VALUE' must only be written
 * just before starting to wait, meaning that we don't actually use that argument since we're
 * not allowed to ever actually wait... */
/* Check if `futex_waitwhile_cmpxch()' would block
 * @return: 0: `futex_waitwhile_cmpxch()' would block
 * @return: 1: `futex_waitwhile_cmpxch()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_cmpxch)(lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value) {
	(void)__new_value;
	return __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) == __old_value ? 0 : 1;
}

/* Same as `futex_waituntil_cmpxch()' with a 0-length timeout
 * @return: 0: Failed to exchange `*UADDR'
 * @return: 1: Successfully exchanged `*UADDR' from `OLD_VALUE' to `NEW_VALUE' */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaituntil_cmpxch)(lfutex_t *__uaddr, lfutex_t __old_value, lfutex_t __new_value) {
	return !__hybrid_atomic_cmpxch(*__uaddr, __old_value, __new_value, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST) ? 0 : 1;
}

#ifdef ____os_gettid_defined
/* Same as `futex_waitlock()' with a 0-length timeout
 * @return: 0: Successfully acquired the lock
 * @return: 1: Failed to acquire acquired the lock without blocking */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitlock)(lfutex_t *__uaddr) {
	for (;;) {
		lfutex_t __oldval;
		__oldval = __hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE);
		if ((__oldval & LFUTEX_WAIT_LOCK_TIDMASK) != 0)
			break;
		if (__hybrid_atomic_cmpxch_weak(*__uaddr, __oldval, (__oldval & ~LFUTEX_WAIT_LOCK_TIDMASK) | __os_gettid(),
		                                __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
			return 0;
	}
	return 1;
}
#endif /* ____os_gettid_defined */

/* Check if `futex_waitwhile_exactbits()' would block
 * @return: 0: `futex_waitwhile_exactbits()' would block
 * @return: 1: `futex_waitwhile_exactbits()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) == __setmask ? 0 : 1;
}

/* Check if `futex_waituntil_exactbits()' would block
 * @return: 0: `futex_waituntil_exactbits()' would block
 * @return: 1: `futex_waituntil_exactbits()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaituntil_exactbits)(lfutex_t *__uaddr, lfutex_t __bitmask, lfutex_t __setmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) != __setmask ? 0 : 1;
}

/* Check if `futex_waitwhile_anybit()' would block
 * @return: 0: `futex_waitwhile_anybit()' would block
 * @return: 1: `futex_waitwhile_anybit()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_anybit)(lfutex_t *__uaddr, lfutex_t __bitmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) != 0 ? 0 : 1;
}

/* Check if `futex_waitwhile_allbits()' would block
 * @return: 0: `futex_waitwhile_allbits()' would block
 * @return: 1: `futex_waitwhile_allbits()' wouldn't block */
__FORCELOCAL __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL futex_trywaitwhile_allbits)(lfutex_t *__uaddr, lfutex_t __bitmask) {
	return (__hybrid_atomic_load(*__uaddr, __ATOMIC_ACQUIRE) & __bitmask) == __bitmask ? 0 : 1;
}

}

%
%
%


@@Get/Set the number of times to spin the following futex operations without
@@entering kernel-space, setting waiter-bits, and entering sleep mode:
@@  - LFUTEX_WAIT_WHILE: SPIN({ if (*uaddr != val) DONE(); });
@@  - LFUTEX_WAIT_UNTIL: SPIN({ if (*uaddr == val) DONE(); });
@@  - ...
@@Futex spinning improves performance by bypassing expensive blocking operations
@@when associated locks are often only held for a couple of moments at a time.
@@Take for example `lfutex(LFUTEX_WAIT_WHILE)' (or preferrably `futex_waitwhile()'), which
@@is wrapped like this:
@@>> unsigned int spins;
@@>> spins = futex_getspin();
@@>> while (spins--) {
@@>> 	if (*uaddr != val)
@@>> 		return 0;
@@>> 	if (sched_yield())
@@>> 		break; // If there was nothing to switch to, sched_yield() returns non-zero
@@>> }
@@>> return lfutex(uaddr, LFUTEX_WAIT_WHILE, val, (struct timespec *)NULL);
@@Upon startup, `futex_getspin()' is pre-initialized to `4'.
@@@return: * : The current (get) / old (set) spin value
[nothrow][ATTR_WUNUSED] futex_getspin:() -> unsigned int;

[doc_alias(futex_getspin)][nothrow]
futex_setspin:(unsigned int new_spin) -> unsigned int;

%
%
%
%{
/* Provide overloads for the non-timed functions add an optional `rel_timeout'
 * argument that re-directly to the function's timed variant.
 * Because this overload is purely based on argument count, we can emulate
 * this portably both in C++ and C (using `__HYBRID_PP_VA_OVERLOAD') */
#ifdef __cplusplus
}
%extern "C++" {

[noexport][nocrt][nouser]
futex_wake:([nonnull] lfutex_t *uaddr) -> $ssize_t = futex_wakeall;

[cp][noexport][nocrt][nouser]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile)]
futex_waitwhile:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile;

[cp][noexport][nocrt][nouser]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil)]
futex_waituntil:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec *rel_timeout) -> int = futex_timedwaituntil;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile)]
futex_waitwhile_equal:([nonnull] lfutex_t *uaddr, lfutex_t equal_to_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil)]
futex_waitwhile_notequal:([nonnull] lfutex_t *uaddr, lfutex_t not_equal_to_value, struct timespec *rel_timeout) -> int = futex_timedwaituntil;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_above64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_above)]
futex_waitwhile_above:([nonnull] lfutex_t *uaddr, lfutex_t above_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_above;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_below64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_below)]
futex_waitwhile_below:([nonnull] lfutex_t *uaddr, lfutex_t below_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_below;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_aboveequal64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_aboveequal)]
futex_waitwhile_aboveequal:([nonnull] lfutex_t *uaddr, lfutex_t above_equal_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_aboveequal;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_belowequal64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_belowequal)]
futex_waitwhile_belowequal:([nonnull] lfutex_t *uaddr, lfutex_t below_equal_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_belowequal;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_cmpxch64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitwhile_cmpxch)]
futex_waitwhile_cmpxch:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_cmpxch;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil_cmpxch64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaituntil_cmpxch)]
futex_waituntil_cmpxch:([nonnull] lfutex_t *uaddr, lfutex_t old_value, lfutex_t new_value, struct timespec *rel_timeout) -> int = futex_timedwaituntil_cmpxch;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitlock64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_timedwaitlock)]
futex_waitlock:([nonnull] lfutex_t *uaddr, struct timespec *rel_timeout) -> int = futex_timedwaitlock;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_waitwhile_exactbits64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_waitwhile_exactbits)]
futex_waitwhile_exactbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_exactbits;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_waituntil_exactbits64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_waituntil_exactbits)]
futex_waituntil_exactbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, lfutex_t setmask, struct timespec *rel_timeout) -> int = futex_timedwaituntil_exactbits;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_waitwhile_anybit64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_waitwhile_anybit)]
futex_waitwhile_anybit:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_anybit;

[cp][nocrt][nouser][noexport]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futex_waitwhile_allbits64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futex_waitwhile_allbits)]
futex_waitwhile_allbits:([nonnull] lfutex_t *uaddr, lfutex_t bitmask, struct timespec *rel_timeout) -> int = futex_timedwaitwhile_allbits;

%} /* extern "C++" */
%{
#else /* __cplusplus */
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
#define __PRIVATE_futex_waitwhile_aboveequal_2(uaddr, above_equal_value)              futex_waitwhile_aboveequal(uaddr, above_equal_value)
#define __PRIVATE_futex_waitwhile_aboveequal_3(uaddr, above_equal_value, rel_timeout) futex_timedwaitwhile_aboveequal(uaddr, above_equal_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_belowequal_2(uaddr, below_equal_value)              futex_waitwhile_belowequal(uaddr, below_equal_value)
#define __PRIVATE_futex_waitwhile_belowequal_3(uaddr, below_equal_value, rel_timeout) futex_timedwaitwhile_belowequal(uaddr, below_equal_value, rel_timeout)
#define __PRIVATE_futex_waitwhile_cmpxch_3(uaddr, old_value, new_value)               futex_waitwhile_cmpxch(uaddr, old_value, new_value)
#define __PRIVATE_futex_waitwhile_cmpxch_4(uaddr, old_value, new_value, rel_timeout)  futex_timedwaitwhile_cmpxch(uaddr, old_value, new_value, rel_timeout)
#define __PRIVATE_futex_waituntil_cmpxch_3(uaddr, old_value, new_value)               futex_waituntil_cmpxch(uaddr, old_value, new_value)
#define __PRIVATE_futex_waituntil_cmpxch_4(uaddr, old_value, new_value, rel_timeout)  futex_timedwaituntil_cmpxch(uaddr, old_value, new_value, rel_timeout)
#define __PRIVATE_futex_waitlock_1(uaddr)                                             futex_waitlock(uaddr)
#define __PRIVATE_futex_waitlock_2(uaddr, rel_timeout)                                futex_timedwaitlock(uaddr, rel_timeout)
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
#define futex_waitwhile_cmpxch(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waituntil_cmpxch(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waituntil_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitlock(...)                       __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitlock_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waituntil_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waituntil_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_anybit(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_anybit_, (__VA_ARGS__))(__VA_ARGS__)
#define futex_waitwhile_allbits(...)              __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futex_waitwhile_allbits_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__cplusplus */
}


%{


#endif /* __CC__ */

__SYSDECL_END

}