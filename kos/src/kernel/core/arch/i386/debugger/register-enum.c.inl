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


REGISTER_FIELD8("al", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pax)[0])
REGISTER_FIELD8("cl", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pcx)[0])
REGISTER_FIELD8("dl", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pdx)[0])
REGISTER_FIELD8("bl", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pbx)[0])

REGISTER_FIELD8("ah", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pax)[1])
REGISTER_FIELD8("ch", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pcx)[1])
REGISTER_FIELD8("dh", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pdx)[1])
REGISTER_FIELD8("bh", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pbx)[1])

REGISTER_FIELD8("spl", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_psp)[0])
REGISTER_FIELD8("bpl", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pbp)[0])
REGISTER_FIELD8("sil", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_psi)[0])
REGISTER_FIELD8("dil", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_pdi)[0])

REGISTER_FIELD16("ax", x86_dbg_viewstate.fcs_gpregs.gp_pax)
REGISTER_FIELD16("cx", x86_dbg_viewstate.fcs_gpregs.gp_pcx)
REGISTER_FIELD16("dx", x86_dbg_viewstate.fcs_gpregs.gp_pdx)
REGISTER_FIELD16("bx", x86_dbg_viewstate.fcs_gpregs.gp_pbx)
REGISTER_FIELD16("sp", x86_dbg_viewstate.fcs_gpregs.gp_psp)
REGISTER_FIELD16("bp", x86_dbg_viewstate.fcs_gpregs.gp_pbp)
REGISTER_FIELD16("si", x86_dbg_viewstate.fcs_gpregs.gp_psi)
REGISTER_FIELD16("di", x86_dbg_viewstate.fcs_gpregs.gp_pdi)

REGISTER_FIELD32("eax", x86_dbg_viewstate.fcs_gpregs.gp_pax)
REGISTER_FIELD32("ecx", x86_dbg_viewstate.fcs_gpregs.gp_pcx)
REGISTER_FIELD32("edx", x86_dbg_viewstate.fcs_gpregs.gp_pdx)
REGISTER_FIELD32("ebx", x86_dbg_viewstate.fcs_gpregs.gp_pbx)
REGISTER_FIELD32("esp", x86_dbg_viewstate.fcs_gpregs.gp_psp)
REGISTER_FIELD32("ebp", x86_dbg_viewstate.fcs_gpregs.gp_pbp)
REGISTER_FIELD32("esi", x86_dbg_viewstate.fcs_gpregs.gp_psi)
REGISTER_FIELD32("edi", x86_dbg_viewstate.fcs_gpregs.gp_pdi)

REGISTER_FIELD16("ip", x86_dbg_viewstate.fcs_pip)
REGISTER_FIELD32("eip", x86_dbg_viewstate.fcs_pip)

REGISTER_FIELD16("flags", x86_dbg_viewstate.fcs_pflags)
REGISTER_FIELD32("eflags", x86_dbg_viewstate.fcs_pflags)

REGISTER_FIELD("cr0", x86_dbg_viewstate.fcs_coregs.co_cr0)
REGISTER_FIELD("cr2", x86_dbg_viewstate.fcs_coregs.co_cr2)
REGISTER_FIELD("cr3", x86_dbg_viewstate.fcs_coregs.co_cr3)
REGISTER_FIELD("cr4", x86_dbg_viewstate.fcs_coregs.co_cr4)

REGISTER_FIELD("dr0", x86_dbg_viewstate.fcs_drregs.dr_dr0)
REGISTER_FIELD("dr1", x86_dbg_viewstate.fcs_drregs.dr_dr1)
REGISTER_FIELD("dr2", x86_dbg_viewstate.fcs_drregs.dr_dr2)
REGISTER_FIELD("dr3", x86_dbg_viewstate.fcs_drregs.dr_dr3)
REGISTER_FIELD("dr6", x86_dbg_viewstate.fcs_drregs.dr_dr6)
REGISTER_FIELD("dr7", x86_dbg_viewstate.fcs_drregs.dr_dr7)

REGISTER_FIELD16("es", x86_dbg_viewstate.fcs_sgregs.sg_es)
REGISTER_FIELD16("cs", x86_dbg_viewstate.fcs_sgregs.sg_cs)
REGISTER_FIELD16("ss", x86_dbg_viewstate.fcs_sgregs.sg_ss)
REGISTER_FIELD16("ds", x86_dbg_viewstate.fcs_sgregs.sg_ds)
REGISTER_FIELD16("fs", x86_dbg_viewstate.fcs_sgregs.sg_fs)
REGISTER_FIELD16("gs", x86_dbg_viewstate.fcs_sgregs.sg_gs)
REGISTER_FIELD16("tr", x86_dbg_viewstate.fcs_sgregs.sg_tr)
REGISTER_FIELD16("ldtr", x86_dbg_viewstate.fcs_sgregs.sg_ldt)

REGISTER_FIELD16("gdt.limt", x86_dbg_viewstate.fcs_gdt.dt_limit)
REGISTER_FIELD("gdt.base", x86_dbg_viewstate.fcs_gdt.dt_base)

