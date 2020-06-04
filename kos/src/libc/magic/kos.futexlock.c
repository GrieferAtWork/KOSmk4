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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(lfutex_t = __uintptr_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]
%[default_impl_section(.text.crt.sched.futexlock)]

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

}

[[vartypes($uintptr_t, $uintptr_t), decl_include("<bits/types.h>")]]
[[cp, doc_alias(lfutexlock), ignore, nocrt, alias(lfutexlock)]]
lfutexlock32:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
              $syscall_ulong_t futex_op, lfutex_t val,
              /*struct timespec const *timeout, lfutex_t val2*/...) -> $ssize_t;

@@>> lfutexlock(3)
@@Helper function to implement the behavior of `lfutexlockexpr()' for only a single futex.
@@This function behaves identical to the lfutex() system call, except that it takes
@@two futex addresses, where `ulockaddr' is used with `LFUTEX_WAIT_LOCK_WAITERS' to cache if
@@there are threads that may be waiting to be awoken once `LFUTEX_WAKE' is invoked on that
@@memory location (aka. `futexlock_wakeall(ulockaddr)'), whilst the other futex address
@@(i.e. `uaddr') is used for the wait-while-condition checking, the same way those checks
@@would also be performed by the `lfutex() system call'
@@@param: futex_op: One of:
@@   - LFUTEX_NOP:                (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_NOP, size_t val = ignored)
@@   - LFUTEX_WAIT:               (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT, lfutex_t val = ignored, struct timespec const *timeout)
@@   - LFUTEX_WAIT_LOCK:          (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_LOCK, lfutex_t val = lock_value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE, lfutex_t val = value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_UNTIL:         (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL, lfutex_t val = value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_ABOVE:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_ABOVE, lfutex_t val = value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_BELOW:   (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BELOW, lfutex_t val = value, struct timespec const *timeout)
@@   - LFUTEX_WAIT_WHILE_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
@@   - LFUTEX_WAIT_UNTIL_BITMASK: (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_BITMASK, lfutex_t val = bitmask, struct timespec const *timeout, lfutex_t setmask)
@@   - LFUTEX_WAIT_WHILE_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_WHILE_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
@@   - LFUTEX_WAIT_UNTIL_CMPXCH:  (lfutex_t *ulockaddr, lfutex_t *uaddr, syscall_ulong_t LFUTEX_WAIT_UNTIL_CMPXCH, lfutex_t val = oldval, struct timespec const *timeout, lfutex_t newval)
@@@param: timeout: Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
@@@return: * : Depending on `futex_op'
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINVAL:    The given `futex_op' is invalid
@@@return: -1:EINTR:     A blocking futex-wait operation was interrupted
@@@return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out
[[cp, vartypes(void *, $uintptr_t), decl_include("<bits/types.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(lfutexlock64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(lfutexlock)]]
[[impl_include("<bits/timespec.h>"), userimpl, requires($has_function(lfutexlock32) || $has_function(lfutexlock64))]]
lfutexlock:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
            $syscall_ulong_t futex_op, lfutex_t val,
            /*struct timespec const *timeout, lfutex_t val2*/...) -> $ssize_t {
@@if_has_function(lfutexlock32)@@
	va_list args;
	lfutex_t val2;
	struct timespec32 tms32;
	struct timespec64 const *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 const *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutexlock32(ulockaddr, uaddr, futex_op, val, (struct timespec32 *)NULL, val2);
	tms32.@tv_sec@  = (__time32_t)timeout->@tv_sec@;
	tms32.@tv_nsec@ = timeout->@tv_nsec@;
	return lfutexlock32(ulockaddr, uaddr, futex_op, val, &tms32, val2);
@@else_has_function(lfutexlock32)@@
	va_list args;
	lfutex_t val2;
	struct timespec64 tms64;
	struct timespec32 *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec32 *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutexlock64(ulockaddr, uaddr, futex_op, val, (struct timespec64 const *)NULL, val2);
	tms64.@tv_sec@  = (__time64_t)timeout->@tv_sec@;
	tms64.@tv_nsec@ = timeout->@tv_nsec@;
	return lfutexlock64(ulockaddr, uaddr, futex_op, val, &tms64, val2);
@@endif_has_function(lfutexlock32)@@
}


%
%#ifdef __USE_TIME64
[cp][time64_variant_of(lfutexlock)][vartypes(void *, $uintptr_t)]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
[requires($has_function(lfutexlock32))]
lfutexlock64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr, $syscall_ulong_t futex_op, lfutex_t val, /*struct timespec64 const *timeout, lfutex_t val2*/...) -> $ssize_t {
	va_list args;
	lfutex_t val2;
	struct timespec32 tms32;
	struct timespec64 const *timeout;
	va_start(args, val);
	timeout = va_arg(args, struct timespec64 const *);
	val2 = va_arg(args, lfutex_t);
	va_end(args);
	if (!timeout || !@LFUTEX_USES_TIMEOUT@(futex_op))
		return lfutexlock32(ulockaddr, uaddr, futex_op, val, (struct timespec32 *)NULL, val2);
	tms32.@tv_sec@  = (__time32_t)timeout->@tv_sec@;
	tms32.@tv_nsec@ = timeout->@tv_nsec@;
	return lfutexlock32(ulockaddr, uaddr, futex_op, val, &tms32, val2);
}
%#endif /* __USE_TIME64 */



@@A more efficient variant of `futex_wake()' that can be used to wake up threads waiting
@@on some given futex-lock. - This method of waking is faster, since it doesn't invoke a
@@system call when no thread is waiting on the given lock
[requires($has_function(futex_wakemask))]
[dependency_include(<hybrid/__atomic.h>)]
[impl_include("<kos/bits/futex.h>")][decl_include("<bits/types.h>")]
futexlock_wake:([[nonnull]] lfutex_t *ulockaddr, $size_t max_wake) -> $ssize_t {
	if (!(__hybrid_atomic_load(*ulockaddr, __ATOMIC_ACQUIRE) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	return futex_wakemask(&ulockaddr, 1, (lfutex_t)~LFUTEX_WAIT_LOCK_WAITERS, 0);
}

[doc_alias(futexlock_wake)]
[requires($has_function(futex_wakeall))]
[dependency_include(<hybrid/__atomic.h>)]
[impl_include("<kos/bits/futex.h>")][decl_include("<bits/types.h>")]
futexlock_wakeall:([[nonnull]] lfutex_t *ulockaddr) -> $ssize_t {
	if (!(__hybrid_atomic_load(*ulockaddr, __ATOMIC_ACQUIRE) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	if (!(__hybrid_atomic_fetchand(*ulockaddr, ~LFUTEX_WAIT_LOCK_WAITERS, __ATOMIC_SEQ_CST) & LFUTEX_WAIT_LOCK_WAITERS))
		return 0; /* No waiting threads. */
	return futex_wakeall(ulockaddr);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile:([[nonnull]] lfutex_t *ulockaddr,
                     [[nonnull]] lfutex_t *uaddr, lfutex_t equal_to_value) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, (struct timespec64 const *)NULL);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waituntil)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waituntil:([[nonnull]] lfutex_t *ulockaddr,
                     [[nonnull]] lfutex_t *uaddr, lfutex_t not_equal_to_value) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, (struct timespec64 const *)NULL);
}

futexlock_waitwhile_equal(*) = futexlock_waitwhile;
futexlock_waitwhile_notequal(*) = futexlock_waituntil;

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_above)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_above:([[nonnull]] lfutex_t *ulockaddr,
                           [[nonnull]] lfutex_t *uaddr, lfutex_t above_value) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, (struct timespec64 const *)NULL);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_below)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_below:([[nonnull]] lfutex_t *ulockaddr,
                           [[nonnull]] lfutex_t *uaddr, lfutex_t below_value) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, (struct timespec64 const *)NULL);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_aboveequal)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_aboveequal:([[nonnull]] lfutex_t *ulockaddr,
                                [[nonnull]] lfutex_t *uaddr, lfutex_t above_equal_value) -> int {
	if unlikely(!above_equal_value)
		return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT@, 0, (struct timespec64 const *)NULL);
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_equal_value - 1, (struct timespec64 const *)NULL);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_belowequal)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_belowequal:([[nonnull]] lfutex_t *ulockaddr,
                                [[nonnull]] lfutex_t *uaddr, lfutex_t below_equal_value) -> int {
	if unlikely(below_equal_value == (lfutex_t)-1)
		return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT@, 0, (struct timespec64 const *)NULL);
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_equal_value + 1, (struct timespec64 const *)NULL);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_cmpxch)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_cmpxch:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                            lfutex_t old_value, lfutex_t new_value) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_CMPXCH@, old_value, (struct timespec64 const *)NULL, new_value);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waituntil_cmpxch)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waituntil_cmpxch:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                            lfutex_t old_value, lfutex_t new_value) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_CMPXCH@, old_value, (struct timespec64 const *)NULL, new_value);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitlock)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitlock:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_LOCK@, 0, (struct timespec64 const *)NULL);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_exactbits)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_exactbits:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                               lfutex_t bitmask, lfutex_t setmask) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, (struct timespec64 const *)NULL, setmask);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waituntil_exactbits)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waituntil_exactbits:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                               lfutex_t bitmask, lfutex_t setmask) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, (struct timespec64 const *)NULL, setmask);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_anybit)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_anybit:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr, lfutex_t bitmask) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, (struct timespec64 const *)NULL, 0);
}

[cp][requires($has_function(lfutexlock64))][doc_alias(futex_waitwhile_allbits)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>")][dependency_include("<bits/timespec.h>")]
futexlock_waitwhile_allbits:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr, lfutex_t bitmask) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, (struct timespec64 const *)NULL, bitmask);
}











[[cp, doc_alias(futex_timedwaitwhile)]]
[[decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                          lfutex_t equal_to_value, struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, rel_timeout);
}

[[doc_alias(futex_timedwaituntil)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaituntil64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaituntil)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaituntil:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                          lfutex_t not_equal_to_value, struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, rel_timeout);
}

futexlock_timedwaitwhile_equal(*) = futexlock_timedwaitwhile;
futexlock_timedwaitwhile_notequal(*) = futexlock_timedwaituntil;

[doc_alias(futex_timedwaitwhile_above)]
[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]
[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_above64)]
[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_above)]
[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]
futexlock_timedwaitwhile_above:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                lfutex_t above_value, struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, rel_timeout);
}

[							   [doc_alias(futex_timedwaitwhile_below)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_below64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_below)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile_below:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                lfutex_t below_value, struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, rel_timeout);
}

[[doc_alias(futex_timedwaitwhile_aboveequal)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_aboveequal64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_aboveequal)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile_aboveequal:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                     lfutex_t above_equal_value, struct timespec const *rel_timeout) -> int {
	if unlikely(!above_equal_value)
		return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_equal_value - 1, rel_timeout);
}

[[doc_alias(futex_timedwaitwhile_belowequal)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_belowequal64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_belowequal)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile_belowequal:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                     lfutex_t below_equal_value, struct timespec const *rel_timeout) -> int {
	if unlikely(below_equal_value == (lfutex_t)-1)
		return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_equal_value + 1, rel_timeout);
}

[[doc_alias(futex_timedwaitwhile_cmpxch)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_cmpxch64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_cmpxch)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile_cmpxch:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                 lfutex_t old_value, lfutex_t new_value,
                                 struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_CMPXCH@, old_value, rel_timeout, new_value);
}

[[doc_alias(futex_timedwaituntil_cmpxch)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaituntil_cmpxch64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaituntil_cmpxch)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaituntil_cmpxch:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                 lfutex_t old_value, lfutex_t new_value,
                                 struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_CMPXCH@, old_value, rel_timeout, new_value);
}

[[doc_alias(futex_timedwaitlock)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitlock64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitlock)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitlock:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                         struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_LOCK@, 0, rel_timeout);
}


[[doc_alias(futex_timedwaitwhile_exactbits)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_exactbits64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_exactbits)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile_exactbits:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                    lfutex_t bitmask, lfutex_t setmask,
                                    struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, setmask);
}

[[doc_alias(futex_timedwaituntil_exactbits)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaituntil_exactbits64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaituntil_exactbits)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaituntil_exactbits:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                    lfutex_t bitmask, lfutex_t setmask,
                                    struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, setmask);
}

[[doc_alias(futex_timedwaitwhile_anybit)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_anybit64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_anybit)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile_anybit:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                 lfutex_t bitmask, struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, 0);
}

[[doc_alias(futex_timedwaitwhile_allbits)]]
[[cp, decl_include("<bits/types.h>", "<bits/timespec.h>"), no_crt_self_import]]
[[if(defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_allbits64)]]
[[if(!defined(__USE_TIME_BITS64)), preferred_alias(futexlock_timedwaitwhile_allbits)]]
[[impl_include("<kos/bits/futex.h>"), userimpl, requires_function(lfutexlock)]]
futexlock_timedwaitwhile_allbits:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                  lfutex_t bitmask, struct timespec const *rel_timeout) -> int {
	return lfutexlock(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, bitmask);
}




%
%#ifdef __USE_TIME64
[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                            lfutex_t equal_to_value, struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE@, equal_to_value, rel_timeout);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaituntil)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaituntil64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                            lfutex_t not_equal_to_value, struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL@, not_equal_to_value, rel_timeout);
}

futexlock_timedwaitwhile_equal64(*) = futexlock_timedwaitwhile64;
futexlock_timedwaitwhile_notequal64(*) = futexlock_timedwaituntil64;

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_above)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_above64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                  lfutex_t above_value, struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_value, rel_timeout);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_below)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_below64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                  lfutex_t below_value, struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_value, rel_timeout);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_aboveequal)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_aboveequal64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                       lfutex_t above_equal_value, struct timespec64 const *rel_timeout) -> int {
	if unlikely(!above_equal_value)
		return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_ABOVE@, above_equal_value - 1, rel_timeout);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_belowequal)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_belowequal64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                       lfutex_t below_equal_value, struct timespec64 const *rel_timeout) -> int {
	if unlikely(below_equal_value == (lfutex_t)-1)
		return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT@, 0, rel_timeout);
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BELOW@, below_equal_value + 1, rel_timeout);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_cmpxch)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_cmpxch64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                   lfutex_t old_value, lfutex_t new_value,
                                   struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_CMPXCH@, old_value, rel_timeout, new_value);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaituntil_cmpxch)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaituntil_cmpxch64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                   lfutex_t old_value, lfutex_t new_value,
                                   struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_CMPXCH@, old_value, rel_timeout, new_value);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitlock)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitlock64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                           struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_LOCK@, 0, rel_timeout);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_exactbits)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_exactbits64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                      lfutex_t bitmask, lfutex_t setmask,
                                      struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, setmask);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaituntil_exactbits)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaituntil_exactbits64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                      lfutex_t bitmask, lfutex_t setmask,
                                      struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, setmask);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_anybit)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_anybit64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                   lfutex_t bitmask, struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_UNTIL_BITMASK@, bitmask, rel_timeout, 0);
}

[cp][requires($has_function(lfutexlock64))][time64_variant_of(futexlock_timedwaitwhile_allbits)]
[impl_include("<kos/bits/futex.h>")]
[decl_include("<bits/types.h>", "<bits/timespec.h>")]
futexlock_timedwaitwhile_allbits64:([[nonnull]] lfutex_t *ulockaddr, [[nonnull]] lfutex_t *uaddr,
                                    lfutex_t bitmask, struct timespec64 const *rel_timeout) -> int {
	return lfutexlock64(ulockaddr, uaddr, @LFUTEX_WAIT_WHILE_BITMASK@, bitmask, rel_timeout, bitmask);
}

%#endif /* __USE_TIME64 */


%
%{
/* Provide overloads for the non-timed functions add an optional `rel_timeout'
 * argument that re-directly to the function's timed variant.
 * Because this overload is purely based on argument count, we can emulate
 * this portably both in C++ and C (using `__HYBRID_PP_VA_OVERLOAD') */
#ifdef __cplusplus
}
%extern "C++" {

%[insert:function(futexlock_waitwhile = futexlock_timedwaitwhile, externLinkageOverride: "C++")]
%[insert:function(futexlock_waituntil = futexlock_timedwaituntil, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_equal = futexlock_timedwaitwhile, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_notequal = futexlock_timedwaituntil, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_above = futexlock_timedwaitwhile_above, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_below = futexlock_timedwaitwhile_below, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_aboveequal = futexlock_timedwaitwhile_aboveequal, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_belowequal = futexlock_timedwaitwhile_belowequal, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_cmpxch = futexlock_timedwaitwhile_cmpxch, externLinkageOverride: "C++")]
%[insert:function(futexlock_waituntil_cmpxch = futexlock_timedwaituntil_cmpxch, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitlock = futexlock_timedwaitlock, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_exactbits = futexlock_timedwaitwhile_exactbits, externLinkageOverride: "C++")]
%[insert:function(futexlock_waituntil_exactbits = futexlock_timedwaituntil_exactbits, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_anybit = futexlock_timedwaitwhile_anybit, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_allbits = futexlock_timedwaitwhile_allbits, externLinkageOverride: "C++")]

%#if defined(__USE_TIME64) && !((defined(__USE_TIME_BITS64) || defined(_TIMESPEC_MATCHES_TIMESPEC64)) && defined(__USE_STRUCT64_MACRO))
%[insert:function(futexlock_waitwhile = futexlock_timedwaitwhile64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waituntil = futexlock_timedwaituntil64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_equal = futexlock_timedwaitwhile64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_notequal = futexlock_timedwaituntil64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_above = futexlock_timedwaitwhile_above64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_below = futexlock_timedwaitwhile_below64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_aboveequal = futexlock_timedwaitwhile_aboveequal64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_belowequal = futexlock_timedwaitwhile_belowequal64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_cmpxch = futexlock_timedwaitwhile_cmpxch64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waituntil_cmpxch = futexlock_timedwaituntil_cmpxch64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitlock = futexlock_timedwaitlock64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_exactbits = futexlock_timedwaitwhile_exactbits64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waituntil_exactbits = futexlock_timedwaituntil_exactbits64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_anybit = futexlock_timedwaitwhile_anybit64, externLinkageOverride: "C++")]
%[insert:function(futexlock_waitwhile_allbits = futexlock_timedwaitwhile_allbits64, externLinkageOverride: "C++")]
%#endif /* __USE_TIME64 && !((__USE_TIME_BITS64 || _TIMESPEC_MATCHES_TIMESPEC64) && __USE_STRUCT64_MACRO) */

%} /* extern "C++" */
%{
#else /* __cplusplus */
#define __PRIVATE_futexlock_waitwhile_2(ulockaddr, uaddr, equal_to_value)                            futexlock_waitwhile(ulockaddr, uaddr, equal_to_value)
#define __PRIVATE_futexlock_waitwhile_3(ulockaddr, uaddr, equal_to_value, rel_timeout)               futexlock_timedwaitwhile(ulockaddr, uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waituntil_2(ulockaddr, uaddr, not_equal_to_value)                        futexlock_waituntil(ulockaddr, uaddr, not_equal_to_value)
#define __PRIVATE_futexlock_waituntil_3(ulockaddr, uaddr, not_equal_to_value, rel_timeout)           futexlock_timedwaituntil(ulockaddr, uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_equal_2(ulockaddr, uaddr, equal_to_value)                      futexlock_waitwhile_equal(ulockaddr, uaddr, equal_to_value)
#define __PRIVATE_futexlock_waitwhile_equal_3(ulockaddr, uaddr, equal_to_value, rel_timeout)         futexlock_timedwaitwhile_equal(ulockaddr, uaddr, equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_notequal_2(ulockaddr, uaddr, not_equal_to_value)               futexlock_waitwhile_notequal(ulockaddr, uaddr, not_equal_to_value)
#define __PRIVATE_futexlock_waitwhile_notequal_3(ulockaddr, uaddr, not_equal_to_value, rel_timeout)  futexlock_timedwaitwhile_notequal(ulockaddr, uaddr, not_equal_to_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_above_2(ulockaddr, uaddr, above_value)                         futexlock_waitwhile_above(ulockaddr, uaddr, above_value)
#define __PRIVATE_futexlock_waitwhile_above_3(ulockaddr, uaddr, above_value, rel_timeout)            futexlock_timedwaitwhile_above(ulockaddr, uaddr, above_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_below_2(ulockaddr, uaddr, below_value)                         futexlock_waitwhile_below(ulockaddr, uaddr, below_value)
#define __PRIVATE_futexlock_waitwhile_below_3(ulockaddr, uaddr, below_value, rel_timeout)            futexlock_timedwaitwhile_below(ulockaddr, uaddr, below_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_aboveequal_2(ulockaddr, uaddr, above_equal_value)              futexlock_waitwhile_aboveequal(ulockaddr, uaddr, above_equal_value)
#define __PRIVATE_futexlock_waitwhile_aboveequal_3(ulockaddr, uaddr, above_equal_value, rel_timeout) futexlock_timedwaitwhile_aboveequal(ulockaddr, uaddr, above_equal_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_belowequal_2(ulockaddr, uaddr, below_equal_value)              futexlock_waitwhile_belowequal(ulockaddr, uaddr, below_equal_value)
#define __PRIVATE_futexlock_waitwhile_belowequal_3(ulockaddr, uaddr, below_equal_value, rel_timeout) futexlock_timedwaitwhile_belowequal(ulockaddr, uaddr, below_equal_value, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_cmpxch_3(ulockaddr, uaddr, old_value, new_value)               futexlock_waitwhile_cmpxch(ulockaddr, uaddr, old_value, new_value)
#define __PRIVATE_futexlock_waitwhile_cmpxch_4(ulockaddr, uaddr, old_value, new_value, rel_timeout)  futexlock_timedwaitwhile_cmpxch(ulockaddr, uaddr, old_value, new_value, rel_timeout)
#define __PRIVATE_futexlock_waituntil_cmpxch_3(ulockaddr, uaddr, old_value, new_value)               futexlock_waituntil_cmpxch(ulockaddr, uaddr, old_value, new_value)
#define __PRIVATE_futexlock_waituntil_cmpxch_4(ulockaddr, uaddr, old_value, new_value, rel_timeout)  futexlock_timedwaituntil_cmpxch(ulockaddr, uaddr, old_value, new_value, rel_timeout)
#define __PRIVATE_futexlock_waitlock_1(ulockaddr, uaddr)                                             futexlock_waitlock(ulockaddr, uaddr)
#define __PRIVATE_futexlock_waitlock_2(ulockaddr, uaddr, rel_timeout)                                futexlock_timedwaitlock(ulockaddr, uaddr, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_exactbits_3(ulockaddr, uaddr, bitmask, setmask)                futexlock_waitwhile_exactbits(ulockaddr, uaddr, bitmask, setmask)
#define __PRIVATE_futexlock_waitwhile_exactbits_4(ulockaddr, uaddr, bitmask, setmask, rel_timeout)   futexlock_timedwaitwhile_exactbits(ulockaddr, uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futexlock_waituntil_exactbits_3(ulockaddr, uaddr, bitmask, setmask)                futexlock_waituntil_exactbits(ulockaddr, uaddr, bitmask, setmask)
#define __PRIVATE_futexlock_waituntil_exactbits_4(ulockaddr, uaddr, bitmask, setmask, rel_timeout)   futexlock_timedwaituntil_exactbits(ulockaddr, uaddr, bitmask, setmask, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_anybit_2(ulockaddr, uaddr, bitmask)                            futexlock_waitwhile_anybit(ulockaddr, uaddr, bitmask)
#define __PRIVATE_futexlock_waitwhile_anybit_3(ulockaddr, uaddr, bitmask, rel_timeout)               futexlock_timedwaitwhile_anybit(ulockaddr, uaddr, bitmask, rel_timeout)
#define __PRIVATE_futexlock_waitwhile_allbits_2(ulockaddr, uaddr, bitmask)                           futexlock_waitwhile_allbits(ulockaddr, uaddr, bitmask)
#define __PRIVATE_futexlock_waitwhile_allbits_3(ulockaddr, uaddr, bitmask, rel_timeout)              futexlock_timedwaitwhile_allbits(ulockaddr, uaddr, bitmask, rel_timeout)
#define futexlock_waitwhile(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waituntil(...)                      __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waituntil_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_equal(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_equal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_notequal(...)             __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_notequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_above(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_above_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_below(...)                __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_below_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_aboveequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_aboveequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_belowequal(...)           __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_belowequal_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_cmpxch(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waituntil_cmpxch(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waituntil_cmpxch_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitlock(...)                       __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitlock_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitlock(...)                       __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitlock_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waituntil_exactbits(...)            __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waituntil_exactbits_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_anybit(...)               __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_anybit_, (__VA_ARGS__))(__VA_ARGS__)
#define futexlock_waitwhile_allbits(...)              __HYBRID_PP_VA_OVERLOAD(__PRIVATE_futexlock_waitwhile_allbits_, (__VA_ARGS__))(__VA_ARGS__)
#endif /* !__cplusplus */
}


%{


#endif /* __CC__ */

__SYSDECL_END

}