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

%[define_replacement(lfutex_t = __uintptr_t)]
%[define_replacement(syscall_ulong_t = __syscall_ulong_t)]
%[define_replacement(timespec32 = __timespec32)]
%[define_replacement(timespec64 = __timespec64)]
%[default:section(".text.crt{|.dos}.sched.futexexpr")]
%[default:nodos]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <kos/asm/futex.h>
)]%[insert:prefix(
#include <kos/bits/futex-expr.h>
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

/* Mandatory expression list terminator. */
#define LFUTEXEXPR_END LFUTEXEXPR_INIT(0, LFUTEX_EXPREND, 0, 0)

/* Initializers for futex expressions. */
#define LFUTEXEXPR_EQUAL(offset, value)                     LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_WHILE, value, 0)                                                      /* x == value */
#define LFUTEXEXPR_NOT_EQUAL(offset, value)                 LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_UNTIL, value, 0)                                                      /* x != value */
#define LFUTEXEXPR_ABOVE(offset, value)                     LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_WHILE_ABOVE, value, 0)                                                /* x > value */
#define LFUTEXEXPR_BELOW(offset, value)                     LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_WHILE_BELOW, value, 0)                                                /* x < value */
#define LFUTEXEXPR_ABOVE_EQUAL(offset, value)               LFUTEXEXPR_INIT(offset, (value) ? LFUTEX_WAIT_WHILE_ABOVE : LFUTEX_NOP, (value)-1, 0)                     /* x >= value */
#define LFUTEXEXPR_BELOW_EQUAL(offset, value)               LFUTEXEXPR_INIT(offset, ((value) != (lfutex_t)-1) ? LFUTEX_WAIT_WHILE_BELOW : LFUTEX_NOP, (value) + 1, 0) /* x <= value */
#define LFUTEXEXPR_ANYBIT(offset, bitmask)                  LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_UNTIL_BITMASK, bitmask, 0)                                            /* (x & bitmask) != 0 */
#define LFUTEXEXPR_ALLBITS(offset, bitmask)                 LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_WHILE_BITMASK, bitmask, bitmask)                                      /* (x & bitmask) == bitmask */
#define LFUTEXEXPR_EXACT_BITS(offset, bitmask, setmask)     LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_WHILE_BITMASK, bitmask, setmask)                                      /* (x & bitmask) == setmask */
#define LFUTEXEXPR_NOT_EXACT_BITS(offset, bitmask, setmask) LFUTEXEXPR_INIT(offset, LFUTEX_WAIT_UNTIL_BITMASK, bitmask, setmask)                                      /* (x & bitmask) != setmask */

/* Initializers for futex expressions (helpers for struct types). */
#define LFUTEXEXPR_TEQUAL(Type, Field, value)                     LFUTEXEXPR_EQUAL(__builtin_offsetof(Type, Field), value)
#define LFUTEXEXPR_TNOT_EQUAL(Type, Field, value)                 LFUTEXEXPR_NOT_EQUAL(__builtin_offsetof(Type, Field), value)
#define LFUTEXEXPR_TABOVE(Type, Field, value)                     LFUTEXEXPR_ABOVE(__builtin_offsetof(Type, Field), value)
#define LFUTEXEXPR_TBELOW(Type, Field, value)                     LFUTEXEXPR_BELOW(__builtin_offsetof(Type, Field), value)
#define LFUTEXEXPR_TABOVE_EQUAL(Type, Field, value)               LFUTEXEXPR_ABOVE_EQUAL(__builtin_offsetof(Type, Field), value)
#define LFUTEXEXPR_TBELOW_EQUAL(Type, Field, value)               LFUTEXEXPR_BELOW_EQUAL(__builtin_offsetof(Type, Field), value)
#define LFUTEXEXPR_TANYBIT(Type, Field, bitmask)                  LFUTEXEXPR_INIT(__builtin_offsetof(Type, Field), LFUTEX_WAIT_UNTIL_BITMASK, bitmask, 0)       /* (x & bitmask) != 0 */
#define LFUTEXEXPR_TALLBITS(Type, Field, bitmask)                 LFUTEXEXPR_INIT(__builtin_offsetof(Type, Field), LFUTEX_WAIT_WHILE_BITMASK, bitmask, bitmask) /* (x & bitmask) == bitmask */
#define LFUTEXEXPR_TEXACT_BITS(Type, Field, bitmask, setmask)     LFUTEXEXPR_INIT(__builtin_offsetof(Type, Field), LFUTEX_WAIT_WHILE_BITMASK, bitmask, setmask) /* (x & bitmask) == setmask */
#define LFUTEXEXPR_TNOT_EXACT_BITS(Type, Field, bitmask, setmask) LFUTEXEXPR_INIT(__builtin_offsetof(Type, Field), LFUTEX_WAIT_UNTIL_BITMASK, bitmask, setmask) /* (x & bitmask) != setmask */

#if defined(__cplusplus) && !defined(__CHECKER__)
__NAMESPACE_INT_BEGIN
extern "C++" {

/* Syntax-sugar  */
class __LFutexExprOffsetMask {
private:
	__ptrdiff_t       __m_offset;
	__syscall_ulong_t __m_bitmask;
public:
	__CXX_CLASSMEMBER __LFutexExprOffsetMask(__ptrdiff_t __offset, __syscall_ulong_t __bitmask) __CXX_NOEXCEPT
	    : __m_offset(__offset)
	    , __m_bitmask(__bitmask) {}
	__CXX_CLASSMEMBER struct lfutexexpr operator==(__syscall_ulong_t __setmask) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = LFUTEX_WAIT_WHILE_BITMASK;
		__res.fe_val       = __m_bitmask;
		__res.fe_val2      = __setmask;
		return __res;
	}
	__CXX_CLASSMEMBER struct lfutexexpr operator!=(__syscall_ulong_t __setmask) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = LFUTEX_WAIT_UNTIL_BITMASK;
		__res.fe_val       = __m_bitmask;
		__res.fe_val2      = __setmask;
		return __res;
	}
};

class __LFutexExprOffset {
private:
	__ptrdiff_t __m_offset;
public:
	__CXX_CLASSMEMBER __LFutexExprOffset(__ptrdiff_t __offset) __CXX_NOEXCEPT
	    : __m_offset(__offset) {}
	__CXX_CLASSMEMBER struct lfutexexpr operator==(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = LFUTEX_WAIT_WHILE;
		__res.fe_val       = __val;
		__res.fe_val2      = 0;
		return __res;
	}
	__CXX_CLASSMEMBER struct lfutexexpr operator!=(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = LFUTEX_WAIT_UNTIL;
		__res.fe_val       = __val;
		__res.fe_val2      = 0;
		return __res;
	}
	__CXX_CLASSMEMBER struct lfutexexpr operator<(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = LFUTEX_WAIT_WHILE_BELOW;
		__res.fe_val       = __val;
		__res.fe_val2      = 0;
		return __res;
	}
	__CXX_CLASSMEMBER struct lfutexexpr operator>(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = LFUTEX_WAIT_WHILE_ABOVE;
		__res.fe_val       = __val;
		__res.fe_val2      = 0;
		return __res;
	}
	__CXX_CLASSMEMBER struct lfutexexpr operator<=(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = __val != (lfutex_t)-1 ? LFUTEX_WAIT_WHILE_BELOW : LFUTEX_NOP;
		__res.fe_val       = __val + 1;
		__res.fe_val2      = 0;
		return __res;
	}
	__CXX_CLASSMEMBER struct lfutexexpr operator>=(__syscall_ulong_t __val) const __CXX_NOEXCEPT {
		struct lfutexexpr __res;
		__res.fe_offset    = __m_offset;
		__res.fe_condition = __val ? LFUTEX_WAIT_WHILE_ABOVE : LFUTEX_NOP;
		__res.fe_val       = __val - 1;
		__res.fe_val2      = 0;
		return __res;
	}
	__CXX_CLASSMEMBER __LFutexExprOffsetMask operator&(__syscall_ulong_t __bitmask) const __CXX_NOEXCEPT {
		return __LFutexExprOffsetMask(__m_offset, __bitmask);
	}
};
}
__NAMESPACE_INT_END

