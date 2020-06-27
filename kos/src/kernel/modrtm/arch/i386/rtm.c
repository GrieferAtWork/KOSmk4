/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODRTM_ARCH_I386_RTM_C
#define GUARD_MODRTM_ARCH_I386_RTM_C 1

#include "../../rtm.h"

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/printk.h>

DECL_BEGIN

PRIVATE ATTR_RETNONNULL NONNULL((1)) struct icpustate *FCALL
x86_emulate_xbegin(struct icpustate *__restrict state,
                   uintptr_t fallback_ip) {
	(void)state;
	(void)fallback_ip;
	printk("TODO: Emulate x86 instructions in the context of RTM\n");
	THROW(E_NOT_IMPLEMENTED);
}



PUBLIC struct vm_rtm_driver_hooks rtm_hooks = {
	/* .rdh_driver = */ &drv_self,
	/* .rdh_hooks  = */ {
		/* .rh_xbegin = */ &x86_emulate_xbegin
	}
};


DECL_END

#endif /* !GUARD_MODRTM_ARCH_I386_RTM_C */
