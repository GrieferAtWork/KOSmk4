/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options", []);
opt.removeif(e -> e.startswith("-O"));
opt.append("-Os");
]]]*/
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
#ifndef GUARD_LIBVM86_EMUINSTR_C
#define GUARD_LIBVM86_EMUINSTR_C 1
#define DISABLE_BRANCH_PROFILING
#define LIBEMU86_CONFIG_WANT_16BIT 1
#define LIBEMU86_CONFIG_WANT_32BIT 0
#define LIBEMU86_CONFIG_WANT_64BIT 0
#define __LIBEMU86_STATIC 1

#include "api.h"
/**/

#include <i386-kos/asm/cpu-flags.h>
#include <kos/except.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <stddef.h>

#include <libemu86/emu86.h>

#include "emulator.h"

DECL_BEGIN

/* Emulate a single instruction and update the program counter to point
 * to the next instruction.
 *  - In the case of string instructions, execute a single loop and place
 *    the program counter back at the start after updating loop counters.
 *  - This function does not check for pending interrupts prior to execution
 *    of any single instruction.
 *  - When `VM86_FROZEN' is returned, the program counter is also reset to
 *    the start of the responsible instruction.
 * @return: VM86_SUCCESS:      The single instruction was successfully executed.
 * @return: VM86_STOPPED:      The program counter was already placed at 0xffff:0xffff, or has jumped to that location.
 * @return: VM86_INTR_ENABLED: Interrupts should be enabled after the next call to `vm86_step()'
 * @return: * :                One of `VM86_*' */
INTDEF NONNULL((1)) int CC libvm86_step(vm86_state_t *__restrict self);

PRIVATE WUNUSED NONNULL((1)) byte_t *CC
libvm86_translate(vm86_state_t *__restrict self, void const *addr) {
	if (self->vr_trans)
		addr = (*self->vr_trans)(self, (void *)addr);
	return (byte_t *)addr;
}

DECL_END

#define EMU86_EMULATE_INB(portno, result)             \
	do {                                              \
		int error;                                    \
		error = libvm86_inb(self, portno, &(result)); \
		if (error != VM86_SUCCESS)                    \
			return error;                             \
	}	__WHILE0
#define EMU86_EMULATE_INW(portno, result)             \
	do {                                              \
		int error;                                    \
		error = libvm86_inw(self, portno, &(result)); \
		if (error != VM86_SUCCESS)                    \
			return error;                             \
	}	__WHILE0
#define EMU86_EMULATE_INL(portno, result)             \
	do {                                              \
		int error;                                    \
		error = libvm86_inl(self, portno, &(result)); \
		if (error != VM86_SUCCESS)                    \
			return error;                             \
	}	__WHILE0
#define EMU86_EMULATE_OUTB(portno, value)          \
	do {                                           \
		int error;                                 \
		error = libvm86_outb(self, portno, value); \
		if (error != VM86_SUCCESS)                 \
			return error;                          \
	}	__WHILE0
#define EMU86_EMULATE_OUTW(portno, value)          \
	do {                                           \
		int error;                                 \
		error = libvm86_outw(self, portno, value); \
		if (error != VM86_SUCCESS)                 \
			return error;                          \
	}	__WHILE0
#define EMU86_EMULATE_OUTL(portno, value)          \
	do {                                           \
		int error;                                 \
		error = libvm86_outl(self, portno, value); \
		if (error != VM86_SUCCESS)                 \
			return error;                          \
	}	__WHILE0


#define EMU86_EMULATE_DECL         INTERN
#define EMU86_EMULATE_ATTR         NONNULL((1))
#define EMU86_EMULATE_RETURN()     return VM86_SUCCESS
#define EMU86_EMULATE_RETURN_TYPE  int
#define EMU86_EMULATE_NOTHROW      /* nothing */
#define EMU86_EMULATE_CC           CC
#define EMU86_EMULATE_NAME         libvm86_step
#define EMU86_EMULATE_ARGS         vm86_state_t *__restrict self
#define EMU86_EMULATE_HELPER_ATTR  __ATTR_NONNULL((1))
#define EMU86_EMULATE_HELPER_ARGS  vm86_state_t *__restrict self
#define EMU86_EMULATE_HELPER_PARAM self
#define EMU86_EMULATE_TRY \
	__TRY
