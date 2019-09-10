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
#ifndef GUARD_LIBVM86_EMULATOR_C
#define GUARD_LIBVM86_EMULATOR_C 1

#include "emulator.h"

#include <hybrid/compiler.h>

#include <hybrid/bit.h>

#include <kos/except.h>

#include <libvm86/api.h>
#include <libvm86/emulator.h>

#include <assert.h>
#include <stddef.h>

#include "api.h"
#include "x86.h"

#ifdef __KERNEL__
#include <kernel/except.h>
#endif /* __KERNEL__ */

DECL_BEGIN

LOCAL NONNULL((1)) int CC
libvm86_check_interrupts(vm86_state_t *__restrict self) {
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(self->vr_intr_pending); ++i) {
		unsigned int shift;
		uint8_t intno;
		if (!self->vr_intr_pending[i])
			continue;
		shift = FFS(self->vr_intr_pending[i]) - 1;
		self->vr_intr_pending[i] &= ~((uintptr_t)1 << shift);
		intno = (uint8_t)((i * (sizeof(uintptr_t) * 8)) + shift);
		/* Load the interrupt vector. */
		return libvm86_sw_intr(self, intno);
	}
	/* No more interrupts. */
	self->vr_stateflags &= ~VM86_STATE_FINTR;
	return VM86_SUCCESS;
}

/* Same as `vm86_step()', but also check for pending interrupts beforehand. */
INTERN NONNULL((1)) int CC
libvm86_fullstep(vm86_state_t *__restrict self) {
	if ((self->vr_regs.vr_flags & IF) &&
	    (self->vr_stateflags & VM86_STATE_FINTR)) {
		int error;
		error = libvm86_check_interrupts(self);
		if unlikely(error != VM86_SUCCESS)
			return error;
	}
	return libvm86_step(self);
}

/* Execute VM86 emulator code until that code finishes execution. */
INTERN NONNULL((1)) int CC
libvm86_exec(vm86_state_t *__restrict self) {
	int result;
	for (;;) {
		result = libvm86_fullstep(self);
check_result:
		if (result == VM86_SUCCESS)
			continue;
		if (result == VM86_INTR_ENABLED) {
			result = libvm86_step(self);
			goto check_result;
		}
		break;
	}
	return result;
}

/* Trigger an interrupt.
 * vm86_sw_intr:
 *   - Always trigger the interrupt
 * vm86_hw_intr:
 *   - Check if #IF is set
 *    - Yes: Trigger the interrupt by invoking `vm86_sw_intr(intno)'
 *    - No:  Mark the interrupt as pending
 * vm86_pic_intr:
 *   - `pic_intno' must be `>= 0 && <= 15', where 0..7 maps to PIC#1 and 8..15 to PIC#2
 *   #1: Determine which PIC is addressed.
 *   #2: If the interrupt is being ignored, returning immediately.
 *   #3: If the interrupt is already pending, returning immediately.
 *   #4: If `VM86_PIC_FNEEDEOI' is set, mark the interrupt and pending and returning immediately.
 *   #5: Set the `VM86_PIC_FNEEDEOI' flag (unless `VM86_PIC_FAUTOEOI' is also set)
 *   #6: Invoke `vm86_hw_intr()' with the pic_intno adjusted
 *       relative to the base of the associated PIC:
 *       >> intno = pic_intno >= 8 ? (vr_pic2_base + (pic_intno - 8)) : (vr_pic1_base + pic_intno);
 * @return: VM86_SUCCESS:      Success.
 * @return: VM86_DOUBLE_FAULT: Stack overflow.
 * @return: VM86_SEGFAULT:     Segmentation fault. */
