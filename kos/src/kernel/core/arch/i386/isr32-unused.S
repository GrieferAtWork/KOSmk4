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
#ifdef __INTELLISENSE__
#include "isr32.S"
#define ISR_VECTOR 7f
#endif /* __INTELLISENSE__ */

INTERN_FUNCTION(PP_CAT2(__x86_defisr_, ISR_VECTOR_NAME))
	pushl_cfi  $(ISR_VECTOR_ID)
	PRIVATE(__x86_isr_unused_common)
	jmp     __x86_isr_unused_common
	.cfi_adjust_cfa_offset -4
END(PP_CAT2(__x86_defisr_, ISR_VECTOR_NAME))

#undef ISR_VECTOR