#define EMU86_EMULATE_EXCEPT        \
	__EXCEPT {                      \
		if (was_thrown(E_SEGFAULT)) \
			return VM86_SEGFAULT;   \
		RETHROW();                  \
	}
#define EMU86_EMULATE_GETOPFLAGS() EMU86_F_NORMAL

PRIVATE uintptr_t const vm86_breg_offset[8] = {
	[EMU86_R_AL] = offsetof(vm86_state_t, vr_regs.vr_al), /* %al */
	[EMU86_R_CL] = offsetof(vm86_state_t, vr_regs.vr_cl), /* %cl */
	[EMU86_R_DL] = offsetof(vm86_state_t, vr_regs.vr_dl), /* %dl */
	[EMU86_R_BL] = offsetof(vm86_state_t, vr_regs.vr_bl), /* %bl */
	[EMU86_R_AH] = offsetof(vm86_state_t, vr_regs.vr_ah), /* %ah */
	[EMU86_R_CH] = offsetof(vm86_state_t, vr_regs.vr_ch), /* %ch */
	[EMU86_R_DH] = offsetof(vm86_state_t, vr_regs.vr_dh), /* %dh */
	[EMU86_R_BH] = offsetof(vm86_state_t, vr_regs.vr_bh), /* %bh */
};

#define REG8(id)  (*((u8 *)self + vm86_breg_offset[id]))
#define REG16(id) self->vr_regs.vr_regdataw[(id) * 2]
#define REG32(id) self->vr_regs.vr_regdatal[id]
#undef EMU86_EMULATE_TRANSLATEADDR_IS_NOOP
#define EMU86_EMULATE_TRANSLATEADDR(addr) libvm86_translate(self, addr)
#define EMU86_EMULATE_CONFIG_VM86 0 /* We're emulating realmode, not vm86 */
#define EMU86_ISUSER() 0
#define EMU86_ISUSER_NOVM86() 0
#define EMU86_ISVM86() 0
#define EMU86_VALIDATE_READABLE(addr, num_bytes)  (void)0
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes)  (void)0
#define EMU86_VALIDATE_READWRITE(addr, num_bytes) (void)0
#define EMU86_VALIDATE_READABLE_IS_NOOP  1
#define EMU86_VALIDATE_WRITABLE_IS_NOOP  1
#define EMU86_VALIDATE_READWRITE_IS_NOOP 1
#define EMU86_GETFLAGS()            self->vr_regs.vr_eflags
#define EMU86_SETFLAGS(v)           (self->vr_regs.vr_eflags = (v))
#define EMU86_MSKFLAGS(mask, value) (self->vr_regs.vr_eflags = (self->vr_regs.vr_eflags & (mask)) | (value))
#define EMU86_GETPCPTR()            ((byte_t *)(uintptr_t)vm86_state_ip(self))
#define EMU86_SETPCPTR(v)           self->vr_regs.vr_ip = (u16)((uintptr_t)(v) - (self->vr_regs.vr_cs << 4))
#define EMU86_GETIPREG()            self->vr_regs.vr_ip
#define EMU86_SETIPREG(v)           self->vr_regs.vr_ip = (u16)(v)
#define EMU86_GETSTACKPTR()         ((byte_t *)(uintptr_t)vm86_state_sp(self))
#define EMU86_SETSTACKPTR(v)        self->vr_regs.vr_sp = (u16)((uintptr_t)(v) - (self->vr_regs.vr_ss << 4))
#define EMU86_GETSPREG()            self->vr_regs.vr_sp
#define EMU86_SETSPREG(v)           self->vr_regs.vr_sp = (u16)(v)
#undef EMU86_GETSEGBASE_IS_NOOP_DS
#undef EMU86_GETSEGBASE_IS_NOOP_ES
#undef EMU86_GETSEGBASE_IS_NOOP_CS
#undef EMU86_GETSEGBASE_IS_NOOP_SS
#undef EMU86_GETSEGBASE_IS_NOOP_FS
#undef EMU86_GETSEGBASE_IS_NOOP_GS
#define EMU86_GETSEGBASE(segid) self->vr_regs.vr_segments[segid]
#define EMU86_GETESBASE()       self->vr_regs.vr_es
#define EMU86_GETCSBASE()       self->vr_regs.vr_cs
#define EMU86_GETSSBASE()       self->vr_regs.vr_ss
#define EMU86_GETDSBASE()       self->vr_regs.vr_ds
#define EMU86_GETFSBASE()       self->vr_regs.vr_fs
#define EMU86_GETGSBASE()       self->vr_regs.vr_gs
#define EMU86_SEGADDR(setid, segoffset) (byte_t *)(uintptr_t)VM86_ADDR(setid, segoffset)
#define EMU86_GETES()           self->vr_regs.vr_es
#define EMU86_SETES(v)          self->vr_regs.vr_es = (u16)(v)
#define EMU86_GETCS()           self->vr_regs.vr_cs
#define EMU86_SETCS(v)          self->vr_regs.vr_cs = (u16)(v)
#define EMU86_GETSS()           self->vr_regs.vr_ss
#define EMU86_SETSS(v)          self->vr_regs.vr_ss = (u16)(v)
#define EMU86_GETDS()           self->vr_regs.vr_ds
#define EMU86_SETDS(v)          self->vr_regs.vr_ds = (u16)(v)
#define EMU86_GETFS()           self->vr_regs.vr_fs
#define EMU86_SETFS(v)          self->vr_regs.vr_fs = (u16)(v)
#define EMU86_GETGS()           self->vr_regs.vr_gs
#define EMU86_SETGS(v)          self->vr_regs.vr_gs = (u16)(v)
#define EMU86_EMULATE_PUSH(new_sp, num_bytes)             \
	do {                                                  \
		if unlikely(!vm86_state_canpush(self, num_bytes)) \
			return VM86_DOUBLE_FAULT;                     \
	}	__WHILE0
