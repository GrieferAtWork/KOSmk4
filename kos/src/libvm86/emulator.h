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
#ifndef GUARD_LIBVM86_EMULATOR_H
#define GUARD_LIBVM86_EMULATOR_H 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvm86/api.h>
#include <libvm86/emulator.h>

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

/* Execute VM86 emulator code until that code finishes execution. */
INTDEF NONNULL((1)) int CC libvm86_exec(vm86_state_t *__restrict self);

/* Trigger an interrupt.
 * @return: VM86_SUCCESS:      Success.
 * @return: VM86_DOUBLE_FAULT: Stack overflow.
 * @return: VM86_SEGFAULT:     Segmentation fault. */
INTDEF NONNULL((1)) int CC libvm86_intr(vm86_state_t *__restrict self, uint8_t intno);

/* Read/Write values to/from an emulated IO port.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
INTDEF NONNULL((1, 3)) int CC libvm86_inb(vm86_state_t *__restrict self, uint16_t port, uint8_t *__restrict presult);
INTDEF NONNULL((1, 3)) int CC libvm86_inw(vm86_state_t *__restrict self, uint16_t port, uint16_t *__restrict presult);
INTDEF NONNULL((1, 3)) int CC libvm86_inl(vm86_state_t *__restrict self, uint16_t port, uint32_t *__restrict presult);
INTDEF NONNULL((1)) int CC libvm86_outb(vm86_state_t *__restrict self, uint16_t port, uint8_t value);
INTDEF NONNULL((1)) int CC libvm86_outw(vm86_state_t *__restrict self, uint16_t port, uint16_t value);
INTDEF NONNULL((1)) int CC libvm86_outl(vm86_state_t *__restrict self, uint16_t port, uint32_t value);


DECL_END

#endif /* !GUARD_LIBVM86_EMULATOR_H */
