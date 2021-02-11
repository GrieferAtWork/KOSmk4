/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef ___STDINC_H
#define ___STDINC_H 1

#ifndef __NO_KOS_SYSTEM_HEADERS__
/* Indicator for user-applications that KOS's system headers are available.
 * >> #include <string.h> // Will define `__KOS_SYSTEM_HEADERS__'
 * >> #ifdef __KOS_SYSTEM_HEADERS__
 * >> #include <hybrid/compiler.h> // Pull in KOS-specific headers without relying on `__has_include'.
 * >> #endif
 */
#define __KOS_SYSTEM_HEADERS__
#ifndef __KOS_VERSION__
#define __KOS_VERSION__ 400
#endif /* !__KOS_VERSION__ */
#endif /* !__NO_KOS_SYSTEM_HEADERS__ */

/* ... */

#if (/*defined(__cplusplus) ||*/                          \
     (!defined(__LINKER__) && !defined(__ASSEMBLY__) &&   \
      !defined(__ASSEMBLER__) && !defined(__assembler) && \
      !defined(__DEEMON__)))
#define __CC__  1 /* C Compiler. */
#define __CCAST   /* Nothing */
#else /* ... */
#undef __cplusplus
#define __CCAST(T) /* Nothing */
#endif /* !... */

#if !defined(__PE__) && !defined(__ELF__)
/* Try to determine current binary format using other platform
 * identifiers. (When KOS headers  are used on other  systems) */
#if (defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || defined(__WINDOWS__) || \
     defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) ||                       \
     defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) ||              \
     defined(_WIN32_WCE) || defined(WIN32_WCE))
#define __PE__ 1
#elif (defined(__linux__) || defined(__linux) || defined(linux) || \
       defined(__unix__) || defined(__unix) || defined(unix) ||    \
       defined(__KOS__))
#define __ELF__ 1
#elif defined(__TINYC__)
/* TCC predefines its own redirect macro when targeting ELF, meaning
 * that by testing for this predefinition, we can easily detect when
 * compiling for ELF, and conversely when compiling for PE. */
#ifdef __REDIRECT
#define __ELF__ 1
#else /* __REDIRECT */
#define __PE__  1
#endif /* !__REDIRECT */
#else /* ... */
#warning "Target binary format not defined. - Assuming `__ELF__'"
#define __ELF__ 1
#endif /* !... */
#endif /* !__PE__ && !__ELF__ */

#include "compiler/pp-generic.h"

#ifndef __CC__
#include "compiler/c.h"
#include "compiler/other.h"
#else /* !__CC__ */
#define __COMPILER_LENOF(arr)  (sizeof(arr) / sizeof(*(arr)))
#define __COMPILER_ENDOF(arr)  ((arr) + (sizeof(arr) / sizeof(*(arr))))
#define __COMPILER_STRLEN(str) (sizeof(str) / sizeof(char) - 1)
#define __COMPILER_STREND(str) ((str) + (sizeof(str) / sizeof(char) - 1))
#if defined(__clang__)
#include "compiler/clang.h"
#elif defined(__GNUC__)
#include "compiler/gcc.h"
#elif defined(_MSC_VER)
#include "compiler/msvc.h"
#else
#include "compiler/generic.h"
#endif
#ifdef __cplusplus
#include "compiler/c++.h"
#else /* __cplusplus */
#include "compiler/c.h"
#endif /* !__cplusplus */
#endif /* __CC__ */

#ifndef __SYSDECL_BEGIN
#define __SYSDECL_BEGIN __DECL_BEGIN
#define __SYSDECL_END   __DECL_END
#endif /* !__SYSDECL_BEGIN */

#ifdef __INTELLISENSE__
#define __NOTHROW /* Nothing */
#elif !defined(__PREPROCESSOR_HAVE_VA_ARGS) && !defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __NOTHROW /* Nothing */
#elif defined(__cplusplus)
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __PRIVATE_NOTHROW2(...) (__VA_ARGS__) __CXX_NOEXCEPT
#define __NOTHROW(...)          (__VA_ARGS__) __PRIVATE_NOTHROW2
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __PRIVATE_NOTHROW2(a...) (a) __CXX_NOEXCEPT
#define __NOTHROW(a...)          (a) __PRIVATE_NOTHROW2
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#elif defined(__NO_ATTR_NOTHROW)
#ifdef __STDC__
#define __NOTHROW /* Nothing */
#else /* __STDC__ */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __PRIVATE_NOTHROW2(...) ()
#define __NOTHROW(...)          (__VA_ARGS__) __PRIVATE_NOTHROW2
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __PRIVATE_NOTHROW2(a...) ()
#define __NOTHROW(a...)          (a) __PRIVATE_NOTHROW2
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */
#endif /* !__STDC__ */
#else /* ... */
#define __NOTHROW __ATTR_NOTHROW
#endif /* !... */

/* A  special  variant  of  NOTHROW  that  is  only  applied   when
 * `-fnon-call-exceptions' is disabled  (NCX --  NonCallExceptions)
 * This applies to a huge  set of functions, including  practically
 * everything from <string.h>, as well as a lot of other functions.
 *     So many as a matter of fact, that it is the default nothrow-mode
 *     used  by   magic  headers   created  by   `generated_header.dee'
 * Basically, anything that is designed to interact with user-provided
 * memory  buffers applies  for this, as  the user may  have defined a
 * signal handler to throw an  exception upon `SIGSEGV', or the  like.
 * Or alternatively, has KOS kernel exceptions enabled (s.a. <kos/except-handler.h>) */