#define EMU86_EMULATE_POP(old_sp, num_bytes)             \
	do {                                                 \
		if unlikely(!vm86_state_canpop(self, num_bytes)) \
			return VM86_DOUBLE_FAULT;                    \
	}	__WHILE0
#define EMU86_GETSEG(regno)        self->vr_regs.vr_segments[regno]
#define EMU86_SETSEG(regno, value) self->vr_regs.vr_segments[regno] = (value)
#define EMU86_GETREGB(regno, ...)        REG8(regno)
#define EMU86_SETREGB(regno, value, ...) REG8(regno) = (u8)(value)
#define EMU86_GETREGW(regno)             REG16(regno)
#define EMU86_SETREGW(regno, value)      REG16(regno) = (u16)(value)
#define EMU86_GETREGL(regno)             REG32(regno)
#define EMU86_SETREGL(regno, value)      REG32(regno) = (u32)(value)
#define EMU86_GETIP()           self->vr_regs.vr_ip
#define EMU86_SETIP(v)          self->vr_regs.vr_ip = (u16)(v)
#define EMU86_GETEIP()          (u32)self->vr_regs.vr_ip
#define EMU86_SETEIP(v)         self->vr_regs.vr_ip = (u16)(u32)(v)
#define EMU86_GETAL()           self->vr_regs.vr_al
#define EMU86_GETCL()           self->vr_regs.vr_cl
#define EMU86_GETDL()           self->vr_regs.vr_dl
#define EMU86_GETBL()           self->vr_regs.vr_bl
#define EMU86_SETAL(v)          self->vr_regs.vr_al = (u8)(v)
#define EMU86_SETCL(v)          self->vr_regs.vr_cl = (u8)(v)
#define EMU86_SETDL(v)          self->vr_regs.vr_dl = (u8)(v)
#define EMU86_SETBL(v)          self->vr_regs.vr_bl = (u8)(v)
#define EMU86_GETAH()           self->vr_regs.vr_ah
#define EMU86_GETCH()           self->vr_regs.vr_ch
#define EMU86_GETDH()           self->vr_regs.vr_dh
#define EMU86_GETBH()           self->vr_regs.vr_bh
#define EMU86_SETAH(v)          self->vr_regs.vr_ah = (u8)(v)
#define EMU86_SETCH(v)          self->vr_regs.vr_ch = (u8)(v)
#define EMU86_SETDH(v)          self->vr_regs.vr_dh = (u8)(v)
#define EMU86_SETBH(v)          self->vr_regs.vr_bh = (u8)(v)
#define EMU86_GETAX()           self->vr_regs.vr_ax
#define EMU86_GETCX()           self->vr_regs.vr_cx
#define EMU86_GETDX()           self->vr_regs.vr_dx
#define EMU86_GETBX()           self->vr_regs.vr_bx
#define EMU86_GETSP()           self->vr_regs.vr_sp
#define EMU86_GETBP()           self->vr_regs.vr_bp
#define EMU86_GETSI()           self->vr_regs.vr_si
#define EMU86_GETDI()           self->vr_regs.vr_di
#define EMU86_SETAX(v)          self->vr_regs.vr_ax = (u16)(v)
#define EMU86_SETCX(v)          self->vr_regs.vr_cx = (u16)(v)
#define EMU86_SETDX(v)          self->vr_regs.vr_dx = (u16)(v)
#define EMU86_SETBX(v)          self->vr_regs.vr_bx = (u16)(v)
#define EMU86_SETSP(v)          self->vr_regs.vr_sp = (u16)(v)
#define EMU86_SETBP(v)          self->vr_regs.vr_bp = (u16)(v)
#define EMU86_SETSI(v)          self->vr_regs.vr_si = (u16)(v)
#define EMU86_SETDI(v)          self->vr_regs.vr_di = (u16)(v)
#define EMU86_GETEAX()          self->vr_regs.vr_eax
#define EMU86_GETECX()          self->vr_regs.vr_ecx
#define EMU86_GETEDX()          self->vr_regs.vr_edx
#define EMU86_GETEBX()          self->vr_regs.vr_ebx
#define EMU86_GETESP()          self->vr_regs.vr_esp
#define EMU86_GETEBP()          self->vr_regs.vr_ebp
#define EMU86_GETESI()          self->vr_regs.vr_esi
#define EMU86_GETEDI()          self->vr_regs.vr_edi
#define EMU86_SETEAX(v)         self->vr_regs.vr_eax = (u32)(v)
#define EMU86_SETECX(v)         self->vr_regs.vr_ecx = (u32)(v)
#define EMU86_SETEDX(v)         self->vr_regs.vr_edx = (u32)(v)
#define EMU86_SETEBX(v)         self->vr_regs.vr_ebx = (u32)(v)
#define EMU86_SETESP(v)         self->vr_regs.vr_esp = (u32)(v)
#define EMU86_SETEBP(v)         self->vr_regs.vr_ebp = (u32)(v)
#define EMU86_SETESI(v)         self->vr_regs.vr_esi = (u32)(v)
#define EMU86_SETEDI(v)         self->vr_regs.vr_edi = (u32)(v)
#define EMU86_GETPAX(...)       self->vr_regs.vr_ax
#define EMU86_GETPCX(...)       self->vr_regs.vr_cx
#define EMU86_GETPDX(...)       self->vr_regs.vr_dx
#define EMU86_GETPBX(...)       self->vr_regs.vr_bx
#define EMU86_GETPSP(...)       self->vr_regs.vr_sp
#define EMU86_GETPBP(...)       self->vr_regs.vr_bp
#define EMU86_GETPSI(...)       self->vr_regs.vr_si
#define EMU86_GETPDI(...)       self->vr_regs.vr_di
#define EMU86_SETPAX(v, ...)    self->vr_regs.vr_ax = (u16)(v)
#define EMU86_SETPCX(v, ...)    self->vr_regs.vr_cx = (u16)(v)
#define EMU86_SETPDX(v, ...)    self->vr_regs.vr_dx = (u16)(v)
#define EMU86_SETPBX(v, ...)    self->vr_regs.vr_bx = (u16)(v)
#define EMU86_SETPSP(v, ...)    self->vr_regs.vr_sp = (u16)(v)
#define EMU86_SETPBP(v, ...)    self->vr_regs.vr_bp = (u16)(v)
#define EMU86_SETPSI(v, ...)    self->vr_regs.vr_si = (u16)(v)
#define EMU86_SETPDI(v, ...)    self->vr_regs.vr_di = (u16)(v)

