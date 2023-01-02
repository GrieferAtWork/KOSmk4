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
#ifndef _I386_KOS_ASM_ISA_H
#define _I386_KOS_ASM_ISA_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

/* ISA codes. */
#if __SIZEOF_POINTER__ == 8
#define ISA_X86_64 0
#define ISA_I386   1
#elif __SIZEOF_POINTER__ == 4
#define ISA_I386 0
#ifndef __I386_NO_VM86
#define ISA_8086 1
#endif /* !__I386_NO_VM86 */
#elif __SIZEOF_POINTER__ == 2
#define ISA_8086 0
#endif /* !__x86_64__ */

/* Default ISA type. */
#if __SIZEOF_POINTER__ == 8 && defined(ISA_X86_64)
#define ISA_DEFAULT ISA_X86_64
#elif __SIZEOF_POINTER__ == 4 && defined(ISA_I386)
#define ISA_DEFAULT ISA_I386
#elif __SIZEOF_POINTER__ == 2 && defined(ISA_8086)
#define ISA_DEFAULT ISA_8086
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported __SIZEOF_POINTER__"
#endif /* __SIZEOF_POINTER__ != ... */


#ifdef __CC__
__DECL_BEGIN
typedef __UINT8_TYPE__ isa_t;
__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_ASM_ISA_H */
