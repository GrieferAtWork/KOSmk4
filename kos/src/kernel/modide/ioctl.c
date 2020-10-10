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
#ifndef GUARD_MODIDE_IOCTL_C
#define GUARD_MODIDE_IOCTL_C 1
#define _KOS_SOURCE 1

#include "ata.h"
/**/

#include <kernel/compiler.h>

#include <kernel/compat.h>
#include <kernel/user.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <linux/hdreg.h>
#include <sys/io.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

PRIVATE ATTR_PURE WUNUSED NONNULL((1)) pos_t
NOTHROW(KCALL BlockDevice_GetPartitionStart)(struct block_device const *__restrict self) {
	struct block_device_partition *part;
	if (!block_device_ispartition(self))
		return 0;
	part = (struct block_device_partition *)self;
	return part->bp_minaddr;
}

/* Device I/O control callback for ATA drive objects. */
INTERN NONNULL((1)) syscall_slong_t KCALL
AtaDrive_Ioctl(AtaDrive *__restrict self,
               struct block_device *__restrict partition,
               syscall_ulong_t cmd, USER UNCHECKED void *arg,
               iomode_t mode) THROWS(...) {
	(void)mode;
	switch (cmd) {

	case HDIO_GETGEO:
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			goto do_compat_hdio_getgeo;
		ATTR_FALLTHROUGH
#endif /* __ARCH_HAVE_COMPAT */
	case _IOR(_IOC_TYPE(HDIO_GETGEO), _IOC_NR(HDIO_GETGEO), struct hd_geometry): {
		struct hd_geometry *data;
		validate_writable(arg, sizeof(struct hd_geometry));
		data = (struct hd_geometry *)arg;
		COMPILER_WRITE_BARRIER();
		data->heads     = self->ad_chs_number_of_heads;
		data->cylinders = self->ad_chs_cylinders;
		data->sectors   = self->ad_chs_sectors_per_track;
		data->start     = (ulongptr_t)BlockDevice_GetPartitionStart(partition);
		COMPILER_WRITE_BARRIER();
	}	break;

#ifdef __ARCH_HAVE_COMPAT
	case _IOR(_IOC_TYPE(HDIO_GETGEO), _IOC_NR(HDIO_GETGEO), struct hd_geometry_compat): {
		struct hd_geometry_compat *data;
do_compat_hdio_getgeo:
		validate_writable(arg, sizeof(struct hd_geometry_compat));
		data = (struct hd_geometry_compat *)arg;
		COMPILER_WRITE_BARRIER();
		data->heads     = self->ad_chs_number_of_heads;
		data->cylinders = self->ad_chs_cylinders;
		data->sectors   = self->ad_chs_sectors_per_track;
		data->start     = (__ARCH_COMPAT_LONGPTR_TYPE)BlockDevice_GetPartitionStart(partition);
		COMPILER_WRITE_BARRIER();
	}	break;
#endif /* __ARCH_HAVE_COMPAT */

	case HDIO_GET_IDENTITY:
	case _IOR(_IOC_TYPE(HDIO_GET_IDENTITY), _IOC_NR(HDIO_GET_IDENTITY), struct hd_driveid): {
		struct hd_driveid specs;
		AtaBus *bus;
		validate_writable(arg, sizeof(specs));
		bus = self->ad_bus;
		AtaBus_LockPIO(bus);
		TRY {
			assert(!task_isconnected());
			task_connect(&bus->ab_piointr);
			outb(bus->ab_busio + ATA_DRIVE_SELECT,
			     0xa0 + (self->ad_drive - ATA_DRIVE_MASTER));
			AtaBus_HW_SelectDelay(bus);
			outb(bus->ab_busio + ATA_ADDRESS1, 0);
			outb(bus->ab_busio + ATA_ADDRESS2, 0);
			outb(bus->ab_busio + ATA_ADDRESS3, 0);
			outb(bus->ab_busio + ATA_FEATURES, 1); /* ??? */
			TRY {
				outb(bus->ab_busio + ATA_COMMAND, ATA_COMMAND_IDENTIFY);
				if (!task_trywait()) {
					struct sig *signal;
					u8 status;
					status = inb(bus->ab_ctrlio);
					if (status == 0) {
						signal = task_receiveall();
						if unlikely(signal)
							goto got_identify_signal;
						/* While not actually a timeout, this should be treated just like a timeout! */
						THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HARDDISK);
					}
					{
						struct timespec timeout;
						timeout = realtime();
						timeout.tv_sec += 2;
						signal = task_waitfor(&timeout);
					}
					if (!signal)
						THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HARDDISK);
				}
				{
got_identify_signal:
					AtaError_t error;
					error = AtaBus_HW_WaitForDrq(bus);
					if (error != ATA_ERROR_OK) {
						THROW((ATA_ERROR_CLASS(error), ATA_ERROR_SUBCLASS(error)),
						      ATA_ERROR_REASON(error));
					}
				}
				insw(bus->ab_busio + ATA_DATA, &specs, 256);
			} EXCEPT {
				outb(bus->ab_busio + ATA_FEATURES, 0); /* ??? */
				RETHROW();
			}
			outb(bus->ab_busio + ATA_FEATURES, 0); /* ??? */
		} EXCEPT {
			AtaBus_UnlockPIO(bus);
			RETHROW();
		}
		AtaBus_UnlockPIO(bus);
		COMPILER_WRITE_BARRIER();
		memcpy(arg, &specs, sizeof(specs));
		COMPILER_WRITE_BARRIER();
	}	break;

	case HDIO_GET_DMA:
	case _IOR(_IOC_TYPE(HDIO_GET_DMA), _IOC_NR(HDIO_GET_DMA), int): {
		validate_writable(arg, sizeof(int));
		COMPILER_WRITE_BARRIER();
		*(int *)arg = ((void *)self->bd_type.dt_read == (void *)&AtaDrive_DmaDriveRead) ? 1 : 0;
		COMPILER_WRITE_BARRIER();
	}	break;

	case HDIO_GET_WCACHE:
	case _IOR(_IOC_TYPE(HDIO_GET_WCACHE), _IOC_NR(HDIO_GET_WCACHE), int): {
		validate_writable(arg, sizeof(int));
		COMPILER_WRITE_BARRIER();
		*(int *)arg = (self->ad_features & ATA_DRIVE_FEATURE_FFLUSH) ? 1 : 0;
		COMPILER_WRITE_BARRIER();
	}	break;

	case HDIO_SET_WCACHE:
	case _IOW(_IOC_TYPE(HDIO_SET_WCACHE), _IOC_NR(HDIO_SET_WCACHE), int): {
		int cache_mode;
		validate_readable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		cache_mode = *(int *)arg;
		COMPILER_READ_BARRIER();
		if (cache_mode) {
			/* WARNING: The drive may not actually support this... */
			ATOMIC_OR(self->ad_features, ATA_DRIVE_FEATURE_FFLUSH);
		} else {
			ATOMIC_AND(self->ad_features, ~ATA_DRIVE_FEATURE_FFLUSH);
		}
	}	break;

	case HDIO_DRIVE_RESET: {
		AtaBus *bus;
		bus = self->ad_bus;
		AtaBus_LockPIO(bus);
		TRY {
			AtaBus_HW_ResetBusAuto(bus);
		} EXCEPT {
			AtaBus_UnlockPIO(bus);
			RETHROW();
		}
		AtaBus_UnlockPIO(bus);
	}	break;

	case HDIO_GET_BUSSTATE:
	case _IOR(_IOC_TYPE(HDIO_GET_BUSSTATE), _IOC_NR(HDIO_GET_BUSSTATE), int): {
		uintptr_half_t state;
		validate_writable(arg, sizeof(int));
		state = ATOMIC_READ(self->ad_bus->ab_state);
		COMPILER_WRITE_BARRIER();
		/* XXX: I have no idea what `BUSSTATE_TRISTATE' is all about...
		 *      (Or if this right here is even correct) */
		*(int *)arg = state == ATA_BUS_STATE_READY
		              ? BUSSTATE_OFF
		              : BUSSTATE_ON;
		COMPILER_WRITE_BARRIER();
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
		      cmd);
	}
	return 0;
}


DECL_END

#endif /* !GUARD_MODIDE_IOCTL_C */