#if (!defined(__NO_NON_CALL_EXCEPTIONS) || \
     (defined(__NON_CALL_EXCEPTIONS) && (__NON_CALL_EXCEPTIONS + 0) != 0))
#undef __NO_NON_CALL_EXCEPTIONS
#undef __NON_CALL_EXCEPTIONS
#define __NON_CALL_EXCEPTIONS
#define __NOTHROW_NCX /* Nothing */
#ifdef __cplusplus
#define __CXX_NOEXCEPT_NCX /* Nothing */
#endif /* __cplusplus */
#else /* __NON_CALL_EXCEPTIONS */
#undef __NO_NON_CALL_EXCEPTIONS
#undef __NON_CALL_EXCEPTIONS
#undef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG /* No work-around needed w/o NCX */
#define __NO_NON_CALL_EXCEPTIONS
#define __NOTHROW_NCX __NOTHROW
#ifdef __cplusplus
#define __CXX_NOEXCEPT_NCX __CXX_NOEXCEPT
#endif /* __cplusplus */
#endif /* !__NON_CALL_EXCEPTIONS */



/* RPC-nothrow exceptions definition (used for functions that may only  throw
 * exceptions due to the use of RPC callbacks and pthread cancellation points
 * which themself may throw errors).
 * By default, declare functions such that generated code is capable of  dealing
 * with throwing RPC functions (`rpc_schedule()'), as well as `pthread_cancel()'
 * -> This mainly affects system calls */
#if !defined(__NON_CALL_EXCEPTIONS) && defined(__NO_RPC_EXCEPTIONS)
#define __NOTHROW_RPC            __NOTHROW
#ifdef __KOS__
#define __NOTHROW_RPC_KOS        /* nothing */
#define __NOTHROW_RPC_NOKOS      __NOTHROW
#else /* __KOS__ */
#define __NOTHROW_RPC_KOS        __NOTHROW
#define __NOTHROW_RPC_NOKOS      /* nothing */
#endif /* !__KOS__ */
#ifdef __cplusplus
#define __CXX_NOEXCEPT_RPC       __CXX_NOEXCEPT
#ifdef __KOS__
#define __CXX_NOEXCEPT_RPC_NOKOS __CXX_NOEXCEPT
#else /* __KOS__ */
#define __CXX_NOEXCEPT_RPC_NOKOS /* nothing */
#endif /* !__KOS__ */
#endif /* __cplusplus */
#else /* !__NON_CALL_EXCEPTIONS && __NO_RPC_EXCEPTIONS */
#define __NOTHROW_RPC            /* Nothing */
#define __NOTHROW_RPC_KOS        /* nothing */
#define __NOTHROW_RPC_NOKOS      /* nothing */
#ifdef __cplusplus
#define __CXX_NOEXCEPT_RPC       /* Nothing */
#define __CXX_NOEXCEPT_RPC_NOKOS /* Nothing */
#endif /* __cplusplus */
#endif /* __NON_CALL_EXCEPTIONS || !__NO_RPC_EXCEPTIONS */

#define __untraced    /* Annotation for `if __untraced(...)' or `while __untraced(...)' \
                       * Using this macro prevents the injection of meta-data profilers \
                       * which would otherwise allow branches to be traced. */


/* Pure RPC exception declaration (functions unrelated to the current NCX mode) */
#if defined(__NO_RPC_EXCEPTIONS)
#define __NOTHROW_RPC_PURE      __NOTHROW
#ifdef __cplusplus
#define __CXX_NOEXCEPT_RPC_PURE __CXX_NOEXCEPT
#endif /* __cplusplus */
#else /* __NO_RPC_EXCEPTIONS */
#define __NOTHROW_RPC_PURE      /* Nothing */
#ifdef __cplusplus
#define __CXX_NOEXCEPT_RPC_PURE /* Nothing */
#endif /* __cplusplus */
#endif /* !__NO_RPC_EXCEPTIONS */

#if defined(__COMPILER_HAVE_AUTOTYPE) && !defined(__NO_XBLOCK)
#define __COMPILER_UNUSED(expr) __XBLOCK({ __auto_type __expr = (expr); __expr; })
#elif defined(__COMPILER_HAVE_TYPEOF) && !defined(__NO_XBLOCK)
#define __COMPILER_UNUSED(expr) __XBLOCK({ __typeof__(expr) __expr = (expr); __expr; })
#else /* ... */
#define __COMPILER_UNUSED(expr) (expr)
#endif /* !... */

