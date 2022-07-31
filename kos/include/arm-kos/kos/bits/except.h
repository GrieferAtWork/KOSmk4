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
#ifndef _ARM_KOS_KOS_BITS_EXCEPT_H
#define _ARM_KOS_KOS_BITS_EXCEPT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

/* Due to aliasing, all of the following are true */
#define __EXCEPT_REGISTER_STATE_TYPE_IS_UCPUSTATE
#define __EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE
#define __EXCEPT_REGISTER_STATE_TYPE_IS_ICPUSTATE
#define __EXCEPT_REGISTER_STATE_TYPE_IS_SCPUSTATE
#define __EXCEPT_REGISTER_STATE_TYPE_IS_FCPUSTATE

#ifdef __USE_KOS_KERNEL
#include <kos/kernel/cpu-state.h>
#define __EXCEPT_REGISTER_STATE_TYPE                               struct ucpustate
#define __SIZEOF_EXCEPT_REGISTER_STATE                             SIZEOF_UCPUSTATE
#define __EXCEPT_REGISTER_STATE_TYPE_RDPC(x)                       ((__BYTE_TYPE__ const *)(x).ucs_pc)
#define __EXCEPT_REGISTER_STATE_TYPE_WRPC(x, value)                ((x).ucs_pc = (__UINT32_TYPE__)(value))
#define __EXCEPT_REGISTER_STATE_TYPE_RDSP(x)                       ((__BYTE_TYPE__ const *)(x).ucs_sp)
#define __EXCEPT_REGISTER_STATE_TYPE_WRSP(x, value)                ((x).ucs_sp = (__UINT32_TYPE__)(value))
#define __EXCEPT_REGISTER_STATE_TYPE_RD_UNWIND_EXCEPTION(x)        ((__BYTE_TYPE__ const *)(x).ucs_r0) /* TODO: Check if this is correct! */
#define __EXCEPT_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(x, value) ((x).ucs_r0 = (__UINT32_TYPE__)(value))
#else /* __USE_KOS_KERNEL */
#include <hybrid/typecore.h>

#define __EXCEPT_REGISTER_STATE_TYPE   struct __except_register_state_type_struct
#define __SIZEOF_EXCEPT_REGISTER_STATE 40
#ifdef __CC__
__DECL_BEGIN
/* NOTE: This structure share binary compatibility with `struct kcpustate'! */
struct __except_register_state_type_struct {
	__UINT32_TYPE__ __ers_r0;   /* r0 */
	__UINT32_TYPE__ __ers_r1;   /* r1 */
	__UINT32_TYPE__ __ers_r2;   /* r2 */
	__UINT32_TYPE__ __ers_r3;   /* r3 */
	__UINT32_TYPE__ __ers_r4;   /* r4 */
	__UINT32_TYPE__ __ers_r5;   /* r5 */
	__UINT32_TYPE__ __ers_r6;   /* r6 */
	__UINT32_TYPE__ __ers_r7;   /* r7 */
	__UINT32_TYPE__ __ers_r8;   /* r8 */
	__UINT32_TYPE__ __ers_r9;   /* r9 */
	__UINT32_TYPE__ __ers_r10;  /* r10 */
	__UINT32_TYPE__ __ers_r11;  /* r11 */
	__UINT32_TYPE__ __ers_r12;  /* r12 */
	__UINT32_TYPE__ __ers_sp;   /* r13 */
	__UINT32_TYPE__ __ers_lr;   /* r14 */
	__UINT32_TYPE__ __ers_pc;   /* r15 */
	__UINT32_TYPE__ __ers_cpsr; /* CurrentProgramStatusRegister */
};
__DECL_END
#define __EXCEPT_REGISTER_STATE_TYPE_RDPC(x)                       ((__BYTE_TYPE__ const *)(x).__ers_pc)
#define __EXCEPT_REGISTER_STATE_TYPE_WRPC(x, value)                ((x).__ers_pc = (__UINT32_TYPE__)(value))
#define __EXCEPT_REGISTER_STATE_TYPE_RDSP(x)                       ((__BYTE_TYPE__ const *)(x).__ers_sp)
#define __EXCEPT_REGISTER_STATE_TYPE_WRSP(x, value)                ((x).__ers_sp = (__UINT32_TYPE__)(value))
#define __EXCEPT_REGISTER_STATE_TYPE_RD_UNWIND_EXCEPTION(x)        ((__BYTE_TYPE__ const *)(x).__ers_r0) /* TODO: Check if this is correct! */
#define __EXCEPT_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(x, value) ((x).__ers_r0 = (__UINT32_TYPE__)(value))
#endif /* __CC__ */
#endif /* !__USE_KOS_KERNEL */


#endif /* !_ARM_KOS_KOS_BITS_EXCEPT_H */
