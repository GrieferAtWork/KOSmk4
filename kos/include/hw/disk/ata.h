/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_DISK_ATA_H
#define _HW_DISK_ATA_H 1

#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <sys/io.h>

__DECL_BEGIN

/* Default sector size for all ATA disks. */
#define DEFAULT_ATA_SECTOR_SIZE  512
#define DEFAULT_ATA_SECTOR_SHIFT 9 /* == log2(DEFAULT_ATA_SECTOR_SIZE) */

/* Default ATA port numbers (probe these when PCI
 * doesn't enumerate any ATA drives) */
#define ATA_DEFAULT_PRIMARY_BUS    __IOPORT(0x1f0)
#define ATA_DEFAULT_PRIMARY_CTRL   __IOPORT(0x3f6)
#define ATA_DEFAULT_SECONDARY_BUS  __IOPORT(0x170)
#define ATA_DEFAULT_SECONDARY_CTRL __IOPORT(0x376)


/* Offsets for `a_bus' */
#define ATA_DATA           __IOPORT(0) /* ATA Data port */
#define ATA_FEATURES       __IOPORT(1)
#define ATA_SECTOR_COUNT   __IOPORT(2)
#define ATA_ADDRESS1       __IOPORT(3)
#define ATA_ADDRESS2       __IOPORT(4)
#define ATA_ADDRESS3       __IOPORT(5)
#define ATA_DRIVE_SELECT   __IOPORT(6)
#define ATA_STATUS         __IOPORT(7) /* [READ] ATA Status port (same values as `a_ctrl')
                                        * NOTE: Unlike  `a_ctrl', when read, pending interrupts are cleared.
                                        *       This port should  really only be  used for polling-like  ATA
                                        *       operations, as only `a_ctrl' can safely be used when working
                                        *       with interrupts enabled. */
#define ATA_COMMAND        __IOPORT(7) /* [WRITE] ATA Command port */

/* TODO: Get rid of these macros. -- Use the `WIN_*' constants from <linux/hdreg.h> */
#   define ATA_COMMAND_READ_SECTORS    0x20 /* CHS */
#   define ATA_COMMAND_READ_PIO        0x20 /* 28-bit LBA */
#   define ATA_COMMAND_READ_PIO_EXT    0x24 /* 48-bit LBA */
#   define ATA_COMMAND_READ_DMA        0xc8 /* 28-bit LBA */
#   define ATA_COMMAND_READ_DMA_EXT    0x25 /* 48-bit LBA */
#   define ATA_COMMAND_WRITE_SECTORS   0x30 /* CHS */
#   define ATA_COMMAND_WRITE_PIO       0x30 /* 28-bit LBA */
#   define ATA_COMMAND_WRITE_PIO_EXT   0x34 /* 48-bit LBA */
#   define ATA_COMMAND_WRITE_DMA       0xca /* 28-bit LBA */
#   define ATA_COMMAND_WRITE_DMA_EXT   0x35 /* 48-bit LBA */
#   define ATA_COMMAND_CACHE_FLUSH     0xe7 /* 28-bit LBA */
#   define ATA_COMMAND_CACHE_FLUSH_EXT 0xea /* 48-bit LBA */
#   define ATA_COMMAND_PACKET          0xa0
#   define ATA_COMMAND_IDENTIFY_PACKET 0xa1
#   define ATA_COMMAND_IDENTIFY        0xec /* Allows the user to read a `struct hd_driveid' */


/* Bits for `a_ctrl' (DeviceControlRegister) */
#define ATA_DCR_ERR   0x01 /* Indicates an error occurred. (Cleared when `ATA_COMMAND' is written) */
#define ATA_DCR_IDX   0x02 /* Index??? (Always zero)*/
#define ATA_DCR_CORR  0x04 /* Corrected data??? (Always zero) */
#define ATA_DCR_DRQ   0x08 /* Set when the drive is ready to receive/transmit PIO data */
#define ATA_DCR_DSC   0x10 /* Overlapped Mode Service Request??? */
#define ATA_DCR_DF    0x20 /* Drive fault error (independent of `ATA_DCR_ERR') */
#define ATA_DCR_DRDY  0x40 /* 0 when the drive isn't spinning, or after an error (1 otherwise) */
#define ATA_DCR_BSY   0x80 /* Drive is preparing to receive/transmit data (wait for it to clear) */
#define ATA_CTRL_NIEN 0x02 /* Disable interrupts */
#define ATA_CTRL_SRST 0x04 /* Software reset bit */
#define ATA_CTRL_HOB  0x80 /* Read back the last high-order byte of the last LBA-48 value sent */

/* valid values for `drive' */
#define ATA_DRIVE_MASTER    0x40
#define ATA_DRIVE_SLAVE     0x50

