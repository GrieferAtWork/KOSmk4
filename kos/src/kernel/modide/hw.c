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
#ifndef GUARD_MODIDE_HW_C
#define GUARD_MODIDE_HW_C 1
#define _KOS_SOURCE 1

#include "ata.h"
/**/

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <sched/tsc.h>

#include <assert.h>
#include <time.h>

/* Hardware helper functions */

DECL_BEGIN

INTERN NOBLOCK AtaError_t
NOTHROW(FCALL AtaBus_HW_WaitForBusy_P)(port_t ctrlio, ktime_t timeout_BSY) {
	u8 status;
	ktime_t abs_timeout;
	status = inb(ctrlio);
	if (!(status & ATA_DCR_BSY))
		return ATA_ERROR_OK;
	if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
		return ATA_HW_GetErrorFromStatusRegister(status);
	abs_timeout = ktime();
	abs_timeout += timeout_BSY;
	while ((status = inb(ctrlio)) & ATA_DCR_BSY) {
		if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
			return ATA_HW_GetErrorFromStatusRegister(status);
		if unlikely(ktime() >= abs_timeout)
			return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_DCR_BSY);
		task_tryyield_or_pause();
		io_delay();
	}
	return ATA_ERROR_OK;
}

/* Wait for `!ATA_DCR_BSY', but time out eventually. */
INTERN NOBLOCK AtaError_t
NOTHROW(FCALL AtaBus_HW_WaitForBusy)(AtaBus *__restrict self) {
	return AtaBus_HW_WaitForBusy_P(self->ab_ctrlio, self->ab_timeout_BSY);
}

/* Wait for `ATA_DCR_DRQ', but time out eventually. */
INTERN NOBLOCK AtaError_t
NOTHROW(FCALL AtaBus_HW_WaitForDrq)(AtaBus *__restrict self) {
	u8 status;
	ktime_t abs_timeout;
	if (((status = inb(self->ab_ctrlio)) & ATA_DCR_BSY) == 0) {
		abs_timeout = ktime();
		abs_timeout += self->ab_timeout_BSY;
		while ((status = inb(self->ab_ctrlio)) & ATA_DCR_BSY) {
			if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
				return ATA_HW_GetErrorFromStatusRegister(status);
			if unlikely(ktime() >= abs_timeout)
				return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_DCR_BSY);
			task_tryyield_or_pause();
			io_delay();
		}
	}
	if (status & (ATA_DCR_ERR | ATA_DCR_DF))
		return ATA_HW_GetErrorFromStatusRegister(status);
	if (status & ATA_DCR_DRQ)
		return ATA_ERROR_OK;
	abs_timeout = ktime();
	abs_timeout += self->ab_timeout_DRQ;
	for (;;) {
		task_tryyield_or_pause();
		io_delay();
		status = inb(self->ab_ctrlio);
		if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
			return ATA_HW_GetErrorFromStatusRegister(status);
		if unlikely(ktime() >= abs_timeout)
			return ATA_ERROR(E_IOERROR_TIMEOUT, E_IOERROR_REASON_ATA_DCR_BSY);
		if (status & ATA_DCR_DRQ)
			break;
	}
	return ATA_ERROR_OK;
}

/* Reset the given bus on a hardware-level. */
INTERN NOBLOCK void
NOTHROW(FCALL AtaBus_HW_ResetBus_P)(port_t ctrlio) {
	outb(ctrlio, ATA_CTRL_SRST);
	AtaBus_HW_SelectDelay_P(ctrlio);
	outb(ctrlio, 0);
	AtaBus_HW_SelectDelay_P(ctrlio);
}

/* Same as `AtaBus_HW_ResetBus()', but re-initialize DMA afterwards. */
INTERN NOBLOCK void
NOTHROW(FCALL AtaBus_HW_ResetBusAndInitializeDMA)(AtaBus *__restrict self) {
	physaddr_t phys;
	AtaBus_HW_ResetBus(self);
	/* Re-set the PRDT address. */
	phys = pagedir_translate(self->ab_prdt);
	assert(phys <= (physaddr_t)0xffffffff);
	outl(self->ab_dmaio + DMA_PRIMARY_PRDT, (u32)phys);
}



DECL_END

#endif /* !GUARD_MODIDE_HW_C */
