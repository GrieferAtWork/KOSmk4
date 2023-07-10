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
#define __CC__ 1 /* C Compiler. */
#define __CCAST  /* Nothing */
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
#include "compiler/other.h"
#else /* !__CC__ */
#define __COMPILER_LENOF(arr)  (sizeof(arr) / sizeof(*(arr)))
#define __COMPILER_ENDOF(arr)  ((arr) + sizeof(arr) / sizeof(*(arr)))
#define __COMPILER_STRLEN(str) (sizeof(str) / sizeof(char) - 1)
#define __COMPILER_STREND(str) ((str) + sizeof(str) / sizeof(char) - 1)
#if defined(__clang__)
#include "compiler/clang.h"
#elif defined(__GNUC__)
#include "compiler/gcc.h"
#elif defined(_MSC_VER)
#include "compiler/msvc.h"
#else /* ... */
#include "compiler/generic.h"
#endif /* !... */
#ifdef __cplusplus
#include "compiler/c++.h"
#else /* __cplusplus */
#include "compiler/c.h"
#endif /* !__cplusplus */
#endif /* __CC__ */

#ifndef __has_GCC_warning
#define __has_GCC_warning(x) 0
#define __pragma_GCC_diagnostic_push               /* nothing */
#define __pragma_GCC_diagnostic_pop                /* nothing */
#define __pragma_GCC_diagnostic_ignored(name)      /* nothing */
#define __pragma_GCC_diagnostic_push_ignored(name) /* nothing */
#define __pragma_GCC_diagnostic_pop_ignored(name)  /* nothing */
#endif /* !__has_GCC_warning */

#ifndef __pragma_MSVC_diagnostic_ignored
#define __pragma_MSVC_diagnostic_ignored(ids)      /* nothing */
#define __pragma_MSVC_diagnostic_push_ignored(ids) /* nothing */
#define __pragma_MSVC_diagnostic_pop_ignored(ids)  /* nothing */
#endif /* !__pragma_MSVC_diagnostic_ignored */


#ifndef __SYSDECL_BEGIN
#define __SYSDECL_BEGIN __DECL_BEGIN
#define __SYSDECL_END   __DECL_END
#endif /* !__SYSDECL_BEGIN */

#ifndef __NOTHROW
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
#endif /* !__NOTHROW */


/* A  special  variant  of  NOTHROW  that  is  only  applied   when
 * `-fnon-call-exceptions' is disabled  (NCX --  NonCallExceptions)
 * This applies to a huge  set of functions, including  practically
 * everything from <string.h>, as well as a lot of other functions.
 *     So many as a matter of fact, that it is the default nothrow-
 *     mode used by magic headers created by `generated_header.dee'
 * Basically, anything that is designed to interact with user-provided
 * memory buffers qualifies for this, as  the user may have defined  a
 * signal handler to throw an exception upon `SIGSEGV', or the like.
 * Or alternatively, has KOS kernel exceptions enabled (s.a. <kos/except-handler.h>) */
#ifndef __NOTHROW_NCX
#if (!defined(__NO_NON_CALL_EXCEPTIONS) || \
     (defined(__NON_CALL_EXCEPTIONS) && (__NON_CALL_EXCEPTIONS + 0) != 0) || \
     (defined(__KOS__) && defined(__KERNEL__)))
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
#endif /* !__NOTHROW_NCX */



/* RPC-nothrow exceptions definition (used for functions that may only  throw
 * exceptions due to the use of RPC callbacks and pthread cancellation points
 * which themself may throw errors).
 * By default, declare functions such that generated code is capable of  dealing
 * with throwing RPC functions (`rpc_schedule()'), as well as `pthread_cancel()'
 * -> This mainly affects system calls */
#ifndef __NOTHROW_RPC
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
#endif /* !__NOTHROW_RPC */


/* Same as `__NOTHROW', but must be used in `typedef's and variable declarations:
 * >> typedef void NOTHROW_T(KCALL *PFUN)(void);
 * >> typedef void NOTHROW_T(KCALL TFUN)(void);
 * >> void NOTHROW_T(KCALL *funptr)(void);
 * >> void NOTHROW(KCALL fun)(void); */