#ifndef __DEFINE_PUBLIC_ALIAS
#ifdef __COMPILER_HAVE_GCC_ASM
#ifdef __PE__
#if 1 /* PE doesn't have .pushsection, .popsection,  or even .previous, however we'd  need
       * to change sections in order  to write to the `.drectve'  section that we want  to
       * export a certain symbol. - So while  in theory we can define non-public  aliases,
       * defining public ones is something that we cannot do without assuming the caller's
       * current section. */
#define __NO_DEFINE_ALIAS
#define __DEFINE_PRIVATE_ALIAS(new, old)      /* Nothing */
#define __DEFINE_PUBLIC_ALIAS(new, old)       /* Nothing */
#define __DEFINE_INTERN_ALIAS(new, old)       /* Nothing */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) /* Nothing */
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  /* Nothing */
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  /* Nothing */
#else /* ... */
#define __DEFINE_ALIAS_STR(x) #x
#define __DEFINE_PE_DIRECTIVE_STR2(directive) ".pushsection .drectve\n.ascii " #directive "\n.popsection\n"
#define __DEFINE_PE_DIRECTIVE_STR(directive)  __DEFINE_PE_DIRECTIVE_STR2(directive)
#define __DEFINE_PE_EXPORT_STR3(name)         __DEFINE_PE_DIRECTIVE_STR(" -export:" #name)
#define __DEFINE_PE_EXPORT_STR2(name)         __DEFINE_PE_EXPORT_STR3(name)
#define __DEFINE_PE_EXPORT_STR(name)          __DEFINE_PE_EXPORT_STR2(#name)
#define __DEFINE_PRIVATE_ALIAS(new, old)      __asm__(".local " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_PUBLIC_ALIAS(new, old)       __asm__(__DEFINE_PE_EXPORT_STR(new) ".global " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_INTERN_ALIAS(new, old)       __asm__(".global " __DEFINE_ALIAS_STR(new) "\n.hidden " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) __asm__(".weak " __DEFINE_ALIAS_STR(new) "\n.local " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  __asm__(__DEFINE_PE_EXPORT_STR(new) ".weak " __DEFINE_ALIAS_STR(new) "\n.global " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  __asm__(".weak " __DEFINE_ALIAS_STR(new) "\n.global " __DEFINE_ALIAS_STR(new) "\n.hidden " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#endif /* !... */
#else /* __PE__ */
#define __DEFINE_ALIAS_STR(x) #x
#define __DEFINE_PRIVATE_ALIAS(new, old)      __asm__(".local " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_PUBLIC_ALIAS(new, old)       __asm__(".global " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_INTERN_ALIAS(new, old)       __asm__(".global " __DEFINE_ALIAS_STR(new) "\n.hidden " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) __asm__(".weak " __DEFINE_ALIAS_STR(new) "\n.local " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  __asm__(".weak " __DEFINE_ALIAS_STR(new) "\n.global " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  __asm__(".weak " __DEFINE_ALIAS_STR(new) "\n.global " __DEFINE_ALIAS_STR(new) "\n.hidden " __DEFINE_ALIAS_STR(new) "\n.set " __DEFINE_ALIAS_STR(new) "," __DEFINE_ALIAS_STR(old) "\n")
#endif /* !__PE__ */
#else /* __COMPILER_HAVE_GCC_ASM */
#define __NO_DEFINE_ALIAS
#define __DEFINE_PRIVATE_ALIAS(new, old)      /* Nothing */
#define __DEFINE_PUBLIC_ALIAS(new, old)       /* Nothing */
#define __DEFINE_INTERN_ALIAS(new, old)       /* Nothing */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) /* Nothing */
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  /* Nothing */
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  /* Nothing */
#endif /* !__COMPILER_HAVE_GCC_ASM */
#endif /* !__DEFINE_PUBLIC_ALIAS */

#if !defined(__CC__)
#define __IMPDEF        /* Nothing */
#define __IMPDAT        /* Nothing */
#define __EXPDEF        /* Nothing */
#define __PUBDEF        /* Nothing */
#define __PRIVATE       /* Nothing */
#define __INTDEF        /* Nothing */
#define __PUBLIC        /* Nothing */
#define __INTERN        /* Nothing */
#define __PUBLIC_CONST  /* Nothing */
#define __INTERN_CONST  /* Nothing */
#define __PUBLIC_COMDAT /* Nothing */
#define __INTERN_COMDAT /* Nothing */
#elif defined(__INTELLISENSE__)
#define __IMPDEF        extern
#define __IMPDAT        extern
#define __EXPDEF        extern
#define __PUBDEF        extern
#define __PRIVATE       static
#define __INTDEF        extern
#define __PUBLIC        /* Nothing */
#define __INTERN        /* Nothing */
#define __PUBLIC_CONST  /* Nothing */
#define __INTERN_CONST  /* Nothing */
#define __PUBLIC_COMDAT /* Nothing */
#define __INTERN_COMDAT /* Nothing */
#elif defined(__PE__)
#define __IMPDEF        extern __ATTR_DLLIMPORT
#define __IMPDAT        extern __ATTR_DLLIMPORT
#define __EXPDEF        extern __ATTR_DLLEXPORT
#define __PUBDEF        extern
#define __PRIVATE       static
#define __INTDEF        extern
#define __PUBLIC        __ATTR_DLLEXPORT
#define __INTERN        /* Nothing */
#ifdef __cplusplus
#define __PUBLIC_CONST  extern __ATTR_DLLEXPORT
#define __INTERN_CONST  extern /* Nothing */
#else /* __cplusplus */
#define __PUBLIC_CONST  __ATTR_DLLEXPORT
#define __INTERN_CONST  /* Nothing */
#endif /* !__cplusplus */
#else /* ... */
#if defined(__KOS__) && defined(__KERNEL__)
#define __IMPDEF        __PUBDEF
#elif defined(__ELF__) && defined(__WANT_NO_PLT_RELOCATIONS)
/* Even though this does work, and does prevent the creation of PLT entries,
 * and instead uses the GOT directly in order to access functions, this also
 * prevents lazy relocations from being  used, so overall, enabling this  by
 * default would degrade program performance.
 * As such, this feature is implement as opt-in on a per-file basis, with the
 * user  having to `#define __WANT_NO_PLT_RELOCATIONS' prior to including any
 * system header file. */
