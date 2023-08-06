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
#ifndef _KOS_ANNO_H
#define _KOS_ANNO_H 1

/* KOS-specific data/function annotations. */

#include <__stdinc.h>

/*
 * The meaning of NOBLOCK vs. <neither> vs. BLOCKING
 *
 * NOBLOCK:   The  function can be safely called, even while holding atomic locks,
 *            though  not necessarily while holding SMP locks. You may assume that
 *            the function doesn't include a call to `task_yield()' (though it may
 *            include a call  to `task_tryyield[_or_pause]()'), and  as such  will
 *            never throw `E_WOULDBLOCK' if called with preemption disabled.
 *
 * <neither>: The function may  acquire atomic locks  and throw E_WOULDBLOCK  from
 *            within  `task_yield()'  if  such  a  lock  cannot  be  acquired when
 *            preemption isn't enabled. However, the function isn't a cancellation
 *            point, and won't try to service RPCs either.
 *
 * BLOCKING:  The function is a cancellation point, in that it includes code-paths
 *            that include calls to `task_serve()'. As such, the function must not
 *            be called while holding  any sort of atomic  lock, and care must  be
 *            taken  if called while holding non-atomic locks, in which case there
 *            exists the possibility of a deadlock scenario.
 *
 */

#ifdef __CHECKER__
#include <kos/except/checker.h>
#define __PHYS        __ATTR_PHYS
#define __VIRT        __ATTR_VIRT
#define __NCX         __ATTR_NCX
#define __UNCHECKED   __ATTR_UNCHECKED
#define __NOBLOCK     __ATTR_NOBLOCK
#define __NOBLOCK_IF  __ATTR_NOBLOCK_IF
#define __BLOCKING    __ATTR_BLOCKING
#define __BLOCKING_IF __ATTR_BLOCKING_IF
#define __NOPREEMPT   __ATTR_NOPREEMPT
#define __THROWS      __ATTR_THROWS
#define __THROWING    __ATTR_THROWS
#else /* __CHECKER__ */
#define __PHYS            /* Annotation for physical pointers */
#define __VIRT            /* Annotation for virtual pointers */
#define __NCX             /* Annotation for memory which (when accessed) may cause sporadic exceptions. */
#define __UNCHECKED       /* Annotation for unchecked memory (like `NCX', but access is not allowed) */
#define __NOBLOCK         /* Annotation for functions that are guarantied to never block,
                           * making them safe to-be called from any asynchronous context. */
#define __NOBLOCK_IF(x)   /* Same as `__NOBLOCK', but only when `x' is true. */
#define __BLOCKING        /* Annotation for functions that may block indefinitely (as well as service RPCs and be a cancellation point, unless otherwise documented) */
#define __BLOCKING_IF(x)  /* Annotation for functions that may block indefinitely (as well as service RPCs and be a cancellation point, unless otherwise documented) */
#define __NOPREEMPT       /* Annotation for functions that may only be called with preemption disabled. In user-
                           * space, this means that all posix-signals are masked (s.a.  `setsigmaskfullptr(3)'). */

#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __THROWS(...)     /* Annotation for the set of error codes/classes/sub-classes that may be thrown
                           * by a function.
                           * You may include `...' as a possible  error code to indicate that the  function
                           * is also allowed to  throw any other kind  of exception, usually indicative  of
                           * the  function  following  a  path  that  includes  a  call  to  `task_serve()'
                           * Note however that  this is merely  for documentation purposes,  as well as  to
                           * document the ~expected~ error codes  (e.g. anything that can throw  E_SEGFAULT
                           * usually does so by accessing user-space  memory, which also implies access  to
                           * VIO callbacks,  and the  fact that  VIO  is also  allowed to  throw  arbitrary
                           * exceptions, meaning that technically  speaking, `E_SEGFAULT' would also  imply
                           * `...'). Any function that isn't `__NOTHROW()' is still always allowed to throw
                           * any error that isn't apart of the `__THROWS()' set. */
#define __THROWING(...)   /* Like `__THROWS', but used where `__NOTHROW' would go */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __THROWS(e...)    /* ... */
#define __THROWING(e...)  /* Like `__THROWS', but used where `__NOTHROW' would go */
#endif /* ... */
#endif /* !__CHECKER__ */

#define __ABNORMAL_RETURN /* Annotation for functions that (may) not return normally, or by throwing an exception.
                           * Functions with this annotation must not be  called if there are any finally  handlers
                           * on-stack  which need to perform cleanup, or any EXCEPT-handlers that would want to do
                           * the same. The poster-example for this kind of behavior is `longjmp(3)' */

#define __WEAK            /* Annotation for weakly referenced data/data updated randomly with both the old/new state being valid. */
#define __REF             /* Annotation for reference holders/transfers.
                           * When used on a struct-field/local/global variable: Reference storage
                           * When used on a return  type:  The   function  returns  a   reference
                           * When used on an argument: The function inherits a reference (but look out for `inherit(<condition>)' annotations) */
#define __REF_IF(x)       /* Same as `__REF', but only when `x' is true. */

#if defined(__INTELLISENSE__) && defined(__cplusplus)
/* Highlight invalid use of this annotation in intellisense! */
#undef __THROWS
#define __THROWS(...) noexcept(false)
#undef __THROWING
#define __THROWING(...) __PRIVATE_THROWING
#define __PRIVATE_THROWING(...) (__VA_ARGS__) __PRIVATE_THROWING2
#define __PRIVATE_THROWING2(...) (__VA_ARGS__) noexcept(false)
#endif /* __clang_tidy__ && __cplusplus */

#ifdef __GUARD_HYBRID_COMPILER_H
#define PHYS            __PHYS
#define VIRT            __VIRT
#define NCX             __NCX
#define UNCHECKED       __UNCHECKED
#define REF             __REF
#define REF_IF          __REF_IF
#define NOBLOCK         __NOBLOCK
#define NOBLOCK_IF      __NOBLOCK_IF
#define BLOCKING        __BLOCKING
#define BLOCKING_IF     __BLOCKING_IF
#define NOPREEMPT       __NOPREEMPT
#define ABNORMAL_RETURN __ABNORMAL_RETURN
#define THROWS          __THROWS
#ifndef WEAK
#define WEAK __WEAK
#endif /* !WEAK */
#endif /* __GUARD_HYBRID_COMPILER_H */

#endif /* !_KOS_ANNO_H */
