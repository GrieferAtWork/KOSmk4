/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_USERKERN_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_USERKERN_H 1

#include <kernel/compiler.h>

#include <libvio/api.h>

/*[[[config CONFIG_HAVE_KERNEL_USERKERN_SEGMENT = true]]]*/
#ifdef CONFIG_NO_KERNEL_USERKERN_SEGMENT
#undef CONFIG_HAVE_KERNEL_USERKERN_SEGMENT
#elif !defined(CONFIG_HAVE_KERNEL_USERKERN_SEGMENT)
#define CONFIG_HAVE_KERNEL_USERKERN_SEGMENT
#elif (-CONFIG_HAVE_KERNEL_USERKERN_SEGMENT - 1) == -1
#undef CONFIG_HAVE_KERNEL_USERKERN_SEGMENT
#define CONFIG_NO_KERNEL_USERKERN_SEGMENT
#endif /* ... */
/*[[[end]]]*/

#ifndef LIBVIO_CONFIG_ENABLED
#undef CONFIG_NO_KERNEL_USERKERN_SEGMENT
#undef CONFIG_HAVE_KERNEL_USERKERN_SEGMENT
#define CONFIG_NO_KERNEL_USERKERN_SEGMENT
#endif /* !LIBVIO_CONFIG_ENABLED */

#ifndef CONFIG_NO_KERNEL_USERKERN_SEGMENT
#include <sched/arch/userkern.h>
#ifndef CONFIG_NO_KERNEL_USERKERN_SEGMENT
#include <compat/config.h>

#ifdef __CC__

DECL_BEGIN

struct vio_ops;
struct mfile;
struct mpart;

/* VIO bindings for the kernel-reserve segment of user-space VMs */
DATDEF struct vio_ops userkern_segment_vio;
DATDEF struct mfile userkern_segment_file;
DATDEF struct mpart userkern_segment_part;

#ifdef __ARCH_HAVE_COMPAT
DATDEF struct vio_ops userkern_segment_vio_compat;
DATDEF struct mfile userkern_segment_file_compat;
DATDEF struct mpart userkern_segment_part_compat;
#endif /* __ARCH_HAVE_COMPAT */

DECL_END

#endif /* __CC__ */
#endif /* !CONFIG_NO_KERNEL_USERKERN_SEGMENT */
#endif /* !CONFIG_NO_KERNEL_USERKERN_SEGMENT */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_SCHED_USERKERN_H */
