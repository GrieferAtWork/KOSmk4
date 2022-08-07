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
#ifndef _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_COMPAT_H
#define _I386_KOS_KOS_KERNEL_BITS_CPU_STATE_COMPAT_H 1

#include <hybrid/host.h>

#include "cpu-state.h"

/* Define names for pointer-sized cpu-state fields. */
#ifdef __x86_64__
#define gp_Pdi                  gp_rdi
#define gp_Psi                  gp_rsi
#define gp_Pbp                  gp_rbp
#define gp_Psp                  gp_rsp
#define gp_Pbx                  gp_rbx
#define gp_Pdx                  gp_rdx
#define gp_Pcx                  gp_rcx
#define gp_Pax                  gp_rax
#define gp_R_fcall0P            gp_rdi
#define gp_R_fcall1P            gp_rsi
#define ir_Pip                  ir_rip
#define ir_Pflags               ir_rflags
#define ir_Psp                  ir_rsp
#define ucs_Pflags              ucs_rflags
#define ucs_Pip                 ucs_rip
#define lcs_Pdi                 lcs_rdi
#define lcs_Psi                 lcs_rsi
#define lcs_Pbp                 lcs_rbp
#define lcs_Psp                 lcs_rsp
#define lcs_Pbx                 lcs_rbx
#define lcs_Pip                 lcs_rip
#define kcs_Pflags              kcs_rflags
#define kcs_Pip                 kcs_rip
#define fcs_Pflags              fcs_rflags
#define fcs_Pip                 fcs_rip
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
#define OFFSET_ICPUSTATE_PDI    (OFFSET_ICPUSTATE64_GPREGSNSP + OFFSET_GPREGSNSP64_RDI)
#define OFFSET_ICPUSTATE_PSI    (OFFSET_ICPUSTATE64_GPREGSNSP + OFFSET_GPREGSNSP64_RSI)
#define OFFSET_ICPUSTATE_PBP    (OFFSET_ICPUSTATE64_GPREGSNSP + OFFSET_GPREGSNSP64_RBP)
#define OFFSET_ICPUSTATE_PBX    (OFFSET_ICPUSTATE64_GPREGSNSP + OFFSET_GPREGSNSP64_RBX)
#define OFFSET_ICPUSTATE_PDX    (OFFSET_ICPUSTATE64_GPREGSNSP + OFFSET_GPREGSNSP64_RDX)
#define OFFSET_ICPUSTATE_PCX    (OFFSET_ICPUSTATE64_GPREGSNSP + OFFSET_GPREGSNSP64_RCX)
#define OFFSET_ICPUSTATE_PAX    (OFFSET_ICPUSTATE64_GPREGSNSP + OFFSET_GPREGSNSP64_RAX)
#define OFFSET_UCPUSTATE_PFLAGS OFFSET_UCPUSTATE_RFLAGS
#define OFFSET_UCPUSTATE_PIP    OFFSET_UCPUSTATE_RIP
#define OFFSET_LCPUSTATE_PBP    OFFSET_LCPUSTATE_RBP
#define OFFSET_LCPUSTATE_PSP    OFFSET_LCPUSTATE_RSP
#define OFFSET_LCPUSTATE_PBX    OFFSET_LCPUSTATE_RBX
#define OFFSET_LCPUSTATE_PIP    OFFSET_LCPUSTATE_RIP
#define OFFSET_KCPUSTATE_PIP    OFFSET_KCPUSTATE_RIP
#define OFFSET_KCPUSTATE_PFLAGS OFFSET_KCPUSTATE_RFLAGS
#define OFFSET_FCPUSTATE_PFLAGS OFFSET_FCPUSTATE_RFLAGS
#define OFFSET_FCPUSTATE_PIP    OFFSET_FCPUSTATE_RIP
#else /* __x86_64__ */
#define gp_Pdi                  gp_edi
#define gp_Psi                  gp_esi
#define gp_Pbp                  gp_ebp
#define gp_Psp                  gp_esp
#define gp_Pbx                  gp_ebx
#define gp_Pdx                  gp_edx
#define gp_Pcx                  gp_ecx
#define gp_Pax                  gp_eax
#define gp_R_fcall0P            gp_ecx
#define gp_R_fcall1P            gp_edx
#define ir_Pip                  ir_eip
#define ir_Pflags               ir_eflags
#define ir_Psp                  ir_esp
#define ucs_Pflags              ucs_eflags
#define ucs_Pip                 ucs_eip
#define lcs_Pdi                 lcs_edi
#define lcs_Psi                 lcs_esi
#define lcs_Pbp                 lcs_ebp
#define lcs_Psp                 lcs_esp
#define lcs_Pbx                 lcs_ebx
#define lcs_Pip                 lcs_eip
#define kcs_Pflags              kcs_eflags
#define kcs_Pip                 kcs_eip
#define fcs_Pflags              fcs_eflags
#define fcs_Pip                 fcs_eip
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
#define OFFSET_ICPUSTATE_PDI    (OFFSET_ICPUSTATE32_GPREGS + OFFSET_GPREGS32_EDI)
#define OFFSET_ICPUSTATE_PSI    (OFFSET_ICPUSTATE32_GPREGS + OFFSET_GPREGS32_ESI)
#define OFFSET_ICPUSTATE_PBP    (OFFSET_ICPUSTATE32_GPREGS + OFFSET_GPREGS32_EBP)
#define OFFSET_ICPUSTATE_PBX    (OFFSET_ICPUSTATE32_GPREGS + OFFSET_GPREGS32_EBX)
#define OFFSET_ICPUSTATE_PDX    (OFFSET_ICPUSTATE32_GPREGS + OFFSET_GPREGS32_EDX)
#define OFFSET_ICPUSTATE_PCX    (OFFSET_ICPUSTATE32_GPREGS + OFFSET_GPREGS32_ECX)
#define OFFSET_ICPUSTATE_PAX    (OFFSET_ICPUSTATE32_GPREGS + OFFSET_GPREGS32_EAX)
#define OFFSET_UCPUSTATE_PFLAGS OFFSET_UCPUSTATE_EFLAGS
#define OFFSET_UCPUSTATE_PIP    OFFSET_UCPUSTATE_EIP
#define OFFSET_LCPUSTATE_PBP    OFFSET_LCPUSTATE_EBP
#define OFFSET_LCPUSTATE_PSP    OFFSET_LCPUSTATE_ESP
#define OFFSET_LCPUSTATE_PBX    OFFSET_LCPUSTATE_EBX
#define OFFSET_LCPUSTATE_PIP    OFFSET_LCPUSTATE_EIP
#define OFFSET_KCPUSTATE_PIP    OFFSET_KCPUSTATE_EIP
#define OFFSET_KCPUSTATE_PFLAGS OFFSET_KCPUSTATE_EFLAGS
#define OFFSET_FCPUSTATE_PFLAGS OFFSET_FCPUSTATE_EFLAGS
#define OFFSET_FCPUSTATE_PIP    OFFSET_FCPUSTATE_EIP
#endif /* !__x86_64__ */
#define OFFSET_ICPUSTATE_CS     (OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_CS)
#define OFFSET_ICPUSTATE_PIP    (OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_PIP)
#define OFFSET_ICPUSTATE_PFLAGS (OFFSET_ICPUSTATE_IRREGS + OFFSET_IRREGS_PFLAGS)


#endif /* !_I386_KOS_KOS_KERNEL_BITS_CPU_STATE_COMPAT_H */
