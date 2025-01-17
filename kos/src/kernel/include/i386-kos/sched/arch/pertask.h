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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H 1

#include <kernel/compiler.h>

#include <hybrid/host.h>
#include <hybrid/typecore.h>
#include <asm/instr/ttest.h>

DECL_BEGIN

#undef OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE
#if defined(__GNUC__) || 1
#define OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE 1
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



#define THIS_TASK __get_this_task()

FORCELOCAL ATTR_ARTIFICIAL ATTR_CONST WUNUSED
struct task *NOTHROW(__get_this_task)(void) {
	__register struct task *__result;
#ifdef __X86_SEG_TASK
	__result = (struct task *)(*(__X86_SEG_TASK __UINTPTR_TYPE__ const *)0);
#elif defined(__x86_64__)
	__asm__("movq %%gs:0, %0\n" : "=r" (__result));
#else /* __x86_64__ */
	__asm__("movl %%fs:0, %0\n" : "=r" (__result));
#endif /* !__x86_64__ */
	return __result;
}

#define PERTASK(x) (*(__typeof__(&(x)))__get_per_task((void *)&(x)))
FORCELOCAL ATTR_ARTIFICIAL ATTR_CONST ATTR_RETNONNULL WUNUSED
void *NOTHROW(__get_per_task)(void *__ptr) {
	__register void *__result;
#ifdef __X86_SEG_TASK
	__result = (void *)(*(__X86_SEG_TASK __UINTPTR_TYPE__ const *)0 + (__UINTPTR_TYPE__)__ptr);
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
#define __pertask_get8_r(x, result)           __asm__("movb %%gs:%p1, %b0" : "=q" (result) : "mi" (x))
#define __pertask_get16_r(x, result)          __asm__("movw %%gs:%p1, %w0" : "=r" (result) : "mi" (x))
#define __pertask_get32_r(x, result)          __asm__("movl %%gs:%p1, %k0" : "=r" (result) : "mi" (x))
#define __pertask_get64_r(x, result)          __asm__("movq %%gs:%p1, %q0" : "=r" (result) : "mi" (x))
#define __pertask_set8(x, v)                  __asm__("movb %b0, %%gs:%p1" : : "iq" (v), "mi" (x))
#define __pertask_set16(x, v)                 __asm__("movw %w0, %%gs:%p1" : : "ir" (v), "mi" (x))
#define __pertask_set32(x, v)                 __asm__("movl %k0, %%gs:%p1" : : "ir" (v), "mi" (x))
#define __pertask_cmp8_r(x, rhs, cc, result)  __asm__("cmpb %b1, %%gs:%p2" : "=@cc" #cc (result) : "iq" (rhs), "mi" (x))
#define __pertask_cmp16_r(x, rhs, cc, result) __asm__("cmpw %w1, %%gs:%p2" : "=@cc" #cc (result) : "ir" (rhs), "mi" (x))
#define __pertask_cmp32_r(x, rhs, cc, result) __asm__("cmpl %k1, %%gs:%p2" : "=@cc" #cc (result) : "ir" (rhs), "mi" (x))
#define __pertask_test8_r(x, rhs, result)     __asm__("testb %b1, %%gs:%p2" : "=@ccnz" (result) : "iq" (rhs), "mi" (x))
#define __pertask_test16_r(x, rhs, result)    __asm__("testw %w1, %%gs:%p2" : "=@ccnz" (result) : "ir" (rhs), "mi" (x))
#define __pertask_test32_r(x, rhs, result)    __asm__("testl %k1, %%gs:%p2" : "=@ccnz" (result) : "ir" (rhs), "mi" (x))
#define __pertask_ttest_r(x, rhs, result)     __asm__("ttest mask=%p1, loc=%p2, seg=%%gs" : "=@ccnz" (result) : "n" ((__UINT64_TYPE__)(rhs)), "mi" (x))

#define __pertask_set64i(x, v)                 __asm__("movq %q0, %%gs:%p1" : : "ir" (v), "mi" (x))
#define __pertask_cmp64i_r(x, rhs, cc, result) __asm__("cmpq %q1, %%gs:%p2" : "=@cc" #cc (result) : "ir" (rhs), "mi" (x))
#define __pertask_test64i_r(x, rhs, result)    __asm__("testq %q1, %%gs:%p2" : "=@ccnz" (result) : "ir" (rhs), "mi" (x))
#define __pertask_set64r(x, v)                 __asm__("movq %q0, %%gs:%p1" : : "r" (v), "mi" (x))
#define __pertask_cmp64r_r(x, rhs, cc, result) __asm__("cmpq %q1, %%gs:%p2" : "=@cc" #cc (result) : "r" (rhs), "mi" (x))
#define __pertask_test64r_r(x, rhs, result)    __asm__("testq %q1, %%gs:%p2" : "=@ccnz" (result) : "r" (rhs), "mi" (x))
#define __pertask_x64_is32s(v)                 ((__UINT64_TYPE__)(v) == (__UINT64_TYPE__)(__INT64_TYPE__)(__INT32_TYPE__)(__UINT32_TYPE__)(__UINT64_TYPE__)(v))
#define __pertask_set64(x, v)                  if (__builtin_constant_p(v) && __pertask_x64_is32s(v)) __pertask_set64i(x, v); else __pertask_set64r(x, v)
#define __pertask_cmp64_r(x, rhs, cc, result)  if (__builtin_constant_p(rhs) && __pertask_x64_is32s(rhs)) __pertask_cmp64i_r(x, rhs, cc, result); else __pertask_cmp64r_r(x, rhs, cc, result)
#define __pertask_test64_r(x, rhs, result)     if (__builtin_constant_p(rhs) && __pertask_x64_is32s(rhs)) __pertask_test64i_r(x, rhs, result); else __pertask_test64r_r(x, rhs, result)
#else /* __x86_64__ */
#define __pertask_get8_r(x, result)           __asm__("movb %%fs:%p1, %b0" : "=q" (result) : "mi" (x))
#define __pertask_get16_r(x, result)          __asm__("movw %%fs:%p1, %w0" : "=r" (result) : "mi" (x))
#define __pertask_get32_r(x, result)          __asm__("movl %%fs:%p1, %k0" : "=r" (result) : "mi" (x))
#define __pertask_set8(x, v)                  __asm__("movb %b0, %%fs:%p1" : : "iq" (v), "mi" (x))
#define __pertask_set16(x, v)                 __asm__("movw %w0, %%fs:%p1" : : "ir" (v), "mi" (x))
#define __pertask_set32(x, v)                 __asm__("movl %k0, %%fs:%p1" : : "ir" (v), "mi" (x))
#define __pertask_cmp8_r(x, rhs, cc, result)  __asm__("cmpb %b1, %%fs:%p2" : "=@cc" #cc (result) : "iq" (rhs), "mi" (x))
#define __pertask_cmp16_r(x, rhs, cc, result) __asm__("cmpw %w1, %%fs:%p2" : "=@cc" #cc (result) : "ir" (rhs), "mi" (x))
#define __pertask_cmp32_r(x, rhs, cc, result) __asm__("cmpl %k1, %%fs:%p2" : "=@cc" #cc (result) : "ir" (rhs), "mi" (x))
#define __pertask_test8_r(x, rhs, result)     __asm__("testb %b1, %%fs:%p2" : "=@ccnz" (result) : "iq" (rhs), "mi" (x))
#define __pertask_test16_r(x, rhs, result)    __asm__("testw %w1, %%fs:%p2" : "=@ccnz" (result) : "ir" (rhs), "mi" (x))
#define __pertask_test32_r(x, rhs, result)    __asm__("testl %k1, %%fs:%p2" : "=@ccnz" (result) : "ir" (rhs), "mi" (x))
/* NOTE: The mask's cast to `__UINT64_TYPE__' is needed because GCC sucks and outputs the UNSIGNED number
 *       as _SIGNED_ *ugh*. I  even went so far  as to find  the GCC source line  that causes this  mess:
 * /binutils/src/gcc-9.1.0/gcc/config/i386/i386.c:18475:
 * >>if (CONST_INT_P (x))
 * >>    fprintf (file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x));
 *
 * Where  `HOST_WIDE_INT_PRINT_DEC' is `"%" PRId64'.  There aren't any  checks for the signed-ness
 * of the operand, and the value is always output as-is after being converted to a signed integer.
 *
 * This  still happens even though we do  a cast to uint64_t, only that  by doing that we force GCC
 * to do the sign-extension on a 64-bit number, meaning that we'd only run into the problem if  one
 * were to try doing: `PERTASK_TESTMASK(foo, UINT64_C(0x8000000000000000))', which would once again
 * output magically pull this "sign" out of the void and throw it between your legs as you're  just
 * trying to walk along. */
#define __pertask_ttest_r(x, rhs, result)     __asm__("ttest mask=%p1, loc=%p2, seg=%%fs" : "=@ccnz" (result) : "n" ((__UINT64_TYPE__)(rhs)), "mi" (x))
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
template<class __T> WUNUSED __UINT8_TYPE__ (__pertask_get8)(__T const &__x) { __UINT8_TYPE__ __res; __pertask_get8_r(__x, __res); XRETURN __res; }
template<class __T> WUNUSED __UINT16_TYPE__ (__pertask_get16)(__T const &__x) { __UINT16_TYPE__ __res; __pertask_get16_r(__x, __res); XRETURN __res; }
template<class __T> WUNUSED __UINT32_TYPE__ (__pertask_get32)(__T const &__x) { __UINT32_TYPE__ __res; __pertask_get32_r(__x, __res); XRETURN __res; }
#ifdef __pertask_get64_r
#define __pertask_get64 __pertask_get64
template<class __T> WUNUSED __UINT64_TYPE__ (__pertask_get64)(__T const &__x) { __UINT64_TYPE__ __res; __pertask_get64_r(__x, __res); XRETURN __res; }
#endif /* __pertask_get64_r */
}
#else /* __cplusplus */
#define __pertask_get8(x) __pertask_get8(&(x))
#define __pertask_get16(x) __pertask_get16(&(x))
#define __pertask_get32(x) __pertask_get32(&(x))
WUNUSED __UINT8_TYPE__ (__pertask_get8)(void const *__px) { __UINT8_TYPE__ __res; __pertask_get8_r(*(__UINT8_TYPE__ const *), __res); XRETURN __res; }
WUNUSED __UINT16_TYPE__ (__pertask_get16)(void const &__px) { __UINT16_TYPE__ __res; __pertask_get16_r(*(__UINT16_TYPE__ const *)__px, __res); XRETURN __res; }
WUNUSED __UINT32_TYPE__ (__pertask_get32)(void const &__px) { __UINT32_TYPE__ __res; __pertask_get32_r(*(__UINT32_TYPE__ const *)__px, __res); XRETURN __res; }
#ifdef __pertask_get64_r
#define __pertask_get64(x) __pertask_get64(&(x))
WUNUSED __UINT64_TYPE__ (__pertask_get64)(void const &__px) { __UINT64_TYPE__ __res; __pertask_get64_r(*(__UINT64_TYPE__ const *)__px, __res); XRETURN __res; }
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
template<class __T> __UINT8_TYPE__ (__pertask_get8)(__T const &__x) { __UINT8_TYPE__ __res; __pertask_get8_r(__x, __res); return __res; }
template<class __T> __UINT16_TYPE__ (__pertask_get16)(__T const &__x) { __UINT16_TYPE__ __res; __pertask_get16_r(__x, __res); return __res; }
template<class __T> __UINT32_TYPE__ (__pertask_get32)(__T const &__x) { __UINT32_TYPE__ __res; __pertask_get32_r(__x, __res); return __res; }
#ifdef __pertask_get64_r
#define __pertask_get64 __pertask_get64
template<class __T> __UINT64_TYPE__ (__pertask_get64)(__T const &__x) { __UINT64_TYPE__ __res; __pertask_get64_r(__x, __res); return __res; }
#endif /* __pertask_get64_r */
}
#else /* __cplusplus */

