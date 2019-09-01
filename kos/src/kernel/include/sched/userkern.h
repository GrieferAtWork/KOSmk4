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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_USERKERN_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_USERKERN_H 1

#include <kernel/compiler.h>

#include <kernel/vio.h>

#ifndef CONFIG_VIO
#undef CONFIG_NO_USERKERN_SEGMENT
#define CONFIG_NO_USERKERN_SEGMENT 1
#endif /* !CONFIG_VIO */

#ifndef CONFIG_NO_USERKERN_SEGMENT
#include <sched/arch/userkern.h>

#ifndef CONFIG_NO_USERKERN_SEGMENT
#include <kernel/vm.h>
#include <sched/pertask.h>

#include <kos/ukern.h>

#ifdef __CC__

DECL_BEGIN

/* VIO bindings for the kernel-reserve segment of user-space VMs */
DATDEF struct vm_datablock_type_vio userkern_segment_vio;
DATDEF struct vm_datablock userkern_segment_block;
DATDEF struct vm_datapart userkern_segment_part;



DECL_END

#endif /* __CC__ */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_USERKERN_H */
