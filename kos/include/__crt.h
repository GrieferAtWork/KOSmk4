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
#ifndef ___CRT_H
#define ___CRT_H 1

#include "__stdinc.h"
#include "hybrid/host.h"

/* Automatically detect the linked CRT
 *   - __CRT_CYG          (windows / Cygwin)
 *   - __CRT_DOS          (windows / msvcrt.dll)
 *   - __CRT_FREESTANDING (freestanding / none)
 *   - __CRT_GENERIC      (generic / *)
 *   - __CRT_GLC          (linux / Glibc)
 *   - __CRT_KOS          (kos / libc.so)
 *   - __CRT_KOS_KERNEL   (kos / kernel.bin)
 * XXX: Sometimes referenced, but not fully implemented:
 *   - __CRT_NEWLIB
 *   - __CRT_LIBC45
 *   - __CRT_LIBC6
 *   - __CRT_uCLIBC
 */
#if (!defined(__CRT_DOS) && !defined(__CRT_GLC) &&            \
     !defined(__CRT_KOS) && !defined(__CRT_CYG) &&            \
     !defined(__CRT_GENERIC) && !defined(__CRT_KOS_KERNEL) && \
     !defined(__CRT_FREESTANDING))
#ifdef _CRT
/* Allow the user to do `-D_CRT=glibc' on the commandline to select the linked
 * crt. Support values for `_CRT' can be found in <crt-features/_crt-select.h> */
#include <crt-features/_crt-select.h>
#elif defined(__KOS__) && defined(__KERNEL__)
#   define __CRT_KOS_KERNEL
#   define __CRT_KOS_PRIMARY
#   define __CRT_KOS
//#elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ + 0) == 0
/* This might seem like a good idea, but programs using `-ffreestanding',
 * but still ending up #including some  CRT header will likely also  pass
 * `-lc' on the  commandline, so  we shouldn't  respond to  that flag  to
 * determine the linked CRT library to be non-present...
 *
 * If that *is* what you want, you need to compile with `-D_CRT=freestanding' */
///* Freestanding CRT environment. */
//#   define __CRT_FREESTANDING
#elif defined(__KOS__)
#   define __CRT_KOS
#   define __CRT_GLC /* Emulated by KOS */
#   define __CRT_DOS /* Emulated by KOS */
#   define __CRT_KOS_PRIMARY
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
#   define __CRT_CYG_PRIMARY
#   define __CRT_CYG
#elif (defined(__linux__) || defined(__linux) || defined(linux) || \
       defined(__unix__) || defined(__unix) || defined(unix))
#   define __CRT_GLC_PRIMARY
#   define __CRT_GLC
#elif (defined(__WINDOWS__) || defined(_MSC_VER) ||                                       \
       defined(_WIN16) || defined(WIN16) || defined(_WIN32) || defined(WIN32) ||          \
       defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
       defined(_WIN32_WCE) || defined(WIN32_WCE))
#   define __CRT_DOS_PRIMARY
#   define __CRT_DOS
#else /* ... */
#   define __CRT_GENERIC
#endif /* !... */
#endif /* !__CRT_... */




#if defined(__KERNEL__) && defined(__KOS__) && !defined(__HAVE_FPU)
#undef __NO_FPU
#define __NO_FPU /* Disable functions using FPU registers in kernel-mode. */
#endif /* __KERNEL__ && __KOS__ && !__HAVE_FPU */

#ifdef __CRT_KOS_PRIMARY
#ifndef __BUILDING_LIBC
#ifdef __CRT_KOS_KERNEL
#include <crt-features/crt-kos-kernel.h>
#if (defined(CONFIG_NO_ASSERT_RESTARTABLE) || defined(CONFIG_NO_KERNEL_DEBUGGER) || \
     (defined(CONFIG_HAVE_KERNEL_DEBUGGER) && (-CONFIG_HAVE_KERNEL_DEBUGGER - 1) == -1))
#undef __CRT_HAVE___acheck
#undef __CRT_HAVE___acheckf
#endif /* CONFIG_NO_ASSERT_RESTARTABLE || CONFIG_NO_KERNEL_DEBUGGER */
#else /* __CRT_KOS_KERNEL */
#include <crt-features/crt-kos.h>
#endif /* !__CRT_KOS_KERNEL */
#endif /* !__BUILDING_LIBC */
#else /* __CRT_KOS_PRIMARY */
#if defined(__CRT_CYG_PRIMARY)
#include <crt-features/crt-cyg.h>
#elif defined(__CRT_GLC_PRIMARY)
#include <crt-features/crt-glc.h>
#elif defined(__CRT_DOS_PRIMARY)
#include <crt-features/crt-dos.h>
#elif defined(__CRT_GENERIC)
#include <crt-features/generic.h>
#endif /* ... */
#ifdef __WANT_KOS_PRINTF
#include <crt-features/delete-printf.h>
#endif /* __WANT_KOS_PRINTF */
#endif /* !__CRT_KOS_PRIMARY */


#define __ATTR_LIBC_PRINTF(a, b)      /* nothing */
#define __ATTR_LIBC_PRINTF_P(a, b)    /* nothing */
#define __ATTR_LIBC_SCANF(a, b)       /* nothing */
#define __ATTR_LIBC_STRFMON(a, b)     /* nothing */
#define __ATTR_LIBC_STRFTIME(a, b)    /* nothing */
#define __ATTR_LIBC_WPRINTF(a, b)     /* nothing */
#define __ATTR_LIBC_WPRINTF_P(a, b)   /* nothing */
#define __ATTR_LIBC_WSCANF(a, b)      /* nothing */
#define __ATTR_LIBC_WCSFTIME(a, b)    /* nothing */
#define __ATTR_LIBC_C16PRINTF(a, b)   /* nothing */
#define __ATTR_LIBC_C16PRINTF_P(a, b) /* nothing */
#define __ATTR_LIBC_C16SCANF(a, b)    /* nothing */
#define __ATTR_LIBC_C16FTIME(a, b)    /* nothing */
#define __ATTR_LIBC_C32PRINTF(a, b)   /* nothing */
#define __ATTR_LIBC_C32PRINTF_P(a, b) /* nothing */
#define __ATTR_LIBC_C32SCANF(a, b)    /* nothing */
#define __ATTR_LIBC_C32FTIME(a, b)    /* nothing */

#ifndef __LIBC_MALLOC_ALIGNMENT
#ifdef __INTELLISENSE__ /* Don't include <hybrid/typecore.h> */
#define __LIBC_MALLOC_ALIGNMENT 16
#else /* __INTELLISENSE__ */
#include <hybrid/typecore.h>
#ifdef __ALIGNOF_MAX_ALIGN_T__
#define __LIBC_MALLOC_ALIGNMENT __ALIGNOF_MAX_ALIGN_T__
#else /* __ALIGNOF_MAX_ALIGN_T__ */
#define __LIBC_MALLOC_ALIGNMENT __SIZEOF_POINTER__
#endif /* !__ALIGNOF_MAX_ALIGN_T__ */
#endif /* !__INTELLISENSE__ */
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
#define __LIBC_BIND_OPTIMIZATIONS
#endif /* ... */


