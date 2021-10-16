/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODIDE_INIT_C
#define GUARD_MODIDE_INIT_C 1
#define _KOS_SOURCE 1

#include "ata.h"
/**/

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/driver.h>
#include <kernel/isr.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <hw/bus/pci.h>
#include <kos/dev.h>
#include <linux/hdreg.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

#include <libpciaccess/pciaccess.h>

/**/
#include <kernel/x86/pic.h> /* TODO: Non-portable! */

DECL_BEGIN

#ifdef CONFIG_BUILDING_KERNEL_CORE
ATTR_FREEBSS
#endif /* CONFIG_BUILDING_KERNEL_CORE */
DEFINE_CMDLINE_FLAG_VAR(ide_nodma, "ide_nodma");


PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL AtaBus_Fini)(struct chrdev *__restrict self) {
	AtaBus *me = (AtaBus *)self;
	hisr_unregister((isr_function_t)AtaBus_HW_GetInterruptHandler(me), me);
	if (me->ab_prdt)
		vpage_free_untraced(me->ab_prdt, 1);
}

PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1)) void
NOTHROW(KCALL AtaDrive_Fini)(struct block_device *__restrict self) {
	AtaDrive *me = (AtaDrive *)self;
	decref_unlikely(me->ad_bus);
}




PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
Ata_InitializeDrive(struct ata_ports *__restrict ports,
                    /*(in|out)_opt*/ REF AtaBus **__restrict pbus,
                    u8 drive_id, bool is_primary_bus,
                    bool is_default_ide) {
	u8 cl, ch;
	struct hd_driveid specs;
	assert(drive_id == ATA_DRIVE_MASTER ||
	       drive_id == ATA_DRIVE_SLAVE);
	printk(FREESTR(KERN_INFO "[ata] Attempting to initialize %s %s ATA device {"
	                         "%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "%#" PRIxN(__SIZEOF_PORT_T__) "} (default_ide: %u)\n"),
	       is_primary_bus ? FREESTR("primary") : FREESTR("secondary"),
	       drive_id == ATA_DRIVE_MASTER ? FREESTR("master") : FREESTR("slave"),
	       ports->a_bus, ports->a_ctrl,
	       ports->a_dma, is_default_ide ? 1 : 0);
	TRY {
		/* Check for a floating bus. */
		{
			u8 initial_status;
			initial_status = inb(ports->a_bus + ATA_STATUS);
			if (initial_status == 0xff)
				return false; /* Floating bus */
		}


		/* Do a soft reset on both ATA device control ports. */
		AtaBus_HW_ResetBus_P(ports->a_ctrl);

		/* Select the requested drive. */
		outb(ports->a_bus + ATA_DRIVE_SELECT, drive_id);
		AtaBus_HW_SelectDelay_P(ports->a_ctrl);

		/* Wait for the command to be acknowledged. */
		if (AtaBus_HW_WaitForBusy_P(ports->a_ctrl, (ktime_t)3 * NSEC_PER_SEC) != ATA_ERROR_OK)
			return false;

		/* Figure out what kind of drive this is. */
		cl = inb(ports->a_bus + ATA_ADDRESS2);
		ch = inb(ports->a_bus + ATA_ADDRESS3);

		if ((cl == 0x00 && ch == 0x00) || /* PATA */
		    (cl == 0x3c && ch == 0xc3)) { /* SATA */
			REF AtaDrive *drive;
			AtaBus *bus = *pbus;
			if (!bus) {
				*pbus = bus = CHRDEV_ALLOC(AtaBus);
				TRY {
#if ATA_BUS_STATE_READY != 0
					bus->ab_state = ATA_BUS_STATE_READY;
#endif /* ATA_BUS_STATE_READY != 0 */
					assert(bus->ab_aio_pending == NULL);
					assert(bus->ab_aio_current == NULL);
					sig_cinit(&bus->ab_ready);
					sig_cinit(&bus->ab_piointr);
					bus->cd_type.ct_fini = &AtaBus_Fini;
					bus->ab_busio  = ports->a_bus;
					bus->ab_ctrlio = ports->a_ctrl;
					bus->ab_dmaio  = ports->a_dma;
					bus->ab_dma_retry   = 3;
					bus->ab_pio_retry   = 3;
					bus->ab_timeout_BSY = (ktime_t)3 * NSEC_PER_SEC;
					bus->ab_timeout_DRQ = (ktime_t)3 * NSEC_PER_SEC;
					bus->ab_timeout_dat = (ktime_t)2 * NSEC_PER_SEC;
					assert(bus->ab_prdt == NULL);
					/* The BUS structure must be registered alongside an interrupt registration. */
					hisr_register_at(is_primary_bus ? X86_INTNO_PIC2_ATA1 /* TODO: Non-portable! */
					                                : X86_INTNO_PIC2_ATA2,
					                 (isr_function_t)AtaBus_HW_GetInterruptHandler(bus),
					                 bus);
					if (is_default_ide)
						sprintf(bus->cd_name, "ide%c", is_primary_bus ? 'a' : 'b');
					chrdev_register_auto(bus);
				} EXCEPT {
					chrdev_destroy(bus);
					*pbus = NULL;
					RETHROW();
				}
			}
			/* Construct and initialize a new ATA drive for this bus. */
			ATOMIC_WRITE(bus->ab_state, ATA_BUS_STATE_INPIO);
			if (AtaBus_HW_WaitForBusy(bus) != ATA_ERROR_OK)
				return false;
			task_connect(&bus->ab_piointr);
			TRY {
				outb(bus->ab_busio + ATA_DRIVE_SELECT,
				     0xa0 + (drive_id - ATA_DRIVE_MASTER));
				AtaBus_HW_SelectDelay_P(ports->a_ctrl);
				outb(bus->ab_busio + ATA_ADDRESS1, 0);
				outb(bus->ab_busio + ATA_ADDRESS2, 0);
				outb(bus->ab_busio + ATA_ADDRESS3, 0);
				outb(bus->ab_busio + ATA_COMMAND, ATA_COMMAND_IDENTIFY);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}
			if (!task_trywait()) {
				struct sig *signal;
				u8 status;
				status = inb(bus->ab_ctrlio);
				if (status == 0) {
					signal = task_receiveall();
					if unlikely(signal)
						goto got_identify_signal;
					/* Drive doesn't exist (graceful exit) */
					printk(FREESTR(KERN_INFO "[ata] No drive connected [status:0]\n"));
					goto reset_bus_and_fail;
				}
				if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF)) {
					task_disconnectall();
					goto reset_bus_and_fail;
				}
				{
					ktime_t timeout;
					timeout = ktime();
					timeout += relktime_from_seconds(2);
					signal = task_waitfor(timeout);
				}
				if (!signal) {
					printk(FREESTR(KERN_ERR "[ata] Timeout while waiting for ATA_COMMAND_IDENTIFY "
					                        "[status={then:%#" PRIx8 ",now:%#" PRIx8 "}]\n"),
					       status, inb(bus->ab_ctrlio));
reset_bus_and_fail:
					AtaBus_HW_ResetBusAuto(bus);
					ATOMIC_WRITE(bus->ab_state, ATA_BUS_STATE_READY);
					return false;
				}
			}
got_identify_signal:
			if (AtaBus_HW_WaitForDrq(bus) != ATA_ERROR_OK)
				goto reset_bus_and_fail;
			insw(bus->ab_busio + ATA_DATA, &specs, 256);
			outb(bus->ab_busio + ATA_FEATURES, 0); /* ??? */
			ATOMIC_WRITE(bus->ab_state, ATA_BUS_STATE_READY);
			/* Fix specifications to properly represent implications. */
			if (bus->ab_dmaio == (port_t)-1)
				specs.capability &= ~HD_DRIVEID_CAPABILITY_DMA;
			if (!(specs.capability & HD_DRIVEID_CAPABILITY_LBA))
				specs.command_set_2 &= ~HD_DRIVEID_COMMAND_SET_2_LBA48;
			drive = (AtaDrive *)block_device_alloc(DEFAULT_ATA_SECTOR_SIZE,
			                                       specs.capability & HD_DRIVEID_CAPABILITY_DMA
			                                       ? sizeof(AtaDmaDrive)
			                                       : sizeof(AtaDrive));
			drive->ad_bus   = (REF AtaBus *)incref(bus);
			drive->ad_drive = drive_id;
			drive->bd_type.dt_fini  = &AtaDrive_Fini;
			drive->bd_type.dt_ioctl = (syscall_slong_t (KCALL *)(struct block_device *__restrict,
			                                                     struct block_device *__restrict,
			                                                     syscall_ulong_t, USER UNCHECKED void *,
			                                                     iomode_t) THROWS(...))&AtaDrive_Ioctl;
			drive->ad_chs_number_of_heads   = (u8)specs.heads;
			drive->ad_chs_cylinders         = (u16)specs.cyls;
			drive->ad_chs_sectors_per_track = (u8)specs.sectors;
			/*drive->bd_type.dt_fini = NULL;*/
			if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_FLUSH)
				drive->ad_features |= ATA_DRIVE_FEATURE_FFLUSH;
			if (specs.capability & HD_DRIVEID_CAPABILITY_DMA) {
				AtaDmaDrive *ddrive = (AtaDmaDrive *)drive;
				if (!bus->ab_prdt) {
					physaddr_t phys;
					bus->ab_prdt = (AtaPRD *)vpage_alloc_untraced(1, 1, GFP_LOCKED | GFP_PREFLT);
					/* Re-set the PRDT address. */
					phys = pagedir_translate(bus->ab_prdt);
					/* TODO: Ensure that a physical page <= 0xfffff000 is allocated for this VPAGE */
					assertf(phys <= (physaddr_t)0xffffffff, "TODO");
					outl(bus->ab_dmaio + DMA_PRIMARY_PRDT, (u32)phys);
				}
				ddrive->bd_type.dt_read        = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveRead;
				ddrive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveReadPhys;
				ddrive->bd_type.dt_readv       = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveReadVector;
				ddrive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveReadVectorPhys;
				ddrive->bd_type.dt_write       = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveWrite;
				ddrive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveWritePhys;
				ddrive->bd_type.dt_writev      = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveWriteVector;
				ddrive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_DmaDriveWriteVectorPhys;
				if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_LBA48) {
					if ((specs.capability & HD_DRIVEID_CAPABILITY_LBA) &&
						(u64)specs.lba_capacity_2 == (u64)specs.lba_capacity)
						goto use_28bit_dma;
					ddrive->add_nc_read        = &AtaDrive_Lba48DriveRead;
					ddrive->add_nc_read_phys   = &AtaDrive_Lba48DriveReadPhys;
					ddrive->add_nc_readv       = &AtaDrive_Lba48DriveReadVector;
					ddrive->add_nc_readv_phys  = &AtaDrive_Lba48DriveReadVectorPhys;
					ddrive->add_nc_write       = &AtaDrive_Lba48DriveWrite;
					ddrive->add_nc_write_phys  = &AtaDrive_Lba48DriveWritePhys;
					ddrive->add_nc_writev      = &AtaDrive_Lba48DriveWriteVector;
					ddrive->add_nc_writev_phys = &AtaDrive_Lba48DriveWriteVectorPhys;
					goto calculate_lba48;
				} else if (specs.capability & HD_DRIVEID_CAPABILITY_LBA) {
use_28bit_dma:
					ddrive->add_nc_read        = &AtaDrive_Lba28DriveRead;
					ddrive->add_nc_read_phys   = &AtaDrive_Lba28DriveReadPhys;
					ddrive->add_nc_readv       = &AtaDrive_Lba28DriveReadVector;
					ddrive->add_nc_readv_phys  = &AtaDrive_Lba28DriveReadVectorPhys;
					ddrive->add_nc_write       = &AtaDrive_Lba28DriveWrite;
					ddrive->add_nc_write_phys  = &AtaDrive_Lba28DriveWritePhys;
					ddrive->add_nc_writev      = &AtaDrive_Lba28DriveWriteVector;
					ddrive->add_nc_writev_phys = &AtaDrive_Lba28DriveWriteVectorPhys;
					goto calculate_lba28;
				} else {
					ddrive->add_nc_read        = &AtaDrive_ChsDriveRead;
					ddrive->add_nc_read_phys   = &AtaDrive_ChsDriveReadPhys;
					ddrive->add_nc_readv       = &AtaDrive_ChsDriveReadVector;
					ddrive->add_nc_readv_phys  = &AtaDrive_ChsDriveReadVectorPhys;
					ddrive->add_nc_write       = &AtaDrive_ChsDriveWrite;
					ddrive->add_nc_write_phys  = &AtaDrive_ChsDriveWritePhys;
					ddrive->add_nc_writev      = &AtaDrive_ChsDriveWriteVector;
					ddrive->add_nc_writev_phys = &AtaDrive_ChsDriveWriteVectorPhys;
					goto calculate_chs;
				}
			} else {
				if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_LBA48) {
					if ((specs.capability & HD_DRIVEID_CAPABILITY_LBA) &&
					    (u64)specs.lba_capacity_2 == (u64)specs.lba_capacity)
						goto use_28bit_lba;
					drive->bd_type.dt_read        = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveRead;
					drive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveReadPhys;
					drive->bd_type.dt_readv       = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveReadVector;
					drive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveReadVectorPhys;
					drive->bd_type.dt_write       = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveWrite;
					drive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveWritePhys;
					drive->bd_type.dt_writev      = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveWriteVector;
					drive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba48DriveWriteVectorPhys;
calculate_lba48:
					drive->bd_sector_count = (lba_t)specs.lba_capacity_2;
				} else if (specs.capability & HD_DRIVEID_CAPABILITY_LBA) {
use_28bit_lba:
					drive->bd_type.dt_read        = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveRead;
					drive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveReadPhys;
					drive->bd_type.dt_readv       = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveReadVector;
					drive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveReadVectorPhys;
					drive->bd_type.dt_write       = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveWrite;
					drive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveWritePhys;
					drive->bd_type.dt_writev      = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveWriteVector;
					drive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_Lba28DriveWriteVectorPhys;
calculate_lba28:
					drive->bd_sector_count = (lba_t)specs.lba_capacity;
				} else {
					drive->bd_type.dt_read        = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveRead;
					drive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveReadPhys;
					drive->bd_type.dt_readv       = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveReadVector;
					drive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveReadVectorPhys;
					drive->bd_type.dt_write       = (void(KCALL *)(struct block_device *__restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveWrite;
					drive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device *__restrict, physaddr_t, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveWritePhys;
					drive->bd_type.dt_writev      = (void(KCALL *)(struct block_device *__restrict, struct iov_buffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveWriteVector;
					drive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device *__restrict, struct iov_physbuffer *__restrict, size_t, lba_t, struct aio_handle *__restrict) THROWS(...))&AtaDrive_ChsDriveWriteVectorPhys;
calculate_chs:
					drive->bd_sector_count = (lba_t)(u8)specs.heads *
					                         (lba_t)(u16)specs.cyls *
					                         (lba_t)(u8)specs.sectors;
				}
			}
			drive->bd_total_bytes = ((pos_t)drive->bd_sector_count *
			                         (pos_t)ATA_SECTOR_SIZE(drive));
			TRY {
				/* Register the new device. */
				if (is_default_ide) {
					dev_t devno;
					devno = MKDEV(is_primary_bus ? 3 : 22,
					              drive_id == ATA_DRIVE_MASTER ? 0 : 64);
					drive->bd_name[0] = 'h';
					drive->bd_name[1] = 'd';
					drive->bd_name[2] = (is_primary_bus ? 'a' : 'c') +
					                    (drive_id == ATA_DRIVE_MASTER ? 0 : 1);
					drive->bd_name[3] = 0;
					blkdev_register(drive, devno);
				} else {
					blkdev_register_auto(drive);
				}
				blkdev_repart(drive);
			} EXCEPT {
				decref(drive);
				RETHROW();
			}
			return true;
		}
		if ((cl == 0x14 && ch == 0xeb) || /* PATAPI */
		    (cl == 0x69 && ch == 0x96)) { /* SATAPI */
			/* TODO (CD drives and the like...) */
		}
	} EXCEPT {
		error_class_t cls = error_class();
		if (ERRORCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		error_printf("Initializing ATA device");
	}
	return false;
}

PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
initialize_ata(struct ata_ports *__restrict ports,
               bool is_primary_bus,
               bool is_default_ide) {
	REF AtaBus *bus = NULL;
	bool result;
	TRY {
		result = Ata_InitializeDrive(ports, &bus, ATA_DRIVE_MASTER, is_primary_bus, is_default_ide);
		result |= Ata_InitializeDrive(ports, &bus, ATA_DRIVE_SLAVE, is_primary_bus, is_default_ide);
	} EXCEPT {
		xdecref_unlikely(bus);
		RETHROW();
	}
	xdecref_unlikely(bus);
	return result;
}

PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
initialize_ide(struct ide_ports *__restrict self, bool is_default_ide) {
	struct ata_ports a;
	bool result;
	printk(FREESTR(KERN_INFO "[ata] Attempting to initialize IDE device {"
	                         "%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "%#" PRIxN(__SIZEOF_PORT_T__) ","
	                         "%#" PRIxN(__SIZEOF_PORT_T__) "} "
	                         "(default_ide: %u)\n"),
	       self->i_primary_bus, self->i_primary_ctrl,
	       self->i_secondary_bus, self->i_secondary_ctrl,
	       self->i_dma_ctrl, is_default_ide ? 1 : 0);
	/* Initialize the primary and secondary ata devices which may be connected to this IDE. */
	a.a_bus  = self->i_primary_bus;
	a.a_ctrl = self->i_primary_ctrl;
	a.a_dma  = self->i_dma_ctrl;
	result   = initialize_ata(&a, true, is_default_ide);
	a.a_bus  = self->i_secondary_bus;
	a.a_ctrl = self->i_secondary_ctrl;
	a.a_dma  = self->i_dma_ctrl;
	if (a.a_dma != (port_t)-1)
		a.a_dma += (DMA_SECONDARY_COMMAND - DMA_PRIMARY_COMMAND);
	result |= initialize_ata(&a, false, is_default_ide);
	return result;
}

