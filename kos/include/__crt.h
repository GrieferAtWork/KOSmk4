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
 *   - __CRT_MIS          (generic / *)
 *   - __CRT_FREESTANDING (freestanding / none)
 */
#if (!defined(__CRT_DOS) && !defined(__CRT_GLC) && \
     !defined(__CRT_KOS) && !defined(__CRT_CYG) && \
     !defined(__CRT_KRS) && !defined(__CRT_KLS) && \
     !defined(__CRT_MIS) && !defined(__CRT_KOS_KERNEL) && \
     !defined(__CRT_FREESTANDING))
#if defined(__KOS__) && defined(__KERNEL__)
#   define __CRT_KOS_KERNEL 1
#   define __CRT_KOS 1
#   define __NO_STDSTREAMS 1
/* This might seem like a good idea, but programs using `-ffreestanding',
 * but still ending up #including some CRT header will likely also pass
 * `-lc' on the commandline, so we shouldn't respond to that flag to
 * determine the linked CRT library to be non-present... */
//#elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ + 0) == 0
///* Freestanding CRT environment. */
//#   define __CRT_FREESTANDING 1
#elif defined(__KOS__)
#   define __CRT_KOS_NATIVE 1
#   define __CRT_KOS 1
#   define __CRT_GLC 1 /* Emulated by KOS */
#   define __CRT_DOS 1 /* Emulated by KOS */
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
#   define __CRT_CYG_NATIVE 1
#   define __CRT_CYG 1
#elif defined(__linux__) || defined(__linux) || defined(linux) || \
      defined(__unix__) || defined(__unix) || defined(unix)
#   define __CRT_GLC_NATIVE 1
#   define __CRT_GLC 1
#elif defined(__WINDOWS__) || defined(_MSC_VER) || \
      defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) || \
      defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
      defined(_WIN32_WCE) || defined(WIN32_WCE)
#   define __CRT_DOS_NATIVE 1
/* TinyC links against an older version of MSVCRT by default,
 * so we use the old names by default as well. */
#ifdef __TINYC__
#   define __CRT_DOS 1
#else
#   define __CRT_DOS 2
#endif
#else
#   define __CRT_MIS 1
#endif
#endif /* !__CRT_... */

#undef __CRT_GENERIC
#if defined(__CRT_FREESTANDING)
#undef __NO_STDSTREAMS
#define __NO_STDSTREAMS 1
#undef __CRT_CYG_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_CYG_PRIMARY
#undef __CRT_GLC_PRIMARY
#undef __CRT_DOS_PRIMARY
#undef __CRT_KOS_PRIMARY
#elif defined(__CRT_KOS_NATIVE) || defined(__CRT_KOS_KERNEL)
#undef __CRT_CYG_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_CYG_PRIMARY
#undef __CRT_GLC_PRIMARY
#undef __CRT_DOS_PRIMARY
#undef __CRT_KOS_PRIMARY
#ifdef __PE__
/* KOS's libc emulates DOS in PE-mode */
#define __CRT_DOS_PRIMARY 1
#else /* __PE__ */
#define __CRT_KOS_PRIMARY 1
#endif /* !__PE__ */
#elif defined(__CRT_CYG_NATIVE)
#undef __CRT_KOS_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_KOS_PRIMARY
#undef __CRT_GLC_PRIMARY
#undef __CRT_DOS_PRIMARY
#define __CRT_CYG_PRIMARY 1
#elif defined(__CRT_GLC_NATIVE)
#undef __CRT_KOS_NATIVE
#undef __CRT_CYG_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_KOS_PRIMARY
#undef __CRT_CYG_PRIMARY
#undef __CRT_DOS_PRIMARY
#define __CRT_GLC_PRIMARY 1
#elif defined(__CRT_DOS_NATIVE)
#undef __CRT_KOS_NATIVE
#undef __CRT_CYG_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_KOS_PRIMARY
#undef __CRT_CYG_PRIMARY
#undef __CRT_GLC_PRIMARY
#define __CRT_DOS_PRIMARY 1
#elif defined(__CRT_KOS)
#undef __CRT_CYG_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_CYG_PRIMARY
#undef __CRT_GLC_PRIMARY
#undef __CRT_DOS_PRIMARY
#define __CRT_KOS_PRIMARY 1
#elif defined(__CRT_CYG)
#undef __CRT_KOS_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_KOS_PRIMARY
#undef __CRT_GLC_PRIMARY
#undef __CRT_DOS_PRIMARY
#define __CRT_CYG_PRIMARY 1
#elif defined(__CRT_GLC)
#undef __CRT_KOS_NATIVE
#undef __CRT_CYG_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_KOS_PRIMARY
#undef __CRT_CYG_PRIMARY
#undef __CRT_DOS_PRIMARY
#define __CRT_GLC_PRIMARY 1
#elif defined(__CRT_DOS)
#undef __CRT_KOS_NATIVE
#undef __CRT_CYG_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_KOS_PRIMARY
#undef __CRT_CYG_PRIMARY
#undef __CRT_GLC_PRIMARY
#define __CRT_DOS_PRIMARY 1
#else
#undef __CRT_KOS_NATIVE
#undef __CRT_CYG_NATIVE
#undef __CRT_GLC_NATIVE
#undef __CRT_DOS_NATIVE
#undef __CRT_KOS_PRIMARY
#undef __CRT_CYG_PRIMARY
#undef __CRT_GLC_PRIMARY
#undef __CRT_DOS_PRIMARY
#define __CRT_GENERIC 1
#endif


