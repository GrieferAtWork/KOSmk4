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
#else /* __x86_64__ */
#define X86_PERTASK_SEGMENT     %fs
#define X86_PERTASK_SEGMENT_S  "%fs"
#define X86_PERTASK_SEGMENT_F "%%fs"
#endif /* !__x86_64__ */

#ifdef __cplusplus
/* g++ will lie about support for alternative address spaces:
 *   - In c++-mode, fs/gs segments are unavailable (because it's a c-extension; ugh...)
 *   - Even under C, gcc will lie about support when gnu extensions aren't enabled.
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=87626
 *   - F%$king hell man... why???? And why lie about it?
 */
#undef __SEG_FS
#undef __SEG_GS
#endif /* __cplusplus */

#ifdef __CC__
struct task;

#ifdef __x86_64__
#ifdef __SEG_GS
#define __X86_SEG_TASK __seg_gs
#endif /* __SEG_GS */
#else /* __x86_64__ */
#ifdef __SEG_FS
#define __X86_SEG_TASK __seg_fs
#endif /* __SEG_FS */
#endif /* !__x86_64__ */



#define THIS_TASK   __get_this_task()
FORCELOCAL ATTR_CONST WUNUSED
struct task *NOTHROW(KCALL __get_this_task)(void) {
	__register struct task *__result;
#ifdef __X86_SEG_TASK
	__result = (struct task *)*(__X86_SEG_TASK __UINTPTR_TYPE__ *)0;
#elif defined(__x86_64__)
	__asm__("movq %%gs:0, %0\n" : "=r" (__result));
#else /* __x86_64__ */
	__asm__("movl %%fs:0, %0\n" : "=r" (__result));
#endif /* !__x86_64__ */
	return __result;
}

#define PERTASK(x) (*(__typeof__(&(x)))__get_per_task((void *)&(x)))
FORCELOCAL ATTR_CONST WUNUSED
void *NOTHROW(KCALL __get_per_task)(void *__ptr) {
	__register void *__result;
#ifdef __X86_SEG_TASK
	__result = (void *)(*(__X86_SEG_TASK __UINTPTR_TYPE__ *)0 + (__UINTPTR_TYPE__)__ptr);
#elif defined(__x86_64__)
	__asm__("addq %%gs:0, %0\n" : "=r" (__result) : "0" (__ptr));
#else /* __x86_64__ */
	__asm__("addl %%fs:0, %0\n" : "=r" (__result) : "0" (__ptr));
#endif /* !__x86_64__ */
	return __result;
}

extern ATTR_ERROR("Invalid per-task object size") void __invalid_pertask_object_size(void);
#ifdef __X86_SEG_TASK
#define PERTASK_GET(x)    (*((__X86_SEG_TASK __typeof__(x) const *)(__UINTPTR_TYPE__)&(x)))
#define PERTASK_SET(x, v) (*((__X86_SEG_TASK __typeof__(x) *)(__UINTPTR_TYPE__)&(x)) = (v))
#elif defined(__x86_64__)
#define PERTASK_GET(x)                                                  \
	XBLOCK({                                                            \
		__typeof__(x) __pt_res;                                         \
		if __untraced(sizeof(__pt_res) == 1) {                          \
			__asm__("movb %%gs:%p1, %b0" : "=q" (__pt_res) : "mi" (x)); \
		} else if __untraced(sizeof(__pt_res) == 2) {                   \
			__asm__("movw %%gs:%p1, %w0" : "=r" (__pt_res) : "mi" (x)); \
		} else if __untraced(sizeof(__pt_res) == 4) {                   \
			__asm__("movl %%gs:%p1, %k0" : "=r" (__pt_res) : "mi" (x)); \
		} else if __untraced(sizeof(__pt_res) == 8) {                   \
			__asm__("movq %%gs:%p1, %q0" : "=r" (__pt_res) : "mi" (x)); \
		} else {                                                        \
			__invalid_pertask_object_size();                            \
		}                                                               \
		XRETURN __pt_res;                                               \
	})
#define PERTASK_SET(x, v)                                        \
	XBLOCK({                                                     \
		if __untraced(sizeof(x) == 1) {                          \
			__asm__("movb %b0, %%gs:%p1" : : "q" (v), "mi" (x)); \
		} else if __untraced(sizeof(x) == 2) {                   \
			__asm__("movw %w0, %%gs:%p1" : : "r" (v), "mi" (x)); \
		} else if __untraced(sizeof(x) == 4) {                   \
			__asm__("movl %k0, %%gs:%p1" : : "r" (v), "mi" (x)); \
		} else if __untraced(sizeof(x) == 8) {                   \
			__asm__("movq %q0, %%gs:%p1" : : "r" (v), "mi" (x)); \
		} else {                                                 \
			__invalid_pertask_object_size();                     \
		}                                                        \
		(void)0;                                                 \
	})
#else /* __x86_64__ */
#define PERTASK_GET(x)                                                  \
	XBLOCK({                                                            \
		__typeof__(x) __pt_res;                                         \
		if __untraced(sizeof(__pt_res) == 1) {                          \
			__asm__("movb %%fs:%p1, %b0" : "=q" (__pt_res) : "mi" (x)); \
		} else if __untraced(sizeof(__pt_res) == 2) {                   \
			__asm__("movw %%fs:%p1, %w0" : "=r" (__pt_res) : "mi" (x)); \
		} else if __untraced(sizeof(__pt_res) == 4) {                   \
			__asm__("movl %%fs:%p1, %k0" : "=r" (__pt_res) : "mi" (x)); \
		} else {                                                        \
			__invalid_pertask_object_size();                            \
		}                                                               \
		XRETURN __pt_res;                                               \
	})
#define PERTASK_SET(x, v)                                        \
	XBLOCK({                                                     \
		if __untraced(sizeof(x) == 1) {                          \
			__asm__("movb %b0, %%fs:%p1" : : "q" (v), "mi" (x)); \
		} else if __untraced(sizeof(x) == 2) {                   \
			__asm__("movw %w0, %%fs:%p1" : : "r" (v), "mi" (x)); \
		} else if __untraced(sizeof(x) == 4) {                   \
			__asm__("movl %k0, %%fs:%p1" : : "r" (v), "mi" (x)); \
		} else {                                                 \
			__invalid_pertask_object_size();                     \
		}                                                        \
		(void)0;                                                 \
	})
#endif /* !__x86_64__ */
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H */
