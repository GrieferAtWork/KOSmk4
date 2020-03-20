/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options",[]);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-Os");
]]]*/
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
#if 1                     /* TODO: Remove me */
#include "emuinstr.c.old" /* TODO: Remove me */
#else                     /* TODO: Remove me */
#ifndef GUARD_LIBVM86_EMUINSTR_C
#define GUARD_LIBVM86_EMUINSTR_C 1
#define DISABLE_BRANCH_PROFILING 1
#define CONFIG_LIBEMU86_WANT_16BIT 1
#define CONFIG_LIBEMU86_WANT_32BIT 0
#define CONFIG_LIBEMU86_WANT_64BIT 0
#define CONFIG_LIBEMU86_WANT_SEGREGID 1
#define __LIBEMU86_STATIC 1

#include "api.h"
/**/

#include <kos/except.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include "emulator.h"
#include "x86.h"


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

PRIVATE byte_t *CC libvm86_translate(vm86_state_t *__restrict self, void const *addr) {
	if (self->vr_trans)
		addr = (*self->vr_trans)(self, (void *)addr);
	return (byte_t *)addr;
}

DECL_END

#define EMU86_EMULATE_DECL         INTERN
#define EMU86_EMULATE_ATTR         NONNULL((1))
#define EMU86_EMULATE_RETURN       return VM86_SUCCESS
#define EMU86_EMULATE_RETURN_TYPE  int
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION(faultaddr, opcode, op_flags) return libvm86_intr(self, 0x6) /* Invalid Opcode */
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
#define REG8(id)                                                    \
	(*((id) >= 4 ? &self->vr_regs.vr_regdatab[(((id) - 4) * 4) + 1] \
	             : &self->vr_regs.vr_regdatab[(id) * 4]))
#define REG16(id) self->vr_regs.vr_regdataw[(id) * 2]
#define REG32(id) self->vr_regs.vr_regdatal[id]
#undef EMU86_EMULATE_TRANSLATEADDR_IS_NOOP
#define EMU86_EMULATE_TRANSLATEADDR(addr) libvm86_translate(self, addr)
#define EMU86_EMULATE_VM86 0 /* We're emulating realmode, not vm86 */
#define EMU86_EMULATE_CHECKUSER 0
#define EMU86_ISUSER() 0
#define EMU86_ISUSER_NOVM86() 0
#define EMU86_ISVM86() 0
#define EMU86_VALIDATE_READABLE(addr, num_bytes) (void)0
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes) (void)0
#define EMU86_GETFLAGS()            self->vr_regs.vr_eflags
#define EMU86_SETFLAGS(v)           (self->vr_regs.vr_eflags = (v))
#define EMU86_MSKFLAGS(mask, value) (self->vr_regs.vr_eflags = (self->vr_regs.vr_eflags & (mask)) | (value))
#define EMU86_GETPCPTR()            ((byte_t *)(uintptr_t)vm86_state_ip(self))
#define EMU86_SETPCPTR(v)           self->vr_regs.vr_ip = (u16)((uintptr_t)(v) - (self->vr_regs.vr_cs << 4))
#define EMU86_GETIPREG()            self->vr_regs.vr_ip
#define EMU86_SETIPREG(v)           self->vr_regs.vr_ip = (u16)(v)
#define EMU86_GETSTACKPTR()         ((byte_t *)(uintptr_t)vm86_state_sp(self))
#define EMU86_SETSTACKPTR(v)        self->vr_regs.vr_sp = (u16)((uintptr_t)(v) - (self->vr_regs.vr_cs << 4))
#define EMU86_GETSPREG()            self->vr_regs.vr_sp
#define EMU86_SETSPREG(v)           self->vr_regs.vr_sp = (u16)(v)
#undef EMU86_GETSEGBASE_IS_NOOP_DS
#undef EMU86_GETSEGBASE_IS_NOOP_ES
#undef EMU86_GETSEGBASE_IS_NOOP_CS
#undef EMU86_GETSEGBASE_IS_NOOP_SS
#undef EMU86_GETSEGBASE_IS_NOOP_FS
#undef EMU86_GETSEGBASE_IS_NOOP_GS
#define EMU86_GETSEGBASE(segid) self->vr_regs.vr_segments[segid]
#define EMU86_GETDSBASE()       self->vr_regs.vr_es
#define EMU86_GETESBASE()       self->vr_regs.vr_cs
#define EMU86_GETCSBASE()       self->vr_regs.vr_ss
#define EMU86_GETSSBASE()       self->vr_regs.vr_ds
#define EMU86_GETFSBASE()       self->vr_regs.vr_fs
#define EMU86_GETGSBASE()       self->vr_regs.vr_gs
#define EMU86_SEGADDR(setid, segoffset) (byte_t *)(uintptr_t)VM86_ADDR(setid, segoffset)
#define EMU86_GETCS()           self->vr_regs.vr_cs
#define EMU86_SETCS(v)          self->vr_regs.vr_cs = (u16)(v)
#define EMU86_GETSS()           self->vr_regs.vr_ss
#define EMU86_SETSS(v)          self->vr_regs.vr_ss = (u16)(v)
#define EMU86_GETFS()           self->vr_regs.vr_fs
#define EMU86_SETFS(v)          self->vr_regs.vr_fs = (u16)(v)
#define EMU86_GETGS()           self->vr_regs.vr_gs
#define EMU86_SETGS(v)          self->vr_regs.vr_gs = (u16)(v)
#define EMU86_GETDS()           self->vr_regs.vr_ds
#define EMU86_SETDS(v)          self->vr_regs.vr_ds = (u16)(v)
#define EMU86_GETES()           self->vr_regs.vr_es
#define EMU86_SETES(v)          self->vr_regs.vr_es = (u16)(v)
#define EMU86_EMULATE_PUSH(new_sp, num_bytes) (void)0 /* TODO: Check for stack segment overflow! */
#define EMU86_EMULATE_POP(old_sp, num_bytes) (void)0 /* TODO: Check for stack segment underflow! */
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

#define EMU86_EMULATE_THROW_BOUNDERR(bound_idx, bound_min, bound_max) \
	return libvm86_intr(self, 0x5) /* #BR */
#define EMU86_EMULATE_THROW_DIVIDE_ERROR() \
	return libvm86_intr(self, 0x0) /* #DE */
#define EMU86_EMULATE_RETURN_AFTER_STI \
	return VM86_INTR_ENABLED
#define EMU86_EMULATE_RETURN_AFTER_HLT_IF0 \
	return VM86_FROZEN
#define EMU86_EMULATE_RETURN_AFTER_HLT_IF1 \
	return VM86_HALTED


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
#endif /* TODO: Remove me */
