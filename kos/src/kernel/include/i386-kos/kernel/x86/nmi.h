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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_NMI_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_NMI_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__

/* Get/Set NMI (non-maskable interrupt) being enabled
 * These interrupts should normally be enabled in all situations,
 * and should only be disabled momentarily, and when absolutely
 * necessary.
 * Also note that NMI enable/disable is controlled globally, and
 * not, say, per-CPU!
 * @param: enabled: The new nmi-enabled state (if different from `return',
 *                  the state was changed)
 * @return: * :     The NMI-enabled state prior to the call being made. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL x86_get_nmi_enabled)(void);
FUNDEF NOPREEMPT NOBLOCK bool
NOTHROW(KCALL x86_set_nmi_enabled_nopr)(bool enabled);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_NMI_H */
