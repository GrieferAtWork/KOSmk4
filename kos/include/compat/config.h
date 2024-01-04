/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _COMPAT_CONFIG_H
#define _COMPAT_CONFIG_H 1

#include <__stdinc.h>

/* Compatibility mode definitions would go here */

#undef __ARCH_HAVE_COMPAT
#if 0
#include <hybrid/__pointer.h>
#include <hybrid/typecore.h>

#define __ARCH_HAVE_COMPAT                            1
#define __ARCH_COMPAT_FUNCPTR(return, cc, name, args) __HYBRID_FUNCPTRnn(return, cc, name, args)
#define __ARCH_COMPAT(x)                              x##nn

#define __ARCH_COMPAT_SIZEOF_POINTER nn
#define __ARCH_COMPAT_PTR(T)         __HYBRID_PTRnn(T)
#define __ARCH_COMPAT_INTPTR_TYPE    __INTnn_TYPE__
#define __ARCH_COMPAT_LONGPTR_TYPE   __LONGnn_TYPE__
#define __ARCH_COMPAT_UINTPTR_TYPE   __UINTnn_TYPE__
#define __ARCH_COMPAT_ULONGPTR_TYPE  __ULONGnn_TYPE__

#define __ARCH_COMPAT_SIZEOF_REGISTER nn
#define __ARCH_COMPAT_REGISTER_T      __ULONGnn_TYPE__
#define __ARCH_COMPAT_SREGISTER_T     __LONGnn_TYPE__

#define __ARCH_COMPAT_SIZEOF_SIZE_T    nn
#define __ARCH_COMPAT_SIZEOF_PTRDIFF_T nn
#define __ARCH_COMPAT_SIZE_T           __ULONGnn_TYPE__
#define __ARCH_COMPAT_SSIZE_T          __LONGnn_TYPE__
#define __ARCH_COMPAT_PTRDIFF_T        __LONGnn_TYPE__

#define __ARCH_COMPAT_SIZEOF_SHORT nn
#define __ARCH_COMPAT_SHORT        __INTnn_TYPE__
#define __ARCH_COMPAT_USHORT       __UINTnn_TYPE__

#define __ARCH_COMPAT_SIZEOF_INT nn
#define __ARCH_COMPAT_INT        __INTnn_TYPE__
#define __ARCH_COMPAT_UINT       __UINTnn_TYPE__

#define __ARCH_COMPAT_SIZEOF_LONG nn
#define __ARCH_COMPAT_LONG        __LONGnn_TYPE__
#define __ARCH_COMPAT_ULONG       __ULONGnn_TYPE__

#define __ARCH_COMPAT_SIZEOF_LLONG nn
#define __ARCH_COMPAT_LLONG        __LONGnn_TYPE__
#define __ARCH_COMPAT_ULLONG       __ULONGnn_TYPE__

#endif

#endif /* !_COMPAT_CONFIG_H */