#define __pertask_get8(x) __pertask_get8(&(x))
#define __pertask_get16(x) __pertask_get16(&(x))
#define __pertask_get32(x) __pertask_get32(&(x))
__UINT8_TYPE__ (__pertask_get8)(void const *__px) { __UINT8_TYPE__ __res; __pertask_get8_r(*(__UINT8_TYPE__ const *), __res); return __res; }
__UINT16_TYPE__ (__pertask_get16)(void const &__px) { __UINT16_TYPE__ __res; __pertask_get16_r(*(__UINT16_TYPE__ const *)__px, __res); return __res; }
__UINT32_TYPE__ (__pertask_get32)(void const &__px) { __UINT32_TYPE__ __res; __pertask_get32_r(*(__UINT32_TYPE__ const *)__px, __res); return __res; }
#ifdef __pertask_get64_r
#define __pertask_get64(x) __pertask_get64(&(x))
__UINT64_TYPE__ (__pertask_get64)(void const &__px) { __UINT64_TYPE__ __res; __pertask_get64_r(*(__UINT64_TYPE__ const *)__px, __res); return __res; }
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

#ifdef OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE
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
#else /* OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */
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
#endif /* !OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */


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
#elif defined(OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE)
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
#else /* OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */
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
#endif /* !OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */

