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
#ifndef GUARD_LIBVM86_EMUINSTR_C
#define GUARD_LIBVM86_EMUINSTR_C 1
#define DISABLE_BRANCH_PROFILING 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/bit.h>
#include <hybrid/overflow.h>
#include <hybrid/unaligned.h>

#include <i386-kos/asm/cpu-cpuid.h>
#include <i386-kos/asm/cpu-flags.h>
#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <libvm86/api.h>
#include <libvm86/emulator.h>
#include <libvm86/intrin86.h>

#include "emulator.h"
#include "x86.h"

#ifdef __KERNEL__
#include <kernel/except.h>
#include <kernel/printk.h>
#include <kernel/syslog.h>

#include <libdisasm/disassembler.h>
#endif /* __KERNEL__ */

#if defined(__i386__) || defined(__x86_64__)
#include <asm/intrin-arith.h>
#include <asm/intrin.h>
#endif /* __i386__ || __x86_64__ */

#undef if /* Disable tracing */

DECL_BEGIN

#define F_SEGES   0x0000 /* ES segment override. */
#define F_SEGCS   0x0001 /* CS segment override. */
#define F_SEGSS   0x0002 /* SS segment override. */
#define F_SEGDS   0x0003 /* DS segment override. */
#define F_SEGFS   0x0004 /* FS segment override. */
#define F_SEGGS   0x0005 /* GS segment override. */
#define F_SEGMASK 0x0007 /* Segment override mask */
#define F_f0      0x0008 /* The 0xf0 prefix is being used. */
#define F_66      0x0010 /* The 0x66 prefix is being used. */
#define F_67      0x0020 /* The 0x67 prefix is being used. */
#define F_f2      0x0040 /* The 0xf2 prefix is being used. */
#define F_f3      0x0080 /* The 0xf3 prefix is being used. */

#define F_OP32  F_66
#define F_AD32  F_67
#define F_LOCK  F_f0
#define F_REPNE F_f2
#define F_REP   F_f3

LOCAL NONNULL((1, 2)) int (CC libvm86_read_pcbyte)(vm86_state_t *__restrict self, uint8_t *__restrict result);
LOCAL NONNULL((1, 2)) int (CC libvm86_read_pcword)(vm86_state_t *__restrict self, uint16_t *__restrict result);
LOCAL NONNULL((1, 2)) int (CC libvm86_read_pcdword)(vm86_state_t *__restrict self, uint32_t *__restrict result);
LOCAL NONNULL((1)) int (CC libvm86_store_string_byte)(vm86_state_t *__restrict self, uint8_t value);
LOCAL NONNULL((1)) int (CC libvm86_store_string_word)(vm86_state_t *__restrict self, uint16_t value);
LOCAL NONNULL((1)) int (CC libvm86_store_string_dword)(vm86_state_t *__restrict self, uint32_t value);
LOCAL NONNULL((1, 2)) int (CC libvm86_load_string_byte)(vm86_state_t *__restrict self, uint8_t *__restrict presult);
LOCAL NONNULL((1, 2)) int (CC libvm86_load_string_word)(vm86_state_t *__restrict self, uint16_t *__restrict presult);
LOCAL NONNULL((1, 2)) int (CC libvm86_load_string_dword)(vm86_state_t *__restrict self, uint32_t *__restrict presult);
LOCAL NONNULL((1, 2)) int (CC libvm86_load_string_dst_byte)(vm86_state_t *__restrict self, uint8_t *__restrict presult);
LOCAL NONNULL((1, 2)) int (CC libvm86_load_string_dst_word)(vm86_state_t *__restrict self, uint16_t *__restrict presult);
LOCAL NONNULL((1, 2)) int (CC libvm86_load_string_dst_dword)(vm86_state_t *__restrict self, uint32_t *__restrict presult);
LOCAL NONNULL((1)) int (CC libvm86_pushw)(vm86_state_t *__restrict self, uint16_t value);
LOCAL NONNULL((1)) int (CC libvm86_pushl)(vm86_state_t *__restrict self, uint32_t value);
LOCAL NONNULL((1, 2)) int (CC libvm86_popw)(vm86_state_t *__restrict self, uint16_t *__restrict presult);
LOCAL NONNULL((1, 2)) int (CC libvm86_popl)(vm86_state_t *__restrict self, uint32_t *__restrict presult);
LOCAL NONNULL((1)) int (CC libvm86_popw_void)(vm86_state_t *__restrict self);
LOCAL NONNULL((1)) int (CC libvm86_popl_void)(vm86_state_t *__restrict self);

#define libvm86_store_string_byte(self, value, op_flags)       libvm86_store_string_byte(self, value)
#define libvm86_store_string_word(self, value, op_flags)       libvm86_store_string_word(self, value)
#define libvm86_store_string_dword(self, value, op_flags)      libvm86_store_string_dword(self, value)
#define libvm86_load_string_byte(self, presult, op_flags)      libvm86_load_string_byte(self, presult)
#define libvm86_load_string_word(self, presult, op_flags)      libvm86_load_string_word(self, presult)
#define libvm86_load_string_dword(self, presult, op_flags)     libvm86_load_string_dword(self, presult)
#define libvm86_load_string_dst_byte(self, presult, op_flags)  libvm86_load_string_dst_byte(self, presult)
#define libvm86_load_string_dst_word(self, presult, op_flags)  libvm86_load_string_dst_word(self, presult)
#define libvm86_load_string_dst_dword(self, presult, op_flags) libvm86_load_string_dst_dword(self, presult)
#define libvm86_pushw(self, value, op_flags)                   libvm86_pushw(self, value)
#define libvm86_pushl(self, value, op_flags)                   libvm86_pushl(self, value)
#define libvm86_popw(self, presult, op_flags)                  libvm86_popw(self, presult)
#define libvm86_popl(self, presult, op_flags)                  libvm86_popl(self, presult)
#define libvm86_popw_void(self, op_flags)                      libvm86_popw_void(self)
#define libvm86_popl_void(self, op_flags)                      libvm86_popl_void(self)


#if 1
#define REG8(id)                                                      \
	(*((id) >= 4 ? &(self)->vr_regs.vr_regdatab[(((id) - 4) * 4) + 1] \
	             : &(self)->vr_regs.vr_regdatab[(id) * 4]))
#define REG16(id) (self)->vr_regs.vr_regdataw[(id) * 2]
#define REG32(id) (self)->vr_regs.vr_regdatal[id]
#define SEG(id)   (self)->vr_regs.vr_segments[id]
#else
#define REG8(id)                                                                \
	(*((id) >= 4 ? ((uint8_t *)(((uint32_t *)&(self)->vr_regs) + ((id)-4))) + 1 \
	             : ((uint8_t *)(((uint32_t *)&(self)->vr_regs) + (id)))))
#define REG16(id) \
	(*(uint16_t *)(((uint32_t *)&(self)->vr_regs) + (id)))
#define REG32(id) \
	(((uint32_t *)&(self)->vr_regs)[id])
#define SEG(id) \
	(((uint16_t *)&(self)->vr_regs.vr_es)[id])
#endif

#define R_AX  0 /* Accumulator. */
#define R_CX  1 /* Counter register. */
#define R_DX  2 /* General purpose d-register. */
#define R_BX  3 /* General purpose b-register. */
#define R_SP  4 /* Stack pointer. */
#define R_BP  5 /* Stack base pointer. */
#define R_SI  6 /* Source pointer. */
#define R_DI  7 /* Destination pointer. */

struct modrm {
	uint32_t  mi_offset; /* Memory address. */
#define MODRM_REGISTER 0
#define MODRM_MEMORY   1
	/* EXAMPLES:
	 *  - mov $42, %mi_rm                                   # mi_type == MODRM_REGISTER
	 *  - mov $42, mi_offset(%mi_rm)                        # mi_type == MODRM_MEMORY
	 *  - mov %mi_reg, mi_offset(%mi_rm,%mi_index,mi_shift) # mi_type == MODRM_MEMORY
	 */
	uint8_t   mi_type;   /* mod R/M type (One of `MODRM_*') */
	uint8_t   mi_reg;    /* Secondary register operand, or instruction sub-class. */
	uint8_t   mi_rm;     /* Base register (or 0xff when not set). */
	uint8_t   mi_index;  /* Index register (or 0xff when not set). */
	uint8_t   mi_shift;  /* Index shift (or 0). */
};

INTDEF NONNULL((1, 2)) int (CC libvm86_modrm_decode)(vm86_state_t *__restrict self, struct modrm *__restrict info, uint16_t op_flags);
LOCAL WUNUSED NONNULL((1, 2)) void *(CC libvm86_modrm_getaddr)(vm86_state_t *__restrict self, struct modrm const *__restrict info, uint16_t op_flags);
LOCAL NONNULL((1, 2, 3)) int (CC libvm86_modrm_readb)(vm86_state_t *__restrict self, struct modrm const *__restrict info, uint8_t *__restrict presult, uint16_t op_flags);
LOCAL NONNULL((1, 2, 3)) int (CC libvm86_modrm_readw)(vm86_state_t *__restrict self, struct modrm const *__restrict info, uint16_t *__restrict presult, uint16_t op_flags);
LOCAL NONNULL((1, 2, 3)) int (CC libvm86_modrm_readl)(vm86_state_t *__restrict self, struct modrm const *__restrict info, uint32_t *__restrict presult, uint16_t op_flags);
LOCAL NONNULL((1, 2)) int (CC libvm86_modrm_writeb)(vm86_state_t *__restrict self, struct modrm const *__restrict info, uint8_t value, uint16_t op_flags);
LOCAL NONNULL((1, 2)) int (CC libvm86_modrm_writew)(vm86_state_t *__restrict self, struct modrm const *__restrict info, uint16_t value, uint16_t op_flags);
LOCAL NONNULL((1, 2)) int (CC libvm86_modrm_writel)(vm86_state_t *__restrict self, struct modrm const *__restrict info, uint32_t value, uint16_t op_flags);



