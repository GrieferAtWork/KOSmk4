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
#ifndef GUARD_MODRTM_RTM_C
#define GUARD_MODRTM_RTM_C 1

#include "rtm.h"

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/mman/rtm.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>

#include <stddef.h>

DECL_BEGIN

/* Define driver init/fini callbacks to register RTM hooks */
PRIVATE DRIVER_INIT void KCALL rtm_init(void) {
	/* Install our RTM hooks.
	 * If RTM hooks had already been installed, throw an exception */
	if (!awref_cmpxch(&mrtm_hooks, NULL, &rtm_hooks))
		THROW(E_ILLEGAL_OPERATION, E_ILLEGAL_OPERATION_CONTEXT_RTM_ALREADY_LOADED);
}

PRIVATE DRIVER_FINI void KCALL rtm_fini(void) {
	/* Uninstall our RTM hooks */
	awref_cmpxch(&mrtm_hooks, &rtm_hooks, NULL);
}

DECL_END

#endif /* !GUARD_MODRTM_RTM_C */
