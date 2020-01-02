/* Copyright (c) 2019-2020 Griefer@Work                                       *
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

#undef CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE
#if defined(__GNUC__) || 1
#define CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE 1
#endif

#ifdef __x86_64__
#define X86_PERTASK_SEGMENT   %gs
#define X86_PERTASK_SEGMENT_S "%gs"
#define X86_PERTASK_SEGMENT_F "%%gs"
#else /* __x86_64__ */
#define X86_PERTASK_SEGMENT   %fs
#define X86_PERTASK_SEGMENT_S "%fs"
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

#ifdef __X86_SEG_TASK
#define PERTASK_GET(x)    (*((__X86_SEG_TASK __typeof__(x) const *)(__UINTPTR_TYPE__)&(x)))
#define PERTASK_SET(x, v) (void)(*((__X86_SEG_TASK __typeof__(x) *)(__UINTPTR_TYPE__)&(x)) = (v))
#else /* __X86_SEG_TASK */
extern ATTR_ERROR("Invalid per-task object size") void __invalid_pertask_object_size(void);

#ifdef __x86_64__
#define __pertask_get8_r(x, result)  __asm__("movb %%gs:%p1, %b0" : "=q" (result) : "mi" (x))
#define __pertask_get16_r(x, result) __asm__("movw %%gs:%p1, %w0" : "=r" (result) : "mi" (x))
#define __pertask_get32_r(x, result) __asm__("movl %%gs:%p1, %k0" : "=r" (result) : "mi" (x))
#define __pertask_get64_r(x, result) __asm__("movq %%gs:%p1, %q0" : "=r" (result) : "mi" (x))
#define __pertask_set8(x, v)         __asm__("movb %b0, %%gs:%p1" : : "q" (v), "mi" (x))
#define __pertask_set16(x, v)        __asm__("movw %w0, %%gs:%p1" : : "r" (v), "mi" (x))
#define __pertask_set32(x, v)        __asm__("movl %k0, %%gs:%p1" : : "r" (v), "mi" (x))
#define __pertask_set64(x, v)        __asm__("movq %q0, %%gs:%p1" : : "r" (v), "mi" (x))
#else /* __x86_64__ */
#define __pertask_get8_r(x, result)  __asm__("movb %%fs:%p1, %b0" : "=q" (result) : "mi" (x))
#define __pertask_get16_r(x, result) __asm__("movw %%fs:%p1, %w0" : "=r" (result) : "mi" (x))
#define __pertask_get32_r(x, result) __asm__("movl %%fs:%p1, %k0" : "=r" (result) : "mi" (x))
#define __pertask_set8(x, v)         __asm__("movb %b0, %%fs:%p1" : : "q" (v), "mi" (x))
#define __pertask_set16(x, v)        __asm__("movw %w0, %%fs:%p1" : : "r" (v), "mi" (x))
#define __pertask_set32(x, v)        __asm__("movl %k0, %%fs:%p1" : : "r" (v), "mi" (x))
#endif /* !__x86_64__ */

/************************************************************************/
/* Define PERTASK_GET()                                                 */
/************************************************************************/
#ifdef __NO_XBLOCK