/* @return: true:  Primary IDE device found.
 * @return: false: Secondary IDE device found, or initialization failed. */
PRIVATE ATTR_FREETEXT ATTR_NOINLINE bool KCALL
kernel_load_pci_ide(struct pci_device *__restrict dev) {
	bool result = false;
	struct ide_ports i;
	if (dev->pd_regions[0].pmr_size == 0) {
		i.i_primary_bus = ATA_DEFAULT_PRIMARY_BUS;
		result          = true;
	} else {
		if (!dev->pd_regions[0].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR0 (primary bus)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_primary_bus = (port_t)dev->pd_regions[0].pmr_addr;
		if (i.i_primary_bus == ATA_DEFAULT_PRIMARY_BUS)
			result = true;
	}
	if (dev->pd_regions[1].pmr_size == 0) {
		i.i_primary_ctrl = ATA_DEFAULT_PRIMARY_CTRL;
		result           = true;
	} else {
		if (!dev->pd_regions[1].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR1 (primary control)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_primary_ctrl = (port_t)dev->pd_regions[1].pmr_addr;
		if (i.i_primary_ctrl == ATA_DEFAULT_PRIMARY_CTRL)
			result = true;
	}
	if (dev->pd_regions[2].pmr_size == 0) {
		i.i_secondary_bus = ATA_DEFAULT_SECONDARY_BUS;
		result            = true;
	} else {
		if (!dev->pd_regions[2].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR2 (secondary bus)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_secondary_bus = (port_t)dev->pd_regions[2].pmr_addr;
		if (i.i_secondary_bus == ATA_DEFAULT_SECONDARY_BUS)
			result = true;
	}
	if (dev->pd_regions[3].pmr_size == 0) {
		i.i_secondary_ctrl = ATA_DEFAULT_SECONDARY_CTRL;
		result             = true;
	} else {
		if (!dev->pd_regions[3].pmr_is_IO) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %" PRIp32 " uses a "
			                            "memory mapping for BAR3 (secondary control)\n"),
			       dev->pd_addr);
			return false;
		}
		i.i_secondary_ctrl = (port_t)dev->pd_regions[3].pmr_addr;
		if (i.i_secondary_ctrl == ATA_DEFAULT_SECONDARY_CTRL)
			result = true;
	}
	i.i_dma_ctrl = (port_t)-1;

	/* Check if this IDE may support DMA mode. */
	if (dev->pd_regions[4].pmr_is_IO && dev->pd_regions[4].pmr_size >= 16) {
		i.i_dma_ctrl = (port_t)dev->pd_regions[4].pmr_addr;
		pci_device_cfg_writel(dev, PCI_DEV4,
		                      (pci_device_cfg_readl(dev, PCI_DEV4) & ~(PCI_CDEV4_NOIRQ)) |
		                      (PCI_CDEV4_BUSMASTER | PCI_CDEV4_ALLOW_MEMWRITE));
	}

	/* Forceably disable DMA, the same way a bus without support would */
	if (ide_nodma)
		i.i_dma_ctrl = (port_t)-1;
	return initialize_ide(&i, result) ? result : false;
}


#ifdef CONFIG_BUILDING_KERNEL_CORE
INTERN ATTR_FREETEXT void KCALL kernel_initialize_ide_driver(void)
#else /* CONFIG_BUILDING_KERNEL_CORE */
PRIVATE DRIVER_INIT ATTR_FREETEXT void KCALL ata_init(void)
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
{
	bool has_primary = false;
	struct pci_device *dev;
	/* Search for IDE PCI devices. */
	PCI_FOREACH_DEVICE_CLASS (dev, PCI_DEV8_CLASS_STORAGE, 1) {
		has_primary |= kernel_load_pci_ide(dev);
	}
	if (!has_primary) {
		/* Check for an IDE device at the default location. */
		struct ide_ports i;
		i.i_primary_bus    = ATA_DEFAULT_PRIMARY_BUS;
		i.i_primary_ctrl   = ATA_DEFAULT_PRIMARY_CTRL;
		i.i_secondary_bus  = ATA_DEFAULT_SECONDARY_BUS;
		i.i_secondary_ctrl = ATA_DEFAULT_SECONDARY_CTRL;
		i.i_dma_ctrl       = (port_t)-1;
		initialize_ide(&i, true);
	}
}

DECL_END

#endif /* !GUARD_MODIDE_INIT_C */
