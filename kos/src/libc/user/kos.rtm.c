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
#ifndef GUARD_LIBC_USER_KOS_RTM_C
#define GUARD_LIBC_USER_KOS_RTM_C 1

#include "../api.h"
/**/

#include <kos/except.h>
#include <kos/syscalls.h>

#include <syscall.h>

#include "kos.rtm.h"

DECL_BEGIN

#undef OS_HAVE_RTM
#if (defined(SYS_rtm_begin) && defined(SYS_rtm_end) && \
     defined(SYS_rtm_abort) && defined(SYS_rtm_test))
#define OS_HAVE_RTM 1
#endif /* SYS_rtm_... */

/*[[[head:libc_rtm_begin,hash:CRC-32=0x157cee05]]]*/
#ifndef LIBC_ARCH_HAVE_RTM_BEGIN
/* >> rtm_begin(2)
 * Begin  an  RTM operation.  Note that  if  the arch-specific  RTM driver
 * wasn't already loaded into the kernel, it will be loaded automatically,
 * though any error that may happen during this will result in `RTM_NOSYS'
 * begin returned.
 * Note that while an RTM  operation is in progress,  only a very small  hand
 * full  of system calls are allowed to  be used. Attempting to use arbitrary
 * system calls will most likely  result in an `RTM_ABORT_FAILED' error,  and
 * attempting to access too much system memory in general will result in this
 * function returning  with  `RTM_ABORT_CAPACITY',  rather  than  succeeding.
 * The following is  a list  of system calls  which are  whitelisted for  use
 * during a transaction:
 *   - rtm_begin(2):  Nested RTM operation
 *   - rtm_end(2):    End an RTM operation
 *   - rtm_abort(2):  Abort an RTM operation
 *   - rtm_test(2):   Check if an RTM operation is in progress (always returns `1')
 * Anything else will most likely result in this system call returning `RTM_ABORT_FAILED'
 * @return: RTM_STARTED : RTM operation was started.
 * @return: RTM_NOSYS   : RTM isn't supposed because the RTM driver is missing, or cannot be loaded.
 * @return: RTM_ABORT_* : RTM operation failed (s.a. code from `<kos/rtm.h>') */
INTERN ATTR_SECTION(".text.crt.system.rtm") rtm_status_t
NOTHROW(LIBCCALL libc_rtm_begin)(void)
/*[[[body:libc_rtm_begin]]]*/
{
#ifdef OS_HAVE_RTM
	return sys_rtm_begin();
#else /* OS_HAVE_RTM */
	return libc_seterrno(ENOSYS);
#endif /* !OS_HAVE_RTM */
}
#endif /* MAGIC:impl_if */
/*[[[end:libc_rtm_begin]]]*/

/*[[[head:libc_rtm_end,hash:CRC-32=0x1b9142a7]]]*/
#ifndef LIBC_ARCH_HAVE_RTM_END
/* >> rtm_end(2)
 * End a transaction
 * If the transaction was successful, return normally
 * If the transaction failed, `rtm_begin()' returns `RTM_ABORT_*'
 * If no transaction was in  progress, the behavior is  undefined */
INTERN ATTR_SECTION(".text.crt.system.rtm") void
NOTHROW(LIBCCALL libc_rtm_end)(void)
/*[[[body:libc_rtm_end]]]*/
{
#ifdef OS_HAVE_RTM
	sys_rtm_end();
#endif /* OS_HAVE_RTM */
}
#endif /* MAGIC:impl_if */
/*[[[end:libc_rtm_end]]]*/

/*[[[head:libc_rtm_abort,hash:CRC-32=0x357b8f8d]]]*/
#ifndef LIBC_ARCH_HAVE_RTM_ABORT
/* >> rtm_abort(2)
 * Abort  the   current  transaction   by   having  `rtm_begin()'   return   with
 * `RTM_ABORT_EXPLICIT | ((code << RTM_ABORT_CODE_S) & RTM_ABORT_CODE_M)'
 * If no  transaction  was  in  progress, behave  as  a  no-op.  Otherwise,  this
 * function does not return normally, but returns from the original `rtm_begin()' */
INTERN ATTR_SECTION(".text.crt.system.rtm") void
NOTHROW(__FCALL libc_rtm_abort)(unsigned int code)
/*[[[body:libc_rtm_abort]]]*/
{
#ifdef OS_HAVE_RTM
	sys_rtm_abort((syscall_ulong_t)code);
#else /* OS_HAVE_RTM */
	(void)code; /* no-op */
#endif /* !OS_HAVE_RTM */
}
#endif /* MAGIC:impl_if */
/*[[[end:libc_rtm_abort]]]*/

/*[[[head:libc_rtm_test,hash:CRC-32=0x1102dfb0]]]*/
#ifndef LIBC_ARCH_HAVE_RTM_TEST
/* >> rtm_test(2)
 * Check if a transaction is currently in progress
 * @return: 0 : No RTM operation in progress
 * @return: 1 : An RTM operation is currently in progress */
INTERN ATTR_SECTION(".text.crt.system.rtm") ATTR_PURE WUNUSED int
NOTHROW(LIBCCALL libc_rtm_test)(void)
/*[[[body:libc_rtm_test]]]*/
{
#ifdef OS_HAVE_RTM
	return sys_rtm_test();
#else /* OS_HAVE_RTM */
	COMPILER_IMPURE();
	/* Always indicate outside-of-rtm */
	return 0;
#endif /* !OS_HAVE_RTM */
}
#endif /* MAGIC:impl_if */
/*[[[end:libc_rtm_test]]]*/



/*[[[start:exports,hash:CRC-32=0xe0fcce17]]]*/
#ifndef LIBC_ARCH_HAVE_RTM_BEGIN
DEFINE_PUBLIC_ALIAS(rtm_begin, libc_rtm_begin);
#endif /* !LIBC_ARCH_HAVE_RTM_BEGIN */
#ifndef LIBC_ARCH_HAVE_RTM_END
DEFINE_PUBLIC_ALIAS(rtm_end, libc_rtm_end);
#endif /* !LIBC_ARCH_HAVE_RTM_END */
#ifndef LIBC_ARCH_HAVE_RTM_ABORT
DEFINE_PUBLIC_ALIAS(rtm_abort, libc_rtm_abort);
#endif /* !LIBC_ARCH_HAVE_RTM_ABORT */
#ifndef LIBC_ARCH_HAVE_RTM_TEST
DEFINE_PUBLIC_ALIAS(rtm_test, libc_rtm_test);
#endif /* !LIBC_ARCH_HAVE_RTM_TEST */
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_RTM_C */
