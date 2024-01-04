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
#ifndef _CXX_BITS_IS_FUNCTION_H
#define _CXX_BITS_IS_FUNCTION_H 1

#include <__stdcxx.h>
#include "remove_cv.h"
#include "integral_constant.h"

__CXXDECL_BEGIN
__NAMESPACE_STD_BEGIN

#define __PRIVATE_PP_EXPAND(...) __VA_ARGS__

#if (!defined(__GNUC__) && defined(_MSC_VER)) || \
    (defined(__INTELLISENSE__) && !defined(__INTELLISENSE_GCC__))
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE(template_prefix,return_type,cc,argument_list) \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list >: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc &) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc const &) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc volatile &) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc const volatile &) argument_list >: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc &&) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc const &&) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc volatile &&) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc const volatile &&) argument_list >: public true_type {}; \
/**/
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE(template_prefix,return_type,cc,argument_list) \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list >: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc &) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc const &) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc volatile &) argument_list>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type (cc const volatile &) argument_list >: public true_type {}; \
/**/
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#else
#ifdef __COMPILER_HAVE_CXX_RVALUE_REFERENCE
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE(template_prefix,return_type,cc,argument_list) \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list >: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list &>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const &>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list volatile &>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const volatile &>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list &&>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const &&>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list volatile &&>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const volatile &&>: public true_type {}; \
/**/
#else /* __COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE(template_prefix,return_type,cc,argument_list) \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list >: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const volatile>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list &>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const &>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list volatile &>: public true_type {}; \
	template< __PRIVATE_PP_EXPAND template_prefix > struct is_function< return_type cc argument_list const volatile &>: public true_type {}; \
/**/
#endif /* !__COMPILER_HAVE_CXX_RVALUE_REFERENCE */
#endif

/*[[[deemon
print "#ifdef __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_0(cc) __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class... __ArgumentTypes),__ReturnType,cc,(__ArgumentTypes...))";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_1(cc) __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class... __ArgumentTypes),__ReturnType,cc,(__ArgumentTypes......))";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(cc,is_varargs) __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_##is_varargs(cc)";
print "#else";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_0 /" "* nothing *" "/";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_1 ,...";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV2_0 /" "* nothing *" "/";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV2_1 ...";
print "#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(cc,is_varargs) \\";
print "\t__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType),__ReturnType,cc,(__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV2_##is_varargs)) \\";
for (local x: [1:16]) {
    print "\t__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType",;
    for (local y: [:x]) {
        print ", class __At",;
        print y,;
    }
    print "),__ReturnType,cc,(",;
    for (local y: [:x]) {
        if (y)
            print ",",;
        print "__At",;
        print y,;
    }
    print " __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \\";
}
print "/" "**" "/";
print "#endif";
]]]*/
#ifdef __COMPILER_HAVE_CXX_VARIABLE_TEMPLATES
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_0(cc) __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class... __ArgumentTypes),__ReturnType,cc,(__ArgumentTypes...))
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_1(cc) __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class... __ArgumentTypes),__ReturnType,cc,(__ArgumentTypes......))
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(cc,is_varargs) __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_##is_varargs(cc)
#else
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_0 /* nothing */
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_1 ,...
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV2_0 /* nothing */
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV2_1 ...
#define __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(cc,is_varargs) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType),__ReturnType,cc,(__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV2_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0),__ReturnType,cc,(__At0 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1),__ReturnType,cc,(__At0,__At1 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2),__ReturnType,cc,(__At0,__At1,__At2 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3),__ReturnType,cc,(__At0,__At1,__At2,__At3 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7, class __At8),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7,__At8 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7, class __At8, class __At9),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7,__At8,__At9 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7, class __At8, class __At9, class __At10),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7,__At8,__At9,__At10 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7, class __At8, class __At9, class __At10, class __At11),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7,__At8,__At9,__At10,__At11 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7, class __At8, class __At9, class __At10, class __At11, class __At12),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7,__At8,__At9,__At10,__At11,__At12 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7, class __At8, class __At9, class __At10, class __At11, class __At12, class __At13),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7,__At8,__At9,__At10,__At11,__At12,__At13 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
	__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE((class __ReturnType, class __At0, class __At1, class __At2, class __At3, class __At4, class __At5, class __At6, class __At7, class __At8, class __At9, class __At10, class __At11, class __At12, class __At13, class __At14),__ReturnType,cc,(__At0,__At1,__At2,__At3,__At4,__At5,__At6,__At7,__At8,__At9,__At10,__At11,__At12,__At13,__At14 __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2_ISV_##is_varargs)) \
/**/
#endif
//[[[end]]]


template<class __T> struct is_function: public false_type {};
#if defined(__INTELLISENSE__) || (!defined(__GNUC__) && defined(_MSC_VER))
/* In Visual C, the calling convention of a function takes part in type resolution */
#if defined(__i386__) && !defined(__x86_64__)
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(__ATTR_CDECL, 0)
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(__ATTR_CDECL, 1)
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(__ATTR_STDCALL, 0)
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(__ATTR_FASTCALL, 0)
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(__ATTR_THISCALL, 0)
#else
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(/*nothing*/, 0)
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(/*nothing*/, 1)
#endif
#else
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(/*nothing*/, 0)
__PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2(/*nothing*/, 1)
#endif

#undef __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE2
#undef __PRIVATE_CXX_IS_FUNCTION_SPECIALIZE
#undef __PRIVATE_PP_EXPAND

__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_CXX_BITS_IS_FUNCTION_H */
