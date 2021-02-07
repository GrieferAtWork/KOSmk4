/* HASH CRC-32:0x4bb004df */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_setsigmaskfullptr_defined
#define __local_setsigmaskfullptr_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_setsigmaskptr
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: setsigmaskptr from signal */
#ifndef __local___localdep_setsigmaskptr_defined
#define __local___localdep_setsigmaskptr_defined 1
/* >> setsigmaskptr(3)
 * Set the current signal mask pointer to `sigmaskptr'
 * This is a kos-specific function that can be used to
 * speed up/replace calls to `sigprocmask()'. But using
 * this function safely requires knowledge of its underlying
 * semantics. If you're unsure on those, you should instead
 * just use the portable `sigprocmask()' and forget you ever
 * read this comment :)
 * Example usage:
 * >> static sigset_t const fullset = SIGSET_INIT_FULL;
 * >> sigset_t *oldset = setsigmaskptr((sigset_t *)&fullset);
 * >> // Code in here executes with all maskable signals masked
 * >> // Note however that code in here also mustn't call sigprocmask()
 * >> setsigmaskptr(oldset);
 * Equivalent code using sigprocmask (which has way more overhead):
 * >> static sigset_t const fullset = SIGSET_INIT_FULL;
 * >> sigset_t oldset;
 * >> sigprocmask(SIG_SETMASK, &fullset, &oldset);
 * >> // Code in here executes with all maskable signals masked
 * >> sigprocmask(SIG_SETMASK, &oldset, NULL);
 * @param: sigmaskptr: Address of the signal mask to use from now on.
 * @return: * : Address of the previously used signal mask. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1)),struct __sigset_struct *,__NOTHROW_NCX,__localdep_setsigmaskptr,(struct __sigset_struct *__sigmaskptr),setsigmaskptr,(__sigmaskptr))
#endif /* !__local___localdep_setsigmaskptr_defined */
/* >> setsigmaskfullptr(3)
 * Same as `setsigmaskptr()', but set a statically allocated, fully
 * filled signal mask as the calling thread's current signal mask.
 * This essentially means that this function can be used to temporarily
 * disable the reception of all signals within the calling thread, thus
 * allowing the thread to run without being interrupted (by another but
 * SIGKILL and SIGSTOP, which can't be masked), until the returned signal
 * mask is restored.
 * >> sigset_t *os;
 * >> os = setsigmaskfullptr();
 * >> ...
 * >> setsigmaskptr(os); */
__LOCAL_LIBC(setsigmaskfullptr) __ATTR_RETNONNULL struct __sigset_struct *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setsigmaskfullptr))(void) {
	static struct __sigset_struct const __ss_full = __SIGSET_INIT((__ULONGPTR_TYPE__)-1);
	return __localdep_setsigmaskptr((struct __sigset_struct *)&__ss_full);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setsigmaskfullptr_defined
#define __local___localdep_setsigmaskfullptr_defined 1
#define __localdep_setsigmaskfullptr __LIBC_LOCAL_NAME(setsigmaskfullptr)
#endif /* !__local___localdep_setsigmaskfullptr_defined */
#else /* __CRT_HAVE_setsigmaskptr */
#undef __local_setsigmaskfullptr_defined
#endif /* !__CRT_HAVE_setsigmaskptr */
#endif /* !__local_setsigmaskfullptr_defined */
