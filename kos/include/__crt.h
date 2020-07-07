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
#ifndef ___CRT_H
#define ___CRT_H 1

#include "__stdinc.h"
#include "hybrid/host.h"

/* Automatically detect the linked CRT
 *   - __CRT_DOS          (windows / msvcrt.dll)
 *   - __CRT_GLC          (linux / glibc.so)
 *   - __CRT_CYG          (windows / cygwin)
 *   - __CRT_KOS          (kos / libc.so)
 *   - __CRT_KOS_KERNEL   (kos / kernel.bin)
 *   - __CRT_GENERIC      (generic / *)
 *   - __CRT_FREESTANDING (freestanding / none)
 */
#if (!defined(__CRT_DOS) && !defined(__CRT_GLC) && \
     !defined(__CRT_KOS) && !defined(__CRT_CYG) && \
     !defined(__CRT_KRS) && !defined(__CRT_KLS) && \
     !defined(__CRT_GENERIC) && !defined(__CRT_KOS_KERNEL) && \
     !defined(__CRT_FREESTANDING))
#if defined(__KOS__) && defined(__KERNEL__)
#   define __CRT_KOS_KERNEL 1
#   define __CRT_KOS_PRIMARY 1
#   define __CRT_KOS 1
/* This might seem like a good idea, but programs using `-ffreestanding',
 * but still ending up #including some CRT header will likely also pass
 * `-lc' on the commandline, so we shouldn't respond to that flag to
 * determine the linked CRT library to be non-present... */
//#elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ + 0) == 0
///* Freestanding CRT environment. */
//#   define __CRT_FREESTANDING 1
#elif defined(__KOS__)
#   define __CRT_KOS 1
#   define __CRT_GLC 1 /* Emulated by KOS */
#   define __CRT_DOS 1 /* Emulated by KOS */
#ifdef __PE__
#   define __CRT_DOS_PRIMARY 1
#else /* __PE__ */
#   define __CRT_KOS_PRIMARY 1
#endif /* !__PE__ */
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
#   define __CRT_CYG_PRIMARY 1
#   define __CRT_CYG 1
#elif defined(__linux__) || defined(__linux) || defined(linux) || \
      defined(__unix__) || defined(__unix) || defined(unix)
#   define __CRT_GLC_PRIMARY 1
#   define __CRT_GLC 1
#elif defined(__WINDOWS__) || defined(_MSC_VER) || \
      defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) || \
      defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
      defined(_WIN32_WCE) || defined(WIN32_WCE)
#   define __CRT_DOS_PRIMARY 1
/* TinyC links against an older version of MSVCRT by default,
 * so we use the old names by default as well. */
#ifdef __TINYC__
#   define __CRT_DOS 1
#else
#   define __CRT_DOS 2
#endif
#else /* ... */
#   define __CRT_GENERIC 1
#endif /* !... */
#endif /* !__CRT_... */




#if defined(__KERNEL__) && defined(__KOS__)
#undef __NO_FPU
#define __NO_FPU 1 /* Disable functions using FPU registers in kernel-mode. */
#endif /* __KERNEL__ && __KOS__ */

#ifdef __CRT_KOS_PRIMARY
#ifndef __BUILDING_LIBC
#ifdef __CRT_KOS_KERNEL
#define __NO_STDSTREAMS 1
#include <crt-features/crt-kos-kernel.h>
#if defined(CONFIG_NO_ASSERT_RESTARTABLE) || defined(CONFIG_NO_DEBUGGER)
#undef __CRT_HAVE___acheck
#undef __CRT_HAVE___acheckf
#endif /* CONFIG_NO_ASSERT_RESTARTABLE || CONFIG_NO_DEBUGGER */
#else /* __CRT_KOS_KERNEL */
#include <crt-features/crt-kos.h>
#endif /* !__CRT_KOS_KERNEL */
#endif /* !__BUILDING_LIBC */
#elif defined(__CRT_CYG_PRIMARY)
#include <crt-features/crt-cyg.h>
#elif defined(__CRT_GLC_PRIMARY)
#include <crt-features/crt-glc.h>
#elif defined(__CRT_DOS_PRIMARY)
#include <crt-features/crt-dos.h>
#elif defined(__CRT_GENERIC)
#include <crt-features/generic.h>
#elif defined(__CRT_FREESTANDING)
#define __NO_STDSTREAMS 1
#endif /* ... */


