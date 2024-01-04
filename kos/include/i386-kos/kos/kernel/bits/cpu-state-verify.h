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
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_VERIFY_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_VERIFY_H 1

/* Helper functions for verification of CPU state values. */

#include <bits/types.h>
#include <kos/anno.h>

#ifndef __INTELLISENSE__
#include <asm/registers.h>
#include <asm/registers-compat.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include "../x86/gdt.h"
#endif /* !__INTELLISENSE__ */

#ifdef __CC__
#if defined(THROW) || defined(__INTELLISENSE__)
__DECL_BEGIN

/* Verify that only bits maskable by `MODIFYABLE_MASK' have changed. */
__LOCAL void (cpustate_verify_usereflags)(__uint32_t __old_eflags,
                                          __uint32_t __new_eflags,
                                          __uint32_t __modifyable_mask)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely((__old_eflags & ~__modifyable_mask) !=
	              (__new_eflags & ~__modifyable_mask)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_MISC_EFLAGS,
		      __new_eflags, __old_eflags, __modifyable_mask);
	}
#endif /* !__INTELLISENSE__ */
}

#ifdef __x86_64__
/* Verify that only bits maskable by `MODIFYABLE_MASK' have changed. */
__LOCAL void (cpustate_verify_userrflags)(__uint64_t __old_rflags,
                                          __uint64_t __new_rflags,
                                          __uint64_t __modifyable_mask)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely((__old_rflags & ~__modifyable_mask) !=
	              (__new_rflags & ~__modifyable_mask)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_MISC_RFLAGS,
		      __new_rflags, __old_rflags, __modifyable_mask);
	}
#endif /* !__INTELLISENSE__ */
}
#define cpustate_verify_userpflags cpustate_verify_userrflags
#else /* __x86_64__ */
#define cpustate_verify_userpflags cpustate_verify_usereflags
#endif /* !__x86_64__ */


/* Verify that `V_CS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_usercs)(__u16 __v_cs)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely(!SEGMENT_IS_VALID_USERCODE(__v_cs)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_CS, __v_cs);
	}
#endif /* !__INTELLISENSE__ */
}

/* Verify that `V_SS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_userss)(__u16 __v_ss)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_ss)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_SS, __v_ss);
	}
#endif /* !__INTELLISENSE__ */
}

/* Verify that `V_GS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_usergs)(__u16 __v_gs)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_gs)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_GS, __v_gs);
	}
#endif /* !__INTELLISENSE__ */
}

/* Verify that `V_FS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_userfs)(__u16 __v_fs)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_fs)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_FS, __v_fs);
	}
#endif /* !__INTELLISENSE__ */
}

/* Verify that `V_ES' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_useres)(__u16 __v_es)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_es)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_ES, __v_es);
	}
#endif /* !__INTELLISENSE__ */
}

/* Verify that `V_DS' is a valid user-space segment register. */
__LOCAL void (cpustate_verify_userds)(__u16 __v_ds)
		__THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
#ifndef __INTELLISENSE__
	if __unlikely(!SEGMENT_IS_VALID_USERDATA(__v_ds)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
		      X86_REGISTER_SEGMENT_DS, __v_ds);
	}
#endif /* !__INTELLISENSE__ */
}

__DECL_END
#endif /* THROW || __INTELLISENSE__ */
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE_VERIFY_H */