#ifdef __LIBC_BIND_CRTBUILTINS
#if (__LIBC_BIND_CRTBUILTINS + 0) == 0
#undef __LIBC_BIND_CRTBUILTINS
#endif /* !__LIBC_BIND_CRTBUILTINS */
#elif (!defined(__INTELLISENSE__) && !defined(__NO_has_builtin) &&                              \
       /* Don't bind CRT-builtin functions (such as `__builtin_malloc()') when building         \
        * libc itself, so-as  to prevent  GCC from generating  relocations against  the         \
        * real symbols (which would end up as relocations in the final binary), when we         \
        * actually want everything to be linked against symbols from the `libc_' namespace. */  \
       !defined(__BUILDING_LIBC) &&                                                             \
       /* Don't bind CRT-builtin functions when linking against the i386 kernel's builtin  CRT. \
        * Because GCC assumes the default calling convention for builtin functions, we'd end up \
        * with stack corruptions since the kernel uses STDCALL, but gcc invokes as CDECL. */    \
       !(defined(__CRT_KOS_KERNEL) && (defined(__i386__) && !defined(__x86_64__))))
#define __LIBC_BIND_CRTBUILTINS
#endif


/* Automatic namespacing for fast (platform/arch-specific) optimized implementations of functions. */
#ifdef __cplusplus
#define __NAMESPACE_FAST_BEGIN               namespace __optimized_imp {
#define __NAMESPACE_FAST_END                 }
#define __NAMESPACE_FAST_SYM                 ::__optimized_imp::
#define __NAMESPACE_FAST_USING(x)            using ::__optimized_imp::x;
#ifdef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
#define __NAMESPACE_FAST_USING_OR_IMPL(x, i) i
#else /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING */
#define __NAMESPACE_FAST_USING_OR_IMPL(x, i) using ::__optimized_imp::x;
#endif /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING */
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
#ifdef __INTELLISENSE__
#define __LIBC_LOCAL_NAME(x) x
#define __LIBC_LOCAL_NAME_IS_IDENTITY
#elif defined(_MSC_VER)
#define __LIBC_LOCAL_NAME(x) x
#define __LIBC_LOCAL_NAME_IS_IDENTITY
#else /* __INTELLISENSE__ */
/* Name local functions differently to prevent errors:
 * >> extern "C" {
 * >> namespace inner {
 * >> inline __attribute__((__noinline__)) int my_function(void) {
 * >> 	return 42;
 * >> }
 * >> }
 * >> static int my_function(void) {
 * >> 	return inner::my_function();
 * >> }
 * >> }
 * >>
 * >> extern "C" {
 * >> extern void foo(void *);
 * >> void foobar(void) {
 * >> 	foo((void *)&my_function);
 * >> }
 * >> }
 *
 * Error:
 * >> Assembler messages:
 * >> Error: symbol `my_function' is already defined
 * >> Error: .size expression for my_function does not evaluate to a constant
 */
#define __LIBC_LOCAL_NAME(x) __l_##x
#endif /* !__INTELLISENSE__ */
extern "C++" {namespace __local_imp {
#if (__has_feature(cxx_alias_templates) ||                                  \
     (defined(__cpp_alias_templates) && __cpp_alias_templates >= 200704) || \
     (defined(__BORLANDC__) && __BORLANDC__ > 0x613) ||                     \
     (defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180020827))
/*#define __COMPILER_HAVE_CXX_TEMPLATE_USING*/
/* Hacky work-around to define a  macro `__NAMESPACE_LOCAL_TYPEHAX' that can  be
 * used to cast a given function into a (seemingly incompatible) prototype while
 * also  allowing (read: requiring)  the caller to  prefix the entire expression
 * with `__NAMESPACE_LOCAL_SYM'
 *
 * Used by `cheaders.dee' when generating macros for linking against functions
 * from the __local_imp namespace. */
template<class __T> using __loc_T = __T;
#define __NAMESPACE_LOCAL_TYPEHAX(Tp, Tr, x) __loc_T<Tr>(::__local_imp::__LIBC_LOCAL_NAME(x))
#else /* ... */
template<class __S> struct __loc_T { typedef __S __T; };
#define __NAMESPACE_LOCAL_TYPEHAX(Tp, Tr, x) __loc_T<Tr>::__T(::__local_imp::__LIBC_LOCAL_NAME(x))
#endif /* !... */
}}
#define __NAMESPACE_LOCAL_BEGIN               namespace __local_imp {
#define __NAMESPACE_LOCAL_END                 }
#define __NAMESPACE_LOCAL_SYM                 ::__local_imp::
#ifdef __LIBC_LOCAL_NAME_IS_IDENTITY
#define __NAMESPACE_LOCAL_USING(x)            using ::__local_imp::x;
#ifdef __COMPILER_HAVE_BUG_BLOATY_CXX_USING
#define __NAMESPACE_LOCAL_USING_OR_IMPL(x, i) i
#else /* __COMPILER_HAVE_BUG_BLOATY_CXX_USING */
#define __NAMESPACE_LOCAL_USING_OR_IMPL(x, i) using ::__local_imp::x;
#endif /* !__COMPILER_HAVE_BUG_BLOATY_CXX_USING */
#else /* __LIBC_LOCAL_NAME_IS_IDENTITY */
#define __NAMESPACE_LOCAL_USING_OR_IMPL(x, i) i
#endif /* !__LIBC_LOCAL_NAME_IS_IDENTITY */
#else /* __cplusplus */
#define __NAMESPACE_LOCAL_TYPEHAX(Tp, Tr, x)  (*(Tp)&__local_##x)
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
 *     The caller of a  function is responsible to  clean up the argument  list.
 *     When defined,  this allows  functions to  be called  with more  arguments
 *     than they actually take, with superfluous arguments simply being ignored.
 *       - __LIBCCALL_CALLER_CLEANUP
 *       - __LIBKCALL_CALLER_CLEANUP
 *       - __LIBDCALL_CALLER_CLEANUP
 */