#if (defined(__cplusplus) && \
     ((defined(__GNUC__) && __GNUC__ >= 12))) /* TODO: Other compilers? */
#define __NOTHROW_T           __NOTHROW
#define __NOTHROW_NCX_T       __NOTHROW_NCX
#define __NOTHROW_RPC_T       __NOTHROW_RPC
#define __NOTHROW_RPC_KOS_T   __NOTHROW_RPC_KOS
#define __NOTHROW_RPC_NOKOS_T __NOTHROW_RPC_NOKOS
#define __NOTHROW_RPC_PURE_T  __NOTHROW_RPC_PURE
#else /* __cplusplus */
#define __NOTHROW_T           /* nothing */
#define __NOTHROW_NCX_T       /* nothing */
#define __NOTHROW_RPC_T       /* nothing */
#define __NOTHROW_RPC_KOS_T   /* nothing */
#define __NOTHROW_RPC_NOKOS_T /* nothing */
#define __NOTHROW_RPC_PURE_T  /* nothing */
#endif /* !__cplusplus */
#if 0 /* These (currently) result in -Wattribute warnings */
#define __ATTR_PURE_T          __ATTR_PURE
#define __ATTR_LEAF_T          __ATTR_LEAF
#define __ATTR_HOT_T           __ATTR_HOT
#define __ATTR_COLD_T          __ATTR_COLD
#define __ATTR_NOTHROW_T       __ATTR_NOTHROW
#define __ATTR_RETURNS_TWICE_T __ATTR_RETURNS_TWICE
#else
#define __ATTR_PURE_T          /* nothing */
#define __ATTR_LEAF_T          /* nothing */
#define __ATTR_HOT_T           /* nothing */
#define __ATTR_COLD_T          /* nothing */
#define __ATTR_NOTHROW_T       /* nothing */
#define __ATTR_RETURNS_TWICE_T /* nothing */
#endif
#if 1
#define __ATTR_CONST_T          __ATTR_CONST
#define __ATTR_WUNUSED_T        __ATTR_WUNUSED
#define __ATTR_RETNONNULL_T     __ATTR_RETNONNULL
#define __ATTR_NONNULL_T        __ATTR_NONNULL
#define __ATTR_NORETURN_T       __ATTR_NORETURN
#define __ATTR_MALLOC_T         __ATTR_MALLOC
#define __ATTR_ALLOC_SIZE_T     __ATTR_ALLOC_SIZE
#define __ATTR_ASSUME_ALIGNED_T __ATTR_ASSUME_ALIGNED
#define __ATTR_ALLOC_ALIGN_T    __ATTR_ALLOC_ALIGN
#define __ATTR_SENTINEL_T       __ATTR_SENTINEL
#define __ATTR_SENTINEL_O_T     __ATTR_SENTINEL_O
#define __ATTR_DEPRECATED_T     __ATTR_DEPRECATED
#define __ATTR_DEPRECATED_T_    __ATTR_DEPRECATED_
#define __ATTR_WARNING_T        __ATTR_WARNING
#define __ATTR_ERROR_T          __ATTR_ERROR
#define __ATTR_ACCESS_NONE_T    __ATTR_ACCESS_NONE
#define __ATTR_INS_T            __ATTR_INS
#define __ATTR_OUTS_T           __ATTR_OUTS
#define __ATTR_INOUTS_T         __ATTR_INOUTS
#define __ATTR_IN_OPT_T         __ATTR_IN_OPT
#define __ATTR_OUT_OPT_T        __ATTR_OUT_OPT
#define __ATTR_INOUT_OPT_T      __ATTR_INOUT_OPT
#define __ATTR_IN_T             __ATTR_IN
#define __ATTR_OUT_T            __ATTR_OUT
#define __ATTR_INOUT_T          __ATTR_INOUT
#else
#define __ATTR_LEAF_T           /* nothing */
#define __ATTR_CONST_T          /* nothing */
#define __ATTR_WUNUSED_T        /* nothing */
#define __ATTR_RETNONNULL_T     /* nothing */
#define __ATTR_NONNULL_T        /* nothing */
#define __ATTR_NORETURN_T       /* nothing */
#define __ATTR_MALLOC_T         /* nothing */
#define __ATTR_HOT_T            /* nothing */
#define __ATTR_COLD_T           /* nothing */
#define __ATTR_ALLOC_SIZE_T     /* nothing */
#define __ATTR_ASSUME_ALIGNED_T /* nothing */
#define __ATTR_ALLOC_ALIGN_T    /* nothing */
#define __ATTR_NOTHROW_T        /* nothing */
#define __ATTR_SENTINEL_T       /* nothing */
#define __ATTR_SENTINEL_O_T     /* nothing */
#define __ATTR_DEPRECATED_T     /* nothing */
#define __ATTR_DEPRECATED_T_    /* nothing */
#define __ATTR_WARNING_T        /* nothing */
#define __ATTR_ERROR_T          /* nothing */
#define __ATTR_RETURNS_TWICE_T  /* nothing */
#define __ATTR_ACCESS_NONE_T    /* nothing */
#define __ATTR_INS_T            /* nothing */
#define __ATTR_OUTS_T           /* nothing */
#define __ATTR_INOUTS_T         /* nothing */
#define __ATTR_IN_OPT_T         /* nothing */
#define __ATTR_OUT_OPT_T        /* nothing */
#define __ATTR_INOUT_OPT_T      /* nothing */
#define __ATTR_IN_T             /* nothing */
#define __ATTR_OUT_T            /* nothing */
#define __ATTR_INOUT_T          /* nothing */
#endif