#define __ATTR_LIBC_PRINTF(a, b)    /* nothing */
#define __ATTR_LIBC_PRINTF_P(a, b)  /* nothing */
#define __ATTR_LIBC_SCANF(a, b)     /* nothing */
#define __ATTR_LIBC_STRFMON(a, b)   /* nothing */
#define __ATTR_LIBC_WPRINTF(a, b)   /* nothing */
#define __ATTR_LIBC_WPRINTF_P(a, b) /* nothing */
#define __ATTR_LIBC_WSCANF(a, b)    /* nothing */

#ifndef __LIBC_MALLOC_ALIGNMENT
#include <hybrid/typecore.h>
#ifdef __ALIGNOF_MAX_ALIGN_T__
#define __LIBC_MALLOC_ALIGNMENT __ALIGNOF_MAX_ALIGN_T__
#else /* __ALIGNOF_MAX_ALIGN_T__ */
#define __LIBC_MALLOC_ALIGNMENT __SIZEOF_POINTER__
#endif /* !__ALIGNOF_MAX_ALIGN_T__ */
#endif /* !__LIBC_MALLOC_ALIGNMENT */

#ifndef __ATTR_MALL_DEFAULT_ALIGNED
#define __ATTR_MALL_DEFAULT_ALIGNED \
	__ATTR_ASSUME_ALIGNED(__LIBC_MALLOC_ALIGNMENT)
#endif /* !__ATTR_MALL_DEFAULT_ALIGNED */

#ifndef __ATTR_MALL_PAGEALIGNED
#include <asm/pagesize.h>
#ifdef __ARCH_PAGESIZE
#define __ATTR_MALL_PAGEALIGNED __ATTR_ASSUME_ALIGNED(__ARCH_PAGESIZE)
#else /* __ARCH_PAGESIZE */
#define __ATTR_MALL_PAGEALIGNED __ATTR_MALL_DEFAULT_ALIGNED
#endif /* !__ARCH_PAGESIZE */
#endif /* !__ATTR_MALL_PAGEALIGNED */

#undef __LIBC_BIND_OPTIMIZATIONS
#if (!defined(__INTELLISENSE__) && \
     (defined(__OPTIMIZE__) || defined(__KERNEL__)))
#define __LIBC_BIND_OPTIMIZATIONS 1
#endif /* ... */


#ifdef __LIBC_BIND_CRTBUILTINS
#if (__LIBC_BIND_CRTBUILTINS + 0) == 0
#undef __LIBC_BIND_CRTBUILTINS
#endif /* !__LIBC_BIND_CRTBUILTINS */
#elif (!defined(__INTELLISENSE__) && !defined(__NO_has_builtin) &&                              \
       /* Don't bind CRT-builtin functions (such as `__builtin_malloc()') when building         \
        * libc itself, so-as to prevent GCC from generating relocations against the             \
        * real symbols (which would end up as relocations in the final binary), when we         \
        * actually want everything to be linked against symbols from the `libc_' namespace. */  \
       !defined(__BUILDING_LIBC) &&                                                             \
       /* Don't bind CRT-builtin functions when linking against the i386 kernel's builtin CRT.  \
        * Because GCC assumes the default calling convention for builtin functions, we'd end up \
        * with stack corruptions since the kernel uses STDCALL, but gcc invokes as CDECL. */    \
       !(defined(__CRT_KOS_KERNEL) && (defined(__i386__) && !defined(__x86_64__))))
#define __LIBC_BIND_CRTBUILTINS 1
#endif


