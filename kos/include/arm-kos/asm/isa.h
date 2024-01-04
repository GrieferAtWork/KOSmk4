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
#ifndef _ARM_KOS_ASM_ISA_H
#define _ARM_KOS_ASM_ISA_H 1

#include <__stdinc.h>

/* Default ISA type. */
#define ISA_ARM   0
#define ISA_THUMB 1

#ifdef __thumb__ /* -mthumb */
#define ISA_DEFAULT ISA_ARM
#else /* __thumb__ */
#define ISA_DEFAULT ISA_THUMB
#endif /* !__thumb__ */


#ifdef __CC__
#include <hybrid/typecore.h>

__DECL_BEGIN
typedef __UINT8_TYPE__ isa_t;
__DECL_END
#endif /* __CC__ */

#endif /* !_ARM_KOS_ASM_ISA_H */
