/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_COMPILER_H
#define __GUARD_HYBRID_COMPILER_H 1

#include "../__stdinc.h"

/*
 * ATTR_LEAF:
 *    - Doesn't depend on any global state
 *    - (may) dereference pointers
 *    - (may) modify memory pointed-to by input arguments
 *    - Example: `memcpy()'
 * ATTR_PURE:
 *    - Doesn't depend on any global state
 *    - (may) dereference pointers
 *    - Only visible side-effect is return value (therefor mustn't return `void')
 *    - Example: `memcmp()'
 * ATTR_CONST:
 *    - Doesn't depend on any global state
 *    - Only visible side-effect is return value (therefor mustn't return `void')
 *    - Example: `abs()'
 *
 * Implications:
 *    - ATTR_PURE / ATTR_CONST --> WUNUSED
 *    - ATTR_CONST --> NOTHROW()
 *
 */

#define ATTR_NOINLINE           __ATTR_NOINLINE
#define ATTR_NORETURN           __ATTR_NORETURN
#define ATTR_FASTCALL           __ATTR_FASTCALL
#define ATTR_STDCALL            __ATTR_STDCALL
#define ATTR_CDECL              __ATTR_CDECL
#define ATTR_SYSVABI            __ATTR_SYSVABI
#define ATTR_MSABI              __ATTR_MSABI
#define ATTR_PURE               __ATTR_PURE
#define ATTR_PURE_P             __ATTR_PURE_P
#define ATTR_CONST              __ATTR_CONST
#define ATTR_CONST_P            __ATTR_CONST_P
#define ATTR_LEAF               __ATTR_LEAF
#define ATTR_LEAF_P             __ATTR_LEAF_P
#define ATTR_FLATTEN            __ATTR_FLATTEN
#define ATTR_MALLOC             __ATTR_MALLOC
#define ATTR_HOT                __ATTR_HOT
#define ATTR_COLD               __ATTR_COLD
#define ATTR_WEAK               __ATTR_WEAK
#define ATTR_ALLOC_SIZE         __ATTR_ALLOC_SIZE
#define ATTR_ASSUME_ALIGNED     __ATTR_ASSUME_ALIGNED
#define ATTR_ALLOC_ALIGN        __ATTR_ALLOC_ALIGN
#define ATTR_NOTHROW            __ATTR_NOTHROW
#define ATTR_DLLIMPORT          __ATTR_DLLIMPORT
#define ATTR_DLLEXPORT          __ATTR_DLLEXPORT
#define ATTR_NOCLONE            __ATTR_NOCLONE
#define ATTR_USED               __ATTR_USED
#define ATTR_UNUSED             __ATTR_UNUSED
#define ATTR_SENTINEL           __ATTR_SENTINEL
#define ATTR_SENTINEL_O         __ATTR_SENTINEL_O
#define ATTR_THREAD             __ATTR_THREAD
#define ATTR_DEPRECATED         __ATTR_DEPRECATED
#define ATTR_DEPRECATED_        __ATTR_DEPRECATED_
#define ATTR_WARNING            __ATTR_WARNING
#define ATTR_ERROR              __ATTR_ERROR
#define ATTR_SECTION            __ATTR_SECTION
#define ATTR_RETNONNULL         __ATTR_RETNONNULL
#define ATTR_ALIGNED            __ATTR_ALIGNED
#define ATTR_ALIAS              __ATTR_ALIAS
#define ATTR_INLINE             __ATTR_INLINE
#define ATTR_FORCEINLINE        __ATTR_FORCEINLINE
#define ATTR_FALLTHROUGH        __ATTR_FALLTHROUGH
#define ATTR_PACKED             __ATTR_PACKED
#define ATTR_RETURNS_TWICE      __ATTR_RETURNS_TWICE
#define ATTR_EXTERNALLY_VISIBLE __ATTR_EXTERNALLY_VISIBLE
#define ATTR_ARTIFICIAL         __ATTR_ARTIFICIAL

#define COMPILER_LENOF                __COMPILER_LENOF
#define COMPILER_ENDOF                __COMPILER_ENDOF
#define COMPILER_STRLEN               __COMPILER_STRLEN
#define COMPILER_STREND               __COMPILER_STREND
#define COMPILER_UNUSED               __COMPILER_UNUSED
#define COMPILER_ALIGNOF              __COMPILER_ALIGNOF
#define COMPILER_OFFSETOF             __builtin_offsetof
#define COMPILER_OFFSETAFTER          __COMPILER_OFFSETAFTER
#define COMPILER_CONTAINER_OF         __COMPILER_CONTAINER_OF
#define COMPILER_BARRIER              __COMPILER_BARRIER
#define COMPILER_READ_BARRIER         __COMPILER_READ_BARRIER
#define COMPILER_WRITE_BARRIER        __COMPILER_WRITE_BARRIER
#define COMPILER_IGNORE_UNINITIALIZED __COMPILER_IGNORE_UNINITIALIZED
#define COMPILER_FLEXIBLE_ARRAY       __COMPILER_FLEXIBLE_ARRAY
#define COMPILER_IMPURE               __COMPILER_IMPURE