INTERN NONNULL((1)) int CC
libvm86_sw_intr(vm86_state_t *__restrict self, uint8_t intno) {
	if (self->vr_intr) {
		(*self->vr_intr)(self, intno);
	} else {
		/* Make `base' volatile, so the compiler can't be bothered by it possibly being
		 * NULL (which is actually what we want it to be in this very special case!) */
		uint16_t *sp;
		uint16_t *volatile base = (uint16_t *)0;
		uint16_t cs, ip;
		if (self->vr_trans)
			base = (uint16_t *)(*self->vr_trans)(self, NULL);
		TRY {
			ip = base[(intno * 2) + 0];
			cs = base[(intno * 2) + 1];
		} EXCEPT {
			if (!WAS_SEGFAULT_THROWN())
				RETHROW();
			return VM86_SEGFAULT;
		}
		if (!vm86_state_hasstack(self, 6))
			return VM86_DOUBLE_FAULT;
		sp     = (uint16_t *)vm86_state_sp(self);
		sp[-1] = self->vr_regs.vr_flags;
		sp[-2] = self->vr_regs.vr_cs;
		sp[-3] = self->vr_regs.vr_ip;
		self->vr_regs.vr_flags &= ~(IF | TF);
		self->vr_regs.vr_cs = cs;
		self->vr_regs.vr_ip = ip;
		self->vr_regs.vr_sp -= 6;
	}
	return VM86_SUCCESS;
}

INTERN NONNULL((1)) int CC
libvm86_hw_intr(vm86_state_t *__restrict self, uint8_t intno) {
	if (!(self->vr_regs.vr_flags & IF)) {
		self->vr_intr_pending[intno / (sizeof(uintptr_t) * 8)] |=
		    (uintptr_t)1 << (intno % (sizeof(uintptr_t) * 8));
		return VM86_SUCCESS;
	}
	return libvm86_sw_intr(self, intno);
}

INTERN NONNULL((1)) int CC
libvm86_pic_intr(vm86_state_t *__restrict self, uint8_t pic_intno) {
	uint8_t mask;
	assert(pic_intno <= 15);
	if (pic_intno >= 8) {
		pic_intno -= 8;
		mask = (uint8_t)1 << pic_intno;
		if (self->vr_pic2_ignr & mask)
			return VM86_SUCCESS; /* Ignored */
		if (self->vr_pic2_mask & mask)
			return VM86_SUCCESS; /* Already pending */
		if (self->vr_pic2_mode & VM86_PIC_FNEEDEOI) {
			/* Mark as pending */
			self->vr_pic2_mask |= mask;
			return VM86_SUCCESS;
		}
		if (!(self->vr_pic2_mode & VM86_PIC_FAUTOEOI))
			self->vr_pic2_mode |= VM86_PIC_FNEEDEOI;
		pic_intno += self->vr_pic2_base;
	} else {
		mask = (uint8_t)1 << pic_intno;
		if (self->vr_pic1_ignr & mask)
			return VM86_SUCCESS; /* Ignored */
		if (self->vr_pic1_mask & mask)
			return VM86_SUCCESS; /* Already pending */
		if (self->vr_pic1_mode & VM86_PIC_FNEEDEOI) {
			/* Mark as pending */
			self->vr_pic1_mask |= mask;
			return VM86_SUCCESS;
		}
		if (!(self->vr_pic1_mode & VM86_PIC_FAUTOEOI))
			self->vr_pic1_mode |= VM86_PIC_FNEEDEOI;
		pic_intno += self->vr_pic1_base;
	}
	return libvm86_hw_intr(self, pic_intno);
}


LOCAL NONNULL((1)) int CC
libvm86_pic1_check_interrupts(vm86_state_t *__restrict self) {
	if (self->vr_pic1_mask) {
		unsigned int shift;
		shift = FFS(self->vr_pic1_mask) - 1;
		self->vr_pic1_mask &= ~((uint8_t)1 << shift);
		if (!(self->vr_pic1_mode & VM86_PIC_FAUTOEOI))
			self->vr_pic1_mode |= VM86_PIC_FNEEDEOI;
		return libvm86_hw_intr(self, self->vr_pic1_base + shift);
	}
	return VM86_SUCCESS;
}

LOCAL NONNULL((1)) int CC
libvm86_pic2_check_interrupts(vm86_state_t *__restrict self) {
	if (self->vr_pic2_mask) {
		unsigned int shift;
		shift = FFS(self->vr_pic2_mask) - 1;
		self->vr_pic2_mask &= ~((uint8_t)1 << shift);
		if (!(self->vr_pic2_mode & VM86_PIC_FAUTOEOI))
			self->vr_pic2_mode |= VM86_PIC_FNEEDEOI;
		return libvm86_hw_intr(self, self->vr_pic2_base + shift);
	}
	return VM86_SUCCESS;
}


