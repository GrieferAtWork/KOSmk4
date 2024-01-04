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
#ifndef _LIBSERVICE_TYPES_H
#define _LIBSERVICE_TYPES_H 1

#include "api.h"

#include <hybrid/typecore.h>

#include <libservice/asm/types.h>
#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#define _SERVICE_TYPE_CLASSMASK __UINT32_C(0xffff0000)
#define _SERVICE_TYPE_PARAMMASK __UINT32_C(0x0000ffff)

/* Standard types */
#define SERVICE_TYPE_VOID      0x000000 /* [TYPE(void)] Void (only for return types) */
#define SERVICE_TYPE_STR_IN    0x000001 /* [TYPE(char const *)] NUL-terminated string pointer */
#define _SERVICE_TYPE_ARCH_MIN 0x000002 /* First index for arch-specific types. (mainly those for integers) */

#ifndef SERVICE_TYPE_INTn
#error "Arch didn't define macro: `#define SERVICE_TYPE_INTn(sizeof) ...'"
#endif /* !SERVICE_TYPE_INTn */
#ifndef SERVICE_TYPE_UINTn
#error "Arch didn't define macro: `#define SERVICE_TYPE_UINTn(sizeof) ...'"
#endif /* !SERVICE_TYPE_UINTn */


/* [TYPE(void const *)] Input buffer (with size argument) */
#define SERVICE_TYPE_ARGBUF_IN(in_sizearg_index) \
	(0x010000 | (in_sizearg_index))

/* Flag for `sizearg_index' in `SERVICE_TYPE_ARGBUF_OUT'
 * and `SERVICE_TYPE_ARGBUF_INOUT' to  specify that  the
 * function's  return  value represents  may be  used to
 * indicate an upper bound on output buffer size.
 *
 * As such, the buffer size potentially copied back to
 * the caller is  `MIN(return, PARAMS[sizearg_index])' */
#define SERVICE_OUT_SIZEARG_RETURN_MINVAL 0x8000

/* [TYPE(void *)] Output buffer (with size argument)
 * NOTE: Accepts `SERVICE_OUT_SIZEARG_RETURN_MINVAL'! */
#define SERVICE_TYPE_ARGBUF_OUT(sizearg_index) \
	(0x020000 | (sizearg_index))

/* [TYPE(void *)] Input/output buffer (with size argument)
 * NOTE: Accepts `SERVICE_OUT_SIZEARG_RETURN_MINVAL'! */
#define SERVICE_TYPE_ARGBUF_INOUT(sizearg_index) \
	(0x030000 | (sizearg_index))

/* Fixed-size buffer arguments. */
#define SERVICE_TYPE_FIXBUF_IN(size)    (0x040000 | (size))
#define SERVICE_TYPE_FIXBUF_OUT(size)   (0x050000 | (size))
#define SERVICE_TYPE_FIXBUF_INOUT(size) (0x060000 | (size))

/* Max # of arguments which may be taken by any server function.
 * When more arguments are needed, those may be packaged  within
 * a  `SERVICE_TYPE_FIXBUF_IN()' argument referring to some sort
 * of buffer struct. */
#define SERVICE_ARGC_MAX 8


/* Minimum guarantied alignment for out-of-band buffers.
 *
 * Generally speaking, this is the alignment which you should strive
 * to have all buffers passed to/from service functions (both  those
 * that are fixed-length, and those that aren't). Note however  that
 * this is no  strict requirement, and  that service functions  will
 * continue to operate normally even when this alignment isn't  met.
 *
 * As far as semantics go, this is simply the alignment used  by
 * wrapper functions when allocating storage for out-of-band, as
 * well as inline buffers. */
#define SERVICE_BUFFER_ALIGNMENT __SIZEOF_POINTER__



#ifdef __CC__
__DECL_BEGIN

/* One of `SERVICE_TYPE_*' */
typedef __UINT32_TYPE__ service_typeid_t;