#if __has_attribute(__noplt__) && __has_attribute(__visibility__)
#define __HAVE_NO_PLT_RELOCATIONS /* ACK feedback that we've understood the `__WANT_NO_PLT_RELOCATIONS' request */
#define __IMPDEF        extern __attribute__((__noplt__, __visibility__("default")))
#elif !defined(__NO_ATTR_VISIBILITY) && !defined(__NO_ATTR_NOPLT)
#define __HAVE_NO_PLT_RELOCATIONS /* ACK feedback that we've understood the `__WANT_NO_PLT_RELOCATIONS' request */
#define __IMPDEF        extern __ATTR_NOPLT __ATTR_VISIBILITY("default")
#elif !defined(__NO_ATTR_VISIBILITY)
#define __IMPDEF        extern __ATTR_VISIBILITY("default")
#elif !defined(__NO_ATTR_NOPLT)
#define __HAVE_NO_PLT_RELOCATIONS /* ACK feedback that we've understood the `__WANT_NO_PLT_RELOCATIONS' request */
#define __IMPDEF        extern __ATTR_NOPLT
#else /* ... */
#define __IMPDEF        extern
#endif /* !... */
#elif defined(__NO_ATTR_VISIBILITY)
#define __IMPDEF        extern
#else /* __ELF__ */
#define __IMPDEF        extern __ATTR_VISIBILITY("default")
#endif /* !__ELF__ */
#ifndef __NO_ATTR_VISIBILITY
#define __IMPDAT        extern __ATTR_VISIBILITY("default")
#define __EXPDEF        extern __ATTR_VISIBILITY("default")
#define __PUBDEF        extern __ATTR_VISIBILITY("default")
#define __PUBLIC               __ATTR_VISIBILITY("default")
#define __PRIVATE       static
#define __INTDEF        extern __ATTR_VISIBILITY("hidden")
#define __INTERN               __ATTR_VISIBILITY("hidden")
#ifdef __cplusplus
#define __PUBLIC_CONST  extern __ATTR_VISIBILITY("default")
#define __INTERN_CONST  extern __ATTR_VISIBILITY("hidden")
#else /* __cplusplus */
#define __PUBLIC_CONST         __ATTR_VISIBILITY("default")
#define __INTERN_CONST         __ATTR_VISIBILITY("hidden")
#endif /* !__cplusplus */
#else /* !__NO_ATTR_VISIBILITY */
#define __IMPDAT        extern
#define __EXPDEF        extern
#define __PUBDEF        extern
#define __PUBLIC        /* nothing */
#define __PRIVATE       static
#define __INTDEF        extern
#define __INTERN        /* nothing */
#ifdef __cplusplus
#define __PUBLIC_CONST  extern
#define __INTERN_CONST  extern
#else /* __cplusplus */
#define __PUBLIC_CONST  /* nothing */
#define __INTERN_CONST  /* nothing */
#endif /* !__cplusplus */
#endif /* __NO_ATTR_VISIBILITY */
#endif /* !... */

/* COMDAT function definitions:
 * When applied to  a function, an  attempt will  be made to  ensure that  multiple
 * instances  of the same  function, which may exist  in multiple compilation units
 * get merged into a single  instance at link-time. No  guaranty is made that  this
 * will actually be the case, meaning that as a fall-back, these macros are allowed
 * to  simply declare functions as static (with the exception of `__PUBLIC_COMDAT',
 * which will define  `__NO_PUBLIC_COMDAT' if  the function cannot  be provided  as
 * part of the containing programs export table)
 *   - __INTERN_COMDAT: Combination of  __PRIVATE, in  that  the symbol  is  only
 *                      guarantied to be visible within the declaring compilation
 *                      unit, but also similar to  `__INTERN', in that the  final
 *                      run-time address of the  symbol may be identical  between
 *                      multiple compilation units.
 *                      Note that unlike `__INTERN', declaration with this visibility
 *                      should  appear  in   headers,  rather   than  source   files!
 *   - __PUBLIC_COMDAT: An  optional extension to  `__INTERN_COMDAT' that exists mainly
 *                      in  c++, where  the annotated  function (may)  also be exported
 *                      from the associated program, and relocations (may) be generated
 *                      to  ensure that a  single, common address is  used in the event
 *                      that   other   linked  components   export  the   same  symbol.
 *                      If this macro is a simple alias for `__INTERN_COMDAT', then the
 *                      macro `__NO_PUBLIC_COMDAT' is defined to `1' */
