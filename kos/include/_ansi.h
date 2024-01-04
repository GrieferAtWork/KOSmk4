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
/* (#) Portability: Cygwin (/newlib/libc/include/_ansi.h) */
/* (#) Portability: Newlib (/newlib/libc/include/_ansi.h) */
#ifndef __ANSI_H
#define __ANSI_H 1
#define _ANSIDECL_H_ 1

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/_ansi.h' */

#include <__stdinc.h>
#include <__crt.h>
#include <newlib.h>
#include <sys/config.h>

#ifndef __NO_PROTOTYPES
#define _HAVE_STDC
#endif /* __NO_PROTOTYPES */

#ifdef _HAVE_STD_CXX
#define _BEGIN_STD_C __DECL_BEGIN __NAMESPACE_STD_BEGIN
#define _END_STD_C   __NAMESPACE_STD_END __DECL_END
#else /* _HAVE_STD_CXX */
#define _BEGIN_STD_C __DECL_BEGIN
#define _END_STD_C   __DECL_END
#endif /* !_HAVE_STD_CXX */

#ifdef __NO_ATTR_NOTHROW_SUFFIX
#define _NOTHROW /* Nothing */
#else /* __NO_ATTR_NOTHROW_SUFFIX */
#define _NOTHROW __ATTR_NOTHROW
#endif /* !__NO_ATTR_NOTHROW_SUFFIX */

#ifdef _HAVE_STDC
#   define _PTR      void *
#   define _AND      ,
#   define _NOARGS   void
#   define _CONST    const
#   define _VOLATILE volatile
#   define _SIGNED   signed
#   define _DOTS     , ...
#   define _VOID     void
#   define _EXFUN_NOTHROW(name, proto) __NOTHROW(name) proto
#   define _EXFUN(name, proto)         (name) proto
#   define _EXPARM(name,proto)         (*name) proto
#   define _EXFNPTR(name,proto)        (*name) proto
#   define _DEFUN(name, arglist, args) (name)(args)
#   define _DEFUN_VOID(name)           (name)(void)
#   define _CAST_VOID                  (void)
#ifndef _PARAMS
#   define _PARAMS(args)               args
#endif /* !_PARAMS */
#else /* _HAVE_STDC */
#   define _PTR                         char *
#   define _AND                         ;
#   define _NOARGS                      /* Nothing */
#   define _CONST                       /* Nothing */
#   define _VOLATILE                    /* Nothing */
#   define _SIGNED                      /* Nothing */
#   define _DOTS                        /* Nothing */
#   define _VOID                        void
#   define _EXFUN_NOTHROW(name, proto)  name()
#   define _EXFUN(name, proto)          name()
#   define _DEFUN(name, arglist, args)  name arglist args;
#   define _DEFUN_VOID(name)            name()
#   define _CAST_VOID                   /* Nothing */
#ifndef _PARAMS
#   define _PARAMS(args)                ()
#endif /* !_PARAMS */
#endif /* !_HAVE_STDC */

#ifndef _LONG_DOUBLE
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define _LONG_DOUBLE __LONGDOUBLE
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define _LONG_DOUBLE double
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#endif /* _LONG_DOUBLE */


#undef _ATTRIBUTE
#define _ATTRIBUTE(attrs) __attribute__(attrs)
#if defined(__GNUC__) && !defined(__GNUC_STDC_INLINE__)
#define _ELIDABLE_INLINE extern __ATTR_FORCEINLINE
#else /* __GNUC__ && !__GNUC_STDC_INLINE__ */
#define _ELIDABLE_INLINE static __ATTR_INLINE
#endif /* !__GNUC__ || __GNUC_STDC_INLINE__ */

#define _NOINLINE        __ATTR_NOINLINE
#define _NOINLINE_STATIC __ATTR_NOINLINE static

#endif /* !__ANSI_H */