/* Automatic namespacing for fast (platform/arch-specific) optimized implementations of functions. */
#ifdef __cplusplus
#define __NAMESPACE_FAST_BEGIN               namespace __optimized_imp {
#define __NAMESPACE_FAST_END                 }
#define __NAMESPACE_FAST_SYM                 ::__optimized_imp::
#define __NAMESPACE_FAST_USING(x)            using ::__optimized_imp::x;
#define __NAMESPACE_FAST_USING_OR_IMPL(x, i) using ::__optimized_imp::x;
#define __LIBC_FAST_NAME(x)                  x
#else /* __cplusplus */
#define __NAMESPACE_FAST_BEGIN               /* nothing */
#define __NAMESPACE_FAST_END                 /* nothing */
#define __NAMESPACE_FAST_SYM                 /* nothing */
#define __NAMESPACE_FAST_USING(x)            /* nothing */
#define __NAMESPACE_FAST_USING_OR_IMPL(x, i) i
#define __LIBC_FAST_NAME(x)                  __optimized_##x
#endif /* !__cplusplus */

/* Automatic namespacing for header-local implementations of functions. */
#ifdef __cplusplus
#define __NAMESPACE_LOCAL_BEGIN               namespace __local_imp {
#define __NAMESPACE_LOCAL_END                 }
#define __NAMESPACE_LOCAL_SYM                 ::__local_imp::
#define __NAMESPACE_LOCAL_USING(x)            using ::__local_imp::x;
#define __NAMESPACE_LOCAL_USING_OR_IMPL(x, i) using ::__local_imp::x;
#define __LIBC_LOCAL_NAME(x)                  x
#else /* __cplusplus */
#define __NAMESPACE_LOCAL_BEGIN               /* nothing */
#define __NAMESPACE_LOCAL_END                 /* nothing */
#define __NAMESPACE_LOCAL_SYM                 /* nothing */
#define __NAMESPACE_LOCAL_USING(x)            /* nothing */
#define __NAMESPACE_LOCAL_USING_OR_IMPL(x, i) i
#define __LIBC_LOCAL_NAME(x)                  __local_##x
#endif /* !__cplusplus */

#ifndef __FCALL
#if defined(__x86_64__)
#define __FCALL __ATTR_SYSVABI
#elif defined(__i386__)
#define __FCALL __ATTR_FASTCALL
#else /* ... */
#define __FCALL /* nothing */
#endif /* !... */
#endif /* !__FCALL */

#ifndef __KCALL
#ifdef __x86_64__
#define __KCALL __ATTR_SYSVABI
#elif defined(__i386__)
#define __KCALL __ATTR_STDCALL
#else /* ... */
#define __KCALL /* nothing */
#endif /* !... */
#endif /* !__KCALL */

/*
 * Same-cc test macros:
 *   - __LIBCCALL_IS_LIBKCALL    C == K
 *   - __LIBCCALL_IS_LIBDCALL    C == D
 *   - __LIBDCALL_IS_LIBKCALL    K == D
 *
 *   - __VLIBCCALL_IS_VLIBKCALL  VC == VK
 *   - __VLIBCCALL_IS_VLIBDCALL  VC == VD
 *   - __VLIBDCALL_IS_VLIBKCALL  VK == VD
 *
 *   - __VLIBCCALL_IS_LIBCCALL   VC == C
 *   - __VLIBDCALL_IS_LIBDCALL   VD == D
 *   - __VLIBKCALL_IS_LIBKCALL   VK == K
 *
 * cc-behavior test macros:
 *   - *_CALLER_CLEANUP:
 *     The caller of a function is responsible to clean up the argument list.
 *     When defined, this allows functions to be called with more arguments
 *     that they actually take
 *       - __LIBCCALL_CALLER_CLEANUP
 *       - __LIBKCALL_CALLER_CLEANUP
 *       - __LIBDCALL_CALLER_CLEANUP
 */
