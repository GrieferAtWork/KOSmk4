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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_DRIVERS_SERIAL_C
#define GUARD_KERNEL_CORE_DRIVERS_SERIAL_C 1

#include <kernel/compiler.h>

#include <kernel/serial.h>
#include <kernel/types.h>

#include <kos/io/serial.h>
#include <sys/io.h>

DECL_BEGIN

/* Probe for a serial port with the given base address. */
PUBLIC bool KCALL serial_probe(port_t base) {
	/* Quick test: Check if the scratch register works. */
	{
		u8 temp = inb(SERIAL_IOADDR_SCR(base));
		outb(SERIAL_IOADDR_SCR(base), temp + 1);
		if (inb(SERIAL_IOADDR_SCR(base)) == temp + 1)
			return true;
	}
	/* Go the long route... */
	outb(SERIAL_IOADDR_IER(base), 0);               /* Disable interrupts */
	outb(SERIAL_IOADDR_LCR(base), SERIAL_LCR_DLAB); /* Enable DLAB */
	outb(SERIAL_IOADDR_DLL(base), SERIAL_DL_38400 & 0xff);
	outb(SERIAL_IOADDR_DLM(base), SERIAL_DL_38400 >> 8);
	outb(SERIAL_IOADDR_LCR(base), SERIAL_LCR_DWL_8 | SERIAL_LCR_STB_1 | SERIAL_LCR_PRT_NO);
	outb(SERIAL_IOADDR_FCR(base), SERIAL_FCR_ENABLED | SERIAL_FCR_CRFIFO |
	                              SERIAL_FCR_CTFIFO | SERIAL_FCR_RITL_14);
	outb(SERIAL_IOADDR_MCR(base), SERIAL_MCR_LPM);
	{
		static u8 const test_data[4] = { 't', 'e', 's', 't' };
		unsigned int i;
		for (i = 0; i < COMPILER_LENOF(test_data); ++i) {
			u8 recv, send = test_data[i];
			outb(SERIAL_IOADDR_THR(base), send);
			recv = inb(SERIAL_IOADDR_THR(base));
			if (recv != send)
				return false;
		}
	}
	return true;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_DRIVERS_SERIAL_C */
