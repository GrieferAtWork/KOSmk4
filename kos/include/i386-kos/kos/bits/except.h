/* HASH CRC-32:0xcc09098b */
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
#ifndef _I386_KOS_KOS_BITS_EXCEPT_H
#define _I386_KOS_KOS_BITS_EXCEPT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#ifdef __USE_KOS_KERNEL
#include <kos/kernel/cpu-state.h>
#endif /* __USE_KOS_KERNEL */

#undef __ERROR_REGISTER_STATE_TYPE
#define __ERROR_REGISTER_STATE_TYPE struct kcpustate
#ifdef __USE_KOS_KERNEL
#define __SIZEOF_ERROR_REGISTER_STATE SIZEOF_KCPUSTATE
#endif /* __USE_KOS_KERNEL */
#ifdef __x86_64__
#define __ERROR_REGISTER_STATE_TYPE_RDPC(x)                       ((x).kcs_rip)
#define __ERROR_REGISTER_STATE_TYPE_WRPC(x, value)                ((x).kcs_rip = (value))
#define __ERROR_REGISTER_STATE_TYPE_RDSP(x)                       ((x).kcs_gpregs.gp_rsp)
#define __ERROR_REGISTER_STATE_TYPE_WRSP(x, value)                ((x).kcs_gpregs.gp_rsp = (value))
#define __ERROR_REGISTER_STATE_TYPE_RD_UNWIND_EXCEPTION(x)        ((x).kcs_gpregs.gp_rax)
#define __ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(x, value) ((x).kcs_gpregs.gp_rax = (value))
#else /* __x86_64__ */
#define __ERROR_REGISTER_STATE_TYPE_RDPC(x)                       ((x).kcs_eip)
#define __ERROR_REGISTER_STATE_TYPE_WRPC(x, value)                ((x).kcs_eip = (value))
#define __ERROR_REGISTER_STATE_TYPE_RDSP(x)                       ((x).kcs_gpregs.gp_esp)
#define __ERROR_REGISTER_STATE_TYPE_WRSP(x, value)                ((x).kcs_gpregs.gp_esp = (value))
#define __ERROR_REGISTER_STATE_TYPE_RD_UNWIND_EXCEPTION(x)        ((x).kcs_gpregs.gp_eax)
#define __ERROR_REGISTER_STATE_TYPE_WR_UNWIND_EXCEPTION(x, value) ((x).kcs_gpregs.gp_eax = (value))
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_KOS_BITS_EXCEPT_H */