PRIVATE NONNULL((1, 4)) int CC
libvm86_portio(vm86_state_t *__restrict self,
               uint16_t port,
               unsigned int action,
               void *__restrict data) {
	int result = VM86_BADPORT;
	switch (port) {

	case X86_PIC1_CMD:
	case X86_PIC2_CMD: {
		uint8_t value, *pmode;
		if unlikely(!VM86_HANDLE_IO_ISOUT(action))
			break;
		value  = *(uint8_t *)data;
		result = VM86_SUCCESS;
		pmode  = &self->vr_pic1_mode;
		if (port == X86_PIC2_CMD)
			pmode = &self->vr_pic2_mode;
		if (value & X86_PIC_CMD_EOI) {
			int error;
			/* Acknowledge interrupt. */
			*pmode &= ~VM86_PIC_FNEEDEOI;
			/* -> Check for pending interrupts. */
			error = port == X86_PIC1_CMD
			            ? libvm86_pic1_check_interrupts(self)
			            : libvm86_pic2_check_interrupts(self);
			if unlikely(error != VM86_SUCCESS)
				return error;
		}
		if (value & X86_ICW1_INIT) {
			/* Switch to initialization-mode */
			*pmode &= ~(VM86_PIC_STATEMASK | VM86_PIC_FAUTOEOI);
			*pmode |= (value & X86_ICW1_ICW4)
			              ? VM86_PIC_STATE_WORD2
			              : VM86_PIC_STATE_WORD2_N4;
		}
	}	break;

	case X86_PIC1_DATA:
		if (VM86_HANDLE_IO_ISIN(action)) {
			/* Return disabled interrupts. */
			*(uint8_t *)data = self->vr_pic1_ignr;
		} else {
			switch (self->vr_pic1_mode & VM86_PIC_STATEMASK) {
			case VM86_PIC_STATE_RUNNING:
				/* Disable interrupts. */
				self->vr_pic1_ignr = *(uint8_t *)data;
				self->vr_pic1_mask &= ~self->vr_pic1_ignr; /* Clear ignored, pending interrupts. */
				break;

			case VM86_PIC_STATE_WORD2:
			case VM86_PIC_STATE_WORD2_N4:
				/* Word #2: Define the IRQ offsets. */
				self->vr_pic1_base = *(uint8_t *)data;
				self->vr_pic1_mode += 1 << VM86_PIC_STATESHIFT;
				break;
			case VM86_PIC_STATE_WORD3:
			case VM86_PIC_STATE_WORD3_N4:
				/* Word #3: Tell the master and slave how they are wired to each other. */
				if ((self->vr_pic1_mode & VM86_PIC_STATEMASK) == VM86_PIC_STATE_WORD3) {
					self->vr_pic1_mode += 1 << VM86_PIC_STATESHIFT;
				} else {
					self->vr_pic1_mode &= ~VM86_PIC_STATEMASK;
				}
				break;
			case VM86_PIC_STATE_WORD4:
				/* Word #4: Define the environment mode. */
				self->vr_pic1_mode &= ~VM86_PIC_STATEMASK;
				if (*(uint8_t *)data & X86_ICW4_AUTO)
					self->vr_pic1_mode |= VM86_PIC_FAUTOEOI;
				break;

			default: break;
			}
		}
		result = VM86_SUCCESS;
		break;

	case X86_PIC2_DATA:
		if (VM86_HANDLE_IO_ISIN(action)) {
			/* Return disabled interrupts. */
			*(uint8_t *)data = self->vr_pic2_ignr;
		} else {
			switch (self->vr_pic2_mode & VM86_PIC_STATEMASK) {
			case VM86_PIC_STATE_RUNNING:
				/* Disable interrupts. */
				self->vr_pic2_ignr = *(uint8_t *)data;
				self->vr_pic2_mask &= ~self->vr_pic2_ignr; /* Clear ignored, pending interrupts. */
				break;

			case VM86_PIC_STATE_WORD2:
			case VM86_PIC_STATE_WORD2_N4:
				/* Word #2: Define the IRQ offsets. */
				self->vr_pic2_base = *(uint8_t *)data;
				self->vr_pic2_mode += 1 << VM86_PIC_STATESHIFT;
				break;
			case VM86_PIC_STATE_WORD3:
			case VM86_PIC_STATE_WORD3_N4:
				/* Word #3: Tell the master and slave how they are wired to each other. */
				if ((self->vr_pic2_mode & VM86_PIC_STATEMASK) == VM86_PIC_STATE_WORD3) {
					self->vr_pic2_mode += 1 << VM86_PIC_STATESHIFT;
				} else {
					self->vr_pic2_mode &= ~VM86_PIC_STATEMASK;
				}
				break;
			case VM86_PIC_STATE_WORD4:
				/* Word #4: Define the environment mode. */
				self->vr_pic2_mode &= ~VM86_PIC_STATEMASK;
				if (*(uint8_t *)data & X86_ICW4_AUTO)
					self->vr_pic2_mode |= VM86_PIC_FAUTOEOI;
				break;

			default: break;
			}
		}
		result = VM86_SUCCESS;
		break;

	default:
		break;
	}
		if likely(self->vr_io)
			result = (*self->vr_io)(self, port, action, data);
	return result;
}