#define EMU86_EMULATE_SETUP()            \
	if (self->vr_regs.vr_cs == 0xffff && \
	    self->vr_regs.vr_ip == 0xffff)   \
		return VM86_STOPPED;

/* Define custom handlers for specific instructions. */
#define EMU86_EMULATE_RETURN_AFTER_STI() \
	return VM86_INTR_ENABLED
#define EMU86_EMULATE_RETURN_AFTER_HLT_IF0() \
	return VM86_FROZEN
#define EMU86_EMULATE_RETURN_AFTER_HLT_IF1() \
	return VM86_HALTED
#define EMU86_EMULATE_RETURN_AFTER_INT(intno) \
	return libvm86_intr(self, intno)
#define EMU86_EMULATE_RETURN_AFTER_INT1() \
	return libvm86_intr(self, 0x01) /* #DB */
#define EMU86_EMULATE_RETURN_AFTER_INT3() \
	return libvm86_intr(self, 0x03) /* #BP */
#define EMU86_EMULATE_RETURN_AFTER_INTO() \
	return libvm86_intr(self, 0x04) /* #OF */
#define EMU86_EMULATE_RETURN_AFTER_XEND() \
	return libvm86_intr(self, 0x0d) /* #GP */
#define EMU86_EMULATE_THROW_BOUNDERR(bound_idx, bound_min, bound_max) \
	return libvm86_intr(self, 0x05) /* #BR */
