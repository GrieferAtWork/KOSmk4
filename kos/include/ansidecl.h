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
/* (#) Portability: EMX kLIBC (/libc/include/ansidecl.h) */
/* (#) Portability: libc4/5   (/include/ansidecl.h) */
/* (#) Portability: libiberty (/include/ansidecl.h) */
#ifndef _ANSIDECL_H
#define _ANSIDECL_H 1

#include <__stdinc.h>

#include <sys/cdefs.h>

#undef ANSI_PROTOTYPES
#ifndef __NO_PROTOTYPES
#define ANSI_PROTOTYPES 1
#endif /* !__NO_PROTOTYPES */

#ifndef ANSI_PROTOTYPES
#undef const
#undef volatile
#undef signed
#define const
#define volatile
#define signed
#endif /* !ANSI_PROTOTYPES */


#define PTR                      _PTR
#define PTRCONST                 _PTR _CONST
#define LONG_DOUBLE              __LONGDOUBLE
#define AND                      _AND
#define NOARGS                   _NOARGS
#define CONST                    _CONST
#define VOLATILE                 _VOLATILE
#define SIGNED                   _SIGNED
#define DOTS                     _DOTS
#define EXFUN                    _EXFUN
#define DEFUN                    _DEFUN
#define DEFUN_VOID               _DEFUN_VOID
#define PARAMS                   _PARAMS
#define PROTO(type, name, proto) type _EXFUN(name, proto)

#if !defined(GCC_VERSION) && defined(__GNUC__)
#define GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#endif /* GCC_VERSION && __GNUC__ */

#if !defined(inline) && !defined(__ATTR_INLINE_IS_inline) && !defined(__NO_ATTR_INLINE)
#define inline __ATTR_INLINE
#endif /* !inline && !__ATTR_INLINE_IS_inline && !__NO_ATTR_INLINE */

#ifdef ANSI_PROTOTYPES
#define VPARAMS(args)               args
#define VA_START(va_list, var)      __builtin_va_start(va_list, var)
#define VA_OPEN(ap, var)            { va_list ap; __builtin_va_start(ap, var); { (void)0
#define VA_CLOSE(ap)                } __builtin_va_end(ap); }
#define VA_FIXEDARG(AP, type, name) (void)0
#else /* ANSI_PROTOTYPES */
#define VPARAMS(args)               (va_alist) va_dcl
#define VA_START(va_list, var)      __builtin_va_start(va_list)
#define VA_OPEN(ap, var)            { __builtin_va_list ap; __builtin_va_start(ap); { (void)0
#define VA_CLOSE(ap)                } __builtin_va_end(ap); }
#define VA_FIXEDARG(ap, type, name) type name = __builtin_va_arg(ap, type)
#endif /* !ANSI_PROTOTYPES */