#if defined(__KERNEL__) && defined(__KOS__)
#undef __NO_FPU
#define __NO_FPU 1 /* Disable functions using FPU registers in kernel-mode. */
#endif /* __KERNEL__ && __KOS__ */

#ifdef __CRT_KOS_PRIMARY
#ifdef __CRT_KOS_KERNEL
#include <crt-features/crt-kos-kernel.h>
#if defined(CONFIG_NO_ASSERT_RESTARTABLE) || defined(CONFIG_NO_DEBUGGER)
#undef __CRT_HAVE___acheck
#undef __CRT_HAVE___acheckf
#endif
#elif defined(__BUILDING_LIBC)
#include <crt-features/all.h>
#include <crt-features/crt-kos-syscalls.h>
#else
#include <crt-features/crt-kos.h>
#endif
#elif defined(__CRT_CYG_PRIMARY)
#include <crt-features/crt-cyg.h>
#elif defined(__CRT_GLC_PRIMARY)
#include <crt-features/crt-glc.h>
#elif defined(__CRT_DOS_PRIMARY)
#include <crt-features/crt-dos.h>
#elif defined(__CRT_GENERIC)
#include <crt-features/generic.h>
#endif


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
#if !defined(__INTELLISENSE__) && \
    (defined(__OPTIMIZE__) || defined(__KERNEL__))
#define __LIBC_BIND_OPTIMIZATIONS 1
#endif


#undef __LIBC_BIND_CRTBUILTINS
#if !defined(__INTELLISENSE__) && \
    !defined(__NO_has_builtin) && \
    /* Don't bind CRT-builtin functions (such as `__builtin_malloc()') when building \
     * libc itself, so-as to prevent GCC from generating relocations against the \
     * real symbols (which would end up as relocations in the final binary), when we \
     * actually want everything to be linked against symbols from the `libc_' namespace. */ \
    !defined(__BUILDING_LIBC) && \
    /* Don't bind CRT-builtin functions when linking against the i386 kernel's builtin CRT. \
     * Because GCC assumes the default calling convention for builtin functions, we'd end up \
     * with stack corruptions since the kernel uses STDCALL, but gcc invokes as CDECL. */ \
    !(defined(__CRT_KOS_KERNEL) && (defined(__i386__) && !defined(__x86_64__)))
#define __LIBC_BIND_CRTBUILTINS 1
#endif


/* Automatic namespacing for fast (platform/arch-specific) optimized implementations of functions. */
#ifdef __cplusplus
#define __NAMESPACE_FAST_BEGIN              namespace __optimized_imp {
#define __NAMESPACE_FAST_END                }
#define __NAMESPACE_FAST_SYM                ::__optimized_imp::
#define __NAMESPACE_FAST_USING(x)           using ::__optimized_imp::x;
#define __NAMESPACE_FAST_USING_OR_IMPL(x,i) using ::__optimized_imp::x;
#define __LIBC_FAST_NAME(x)                 x
#else /* __cplusplus */
#define __NAMESPACE_FAST_BEGIN              /* nothing */
#define __NAMESPACE_FAST_END                /* nothing */
#define __NAMESPACE_FAST_SYM                /* nothing */
#define __NAMESPACE_FAST_USING(x)           /* nothing */
#define __NAMESPACE_FAST_USING_OR_IMPL(x,i) i
#define __LIBC_FAST_NAME(x)                 __FAST_##x
#endif /* !__cplusplus */

/* Automatic namespacing for header-local implementations of functions. */
#ifdef __cplusplus
#define __NAMESPACE_LOCAL_BEGIN              namespace __local_imp {
#define __NAMESPACE_LOCAL_END                }
#define __NAMESPACE_LOCAL_SYM                ::__local_imp::
#define __NAMESPACE_LOCAL_USING(x)           using ::__local_imp::x;
#define __NAMESPACE_LOCAL_USING_OR_IMPL(x,i) using ::__local_imp::x;
#define __LIBC_LOCAL_NAME(x)                 x
#else /* __cplusplus */
#define __NAMESPACE_LOCAL_BEGIN              /* nothing */
#define __NAMESPACE_LOCAL_END                /* nothing */
#define __NAMESPACE_LOCAL_SYM                /* nothing */
#define __NAMESPACE_LOCAL_USING(x)           /* nothing */
#define __NAMESPACE_LOCAL_USING_OR_IMPL(x,i) i
#define __LIBC_LOCAL_NAME(x)                 __LOCAL_##x
#endif /* !__cplusplus */

