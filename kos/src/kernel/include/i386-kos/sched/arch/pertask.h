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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H 1

#include <kernel/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>

DECL_BEGIN

#ifdef __x86_64__
#define X86_PERTASK_SEGMENT     %gs
#define X86_PERTASK_SEGMENT_S  "%gs"
#define X86_PERTASK_SEGMENT_F "%%gs"
#else
#define X86_PERTASK_SEGMENT     %fs
#define X86_PERTASK_SEGMENT_S  "%fs"
#define X86_PERTASK_SEGMENT_F "%%fs"
#endif

#ifdef __CC__
struct task;

#define THIS_TASK   __get_this_task()
FORCELOCAL ATTR_CONST WUNUSED
struct task *NOTHROW(KCALL __get_this_task)(void) {
	register struct task *__result;
#ifdef __x86_64__
	__asm__("movq " X86_PERTASK_SEGMENT_F ":0, %0\n"
	        : "=r" (__result));
#else
	__asm__("movl " X86_PERTASK_SEGMENT_F ":0, %0\n"
	        : "=r" (__result));
#endif
	return __result;
}
#define PERTASK(x)    (*(__typeof__(&(x)))__get_per_task((void *)&(x)))
FORCELOCAL ATTR_CONST WUNUSED
void *NOTHROW(KCALL __get_per_task)(void *__ptr) {
	register void *__result;
#ifdef __x86_64__
	__asm__("addq " X86_PERTASK_SEGMENT_F ":0, %0\n"
	        : "=r" (__result)
	        : "0" (__ptr));
#else
	__asm__("addl " X86_PERTASK_SEGMENT_F ":0, %0\n"
	        : "=r" (__result)
	        : "0" (__ptr));
#endif
	return __result;
}

extern ATTR_ERROR("Invalid per-task object size") void __invalid_pertask_object_size(void);
#ifdef __x86_64__
#define PERTASK_GET(x) \
  XBLOCK({ __typeof__(x) __pt_res; \
           if __untraced(sizeof(__pt_res) == 1) { \
               __asm__("movb " X86_PERTASK_SEGMENT_F ":%p1, %b0" : "=q" (__pt_res) : "mi" (x)); \
           } else if __untraced(sizeof(__pt_res) == 2) { \
               __asm__("movw " X86_PERTASK_SEGMENT_F ":%p1, %w0" : "=r" (__pt_res) : "mi" (x)); \
           } else if __untraced(sizeof(__pt_res) == 4) { \
               __asm__("movl " X86_PERTASK_SEGMENT_F ":%p1, %k0" : "=r" (__pt_res) : "mi" (x)); \
           } else if __untraced(sizeof(__pt_res) == 8) { \
               __asm__("movq " X86_PERTASK_SEGMENT_F ":%p1, %q0" : "=r" (__pt_res) : "mi" (x)); \
           } else { \
               __invalid_pertask_object_size(); \
           } \
           XRETURN __pt_res; })
#define PERTASK_SET(x,v) \
  XBLOCK({ if __untraced(sizeof(x) == 1) { \
               __asm__("movb %b0, " X86_PERTASK_SEGMENT_F ":%p1" : : "q" (v), "mi" (x)); \
           } else if __untraced(sizeof(x) == 2) { \
               __asm__("movw %w0, " X86_PERTASK_SEGMENT_F ":%p1" : : "r" (v), "mi" (x)); \
           } else if __untraced(sizeof(x) == 4) { \
               __asm__("movl %k0, " X86_PERTASK_SEGMENT_F ":%p1" : : "r" (v), "mi" (x)); \
           } else if __untraced(sizeof(x) == 8) { \
               __asm__("movq %q0, " X86_PERTASK_SEGMENT_F ":%p1" : : "r" (v), "mi" (x)); \
           } else { \
               __invalid_pertask_object_size(); \
           } \
           (void)0; })
#else
#define PERTASK_GET(x) \
  XBLOCK({ __typeof__(x) __pt_res; \
           if __untraced(sizeof(__pt_res) == 1) { \
               __asm__("movb " X86_PERTASK_SEGMENT_F ":%p1, %b0" : "=q" (__pt_res) : "mi" (x)); \
           } else if __untraced(sizeof(__pt_res) == 2) { \
               __asm__("movw " X86_PERTASK_SEGMENT_F ":%p1, %w0" : "=r" (__pt_res) : "mi" (x)); \
           } else if __untraced(sizeof(__pt_res) == 4) { \
               __asm__("movl " X86_PERTASK_SEGMENT_F ":%p1, %k0" : "=r" (__pt_res) : "mi" (x)); \
           } else { \
               __invalid_pertask_object_size(); \
           } \
           XRETURN __pt_res; })
#define PERTASK_SET(x,v) \
  XBLOCK({ if __untraced(sizeof(x) == 1) { \
               __asm__("movb %b0, " X86_PERTASK_SEGMENT_F ":%p1" : : "q" (v), "mi" (x)); \
           } else if __untraced(sizeof(x) == 2) { \
               __asm__("movw %w0, " X86_PERTASK_SEGMENT_F ":%p1" : : "r" (v), "mi" (x)); \
           } else if __untraced(sizeof(x) == 4) { \
               __asm__("movl %k0, " X86_PERTASK_SEGMENT_F ":%p1" : : "r" (v), "mi" (x)); \
           } else { \
               __invalid_pertask_object_size(); \
           } \
           (void)0; })
#endif
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H */
