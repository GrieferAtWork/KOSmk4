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
#ifndef _I386_KOS_KOS_KERNEL_CPU_STATE_COMPAT_H
#define _I386_KOS_KOS_KERNEL_CPU_STATE_COMPAT_H 1

#include <hybrid/host.h>

#include "cpu-state.h"

/* Define names for pointer-sized cpu-state fields. */
#ifdef __x86_64__
#define gp_pdi                  gp_rdi
#define gp_psi                  gp_rsi
#define gp_pbp                  gp_rbp
#define gp_psp                  gp_rsp
#define gp_pbx                  gp_rbx
#define gp_pdx                  gp_rdx
#define gp_pcx                  gp_rcx
#define gp_pax                  gp_rax
#define ir_pip                  ir_rip
#define ir_pflags               ir_rflags
#define ir_psp                  ir_rsp
#define ucs_pflags              ucs_rflags
#define ucs_pip                 ucs_rip
#define lcs_pdi                 lcs_rdi
#define lcs_psi                 lcs_rsi
#define lcs_pbp                 lcs_rbp
#define lcs_psp                 lcs_rsp
#define lcs_pbx                 lcs_rbx
#define lcs_pip                 lcs_rip
#define kcs_pflags              kcs_rflags
#define kcs_pip                 kcs_rip
#define fcs_pflags              fcs_rflags
#define fcs_pip                 fcs_rip
#define OFFSET_GPREGS_PDI       OFFSET_GPREGS_RDI
#define OFFSET_GPREGS_PSI       OFFSET_GPREGS_RSI
#define OFFSET_GPREGS_PBP       OFFSET_GPREGS_RBP
#define OFFSET_GPREGS_PSP       OFFSET_GPREGS_RSP
#define OFFSET_GPREGS_PBX       OFFSET_GPREGS_RBX
#define OFFSET_GPREGS_PDX       OFFSET_GPREGS_RDX
#define OFFSET_GPREGS_PCX       OFFSET_GPREGS_RCX
#define OFFSET_GPREGS_PAX       OFFSET_GPREGS_RAX
#define OFFSET_IRREGS_PIP       OFFSET_IRREGS_RIP
#define OFFSET_IRREGS_PFLAGS    OFFSET_IRREGS_RFLAGS
#define OFFSET_IRREGS_PSP       OFFSET_IRREGS_RSP
#define OFFSET_UCPUSTATE_PFLAGS OFFSET_UCPUSTATE_RFLAGS
#define OFFSET_UCPUSTATE_PIP    OFFSET_UCPUSTATE_RIP
#define OFFSET_LCPUSTATE_PBP    OFFSET_LCPUSTATE_RBP
#define OFFSET_LCPUSTATE_PSP    OFFSET_LCPUSTATE_RSP
#define OFFSET_LCPUSTATE_PBX    OFFSET_LCPUSTATE_RBX
#define OFFSET_LCPUSTATE_PIP    OFFSET_LCPUSTATE_RIP
#define OFFSET_KCPUSTATE_PIP    OFFSET_KCPUSTATE_RIP
#define OFFSET_FCPUSTATE_PFLAGS OFFSET_FCPUSTATE_RFLAGS
#define OFFSET_FCPUSTATE_PIP    OFFSET_FCPUSTATE_RIP
#else /* __x86_64__ */
#define gp_pdi                  gp_edi
#define gp_psi                  gp_esi
#define gp_pbp                  gp_ebp
#define gp_psp                  gp_esp
#define gp_pbx                  gp_ebx
#define gp_pdx                  gp_edx
#define gp_pcx                  gp_ecx
#define gp_pax                  gp_eax
#define ir_pip                  ir_eip
#define ir_pflags               ir_eflags
#define ir_psp                  ir_esp
#define ucs_pflags              ucs_eflags
#define ucs_pip                 ucs_eip
#define lcs_pdi                 lcs_edi
#define lcs_psi                 lcs_esi
#define lcs_pbp                 lcs_ebp
#define lcs_psp                 lcs_esp
#define lcs_pbx                 lcs_ebx
#define lcs_pip                 lcs_eip
#define kcs_pflags              kcs_eflags
#define kcs_pip                 kcs_eip
#define fcs_pflags              fcs_eflags
#define fcs_pip                 fcs_eip
#define OFFSET_GPREGS_PDI       OFFSET_GPREGS_EDI
#define OFFSET_GPREGS_PSI       OFFSET_GPREGS_ESI
#define OFFSET_GPREGS_PBP       OFFSET_GPREGS_EBP
#define OFFSET_GPREGS_PSP       OFFSET_GPREGS_ESP
#define OFFSET_GPREGS_PBX       OFFSET_GPREGS_EBX
#define OFFSET_GPREGS_PDX       OFFSET_GPREGS_EDX
#define OFFSET_GPREGS_PCX       OFFSET_GPREGS_ECX
#define OFFSET_GPREGS_PAX       OFFSET_GPREGS_EAX
#define OFFSET_IRREGS_PIP       OFFSET_IRREGS_EIP
#define OFFSET_IRREGS_PFLAGS    OFFSET_IRREGS_EFLAGS
#define OFFSET_IRREGS_PSP       OFFSET_IRREGS_ESP
#define OFFSET_UCPUSTATE_PFLAGS OFFSET_UCPUSTATE_EFLAGS
#define OFFSET_UCPUSTATE_PIP    OFFSET_UCPUSTATE_EIP
#define OFFSET_LCPUSTATE_PBP    OFFSET_LCPUSTATE_EBP
#define OFFSET_LCPUSTATE_PSP    OFFSET_LCPUSTATE_ESP
#define OFFSET_LCPUSTATE_PBX    OFFSET_LCPUSTATE_EBX
#define OFFSET_LCPUSTATE_PIP    OFFSET_LCPUSTATE_EIP
#define OFFSET_KCPUSTATE_PIP    OFFSET_KCPUSTATE_EIP
#define OFFSET_FCPUSTATE_PFLAGS OFFSET_FCPUSTATE_EFLAGS
#define OFFSET_FCPUSTATE_PIP    OFFSET_FCPUSTATE_EIP
#endif /* !__x86_64__ */


#endif /* !_I386_KOS_KOS_KERNEL_CPU_STATE_COMPAT_H */