#ifndef __FCALL
#if defined(__x86_64__)
#define __FCALL __ATTR_SYSVABI
#elif defined(__i386__)
#define __FCALL __ATTR_FASTCALL
#else
#define __FCALL /* nothing */
#endif
#endif /* !__FCALL */

#ifndef __KCALL
#ifdef __x86_64__
#define __KCALL __ATTR_SYSVABI
#elif defined(__i386__)
#define __KCALL __ATTR_STDCALL
#else
#define __KCALL /* nothing */
#endif
#endif /* !__KCALL */

#ifndef __LIBCCALL
#undef __LIBCCALL_CALLER_CLEANUP
#undef __VLIBCCALL_CALLER_CLEANUP
#ifdef __x86_64__
#ifdef __CRT_KOS_PRIMARY
#   define __LIBCCALL  __ATTR_SYSVABI
#   define __LIBDCALL  __ATTR_MSABI
#   define __VLIBCCALL __ATTR_SYSVABI
#   define __VLIBDCALL __ATTR_MSABI
#   define __LIBDCALL_DIFFERS_FROM_LIBCCALL 1
#   define __VLIBDCALL_DIFFERS_FROM_VLIBCCALL 1
#elif defined(__CRT_DOS_PRIMARY) || defined(__CRT_CYG_PRIMARY)
#   define __LIBCCALL  __ATTR_MSABI
#   define __LIBDCALL  __ATTR_MSABI
#   define __VLIBCCALL __ATTR_MSABI
#   define __VLIBDCALL __ATTR_MSABI
#else
#   define __LIBCCALL  __ATTR_SYSVABI
#   define __LIBDCALL  __ATTR_SYSVABI
#   define __VLIBCCALL __ATTR_SYSVABI
#   define __VLIBDCALL __ATTR_SYSVABI
#endif
#   define __LIBCCALL_CALLER_CLEANUP  1
#   define __LIBDCALL_CALLER_CLEANUP  1
#   define __VLIBCCALL_CALLER_CLEANUP 1
#   define __VLIBDCALL_CALLER_CLEANUP 1
#elif defined(__i386__)
#ifdef __CRT_KOS_KERNEL
#   define __LIBCCALL  __KCALL /* STDCALL */
#   define __LIBDCALL  __KCALL /* STDCALL */
#else /* __CRT_KOS_KERNEL */
#   define __LIBCCALL_CALLER_CLEANUP  1
#   define __LIBCCALL  __ATTR_CDECL
#   define __LIBDCALL_CALLER_CLEANUP  1
#   define __LIBDCALL  __ATTR_CDECL
#endif /* !__CRT_KOS_KERNEL */
#   define __VLIBCCALL __ATTR_CDECL
#   define __VLIBCCALL_CALLER_CLEANUP 1
#   define __VLIBDCALL __ATTR_CDECL
#   define __VLIBDCALL_CALLER_CLEANUP 1
#elif defined(__arm__)
#   define __LIBCCALL  /* Nothing */
#   define __LIBDCALL  /* Nothing */
#   define __VLIBCCALL /* Nothing */
#   define __VLIBDCALL /* Nothing */
#   define __LIBCCALL_CALLER_CLEANUP  1
#   define __LIBDCALL_CALLER_CLEANUP  1
#   define __VLIBCCALL_CALLER_CLEANUP 1
#   define __VLIBDCALL_CALLER_CLEANUP 1
#else
#   define __LIBCCALL  /* Nothing */
#   define __LIBDCALL  /* Nothing */
#   define __VLIBCCALL /* Nothing */
#   define __VLIBDCALL /* Nothing */
#endif
#endif /* !__LIBCCALL */

#ifndef __LIBC
#if defined(__KOS__) && defined(__KERNEL__)
#define __LIBC __PUBDEF
#else
#define __LIBC __IMPDEF
#endif
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
#else
#define __LOCAL_LIBC(name) __PRIVATE __ATTR_UNUSED
#endif
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
#else
#define __LOCAL_LIBC_DATA(name) __PRIVATE __ATTR_UNUSED __LOCAL_LIBC_DATA_SECTION(name)
#endif
#endif /* !__LOCAL_LIBC_DATA */

