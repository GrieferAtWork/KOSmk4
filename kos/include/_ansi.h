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
#ifndef __ANSI_H
#define __ANSI_H 1
#define _ANSIDECL_H_ 1

/* DISCLAIMER: This file is based off of cygwin's `/usr/include/_ansi.h' */

#include <__stdinc.h>
#include <newlib.h>
#include <sys/config.h>

#if defined(__STDC__) || 1
#define _HAVE_STDC
#endif

#ifdef _HAVE_STD_CXX
#define _BEGIN_STD_C __NAMSPACE_STD_BEGIN __DECL_BEGIN
#define _END_STD_C   __DECL_END __NAMSPACE_STD_END
#else
#define _BEGIN_STD_C __DECL_BEGIN
#define _END_STD_C   __DECL_END
#endif

#ifdef __NO_ATTR_NOTHROW_SUFFIX
#define _NOTHROW /* Nothing */
#else
#define _NOTHROW __ATTR_NOTHROW
#endif

#ifdef _HAVE_STDC
#   define _PTR      void *
#   define _AND      ,
#   define _NOARGS   void
#   define _CONST    const
#   define _VOLATILE volatile
#   define _SIGNED   signed
#   define _DOTS     , ...
#   define _VOID     void
#   define _EXFUN_NOTHROW(name,proto) (__LIBCCALL name) proto _NOTHROW
#   define _EXFUN(name,proto)         (__LIBCCALL name) proto
#   define _EXPARM(name,proto)      (* __LIBCCALL name) proto
#   define _EXFNPTR(name,proto)      (__LIBCCALL *name) proto
#   define _DEFUN(name,arglist,args) name(args)
#   define _DEFUN_VOID(name)         name(_NOARGS)
#   define _CAST_VOID               (void)
#ifndef _LONG_DOUBLE
#   define _LONG_DOUBLE              long double
#endif
#ifndef _PARAMS
#   define _PARAMS(paramlist)        paramlist
#endif
#else
#   define _PTR                         char *
#   define _AND                         ;
#   define _NOARGS                      /* Nothing */
#   define _CONST                       /* Nothing */
#   define _VOLATILE                    /* Nothing */
#   define _SIGNED                      /* Nothing */
#   define _DOTS                        /* Nothing */
#   define _VOID                        void
#   define _EXFUN(name,proto)           name()
#   define _EXFUN_NOTHROW(name,proto)   name()
#   define _DEFUN(name,arglist,args)    name arglist args;
#   define _DEFUN_VOID(name)            name()
#   define _CAST_VOID                   /* Nothing */
#   define _LONG_DOUBLE                 double
#ifndef _PARAMS
#   define _PARAMS(paramlist)          ()
#endif
#endif

#define _ATTRIBUTE(attrs) __attribute__(attrs)
#if defined(__GNUC__) && !defined(__GNUC_STDC_INLINE__)
#   define _ELIDABLE_INLINE extern __ATTR_FORCEINLINE
#else
#   define _ELIDABLE_INLINE static __ATTR_INLINE
#endif
#define _NOINLINE        __ATTR_NOINLINE
#define _NOINLINE_STATIC __ATTR_NOINLINE static

#endif /* !__ANSI_H */
