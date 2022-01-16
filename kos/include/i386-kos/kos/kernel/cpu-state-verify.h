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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_VERIFY_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_VERIFY_H 1

/* Helper functions for verification of CPU state values. */

#include <hybrid/__assert.h>

#include <asm/registers.h>
#include <bits/types.h>
#include <kos/anno.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/gdt.h>

#include "cpu-state.h"


#ifdef __CC__
__DECL_BEGIN

/* Verify that only bits maskable by `MODIFYABLE_MASK' have changed. */
__LOCAL void (cpustate_verify_userpflags)(__uintptr_t __old_pflags,
                                          __uintptr_t __new_pflags,
                                          __uintptr_t __modifyable_mask)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if __unlikely((__old_pflags & ~__modifyable_mask) !=
	              (__new_pflags & ~__modifyable_mask)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_MISC_EFLAGS,
		      __new_pflags);
	}
}

/* Verify that `V_CS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_usercs)(__u16 __v_cs)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if __unlikely(!SEGMENT_IS_VALID_USERCODE(__v_cs)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, __v_cs);
	}
}

/* Verify that `V_SS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_userss)(__u16 __v_ss)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_ss)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_SS, __v_ss);
	}
}

/* Verify that `V_GS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_usergs)(__u16 __v_gs)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_gs)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_GS, __v_gs);
	}
}

/* Verify that `V_FS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_userfs)(__u16 __v_fs)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_fs)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_FS, __v_fs);
	}
}

/* Verify that `V_ES' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_useres)(__u16 __v_es)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_es)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_ES, __v_es);
	}
}

/* Verify that `V_DS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_userds)(__u16 __v_ds)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_ds)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_DS, __v_ds);
	}
}


__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_VERIFY_H */
