/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_HOST_H
#define __GUARD_HYBRID_HOST_H 1

#include "../__stdinc.h"

/************************************************************************/
/* COMPILER OPTIONS                                                     */
/************************************************************************/
#if (!defined(__pic__) && \
     (defined(__PIC__) || defined(__PIE__) || defined(__pie__)))
#define __pic__ 1 /* PositionIndependentCode (try to minimize relocations) */
#endif /* __pic__... */


/************************************************************************/
/* OS / ABI                                                             */
/************************************************************************/
#if (!defined(__DJGPP__) && \
     (defined(__DJGPP) || defined(DJGPP)))
#ifdef __DJGPP
#define __DJGPP__ __DJGPP
#else /* __DJGPP */
#define __DJGPP__ DJGPP
#endif /* !__DJGPP */
#endif /* __DJGPP__... */
#if (!defined(__MSDOS__) && \
     (defined(__MSDOS) || defined(MSDOS) || defined(__DJGPP__)))
#define __MSDOS__ 1
#endif /* __MSDOS__... */
#if (!defined(_WIN64) &&                                          \
     (defined(WIN64) || defined(__WIN64) || defined(__WIN64__) || \
      defined(__MINGW64__)))
#define _WIN64 1
#endif /* _WIN64... */
#if (!defined(_WIN32) && \
     (defined(WIN32) || defined(__WIN32) || defined(__WIN32__)))
#define _WIN32 1
#endif /* _WIN32... */
#if (!defined(_WIN16) && \
     (defined(WIN16) || defined(__WIN16) || defined(__WIN16__)))
#define _WIN16 1
#endif /* _WIN16... */
#if (!defined(__WINNT__) &&                                               \
     (defined(_WIN32) || defined(_WIN16) || defined(_WIN64) ||            \
      defined(__TOS_WIN__) || defined(__WINDOWS__) ||                     \
      (defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)) || \
      defined(_WIN32_WCE) || defined(WIN32_WCE) || defined(__WINNT) ||    \
      defined(WINNT) || defined(__MINGW32__) || defined(__CYGWIN__) ||    \
      defined(__CYGWIN32__)))
#define __WINNT__ 1
#endif /* __WINNT__... */
#if (!defined(__linux__) && \
     (defined(__linux) || defined(linux) || defined(__gnu_linux__)))
#define __linux__ 1
#endif /* __linux__... */
#if (!defined(__hpux__) && \
     (defined(__hpux) || defined(hpux)))
#define __hpux__ 1
#endif /* __hpux__... */
#if (!defined(__phoenix__) && \
     (defined(__phoenix) || defined(phoenix)))
#define __phoenix__ 1
#endif /* __phoenix__... */
#if (!defined(__unix__) &&                                                         \
     (defined(__unix) || defined(__unix) || defined(unix) || defined(__linux__) || \
      defined(__KOS__) || defined(__OpenBSD__) || defined(__FreeBSD__) ||          \
      defined(__NetBSD__) || defined(__uClinux__) || defined(__DragonFly__) ||     \
      defined(__gnu_hurd__) || defined(__GNU__) || defined(__hpux__) ||            \
      defined(__phoenix__)))
#define __unix__ 1
#endif /* __unix__... */


/************************************************************************/
/* CPU / ARCH                                                           */
/************************************************************************/
#if (!defined(__x86_64__) &&                    \
     (defined(__amd64__) || defined(__amd64) || \
      defined(amd64) || defined(__x86_64) ||    \
      defined(_M_X64) || defined(_M_AMD64) ||   \
      defined(_WIN64) || defined(WIN64)))
#define __x86_64__ 1
#endif /* __x86_64__... */

#if (!defined(__i686__) && \
     (defined(__i686) || defined(i686)))
#define __i686__ 1
#endif /* __i686__... */

#if (!defined(__i586__) && \
     (defined(__i586) || defined(i586)))
#define __i586__ 1
#endif /* __i586__... */

#if (!defined(__i486__) && \
     (defined(__i486) || defined(i486)))
#define __i486__ 1
#endif /* __i486__... */

#if (!defined(__i386__) &&                                          \
     (defined(__i386) || defined(i386) || defined(__i686__) ||      \
      defined(__i586__) || defined(__i486__) || defined(__I86__) || \
      defined(_M_IX86) || defined(__X86__) || defined(_X86_) ||     \
      defined(__THW_INTEL__) || defined(__INTEL__) || defined(__x86__)))
#define __i386__ 1
#endif /* __i386__... */

#ifdef _M_IX86
#if !defined(__i486__) && (_M_IX86 + 0) >= 400
#define __i486__ 1
#endif /* !__i486__ && _M_IX86 >= 400 */
#if !defined(__i586__) && (_M_IX86 + 0) >= 500
#define __i586__ 1
#endif /* !__i586__ && _M_IX86 >= 500 */
#if !defined(__i686__) && (_M_IX86 + 0) >= 600
#define __i686__ 1
#endif /* !__i686__ && _M_IX86 >= 600 */
#endif /* _M_IX86 */