/* Without XBLOCK support */
#ifdef __cplusplus
extern "C++" {
#define __pertask_get8 __pertask_get8
#define __pertask_get16 __pertask_get16
#define __pertask_get32 __pertask_get32
template<class __T> __UINT8_TYPE__ (__pertask_get8)(__T const &__x) { __UINT8_TYPE__ __res; __pertask_get8_r(__x, __res); XRETURN __res; }
template<class __T> __UINT16_TYPE__ (__pertask_get16)(__T const &__x) { __UINT16_TYPE__ __res; __pertask_get16_r(__x, __res); XRETURN __res; }
template<class __T> __UINT32_TYPE__ (__pertask_get32)(__T const &__x) { __UINT32_TYPE__ __res; __pertask_get32_r(__x, __res); XRETURN __res; }
#ifdef __pertask_get64_r
#define __pertask_get64 __pertask_get64
template<class __T> __UINT64_TYPE__ (__pertask_get64)(__T const &__x) { __UINT64_TYPE__ __res; __pertask_get64_r(__x, __res); XRETURN __res; }
#endif /* __pertask_get64_r */
}
#else /* __cplusplus */
#define __pertask_get8(x) __pertask_get8(&(x))
#define __pertask_get16(x) __pertask_get16(&(x))
#define __pertask_get32(x) __pertask_get32(&(x))
__UINT8_TYPE__ (__pertask_get8)(void const *__px) { __UINT8_TYPE__ __res; __pertask_get8_r(*(__UINT8_TYPE__ const *), __res); XRETURN __res; }
__UINT16_TYPE__ (__pertask_get16)(void const &__px) { __UINT16_TYPE__ __res; __pertask_get16_r(*(__UINT16_TYPE__ const *)__px, __res); XRETURN __res; }
__UINT32_TYPE__ (__pertask_get32)(void const &__px) { __UINT32_TYPE__ __res; __pertask_get32_r(*(__UINT32_TYPE__ const *)__px, __res); XRETURN __res; }
#ifdef __pertask_get64_r
#define __pertask_get64(x) __pertask_get64(&(x))
__UINT64_TYPE__ (__pertask_get64)(void const &__px) { __UINT64_TYPE__ __res; __pertask_get64_r(*(__UINT64_TYPE__ const *)__px, __res); XRETURN __res; }
#endif /* __pertask_get64_r */
#endif /* !__cplusplus */

#ifdef __pertask_get64
#define PERTASK_GET(x)                                                        \
	((__typeof__(x))__builtin_choose_expr(sizeof(x) == 1, __pertask_get8(x),  \
	                __builtin_choose_expr(sizeof(x) == 2, __pertask_get16(x), \
	                __builtin_choose_expr(sizeof(x) == 4, __pertask_get32(x), \
	                __builtin_choose_expr(sizeof(x) == 8, __pertask_get64(x), \
	                (__invalid_pertask_object_size(), 0))))))
#else /* __pertask_get64_r */
#define PERTASK_GET(x)                                                        \
	((__typeof__(x))__builtin_choose_expr(sizeof(x) == 1, __pertask_get8(x),  \
	                __builtin_choose_expr(sizeof(x) == 2, __pertask_get16(x), \
	                __builtin_choose_expr(sizeof(x) == 4, __pertask_get32(x), \
	                (__invalid_pertask_object_size(), 0)))))
#endif /* !__pertask_get64_r */

#elif !defined(__NO_builtin_choose_expr)
#ifdef __NO_XBLOCK
/* Without XBLOCK support */
#ifdef __cplusplus
extern "C++" {
#define __pertask_get8 __pertask_get8
#define __pertask_get16 __pertask_get16
#define __pertask_get32 __pertask_get32
template<class __T> __UINT8_TYPE__ (__pertask_get8)(__T const &__x) { __UINT8_TYPE__ __res; __pertask_get8_r(__x, __res); XRETURN __res; }
template<class __T> __UINT16_TYPE__ (__pertask_get16)(__T const &__x) { __UINT16_TYPE__ __res; __pertask_get16_r(__x, __res); XRETURN __res; }
template<class __T> __UINT32_TYPE__ (__pertask_get32)(__T const &__x) { __UINT32_TYPE__ __res; __pertask_get32_r(__x, __res); XRETURN __res; }
#ifdef __pertask_get64_r
#define __pertask_get64 __pertask_get64
template<class __T> __UINT64_TYPE__ (__pertask_get64)(__T const &__x) { __UINT64_TYPE__ __res; __pertask_get64_r(__x, __res); XRETURN __res; }
#endif /* __pertask_get64_r */
}
#else /* __cplusplus */