#ifdef __x86_64__
#   define __LIBKCALL  __ATTR_SYSVABI
#   define __VLIBKCALL __ATTR_SYSVABI
#   define __LIBDCALL  __ATTR_MSABI
#   define __VLIBDCALL __ATTR_MSABI
#   define __LIBCCALL_CALLER_CLEANUP 1
#   define __LIBKCALL_CALLER_CLEANUP 1
#   define __LIBDCALL_CALLER_CLEANUP 1
#   define __VLIBCCALL_IS_LIBCCALL 1
#   define __VLIBDCALL_IS_LIBDCALL 1
#   define __VLIBKCALL_IS_LIBKCALL 1
#ifdef __PE__
#   define __LIBCCALL_IS_LIBDCALL 1
#   define __LIBCCALL  __LIBDCALL
#   define __VLIBCCALL_IS_VLIBDCALL 1
#   define __VLIBCCALL  __VLIBDCALL
#else /* __PE__ */
#   define __LIBCCALL_IS_LIBKCALL 1
#   define __LIBCCALL  __LIBKCALL
#   define __VLIBCCALL_IS_VLIBKCALL 1
#   define __VLIBCCALL  __VLIBKCALL
#endif /* !__PE__ */
#elif defined(__i386__)
#ifdef __CRT_KOS_KERNEL
#   define __LIBCCALL  __KCALL
#   define __LIBKCALL  __KCALL
#   define __LIBDCALL  __KCALL
#else /* __CRT_KOS_KERNEL */
#   define __LIBCCALL  __ATTR_CDECL
#   define __LIBKCALL  __ATTR_CDECL
#   define __LIBDCALL  __ATTR_CDECL
#   define __VLIBCCALL_IS_LIBCCALL  1
#   define __VLIBKCALL_IS_LIBKCALL  1
#   define __VLIBDCALL_IS_LIBDCALL  1
#   define __LIBCCALL_CALLER_CLEANUP  1
#   define __LIBKCALL_CALLER_CLEANUP  1
#   define __LIBDCALL_CALLER_CLEANUP  1
#endif /* !__CRT_KOS_KERNEL */
#   define __LIBCCALL_IS_LIBKCALL 1
#   define __LIBCCALL_IS_LIBDCALL 1
#   define __LIBDCALL_IS_LIBKCALL 1
#   define __VLIBCCALL __ATTR_CDECL
#   define __VLIBKCALL __ATTR_CDECL
#   define __VLIBDCALL __ATTR_CDECL
#   define __VLIBCCALL_IS_VLIBKCALL 1
#   define __VLIBCCALL_IS_VLIBDCALL 1
#   define __VLIBDCALL_IS_VLIBKCALL 1
#else /* Arch... */
#if defined(__arm__)
#   define __LIBCCALL_CALLER_CLEANUP 1
#   define __LIBKCALL_CALLER_CLEANUP 1
#   define __LIBDCALL_CALLER_CLEANUP 1
#endif /* __arm__ */
#   define __LIBCCALL  /* Nothing */
#   define __LIBDCALL  /* Nothing */
#   define __LIBKCALL  /* Nothing */
#   define __VLIBCCALL /* Nothing */
#   define __VLIBDCALL /* Nothing */
#   define __VLIBKCALL /* Nothing */
#   define __LIBCCALL_IS_LIBKCALL   1
#   define __LIBCCALL_IS_LIBDCALL   1
#   define __LIBDCALL_IS_LIBKCALL   1
#   define __VLIBCCALL_IS_VLIBKCALL 1
#   define __VLIBCCALL_IS_VLIBDCALL 1
#   define __VLIBDCALL_IS_VLIBKCALL 1
#   define __VLIBCCALL_IS_LIBCCALL  1
#   define __VLIBDCALL_IS_LIBDCALL  1
#   define __VLIBKCALL_IS_LIBKCALL  1
#endif /* !Arch... */




#ifndef __LIBC
#if defined(__KOS__) && defined(__KERNEL__)
#define __LIBC __PUBDEF
#else /* __KOS__ && __KERNEL__ */
#define __LIBC __IMPDEF
#endif /* !__KOS__ || !__KERNEL__ */
#endif /* !__LIBC */