#define LFUTEXEXPR_FIELD(Type, Field) \
	(__NAMESPACE_INT_SYM __LFutexExprOffset(__builtin_offsetof(Type, Field)))
#define LFUTEXEXPR_OFFSET(offset) \
	(__NAMESPACE_INT_SYM __LFutexExprOffset(offset))
#endif /* __cplusplus && !__CHECKER__ */

};


[[decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
[[cp, doc_alias("lfutexexpr"), ignore, nocrt, alias("lfutexexpr")]]
int crt_lfutexexpr32([[nonnull]] lfutex_t *ulockaddr, void *base,
                     [[in]] struct lfutexexpr const *expr,
                     [[in_opt]] struct $timespec32 const *timeout,
                     unsigned int timeout_flags);
[[decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
[[cp, doc_alias("lfutexexpr64"), ignore, nocrt, alias("lfutexexpr64")]]
int crt_lfutexexpr64([[nonnull]] lfutex_t *ulockaddr, void *base,
                     [[in]] struct lfutexexpr const *expr,
                     [[in_opt]] struct $timespec64 const *timeout,
                     unsigned int timeout_flags);

[[ignore, nocrt, alias("LFutexExpr"), cp, doc_alias("LFutexExpr_except")]]
[[decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
int crt_LFutexExpr32_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                            [[in]] struct lfutexexpr const *expr,
                            [[in_opt]] struct $timespec32 const *timeout,
                            unsigned int timeout_flags);
[[ignore, nocrt, alias("LFutexExpr64"), cp, doc_alias("LFutexExpr64_except")]]
[[decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
int crt_LFutexExpr64_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                            [[in]] struct lfutexexpr const *expr,
                            [[in_opt]] struct $timespec64 const *timeout,
                            unsigned int timeout_flags);
[[ignore, nocrt, alias("LFutexExprI"), cp, doc_alias("LFutexExprI_except")]]
[[decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
int crt_LFutexExprI32_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                             [[in]] struct lfutexexpr const *expr,
                             [[in_opt]] struct $timespec32 const *timeout,
                             unsigned int timeout_flags);
[[ignore, nocrt, alias("LFutexExprI64"), cp, doc_alias("LFutexExprI64_except")]]
[[decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
int crt_LFutexExprI64_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                             [[in]] struct lfutexexpr const *expr,
                             [[in_opt]] struct $timespec64 const *timeout,
                             unsigned int timeout_flags);






@@>> lfutexexpr(2), lfutexexpr64(2)
@@The lfutexexpr(2) system call can be used to specify arbitrarily complex
@@expressions that must atomically (in relation to other futex operations)
@@hold true before the scheduler will suspend the calling thread.
@@@param: ulockaddr:     The futex on which to wait
@@@param: base:          Base pointer added to the `fe_offset' fields of given expressions
@@@param: expr:          Vector of expressions for which to check, terminated by `LFUTEX_EXPREND'
@@@param: timeout:       Timeout for wait operations (s.a. `LFUTEX_WAIT_FLAG_TIMEOUT_*')
@@@param: timeout_flags: Set of `LFUTEX_WAIT_FLAG_TIMEOUT_*'
@@@return: * : The first  non-zero  return value  from  executing  all of  the  given  `expr'
@@             in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
@@             to see their  possible return  values, which are  always `0'  when they  would
@@             perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
@@             thread had to perform a wait operation, at which point this function returning
@@             that value means that you've once again been re-awoken.
@@@return: -1:EFAULT:    A faulty pointer was given
@@@return: -1:EINVAL:    One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
@@@return: -1:EINTR:     A blocking futex-wait operation was interrupted
@@@return: -1:ETIMEDOUT: A blocking futex-wait operation has timed out
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("lfutexexpr")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("lfutexexpr64")]]
[[userimpl, requires($has_function(crt_lfutexexpr32) || $has_function(crt_lfutexexpr64))]]
[[section(".text.crt{|.dos}.sched.futexlockexpr")]]
int lfutexexpr([[nonnull]] lfutex_t *ulockaddr, void *base,
               [[in]] struct lfutexexpr const *expr,
               [[in_opt]] struct timespec const *timeout,
               unsigned int timeout_flags) {
@@pp_if $has_function(crt_lfutexexpr32)@@
	struct timespec32 tms32;
	if (!timeout)
		return crt_lfutexexpr32(ulockaddr, base, expr, NULL, 0);
	tms32.tv_sec  = (time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return crt_lfutexexpr32(ulockaddr, base, expr, &tms32, timeout_flags);
@@pp_else@@
	struct timespec64 tms64;
	if (!timeout)
		return crt_lfutexexpr64(ulockaddr, base, expr, NULL, 0);
	tms64.tv_sec  = (time64_t)timeout->tv_sec;
	tms64.tv_nsec = timeout->tv_nsec;
	return crt_lfutexexpr64(ulockaddr, base, expr, &tms64, timeout_flags);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[cp, decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
[[preferred_time64_variant_of(lfutexexpr), doc_alias("lfutexexpr")]]
[[userimpl, requires_function(crt_lfutexexpr32), section(".text.crt{|.dos}.sched.futexlockexpr")]]
int lfutexexpr64([[nonnull]] lfutex_t *ulockaddr, void *base,
                 [[in]] struct lfutexexpr const *expr,
                 [[in_opt]] struct timespec64 const *timeout,
                 unsigned int timeout_flags) {
	struct timespec32 tms32;
	if (!timeout)
		return crt_lfutexexpr32(ulockaddr, base, expr, NULL, 0);
	tms32.tv_sec  = (time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return crt_lfutexexpr32(ulockaddr, base, expr, &tms32, timeout_flags);
}
%#endif /* __USE_TIME64 */





@@>> LFutexExpr(2), LFutexExpr64(2)
@@Excetion-enabled version of `lfutexexpr(2)'
@@@return: * :  The first  non-zero  return value  from  executing  all of  the  given  `expr'
@@              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
@@              to see their  possible return  values, which are  always `0'  when they  would
@@              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
@@              thread had to perform a wait operation, at which point this function returning
@@              that value means that you've once again been re-awoken.
@@@return: < 0: Timeout expired
@@@throws: E_SEGFAULT:         A faulty pointer was given
@@@throws: E_INVALID_ARGUMENT: One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
@@@throws: E_INTERRUPT:        A blocking futex-wait operation was interrupted
[[cp, throws, decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("LFutexExpr")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("LFutexExpr64")]]
[[userimpl, requires($has_function(crt_LFutexExpr32_except) ||
                     $has_function(crt_LFutexExpr64_except))]]
[[section(".text.crt{|.dos}.sched.futexlockexpr")]]
[[exposed_name("LFutexExpr"), crt_name("LFutexExpr")]]
int LFutexExpr_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                      [[in]] struct lfutexexpr const *expr,
                      [[in_opt]] struct timespec const *timeout,
                      unsigned int timeout_flags) {
@@pp_if $has_function(crt_LFutexExpr32_except)@@
	struct timespec32 tms32;
	if (!timeout)
		return crt_LFutexExpr32_except(ulockaddr, base, expr, NULL, timeout_flags);
	tms32.tv_sec  = (time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return crt_LFutexExpr32_except(ulockaddr, base, expr, &tms32, timeout_flags);
@@pp_else@@
	struct timespec64 tms64;
	if (!timeout)
		return crt_LFutexExpr64_except(ulockaddr, base, expr, NULL, timeout_flags);
	tms64.tv_sec  = (time64_t)timeout->tv_sec;
	tms64.tv_nsec = timeout->tv_nsec;
	return crt_LFutexExpr64_except(ulockaddr, base, expr, &tms64, timeout_flags);
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[cp, throws, decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
[[preferred_time64_variant_of(LFutexExpr), doc_alias("LFutexExpr_except")]]
[[userimpl, requires_function(crt_LFutexExpr32_except), section(".text.crt{|.dos}.sched.futexlockexpr")]]
[[exposed_name("LFutexExpr64"), crt_name("LFutexExpr64")]]
int LFutexExpr64_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                        [[in]] struct lfutexexpr const *expr,
                        [[in_opt]] struct timespec64 const *timeout,
                        unsigned int timeout_flags) {
	struct timespec32 tms32;
	if (!timeout)
		return crt_LFutexExpr32_except(ulockaddr, base, expr, NULL, timeout_flags);
	tms32.tv_sec  = (time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return crt_LFutexExpr32_except(ulockaddr, base, expr, &tms32, timeout_flags);
}
%#endif /* __USE_TIME64 */



@@>> LFutexExprI(2), LFutexExprI64(2)
@@Same as `LFutexExpr()', but implicitly handle `E_INTERRUPT' exceptions by re-starting the system call.
@@@return: * :  The first  non-zero  return value  from  executing  all of  the  given  `expr'
@@              in order (s.a. the documentations of the individual `LFUTEX_WAIT_*'  functions
@@              to see their  possible return  values, which are  always `0'  when they  would
@@              perform a wait  operation, and usually  `1' otherwise) or  `0' if the  calling
@@              thread had to perform a wait operation, at which point this function returning
@@              that value means that you've once again been re-awoken.
@@@return: < 0: Timeout expired
@@@throws: E_SEGFAULT:         A faulty pointer was given
@@@throws: E_INVALID_ARGUMENT: One of the given commands is invalid, or `expr[0].fe_condition == LFUTEX_EXPREND'
[[cp, throws, decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>"), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("LFutexExprI")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__), alias("LFutexExprI64")]]
[[requires($has_function(crt_LFutexExprI32_except) || $has_function(crt_LFutexExprI64_except) ||
           (defined(__cplusplus) && defined(__KOS__) && $has_function(LFutexExpr_except)))]]
[[section(".text.crt{|.dos}.sched.futexlockexpr")]]
[[exposed_name("LFutexExprI"), crt_name("LFutexExprI")]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !($has_function(crt_LFutexExprI32_except) || $has_function(crt_LFutexExprI64_except))@@
#include <kos/except.h>
@@pp_endif@@
)]]
int LFutexExprI_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                       [[in]] struct lfutexexpr const *expr,
                       [[in_opt]] struct timespec const *timeout,
                       unsigned int timeout_flags) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_LFutexExprI32_except)@@
	struct timespec32 tms32;
	if (!timeout)
		return crt_LFutexExprI32_except(ulockaddr, base, expr, NULL, timeout_flags);
	tms32.tv_sec  = (time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return crt_LFutexExprI32_except(ulockaddr, base, expr, &tms32, timeout_flags);
@@pp_elif !defined(__BUILDING_LIBC) && $has_function(crt_LFutexExprI64_except)@@
	struct timespec64 tms64;
	if (!timeout)
		return crt_LFutexExprI64_except(ulockaddr, base, expr, NULL, timeout_flags);
	tms64.tv_sec  = (time64_t)timeout->tv_sec;
	tms64.tv_nsec = timeout->tv_nsec;
	return crt_LFutexExprI64_except(ulockaddr, base, expr, &tms64, timeout_flags);
@@pp_else@@
	for (;;) {
@@pp_if defined(@TRY@)@@
		@TRY@
@@pp_endif@@
		{
			return LFutexExpr_except(ulockaddr, base, expr, timeout, timeout_flags);
		}
@@pp_if defined(@TRY@)@@
		@EXCEPT@ {
			if (!@was_thrown@(@E_INTERRUPT@))
				@RETHROW@();
		}
@@pp_endif@@
	}
@@pp_endif@@
}

%
%#ifdef __USE_TIME64
[[cp, throws, decl_include("<bits/types.h>", "<bits/os/timespec.h>", "<kos/bits/futex-expr.h>")]]
[[preferred_time64_variant_of(LFutexExprI), doc_alias("LFutexExprI_except")]]
[[exposed_name("LFutexExprI64"), crt_name("LFutexExprI64")]]
[[section(".text.crt{|.dos}.sched.futexlockexpr")]]
[[requires($has_function(crt_LFutexExprI32_except) ||
           (defined(__cplusplus) && defined(__KOS__) && $has_function(LFutexExpr64_except)))]]
[[impl_prefix(
@@pp_if defined(__BUILDING_LIBC) || !$has_function(crt_LFutexExprI32_except)@@
#include <kos/except.h>
@@pp_endif@@
)]]
int LFutexExprI64_except([[nonnull]] lfutex_t *ulockaddr, void *base,
                         [[in]] struct lfutexexpr const *expr,
                         [[in_opt]] struct timespec64 const *timeout,
                         unsigned int timeout_flags) {
@@pp_if !defined(__BUILDING_LIBC) && $has_function(crt_LFutexExprI32_except)@@
	struct timespec32 tms32;
	if (!timeout)
		return crt_LFutexExprI32_except(ulockaddr, base, expr, NULL, 0);
	tms32.tv_sec  = (time32_t)timeout->tv_sec;
	tms32.tv_nsec = timeout->tv_nsec;
	return crt_LFutexExprI32_except(ulockaddr, base, expr, &tms32, timeout_flags);
@@pp_else@@
	for (;;) {
@@pp_if defined(@TRY@)@@
		@TRY@
@@pp_endif@@
		{
			return LFutexExpr64_except(ulockaddr, base, expr, timeout, timeout_flags);
		}
@@pp_if defined(@TRY@)@@
		@EXCEPT@ {
			if (!@was_thrown@(@E_INTERRUPT@))
				@RETHROW@();
		}
@@pp_endif@@
	}
@@pp_endif@@
}
%#endif /* __USE_TIME64 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