#define __pertask_get8(x) __pertask_get8(&(x))
#define __pertask_get16(x) __pertask_get16(&(x))
#define __pertask_get32(x) __pertask_get32(&(x))
__UINT8_TYPE__ (__pertask_get8)(void const *__px) { __UINT8_TYPE__ __res; __pertask_get8_r(*(__UINT8_TYPE__ const *), __res); XRETURN __res; }
__UINT16_TYPE__ (__pertask_get16)(void const &__px) { __UINT16_TYPE__ __res; __pertask_get16_r(*(__UINT16_TYPE__ const *)__px, __res); XRETURN __res; }
__UINT32_TYPE__ (__pertask_get32)(void const &__px) { __UINT32_TYPE__ __res; __pertask_get32_r(*(__UINT32_TYPE__ const *)__px, __res); XRETURN __res; }
#ifdef __pertask_get64_r
#define __pertask_get64(x) __pertask_get64(&(x))
__UINT64_TYPE__ (__pertask_get64)(void const &__px) { __UINT64_TYPE__ __res; __pertask_get64_r(*(__UINT64_TYPE__ const *)__px, __res); XRETURN __res; }
#endif /* __pertask_get64_r */
#endif /* !__cplusplus */
#else /* __NO_XBLOCK */
/* With XBLOCK support */
#define __pertask_get8(x)  XBLOCK({ __UINT8_TYPE__ __pt_res; __pertask_get8_r(x, __pt_res); XRETURN __pt_res; })
#define __pertask_get16(x) XBLOCK({ __UINT16_TYPE__ __pt_res; __pertask_get16_r(x, __pt_res); XRETURN __pt_res; })
#define __pertask_get32(x) XBLOCK({ __UINT32_TYPE__ __pt_res; __pertask_get32_r(x, __pt_res); XRETURN __pt_res; })
#ifdef __pertask_get64_r
#define __pertask_get64(x) XBLOCK({ __UINT64_TYPE__ __pt_res; __pertask_get64_r(x, __pt_res); XRETURN __pt_res; })
#endif /* __pertask_get64_r */
#endif /* !__NO_XBLOCK */
#ifdef __pertask_get64
#define PERTASK_GET(x)                                                        \
	((__typeof__(x))__builtin_choose_expr(sizeof(x) == 1, __pertask_get8(x),  \
	                __builtin_choose_expr(sizeof(x) == 2, __pertask_get16(x), \
	                __builtin_choose_expr(sizeof(x) == 4, __pertask_get32(x), \
	                __builtin_choose_expr(sizeof(x) == 8, __pertask_get64(x), \
	                (__invalid_pertask_object_size(), 0))))))
#else /* __pertask_get64_r */
#define PERTASK_GET(x)                                                        \
	((__typeof__(x))__builtin_choose_expr(sizeof(x) == 1, __pertask_get8(x),  \
	                __builtin_choose_expr(sizeof(x) == 2, __pertask_get16(x), \
	                __builtin_choose_expr(sizeof(x) == 4, __pertask_get32(x), \
	                (__invalid_pertask_object_size(), 0)))))
#endif /* !__pertask_get64_r */
#elif defined(__cplusplus) && !defined(__NO_XBLOCK)

extern "C++" {
__NAMESPACE_INT_BEGIN
template<class __T> struct __pt_remove_cv { typedef __T __type; };
template<class __T> struct __pt_remove_cv<__T const> { typedef __T __type; };
template<class __T> struct __pt_remove_cv<__T volatile> { typedef __T __type; };
template<class __T> struct __pt_remove_cv<__T const volatile> { typedef __T __type; };
template<class __T> using __pt_remove_cv_t = typename __pt_remove_cv<__T>::__type;
__NAMESPACE_INT_END
}