/************************************************************************/
/* Define __X86_PERTASK_CMP()                                           */
/************************************************************************/
#ifdef __NO_XBLOCK
/* TODO */
#elif defined(OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE)
#ifdef __pertask_cmp64_r
#define __X86_PERTASK_CMP(x, rhs, cc)                            \
	XBLOCK({                                                     \
		__BOOL __xpc_res;                                        \
		switch (sizeof(x)) {                                     \
		case 1: __pertask_cmp8_r(x, rhs, cc, __xpc_res); break;  \
		case 2: __pertask_cmp16_r(x, rhs, cc, __xpc_res); break; \
		case 4: __pertask_cmp32_r(x, rhs, cc, __xpc_res); break; \
		case 8: __pertask_cmp64_r(x, rhs, cc, __xpc_res); break; \
		default: __invalid_pertask_object_size();                \
		}                                                        \
		XRETURN __xpc_res;                                       \
	})
#else /* __pertask_cmp64_r */
#define __X86_PERTASK_CMP(x, rhs, cc)                            \
	XBLOCK({                                                     \
		__BOOL __xpc_res;                                        \
		switch (sizeof(x)) {                                     \
		case 1: __pertask_cmp8_r(x, rhs, cc, __xpc_res); break;  \
		case 2: __pertask_cmp16_r(x, rhs, cc, __xpc_res); break; \
		case 4: __pertask_cmp32_r(x, rhs, cc, __xpc_res); break; \
		default: __invalid_pertask_object_size();                \
		}                                                        \
		XRETURN __xpc_res;                                       \
	})