/* Read/Write values to/from an emulated VIO port.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
INTERN NONNULL((1, 3)) int CC
libvm86_inb(vm86_state_t *__restrict self,
            uint16_t port, uint8_t *__restrict presult) {
	*presult = 0;
	return libvm86_portio(self, port, VM86_HANDLE_IO_INB, presult);
}

INTERN NONNULL((1, 3)) int CC
libvm86_inw(vm86_state_t *__restrict self,
            uint16_t port, uint16_t *__restrict presult) {
	*presult = 0;
	return libvm86_portio(self, port, VM86_HANDLE_IO_INW, presult);
}

INTERN NONNULL((1, 3)) int CC
libvm86_inl(vm86_state_t *__restrict self,
            uint16_t port, uint32_t *__restrict presult) {
	*presult = 0;
	return libvm86_portio(self, port, VM86_HANDLE_IO_INL, presult);
}

INTERN NONNULL((1)) int CC
libvm86_outb(vm86_state_t *__restrict self,
             uint16_t port, uint8_t value) {
	return libvm86_portio(self, port, VM86_HANDLE_IO_OUTB, &value);
}

INTERN NONNULL((1)) int CC
libvm86_outw(vm86_state_t *__restrict self,
             uint16_t port, uint16_t value) {
	return libvm86_portio(self, port, VM86_HANDLE_IO_OUTW, &value);
}

INTERN NONNULL((1)) int CC
libvm86_outl(vm86_state_t *__restrict self,
             uint16_t port, uint32_t value) {
	return libvm86_portio(self, port, VM86_HANDLE_IO_OUTL, &value);
}





DEFINE_PUBLIC_ALIAS(vm86_fullstep, libvm86_fullstep);
DEFINE_PUBLIC_ALIAS(vm86_exec, libvm86_exec);
DEFINE_PUBLIC_ALIAS(vm86_sw_intr, libvm86_sw_intr);
DEFINE_PUBLIC_ALIAS(vm86_hw_intr, libvm86_hw_intr);
DEFINE_PUBLIC_ALIAS(vm86_pic_intr, libvm86_pic_intr);
DEFINE_PUBLIC_ALIAS(vm86_inb, libvm86_inb);
DEFINE_PUBLIC_ALIAS(vm86_inw, libvm86_inw);
DEFINE_PUBLIC_ALIAS(vm86_inl, libvm86_inl);
DEFINE_PUBLIC_ALIAS(vm86_outb, libvm86_outb);
DEFINE_PUBLIC_ALIAS(vm86_outw, libvm86_outw);
DEFINE_PUBLIC_ALIAS(vm86_outl, libvm86_outl);

DECL_END

#endif /* !GUARD_LIBVM86_EMULATOR_C */
