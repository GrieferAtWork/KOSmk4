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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_FAULT_VIO_H
#define GUARD_KERNEL_CORE_ARCH_I386_FAULT_VIO_H 1

#include <kernel/compiler.h>

#include <kernel/vio.h>
#include <kernel/vm.h>

#ifdef CONFIG_VIO
DECL_BEGIN

typedef struct {
	struct vio_args          ma_args;    /* [OVERRIDE(.va_block,REF)]
	                                      * [OVERRIDE(.va_part,REF)] Basic VIO arguments. */
	struct task_connections *ma_oldcons; /* [1..1] Old task connections (must be restored) */
} vio_main_args_t;


/* Main function for VIO instruction emulation. */
INTDEF struct icpustate *
NOTHROW(FCALL x86_vio_main)(/*inherit(always)*/ vio_main_args_t *__restrict args, uintptr_t cr2);

DECL_END
#endif /* CONFIG_VIO */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_FAULT_VIO_H */
