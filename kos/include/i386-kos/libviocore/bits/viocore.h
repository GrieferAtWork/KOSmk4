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
#ifndef _I386_KOS_LIBVIOCORE_BITS_VIOCORE_H
#define _I386_KOS_LIBVIOCORE_BITS_VIOCORE_H 1

#include <libviocore/api.h>
/**/

#include <hybrid/host.h>

#include <bits/types.h>

#include <libvio/vio.h>

#ifdef __CC__
__DECL_BEGIN

struct vio_emulate_args {
	struct vioargs vea_args;  /* [OVERRIDE(.va_state, [1..1])] Underlying VIO arguments. */
	vio_addr_t     vea_addr;  /* == vioargs_vioaddr(&.vea_args, .vea_ptrlo) */
	void          *vea_ptrlo; /* Lower virtual address at which the VIO fault happened. */
	void          *vea_ptrhi; /* Upper virtual address at which the VIO fault happened. */
#if defined(__KERNEL__) && !defined(__x86_64__)
	/* Because  `struct icpustate32'  doesn't contain  dedicated fields  for the
	 * %esp and %ss registers when describing kernel-space register states,
	 * emulating instructions that may  modify these registers requires  special
	 * care in order to delay the actual assignment of new register values until
	 * after instruction emulation has completed.
	 * This  is done by having the kernel-space #PF check if a custom %ss or %esp
	 * had  been  assigned during  emulation, such  that it  will then  load them
	 * by re-directing execution to a custom register loading bootstrap function.
	 * s.a. `x86_vio_kernel_esp_bootstrap_loader()' in
	 *      `kernel/core/arch/i386/fault/handle_pagefault.c' */
	__uint16_t vea_kernel_override;     /* Set of `VIO_EMULATE_ARGS_386_KERNEL_*_VALID' */
	__uint16_t vea_kernel_ss_override;  /* [valid_if(VIO_EMULATE_ARGS_386_KERNEL_SS_VALID)] Override for the kernel %ss */
	__uint32_t vea_kernel_esp_override; /* [valid_if(VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID)] Override for the kernel %esp */
#define VIO_EMULATE_ARGS_386_KERNEL_SS_VALID  0x0001 /* `vea_kernel_ss_override' is valid */
#define VIO_EMULATE_ARGS_386_KERNEL_ESP_VALID 0x0002 /* `vea_kernel_esp_override' is valid */
#endif /* __KERNEL__ && !__x86_64__ */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_LIBVIOCORE_BITS_VIOCORE_H */