#ifdef __x86_64__
#ifdef __CRT_KOS_KERNEL
/* Use SYSVABI for everything in kernel-space! */
#   define __LIBKCALL  __ATTR_SYSVABI
#   define __VLIBKCALL __ATTR_SYSVABI
#   define __LIBDCALL  __ATTR_SYSVABI
#   define __VLIBDCALL __ATTR_SYSVABI
#   define __LIBCCALL  __ATTR_SYSVABI
#   define __VLIBCCALL __ATTR_SYSVABI
#   define __LIBCCALL_IS_LIBKCALL
#   define __LIBCCALL_IS_LIBDCALL
#   define __LIBDCALL_IS_LIBKCALL
#   define __VLIBCCALL_IS_VLIBKCALL
#   define __VLIBCCALL_IS_VLIBDCALL
#   define __VLIBDCALL_IS_VLIBKCALL
#   define __VLIBCCALL_IS_LIBCCALL
#   define __VLIBDCALL_IS_LIBDCALL
#   define __VLIBKCALL_IS_LIBKCALL
#   define __LIBCCALL_CALLER_CLEANUP
#   define __LIBKCALL_CALLER_CLEANUP
#   define __LIBDCALL_CALLER_CLEANUP
#else /* __CRT_KOS_KERNEL */
#   define __LIBKCALL  __ATTR_SYSVABI
#   define __VLIBKCALL __ATTR_SYSVABI
#   define __LIBDCALL  __ATTR_MSABI
#   define __VLIBDCALL __ATTR_MSABI
#   define __LIBCCALL_CALLER_CLEANUP
#   define __LIBKCALL_CALLER_CLEANUP
#   define __LIBDCALL_CALLER_CLEANUP
#   define __VLIBCCALL_IS_LIBCCALL
#   define __VLIBDCALL_IS_LIBDCALL
#   define __VLIBKCALL_IS_LIBKCALL
#ifdef __PE__
#   define __LIBCCALL_IS_LIBDCALL
#   define __LIBCCALL  __LIBDCALL
#   define __VLIBCCALL_IS_VLIBDCALL
#   define __VLIBCCALL  __VLIBDCALL
#else /* __PE__ */
#   define __LIBCCALL_IS_LIBKCALL
#   define __LIBCCALL  __LIBKCALL
#   define __VLIBCCALL_IS_VLIBKCALL
#   define __VLIBCCALL  __VLIBKCALL
#endif /* !__PE__ */
#endif /* !__CRT_KOS_KERNEL */
#elif defined(__i386__)
#ifdef __CRT_KOS_KERNEL
#   define __LIBCCALL  __KCALL
#   define __LIBKCALL  __KCALL
#   define __LIBDCALL  __KCALL
#else /* __CRT_KOS_KERNEL */
#   define __LIBCCALL  __ATTR_CDECL
#   define __LIBKCALL  __ATTR_CDECL
#   define __LIBDCALL  __ATTR_CDECL
#   define __VLIBCCALL_IS_LIBCCALL
#   define __VLIBKCALL_IS_LIBKCALL
#   define __VLIBDCALL_IS_LIBDCALL
#   define __LIBCCALL_CALLER_CLEANUP
#   define __LIBKCALL_CALLER_CLEANUP
#   define __LIBDCALL_CALLER_CLEANUP
#endif /* !__CRT_KOS_KERNEL */
#   define __LIBCCALL_IS_LIBKCALL
#   define __LIBCCALL_IS_LIBDCALL
#   define __LIBDCALL_IS_LIBKCALL
#   define __VLIBCCALL __ATTR_CDECL
#   define __VLIBKCALL __ATTR_CDECL
#   define __VLIBDCALL __ATTR_CDECL
#   define __VLIBCCALL_IS_VLIBKCALL
#   define __VLIBCCALL_IS_VLIBDCALL
#   define __VLIBDCALL_IS_VLIBKCALL
#else /* Arch... */
#if defined(__arm__)
#   define __LIBCCALL_CALLER_CLEANUP
#   define __LIBKCALL_CALLER_CLEANUP
#   define __LIBDCALL_CALLER_CLEANUP
#endif /* __arm__ */
#   define __LIBCCALL  /* Nothing */
#   define __LIBDCALL  /* Nothing */
#   define __LIBKCALL  /* Nothing */
#   define __VLIBCCALL /* Nothing */
#   define __VLIBDCALL /* Nothing */
#   define __VLIBKCALL /* Nothing */
#   define __LIBCCALL_IS_LIBKCALL
#   define __LIBCCALL_IS_LIBDCALL
#   define __LIBDCALL_IS_LIBKCALL
#   define __VLIBCCALL_IS_VLIBKCALL
#   define __VLIBCCALL_IS_VLIBDCALL
#   define __VLIBDCALL_IS_VLIBKCALL
#   define __VLIBCCALL_IS_LIBCCALL
#   define __VLIBDCALL_IS_LIBDCALL
#   define __VLIBKCALL_IS_LIBKCALL
#endif /* !Arch... */




#ifndef __LIBC
#if defined(__KOS__) && defined(__KERNEL__)
#define __LIBC __PUBDEF
#elif defined(__CRT_KOS) && defined(__BUILDING_LIBC)
#define __LIBC __INTDEF
#else /* ... */
#define __LIBC __IMPDEF
#endif /* !... */
#endif /* !__LIBC */



/* Linkage for local function substitutions. */
#ifndef __LOCAL_LIBC
#define __LOCAL_LIBC(name) __INTERN_COMDAT_SECTION(".text.local", #name)
#endif /* !__LOCAL_LIBC */

#ifndef __NO_ATTR_SECTION
#ifdef __TINYC__
#define __LOCAL_LIBC_DATA_SECTION(name)       __ATTR_SECTION(__PP_PRIVATE_STR(.data.local.name))
#define __LOCAL_LIBC_CONST_DATA_SECTION(name) __ATTR_SECTION(__PP_PRIVATE_STR(.rodata.local.name))
#else /* __TINYC__ */
#define __LOCAL_LIBC_DATA_SECTION(name)       __ATTR_SECTION(".data.local." #name)
#define __LOCAL_LIBC_CONST_DATA_SECTION(name) __ATTR_SECTION(".rodata.local." #name)
#endif /* !__TINYC__ */
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
struct __locale_struct;
#ifdef __cplusplus
#define __locale_t struct ::__locale_struct *
#else /* __cplusplus */
#define __locale_t struct __locale_struct *
#endif /* !__cplusplus */
#endif /* ... */