#if __GCC_VERSION_NUM < 20700
#ifndef __attribute__
#define __attribute__(x) /* Nothing */
#endif /* !__attribute__ */
#endif /* __GCC_VERSION_NUM < 20700 */
#ifndef ATTRIBUTE_MALLOC
#define ATTRIBUTE_MALLOC __ATTR_MALLOC
#endif /* !ATTRIBUTE_MALLOC */
#ifndef ATTRIBUTE_UNUSED_LABEL
#ifdef __cplusplus
#if defined(GCC_VERSION) && GCC_VERSION >= 4005
#define ATTRIBUTE_UNUSED_LABEL __ATTR_UNUSED;
#elif !defined(GCC_VERSION)
#define ATTRIBUTE_UNUSED_LABEL __ATTR_UNUSED
#else /* ... */
#define ATTRIBUTE_UNUSED_LABEL
#endif /* !... */
#else /* __cplusplus */
#if defined(GCC_VERSION) && GCC_VERSION >= 2093
#define ATTRIBUTE_UNUSED_LABEL __ATTR_UNUSED
#elif !defined(GCC_VERSION)
#define ATTRIBUTE_UNUSED_LABEL __ATTR_UNUSED
#else /* ... */
#define ATTRIBUTE_UNUSED_LABEL
#endif /* !... */
#endif /* !__cplusplus */
#endif /* !ATTRIBUTE_UNUSED_LABEL */
#ifndef ATTRIBUTE_UNUSED
#define ATTRIBUTE_UNUSED __ATTR_UNUSED
#endif /* !ATTRIBUTE_UNUSED */
#ifndef ARG_UNUSED
#define ARG_UNUSED __UNUSED
#endif /* !ARG_UNUSED */
#ifndef ATTRIBUTE_NORETURN
#define ATTRIBUTE_NORETURN __ATTR_NORETURN
#endif /* !ATTRIBUTE_NORETURN */
#ifndef ATTRIBUTE_NONNULL
#define ATTRIBUTE_NONNULL(n) __ATTR_NONNULL((n))
#endif /* !ATTRIBUTE_NONNULL */
#ifndef ATTRIBUTE_PURE
#define ATTRIBUTE_PURE __ATTR_PURE
#endif /* !ATTRIBUTE_PURE */
#ifndef ATTRIBUTE_PRINTF
#define ATTRIBUTE_PRINTF(m, n) __ATTR_FORMAT_PRINTF(m, n) __ATTR_NONNULL((m))
#define ATTRIBUTE_PRINTF_1     ATTRIBUTE_PRINTF(1, 2)
#define ATTRIBUTE_PRINTF_2     ATTRIBUTE_PRINTF(2, 3)
#define ATTRIBUTE_PRINTF_3     ATTRIBUTE_PRINTF(3, 4)
#define ATTRIBUTE_PRINTF_4     ATTRIBUTE_PRINTF(4, 5)
#define ATTRIBUTE_PRINTF_5     ATTRIBUTE_PRINTF(5, 6)
#endif /* !ATTRIBUTE_PRINTF */
#ifndef ATTRIBUTE_FPTR_PRINTF
#if !defined(GCC_VERSION) || GCC_VERSION >= 3001
#define ATTRIBUTE_FPTR_PRINTF(m, n) ATTRIBUTE_PRINTF(m, n)
#else /* !GCC_VERSION || GCC_VERSION >= 3001 */
#define ATTRIBUTE_FPTR_PRINTF(m, n)
#endif /* GCC_VERSION && GCC_VERSION < 3001 */
#define ATTRIBUTE_FPTR_PRINTF_1 ATTRIBUTE_FPTR_PRINTF(1, 2)
#define ATTRIBUTE_FPTR_PRINTF_2 ATTRIBUTE_FPTR_PRINTF(2, 3)
#define ATTRIBUTE_FPTR_PRINTF_3 ATTRIBUTE_FPTR_PRINTF(3, 4)
#define ATTRIBUTE_FPTR_PRINTF_4 ATTRIBUTE_FPTR_PRINTF(4, 5)
#define ATTRIBUTE_FPTR_PRINTF_5 ATTRIBUTE_FPTR_PRINTF(5, 6)
#endif /* !ATTRIBUTE_FPTR_PRINTF */
#ifndef ATTRIBUTE_NULL_PRINTF
#if !defined(GCC_VERSION) || GCC_VERSION >= 3003
#define ATTRIBUTE_NULL_PRINTF(m, n) __ATTR_FORMAT_PRINTF(m, n)
#else /* !GCC_VERSION || GCC_VERSION >= 3003 */
#define ATTRIBUTE_NULL_PRINTF(m, n)
#endif /* GCC_VERSION && GCC_VERSION < 3003 */
#define ATTRIBUTE_NULL_PRINTF_1 ATTRIBUTE_NULL_PRINTF(1, 2)
#define ATTRIBUTE_NULL_PRINTF_2 ATTRIBUTE_NULL_PRINTF(2, 3)
#define ATTRIBUTE_NULL_PRINTF_3 ATTRIBUTE_NULL_PRINTF(3, 4)
#define ATTRIBUTE_NULL_PRINTF_4 ATTRIBUTE_NULL_PRINTF(4, 5)
#define ATTRIBUTE_NULL_PRINTF_5 ATTRIBUTE_NULL_PRINTF(5, 6)
#endif /* !ATTRIBUTE_NULL_PRINTF */
#ifndef ATTRIBUTE_SENTINEL
#define ATTRIBUTE_SENTINEL __ATTR_SENTINEL
#endif /* !ATTRIBUTE_SENTINEL */
#ifndef ATTRIBUTE_ALIGNED_ALIGNOF
#define ATTRIBUTE_ALIGNED_ALIGNOF(m) __ATTR_ALIGNED(__COMPILER_ALIGNOF(m))
#endif /* !ATTRIBUTE_ALIGNED_ALIGNOF */
#ifndef ATTRIBUTE_RETURNS_NONNULL
#define ATTRIBUTE_RETURNS_NONNULL __ATTR_RETNONNULL
#endif /* !ATTRIBUTE_RETURNS_NONNULL */
#ifndef ATTRIBUTE_PACKED
#define ATTRIBUTE_PACKED __ATTR_PACKED
#endif /* !ATTRIBUTE_PACKED */
#ifndef ATTRIBUTE_COLD
#define ATTRIBUTE_COLD __ATTR_COLD
#endif /* !ATTRIBUTE_COLD */
#ifndef ATTRIBUTE_HOT
#define ATTRIBUTE_HOT __ATTR_HOT
#endif /* !ATTRIBUTE_HOT */
#ifndef ATTRIBUTE_NO_SANITIZE_UNDEFINED
#if __has_attribute(no_sanitize_undefined) || (defined(GCC_VERSION) && GCC_VERSION >= 4009)
#define ATTRIBUTE_NO_SANITIZE_UNDEFINED __attribute__((no_sanitize_undefined))
#else /* __has_attribute(no_sanitize_undefined) || (GCC_VERSION && GCC_VERSION >= 4009) */
#define ATTRIBUTE_NO_SANITIZE_UNDEFINED
#endif /* !__has_attribute(no_sanitize_undefined) && (!GCC_VERSION || GCC_VERSION < 4009) */
#endif /* !ATTRIBUTE_NO_SANITIZE_UNDEFINED */
#ifndef EXPORTED_CONST
#ifdef __cplusplus
#define EXPORTED_CONST extern const
#else /* __cplusplus */
#define EXPORTED_CONST const
#endif /* !__cplusplus */
#endif /* !EXPORTED_CONST */
#ifndef ENUM_BITFIELD
#ifdef __cplusplus
#define ENUM_BITFIELD(TYPE) enum TYPE
#elif defined(GCC_VERSION) && GCC_VERSION > 2000
#define ENUM_BITFIELD(TYPE) __extension__ enum TYPE
#else /* ... */
#define ENUM_BITFIELD(TYPE) unsigned int
#endif /* !... */
#endif /* !ENUM_BITFIELD */
#ifndef GCC_FINAL
#if defined(__cplusplus) && __cplusplus >= 201103L
#define GCC_FINAL final
#elif defined(GCC_VERSION) && GCC_VERSION >= 4007
#define GCC_FINAL __final
#else /* ... */
#define GCC_FINAL /* nothing */
#endif /* !... */
#endif /* !GCC_FINAL */


#endif /* !_ANSIDECL_H */
