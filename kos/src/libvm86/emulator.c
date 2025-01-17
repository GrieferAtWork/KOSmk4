/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBVM86_EMULATOR_C
#define GUARD_LIBVM86_EMULATOR_C 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/bit.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>

#include <libvm86/api.h>
#include <libvm86/emulator.h>

#include "emulator.h"

DECL_BEGIN

/* Execute VM86 emulator code until that code finishes execution. */
INTERN NONNULL((1)) int CC
libvm86_exec(vm86_state_t *__restrict self) {
	int result;
	for (;;) {
		result = libvm86_step(self);
		if (result != VM86_SUCCESS &&
		    result != VM86_INTR_ENABLED)
			break;
	}
	return result;
}

/* Trigger an interrupt.
 * @return: VM86_SUCCESS:      Success.
 * @return: VM86_DOUBLE_FAULT: Stack overflow.
 * @return: VM86_SEGFAULT:     Segmentation fault. */
INTERN NONNULL((1)) int CC
libvm86_intr(vm86_state_t *__restrict self, uint8_t intno) {
	if (self->vr_intr) {
		(*self->vr_intr)(self, intno);
	} else {
		/* Make `base' volatile, so the compiler can't be bothered by it possibly being
		 * NULL  (which is actually what we want it to be in this very special case, as
		 * the realmode IDT is located at address 0!) */
		uint16_t *volatile base = (uint16_t *)0;
		uint16_t *sp, cs, ip;
		if (self->vr_trans)
			base = (uint16_t *)(*self->vr_trans)(self, 0);
		NESTED_TRY {
			ip = base[(intno * 2) + 0];
			cs = base[(intno * 2) + 1];
		} EXCEPT {
			if (!was_thrown(E_SEGFAULT))
				RETHROW();
			return VM86_SEGFAULT;
		}
		if (!vm86_state_canpush(self, 6))
			return VM86_DOUBLE_FAULT;
		sp = (uint16_t *)(uintptr_t)vm86_state_sp(self);
		if (self->vr_trans)
			sp = (uint16_t *)(*self->vr_trans)(self, sp);
		sp[-1] = self->vr_regs.vr_flags;
		sp[-2] = self->vr_regs.vr_cs;
		sp[-3] = self->vr_regs.vr_ip;
		self->vr_regs.vr_flags &= ~(VM86_EFLAGS_IF | VM86_EFLAGS_TF);
		self->vr_regs.vr_cs = cs;
		self->vr_regs.vr_ip = ip;
		self->vr_regs.vr_sp -= 6;
	}
	return VM86_SUCCESS;
}


/* Read/Write values to/from an emulated IO port.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
INTERN NONNULL((1, 3)) int CC
libvm86_inb(vm86_state_t *__restrict self,
            uint16_t port, uint8_t *__restrict presult) {
	if unlikely(!self->vr_io)
		return VM86_BADPORT;
	return (*self->vr_io)(self, port, VM86_HANDLE_IO_INB, presult);
}

INTERN NONNULL((1, 3)) int CC
libvm86_inw(vm86_state_t *__restrict self,
            uint16_t port, uint16_t *__restrict presult) {
	if unlikely(!self->vr_io)
		return VM86_BADPORT;
	return (*self->vr_io)(self, port, VM86_HANDLE_IO_INW, presult);
}

INTERN NONNULL((1, 3)) int CC
libvm86_inl(vm86_state_t *__restrict self,
            uint16_t port, uint32_t *__restrict presult) {
	if unlikely(!self->vr_io)
		return VM86_BADPORT;
	return (*self->vr_io)(self, port, VM86_HANDLE_IO_INL, presult);
}

INTERN NONNULL((1)) int CC
libvm86_outb(vm86_state_t *__restrict self,
             uint16_t port, uint8_t value) {
	if unlikely(!self->vr_io)
		return VM86_BADPORT;
	return (*self->vr_io)(self, port, VM86_HANDLE_IO_OUTB, &value);
}

INTERN NONNULL((1)) int CC
libvm86_outw(vm86_state_t *__restrict self,
             uint16_t port, uint16_t value) {
	if unlikely(!self->vr_io)
		return VM86_BADPORT;
	return (*self->vr_io)(self, port, VM86_HANDLE_IO_OUTW, &value);
}

INTERN NONNULL((1)) int CC
libvm86_outl(vm86_state_t *__restrict self,
             uint16_t port, uint32_t value) {
	if unlikely(!self->vr_io)
		return VM86_BADPORT;
	return (*self->vr_io)(self, port, VM86_HANDLE_IO_OUTL, &value);
}


DEFINE_PUBLIC_ALIAS(vm86_exec, libvm86_exec);
DEFINE_PUBLIC_ALIAS(vm86_intr, libvm86_intr);
DEFINE_PUBLIC_ALIAS(vm86_inb, libvm86_inb);
DEFINE_PUBLIC_ALIAS(vm86_inw, libvm86_inw);
DEFINE_PUBLIC_ALIAS(vm86_inl, libvm86_inl);
DEFINE_PUBLIC_ALIAS(vm86_outb, libvm86_outb);
DEFINE_PUBLIC_ALIAS(vm86_outw, libvm86_outw);
DEFINE_PUBLIC_ALIAS(vm86_outl, libvm86_outl);

DECL_END

#endif /* !GUARD_LIBVM86_EMULATOR_C */