#define EMU86_EMULATE_THROW_SEGFAULT_UNALIGNED(addr, context, req_alignment) \
	return libvm86_intr(self, 0x0d) /* #GP */


/* Define how we want to handle exceptions */
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION() \
	return libvm86_intr(self, 0x6) /* Invalid Opcode */
/* Have all of the verbose bad-instruction return-paths alias the main one. */
#undef EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION_RMREG
#undef EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION
#undef EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION_RMREG
#undef EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM
#undef EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM_RMREG
#undef EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM
#undef EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM_RMREG
#undef EMU86_EMULATE_RETURN_UNEXPECTED_LOCK
#undef EMU86_EMULATE_RETURN_UNEXPECTED_LOCK_RMREG
#undef EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION
#undef EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION_RMREG
#define EMU86_EMULATE_THROW_DIVIDE_BY_ZERO_ALLOW_RETHROW 0
#define EMU86_EMULATE_THROW_DIVIDE_ERROR() \
	return libvm86_intr(self, 0x0) /* #DE */
#define EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(how, regno, offset, regval, regval2) \
	return libvm86_intr(self, (how) == E_ILLEGAL_INSTRUCTION_REGISTER_RDINV ||                \
	                          (how) == E_ILLEGAL_INSTRUCTION_REGISTER_WRINV                   \
	                          ? 0x06 /* #UD */                                                \
	                          : 0x0d /* #GP */)



/* Configure general library implementation */
#define EMU86_EMULATE_CONFIG_ONLY_MEMORY     0 /* Emulate all instructions */
#define EMU86_EMULATE_CONFIG_CHECKUSER       0 /* Disable user-access checks (realmode always has full permissions) */
#define EMU86_EMULATE_CONFIG_CHECKERROR      0 /* Don't check disabled instructions for usage errors (disabled
                                                * instruction don't exist for all that we're concerned  about) */