/* Annotation for `if __untraced(...)' or `while __untraced(...)'
 * Using this macro prevents the injection of meta-data profilers
 * which would otherwise allow branches to be traced. */
#define __untraced /* nothing */


#if defined(__COMPILER_HAVE_AUTOTYPE) && !defined(__NO_XBLOCK)
#define __COMPILER_UNUSED(expr) __XBLOCK({ __auto_type __cu_expr = (expr); __cu_expr; })
#elif defined(__COMPILER_HAVE_TYPEOF) && !defined(__NO_XBLOCK)
#define __COMPILER_UNUSED(expr) __XBLOCK({ __typeof__(expr) __cu_expr = (expr); __cu_expr; })
#else /* ... */
#define __COMPILER_UNUSED /* nothing */
#endif /* !... */

#ifndef __DEFINE_PUBLIC_ALIAS
#if defined(__INTELLISENSE_GCC__) && 0
#define __DEFINE_PRIVATE_ALIAS(new, old)      static __typeof__(old) new __attribute__((__alias__(#old)))
#define __DEFINE_PUBLIC_ALIAS(new, old)       __typeof__(old) new __attribute__((__alias__(#old)))
#define __DEFINE_INTERN_ALIAS(new, old)       __typeof__(old) new __attribute__((__alias__(#old)))
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) static __typeof__(old) new __attribute__((__alias__(#old)))
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  __typeof__(old) new __attribute__((__alias__(#old)))
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  __typeof__(old) new __attribute__((__alias__(#old)))
#elif defined(__INTELLISENSE__)
#define __NO_DEFINE_ALIAS
#define __DEFINE_PRIVATE_ALIAS(new, old)      /* nothing */
#define __DEFINE_PUBLIC_ALIAS(new, old)       /* nothing */
#define __DEFINE_INTERN_ALIAS(new, old)       /* nothing */
#define __DEFINE_PRIVATE_WEAK_ALIAS(new, old) /* nothing */
#define __DEFINE_PUBLIC_WEAK_ALIAS(new, old)  /* nothing */
#define __DEFINE_INTERN_WEAK_ALIAS(new, old)  /* nothing */
#elif defined(__COMPILER_HAVE_GCC_ASM)
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

#ifndef __CC__
#define __IMPDEF                               /* Nothing */
#define __IMPDAT                               /* Nothing */
#define __EXPDEF                               /* Nothing */
#define __PUBDEF                               /* Nothing */
#define __PRIVATE                              /* Nothing */
#define __INTDEF                               /* Nothing */
#define __PUBLIC                               /* Nothing */
#define __INTERN                               /* Nothing */
#define __PUBLIC_CONST                         /* Nothing */
#define __INTERN_CONST                         /* Nothing */
#define __INTERN_COMDAT(name)                  /* Nothing */
#define __INTERN_COMDAT_SECTION(sectnam, name) /* Nothing */
#define __INTERN_INLINE(name)                  /* Nothing */
#define __INTERN_INLINE_SECTION(sectnam, name) /* Nothing */
#elif defined(__INTELLISENSE__)
#define __IMPDEF                               extern
#define __IMPDAT                               extern
#define __EXPDEF                               extern
#define __PUBDEF                               extern
#define __PRIVATE                              static
#define __INTDEF                               extern
#define __PUBLIC                               /* Nothing */
#define __INTERN                               /* Nothing */
#define __PUBLIC_CONST                         /* Nothing */
#define __INTERN_CONST                         /* Nothing */
#define __INTERN_COMDAT(name)                  /* Nothing */
#define __INTERN_COMDAT_SECTION(sectnam, name) /* Nothing */
#define __INTERN_INLINE(name)                  /* Nothing */
#define __INTERN_INLINE_SECTION(sectnam, name) /* Nothing */
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

/* COMDAT function definitions
 *
 * - Only emit code if function is actually used
 * - Try to use COMDAT symbols, meaning in case of multiple definitions in different
 *   source  files, one is selected randomly that is then linked to all other source
 *   files. (if this part isn't supported, define `__NO_INTERN_COMDAT')
 * - Symbol visibility is either INTERN or PRIVATE (the later only in the  fallback
 *   case where we're unable to declare COMDAT symbols, in which case we'll instead
 *   declare them as PRIVATE)
 *
 * >> __INTERN_COMDAT("foo")                  void foo() { ... } // Normal comdat symbol; impl in ".text"
 * >> __INTERN_COMDAT_SECTION(".text", "foo") void foo() { ... } // Normal comdat symbol; impl in custom section
 * >> __INTERN_INLINE("foo")                  void foo() { ... } // Try to inline; non-inline impl in ".text"
 * >> __INTERN_INLINE_SECTION(".text", "foo") void foo() { ... } // Try to inline; non-inline impl in custom section
 */
#ifndef __INTERN_COMDAT
#if defined(__GNUC__) && defined(__ELF__) && 0 /* XXX: This method doesn't work with `*.constprop.0' functions... */
#define __INTERN_COMDAT_SECTION(sectnam, name) static __attribute__((__unused__, __section__(sectnam "." name ",\"axG\",@progbits," name ",comdat;.weak " name ";.hidden " name "#")))
#define __INTERN_COMDAT(name)                  static __attribute__((__unused__, __section__(".text." name ",\"axG\",@progbits," name ",comdat;.weak " name ";.hidden " name "#")))
#ifdef __cplusplus
#define __INTERN_INLINE_SECTION(sectnam, name) inline __attribute__((__unused__, __visibility__("hidden"), __section__(sectnam)))
#define __INTERN_INLINE(name)                  inline __attribute__((__unused__, __visibility__("hidden")))
#else /* __cplusplus */
#define __INTERN_INLINE_SECTION(sectnam, name) static __inline__ __attribute__((__section__(sectnam "." name ",\"axG\",@progbits," name ",comdat;.weak " name ";.hidden " name "#")))
#define __INTERN_INLINE(name)                  static __inline__ __attribute__((__section__(".text." name ",\"axG\",@progbits," name ",comdat;.weak " name ";.hidden " name "#")))
#endif /* !__cplusplus */
#elif defined(__cplusplus)
/* C++ guaranties for "inline" functions match  comdat requirements. -- Only problem  is
 * that using "inline" also requests that the compiler try to inline the function, which
 * is  something we may not actually want. --  Sadly, there is no attribute to take back
 * the inlining-part of "inline", without also telling the compiler to NEVER inline  the
 * function. */
#if defined(__GNUC__) && 0 /* Using NOINLINE generally degrades performance. -- The compiler already skips inline if functions get too large */
#define __INTERN_COMDAT(sectnam, name)         inline __ATTR_NOINLINE __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
#define __INTERN_COMDAT_SECTION(sectnam, name) inline __ATTR_NOINLINE __ATTR_UNUSED __ATTR_VISIBILITY("hidden") __ATTR_SECTION(sectnam "." name)
#else
#define __INTERN_COMDAT(sectnam, name)         inline __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
#define __INTERN_COMDAT_SECTION(sectnam, name) inline __ATTR_UNUSED __ATTR_VISIBILITY("hidden") __ATTR_SECTION(sectnam "." name)
#endif
#define __INTERN_INLINE(sectnam, name)         inline __ATTR_UNUSED __ATTR_VISIBILITY("hidden")
#define __INTERN_INLINE_SECTION(sectnam, name) inline __ATTR_UNUSED __ATTR_VISIBILITY("hidden") __ATTR_SECTION(sectnam "." name)
#elif defined(__GNUC__) && defined(__OPTIMIZE__) /* `static' only gets guarantied removed in optimized builds... (strange) */
#define __NO_INTERN_COMDAT /* In this fallback case, we don't actually have proper COMDAT functionality... */
#define __INTERN_COMDAT(sectnam, name)         static __ATTR_UNUSED
#define __INTERN_COMDAT_SECTION(sectnam, name) static __ATTR_UNUSED __ATTR_SECTION(sectnam)
#define __INTERN_INLINE(sectnam, name)         __LOCAL
#define __INTERN_INLINE_SECTION(sectnam, name) __LOCAL __ATTR_SECTION(sectnam)
#else /* ... */
#define __NO_INTERN_COMDAT /* In this fallback case, we don't actually have proper COMDAT functionality... */
#define __INTERN_COMDAT(sectnam, name)         __LOCAL
#define __INTERN_COMDAT_SECTION(sectnam, name) __LOCAL __ATTR_SECTION(sectnam)
#define __INTERN_INLINE(sectnam, name)         __LOCAL
#define __INTERN_INLINE_SECTION(sectnam, name) __LOCAL __ATTR_SECTION(sectnam)
#endif /* !... */
#endif /* !__INTERN_COMDAT */



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
#define __COMPILER_SREDIRECT(decl,attr,T,name,asmname)                                                                  decl attr T name;
#define __COMPILER_SREDIRECT2(decl,attr,Tdecl,name,asmname)                                                             decl attr Tdecl;
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
#define __COMPILER_SREDIRECT(decl,attr,T,name,asmname)                                                                  /* nothing */
#define __COMPILER_SREDIRECT2(decl,attr,Tdecl,name,asmname)                                                             /* nothing */
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
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __COMPILER_SREDIRECT(decl,attr,T,name,asmname)                                                                  decl attr T name; decl attr T name __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_SREDIRECT2(decl,attr,Tdecl,name,asmname)                                                             decl attr Tdecl; decl attr Tdecl __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       decl attr Treturn nothrow(cc name) param; decl attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          decl attr void nothrow(cc name) param; decl attr void nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) decl attr Treturn nothrow(cc name) paramf; decl attr Treturn nothrow(cc name) paramf __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmnamef));
#define __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    decl attr void nothrow(cc name) paramf; decl attr void nothrow(cc name) paramf __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmnamef));
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      decl attr Treturn nothrow(cc name) param; decl attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         decl attr void nothrow(cc name) param; decl attr void nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __COMPILER_SREDIRECT(decl,attr,T,name,asmname)                                                                  decl attr T name __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_SREDIRECT2(decl,attr,Tdecl,name,asmname)                                                             decl attr Tdecl __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_REDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       decl attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_REDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          decl attr void nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_VFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) decl attr Treturn nothrow(cc name) paramf __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmnamef));
#define __COMPILER_VFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    decl attr void nothrow(cc name) paramf __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmnamef));
#define __COMPILER_XREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      decl attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_XREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         decl attr void nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#ifdef ____PRIVATE_VREDIRECT_UNPACK
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    decl attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...); decl attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       decl attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...); decl attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __COMPILER_VREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    decl attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#define __COMPILER_VREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       decl attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#endif /* ____PRIVATE_VREDIRECT_UNPACK */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          extern attr Treturn nothrow(cc name) param;
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) extern attr Treturn nothrow(cc name) param; extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param __VA_ARGS__
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...) extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname)); __EXTERN_INLINE attr Treturn nothrow(cc name) param __VA_ARGS__
#endif /* !__NO_EXTERN_INLINE */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          extern attr Treturn nothrow(cc name) param;
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) extern attr Treturn nothrow(cc name) param; extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl...)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl...) extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname)); __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#else /* ... */
#ifdef __NO_EXTERN_INLINE
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          extern attr Treturn nothrow(cc name) param;
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) extern attr Treturn nothrow(cc name) param; extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname));
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#else /* __NO_EXTERN_INLINE */
#define __COMPILER_EIDECLARE(attr,Treturn,nothrow,cc,name,param,inline_impl)          __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#define __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,inline_impl) extern attr Treturn nothrow(cc name) param __COMPILER_ASMNAME(__PP_PRIVATE_STR(asmname)); __EXTERN_INLINE attr Treturn nothrow(cc name) param inline_impl
#endif /* !__NO_EXTERN_INLINE */
#endif /* !... */
#elif defined(__PRAGMA_REDEFINE_EXTNAME)
/* Use _Pragma("redefine_extname " #name " " #asmname). */
#define __COMPILER_SREDIRECT(decl,attr,T,name,asmname)                                                                  __pragma(redefine_extname name asmname) decl attr T name;
#define __COMPILER_SREDIRECT2(decl,attr,Tdecl,name,asmname)                                                             __pragma(redefine_extname name asmname) decl attr Tdecl;
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

