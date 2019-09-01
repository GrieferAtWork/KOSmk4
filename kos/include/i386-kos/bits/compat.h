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
#ifndef _I386_KOS_BITS_COMPAT_H
#define _I386_KOS_BITS_COMPAT_H 1

#include <__stdinc.h>
#include <hybrid/host.h>
/* Compatibility mode definitions */

#undef __ARCH_HAVE_COMPAT
#ifdef __x86_64__
#include <hybrid/typecore.h>
#include <hybrid/__pointer.h>

#define __ARCH_HAVE_COMPAT 1
#define __ARCH_COMPAT_FUNCPTR(return, cc, name, args) __HYBRID_FUNCPTR32(return, cc, name, args)
#define __ARCH_COMPAT_PTR(T) __HYBRID_PTR32(T)
#define __ARCH_COMPAT_SIZEOF_POINTER 4
#define __ARCH_COMPAT_INTPTR_TYPE   __INT32_TYPE__
#define __ARCH_COMPAT_LONGPTR_TYPE  __LONG32_TYPE__
#define __ARCH_COMPAT_UINTPTR_TYPE  __UINT32_TYPE__
#define __ARCH_COMPAT_ULONGPTR_TYPE __ULONG32_TYPE__
#define __ARCH_COMPAT_SIZE_TYPE     __ULONG32_TYPE__
#define __ARCH_COMPAT_SSIZE_TYPE    __LONG32_TYPE__
#endif /* __x86_64__ */

#endif /* !_I386_KOS_BITS_COMPAT_H */
