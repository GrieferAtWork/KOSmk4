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
#ifndef __GUARD_HYBRID_PP___VA_NARGS_H
#define __GUARD_HYBRID_PP___VA_NARGS_H 1

#include "../../__stdinc.h"

#ifdef __PREPROCESSOR_HAVE_VA_ARGS

#ifdef __has_known_extension
#if __has_known_extension("va-nargs-in-macros")
#   if !__has_extension("va-nargs-in-macros")
#      pragma extension("va-nargs-in-macros")
#   endif /* !__has_extension("va-nargs-in-macros") */
#   define __HYBRID_PP_VA_NARGS(...) __VA_NARGS__
#elif __has_known_extension("va-comma-in-macros")
#   if !__has_extension("va-comma-in-macros")
#      pragma extension("va-comma-in-macros")
#   endif /* !__has_extension("va-comma-in-macros") */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(__VA_ARGS__ __VA_COMMA__ 59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#elif __has_known_extension("glue-comma-in-macros")
#   if !__has_extension("glue-comma-in-macros")
#      pragma extension("glue-comma-in-macros")
#   endif /* !__has_extension("glue-comma-in-macros") */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(~,##__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#endif /* ... */
#endif /* __has_known_extension */

#ifndef __HYBRID_PP_VA_NARGS
#if defined(_MSC_VER) || defined(__INTELLISENSE__)
/* MSVC-Specific (Capable of detecting empty __VA_ARGS__ with ~,__VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(...) __VA_ARGS__
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_1(...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(__VA_ARGS__)
#   define __HYBRID_PP_PRIVATE_VA_NARGS_I(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_PRIVATE_VA_NARGS_X(...) (~,__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_1(__HYBRID_PP_PRIVATE_VA_NARGS_I __HYBRID_PP_PRIVATE_VA_NARGS_X(__VA_ARGS__))
#elif __has_extension(tpp_va_comma)
/* TPP-Specific (Capable of detecting empty __VA_ARGS__ with __VA_COMMA__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(__VA_ARGS__ __VA_COMMA__ 59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#elif defined(__GNUC__) || (defined(__TPP_VERSION__) && __TPP_VERSION__ >= 103)
/* GCC-Specific (Capable of detecting empty __VA_ARGS__ with ,##__VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(~,##__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#else /* ... */
/* Check if __VA_OPT__ is supported, and if it is, use it for a standard, 0-arg-capable implementation.
 * Note that we can check for `__VA_OPT__' without having to rely on any feature-test macros, since its
 * behavior is well-defined even on preprocessors that don't support it! */
#define __HYBRID_PP_PRIVATE_TEST_VA_OPT2(a, b, ...) b
#define __HYBRID_PP_PRIVATE_TEST_VA_OPT(...) __HYBRID_PP_PRIVATE_TEST_VA_OPT2(__VA_OPT__(,) 1, 0)
#if __HYBRID_PP_PRIVATE_TEST_VA_OPT(~)
/* STD-Implementation (Capable of detecting empty __VA_ARGS__ with __VA_OPT__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(__VA_ARGS__ __VA_OPT__(,) 59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#else /* __HYBRID_PP_PRIVATE_TEST_VA_OPT(~) */
/* STD-Implementation (Not Capable of detecting empty __VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(...) __VA_ARGS__
#   define __HYBRID_PP_PRIVATE_VA_NARGS2(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_PRIVATE_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS2(__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(__HYBRID_PP_PRIVATE_VA_NARGS(__VA_ARGS__))
#endif /* !__HYBRID_PP_PRIVATE_TEST_VA_OPT(~) */
#undef __HYBRID_PP_PRIVATE_TEST_VA_OPT2
#undef __HYBRID_PP_PRIVATE_TEST_VA_OPT
#endif /* !... */
#endif /* !__HYBRID_PP_VA_NARGS */

#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)

#ifndef __HYBRID_PP_VA_NARGS
#if defined(_MSC_VER) || defined(__INTELLISENSE__)
/* MSVC-Specific (Capable of detecting empty __VA_ARGS__ with ~,__VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(args...) args
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_1(args...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(args)
#   define __HYBRID_PP_PRIVATE_VA_NARGS_I(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,args...) N
#   define __HYBRID_PP_PRIVATE_VA_NARGS_X(args...) (~,args,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#   define __HYBRID_PP_VA_NARGS(args...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_1(__HYBRID_PP_PRIVATE_VA_NARGS_I __HYBRID_PP_PRIVATE_VA_NARGS_X(args))
#elif __has_extension(tpp_va_comma)
/* TPP-Specific (Capable of detecting empty __VA_ARGS__ with __VA_COMMA__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,args...) N
#   define __HYBRID_PP_VA_NARGS(args...) __HYBRID_PP_PRIVATE_VA_NARGS(args __VA_COMMA__ 59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#elif defined(__GNUC__) || (defined(__TPP_VERSION__) && __TPP_VERSION__ >= 103)
/* GCC-Specific (Capable of detecting empty __VA_ARGS__ with ,##__VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,args...) N
#   define __HYBRID_PP_VA_NARGS(args...) __HYBRID_PP_PRIVATE_VA_NARGS(~,##args,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#else /* ... */
/* Check if __VA_OPT__ is supported, and if it is, use it for a standard, 0-arg-capable implementation.
 * Note that we can check for `__VA_OPT__' without having to rely on any feature-test macros, since its
 * behavior is well-defined even on preprocessors that don't support it! */
