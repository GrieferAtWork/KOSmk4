/* HASH CRC-32:0xffd5532 */
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
#ifndef __local_sigstack_defined
#define __local_sigstack_defined 1
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SS_ONSTACK) && defined(__SS_DISABLE) && defined(__CRT_HAVE_sigaltstack)
#include <bits/os/sigstack.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: sigaltstack from signal */
#ifndef __local___localdep_sigaltstack_defined
#define __local___localdep_sigaltstack_defined 1
/* >> sigaltstack(2)
 * Get/Set the alternate signal stack for the calling thread. When set,
 * the alternate signal stack can be used to host signal handlers that
 * have been established with the `SA_ONSTACK' flag in `sa_flags'.
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__CREDIRECT(,int,__NOTHROW_NCX,__localdep_sigaltstack,(struct sigaltstack const *__ss, struct sigaltstack *__oss),sigaltstack,(__ss,__oss))
#endif /* !__local___localdep_sigaltstack_defined */
/* >> sigstack(2)
 * Deprecated, and slightly different version of `sigaltstack(2)'
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
__LOCAL_LIBC(sigstack) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigstack))(struct sigstack *__ss, struct sigstack *__oss) {
	struct sigaltstack __ass, __aoss;
	int __result;
	if (__ss) {
		__ass.ss_flags = __ss->ss_onstack
		                 ? __SS_ONSTACK
		                 : __SS_DISABLE;
		__ass.ss_sp   = __ss->ss_sp;
		__ass.ss_size = (__SIZE_TYPE__)-1;
	}
	__result = __localdep_sigaltstack(__ss ? &__ass : __NULLPTR,
	                     __oss ? &__aoss : __NULLPTR);
	if (__likely(!__result) && __oss) {
		__oss->ss_onstack = !!(__aoss.ss_flags & __SS_ONSTACK);
		__oss->ss_sp      = __aoss.ss_sp;
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigstack_defined
#define __local___localdep_sigstack_defined 1
#define __localdep_sigstack __LIBC_LOCAL_NAME(sigstack)
#endif /* !__local___localdep_sigstack_defined */
#else /* __SS_ONSTACK && __SS_DISABLE && __CRT_HAVE_sigaltstack */
#undef __local_sigstack_defined
#endif /* !__SS_ONSTACK || !__SS_DISABLE || !__CRT_HAVE_sigaltstack */
#endif /* !__local_sigstack_defined */