#if (!defined(__bfin__) &&                                     \
     (defined(__bfin) || defined(bfin) || defined(__BFIN__) || \
      defined(__BFIN) || defined(BFIN)))
#define __bfin__ 1
#endif /* __bfin__... */

#if (!defined(__TMS320C6X__) && defined(_TMS320C6X))
#define __TMS320C6X__ 1
#endif /* __TMS320C6X__... */

#if (!defined(__csky__) && defined(__CSKY__))
#define __csky__ __CSKY__
#endif /* __csky__... */

#if (!defined(__ckcore__) && defined(__CKCORE__))
#define __ckcore__ __CKCORE__
#endif /* __ckcore__... */

#if (!defined(__aarch64__) && \
     (defined(__aarch64) || defined(__arm64__) || defined(__arm64)))
#define __aarch64__ 1
#endif /* __aarch64__... */

#if (!defined(__arm__) && \
     (defined(_M_ARM) || defined(_M_ARMT) || defined(_M_ARM_NT)))
#define __arm__ 1
#endif /* __arm__... */

#if (!defined(__alpha__) && \
     (defined(__alpha) || defined(__ALPHA)))
#define __alpha__ 1
#endif /* __alpha__... */

#if (!defined(__m32r__) && defined(__M32R__))
#define __m32r__ 1
#endif /* __m32r__... */

#if (!defined(__mcore__) && defined(__MCORE__))
#define __mcore__ 1
#endif /* __mcore__... */

#if (!defined(__microblaze__) && defined(__MICROBLAZE__))
#define __microblaze__ 1
#endif /* __microblaze__... */

#if (!defined(__mips64) &&                      \
     (defined(__R4000__) || defined(__R4000) || \
      defined(R4000) || defined(_R4000)))
#define __mips64 1
#endif /* __mips64... */

#if (!defined(__mips__) &&                                  \
     (defined(__mips) || defined(_mips) || defined(mips) || \
      defined(__mips64)))
#define __mips__ 1
#endif /* __mips__... */

#if (!defined(__m68k__) &&                          \
     (defined(__mc68000__) || defined(__mc68000) || \
      defined(mc68000) || defined(_M_M68K)))
#define __m68k__ 1
#endif /* __m68k__... */

#if (!defined(__ia64__) &&                                     \
     (defined(__ia64) || defined(ia64) || defined(__IA64__) || \
      defined(__IA64) || defined(__itanium__)))
#define __ia64__ 1
#endif /* __ia64__... */

#if (!defined(__fr30__) && (defined(__fr30) || defined(fr30)))
#define __fr30__ 1
#endif /* __fr30__... */

#if (!defined(__mmix__) && defined(__MMIX__))
#define __mmix__ 1
#endif /* __mmix__... */

#if (!defined(__mn10300__) && defined(__MN10300__))
#define __mn10300__ 1
#endif /* __mn10300__... */

#if (!defined(__nds32__) && defined(__NDS32__))
#define __nds32__ 1
#endif /* __nds32__... */

#if (!defined(__or1k__) && defined(__OR1K__))
#define __or1k__ 1
#endif /* __or1k__... */

#if (!defined(__hp800__) && (defined(__hp800) || defined(hp800)))
#define __hp800__ 1
#endif /* __hp800__... */

#if (!defined(__hp9000__) && (defined(__hp9000) || defined(hp9000)))
#define __hp9000__ 1
#endif /* __hp9000__... */

#if (!defined(__hp9000s700__) && defined(__hp9000s700))
#define __hp9000s700__ 1
#endif /* __hp9000s700__... */

#if (!defined(__hp9000s800__) &&                                  \
     (defined(hp9k8) || defined(__hp9k8) || defined(__hp9k8__) || \
      defined(__hp9000s800) || defined(hp9000s800)))
#define __hp9000s800__ 1
#endif /* __hp9000s800__... */

#if (!defined(__hppa__) &&                                     \
     (defined(__HPPA__) || defined(__hppa) || defined(hppa) || \
      defined(__hp800__) || defined(__hp9000__) ||             \
      defined(__hp9000s700__) || defined(__hp9000s800__)))
#define __hppa__ 1
#endif /* __hppa__... */

#if (!defined(__pdp11__) && \
     (defined(__pdp11) || defined(pdp11)))
#define __pdp11__ 1
#endif /* __pdp11__... */

#if (!defined(__xstormy16__) && \
     (defined(__xstormy16) || defined(xstormy16)))
#define __xstormy16__ 1
#endif /* __xstormy16__... */

#if (!defined(__vxworks) && defined(__VXWORKS__))
#define __vxworks 1
#endif /* __vxworks... */

#if (!defined(__xtensa__) && defined(__XTENSA__))
#define __xtensa__ 1
#endif /* __xtensa__... */

#if (!defined(__vms__) &&                   \
     (defined(__vms) || defined(__VMS__) || \
      defined(__VMS) /*|| defined(vms) || defined(VMS)*/))
#define __vms__ 1
#endif /* __vms__... */

#if (!defined(__v850__) && defined(__v850))
#define __v850__ 1
#endif /* __v850__... */

