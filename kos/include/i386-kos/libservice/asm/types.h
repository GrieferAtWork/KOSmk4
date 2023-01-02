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
#ifndef _I386_KOS_LIBSERVICE_ASM_TYPES_H
#define _I386_KOS_LIBSERVICE_ASM_TYPES_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#define SERVICE_TYPE_X86_64_R64 (_SERVICE_TYPE_ARCH_MIN + 0) /* 64-bit register / pushq */

/* Return the internal type used to represent a signed/unsigned integer of the given size. */
#define SERVICE_TYPE_INTn(sizeof)  SERVICE_TYPE_X86_64_R64
#define SERVICE_TYPE_UINTn(sizeof) SERVICE_TYPE_X86_64_R64
#else /* __x86_64__ */
#define SERVICE_TYPE_386_R32 (_SERVICE_TYPE_ARCH_MIN + 0) /* 32-bit register / pushl */
#define SERVICE_TYPE_386_R64 (_SERVICE_TYPE_ARCH_MIN + 1) /* 64-bit register / pushl*2 */

/* Return the internal type used to represent a signed/unsigned integer of the given size. */
#define SERVICE_TYPE_INTn(sizeof)  ((sizeof) >= 8 ? SERVICE_TYPE_386_R64 : SERVICE_TYPE_386_R32)
#define SERVICE_TYPE_UINTn(sizeof) ((sizeof) >= 8 ? SERVICE_TYPE_386_R64 : SERVICE_TYPE_386_R32)
#endif /* !__x86_64__ */


#endif /* !_I386_KOS_LIBSERVICE_ASM_TYPES_H */