/* Define a missing libc function inline within a header.
 *  - To prevent unnecessary dependencies, or binaries inflated with
 *    unused functions, define everything as inline (if supported by
 *    the compiler)
 *  - While we don't actually wish the function to be expanded inline,
 *    what we do want is to have them disappear when they're not being
 *    used, which is a secondary effect of inline declarations, and one
 *    that I do not know how to reproduce without also instructing the
 *    compiler to try and inline the function.
 *  - If the compiler doesn't support inlining, try to link the function
 *    such that it will only appear once in the resulting binary, while
 *    also making it as easy as possible for the linker to get rid of
 *    the function.
 *  - If none of these options are possible, fall-back to defining the
 *    functions as C-standard, portable `static' (PRIVATE) definitions. */
#ifndef __LOCAL_LIBC
#if !defined(__NO_ATTR_INLINE) && 1
#define __LOCAL_LIBC(name) __LOCAL
#elif !defined(__NO_ATTR_SELECTANY)
#define __LOCAL_LIBC(name) __INTERN __ATTR_SELECTANY __ATTR_UNUSED
#elif !defined(__NO_ATTR_WEAK)
#define __LOCAL_LIBC(name) __INTERN __ATTR_WEAK __ATTR_UNUSED
#else /* ... */
#define __LOCAL_LIBC(name) __PRIVATE __ATTR_UNUSED
#endif /* !... */
#endif /* !__LOCAL_LIBC */

#ifndef __NO_ATTR_SECTION
#define __LOCAL_LIBC_DATA_SECTION(name)       __ATTR_SECTION(".data.local." #name)
#define __LOCAL_LIBC_CONST_DATA_SECTION(name) __ATTR_SECTION(".rodata.local." #name)
#else /* !__NO_ATTR_SECTION */
#define __LOCAL_LIBC_DATA_SECTION(name)       /* nothing */
#define __LOCAL_LIBC_CONST_DATA_SECTION(name) /* nothing */
#endif /* __NO_ATTR_SECTION */

#ifndef __LOCAL_LIBC_DATA
#if !defined(__NO_ATTR_SELECTANY) && 1
#define __LOCAL_LIBC_DATA(name) __INTERN __ATTR_SELECTANY __ATTR_UNUSED __LOCAL_LIBC_DATA_SECTION(name)
#elif !defined(__NO_ATTR_WEAK) && 1
#define __LOCAL_LIBC_DATA(name) __INTERN __ATTR_WEAK __ATTR_UNUSED __LOCAL_LIBC_DATA_SECTION(name)
#else /* ... */
#define __LOCAL_LIBC_DATA(name) __PRIVATE __ATTR_UNUSED __LOCAL_LIBC_DATA_SECTION(name)
#endif /* !... */
#endif /* !__LOCAL_LIBC_DATA */

#ifndef __LOCAL_LIBC_CONST_DATA
#ifdef __cplusplus
#if !defined(__NO_ATTR_SELECTANY) && 1
#define __LOCAL_LIBC_CONST_DATA(name) extern __ATTR_SELECTANY __ATTR_UNUSED __LOCAL_LIBC_CONST_DATA_SECTION(name)
#elif !defined(__NO_ATTR_WEAK) && 1
#define __LOCAL_LIBC_CONST_DATA(name) extern __INTERN __ATTR_WEAK __ATTR_UNUSED __LOCAL_LIBC_CONST_DATA_SECTION(name)
#else /* ... */
#define __LOCAL_LIBC_CONST_DATA(name) __PRIVATE __ATTR_UNUSED __LOCAL_LIBC_CONST_DATA_SECTION(name)
#endif /* !... */
#else /* __cplusplus */
#define __LOCAL_LIBC_CONST_DATA       __LOCAL_LIBC_DATA
#endif /* !__cplusplus */
#endif /* !__LOCAL_LIBC_CONST_DATA */

#ifdef __CC__
#ifndef __FILE
#define __FILE struct __NAMESPACE_STD_SYM __IO_FILE
__NAMESPACE_STD_BEGIN
struct __IO_FILE;
__NAMESPACE_STD_END
#endif /* !__FILE */
#ifndef __LOCALE_T
typedef void *__locale_t;
#endif /* !__LOCALE_T */
#endif /* ... */


