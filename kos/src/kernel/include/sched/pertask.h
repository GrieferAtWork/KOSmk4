/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PERTASK_H
#define GUARD_KERNEL_INCLUDE_SCHED_PERTASK_H 1

#include <kernel/compiler.h>

#include <sched/arch/pertask.h>

#include <hybrid/typecore.h>

#ifdef __CC__

#if defined(__INTELLISENSE__) && defined(__cplusplus)
struct task;
struct cpu;
struct vm;
extern "C++" {
template<class __T> __T &(FORTASK)(struct task *__restrict self, __T &x);
template<class __T> __T &(FORCPU)(struct cpu *__restrict self, __T &x);
template<class __T> __T &(FORVM)(struct vm *__restrict self, __T &x);
}
#define FORTASK FORTASK
#define FORCPU  FORCPU
#define FORVM   FORVM
#else
#define FORTASK(self,x)  (*(__typeof__(&(x)))((__UINTPTR_TYPE__)(self)+(__UINTPTR_TYPE__)&(x)))
#define FORCPU(self,x)   (*(__typeof__(&(x)))((__UINTPTR_TYPE__)(self)+(__UINTPTR_TYPE__)&(x)))
#define FORVM(self,x)    (*(__typeof__(&(x)))((__UINTPTR_TYPE__)(self)+(__UINTPTR_TYPE__)&(x)))
#endif


#ifndef PERTASK
#error "Arch didn't `#define PERTASK'"
#endif /* !PERTASK */
#ifndef PERTASK_GET
#define PERTASK_GET(x)       PERTASK(x)
#endif
#ifndef PERTASK_SET
#define PERTASK_SET(x,value) (void)(PERTASK(x)=(value))
#endif
#ifndef THIS_TASK
#define THIS_TASK   PERTASK_GET(*(struct task *)0)
#endif /* !THIS_TASK */

#ifdef __INTELLISENSE__
#undef PERTASK
#undef PERTASK_GET
#undef PERTASK_SET
extern "C++" {
template<class T> T &PERTASK(T &x);
template<class T> T PERTASK_GET(T &x);
template<class T> void PERTASK_SET(T &x, T value);
}
#define PERTASK     PERTASK
#define PERTASK_GET PERTASK_GET
#define PERTASK_SET PERTASK_SET
#endif

#ifndef PERCPU
#ifdef CONFIG_NO_SMP
DECL_BEGIN
INTDEF __UINT8_TYPE__ ___bootcpu[] ASMNAME("_bootcpu");
DECL_END
#define PERCPU(x)   (*(__typeof__(&(x)))(___bootcpu+(__UINTPTR_TYPE__)&(x)))
#else
DATDEF __UINTPTR_TYPE__ ___this_cpu ASMNAME("this_cpu");
#define PERCPU(x)   (*(__typeof__(&(x)))(PERTASK_GET(___this_cpu)+(__UINTPTR_TYPE__)&(x)))
#endif
#endif /* !PERCPU */

#ifndef PERTASK_TEST
#define PERTASK_TEST(x) (!!PERTASK_GET(x))
#endif
#ifndef PERTASK_INC
#define PERTASK_INC(x)  (void)++PERTASK(x)
#endif
#ifndef PERTASK_DEC
#define PERTASK_DEC(x)  (void)--PERTASK(x)
#endif


/* >> void KCALL func(struct task *__restrict self);
 * Invoked during task_alloc(). */
#define DEFINE_PERTASK_INIT(func)    DEFINE_CALLBACK(".rodata.callback.pertask.init",func)

/* >> NOBLOCK void NOTHROW(KCALL func)(struct task *__restrict self);
 * Invoked during task_destroy(). */
#define DEFINE_PERTASK_FINI(func)    DEFINE_CALLBACK(".rodata.callback.pertask.fini",func)

/* >> void KCALL func(struct task *__restrict new_thread, uintptr_t flags);
 * Invoked to initialize a given clone `new_thread' of the calling thread.
 * @param: flags: Set of `CLONE_*' from `<bits/sched.h>' */
#define DEFINE_PERTASK_CLONE(func)   DEFINE_CALLBACK(".rodata.callback.pertask.clone",func)

/* >> void NOTHROW(KCALL func)(void);
 * Invoked during task_exit(). */
#define DEFINE_PERTASK_ONEXIT(func)  DEFINE_CALLBACK(".rodata.callback.pertask.onexit",func)

#endif

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PERTASK_H */
