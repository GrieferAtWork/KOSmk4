/* HASH CRC-32:0xa9deb962 */
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
#ifndef __local_sigset_defined
#define __local_sigset_defined
#include <__crt.h>
#include <asm/os/signal.h>
#if defined(__SIG_ERR) && defined(__SIG_HOLD) && defined(__SIG_BLOCK) && (defined(__CRT_HAVE_sigprocmask) || defined(__CRT_HAVE___sigprocmask) || defined(__CRT_HAVE___libc_sigprocmask) || defined(__CRT_HAVE_pthread_sigmask) || defined(__CRT_HAVE_thr_sigsetmask)) && (defined(__CRT_HAVE_sigaction) || defined(__CRT_HAVE___sigaction))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sigaction_defined
#define __local___localdep_sigaction_defined
#ifdef __CRT_HAVE_sigaction
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),sigaction,(__signo,__act,__oact))
#elif defined(__CRT_HAVE___sigaction)
__NAMESPACE_LOCAL_END
struct sigaction;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN_OPT(2) __ATTR_OUT_OPT(3),int,__NOTHROW_NCX,__localdep_sigaction,(__signo_t __signo, struct sigaction const *__act, struct sigaction *__oact),__sigaction,(__signo,__act,__oact))
#else /* ... */
#undef __local___localdep_sigaction_defined
#endif /* !... */
#endif /* !__local___localdep_sigaction_defined */
#ifndef __local___localdep_sigaddset_defined
#define __local___localdep_sigaddset_defined
#ifdef __CRT_HAVE_sigaddset
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
#include <libc/errno.h>
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
#ifndef __local___localdep_sigismember_defined
#define __local___localdep_sigismember_defined
#ifdef __CRT_HAVE_sigismember
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
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
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#elif defined(__CRT_HAVE___sigismember)
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
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
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_sigismember,(struct __sigset_struct const *__set, __signo_t __signo),__sigismember,{ __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; })
#else /* ... */
__NAMESPACE_LOCAL_END
#include <bits/os/sigset.h>
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
__LOCAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) int __NOTHROW_NCX(__LIBCCALL __localdep_sigismember)(struct __sigset_struct const *__set, __signo_t __signo) { __ULONGPTR_TYPE__ __mask, __word; __PRIVATE_SIGSET_VALIDATE_SIGNO(__signo) __mask = __sigset_mask(__signo); __word = __sigset_word(__signo); return (__set->__val[__word] & __mask) __PRIVATE_SIGSET_ISMEMBER_EXT; }
#endif /* !... */
#endif /* !__local___localdep_sigismember_defined */
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
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <bits/os/sigaction.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigset) __sighandler_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigset))(__signo_t __signo, __sighandler_t __disp) {
	struct sigaction __act, __oact;
	struct __sigset_struct __set, __oset;
	if __unlikely(__disp == (__sighandler_t)__SIG_ERR)
		goto __err_inval;
	(__NAMESPACE_LOCAL_SYM __localdep_sigemptyset)(&__set);
	(__NAMESPACE_LOCAL_SYM __localdep_sigaddset)(&__set, __signo);
	if (__disp == (__sighandler_t)__SIG_HOLD) {
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigprocmask)(__SIG_BLOCK, &__set, &__oset) != 0)
			goto __err;
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigismember)(&__oset, __signo))
			goto __err;
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__signo, __NULLPTR, &__oact) != 0)
			goto __err;
		return __oact.sa_handler;
	}
	__act.sa_handler = __disp;
	(__NAMESPACE_LOCAL_SYM __localdep_sigemptyset)(&__act.sa_mask);
	__act.sa_flags = 0;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigaction)(__signo, &__act, &__oact) != 0)
		goto __err;
	if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_sigprocmask)(__SIG_UNBLOCK, &__set, &__oset) != 0)
		goto __err;
	return (__NAMESPACE_LOCAL_SYM __localdep_sigismember)(&__oset, __signo)
	       ? (__sighandler_t)__SIG_HOLD
	       : __oact.sa_handler;
__err_inval:
#ifdef __EINVAL
	(void)__libc_seterrno(__EINVAL);
#else /* __EINVAL */
	(void)__libc_seterrno(1);
#endif /* !__EINVAL */
__err:
	return (__sighandler_t)__SIG_ERR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigset_defined
#define __local___localdep_sigset_defined
#define __localdep_sigset __LIBC_LOCAL_NAME(sigset)
#endif /* !__local___localdep_sigset_defined */
#else /* __SIG_ERR && __SIG_HOLD && __SIG_BLOCK && (__CRT_HAVE_sigprocmask || __CRT_HAVE___sigprocmask || __CRT_HAVE___libc_sigprocmask || __CRT_HAVE_pthread_sigmask || __CRT_HAVE_thr_sigsetmask) && (__CRT_HAVE_sigaction || __CRT_HAVE___sigaction) */
#undef __local_sigset_defined
#endif /* !__SIG_ERR || !__SIG_HOLD || !__SIG_BLOCK || (!__CRT_HAVE_sigprocmask && !__CRT_HAVE___sigprocmask && !__CRT_HAVE___libc_sigprocmask && !__CRT_HAVE_pthread_sigmask && !__CRT_HAVE_thr_sigsetmask) || (!__CRT_HAVE_sigaction && !__CRT_HAVE___sigaction) */
#endif /* !__local_sigset_defined */
