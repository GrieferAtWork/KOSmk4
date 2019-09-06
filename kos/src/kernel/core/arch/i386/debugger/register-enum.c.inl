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

#ifndef REGISTER
#define REGISTER(name, get, set)
#endif /* !REGISTER */

#define REGISTER_FIELD(name, field)   REGISTER(name, field, field = value)
#define REGISTER_FIELD8(name, field)  REGISTER(name, (u8)field, field = (u8)value)
#define REGISTER_FIELD16(name, field) REGISTER(name, (u16)field, field = (u16)value)
#define REGISTER_FIELD32(name, field) REGISTER(name, (u32)field, field = (u32)value)
#define REGISTER_FIELD64(name, field) REGISTER(name, (u64)field, field = (u64)value)
#define S dbg_viewstate

#ifdef __x86_64__
#define S_eax  S.fcs_gpregs.gp_rax
#define S_ecx  S.fcs_gpregs.gp_rcx
#define S_edx  S.fcs_gpregs.gp_rdx
#define S_ebx  S.fcs_gpregs.gp_rbx
#define S_esp  S.fcs_gpregs.gp_rsp
#define S_ebp  S.fcs_gpregs.gp_rbp
#define S_esi  S.fcs_gpregs.gp_rsi
#define S_edi  S.fcs_gpregs.gp_rdi
#define S_eip  S.fcs_rip
#define S_efl  S.fcs_rflags
#else /* __x86_64__ */
#define S_eax  S.fcs_gpregs.gp_eax
#define S_ecx  S.fcs_gpregs.gp_ecx
#define S_edx  S.fcs_gpregs.gp_edx
#define S_ebx  S.fcs_gpregs.gp_ebx
#define S_esp  S.fcs_gpregs.gp_esp
#define S_ebp  S.fcs_gpregs.gp_ebp
#define S_esi  S.fcs_gpregs.gp_esi
#define S_edi  S.fcs_gpregs.gp_edi
#define S_eip  S.fcs_eip
#define S_efl  S.fcs_eflags
#endif /* !__x86_64__ */


REGISTER_FIELD8("al", ((u8 *)&S_eax)[0])
REGISTER_FIELD8("cl", ((u8 *)&S_ecx)[0])
REGISTER_FIELD8("dl", ((u8 *)&S_edx)[0])
REGISTER_FIELD8("bl", ((u8 *)&S_ebx)[0])

REGISTER_FIELD8("ah", ((u8 *)&S_eax)[1])
REGISTER_FIELD8("ch", ((u8 *)&S_ecx)[1])
REGISTER_FIELD8("dh", ((u8 *)&S_edx)[1])
REGISTER_FIELD8("bh", ((u8 *)&S_ebx)[1])

REGISTER_FIELD8("spl", ((u8 *)&S_esp)[0])
REGISTER_FIELD8("bpl", ((u8 *)&S_ebp)[0])
REGISTER_FIELD8("sil", ((u8 *)&S_esi)[0])
REGISTER_FIELD8("dil", ((u8 *)&S_edi)[0])

REGISTER_FIELD16("ax", S_eax)
REGISTER_FIELD16("cx", S_ecx)
REGISTER_FIELD16("dx", S_edx)
REGISTER_FIELD16("bx", S_ebx)
REGISTER_FIELD16("sp", S_esp)
REGISTER_FIELD16("bp", S_ebp)
REGISTER_FIELD16("si", S_esi)
REGISTER_FIELD16("di", S_edi)

REGISTER_FIELD32("eax", S_eax)
REGISTER_FIELD32("ecx", S_ecx)
REGISTER_FIELD32("edx", S_edx)
REGISTER_FIELD32("ebx", S_ebx)
REGISTER_FIELD32("esp", S_esp)
REGISTER_FIELD32("ebp", S_ebp)
REGISTER_FIELD32("esi", S_esi)
REGISTER_FIELD32("edi", S_edi)

REGISTER_FIELD16("ip", S_eip)
REGISTER_FIELD32("eip", S_eip)

REGISTER_FIELD16("flags", S_efl)
REGISTER_FIELD32("eflags", S_efl)

REGISTER_FIELD("cr0", S.fcs_coregs.co_cr0)
REGISTER_FIELD("cr2", S.fcs_coregs.co_cr2)
REGISTER_FIELD("cr3", S.fcs_coregs.co_cr3)
REGISTER_FIELD("cr4", S.fcs_coregs.co_cr4)

REGISTER_FIELD("dr0", S.fcs_drregs.dr_dr0)
REGISTER_FIELD("dr1", S.fcs_drregs.dr_dr1)
REGISTER_FIELD("dr2", S.fcs_drregs.dr_dr2)
REGISTER_FIELD("dr3", S.fcs_drregs.dr_dr3)
REGISTER_FIELD("dr6", S.fcs_drregs.dr_dr6)
REGISTER_FIELD("dr7", S.fcs_drregs.dr_dr7)