#ifdef __cplusplus
extern "C++" { namespace __intern {

template<class __T> struct __libservice_typeof;

template<> struct __libservice_typeof<void> { enum { __v = SERVICE_TYPE_VOID }; };
template<> struct __libservice_typeof<void *> { };       /* Explicitly disallowed */
template<> struct __libservice_typeof<void const *> { }; /* Explicitly disallowed */
template<> struct __libservice_typeof<char const *> { enum { __v = SERVICE_TYPE_STR_IN }; };
template<class __T> struct __libservice_typeof<__T *> { enum { __v = SERVICE_TYPE_FIXBUF_OUT(sizeof(__T)) }; };
template<class __T> struct __libservice_typeof<__T const *> { enum { __v = SERVICE_TYPE_FIXBUF_IN(sizeof(__T)) }; };
template<> struct __libservice_typeof<bool> { enum { __v = SERVICE_TYPE_UINTn(sizeof(bool)) }; };
#ifdef __CHAR_UNSIGNED__
template<> struct __libservice_typeof<char> { enum { __v = SERVICE_TYPE_UINTn(__SIZEOF_CHAR__) }; };
#else /* __CHAR_UNSIGNED__ */
template<> struct __libservice_typeof<char> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_CHAR__) }; };
#endif /* !__CHAR_UNSIGNED__ */
template<> struct __libservice_typeof<signed char> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_CHAR__) }; };
template<> struct __libservice_typeof<unsigned char> { enum { __v = SERVICE_TYPE_UINTn(__SIZEOF_CHAR__) }; };
#ifdef __native_wchar_t_defined
#ifdef __WCHAR_UNSIGNED__
template<> struct __libservice_typeof<wchar_t> { enum { __v = SERVICE_TYPE_UINTn(__SIZEOF_WCHAR_T__) }; };
#else /* __WCHAR_UNSIGNED__ */
template<> struct __libservice_typeof<wchar_t> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_WCHAR_T__) }; };
#endif /* !__WCHAR_UNSIGNED__ */
#endif /* __native_wchar_t_defined */
#ifdef __native_char16_t_defined
template<> struct __libservice_typeof<char16_t> { enum { __v = SERVICE_TYPE_UINTn(2) }; };
template<> struct __libservice_typeof<char32_t> { enum { __v = SERVICE_TYPE_UINTn(4) }; };
#endif /* __native_char16_t_defined */
template<> struct __libservice_typeof<short> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_SHORT__) }; };
template<> struct __libservice_typeof<unsigned short> { enum { __v = SERVICE_TYPE_UINTn(__SIZEOF_SHORT__) }; };
template<> struct __libservice_typeof<int> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_INT__) }; };
template<> struct __libservice_typeof<unsigned int> { enum { __v = SERVICE_TYPE_UINTn(__SIZEOF_INT__) }; };
template<> struct __libservice_typeof<long> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_LONG__) }; };
template<> struct __libservice_typeof<unsigned long> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_LONG__) }; };
#ifdef __COMPILER_HAVE_LONGLONG
template<> struct __libservice_typeof<__LONGLONG> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_LONG_LONG__) }; };
template<> struct __libservice_typeof<__ULONGLONG> { enum { __v = SERVICE_TYPE_INTn(__SIZEOF_LONG_LONG__) }; };
#endif /* __COMPILER_HAVE_LONGLONG */
#ifdef __COMPILER_INT8_IS_UNIQUE_TYPE
template<> struct __libservice_typeof<__int8> { enum { __v = SERVICE_TYPE_INTn(1) }; };
template<> struct __libservice_typeof<unsigned __int8> { enum { __v = SERVICE_TYPE_INTn(1) }; };
#endif /* __COMPILER_INT8_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT16_IS_UNIQUE_TYPE
template<> struct __libservice_typeof<__int16> { enum { __v = SERVICE_TYPE_INTn(2) }; };
template<> struct __libservice_typeof<unsigned __int16> { enum { __v = SERVICE_TYPE_INTn(2) }; };
#endif /* __COMPILER_INT16_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT32_IS_UNIQUE_TYPE
template<> struct __libservice_typeof<__int32> { enum { __v = SERVICE_TYPE_INTn(4) }; };
template<> struct __libservice_typeof<unsigned __int32> { enum { __v = SERVICE_TYPE_INTn(4) }; };
#endif /* __COMPILER_INT32_IS_UNIQUE_TYPE */
#ifdef __COMPILER_INT64_IS_UNIQUE_TYPE
template<> struct __libservice_typeof<__int64> { enum { __v = SERVICE_TYPE_INTn(8) }; };
template<> struct __libservice_typeof<unsigned __int64> { enum { __v = SERVICE_TYPE_INTn(8) }; };
#endif /* __COMPILER_INT64_IS_UNIQUE_TYPE */

template<class __T> struct __libservice_errval { enum { __v = -1 }; };
template<class __T> struct __libservice_errval<__T *> { enum { __v = 0 }; };
template<> struct __libservice_errval<bool> { enum { __v = 0 }; };


template<class __T> struct __libservice_funinfo;
/*[[[deemon
for (local i: [:SERVICE_ARGC_MAX]) {
	local names = ((for (local x: [:i]) "__A" + x)...);
	print("template<class __RT"),;
	if (i)
		print(", ", ", ".join(for (local x: names) "class " + x)),;
	print(">");
	print("struct __libservice_funinfo<__RT LIBSERVICE_CC("),;
	if (i)
		print(", ".join(names)),;
	print(")> {");
	print("	typedef __libservice_errval<__RT> __f_ev;");
	print("	typedef __libservice_typeof<__RT> __f_rt;");
	for (local x: [:i])
		print("	typedef __libservice_typeof<__A", x, "> __f_a", x, ";");
	for (local x: [i:SERVICE_ARGC_MAX])
		print("	typedef __libservice_typeof<void> __f_a", x, ";");
	print("};");
}
]]]*/
template<class __RT>
struct __libservice_funinfo<__RT LIBSERVICE_CC()> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<void> __f_a0;
	typedef __libservice_typeof<void> __f_a1;
	typedef __libservice_typeof<void> __f_a2;
	typedef __libservice_typeof<void> __f_a3;
	typedef __libservice_typeof<void> __f_a4;
	typedef __libservice_typeof<void> __f_a5;
	typedef __libservice_typeof<void> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
