/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!ignore_unnecessary_include*/
#ifndef _I386_KOS_COMPAT_CONFIG_H
#define _I386_KOS_COMPAT_CONFIG_H 1

#include <__stdinc.h>

#include <hybrid/host.h> /* __x86_64__ */

/* Compatibility mode definitions */

#undef __ARCH_HAVE_COMPAT
#ifdef __x86_64__
#include <hybrid/__pointer.h>
#include <hybrid/typecore.h>

#define __ARCH_HAVE_COMPAT                            1
#define __ARCH_COMPAT_FUNCPTR(return, cc, name, args) __HYBRID_FUNCPTR32(return, cc, name, args)
#define __ARCH_COMPAT(x)                              x##32

#define __ARCH_COMPAT_SIZEOF_POINTER 4
#define __ARCH_COMPAT_PTR            __HYBRID_PTR32
#define __ARCH_COMPAT_INTPTR_TYPE    __INT32_TYPE__
#define __ARCH_COMPAT_LONGPTR_TYPE   __LONG32_TYPE__
#define __ARCH_COMPAT_UINTPTR_TYPE   __UINT32_TYPE__
#define __ARCH_COMPAT_ULONGPTR_TYPE  __ULONG32_TYPE__

#define __ARCH_COMPAT_SIZEOF_REGISTER 4
#define __ARCH_COMPAT_REGISTER_T      __ULONG32_TYPE__
#define __ARCH_COMPAT_SREGISTER_T     __LONG32_TYPE__

#define __ARCH_COMPAT_SIZEOF_SIZE_T    4
#define __ARCH_COMPAT_SIZEOF_PTRDIFF_T 4
#define __ARCH_COMPAT_SIZE_T           __ULONG32_TYPE__
#define __ARCH_COMPAT_SSIZE_T          __LONG32_TYPE__
#define __ARCH_COMPAT_PTRDIFF_T        __LONG32_TYPE__

#define __ARCH_COMPAT_SIZEOF_SHORT 2
#define __ARCH_COMPAT_SHORT        __INT16_TYPE__
#define __ARCH_COMPAT_USHORT       __UINT16_TYPE__

#define __ARCH_COMPAT_SIZEOF_INT 4
#define __ARCH_COMPAT_INT        __INT32_TYPE__
#define __ARCH_COMPAT_UINT       __UINT32_TYPE__

#define __ARCH_COMPAT_SIZEOF_LONG 4
#define __ARCH_COMPAT_LONG        __LONG32_TYPE__
#define __ARCH_COMPAT_ULONG       __ULONG32_TYPE__

#define __ARCH_COMPAT_SIZEOF_LLONG 8
#define __ARCH_COMPAT_LLONG        __LONG64_TYPE__
#define __ARCH_COMPAT_ULLONG       __ULONG64_TYPE__

#endif /* __x86_64__ */

#endif /* !_I386_KOS_COMPAT_CONFIG_H */