#ifndef __INTERN_COMDAT
#ifdef __cplusplus
#define __INTERN_COMDAT inline __ATTR_NOINLINE __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
#elif !defined(__NO_ATTR_SELECTANY) && 0 /* __ATTR_SELECTANY can only be used for data... */
#define __INTERN_COMDAT extern __ATTR_UNUSED __ATTR_SELECTANY __ATTR_VISIBILITY("hidden")
#elif !defined(__NO_ATTR_WEAK)
#define __INTERN_COMDAT __ATTR_UNUSED __ATTR_WEAK __ATTR_VISIBILITY("hidden")
#else /* ... */
#define __INTERN_COMDAT static __ATTR_UNUSED
#endif /* !... */
#endif /* !__INTERN_COMDAT */
#ifndef __PUBLIC_COMDAT
#ifdef __cplusplus
#define __PUBLIC_COMDAT __PUBLIC inline __ATTR_NOINLINE
#elif !defined(__NO_ATTR_SELECTANY) && 0 /* __ATTR_SELECTANY can only be used for data... */
#define __PUBLIC_COMDAT extern __ATTR_SELECTANY __ATTR_VISIBILITY("default")
#elif !defined(__NO_ATTR_WEAK)
#define __PUBLIC_COMDAT __PUBLIC __ATTR_WEAK
#else /* ... */
#define __NO_PUBLIC_COMDAT
#define __PUBLIC_COMDAT __INTERN_COMDAT
#endif /* !... */
#endif /* !__PUBLIC_COMDAT */



#ifndef __UNUSED
#ifdef __INTELLISENSE__
#define __UNUSED       /* Nothing */
#elif defined(__cplusplus) || defined(__DEEMON__)
#define __UNUSED(name) /* Nothing */
#elif !defined(__NO_ATTR_UNUSED)
#define __UNUSED(name) name __ATTR_UNUSED
#elif defined(__LCLINT__)
#define __UNUSED(name) /*@unused@*/ name
#elif defined(_MSC_VER)
#define __UNUSED(name) name
#pragma warning(disable: 4100)
#else /* ... */
#define __UNUSED(name) name
#endif /* !... */
#endif /* !__UNUSED */


#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define ____PRIVATE_VREDIRECT_UNPACK(...) __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define ____PRIVATE_VREDIRECT_UNPACK(a...) a
#endif /* ... */

/* General purpose redirection implementation. */
#ifndef __COMPILER_REDIRECT
#if defined(__INTELLISENSE__) || defined(__LCLINT__)
/* Only declare the functions for intellisense to minimize IDE lag. */
#define __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       decl attr Treturn nothrow(cc name) param;
#define __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          decl attr void nothrow(cc name) param;
#ifdef ____PRIVATE_VREDIRECT_UNPACK
#define __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    decl attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       decl attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#endif /* ____PRIVATE_VREDIRECT_UNPACK */
#define __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) decl attr Treturn nothrow(cc name) paramf;
#define __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    decl attr void nothrow(cc name) paramf;
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      decl attr Treturn nothrow(cc name) param;
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         decl attr void nothrow(cc name) param;
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)                                                    extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...)                                           extern attr Treturn nothrow(cc name) param;
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)                                         extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...)                                extern attr Treturn nothrow(cc name) param;
#else /* ... */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)                                            extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl)                                   extern attr Treturn nothrow(cc name) param;
#endif /* !... */
#elif !defined(__CC__)
#define __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       /* nothing */
#define __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          /* nothing */
#define __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    /* nothing */
#define __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       /* nothing */
#define __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    /* nothing */
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      /* nothing */
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         /* nothing */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)                                                    /* nothing */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...)                                           /* nothing */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)                                         /* nothing */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...)                                /* nothing */
#else /* ... */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)                                            /* nothing */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl)                                   /* nothing */
#endif /* !... */
#elif !defined(__NO_ASMNAME)
/* Use GCC family's assembly name extension. */
#define __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       decl attr Treturn nothrow(cc name) param __ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          decl attr void nothrow(cc name) param __ASMNAME(__PP_PRIVATE_STR(asmname));
#ifdef ____PRIVATE_VREDIRECT_UNPACK
#define __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    decl attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       decl attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME(__PP_PRIVATE_STR(asmname));
#endif /* ____PRIVATE_VREDIRECT_UNPACK */
#define __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) decl attr Treturn nothrow(cc name) paramf __ASMNAME(__PP_PRIVATE_STR(asmnamef));
#define __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    decl attr void nothrow(cc name) paramf __ASMNAME(__PP_PRIVATE_STR(asmnamef));
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      decl attr Treturn nothrow(cc name) param __ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         decl attr void nothrow(cc name) param __ASMNAME(__PP_PRIVATE_STR(asmname));
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) __LOCAL attr Treturn nothrow(cc name) param __VA_ARGS__
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param __VA_ARGS__
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) extern attr Treturn nothrow(cc name) param __ASMNAME(__PP_PRIVATE_STR(asmname)); __EXTERN_INLINE attr Treturn nothrow(cc name) param __VA_ARGS__
#endif /* !__NO_EXTERN_INLINE */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) __LOCAL attr Treturn nothrow(cc name) param inline_impl
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) extern attr Treturn nothrow(cc name) param __ASMNAME(__PP_PRIVATE_STR(asmname)); __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#else /* ... */
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) __LOCAL attr Treturn nothrow(cc name) param inline_impl
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) extern attr Treturn nothrow(cc name) param __ASMNAME(__PP_PRIVATE_STR(asmname)); __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#endif /* !... */
#elif defined(__PRAGMA_REDEFINE_EXTNAME)
/* Use _Pragma("redefine_extname " #name " " #asmname). */
#define __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       __pragma(redefine_extname name asmname) decl attr Treturn nothrow(cc name) param;
#define __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          __pragma(redefine_extname name asmname) decl attr void nothrow(cc name) param;
#ifdef ____PRIVATE_VREDIRECT_UNPACK
#define __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    __pragma(redefine_extname name asmname) decl attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       __pragma(redefine_extname name asmname) decl attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#endif /* ____PRIVATE_VREDIRECT_UNPACK */
#define __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __pragma(redefine_extname name asmnamef) decl attr Treturn nothrow(cc name) paramf;
#define __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __pragma(redefine_extname name asmnamef) decl attr void nothrow(cc name) paramf;
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      __pragma(redefine_extname name asmname) decl attr Treturn nothrow(cc name) param;
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         __pragma(redefine_extname name asmname) decl attr void nothrow(cc name) param;
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) __LOCAL attr Treturn nothrow(cc name) param __VA_ARGS__
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param __VA_ARGS__
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) __pragma(redefine_extname name asmname) __EXTERN_INLINE attr Treturn nothrow(cc name) param __VA_ARGS__
#endif /* !__NO_EXTERN_INLINE */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) __LOCAL attr Treturn nothrow(cc name) param inline_impl
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) __pragma(redefine_extname name asmname) __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#else /* ... */
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          extern attr Treturn nothrow(cc name) param;
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) __LOCAL attr Treturn nothrow(cc name) param inline_impl
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) __pragma(redefine_extname name asmname) __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#endif /* !... */
#else /* ... */

