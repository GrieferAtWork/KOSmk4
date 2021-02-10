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
#ifndef __GUARD_HYBRID_HOST_H
#define __GUARD_HYBRID_HOST_H 1

#include "../__stdinc.h"

#if (!defined(__x86_64__) &&                    \
     (defined(__amd64__) || defined(__amd64) || \
      defined(amd64) || defined(__x86_64) ||    \
      defined(_M_X64) || defined(_M_AMD64) ||   \
      defined(_WIN64) || defined(WIN64)))
#define __x86_64__ 1
#endif /* x86_64... */

#if (!defined(__i386__) &&                    \
     (defined(__i386) || defined(i386) ||     \
      defined(__I86__) || defined(_M_IX86) || \
      defined(__X86__) || defined(_X86_) ||   \
      defined(__THW_INTEL__) || defined(__INTEL__)))
#define __i386__ 1
#endif /* i386... */

#ifdef _M_IX86
#if !defined(__i486__) && _M_IX86 >= 400
#define __i486__ 1
#endif /* !__i486__ && _M_IX86 >= 400 */
#if !defined(__i586__) && _M_IX86 >= 500
#define __i586__ 1
#endif /* !__i586__ && _M_IX86 >= 500 */
#if !defined(__i686__) && _M_IX86 >= 600
#define __i686__ 1
#endif /* !__i686__ && _M_IX86 >= 600 */
#endif /* _M_IX86 */

#if (!defined(__arm__) && \
     (defined(_M_ARM) || defined(_M_ARMT) || defined(_M_ARM_NT)))
#define __arm__ 1
#endif /* __arm__... */

#if (!defined(__alpha__) && defined(__alpha))
#define __alpha__ 1
#endif /* __alpha__... */

#if (!defined(__ia64__) && (defined(__ia64) || defined(ia64)))
#define __ia64__ 1
#endif /* __ia64__... */

#if !defined(__sparc__) && defined(__sparc)
#define __sparc__ 1
#endif /* __sparc__... */

#if (!defined(__sparcv9__) && defined(__sparcv9))
#define __sparcv9__ 1
#endif /* __sparcv9__... */

#if (!defined(__sparc64__) &&                       \
     (defined(__sparc64) || defined(__sparcv9__) || \
      (defined(__sparc__) && defined(__arch64__))))
#define __sparc64__ 1
#endif /* __sparc64__... */

#undef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#ifdef _ALIGNMENT_REQUIRED
#if (_ALIGNMENT_REQUIRED + 0) == 0
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#endif /* _ALIGNMENT_REQUIRED */
#elif defined(__i386__) || defined(__x86_64__)
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#elif !defined(__KOS_SYSTEM_HEADERS__) && __has_include(<sys/isa_defs.h>)
#include <sys/isa_defs.h>
#if defined(_ALIGNMENT_REQUIRED) && (_ALIGNMENT_REQUIRED + 0) == 0
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#endif /* _ALIGNMENT_REQUIRED == 0 */
#endif /* ... */

#undef __ARCH_STACK_GROWS_DOWNWARDS
#if defined(__i386__) || defined(__x86_64__)
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#elif defined(__arm__)
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#else /* ... */
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#endif /* !... */

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
