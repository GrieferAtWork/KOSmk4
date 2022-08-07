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
#ifndef _I386_KOS_KOS_KERNEL_X86_TSS_COMPAT_H
#define _I386_KOS_KOS_KERNEL_X86_TSS_COMPAT_H 1

#include <hybrid/host.h>

#include "tss.h"

#ifdef __x86_64__
#define OFFSET_TSS_PSP0 OFFSET_TSS_RSP0
#define OFFSET_TSS_PSP1 OFFSET_TSS_RSP1
#define OFFSET_TSS_PSP2 OFFSET_TSS_RSP2
#else /* __x86_64__ */
#define OFFSET_TSS_PSP0 OFFSET_TSS_ESP0
#define OFFSET_TSS_PSP1 OFFSET_TSS_ESP1
#define OFFSET_TSS_PSP2 OFFSET_TSS_ESP2
#endif /* !__x86_64__ */

#ifdef __CC__
#ifdef __x86_64__
#define t_psp0 t_rsp0
#define t_psp1 t_rsp1
#define t_psp2 t_rsp2
#else /* __x86_64__ */
#define t_psp0 t_esp0
#define t_psp1 t_esp1
#define t_psp2 t_esp2
#endif /* !__x86_64__ */
#endif /* __CC__ */

#endif /* !_I386_KOS_KOS_KERNEL_X86_TSS_COMPAT_H */
