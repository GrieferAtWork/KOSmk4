/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%[default:section(".text.crt{|.dos}.system.rtm")]

%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <kos/anno.h>
)]%[insert:prefix(
#include <kos/asm/rtm.h> /* [__RTM_STARTED, ...], __RTM_NOSYS */
)]%[insert:prefix(
#include <kos/bits/rtm.h>
)]%{

/* RTM abort reason flags. */
#if !defined(RTM_ABORT_FAILED) && defined(__RTM_ABORT_FAILED)
#define RTM_ABORT_FAILED   __RTM_ABORT_FAILED   /* Transaction cannot be performed atomically. */
#endif /* !RTM_ABORT_FAILED && __RTM_ABORT_FAILED */
#if !defined(RTM_ABORT_EXPLICIT) && defined(__RTM_ABORT_EXPLICIT)
#define RTM_ABORT_EXPLICIT __RTM_ABORT_EXPLICIT /* Abort was caused by `sys_rtm_abort()' (s.a. `RTM_ABORT_CODE()'). */
#endif /* !RTM_ABORT_EXPLICIT && __RTM_ABORT_EXPLICIT */
#if !defined(RTM_ABORT_RETRY) && defined(__RTM_ABORT_RETRY)
#define RTM_ABORT_RETRY    __RTM_ABORT_RETRY    /* The transaction may succeed if re-attempted. */
#endif /* !RTM_ABORT_RETRY && __RTM_ABORT_RETRY */
#if !defined(RTM_ABORT_CAPACITY) && defined(__RTM_ABORT_CAPACITY)
#define RTM_ABORT_CAPACITY __RTM_ABORT_CAPACITY /* The internal buffer to track transactions overflowed. */
#endif /* !RTM_ABORT_CAPACITY && __RTM_ABORT_CAPACITY */
#if !defined(RTM_ABORT_CODE_M) && defined(__RTM_ABORT_CODE_M)
#define RTM_ABORT_CODE_M   __RTM_ABORT_CODE_M   /* [valid_if(RTM_ABORT_EXPLICIT)] XABORT argument. */
#endif /* !RTM_ABORT_CODE_M && __RTM_ABORT_CODE_M */
#if !defined(RTM_ABORT_CODE_S) && defined(__RTM_ABORT_CODE_S)
#define RTM_ABORT_CODE_S   __RTM_ABORT_CODE_S   /* Shift for `RTM_ABORT_CODE_M'. */
#endif /* !RTM_ABORT_CODE_S && __RTM_ABORT_CODE_S */

/* Helper macro for extracting the abort code (as passed to `rtm_abort()')
 * from a given  `rtm_status_t x' when  `x & RTM_ABORT_EXPLICIT' is  true. */
#if !defined(RTM_ABORT_CODE) && defined(__RTM_ABORT_CODE_M) && defined(__RTM_ABORT_CODE_S)
#define RTM_ABORT_CODE(/*rtm_status_t*/ x) \
	(__CCAST(unsigned int)(((x)&__RTM_ABORT_CODE_M) >> __RTM_ABORT_CODE_S))
#endif /* !RTM_ABORT_CODE && __RTM_ABORT_CODE_M && __RTM_ABORT_CODE_S */

/* Returned by `rtm_begin()' when RTM isn't supported.
 * NOTE: When this macro isn't defined, then RTM is always supported */
#if !defined(RTM_NOSYS) && defined(__RTM_NOSYS)
#define RTM_NOSYS __RTM_NOSYS /* RTM isn't supposed */
#endif /* !RTM_NOSYS && __RTM_NOSYS */

/* Returned  by  `rtm_begin()' when  RTM was  entered successfully.
 * NOTE: When this macro isn't defined, then RTM is never supported */
#if !defined(RTM_STARTED) && defined(__RTM_STARTED)
#define RTM_STARTED __RTM_STARTED /* RTM was entered */
#endif /* !RTM_STARTED && __RTM_STARTED */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __rtm_status_t_defined
#define __rtm_status_t_defined
/* RTM status code:
 *   - One of `RTM_NOSYS' or `RTM_STARTED'
 *   - Or a set of `RTM_ABORT_*', possibly or'd with `RTM_ABORT_CODE()' */
typedef __rtm_status_t rtm_status_t;
#endif /* !__rtm_status_t_defined */

}

