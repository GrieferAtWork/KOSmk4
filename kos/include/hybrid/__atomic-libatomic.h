/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID___ATOMIC_LIBATOMIC_H
#define __GUARD_HYBRID___ATOMIC_LIBATOMIC_H 1

#include "../__stdinc.h"
#include "typecore.h"

#ifndef __GUARD_HYBRID___ATOMIC_H
#error "Never include this file directly. - Always include `<hybrid/__atomic.h>' instead"
#endif /* !__GUARD_HYBRID___ATOMIC_H */

__DECL_BEGIN

__NAMESPACE_INT_BEGIN

#ifdef __NO_ASMNAME
#define __HYBRID_DEFINE_LIBATOMIC_FUNCTIONS(T, n)                                    \
	extern T (__atomic_load_##n)(T *__mptr, int __order);                            \
	extern void (__atomic_store_##n)(T *__mptr, T __val, int __order);               \
	extern T (__atomic_exchange_##n)(T *__mptr, T __val, int __order);               \
	extern __BOOL (__atomic_compare_exchange_##n)(T *__mptr, T *__expected,          \
	                                            T __newval, int __succ, int __fail); \
	/*extern __BOOL (__atomic_test_and_set_##n)(T *__mptr, int __order);*/           \
	extern T (__atomic_fetch_add_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_fetch_sub_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_fetch_and_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_fetch_xor_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_fetch_or_##n)(T *__mptr, T, int __order);                     \
	extern T (__atomic_fetch_nand_##n)(T *__mptr, T, int __order);                   \
	extern T (__atomic_add_fetch_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_sub_fetch_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_and_fetch_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_xor_fetch_##n)(T *__mptr, T, int __order);                    \
	extern T (__atomic_or_fetch_##n)(T *__mptr, T, int __order);                     \
	extern T (__atomic_nand_fetch_##n)(T *__mptr, T, int __order);
#else /* __NO_ASMNAME */
#define __HYBRID_DEFINE_LIBATOMIC_FUNCTIONS(T, n)                                                                                 \
	extern T (__hybrid_atomic_load_##n)(T *__mptr, int __order) __COMPILER_ASMNAME("__atomic_load_" #n);                          \
	extern void (__hybrid_atomic_store_##n)(T *__mptr, T __val, int __order) __COMPILER_ASMNAME("__atomic_store_" #n);            \
	extern T (__hybrid_atomic_exchange_##n)(T *__mptr, T __val, int __order) __COMPILER_ASMNAME("__atomic_exchange_" #n);         \
	extern __BOOL (__hybrid_atomic_compare_exchange_##n)(T *__mptr, T *__expected,                                                \
	                                                     T __newval, int __succ, int __fail)                                      \
			__COMPILER_ASMNAME("__atomic_compare_exchange_" #n);                                                                  \
	/*extern __BOOL (__hybrid_atomic_test_and_set_##n)(T *__mptr, int __order) __COMPILER_ASMNAME("__atomic_test_and_set_" #n);*/ \
	extern T (__hybrid_atomic_fetch_add_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_fetch_add_" #n);             \
	extern T (__hybrid_atomic_fetch_sub_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_fetch_sub_" #n);             \
	extern T (__hybrid_atomic_fetch_and_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_fetch_and_" #n);             \
	extern T (__hybrid_atomic_fetch_xor_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_fetch_xor_" #n);             \
	extern T (__hybrid_atomic_fetch_or_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_fetch_or_" #n);               \
	extern T (__hybrid_atomic_fetch_nand_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_fetch_nand_" #n);           \
	extern T (__hybrid_atomic_add_fetch_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_add_fetch_" #n);             \
	extern T (__hybrid_atomic_sub_fetch_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_sub_fetch_" #n);             \
	extern T (__hybrid_atomic_and_fetch_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_and_fetch_" #n);             \
	extern T (__hybrid_atomic_xor_fetch_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_xor_fetch_" #n);             \
	extern T (__hybrid_atomic_or_fetch_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_or_fetch_" #n);               \
	extern T (__hybrid_atomic_nand_fetch_##n)(T *__mptr, T, int __order) __COMPILER_ASMNAME("__atomic_nand_fetch_" #n);
#endif /* !__NO_ASMNAME */
__HYBRID_DEFINE_LIBATOMIC_FUNCTIONS(__UINT8_TYPE__, 1)
__HYBRID_DEFINE_LIBATOMIC_FUNCTIONS(__UINT16_TYPE__, 2)
__HYBRID_DEFINE_LIBATOMIC_FUNCTIONS(__UINT32_TYPE__, 4)
#ifdef __UINT64_TYPE__
__HYBRID_DEFINE_LIBATOMIC_FUNCTIONS(__UINT64_TYPE__, 8)
#ifdef __UINT128_TYPE__
__HYBRID_DEFINE_LIBATOMIC_FUNCTIONS(__UINT128_TYPE__, 16)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#undef __HYBRID_DEFINE_LIBATOMIC_FUNCTIONS

#ifdef __NO_ASMNAME
#define __hybrid_atomic_load_1              __atomic_load_1
#define __hybrid_atomic_store_1             __atomic_store_1
#define __hybrid_atomic_exchange_1          __atomic_exchange_1
#define __hybrid_atomic_compare_exchange_1  __atomic_compare_exchange_1
#define __hybrid_atomic_test_and_set_1      __atomic_test_and_set_1
#define __hybrid_atomic_fetch_add_1         __atomic_fetch_add_1
#define __hybrid_atomic_fetch_sub_1         __atomic_fetch_sub_1
#define __hybrid_atomic_fetch_and_1         __atomic_fetch_and_1
#define __hybrid_atomic_fetch_xor_1         __atomic_fetch_xor_1
#define __hybrid_atomic_fetch_or_1          __atomic_fetch_or_1
#define __hybrid_atomic_fetch_nand_1        __atomic_fetch_nand_1
#define __hybrid_atomic_add_fetch_1         __atomic_add_fetch_1
#define __hybrid_atomic_sub_fetch_1         __atomic_sub_fetch_1
#define __hybrid_atomic_and_fetch_1         __atomic_and_fetch_1
#define __hybrid_atomic_xor_fetch_1         __atomic_xor_fetch_1
#define __hybrid_atomic_or_fetch_1          __atomic_or_fetch_1
#define __hybrid_atomic_nand_fetch_1        __atomic_nand_fetch_1
#define __hybrid_atomic_load_2              __atomic_load_2
#define __hybrid_atomic_store_2             __atomic_store_2
#define __hybrid_atomic_exchange_2          __atomic_exchange_2
#define __hybrid_atomic_compare_exchange_2  __atomic_compare_exchange_2
#define __hybrid_atomic_test_and_set_2      __atomic_test_and_set_2
#define __hybrid_atomic_fetch_add_2         __atomic_fetch_add_2
#define __hybrid_atomic_fetch_sub_2         __atomic_fetch_sub_2
#define __hybrid_atomic_fetch_and_2         __atomic_fetch_and_2
#define __hybrid_atomic_fetch_xor_2         __atomic_fetch_xor_2
#define __hybrid_atomic_fetch_or_2          __atomic_fetch_or_2
#define __hybrid_atomic_fetch_nand_2        __atomic_fetch_nand_2
#define __hybrid_atomic_add_fetch_2         __atomic_add_fetch_2
#define __hybrid_atomic_sub_fetch_2         __atomic_sub_fetch_2
#define __hybrid_atomic_and_fetch_2         __atomic_and_fetch_2
#define __hybrid_atomic_xor_fetch_2         __atomic_xor_fetch_2
#define __hybrid_atomic_or_fetch_2          __atomic_or_fetch_2
#define __hybrid_atomic_nand_fetch_2        __atomic_nand_fetch_2
#define __hybrid_atomic_load_4              __atomic_load_4
#define __hybrid_atomic_store_4             __atomic_store_4
#define __hybrid_atomic_exchange_4          __atomic_exchange_4
#define __hybrid_atomic_compare_exchange_4  __atomic_compare_exchange_4
#define __hybrid_atomic_test_and_set_4      __atomic_test_and_set_4
#define __hybrid_atomic_fetch_add_4         __atomic_fetch_add_4
#define __hybrid_atomic_fetch_sub_4         __atomic_fetch_sub_4
#define __hybrid_atomic_fetch_and_4         __atomic_fetch_and_4
#define __hybrid_atomic_fetch_xor_4         __atomic_fetch_xor_4
#define __hybrid_atomic_fetch_or_4          __atomic_fetch_or_4
#define __hybrid_atomic_fetch_nand_4        __atomic_fetch_nand_4
#define __hybrid_atomic_add_fetch_4         __atomic_add_fetch_4
#define __hybrid_atomic_sub_fetch_4         __atomic_sub_fetch_4
#define __hybrid_atomic_and_fetch_4         __atomic_and_fetch_4
#define __hybrid_atomic_xor_fetch_4         __atomic_xor_fetch_4
#define __hybrid_atomic_or_fetch_4          __atomic_or_fetch_4
#define __hybrid_atomic_nand_fetch_4        __atomic_nand_fetch_4
#ifdef __UINT64_TYPE__
#define __hybrid_atomic_load_8              __atomic_load_8
#define __hybrid_atomic_store_8             __atomic_store_8
#define __hybrid_atomic_exchange_8          __atomic_exchange_8
#define __hybrid_atomic_compare_exchange_8  __atomic_compare_exchange_8
#define __hybrid_atomic_test_and_set_8      __atomic_test_and_set_8
#define __hybrid_atomic_fetch_add_8         __atomic_fetch_add_8
#define __hybrid_atomic_fetch_sub_8         __atomic_fetch_sub_8
#define __hybrid_atomic_fetch_and_8         __atomic_fetch_and_8
#define __hybrid_atomic_fetch_xor_8         __atomic_fetch_xor_8
#define __hybrid_atomic_fetch_or_8          __atomic_fetch_or_8
#define __hybrid_atomic_fetch_nand_8        __atomic_fetch_nand_8
#define __hybrid_atomic_add_fetch_8         __atomic_add_fetch_8
#define __hybrid_atomic_sub_fetch_8         __atomic_sub_fetch_8
#define __hybrid_atomic_and_fetch_8         __atomic_and_fetch_8
#define __hybrid_atomic_xor_fetch_8         __atomic_xor_fetch_8
#define __hybrid_atomic_or_fetch_8          __atomic_or_fetch_8
#define __hybrid_atomic_nand_fetch_8        __atomic_nand_fetch_8
#ifdef __UINT128_TYPE__
#define __hybrid_atomic_load_16             __atomic_load_16
#define __hybrid_atomic_store_16            __atomic_store_16
#define __hybrid_atomic_exchange_16         __atomic_exchange_16
#define __hybrid_atomic_compare_exchange_16 __atomic_compare_exchange_16
#define __hybrid_atomic_test_and_set_16     __atomic_test_and_set_16
#define __hybrid_atomic_fetch_add_16        __atomic_fetch_add_16
#define __hybrid_atomic_fetch_sub_16        __atomic_fetch_sub_16
#define __hybrid_atomic_fetch_and_16        __atomic_fetch_and_16
#define __hybrid_atomic_fetch_xor_16        __atomic_fetch_xor_16
#define __hybrid_atomic_fetch_or_16         __atomic_fetch_or_16
#define __hybrid_atomic_fetch_nand_16       __atomic_fetch_nand_16
#define __hybrid_atomic_add_fetch_16        __atomic_add_fetch_16
#define __hybrid_atomic_sub_fetch_16        __atomic_sub_fetch_16
#define __hybrid_atomic_and_fetch_16        __atomic_and_fetch_16
#define __hybrid_atomic_xor_fetch_16        __atomic_xor_fetch_16
#define __hybrid_atomic_or_fetch_16         __atomic_or_fetch_16
#define __hybrid_atomic_nand_fetch_16       __atomic_nand_fetch_16
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#endif /* __NO_ASMNAME */

#ifdef __cplusplus
#ifdef __UINT128_TYPE__
#define __HYBRID_DEFINE_LIBATOMIC_SELECTOR(return_type, name, params, getargs, return_, ...)            \
	return_type(name) params {                                                                          \
		__STATIC_IF(sizeof(__T) == 1) {                                                                 \
			return_((__NAMESPACE_INT_SYM name##_1)getargs(__UINT8_TYPE__, __VA_ARGS__));                \
		}                                                                                               \
		__STATIC_ELSE(sizeof(__T) == 1) {                                                               \
			__STATIC_IF(sizeof(__T) == 2) {                                                             \
				return_((__NAMESPACE_INT_SYM name##_2)getargs(__UINT16_TYPE__, __VA_ARGS__));           \
			}                                                                                           \
			__STATIC_ELSE(sizeof(__T) == 2) {                                                           \
				__STATIC_IF(sizeof(__T) == 4) {                                                         \
					return_((__NAMESPACE_INT_SYM name##_4)getargs(__UINT32_TYPE__, __VA_ARGS__));       \
				}                                                                                       \
				__STATIC_ELSE(sizeof(__T) == 4) {                                                       \
					__STATIC_IF(sizeof(__T) == 8) {                                                     \
						return_((__NAMESPACE_INT_SYM name##_8)getargs(__UINT64_TYPE__, __VA_ARGS__));   \
					}                                                                                   \
					__STATIC_ELSE(sizeof(__T) == 8) {                                                   \
						return_((__NAMESPACE_INT_SYM name##_16)getargs(__UINT128_TYPE__, __VA_ARGS__)); \
					}                                                                                   \
				}                                                                                       \
			}                                                                                           \
		}                                                                                               \
	}
#elif defined(__UINT64_TYPE__)
#define __HYBRID_DEFINE_LIBATOMIC_SELECTOR(return_type, name, params, getargs, return_, ...)      \
	return_type(name) params {                                                                    \
		__STATIC_IF(sizeof(__T) == 1) {                                                           \
			return_((__NAMESPACE_INT_SYM name##_1)getargs(__UINT8_TYPE__, __VA_ARGS__));          \
		}                                                                                         \
		__STATIC_ELSE(sizeof(__T) == 1) {                                                         \
			__STATIC_IF(sizeof(__T) == 2) {                                                       \
				return_((__NAMESPACE_INT_SYM name##_2)getargs(__UINT16_TYPE__, __VA_ARGS__));     \
			}                                                                                     \
			__STATIC_ELSE(sizeof(__T) == 2) {                                                     \
				__STATIC_IF(sizeof(__T) == 4) {                                                   \
					return_((__NAMESPACE_INT_SYM name##_4)getargs(__UINT32_TYPE__, __VA_ARGS__)); \
				}                                                                                 \
				__STATIC_ELSE(sizeof(__T) == 4) {                                                 \
					return_((__NAMESPACE_INT_SYM name##_8)getargs(__UINT64_TYPE__, __VA_ARGS__)); \
				}                                                                                 \
			}                                                                                     \
		}                                                                                         \
	}
#else
#define __HYBRID_DEFINE_LIBATOMIC_SELECTOR(return_type, name, params, getargs, return_, ...)  \
	return_type(name) params {                                                                \
		__STATIC_IF(sizeof(__T) == 1) {                                                       \
			return_((__NAMESPACE_INT_SYM name##_1)getargs(__UINT8_TYPE__, __VA_ARGS__));      \
		}                                                                                     \
		__STATIC_ELSE(sizeof(__T) == 1) {                                                     \
			__STATIC_IF(sizeof(__T) == 2) {                                                   \
				return_((__NAMESPACE_INT_SYM name##_2)getargs(__UINT16_TYPE__, __VA_ARGS__)); \
			}                                                                                 \
			__STATIC_ELSE(sizeof(__T) == 2) {                                                 \
				return_((__NAMESPACE_INT_SYM name##_4)getargs(__UINT32_TYPE__, __VA_ARGS__)); \
			}                                                                                 \
		}                                                                                     \
	}
#endif

#else /* __cplusplus */

#ifdef __NO_builtin_choose_expr
#ifdef __UINT128_TYPE__
#define __HYBRID_CALL_LIBATOMIC_SELECTOR(name, sizeof, getargs, ...)  \
	(sizeof == 1 ? (name##_1) getargs(__UINT8_TYPE__, __VA_ARGS__) :  \
	 sizeof == 2 ? (name##_2) getargs(__UINT16_TYPE__, __VA_ARGS__) : \
	 sizeof == 4 ? (name##_4) getargs(__UINT32_TYPE__, __VA_ARGS__) : \
	 sizeof == 8 ? (name##_8) getargs(__UINT32_TYPE__, __VA_ARGS__) : \
	               (name##_16) getargs(__UINT128_TYPE__, __VA_ARGS__))
#elif defined(__UINT64_TYPE__)
#define __HYBRID_CALL_LIBATOMIC_SELECTOR(name, sizeof, getargs, ...)  \
	(sizeof == 1 ? (name##_1) getargs(__UINT8_TYPE__, __VA_ARGS__) :  \
	 sizeof == 2 ? (name##_2) getargs(__UINT16_TYPE__, __VA_ARGS__) : \
	 sizeof == 4 ? (name##_4) getargs(__UINT32_TYPE__, __VA_ARGS__) : \
	               (name##_8) getargs(__UINT64_TYPE__, __VA_ARGS__))
#else
#define __HYBRID_CALL_LIBATOMIC_SELECTOR(name, sizeof, getargs, ...)  \
	(sizeof == 1 ? (name##_1) getargs(__UINT8_TYPE__, __VA_ARGS__) :  \
	 sizeof == 2 ? (name##_2) getargs(__UINT16_TYPE__, __VA_ARGS__) : \
	               (name##_4) getargs(__UINT32_TYPE__, __VA_ARGS__))
#endif
#else /* __NO_builtin_choose_expr */
#ifdef __UINT128_TYPE__
#define __HYBRID_CALL_LIBATOMIC_SELECTOR(name, sizeof, getargs, ...)                     \
	__builtin_choose_expr(sizeof == 1, (name##_1) getargs(__UINT8_TYPE__, __VA_ARGS__),  \
	__builtin_choose_expr(sizeof == 2, (name##_2) getargs(__UINT16_TYPE__, __VA_ARGS__), \
	__builtin_choose_expr(sizeof == 4, (name##_4) getargs(__UINT32_TYPE__, __VA_ARGS__), \
	__builtin_choose_expr(sizeof == 8, (name##_8) getargs(__UINT32_TYPE__, __VA_ARGS__), \
	                                   (name##_16) getargs(__UINT128_TYPE__, __VA_ARGS__)))))
#elif defined(__UINT64_TYPE__)
#define __HYBRID_CALL_LIBATOMIC_SELECTOR(name, sizeof, getargs, ...)                     \
	__builtin_choose_expr(sizeof == 1, (name##_1) getargs(__UINT8_TYPE__, __VA_ARGS__),  \
	__builtin_choose_expr(sizeof == 2, (name##_2) getargs(__UINT16_TYPE__, __VA_ARGS__), \
	__builtin_choose_expr(sizeof == 4, (name##_4) getargs(__UINT32_TYPE__, __VA_ARGS__), \
	                                   (name##_8) getargs(__UINT64_TYPE__, __VA_ARGS__))))
#else
#define __HYBRID_CALL_LIBATOMIC_SELECTOR(name, sizeof, getargs, ...)                     \
	__builtin_choose_expr(sizeof == 1, (name##_1) getargs(__UINT8_TYPE__, __VA_ARGS__),  \
	__builtin_choose_expr(sizeof == 2, (name##_2) getargs(__UINT16_TYPE__, __VA_ARGS__), \
	                                   (name##_4) getargs(__UINT32_TYPE__, __VA_ARGS__)))
#endif
#endif /* !__NO_builtin_choose_expr */

#endif /* !__cplusplus */

#ifdef __cplusplus

extern "C++" {

template<class __To> struct __hybrid_atomic_castto {
	template<class __T>
	static __ATTR_FORCEINLINE __To (__doit)(__T __v) {
		return (__To)__v;
	}
};
template<class __To> struct __hybrid_atomic_castto<__To *> {
	template<class __T>
	static __ATTR_FORCEINLINE __To *(__doit)(__T __v) {
		return (__To *)(__UINTPTR_TYPE__)__v;
	}
};
template<class __From, class __To> struct __hybrid_atomic_castfrom {
	static __ATTR_FORCEINLINE __To (__doit)(__From __v) {
		return (__To)__v;
	}
};
template<class __From, class __To> struct __hybrid_atomic_castfrom<__From *, __To> {
	static __ATTR_FORCEINLINE __To (__doit)(__From *__v) {
		return (__To)(__UINTPTR_TYPE__)__v;
	}
};

#define __hybrid_atomic_getargs_load(T, x, order) \
	((T *)x, order)
#define __hybrid_atomic_getargs_store(T, x, v, order) \
	((T *)x, __hybrid_atomic_castfrom<__VT, T>::__doit(v), order)
#define __hybrid_atomic_getargs_cmpxch(T, x, poldv, newv, succ, fail) \
	((T *)x, (T *)poldv, __hybrid_atomic_castfrom<__VT, T>::__doit(newv), succ, fail)

template<class __T> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_load,
                                   (__T *__x, int __order),
                                   __hybrid_atomic_getargs_load,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(void, __hybrid_atomic_store,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   , __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_exchange,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1, 2))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__BOOL, __hybrid_atomic_compare_exchange,
                                   (__T *__x, __T *__pov, __VT __nv, int __succ, int __fail),
                                   __hybrid_atomic_getargs_cmpxch,
                                   return, __x, __pov, __nv, __succ, __fail)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_add_fetch,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_sub_fetch,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_and_fetch,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_or_fetch,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_xor_fetch,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_nand_fetch,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_fetch_add,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_fetch_sub,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_fetch_and,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_fetch_or,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_fetch_xor,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)

template<class __T, class __VT> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1))
__HYBRID_DEFINE_LIBATOMIC_SELECTOR(__T, __hybrid_atomic_fetch_nand,
                                   (__T *__x, __VT __v, int __order),
                                   __hybrid_atomic_getargs_store,
                                   return __hybrid_atomic_castto<__T>::__doit,
                                   __x, __v, __order)
#undef __HYBRID_DEFINE_LIBATOMIC_SELECTOR
#undef __hybrid_atomic_getargs_load
#undef __hybrid_atomic_getargs_store
#undef __hybrid_atomic_getargs_cmpxch

#ifdef __NO_XBLOCK
template<class __T, class __TN> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1)) __BOOL
(__hybrid_atomic_cmpxch)(__T *__x, __T __ov, __TN __nv, int __succ, int __fail) {
	return __hybrid_atomic_compare_exchange(__x, &__ov, __nv, __succ, __fail);
}
template<class __T, class __TN> __ATTR_FORCEINLINE __ATTR_LEAF __ATTR_NONNULL((1)) __T
(__hybrid_atomic_cmpxch_val)(__T *__x, __T __ov, __TN __nv, int __succ, int __fail) {
	__hybrid_atomic_compare_exchange(__x, &__ov, __nv, __succ, __fail);
	return __ov;
}
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail) \
	(__NAMESPACE_INT_SYM __hybrid_atomic_cmpxch)(&(x), oldv, newv, succ, fail)
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail) \
	(__NAMESPACE_INT_SYM __hybrid_atomic_cmpxch_val)(&(x), oldv, newv, succ, fail)
#else /* __NO_XBLOCK */
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail)                                                 \
	__XBLOCK({                                                                                            \
		__typeof__(x) __oldv = (oldv);                                                                    \
		__XRETURN(__NAMESPACE_INT_SYM __hybrid_atomic_compare_exchange)(&(x), &__oldv, newv, succ, fail); \
	})
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail)                                    \
	__XBLOCK({                                                                                   \
		__typeof__(x) __oldv = (oldv);                                                           \
		(__NAMESPACE_INT_SYM __hybrid_atomic_compare_exchange)(&(x), &__oldv, newv, succ, fail); \
		__XRETURN __oldv;                                                                        \
	})
#endif /* !__NO_XBLOCK */

} /* extern "C++" */
#define __hybrid_atomic_load(x, order)         (__NAMESPACE_INT_SYM __hybrid_atomic_load)(&(x), order)
#define __hybrid_atomic_store(x, v, order)     (__NAMESPACE_INT_SYM __hybrid_atomic_store)(&(x), v, order)
#define __hybrid_atomic_xch(x, v, order)       (__NAMESPACE_INT_SYM __hybrid_atomic_exchange)(&(x), v, order)
#define __hybrid_atomic_addfetch(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_add_fetch)(&(x), v, order)
#define __hybrid_atomic_subfetch(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_sub_fetch)(&(x), v, order)
#define __hybrid_atomic_andfetch(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_and_fetch)(&(x), v, order)
#define __hybrid_atomic_orfetch(x, v, order)   (__NAMESPACE_INT_SYM __hybrid_atomic_or_fetch)(&(x), v, order)
#define __hybrid_atomic_xorfetch(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_xor_fetch)(&(x), v, order)
#define __hybrid_atomic_nandfetch(x, v, order) (__NAMESPACE_INT_SYM __hybrid_atomic_nand_fetch)(&(x), v, order)
#define __hybrid_atomic_fetchadd(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_fetch_add)(&(x), v, order)
#define __hybrid_atomic_fetchsub(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_fetch_sub)(&(x), v, order)
#define __hybrid_atomic_fetchand(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_fetch_and)(&(x), v, order)
#define __hybrid_atomic_fetchor(x, v, order)   (__NAMESPACE_INT_SYM __hybrid_atomic_fetch_or)(&(x), v, order)
#define __hybrid_atomic_fetchxor(x, v, order)  (__NAMESPACE_INT_SYM __hybrid_atomic_fetch_xor)(&(x), v, order)
#define __hybrid_atomic_fetchnand(x, v, order) (__NAMESPACE_INT_SYM __hybrid_atomic_fetch_nand)(&(x), v, order)

#else /* __cplusplus */

#define __hybrid_atomic_getargs_load(T, x, order)     ((T *)&(x), order)
#define __hybrid_atomic_getargs_store(T, x, v, order) ((T *)&(x), (T)(v), order)

#define __hybrid_atomic_load(x, order) \
	__ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_load, sizeof(x), __hybrid_atomic_getargs_load, x, order))
#define __hybrid_atomic_store(x, v, order) \
	__HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_store, sizeof(x), __hybrid_atomic_getargs_store, x, v, order)
#define __hybrid_atomic_xch(x, v, order) \
	__ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_exchange, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))

#ifdef __NO_XBLOCK
/* Work-around for compilers without expression block support */
#define __HYBRID_DEFINE_ATOMIC_CMPXCH_N(T, n)                                           \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) __BOOL               \
	(__hybrid_atomic_cmpxch_##n)(T * __x, T __ov, T __nv, int __succ, int __fail) {     \
		return __hybrid_atomic_compare_exchange_##n(__x, &__ov, __nv, __succ, __fail);  \
	}                                                                                   \
	__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_LEAF __ATTR_NONNULL((1)) T                    \
	(__hybrid_atomic_cmpxch_val_##n)(T * __x, T __ov, T __nv, int __succ, int __fail) { \
		__hybrid_atomic_compare_exchange_##n(__x, &__ov, __nv, __succ, __fail);         \
		return __ov;                                                                    \
	}
__HYBRID_DEFINE_ATOMIC_CMPXCH_N(__UINT8_TYPE__, 1)
__HYBRID_DEFINE_ATOMIC_CMPXCH_N(__UINT16_TYPE__, 2)
__HYBRID_DEFINE_ATOMIC_CMPXCH_N(__UINT32_TYPE__, 4)
#ifdef __UINT64_TYPE__
__HYBRID_DEFINE_ATOMIC_CMPXCH_N(__UINT64_TYPE__, 8)
#ifdef __UINT128_TYPE__
__HYBRID_DEFINE_ATOMIC_CMPXCH_N(__UINT128_TYPE__, 16)
#endif /* __UINT128_TYPE__ */
#endif /* __UINT64_TYPE__ */
#undef __HYBRID_DEFINE_ATOMIC_CMPXCH_N
#define __hybrid_atomic_getargs_cmpxch(T, x, oldv, newv, succ, fail) \
	((T *)&(x), (T)(oldv), (T)(newv), succ, fail)
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail) \
	__HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_cmpxch, sizeof(x), __hybrid_atomic_getargs_cmpxch, x, oldv, newv, succ, fail)
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail) \
	__ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_cmpxch_val, sizeof(x), __hybrid_atomic_getargs_cmpxch, x, oldv, newv, succ, fail))

#else /* __NO_XBLOCK */

/* Simple case: Implement compare-exchange support using expression blocks */
#define __hybrid_atomic_getargs_cmpxch(T, x, poldv, newv, succ, fail) \
	((T *)&(x), (T *)poldv, (T)(newv), succ, fail)
#define __hybrid_atomic_cmpxch(x, oldv, newv, succ, fail)                                            \
	__XBLOCK({                                                                                       \
		__typeof__(x) __oldv = (oldv);                                                               \
		__XRETURN __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_compare_exchange, sizeof(__oldv), \
		                                           __hybrid_atomic_getargs_cmpxch, x, &__oldv, newv, \
		                                           succ, fail);                                      \
	})
#define __hybrid_atomic_cmpxch_val(x, oldv, newv, succ, fail)                              \
	__XBLOCK({                                                                             \
		__typeof__(x) __oldv = (oldv);                                                     \
		__HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_compare_exchange, sizeof(__oldv), \
		                                 __hybrid_atomic_getargs_cmpxch, x, &__oldv, newv, \
		                                 succ, fail);                                      \
		__XRETURN __oldv;                                                                  \
	})
#endif /* !__NO_XBLOCK */
#define __hybrid_atomic_addfetch(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_add_fetch, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_subfetch(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_sub_fetch, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_andfetch(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_and_fetch, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_orfetch(x, v, order)   __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_or_fetch, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_xorfetch(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_xor_fetch, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_nandfetch(x, v, order) __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_nand_fetch, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_fetchadd(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_fetch_add, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_fetchsub(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_fetch_sub, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_fetchand(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_fetch_and, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_fetchor(x, v, order)   __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_fetch_or, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_fetchxor(x, v, order)  __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_fetch_xor, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#define __hybrid_atomic_fetchnand(x, v, order) __ATOMIC_RECAST(x, __HYBRID_CALL_LIBATOMIC_SELECTOR(__hybrid_atomic_fetch_nand, sizeof(x), __hybrid_atomic_getargs_store, x, v, order))
#endif /* !__cplusplus */
#define __hybrid_atomic_cmpxch_weak(x, oldv, newv, succ, fail) \
	__hybrid_atomic_cmpxch(x, oldv, newv, succ, fail)

__NAMESPACE_INT_END
__DECL_END

#endif /* !__GUARD_HYBRID___ATOMIC_LIBATOMIC_H */