#ifndef __CC__
#define __CASMNAME(x)                                                                                   /* nothing */
#define __CASMNAME_DOS(x)                                                                               /* nothing */
#define __CASMNAME_KOS(x)                                                                               /* nothing */
#define __CASMNAME_SAME(x)                                                                              /* nothing */
#define __CASMNAME_SAME_DOS(x)                                                                          /* nothing */
#define __CASMNAME_SAME_KOS(x)                                                                          /* nothing */
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                /* nothing */
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   /* nothing */
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       /* nothing */
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   /* nothing */
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   /* nothing */
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          /* nothing */
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      /* nothing */
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      /* nothing */
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    /* nothing */
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) /* nothing */
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) /* nothing */
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       /* nothing */
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   /* nothing */
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   /* nothing */
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    /* nothing */
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      /* nothing */
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  /* nothing */
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  /* nothing */
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         /* nothing */
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     /* nothing */
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     /* nothing */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)                                               /* nothing */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)                                           /* nothing */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)                                           /* nothing */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)                                      /* nothing */
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...)                                  /* nothing */
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...)                                  /* nothing */
#elif defined(__BUILDING_LIBC) && defined(__KOS__)
#define __CASMNAME(x)                                                                                   __ASMNAME("libc_" x)
#define __CASMNAME_DOS(x)                                                                               __ASMNAME("libd_" x)
#define __CASMNAME_KOS(x)                                                                               __ASMNAME("libc_" x)
#define __CASMNAME_SAME(x)                                                                              __ASMNAME("libc_" x)
#define __CASMNAME_SAME_DOS(x)                                                                          __ASMNAME("libd_" x)
#define __CASMNAME_SAME_KOS(x)                                                                          __ASMNAME("libc_" x)
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #name);
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   __INTDEF attr void nothrow(__LIBCCALL name) param __ASMNAME("libc_" #name);
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __INTDEF attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("libc_" #asmname);
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          __INTDEF attr void nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __INTDEF attr void nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      __INTDEF attr void nothrow(__LIBKCALL name) param __ASMNAME("libc_" #asmname);
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    __INTDEF attr Treturn nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libc_" #asmname);
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __INTDEF attr Treturn nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libd_" #asmname);
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __INTDEF attr Treturn nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libc_" #asmname);
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       __INTDEF attr void nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libc_" #asmname);
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __INTDEF attr void nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libd_" #asmname);
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __INTDEF attr void nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libc_" #asmname);
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBCCALL name) paramf __ASMNAME("libc_" #asmnamef);
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBDCALL name) paramf __ASMNAME("libd_" #asmnamef);
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBKCALL name) paramf __ASMNAME("libc_" #asmnamef);
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __INTDEF attr void nothrow(__VLIBCCALL name) paramf __ASMNAME("libc_" #asmnamef);
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr void nothrow(__VLIBDCALL name) paramf __ASMNAME("libd_" #asmnamef);
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr void nothrow(__VLIBKCALL name) paramf __ASMNAME("libc_" #asmnamef);
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __INTDEF attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("libc_" #asmname);
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         __INTDEF attr void nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __INTDEF attr void nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     __INTDEF attr void nothrow(__LIBKCALL name) param __ASMNAME("libc_" #asmname);
#ifdef __NO_EXTERN_INLINE
#ifdef __NO_INLINE__
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #name);
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #name);
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("libc_" #name);
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("libc_" #asmname);
#else /* __NO_INLINE__ */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#endif /* !__NO_INLINE__ */
#else /* __NO_EXTERN_INLINE */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #name); __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #name); __EXTERN_INLINE attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("libc_" #name); __EXTERN_INLINE attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("libc_" #asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#endif /* !__NO_EXTERN_INLINE */
#else /* __BUILDING_LIBC... */
#define __CASMNAME                                                                                      __ASMNAME
#define __CASMNAME_SAME(x)                                                                              /* nothing */
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   __LIBC attr void nothrow(__LIBCCALL name) param;
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       __REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBCCALL,name,param,asmname,args)
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          __REDIRECT_VOID(__LIBC,attr,nothrow,__LIBCCALL,name,param,asmname,args)
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    __VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBCCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       __VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBCCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBCCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBCCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      __XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBCCALL,name,param,asmname,code)
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         __XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBCCALL,name,param,asmname,code)
#ifdef __PE__
#define __CASMNAME_DOS                                                                                  __ASMNAME
#define __CASMNAME_KOS(x)                                                                               __ASMNAME("KOS$" x)
#define __CASMNAME_SAME_DOS(x)                                                                          /* nothing */
#define __CASMNAME_SAME_KOS(x)                                                                          __ASMNAME("KOS$" x)
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,args)
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,KOS$##asmname,args)
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __REDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,args)
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      __REDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,KOS$##asmname,args)
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,KOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,KOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBDCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBKCALL,name,paramf,KOS$##asmnamef,vparamf,KOS$##vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBDCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBKCALL,name,paramf,KOS$##asmnamef,vparamf,KOS$##vasmnamef,args,before_va_start)
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,code)
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,KOS$##asmname,code)
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,code)
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     __XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,KOS$##asmname,code)
#else /* __PE__ */
#define __CASMNAME_DOS(x)                                                                               __ASMNAME("DOS$" x)
#define __CASMNAME_KOS                                                                                  __ASMNAME
#define __CASMNAME_SAME_DOS(x)                                                                          __ASMNAME("DOS$" x)
#define __CASMNAME_SAME_KOS(x)                                                                          /* nothing */
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,args)
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,asmname,args)
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __REDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,args)
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      __REDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,asmname,args)
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBDCALL,name,paramf,DOS$##asmnamef,vparamf,DOS$##vasmnamef,args,before_va_start)
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBKCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBDCALL,name,paramf,DOS$##asmnamef,vparamf,DOS$##vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBKCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,code)
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,asmname,code)
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,code)
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     __XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,asmname,code)
#endif /* !__PE__ */
#ifdef __NO_EXTERN_INLINE
#ifdef __NO_INLINE__
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#ifdef __NO_ASMNAME
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#else /* __NO_ASMNAME */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __LIBC attr Treturn nothrow(__LIBCCALL name) param __ASMNAME(#asmname);
#endif /* !__NO_ASMNAME */
#else /* __NO_INLINE__ */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#endif /* !__NO_INLINE__ */
#ifdef __PE__
#ifdef __NO_INLINE__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param;
#ifdef __NO_ASMNAME
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#else /* __NO_ASMNAME */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("KOS$" #name);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __ASMNAME(#asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("KOS$" #asmname);
#endif /* !__NO_ASMNAME */
#else /* __NO_INLINE__ */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#endif /* !__NO_INLINE__ */
#else /* __PE__ */
#ifdef __NO_INLINE__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param;
#ifdef __NO_ASMNAME
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#else /* __NO_ASMNAME */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("DOS$" #name);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __ASMNAME(#asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("DOS$" #asmname);
#endif /* !__NO_ASMNAME */
#else /* __NO_INLINE__ */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#endif /* !__NO_INLINE__ */
#endif /* !__PE__ */
#else /* __NO_EXTERN_INLINE */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __LIBC attr Treturn nothrow(__LIBCCALL name) param; __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __LIBC attr Treturn nothrow(__LIBCCALL name) param __ASMNAME(#asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#ifdef __PE__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param; __EXTERN_INLINE attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("KOS$" #name); __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __ASMNAME(#asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __ASMNAME("KOS$" #asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#else /* __PE__ */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("DOS$" #name); __EXTERN_INLINE attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param; __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("DOS$" #asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __ASMNAME(#asmname); __EXTERN_INLINE attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#endif /* !__PE__ */
#endif /* !__NO_EXTERN_INLINE */
#endif /* !__BUILDING_LIBC... */