#ifndef __CC__
#define __CASMNAME(x)                                                                                   /* nothing */
#define __CASMNAME_DOS(x)                                                                               /* nothing */
#define __CASMNAME_KOS(x)                                                                               /* nothing */
#define __CASMNAME_SAME(x)                                                                              /* nothing */
#define __CASMNAME_DOS_SAME(x)                                                                          /* nothing */
#define __CASMNAME_KOS_SAME(x)                                                                          /* nothing */
#define __CSDECLARE(attr,T,name)                                                                        /* nothing */
#define __CSREDIRECT(attr,T,name,asmname)                                                               /* nothing */
#define __CSDECLARE2(attr,Tdecl,name)                                                                   /* nothing */
#define __CSREDIRECT2(attr,Tdecl,name,asmname)                                                          /* nothing */
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
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)                                               /* nothing */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)                                           /* nothing */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)                                           /* nothing */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)                                      /* nothing */
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...)                                  /* nothing */
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...)                                  /* nothing */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl...)                                    /* nothing */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)                                /* nothing */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)                                /* nothing */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl...)                           /* nothing */
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...)                       /* nothing */
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...)                       /* nothing */
#else /* ... */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl)                                       /* nothing */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)                                   /* nothing */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)                                   /* nothing */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl)                              /* nothing */
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl)                          /* nothing */
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl)                          /* nothing */
#endif /* !... */
#elif defined(__INTELLISENSE__) /* Help out the IDE... */
#define __CASMNAME(x)                                                                                   /* nothing */
#define __CASMNAME_DOS(x)                                                                               /* nothing */
#define __CASMNAME_KOS(x)                                                                               /* nothing */
#define __CASMNAME_SAME(x)                                                                              /* nothing */
#define __CASMNAME_DOS_SAME(x)                                                                          /* nothing */
#define __CASMNAME_KOS_SAME(x)                                                                          /* nothing */
#define __CSDECLARE(attr,T,name)                                                                        extern attr T name;
#define __CSREDIRECT(attr,T,name,asmname)                                                               extern attr T name;
#define __CSDECLARE2(attr,Tdecl,name)                                                                   extern attr Tdecl;
#define __CSREDIRECT2(attr,Tdecl,name,asmname)                                                          extern attr Tdecl;
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                extern attr Treturn nothrow(__LIBCCALL name) param;
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   extern attr void nothrow(__LIBCCALL name) param;
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       extern attr Treturn nothrow(__LIBCCALL name) param;
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   extern attr Treturn nothrow(__LIBDCALL name) param;
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   extern attr Treturn nothrow(__LIBKCALL name) param;
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          extern attr void nothrow(__LIBCCALL name) param;
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      extern attr void nothrow(__LIBDCALL name) param;
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      extern attr void nothrow(__LIBKCALL name) param;
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    extern attr Treturn nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) extern attr Treturn nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) extern attr Treturn nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       extern attr void nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   extern attr void nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   extern attr void nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...);
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern attr Treturn nothrow(__VLIBCCALL name) paramf;
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern attr Treturn nothrow(__VLIBDCALL name) paramf;
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern attr Treturn nothrow(__VLIBKCALL name) paramf;
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    extern attr void nothrow(__VLIBCCALL name) paramf;
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern attr void nothrow(__VLIBDCALL name) paramf;
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern attr void nothrow(__VLIBKCALL name) paramf;
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      extern attr Treturn nothrow(__LIBCCALL name) param;
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  extern attr Treturn nothrow(__LIBDCALL name) param;
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  extern attr Treturn nothrow(__LIBKCALL name) param;
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         extern attr void nothrow(__LIBCCALL name) param;
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     extern attr void nothrow(__LIBDCALL name) param;
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     extern attr void nothrow(__LIBKCALL name) param;
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)                                               extern attr Treturn nothrow(__LIBCCALL name) param;
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)                                           extern attr Treturn nothrow(__LIBDCALL name) param;
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)                                           extern attr Treturn nothrow(__LIBKCALL name) param;
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)                                      extern attr Treturn nothrow(__LIBCCALL name) param;
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...)                                  extern attr Treturn nothrow(__LIBDCALL name) param;
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...)                                  extern attr Treturn nothrow(__LIBKCALL name) param;
#elif defined(__BUILDING_LIBC) && defined(__KOS__)
#define __CASMNAME(x)                                                                                   __COMPILER_ASMNAME("libc_" x)
#define __CASMNAME_DOS(x)                                                                               __COMPILER_ASMNAME("libd_" x)
#define __CASMNAME_KOS(x)                                                                               __COMPILER_ASMNAME("libc_" x)
#define __CASMNAME_SAME(x)                                                                              __COMPILER_ASMNAME("libc_" x)
#define __CASMNAME_DOS_SAME(x)                                                                          __COMPILER_ASMNAME("libd_" x)
#define __CASMNAME_KOS_SAME(x)                                                                          __COMPILER_ASMNAME("libc_" x)
#define __CSDECLARE(attr,T,name)                                                                        __INTDEF attr T name __COMPILER_ASMNAME("libc_" #name);
#define __CSREDIRECT(attr,T,name,asmname)                                                               __INTDEF attr T name __COMPILER_ASMNAME("libc_" #asmname);
#define __CSDECLARE2(attr,Tdecl,name)                                                                   __INTDEF attr Tdecl __COMPILER_ASMNAME("libc_" #name);
#define __CSREDIRECT2(attr,Tdecl,name,asmname)                                                          __INTDEF attr Tdecl __COMPILER_ASMNAME("libc_" #asmname);
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                __INTDEF attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #name);
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   __INTDEF attr void nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #name);
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       __INTDEF attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __INTDEF attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #asmname);
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __INTDEF attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          __INTDEF attr void nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __INTDEF attr void nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #asmname);
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      __INTDEF attr void nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    __INTDEF attr Treturn nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libc_" #asmname);
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __INTDEF attr Treturn nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libd_" #asmname);
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __INTDEF attr Treturn nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libc_" #asmname);
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       __INTDEF attr void nothrow(__LIBCCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libc_" #asmname);
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __INTDEF attr void nothrow(__LIBDCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libd_" #asmname);
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __INTDEF attr void nothrow(__LIBKCALL name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libc_" #asmname);
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBCCALL name) paramf __COMPILER_ASMNAME("libc_" #asmnamef);
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBDCALL name) paramf __COMPILER_ASMNAME("libd_" #asmnamef);
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr Treturn nothrow(__VLIBKCALL name) paramf __COMPILER_ASMNAME("libc_" #asmnamef);
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __INTDEF attr void nothrow(__VLIBCCALL name) paramf __COMPILER_ASMNAME("libc_" #asmnamef);
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr void nothrow(__VLIBDCALL name) paramf __COMPILER_ASMNAME("libd_" #asmnamef);
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __INTDEF attr void nothrow(__VLIBKCALL name) paramf __COMPILER_ASMNAME("libc_" #asmnamef);
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      __INTDEF attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __INTDEF attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #asmname);
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __INTDEF attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         __INTDEF attr void nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __INTDEF attr void nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #asmname);
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     __INTDEF attr void nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#ifdef __NO_EXTERN_INLINE
#ifdef __NO_INLINE__
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __INTDEF attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #name);
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #name);
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #name);
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __INTDEF attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #asmname);
#else /* __NO_INLINE__ */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#endif /* !__NO_INLINE__ */
#else /* __NO_EXTERN_INLINE */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)              __INTDEF attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __INTDEF attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...)     __INTDEF attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME("libc_" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("libd_" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __INTDEF attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("libc_" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#endif /* !__NO_EXTERN_INLINE */
#define __COMPILER_CREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args)                                       decl attr Treturn nothrow(cc name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __COMPILER_CREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args)                                          decl attr void nothrow(cc name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __COMPILER_CVREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)    decl attr Treturn nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libc_" #asmname);
#define __COMPILER_CVREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,args,before_va_start,varcount,vartypes)       decl attr void nothrow(cc name)(____PRIVATE_VREDIRECT_UNPACK param, ...) __COMPILER_ASMNAME("libc_" #asmname);
#define __COMPILER_CVFREDIRECT(decl,attr,Treturn,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) decl attr Treturn nothrow(cc name) paramf __COMPILER_ASMNAME("libc_" #asmnamef);
#define __COMPILER_CVFREDIRECT_VOID(decl,attr,nothrow,cc,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    decl attr void nothrow(cc name) paramf __COMPILER_ASMNAME("libc_" #asmnamef);
#define __COMPILER_CXREDIRECT(decl,attr,Treturn,nothrow,cc,name,param,asmname,code)                                      decl attr Treturn nothrow(cc name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __COMPILER_CXREDIRECT_VOID(decl,attr,nothrow,cc,name,param,asmname,code)                                         decl attr void nothrow(cc name) param __COMPILER_ASMNAME("libc_" #asmname);
#define __COMPILER_CEIDECLARE(attr,Treturn,nothrow,cc,name,param,...)                                                    __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,libc_##name,__VA_ARGS__)
#define __COMPILER_CEIREDIRECT(attr,Treturn,nothrow,cc,name,param,asmname,...)                                           __COMPILER_EIREDIRECT(attr,Treturn,nothrow,cc,name,param,libc_##asmname,__VA_ARGS__)
#else /* __BUILDING_LIBC... */
#define __CASMNAME                                                                                      __COMPILER_ASMNAME
#define __CASMNAME_SAME(x)                                                                              /* nothing */
#define __CSDECLARE(attr,T,name)                                                                        __LIBC attr T name;
#define __CSREDIRECT(attr,T,name,asmname)                                                               __COMPILER_SREDIRECT(__LIBC,attr,T,name,asmname)
#define __CSDECLARE2(attr,Tdecl,name)                                                                   __LIBC attr Tdecl;
#define __CSREDIRECT2(attr,Tdecl,name,asmname)                                                          __COMPILER_SREDIRECT2(__LIBC,attr,Tdecl,name,asmname)
#define __CDECLARE(attr,Treturn,nothrow,name,param,args)                                                __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#define __CDECLARE_VOID(attr,nothrow,name,param,args)                                                   __LIBC attr void nothrow(__LIBCCALL name) param;
#define __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args)                                       __COMPILER_REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBCCALL,name,param,asmname,args)
#define __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args)                                          __COMPILER_REDIRECT_VOID(__LIBC,attr,nothrow,__LIBCCALL,name,param,asmname,args)
#define __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    __COMPILER_VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBCCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       __COMPILER_VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBCCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBCCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    __COMPILER_VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBCCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code)                                      __COMPILER_XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBCCALL,name,param,asmname,code)
#define __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code)                                         __COMPILER_XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBCCALL,name,param,asmname,code)
#ifdef __PE__
#define __CASMNAME_DOS                                                                                  __COMPILER_ASMNAME
#define __CASMNAME_KOS(x)                                                                               __COMPILER_ASMNAME("KOS$" x)
#define __CASMNAME_DOS_SAME(x)                                                                          /* nothing */
#define __CASMNAME_KOS_SAME(x)                                                                          __COMPILER_ASMNAME("KOS$" x)
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __COMPILER_REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,args)
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __COMPILER_REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,KOS$##asmname,args)
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __COMPILER_REDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,args)
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      __COMPILER_REDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,KOS$##asmname,args)
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __COMPILER_VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __COMPILER_VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,KOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __COMPILER_VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __COMPILER_VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,KOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBDCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBKCALL,name,paramf,KOS$##asmnamef,vparamf,KOS$##vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBDCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBKCALL,name,paramf,KOS$##asmnamef,vparamf,KOS$##vasmnamef,args,before_va_start)
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __COMPILER_XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,asmname,code)
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __COMPILER_XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,KOS$##asmname,code)
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __COMPILER_XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,asmname,code)
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     __COMPILER_XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,KOS$##asmname,code)
#else /* __PE__ */
#define __CASMNAME_DOS(x)                                                                               __COMPILER_ASMNAME("DOS$" x)
#define __CASMNAME_KOS                                                                                  __COMPILER_ASMNAME
#define __CASMNAME_DOS_SAME(x)                                                                          __COMPILER_ASMNAME("DOS$" x)
#define __CASMNAME_KOS_SAME(x)                                                                          /* nothing */
#define __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __COMPILER_REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,args)
#define __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args)                                   __COMPILER_REDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,asmname,args)
#define __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args)                                      __COMPILER_REDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,args)
#define __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args)                                      __COMPILER_REDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,asmname,args)
#define __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __COMPILER_VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) __COMPILER_VREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __COMPILER_VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,args,before_va_start,varcount,vartypes)
#define __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   __COMPILER_VREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,asmname,args,before_va_start,varcount,vartypes)
#define __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBDCALL,name,paramf,DOS$##asmnamef,vparamf,DOS$##vasmnamef,args,before_va_start)
#define __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT(__LIBC,attr,Treturn,nothrow,__VLIBKCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBDCALL,name,paramf,DOS$##asmnamef,vparamf,DOS$##vasmnamef,args,before_va_start)
#define __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) __COMPILER_VFREDIRECT_VOID(__LIBC,attr,nothrow,__VLIBKCALL,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)
#define __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __COMPILER_XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBDCALL,name,param,DOS$##asmname,code)
#define __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code)                                  __COMPILER_XREDIRECT(__LIBC,attr,Treturn,nothrow,__LIBKCALL,name,param,asmname,code)
#define __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code)                                     __COMPILER_XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBDCALL,name,param,DOS$##asmname,code)
#define __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code)                                     __COMPILER_XREDIRECT_VOID(__LIBC,attr,nothrow,__LIBKCALL,name,param,asmname,code)
#endif /* !__PE__ */
#ifdef __NO_EXTERN_INLINE

#ifdef __NO_INLINE__
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...) __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl...) __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#else /* ... */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl) __LIBC attr Treturn nothrow(__LIBCCALL name) param;
#endif /* !... */
#ifdef __NO_ASMNAME
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#else /* ... */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#endif /* !... */
#else /* __NO_ASMNAME */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBCCALL name) param; __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBCCALL name) param; __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#else /* ... */
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBCCALL name) param; __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#endif /* !... */
#endif /* !__NO_ASMNAME */
#else /* __NO_INLINE__ */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#endif /* !... */
#endif /* !__NO_INLINE__ */
#ifdef __PE__
#ifdef __NO_INLINE__
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param;
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...) __LIBC attr Treturn nothrow(__LIBDCALL name) param;
#else /* ... */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl) __LIBC attr Treturn nothrow(__LIBDCALL name) param;
#endif /* !... */
#ifdef __NO_ASMNAME
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#endif /* !... */
#else /* __NO_ASMNAME */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#else /* ... */
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#endif /* !... */
#endif /* !__NO_ASMNAME */
#else /* __NO_INLINE__ */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#endif /* !... */
#endif /* !__NO_INLINE__ */
#else /* __PE__ */
#ifdef __NO_INLINE__
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param;
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...) __LIBC attr Treturn nothrow(__LIBKCALL name) param;
#else /* ... */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl) __LIBC attr Treturn nothrow(__LIBKCALL name) param;
#endif /* !... */
#ifdef __NO_ASMNAME
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#endif /* !... */
#else /* __NO_ASMNAME */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#else /* ... */
#ifdef __COMPILER_ASMNAME_ON_SECOND_DECL
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBKCALL name) param; __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBDCALL name) param; __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname);
#else /* __COMPILER_ASMNAME_ON_SECOND_DECL */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name);
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname);
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname);
#endif /* !__COMPILER_ASMNAME_ON_SECOND_DECL */
#endif /* !... */
#endif /* !__NO_ASMNAME */
#else /* __NO_INLINE__ */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)          __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBKCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LOCAL __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#endif /* !... */
#endif /* !__NO_INLINE__ */
#endif /* !__PE__ */