#define EMU86_EMULATE_CONFIG_ONLY_CHECKERROR 0 /* Any instruction not explicitly configured is enabled */

/* Configure ISA extensions */
#define EMU86_EMULATE_CONFIG_FSGSBASE_32BIT       0 /* [not enabled: fsgsbase isn't enabled in realmode] */
#define EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC 0 /* [not enabled: There is no user-space in realmode] */
/* Ignore this config option. - Only realmode code specifically written for KOS would be
 * able  to take advantage of this, and given that libvm86 is meant to emulate 3rd-party
 * assembly, that assembly probably would never make use of something like this. */
#if defined(CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS) && 0
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT           1 /* [enabled] Accept `lock' for shl/shr/sal/sar/rol/ror/rcl/rcr */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT2          1 /* [enabled] Accept `lock' for shld/shrd */
#define EMU86_EMULATE_CONFIG_LOCK_ARPL            1 /* [enabled] Accept `lock' for arpl */
#else /* CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT           0 /* [not enabled] Accept `lock' for shl/shr/sal/sar/rol/ror/rcl/rcr */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT2          0 /* [not enabled] Accept `lock' for shld/shrd */
#define EMU86_EMULATE_CONFIG_LOCK_ARPL            0 /* [not enabled] Accept `lock' for arpl */
#endif /* !CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS */

/* Configure how/if MSR register access should be emulated */
#define EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED          1 /* Emulate rdmsr for `IA32_TIME_STAMP_COUNTER' and `IA32_TSC_AUX' */
#define EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED_FSGSBASE 0 /* Don't emulate `IA32_FS_BASE' or `IA32_GS_BASE' */
#define EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED          0 /* Don't emulate wrmsr */

/* Disable  some instructions  who's use doesn't  make sense in  pure real-mode, or
 * that couldn't actually be emulated without also emulating all of protected-mode! */
#define EMU86_EMULATE_CONFIG_WANT_RDFSBASE 0 /* Realmode uses the segment index << 4 as segment base! */
#define EMU86_EMULATE_CONFIG_WANT_RDGSBASE 0 /* ... */
#define EMU86_EMULATE_CONFIG_WANT_WRFSBASE 0 /* ... */
#define EMU86_EMULATE_CONFIG_WANT_WRGSBASE 0 /* ... */
#define EMU86_EMULATE_CONFIG_WANT_SWAPGS   0 /* ... */
#define EMU86_EMULATE_CONFIG_WANT_MOV_DREG 0 /* We're not emulating debug registers, so disable this instruction! */

/* Actually enable emulation of mov-from-creg, but implement mov-to-creg  such
 * that any attempt to modify any of the bits from their fixed, constant state
 * will result in a #GP getting thrown. */
#define EMU86_EMULATE_CONFIG_WANT_MOV_CREG 1
#define EMU86_EMULATE_CONFIG_WANT_SMSW 1 /* Substituted by read from %cr0 */
#define EMU86_EMULATE_CONFIG_WANT_LMSW 1 /* Substituted by write to %cr0 */
#define EMU86_EMULATE_RDCR0() 0
#define EMU86_EMULATE_RDCR4() 0
#define EMU86_EMULATE_WRCR0(value)                     \
	do {                                               \
		if (EMU86_EMULATE_RDCR0() != (value))          \
			return libvm86_intr(self, 0x0d /* #GP */); \
	}	__WHILE0
#define EMU86_EMULATE_WRCR4(value)                     \
	do {                                               \
		if (EMU86_EMULATE_RDCR4() != (value))          \
			return libvm86_intr(self, 0x0d /* #GP */); \
	}	__WHILE0
/* %cr2 and %cr3 are treated as auxiliary general purpose registers. */
#define EMU86_EMULATE_RDCR2()      (u32)self->vr_regs.vr_cr2
#define EMU86_EMULATE_RDCR3()      (u32)self->vr_regs.vr_cr3
#define EMU86_EMULATE_WRCR2(value) (void)(self->vr_regs.vr_cr2 = (u32)(value))
#define EMU86_EMULATE_WRCR3(value) (void)(self->vr_regs.vr_cr3 = (u32)(value))

