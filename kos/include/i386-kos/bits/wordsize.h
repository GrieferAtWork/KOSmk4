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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_WORDSIZE_H
#define _I386_KOS_BITS_WORDSIZE_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#if defined(__x86_64__) && !defined(__ILP32__)
#   define __WORDSIZE 64
#elif defined(__x86_64__) || defined(__i386__)
#   define __WORDSIZE 32
#else
#   include <hybrid/typecore.h>
#if __SIZEOF_POINTER__ == 1
#   define __WORDSIZE 8
#elif __SIZEOF_POINTER__ == 2
#   define __WORDSIZE 16
#elif __SIZEOF_POINTER__ == 4
#   define __WORDSIZE 32
#elif __SIZEOF_POINTER__ == 8
#   define __WORDSIZE 64
#else
#   define __WORDSIZE (__SIZEOF_POINTER__*8)
#endif
#endif

#ifdef __x86_64__
#   define __WORDSIZE_TIME64_COMPAT32 1
#   define __SYSCALL_WORDSIZE         64
#endif /* __x86_64__ */

#endif /* !_I386_KOS_BITS_WORDSIZE_H */
