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
#ifndef GUARD_LIBVM86_EMULATOR_H
#define GUARD_LIBVM86_EMULATOR_H 1

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libvm86/api.h>
#include <libvm86/emulator.h>

#include "api.h"

DECL_BEGIN

/* Emulate a single instruction and update the program counter to point
 * to the next instruction.
 *  - In the case of string instructions, execute a single loop and place
 *    the program counter back at the start after updating loop counters.
 *  - This function does not check for pending interrupts prior to execution
 *    of any single instruction.
 *  - When `VM86_FROZEN' is returned, the program counter is also reset to
 *    the start of the responsible instruction.
 * @return: VM86_SUCCESS: The single instruction was successfully executed.
 * @return: VM86_STOPPED: The program counter was already placed at 0xffff:0xffff, or has jumped to that location.
 * @return: * :           One of `VM86_*' */
INTDEF int CC libvm86_step(vm86_state_t *__restrict self);

/* Same as `vm86_step()', but also check for pending interrupts beforehand. */
INTDEF int CC libvm86_fullstep(vm86_state_t *__restrict self);

/* Execute VM86 emulator code until that code finishes execution. */
INTDEF int CC libvm86_exec(vm86_state_t *__restrict self);

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
INTDEF int CC libvm86_sw_intr(vm86_state_t *__restrict self, uint8_t intno);
INTDEF int CC libvm86_hw_intr(vm86_state_t *__restrict self, uint8_t intno);
INTDEF int CC libvm86_pic_intr(vm86_state_t *__restrict self, uint8_t pic_intno);

/* Read/Write values to/from an emulated VIO port.
 * @return: VM86_SUCCESS: Success.
 * @return: VM86_BADPORT: Bad port. */
INTDEF int CC libvm86_inb(vm86_state_t *__restrict self, uint16_t port, uint8_t *__restrict presult);
INTDEF int CC libvm86_inw(vm86_state_t *__restrict self, uint16_t port, uint16_t *__restrict presult);
INTDEF int CC libvm86_inl(vm86_state_t *__restrict self, uint16_t port, uint32_t *__restrict presult);
INTDEF int CC libvm86_outb(vm86_state_t *__restrict self, uint16_t port, uint8_t value);
INTDEF int CC libvm86_outw(vm86_state_t *__restrict self, uint16_t port, uint16_t value);
INTDEF int CC libvm86_outl(vm86_state_t *__restrict self, uint16_t port, uint32_t value);


DECL_END

#endif /* !GUARD_LIBVM86_EMULATOR_H */