#ifdef __INTELLISENSE__
#define DEFINE_PRIVATE_ALIAS(new, old)      /* nothing */
#define DEFINE_PUBLIC_ALIAS(new, old)       /* nothing */
#define DEFINE_INTERN_ALIAS(new, old)       /* nothing */
#define DEFINE_PRIVATE_WEAK_ALIAS(new, old) /* nothing */
#define DEFINE_PUBLIC_WEAK_ALIAS(new, old)  /* nothing */
#define DEFINE_INTERN_WEAK_ALIAS(new, old)  /* nothing */
#else /* __INTELLISENSE__ */
#define DEFINE_PRIVATE_ALIAS      __DEFINE_PRIVATE_ALIAS
#define DEFINE_PUBLIC_ALIAS       __DEFINE_PUBLIC_ALIAS
#define DEFINE_INTERN_ALIAS       __DEFINE_INTERN_ALIAS
#define DEFINE_PRIVATE_WEAK_ALIAS __DEFINE_PRIVATE_WEAK_ALIAS
#define DEFINE_PUBLIC_WEAK_ALIAS  __DEFINE_PUBLIC_WEAK_ALIAS
#define DEFINE_INTERN_WEAK_ALIAS  __DEFINE_INTERN_WEAK_ALIAS
#endif /* !__INTELLISENSE__ */

#define likely              __likely
#define unlikely            __unlikely

#define DECL_BEGIN          __DECL_BEGIN
#define DECL_END            __DECL_END
//#define SYSDECL_BEGIN     __SYSDECL_BEGIN /* Not defined to discourage use in anything but system headers. */
//#define SYSDECL_END       __SYSDECL_END
#define ASMNAME             __ASMNAME
#define XBLOCK              __XBLOCK
#define XRETURN             __XRETURN
#ifdef __INTELLISENSE__
#define NOTHROW             /* nothing */
#define NOTHROW_NCX         /* nothing */
#define NOTHROW_RPC         /* nothing */
#define NOTHROW_RPC_KOS     /* nothing */
#define NOTHROW_RPC_NOKOS   /* nothing */
#define NOTHROW_RPC_PURE    /* nothing */
#else /* __INTELLISENSE__ */
#define NOTHROW             __NOTHROW
#define NOTHROW_NCX         __NOTHROW_NCX
#define NOTHROW_RPC         __NOTHROW_RPC
#define NOTHROW_RPC_KOS     __NOTHROW_RPC_KOS
#define NOTHROW_RPC_NOKOS   __NOTHROW_RPC_NOKOS
#define NOTHROW_RPC_PURE    __NOTHROW_RPC_PURE
#endif /* !__INTELLISENSE__ */

#ifdef __REDIRECT_WSUPPRESS_BEGIN
/* If defined by the compiler, suppress specific warnings within redirections. */
#define REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args) __REDIRECT_WSUPPRESS_END
#define REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args) __REDIRECT_WSUPPRESS_END
#define VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes) __REDIRECT_WSUPPRESS_END
#define VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes) __REDIRECT_WSUPPRESS_END
#define VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __REDIRECT_WSUPPRESS_END
#define VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __REDIRECT_WSUPPRESS_END
#define XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code) __REDIRECT_WSUPPRESS_END
#define XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         __COMPILER_REDIRECT_WSUPPRESS_BEGIN __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code) __REDIRECT_WSUPPRESS_END
#else /* __REDIRECT_WSUPPRESS_BEGIN */
#define REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)
#define REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)
#define VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)
#define VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)
#define VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)
#define XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)
#endif /* !__REDIRECT_WSUPPRESS_BEGIN */
#define EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,__VA_ARGS__)
#define EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,__VA_ARGS__)

/* Preprocessor macros */
#define PP_PRIVATE_STR  __PP_PRIVATE_STR
#define PP_STR          __PP_STR
#define PP_PRIVATE_CAT2 __PP_PRIVATE_CAT2
#define PP_PRIVATE_CAT3 __PP_PRIVATE_CAT3
#define PP_PRIVATE_CAT4 __PP_PRIVATE_CAT4
#define PP_CAT2         __PP_CAT2
#define PP_CAT3         __PP_CAT3
#define PP_CAT4         __PP_CAT4
#define PP_PRIVATE_MUL8 __PP_PRIVATE_MUL8
#define PP_MUL8         __PP_MUL8

/* Static assertion */
#define STATIC_ASSERT     __STATIC_ASSERT
#define STATIC_ASSERT_MSG __STATIC_ASSERT_MSG

/* Attributes without ATTR_* prefix */
#define NONNULL     __ATTR_NONNULL
#define NONNULL_CXX __ATTR_NONNULL_CXX
#define WUNUSED     __ATTR_WUNUSED
#define UNUSED      __UNUSED

/* C++ default arguments */
#define DFL __DFL

/* Linkage macros */
#define IMPDAT             __IMPDAT
#define IMPDEF             __IMPDEF
#define EXPDEF             __EXPDEF
#define FUNDEF             __PUBDEF
#define DATDEF             __PUBDEF
#define PUBLIC             __PUBLIC
#define INTDEF             __INTDEF
#define INTERN             __INTERN
#define PUBLIC_CONST       __PUBLIC_CONST
#define INTERN_CONST       __INTERN_CONST
#define INTERN_COMDAT      __INTERN_COMDAT
#define PUBLIC_COMDAT      __PUBLIC_COMDAT
#define PRIVATE            __PRIVATE
#define LOCAL              __LOCAL
#define FORCELOCAL         __FORCELOCAL
#define EXTERN_INLINE      __EXTERN_INLINE
#define EXTERN_FORCEINLINE __EXTERN_FORCEINLINE

#ifdef __ASSEMBLER__
#include "__assembly.h"
#endif /* __ASSEMBLER__ */

#endif /* !__GUARD_HYBRID_COMPILER_H */
