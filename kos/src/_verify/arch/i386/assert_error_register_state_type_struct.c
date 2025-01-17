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
#ifndef GUARD__VERIFY_ARCH_I386_ASSERT_EXCEPT_REGISTER_STATE_TYPE_STRUCT_C
#define GUARD__VERIFY_ARCH_I386_ASSERT_EXCEPT_REGISTER_STATE_TYPE_STRUCT_C 1

#include <features.h>
#undef __USE_KOS_KERNEL /* Mustn't be defined to get headers to use `struct __except_register_state_type_struct' */

/**/
#include <kos/bits/except.h>             /* struct __except_register_state_type_struct */
#include <kos/kernel/cpu-state-compat.h> /* gp_p..., kcs_Pflags, kcs_Pip */
#include <kos/kernel/cpu-state.h>        /* struct kcpustate */
/**/

#include <hybrid/host.h>

#include <assert.h>
#include <stddef.h>

/* Assert that `struct __except_register_state_type_struct' matches `struct kcpustate' */
#define ASSERT_SAME_OFFSET(escaped_field, kcpustate_field)                              \
	static_assert(offsetof(struct __except_register_state_type_struct, escaped_field) == \
	              offsetof(struct kcpustate, kcpustate_field))
#ifdef __x86_64__
ASSERT_SAME_OFFSET(__ers_r15, kcs_gpregs.gp_r15);
ASSERT_SAME_OFFSET(__ers_r14, kcs_gpregs.gp_r14);
ASSERT_SAME_OFFSET(__ers_r13, kcs_gpregs.gp_r13);
ASSERT_SAME_OFFSET(__ers_r12, kcs_gpregs.gp_r12);
ASSERT_SAME_OFFSET(__ers_r11, kcs_gpregs.gp_r11);
ASSERT_SAME_OFFSET(__ers_r10, kcs_gpregs.gp_r10);
ASSERT_SAME_OFFSET(__ers_r9, kcs_gpregs.gp_r9);
ASSERT_SAME_OFFSET(__ers_r8, kcs_gpregs.gp_r8);
#endif /* __x86_64__ */
ASSERT_SAME_OFFSET(__ers_pdi, kcs_gpregs.gp_Pdi);
ASSERT_SAME_OFFSET(__ers_psi, kcs_gpregs.gp_Psi);
ASSERT_SAME_OFFSET(__ers_pbp, kcs_gpregs.gp_Pbp);
ASSERT_SAME_OFFSET(__ers_psp, kcs_gpregs.gp_Psp);
ASSERT_SAME_OFFSET(__ers_pbx, kcs_gpregs.gp_Pbx);
ASSERT_SAME_OFFSET(__ers_pdx, kcs_gpregs.gp_Pdx);
ASSERT_SAME_OFFSET(__ers_pcx, kcs_gpregs.gp_Pcx);
ASSERT_SAME_OFFSET(__ers_pax, kcs_gpregs.gp_Pax);
ASSERT_SAME_OFFSET(__ers_pflags, kcs_Pflags);
ASSERT_SAME_OFFSET(__ers_pip, kcs_Pip);
#undef ASSERT_SAME_OFFSET


#endif /* !GUARD__VERIFY_ARCH_I386_ASSERT_EXCEPT_REGISTER_STATE_TYPE_STRUCT_C */
