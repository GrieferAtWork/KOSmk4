/* HASH CRC-32:0x3b0bc031 */
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
#ifndef _KOS_RTM_H
#define _KOS_RTM_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/asm/rtm.h> /* [__RTM_STARTED, ...], __RTM_NOSYS */
#include <kos/bits/rtm.h>

/* RTM abort reason flags. */
#ifdef __RTM_ABORT_FAILED
#define RTM_ABORT_FAILED   __RTM_ABORT_FAILED   /* Transaction cannot be performed atomically. */
#endif /* __RTM_ABORT_FAILED */
#ifdef __RTM_ABORT_EXPLICIT
#define RTM_ABORT_EXPLICIT __RTM_ABORT_EXPLICIT /* Abort was caused by `sys_rtm_abort()' (s.a. `RTM_ABORT_CODE()'). */
#endif /* __RTM_ABORT_EXPLICIT */
#ifdef __RTM_ABORT_RETRY
#define RTM_ABORT_RETRY    __RTM_ABORT_RETRY    /* The transaction may succeed if re-attempted. */
#endif /* __RTM_ABORT_RETRY */
#ifdef __RTM_ABORT_CAPACITY
#define RTM_ABORT_CAPACITY __RTM_ABORT_CAPACITY /* The internal buffer to track transactions overflowed. */
#endif /* __RTM_ABORT_CAPACITY */
#ifdef __RTM_ABORT_CODE_M
#define RTM_ABORT_CODE_M   __RTM_ABORT_CODE_M   /* [valid_if(RTM_ABORT_EXPLICIT)] XABORT argument. */
#endif /* __RTM_ABORT_CODE_M */
#ifdef __RTM_ABORT_CODE_S
#define RTM_ABORT_CODE_S   __RTM_ABORT_CODE_S   /* Shift for `RTM_ABORT_CODE_M'. */
#endif /* __RTM_ABORT_CODE_S */

/* Helper macro for extracting the abort code (as passed to `rtm_abort()')
 * from a given `rtm_status_t x' when `x & RTM_ABORT_EXPLICIT' is true. */
#if defined(RTM_ABORT_CODE_M) && defined(RTM_ABORT_CODE_S)
#define RTM_ABORT_CODE(/*rtm_status_t*/ x) \
	(__CCAST(unsigned int)(((x)&RTM_ABORT_CODE_M) >> RTM_ABORT_CODE_S))
#endif /* RTM_ABORT_CODE_M && RTM_ABORT_CODE_S */

/* Returned by `rtm_begin()' when RTM isn't supported.
 * NOTE: When this macro isn't defined, then RTM is always supported */
#ifdef __RTM_NOSYS
#define RTM_NOSYS __RTM_NOSYS /* RTM isn't supposed */
#endif /* __RTM_NOSYS */

/* Returned by `rtm_begin()' when RTM was entered successfully.
 * NOTE: When this macro isn't defined, then RTM is never supported */
#ifdef __RTM_STARTED
#define RTM_STARTED __RTM_STARTED /* RTM was entered */
#endif /* __RTM_STARTED */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __rtm_status_t_defined
#define __rtm_status_t_defined 1
/* RTM status code:
 *   - One of `RTM_NOSYS' or `RTM_STARTED'
 *   - Or a set of `RTM_ABORT_*', possibly or'd with `RTM_ABORT_CODE()' */
typedef __rtm_status_t rtm_status_t;
#endif /* !__rtm_status_t_defined */