REGISTER_FIELD16("idt.limt", x86_dbg_viewstate.fcs_idt.dt_limit)
REGISTER_FIELD("idt.base", x86_dbg_viewstate.fcs_idt.dt_base)

/* A couple of helpful aliases */
REGISTER_FIELD(".", x86_dbg_viewstate.fcs_pip)
REGISTER_FIELD("pc", x86_dbg_viewstate.fcs_pip)
REGISTER_FIELD("sp", x86_dbg_viewstate.fcs_gpregs.gp_psp)

#ifdef __x86_64__


REGISTER_FIELD64("rax", x86_dbg_viewstate.fcs_gpregs.gp_pax)
REGISTER_FIELD64("rcx", x86_dbg_viewstate.fcs_gpregs.gp_pcx)
REGISTER_FIELD64("rdx", x86_dbg_viewstate.fcs_gpregs.gp_pdx)
REGISTER_FIELD64("rbx", x86_dbg_viewstate.fcs_gpregs.gp_pbx)
REGISTER_FIELD64("rsp", x86_dbg_viewstate.fcs_gpregs.gp_psp)
REGISTER_FIELD64("rbp", x86_dbg_viewstate.fcs_gpregs.gp_pbp)
REGISTER_FIELD64("rsi", x86_dbg_viewstate.fcs_gpregs.gp_psi)
REGISTER_FIELD64("rdi", x86_dbg_viewstate.fcs_gpregs.gp_pdi)
REGISTER_FIELD64("rip", x86_dbg_viewstate.fcs_pip)
REGISTER_FIELD64("rflags", x86_dbg_viewstate.fcs_pflags)

REGISTER_FIELD8("r8l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r8)[0])
REGISTER_FIELD8("r9l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r9)[0])
REGISTER_FIELD8("r10l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r10)[0])
REGISTER_FIELD8("r11l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r11)[0])
REGISTER_FIELD8("r12l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r12)[0])
REGISTER_FIELD8("r13l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r13)[0])
REGISTER_FIELD8("r14l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r14)[0])
REGISTER_FIELD8("r15l", ((u8 *)&x86_dbg_viewstate.fcs_gpregs.gp_r15)[0])

REGISTER_FIELD16("r8w", x86_dbg_viewstate.fcs_gpregs.gp_r8)
REGISTER_FIELD16("r9w", x86_dbg_viewstate.fcs_gpregs.gp_r9)
REGISTER_FIELD16("r10w", x86_dbg_viewstate.fcs_gpregs.gp_r10)
REGISTER_FIELD16("r11w", x86_dbg_viewstate.fcs_gpregs.gp_r11)
REGISTER_FIELD16("r12w", x86_dbg_viewstate.fcs_gpregs.gp_r12)
REGISTER_FIELD16("r13w", x86_dbg_viewstate.fcs_gpregs.gp_r13)
REGISTER_FIELD16("r14w", x86_dbg_viewstate.fcs_gpregs.gp_r14)
REGISTER_FIELD16("r15w", x86_dbg_viewstate.fcs_gpregs.gp_r15)

REGISTER_FIELD32("r8d", x86_dbg_viewstate.fcs_gpregs.gp_r8)
REGISTER_FIELD32("r9d", x86_dbg_viewstate.fcs_gpregs.gp_r9)
REGISTER_FIELD32("r10d", x86_dbg_viewstate.fcs_gpregs.gp_r10)
REGISTER_FIELD32("r11d", x86_dbg_viewstate.fcs_gpregs.gp_r11)
REGISTER_FIELD32("r12d", x86_dbg_viewstate.fcs_gpregs.gp_r12)
REGISTER_FIELD32("r13d", x86_dbg_viewstate.fcs_gpregs.gp_r13)
REGISTER_FIELD32("r14d", x86_dbg_viewstate.fcs_gpregs.gp_r14)
REGISTER_FIELD32("r15d", x86_dbg_viewstate.fcs_gpregs.gp_r15)

REGISTER_FIELD64("r8", x86_dbg_viewstate.fcs_gpregs.gp_r8)
REGISTER_FIELD64("r9", x86_dbg_viewstate.fcs_gpregs.gp_r9)
REGISTER_FIELD64("r10", x86_dbg_viewstate.fcs_gpregs.gp_r10)
REGISTER_FIELD64("r11", x86_dbg_viewstate.fcs_gpregs.gp_r11)
REGISTER_FIELD64("r12", x86_dbg_viewstate.fcs_gpregs.gp_r12)
REGISTER_FIELD64("r13", x86_dbg_viewstate.fcs_gpregs.gp_r13)
REGISTER_FIELD64("r14", x86_dbg_viewstate.fcs_gpregs.gp_r14)
REGISTER_FIELD64("r15", x86_dbg_viewstate.fcs_gpregs.gp_r15)

#endif /* __x86_64__ */

#undef REGISTER_FIELD64
#undef REGISTER_FIELD32
#undef REGISTER_FIELD16
#undef REGISTER_FIELD8
#undef REGISTER_FIELD
#undef REGISTER