#define __NO_COMPILER_SREDIRECT
#define __COMPILER_SREDIRECT(decl,attr,T,name,asmname) \
	decl attr __ATTR_DEPRECATED("symbol '" #name "' could not be redirected to '" #asmname "'") T name;
#define __COMPILER_SREDIRECT2(decl,attr,Tdecl,name,asmname) \
	decl attr __ATTR_DEPRECATED("symbol '" #name "' could not be redirected to '" #asmname "'") Tdecl;

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
#if __has_builtin(__builtin_offsetof) || defined(__GNUC__)
/* Needed,  because some compilers (like GCC) will otherwise
 * claim that `offsetafter()' is a "non-constant" expression
 * (even though it  clearly isn't). So  work around this  by
 * using the native offsetof() builtin, in conjunection with
 * sizeof(), both of which are _required_ to be constant! */
#define __COMPILER_OFFSETAFTER(s, m) (__builtin_offsetof(s, m) + sizeof(((s *)0)->m))
#else /* __has_builtin(__builtin_offsetof) || __GNUC__ */
#define __COMPILER_OFFSETAFTER(s, m) ((__SIZE_TYPE__)(&((s *)0)->m + 1))
#endif /* !__has_builtin(__builtin_offsetof) && !__GNUC__ */
#define __COMPILER_CONTAINER_OF(ptr, type, member) ((type *)((__UINTPTR_TYPE__)(ptr) - __builtin_offsetof(type, member)))
#endif /* !__INTELLISENSE__ */
#endif /* __CC__ */

/************************************************************************/
/* Workarounds for compiler bugs.                                       */
/************************************************************************/
#ifndef __COMPILER_WORKAROUND_GCC_105689
#define __COMPILER_WORKAROUND_GCC_105689(ptr) /* nothing */
#endif /* !__COMPILER_WORKAROUND_GCC_105689 */


#ifdef __KOS_SYSTEM_HEADERS__
#if __has_include(<asm/__stdinc.h>)
#include <asm/__stdinc.h>
#endif /* __has_include(<asm/__stdinc.h>) */
#endif /* __KOS_SYSTEM_HEADERS__ */

#endif /* !___STDINC_H */