template<class __RT, class __A0>
struct __libservice_funinfo<__RT LIBSERVICE_CC(__A0)> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<__A0> __f_a0;
	typedef __libservice_typeof<void> __f_a1;
	typedef __libservice_typeof<void> __f_a2;
	typedef __libservice_typeof<void> __f_a3;
	typedef __libservice_typeof<void> __f_a4;
	typedef __libservice_typeof<void> __f_a5;
	typedef __libservice_typeof<void> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
template<class __RT, class __A0, class __A1>
struct __libservice_funinfo<__RT LIBSERVICE_CC(__A0, __A1)> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<__A0> __f_a0;
	typedef __libservice_typeof<__A1> __f_a1;
	typedef __libservice_typeof<void> __f_a2;
	typedef __libservice_typeof<void> __f_a3;
	typedef __libservice_typeof<void> __f_a4;
	typedef __libservice_typeof<void> __f_a5;
	typedef __libservice_typeof<void> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
template<class __RT, class __A0, class __A1, class __A2>
struct __libservice_funinfo<__RT LIBSERVICE_CC(__A0, __A1, __A2)> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<__A0> __f_a0;
	typedef __libservice_typeof<__A1> __f_a1;
	typedef __libservice_typeof<__A2> __f_a2;
	typedef __libservice_typeof<void> __f_a3;
	typedef __libservice_typeof<void> __f_a4;
	typedef __libservice_typeof<void> __f_a5;
	typedef __libservice_typeof<void> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
template<class __RT, class __A0, class __A1, class __A2, class __A3>
struct __libservice_funinfo<__RT LIBSERVICE_CC(__A0, __A1, __A2, __A3)> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<__A0> __f_a0;
	typedef __libservice_typeof<__A1> __f_a1;
	typedef __libservice_typeof<__A2> __f_a2;
	typedef __libservice_typeof<__A3> __f_a3;
	typedef __libservice_typeof<void> __f_a4;
	typedef __libservice_typeof<void> __f_a5;
	typedef __libservice_typeof<void> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
template<class __RT, class __A0, class __A1, class __A2, class __A3, class __A4>
struct __libservice_funinfo<__RT LIBSERVICE_CC(__A0, __A1, __A2, __A3, __A4)> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<__A0> __f_a0;
	typedef __libservice_typeof<__A1> __f_a1;
	typedef __libservice_typeof<__A2> __f_a2;
	typedef __libservice_typeof<__A3> __f_a3;
	typedef __libservice_typeof<__A4> __f_a4;
	typedef __libservice_typeof<void> __f_a5;
	typedef __libservice_typeof<void> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
template<class __RT, class __A0, class __A1, class __A2, class __A3, class __A4, class __A5>
struct __libservice_funinfo<__RT LIBSERVICE_CC(__A0, __A1, __A2, __A3, __A4, __A5)> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<__A0> __f_a0;
	typedef __libservice_typeof<__A1> __f_a1;
	typedef __libservice_typeof<__A2> __f_a2;
	typedef __libservice_typeof<__A3> __f_a3;
	typedef __libservice_typeof<__A4> __f_a4;
	typedef __libservice_typeof<__A5> __f_a5;
	typedef __libservice_typeof<void> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
template<class __RT, class __A0, class __A1, class __A2, class __A3, class __A4, class __A5, class __A6>
struct __libservice_funinfo<__RT LIBSERVICE_CC(__A0, __A1, __A2, __A3, __A4, __A5, __A6)> {
	typedef __libservice_errval<__RT> __f_ev;
	typedef __libservice_typeof<__RT> __f_rt;
	typedef __libservice_typeof<__A0> __f_a0;
	typedef __libservice_typeof<__A1> __f_a1;
	typedef __libservice_typeof<__A2> __f_a2;
	typedef __libservice_typeof<__A3> __f_a3;
	typedef __libservice_typeof<__A4> __f_a4;
	typedef __libservice_typeof<__A5> __f_a5;
	typedef __libservice_typeof<__A6> __f_a6;
	typedef __libservice_typeof<void> __f_a7;
};
/*[[[end]]]*/
template<class __RT, class... __Args>
struct __libservice_funinfo<__RT(LIBSERVICE_CC *)(__Args...)>
    : public __libservice_funinfo<__RT LIBSERVICE_CC(__Args...)> { };
template<class __RT, class... __Args>
struct __libservice_funinfo<__RT(LIBSERVICE_CC &)(__Args...)>
    : public __libservice_funinfo<__RT LIBSERVICE_CC(__Args...)> { };
}}

#define SERVICE_CXX_TYPEOF(...)       ((service_typeid_t)::__intern::__libservice_typeof<__VA_ARGS__>::__v)
#define SERVICE_CXX_FUNINFO(function) ::__intern::__libservice_funinfo<decltype(function)>
#endif /* __cplusplus */


__DECL_END
#endif /* __CC__ */



#endif /* !_LIBSERVICE_TYPES_H */
