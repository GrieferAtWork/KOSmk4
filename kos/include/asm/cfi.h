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
#ifndef _ASM_CFI_H
#define _ASM_CFI_H 1

#include <__stdinc.h>

#include <hybrid/__asm.h>

#ifndef __COMPILER_NO_GCC_ASM_MACROS
__ASM_BEGIN

/* Decode register names and invoke `func' with the effective CFI register ID. */
__ASM_L(.macro __cfi_decode_register func:req, reg:req)
#if 0
#define __REGISTER_CASE(name,id) __ASM_L(.ifc __ASM_ARG(\reg),name; __ASM_ARG(\func) id; .else)
	__REGISTER_CASE(register_zero,0)
	__REGISTER_CASE(register_one,1)
	/* ... */
__ASM_L(	__ASM_ARG(\func) __ASM_ARG(\reg))
__ASM_L(	.endif;.endif)
#undef __REGISTER_CASE
#else
__ASM_L(	__ASM_ARG(\func) __ASM_ARG(\reg))
#endif
__ASM_L(.endm)

__ASM_END
#endif /* !__COMPILER_NO_GCC_ASM_MACROS */

#endif /* !_ASM_CFI_H */
