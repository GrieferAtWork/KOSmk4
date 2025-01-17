/* HASH CRC-32:0xad71095c */
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
#ifndef __local_set_single_signal_masked_defined
#define __local_set_single_signal_masked_defined
#include <__crt.h>
#if defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sigaddset_defined
#define __local___localdep_sigaddset_defined
#ifdef __CRT_HAVE_sigaddset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#include <libc/errno.h>
#include <asm/os/signal.h>
#include <hybrid/typecore.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_sigaddset,(struct __sigset_struct *__set, __signo_t __signo),sigaddset,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; })
#elif defined(__CRT_HAVE___sigaddset)
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#include <libc/errno.h>
#include <asm/os/signal.h>
#include <hybrid/typecore.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_sigaddset,(struct __sigset_struct *__set, __signo_t __signo),__sigaddset,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; })
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#include <libc/errno.h>
#include <asm/os/signal.h>
#include <hybrid/typecore.h>
#ifndef __PRIVATE_SIGSET_VALIDATE_SIGNO
#if defined(__KERNEL__) && __SIZEOF_INT__ >= __SIZEOF_POINTER__
#define __PRIVATE_SIGSET_ISMEMBER_EXT /* nothing */
#else /* __KERNEL__ && __SIZEOF_INT__ >= __SIZEOF_POINTER__ */
#define __PRIVATE_SIGSET_ISMEMBER_EXT != 0
#endif /* !__KERNEL__ && __SIZEOF_INT__ < __SIZEOF_POINTER__ */
#if defined(__KERNEL__) && defined(__KOS__)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) /* nothing */
#elif defined(__NSIG) && defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(__EINVAL);          \
	}
#elif defined(__NSIG)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo)     \
	if __unlikely(signo <= 0 || signo >= __NSIG) { \
		return __libc_seterrno(1);                 \
	}
#elif defined(__EINVAL)
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(__EINVAL);      \
	}
#else /* ... */
#define __PRIVATE_SIGSET_VALIDATE_SIGNO(signo) \
	if __unlikely(signo <= 0) {                \
		return __libc_seterrno(1);             \
	}
#endif /* !... */
#endif /* !__PRIVATE_SIGSET_VALIDATE_SIGNO */
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_INOUT(1) int __NOTHROW_NCX(__LIBCCALL __localdep_sigaddset)(struct __sigset_struct *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); __set->__val[__word] |= __mask; return 0; }
#endif /* !... */
#endif /* !__local___localdep_sigaddset_defined */
#ifndef __local___localdep_sigemptyset_defined
#define __local___localdep_sigemptyset_defined
#ifdef __CRT_HAVE_sigemptyset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_sigemptyset,(struct __sigset_struct *__set),sigemptyset,(__set))
#else /* __CRT_HAVE_sigemptyset */
__NAMESPACE_LOCAL_END
#include <libc/local/signal/sigemptyset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sigemptyset __LIBC_LOCAL_NAME(sigemptyset)
#endif /* !__CRT_HAVE_sigemptyset */
#endif /* !__local___localdep_sigemptyset_defined */
#ifndef __local___localdep_sigprocmask_defined
#define __local___localdep_sigprocmask_defined
#ifdef __CRT_HAVE_sigprocmask
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE___libc_sigprocmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),__libc_sigprocmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_pthread_sigmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),pthread_sigmask,(__how,__set,__oset))
#elif defined(__CRT_HAVE_thr_sigsetmask)
__NAMESPACE_LOCAL_END
struct __sigset_struct;
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigprocmask,(__STDC_INT_AS_UINT_T __how, struct __sigset_struct const *__set, struct __sigset_struct *__oset),thr_sigsetmask,(__how,__set,__oset))
#else /* ... */
#undef __local___localdep_sigprocmask_defined
#endif /* !... */
#endif /* !__local___localdep_sigprocmask_defined */
__LOCAL_LIBC(set_single_signal_masked) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(set_single_signal_masked))(__signo_t __sig, int __how) {
	struct __sigset_struct __set;
	(__NAMESPACE_LOCAL_SYM __localdep_sigemptyset)(&__set);
	(__NAMESPACE_LOCAL_SYM __localdep_sigaddset)(&__set, __sig);
	return (__NAMESPACE_LOCAL_SYM __localdep_sigprocmask)(__how, &__set, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_set_single_signal_masked_defined
#define __local___localdep_set_single_signal_masked_defined
#define __localdep_set_single_signal_masked __LIBC_LOCAL_NAME(set_single_signal_masked)
#endif /* !__local___localdep_set_single_signal_masked_defined */
#else /* __CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask */
#undef __local_set_single_signal_masked_defined
#endif /* !__CRT_HAVE_sigprocmask && !__CRT_HAVE___sigprocmask && !__CRT_HAVE___libc_sigprocmask && !__CRT_HAVE_pthread_sigmask && !__CRT_HAVE_thr_sigsetmask */
#endif /* !__local_set_single_signal_masked_defined */