#ifdef CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE
#ifdef __pertask_get64_r
#define PERTASK_GET(x)                                                \
	XBLOCK({                                                          \
		__NAMESPACE_INT_SYM __pt_remove_cv_t<__typeof__(x)> __pt_res; \
		switch (sizeof(x)) {                                          \
		case 1: __pertask_get8_r(x, __pt_res); break;                 \
		case 2: __pertask_get16_r(x, __pt_res); break;                \
		case 4: __pertask_get32_r(x, __pt_res); break;                \
		case 8: __pertask_get64_r(x, __pt_res); break;                \
		default: __invalid_pertask_object_size();                     \
		}                                                             \
		XRETURN __pt_res;                                             \
	})
#else /* __pertask_get64_r */
#define PERTASK_GET(x)                                                \
	XBLOCK({                                                          \
		__NAMESPACE_INT_SYM __pt_remove_cv_t<__typeof__(x)> __pt_res; \
		switch (sizeof(x)) {                                          \
		case 1: __pertask_get8_r(x, __pt_res); break;                 \
		case 2: __pertask_get16_r(x, __pt_res); break;                \
		case 4: __pertask_get32_r(x, __pt_res); break;                \
		default: __invalid_pertask_object_size();                     \
		}                                                             \
		XRETURN __pt_res;                                             \
	})
#endif /* !__pertask_get64_r */
#else /* CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */
#ifdef __pertask_get64_r
#define PERTASK_GET(x)                                                \
	XBLOCK({                                                          \
		__NAMESPACE_INT_SYM __pt_remove_cv_t<__typeof__(x)> __pt_res; \
		if __untraced(sizeof(x) == 1) {                               \
			__pertask_get8_r(x, __pt_res);                            \
		} else if __untraced(sizeof(x) == 2) {                        \
			__pertask_get16_r(x, __pt_res);                           \
		} else if __untraced(sizeof(x) == 4) {                        \
			__pertask_get32_r(x, __pt_res);                           \
		} else if __untraced(sizeof(x) == 8) {                        \
			__pertask_get64_r(x, __pt_res);                           \
		} else {                                                      \
			__invalid_pertask_object_size();                          \
		}                                                             \
		XRETURN __pt_res;                                             \
	})
#else /* __pertask_get64_r */
#define PERTASK_GET(x)                                                \
	XBLOCK({                                                          \
		__NAMESPACE_INT_SYM __pt_remove_cv_t<__typeof__(x)> __pt_res; \
		if __untraced(sizeof(x) == 1) {                               \
			__pertask_get8_r(x, __pt_res);                            \
		} else if __untraced(sizeof(x) == 2) {                        \
			__pertask_get16_r(x, __pt_res);                           \
		} else if __untraced(sizeof(x) == 4) {                        \
			__pertask_get32_r(x, __pt_res);                           \
		} else {                                                      \
			__invalid_pertask_object_size();                          \
		}                                                             \
		XRETURN __pt_res;                                             \
	})
#endif /* !__pertask_get64_r */
#endif /* !CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */


#else /* __cplusplus */

#define __pertask_get8(x)  XBLOCK({ __UINT8_TYPE__ __pt_res; __pertask_get8_r(x, __pt_res); XRETURN __pt_res; })
#define __pertask_get16(x) XBLOCK({ __UINT16_TYPE__ __pt_res; __pertask_get16_r(x, __pt_res); XRETURN __pt_res; })
#define __pertask_get32(x) XBLOCK({ __UINT32_TYPE__ __pt_res; __pertask_get32_r(x, __pt_res); XRETURN __pt_res; })
#ifdef __pertask_get64_r
#define __pertask_get64(x) XBLOCK({ __UINT64_TYPE__ __pt_res; __pertask_get64_r(x, __pt_res); XRETURN __pt_res; })
#define PERTASK_GET(x)                                     \
	((__typeof__(x))(sizeof(x) == 1 ? __pertask_get8(x) :  \
	                 sizeof(x) == 2 ? __pertask_get16(x) : \
	                 sizeof(x) == 4 ? __pertask_get32(x) : \
	                 sizeof(x) == 8 ? __pertask_get64(x) : \
	                 (__invalid_pertask_object_size(), 0)))