#else /* __NO_EXTERN_INLINE */

#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBCCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBCCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBCCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBCCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#endif /* !... */
#ifdef __PE__
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBDCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME("KOS$" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#endif /* !... */
#else /* __PE__ */
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param __VA_ARGS__
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param __VA_ARGS__
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl...)          __LIBC attr Treturn nothrow(__LIBKCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl...) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#else /* ... */
#define __CEIDECLARE_DOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #name); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIDECLARE_KOS(attr,Treturn,nothrow,name,param,inline_impl)          __LIBC attr Treturn nothrow(__LIBKCALL name) param; __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#define __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBDCALL name) param __COMPILER_ASMNAME("DOS$" #asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBDCALL name) param inline_impl
#define __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) __LIBC attr Treturn nothrow(__LIBKCALL name) param __COMPILER_ASMNAME(#asmname); __EXTERN_INLINE __ATTR_ARTIFICIAL attr Treturn nothrow(__LIBCCALL name) param inline_impl
#endif /* !... */
#endif /* !__PE__ */

#endif /* !__NO_EXTERN_INLINE */
#endif /* !__BUILDING_LIBC... */

#ifndef __COMPILER_CREDIRECT
#define __COMPILER_CREDIRECT        __COMPILER_REDIRECT
#define __COMPILER_CREDIRECT_VOID   __COMPILER_REDIRECT_VOID
#define __COMPILER_CVREDIRECT       __COMPILER_VREDIRECT
#define __COMPILER_CVREDIRECT_VOID  __COMPILER_VREDIRECT_VOID
#define __COMPILER_CVFREDIRECT      __COMPILER_VFREDIRECT
#define __COMPILER_CVFREDIRECT_VOID __COMPILER_VFREDIRECT_VOID
#define __COMPILER_CXREDIRECT       __COMPILER_XREDIRECT
#define __COMPILER_CXREDIRECT_VOID  __COMPILER_XREDIRECT_VOID
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __COMPILER_CEIDECLARE  __COMPILER_EIDECLARE
#define __COMPILER_CEIREDIRECT __COMPILER_EIREDIRECT
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __COMPILER_CEIDECLARE  __COMPILER_EIDECLARE
#define __COMPILER_CEIREDIRECT __COMPILER_EIREDIRECT
#else /* ... */
#define __COMPILER_CEIDECLARE  __COMPILER_EIDECLARE
#define __COMPILER_CEIREDIRECT __COMPILER_EIREDIRECT
#endif /* !... */
#endif /* !__COMPILER_CREDIRECT */


