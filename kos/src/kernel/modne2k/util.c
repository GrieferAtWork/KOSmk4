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
#ifndef GUARD_MODNE2K_UTIL_C
#define GUARD_MODNE2K_UTIL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/isr.h>
#include <kernel/printk.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hw/net/ne2k.h>
#include <kos/except/reason/io.h>
#include <sys/io.h>

#include <stddef.h>
#include <string.h>

#include "ne2k.h"

DECL_BEGIN

INTERN void KCALL Ne2k_ResetCard(port_t iobase) THROWS(E_IOERROR_TIMEOUT) {
	struct timespec timeout;
	u8 reset_word;
	/* Select page #0 */
	outb(E8390_CMD(iobase), E8390_STOP | E8390_PAGE0 | E8390_NODMA);

	/* Set the card */
	reset_word = inb(NE_RESET(iobase));
	outb(NE_RESET(iobase), reset_word);

	/* Wait for the reset to be completed. */
	timeout = realtime();
	timeout.add_milliseconds(400);
	while (!(inb(EN0_ISR(iobase)) & ENISR_RESET)) {
		if (realtime() > timeout) {
			printk(KERN_WARNING "[ne2k] Card at %#I16x failed to acknowledge reset\n",
			       iobase);
			THROW(E_IOERROR_TIMEOUT,
			      E_IOERROR_SUBSYSTEM_NET,
			      E_IOERROR_REASON_NE2K_RESET_ACK);
		}
		task_tryyield_or_pause();
	}
}


DECL_END

#endif /* !GUARD_MODNE2K_UTIL_C */