#if !defined(__INTELLISENSE__) || 1
LOCAL NONNULL((1, 2)) int
(CC libvm86_read_pcbyte)(vm86_state_t *__restrict self,
                         uint8_t *__restrict presult) {
	uint8_t *pc, value;
	pc = (uint8_t *)vm86_state_ip(self);
	if (self->vr_trans)
		pc = (uint8_t *)self->vr_trans(self, pc);
	TRY {
		value = *pc;
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	self->vr_regs.vr_ip += 1;
	*presult = value;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_read_pcword)(vm86_state_t *__restrict self,
                         uint16_t *__restrict presult) {
	uint16_t *pc, value;
	pc = (uint16_t *)vm86_state_ip(self);
	if (self->vr_trans)
		pc = (uint16_t *)self->vr_trans(self, pc);
	TRY {
		value = UNALIGNED_GET16(pc);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	self->vr_regs.vr_ip += 2;
	*presult = value;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_read_pcdword)(vm86_state_t *__restrict self,
                          uint32_t *__restrict presult) {
	uint32_t *pc, value;
	pc = (uint32_t *)vm86_state_ip(self);
	if (self->vr_trans)
		pc = (uint32_t *)self->vr_trans(self, pc);
	TRY {
		value = UNALIGNED_GET32(pc);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	self->vr_regs.vr_ip += 4;
	*presult = value;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int
(CC libvm86_store_string_byte)(vm86_state_t *__restrict self,
                               uint8_t value) {
	uint8_t *addr;
	addr = (uint8_t *)vm86_state_di(self);
	if (self->vr_trans)
		addr = (uint8_t *)self->vr_trans(self, addr);
	TRY {
		*addr = value;
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_edi -= 1;
	} else {
		self->vr_regs.vr_edi += 1;
	}
	self->vr_regs.vr_edi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int
(CC libvm86_store_string_word)(vm86_state_t *__restrict self,
                               uint16_t value) {
	uint16_t *addr;
	addr = (uint16_t *)vm86_state_di(self);
	if (self->vr_trans)
		addr = (uint16_t *)self->vr_trans(self, addr);
	TRY {
		UNALIGNED_SET16(addr, value);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_edi -= 2;
	} else {
		self->vr_regs.vr_edi += 2;
	}
	self->vr_regs.vr_edi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int
(CC libvm86_store_string_dword)(vm86_state_t *__restrict self,
                                uint32_t value) {
	uint32_t *addr;
	addr = (uint32_t *)vm86_state_di(self);
	if (self->vr_trans)
		addr = (uint32_t *)self->vr_trans(self, addr);
	TRY {
		UNALIGNED_SET32(addr, value);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_edi -= 4;
	} else {
		self->vr_regs.vr_edi += 4;
	}
	self->vr_regs.vr_edi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_load_string_byte)(vm86_state_t *__restrict self,
                              uint8_t *__restrict presult) {
	uint8_t *addr, value;
	addr = (uint8_t *)vm86_state_si(self);
	if (self->vr_trans)
		addr = (uint8_t *)self->vr_trans(self, addr);
	TRY {
		value = *addr;
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_esi -= 1;
	} else {
		self->vr_regs.vr_esi += 1;
	}
	self->vr_regs.vr_esi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_load_string_word)(vm86_state_t *__restrict self,
                              uint16_t *__restrict presult) {
	uint16_t *addr, value;
	addr = (uint16_t *)vm86_state_si(self);
	if (self->vr_trans)
		addr = (uint16_t *)self->vr_trans(self, addr);
	TRY {
		value = UNALIGNED_GET16(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_esi -= 2;
	} else {
		self->vr_regs.vr_esi += 2;
	}
	self->vr_regs.vr_esi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_load_string_dword)(vm86_state_t *__restrict self,
                               uint32_t *__restrict presult) {
	uint32_t *addr, value;
	addr = (uint32_t *)vm86_state_si(self);
	if (self->vr_trans)
		addr = (uint32_t *)self->vr_trans(self, addr);
	TRY {
		value = UNALIGNED_GET32(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_esi -= 4;
	} else {
		self->vr_regs.vr_esi += 4;
	}
	self->vr_regs.vr_esi &= 0xffff;
	return VM86_SUCCESS;
}


LOCAL NONNULL((1, 2)) int
(CC libvm86_load_string_dst_byte)(vm86_state_t *__restrict self,
                                  uint8_t *__restrict presult) {
	uint8_t *addr, value;
	addr = (uint8_t *)vm86_state_di(self);
	if (self->vr_trans)
		addr = (uint8_t *)self->vr_trans(self, addr);
	TRY {
		value = *addr;
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_edi -= 1;
	} else {
		self->vr_regs.vr_edi += 1;
	}
	self->vr_regs.vr_edi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_load_string_dst_word)(vm86_state_t *__restrict self,
                                  uint16_t *__restrict presult) {
	uint16_t *addr, value;
	addr = (uint16_t *)vm86_state_di(self);
	if (self->vr_trans)
		addr = (uint16_t *)self->vr_trans(self, addr);
	TRY {
		value = UNALIGNED_GET16(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_edi -= 2;
	} else {
		self->vr_regs.vr_edi += 2;
	}
	self->vr_regs.vr_edi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_load_string_dst_dword)(vm86_state_t *__restrict self,
                                   uint32_t *__restrict presult) {
	uint32_t *addr, value;
	addr = (uint32_t *)vm86_state_di(self);
	if (self->vr_trans)
		addr = (uint32_t *)self->vr_trans(self, addr);
	TRY {
		value = UNALIGNED_GET32(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	if (self->vr_regs.vr_flags & DF) {
		self->vr_regs.vr_edi -= 4;
	} else {
		self->vr_regs.vr_edi += 4;
	}
	self->vr_regs.vr_edi &= 0xffff;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int
(CC libvm86_pushw)(vm86_state_t *__restrict self,
                   uint16_t value) {
	uint16_t *addr;
	if unlikely(!vm86_state_hasstack(self, 2))
		return VM86_DOUBLE_FAULT;
	addr = (uint16_t *)(uintptr_t)(vm86_state_sp(self) - 2);
	if (self->vr_trans)
		addr = (uint16_t *)self->vr_trans(self, addr);
	TRY {
		UNALIGNED_SET16(addr, value);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	self->vr_regs.vr_esp -= 2;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int
(CC libvm86_pushl)(vm86_state_t *__restrict self,
                   uint32_t value) {
	uint32_t *addr;
	if unlikely(!vm86_state_hasstack(self, 4))
		return VM86_DOUBLE_FAULT;
	addr = (uint32_t *)(uintptr_t)(vm86_state_sp(self) - 4);
	if (self->vr_trans)
		addr = (uint32_t *)self->vr_trans(self, addr);
	TRY {
		UNALIGNED_SET32(addr, value);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	self->vr_regs.vr_esp -= 4;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_popw)(vm86_state_t *__restrict self,
                  uint16_t *__restrict presult) {
	uint16_t *addr, value;
	if unlikely(self->vr_regs.vr_sp < 2)
		return VM86_DOUBLE_FAULT;
	addr = (uint16_t *)vm86_state_sp(self);
	if (self->vr_trans)
		addr = (uint16_t *)self->vr_trans(self, addr);
	TRY {
		value = UNALIGNED_GET16(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	self->vr_regs.vr_esp += 2;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int
(CC libvm86_popl)(vm86_state_t *__restrict self,
                  uint32_t *__restrict presult) {
	uint32_t *addr, value;
	if unlikely(self->vr_regs.vr_sp < 4)
		return VM86_DOUBLE_FAULT;
	addr = (uint32_t *)vm86_state_sp(self);
	if (self->vr_trans)
		addr = (uint32_t *)self->vr_trans(self, addr);
	TRY {
		value = UNALIGNED_GET32(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	self->vr_regs.vr_esp += 4;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int
(CC libvm86_popw_void)(vm86_state_t *__restrict self) {
	if unlikely(self->vr_regs.vr_sp < 2)
		return VM86_DOUBLE_FAULT;
	self->vr_regs.vr_esp += 2;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int
(CC libvm86_popl_void)(vm86_state_t *__restrict self) {
	if unlikely(self->vr_regs.vr_sp < 4)
		return VM86_DOUBLE_FAULT;
	self->vr_regs.vr_esp += 4;
	return VM86_SUCCESS;
}

#define MODRM_MOD_MASK  0xc0 /* 0b11000000 */
#define MODRM_REG_MASK  0x38 /* 0b00111000 */
#define MODRM_RM_MASK   0x07 /* 0b00000111 */
#define MODRM_MOD_SHIFT 6
#define MODRM_REG_SHIFT 3
#define MODRM_RM_SHIFT  0
#define MODRM_GETMOD(x) (((x)&MODRM_MOD_MASK) >> MODRM_MOD_SHIFT)
#define MODRM_GETREG(x) (((x)&MODRM_REG_MASK) >> MODRM_REG_SHIFT)
#define MODRM_GETRM(x)  (((x)&MODRM_RM_MASK) >> MODRM_RM_SHIFT)

INTERN NONNULL((1, 2)) int CC
libvm86_modrm_decode(vm86_state_t *__restrict self,
                     struct modrm *__restrict info,
                     uint16_t op_flags) {
	uint8_t rmbyte;
	int error;
	error = libvm86_read_pcbyte(self, &rmbyte);
	if unlikely(error != VM86_SUCCESS)
		goto err;
	info->mi_reg = MODRM_GETREG(rmbyte);
	if (op_flags & F_AD32) {
		uint8_t sibbyte;
		info->mi_rm = MODRM_GETRM(rmbyte);
		switch (rmbyte & MODRM_MOD_MASK) {

		case 0x0 << MODRM_MOD_SHIFT:
			/* R/M */
			info->mi_type = MODRM_MEMORY;
			if (info->mi_rm == R_BP) {
				info->mi_rm     = 0xff;
				info->mi_index  = 0xff;
				error = libvm86_read_pcdword(self, &info->mi_offset);
				if unlikely(error != VM86_SUCCESS)
					goto err;
			} else if (info->mi_rm == R_SP) {
				error = libvm86_read_pcbyte(self, &sibbyte);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				info->mi_offset = 0;
parse_sib_byte:
				info->mi_shift = MODRM_GETMOD(sibbyte);
				info->mi_index = MODRM_GETREG(sibbyte);
				info->mi_rm    = MODRM_GETRM(sibbyte);
				if (info->mi_index == R_SP)
					info->mi_index = 0xff;
				if ((info->mi_rm == R_BP) &&
				    (rmbyte & MODRM_MOD_MASK) == (0x0 << MODRM_MOD_SHIFT))
					info->mi_rm = 0xff;
			} else {
				info->mi_index  = 0xff;
				info->mi_offset = 0;
			}
			break;

		case 0x1 << MODRM_MOD_SHIFT: {
			uint8_t temp;
			/* R/M + 1-byte offset */
			info->mi_type  = MODRM_MEMORY;
			info->mi_index = 0xff;
			if (info->mi_rm == R_SP) {
				error = libvm86_read_pcbyte(self, &sibbyte);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_read_pcbyte(self, &temp);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				info->mi_offset = (uint32_t)(int32_t)(int8_t)temp;
				goto parse_sib_byte;
			}
			error = libvm86_read_pcbyte(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			info->mi_offset = (uint32_t)(int32_t)(int8_t)temp;
		}	break;

		case 0x2 << MODRM_MOD_SHIFT:
			/* R/M + 4-byte offset */
			info->mi_type  = MODRM_MEMORY;
			info->mi_index = 0xff;
			if (info->mi_rm == R_SP) {
				error = libvm86_read_pcbyte(self, &sibbyte);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_read_pcdword(self, &info->mi_offset);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				goto parse_sib_byte;
			}
			error = libvm86_read_pcdword(self, &info->mi_offset);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			break;

		case 0x3 << MODRM_MOD_SHIFT:
			/* Register operand. */
			info->mi_type  = MODRM_REGISTER;
			info->mi_index = 0xff;
			break;

		default: __builtin_unreachable();
		}
	} else {
		info->mi_shift = 0;
		if ((rmbyte & MODRM_MOD_MASK) == (0x3 << MODRM_MOD_SHIFT)) {
			/* Register operand. */
			info->mi_rm    = MODRM_GETRM(rmbyte);
			info->mi_type  = MODRM_REGISTER;
			info->mi_index = 0xff;
		} else {
			info->mi_offset = 0;
			info->mi_type   = MODRM_MEMORY;
			switch (MODRM_GETRM(rmbyte)) {
			case 0: /* [BX + SI] */
				info->mi_rm    = R_BX;
				info->mi_index = R_SI;
				break;
			case 1: /* [BX + DI] */
				info->mi_rm    = R_BX;
				info->mi_index = R_DI;
				break;
			case 2: /* [BP + SI] */
				info->mi_rm    = R_BP;
				info->mi_index = R_SI;
				break;
			case 3: /* [BP + DI] */
				info->mi_rm    = R_BP;
				info->mi_index = R_DI;
				break;
			case 4: /* [SI] */
				info->mi_rm    = R_SI;
				info->mi_index = 0xff;
				break;
			case 5: /* [DI] */
				info->mi_rm    = R_DI;
				info->mi_index = 0xff;
				break;
			case 6: /* [BP] */
				info->mi_index = 0xff;
				info->mi_rm    = R_BP;
				if ((rmbyte & MODRM_MOD_MASK) == (0x0 << MODRM_MOD_SHIFT)) { /* [disp16] */
					uint16_t temp;
					info->mi_rm = 0xff;
					error = libvm86_read_pcword(self, &temp);
					if likely(error == VM86_SUCCESS)
						info->mi_offset = (uint32_t)(int32_t)(int16_t)temp;
					return error;
				}
				break;
			case 7: /* [BX] */
				info->mi_rm    = R_BX;
				info->mi_index = 0xff;
				break;
			default: __builtin_unreachable();
			}
			if ((rmbyte & MODRM_MOD_MASK) == (0x1 << MODRM_MOD_SHIFT)) {
				uint8_t temp;
				/* [... + disp8] */
				error = libvm86_read_pcbyte(self, &temp);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				info->mi_offset = (uint32_t)(int32_t)(int8_t)temp;
			} else if ((rmbyte & MODRM_MOD_MASK) == (0x2 << MODRM_MOD_SHIFT)) {
				/* [... + disp16] */
				uint16_t temp;
				error = libvm86_read_pcword(self, &temp);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				info->mi_offset = (uint32_t)(int32_t)(int16_t)temp;
			}
		}
	}
	return VM86_SUCCESS;
err:
	return error;
}

LOCAL WUNUSED NONNULL((1, 2)) void *CC
libvm86_modrm_getaddr(vm86_state_t *__restrict self,
                      struct modrm const *__restrict info,
                      uint16_t op_flags) {
	uintptr_t addr;
	if (info->mi_type == MODRM_REGISTER)
		return &REG32(info->mi_rm);
	addr = info->mi_offset;
	if (info->mi_rm != 0xff)
		addr += REG16(info->mi_rm);
	if (info->mi_index != 0xff)
		addr += REG16(info->mi_index) << info->mi_shift;
	addr = VM86_ADDR(SEG(op_flags & F_SEGMASK), addr & 0xffff);
	if (self->vr_trans)
		addr = (uintptr_t)(*self->vr_trans)(self, (void *)addr);
	return (void *)addr;
}

LOCAL NONNULL((1, 2, 3)) int CC
libvm86_modrm_readb(vm86_state_t *__restrict self,
                    struct modrm const *__restrict info,
                    uint8_t *__restrict presult,
                    uint16_t op_flags) {
	if (info->mi_type == MODRM_REGISTER) {
		*presult = REG8(info->mi_rm);
	} else {
		uint8_t *addr, value;
		addr = (uint8_t *)libvm86_modrm_getaddr(self, info, op_flags);
		TRY {
			value = *addr;
		} EXCEPT {
			if (!WAS_SEGFAULT_THROWN())
				RETHROW();
			return VM86_SEGFAULT;
		}
		*presult = value;
	}
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2, 3)) int CC
libvm86_modrm_readw(vm86_state_t *__restrict self,
                    struct modrm const *__restrict info,
                    uint16_t *__restrict presult,
                    uint16_t op_flags) {
	uint16_t *addr, value;
	addr = (uint16_t *)libvm86_modrm_getaddr(self, info, op_flags);
	TRY {
		value = UNALIGNED_GET16(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2, 3)) int CC
libvm86_modrm_readl(vm86_state_t *__restrict self,
                    struct modrm const *__restrict info,
                    uint32_t *__restrict presult,
                    uint16_t op_flags) {
	uint32_t *addr, value;
	addr = (uint32_t *)libvm86_modrm_getaddr(self, info, op_flags);
	TRY {
		value = UNALIGNED_GET32(addr);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	*presult = value;
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int CC
libvm86_modrm_writeb(vm86_state_t *__restrict self,
                     struct modrm const *__restrict info,
                     uint8_t value, uint16_t op_flags) {
	if (info->mi_type == MODRM_REGISTER) {
		REG8(info->mi_rm) = value;
	} else {
		uint8_t *addr;
		addr = (uint8_t *)libvm86_modrm_getaddr(self, info, op_flags);
		TRY {
			*addr = value;
		} EXCEPT {
			if (!WAS_SEGFAULT_THROWN())
				RETHROW();
			return VM86_SEGFAULT;
		}
	}
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int CC
libvm86_modrm_writew(vm86_state_t *__restrict self,
                     struct modrm const *__restrict info,
                     uint16_t value, uint16_t op_flags) {
	if (info->mi_type == MODRM_REGISTER) {
		REG32(info->mi_rm) = value;
	} else {
		uint16_t *addr;
		addr = (uint16_t *)libvm86_modrm_getaddr(self, info, op_flags);
		TRY {
			UNALIGNED_SET16(addr, value);
		} EXCEPT {
			if (!WAS_SEGFAULT_THROWN())
				RETHROW();
			return VM86_SEGFAULT;
		}
	}
	return VM86_SUCCESS;
}

LOCAL NONNULL((1, 2)) int CC
libvm86_modrm_writel(vm86_state_t *__restrict self,
                     struct modrm const *__restrict info,
                     uint32_t value, uint16_t op_flags) {
	uint32_t *addr;
	addr = (uint32_t *)libvm86_modrm_getaddr(self, info, op_flags);
	TRY {
		UNALIGNED_SET32(addr, value);
	} EXCEPT {
		if (!WAS_SEGFAULT_THROWN())
			RETHROW();
		return VM86_SEGFAULT;
	}
	return VM86_SUCCESS;
}

#endif


PRIVATE ATTR_ALIGNED(4)
char const cpuid_brand_string[48] = {
	'K','O','S',' ','l','i','b','v','m','8','6',' ',
	'e','m','u','l','a','t','o','r',' ','(',
#ifdef __KERNEL__
	'k','e','r','n',
#else /* __KERNEL__ */
	'u','s','e','r',
#endif /* !__KERNEL__ */
	')',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '
};



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
INTERN NONNULL((1)) int CC libvm86_step(vm86_state_t *__restrict self) {
	int error;
	uint8_t opcode;
	uint16_t op_flags = F_SEGDS;
	uint16_t ip_start = self->vr_regs.vr_ip;
	struct modrm mod;

	if (self->vr_regs.vr_cs == 0xffff &&
	    self->vr_regs.vr_ip == 0xffff)
		return VM86_STOPPED;
#if defined(__KERNEL__) && 0
	{
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
		                "esp=%I16p:%I16p, ebp:%I32p, esi:%I16p:%I16p, edi:%I16p:%I16p, "
		                "eip=%I16p:%I16p, efl=%I16p [",
		       self->vr_regs.vr_eax, self->vr_regs.vr_ecx,
		       self->vr_regs.vr_edx, self->vr_regs.vr_ebx,
		       self->vr_regs.vr_ss, self->vr_regs.vr_sp,
		       self->vr_regs.vr_ebp,
		       self->vr_regs.vr_ds, self->vr_regs.vr_si,
		       self->vr_regs.vr_es, self->vr_regs.vr_di,
		       self->vr_regs.vr_cs, self->vr_regs.vr_ip,
		       self->vr_regs.vr_flags);
		if (self->vr_regs.vr_flags & CF)
			printk(KERN_RAW "CF");
		if (self->vr_regs.vr_flags & PF)
			printk(KERN_RAW "%sPF", self->vr_regs.vr_flags & CF ? "," : "");
		if (self->vr_regs.vr_flags & ZF)
			printk(KERN_RAW "%sZF", self->vr_regs.vr_flags & (CF | PF) ? "," : "");
		if (self->vr_regs.vr_flags & SF)
			printk(KERN_RAW "%sSF", self->vr_regs.vr_flags & (CF | PF | ZF) ? "," : "");
		if (self->vr_regs.vr_flags & OF)
			printk(KERN_RAW "%sOF", self->vr_regs.vr_flags & (CF | PF | ZF | SF) ? "," : "");
		printk(KERN_RAW "]\n");
	}
#endif /* __KERNEL__ */

read_opcode:
	error = libvm86_read_pcbyte(self, &opcode);
	if unlikely(error != VM86_SUCCESS)
		goto err;

	switch (opcode) {

	case 0x26: op_flags = (op_flags & ~F_SEGMASK) | F_SEGES; goto read_opcode;
	case 0x2e: op_flags = (op_flags & ~F_SEGMASK) | F_SEGCS; goto read_opcode;
	case 0x36: op_flags = (op_flags & ~F_SEGMASK) | F_SEGSS; goto read_opcode;
	case 0x3e: op_flags = (op_flags & ~F_SEGMASK) | F_SEGDS; goto read_opcode;
	case 0x64: op_flags = (op_flags & ~F_SEGMASK) | F_SEGFS; goto read_opcode;
	case 0x65: op_flags = (op_flags & ~F_SEGMASK) | F_SEGGS; goto read_opcode;
	case 0x66: op_flags |= F_66; goto read_opcode;
	case 0x67: op_flags |= F_67; goto read_opcode;
	case 0xf0: op_flags |= F_f0; goto read_opcode;
	case 0xf2: op_flags |= F_f2; goto read_opcode;
	case 0xf3: op_flags |= F_f3; goto read_opcode;


#define GUARD_SEGFAULT(...)              \
	do {                                 \
		TRY                              \
			__VA_ARGS__                  \
		EXCEPT {                         \
			if (!was_thrown(E_SEGFAULT)) \
				RETHROW();               \
			goto err_segfault;           \
		}                                \
	} __WHILE0


#define DEFINE_LXS(opcode, segment_register)                          \
	case opcode: {                                                    \
		byte_t *addr;                                                 \
		uint16_t segment;                                             \
		uint32_t offset;                                              \
		error = libvm86_modrm_decode(self, &mod, op_flags);           \
		if unlikely(error != VM86_SUCCESS)                            \
			goto err;                                                 \
		if unlikely(mod.mi_type == MODRM_REGISTER)                    \
			goto err_ilop;                                            \
		addr = (byte_t *)libvm86_modrm_getaddr(self, &mod, op_flags); \
		GUARD_SEGFAULT({                                              \
			segment = UNALIGNED_GET16((uint16_t *)(addr + 0));        \
			offset  = op_flags & F_OP32                               \
			             ? UNALIGNED_GET32((uint32_t *)(addr + 2))    \
			             : UNALIGNED_GET16((uint16_t *)(addr + 2));   \
		});                                                           \
		segment_register  = segment;                                  \
		REG32(mod.mi_reg) = offset;                                   \
	}	break;


	case 0x0f:
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		switch (opcode) {

#ifndef __INTELLISENSE__
		case 0xa1:
			/* 0F A1     POP FS     ZO     Valid     Valid     Pop top of stack into FS; increment stack pointer by 16 bits.
			 * 0F A1     POP FS     ZO     N.E.     Valid     Pop top of stack into FS; increment stack pointer by 32 bits. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (op_flags & F_OP32) {
				uint32_t temp;
				error = libvm86_popl(self, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_fs = (uint16_t)temp;
			} else {
				error = libvm86_popw(self, &self->vr_regs.vr_fs, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
			}
			break;


		case 0xa9:
			/* 0F A9     POP GS     ZO     Valid     Valid     Pop top of stack into GS; increment stack pointer by 16 bits.
			 * 0F A9     POP GS     ZO     N.E.     Valid     Pop top of stack into GS; increment stack pointer by 32 bits.*/
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (op_flags & F_OP32) {
				uint32_t temp;
				error = libvm86_popl(self, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_gs = (uint16_t)temp;
			} else {
				error = libvm86_popw(self, &self->vr_regs.vr_gs, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
			}
			break;


		case 0xa0:
			/* 0F A0     PUSH FS     ZO     Valid     Valid     Push FS. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			error = op_flags & F_OP32
			            ? libvm86_pushl(self, self->vr_regs.vr_fs, op_flags)
			            : libvm86_pushw(self, self->vr_regs.vr_fs, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			break;


		case 0xa8:
			/* 0F A8     PUSH GS     ZO     Valid     Valid     Push GS. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			error = op_flags & F_OP32
			            ? libvm86_pushl(self, self->vr_regs.vr_gs, op_flags)
			            : libvm86_pushw(self, self->vr_regs.vr_gs, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			break;


#define DEFINE_MOVcc(opcode, cond)                                                         \
		case opcode & 0xff:                                                                \
			error = libvm86_modrm_decode(self, &mod, op_flags);                            \
			if unlikely(error != VM86_SUCCESS)                                             \
				goto err;                                                                  \
			if (cond) {                                                                    \
				if (op_flags & F_OP32) {                                                   \
					error = libvm86_modrm_readl(self, &mod, &REG32(mod.mi_reg), op_flags); \
					if unlikely(error != VM86_SUCCESS)                                     \
						goto err;                                                          \
				} else {                                                                   \
					error = libvm86_modrm_readw(self, &mod, &REG16(mod.mi_reg), op_flags); \
					if unlikely(error != VM86_SUCCESS)                                     \
						goto err;                                                          \
					REG32(mod.mi_reg) &= 0xffff;                                           \
				}                                                                          \
			}                                                                              \
			break;                                                                         \
		case (opcode & 0xff) + 0x50:                                                       \
			error = libvm86_modrm_decode(self, &mod, op_flags);                            \
			if unlikely(error != VM86_SUCCESS)                                             \
				goto err;                                                                  \
			error = libvm86_modrm_writeb(self, &mod, (cond) ? 1 : 0, op_flags);            \
			if unlikely(error != VM86_SUCCESS)                                             \
				goto err;                                                                  \
			break

			/* 0F 40      CMOVO r16, r/m16        Move if overflow (OF=1) */
			/* 0F 40      CMOVO r32, r/m32        Move if overflow (OF=1) */
			DEFINE_MOVcc(0x0f40, self->vr_regs.vr_flags & OF);

			/* 0F 41      CMOVNO r16, r/m16       Move if not overflow (OF=0) */
			/* 0F 41      CMOVNO r32, r/m32       Move if not overflow (OF=0) */
			DEFINE_MOVcc(0x0f41, !(self->vr_regs.vr_flags & OF));

			/* 0F 42      CMOVB r16, r/m16        Move if below (CF=1) */
			/* 0F 42      CMOVB r32, r/m32        Move if below (CF=1) */
			/* 0F 42      CMOVC r16, r/m16        Move if carry (CF=1) */
			/* 0F 42      CMOVC r32, r/m32        Move if carry (CF=1) */
			/* 0F 42      CMOVNAE r16, r/m16      Move if not above or equal (CF=1) */
			/* 0F 42      CMOVNAE r32, r/m32      Move if not above or equal (CF=1) */
			DEFINE_MOVcc(0x0f42, self->vr_regs.vr_flags & CF);

			/* 0F 43      CMOVAE r16, r/m16       Move if above or equal (CF=0) */
			/* 0F 43      CMOVAE r32, r/m32       Move if above or equal (CF=0) */
			/* 0F 43      CMOVNB r16, r/m16       Move if not below (CF=0) */
			/* 0F 43      CMOVNB r32, r/m32       Move if not below (CF=0) */
			/* 0F 43      CMOVNC r16, r/m16       Move if not carry (CF=0) */
			/* 0F 43      CMOVNC r32, r/m32       Move if not carry (CF=0) */
			DEFINE_MOVcc(0x0f43, !(self->vr_regs.vr_flags & CF));

			/* 0F 44      CMOVE r16, r/m16        Move if equal (ZF=1) */
			/* 0F 44      CMOVE r32, r/m32        Move if equal (ZF=1) */
			/* 0F 44      CMOVZ r16, r/m16        Move if zero (ZF=1) */
			/* 0F 44      CMOVZ r32, r/m32        Move if zero (ZF=1) */
			DEFINE_MOVcc(0x0f44, self->vr_regs.vr_flags & ZF);

			/* 0F 45      CMOVNE r16, r/m16       Move if not equal (ZF=0) */
			/* 0F 45      CMOVNE r32, r/m32       Move if not equal (ZF=0) */
			/* 0F 45      CMOVNZ r16, r/m16       Move if not zero (ZF=0) */
			/* 0F 45      CMOVNZ r32, r/m32       Move if not zero (ZF=0) */
			DEFINE_MOVcc(0x0f45, !(self->vr_regs.vr_flags & ZF));

			/* 0F 46      CMOVBE r16, r/m16       Move if below or equal (CF=1 or ZF=1) */
			/* 0F 46      CMOVBE r32, r/m32       Move if below or equal (CF=1 or ZF=1) */
			/* 0F 46      CMOVNA r16, r/m16       Move if not above (CF=1 or ZF=1) */
			/* 0F 46      CMOVNA r32, r/m32       Move if not above (CF=1 or ZF=1) */
			DEFINE_MOVcc(0x0f46, self->vr_regs.vr_flags & (CF | ZF));

			/* 0F 47      CMOVA r16, r/m16        Move if above (CF=0 and ZF=0) */
			/* 0F 47      CMOVA r32, r/m32        Move if above (CF=0 and ZF=0) */
			/* 0F 47      CMOVNBE r16, r/m16      Move if not below or equal (CF=0 and ZF=0) */
			/* 0F 47      CMOVNBE r32, r/m32      Move if not below or equal (CF=0 and ZF=0) */
			DEFINE_MOVcc(0x0f47, !(self->vr_regs.vr_flags & (CF | ZF)));

			/* 0F 48      CMOVS r16, r/m16        Move if sign (SF=1) */
			/* 0F 48      CMOVS r32, r/m32        Move if sign (SF=1) */
			DEFINE_MOVcc(0x0f48, self->vr_regs.vr_flags & SF);

			/* 0F 49      CMOVNS r16, r/m16       Move if not sign (SF=0) */
			/* 0F 49      CMOVNS r32, r/m32       Move if not sign (SF=0) */
			DEFINE_MOVcc(0x0f49, !(self->vr_regs.vr_flags & SF));

			/* 0F 4A      CMOVP r16, r/m16        Move if parity (PF=1) */
			/* 0F 4A      CMOVP r32, r/m32        Move if parity (PF=1) */
			/* 0F 4A      CMOVPE r16, r/m16       Move if parity even (PF=1) */
			/* 0F 4A      CMOVPE r32, r/m32       Move if parity even (PF=1) */
			DEFINE_MOVcc(0x0f4a, self->vr_regs.vr_flags & PF);

			/* 0F 4B      CMOVNP r16, r/m16       Move if not parity (PF=0) */
			/* 0F 4B      CMOVNP r32, r/m32       Move if not parity (PF=0) */
			/* 0F 4B      CMOVPO r16, r/m16       Move if parity odd (PF=0) */
			/* 0F 4B      CMOVPO r32, r/m32       Move if parity odd (PF=0) */
			DEFINE_MOVcc(0x0f4b, !(self->vr_regs.vr_flags & PF));

			/* 0F 4C      CMOVL r16, r/m16        Move if less (SF<>OF) */
			/* 0F 4C      CMOVL r32, r/m32        Move if less (SF<>OF) */
			/* 0F 4C      CMOVNGE r16, r/m16      Move if not greater or equal (SF<>OF) */
			/* 0F 4C      CMOVNGE r32, r/m32      Move if not greater or equal (SF<>OF) */
			DEFINE_MOVcc(0x0f4c, !!(self->vr_regs.vr_flags & SF) != !!(self->vr_regs.vr_flags & OF));

			/* 0F 4D      CMOVGE r16, r/m16       Move if greater or equal (SF=OF) */
			/* 0F 4D      CMOVGE r32, r/m32       Move if greater or equal (SF=OF) */
			/* 0F 4D      CMOVNL r16, r/m16       Move if not less (SF=OF) */
			/* 0F 4D      CMOVNL r32, r/m32       Move if not less (SF=OF) */
			DEFINE_MOVcc(0x0f4d, !!(self->vr_regs.vr_flags & SF) == !!(self->vr_regs.vr_flags & OF));

			/* 0F 4E      CMOVLE r16, r/m16       Move if less or equal (ZF=1 or SF<>OF) */
			/* 0F 4E      CMOVLE r32, r/m32       Move if less or equal (ZF=1 or SF<>OF) */
			/* 0F 4E      CMOVNG r16, r/m16       Move if not greater (ZF=1 or SF<>OF) */
			/* 0F 4E      CMOVNG r32, r/m32       Move if not greater (ZF=1 or SF<>OF) */
			DEFINE_MOVcc(0x0f4e, (self->vr_regs.vr_flags & ZF) ||
			                     (!!(self->vr_regs.vr_flags & SF) !=
			                      !!(self->vr_regs.vr_flags & OF)));

			/* 0F 4F      CMOVG r16, r/m16        Move if greater (ZF=0 and SF=OF) */
			/* 0F 4F      CMOVG r32, r/m32        Move if greater (ZF=0 and SF=OF) */
			/* 0F 4F      CMOVNLE r16, r/m16      Move if not less or equal (ZF=0 and SF=OF) */
			/* 0F 4F      CMOVNLE r32, r/m32      Move if not less or equal (ZF=0 and SF=OF) */
			DEFINE_MOVcc(0x0f4f, !(self->vr_regs.vr_flags & ZF) &&
			                     (!!(self->vr_regs.vr_flags & SF) ==
			                      !!(self->vr_regs.vr_flags & OF)));
#undef DEFINE_MOVcc

			/* 0F 80 cd     JO rel32     D     Valid   Valid     Jump near if overflow (OF=1).
			 * 0F 80 cw     JO rel16     D     N.S.    Valid     Jump near if overflow (OF=1). Not supported in 64-bit mode.
			 * 0F 81 cd     JNO rel32    D     Valid   Valid     Jump near if not overflow (OF=0).
			 * 0F 81 cw     JNO rel16    D     N.S.    Valid     Jump near if not overflow (OF=0). Not supported in 64-bit mode.
			 * 0F 82 cd     JB rel32     D     Valid   Valid     Jump near if below (CF=1).
			 * 0F 82 cw     JB rel16     D     N.S.    Valid     Jump near if below (CF=1). Not supported in 64-bit mode.
			 * 0F 83 cd     JAE rel32    D     Valid   Valid     Jump near if above or equal (CF=0).
			 * 0F 83 cw     JAE rel16    D     N.S.    Valid     Jump near if above or equal (CF=0). Not supported in 64-bit mode.
			 * 0F 84 cd     JE rel32     D     Valid   Valid     Jump near if equal (ZF=1).
			 * 0F 84 cw     JE rel16     D     N.S.    Valid     Jump near if equal (ZF=1). Not supported in 64-bit mode.
			 * 0F 85 cd     JNE rel32    D     Valid   Valid     Jump near if not equal (ZF=0).
			 * 0F 85 cw     JNE rel16    D     N.S.    Valid     Jump near if not equal (ZF=0). Not supported in 64-bit mode.
			 * 0F 86 cd     JBE rel32    D     Valid   Valid     Jump near if below or equal (CF=1 or ZF=1).
			 * 0F 86 cw     JBE rel16    D     N.S.    Valid     Jump near if below or equal (CF=1 or ZF=1). Not supported in 64-bit mode.
			 * 0F 87 cd     JA rel32     D     Valid   Valid     Jump near if above (CF=0 and ZF=0).
			 * 0F 87 cw     JA rel16     D     N.S.    Valid     Jump near if above (CF=0 and ZF=0). Not supported in 64-bit mode.
			 * 0F 88 cd     JS rel32     D     Valid   Valid     Jump near if sign (SF=1).
			 * 0F 88 cw     JS rel16     D     N.S.    Valid     Jump near if sign (SF=1). Not supported in 64-bit mode.
			 * 0F 89 cd     JNS rel32    D     Valid   Valid     Jump near if not sign (SF=0).
			 * 0F 89 cw     JNS rel16    D     N.S.    Valid     Jump near if not sign (SF=0). Not supported in 64-bit mode.
			 * 0F 8A cd     JP rel32     D     Valid   Valid     Jump near if parity (PF=1).
			 * 0F 8A cw     JP rel16     D     N.S.    Valid     Jump near if parity (PF=1). Not supported in 64-bit mode.
			 * 0F 8B cd     JNP rel32    D     Valid   Valid     Jump near if not parity (PF=0).
			 * 0F 8B cw     JNP rel16    D     N.S.    Valid     Jump near if not parity (PF=0). Not supported in 64-bit mode.
			 * 0F 8C cd     JL rel32     D     Valid   Valid     Jump near if less (SF≠ OF).
			 * 0F 8C cw     JL rel16     D     N.S.    Valid     Jump near if less (SF≠ OF). Not supported in 64-bit mode.
			 * 0F 8D cd     JGE rel32    D     Valid   Valid     Jump near if greater or equal (SF=OF).
			 * 0F 8D cw     JGE rel16    D     N.S.    Valid     Jump near if greater or equal (SF=OF). Not supported in 64-bit mode.
			 * 0F 8E cd     JLE rel32    D     Valid   Valid     Jump near if less or equal (ZF=1 or SF≠ OF).
			 * 0F 8E cw     JLE rel16    D     N.S.    Valid     Jump near if less or equal (ZF=1 or SF≠ OF). Not supported in 64-bit mode.
			 * 0F 8F cd     JG rel32     D     Valid   Valid     Jump near if greater (ZF=0 and SF=OF).
			 * 0F 8F cw     JG rel16     D     N.S.    Valid     Jump near if greater (ZF=0 and SF=OF). Not supported in 64-bit mode. */
#define DEFINE_Jcc(opc, cond)                                                       \
			case opc & 0xff:                                                        \
				if (cond) {                                                         \
					if (op_flags & F_OP32) {                                        \
						uint32_t offset;                                            \
						error = libvm86_read_pcdword(self, &offset);                \
						if unlikely(error != VM86_SUCCESS)                          \
							goto err;                                               \
						self->vr_regs.vr_eip += (uint32_t)(int32_t)offset;          \
					} else {                                                        \
						uint16_t offset;                                            \
						error = libvm86_read_pcword(self, &offset);                 \
						if unlikely(error != VM86_SUCCESS)                          \
							goto err;                                               \
						self->vr_regs.vr_eip += (uint32_t)(int32_t)(int16_t)offset; \
						self->vr_regs.vr_eip &= 0xffff;                             \
					}                                                               \
				} else if (op_flags & F_OP32) {                                     \
					self->vr_regs.vr_eip += 4;                                      \
				} else {                                                            \
					self->vr_regs.vr_eip += 2;                                      \
				}                                                                   \
				break
			DEFINE_Jcc(0x0f80, self->vr_regs.vr_flags & OF);
			DEFINE_Jcc(0x0f81, !(self->vr_regs.vr_flags & OF));
			DEFINE_Jcc(0x0f82, self->vr_regs.vr_flags & CF);
			DEFINE_Jcc(0x0f83, !(self->vr_regs.vr_flags & CF));
			DEFINE_Jcc(0x0f84, self->vr_regs.vr_flags & ZF);
			DEFINE_Jcc(0x0f85, !(self->vr_regs.vr_flags & ZF));
			DEFINE_Jcc(0x0f86, self->vr_regs.vr_flags & (CF | ZF));
			DEFINE_Jcc(0x0f87, !(self->vr_regs.vr_flags & (CF | ZF)));
			DEFINE_Jcc(0x0f88, self->vr_regs.vr_flags & SF);
			DEFINE_Jcc(0x0f89, !(self->vr_regs.vr_flags & SF));
			DEFINE_Jcc(0x0f8a, self->vr_regs.vr_flags & PF);
			DEFINE_Jcc(0x0f8b, !(self->vr_regs.vr_flags & PF));
			DEFINE_Jcc(0x0f8c, !!(self->vr_regs.vr_flags & SF) != !!(self->vr_regs.vr_flags & OF));
			DEFINE_Jcc(0x0f8d, !!(self->vr_regs.vr_flags & SF) == !!(self->vr_regs.vr_flags & OF));
			DEFINE_Jcc(0x0f8e, (self->vr_regs.vr_flags & ZF) || (!!(self->vr_regs.vr_flags & SF) != !!(self->vr_regs.vr_flags & OF)));
			DEFINE_Jcc(0x0f8f, !(self->vr_regs.vr_flags & ZF) && (!!(self->vr_regs.vr_flags & SF) == !!(self->vr_regs.vr_flags & OF)));
#undef DEFINE_Jcc

			/* 0F B2 /r  LSS r16,m16:16     RM     Valid     Valid     Load SS:r16 with far pointer from memory.
			 * 0F B2 /r  LSS r32,m16:32     RM     Valid     Valid     Load SS:r32 with far pointer from memory. */
			DEFINE_LXS(0xb2, self->vr_regs.vr_ss)
			/* 0F B4 /r  LFS r16,m16:16     RM     Valid     Valid     Load FS:r16 with far pointer from memory.
			 * 0F B4 /r  LFS r32,m16:32     RM     Valid     Valid     Load FS:r32 with far pointer from memory. */
			DEFINE_LXS(0xb4, self->vr_regs.vr_fs)
			/* 0F B5 /r  LGS r16,m16:16     RM     Valid     Valid     Load GS:r16 with far pointer from memory.
			 * 0F B5 /r  LGS r32,m16:32     RM     Valid     Valid     Load GS:r32 with far pointer from memory. */
			DEFINE_LXS(0xb5, self->vr_regs.vr_gs)



		case 0xaf:
			/* 0F AF /r     IMUL r16, r/m16     RM     Valid     Valid     word register := word register * r/m16.
			 * 0F AF /r     IMUL r32, r/m32     RM     Valid     Valid     doubleword register := doubleword register * r/m32. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			if (op_flags & F_OP32) {
				uint32_t operand;
				error = libvm86_modrm_readl(self, &mod, &operand, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(OF | CF);
				if (OVERFLOW_SMUL((int32_t)REG32(mod.mi_reg),
				                  (int32_t)operand,
				                  (int32_t *)&REG32(mod.mi_reg))) {
					*(int32_t *)&REG32(mod.mi_reg) = (int32_t)REG32(mod.mi_reg) * (int32_t)operand;
					self->vr_regs.vr_flags |= (OF | CF);
				}
			} else {
				uint16_t operand;
				error = libvm86_modrm_readw(self, &mod, &operand, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(OF | CF);
				if (OVERFLOW_SMUL((int16_t)REG16(mod.mi_reg),
				                  (int16_t)operand,
				                  (int16_t *)&REG16(mod.mi_reg))) {
					*(int16_t *)&REG16(mod.mi_reg) = (int16_t)REG16(mod.mi_reg) * (int16_t)operand;
					self->vr_regs.vr_flags |= (OF | CF);
				}
				REG32(mod.mi_reg) &= 0xffff;
			}
			break;



		case 0x1f:
			/* NOP */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			break;
#endif /* !__INTELLISENSE__ */

		case 0xa2:
			/* 0F A2     CPUID     ZO     Valid     Valid     Returns processor identification and feature information to the EAX, EBX, ECX, and EDX registers, as determined by input entered in EAX (in some cases, ECX as well). */
			switch (self->vr_regs.vr_eax) {
			case 0:
			case 0x80000000:
				if (self->vr_regs.vr_eax == 0)
					self->vr_regs.vr_eax = 7;
				else {
					self->vr_regs.vr_eax = 0x80000004;
				}
				self->vr_regs.vr_ebx = 0x756e6547;
				self->vr_regs.vr_ecx = 0x6c65746e;
				self->vr_regs.vr_edx = 0x49656e69;
				break;
			case 1:
				self->vr_regs.vr_eax = 0x663;
				self->vr_regs.vr_ebx = 0x00000800; /* ??? */
				self->vr_regs.vr_ecx = (CPUID_1C_MOVBE | CPUID_1C_POPCNT);
				self->vr_regs.vr_edx = (CPUID_1D_CX8 | CPUID_1D_CMOV | CPUID_1D_CLFSH);
				break;
			case 7:
			default:
				self->vr_regs.vr_eax = 0;
				self->vr_regs.vr_ebx = (CPUID_7B_CLFLUSHOPT);
				self->vr_regs.vr_ecx = (CPUID_7C_PREFETCHWT1);
				self->vr_regs.vr_edx = 0;
				break;
			case 0x80000001:
				self->vr_regs.vr_eax = 0;
				self->vr_regs.vr_ebx = 0;
				self->vr_regs.vr_ecx = (CPUID_80000001C_ABM | CPUID_80000001C_3DNOWPREFETCH |
				                        CPUID_80000001C_TBM);
				self->vr_regs.vr_edx = (CPUID_80000001D_CX8 | CPUID_80000001D_CMOV);
				break;
			case 0x80000002:
				self->vr_regs.vr_eax = ((uint32_t const *)cpuid_brand_string)[0];
				self->vr_regs.vr_ebx = ((uint32_t const *)cpuid_brand_string)[1];
				self->vr_regs.vr_ecx = ((uint32_t const *)cpuid_brand_string)[2];
				self->vr_regs.vr_edx = ((uint32_t const *)cpuid_brand_string)[3];
				break;
			case 0x80000003:
				self->vr_regs.vr_eax = ((uint32_t const *)cpuid_brand_string)[4];
				self->vr_regs.vr_ebx = ((uint32_t const *)cpuid_brand_string)[5];
				self->vr_regs.vr_ecx = ((uint32_t const *)cpuid_brand_string)[6];
				self->vr_regs.vr_edx = ((uint32_t const *)cpuid_brand_string)[7];
				break;
			case 0x80000004:
				self->vr_regs.vr_eax = ((uint32_t const *)cpuid_brand_string)[8];
				self->vr_regs.vr_ebx = ((uint32_t const *)cpuid_brand_string)[9];
				self->vr_regs.vr_ecx = ((uint32_t const *)cpuid_brand_string)[10];
				self->vr_regs.vr_edx = ((uint32_t const *)cpuid_brand_string)[11];
				break;
			}
			break;


		case 0xba: {
			uint8_t imm_operand;
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_read_pcbyte(self, &imm_operand);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			switch (mod.mi_reg) {

			case 4:
				/* 0F BA /4 ib 	BT r/m16, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag.
				 * 0F BA /4 ib 	BT r/m32, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag. */
				if (op_flags & F_OP32) {
					uint32_t value, mask = (uint32_t)1 << (imm_operand % 32);
					error = libvm86_modrm_readl(self, &mod, &value, op_flags);
					if unlikely(error != VM86_SUCCESS)
						goto err;
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				} else {
					uint16_t value, mask = (uint16_t)1 << (imm_operand % 16);
					error = libvm86_modrm_readw(self, &mod, &value, op_flags);
					if unlikely(error != VM86_SUCCESS)
						goto err;
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				}
				break;

			case 5:
				/* 0F BA /5 ib 	BTS r/m16, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag and set.
				 * 0F BA /5 ib 	BTS r/m32, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag and set. */
				if (op_flags & F_OP32) {
					uint32_t *addr, value, mask = (uint32_t)1 << (imm_operand % 32);
					addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							value = ATOMIC_FETCHOR(*addr, mask);
						} else {
							value = *addr;
							*addr = value | mask;
						}
					});
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				} else {
					uint16_t *addr, value, mask = (uint16_t)1 << (imm_operand % 16);
					addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							value = ATOMIC_FETCHOR(*addr, mask);
						} else {
							value = *addr;
							*addr = value | mask;
						}
					});
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				}
				break;

			case 6:
				/* 0F BA /6 ib 	BTR r/m16, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag and clear.
				 * 0F BA /6 ib 	BTR r/m32, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag and clear. */
				if (op_flags & F_OP32) {
					uint32_t *addr, value, mask = (uint32_t)1 << (imm_operand % 32);
					addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							value = ATOMIC_FETCHAND(*addr, ~mask);
						} else {
							value = *addr;
							*addr = value & ~mask;
						}
					});
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				} else {
					uint16_t *addr, value, mask = (uint16_t)1 << (imm_operand % 16);
					addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							value = ATOMIC_FETCHAND(*addr, ~mask);
						} else {
							value = *addr;
							*addr = value & ~mask;
						}
					});
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				}
				break;

			case 7:
				/* 0F BA /7 ib 	BTC r/m16, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag and complement.
				 * 0F BA /7 ib 	BTC r/m32, imm8 	MI 	Valid 	Valid 	Store selected bit in CF flag and complement. */
				if (op_flags & F_OP32) {
					uint32_t *addr, value, mask = (uint32_t)1 << (imm_operand % 32);
					addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							value = ATOMIC_FETCHXOR(*addr, mask);
						} else {
							value = *addr;
							*addr = value ^ mask;
						}
					});
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				} else {
					uint16_t *addr, value, mask = (uint16_t)1 << (imm_operand % 16);
					addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							value = ATOMIC_FETCHXOR(*addr, mask);
						} else {
							value = *addr;
							*addr = value ^ mask;
						}
					});
					self->vr_regs.vr_eflags &= ~CF;
					if (value & mask)
						self->vr_regs.vr_eflags |= CF;
				}
				break;

			default:
				goto err_ilop;
			}
		}	break;


		case 0xa3:
			/* 0F A3 /r     BT r/m16, r16     MR     Valid     Valid     Store selected bit in CF flag.
			 * 0F A3 /r     BT r/m32, r32     MR     Valid     Valid     Store selected bit in CF flag. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			if (op_flags & F_OP32) {
				uint32_t value, mask = (uint32_t)1 << (REG32(mod.mi_reg) % 32);
				error = libvm86_modrm_readl(self, &mod, &value, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			} else {
				uint16_t value, mask = (uint16_t)1 << (REG16(mod.mi_reg) % 16);
				error = libvm86_modrm_readw(self, &mod, &value, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			}
			break;


		case 0xab:
			/* 0F AB /r 	BTS r/m16, r16 	MR 	Valid 	Valid 	Store selected bit in CF flag and set.
			 * 0F AB /r 	BTS r/m32, r32 	MR 	Valid 	Valid 	Store selected bit in CF flag and set. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			if (op_flags & F_OP32) {
				uint32_t *addr, value, mask = (uint32_t)1 << (REG32(mod.mi_reg) % 32);
				addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						value = ATOMIC_FETCHOR(*addr, mask);
					} else {
						value = *addr;
						*addr = value | mask;
					}
				});
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			} else {
				uint16_t *addr, value, mask = (uint16_t)1 << (REG16(mod.mi_reg) % 16);
				addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						value = ATOMIC_FETCHOR(*addr, mask);
					} else {
						value = *addr;
						*addr = value | mask;
					}
				});
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			}
			break;


		case 0xb3:
			/* 0F B3 /r 	BTR r/m16, r16 	MR 	Valid 	Valid 	Store selected bit in CF flag and clear.
			 * 0F B3 /r 	BTR r/m32, r32 	MR 	Valid 	Valid 	Store selected bit in CF flag and clear. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			if (op_flags & F_OP32) {
				uint32_t *addr, value, mask = (uint32_t)1 << (REG32(mod.mi_reg) % 32);
				addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						value = ATOMIC_FETCHAND(*addr, ~mask);
					} else {
						value = *addr;
						*addr = value & ~mask;
					}
				});
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			} else {
				uint16_t *addr, value, mask = (uint16_t)1 << (REG16(mod.mi_reg) % 16);
				addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						value = ATOMIC_FETCHAND(*addr, ~mask);
					} else {
						value = *addr;
						*addr = value & ~mask;
					}
				});
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			}
			break;


		case 0xbb:
			/* 0F BB /r 	BTC r/m16, r16 	MR 	Valid 	Valid 	Store selected bit in CF flag and complement.
			 * 0F BB /r 	BTC r/m32, r32 	MR 	Valid 	Valid 	Store selected bit in CF flag and complement. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			if (op_flags & F_OP32) {
				uint32_t *addr, value, mask = (uint32_t)1 << (REG32(mod.mi_reg) % 32);
				addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						value = ATOMIC_FETCHXOR(*addr, mask);
					} else {
						value = *addr;
						*addr = value ^ mask;
					}
				});
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			} else {
				uint16_t *addr, value, mask = (uint16_t)1 << (REG16(mod.mi_reg) % 16);
				addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						value = ATOMIC_FETCHXOR(*addr, mask);
					} else {
						value = *addr;
						*addr = value ^ mask;
					}
				});
				self->vr_regs.vr_eflags &= ~CF;
				if (value & mask)
					self->vr_regs.vr_eflags |= CF;
			}
			break;


		case 0xb6: {
			uint8_t value;
			/* 0F B6 /r 	MOVZX r16, r/m8 	RM 	Valid 	Valid 	Move byte to word with zero-extension.
			 * 0F B6 /r 	MOVZX r32, r/m8 	RM 	Valid 	Valid 	Move byte to doubleword, zero-extension. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_readb(self, &mod, &value, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			if (op_flags & F_OP32) {
				REG16(mod.mi_reg) = (uint16_t)value;
			} else {
				REG32(mod.mi_reg) = (uint32_t)value;
			}
		}	break;

		case 0xb7: {
			uint16_t value;
			/* 0F B7 /r 	MOVZX r32, r/m16 	RM 	Valid 	Valid 	Move word to doubleword, zero-extension. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_readw(self, &mod, &value, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			REG32(mod.mi_reg) = (uint32_t)value;
		}	break;


		case 0xbe: {
			uint8_t value;
			/* 0F BE /r 	MOVSX r16, r/m8 	RM 	Valid 	Valid 	Move byte to word with sign-extension.
			 * 0F BE /r 	MOVSX r32, r/m8 	RM 	Valid 	Valid 	Move byte to doubleword with sign-extension. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_readb(self, &mod, &value, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			if (op_flags & F_OP32) {
				REG16(mod.mi_reg) = (uint16_t)(int16_t)(int8_t)value;
			} else {
				REG32(mod.mi_reg) = (uint32_t)(int32_t)(int8_t)value;
			}
		}	break;


		case 0xbf: {
			uint16_t value;
			/* 0F BF /r 	MOVSX r32, r/m16 	RM 	Valid 	Valid 	Move word to doubleword, with sign-extension. */
			error = libvm86_modrm_decode(self, &mod, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_readw(self, &mod, &value, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			REG32(mod.mi_reg) = (uint32_t)(int32_t)(int16_t)value;
		}	break;


			/* TODO: bsf */
			/* TODO: bsr */
			/* TODO: tzcnt */
			/* TODO: lzcnt */
			/* TODO: popcnt */
			/* TODO: shld */
			/* TODO: shrd */
			/* TODO: cmpxchg */
			/* TODO: xadd */
			/* TODO: bswap */
			/* TODO: cmpxchg8 */
			/* TODO: cflush */
			/* TODO: prefetchwt1 */
			/* TODO: clflushopt */
			/* TODO: prefetch */
			/* TODO: prefetchw */

			/* TODO: bextr */
			/* TODO: blcfill */
			/* TODO: blci */
			/* TODO: blcic */
			/* TODO: blcmsk */
			/* TODO: blcs */
			/* TODO: blsfill */
			/* TODO: blsic */
			/* TODO: t1mskc */
			/* TODO: tzmsk */

		default:
			goto err_ilop;
		}
		break;

#if !defined(__INTELLISENSE__)
	case 0x37:
		/* 37     AAA     ZO     Invalid     Valid     ASCII adjust AL after addition. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if ((self->vr_regs.vr_al & 0xf) > 9 ||
		    (self->vr_regs.vr_flags & AF)) {
			self->vr_regs.vr_ax += 0x106;
			self->vr_regs.vr_flags |= (AF | CF);
		} else {
			self->vr_regs.vr_flags &= ~(AF | CF);
		}
		self->vr_regs.vr_al &= 0x0f;
		break;


	case 0x3f:
		/* 3F     AAS     ZO     Invalid     Valid     ASCII adjust AL after subtraction. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if ((self->vr_regs.vr_al & 0xf) > 9 ||
		    (self->vr_regs.vr_flags & AF)) {
			self->vr_regs.vr_ax -= 6;
			self->vr_regs.vr_ah -= 1;
			self->vr_regs.vr_flags |= (AF | CF);
		} else {
			self->vr_regs.vr_flags &= ~(AF | CF);
		}
		self->vr_regs.vr_al &= 0x0f;
		break;


	case 0xcc:
		/* CC     INT3     ZO     Valid     Valid     Generate breakpoint trap. */
		return libvm86_intr(self, 3);


	case 0xcd:
		/* CD ib     INT imm8     I     Valid     Valid     Generate software interrupt with vector specified by immediate byte. */
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		return libvm86_intr(self, opcode);


	case 0xce:
		/* CE     INTO     ZO     Invalid     Valid     Generate overflow trap if overflow flag is 1. */
		if (self->vr_regs.vr_flags & OF)
			return libvm86_intr(self, 4);
		break;


	case 0xd4:
		/* D4 0A     AAM          ZO     Invalid     Valid     ASCII adjust AX after multiply.
		 * D4 ib     AAM imm8     ZO     Invalid     Valid     Adjust AX after multiply to number base imm8. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
#ifdef E_DIVIDE_BY_ZERO
		TRY {
			self->vr_regs.vr_ah = self->vr_regs.vr_al / opcode;
			self->vr_regs.vr_al = self->vr_regs.vr_al % opcode;
		} EXCEPT {
			if (!was_thrown(E_DIVIDE_BY_ZERO))
				RETHROW();
			goto err_ilop;
		}
#else /* E_DIVIDE_BY_ZERO */
		if unlikely(!opcode)
			goto err_ilop;
		self->vr_regs.vr_ah = self->vr_regs.vr_al / opcode;
		self->vr_regs.vr_al = self->vr_regs.vr_al % opcode;
#endif /* !E_DIVIDE_BY_ZERO */
		break;


	case 0xd5:
		/* D5 0A     AAD          ZO     Invalid     Valid     ASCII adjust AX before division.
		 * D5 ib     AAD imm8     ZO     Invalid     Valid     Adjust AX before division to number base imm8. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_al += self->vr_regs.vr_ah * opcode;
		self->vr_regs.vr_ah = 0;
		break;


	case 0x6c:
		/* 6C     INS m8, DX     ZO     Valid     Valid     Input byte from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.* */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		{
			uint8_t temp;
			error = libvm86_inb(self, self->vr_regs.vr_dx, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_store_string_byte(self, temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		if (op_flags & F_REP) {
do_rep_instruction:
			/* Decrement the loop counter. */
			if (op_flags & F_67) {
				--self->vr_regs.vr_ecx;
				if (!self->vr_regs.vr_ecx)
					break;
			} else {
				--self->vr_regs.vr_cx;
				if (!self->vr_regs.vr_cx)
					break;
			}
			/* Repeat the instruction. */
			self->vr_regs.vr_ip = ip_start;
		}
		break;


	case 0x6d:
		/* 6D     INS m16, DX     ZO     Valid     Valid     Input word from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1
		 * 6D     INS m32, DX     ZO     Valid     Valid     Input doubleword from I/O port specified in DX into memory location specified in ES:(E)DI or RDI.1 */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_inl(self, self->vr_regs.vr_dx, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_store_string_dword(self, temp, op_flags);
		} else {
			uint16_t temp;
			error = libvm86_inw(self, self->vr_regs.vr_dx, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_store_string_word(self, temp, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;


	case 0x6e:
		/* 6E     OUTS DX, m8     ZO     Valid     Valid     Output byte from memory location specified in DS:(E)SI or RSI to I/O port specified in DX**. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		{
			uint8_t temp;
			error = libvm86_load_string_byte(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_outb(self, self->vr_regs.vr_dx, temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;


	case 0x6f:
		/* 6F     OUTS DX, m16    ZO     Valid     Valid     Output word from memory location specified in DS:(E)SI or RSI to I/O port specified in DX**. */
		/* 6F     OUTS DX, m32    ZO     Valid     Valid     Output doubleword from memory location specified in DS:(E)SI or RSI to I/O port specified in DX**. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_load_string_dword(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_outl(self, self->vr_regs.vr_dx, temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			uint16_t temp;
			error = libvm86_load_string_word(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_outw(self, self->vr_regs.vr_dx, temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;


	case 0xe4:
		/* E4 ib     IN AL, imm8     I     Valid     Valid     Input byte from imm8 I/O port address into AL. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		return libvm86_inb(self, opcode, &self->vr_regs.vr_al);


	case 0xe5:
		/* E5 ib     IN AX, imm8     I     Valid     Valid     Input word from imm8 I/O port address into AX. */
		/* E5 ib     IN EAX, imm8     I     Valid     Valid     Input dword from imm8 I/O port address into EAX. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			return libvm86_inl(self, opcode, &self->vr_regs.vr_eax);
		} else {
			return libvm86_inw(self, opcode, &self->vr_regs.vr_ax);
		}
		break;


	case 0xec:
		/* EC     IN AL,DX     ZO     Valid     Valid     Input byte from I/O port in DX into AL. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		return libvm86_inb(self, self->vr_regs.vr_dx, &self->vr_regs.vr_al);


	case 0xed:
		/* ED     IN AX,DX     ZO     Valid     Valid     Input word from I/O port in DX into AX. */
		/* ED     IN EAX,DX    ZO     Valid     Valid     Input doubleword from I/O port in DX into EAX. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			return libvm86_inl(self, self->vr_regs.vr_dx, &self->vr_regs.vr_eax);
		}
		error = libvm86_inw(self, self->vr_regs.vr_dx, &self->vr_regs.vr_ax);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_eax &= 0xffff;
		break;


	case 0xe6:
		/* E6 ib     OUT imm8, AL     I     Valid     Valid     Output byte in AL to I/O port address imm8. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		return libvm86_outb(self, opcode, self->vr_regs.vr_al);


	case 0xe7:
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			/* E7 ib  OUT imm8, EAX    I     Valid     Valid     Output doubleword in EAX to I/O port address imm8. */
			return libvm86_outl(self, opcode, self->vr_regs.vr_eax);
		} else {
			/* E7 ib  OUT imm8, AX     I     Valid     Valid     Output word in AX to I/O port address imm8. */
			return libvm86_outw(self, opcode, self->vr_regs.vr_ax);
		}
		break;


	case 0xee:
		if (op_flags & (F_LOCK))
			goto err_ilop;
		/* EE     OUT DX, AL     ZO     Valid     Valid     Output byte in AL to I/O port address in DX. */
		return libvm86_outb(self, self->vr_regs.vr_dx, self->vr_regs.vr_al);


	case 0xef:
		if (op_flags & (F_LOCK))
			goto err_ilop;
		/* EF     OUT DX, AX     ZO     Valid     Valid     Output word in AX to I/O port address in DX. */
		/* EF     OUT DX, EAX    ZO     Valid     Valid     Output doubleword in EAX to I/O port address in DX. */
		if (op_flags & F_OP32) {
			return libvm86_outl(self, self->vr_regs.vr_dx, self->vr_regs.vr_eax);
		} else {
			return libvm86_outw(self, self->vr_regs.vr_dx, self->vr_regs.vr_ax);
		}
		break;


	case 0xf1:
		/* F1     INT1     ZO     Valid     Valid     Generate debug trap. */
		return libvm86_intr(self, 1);


	case 0xf5:
		/* F5     CMC     ZO     Valid     Valid     Complement CF flag. */
		self->vr_regs.vr_flags ^= CF;
		break;


	case 0xf8:
		/* F8     CLC     ZO     Valid     Valid     Clear CF flag. */
		self->vr_regs.vr_flags &= ~CF;
		break;


	case 0xf9:
		/* F9     STC     ZO     Valid     Valid     Set CF flag. */
		self->vr_regs.vr_flags |= CF;
		break;


	case 0xfc:
		/* FC     CLD     ZO     Valid     Valid     Clear DF flag. */
		self->vr_regs.vr_flags &= ~DF;
		break;


	case 0xfd:
		/* FD     STD     ZO     Valid     Valid     Set DF flag. */
		self->vr_regs.vr_flags |= DF;
		break;


	case 0xfa:
		/* FA     CLI     ZO     Valid     Valid     Clear interrupt flag; interrupts disabled when interrupt flag cleared. */
		self->vr_regs.vr_flags &= ~IF;
		break;


	case 0xfb:
		/* FB     STI     ZO     Valid     Valid     Set interrupt flag; external, maskable interrupts enabled at the end of the next instruction. */
		if (!(self->vr_regs.vr_flags & IF)) {
			self->vr_regs.vr_flags |= IF;
			return VM86_INTR_ENABLED; /* Don't enable interrupts until after the next instruction! */
		}
		break;


	case 0xf4:
		/* F4     HLT     ZO     Valid     Valid     Halt */
		if (self->vr_regs.vr_flags & IF)
			return VM86_HALTED;
		self->vr_regs.vr_ip = ip_start;
		return VM86_FROZEN;


	case 0x9c:
		/* 9C     PUSHF     ZO     Valid     Valid     Push lower 16 bits of EFLAGS.
		 * 9C     PUSHFD    ZO     N.E.      Valid     Push EFLAGS. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		return op_flags & F_OP32
		       ? libvm86_pushl(self, self->vr_regs.vr_eflags & 0x00fcffff, op_flags)
		       : libvm86_pushw(self, self->vr_regs.vr_flags, op_flags);
		break;


	case 0x9d:
		if (op_flags & (F_LOCK))
			goto err_ilop;
		/* 9D     POPF     ZO     Valid     Valid     Pop top of stack into lower 16 bits of EFLAGS.
		 * 9D     POPFD    ZO     N.E.      Valid     Pop top of stack into EFLAGS. */
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_popl(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_eflags = temp & 0x00fcffff;
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_flags, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_eflags &= 0xffff;
		}
		break;


	case 0x60:
		/* 60     PUSHA     ZO     Invalid     Valid     Push AX, CX, DX, BX, original SP, BP, SI, and DI.
		 * 60     PUSHAD    ZO     Invalid     Valid     Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			uint32_t orig_sp;
			orig_sp = self->vr_regs.vr_esp;
			error = libvm86_pushl(self, self->vr_regs.vr_eax, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_ecx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_edx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_ebx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, orig_sp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_ebp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_esi, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_edi, op_flags);
		} else {
			uint16_t orig_sp;
			orig_sp = self->vr_regs.vr_sp;
			error   = libvm86_pushw(self, self->vr_regs.vr_ax, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_cx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_dx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_bx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, orig_sp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_bp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_si, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_di, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x61:
		/* 61     POPA     ZO     Invalid     Valid     Pop DI, SI, BP, BX, DX, CX, and AX.
		 * 61     POPAD    ZO     Invalid     Valid     Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			error = libvm86_popl(self, &self->vr_regs.vr_edi, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &self->vr_regs.vr_esi, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &self->vr_regs.vr_ebp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl_void(self, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &self->vr_regs.vr_ebx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &self->vr_regs.vr_edx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &self->vr_regs.vr_ecx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &self->vr_regs.vr_eax, op_flags);
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_di, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_si, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_bp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw_void(self, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_bx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_dx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_cx, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_ax, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x1f:
		/* 1F     POP DS     ZO     Invalid     Valid     Pop top of stack into DS; increment stack pointer. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_popl(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_ds = (uint16_t)temp;
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_ds, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		break;


	case 0x07:
		/* 07     POP ES     ZO     Invalid     Valid     Pop top of stack into ES; increment stack pointer. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_popl(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_es = (uint16_t)temp;
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_es, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		break;


	case 0x17:
		/* 17     POP SS     ZO     Invalid     Valid     Pop top of stack into SS; increment stack pointer. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_popl(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_ss = (uint16_t)temp;
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_ss, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		if (self->vr_regs.vr_flags & IF)
			return VM86_INTR_ENABLED; /* Suppress interrupts before the next instruction. */
		break;


	case 0x50 ... 0x57:
		/* 50+rw     PUSH r16     O     Valid    Valid     Push r16.
		 * 50+rd     PUSH r32     O     N.E.     Valid     Push r32. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = op_flags & F_OP32
		        ? libvm86_pushl(self, REG32((uint8_t)(opcode - 0x50)), op_flags)
		        : libvm86_pushw(self, REG16((uint8_t)(opcode - 0x50)), op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x58 ... 0x5f:
		/* 58+ rw     POP r16     O     Valid    Valid     Pop top of stack into r16; increment stack pointer.
		 * 58+ rd     POP r32     O     N.E.     Valid     Pop top of stack into r32; increment stack pointer. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			error = libvm86_popl(self, &REG32((uint8_t)(opcode - 0x58)), op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			error = libvm86_popw(self, &REG16((uint8_t)(opcode - 0x58)), op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			REG32((uint8_t)(opcode - 0x58)) &= 0xffff;
		}
		break;


	case 0x8f:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		switch (mod.mi_reg) {

		case 0:
			/* 8F /0     POP r/m16     M     Valid     Valid     Pop top of stack into m16; increment stack pointer.
			 * 8F /0     POP r/m32     M     N.E.     Valid     Pop top of stack into m32; increment stack pointer. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (op_flags & F_OP32) {
				uint32_t temp;
				error = libvm86_popl(self, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_modrm_writel(self, &mod, temp, op_flags);
			} else {
				uint16_t temp;
				error = libvm86_popw(self, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_modrm_writew(self, &mod, temp, op_flags);
			}
			if unlikely(error != VM86_SUCCESS)
				goto err;
			break;

		default:
			goto err_ilop;
		}
		break;


	case 0x0e:
		/* 0E     PUSH CS     ZO     Invalid     Valid     Push CS. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = op_flags & F_OP32
		        ? libvm86_pushl(self, self->vr_regs.vr_cs, op_flags)
		        : libvm86_pushw(self, self->vr_regs.vr_cs, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x16:
		/* 16     PUSH SS     ZO     Invalid     Valid     Push SS. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = op_flags & F_OP32
		        ? libvm86_pushl(self, self->vr_regs.vr_ss, op_flags)
		        : libvm86_pushw(self, self->vr_regs.vr_ss, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x1e:
		/* 1E     PUSH DS     ZO     Invalid     Valid     Push DS. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = op_flags & F_OP32
		        ? libvm86_pushl(self, self->vr_regs.vr_ds, op_flags)
		        : libvm86_pushw(self, self->vr_regs.vr_ds, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x06:
		/* 06     PUSH ES     ZO     Invalid     Valid     Push ES. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = op_flags & F_OP32
		        ? libvm86_pushl(self, self->vr_regs.vr_es, op_flags)
		        : libvm86_pushw(self, self->vr_regs.vr_es, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x6a:
		/* 6A ib     PUSH imm8     I     Valid     Valid     Push imm8. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = op_flags & F_OP32
		        ? libvm86_pushl(self, opcode, op_flags)
		        : libvm86_pushw(self, opcode, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x68:
		/* 68 iw     PUSH imm16     I     Valid     Valid     Push imm16. */
		/* 68 id     PUSH imm32     I     Valid     Valid     Push imm32. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_read_pcdword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, temp, op_flags);
		} else {
			uint16_t temp;
			error = libvm86_read_pcword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, temp, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0xc3:
		/* C3     RET     ZO     Valid     Valid     Near return to calling procedure. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = op_flags & F_OP32
		        ? libvm86_popl(self, &self->vr_regs.vr_eip, op_flags)
		        : libvm86_popw(self, &self->vr_regs.vr_ip, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (!(op_flags & F_OP32))
			self->vr_regs.vr_eip &= 0xffff;
		break;


	case 0xc2: {
		uint16_t sp_adjustment;
		/* C2 iw     RET imm16     I     Valid     Valid     Near return to calling procedure and pop imm16 bytes from stack. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcword(self, &sp_adjustment);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = op_flags & F_OP32
		        ? libvm86_popl(self, &self->vr_regs.vr_eip, op_flags)
		        : libvm86_popw(self, &self->vr_regs.vr_ip, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (!(op_flags & F_OP32))
			self->vr_regs.vr_eip &= 0xffff;
		if (op_flags & F_AD32)
			self->vr_regs.vr_esp += sp_adjustment;
		else {
			self->vr_regs.vr_sp += sp_adjustment;
		}
	}	break;


	case 0xcb:
		/* CB     RET     ZO     Valid     Valid     Far return to calling procedure. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_popl(self, &self->vr_regs.vr_eip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_cs = (uint16_t)temp;
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_ip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_cs, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		break;


	case 0xca: {
		uint16_t sp_adjustment;
		/* CA iw     RET imm16     I     Valid     Valid     Far return to calling procedure and pop imm16 bytes from stack. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		error = libvm86_read_pcword(self, &sp_adjustment);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_popl(self, &self->vr_regs.vr_eip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_cs = (uint16_t)temp;
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_ip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_cs, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
		if (op_flags & F_AD32)
			self->vr_regs.vr_esp += sp_adjustment;
		else {
			self->vr_regs.vr_sp += sp_adjustment;
		}
	}	break;


	case 0x9a: {
		uint32_t offset;
		uint16_t segment;
		/* 9A cd     CALL ptr16:16     D     Invalid     Valid     Call far, absolute, address given in operand.
		 * 9A cd     CALL ptr16:32     D     Invalid     Valid     Call far, absolute, address given in operand. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_AD32) {
			error = libvm86_read_pcdword(self, &offset);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_read_pcword(self, &segment);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_cs, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_eip, op_flags);
		} else {
			error = libvm86_read_pcword(self, &segment);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			offset = (uint32_t)segment;
			error  = libvm86_read_pcword(self, &segment);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_cs, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_ip, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_eip = offset;
		self->vr_regs.vr_cs  = segment;
	}	break;


	case 0xe8:
		/* E8 cw     CALL rel16     M     N.S.     Valid     Call near, relative, displacement relative to next instruction.
		 * E8 cd     CALL rel32     M     Valid     Valid     Call near, relative, displacement relative to next instruction. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			int32_t disp;
			error = libvm86_read_pcdword(self, (uint32_t *)&disp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushl(self, self->vr_regs.vr_eip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_eip += disp;
		} else {
			int16_t disp;
			error = libvm86_read_pcword(self, (uint16_t *)&disp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_pushw(self, self->vr_regs.vr_ip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_ip += disp;
			self->vr_regs.vr_eip &= 0xffff;
		}
		break;


#ifdef __INTELLISENSE__
#define DEFINE_ARITHMETIC_OPCODES(id, DO_REGB, DO_REGW, DO_REGL, DO_MEMB, DO_MEMW, DO_MEML) /* nothing */
#else /* __INTELLISENSE__ */
#define DEFINE_ARITHMETIC_OPCODES(id, DO_REGB, DO_REGW, DO_REGL, DO_MEMB, DO_MEMW, DO_MEML) \
	case (id * 8) + 0:                                                                      \
		error = libvm86_modrm_decode(self, &mod, op_flags);                                 \
		if unlikely(error != VM86_SUCCESS)                                                  \
			goto err;                                                                       \
		if (mod.mi_type == MODRM_REGISTER) {                                                \
			DO_REGB(REG8(mod.mi_rm), REG8(mod.mi_reg));                                     \
		} else {                                                                            \
			uint8_t *addr;                                                                  \
			addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);                  \
			DO_MEMB(addr, REG8(mod.mi_reg));                                                \
		}                                                                                   \
		break;                                                                              \
	case (id * 8) + 1:                                                                      \
		error = libvm86_modrm_decode(self, &mod, op_flags);                                 \
		if unlikely(error != VM86_SUCCESS)                                                  \
			goto err;                                                                       \
		if (op_flags & F_OP32) {                                                            \
			if (mod.mi_type == MODRM_REGISTER) {                                            \
				DO_REGL(REG32(mod.mi_rm), REG32(mod.mi_reg));                               \
			} else {                                                                        \
				uint32_t *addr;                                                             \
				addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);             \
				DO_MEML(addr, REG32(mod.mi_reg));                                           \
			}                                                                               \
		} else {                                                                            \
			if (mod.mi_type == MODRM_REGISTER) {                                            \
				DO_REGW(REG16(mod.mi_rm), REG16(mod.mi_reg));                               \
				REG32(mod.mi_rm) &= 0xffff;                                                 \
			} else {                                                                        \
				uint16_t *addr;                                                             \
				addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);             \
				DO_MEMW(addr, REG16(mod.mi_reg));                                           \
			}                                                                               \
		}                                                                                   \
		break;                                                                              \
	case (id * 8) + 2:                                                                      \
		error = libvm86_modrm_decode(self, &mod, op_flags);                                 \
		if unlikely(error != VM86_SUCCESS)                                                  \
			goto err;                                                                       \
		error = libvm86_modrm_readb(self, &mod, &opcode, op_flags);                         \
		if unlikely(error != VM86_SUCCESS)                                                  \
			goto err;                                                                       \
		DO_REGB(REG8(mod.mi_reg), opcode);                                                  \
		break;                                                                              \
	case (id * 8) + 3:                                                                      \
		error = libvm86_modrm_decode(self, &mod, op_flags);                                 \
		if unlikely(error != VM86_SUCCESS)                                                  \
			goto err;                                                                       \
		if (op_flags & F_OP32) {                                                            \
			uint32_t temp;                                                                  \
			error = libvm86_modrm_readl(self, &mod, &temp, op_flags);                       \
			if unlikely(error != VM86_SUCCESS)                                              \
				goto err;                                                                   \
			DO_REGL(REG32(mod.mi_reg), temp);                                               \
		} else {                                                                            \
			uint16_t temp;                                                                  \
			error = libvm86_modrm_readw(self, &mod, &temp, op_flags);                       \
			if unlikely(error != VM86_SUCCESS)                                              \
				goto err;                                                                   \
			DO_REGW(REG16(mod.mi_reg), temp);                                               \
			REG32(mod.mi_reg) &= 0xffff;                                                    \
		}                                                                                   \
		break;                                                                              \
	case (id * 8) + 4:                                                                      \
		if (op_flags & (F_LOCK))                                                            \
			goto err_ilop;                                                                  \
		error = libvm86_read_pcbyte(self, &opcode);                                         \
		if unlikely(error != VM86_SUCCESS)                                                  \
			goto err;                                                                       \
		DO_REGB(self->vr_regs.vr_al, opcode);                                               \
		break;                                                                              \
	case (id * 8) + 5:                                                                      \
		if (op_flags & (F_LOCK))                                                            \
			goto err_ilop;                                                                  \
		if (op_flags & F_OP32) {                                                            \
			uint32_t temp;                                                                  \
			error = libvm86_read_pcdword(self, &temp);                                      \
			if unlikely(error != VM86_SUCCESS)                                              \
				goto err;                                                                   \
			DO_REGL(self->vr_regs.vr_eax, temp);                                            \
		} else {                                                                            \
			uint16_t temp;                                                                  \
			error = libvm86_read_pcword(self, &temp);                                       \
			if unlikely(error != VM86_SUCCESS)                                              \
				goto err;                                                                   \
			DO_REGW(self->vr_regs.vr_ax, temp);                                             \
			self->vr_regs.vr_eax &= 0xffff;                                                 \
		}                                                                                   \
		break;                                                                              \
do_80h_reg##id:                                                                             \
		if (mod.mi_type == MODRM_REGISTER) {                                                \
			DO_REGB(REG8(mod.mi_rm), opcode);                                               \
		} else {                                                                            \
			uint8_t *addr;                                                                  \
			addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);                  \
			DO_MEMB(addr, opcode);                                                          \
		}                                                                                   \
		break;                                                                              \
do_81h_reg##id##_op16:                                                                      \
		if (mod.mi_type == MODRM_REGISTER) {                                                \
			DO_REGW(REG16(mod.mi_rm), operand16);                                           \
			REG32(mod.mi_rm) &= 0xffff;                                                     \
		} else {                                                                            \
			uint16_t *addr;                                                                 \
			addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);                 \
			DO_MEMW(addr, operand16);                                                       \
		}                                                                                   \
		break;                                                                              \
do_81h_reg##id##_op32:                                                                      \
		if (mod.mi_type == MODRM_REGISTER) {                                                \
			DO_REGL(REG32(mod.mi_rm), operand32);                                           \
		} else {                                                                            \
			uint32_t *addr;                                                                 \
			addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);                 \
			DO_MEML(addr, operand32);                                                       \
		}                                                                                   \
		break;
#endif /* !__INTELLISENSE__ */


#define DO_REGBITOPT(T, w, value, operand, atomic_opfetch, op) \
	{                                                          \
		value op## = operand;                                  \
		self->vr_regs.vr_flags &= ~(OF | CF | ZF | SF | PF);   \
		self->vr_regs.vr_flags |= f_test##w(value);            \
	}
#define DO_MEMBITOPT(T, w, addr, operand, atomic_opfetch, op) \
	{                                                         \
		T newval;                                             \
		GUARD_SEGFAULT({                                      \
			if (op_flags & F_LOCK) {                          \
				newval = atomic_opfetch(*addr, operand);      \
			} else {                                          \
				newval = *addr op operand;                    \
				*addr  = newval;                              \
			}                                                 \
		});                                                   \
		self->vr_regs.vr_flags &= ~(OF | CF | ZF | SF | PF);  \
		self->vr_regs.vr_flags |= f_test##w(newval);          \
	}

#define DO_REGARITHOPT(T, w, value, operand, f_evalflags, cc_mask, atomic_fetchop, op) \
	{                                                                                  \
		self->vr_regs.vr_flags &= ~(cc_mask);                                          \
		self->vr_regs.vr_flags |= f_evalflags(value, operand);                         \
		value op##= operand;                                                           \
	}
#define DO_MEMARITHOPT(T, w, addr, operand, f_evalflags, cc_mask, atomic_fetchop, op) \
	{                                                                                 \
		T oldval;                                                                     \
		GUARD_SEGFAULT({                                                              \
			if (op_flags & F_LOCK) {                                                  \
				oldval = atomic_fetchop(*addr, operand);                              \
			} else {                                                                  \
				oldval = *addr;                                                       \
				*addr  = oldval op operand;                                           \
			}                                                                         \
		});                                                                           \
		self->vr_regs.vr_flags &= ~(cc_mask);                                         \
		self->vr_regs.vr_flags |= f_evalflags(oldval, operand);                       \
	}






	{
		uint32_t operand32;
		uint16_t operand16;
		/* 00 /r     ADD r/m8, r8     MR     Valid     Valid     Add r8 to r/m8.
		 * 01 /r     ADD r/m16, r16   MR     Valid     Valid     Add r16 to r/m16.
		 * 01 /r     ADD r/m32, r32   MR     Valid     Valid     Add r32 to r/m32.
		 * 02 /r     ADD r8, r/m8     RM     Valid     Valid     Add r/m8 to r8.
		 * 03 /r     ADD r16, r/m16   RM     Valid     Valid     Add r/m16 to r16.
		 * 03 /r     ADD r32, r/m32   RM     Valid     Valid     Add r/m32 to r32.
		 * 04 ib     ADD AL, imm8     I      Valid     Valid     Add imm8 to AL.
		 * 05 iw     ADD AX, imm16    I      Valid     Valid     Add imm16 to AX.
		 * 05 id     ADD EAX, imm32   I      Valid     Valid     Add imm32 to EAX.
		 * 80 /0 ib  ADD r/m8, imm8   MI     Valid     Valid     Add imm8 to r/m8.
		 * 81 /0 iw  ADD r/m16, imm16 MI     Valid     Valid     Add imm16 to r/m16.
		 * 81 /0 id  ADD r/m32, imm32 MI     Valid     Valid     Add imm32 to r/m32.
		 * 83 /0 ib  ADD r/m16, imm8  MI     Valid     Valid     Add sign-extended imm8 to r/m16.
		 * 83 /0 ib  ADD r/m32, imm8  MI     Valid     Valid     Add sign-extended imm8 to r/m32. */
#define DO_REGADDB(value, operand) DO_REGARITHOPT(uint8_t, b, value, operand, f_addb, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHADD, +)
#define DO_REGADDW(value, operand) DO_REGARITHOPT(uint16_t, w, value, operand, f_addw, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHADD, +)
#define DO_REGADDL(value, operand) DO_REGARITHOPT(uint32_t, l, value, operand, f_addl, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHADD, +)
#define DO_MEMADDB(addr, operand)  DO_MEMARITHOPT(uint8_t, b, addr, operand, f_addb, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHADD, +)
#define DO_MEMADDW(addr, operand)  DO_MEMARITHOPT(uint16_t, w, addr, operand, f_addw, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHADD, +)
#define DO_MEMADDL(addr, operand)  DO_MEMARITHOPT(uint32_t, l, addr, operand, f_addl, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHADD, +)
		DEFINE_ARITHMETIC_OPCODES(0,
		                          DO_REGADDB,
		                          DO_REGADDW,
		                          DO_REGADDL,
		                          DO_MEMADDB,
		                          DO_MEMADDW,
		                          DO_MEMADDL)


		/* 08 /r     OR r/m8, r8       MR    Valid     Valid     r/m8 OR r8.
		 * 09 /r     OR r/m16, r16     MR    Valid     Valid     r/m16 OR r16.
		 * 09 /r     OR r/m32, r32     MR    Valid     Valid     r/m32 OR r32.
		 * 0A /r     OR r8, r/m8       RM    Valid     Valid     r8 OR r/m8.
		 * 0B /r     OR r16, r/m16     RM    Valid     Valid     r16 OR r/m16.
		 * 0B /r     OR r32, r/m32     RM    Valid     Valid     r32 OR r/m32.
		 * 0C ib     OR AL, imm8       I     Valid     Valid     AL OR imm8.
		 * 0D iw     OR AX, imm16      I     Valid     Valid     AX OR imm16.
		 * 0D id     OR EAX, imm32     I     Valid     Valid     EAX OR imm32.
		 * 80 /1 ib  OR r/m8, imm8     MI    Valid     Valid     r/m8 OR imm8.
		 * 81 /1 iw  OR r/m16, imm16   MI    Valid     Valid     r/m16 OR imm16.
		 * 81 /1 id  OR r/m32, imm32   MI    Valid     Valid     r/m32 OR imm32.
		 * 83 /1 ib  OR r/m16, imm8    MI    Valid     Valid     r/m16 OR imm8 (sign-extended).
		 * 83 /1 ib  OR r/m32, imm8    MI    Valid     Valid     r/m32 OR imm8 (sign-extended). */
#define DO_REGORB(value, operand) DO_REGBITOPT(uint8_t, b, value, operand, ATOMIC_ORFETCH, |)
#define DO_REGORW(value, operand) DO_REGBITOPT(uint16_t, w, value, operand, ATOMIC_ORFETCH, |)
#define DO_REGORL(value, operand) DO_REGBITOPT(uint32_t, l, value, operand, ATOMIC_ORFETCH, |)
#define DO_MEMORB(addr, operand)  DO_MEMBITOPT(uint8_t, b, addr, operand, ATOMIC_ORFETCH, |)
#define DO_MEMORW(addr, operand)  DO_MEMBITOPT(uint16_t, w, addr, operand, ATOMIC_ORFETCH, |)
#define DO_MEMORL(addr, operand)  DO_MEMBITOPT(uint32_t, l, addr, operand, ATOMIC_ORFETCH, |)
		DEFINE_ARITHMETIC_OPCODES(1,
		                          DO_REGORB,
		                          DO_REGORW,
		                          DO_REGORL,
		                          DO_MEMORB,
		                          DO_MEMORW,
		                          DO_MEMORL)

#define DO_MEMCARRYT(T, f_carryfunc, addr, operand)                                                     \
		{                                                                                               \
			GUARD_SEGFAULT({                                                                            \
				T oldval;                                                                               \
				if (op_flags & F_LOCK) {                                                                \
					uint16_t temp_flags;                                                                \
					do {                                                                                \
						temp_flags = self->vr_regs.vr_flags;                                            \
						oldval     = ATOMIC_READ(*addr);                                                \
					} while (!ATOMIC_CMPXCH(*addr, oldval, f_carryfunc(oldval, operand, &temp_flags))); \
					self->vr_regs.vr_flags = temp_flags;                                                \
				} else {                                                                                \
					*addr = f_carryfunc(*addr, operand, &self->vr_regs.vr_flags);                       \
				}                                                                                       \
			});                                                                                         \
		}


		/* 10 /r     ADC r/m8, r8      MR    Valid     Valid     Add with carry byte register to r/m8.
		 * 11 /r     ADC r/m16, r16    MR    Valid     Valid     Add with carry r16 to r/m16.
		 * 11 /r     ADC r/m32, r32    MR    Valid     Valid     Add with carry r32 to r/m32.
		 * 12 /r     ADC r8, r/m8      RM    Valid     Valid     Add with carry r/m8 to byte register.
		 * 13 /r     ADC r16, r/m16    RM    Valid     Valid     Add with carry r/m16 to r16.
		 * 13 /r     ADC r32, r/m32    RM    Valid     Valid     Add with carry r/m32 to r32.
		 * 14 ib     ADC AL, imm8      I     Valid     Valid     Add with carry imm8 to AL.
		 * 15 iw     ADC AX, imm16     I     Valid     Valid     Add with carry imm16 to AX.
		 * 15 id     ADC EAX, imm32    I     Valid     Valid     Add with carry imm32 to EAX.
		 * 80 /2 ib  ADC r/m8, imm8    MI    Valid     Valid     Add with carry imm8 to r/m8.
		 * 81 /2 iw  ADC r/m16, imm16  MI    Valid     Valid     Add with carry imm16 to r/m16.
		 * 81 /2 id  ADC r/m32, imm32  MI    Valid     Valid     Add with carry imm32 to r/m32.
		 * 83 /2 ib  ADC r/m16, imm8   MI    Valid     Valid     Add with carry sign-extended imm8 to r/m16.
		 * 83 /2 ib  ADC r/m32, imm8   MI    Valid     Valid     Add with carry sign-extended imm8 into r/m32. */
#define DO_REGADCB(value, operand) { value = f_adcb(value, operand, &self->vr_regs.vr_flags); }
#define DO_REGADCW(value, operand) { value = f_adcw(value, operand, &self->vr_regs.vr_flags); }
#define DO_REGADCL(value, operand) { value = f_adcl(value, operand, &self->vr_regs.vr_flags); }
#define DO_MEMADCB(addr, operand)  DO_MEMCARRYT(uint8_t, f_adcb, addr, operand)
#define DO_MEMADCW(addr, operand)  DO_MEMCARRYT(uint16_t, f_adcw, addr, operand)
#define DO_MEMADCL(addr, operand)  DO_MEMCARRYT(uint32_t, f_adcl, addr, operand)
		DEFINE_ARITHMETIC_OPCODES(2,
		                          DO_REGADCB,
		                          DO_REGADCW,
		                          DO_REGADCL,
		                          DO_MEMADCB,
		                          DO_MEMADCW,
		                          DO_MEMADCL)

		/* 10 /r     SBB r/m8, r8      MR    Valid     Valid     Subtract with borrow byte register to r/m8.
		 * 11 /r     SBB r/m16, r16    MR    Valid     Valid     Subtract with borrow r16 to r/m16.
		 * 11 /r     SBB r/m32, r32    MR    Valid     Valid     Subtract with borrow r32 to r/m32.
		 * 12 /r     SBB r8, r/m8      RM    Valid     Valid     Subtract with borrow r/m8 to byte register.
		 * 13 /r     SBB r16, r/m16    RM    Valid     Valid     Subtract with borrow r/m16 to r16.
		 * 13 /r     SBB r32, r/m32    RM    Valid     Valid     Subtract with borrow r/m32 to r32.
		 * 14 ib     SBB AL, imm8      I     Valid     Valid     Subtract with borrow imm8 to AL.
		 * 15 iw     SBB AX, imm16     I     Valid     Valid     Subtract with borrow imm16 to AX.
		 * 15 id     SBB EAX, imm32    I     Valid     Valid     Subtract with borrow imm32 to EAX.
		 * 80 /2 ib  SBB r/m8, imm8    MI    Valid     Valid     Subtract with borrow imm8 to r/m8.
		 * 81 /2 iw  SBB r/m16, imm16  MI    Valid     Valid     Subtract with borrow imm16 to r/m16.
		 * 81 /2 id  SBB r/m32, imm32  MI    Valid     Valid     Subtract with borrow imm32 to r/m32.
		 * 83 /2 ib  SBB r/m16, imm8   MI    Valid     Valid     Subtract with borrow sign-extended imm8 to r/m16.
		 * 83 /2 ib  SBB r/m32, imm8   MI    Valid     Valid     Subtract with borrow sign-extended imm8 into r/m32. */
#define DO_REGSBBB(value, operand) { value = f_sbbb(value, operand, &self->vr_regs.vr_flags); }
#define DO_REGSBBW(value, operand) { value = f_sbbw(value, operand, &self->vr_regs.vr_flags); }
#define DO_REGSBBL(value, operand) { value = f_sbbl(value, operand, &self->vr_regs.vr_flags); }
#define DO_MEMSBBB(addr, operand)  DO_MEMCARRYT(uint8_t, f_sbbb, addr, operand)
#define DO_MEMSBBW(addr, operand)  DO_MEMCARRYT(uint16_t, f_sbbw, addr, operand)
#define DO_MEMSBBL(addr, operand)  DO_MEMCARRYT(uint32_t, f_sbbl, addr, operand)
		DEFINE_ARITHMETIC_OPCODES(3,
		                          DO_REGSBBB,
		                          DO_REGSBBW,
		                          DO_REGSBBL,
		                          DO_MEMSBBB,
		                          DO_MEMSBBW,
		                          DO_MEMSBBL)

		/* 20 /r     AND r/m8, r8      MR    Valid     Valid     r/m8 AND r8.
		 * 21 /r     AND r/m16, r16    MR    Valid     Valid     r/m16 AND r16.
		 * 21 /r     AND r/m32, r32    MR    Valid     Valid     r/m32 AND r32.
		 * 22 /r     AND r8, r/m8      RM    Valid     Valid     r8 AND r/m8.
		 * 23 /r     AND r16, r/m16    RM    Valid     Valid     r16 AND r/m16.
		 * 23 /r     AND r32, r/m32    RM    Valid     Valid     r32 AND r/m32.
		 * 24 ib     AND AL, imm8      I     Valid     Valid     AL AND imm8.
		 * 25 iw     AND AX, imm16     I     Valid     Valid     AX AND imm16.
		 * 25 id     AND EAX, imm32    I     Valid     Valid     EAX AND imm32.
		 * 80 /4 ib  AND r/m8, imm8    MI    Valid     Valid     r/m8 AND imm8.
		 * 81 /4 iw  AND r/m16, imm16  MI    Valid     Valid     r/m16 AND imm16.
		 * 81 /4 id  AND r/m32, imm32  MI    Valid     Valid     r/m32 AND imm32.
		 * 83 /4 ib  AND r/m16, imm8   MI    Valid     Valid     r/m16 AND imm8 (sign-extended).
		 * 83 /4 ib  AND r/m32, imm8   MI    Valid     Valid     r/m32 AND imm8 (sign-extended). */
#define DO_REGANDB(value, operand) DO_REGBITOPT(uint8_t, b, value, operand, ATOMIC_ANDFETCH, &)
#define DO_REGANDW(value, operand) DO_REGBITOPT(uint16_t, w, value, operand, ATOMIC_ANDFETCH, &)
#define DO_REGANDL(value, operand) DO_REGBITOPT(uint32_t, l, value, operand, ATOMIC_ANDFETCH, &)
#define DO_MEMANDB(addr, operand)  DO_MEMBITOPT(uint8_t, b, addr, operand, ATOMIC_ANDFETCH, &)
#define DO_MEMANDW(addr, operand)  DO_MEMBITOPT(uint16_t, w, addr, operand, ATOMIC_ANDFETCH, &)
#define DO_MEMANDL(addr, operand)  DO_MEMBITOPT(uint32_t, l, addr, operand, ATOMIC_ANDFETCH, &)
		DEFINE_ARITHMETIC_OPCODES(4,
		                          DO_REGANDB,
		                          DO_REGANDW,
		                          DO_REGANDL,
		                          DO_MEMANDB,
		                          DO_MEMANDW,
		                          DO_MEMANDL)

		/* 28 /r     SUB r/m8, r8      MR    Valid     Valid     Subtract r8 from r/m8.
		 * 29 /r     SUB r/m16, r16    MR    Valid     Valid     Subtract r16 from r/m16.
		 * 29 /r     SUB r/m32, r32    MR    Valid     Valid     Subtract r32 from r/m32.
		 * 2A /r     SUB r8, r/m8      RM    Valid     Valid     Subtract r/m8 from r8.
		 * 2B /r     SUB r16, r/m16    RM    Valid     Valid     Subtract r/m16 from r16.
		 * 2B /r     SUB r32, r/m32    RM    Valid     Valid     Subtract r/m32 from r32.
		 * 2C ib     SUB AL, imm8      I     Valid     Valid     Subtract imm8 from AL.
		 * 2D iw     SUB AX, imm16     I     Valid     Valid     Subtract imm16 from AX.
		 * 2D id     SUB EAX, imm32    I     Valid     Valid     Subtract imm32 from EAX.
		 * 80 /5 ib  SUB r/m8, imm8    MI    Valid     Valid     Subtract imm8 from r/m8.
		 * 81 /5 iw  SUB r/m16, imm16  MI    Valid     Valid     Subtract imm16 from r/m16.
		 * 81 /5 id  SUB r/m32, imm32  MI    Valid     Valid     Subtract imm32 from r/m32.
		 * 83 /5 ib  SUB r/m16, imm8   MI    Valid     Valid     Subtract sign-extended imm8 from r/m16.
		 * 83 /5 ib  SUB r/m32, imm8   MI    Valid     Valid     Subtract sign-extended imm8 from r/m32. */
#define DO_REGSUBB(value, operand) DO_REGARITHOPT(uint8_t, b, value, operand, f_cmpb, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHSUB, -)
#define DO_REGSUBW(value, operand) DO_REGARITHOPT(uint16_t, w, value, operand, f_cmpw, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHSUB, -)
#define DO_REGSUBL(value, operand) DO_REGARITHOPT(uint32_t, l, value, operand, f_cmpl, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHSUB, -)
#define DO_MEMSUBB(addr, operand)  DO_MEMARITHOPT(uint8_t, b, addr, operand, f_cmpb, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHSUB, -)
#define DO_MEMSUBW(addr, operand)  DO_MEMARITHOPT(uint16_t, w, addr, operand, f_cmpw, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHSUB, -)
#define DO_MEMSUBL(addr, operand)  DO_MEMARITHOPT(uint32_t, l, addr, operand, f_cmpl, OF | SF | ZF | AF | CF | PF, ATOMIC_FETCHSUB, -)
		DEFINE_ARITHMETIC_OPCODES(5,
		                          DO_REGSUBB,
		                          DO_REGSUBW,
		                          DO_REGSUBL,
		                          DO_MEMSUBB,
		                          DO_MEMSUBW,
		                          DO_MEMSUBL)

		/* 30 /r     XOR r/m8, r8      MR    Valid     Valid     r/m8 XOR r8.
		 * 31 /r     XOR r/m16, r16    MR    Valid     Valid     r/m16 XOR r16.
		 * 31 /r     XOR r/m32, r32    MR    Valid     Valid     r/m32 XOR r32.
		 * 32 /r     XOR r8, r/m8      RM    Valid     Valid     r8 XOR r/m8.
		 * 33 /r     XOR r16, r/m16    RM    Valid     Valid     r16 XOR r/m16.
		 * 33 /r     XOR r32, r/m32    RM    Valid     Valid     r32 XOR r/m32.
		 * 34 ib     XOR AL, imm8      I     Valid     Valid     AL XOR imm8.
		 * 35 iw     XOR AX, imm16     I     Valid     Valid     AX XOR imm16.
		 * 35 id     XOR EAX, imm32    I     Valid     Valid     EAX XOR imm32.
		 * 80 /6 ib  XOR r/m8, imm8    MI    Valid     Valid     r/m8 XOR imm8.
		 * 81 /6 iw  XOR r/m16, imm16  MI    Valid     Valid     r/m16 XOR imm16.
		 * 81 /6 id  XOR r/m32, imm32  MI    Valid     Valid     r/m32 XOR imm32.
		 * 83 /6 ib  XOR r/m16, imm8   MI    Valid     Valid     r/m16 XOR imm8 (sign-extended).
		 * 83 /6 ib  XOR r/m32, imm8   MI    Valid     Valid     r/m32 XOR imm8 (sign-extended). */
#define DO_REGXORB(value, operand) DO_REGBITOPT(uint8_t, b, value, operand, ATOMIC_XORFETCH, ^)
#define DO_REGXORW(value, operand) DO_REGBITOPT(uint16_t, w, value, operand, ATOMIC_XORFETCH, ^)
#define DO_REGXORL(value, operand) DO_REGBITOPT(uint32_t, l, value, operand, ATOMIC_XORFETCH, ^)
#define DO_MEMXORB(addr, operand)  DO_MEMBITOPT(uint8_t, b, addr, operand, ATOMIC_XORFETCH, ^)
#define DO_MEMXORW(addr, operand)  DO_MEMBITOPT(uint16_t, w, addr, operand, ATOMIC_XORFETCH, ^)
#define DO_MEMXORL(addr, operand)  DO_MEMBITOPT(uint32_t, l, addr, operand, ATOMIC_XORFETCH, ^)
		DEFINE_ARITHMETIC_OPCODES(6,
		                          DO_REGXORB,
		                          DO_REGXORW,
		                          DO_REGXORL,
		                          DO_MEMXORB,
		                          DO_MEMXORW,
		                          DO_MEMXORL)

		/* 38 /r     CMP r/m8, r8      MR    Valid     Valid     Compare r8 with r/m8.
		 * 39 /r     CMP r/m16, r16    MR    Valid     Valid     Compare r16 with r/m16.
		 * 39 /r     CMP r/m32, r32    MR    Valid     Valid     Compare r32 with r/m32.
		 * 3A /r     CMP r8, r/m8      RM    Valid     Valid     Compare r/m8 with r8.
		 * 3B /r     CMP r16, r/m16    RM    Valid     Valid     Compare r/m16 with r16.
		 * 3B /r     CMP r32, r/m32    RM    Valid     Valid     Compare r/m32 with r32.
		 * 3C ib     CMP AL, imm8      I     Valid     Valid     Compare imm8 with AL.
		 * 3D iw     CMP AX, imm16     I     Valid     Valid     Compare imm16 with AX.
		 * 3D id     CMP EAX, imm32    I     Valid     Valid     Compare imm32 with EAX.
		 * 80 /7 ib  CMP r/m8, imm8    MI    Valid     Valid     Compare imm8 with r/m8.
		 * 81 /7 iw  CMP r/m16, imm16  MI    Valid     Valid     Compare imm16 with r/m16.
		 * 81 /7 id  CMP r/m32, imm32  MI    Valid     Valid     Compare imm32 with r/m32.
		 * 83 /7 ib  CMP r/m16, imm8   MI    Valid     Valid     Compare sign-extended imm8 with r/m16.
		 * 83 /7 ib  CMP r/m32, imm8   MI    Valid     Valid     Compare sign-extended imm8 with r/m32. */
#define DO_REGCMPT(T, w, value, operand, f_evalflags, cc_mask)     \
		{                                                          \
			self->vr_regs.vr_flags &= ~(cc_mask);                  \
			self->vr_regs.vr_flags |= f_evalflags(value, operand); \
		}
#define DO_MEMCMPT(T, w, addr, operand, f_evalflags, cc_mask)       \
		{                                                           \
			T oldval;                                               \
			if unlikely(op_flags & F_LOCK)                          \
				goto err_ilop;                                      \
			GUARD_SEGFAULT({                                        \
				oldval = *addr;                                     \
			});                                                     \
			self->vr_regs.vr_flags &= ~(cc_mask);                   \
			self->vr_regs.vr_flags |= f_evalflags(oldval, operand); \
		}
#define DO_REGCMPB(value, operand) DO_REGCMPT(uint8_t, b, value, operand, f_cmpb, OF | SF | ZF | AF | CF | PF)
#define DO_REGCMPW(value, operand) DO_REGCMPT(uint16_t, w, value, operand, f_cmpw, OF | SF | ZF | AF | CF | PF)
#define DO_REGCMPL(value, operand) DO_REGCMPT(uint32_t, l, value, operand, f_cmpl, OF | SF | ZF | AF | CF | PF)
#define DO_MEMCMPB(addr, operand)  DO_MEMCMPT(uint8_t, b, addr, operand, f_cmpb, OF | SF | ZF | AF | CF | PF)
#define DO_MEMCMPW(addr, operand)  DO_MEMCMPT(uint16_t, w, addr, operand, f_cmpw, OF | SF | ZF | AF | CF | PF)
#define DO_MEMCMPL(addr, operand)  DO_MEMCMPT(uint32_t, l, addr, operand, f_cmpl, OF | SF | ZF | AF | CF | PF)
		DEFINE_ARITHMETIC_OPCODES(7,
		                          DO_REGCMPB,
		                          DO_REGCMPW,
		                          DO_REGCMPL,
		                          DO_MEMCMPB,
		                          DO_MEMCMPW,
		                          DO_MEMCMPL)


#ifndef __INTELLISENSE__
	case 0x80:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		switch (mod.mi_reg) {
		case 0: goto do_80h_reg0;
		case 1: goto do_80h_reg1;
		case 2: goto do_80h_reg2;
		case 3: goto do_80h_reg3;
		case 4: goto do_80h_reg4;
		case 5: goto do_80h_reg5;
		case 6: goto do_80h_reg6;
		case 7: goto do_80h_reg7;
		default: goto err_ilop;
		}
		break;

	case 0x81:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			error = libvm86_read_pcdword(self, &operand32);
			if unlikely(error != VM86_SUCCESS)
				goto err;
do_81h_op32:
			switch (mod.mi_reg) {
			case 0: goto do_81h_reg0_op32;
			case 1: goto do_81h_reg1_op32;
			case 2: goto do_81h_reg2_op32;
			case 3: goto do_81h_reg3_op32;
			case 4: goto do_81h_reg4_op32;
			case 5: goto do_81h_reg5_op32;
			case 6: goto do_81h_reg6_op32;
			case 7: goto do_81h_reg7_op32;
			default: goto err_ilop;
			}
		} else {
			error = libvm86_read_pcword(self, &operand16);
			if unlikely(error != VM86_SUCCESS)
				goto err;
do_81h_op16:
			switch (mod.mi_reg) {
			case 0: goto do_81h_reg0_op16;
			case 1: goto do_81h_reg1_op16;
			case 2: goto do_81h_reg2_op16;
			case 3: goto do_81h_reg3_op16;
			case 4: goto do_81h_reg4_op16;
			case 5: goto do_81h_reg5_op16;
			case 6: goto do_81h_reg6_op16;
			case 7: goto do_81h_reg7_op16;
			default: goto err_ilop;
			}
		}
		break;

	case 0x83:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			operand32 = (uint32_t)(int32_t)(int8_t)opcode;
			goto do_81h_op32;
		}
		operand16 = (uint16_t)(int16_t)(int8_t)opcode;
		goto do_81h_op16;
#endif /* !__INTELLISENSE__ */
	}	break;

	case 0x9e:
		/* 9E     SAHF     ZO     Invalid*     Valid     Loads SF, ZF, AF, PF, and CF from AH into EFLAGS register. */
		self->vr_regs.vr_flags &= ~(SF | ZF | AF | PF | CF);
		self->vr_regs.vr_flags |= self->vr_regs.vr_ah & (SF | ZF | AF | PF | CF);
		break;

	case 0x9f:
		/* 9F     LAHF     ZO     Invalid*     Valid     Load: AH := EFLAGS(SF:ZF:0:AF:0:PF:1:CF). */
		self->vr_regs.vr_ah = self->vr_regs.vr_flags & (SF | ZF | AF | PF | CF);
		break;


	case 0x27: {
		uint8_t old_al;
		uint16_t old_flags;
		/* 27     DAA     ZO     Invalid     Valid     Decimal adjust AL after addition. */
		old_al    = self->vr_regs.vr_al;
		old_flags = self->vr_regs.vr_flags;
		self->vr_regs.vr_flags &= ~CF;
		if ((old_al & 0x0f) > 9 || (self->vr_regs.vr_flags & AF)) {
			uint16_t flags      = 0;
			self->vr_regs.vr_al = f_adcb(old_al, 6, &flags);
			self->vr_regs.vr_flags |= flags & CF;
			self->vr_regs.vr_flags |= AF;
		} else {
			self->vr_regs.vr_flags &= ~AF;
		}
		if ((old_al > 0x99) || (old_flags & CF)) {
			self->vr_regs.vr_al += 0x60;
			self->vr_regs.vr_flags |= CF;
		} else {
			self->vr_regs.vr_flags &= ~CF;
		}
	}	break;


	case 0x2f: {
		uint8_t old_al;
		uint16_t old_flags;
		/* 2F     DAS     ZO     Invalid     Valid     Decimal adjust AL after subtraction. */
		old_al    = self->vr_regs.vr_al;
		old_flags = self->vr_regs.vr_flags;
		self->vr_regs.vr_flags &= ~CF;
		if ((old_al & 0x0f) > 9 || (old_flags & AF)) {
			uint16_t flags      = 0;
			self->vr_regs.vr_al = f_sbbb(old_al, 6, &flags);
			self->vr_regs.vr_flags |= flags & CF;
			self->vr_regs.vr_flags |= AF;
		} else {
			self->vr_regs.vr_flags &= ~AF;
		}
		if ((old_al > 0x99) || (old_flags & CF)) {
			self->vr_regs.vr_al -= 0x60;
			self->vr_regs.vr_flags |= CF;
		} /*else {
			self->vr_regs.vr_flags &= ~CF;
		}*/
	}	break;

	case 0x40 ... 0x47:
		/* 40+ rw**   INC r16     O     N.E.     Valid     Increment word register by 1.
		 * 40+ rd     INC r32     O     N.E.     Valid     Increment doubleword register by 1. */
		self->vr_regs.vr_flags &= ~(OF | SF | ZF | AF | PF);
		self->vr_regs.vr_flags |= op_flags & F_OP32
		                          ? f_addl(REG32((uint8_t)(opcode - 0x40))++, (uint32_t)1) & (OF | SF | ZF | AF | PF)
		                          : f_addw(REG16((uint8_t)(opcode - 0x40))++, (uint16_t)1) & (OF | SF | ZF | AF | PF);
		break;

	case 0x48 ... 0x4f:
		/* 40+ rw**   DEC r16     O     N.E.     Valid     Decrement word register by 1.
		 * 40+ rd     DEC r32     O     N.E.     Valid     Decrement doubleword register by 1. */
		self->vr_regs.vr_flags &= ~(OF | SF | ZF | AF | PF);
		self->vr_regs.vr_flags |= op_flags & F_OP32
		                          ? f_addl(REG32((uint8_t)(opcode - 0x48))--, (uint32_t)-1) & (OF | SF | ZF | AF | PF)
		                          : f_addw(REG16((uint8_t)(opcode - 0x48))--, (uint16_t)-1) & (OF | SF | ZF | AF | PF);
		break;


	case 0x62:
		/* 62 /r     BOUND r16, m16&16     RM     Invalid     Valid     Check if r16 (array index) is within bounds specified by m16&16.
		 * 62 /r     BOUND r32, m32&32     RM     Invalid     Valid     Check if r32 (array index) is within bounds specified by m32&32. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if unlikely(mod.mi_type == MODRM_REGISTER)
			goto err_ilop;
		{
			void *addr;
			addr = libvm86_modrm_getaddr(self, &mod, op_flags);
			if (op_flags & F_OP32) {
				int32_t lo, hi;
				GUARD_SEGFAULT({
					lo = ((int32_t *)addr)[0];
					hi = ((int32_t *)addr)[1];
				});
				if ((int32_t)REG32(mod.mi_reg) < lo ||
				    (int32_t)REG32(mod.mi_reg) > hi)
					libvm86_intr(self, 5); /* #BR */
			} else {
				int16_t lo, hi;
				GUARD_SEGFAULT({
					lo = ((int16_t *)addr)[0];
					hi = ((int16_t *)addr)[1];
				});
				if ((int16_t)REG16(mod.mi_reg) < lo ||
				    (int16_t)REG16(mod.mi_reg) > hi)
					libvm86_intr(self, 5); /* #BR */
			}
		}
		break;

	case 0xe9:
		/* E9 cw     JMP rel16     M     N.S.     Valid     Jump near, relative, displacement relative to next instruction.
		 * E9 cd     JMP rel32     M     Valid    Valid     Jump near, relative, displacement relative to next instruction. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_OP32) {
			int32_t disp;
			error = libvm86_read_pcdword(self, (uint32_t *)&disp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_eip += disp;
		} else {
			int16_t disp;
			error = libvm86_read_pcword(self, (uint16_t *)&disp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_ip += disp;
			self->vr_regs.vr_eip &= 0xffff;
		}
		break;

	case 0xea: {
		uint32_t offset;
		uint16_t segment;
		/* EA cd     JMP ptr16:16     D     Invalid     Valid     Jump far, absolute, address given in operand.
		 * EA cd     JMP ptr16:32     D     Invalid     Valid     Jump far, absolute, address given in operand. */
		if (op_flags & (F_LOCK))
			goto err_ilop;
		if (op_flags & F_AD32) {
			error = libvm86_read_pcdword(self, &offset);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_read_pcword(self, &segment);
		} else {
			error = libvm86_read_pcword(self, &segment);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			offset = (uint32_t)segment;
			error  = libvm86_read_pcword(self, &segment);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_eip = offset;
		self->vr_regs.vr_cs  = segment;
	}	break;


	case 0xeb:
		/* EB cb     JMP rel8     D     Valid     Valid     Jump short, RIP = RIP + 8-bit displacement sign extended to 64-bits */
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_eip += (uint32_t)(int32_t)(int8_t)opcode;
		break;


	case 0xfe:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		switch (mod.mi_reg) {

		case 0:
			/* FE /0     INC r/m8     M     Valid     Valid     Increment r/m byte by 1. */
			self->vr_regs.vr_flags &= ~(OF | SF | ZF | AF | PF);
			if (mod.mi_type == MODRM_REGISTER) {
				self->vr_regs.vr_flags |= f_addb(REG8(mod.mi_rm)++, (uint8_t)1) & (OF | SF | ZF | AF | PF);
			} else {
				uint8_t *addr, oldval;
				addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						oldval = ATOMIC_FETCHINC(*addr);
					} else {
						oldval = *addr;
						*addr  = oldval + 1;
					}
				});
				self->vr_regs.vr_flags |= f_addb(oldval, (uint8_t)1) & (OF | SF | ZF | AF | PF);
			}
			break;

		case 1:
			/* FE /1     DEC r/m8     M     Valid     Valid     Decrement r/m8 by 1. */
			self->vr_regs.vr_flags &= ~(OF | SF | ZF | AF | PF);
			if (mod.mi_type == MODRM_REGISTER) {
				self->vr_regs.vr_flags |= f_addb(REG8(mod.mi_rm)--, (uint8_t)-1) & (OF | SF | ZF | AF | PF);
			} else {
				uint8_t *addr, oldval;
				addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						oldval = ATOMIC_FETCHDEC(*addr);
					} else {
						oldval = *addr;
						*addr  = oldval - 1;
					}
				});
				self->vr_regs.vr_flags |= f_addb(oldval, (uint8_t)-1) & (OF | SF | ZF | AF | PF);
			}
			break;

		default:
			goto err_ilop;
		}
		break;


	case 0xff:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		switch (mod.mi_reg) {

		case 0:
			/* FF /0     INC r/m16     M     Valid     Valid     Increment r/m word by 1.
			 * FF /0     INC r/m32     M     Valid     Valid     Increment r/m doubleword by 1. */
			self->vr_regs.vr_flags &= ~(OF | SF | ZF | AF | PF);
			if (mod.mi_type == MODRM_REGISTER) {
				self->vr_regs.vr_flags |= op_flags & F_OP32
				                          ? f_addl(REG32(mod.mi_rm)++, (uint32_t)1) & (OF | SF | ZF | AF | PF)
				                          : f_addw(REG16(mod.mi_rm)++, (uint16_t)1) & (OF | SF | ZF | AF | PF);
			} else {
				void *addr;
				addr = libvm86_modrm_getaddr(self, &mod, op_flags);
				if (op_flags & F_OP32) {
					uint32_t oldval;
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							oldval = ATOMIC_FETCHINC(*(uint32_t *)addr);
						} else {
							oldval = UNALIGNED_GET32((uint32_t *)addr);
							UNALIGNED_SET32((uint32_t *)addr, oldval + 1);
						}
					});
					self->vr_regs.vr_flags |= f_addl(oldval, (uint32_t)1) & (OF | SF | ZF | AF | PF);
				} else {
					uint16_t oldval;
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							oldval = ATOMIC_FETCHINC(*(uint16_t *)addr);
						} else {
							oldval = UNALIGNED_GET16((uint16_t *)addr);
							UNALIGNED_SET16((uint16_t *)addr, oldval + 1);
						}
					});
					self->vr_regs.vr_flags |= f_addw(oldval, (uint16_t)1) & (OF | SF | ZF | AF | PF);
				}
			}
			break;


		case 1:
			/* FF /1     DEC r/m16     M     Valid     Valid     Decrement r/m16 by 1.
			 * FF /1     DEC r/m32     M     Valid     Valid     Decrement r/m32 by 1. */
			self->vr_regs.vr_flags &= ~(OF | SF | ZF | AF | PF);
			if (mod.mi_type == MODRM_REGISTER) {
				self->vr_regs.vr_flags |= op_flags & F_OP32
				                          ? f_addl(REG32(mod.mi_rm)--, (uint32_t)-1) & (OF | SF | ZF | AF | PF)
				                          : f_addw(REG16(mod.mi_rm)--, (uint16_t)-1) & (OF | SF | ZF | AF | PF);
			} else {
				void *addr;
				addr = libvm86_modrm_getaddr(self, &mod, op_flags);
				if (op_flags & F_OP32) {
					uint32_t oldval;
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							oldval = ATOMIC_FETCHDEC(*(uint32_t *)addr);
						} else {
							oldval = UNALIGNED_GET32((uint32_t *)addr);
							UNALIGNED_SET32((uint32_t *)addr, oldval - 1);
						}
					});
					self->vr_regs.vr_flags |= f_addl(oldval, (uint32_t)-1) & (OF | SF | ZF | AF | PF);
				} else {
					uint16_t oldval;
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							oldval = ATOMIC_FETCHDEC(*(uint16_t *)addr);
						} else {
							oldval = UNALIGNED_GET16((uint16_t *)addr);
							UNALIGNED_SET16((uint16_t *)addr, oldval - 1);
						}
					});
					self->vr_regs.vr_flags |= f_addw(oldval, (uint16_t)-1) & (OF | SF | ZF | AF | PF);
				}
			}
			break;


		case 2:
			/* FF /2     CALL r/m16     M     N.E.     Valid     Call near, absolute indirect, address given in r/m16.
			 * FF /2     CALL r/m32     M     N.E.     Valid     Call near, absolute indirect, address given in r/m32. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (op_flags & F_OP32) {
				uint32_t addr;
				error = libvm86_modrm_readl(self, &mod, &addr, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_pushl(self, self->vr_regs.vr_eip, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_eip = addr;
			} else {
				uint16_t addr;
				error = libvm86_modrm_readw(self, &mod, &addr, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_pushw(self, self->vr_regs.vr_ip, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_eip = addr;
			}
			break;


		case 3: {
			void *addr;
			/* FF /3     CALL m16:16     M     Valid     Valid     Call far, absolute indirect address given in m16:16.
			 * FF /3     CALL m16:32     M     Valid     Valid     Call far, absolute indirect address given in m16:32. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (mod.mi_type == MODRM_REGISTER)
				goto err_ilop;
			addr = libvm86_modrm_getaddr(self, &mod, op_flags);
			if (op_flags & F_OP32) {
				error = libvm86_pushl(self, self->vr_regs.vr_cs, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_pushl(self, self->vr_regs.vr_eip, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				GUARD_SEGFAULT({
					self->vr_regs.vr_eip = UNALIGNED_GET32((uint32_t *)((byte_t *)addr + 0));
					self->vr_regs.vr_cs  = UNALIGNED_GET16((uint16_t *)((byte_t *)addr + 4));
				});
			} else {
				error = libvm86_pushw(self, self->vr_regs.vr_cs, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_pushw(self, self->vr_regs.vr_ip, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				GUARD_SEGFAULT({
					self->vr_regs.vr_eip = UNALIGNED_GET16((uint16_t *)((byte_t *)addr + 0));
					self->vr_regs.vr_cs  = UNALIGNED_GET16((uint16_t *)((byte_t *)addr + 2));
				});
			}
		}	break;


		case 4:
			/* FF /4     JMP r/m16     M     N.E.     Valid     Jump near, absolute indirect, address given in r/m16.
			 * FF /4     JMP r/m32     M     N.E.     Valid     Jump near, absolute indirect, address given in r/m32. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (op_flags & F_OP32) {
				error = libvm86_modrm_readl(self, &mod, &self->vr_regs.vr_eip, op_flags);
			} else {
				error = libvm86_modrm_readw(self, &mod, &self->vr_regs.vr_ip, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_eip &= 0xffff;
			}
			if unlikely(error != VM86_SUCCESS)
				goto err;
			break;


		case 5: {
			void *addr;
			/* FF /5     JMP m16:16     M     Valid     Valid     Jump far, absolute indirect address given in m16:16.
			 * FF /5     JMP m16:32     M     Valid     Valid     Jump far, absolute indirect address given in m16:32. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (mod.mi_type == MODRM_REGISTER)
				goto err_ilop;
			addr = libvm86_modrm_getaddr(self, &mod, op_flags);
			GUARD_SEGFAULT({
				if (op_flags & F_OP32) {
					self->vr_regs.vr_eip = UNALIGNED_GET32((uint32_t *)((byte_t *)addr + 0));
					self->vr_regs.vr_cs  = UNALIGNED_GET16((uint16_t *)((byte_t *)addr + 4));
				} else {
					self->vr_regs.vr_eip = UNALIGNED_GET16((uint16_t *)((byte_t *)addr + 0));
					self->vr_regs.vr_cs  = UNALIGNED_GET16((uint16_t *)((byte_t *)addr + 2));
				}
			});
		}	break;


		case 6:
			/* FF /6     PUSH r/m16     M     Valid     Valid     Push r/m16.
			 * FF /6     PUSH r/m32     M     N.E.     Valid     Push r/m32. */
			if (op_flags & (F_LOCK))
				goto err_ilop;
			if (op_flags & F_OP32) {
				uint32_t temp;
				error = libvm86_modrm_readl(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_pushl(self, temp, op_flags);
			} else {
				uint16_t temp;
				error = libvm86_modrm_readw(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_pushw(self, temp, op_flags);
			}
			if unlikely(error != VM86_SUCCESS)
				goto err;
			break;

		default:
			goto err_ilop;
		}
		break;


	case 0x88:
		/* 88 /r     MOV r/m8,r8      MR     Valid     Valid     Move r8 to r/m8. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_modrm_writeb(self, &mod, REG8(mod.mi_reg), op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;

	case 0x89:
		/* 89 /r     MOV r/m16,r16    MR     Valid     Valid     Move r16 to r/m16.
		 * 89 /r     MOV r/m32,r32    MR     Valid     Valid     Move r32 to r/m32. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = op_flags & F_OP32
		        ? libvm86_modrm_writel(self, &mod, REG32(mod.mi_reg), op_flags)
		        : libvm86_modrm_writew(self, &mod, REG16(mod.mi_reg), op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;

	case 0x8a:
		/* 8A /r     MOV r8,r/m8      RM     Valid     Valid     Move r/m8 to r8. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_modrm_readb(self, &mod, &REG8(mod.mi_reg), op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;

	case 0x8b:
		/* 8B /r     MOV r16,r/m16    RM     Valid     Valid     Move r/m16 to r16.
		 * 8B /r     MOV r32,r/m32    RM     Valid     Valid     Move r/m32 to r32. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			error = libvm86_modrm_readl(self, &mod, &REG32(mod.mi_reg), op_flags);
			if unlikely(error != VM86_SUCCESS)
			goto err;
		} else {
			error = libvm86_modrm_readw(self, &mod, &REG16(mod.mi_reg), op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			REG32(mod.mi_reg) &= 0xffff;
		}
		break;

	case 0x8c:
		/* 8C /r     MOV r/m16,Sreg** MR     Valid     Valid     Move segment register to r/m16. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if unlikely(mod.mi_reg >= 6)
			goto err_ilop; /* Invalid segment register. */
		error = op_flags & F_OP32
		        ? libvm86_modrm_writel(self, &mod, SEG(mod.mi_reg), op_flags)
		        : libvm86_modrm_writew(self, &mod, SEG(mod.mi_reg), op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;

	case 0x8e:
		/* 8E /r     MOV Sreg,r/m16** RM     Valid     Valid     Move r/m16 to segment register. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if unlikely(mod.mi_reg >= 6)
			goto err_ilop; /* Invalid segment register. */
		error = libvm86_modrm_readw(self, &mod, &SEG(mod.mi_reg), op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;

	case 0xa0: {
		uint8_t *addr, value;
		uint32_t offset;
		/* A0     MOV AL,moffs8*    FD     Valid     Valid     Move byte at (seg:offset) to AL. */
		if (op_flags & F_AD32) {
			error = libvm86_read_pcdword(self, &offset);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			uint16_t temp;
			error = libvm86_read_pcword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			offset = temp;
		}
		addr = (uint8_t *)VM86_ADDR(SEG(op_flags & F_SEGMASK), offset & 0xffff);
		if (self->vr_trans)
			addr = (uint8_t *)self->vr_trans(self, addr);
		GUARD_SEGFAULT({
			value = *addr;
		});
		self->vr_regs.vr_al = value;
	}	break;


	case 0xa1: {
		uint32_t offset;
		void *addr;
		/* A1     MOV AX,moffs16*   FD     Valid     Valid     Move word at (seg:offset) to AX.
		 * A1     MOV EAX,moffs32*  FD     Valid     Valid     Move doubleword at (seg:offset) to EAX. */
		if (op_flags & F_AD32) {
			error = libvm86_read_pcdword(self, &offset);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			uint16_t temp;
			error = libvm86_read_pcword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			offset = temp;
		}
		addr = (void *)VM86_ADDR(SEG(op_flags & F_SEGMASK), offset & 0xffff);
		if (self->vr_trans)
			addr = (uint8_t *)self->vr_trans(self, addr);
		if (op_flags & F_OP32) {
			uint32_t value;
			GUARD_SEGFAULT({
				value = UNALIGNED_GET32((uint32_t *)addr);
			});
			self->vr_regs.vr_eax = value;
		} else {
			uint16_t value;
			GUARD_SEGFAULT({
				value = UNALIGNED_GET16((uint16_t *)addr);
			});
			self->vr_regs.vr_eax = (uint32_t)value;
		}
	}	break;


	case 0xa2: {
		uint8_t *addr;
		uint32_t offset;
		/* A2     MOV moffs8,AL     TD     Valid     Valid     Move AL to (seg:offset). */
		if (op_flags & F_AD32) {
			error = libvm86_read_pcdword(self, &offset);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			uint16_t temp;
			error = libvm86_read_pcword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			offset = temp;
		}
		addr = (uint8_t *)VM86_ADDR(SEG(op_flags & F_SEGMASK), offset & 0xffff);
		if (self->vr_trans)
			addr = (uint8_t *)self->vr_trans(self, addr);
		GUARD_SEGFAULT({
			*addr = self->vr_regs.vr_al;
		});
	}	break;


	case 0xa3: {
		uint32_t offset;
		void *addr;
		/* A3     MOV moffs16*,AX   TD     Valid     Valid     Move AX to (seg:offset).
		 * A3     MOV moffs32*,EAX  TD     Valid     Valid     Move EAX to (seg:offset). */
		if (op_flags & F_AD32) {
			error = libvm86_read_pcdword(self, &offset);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			uint16_t temp;
			error = libvm86_read_pcword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			offset = temp;
		}
		addr = (void *)VM86_ADDR(SEG(op_flags & F_SEGMASK), offset & 0xffff);
		if (self->vr_trans)
			addr = (uint8_t *)self->vr_trans(self, addr);
		GUARD_SEGFAULT({
			if (op_flags & F_OP32)
				UNALIGNED_SET32((uint32_t *)addr, self->vr_regs.vr_eax);
			else {
				UNALIGNED_SET16((uint16_t *)addr, self->vr_regs.vr_ax);
			}
		});
	}	break;


	case 0xb0 ... 0xb7:
		/* B0+ rb ib    MOV r8, imm8      OI     Valid     Valid     Move imm8 to r8. */
		error = libvm86_read_pcbyte(self, &REG8((uint8_t)(opcode - 0xb0)));
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0xb8 ... 0xbf:
		/* B8+ rw iw    MOV r16, imm16    OI     Valid     Valid     Move imm16 to r16.
		 * B8+ rd id    MOV r32, imm32    OI     Valid     Valid     Move imm32 to r32. */
		if (op_flags & F_OP32) {
			error = libvm86_read_pcdword(self, &REG32((uint8_t)(opcode - 0xb8)));
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			error = libvm86_read_pcword(self, &REG16(opcode - 0xb8));
			if unlikely(error != VM86_SUCCESS)
				goto err;
			REG32(opcode - 0xb8) &= 0xffff;
		}
		break;


	case 0xc6:
		/* C6 /0 ib     MOV r/m8, imm8    MI     Valid     Valid     Move imm8 to r/m8. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_modrm_writeb(self, &mod, opcode, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0xc7:
		/* C7 /0 iw     MOV r/m16, imm16  MI     Valid     Valid     Move imm16 to r/m16.
		 * C7 /0 id     MOV r/m32, imm32  MI     Valid     Valid     Move imm32 to r/m32. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_read_pcdword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_writel(self, &mod, temp, op_flags);
		} else {
			uint16_t temp;
			error = libvm86_read_pcword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_writew(self, &mod, temp, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		break;


	case 0x8d: {
		uint32_t value;
		/* 8D /r     LEA r16,m     RM     Valid     Valid     Store effective address for m in register r16.
		 * 8D /r     LEA r32,m     RM     Valid     Valid     Store effective address for m in register r32. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if unlikely(mod.mi_type == MODRM_REGISTER)
			goto err_ilop;
		value = mod.mi_offset;
		if (op_flags & F_AD32) {
			if (mod.mi_rm != 0xff)
				value += REG32(mod.mi_rm);
			if (mod.mi_index != 0xff)
				value += REG32(mod.mi_index) << mod.mi_shift;
		} else {
			if (mod.mi_rm != 0xff)
				value += REG16(mod.mi_rm);
			if (mod.mi_index != 0xff)
				value += REG16(mod.mi_index) << mod.mi_shift;
		}
		if (!(op_flags & F_OP32))
			value &= 0xffff;
		REG32(mod.mi_reg) = value;
	}	break;


	case 0xc9:
		/* C9     LEAVE     ZO     Valid    Valid     Set SP to BP, then pop BP.
		 * C9     LEAVE     ZO     N.E.     Valid     Set ESP to EBP, then pop EBP. */
		self->vr_regs.vr_esp = self->vr_regs.vr_ebp;
		if (op_flags & F_OP32) {
			error = libvm86_popl(self, &self->vr_regs.vr_ebp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			self->vr_regs.vr_esp &= 0xffff;
			error = libvm86_popw(self, &self->vr_regs.vr_bp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_ebp &= 0xffff;
		}
		break;


	case 0xcf:
		/* CF     IRET     ZO     Valid     Valid     Interrupt return (16-bit operand size).
		 * CF     IRETD    ZO     Valid     Valid     Interrupt return (32-bit operand size). */
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_popl(self, &self->vr_regs.vr_eip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popl(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_cs = temp;
			error               = libvm86_popl(self, &self->vr_regs.vr_eflags, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			error = libvm86_popw(self, &self->vr_regs.vr_ip, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_cs, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_popw(self, &self->vr_regs.vr_flags, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_ip &= 0xffff;
			self->vr_regs.vr_flags &= 0xffff;
		}
		break;

		/* 70 cb     JO rel8     D     Valid     Valid     Jump short if overflow (OF=1).
		 * 71 cb     JNO rel8    D     Valid     Valid     Jump short if not overflow (OF=0).
		 * 72 cb     JB rel8     D     Valid     Valid     Jump short if below (CF=1).
		 * 73 cb     JAE rel8    D     Valid     Valid     Jump short if above or equal (CF=0).
		 * 74 cb     JE rel8     D     Valid     Valid     Jump short if equal (ZF=1).
		 * 75 cb     JNE rel8    D     Valid     Valid     Jump short if not equal (ZF=0).
		 * 76 cb     JBE rel8    D     Valid     Valid     Jump short if below or equal (CF=1 or ZF=1).
		 * 77 cb     JA rel8     D     Valid     Valid     Jump short if above (CF=0 and ZF=0).
		 * 78 cb     JS rel8     D     Valid     Valid     Jump short if sign (SF=1).
		 * 7A cb     JP rel8     D     Valid     Valid     Jump short if parity (PF=1).
		 * 7B cb     JNP rel8    D     Valid     Valid     Jump short if not parity (PF=0).
		 * 7C cb     JL rel8     D     Valid     Valid     Jump short if less (SF≠ OF).
		 * 7D cb     JGE rel8    D     Valid     Valid     Jump short if greater or equal (SF=OF).
		 * 7E cb     JLE rel8    D     Valid     Valid     Jump short if less or equal (ZF=1 or SF≠ OF).
		 * 7F cb     JG rel8     D     Valid     Valid     Jump short if greater (ZF=0 and SF=OF). */
#define DEFINE_Jcc(opc, cond)                                          \
	case opc:                                                          \
		error = libvm86_read_pcbyte(self, &opcode);                    \
		if unlikely(error != VM86_SUCCESS)                             \
			goto err;                                                  \
		if (cond)                                                      \
			self->vr_regs.vr_eip += (uint32_t)(int32_t)(int8_t)opcode; \
		break
	DEFINE_Jcc(0x70, self->vr_regs.vr_flags & OF);
	DEFINE_Jcc(0x71, !(self->vr_regs.vr_flags & OF));
	DEFINE_Jcc(0x72, self->vr_regs.vr_flags & CF);
	DEFINE_Jcc(0x73, !(self->vr_regs.vr_flags & CF));
	DEFINE_Jcc(0x74, self->vr_regs.vr_flags & ZF);
	DEFINE_Jcc(0x75, !(self->vr_regs.vr_flags & ZF));
	DEFINE_Jcc(0x76, self->vr_regs.vr_flags & (CF | ZF));
	DEFINE_Jcc(0x77, !(self->vr_regs.vr_flags & (CF | ZF)));
	DEFINE_Jcc(0x78, self->vr_regs.vr_flags & SF);
	DEFINE_Jcc(0x79, !(self->vr_regs.vr_flags & SF));
	DEFINE_Jcc(0x7a, self->vr_regs.vr_flags & PF);
	DEFINE_Jcc(0x7b, !(self->vr_regs.vr_flags & PF));
	DEFINE_Jcc(0x7c, !!(self->vr_regs.vr_flags & SF) != !!(self->vr_regs.vr_flags & OF));
	DEFINE_Jcc(0x7d, !!(self->vr_regs.vr_flags & SF) == !!(self->vr_regs.vr_flags & OF));
	DEFINE_Jcc(0x7e, (self->vr_regs.vr_flags & ZF) || (!!(self->vr_regs.vr_flags & SF) != !!(self->vr_regs.vr_flags & OF)));
	DEFINE_Jcc(0x7f, !(self->vr_regs.vr_flags & ZF) && (!!(self->vr_regs.vr_flags & SF) == !!(self->vr_regs.vr_flags & OF)));
#undef DEFINE_Jcc

	case 0xe3:
		/* E3 cb     JCXZ rel8   D     N.E.      Valid     Jump short if CX register is 0.
		 * E3 cb     JECXZ rel8  D     Valid     Valid     Jump short if ECX register is 0. */
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32 ? (self->vr_regs.vr_ecx != 0) : (self->vr_regs.vr_cx != 0))
			self->vr_regs.vr_eip += (uint32_t)(int32_t)(int8_t)opcode;
		break;

	case 0xe2:
		/* E2 cb     LOOP rel8     D     Valid     Valid     Decrement count; jump short if count ≠ 0. */
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		--self->vr_regs.vr_ecx;
		if (self->vr_regs.vr_ecx != 0)
			self->vr_regs.vr_eip += (uint32_t)(int32_t)(int8_t)opcode;
		break;

	case 0xe1:
		/* E1 cb     LOOPE rel8     D     Valid     Valid     Decrement count; jump short if count ≠ 0 and ZF = 1. */
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		--self->vr_regs.vr_ecx;
		if (self->vr_regs.vr_ecx != 0 && (self->vr_regs.vr_flags & ZF))
			self->vr_regs.vr_eip += (uint32_t)(int32_t)(int8_t)opcode;
		break;

	case 0xe0:
		/* E0 cb     LOOPNE rel8     D     Valid     Valid     Decrement count; jump short if count ≠ 0 and ZF = 0. */
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		--self->vr_regs.vr_ecx;
		if (self->vr_regs.vr_ecx != 0 && !(self->vr_regs.vr_flags & ZF))
			self->vr_regs.vr_eip += (uint32_t)(int32_t)(int8_t)opcode;
		break;

	case 0xc8: {
		uint16_t alloc_size;
		uint8_t nesting_level;
		uint32_t frame_temp;
		/* C8 iw 00     ENTER imm16, 0     II     Valid     Valid     Create a stack frame for a procedure.
		 * C8 iw 01     ENTER imm16, 1     II     Valid     Valid     Create a stack frame with a nested pointer for a procedure.
		 * C8 iw ib     ENTER imm16, imm8  II     Valid     Valid     Create a stack frame with nested pointers for a procedure. */
		error = libvm86_read_pcword(self, &alloc_size);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_read_pcbyte(self, &nesting_level);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			frame_temp = self->vr_regs.vr_esp;
			error      = libvm86_pushl(self, self->vr_regs.vr_ebp, op_flags);
		} else {
			frame_temp = self->vr_regs.vr_sp;
			error      = libvm86_pushw(self, self->vr_regs.vr_bp, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
#if 1
		nesting_level %= 32;
		if (nesting_level >= 1) {
			for (; nesting_level >= 2; --nesting_level) {
				if (op_flags & F_OP32) {
					uint32_t temp, *addr;
					self->vr_regs.vr_ebp -= 4;
					addr = (uint32_t *)VM86_ADDR(self->vr_regs.vr_ss, self->vr_regs.vr_ebp & 0xffff);
					if (self->vr_trans)
						addr = (uint32_t *)(*self->vr_trans)(self, addr);
					GUARD_SEGFAULT({
						temp = UNALIGNED_GET32(addr);
					});
					error = libvm86_pushl(self, temp, op_flags);
				} else {
					uint16_t temp, *addr;
					self->vr_regs.vr_ebp -= 2;
					addr = (uint16_t *)VM86_ADDR(self->vr_regs.vr_ss, self->vr_regs.vr_ebp & 0xffff);
					if (self->vr_trans)
						addr = (uint16_t *)(*self->vr_trans)(self, addr);
					GUARD_SEGFAULT({
						temp = UNALIGNED_GET16(addr);
					});
					error = libvm86_pushw(self, temp, op_flags);
				}
				if unlikely(error != VM86_SUCCESS)
					goto err;
			}
			error = op_flags & F_OP32
			        ? libvm86_pushl(self, (uint32_t)frame_temp, op_flags)
			        : libvm86_pushw(self, (uint16_t)frame_temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		}
#endif
		self->vr_regs.vr_ebp = frame_temp;
		self->vr_regs.vr_esp -= alloc_size;
	}	break;

	case 0xa8:
		/* A8 ib     TEST AL, imm8     I     Valid     Valid     AND imm8 with AL; set SF, ZF, PF according to result. */
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_flags &= ~(SF | ZF | PF);
		self->vr_regs.vr_flags |= f_testb(self->vr_regs.vr_al & opcode);
		break;

	case 0xa9:
		/* A9 iw     TEST AX, imm16     I     Valid     Valid     AND imm16 with AX; set SF, ZF, PF according to result.
		 * A9 id     TEST EAX, imm32    I     Valid     Valid     AND imm32 with EAX; set SF, ZF, PF according to result. */
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_read_pcdword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(SF | ZF | PF);
			self->vr_regs.vr_flags |= f_testl(self->vr_regs.vr_eax & temp);
		} else {
			uint16_t temp;
			error = libvm86_read_pcword(self, &temp);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(SF | ZF | PF);
			self->vr_regs.vr_flags |= f_testw(self->vr_regs.vr_ax & temp);
		}
		break;

	{
		uint8_t value;
	case 0x84:
		/* 84 /r     TEST r/m8, r8     MR     Valid     Valid     AND r8 with r/m8; set SF, ZF, PF according to result. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_modrm_readb(self, &mod, &value, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_flags &= ~(SF | ZF | PF);
		self->vr_regs.vr_flags |= f_testw(value & REG8(mod.mi_reg));
	}	break;

	case 0x85:
		/* 85 /r     TEST r/m16, r16     MR     Valid     Valid     AND r16 with r/m16; set SF, ZF, PF according to result.
		 * 85 /r     TEST r/m32, r32     MR     Valid     Valid     AND r32 with r/m32; set SF, ZF, PF according to result. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			uint32_t value;
			error = libvm86_modrm_readl(self, &mod, &value, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(SF | ZF | PF);
			self->vr_regs.vr_flags |= f_testl(value & REG32(mod.mi_reg));
		} else {
			uint16_t value;
			error = libvm86_modrm_readw(self, &mod, &value, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(SF | ZF | PF);
			self->vr_regs.vr_flags |= f_testw(value & REG16(mod.mi_reg));
		}
		break;

	case 0x90:
		/* 90     NOP     ZO     Valid     Valid     One byte no-operation instruction. */
		break;

	case 0x91 ... 0x97:
		/* 90+rw     XCHG AX, r16     O     Valid     Valid     Exchange r16 with AX.
		 * 90+rw     XCHG r16, AX     O     Valid     Valid     Exchange AX with r16.
		 * 90+rd     XCHG EAX, r32     O     Valid     Valid     Exchange r32 with EAX.
		 * 90+rd     XCHG r32, EAX     O     Valid     Valid     Exchange EAX with r32. */
		if (op_flags & F_OP32) {
			uint32_t temp;
			temp                            = REG32((uint8_t)(opcode - 0x90));
			REG32((uint8_t)(opcode - 0x90)) = self->vr_regs.vr_eax;
			self->vr_regs.vr_eax = temp;
		} else {
			uint16_t temp;
			temp                            = REG16((uint8_t)(opcode - 0x90));
			REG32((uint8_t)(opcode - 0x90)) = (uint32_t)self->vr_regs.vr_ax;
			self->vr_regs.vr_eax = (uint32_t)temp;
		}
		break;

	case 0x86:
		/* 86 /r     XCHG r/m8, r8     MR     Valid     Valid     Exchange r8 (byte register) with byte from r/m8.
		 * 86 /r     XCHG r8, r/m8     RM     Valid     Valid     Exchange byte from r/m8 with r8 (byte register). */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (mod.mi_type == MODRM_REGISTER) {
			uint8_t temp;
			temp             = REG8(mod.mi_rm);
			REG8(mod.mi_rm)  = REG8(mod.mi_reg);
			REG8(mod.mi_reg) = temp;
		} else {
			uint8_t *addr, oldval;
			addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
			GUARD_SEGFAULT({
				oldval = ATOMIC_XCH(*addr, REG8(mod.mi_reg));
			});
			REG8(mod.mi_reg) = oldval;
		}
		break;

	case 0x87:
		/* 87 /r     XCHG r/m16, r16     MR     Valid     Valid     Exchange r16 with word from r/m16.
		 * 87 /r     XCHG r16, r/m16     RM     Valid     Valid     Exchange word from r/m16 with r16.
		 * 87 /r     XCHG r/m32, r32     MR     Valid     Valid     Exchange r32 with doubleword from r/m32.
		 * 87 /r     XCHG r32, r/m32     RM     Valid     Valid     Exchange doubleword from r/m32 with r32. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			 goto err;
		if (mod.mi_type == MODRM_REGISTER) {
			if (op_flags & F_OP32) {
				uint32_t temp;
				temp              = REG32(mod.mi_rm);
				REG32(mod.mi_rm)  = REG32(mod.mi_reg);
				REG32(mod.mi_reg) = temp;
			} else {
				uint16_t temp;
				temp              = REG16(mod.mi_rm);
				REG32(mod.mi_rm)  = (uint32_t)REG16(mod.mi_reg);
				REG32(mod.mi_reg) = (uint32_t)temp;
			}
		} else {
			uint32_t *addr, oldval;
			addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
			GUARD_SEGFAULT({
				oldval = op_flags & F_OP32
				         ? (uint32_t)ATOMIC_XCH(*(uint32_t *)addr, REG32(mod.mi_reg))
				         : (uint32_t)ATOMIC_XCH(*(uint16_t *)addr, REG16(mod.mi_reg));
			});
			REG32(mod.mi_reg) = oldval;
		}
		break;

	case 0x98:
		/* 98     CBW     ZO     Valid     Valid     AX := sign-extend of AL.
		 * 98     CWDE    ZO     Valid     Valid     EAX := sign-extend of AX. */
		if (op_flags & F_OP32) {
			self->vr_regs.vr_eax = (uint32_t)(int32_t)(int16_t)self->vr_regs.vr_ax;
		} else {
			self->vr_regs.vr_eax = (uint32_t)(uint16_t)(int16_t)(int8_t)self->vr_regs.vr_al;
		}
		break;

	case 0x99:
		/* 99     CWD     ZO     Valid     Valid     DX:AX := sign-extend of AX.
		 * 99     CDQ     ZO     Valid     Valid     EDX:EAX := sign-extend of EAX. */
		if (op_flags & F_OP32) {
			self->vr_regs.vr_edx = 0;
			if (self->vr_regs.vr_eax & UINT32_C(0x80000000))
				self->vr_regs.vr_edx = UINT32_C(0xffffffff);
		} else {
			self->vr_regs.vr_edx = 0;
			if (self->vr_regs.vr_ax & 0x8000)
				self->vr_regs.vr_edx = 0xffff;
		}
		break;

	/* C4 /r     LES r16,m16:16     RM     Invalid     Valid     Load ES:r16 with far pointer from memory.
	 * C4 /r     LES r32,m16:32     RM     Invalid     Valid     Load ES:r32 with far pointer from memory. */
	DEFINE_LXS(0xc4, self->vr_regs.vr_es);

	/* C5 /r     LDS r16,m16:16     RM     Invalid     Valid     Load DS:r16 with far pointer from memory.
	 * C5 /r     LDS r32,m16:32     RM     Invalid     Valid     Load DS:r32 with far pointer from memory. */
	DEFINE_LXS(0xc5, self->vr_regs.vr_ds);


	case 0xa4:
		/* A4     MOVS m8, m8     ZO     Valid     Valid     For legacy mode, Move byte from address DS:(E)SI to ES:(E)DI. For 64-bit mode move byte from address (R|E)SI to (R|E)DI. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		error = libvm86_load_string_byte(self, &opcode, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_store_string_byte(self, opcode, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;

	case 0xa5:
		/* A5     MOVS m16, m16     ZO     Valid     Valid     For legacy mode, move word from address DS:(E)SI to ES:(E)DI. For 64-bit mode move word at address (R|E)SI to (R|E)DI.
		 * A5     MOVS m32, m32     ZO     Valid     Valid     For legacy mode, move dword from address DS:(E)SI to ES:(E)DI. For 64-bit mode move dword from address (R|E)SI to (R|E)DI. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_load_string_dword(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_store_string_dword(self, temp, op_flags);
		} else {
			uint16_t temp;
			error = libvm86_load_string_word(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_store_string_word(self, temp, op_flags);
		}
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;

	case 0xaa:
		/* AA     STOS m8     NA     Valid     Valid     For legacy mode, store AL at address ES:(E)DI; For 64-bit mode store AL at address RDI or EDI. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		error = libvm86_store_string_byte(self, self->vr_regs.vr_al, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;

	case 0xab:
		/* AB     STOS m16     NA     Valid     Valid     For legacy mode, store AX at address ES:(E)DI; For 64-bit mode store AX at address RDI or EDI.
		 * AB     STOS m32     NA     Valid     Valid     For legacy mode, store EAX at address ES:(E)DI; For 64-bit mode store EAX at address RDI or EDI. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		error = op_flags & F_OP32
		        ? libvm86_store_string_dword(self, self->vr_regs.vr_eax, op_flags)
		        : libvm86_store_string_word(self, self->vr_regs.vr_ax, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;

	case 0xac:
		/* AC     LODS m8     ZO     Valid     Valid     For legacy mode, Load byte at address DS:(E)SI into AL. For 64-bit mode load byte at address (R)SI into AL. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		error = libvm86_load_string_byte(self, &self->vr_regs.vr_al, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;

	case 0xad:
		/* AD     LODS m16     ZO     Valid     Valid     For legacy mode, Load word at address DS:(E)SI into AX. For 64-bit mode load word at address (R)SI into AX.
		 * AD     LODS m32     ZO     Valid     Valid     For legacy mode, Load dword at address DS:(E)SI into EAX. For 64-bit mode load dword at address (R)SI into EAX. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		if (op_flags & F_OP32) {
			error = libvm86_load_string_dword(self, &self->vr_regs.vr_eax, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
		} else {
			error = libvm86_load_string_word(self, &self->vr_regs.vr_ax, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_eax &= 0xffff;
		}
		if (op_flags & F_REP)
			goto do_rep_instruction;
		break;

	{
		uint8_t a, b;
	case 0xa6:
		/* A6     CMPS m8, m8     ZO     Valid     Valid     For legacy mode, compare byte at address DS:(E)SI with byte at address ES:(E)DI; For 64-bit mode compare byte at address (R|E)SI to byte at address (R|E)DI. The status flags are set accordingly. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		error = libvm86_load_string_byte(self, &a, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_load_string_dst_byte(self, &b, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
		self->vr_regs.vr_flags |= f_cmpb(a, b);
		if ((op_flags & F_REPNE) && (self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
		else if ((op_flags & F_REP) && !(self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
	}	break;

	case 0xa7:
		/* A7     CMPS m16, m16     ZO     Valid     Valid     For legacy mode, compare word at address DS:(E)SI with word at address ES:(E)DI; For 64-bit mode compare word at address (R|E)SI with word at address (R|E)DI. The status flags are set accordingly.
		 * A7     CMPS m32, m32     ZO     Valid     Valid     For legacy mode, compare dword at address DS:(E)SI at dword at address ES:(E)DI; For 64-bit mode compare dword at address (R|E)SI at dword at address (R|E)DI. The status flags are set accordingly. */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		if (op_flags & F_OP32) {
			uint32_t a, b;
			error = libvm86_load_string_dword(self, &a, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_load_string_dst_dword(self, &b, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
			self->vr_regs.vr_flags |= f_cmpl(a, b);
		} else {
			uint16_t a, b;
			error = libvm86_load_string_word(self, &a, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_load_string_dst_word(self, &b, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
			self->vr_regs.vr_flags |= f_cmpw(a, b);
		}
		if ((op_flags & F_REPNE) && (self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
		else if ((op_flags & F_REP) && !(self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
		break;

	case 0xae:
		/* AE     SCAS m8     ZO     Valid     Valid     Compare AL with byte at ES:(E)DI or RDI, then set status flags.* */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		error = libvm86_load_string_dst_byte(self, &opcode, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
		self->vr_regs.vr_flags |= f_cmpb(self->vr_regs.vr_al, opcode);
		if ((op_flags & F_REPNE) && (self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
		else if ((op_flags & F_REP) && !(self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
		break;

	case 0xaf:
		/* AF     SCAS m16     ZO     Valid     Valid     Compare AX with word at ES:(E)DI or RDI, then set status flags.*
		 * AF     SCAS m32     ZO     Valid     Valid     Compare EAX with doubleword at ES(E)DI or RDI then set status flags.* */
		if ((op_flags & F_REP) &&
		    ((op_flags & F_67) ? self->vr_regs.vr_ecx : self->vr_regs.vr_cx) == 0)
			break;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_load_string_dst_dword(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
			self->vr_regs.vr_flags |= f_cmpl(self->vr_regs.vr_eax, temp);
		} else {
			uint16_t temp;
			error = libvm86_load_string_dst_word(self, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
			self->vr_regs.vr_flags |= f_cmpw(self->vr_regs.vr_ax, temp);
		}
		if ((op_flags & F_REPNE) && (self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
		else if ((op_flags & F_REP) && !(self->vr_regs.vr_flags & ZF))
			goto do_rep_instruction;
		break;


	case 0xd7: {
		uint8_t *addr;
		/* D7     XLAT m8   ZO     Valid     Valid     Set AL to memory byte DS:[(E)BX + unsigned AL].
		 * D7     XLATB     ZO     Valid     Valid     Set AL to memory byte DS:[(E)BX + unsigned AL]. */
		if (op_flags & F_AD32) {
			addr = (uint8_t *)(uintptr_t)self->vr_regs.vr_ebx;
		} else {
			addr = (uint8_t *)(uintptr_t)self->vr_regs.vr_bx;
		}
		addr += self->vr_regs.vr_al;
		addr = (uint8_t *)VM86_ADDR(self->vr_regs.vr_ds, (uintptr_t)addr & 0xffff);
		if (self->vr_trans)
			addr = (uint8_t *)(*self->vr_trans)(self, addr);
		GUARD_SEGFAULT({
			self->vr_regs.vr_al = *addr;
		});
	}	break;


	case 0xd6:
		/* salc */
		self->vr_regs.vr_al = 0x00;
		if (self->vr_regs.vr_flags & CF)
			self->vr_regs.vr_al = 0xff;
		break;


#define DO_REGROXT(T, w, f_func, reg, shift)               \
	{                                                      \
		reg = f_func(reg, shift, &self->vr_regs.vr_flags); \
	}
#define DO_MEMROXT(T, w, f_func, addr, shift)                                              \
	{                                                                                      \
		GUARD_SEGFAULT({                                                                   \
			if (op_flags & F_LOCK) {                                                       \
				T oldval;                                                                  \
				uint16_t new_flags;                                                        \
				do {                                                                       \
					new_flags = self->vr_regs.vr_flags;                                    \
					oldval    = ATOMIC_READ(*addr);                                        \
				} while (!ATOMIC_CMPXCH(*addr, oldval, f_func(*addr, shift, &new_flags))); \
				self->vr_regs.vr_flags = new_flags;                                        \
			} else {                                                                       \
				T newval;                                                                  \
				newval = f_func(UNALIGNED_GET(addr), shift, &self->vr_regs.vr_flags);      \
				UNALIGNED_SET(addr, newval);                                               \
			}                                                                              \
		});                                                                                \
	}


#define DEFINE_ROTATE_SHIFT_OPCODES(id, DO_REGB, DO_REGW, DO_REGL, DO_MEMB, DO_MEMW, DO_MEML) \
do_c0h_reg##id:                                                                               \
	if (mod.mi_type == MODRM_REGISTER) {                                                      \
		DO_REGB(REG8(mod.mi_rm), opcode);                                                     \
	} else {                                                                                  \
		uint8_t *addr;                                                                        \
		addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);                        \
		DO_MEMB(addr, opcode);                                                                \
	}                                                                                         \
	break;                                                                                    \
do_c1h_reg##id:                                                                               \
	if (mod.mi_type == MODRM_REGISTER) {                                                      \
		if (op_flags & F_OP32) {                                                              \
			DO_REGL(REG32(mod.mi_rm), opcode);                                                \
		} else {                                                                              \
			DO_REGW(REG16(mod.mi_rm), opcode);                                                \
			REG32(mod.mi_rm) &= 0xffff;                                                       \
		}                                                                                     \
	} else {                                                                                  \
		void *addr;                                                                           \
		addr = libvm86_modrm_getaddr(self, &mod, op_flags);                                   \
		if (op_flags & F_OP32) {                                                              \
			DO_MEML(((uint32_t *)addr), opcode);                                              \
		} else {                                                                              \
			DO_MEMW(((uint16_t *)addr), opcode);                                              \
		}                                                                                     \
	}                                                                                         \
	break


	/* C0 /0 ib  ROL r/m8, imm8   MI     Valid     Valid     Rotate 8 bits r/m8 left imm8 times.
	 * C1 /0 ib  ROL r/m16, imm8  MI     Valid     Valid     Rotate 16 bits r/m16 left imm8 times.
	 * C1 /0 ib  ROL r/m32, imm8  MI     Valid     Valid     Rotate 32 bits r/m32 left imm8 times.
	 * D0 /0     ROL r/m8, 1      M1     Valid     Valid     Rotate 8 bits r/m8 left once.
	 * D1 /0     ROL r/m16, 1     M1     Valid     Valid     Rotate 16 bits r/m16 left once.
	 * D1 /0     ROL r/m32, 1     M1     Valid     Valid     Rotate 32 bits r/m32 left once.
	 * D2 /0     ROL r/m8, CL     MC     Valid     Valid     Rotate 8 bits r/m8 left CL times.
	 * D3 /0     ROL r/m16, CL    MC     Valid     Valid     Rotate 16 bits r/m16 left CL times.
	 * D3 /0     ROL r/m32, CL    MC     Valid     Valid     Rotate 32 bits r/m32 left CL times. */
#define DO_REGROLB(reg, shift)  DO_REGROXT(uint8_t, b, f_rolb, reg, shift)
#define DO_REGROLW(reg, shift)  DO_REGROXT(uint16_t, w, f_rolw, reg, shift)
#define DO_REGROLL(reg, shift)  DO_REGROXT(uint32_t, l, f_roll, reg, shift)
#define DO_MEMROLB(addr, shift) DO_MEMROXT(uint8_t, b, f_rolb, addr, shift)
#define DO_MEMROLW(addr, shift) DO_MEMROXT(uint16_t, w, f_rolw, addr, shift)
#define DO_MEMROLL(addr, shift) DO_MEMROXT(uint32_t, l, f_roll, addr, shift)
	DEFINE_ROTATE_SHIFT_OPCODES(0, DO_REGROLB, DO_REGROLW, DO_REGROLL, DO_MEMROLB, DO_MEMROLW, DO_MEMROLL);

	/* C0 /1 ib  ROR r/m8, imm8   MI     Valid     Valid     Rotate 8 bits r/m16 right imm8 times.
	 * C1 /1 ib  ROR r/m16, imm8  MI     Valid     Valid     Rotate 16 bits r/m16 right imm8 times.
	 * C1 /1 ib  ROR r/m32, imm8  MI     Valid     Valid     Rotate 32 bits r/m32 right imm8 times.
	 * D0 /1     ROR r/m8, 1      M1     Valid     Valid     Rotate 8 bits r/m8 right once.
	 * D1 /1     ROR r/m16, 1     M1     Valid     Valid     Rotate 16 bits r/m16 right once.
	 * D1 /1     ROR r/m32, 1     M1     Valid     Valid     Rotate 32 bits r/m32 right once.
	 * D2 /1     ROR r/m8, CL     MC     Valid     Valid     Rotate 8 bits r/m8 right CL times.
	 * D3 /1     ROR r/m16, CL    MC     Valid     Valid     Rotate 16 bits r/m16 right CL times.
	 * D3 /1     ROR r/m32, CL    MC     Valid     Valid     Rotate 32 bits r/m32 right CL times. */
#define DO_REGRORB(reg, shift)  DO_REGROXT(uint8_t, b, f_rorb, reg, shift)
#define DO_REGRORW(reg, shift)  DO_REGROXT(uint16_t, w, f_rorw, reg, shift)
#define DO_REGRORL(reg, shift)  DO_REGROXT(uint32_t, l, f_rorl, reg, shift)
#define DO_MEMRORB(addr, shift) DO_MEMROXT(uint8_t, b, f_rorb, addr, shift)
#define DO_MEMRORW(addr, shift) DO_MEMROXT(uint16_t, w, f_rorw, addr, shift)
#define DO_MEMRORL(addr, shift) DO_MEMROXT(uint32_t, l, f_rorl, addr, shift)
	DEFINE_ROTATE_SHIFT_OPCODES(1, DO_REGRORB, DO_REGRORW, DO_REGRORL, DO_MEMRORB, DO_MEMRORW, DO_MEMRORL);

	/* C0 /2 ib  RCL r/m8, imm8   MI     Valid     Valid     Rotate 9 bits (CF, r/m8) left imm8 times.
	 * C1 /2 ib  RCL r/m16, imm8  MI     Valid     Valid     Rotate 17 bits (CF, r/m16) left imm8 times.
	 * C1 /2 ib  RCL r/m32, imm8  MI     Valid     Valid     Rotate 33 bits (CF, r/m32) left imm8 times.
	 * D0 /2     RCL r/m8, 1      M1     Valid     Valid     Rotate 9 bits (CF, r/m8) left once.
	 * D1 /2     RCL r/m16, 1     M1     Valid     Valid     Rotate 17 bits (CF, r/m16) left once.
	 * D1 /2     RCL r/m32, 1     M1     Valid     Valid     Rotate 33 bits (CF, r/m32) left once.
	 * D2 /2     RCL r/m8, CL     MC     Valid     Valid     Rotate 9 bits (CF, r/m8) left CL times.
	 * D3 /2     RCL r/m16, CL    MC     Valid     Valid     Rotate 17 bits (CF, r/m16) left CL times.
	 * D3 /2     RCL r/m32, CL    MC     Valid     Valid     Rotate 33 bits (CF, r/m32) left CL times. */
#define DO_REGRCLB(reg, shift)  DO_REGROXT(uint8_t, b, f_rclb, reg, shift)
#define DO_REGRCLW(reg, shift)  DO_REGROXT(uint16_t, w, f_rclw, reg, shift)
#define DO_REGRCLL(reg, shift)  DO_REGROXT(uint32_t, l, f_rcll, reg, shift)
#define DO_MEMRCLB(addr, shift) DO_MEMROXT(uint8_t, b, f_rclb, addr, shift)
#define DO_MEMRCLW(addr, shift) DO_MEMROXT(uint16_t, w, f_rclw, addr, shift)
#define DO_MEMRCLL(addr, shift) DO_MEMROXT(uint32_t, l, f_rcll, addr, shift)
	DEFINE_ROTATE_SHIFT_OPCODES(2, DO_REGRCLB, DO_REGRCLW, DO_REGRCLL, DO_MEMRCLB, DO_MEMRCLW, DO_MEMRCLL);

	/* C0 /3 ib  RCR r/m8, imm8   MI     Valid     Valid     Rotate 9 bits (CF, r/m8) right imm8 times.
	 * C1 /3 ib  RCR r/m16, imm8  MI     Valid     Valid     Rotate 17 bits (CF, r/m16) right imm8 times.
	 * C1 /3 ib  RCR r/m32, imm8  MI     Valid     Valid     Rotate 33 bits (CF, r/m32) right imm8 times.
	 * D0 /3     RCR r/m8, 1      M1     Valid     Valid     Rotate 9 bits (CF, r/m8) right once.
	 * D1 /3     RCR r/m16, 1     M1     Valid     Valid     Rotate 17 bits (CF, r/m16) right once.
	 * D1 /3     RCR r/m32, 1     M1     Valid     Valid     Rotate 33 bits (CF, r/m32) right once. Uses a 6 bit count.
	 * D2 /3     RCR r/m8, CL     MC     Valid     Valid     Rotate 9 bits (CF, r/m8) right CL times.
	 * D3 /3     RCR r/m16, CL    MC     Valid     Valid     Rotate 17 bits (CF, r/m16) right CL times.
	 * D3 /3     RCR r/m32, CL    MC     Valid     Valid     Rotate 33 bits (CF, r/m32) right CL times. */
#define DO_REGRCRB(reg, shift)  DO_REGROXT(uint8_t, b, f_rcrb, reg, shift)
#define DO_REGRCRW(reg, shift)  DO_REGROXT(uint16_t, w, f_rcrw, reg, shift)
#define DO_REGRCRL(reg, shift)  DO_REGROXT(uint32_t, l, f_rcrl, reg, shift)
#define DO_MEMRCRB(addr, shift) DO_MEMROXT(uint8_t, b, f_rcrb, addr, shift)
#define DO_MEMRCRW(addr, shift) DO_MEMROXT(uint16_t, w, f_rcrw, addr, shift)
#define DO_MEMRCRL(addr, shift) DO_MEMROXT(uint32_t, l, f_rcrl, addr, shift)
	DEFINE_ROTATE_SHIFT_OPCODES(3, DO_REGRCRB, DO_REGRCRW, DO_REGRCRL, DO_MEMRCRB, DO_MEMRCRW, DO_MEMRCRL);

	/* C0 /4 ib  SAL r/m8, imm8   MI     Valid     Valid     Multiply r/m8 by 2, imm8 times.
	 * C0 /4 ib  SHL r/m8, imm8   MI     Valid     Valid     Multiply r/m8 by 2, imm8 times.
	 * C1 /4 ib  SAL r/m16, imm8  MI     Valid     Valid     Multiply r/m16 by 2, imm8 times.
	 * C1 /4 ib  SAL r/m32, imm8  MI     Valid     Valid     Multiply r/m32 by 2, imm8 times.
	 * C1 /4 ib  SHL r/m16, imm8  MI     Valid     Valid     Multiply r/m16 by 2, imm8 times.
	 * C1 /4 ib  SHL r/m32, imm8  MI     Valid     Valid     Multiply r/m32 by 2, imm8 times.
	 * D0 /4     SAL r/m8, 1      M1     Valid     Valid     Multiply r/m8 by 2, once.
	 * D0 /4     SHL r/m8, 1      M1     Valid     Valid     Multiply r/m8 by 2, once.
	 * D1 /4     SAL r/m16, 1     M1     Valid     Valid     Multiply r/m16 by 2, once.
	 * D1 /4     SAL r/m32, 1     M1     Valid     Valid     Multiply r/m32 by 2, once.
	 * D1 /4     SHL r/m16,1      M1     Valid     Valid     Multiply r/m16 by 2, once.
	 * D1 /4     SHL r/m32,1      M1     Valid     Valid     Multiply r/m32 by 2, once.
	 * D2 /4     SAL r/m8, CL     MC     Valid     Valid     Multiply r/m8 by 2, CL times.
	 * D2 /4     SHL r/m8, CL     MC     Valid     Valid     Multiply r/m8 by 2, CL times.
	 * D3 /4     SAL r/m16, CL    MC     Valid     Valid     Multiply r/m16 by 2, CL times.
	 * D3 /4     SAL r/m32, CL    MC     Valid     Valid     Multiply r/m32 by 2, CL times.
	 * D3 /4     SHL r/m16, CL    MC     Valid     Valid     Multiply r/m16 by 2, CL times.
	 * D3 /4     SHL r/m32, CL    MC     Valid     Valid     Multiply r/m32 by 2, CL times. */
#define DO_REGSHLB(reg, shift)  DO_REGROXT(uint8_t, b, f_shlb, reg, shift)
#define DO_REGSHLW(reg, shift)  DO_REGROXT(uint16_t, w, f_shlw, reg, shift)
#define DO_REGSHLL(reg, shift)  DO_REGROXT(uint32_t, l, f_shll, reg, shift)
#define DO_MEMSHLB(addr, shift) DO_MEMROXT(uint8_t, b, f_shlb, addr, shift)
#define DO_MEMSHLW(addr, shift) DO_MEMROXT(uint16_t, w, f_shlw, addr, shift)
#define DO_MEMSHLL(addr, shift) DO_MEMROXT(uint32_t, l, f_shll, addr, shift)
	DEFINE_ROTATE_SHIFT_OPCODES(4, DO_REGSHLB, DO_REGSHLW, DO_REGSHLL, DO_MEMSHLB, DO_MEMSHLW, DO_MEMSHLL);

	/* C0 /5 ib  SHR r/m8, imm8   MI     Valid     Valid     Unsigned divide r/m8 by 2, imm8 times.
	 * C1 /5 ib  SHR r/m16, imm8  MI     Valid     Valid     Unsigned divide r/m16 by 2, imm8 times.
	 * C1 /5 ib  SHR r/m32, imm8  MI     Valid     Valid     Unsigned divide r/m32 by 2, imm8 times.
	 * D0 /5     SHR r/m8,1       M1     Valid     Valid     Unsigned divide r/m8 by 2, once.
	 * D1 /5     SHR r/m16, 1     M1     Valid     Valid     Unsigned divide r/m16 by 2, once.
	 * D1 /5     SHR r/m32, 1     M1     Valid     Valid     Unsigned divide r/m32 by 2, once.
	 * D2 /5     SHR r/m8, CL     MC     Valid     Valid     Unsigned divide r/m8 by 2, CL times.
	 * D3 /5     SHR r/m16, CL    MC     Valid     Valid     Unsigned divide r/m16 by 2, CL times
	 * D3 /5     SHR r/m32, CL    MC     Valid     Valid     Unsigned divide r/m32 by 2, CL times. */
#define DO_REGSHRB(reg, shift)  DO_REGROXT(uint8_t, b, f_shrb, reg, shift)
#define DO_REGSHRW(reg, shift)  DO_REGROXT(uint16_t, w, f_shrw, reg, shift)
#define DO_REGSHRL(reg, shift)  DO_REGROXT(uint32_t, l, f_shrl, reg, shift)
#define DO_MEMSHRB(addr, shift) DO_MEMROXT(uint8_t, b, f_shrb, addr, shift)
#define DO_MEMSHRW(addr, shift) DO_MEMROXT(uint16_t, w, f_shrw, addr, shift)
#define DO_MEMSHRL(addr, shift) DO_MEMROXT(uint32_t, l, f_shrl, addr, shift)
	DEFINE_ROTATE_SHIFT_OPCODES(5, DO_REGSHRB, DO_REGSHRW, DO_REGSHRL, DO_MEMSHRB, DO_MEMSHRW, DO_MEMSHRL);

	/* C0 /7 ib  SAR r/m8, imm8   MI     Valid     Valid     Signed divide* r/m8 by 2, imm8 time.
	 * C1 /7 ib  SAR r/m16, imm8  MI     Valid     Valid     Signed divide* r/m16 by 2, imm8 times.
	 * C1 /7 ib  SAR r/m32, imm8  MI     Valid     Valid     Signed divide* r/m32 by 2, imm8 times.
	 * D0 /7     SAR r/m8, 1      M1     Valid     Valid     Signed divide* r/m8 by 2, once.
	 * D1 /7     SAR r/m16,1      M1     Valid     Valid     Signed divide* r/m16 by 2, once.
	 * D1 /7     SAR r/m32, 1     M1     Valid     Valid     Signed divide* r/m32 by 2, once.
	 * D2 /7     SAR r/m8, CL     MC     Valid     Valid     Signed divide* r/m8 by 2, CL times.
	 * D3 /7     SAR r/m16, CL    MC     Valid     Valid     Signed divide* r/m16 by 2, CL times.
	 * D3 /7     SAR r/m32, CL    MC     Valid     Valid     Signed divide* r/m32 by 2, CL times. */
#define DO_REGSARB(reg, shift)  DO_REGROXT(uint8_t, b, f_sarb, reg, shift)
#define DO_REGSARW(reg, shift)  DO_REGROXT(uint16_t, w, f_sarw, reg, shift)
#define DO_REGSARL(reg, shift)  DO_REGROXT(uint32_t, l, f_sarl, reg, shift)
#define DO_MEMSARB(addr, shift) DO_MEMROXT(uint8_t, b, f_sarb, addr, shift)
#define DO_MEMSARW(addr, shift) DO_MEMROXT(uint16_t, w, f_sarw, addr, shift)
#define DO_MEMSARL(addr, shift) DO_MEMROXT(uint32_t, l, f_sarl, addr, shift)
	DEFINE_ROTATE_SHIFT_OPCODES(7, DO_REGSARB, DO_REGSARW, DO_REGSARL, DO_MEMSARB, DO_MEMSARW, DO_MEMSARL);

#undef DEFINE_ROTATE_SHIFT_OPCODES
	case 0xc0:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
do_c0h_switch_reg:
		switch (mod.mi_reg) {
		case 0: goto do_c0h_reg0;
		case 1: goto do_c0h_reg1;
		case 2: goto do_c0h_reg2;
		case 3: goto do_c0h_reg3;
		case 4: goto do_c0h_reg4;
		case 5: goto do_c0h_reg5;
		case 7: goto do_c0h_reg7;
		default: goto err_ilop;
		}
		break;

	case 0xc1:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
do_c1h_switch_reg:
		switch (mod.mi_reg) {
		case 0: goto do_c1h_reg0;
		case 1: goto do_c1h_reg1;
		case 2: goto do_c1h_reg2;
		case 3: goto do_c1h_reg3;
		case 4: goto do_c1h_reg4;
		case 5: goto do_c1h_reg5;
		case 7: goto do_c1h_reg7;
		default: goto err_ilop;
		}
		break;

	case 0xd0:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		opcode = 1;
		goto do_c0h_switch_reg;

	case 0xd1:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		opcode = 1;
		goto do_c1h_switch_reg;

	case 0xd2:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		opcode = self->vr_regs.vr_cl;
		goto do_c0h_switch_reg;

	case 0xd3:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		opcode = self->vr_regs.vr_cl;
		goto do_c1h_switch_reg;


	case 0x6b:
		/* 6B /r ib     IMUL r16, r/m16, imm8     RMI     Valid     Valid     word register := r/m16 * sign-extended immediate byte.
		 * 6B /r ib     IMUL r32, r/m32, imm8     RMI     Valid     Valid     doubleword register := r/m32 * sign-extended immediate byte. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		error = libvm86_read_pcbyte(self, &opcode);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			uint32_t temp;
			error = libvm86_modrm_readl(self, &mod, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(OF | CF);
			if (OVERFLOW_SMUL((int32_t)temp, (int32_t)(int8_t)opcode, (int32_t *)&REG32(mod.mi_reg))) {
				*(int32_t *)&REG32(mod.mi_reg) = ((int32_t)temp *
				                                  (int32_t)(int8_t)opcode);
				self->vr_regs.vr_flags |= (OF | CF);
			}
		} else {
			uint16_t temp;
			error = libvm86_modrm_readw(self, &mod, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(OF | CF);
			if (OVERFLOW_SMUL((int16_t)temp, (int16_t)(int8_t)opcode, (int16_t *)&REG16(mod.mi_reg))) {
				*(int16_t *)&REG16(mod.mi_reg) = ((int16_t)temp *
				                                  (int16_t)(int8_t)opcode);
				self->vr_regs.vr_flags |= (OF | CF);
			}
			REG32(mod.mi_reg) &= 0xffff;
		}
		break;

	case 0x69:
		/* 69 /r iw     IMUL r16, r/m16, imm16     RMI     Valid     Valid     word register := r/m16 * immediate word.
		 * 69 /r id     IMUL r32, r/m32, imm32     RMI     Valid     Valid     doubleword register := r/m32 * immediate doubleword. */
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		if (op_flags & F_OP32) {
			uint32_t temp, operand;
			error = libvm86_read_pcdword(self, &operand);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_readl(self, &mod, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(OF | CF);
			if (OVERFLOW_SMUL((int32_t)temp, (int32_t)operand, (int32_t *)&REG32(mod.mi_reg))) {
				*(int32_t *)&REG32(mod.mi_reg) = ((int32_t)temp *
				                                  (int32_t)operand);
				self->vr_regs.vr_flags |= (OF | CF);
			}
		} else {
			uint16_t temp, operand;
			error = libvm86_read_pcword(self, &operand);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_modrm_readw(self, &mod, &temp, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(OF | CF);
			if (OVERFLOW_SMUL((int16_t)temp, (int16_t)operand, (int16_t *)&REG16(mod.mi_reg))) {
				*(int16_t *)&REG16(mod.mi_reg) = ((int16_t)temp *
				                                  (int16_t)operand);
				self->vr_regs.vr_flags |= (OF | CF);
			}
			REG32(mod.mi_reg) &= 0xffff;
		}
		break;



	case 0xf6: {
		uint8_t value;
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		switch (mod.mi_reg) {

		case 0:
		case 1: /* Undocumented alias */
			/* F6 /0 ib     TEST r/m8, imm8     MI     Valid     Valid     AND imm8 with r/m8; set SF, ZF, PF according to result. */
			error = libvm86_modrm_readb(self, &mod, &value, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			error = libvm86_read_pcbyte(self, &opcode);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(SF | ZF | PF);
			self->vr_regs.vr_flags |= f_testb(value & opcode);
			break;

		case 2:
			/* F6 /2     NOT r/m8     M     Valid     Valid     Reverse each bit of r/m8. */
			if (mod.mi_type == MODRM_REGISTER) {
				REG8(mod.mi_rm) ^= 0xff;
			} else {
				uint8_t *addr;
				addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						ATOMIC_FETCHXOR(*addr, 0xff);
					} else {
						*addr ^= 0xff;
					}
				});
			}
			break;

		case 3: {
			uint8_t oldval;
			/* F6 /3     NEG r/m8     M     Valid     Valid     Two's complement negate r/m8. */
			if (mod.mi_type == MODRM_REGISTER) {
				oldval          = REG8(mod.mi_rm);
				REG8(mod.mi_rm) = (uint8_t) - (int8_t)oldval;
			} else {
				uint8_t *addr;
				addr = (uint8_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_LOCK) {
						do
							oldval = ATOMIC_READ(*addr);
						while (!ATOMIC_CMPXCH(*addr, oldval, (uint8_t) - (int8_t)oldval));
					} else {
						oldval = *addr;
						*addr  = (uint8_t) - (int8_t)oldval;
					}
				});
			}
			self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
			self->vr_regs.vr_flags |= f_addb(oldval, (uint8_t)-1);
			if (!oldval)
				self->vr_regs.vr_flags |= CF;
		}	break;

		case 4:
			/* F6 /4     MUL r/m8     M     Valid     Valid     Unsigned multiply (AX := AL * r/m8). */
			error = libvm86_modrm_readb(self, &mod, &opcode, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(CF | OF);
			if (OVERFLOW_UMUL((uint8_t)self->vr_regs.vr_al,
			                  (uint8_t)opcode,
			                  (uint16_t *)&self->vr_regs.vr_ax)) {
				*(uint16_t *)&self->vr_regs.vr_ax = ((uint16_t)(uint8_t)self->vr_regs.vr_al *
				                                     (uint16_t)(uint8_t)opcode);
				self->vr_regs.vr_flags |= (CF | OF);
			}
			break;

		case 5:
			/* F6 /5     IMUL r/m8*     M     Valid     Valid     AX := AL * r/m byte. */
			error = libvm86_modrm_readb(self, &mod, &opcode, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
			self->vr_regs.vr_flags &= ~(CF | OF);
			if (OVERFLOW_SMUL((int8_t)self->vr_regs.vr_al,
			                  (int8_t)opcode,
			                  (int16_t *)&self->vr_regs.vr_ax)) {
				*(int16_t *)&self->vr_regs.vr_ax = ((int16_t)(int8_t)self->vr_regs.vr_al *
				                                    (int16_t)(int8_t)opcode);
				self->vr_regs.vr_flags |= (CF | OF);
			}
			break;

		case 6:
			/* F6 /6     DIV r/m8     M     Valid     Valid     Unsigned divide AX by r/m8, with result stored in AL := Quotient, AH := Remainder. */
			error = libvm86_modrm_readb(self, &mod, &opcode, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
#ifndef E_DIVIDE_BY_ZERO
			if unlikely(!opcode)
				return libvm86_intr(self, 0x0); /* Divide by zero */
#else /* !E_DIVIDE_BY_ZERO */
			TRY
#endif /* E_DIVIDE_BY_ZERO */
			{
				uint16_t ax         = self->vr_regs.vr_ax;
				self->vr_regs.vr_al = (uint8_t)(ax / opcode);
				self->vr_regs.vr_ah = (uint8_t)(ax % opcode);
			}
#ifdef E_DIVIDE_BY_ZERO
			EXCEPT {
				if (!was_thrown(E_DIVIDE_BY_ZERO))
					RETHROW();
				return libvm86_intr(self, 0x0); /* Divide by zero */
			}
#endif /* E_DIVIDE_BY_ZERO */
			break;

		case 7:
			/* F6 /7     IDIV r/m8     M     Valid     Valid     Signed divide AX by r/m8, with result stored in: AL := Quotient, AH := Remainder. */
			error = libvm86_modrm_readb(self, &mod, &opcode, op_flags);
			if unlikely(error != VM86_SUCCESS)
				goto err;
#ifndef E_DIVIDE_BY_ZERO
			if unlikely(!opcode)
				return libvm86_intr(self, 0x0); /* Divide by zero */
#else /* !E_DIVIDE_BY_ZERO */
			TRY
#endif /* E_DIVIDE_BY_ZERO */
			{
				uint16_t ax         = self->vr_regs.vr_ax;
				self->vr_regs.vr_al = (uint8_t)(int8_t)((int16_t)ax / (int8_t)opcode);
				self->vr_regs.vr_ah = (uint8_t)(int8_t)((int16_t)ax % (int8_t)opcode);
			}
#ifdef E_DIVIDE_BY_ZERO
			EXCEPT {
				if (!was_thrown(E_DIVIDE_BY_ZERO))
					RETHROW();
				return libvm86_intr(self, 0x0); /* Divide by zero */
			}
#endif /* E_DIVIDE_BY_ZERO */
			break;

		default:
			goto err_ilop;
		}
	}	break;


	case 0xf7:
		error = libvm86_modrm_decode(self, &mod, op_flags);
		if unlikely(error != VM86_SUCCESS)
			goto err;
		switch (mod.mi_reg) {

		case 0:
		case 1: /* Undocumented alias */
			/* F7 /0 iw     TEST r/m16, imm16     MI     Valid     Valid     AND imm16 with r/m16; set SF, ZF, PF according to result.
			 * F7 /0 id     TEST r/m32, imm32     MI     Valid     Valid     AND imm32 with r/m32; set SF, ZF, PF according to result. */
			if (op_flags & F_OP32) {
				uint32_t value, operand;
				error = libvm86_modrm_readl(self, &mod, &value, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_read_pcdword(self, &operand);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(SF | ZF | PF);
				self->vr_regs.vr_flags |= f_testl(value & operand);
			} else {
				uint16_t value, operand;
				error = libvm86_modrm_readw(self, &mod, &value, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				error = libvm86_read_pcword(self, &operand);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(SF | ZF | PF);
				self->vr_regs.vr_flags |= f_testw(value & operand);
			}
			break;

		case 2:
			/* F7 /2     NOT r/m16    M     Valid     Valid     Reverse each bit of r/m16.
			 * F7 /2     NOT r/m32    M     Valid     Valid     Reverse each bit of r/m32. */
			if (mod.mi_type == MODRM_REGISTER) {
				REG32(mod.mi_rm) ^= UINT32_C(0xffffffff);
				if (!(op_flags & F_OP32))
					REG32(mod.mi_rm) &= 0xffff;
			} else {
				void *addr;
				addr = libvm86_modrm_getaddr(self, &mod, op_flags);
				GUARD_SEGFAULT({
					if (op_flags & F_OP32) {
						if (op_flags & F_LOCK) {
							ATOMIC_FETCHXOR(*(uint32_t *)addr, UINT32_C(0xffffffff));
						} else {
							*(uint32_t *)addr ^= UINT32_C(0xffffffff);
						}
					} else {
						if (op_flags & F_LOCK) {
							ATOMIC_FETCHXOR(*(uint16_t *)addr, 0xffff);
						} else {
							*(uint16_t *)addr ^= 0xffff;
						}
					}
				});
			}
			break;

		case 3:
			/* F7 /3     NEG r/m16     M     Valid     Valid     Two's complement negate r/m16.
			 * F7 /3     NEG r/m32     M     Valid     Valid     Two's complement negate r/m32. */
			if (op_flags & F_OP32) {
				uint32_t oldval;
				if (mod.mi_type == MODRM_REGISTER) {
					oldval           = REG32(mod.mi_rm);
					REG32(mod.mi_rm) = (uint32_t) - (int32_t)oldval;
				} else {
					uint32_t *addr;
					addr = (uint32_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							do
								oldval = ATOMIC_READ(*addr);
							while (!ATOMIC_CMPXCH(*addr, oldval, (uint32_t) - (int32_t)oldval));
						} else {
							oldval = *addr;
							*addr  = (uint32_t) - (int32_t)oldval;
						}
					});
				}
				self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
				self->vr_regs.vr_flags |= f_addl(oldval, (uint32_t)-1);
				if (!oldval)
					self->vr_regs.vr_flags |= CF;
			} else {
				uint16_t oldval;
				if (mod.mi_type == MODRM_REGISTER) {
					oldval           = REG16(mod.mi_rm);
					REG32(mod.mi_rm) = (uint32_t)(uint16_t) - (int16_t)oldval;
				} else {
					uint16_t *addr;
					addr = (uint16_t *)libvm86_modrm_getaddr(self, &mod, op_flags);
					GUARD_SEGFAULT({
						if (op_flags & F_LOCK) {
							do
								oldval = ATOMIC_READ(*addr);
							while (!ATOMIC_CMPXCH(*addr, oldval, (uint16_t) - (int16_t)oldval));
						} else {
							oldval = *addr;
							*addr  = (uint16_t) - (int16_t)oldval;
						}
					});
				}
				self->vr_regs.vr_flags &= ~(CF | OF | SF | ZF | AF | PF);
				self->vr_regs.vr_flags |= f_addw(oldval, (uint16_t)-1);
				if (!oldval)
					self->vr_regs.vr_flags |= CF;
			}
			break;

		case 4:
			/* F7 /4     MUL r/m16     M     Valid     Valid     Unsigned multiply (DX:AX := AX * r/m16).
			 * F7 /4     MUL r/m32     M     Valid     Valid     Unsigned multiply (EDX:EAX := EAX * r/m32). */
			if (op_flags & F_OP32) {
				uint32_t temp;
				uint64_t res;
				error = libvm86_modrm_readl(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(CF | OF);
				if (OVERFLOW_UMUL((uint32_t)self->vr_regs.vr_eax, (uint32_t)temp, &res)) {
					res = ((uint64_t)(uint32_t)self->vr_regs.vr_eax *
					       (uint64_t)(uint32_t)temp);
					self->vr_regs.vr_flags |= (CF | OF);
				}
				self->vr_regs.vr_eax = (uint32_t)(uint64_t)res;
				self->vr_regs.vr_edx = (uint32_t)((uint64_t)res >> 32);
			} else {
				uint16_t temp;
				uint32_t res;
				error = libvm86_modrm_readw(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(CF | OF);
				if (OVERFLOW_UMUL((uint16_t)self->vr_regs.vr_ax, (uint16_t)temp, &res)) {
					res = ((uint32_t)(uint16_t)self->vr_regs.vr_ax *
					       (uint32_t)(uint16_t)temp);
					self->vr_regs.vr_flags |= (CF | OF);
				}
				self->vr_regs.vr_eax = ((uint32_t)res) & 0xffff;
				self->vr_regs.vr_edx = ((uint32_t)res >> 16) & 0xffff;
			}
			break;

		case 5:
			/* F7 /5     IMUL r/m16     M     Valid     Valid     DX:AX := AX * r/m word.
			 * F7 /5     IMUL r/m32     M     Valid     Valid     EDX:EAX := EAX * r/m32. */
			if (op_flags & F_OP32) {
				uint32_t temp;
				int64_t res;
				error = libvm86_modrm_readl(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(CF | OF);
				if (OVERFLOW_SMUL((int32_t)self->vr_regs.vr_eax, (int32_t)temp, &res)) {
					res = ((int64_t)(int32_t)self->vr_regs.vr_eax *
					       (int64_t)(int32_t)temp);
					self->vr_regs.vr_flags |= (CF | OF);
				}
				self->vr_regs.vr_eax = (uint32_t)(uint64_t)res;
				self->vr_regs.vr_edx = (uint32_t)((uint64_t)res >> 32);
			} else {
				uint16_t temp;
				int32_t res;
				error = libvm86_modrm_readw(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
				self->vr_regs.vr_flags &= ~(CF | OF);
				if (OVERFLOW_SMUL((int16_t)self->vr_regs.vr_ax, (int16_t)temp, &res)) {
					res = ((int32_t)(int16_t)self->vr_regs.vr_ax *
					       (int32_t)(int16_t)temp);
					self->vr_regs.vr_flags |= (CF | OF);
				}
				self->vr_regs.vr_eax = ((uint32_t)res) & 0xffff;
				self->vr_regs.vr_edx = ((uint32_t)res >> 16) & 0xffff;
			}
			break;

		case 6:
			/* F7 /6     DIV r/m16     M     Valid     Valid     Unsigned divide DX:AX by r/m16, with result stored in AX := Quotient, DX := Remainder.
			 * F7 /6     DIV r/m32     M     Valid     Valid     Unsigned divide EDX:EAX by r/m32, with result stored in EAX := Quotient, EDX := Remainder. */
			if (op_flags & F_OP32) {
				uint32_t temp;
				error = libvm86_modrm_readl(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
#ifndef E_DIVIDE_BY_ZERO
				if unlikely(!opcode) {
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#else /* !E_DIVIDE_BY_ZERO */
				TRY
#endif /* E_DIVIDE_BY_ZERO */
				{
					uint64_t edxeax = ((uint64_t)self->vr_regs.vr_edx << 32 |
					                   (uint64_t)self->vr_regs.vr_eax);
					self->vr_regs.vr_eax = (uint32_t)(edxeax / temp);
					self->vr_regs.vr_edx = (uint32_t)(edxeax % temp);
				}
#ifdef E_DIVIDE_BY_ZERO
				EXCEPT {
					if (!was_thrown(E_DIVIDE_BY_ZERO))
						RETHROW();
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#endif /* E_DIVIDE_BY_ZERO */
			} else {
				uint16_t temp;
				error = libvm86_modrm_readw(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
#ifndef E_DIVIDE_BY_ZERO
				if unlikely(!opcode) {
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#else /* !E_DIVIDE_BY_ZERO */
				TRY
#endif /* E_DIVIDE_BY_ZERO */
				{
					uint32_t dxax = ((uint32_t)self->vr_regs.vr_dx << 16 |
					                 (uint32_t)self->vr_regs.vr_ax);
					self->vr_regs.vr_eax = (uint16_t)(dxax / temp);
					self->vr_regs.vr_edx = (uint16_t)(dxax % temp);
				}
#ifdef E_DIVIDE_BY_ZERO
				EXCEPT {
					if (!was_thrown(E_DIVIDE_BY_ZERO))
						RETHROW();
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#endif /* E_DIVIDE_BY_ZERO */
			}
			break;

		case 7:
			/* F7 /7     IDIV r/m16     M     Valid     Valid     Signed divide DX:AX by r/m16, with result stored in AX := Quotient, DX := Remainder.
			 * F7 /7     IDIV r/m32     M     Valid     Valid     Signed divide EDX:EAX by r/m32, with result stored in EAX := Quotient, EDX := Remainder. */
			if (op_flags & F_OP32) {
				uint32_t temp;
				error = libvm86_modrm_readl(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
#ifndef E_DIVIDE_BY_ZERO
				if unlikely(!opcode) {
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#else /* !E_DIVIDE_BY_ZERO */
				TRY
#endif /* E_DIVIDE_BY_ZERO */
				{
					uint64_t edxeax = ((uint64_t)self->vr_regs.vr_edx << 32 |
					                   (uint64_t)self->vr_regs.vr_eax);
					self->vr_regs.vr_eax = (uint32_t)(int32_t)((int64_t)edxeax / (int32_t)temp);
					self->vr_regs.vr_edx = (uint32_t)(int32_t)((int64_t)edxeax % (int32_t)temp);
				}
#ifdef E_DIVIDE_BY_ZERO
				EXCEPT {
					if (!was_thrown(E_DIVIDE_BY_ZERO))
						RETHROW();
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#endif /* E_DIVIDE_BY_ZERO */
			} else {
				uint16_t temp;
				error = libvm86_modrm_readw(self, &mod, &temp, op_flags);
				if unlikely(error != VM86_SUCCESS)
					goto err;
#ifndef E_DIVIDE_BY_ZERO
				if unlikely(!opcode) {
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#else /* !E_DIVIDE_BY_ZERO */
				TRY
#endif /* E_DIVIDE_BY_ZERO */
				{
					uint32_t dxax = ((uint32_t)self->vr_regs.vr_dx << 16 |
					                 (uint32_t)self->vr_regs.vr_ax);
					self->vr_regs.vr_eax = (uint16_t)(int16_t)((int32_t)dxax / (int16_t)temp);
					self->vr_regs.vr_edx = (uint16_t)(int16_t)((int32_t)dxax % (int16_t)temp);
				}
#ifdef E_DIVIDE_BY_ZERO
				EXCEPT {
					if (!was_thrown(E_DIVIDE_BY_ZERO))
						RETHROW();
					return libvm86_intr(self, 0x0); /* Divide by zero */
				}
#endif /* E_DIVIDE_BY_ZERO */
			}
			break;

		default:
			goto err_ilop;
		}
		break;
#endif

	default:
err_ilop:
		self->vr_regs.vr_eip = ip_start;
		return libvm86_intr(self, 0x6); /* Invalid Opcode */
	}
	return VM86_SUCCESS;
err:
	self->vr_regs.vr_eip = ip_start;
	return error;
err_segfault:
	self->vr_regs.vr_eip = ip_start;
	return VM86_SEGFAULT;
#undef DEFINE_LXS
}


DEFINE_PUBLIC_ALIAS(vm86_step, libvm86_step);

DECL_END

#endif /* !GUARD_LIBVM86_EMUINSTR_C */