/* Special c-declare functions that are needed to work around a GCC bug that
 * causes certain functions to  _always_ be considered as  nothrow/noexcept,
 * irregardless of compiler options passed, or how they are declared.
 *
 * The  only  thing  that seems  to  work as  far  as  workarounds go,  is  to declare
 * the function with extern "C++" linkage, and use `__COMPILER_ASMNAME()' to re-assign
 * the proper symbol name. */
#ifdef __COMPILER_HAVE_GCCNCX_BUILTIN_BUG
#define __CASMNAME_GCCNCX          __CASMNAME
#define __CASMNAME_DOS_GCCNCX      __CASMNAME_DOS
#define __CASMNAME_KOS_GCCNCX      __CASMNAME_KOS
#define __CASMNAME_SAME_GCCNCX     __CASMNAME
#define __CASMNAME_DOS_SAME_GCCNCX __CASMNAME_DOS
#define __CASMNAME_KOS_SAME_GCCNCX __CASMNAME_KOS
#define __CDECLARE_GCCNCX(attr,Treturn,nothrow,name,param,args)                                                extern "C++" { __CREDIRECT(attr,Treturn,nothrow,name,param,name,args) }
#define __CDECLARE_VOID_GCCNCX(attr,nothrow,name,param,args)                                                   extern "C++" { __CREDIRECT_VOID(attr,nothrow,name,param,name,args) }
#define __CREDIRECT_GCCNCX(attr,Treturn,nothrow,name,param,asmname,args)                                       extern "C++" { __CREDIRECT(attr,Treturn,nothrow,name,param,asmname,args) }
#define __CREDIRECT_DOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,args)                                   extern "C++" { __CREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args) }
#define __CREDIRECT_KOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,args)                                   extern "C++" { __CREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args) }
#define __CREDIRECT_VOID_GCCNCX(attr,nothrow,name,param,asmname,args)                                          extern "C++" { __CREDIRECT_VOID(attr,nothrow,name,param,asmname,args) }
#define __CREDIRECT_VOID_DOS_GCCNCX(attr,nothrow,name,param,asmname,args)                                      extern "C++" { __CREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args) }
#define __CREDIRECT_VOID_KOS_GCCNCX(attr,nothrow,name,param,asmname,args)                                      extern "C++" { __CREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args) }
#define __CVREDIRECT_GCCNCX(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)    extern "C++" { __CVREDIRECT(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) }
#define __CVREDIRECT_DOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) extern "C++" { __CVREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) }
#define __CVREDIRECT_KOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) extern "C++" { __CVREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) }
#define __CVREDIRECT_VOID_GCCNCX(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)       extern "C++" { __CVREDIRECT_VOID(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) }
#define __CVREDIRECT_VOID_DOS_GCCNCX(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   extern "C++" { __CVREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) }
#define __CVREDIRECT_VOID_KOS_GCCNCX(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes)   extern "C++" { __CVREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,args,before_va_start,varcount,vartypes) }
#define __CVFREDIRECT_GCCNCX(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern "C++" { __CVFREDIRECT(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) }
#define __CVFREDIRECT_DOS_GCCNCX(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern "C++" { __CVFREDIRECT_DOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) }
#define __CVFREDIRECT_KOS_GCCNCX(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern "C++" { __CVFREDIRECT_KOS(attr,Treturn,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) }
#define __CVFREDIRECT_VOID_GCCNCX(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start)    extern "C++" { __CVFREDIRECT_VOID(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) }
#define __CVFREDIRECT_VOID_DOS_GCCNCX(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern "C++" { __CVFREDIRECT_VOID_DOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) }
#define __CVFREDIRECT_VOID_KOS_GCCNCX(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) extern "C++" { __CVFREDIRECT_VOID_KOS(attr,nothrow,name,paramf,asmnamef,vparamf,vasmnamef,args,before_va_start) }
#define __CXREDIRECT_GCCNCX(attr,Treturn,nothrow,name,param,asmname,code)                                      extern "C++" { __CXREDIRECT(attr,Treturn,nothrow,name,param,asmname,code) }
#define __CXREDIRECT_DOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,code)                                  extern "C++" { __CXREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,code) }
#define __CXREDIRECT_KOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,code)                                  extern "C++" { __CXREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,code) }
#define __CXREDIRECT_VOID_GCCNCX(attr,nothrow,name,param,asmname,code)                                         extern "C++" { __CXREDIRECT_VOID(attr,nothrow,name,param,asmname,code) }
#define __CXREDIRECT_VOID_DOS_GCCNCX(attr,nothrow,name,param,asmname,code)                                     extern "C++" { __CXREDIRECT_VOID_DOS(attr,nothrow,name,param,asmname,code) }
#define __CXREDIRECT_VOID_KOS_GCCNCX(attr,nothrow,name,param,asmname,code)                                     extern "C++" { __CXREDIRECT_VOID_KOS(attr,nothrow,name,param,asmname,code) }
#ifdef __PREPROCESSOR_HAVE_VA_ARGS
#define __CEIDECLARE_GCCNCX(attr,Treturn,nothrow,name,param,...)                                               extern "C++" { __CEIREDIRECT(attr,Treturn,nothrow,name,param,name,__VA_ARGS__) }
#define __CEIDECLARE_DOS_GCCNCX(attr,Treturn,nothrow,name,param,...)                                           extern "C++" { __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,name,__VA_ARGS__) }
#define __CEIDECLARE_KOS_GCCNCX(attr,Treturn,nothrow,name,param,...)                                           extern "C++" { __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,name,__VA_ARGS__) }
#define __CEIREDIRECT_GCCNCX(attr,Treturn,nothrow,name,param,asmname,...)                                      extern "C++" { __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,__VA_ARGS__) }
#define __CEIREDIRECT_DOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,...)                                  extern "C++" { __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,__VA_ARGS__) }
#define __CEIREDIRECT_KOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,...)                                  extern "C++" { __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,__VA_ARGS__) }
#elif defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __CEIDECLARE_GCCNCX(attr,Treturn,nothrow,name,param,inline_impl...)                                    extern "C++" { __CEIREDIRECT(attr,Treturn,nothrow,name,param,name,inline_impl) }
#define __CEIDECLARE_DOS_GCCNCX(attr,Treturn,nothrow,name,param,inline_impl...)                                extern "C++" { __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,name,inline_impl) }
#define __CEIDECLARE_KOS_GCCNCX(attr,Treturn,nothrow,name,param,inline_impl...)                                extern "C++" { __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,name,inline_impl) }
#define __CEIREDIRECT_GCCNCX(attr,Treturn,nothrow,name,param,asmname,inline_impl...)                           extern "C++" { __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl) }
#define __CEIREDIRECT_DOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,inline_impl...)                       extern "C++" { __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) }
#define __CEIREDIRECT_KOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,inline_impl...)                       extern "C++" { __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) }
#else /* ... */
#define __CEIDECLARE_GCCNCX(attr,Treturn,nothrow,name,param,inline_impl)                                       extern "C++" { __CEIREDIRECT(attr,Treturn,nothrow,name,param,name,inline_impl) }
#define __CEIDECLARE_DOS_GCCNCX(attr,Treturn,nothrow,name,param,inline_impl)                                   extern "C++" { __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,name,inline_impl) }
#define __CEIDECLARE_KOS_GCCNCX(attr,Treturn,nothrow,name,param,inline_impl)                                   extern "C++" { __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,name,inline_impl) }
#define __CEIREDIRECT_GCCNCX(attr,Treturn,nothrow,name,param,asmname,inline_impl)                              extern "C++" { __CEIREDIRECT(attr,Treturn,nothrow,name,param,asmname,inline_impl) }
#define __CEIREDIRECT_DOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,inline_impl)                          extern "C++" { __CEIREDIRECT_DOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) }
#define __CEIREDIRECT_KOS_GCCNCX(attr,Treturn,nothrow,name,param,asmname,inline_impl)                          extern "C++" { __CEIREDIRECT_KOS(attr,Treturn,nothrow,name,param,asmname,inline_impl) }
#endif /* !... */
#else /* __COMPILER_HAVE_GCCNCX_BUILTIN_BUG */
#define __CASMNAME_GCCNCX             __CASMNAME
#define __CASMNAME_DOS_GCCNCX         __CASMNAME_DOS
#define __CASMNAME_KOS_GCCNCX         __CASMNAME_KOS
#define __CASMNAME_SAME_GCCNCX        __CASMNAME_SAME
#define __CASMNAME_DOS_SAME_GCCNCX    __CASMNAME_DOS_SAME
#define __CASMNAME_KOS_SAME_GCCNCX    __CASMNAME_KOS_SAME
#define __CDECLARE_GCCNCX             __CDECLARE
#define __CDECLARE_VOID_GCCNCX        __CDECLARE_VOID
#define __CREDIRECT_GCCNCX            __CREDIRECT
#define __CREDIRECT_DOS_GCCNCX        __CREDIRECT_DOS
#define __CREDIRECT_KOS_GCCNCX        __CREDIRECT_KOS
#define __CREDIRECT_VOID_GCCNCX       __CREDIRECT_VOID
#define __CREDIRECT_VOID_DOS_GCCNCX   __CREDIRECT_VOID_DOS
#define __CREDIRECT_VOID_KOS_GCCNCX   __CREDIRECT_VOID_KOS
#define __CVREDIRECT_GCCNCX           __CVREDIRECT
#define __CVREDIRECT_DOS_GCCNCX       __CVREDIRECT_DOS
#define __CVREDIRECT_KOS_GCCNCX       __CVREDIRECT_KOS
#define __CVREDIRECT_VOID_GCCNCX      __CVREDIRECT_VOID
#define __CVREDIRECT_VOID_DOS_GCCNCX  __CVREDIRECT_VOID_DOS
#define __CVREDIRECT_VOID_KOS_GCCNCX  __CVREDIRECT_VOID_KOS
#define __CVFREDIRECT_GCCNCX          __CVFREDIRECT
#define __CVFREDIRECT_DOS_GCCNCX      __CVFREDIRECT_DOS
#define __CVFREDIRECT_KOS_GCCNCX      __CVFREDIRECT_KOS
#define __CVFREDIRECT_VOID_GCCNCX     __CVFREDIRECT_VOID
#define __CVFREDIRECT_VOID_DOS_GCCNCX __CVFREDIRECT_VOID_DOS
#define __CVFREDIRECT_VOID_KOS_GCCNCX __CVFREDIRECT_VOID_KOS
#define __CXREDIRECT_GCCNCX           __CXREDIRECT
#define __CXREDIRECT_DOS_GCCNCX       __CXREDIRECT_DOS
#define __CXREDIRECT_KOS_GCCNCX       __CXREDIRECT_KOS
#define __CXREDIRECT_VOID_GCCNCX      __CXREDIRECT_VOID
#define __CXREDIRECT_VOID_DOS_GCCNCX  __CXREDIRECT_VOID_DOS
#define __CXREDIRECT_VOID_KOS_GCCNCX  __CXREDIRECT_VOID_KOS
#define __CEIDECLARE_GCCNCX           __CEIDECLARE
#define __CEIDECLARE_DOS_GCCNCX       __CEIDECLARE_DOS
#define __CEIDECLARE_KOS_GCCNCX       __CEIDECLARE_KOS
#define __CEIREDIRECT_GCCNCX          __CEIREDIRECT
#define __CEIREDIRECT_DOS_GCCNCX      __CEIREDIRECT_DOS
#define __CEIREDIRECT_KOS_GCCNCX      __CEIREDIRECT_KOS
#endif /* !__COMPILER_HAVE_GCCNCX_BUILTIN_BUG */

