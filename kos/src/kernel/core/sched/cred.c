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
#ifndef GUARD_KERNEL_SRC_SCHED_CRED_C
#define GUARD_KERNEL_SRC_SCHED_CRED_C 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/cred.h>

/* Credential checking. */

DECL_BEGIN

PUBLIC void KCALL
cred_require_hwio(void) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO */
}

PUBLIC void KCALL
cred_require_mount(void) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO */
}

PUBLIC void KCALL
cred_require_vmread(struct vm *__restrict target_vm) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO */
}

PUBLIC void KCALL
cred_require_vmwrite(struct vm *__restrict target_vm) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO */
}

PUBLIC void KCALL
cred_require_resource(void) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO: `CAP_SYS_RESOURCE' */
}

PUBLIC void KCALL
cred_require_sysadmin(void) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO: `CAP_SYS_ADMIN' */
}

PUBLIC void KCALL
cred_require_driveroot(void) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* TODO */
}

PUBLIC void KCALL
cred_require_debugtrap(void) THROWS(E_INSUFFICIENT_RIGHTS) {
	/* Caller is allowed to trigger arbitrary debug traps */
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_CRED_C */
