/* HASH CRC-32:0xce83b03c */
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
#ifndef __local_rtm_begin_defined
#define __local_rtm_begin_defined 1
#include <__crt.h>
#include <kos/bits/rtm.h>
#ifdef __arch_rtm_begin
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(rtm_begin) __rtm_status_t
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(rtm_begin))(void) {
	return __arch_rtm_begin();
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_rtm_begin_defined
#define __local___localdep_rtm_begin_defined 1
#define __localdep_rtm_begin __LIBC_LOCAL_NAME(rtm_begin)
#endif /* !__local___localdep_rtm_begin_defined */
#else /* __arch_rtm_begin */
#undef __local_rtm_begin_defined
#endif /* !__arch_rtm_begin */
#endif /* !__local_rtm_begin_defined */