#ifndef __LOCAL_LIBC_CONST_DATA
#ifdef __cplusplus
#if !defined(__NO_ATTR_SELECTANY) && 1
#define __LOCAL_LIBC_CONST_DATA(name) __ATTR_SELECTANY __ATTR_UNUSED __LOCAL_LIBC_CONST_DATA_SECTION(name)
#elif !defined(__NO_ATTR_WEAK) && 1
#define __LOCAL_LIBC_CONST_DATA(name) extern __INTERN __ATTR_WEAK __ATTR_UNUSED __LOCAL_LIBC_CONST_DATA_SECTION(name)
#else
#define __LOCAL_LIBC_CONST_DATA(name) __PRIVATE __ATTR_UNUSED __LOCAL_LIBC_CONST_DATA_SECTION(name)
#endif
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
#define __CASMNAME_SAME(x)                                                                              /* nothing */
#define __CASMNAME_DOS(x)                                                                               /* nothing */
#define __CASMNAME_SAME_DOS(x)                                                                          /* nothing */
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                /* nothing */
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   /* nothing */
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       /* nothing */
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          /* nothing */
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    /* nothing */
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       /* nothing */
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    /* nothing */
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      /* nothing */
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         /* nothing */
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   /* nothing */
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      /* nothing */
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) /* nothing */
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   /* nothing */
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) /* nothing */
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  /* nothing */
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     /* nothing */
#elif defined(__BUILDING_LIBC) && defined(__KOS__)
#define __CASMNAME(x)                                                                                   __ASMNAME("libc_" x)
#define __CASMNAME_SAME(x)                                                                              __ASMNAME("libc_" x)
#define __CASMNAME_DOS(x)                                                                               __ASMNAME("libd_" x)
#define __CASMNAME_SAME_DOS(x)                                                                          __ASMNAME("libd_" x)
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #name);
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   __INTDEF attr void nothrow(__LIBCCALL name) param __ASMNAME("libc_" #name);
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          __INTDEF attr void nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    __INTDEF attr Treturn nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libc_" #asmname);
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       __INTDEF attr void nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libc_" #asmname);
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBCCALL name) paramf __ASMNAME("libc_" #asmnamef);
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __INTDEF attr void nothrow(__VLIBCCALL name) paramf __ASMNAME("libc_" #asmnamef);
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      __INTDEF attr Treturn nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         __INTDEF attr void nothrow(__LIBCCALL name) param __ASMNAME("libc_" #asmname);
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __INTDEF attr void nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __INTDEF attr Treturn nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libd_" #asmname);
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __INTDEF attr void nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __ASMNAME("libd_" #asmname);
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBDCALL name) paramf __ASMNAME("libd_" #asmnamef);
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr void nothrow(__VLIBDCALL name) paramf __ASMNAME("libd_" #asmnamef);
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __INTDEF attr Treturn nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __INTDEF attr void nothrow(__LIBDCALL name) param __ASMNAME("libd_" #asmname);
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
#if defined(__CRT_DOS_PRIMARY) || defined(__CRT_CYG_PRIMARY)
#define __CASMNAME_DOS                                                                                  __ASMNAME
#define __CASMNAME_SAME_DOS(x)                                                                          /* nothing */
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,args)
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __REDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,args)
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBDCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBDCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,code)
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,code)
#else /* __CRT_DOS_PRIMARY || __CRT_CYG_PRIMARY */
#define __CASMNAME_DOS(x)                                                                               __ASMNAME("DOS$" x)
#define __CASMNAME_SAME_DOS(x)                                                                          __ASMNAME("DOS$" x)
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,args)
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __REDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,args)
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBDCALL,name,paramf,DOS$##asmnamef,vparamf,DOS$##vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBDCALL,name,paramf,DOS$##asmnamef,vparamf,DOS$##vasmnamef,args,before_va_start)
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,code)
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,code)
#endif /* !__CRT_DOS_PRIMARY && !__CRT_CYG_PRIMARY */
#endif /* !__BUILDING_LIBC... */


/* Special value used to indicate the *at functions should use the current working directory. */
#ifndef __CRT_AT_FDCWD
#if defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __CRT_AT_FDCWD   (-100)
#elif defined(__CRT_CYG)
#define __CRT_AT_FDCWD   (-2)
#endif
#endif /* !__CRT_AT_FDCWD */


#ifdef __CC__
/* Figure out where unreachable code locations are originating from.
 * Without this, GCC (rightfully) likes to make use of undefined behavior
 * when it comes to unreachable locations in order better optimize code.
 * However, this makes debugging much harder than it needs to be, so to
 * make our lives a bit easier, provide a functions that gets called in these
 * situations, with the equivalent effect of `abort()' and `std::terminate()' */
#if !defined(NDEBUG) && \
    (defined(__BUILDING_LIBC) || defined(__CRT_HAVE___crt_unreachable))
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
#ifdef __CRT_KOS_NATIVE
#include <gnu/stubs.h>
#endif /* __CRT_KOS_NATIVE */

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