/* Offsets for `i_dma_ctrl' / `a_dma' */
#define DMA_PRIMARY_COMMAND   __IOPORT(0x00) /* [TYPE(u8)][READ_WRITE] Primary command (Set of `DMA_COMMAND_F*') */
#define DMA_PRIMARY_STATUS    __IOPORT(0x02) /* [TYPE(u8)][READ][WRITE(CLEAR_BITS)] Primary status (Set of `DMA_STATUS_F*')
                                              * NOTE: When a DMA interrupt is fired, you are _required_ to clear `DMA_STATUS_FINTERRUPTED' in this port! */
#define DMA_PRIMARY_PRDT      __IOPORT(0x04) /* [TYPE(u32)][WRITE] Primary PRDT Address (Points to a vector of `AtaPRD') */
#define DMA_SECONDARY_COMMAND __IOPORT(0x08) /* [TYPE(u8)][READ_WRITE] Secondary command (Set of `DMA_COMMAND_F*') */
#define DMA_SECONDARY_STATUS  __IOPORT(0x0a) /* [TYPE(u8)] Secondary status (Set of `DMA_STATUS_F*') */
#define DMA_SECONDARY_PRDT    __IOPORT(0x0c) /* [TYPE(u32)][WRITE] Secondary PRDT Address (Points to a vector of `AtaPRD') */


/* Bits for `DMA_PRIMARY_COMMAND' */
#define DMA_COMMAND_FENABLED  0x01 /* When set, DMA mode is enabled.
                                    * NOTE: Setting this bit also resets the ATA's DMA pointer to the start
                                    *       of  the PRD vector, should that pointer have been anywhere else
                                    *       prior to then.
                                    * NOTE: When a transfer has been completed, this bit must be cleared
                                    *       before it can be set again. */
#define DMA_COMMAND_FREADMODE 0x08 /* When set, read from disk; when clear, write to disk.
                                    * NOTE: This bit may only be modified when `DMA_COMMAND_FENABLED' has
                                    *       been cleared. */


/* Bits for `DMA_PRIMARY_STATUS' */
#define DMA_STATUS_FDMARUNNING        0x01 /* When  set, DMA mode  is currently running  and working to complete
                                            * all provided `AtaPRD' entries. Once completed, this bit is cleared
                                            * by the ATA device. */
#define DMA_STATUS_FTRANSPORT_FAILURE 0x02 /* Set if any of the `AtaPRD' entries failed to be completed for whatever reason. */
#define DMA_STATUS_FINTERRUPTED       0x04 /* Set if the associated ATA device was responsible for an IRQ being generated. */
#define DMA_STATUS_FNO_PARALLEL_DMA   0x80 /* Indicates that the primary and secondary ATA devices can be used
                                            * for DMA at the same time. (Not normally set on modern  hardware) */


#ifdef __CC__
struct ata_ports {
	__port_t a_bus;  /* I/O port for the ATA bus. */
	__port_t a_ctrl; /* Device control register/Alternate status ports. */
	__port_t a_dma;  /* DMA controller port (or (port_t)-1 if DMA isn't supported)
	                  * NOTE: When initializing a secondary ATA device, this port
	                  *       has been shifted such that  `DMA_SECONDARY_COMMAND'
	                  *       becomes `DMA_PRIMARY_COMMAND', etc. */
};

struct ide_ports {
	__port_t i_primary_bus;    /* I/O port for the primary ATA bus. */
	__port_t i_primary_ctrl;   /* Primary device control register/Alternate status ports. */
	__port_t i_secondary_bus;  /* I/O port for the secondary ATA bus. */
	__port_t i_secondary_ctrl; /* Secondary device control register/Alternate status ports. */
	__port_t i_dma_ctrl;       /* DMA controller port (or (port_t)-1 if DMA isn't supported)
	                            * NOTE: Documentation calls th(is|ese) the `Bus Master Register(s)' */
};
#endif /* __CC__ */



/* Flags for `AtaPRD::p_flags' */
#define PRD_FNORMAL 0x0000 /* Normal AtaPRD flags. */
#define PRD_FLAST   0x8000 /* Must be set for the last AtaPRD */

#define SIZEOF_ATAPRD  8
#ifdef __CC__
typedef struct __ATTR_PACKED __ATTR_ALIGNED(4) {
	/* AtaPRD -- Physical Region Descriptor */
	__PHYS __uint32_t p_bufaddr;  /* Physical address of the target/source buffer */
	__uint16_t        p_bufsize;  /* Buffer size of `p_bufaddr' (in bytes)
	                               * NOTE: When 0, the actual size is `0x10000' */
	__uint16_t        p_flags;    /* Set of `PRD_F*' */
} AtaPRD;
#endif /* __CC__ */


__DECL_END

#endif /* !_HW_DISK_ATA_H */