%[define_type_class(__rtm_status_t = "TIn(__SIZEOF_RTM_STATUS_T__)")]
%[define_type_class(rtm_status_t = "TIn(__SIZEOF_RTM_STATUS_T__)")]
%[define_replacement(rtm_status_t = __rtm_status_t)]


@@>> rtm_begin(2)
@@Begin  an  RTM operation.  Note that  if  the arch-specific  RTM driver
@@wasn't already loaded into the kernel, it will be loaded automatically,
@@though any error that may happen during this will result in `RTM_NOSYS'
@@begin returned.
@@Note that while an RTM  operation is in progress,  only a very small  hand
@@full  of system calls are allowed to  be used. Attempting to use arbitrary
@@system calls will most likely  result in an `RTM_ABORT_FAILED' error,  and
@@attempting to access too much system memory in general will result in this
@@function returning  with  `RTM_ABORT_CAPACITY',  rather  than  succeeding.
@@The following is  a list  of system calls  which are  whitelisted for  use
@@during a transaction:
@@  - rtm_begin(2):  Nested RTM operation
@@  - rtm_end(2):    End an RTM operation
@@  - rtm_abort(2):  Abort an RTM operation
@@  - rtm_test(2):   Check if an RTM operation is in progress (always returns `1')
@@Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
@@@return: RTM_STARTED : RTM operation was started.
@@@return: RTM_NOSYS   : RTM isn't supposed because the RTM driver is missing, or cannot be loaded.
@@@return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>')
[[nothrow, decl_include("<kos/bits/rtm.h>"), crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RTM_BEGIN))]]
[[if($extended_include_prefix("<kos/bits/rtm.h>")defined(__arch_rtm_begin)), preferred_fast_extern_inline("rtm_begin", { return __arch_rtm_begin(); })]]
[[userimpl, requires_include("<kos/bits/rtm.h>"), requires(defined(__arch_rtm_begin))]]
rtm_status_t rtm_begin() {
	return __arch_rtm_begin();
}

@@>> rtm_end(2)
@@End a transaction
@@If the transaction was successful, return normally
@@If the transaction failed, `rtm_begin()' returns `RTM_ABORT_*'
@@If no transaction was in  progress, the behavior is  undefined
[[nothrow, crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RTM_END))]]
[[if($extended_include_prefix("<kos/bits/rtm.h>")defined(__arch_rtm_end)), preferred_fast_extern_inline("rtm_end", { __arch_rtm_end(); })]]
[[userimpl, requires_include("<kos/bits/rtm.h>"), requires(defined(__arch_rtm_end))]]
void rtm_end() {
	__arch_rtm_end();
}

@@>> rtm_abort(2)
@@Abort  the   current  transaction   by   having  `rtm_begin()'   return   with
@@`RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
@@If no  transaction  was  in  progress, behave  as  a  no-op.  Otherwise,  this
@@function does not return normally, but returns from the original `rtm_begin()'
[[nothrow, crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RTM_ABORT))]]
[[if($extended_include_prefix("<kos/bits/rtm.h>")defined(__arch_rtm_abort)), preferred_fast_extern_inline("rtm_abort", { __arch_rtm_abort(code); })]]
[[userimpl, requires_include("<kos/bits/rtm.h>"), requires(defined(__arch_rtm_abort))]]
[[no_crt_dos_wrapper, cc(__FCALL)]]
void rtm_abort(unsigned int code) {
	__arch_rtm_abort(code);
}

@@>> rtm_test(2)
@@Check if a transaction is currently in progress
@@@return: 0 : No RTM operation in progress
@@@return: 1 : An RTM operation is currently in progress
[[pure, wunused, nothrow, crt_kos_impl_requires(!defined(LIBC_ARCH_HAVE_RTM_TEST))]]
[[if($extended_include_prefix("<kos/bits/rtm.h>")defined(__arch_rtm_test)), preferred_fast_extern_inline("rtm_test", { return __arch_rtm_test(); })]]
[[userimpl, requires_include("<kos/bits/rtm.h>"), requires(defined(__arch_rtm_test))]]
int rtm_test() {
	return __arch_rtm_test();
}


%{

__SYSDECL_END
#endif /* __CC__ */

}