#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          extern attr Treturn nothrow(cc name) param;
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param __VA_ARGS__
#endif /* !__NO_EXTERN_INLINE */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) __LOCAL attr Treturn nothrow(cc name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          extern attr Treturn nothrow(cc name) param;
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) __LOCAL attr Treturn nothrow(cc name) param inline_impl
#else /* ... */
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          extern attr Treturn nothrow(cc name) param;
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) __LOCAL attr Treturn nothrow(cc name) param inline_impl
#endif /* !... */

#define __VREDIRECT_VARUNIQUE(prefix)      __PP_CAT2(prefix,__LINE__)
#define __VREDIRECT_INIT_TYPES1(a)                                          a __VREDIRECT_VARUNIQUE(__vu0_) = __builtin_va_arg(____va_args,a);
#define __VREDIRECT_INIT_TYPES2(a,b)       __VREDIRECT_INIT_TYPES1(a)       b __VREDIRECT_VARUNIQUE(__vu1_) = __builtin_va_arg(____va_args,b);
#define __VREDIRECT_INIT_TYPES3(a,b,c)     __VREDIRECT_INIT_TYPES2(a,b)     c __VREDIRECT_VARUNIQUE(__vu2_) = __builtin_va_arg(____va_args,c);
#define __VREDIRECT_INIT_TYPES4(a,b,c,d)   __VREDIRECT_INIT_TYPES3(a,b,c)   d __VREDIRECT_VARUNIQUE(__vu3_) = __builtin_va_arg(____va_args,d);
#define __VREDIRECT_INIT_TYPES5(a,b,c,d,e) __VREDIRECT_INIT_TYPES4(a,b,c,d) e __VREDIRECT_VARUNIQUE(__vu4_) = __builtin_va_arg(____va_args,e);
#define __VREDIRECT_INIT_TYPES(n,types)    __VREDIRECT_INIT_TYPES##n types
#define __VREDIRECT_ENUM_VALUES1                                   , __VREDIRECT_VARUNIQUE(__vu0_)
#define __VREDIRECT_ENUM_VALUES2           __VREDIRECT_ENUM_VALUES1, __VREDIRECT_VARUNIQUE(__vu1_)
#define __VREDIRECT_ENUM_VALUES3           __VREDIRECT_ENUM_VALUES2, __VREDIRECT_VARUNIQUE(__vu2_)
#define __VREDIRECT_ENUM_VALUES4           __VREDIRECT_ENUM_VALUES3, __VREDIRECT_VARUNIQUE(__vu3_)
#define __VREDIRECT_ENUM_VALUES5           __VREDIRECT_ENUM_VALUES4, __VREDIRECT_VARUNIQUE(__vu4_)
#define __VREDIRECT_ENUM_VALUES(n)         __VREDIRECT_ENUM_VALUES##n

#ifndef __LOCAL_REDIRECT
#define __LOCAL_REDIRECT __LOCAL __ATTR_ARTIFICIAL
#endif /* !__LOCAL_REDIRECT */
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)  __LOCAL_REDIRECT attr Treturn nothrow(cc name) param code
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)     __LOCAL_REDIRECT attr void nothrow(cc name) param code

#ifdef __cplusplus
/* In C++, we can use use namespaces to prevent collisions with incompatible prototypes. */
#define __REDIRECT_UNIQUE  __PP_CAT2(__u,__LINE__)
#define __COMPILER_REDIRECT(decl, attr, Treturn, nothrow, cc, name, param, asmname, args)                         \
	namespace __intern { namespace __REDIRECT_UNIQUE { extern "C" { decl Treturn nothrow(cc asmname) param; } } } \
	__LOCAL_REDIRECT attr Treturn nothrow(cc name) param {                                                        \
		return (__intern::__REDIRECT_UNIQUE:: asmname) args;                                                      \
	}
#define __COMPILER_REDIRECT_VOID(decl, attr, nothrow, cc, name, param, asmname, args)                          \
	namespace __intern { namespace __REDIRECT_UNIQUE { extern "C" { decl void nothrow(cc asmname) param; } } } \
	__LOCAL_REDIRECT attr void nothrow(cc name) param {                                                        \
		(__intern::__REDIRECT_UNIQUE:: asmname) args;                                                          \
	}