#define __HYBRID_PP_PRIVATE_TEST_VA_OPT2(a, b, args...) b
#define __HYBRID_PP_PRIVATE_TEST_VA_OPT(args...) __HYBRID_PP_PRIVATE_TEST_VA_OPT2(__VA_OPT__(,) 1, 0)
#if __HYBRID_PP_PRIVATE_TEST_VA_OPT(~)
/* STD-Implementation (Capable of detecting empty __VA_ARGS__ with __VA_OPT__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,args...) N
#   define __HYBRID_PP_VA_NARGS(args...) __HYBRID_PP_PRIVATE_VA_NARGS(args __VA_OPT__(,) 59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#else /* __HYBRID_PP_PRIVATE_TEST_VA_OPT(~) */
/* STD-Implementation (Not Capable of detecting empty __VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(args...) args
#   define __HYBRID_PP_PRIVATE_VA_NARGS2(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,args...) N
#   define __HYBRID_PP_PRIVATE_VA_NARGS(args...) __HYBRID_PP_PRIVATE_VA_NARGS2(args,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)
#   define __HYBRID_PP_VA_NARGS(args...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(__HYBRID_PP_PRIVATE_VA_NARGS(args))
#endif /* !__HYBRID_PP_PRIVATE_TEST_VA_OPT(~) */
#undef __HYBRID_PP_PRIVATE_TEST_VA_OPT2
#undef __HYBRID_PP_PRIVATE_TEST_VA_OPT
#endif /* !... */
#endif /* !__HYBRID_PP_VA_NARGS */

#endif /* ... */

/* General-purpose wrapper for macro overloading:
 * >> #define MY_OVERLOADED_MACRO_1(a)           1 arg: a
 * >> #define MY_OVERLOADED_MACRO_2(a, b)        2 arg: a, b
 * >> #define MY_OVERLOADED_MACRO_3(a, b, c)     3 arg: a, b, c
 * >> #define MY_OVERLOADED_MACRO_4(a, b, c, d)  4 arg: a, b, c, d
 * >> #define MY_OVERLOADED_MACRO(...) __HYBRID_PP_VA_OVERLOAD(MY_OVERLOADED_MACRO_, (__VA_ARGS__))(__VA_ARGS__) */
#if !defined(__HYBRID_PP_VA_OVERLOAD) && defined(__HYBRID_PP_VA_NARGS)
#define __HYBRID_PP_PRIVATE_VA_OVERLOAD2(func, n) func##n
#define __HYBRID_PP_PRIVATE_VA_OVERLOAD(func, n)  __HYBRID_PP_PRIVATE_VA_OVERLOAD2(func, n)
#if defined(_MSC_VER) && !defined(__INTELLISENSE__)
/* Special  handling required to  prevent MSVC from placing  all of the varargs
 * into the first argument of the varargs function. No idea why this is needed,
 * or why this works. - After noticing the issue, I've stumbled across this fix
 * through trial and error, but I'm not complaining, since at least this works! */
#define __HYBRID_PP_VA_OVERLOAD_FE          /* nothing */
#define __HYBRID_PP_VA_OVERLOAD(func, args) \
	__HYBRID_PP_PRIVATE_VA_OVERLOAD(func, __HYBRID_PP_VA_NARGS args) __HYBRID_PP_VA_OVERLOAD_FE
#else /* _MSC_VER && !__INTELLISENSE__ */
#define __HYBRID_PP_VA_OVERLOAD(func, args) \
	__HYBRID_PP_PRIVATE_VA_OVERLOAD(func, __HYBRID_PP_VA_NARGS args)
#endif /* !_MSC_VER || __INTELLISENSE__ */
#endif /* !__HYBRID_PP_VA_OVERLOAD && __HYBRID_PP_VA_NARGS */

#endif /* !__GUARD_HYBRID_PP___VA_NARGS_H */
