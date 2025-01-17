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
#ifndef _I386_KOS_KOS_BITS_EXCEPT_H
#define _I386_KOS_KOS_BITS_EXCEPT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#define __EXCEPT_REGISTER_STATE_TYPE_IS_KCPUSTATE
#ifdef __USE_KOS_KERNEL
#include <kos/kernel/cpu-state.h>
#define __EXCEPT_REGISTER_STATE_TYPE   struct kcpustate
#define __SIZEOF_EXCEPT_REGISTER_STATE SIZEOF_KCPUSTATE
#ifdef __x86_64__
#define __except_register_state_getpc(x)                       ((__BYTE_TYPE__ const *)(x)->kcs_rip)
#define __except_register_state_setpc(x, value)                (void)((x)->kcs_rip = (__u64)(value))
#define __except_register_state_getsp(x)                       ((__BYTE_TYPE__ const *)(x)->kcs_gpregs.gp_rsp)
#define __except_register_state_setsp(x, value)                (void)((x)->kcs_gpregs.gp_rsp = (__u64)(value))
#define __except_register_state_get_unwind_exception(x)        ((__BYTE_TYPE__ const *)(x)->kcs_gpregs.gp_rax)
#define __except_register_state_set_unwind_exception(x, value) (void)((x)->kcs_gpregs.gp_rax = (__u64)(value))
#else /* __x86_64__ */
#define __except_register_state_getpc(x)                       ((__BYTE_TYPE__ const *)(x)->kcs_eip)
#define __except_register_state_setpc(x, value)                (void)((x)->kcs_eip = (__u32)(value))
#define __except_register_state_getsp(x)                       ((__BYTE_TYPE__ const *)(x)->kcs_gpregs.gp_esp)
#define __except_register_state_setsp(x, value)                (void)((x)->kcs_gpregs.gp_esp = (__u32)(value))
#define __except_register_state_get_unwind_exception(x)        ((__BYTE_TYPE__ const *)(x)->kcs_gpregs.gp_eax)
#define __except_register_state_set_unwind_exception(x, value) (void)((x)->kcs_gpregs.gp_eax = (__u32)(value))
#endif /* !__x86_64__ */
#else /* __USE_KOS_KERNEL */
#include <hybrid/typecore.h>

#define __EXCEPT_REGISTER_STATE_TYPE   struct __except_register_state_type_struct
#ifdef __x86_64__
#define __SIZEOF_EXCEPT_REGISTER_STATE 144
#else /* __x86_64__ */
#define __SIZEOF_EXCEPT_REGISTER_STATE 40
#endif /* !__x86_64__ */
#ifdef __CC__
__DECL_BEGIN
/* NOTE: This structure share binary compatibility with `struct kcpustate'! */
struct __except_register_state_type_struct {
#ifdef __x86_64__
	__REGISTER_TYPE__ __ers_r15;    /* General purpose register #15 */
	__REGISTER_TYPE__ __ers_r14;    /* General purpose register #14 */
	__REGISTER_TYPE__ __ers_r13;    /* General purpose register #13 */
	__REGISTER_TYPE__ __ers_r12;    /* General purpose register #12 */
	__REGISTER_TYPE__ __ers_r11;    /* General purpose register #11 */
	__REGISTER_TYPE__ __ers_r10;    /* General purpose register #10 */
	__REGISTER_TYPE__ __ers_r9;     /* General purpose register #9 */
	__REGISTER_TYPE__ __ers_r8;     /* General purpose register #8 */
#endif /* __x86_64__ */
	__REGISTER_TYPE__ __ers_pdi;    /* Destination pointer */
	__REGISTER_TYPE__ __ers_psi;    /* Source pointer */
	__REGISTER_TYPE__ __ers_pbp;    /* Frame base pointer */
	__REGISTER_TYPE__ __ers_psp;    /* Stack pointer */
	__REGISTER_TYPE__ __ers_pbx;    /* Base register */
	__REGISTER_TYPE__ __ers_pdx;    /* Data register */
	__REGISTER_TYPE__ __ers_pcx;    /* Count register */
	__REGISTER_TYPE__ __ers_pax;    /* Accumulator register */
	__REGISTER_TYPE__ __ers_pflags; /* Flags register */
	__REGISTER_TYPE__ __ers_pip;    /* Instruction pointer */
};
__DECL_END
#define __except_register_state_getpc(x)                       ((__BYTE_TYPE__ const *)(x)->__ers_pip)
#define __except_register_state_setpc(x, value)                (void)((x)->__ers_pip = (__REGISTER_TYPE__)(value))
#define __except_register_state_getsp(x)                       ((__BYTE_TYPE__ const *)(x)->__ers_psp)
#define __except_register_state_setsp(x, value)                (void)((x)->__ers_psp = (__REGISTER_TYPE__)(value))
#define __except_register_state_get_unwind_exception(x)        ((__BYTE_TYPE__ const *)(x)->__ers_pax)
#define __except_register_state_set_unwind_exception(x, value) (void)((x)->__ers_pax = (__REGISTER_TYPE__)(value))
#endif /* __CC__ */
#endif /* !__USE_KOS_KERNEL */


#endif /* !_I386_KOS_KOS_BITS_EXCEPT_H */