#endif /* !__pertask_cmp64_r */
#else /* OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */
#ifdef __pertask_cmp64_r
#define __X86_PERTASK_CMP(x, rhs, cc)                 \
	XBLOCK({                                          \
		__BOOL __xpc_res;                             \
		if __untraced(sizeof(x) == 1) {               \
			__pertask_cmp8_r(x, rhs, cc, __xpc_res);  \
		} else if __untraced(sizeof(x) == 2) {        \
			__pertask_cmp16_r(x, rhs, cc, __xpc_res); \
		} else if __untraced(sizeof(x) == 4) {        \
			__pertask_cmp32_r(x, rhs, cc, __xpc_res); \
		} else if __untraced(sizeof(x) == 8) {        \
			__pertask_cmp64_r(x, rhs, cc, __xpc_res); \
		} else {                                      \
			__invalid_pertask_object_size();          \
		}                                             \
		XRETURN __xpc_res;                            \
	})
#else /* __pertask_cmp64_r */
#define __X86_PERTASK_CMP(x, rhs, cc)                 \
	XBLOCK({                                          \
		__BOOL __xpc_res;                             \
		if __untraced(sizeof(x) == 1) {               \
			__pertask_cmp8_r(x, rhs, cc, __xpc_res);  \
		} else if __untraced(sizeof(x) == 2) {        \
			__pertask_cmp16_r(x, rhs, cc, __xpc_res); \
		} else if __untraced(sizeof(x) == 4) {        \
			__pertask_cmp32_r(x, rhs, cc, __xpc_res); \
		} else {                                      \
			__invalid_pertask_object_size();          \
		}                                             \
		XRETURN __xpc_res;                            \
	})
#endif /* !__pertask_cmp64_r */
#endif /* !OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE */


#ifdef __X86_PERTASK_CMP
#define PERTASK_EQ(x, rhs) __X86_PERTASK_CMP(x, rhs, e)
#define PERTASK_NE(x, rhs) __X86_PERTASK_CMP(x, rhs, ne)
#endif /* __X86_PERTASK_CMP */



