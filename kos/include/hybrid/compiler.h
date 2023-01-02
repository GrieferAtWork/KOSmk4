/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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
#define ATTR_NORETURN_T         __ATTR_NORETURN_T
#define ATTR_FASTCALL           __ATTR_FASTCALL
#define ATTR_STDCALL            __ATTR_STDCALL
#define ATTR_CDECL              __ATTR_CDECL
#define ATTR_SYSVABI            __ATTR_SYSVABI
#define ATTR_MSABI              __ATTR_MSABI
#define ATTR_PURE               __ATTR_PURE
#define ATTR_PURE_T             __ATTR_PURE_T
#define ATTR_CONST              __ATTR_CONST
#define ATTR_CONST_T            __ATTR_CONST_T
#define ATTR_LEAF               __ATTR_LEAF
#define ATTR_LEAF_T             __ATTR_LEAF_T
#define ATTR_FLATTEN            __ATTR_FLATTEN
#define ATTR_MALLOC             __ATTR_MALLOC
#define ATTR_MALLOC_T           __ATTR_MALLOC_T
#define ATTR_HOT                __ATTR_HOT
#define ATTR_HOT_T              __ATTR_HOT_T
#define ATTR_COLD               __ATTR_COLD
#define ATTR_COLD_T             __ATTR_COLD_T
#define ATTR_WEAK               __ATTR_WEAK
#define ATTR_ALLOC_SIZE         __ATTR_ALLOC_SIZE
#define ATTR_ALLOC_SIZE_T       __ATTR_ALLOC_SIZE_T
#define ATTR_ASSUME_ALIGNED     __ATTR_ASSUME_ALIGNED
#define ATTR_ASSUME_ALIGNED_T   __ATTR_ASSUME_ALIGNED_T
#define ATTR_ALLOC_ALIGN        __ATTR_ALLOC_ALIGN
#define ATTR_ALLOC_ALIGN_T      __ATTR_ALLOC_ALIGN_T
#define ATTR_NOTHROW            __ATTR_NOTHROW
#define ATTR_NOTHROW_T          __ATTR_NOTHROW_T
#define ATTR_DLLIMPORT          __ATTR_DLLIMPORT
#define ATTR_DLLEXPORT          __ATTR_DLLEXPORT
#define ATTR_NOCLONE            __ATTR_NOCLONE
#define ATTR_USED               __ATTR_USED
#define ATTR_UNUSED             __ATTR_UNUSED
#define ATTR_SENTINEL           __ATTR_SENTINEL
#define ATTR_SENTINEL_T         __ATTR_SENTINEL_T
#define ATTR_SENTINEL_O         __ATTR_SENTINEL_O
#define ATTR_SENTINEL_O_T       __ATTR_SENTINEL_O_T
#define ATTR_THREAD             __ATTR_THREAD
#define ATTR_DEPRECATED         __ATTR_DEPRECATED
#define ATTR_DEPRECATED_T       __ATTR_DEPRECATED_T
#define ATTR_DEPRECATED_        __ATTR_DEPRECATED_
#define ATTR_DEPRECATED_T_      __ATTR_DEPRECATED_T_
#define ATTR_WARNING            __ATTR_WARNING
#define ATTR_WARNING_T          __ATTR_WARNING_T
#define ATTR_ERROR              __ATTR_ERROR
#define ATTR_ERROR_T            __ATTR_ERROR_T
#define ATTR_SECTION            __ATTR_SECTION
#define ATTR_RETNONNULL         __ATTR_RETNONNULL
#define ATTR_RETNONNULL_T       __ATTR_RETNONNULL_T
#define ATTR_ALIGNED            __ATTR_ALIGNED
#define ATTR_ALIAS              __ATTR_ALIAS
#define ATTR_INLINE             __ATTR_INLINE
#define ATTR_FORCEINLINE        __ATTR_FORCEINLINE
#define ATTR_FALLTHROUGH        __ATTR_FALLTHROUGH
#define ATTR_PACKED             __ATTR_PACKED
#define ATTR_RETURNS_TWICE      __ATTR_RETURNS_TWICE
#define ATTR_RETURNS_TWICE_T    __ATTR_RETURNS_TWICE_T
#define ATTR_EXTERNALLY_VISIBLE __ATTR_EXTERNALLY_VISIBLE
#define ATTR_ARTIFICIAL         __ATTR_ARTIFICIAL
#define ATTR_ACCESS_NONE        __ATTR_ACCESS_NONE
#define ATTR_ACCESS_NONE_T      __ATTR_ACCESS_NONE_T
#define ATTR_INS                __ATTR_INS
#define ATTR_INS_T              __ATTR_INS_T
#define ATTR_OUTS               __ATTR_OUTS
#define ATTR_OUTS_T             __ATTR_OUTS_T
#define ATTR_INOUTS             __ATTR_INOUTS
#define ATTR_INOUTS_T           __ATTR_INOUTS_T
#define ATTR_IN_OPT             __ATTR_IN_OPT
#define ATTR_IN_OPT_T           __ATTR_IN_OPT_T
#define ATTR_OUT_OPT            __ATTR_OUT_OPT
#define ATTR_OUT_OPT_T          __ATTR_OUT_OPT_T
#define ATTR_INOUT_OPT          __ATTR_INOUT_OPT
#define ATTR_INOUT_OPT_T        __ATTR_INOUT_OPT_T
#define ATTR_IN                 __ATTR_IN
#define ATTR_IN_T               __ATTR_IN_T
#define ATTR_OUT                __ATTR_OUT
#define ATTR_OUT_T              __ATTR_OUT_T
#define ATTR_INOUT              __ATTR_INOUT
#define ATTR_INOUT_T            __ATTR_INOUT_T


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
#define COMPILER_DELETE_ASSUMPTIONS   __COMPILER_DELETE_ASSUMPTIONS
#define COMPILER_FLEXIBLE_ARRAY       __COMPILER_FLEXIBLE_ARRAY
#define COMPILER_IMPURE               __COMPILER_IMPURE
#define DEFINE_PRIVATE_ALIAS          __DEFINE_PRIVATE_ALIAS
#define DEFINE_PUBLIC_ALIAS           __DEFINE_PUBLIC_ALIAS
#define DEFINE_INTERN_ALIAS           __DEFINE_INTERN_ALIAS
#define DEFINE_PRIVATE_WEAK_ALIAS     __DEFINE_PRIVATE_WEAK_ALIAS
#define DEFINE_PUBLIC_WEAK_ALIAS      __DEFINE_PUBLIC_WEAK_ALIAS
#define DEFINE_INTERN_WEAK_ALIAS      __DEFINE_INTERN_WEAK_ALIAS