/* The TS-bit of our emulated %cr0 has a fixed value. - As such, `clts'
 * is either always a no-op,  or always causes a  #GP as the result  of
 * attempting to set a bit into an unexpected state. */
#define EMU86_EMULATE_CONFIG_WANT_CLTS 1
#if (EMU86_EMULATE_RDCR0() & CR0_TS) == 0
#define EMU86_EMULATE_CLTS() (void)0 /* no-op */
#else /* (EMU86_EMULATE_RDCR0() & CR0_TS) == 0 */
#define EMU86_EMULATE_CLTS() return libvm86_intr(self, 0x0d /* #GP */)
#endif /* (EMU86_EMULATE_RDCR0() & CR0_TS) != 0 */


#define EMU86_EMULATE_CONFIG_WANT_RDMSR 0 /* Arbitrary MSR access isn't allowed (but note that certain MSR are still emulated, though) */
#define EMU86_EMULATE_CONFIG_WANT_WRMSR 0 /* ... */

#define EMU86_EMULATE_CONFIG_WANT_RDPID  1 /* rdpid always returns 0 */
#define EMU86_EMULATE_RDPID()            0 /* This 0 to be exact! */
#define EMU86_EMULATE_RDTSCP(tsc_aux)    ((tsc_aux) = EMU86_EMULATE_RDPID(), __rdtsc())
#define EMU86_EMULATE_CONFIG_WANT_RDTSC  1 /* Enabled... */
#define EMU86_EMULATE_CONFIG_WANT_RDTSCP 1 /* Enabled... */

/* Disable various instruction used to configure P-mode registers. */
#define EMU86_EMULATE_CONFIG_WANT_SLDT   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_LLDT   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_STR    0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_LTR    0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_SGDT   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_LGDT   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_SIDT   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_LIDT   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_VERR   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_VERW   0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_INVLPG 0 /* Without paging, this instruction shouldn't exist */
#define EMU86_EMULATE_CONFIG_WANT_LAR    0 /* P-mode configure instruction */
#define EMU86_EMULATE_CONFIG_WANT_LSL    0 /* P-mode configure instruction */

#define EMU86_EMULATE_CONFIG_WANT_SYSCALL  0 /* Not valid outside of P-mode */
#define EMU86_EMULATE_CONFIG_WANT_SYSRET   0 /* Not valid outside of P-mode */
#define EMU86_EMULATE_CONFIG_WANT_SYSENTER 0 /* Not valid outside of P-mode */
#define EMU86_EMULATE_CONFIG_WANT_SYSEXIT  0 /* Not valid outside of P-mode */


/* Disable some instructions that would only add bloat */
#define EMU86_EMULATE_CONFIG_WANT_MONITOR 0
#define EMU86_EMULATE_CONFIG_WANT_MWAIT   0
#define EMU86_EMULATE_CONFIG_WANT_ENCLS   0
#define EMU86_EMULATE_CONFIG_WANT_ENCLU   0
#define EMU86_EMULATE_CONFIG_WANT_STGI    0
#define EMU86_EMULATE_CONFIG_WANT_CLGI    0
#define EMU86_EMULATE_CONFIG_WANT_LDMXCSR 0
#define EMU86_EMULATE_CONFIG_WANT_STMXCSR 0


#if defined(__KERNEL__) && 0
#include <kernel/printk.h>
#include <kernel/syslog.h>
#include <libdisasm/disassembler.h>

#if 0 /* Cause a crash on segfault */
#undef EMU86_EMULATE_TRY
#undef EMU86_EMULATE_EXCEPT
#endif


DECL_BEGIN
#undef EMU86_EMULATE_SETUP
#define EMU86_EMULATE_SETUP()            \
	if (self->vr_regs.vr_cs == 0xffff && \
	    self->vr_regs.vr_ip == 0xffff)   \
		return VM86_STOPPED;             \
	libvm86_loginstr(self)