/************************************************************************/
/* Define __X86_PERTASK_TEST()                                           */
/************************************************************************/
#ifdef __NO_XBLOCK
/* TODO */
#elif defined(OPT_PERTASK_USE_SWITCH_SIZEOF_VARIABLE)
#ifdef __pertask_test64_r
#define __X86_PERTASK_TEST(x, rhs)                            \
	XBLOCK({                                                  \
		__BOOL __xpc_res;                                     \
		switch (sizeof(x)) {                                  \
		case 1: __pertask_test8_r(x, rhs, __xpc_res); break;  \
		case 2: __pertask_test16_r(x, rhs, __xpc_res); break; \
		case 4: __pertask_test32_r(x, rhs, __xpc_res); break; \
		case 8: __pertask_test64_r(x, rhs, __xpc_res); break; \
		default: __invalid_pertask_object_size();             \
		}                                                     \
		XRETURN __xpc_res;                                    \
	})
#else /* __pertask_test64_r */
#define __X86_PERTASK_TEST(x, rhs)                            \
	XBLOCK({                                                  \
		__BOOL __xpc_res;                                     \
		switch (sizeof(x)) {                                  \
		case 1: __pertask_test8_r(x, rhs, __xpc_res); break;  \
		case 2: __pertask_test16_r(x, rhs, __xpc_res); break; \
		case 4: __pertask_test32_r(x, rhs, __xpc_res); break; \
		default: __invalid_pertask_object_size();             \
		}                                                     \
		XRETURN __xpc_res;                                    \
	})
#endif /* !__pertask_test64_r */
#else /* ... */
#ifdef __pertask_test64_r
#define __X86_PERTASK_TEST(x, rhs)                 \
	XBLOCK({                                       \
		__BOOL __xpc_res;                          \
		if __untraced(sizeof(x) == 1) {            \
			__pertask_test8_r(x, rhs, __xpc_res);  \
		} else if __untraced(sizeof(x) == 2) {     \
			__pertask_test16_r(x, rhs, __xpc_res); \
		} else if __untraced(sizeof(x) == 4) {     \
			__pertask_test32_r(x, rhs, __xpc_res); \
		} else if __untraced(sizeof(x) == 8) {     \
			__pertask_test64_r(x, rhs, __xpc_res); \
		} else {                                   \
			__invalid_pertask_object_size();       \
		}                                          \
		XRETURN __xpc_res;                         \
	})
#else /* __pertask_test64_r */
#define __X86_PERTASK_TEST(x, rhs)                 \
	XBLOCK({                                       \
		__BOOL __xpc_res;                          \
		if __untraced(sizeof(x) == 1) {            \
			__pertask_test8_r(x, rhs, __xpc_res);  \
		} else if __untraced(sizeof(x) == 2) {     \
			__pertask_test16_r(x, rhs, __xpc_res); \
		} else if __untraced(sizeof(x) == 4) {     \
			__pertask_test32_r(x, rhs, __xpc_res); \
		} else {                                   \
			__invalid_pertask_object_size();       \
		}                                          \
		XRETURN __xpc_res;                         \
	})
#endif /* !__pertask_test64_r */
#endif /* !... */
#ifdef __NO_XBLOCK
/* TODO */
#else /* __NO_XBLOCK */
#define __X86_PERTASK_TTEST(x, rhs)           \
	XBLOCK({                                  \
		__BOOL __xpc_res;                     \
		__pertask_ttest_r(x, rhs, __xpc_res); \
		XRETURN __xpc_res;                    \
	})
#endif /* !__NO_XBLOCK */

#if defined(__X86_PERTASK_TEST) && defined(__X86_PERTASK_TTEST)
#ifdef __NO_builtin_choose_expr
#define PERTASK_TESTMASK(x, mask) \
	(__builtin_constant_p(mask) ? __X86_PERTASK_TTEST(x, mask) : __X86_PERTASK_TEST(x, mask))
#else /* __NO_builtin_choose_expr */
#define PERTASK_TESTMASK(x, mask)                       \
	__builtin_choose_expr(__builtin_constant_p(mask),   \
	                      __X86_PERTASK_TTEST(x, mask), \
	                      __X86_PERTASK_TEST(x, mask))
#endif /* !__NO_builtin_choose_expr */
#endif /* __X86_PERTASK_TEST && __X86_PERTASK_TTEST */




#endif /* !__X86_SEG_TASK */
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_ARCH_PERTASK_H */