#ifdef ____PRIVATE_VREDIRECT_UNPACK
#define __COMPILER_VREDIRECT(decl, attr, Treturn, nothrow, cc, name, param, asmname, args, before_va_start, varcount, vartypes)                      \
	namespace __intern { namespace __REDIRECT_UNIQUE { extern "C" { decl Treturn nothrow(cc asmname)(____PRIVATE_VREDIRECT_UNPACK param, ...); } } } \
	__LOCAL_REDIRECT attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) {                                                        \
		Treturn ____va_result;                                                                                                                       \
		__builtin_va_list ____va_args;                                                                                                               \
		__builtin_va_start(____va_args, before_va_start);                                                                                            \
		{                                                                                                                                            \
			__VREDIRECT_INIT_TYPES(varcount, vartypes)                                                                                               \
			____va_result = (__intern::__REDIRECT_UNIQUE:: asmname)(____PRIVATE_VREDIRECT_UNPACK args __VREDIRECT_ENUM_VALUES(varcount));            \
		}                                                                                                                                            \
		__builtin_va_end(____va_args);                                                                                                               \
		return ____va_result;                                                                                                                        \
	}
#define __COMPILER_VREDIRECT_VOID(decl, attr, nothrow, cc, name, param, asmname, args, before_va_start, varcount, vartypes)                       \
	namespace __intern { namespace __REDIRECT_UNIQUE { extern "C" { decl void nothrow(cc asmname)(____PRIVATE_VREDIRECT_UNPACK param, ...); } } } \
	__LOCAL_REDIRECT attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) {                                                        \
		__builtin_va_list ____va_args;                                                                                                            \
		__builtin_va_start(____va_args, before_va_start);                                                                                         \
		{                                                                                                                                         \
			__VREDIRECT_INIT_TYPES(varcount, vartypes)                                                                                            \
			(__intern::__REDIRECT_UNIQUE:: asmname)(____PRIVATE_VREDIRECT_UNPACK args __VREDIRECT_ENUM_VALUES(varcount));                         \
		}                                                                                                                                         \
		__builtin_va_end(____va_args);                                                                                                            \
	}
#define __COMPILER_VFREDIRECT(decl, attr, Treturn, nothrow, cc, name, paramf, asmnamef, vparamf, vasmnamef, args, before_va_start) \
	namespace __intern { namespace __REDIRECT_UNIQUE { extern "C" { decl Treturn nothrow(cc vasmnamef) vparamf; } } }              \
	__LOCAL_REDIRECT attr Treturn nothrow(cc name) paramf {                                                                        \
		Treturn ____va_result;                                                                                                     \
		__builtin_va_list ____va_args;                                                                                             \
		__builtin_va_start(____va_args, before_va_start);                                                                          \
		____va_result = (__intern::__REDIRECT_UNIQUE:: vasmnamef)(____PRIVATE_VREDIRECT_UNPACK args, ____va_args);                 \
		__builtin_va_end(____va_args);                                                                                             \
		return ____va_result;                                                                                                      \
	}
#define __COMPILER_VFREDIRECT_VOID(decl, attr, nothrow, cc, name, paramf, asmnamef, vparamf, vasmnamef, args, before_va_start) \
	namespace __intern { namespace __REDIRECT_UNIQUE { extern "C" { decl void nothrow(cc vasmnamef) vparamf; } } }             \
	__LOCAL_REDIRECT attr void nothrow(cc name) paramf {                                                                       \
		__builtin_va_list ____va_args;                                                                                         \
		__builtin_va_start(____va_args, before_va_start);                                                                      \
		(__intern::__REDIRECT_UNIQUE:: vasmnamef)(____PRIVATE_VREDIRECT_UNPACK args, ____va_args);                             \
		__builtin_va_end(____va_args);                                                                                         \
	}
#endif /* ____PRIVATE_VREDIRECT_UNPACK */
#else /* __cplusplus */
/* Fallback: Assume that the compiler supports scoped declarations,
 *           as  well  as  deleting  them  once  the  scope   ends.
 * NOTE: GCC actually doesn't support this one, somehow keeping  track
 *       of the C declaration types even after the scope ends, causing
 *       it to fail fatal()-style with incompatible-prototype errors.
 * HINT: This implementation does however work for MSVC when compiling for C.
 */

#define __COMPILER_REDIRECT(decl, attr, Treturn, nothrow, cc, name, param, asmname, args) \
	__LOCAL_REDIRECT attr Treturn nothrow(cc name) param {                                \
		decl Treturn nothrow(cc asmname) param;                                           \
		return (asmname) args;                                                            \
	}
#define __COMPILER_REDIRECT_VOID(decl, attr, nothrow, cc, name, param, asmname, args) \
	__LOCAL_REDIRECT attr void nothrow(cc name) param {                               \
		decl void nothrow(cc asmname) param;                                          \
		(asmname) args;                                                               \
	}
#ifdef ____PRIVATE_VREDIRECT_UNPACK
#define __COMPILER_VREDIRECT(decl, attr, Treturn, nothrow, cc, name, param, asmname, args, before_va_start, varcount, vartypes) \
	__LOCAL_REDIRECT attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) {                                   \
		decl Treturn nothrow(cc asmname)(____PRIVATE_VREDIRECT_UNPACK param, ...);                                              \
		Treturn ____va_result;                                                                                                  \
		__builtin_va_list ____va_args;                                                                                          \
		__builtin_va_start(____va_args, before_va_start);                                                                       \
		{                                                                                                                       \
			__VREDIRECT_INIT_TYPES(varcount, vartypes)                                                                          \
			____va_result = (asmname)(____PRIVATE_VREDIRECT_UNPACK args __VREDIRECT_ENUM_VALUES(varcount));                     \
		}                                                                                                                       \
		__builtin_va_end(____va_args);                                                                                          \
		return ____va_result;                                                                                                   \
	}