PRIVATE NONNULL((1)) void CC
libvm86_loginstr(vm86_state_t *__restrict self) {
	struct disassembler da;
	size_t len;
	uint8_t *pc = (uint8_t *)vm86_state_ip(self);
	ptrdiff_t baseoff = 0;
	if (self->vr_trans) {
		uint8_t *newpc;
		newpc   = (uint8_t *)self->vr_trans(self, pc);
		baseoff = (ptrdiff_t)(pc - newpc);
		pc      = newpc;
	}
	disasm_init(&da, &syslog_printer, SYSLOG_LEVEL_RAW,
	            pc, DISASSEMBLER_TARGET_8086,
	            DISASSEMBLER_FNORMAL, baseoff);
	len = (size_t)disasm_print_line_nolf(&da);
	if (len < 60)
		printk(KERN_RAW "%*s", 60 - len, "");
	printk(KERN_RAW "\t# eax=%I32p, ecx=%I32p, edx=%I32p, ebx=%I32p, "
	                "esp=%I16p:%I16p, ebp:%I32p, esi:%I16p:%I32p, edi:%I16p:%I32p, "
	                "eip=%I16p:%I16p, efl=%I16p [",
	       self->vr_regs.vr_eax, self->vr_regs.vr_ecx,
	       self->vr_regs.vr_edx, self->vr_regs.vr_ebx,
	       self->vr_regs.vr_ss, self->vr_regs.vr_sp,
	       self->vr_regs.vr_ebp,
	       self->vr_regs.vr_ds, self->vr_regs.vr_esi,
	       self->vr_regs.vr_es, self->vr_regs.vr_edi,
	       self->vr_regs.vr_cs, self->vr_regs.vr_ip,
	       self->vr_regs.vr_flags);
	if (self->vr_regs.vr_flags & VM86_EFLAGS_CF)
		printk(KERN_RAW "CF");
	if (self->vr_regs.vr_flags & VM86_EFLAGS_PF)
		printk(KERN_RAW "%sPF", self->vr_regs.vr_flags & VM86_EFLAGS_CF ? "," : "");
	if (self->vr_regs.vr_flags & VM86_EFLAGS_ZF)
		printk(KERN_RAW "%sZF", self->vr_regs.vr_flags & (VM86_EFLAGS_CF | VM86_EFLAGS_PF) ? "," : "");
	if (self->vr_regs.vr_flags & VM86_EFLAGS_SF)
		printk(KERN_RAW "%sSF", self->vr_regs.vr_flags & (VM86_EFLAGS_CF | VM86_EFLAGS_PF | VM86_EFLAGS_ZF) ? "," : "");
	if (self->vr_regs.vr_flags & VM86_EFLAGS_OF)
		printk(KERN_RAW "%sOF", self->vr_regs.vr_flags & (VM86_EFLAGS_CF | VM86_EFLAGS_PF | VM86_EFLAGS_ZF | VM86_EFLAGS_SF) ? "," : "");
	if (self->vr_regs.vr_flags & VM86_EFLAGS_AF)
		printk(KERN_RAW "%sAF", self->vr_regs.vr_flags & (VM86_EFLAGS_CF | VM86_EFLAGS_PF | VM86_EFLAGS_ZF | VM86_EFLAGS_SF | VM86_EFLAGS_OF) ? "," : "");
	printk(KERN_RAW "]\n");
}
DECL_END
#endif /* __KERNEL__ */


/* Make sure that `THROW()' isn't used by the emulated code. */
#undef THROW
#define THROW  dont_use_THROW

/* Use relative include to force rebuild, and prevent -Wsystem-headers */
#if 1
#include "../../include/libemu86/emulate.c.inl"
#else
#include <libemu86/emulate.c.inl>
#endif

DECL_BEGIN
DEFINE_PUBLIC_ALIAS(vm86_step, libvm86_step);
DECL_END

#endif /* !GUARD_LIBVM86_EMUINSTR_C */