#if (!defined(__nios2__) &&                 \
     (defined(__nios2) || defined(nios2) || \
      defined(__NIOS2__) || defined(__NIOS2) || defined(NIOS2)))
#define __nios2__ 1
#endif /* __nios2__... */

#if (!defined(__moxie__) &&                 \
     (defined(__moxie) || defined(moxie) || \
      defined(__MOXIE__) || defined(__MOXIE) || defined(MOXIE)))
#define __moxie__ 1
#endif /* __moxie__... */

#if (!defined(__sparc_v9__) && \
     (defined(__sparcv9__) || defined(__sparcv9)))
#define __sparc_v9__ 1
#endif /* __sparc_v9__... */

#if (!defined(__sparc64__) &&                        \
     (defined(__sparc64) || defined(__sparc_v9__) || \
      (defined(__sparc__) && defined(__arch64__))))
#define __sparc64__ 1
#endif /* __sparc64__... */

#if (!defined(__sparc__) &&                        \
     (defined(__sparc) || defined(__sparc_v9__) || \
      defined(__sparc64__)))
#define __sparc__ 1
#if !defined(__sparc64__) && defined(__arch64__)
#define __sparc64__ 1
#endif /* !__sparc64__ && __arch64__ */
#endif /* __sparc__... */

#if (!defined(__powerpc__) &&                               \
     (defined(__powerpc) || defined(powerpc) ||             \
      defined(__PPC__) || defined(__PPC) || defined(PPC) || \
      defined(_M_PPC) || defined(__POWERPC__)))
#define __powerpc__ 1
#endif /* __powerpc__... */

#if (!defined(__powerpc64__) && defined(__PPC64__))
#define __powerpc64__ 1
#endif /* __powerpc64__... */


/************************************************************************/
/* PORTABLE ARCH FEATURES                                               */
/************************************************************************/
#undef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifdef _ALIGNMENT_REQUIRED
#if (_ALIGNMENT_REQUIRED + 0) == 0
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#endif /* _ALIGNMENT_REQUIRED */
#elif defined(__i386__) || defined(__x86_64__)
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#elif defined(__arm__) && defined(__ARM_FEATURE_UNALIGNED)
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#elif !defined(__KOS_SYSTEM_HEADERS__) && __has_include(<sys/isa_defs.h>)
#include <sys/isa_defs.h>
#if defined(_ALIGNMENT_REQUIRED) && (_ALIGNMENT_REQUIRED + 0) == 0
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#endif /* _ALIGNMENT_REQUIRED == 0 */
#endif /* ... */

#undef __ARCH_STACK_GROWS_UPWARDS
#undef __ARCH_STACK_GROWS_DOWNWARDS
#if defined(__i386__) || defined(__x86_64__)
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#elif defined(__arm__)
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#else /* ... */
#if !defined(__KOS_SYSTEM_HEADERS__) && __has_include(<sys/isa_defs.h>)
#include <sys/isa_defs.h>
#if defined(_STACK_GROWS_DOWNWARD) && !defined(_STACK_GROWS_UPWARD)
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#elif !defined(_STACK_GROWS_DOWNWARD) && defined(_STACK_GROWS_UPWARD)
#define __ARCH_STACK_GROWS_UPWARDS 1
#endif /* !_STACK_GROWS_DOWNWARD */
#endif /* ... */
#if !defined(__ARCH_STACK_GROWS_DOWNWARDS) && !defined(__ARCH_STACK_GROWS_UPWARDS)
#define __ARCH_STACK_GROWS_DOWNWARDS 1 /* Default assumption... */
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS && !__ARCH_STACK_GROWS_UPWARDS */
#endif /* !... */

#undef __ARCH_STACK_ALIGNMENT
#ifdef __x86_64__
#define __ARCH_STACK_ALIGNMENT 16
#elif defined(__aarch64__)
#define __ARCH_STACK_ALIGNMENT 16
#elif defined(__arm__)
#define __ARCH_STACK_ALIGNMENT 8
#elif defined(__i386__) && defined(__KOS__) && defined(__KERNEL__)
#define __ARCH_STACK_ALIGNMENT 4
#elif defined(__i386__)
#define __ARCH_STACK_ALIGNMENT 8
#endif /* ... */


/* The native PAGE size of the hosting arch (if known to be  constant)
 * Note that on some architectures, this value is not fixed, but is  a
 * run- or compile-time option of the hosting kernel and should not be
 * assumed to  be a  compile-time  constant by  user-space  processes.
 * This macro should only be defined in cases where this is _not_  the
 * case, and the PAGE size _is_ a fixed, architecture-defined constant
 * that cannot be changed. Otherwise, this macro mustn't get  defined! */
#ifndef __ARCH_PAGESIZE
#ifdef PAGESIZE
#define __ARCH_PAGESIZE PAGESIZE
#elif defined(PAGE_SIZE)
#define __ARCH_PAGESIZE PAGE_SIZE
#elif defined(__i386__) || defined(__x86_64__) || defined(__arm__)
#define __ARCH_PAGESIZE 4096
#endif /* ... */
#endif /* !__ARCH_PAGESIZE */


#endif /* !__GUARD_HYBRID_HOST_H */