REGISTER_FIELD16("es", S.fcs_sgregs.sg_es)
REGISTER_FIELD16("cs", S.fcs_sgregs.sg_cs)
REGISTER_FIELD16("ss", S.fcs_sgregs.sg_ss)
REGISTER_FIELD16("ds", S.fcs_sgregs.sg_ds)
REGISTER_FIELD16("fs", S.fcs_sgregs.sg_fs)
REGISTER_FIELD16("gs", S.fcs_sgregs.sg_gs)
REGISTER_FIELD16("tr", S.fcs_sgregs.sg_tr)
REGISTER_FIELD16("ldtr", S.fcs_sgregs.sg_ldt)

REGISTER_FIELD16("gdt.limt", S.fcs_gdt.dt_limit)
REGISTER_FIELD("gdt.base", S.fcs_gdt.dt_base)

REGISTER_FIELD16("idt.limt", S.fcs_idt.dt_limit)
REGISTER_FIELD("idt.base", S.fcs_idt.dt_base)

/* A couple of helpful aliases */
REGISTER_FIELD(".", S.fcs_eip)
REGISTER_FIELD("pc", S.fcs_eip)
REGISTER_FIELD("sp", S_esp)

#ifdef __x86_64__


REGISTER_FIELD64("rax", S_eax)
REGISTER_FIELD64("rcx", S_ecx)
REGISTER_FIELD64("rdx", S_edx)
REGISTER_FIELD64("rbx", S_ebx)
REGISTER_FIELD64("rsp", S_esp)
REGISTER_FIELD64("rbp", S_ebp)
REGISTER_FIELD64("rsi", S_esi)
REGISTER_FIELD64("rdi", S_edi)
REGISTER_FIELD64("rip", S_eip)
REGISTER_FIELD64("rflags", S_efl)

REGISTER_FIELD8("r8l", ((u8 *)&S.fcs_gpregs.gp_r8)[0])
REGISTER_FIELD8("r9l", ((u8 *)&S.fcs_gpregs.gp_r9)[0])
REGISTER_FIELD8("r10l", ((u8 *)&S.fcs_gpregs.gp_r10)[0])
REGISTER_FIELD8("r11l", ((u8 *)&S.fcs_gpregs.gp_r11)[0])
REGISTER_FIELD8("r12l", ((u8 *)&S.fcs_gpregs.gp_r12)[0])
REGISTER_FIELD8("r13l", ((u8 *)&S.fcs_gpregs.gp_r13)[0])
REGISTER_FIELD8("r14l", ((u8 *)&S.fcs_gpregs.gp_r14)[0])
REGISTER_FIELD8("r15l", ((u8 *)&S.fcs_gpregs.gp_r15)[0])

REGISTER_FIELD16("r8w", S.fcs_gpregs.gp_r8)
REGISTER_FIELD16("r9w", S.fcs_gpregs.gp_r9)
REGISTER_FIELD16("r10w", S.fcs_gpregs.gp_r10)
REGISTER_FIELD16("r11w", S.fcs_gpregs.gp_r11)
REGISTER_FIELD16("r12w", S.fcs_gpregs.gp_r12)
REGISTER_FIELD16("r13w", S.fcs_gpregs.gp_r13)
REGISTER_FIELD16("r14w", S.fcs_gpregs.gp_r14)
REGISTER_FIELD16("r15w", S.fcs_gpregs.gp_r15)

REGISTER_FIELD32("r8d", S.fcs_gpregs.gp_r8)
REGISTER_FIELD32("r9d", S.fcs_gpregs.gp_r9)
REGISTER_FIELD32("r10d", S.fcs_gpregs.gp_r10)
REGISTER_FIELD32("r11d", S.fcs_gpregs.gp_r11)
REGISTER_FIELD32("r12d", S.fcs_gpregs.gp_r12)
REGISTER_FIELD32("r13d", S.fcs_gpregs.gp_r13)
REGISTER_FIELD32("r14d", S.fcs_gpregs.gp_r14)
REGISTER_FIELD32("r15d", S.fcs_gpregs.gp_r15)

REGISTER_FIELD64("r8", S.fcs_gpregs.gp_r8)
REGISTER_FIELD64("r9", S.fcs_gpregs.gp_r9)
REGISTER_FIELD64("r10", S.fcs_gpregs.gp_r10)
REGISTER_FIELD64("r11", S.fcs_gpregs.gp_r11)
REGISTER_FIELD64("r12", S.fcs_gpregs.gp_r12)
REGISTER_FIELD64("r13", S.fcs_gpregs.gp_r13)
REGISTER_FIELD64("r14", S.fcs_gpregs.gp_r14)
REGISTER_FIELD64("r15", S.fcs_gpregs.gp_r15)

#endif /* __x86_64__ */

#undef S_eax
#undef S_ecx
#undef S_edx
#undef S_ebx
#undef S_esp
#undef S_ebp
#undef S_esi
#undef S_edi
#undef S_eip
#undef S_efl

#undef S
#undef REGISTER_FIELD64
#undef REGISTER_FIELD32
#undef REGISTER_FIELD16
#undef REGISTER_FIELD8
#undef REGISTER_FIELD
#undef REGISTER
