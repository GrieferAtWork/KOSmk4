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
#ifndef __GUARD_HYBRID_HOST_H
#define __GUARD_HYBRID_HOST_H 1

#include "../__stdinc.h"

#if !defined(__x86_64__) && \
    (defined(__amd64__) || defined(__amd64) || \
     defined(__x86_64) || defined(_M_X64) || \
     defined(_M_AMD64) || defined(_WIN64) || \
     defined(WIN64))
#define __x86_64__ 1
#endif /* x86_64... */

#if !defined(__i386__) && \
    (defined(__i386) || defined(i386) || \
     defined(__I86__) || defined(_M_IX86) || \
     defined(__X86__) || defined(_X86_) || \
     defined(__THW_INTEL__) || defined(__INTEL__))
#define __i386__   1
#endif /* i386... */

#ifdef _M_IX86
#if !defined(__i486__) && _M_IX86 >= 400
#define __i486__ 1
#endif
#if !defined(__i586__) && _M_IX86 >= 500
#define __i586__ 1
#endif
#if !defined(__i686__) && _M_IX86 >= 600
#define __i686__ 1
#endif
#endif /* _M_IX86 */

#if !defined(__arm__) && \
    (defined(_M_ARM) || defined(_M_ARMT) || defined(_M_ARM_NT))
#define __arm__ 1
#endif

#undef __ARCH_STACK_GROWS_DOWNWARDS
#undef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#if defined(__i386__) || defined(__x86_64__)
#define __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS 1
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#elif defined(__arm__)
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#else
#define __ARCH_STACK_GROWS_DOWNWARDS 1
#endif


#endif /* !__GUARD_HYBRID_HOST_H */