#if defined(__arch_rtm_begin) && defined(__CRT_HAVE_rtm_begin)
/* Begin an RTM operation. Note that if the arch-specific RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls, or attempting to access too much system memory in general
 * will result in this function returning with `RTM_ABORT_CAPACITY', rather
 * than succeeding. The following is a list of system calls which are
 * whitelisted for use during a transaction:
 *   - rtm_begin:  Nested RTM operation
 *   - rtm_end:    End an RTM operation
 *   - rtm_abort:  Abort an RTM operation
 *   - rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the associated driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
__CEIDECLARE(,rtm_status_t,__NOTHROW,rtm_begin,(void),{ return __arch_rtm_begin(); })
#elif defined(__CRT_HAVE_rtm_begin)
/* Begin an RTM operation. Note that if the arch-specific RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls, or attempting to access too much system memory in general
 * will result in this function returning with `RTM_ABORT_CAPACITY', rather
 * than succeeding. The following is a list of system calls which are
 * whitelisted for use during a transaction:
 *   - rtm_begin:  Nested RTM operation
 *   - rtm_end:    End an RTM operation
 *   - rtm_abort:  Abort an RTM operation
 *   - rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the associated driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
__CDECLARE(,rtm_status_t,__NOTHROW,rtm_begin,(void),())
#elif defined(__arch_rtm_begin)
#include <local/kos.rtm/rtm_begin.h>
/* Begin an RTM operation. Note that if the arch-specific RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM operation is in progress, only a very small hand
 * full of system calls are allowed to be used. Attempting to use arbitrary
 * system calls, or attempting to access too much system memory in general
 * will result in this function returning with `RTM_ABORT_CAPACITY', rather
 * than succeeding. The following is a list of system calls which are
 * whitelisted for use during a transaction:
 *   - rtm_begin:  Nested RTM operation
 *   - rtm_end:    End an RTM operation
 *   - rtm_abort:  Abort an RTM operation
 *   - rtm_test:   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the associated driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
__NAMESPACE_LOCAL_USING_OR_IMPL(rtm_begin, __FORCELOCAL __ATTR_ARTIFICIAL rtm_status_t __NOTHROW(__LIBCCALL rtm_begin)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rtm_begin))(); })
#endif /* ... */
#if defined(__arch_rtm_end) && defined(__CRT_HAVE_rtm_end)
/* End a transaction
 * If the transaction was successful, return normally
 * If the transaction failed, `rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, the behavior is undefined */
__CEIDECLARE(,void,__NOTHROW,rtm_end,(void),{ __arch_rtm_end(); })
#elif defined(__CRT_HAVE_rtm_end)
/* End a transaction
 * If the transaction was successful, return normally
 * If the transaction failed, `rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, the behavior is undefined */
__CDECLARE_VOID(,__NOTHROW,rtm_end,(void),())
#elif defined(__arch_rtm_end)
#include <local/kos.rtm/rtm_end.h>
/* End a transaction
 * If the transaction was successful, return normally
 * If the transaction failed, `rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in progress, the behavior is undefined */
__NAMESPACE_LOCAL_USING_OR_IMPL(rtm_end, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW(__LIBCCALL rtm_end)(void) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rtm_end))(); })
#endif /* ... */
#if defined(__arch_rtm_abort) && defined(__CRT_HAVE_rtm_abort)
/* Abort the current transaction by having `rtm_begin()' return with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op. Otherwise, this
 * function does not return normally, but returns from the original `rtm_begin()' */
__COMPILER_EIDECLARE(__LIBC,,void,__NOTHROW__FCALL,,rtm_abort,(unsigned int __code),{ __arch_rtm_abort(__code); })
#elif defined(__CRT_HAVE_rtm_abort)
/* Abort the current transaction by having `rtm_begin()' return with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op. Otherwise, this
 * function does not return normally, but returns from the original `rtm_begin()' */
__LIBC void __NOTHROW(__FCALL rtm_abort)(unsigned int __code) __CASMNAME_SAME("rtm_abort");
#elif defined(__arch_rtm_abort)
#include <local/kos.rtm/rtm_abort.h>
/* Abort the current transaction by having `rtm_begin()' return with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no transaction was in progress, behave as a no-op. Otherwise, this
 * function does not return normally, but returns from the original `rtm_begin()' */
__NAMESPACE_LOCAL_USING_OR_IMPL(rtm_abort, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW(__FCALL rtm_abort)(unsigned int __code) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rtm_abort))(__code); })
#endif /* ... */
#if defined(__arch_rtm_test) && defined(__CRT_HAVE_rtm_test)
/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
__CEIDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,rtm_test,(void),{ return __arch_rtm_test(); })
#elif defined(__CRT_HAVE_rtm_test)
/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW,rtm_test,(void),())
#elif defined(__arch_rtm_test)
#include <local/kos.rtm/rtm_test.h>
/* Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
__NAMESPACE_LOCAL_USING_OR_IMPL(rtm_test, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED int __NOTHROW(__LIBCCALL rtm_test)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rtm_test))(); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_RTM_H */