#else /* __pertask_get64_r */
#define PERTASK_GET(x)                                     \
	((__typeof__(x))(sizeof(x) == 1 ? __pertask_get8(x) :  \
	                 sizeof(x) == 2 ? __pertask_get16(x) : \
	                 sizeof(x) == 4 ? __pertask_get32(x) : \
	                 (__invalid_pertask_object_size(), 0)))
#endif /* !__pertask_get64_r */
#endif /* !__cplusplus */

/************************************************************************/
/* Define PERTASK_SET()                                                 */
/************************************************************************/
#ifdef __NO_XBLOCK
#ifdef __pertask_get64
#define PERTASK_SET(x, v)                                                           \
	__builtin_choose_expr(sizeof(x) == 1, __pertask_set8(x, (__UINT8_TYPE__)(v)),   \
	__builtin_choose_expr(sizeof(x) == 2, __pertask_set16(x, (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(x) == 4, __pertask_set32(x, (__UINT32_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(x) == 8, __pertask_set64(x, (__UINT64_TYPE__)(v)), \
	                     (__invalid_pertask_object_size(), 0)))))
#else /* __pertask_get64_r */
#define PERTASK_SET(x, v)                                                           \
	__builtin_choose_expr(sizeof(x) == 1, __pertask_set8(x, (__UINT8_TYPE__)(v)),   \
	__builtin_choose_expr(sizeof(x) == 2, __pertask_set16(x, (__UINT16_TYPE__)(v)), \
	__builtin_choose_expr(sizeof(x) == 4, __pertask_set32(x, (__UINT32_TYPE__)(v)), \
	                     (__invalid_pertask_object_size(), 0))))
#endif /* !__pertask_get64_r */
#elif defined(CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE)
#ifdef __pertask_set64
#define PERTASK_SET(x, v)                         \
	XBLOCK({                                      \
		switch (sizeof(x)) {                      \
		case 1: __pertask_set8(x, v); break;      \
		case 2: __pertask_set16(x, v); break;     \
		case 4: __pertask_set32(x, v); break;     \
		case 8: __pertask_set64(x, v); break;     \
		default: __invalid_pertask_object_size(); \
		}                                         \
		(void)0;                                  \
	})
#else /* __pertask_set64 */
#define PERTASK_SET(x, v)                         \
	XBLOCK({                                      \
		switch (sizeof(x)) {                      \
		case 1: __pertask_set8(x, v); break;      \
		case 2: __pertask_set16(x, v); break;     \
		case 4: __pertask_set32(x, v); break;     \
		default: __invalid_pertask_object_size(); \
		}                                         \
		(void)0;                                  \
	})
#endif /* !__pertask_set64 */
#else /* CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */
#ifdef __pertask_set64
#define PERTASK_SET(x, v)                      \
	XBLOCK({                                   \
		if __untraced(sizeof(x) == 1) {        \
			__pertask_set8(x, v);              \
		} else if __untraced(sizeof(x) == 2) { \
			__pertask_set16(x, v);             \
		} else if __untraced(sizeof(x) == 4) { \
			__pertask_set32(x, v);             \
		} else if __untraced(sizeof(x) == 8) { \
			__pertask_set64(x, v);             \
		} else {                               \
			__invalid_pertask_object_size();   \
		}                                      \
		(void)0;                               \
	})
#else /* __pertask_set64 */
#define PERTASK_SET(x, v)                      \
	XBLOCK({                                   \
		if __untraced(sizeof(x) == 1) {        \
			__pertask_set8(x, v);              \
		} else if __untraced(sizeof(x) == 2) { \
			__pertask_set16(x, v);             \
		} else if __untraced(sizeof(x) == 4) { \
			__pertask_set32(x, v);             \
		} else {                               \
			__invalid_pertask_object_size();   \
		}                                      \
		(void)0;                               \
	})
#endif /* !__pertask_set64 */
#endif /* !CONFIG_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */


#endif /* !__X86_SEG_TASK */
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H */
