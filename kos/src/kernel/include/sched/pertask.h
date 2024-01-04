/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_PERTASK_H
#define GUARD_KERNEL_INCLUDE_SCHED_PERTASK_H 1

#include <kernel/compiler.h>

#include <hybrid/typecore.h>

#ifndef CONFIG_NO_SMP
#include <sched/arch/pertask.h>
#endif /* !CONFIG_NO_SMP */

#ifdef __CC__
#if defined(__INTELLISENSE__) && defined(__cplusplus)
struct task;
struct cpu;
struct mman;
extern "C++" {
#define FORTASK FORTASK
#define FORCPU  FORCPU
template<class __T> __T &(FORTASK)(struct task *__restrict self, __T &symbol);
template<class __T> __T const &(FORTASK)(struct task const *__restrict self, __T const &symbol);
template<class __T> __T &(FORCPU)(struct cpu *__restrict self, __T &symbol);
template<class __T> __T const &(FORCPU)(struct cpu const *__restrict self, __T const &symbol);
#ifndef FORMMAN
#define FORMMAN FORMMAN
template<class __T> __T &(FORMMAN)(struct mman *__restrict self, __T &symbol);
template<class __T> __T const &(FORMMAN)(struct mman const *__restrict self, __T const &symbol);
#endif /* !FORMMAN */
} /* extern "C++" */
#else /* __INTELLISENSE__ && __cplusplus */
#define FORTASK(self, symbol) (*(__typeof__(&(symbol)))((__UINTPTR_TYPE__)(self) + (__UINTPTR_TYPE__)&(symbol)))
#define FORCPU(self, symbol)  (*(__typeof__(&(symbol)))((__UINTPTR_TYPE__)(self) + (__UINTPTR_TYPE__)&(symbol)))
#ifndef FORMMAN
#define FORMMAN(self, symbol) (*(__typeof__(&(symbol)))((__UINTPTR_TYPE__)(self) + (__UINTPTR_TYPE__)&(symbol)))
#endif /* !FORMMAN */
#endif /* !__INTELLISENSE__ || !__cplusplus */


#ifdef CONFIG_NO_SMP
DATDEF struct task *bootcpu_sched_current;
#define THIS_TASK  ((struct task *)bootcpu_sched_current)
#define PERTASK(x) (*(__typeof__(&(x)))((__BYTE_TYPE__ *)bootcpu_sched_current + (__UINTPTR_TYPE__)(void *)&(x)))
#elif !defined(PERTASK)
#error "Arch didn't `#define PERTASK'"
#endif /* !PERTASK */

#ifndef PERTASK_GET
#define PERTASK_GET(x) PERTASK(x)
#endif /* !PERTASK_GET */

#ifndef PERTASK_SET
#define PERTASK_SET(x, value) (void)(PERTASK(x) = (value))
#endif /* !PERTASK_SET */

#ifndef THIS_TASK
#ifndef __this_task_defined
#define __this_task_defined
DATDEF ATTR_PERTASK struct task this_task; /* The current task (for use with `PERTASK') */
#endif /* !__this_task_defined */
#define THIS_TASK PERTASK(this_task)
#endif /* !THIS_TASK */

#ifdef __INTELLISENSE__
#undef PERTASK
#undef PERTASK_GET
#undef PERTASK_SET
#undef THIS_TASK
#define PERTASK     PERTASK
#define PERTASK_GET PERTASK_GET
#define PERTASK_SET PERTASK_SET
#define THIS_TASK   THIS_TASK
extern "C++" {
template<class T> T &PERTASK(T &x);
template<class T> T const &PERTASK(T const &x);
template<class T> T PERTASK_GET(T const &x);
template<class T, class V, class = decltype(PERTASK_GET<T>(*(V *)0))> void PERTASK_SET(T &x, V value);
extern struct task *THIS_TASK;
} /* extern "C++" */
#endif /* !__INTELLISENSE__ */

#ifndef PERCPU
#ifdef CONFIG_NO_SMP
#define PERCPU(x) x
#else /* CONFIG_NO_SMP */
DECL_BEGIN
DATDEF __UINTPTR_TYPE__ ___this_cpu ASMNAME("this_cpu");
DECL_END
#define PERCPU(x) (*(__typeof__(&(x)))(PERTASK_GET(___this_cpu) + (__UINTPTR_TYPE__)&(x)))
#endif /* !CONFIG_NO_SMP */
#endif /* !PERCPU */

#ifndef PERTASK_TESTMASK
#define PERTASK_TESTMASK(x, v) ((PERTASK_GET(x) & (v)) != 0)
#endif /* !PERTASK_TESTMASK */
#ifndef PERTASK_INC
#define PERTASK_INC(x) (void)++PERTASK(x)
#endif /* !PERTASK_INC */
#ifndef PERTASK_DEC
#define PERTASK_DEC(x) (void)--PERTASK(x)
#endif /* !PERTASK_DEC */

#ifndef PERTASK_EQ
#define PERTASK_EQ(x, rhs) (PERTASK_GET(x) == (rhs))
#ifndef PERTASK_NE
#define PERTASK_NE(x, rhs) (PERTASK_GET(x) != (rhs))
#endif /* !PERTASK_NE */
#else /* !PERTASK_EQ */
#ifndef PERTASK_NE
#define PERTASK_NE(x, rhs) (!PERTASK_EQ(x, rhs))
#endif /* !PERTASK_NE */
#endif /* PERTASK_EQ */

#ifndef PERTASK_TEST
#define PERTASK_TEST(x) PERTASK_NE(x, 0)
#endif /* !PERTASK_TEST */

#endif /* __CC__ */

/* >> NOBLOCK void NOTHROW(KCALL func)(struct task *__restrict self);
 * Invoked during task_destroy(). */
#define DEFINE_PERTASK_FINI(func) \
	DEFINE_CALLBACK(".rodata.callback.pertask.fini", func)

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_PERTASK_H */