#define __PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_ ,
#define __PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_1 ,
#define __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG(x) __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG_IMPL x
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED3(...) __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED2(x) __PRIVATE_CDECLARE_OPT_IS_DEFINED3(__PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_##x)
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED(x) __PRIVATE_CDECLARE_OPT_IS_DEFINED2(x)

#define __PRIVATE_CDECLARE_OPT_0(attr,Treturn,nothrow,name,param,args)
#define __PRIVATE_CDECLARE_VOID_OPT_0(attr,nothrow,name,param,args)
#define __PRIVATE_CDECLARE_OPT_1         __CDECLARE
#define __PRIVATE_CDECLARE_VOID_OPT_1    __CDECLARE_VOID
#define __PRIVATE_CDECLARE_OPT2(is)      __PRIVATE_CDECLARE_OPT_##is
#define __PRIVATE_CDECLARE_VOID_OPT2(is) __PRIVATE_CDECLARE_VOID_OPT_##is
#define __PRIVATE_CDECLARE_OPT(is)       __PRIVATE_CDECLARE_OPT2(is)
#define __PRIVATE_CDECLARE_VOID_OPT(is)  __PRIVATE_CDECLARE_VOID_OPT2(is)

/* Same as the _OPT-less counterpart, only these macros
 * integrate the test for `defined(__CRT_HAVE_<name>)',
 * meaning that the caller won't have to do that check. */
#define __CDECLARE_OPT(attr,Treturn,nothrow,name,param,args) \
	__PRIVATE_CDECLARE_OPT(__PRIVATE_CDECLARE_OPT_IS_DEFINED(__CRT_HAVE_##name))(attr,Treturn,nothrow,name,param,args)
#define __CDECLARE_VOID_OPT(attr,nothrow,name,param,args) \
	__PRIVATE_CDECLARE_VOID_OPT(__PRIVATE_CDECLARE_OPT_IS_DEFINED(__CRT_HAVE_##name))(attr,nothrow,name,param,args)


/* Special value used to indicate the *at functions should use the current working directory. */
#ifndef __CRT_AT_FDCWD
#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __CRT_AT_FDCWD   (-100)
#elif defined(__CRT_CYG)
#define __CRT_AT_FDCWD   (-2)
#endif /* ... */
#endif /* !__CRT_AT_FDCWD */


#ifdef __CC__
/* Figure out where unreachable code locations are originating from.
 * Without this, GCC (rightfully) likes to make use of undefined behavior
 * when it comes to unreachable locations in order better optimize code.
 * However, this makes debugging much harder than it needs to be, so to
 * make our lives a bit easier, provide a functions that gets called in these
 * situations, with the equivalent effect of `abort()' and `std::terminate()' */
#if !defined(NDEBUG) && defined(__CRT_HAVE___crt_unreachable)
__DECL_BEGIN
__CDECLARE_VOID(__ATTR_NORETURN,,__crt_unreachable,(void),())
__DECL_END
#undef __builtin_unreachable
#if __has_builtin(__builtin_unreachable)
#define __builtin_unreachable() (__crt_unreachable(), __builtin_unreachable())
#else /* __has_builtin(__builtin_unreachable) */
#define __builtin_unreachable() __crt_unreachable()
#endif /* !__has_builtin(__builtin_unreachable) */
#endif /* __BUILDING_LIBC || __CRT_HAVE___crt_unreachable */
#endif /* __CC__ */

/* Include __stub_XXX definitions (checked by configure scripts) */
#ifdef __CRT_KOS
#include <gnu/stubs.h>
#endif /* __CRT_KOS */

/* Configure SSP *_chk bindings
 * NOTE: SSP requires compiler support in the form of `__builtin_object_size()'
 *       If this builtin isn't available, SSP is disabled in headers! */
#ifdef __SSP_FORTIFY_LEVEL
#if (__SSP_FORTIFY_LEVEL + 0) > 0
#if !__has_builtin(__builtin_object_size)
#ifdef __PREPROCESSOR_HAVE_WARNING
#warning "__SSP_FORTIFY_LEVEL enabled, but `__builtin_object_size()' not supported"
#endif /* __PREPROCESSOR_HAVE_WARNING */
#undef __SSP_FORTIFY_LEVEL
#endif /* !__has_builtin(__builtin_object_size) */
#else /* __SSP_FORTIFY_LEVEL > 0 */
#undef __SSP_FORTIFY_LEVEL
#endif /* __SSP_FORTIFY_LEVEL <= 0 */
#endif /* __SSP_FORTIFY_LEVEL */

#endif /* !___CRT_H */