#ifdef __LCLINT__
#define __CDECLARE_OPT             __CDECLARE
#define __CDECLARE_VOID_OPT        __CDECLARE_VOID
#define __CDECLARE_GCCNCX_OPT      __CDECLARE_GCCNCX
#define __CDECLARE_VOID_GCCNCX_OPT __CDECLARE_VOID_GCCNCX
#elif defined(__PREPROCESSOR_HAVE_VA_ARGS) || defined(__PREPROCESSOR_HAVE_NAMED_VA_ARGS)
#define __PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_ ,
#define __PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_1 ,
#define __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG(x) __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG_IMPL x
#ifdef __TINYC__
#define __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED2(...) __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED(x) __PRIVATE_CDECLARE_OPT_IS_DEFINED2(__PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_##x)
#elif defined(__PREPROCESSOR_HAVE_VA_ARGS)
#define __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG_IMPL(x, val, ...) val
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED3(...) __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG((__VA_ARGS__ 1,0))
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED2(...) __PRIVATE_CDECLARE_OPT_IS_DEFINED3(__PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_##__VA_ARGS__)
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED(x) __PRIVATE_CDECLARE_OPT_IS_DEFINED2(x)
#else /* __PREPROCESSOR_HAVE_VA_ARGS */
#define __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG_IMPL(x, val, a...) val
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED3(a...) __PRIVATE_CDECLARE_OPT_TAKE_SECOND_ARG((a 1,0))
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED2(x...) __PRIVATE_CDECLARE_OPT_IS_DEFINED3(__PRIVATE_CDECLARE_OPT_ARG_PLACEHOLDER_##x)
#define __PRIVATE_CDECLARE_OPT_IS_DEFINED(x) __PRIVATE_CDECLARE_OPT_IS_DEFINED2(x)
#endif /* !__PREPROCESSOR_HAVE_VA_ARGS */

#define __PRIVATE_CDECLARE_OPT_0(attr,Treturn,nothrow,name,param,args)
#define __PRIVATE_CDECLARE_OPT_1 __CDECLARE
#ifdef _MSC_VER
#define __PRIVATE_CDECLARE_OPT3(is) __PRIVATE_CDECLARE_OPT_##is
#define __PRIVATE_CDECLARE_OPT2(is) __PRIVATE_CDECLARE_OPT3(is)
#else /* _MSC_VER */
#define __PRIVATE_CDECLARE_OPT2(is) __PRIVATE_CDECLARE_OPT_##is
#endif /* !_MSC_VER */
#define __PRIVATE_CDECLARE_OPT(is) __PRIVATE_CDECLARE_OPT2(is)
#define __PRIVATE_CDECLARE_VOID_OPT_0(attr,nothrow,name,param,args)
#define __PRIVATE_CDECLARE_VOID_OPT_1 __CDECLARE_VOID
#ifdef _MSC_VER
#define __PRIVATE_CDECLARE_VOID_OPT3(is) __PRIVATE_CDECLARE_VOID_OPT_##is
#define __PRIVATE_CDECLARE_VOID_OPT2(is) __PRIVATE_CDECLARE_VOID_OPT3(is)
#else /* _MSC_VER */
#define __PRIVATE_CDECLARE_VOID_OPT2(is) __PRIVATE_CDECLARE_VOID_OPT_##is
#endif /* !_MSC_VER */
#define __PRIVATE_CDECLARE_VOID_OPT(is) __PRIVATE_CDECLARE_VOID_OPT2(is)

#define __PRIVATE_CDECLARE_GCCNCX_OPT_0(attr,Treturn,nothrow,name,param,args)
#define __PRIVATE_CDECLARE_GCCNCX_OPT_1 __CDECLARE_GCCNCX
#ifdef _MSC_VER
#define __PRIVATE_CDECLARE_GCCNCX_OPT3(is) __PRIVATE_CDECLARE_GCCNCX_OPT_##is
#define __PRIVATE_CDECLARE_GCCNCX_OPT2(is) __PRIVATE_CDECLARE_GCCNCX_OPT3(is)
#else /* _MSC_VER */
#define __PRIVATE_CDECLARE_GCCNCX_OPT2(is) __PRIVATE_CDECLARE_GCCNCX_OPT_##is
#endif /* !_MSC_VER */
#define __PRIVATE_CDECLARE_GCCNCX_OPT(is) __PRIVATE_CDECLARE_GCCNCX_OPT2(is)
#define __PRIVATE_CDECLARE_VOID_GCCNCX_OPT_0(attr,nothrow,name,param,args)
#define __PRIVATE_CDECLARE_VOID_GCCNCX_OPT_1 __CDECLARE_VOID_GCCNCX
#ifdef _MSC_VER
#define __PRIVATE_CDECLARE_VOID_GCCNCX_OPT3(is) __PRIVATE_CDECLARE_VOID_GCCNCX_OPT_##is
#define __PRIVATE_CDECLARE_VOID_GCCNCX_OPT2(is) __PRIVATE_CDECLARE_VOID_GCCNCX_OPT3(is)
#else /* _MSC_VER */
#define __PRIVATE_CDECLARE_VOID_GCCNCX_OPT2(is) __PRIVATE_CDECLARE_VOID_GCCNCX_OPT_##is
#endif /* !_MSC_VER */
#define __PRIVATE_CDECLARE_VOID_GCCNCX_OPT(is) __PRIVATE_CDECLARE_VOID_GCCNCX_OPT2(is)

/* Same as the _OPT-less counterpart, only these macros
 * integrate the test for `defined(__CRT_HAVE_<name>)',
 * meaning that the caller won't have to do that check. */
#define __CDECLARE_OPT(attr,Treturn,nothrow,name,param,args) \
	__PRIVATE_CDECLARE_OPT(__PRIVATE_CDECLARE_OPT_IS_DEFINED(__CRT_HAVE_##name))(attr,Treturn,nothrow,name,param,args)
#define __CDECLARE_VOID_OPT(attr,nothrow,name,param,args) \
	__PRIVATE_CDECLARE_VOID_OPT(__PRIVATE_CDECLARE_OPT_IS_DEFINED(__CRT_HAVE_##name))(attr,nothrow,name,param,args)
#define __CDECLARE_GCCNCX_OPT(attr,Treturn,nothrow,name,param,args) \
	__PRIVATE_CDECLARE_GCCNCX_OPT(__PRIVATE_CDECLARE_OPT_IS_DEFINED(__CRT_HAVE_##name))(attr,Treturn,nothrow,name,param,args)
#define __CDECLARE_VOID_GCCNCX_OPT(attr,nothrow,name,param,args) \
	__PRIVATE_CDECLARE_VOID_GCCNCX_OPT(__PRIVATE_CDECLARE_OPT_IS_DEFINED(__CRT_HAVE_##name))(attr,nothrow,name,param,args)
#endif /* __PREPROCESSOR_HAVE_VA_ARGS || __PREPROCESSOR_HAVE_NAMED_VA_ARGS */


#ifdef __CC__
/* Figure  out  where  unreachable  code  locations  are  originating   from.
 * Without this, GCC  (rightfully) likes  to make use  of undefined  behavior
 * when it  comes to  unreachable locations  in order  better optimize  code.
 * However, this  makes debugging  much harder  than it  needs to  be, so  to
 * make our lives a bit easier, provide a functions that gets called in these
 * situations, with the equivalent effect of `abort()' and `std::terminate()' */
#if (!defined(NDEBUG) && !defined(NDEBUG_UNREACHABLE) && \
     defined(__CRT_HAVE___ubsan_handle_builtin_unreachable))
/* XXX: Don't do this if user already passed `-fsanitize=unreachable' */
__DECL_BEGIN
__CDECLARE_VOID(__ATTR_NORETURN,,__ubsan_handle_builtin_unreachable,(void),())
__DECL_END
#undef __builtin_unreachable
#if __has_builtin(__builtin_unreachable)
#define __builtin_unreachable() (__ubsan_handle_builtin_unreachable(), __builtin_unreachable())
#else /* __has_builtin(__builtin_unreachable) */
#define __builtin_unreachable() __ubsan_handle_builtin_unreachable()
#endif /* !__has_builtin(__builtin_unreachable) */
#endif /* __BUILDING_LIBC || __CRT_HAVE___ubsan_handle_builtin_unreachable */
#endif /* __CC__ */

/* Include __stub_XXX definitions (checked by configure scripts) */
#if defined(__CRT_KOS) && !defined(__CRT_KOS_KERNEL)
#include <gnu/stubs.h>
/* Even  though  they're implemented,  indicate that  the "invalid_parameter_handler"
 * system is a stub. -- Some 3rd party programs check for presence of these functions
 * and think that when they're present, they're to configure themselves for  windows. */
#define __stub__set_invalid_parameter_handler
#define __stub__get_invalid_parameter_handler
#endif /* __CRT_KOS && !__CRT_KOS_KERNEL */

/* Configure SSP *_chk bindings
 * NOTE: SSP requires compiler support in the form of `__builtin_object_size()'
 *       If  this  builtin  isn't  available,  SSP  is  disabled  in   headers! */
#ifdef __SSP_FORTIFY_LEVEL
#if (__SSP_FORTIFY_LEVEL + 0) > 0
#if !__has_builtin(__builtin_object_size)
/*[[[warning(warn("__SSP_FORTIFY_LEVEL enabled, but `__builtin_object_size()' not supported"))]]]*/
#ifndef __NO_WARNINGS
#ifdef __PREPROCESSOR_HAVE_WARNING
#warning "__SSP_FORTIFY_LEVEL enabled, but `__builtin_object_size()' not supported"
#elif defined(__PREPROCESSOR_HAVE_PRAGMA_WARNING)
#pragma warning("__SSP_FORTIFY_LEVEL enabled, but `__builtin_object_size()' not supported")
#endif /* ... */
#endif /* !__NO_WARNINGS */
/*[[[end]]]*/
#undef __SSP_FORTIFY_LEVEL
#endif /* !__has_builtin(__builtin_object_size) */
#else /* __SSP_FORTIFY_LEVEL > 0 */
#undef __SSP_FORTIFY_LEVEL
#endif /* __SSP_FORTIFY_LEVEL <= 0 */
#endif /* __SSP_FORTIFY_LEVEL */

#endif /* !___CRT_H */