#define __COMPILER_VREDIRECT_VOID(decl, attr, nothrow, cc, name, param, asmname, args, before_va_start, varcount, vartypes) \
	__LOCAL_REDIRECT attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) {                                  \
		decl void nothrow(cc asmname)(____PRIVATE_VREDIRECT_UNPACK param, ...);                                             \
		__builtin_va_list ____va_args;                                                                                      \
		__builtin_va_start(____va_args, before_va_start);                                                                   \
		{                                                                                                                   \
			__VREDIRECT_INIT_TYPES(varcount, vartypes)                                                                      \
			(asmname)(____PRIVATE_VREDIRECT_UNPACK args __VREDIRECT_ENUM_VALUES(varcount));                                 \
		}                                                                                                                   \
		__builtin_va_end(____va_args);                                                                                      \
	}
#define __COMPILER_VFREDIRECT(decl, attr, Treturn, nothrow, cc, name, paramf, asmnamef, vparamf, vasmnamef, args, before_va_start) \
	__LOCAL_REDIRECT attr Treturn nothrow(cc name) paramf {                                                                        \
		decl Treturn nothrow(cc vasmnamef) vparamf;                                                                                \
		__builtin_va_list ____va_args;                                                                                             \
		Treturn ____va_result;                                                                                                     \
		__builtin_va_start(____va_args,before_va_start);                                                                           \
		____va_result = (vasmnamef)(____PRIVATE_VREDIRECT_UNPACK args,____va_args);                                                \
		__builtin_va_end(____va_args);                                                                                             \
		return ____va_result;                                                                                                      \
	}
#define __COMPILER_VFREDIRECT_VOID(decl, attr, nothrow, cc, name, paramf, asmnamef, vparamf, vasmnamef, args, before_va_start) \
	__LOCAL_REDIRECT attr void nothrow(cc name) paramf {                                                                       \
		decl void nothrow(cc vasmnamef) vparamf;                                                                               \
		__builtin_va_list ____va_args;                                                                                         \
		__builtin_va_start(____va_args,before_va_start);                                                                       \
		(vasmnamef)(____PRIVATE_VREDIRECT_UNPACK args,____va_args);                                                            \
		__builtin_va_end(____va_args);                                                                                         \
	}
#endif /* ____PRIVATE_VREDIRECT_UNPACK */
#endif /* !__cplusplus */
#endif /* !... */
#endif /* !__COMPILER_REDIRECT */

#ifdef __CC__
#ifdef __INTELLISENSE__
#ifndef __INTELLISENSE_SIZE_TYPE__
#include "hybrid/typecore.h"
#define __INTELLISENSE_SIZE_TYPE__ __SIZE_TYPE__
#endif /* !__INTELLISENSE_SIZE_TYPE__ */
#define __COMPILER_OFFSETAFTER(s, m) \
	((__INTELLISENSE_SIZE_TYPE__)(&((s *)0)->m + 1))
#if defined(__COMPILER_HAVE_TYPEOF) && !defined(__NO_builtin_types_compatible_p)
/* Syntax highlighting for improper use of `container_of' (typeof(*ptr) != typeof(type::member))
 * Only  do this with intellisense, since GCC's VLA extension might try to turn int(*)[expr(-1)]
 * into  a runtime expression `alloca((size_t)-1)' if (for  some reason) it's unable to evaluate
 * the array length expression at compile-time. */
#define __COMPILER_CONTAINER_OF(ptr, type, member)                                 \
	((type *)(int(*)[__builtin_types_compatible_p(__typeof__(((type *)0)->member), \
	                                              __typeof__(*(ptr))) ? 1 : -1])   \
	 ((__INTELLISENSE_SIZE_TYPE__)(ptr) - __builtin_offsetof(type, member)))
#else
#define __COMPILER_CONTAINER_OF(ptr, type, member) \
	((type *)((__INTELLISENSE_SIZE_TYPE__)(ptr) - __builtin_offsetof(type, member)))
#endif
#else /* __INTELLISENSE__ */
#if !defined(__SIZE_TYPE__) || !defined(__UINTPTR_TYPE__)
#include "hybrid/typecore.h"
#endif /* !__SIZE_TYPE__ || !__UINTPTR_TYPE__ */
#define __COMPILER_OFFSETAFTER(s, m)               ((__SIZE_TYPE__)(&((s *)0)->m + 1))
#define __COMPILER_CONTAINER_OF(ptr, type, member) ((type *)((__UINTPTR_TYPE__)(ptr) - __builtin_offsetof(type, member)))
#endif /* !__INTELLISENSE__ */
#endif /* __CC__ */

#ifdef __KOS_SYSTEM_HEADERS__
#if __has_include(<asm/__stdinc.h>)
#include <asm/__stdinc.h>
#endif /* __has_include(<asm/__stdinc.h>) */
#endif /* __KOS_SYSTEM_HEADERS__ */

#endif /* !___STDINC_H */
