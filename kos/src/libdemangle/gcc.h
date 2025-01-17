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
#ifndef GUARD_LIBDEMANGLE_GCC_H
#define GUARD_LIBDEMANGLE_GCC_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <format-printer.h>

#include <libdemangle/api.h>
#include <libdemangle/gcc.h>

DECL_BEGIN


/* Taken from `https://itanium-cxx-abi.github.io/cxx-abi/abi.html#mangling'
 * How to read:
 * ```
 *     <...>           : Rule
 *     <function name> : Same as <name>.
 *     #...            : Comment
 *     [...]           : Optional
 *     (...)           : Grouping
 *     <foo>*          : Repeat 0, or more times
 *     <foo>+          : Repeat 1, or more times
 * ```
 *
 *
 * ```
 * <mangled-name> ::= _Z <encoding>
 *                ::= _Z <encoding> . <vendor-specific suffix>
 *
 * <encoding> ::= <function<name>> <bare-function-type>
 *            ::= <data<name>>
 *            ::= TV <type>        # virtual table
 *            ::= TT <type>        # VTT structure (construction vtable index)
 *            ::= TI <type>        # typeinfo structure
 *            ::= TS <type>        # typeinfo name (null-terminated byte string)
 *            ::= T <call-offset> <base<encoding>>           # base is the nominal target function of thunk
 *            ::= Tc <call-offset> <call-offset> <base<encoding>>
 *                                 # base is the nominal target function of thunk
 *                                 # first call-offset is 'this' adjustment
 *                                 # second call-offset is result adjustment
 *            ::= GV <object<name>>  # Guard variable for one-time initialization
 *                                   # No <type>
 *            ::= GR <object<name>> _             # First temporary
 *            ::= GR <object<name>> <seq-id> _    # Subsequent temporaries
 *            ::= GTt <encoding>
 *
 * <call-offset> ::= h <nv-offset> _
 *               ::= v <v-offset> _
 * <nv-offset> ::= <offset<number>>                              # non-virtual base override
 * <v-offset>  ::= <offset<number>> _ <virtual offset<number>>   # virtual base override, with vcall offset
 *
 * <name> ::= <nested-name>
 *        ::= <unscoped-name>
 *        ::= <unscoped-template-name> <template-args>
 *        ::= <local-name>          # See Scope Encoding below
 *        ::= St <unqualified-name> # std::
 *
 * <nested-name> ::= N [<CV-qualifiers>] [<ref-qualifier>] <prefix> <unqualified-name> E
 *               ::= N [<CV-qualifiers>] [<ref-qualifier>] <template-prefix> <template-args> E
 *
 * <local-name> ::= Z <function<encoding>> E <entity<name>> [<discriminator>]
 *              ::= Z <function<encoding>> E s [<discriminator>]
 *              ::= Z <function<encoding>> Ed [ <parameter<number>> ] _ <entity<name>>
 *
 * <unscoped-name> ::= <unqualified-name>
 *                 ::= St <unqualified-name>   # ::std::
 *
 * <unscoped-template-name> ::= <unscoped-name>
 *                          ::= <substitution>
 *
 * <prefix> ::= <unqualified-name>                 # global class or namespace
 *          ::= <prefix> <unqualified-name>        # nested class or namespace
 *          ::= <template-prefix> <template-args>  # class template specialization
 *          ::= <template-param>                   # template type parameter
 *          ::= <decltype>                         # decltype qualifier
 *          ::= <prefix> <data-member-prefix>      # initializer of a data member
 *          ::= <substitution>
 *
 * <data-member-prefix> ::= <member<source-name>> [<template-args>] M
 *
 * <template-prefix> ::= <template<unqualified-name>>           # global template
 *                   ::= <prefix> <template<unqualified-name>>  # nested template
 *                   ::= <template-param>                       # template template parameter
 *                   ::= <substitution>
 *
 * <unqualified-name> ::= <operator-name> [<abi-tags>]
 *                    ::= <ctor-dtor-name>
 *                    ::= <source-name>
 *                    ::= <unnamed-type-name>
 *                    ::= DC <source-name>+ E      # structured binding declaration
 *
 * <source-name> ::= <positive length<number>> <identifier>
 * <identifier> ::= <unqualified source code<identifier>>
 *
 * <abi-tags> ::= <abi-tag> [<abi-tags>]
 * <abi-tag> ::= B <source-name>
 *
 * <number> ::= [n] <non-negative decimal<integer>>
 *
 * <seq-id> ::= <0-9A-Z>+
 *
 * <operator-name> ::= nw        # new
 *                 ::= na        # new[]
 *                 ::= dl        # delete
 *                 ::= da        # delete[]
 *                 ::= ps        # + (unary)
 *                 ::= ng        # - (unary)
 *                 ::= ad        # & (unary)
 *                 ::= de        # * (unary)
 *                 ::= co        # ~
 *                 ::= pl        # +
 *                 ::= mi        # -
 *                 ::= ml        # *
 *                 ::= dv        # /
 *                 ::= rm        # %
 *                 ::= an        # &
 *                 ::= or        # |
 *                 ::= eo        # ^
 *                 ::= aS        # =
 *                 ::= pL        # +=
 *                 ::= mI        # -=
 *                 ::= mL        # *=
 *                 ::= dV        # /=
 *                 ::= rM        # %=
 *                 ::= aN        # &=
 *                 ::= oR        # |=
 *                 ::= eO        # ^=
 *                 ::= ls        # <<
 *                 ::= rs        # >>
 *                 ::= lS        # <<=
 *                 ::= rS        # >>=
 *                 ::= eq        # ==
 *                 ::= ne        # !=
 *                 ::= lt        # <
 *                 ::= gt        # >
 *                 ::= le        # <=
 *                 ::= ge        # >=
 *                 ::= ss        # <=>
 *                 ::= nt        # !
 *                 ::= aa        # &&
 *                 ::= oo        # ||
 *                 ::= pp        # ++ (postfix in <expression> context)
 *                 ::= mm        # -- (postfix in <expression> context)
 *                 ::= cm        # ,
 *                 ::= pm        # ->*
 *                 ::= pt        # ->
 *                 ::= cl        # ()
 *                 ::= ix        # []
 *                 ::= qu        # ?
 *                 ::= cv <type>        # (cast)
 *                 ::= li <source-name>          # operator ""
 *                 ::= v <digit> <source-name>   # vendor extended operator
 *
 * <ctor-dtor-name> ::= C1        # complete object constructor
 *                  ::= C2        # base object constructor
 *                  ::= C3        # complete object allocating constructor
 *                  ::= D0        # deleting destructor
 *                  ::= D1        # complete object destructor
 *                  ::= D2        # base object destructor
 *
 * <type> ::= <builtin-type>
 *        ::= [<extended-qualifier>*] [<CV-qualifiers>] <type>                                         # <qualified-type>
 *        ::= [<CV-qualifiers>] [<exception-spec>] [Dx] F [Y] <bare-function-type> [<ref-qualifier>] E # <function-type>
 *        ::= <class-enum-type>
 *        ::= <array-type>
 *        ::= M <class<type>> <member<type>>  # <pointer-to-member-type>
 *        ::= <template-param>
 *        ::= <template-template-param> <template-args>
 *        ::= <decltype>
 *        ::= P <type>        # pointer
 *        ::= R <type>        # l-value reference
 *        ::= O <type>        # r-value reference (C++11)
 *        ::= C <type>        # complex pair (C99)
 *        ::= G <type>        # imaginary (C99)
 *        ::= Dp <type>       # pack expansion (C++0x)
 *        ::= <substitution>  # See Compression below
 *
 * <extended-qualifier> ::= U <source-name> [<template-args>] # vendor extended type qualifier
 * <CV-qualifiers>      ::= [r] [V] [K]                       # restrict (C99), volatile, const
 *
 * <ref-qualifier>      ::= R              # & ref-qualifier
 *                      ::= O              # && ref-qualifier
 *
 * <builtin-type> ::= v        # void
 *                ::= w        # wchar_t
 *                ::= b        # bool
 *                ::= c        # char
 *                ::= a        # signed char
 *                ::= h        # unsigned char
 *                ::= s        # short
 *                ::= t        # unsigned short
 *                ::= i        # int
 *                ::= j        # unsigned int
 *                ::= l        # long
 *                ::= m        # unsigned long
 *                ::= x        # long long, __int64
 *                ::= y        # unsigned long long, __int64
 *                ::= n        # __int128
 *                ::= o        # unsigned __int128
 *                ::= f        # float
 *                ::= d        # double
 *                ::= e        # long double, __float80
 *                ::= g        # __float128
 *                ::= z        # ellipsis
 *                ::= Dd # IEEE 754r decimal floating point (64 bits)
 *                ::= De # IEEE 754r decimal floating point (128 bits)
 *                ::= Df # IEEE 754r decimal floating point (32 bits)
 *                ::= Dh # IEEE 754r half-precision floating point (16 bits)
 *                ::= DF <number> _ # ISO/IEC TS 18661 binary floating point type _FloatN (N bits)
 *                ::= Di # char32_t
 *                ::= Ds # char16_t
 *                ::= Da # auto
 *                ::= Dc # decltype(auto)
 *                ::= Dn # std::nullptr_t (i.e., decltype(nullptr))
 *                ::= u <source-name>        # vendor extended type
 *
 * <bare-function-type> ::= <signature<type>>+    # types are possible return type, then parameter types
 * <exception-spec> ::= Do                # non-throwing exception-specification (e.g., noexcept, throw())
 *                  ::= DO <expression> E # computed (instantiation-dependent) noexcept
 *                  ::= Dw <type>+ E      # dynamic exception specification with instantiation-dependent types
 *
 * <decltype>  ::= Dt <expression> E  # decltype of an id-expression or class member access (C++0x)
 *             ::= DT <expression> E  # decltype of an expression (C++0x)
 *
 * <class-enum-type> ::= <name>     # non-dependent type name, dependent type name, or dependent typename-specifier
 *                   ::= Ts <name>  # dependent elaborated type specifier using 'struct' or 'class'
 *                   ::= Tu <name>  # dependent elaborated type specifier using 'union'
 *                   ::= Te <name>  # dependent elaborated type specifier using 'enum'
 *
 * <unnamed-type-name> ::= Ut [ <non-negative<number>> ] _
 *                     ::= Ul <lambda-sig> E [ <non-negative<number>> ] _
 *
 * <array-type> ::= A <positive dimension<number>> _ <element<type>>
 *              ::= A [<dimension expression>] _ <element<type>>
 *
 * <template-param> ::= T_        # first template parameter
 *                  ::= T <parameter-2 non-negative<number>> _
 * <template-template-param> ::= <template-param>
 *                           ::= <substitution>
 *
 * <function-param> ::= fp <top-level<CV-qualifiers>> _                                                                  # L == 0, first parameter
 *                  ::= fp <top-level<CV-qualifiers>> <parameter-2 non-negative<number>> _                               # L == 0, second and later parameters
 *                  ::= fL <L-1 non-negative<number>> p <top-level<CV-qualifiers>> _                                     # L > 0, first parameter
 *                  ::= fL <L-1 non-negative<number>> p <top-level<CV-qualifiers>> <parameter-2 non-negative<number>> _  # L > 0, second and later parameters
 *
 * <template-args> ::= I <template-arg>+ E
 *
 * <template-arg> ::= <type>                                             # type or template
 *                ::= X <expression> E                                   # expression
 *                ::= <expr-primary>                                     # simple expressions
 *                ::= J <template-arg>* E                                # argument pack
 *
 * <expression> ::= <unary<operator-name>> <expression>
 *              ::= <binary<operator-name>> <expression> <expression>
 *              ::= <ternary<operator-name>> <expression> <expression> <expression>
 *              ::= pp_ <expression>                                     # prefix ++
 *              ::= mm_ <expression>                                     # prefix --
 *              ::= cl <expression>+ E                                   # expression (expr-list), call
 *              ::= cv <type> <expression>                               # type (expression), conversion with one argument
 *              ::= cv <type> _ <expression>* E                          # type (expr-list), conversion with other than one argument
 *              ::= tl <type> <braced-expression>* E                     # type {expr-list}, conversion with braced-init-list argument
 *              ::= il <braced-expression>* E                            # {expr-list}, braced-init-list in any other context
 *              ::= [gs] nw <expression>* _ <type> E                     # new (expr-list) type
 *              ::= [gs] nw <expression>* _ <type> <initializer>         # new (expr-list) type (init)
 *              ::= [gs] na <expression>* _ <type> E                     # new[] (expr-list) type
 *              ::= [gs] na <expression>* _ <type> <initializer>         # new[] (expr-list) type (init)
 *              ::= [gs] dl <expression>                                 # delete expression
 *              ::= [gs] da <expression>                                 # delete[] expression
 *              ::= dc <type> <expression>                               # dynamic_cast<type> (expression)
 *              ::= sc <type> <expression>                               # static_cast<type> (expression)
 *              ::= cc <type> <expression>                               # const_cast<type> (expression)
 *              ::= rc <type> <expression>                               # reinterpret_cast<type> (expression)
 *              ::= ti <type>                                            # typeid (type)
 *              ::= te <expression>                                      # typeid (expression)
 *              ::= st <type>                                            # sizeof (type)
 *              ::= sz <expression>                                      # sizeof (expression)
 *              ::= at <type>                                            # alignof (type)
 *              ::= az <expression>                                      # alignof (expression)
 *              ::= nx <expression>                                      # noexcept (expression)
 *              ::= <template-param>
 *              ::= <function-param>
 *              ::= dt <expression> <unresolved-name>                    # expr.name
 *              ::= pt <expression> <unresolved-name>                    # expr->name
 *              ::= ds <expression> <expression>                         # expr.*expr
 *              ::= sZ <template-param>                                  # sizeof...(T), size of a template parameter pack
 *              ::= sZ <function-param>                                  # sizeof...(parameter), size of a function parameter pack
 *              ::= sP <template-arg>* E                                 # sizeof...(T), size of a captured template parameter pack from an alias template
 *              ::= sp <expression>                                      # expression..., pack expansion
 *              ::= tw <expression>                                      # throw expression
 *              ::= tr                                                   # throw with no operand (rethrow)
 *              ::= <unresolved-name>                                    # f(p), N::f(p), ::f(p),
 *                                                                       # freestanding dependent name (e.g., T::x),
 *                                                                       # object-less non-static member reference
 *              ::= <expr-primary>
 *
 * <unresolved-name> ::= [gs] <base-unresolved-name>                     # x or (with "gs") ::x
 *                   ::= sr <unresolved-type> <base-unresolved-name>     # T::x / decltype(p)::x
 *                   ::= srN <unresolved-type> <unresolved-qualifier-level>+ E <base-unresolved-name>
 *                                                                       # T::N::x /decltype(p)::N::x
 *                   ::= [gs] sr <unresolved-qualifier-level>+ E <base-unresolved-name>
 *                                                                       # A::x, N::y, A<T>::z; "gs" means leading "::"
 *
 * <unresolved-type> ::= <template-param> [ <template-args> ]            # T:: or T<X,Y>::
 *                   ::= <decltype>                                      # decltype(p)::
 *                   ::= <substitution>
 *
 * <unresolved-qualifier-level> ::= <simple-id>
 *
 * <simple-id> ::= <source-name> [ <template-args> ]
 *
 * <base-unresolved-name> ::= <simple-id>                                # unresolved name
 *                        ::= on <operator-name>                         # unresolved operator-function-id
 *                        ::= on <operator-name> <template-args>         # unresolved operator template-id
 *                        ::= dn <destructor-name>                       # destructor or pseudo-destructor;
 *                                                                       # e.g. ~X or ~X<N-1>
 *
 * <destructor-name> ::= <unresolved-type>                               # e.g., ~T or ~decltype(f())
 *                   ::= <simple-id>                                     # e.g., ~A<2*N>
 *
 * <expr-primary> ::= L <type> <value<number>> E                         # integer literal
 *                ::= L <type> <value<float>> E                          # floating literal
 *                ::= L <string<type>> E                                 # string literal
 *                ::= L <nullptr<type>> E                                # nullptr literal (i.e., "LDnE")
 *                ::= L <pointer<type>> 0 E                              # null pointer template argument
 *                ::= L <type> <real-part<float>> _ <imag-part<float>> E # complex floating point literal (C 2000)
 *                ::= L _Z <encoding> E                                  # external name
 *
 * <braced-expression> ::= <expression>
 *                     ::= di <field<source-name>> <braced-expression>    # .name = expr
 *                     ::= dx <index<expression>> <braced-expression>     # [expr] = expr
 *                     ::= dX <range begin<expression>> <range end<expression>> <braced-expression>
 *                                                                        # [expr ... expr] = expr
 *
 * <initializer> ::= pi <expression>* E                                   # parenthesized initialization
 *
 * <discriminator> ::= _ <non-negative<number>>      # when number < 10
 *                 ::= __ <non-negative<number>> _   # when number >= 10
 *
 * <lambda-sig> ::= <parameter<type>>+  # Parameter types or "v" if the lambda has no parameters
 *
 * <substitution> ::= S <seq-id> _
 *                ::= S_
 *
 * <substitution> ::= St # std::
 *                ::= Sa # std::allocator
 *                ::= Sb # std::basic_string
 *                ::= Ss # std::basic_string<char,std::char_traits<char>,std::allocator<char>>
 *                ::= Si # std::basic_istream<char,std::char_traits<char>>
 *                ::= So # std::basic_ostream<char,std::char_traits<char>>
 *                ::= Sd # std::basic_iostream<char,std::char_traits<char>>
 * ```
 */

struct itanium_printer {
	pformatprinter ip_printer; /* Printer callback */
	void          *ip_arg;     /* Printer argument */
	ssize_t        ip_result;  /* Printer result (or negative on error) */
	/* TODO: Substitution vector */
};


INTDEF ssize_t CC
libdm_demangle_gcc(pformatprinter printer, void *arg,
                   char const *__restrict mangled_name);



DECL_END

#endif /* !GUARD_LIBDEMANGLE_GCC_H */