#define likely              __likely
#define unlikely            __unlikely

#define DECL_BEGIN          __DECL_BEGIN
#define DECL_END            __DECL_END
/*#define SYSDECL_BEGIN     __SYSDECL_BEGIN * Not defined to discourage use in anything but system headers. */
/*#define SYSDECL_END       __SYSDECL_END*/
#define ASMNAME             __COMPILER_ASMNAME
#define XBLOCK              __XBLOCK
#define XRETURN             __XRETURN
#define NOTHROW             __NOTHROW
#define NOTHROW_T           __NOTHROW_T
#define NOTHROW_NCX         __NOTHROW_NCX
#define NOTHROW_NCX_T       __NOTHROW_NCX_T
#define NOTHROW_RPC         __NOTHROW_RPC
#define NOTHROW_RPC_T       __NOTHROW_RPC_T
#define NOTHROW_RPC_KOS     __NOTHROW_RPC_KOS
#define NOTHROW_RPC_KOS_T   __NOTHROW_RPC_KOS_T
#define NOTHROW_RPC_NOKOS   __NOTHROW_RPC_NOKOS
#define NOTHROW_RPC_NOKOS_T __NOTHROW_RPC_NOKOS_T
#define NOTHROW_RPC_PURE    __NOTHROW_RPC_PURE
#define NOTHROW_RPC_PURE_T  __NOTHROW_RPC_PURE_T

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
#define REDIRECT        __COMPILER_REDIRECT
#define REDIRECT_VOID   __COMPILER_REDIRECT_VOID
#define VREDIRECT       __COMPILER_VREDIRECT
#define VREDIRECT_VOID  __COMPILER_VREDIRECT_VOID
#define VFREDIRECT      __COMPILER_VFREDIRECT
#define VFREDIRECT_VOID __COMPILER_VFREDIRECT_VOID
#define XREDIRECT       __COMPILER_XREDIRECT
#define XREDIRECT_VOID  __COMPILER_XREDIRECT_VOID
#endif /* !__REDIRECT_WSUPPRESS_BEGIN */
#define EIDECLARE  __COMPILER_EIDECLARE
#define EIREDIRECT __COMPILER_EIREDIRECT

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
#define NONNULL_T   __ATTR_NONNULL_T
#define NONNULL_CXX __ATTR_NONNULL_CXX
#define WUNUSED     __ATTR_WUNUSED
#define WUNUSED_T   __ATTR_WUNUSED_T
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
#define PRIVATE            __PRIVATE
#define LOCAL              __LOCAL
#define FORCELOCAL         __FORCELOCAL
#define EXTERN_INLINE      __EXTERN_INLINE
#define EXTERN_FORCEINLINE __EXTERN_FORCEINLINE

#ifdef __ASSEMBLER__
#include "__assembly.h"
#endif /* __ASSEMBLER__ */

#endif /* !__GUARD_HYBRID_COMPILER_H */
