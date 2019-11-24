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
#ifndef __GUARD_HYBRID_PP___VA_NARGS_H
#define __GUARD_HYBRID_PP___VA_NARGS_H 1

#include "../../__stdinc.h"

#ifdef __PREPROCESSOR_HAVE_VA_ARGS

#ifdef __has_known_extension
#if __has_known_extension("va-nargs-in-macros")
#   if !__has_extension("va-nargs-in-macros")
#      pragma extension("va-nargs-in-macros")
#   endif
#   define __HYBRID_PP_VA_NARGS(...) __VA_NARGS__
#elif __has_known_extension("va-comma-in-macros")
#   if !__has_extension("va-comma-in-macros")
#      pragma extension("va-comma-in-macros")
#   endif
#   define __HYBRID_PP_PRIVATE_VA_NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(__VA_ARGS__ __VA_COMMA__ 59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#elif __has_known_extension("glue-comma-in-macros")
#   if !__has_extension("glue-comma-in-macros")
#      pragma extension("glue-comma-in-macros")
#   endif
#   define __HYBRID_PP_PRIVATE_VA_NARGS(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(~,##__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#endif
#endif

#ifndef __HYBRID_PP_VA_NARGS
#if defined(_MSC_VER) || defined(__INTELLISENSE__)
/* MSVC-Specific (Capable of detecting empty va_args with ~,__VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(...) __VA_ARGS__
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_1(...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(__VA_ARGS__)
#   define __HYBRID_PP_PRIVATE_VA_NARGS_I(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_PRIVATE_VA_NARGS_X(...) (~,__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_1(__HYBRID_PP_PRIVATE_VA_NARGS_I __HYBRID_PP_PRIVATE_VA_NARGS_X(__VA_ARGS__))
#elif __has_extension(tpp_va_comma)
/* TPP-Specific (Capable of detecting empty va_args with __VA_COMMA__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(__VA_ARGS__ __VA_COMMA__ 59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#elif defined(__GNUC__) || (defined(__TPP_VERSION__) && __TPP_VERSION__ >= 103)
/* GCC-Specific (Capable of detecting empty va_args with ,##__VA_ARGS__) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS(x,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS(~,##__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#else
/* STD-Implementation (Not Capable of detecting empty va_args) */
#   define __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(...) __VA_ARGS__
#   define __HYBRID_PP_PRIVATE_VA_NARGS2(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,N,...) N
#   define __HYBRID_PP_PRIVATE_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS2(__VA_ARGS__,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)
#   define __HYBRID_PP_VA_NARGS(...) __HYBRID_PP_PRIVATE_VA_NARGS_EXPAND_0(__HYBRID_PP_PRIVATE_VA_NARGS(__VA_ARGS__))
#endif
#endif /* !__HYBRID_PP_VA_NARGS */

#ifndef __HYBRID_PP_VA_OVERLOAD
#define __HYBRID_PP_PRIVATE_VA_OVERLOAD2(func, n) func##n
#define __HYBRID_PP_PRIVATE_VA_OVERLOAD(func, n)  __HYBRID_PP_PRIVATE_VA_OVERLOAD2(func, n)
#define __HYBRID_PP_VA_OVERLOAD(func, args)       __HYBRID_PP_PRIVATE_VA_OVERLOAD(func, __HYBRID_PP_VA_NARGS args)
#endif /* !__HYBRID_PP_VA_OVERLOAD */

#endif /* __PREPROCESSOR_HAVE_VA_ARGS */

#endif /* !__GUARD_HYBRID_PP___VA_NARGS_H */
