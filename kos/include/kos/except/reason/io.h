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
#ifndef _KOS_EXCEPT_REASON_IO_H
#define _KOS_EXCEPT_REASON_IO_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Sub-system codes for E_IOERROR exceptions */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_IOERROR_SUBSYSTEM_GENERIC,  /* Generic I/O sub-system */
	E_IOERROR_SUBSYSTEM_HARDDISK, /* The error stems from the physical disk faulting */
	E_IOERROR_SUBSYSTEM_FILE,     /* The error stems from an I/O-related file error */
	E_IOERROR_SUBSYSTEM_HID,      /* The error stems from a HumanInterfaceDevice-related connection error */
	E_IOERROR_SUBSYSTEM_USB,      /* The error stems from the USB sub-system */
	E_IOERROR_SUBSYSTEM_TTY,      /* The error stems from the TTY sub-system */
	E_IOERROR_SUBSYSTEM_NET,      /* The error stems from the network sub-system */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_IOERROR_SUBSYSTEM_GENERIC  E_IOERROR_SUBSYSTEM_GENERIC  /* Generic I/O sub-system */
#define E_IOERROR_SUBSYSTEM_HARDDISK E_IOERROR_SUBSYSTEM_HARDDISK /* The error stems from the physical disk faulting */
#define E_IOERROR_SUBSYSTEM_FILE     E_IOERROR_SUBSYSTEM_FILE     /* The error stems from an I/O-related file error */
#define E_IOERROR_SUBSYSTEM_HID      E_IOERROR_SUBSYSTEM_HID      /* The error stems from a HumanInterfaceDevice-related connection error */
#define E_IOERROR_SUBSYSTEM_USB      E_IOERROR_SUBSYSTEM_USB      /* The error stems from the USB sub-system */
#define E_IOERROR_SUBSYSTEM_TTY      E_IOERROR_SUBSYSTEM_TTY      /* The error stems from the TTY sub-system */
#define E_IOERROR_SUBSYSTEM_NET      E_IOERROR_SUBSYSTEM_NET      /* The error stems from the network sub-system */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_IOERROR_SUBSYSTEM_GENERIC  0 /* Generic I/O sub-system */
#define E_IOERROR_SUBSYSTEM_HARDDISK 1 /* The error stems from the physical disk faulting */
#define E_IOERROR_SUBSYSTEM_FILE     2 /* The error stems from an I/O-related file error */
#define E_IOERROR_SUBSYSTEM_HID      3 /* The error stems from a HumanInterfaceDevice-related connection error */
#define E_IOERROR_SUBSYSTEM_USB      4 /* The error stems from the USB sub-system */
#define E_IOERROR_SUBSYSTEM_TTY      5 /* The error stems from the TTY sub-system */
#define E_IOERROR_SUBSYSTEM_NET      6 /* The error stems from the network sub-system */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/




/* Reason codes for E_IOERROR exceptions */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	E_IOERROR_REASON_GENERIC,         /* Generic error reason */
	E_IOERROR_REASON_ATA_DCR_ERR,     /* `ATA_DCR_ERR' was set */
	E_IOERROR_REASON_ATA_DCR_DF,      /* `ATA_DCR_DF' was set */
	E_IOERROR_REASON_ATA_DCR_ERR_DF,  /* `ATA_DCR_ERR' and `ATA_DCR_DF' were set */
	E_IOERROR_REASON_ATA_DMA_ERR,     /* `DMA_STATUS_FTRANSPORT_FAILURE' was set */
	E_IOERROR_REASON_ATA_DCR_BSY,     /* Timeout while waiting for `ATA_DCR_BSY' */
	E_IOERROR_REASON_ATA_SECTOR_WAIT, /* Timeout while waiting for sector data */
	E_IOERROR_REASON_USB_SHORTPACKET, /* Short-packet-detect during a transfer without the `USB_TRANSFER_FLAG_SHORT' flag set. */
	E_IOERROR_REASON_USB_TOOMANY,     /* Too many devices connected (at most 126 (127-1) devices can be supported) */
	E_IOERROR_REASON_UHCI_BADEP,      /* A `uhci_qh::qh_ep' field contained a bad value `POINTER[2]' */
	E_IOERROR_REASON_UHCI_TDCS,       /* At least one of the error bits of `UHCI_TDCS_*' is set (POINTER[2] is the `td_cs' field) */
	E_IOERROR_REASON_UHCI_INCOMPLETE, /* The `UHCI_TDCS_ACTIVE' bit got cleared without any apparent reason. */
	E_IOERROR_REASON_TTY_SIGTTIN,     /* E_IOERROR_NODATA: Attempted to read() a TTY from a background process group. */
	E_IOERROR_REASON_TTY_SIGTTOU,     /* E_IOERROR_NODATA: Attempted to write() a TTY from a background process group. */
	E_IOERROR_REASON_NE2K_RESET_ACK,  /* E_IOERROR_TIMEOUT: Card didn't acknowledge reset command */
	E_IOERROR_REASON_NE2K_WAIT4RDMA,  /* E_IOERROR_TIMEOUT: Timeout while waiting for `ENISR_RDC' */
	E_IOERROR_REASON_NE2K_TXTSR,      /* E_IOERROR_ERRORBIT: [u8 tst = ENISR_*] Transmit error occurred. */
	E_IOERROR_REASON_NE2K_PACKETSIZE, /* E_IOERROR_BADBOUNDS: [size_t packet_size] Packet is too large */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define E_IOERROR_REASON_GENERIC         E_IOERROR_REASON_GENERIC         /* Generic error reason */
#define E_IOERROR_REASON_ATA_DCR_ERR     E_IOERROR_REASON_ATA_DCR_ERR     /* `ATA_DCR_ERR' was set */
#define E_IOERROR_REASON_ATA_DCR_DF      E_IOERROR_REASON_ATA_DCR_DF      /* `ATA_DCR_DF' was set */
#define E_IOERROR_REASON_ATA_DCR_ERR_DF  E_IOERROR_REASON_ATA_DCR_ERR_DF  /* `ATA_DCR_ERR' and `ATA_DCR_DF' were set */
#define E_IOERROR_REASON_ATA_DMA_ERR     E_IOERROR_REASON_ATA_DMA_ERR     /* `DMA_STATUS_FTRANSPORT_FAILURE' was set */
#define E_IOERROR_REASON_ATA_DCR_BSY     E_IOERROR_REASON_ATA_DCR_BSY     /* Timeout while waiting for `ATA_DCR_BSY' */
#define E_IOERROR_REASON_ATA_SECTOR_WAIT E_IOERROR_REASON_ATA_SECTOR_WAIT /* Timeout while waiting for sector data */
#define E_IOERROR_REASON_USB_SHORTPACKET E_IOERROR_REASON_USB_SHORTPACKET /* Short-packet-detect during a transfer without the `USB_TRANSFER_FLAG_SHORT' flag set. */
#define E_IOERROR_REASON_USB_TOOMANY     E_IOERROR_REASON_USB_TOOMANY     /* Too many devices connected (at most 126 (127-1) devices can be supported) */
#define E_IOERROR_REASON_UHCI_BADEP      E_IOERROR_REASON_UHCI_BADEP      /* A `uhci_qh::qh_ep' field contained a bad value `POINTER[2]' */
#define E_IOERROR_REASON_UHCI_TDCS       E_IOERROR_REASON_UHCI_TDCS       /* At least one of the error bits of `UHCI_TDCS_*' is set (POINTER[2] is the `td_cs' field) */
#define E_IOERROR_REASON_UHCI_INCOMPLETE E_IOERROR_REASON_UHCI_INCOMPLETE /* The `UHCI_TDCS_ACTIVE' bit got cleared without any apparent reason. */
#define E_IOERROR_REASON_TTY_SIGTTIN     E_IOERROR_REASON_TTY_SIGTTIN     /* E_IOERROR_NODATA: Attempted to read() a TTY from a background process group. */
#define E_IOERROR_REASON_TTY_SIGTTOU     E_IOERROR_REASON_TTY_SIGTTOU     /* E_IOERROR_NODATA: Attempted to write() a TTY from a background process group. */
#define E_IOERROR_REASON_NE2K_RESET_ACK  E_IOERROR_REASON_NE2K_RESET_ACK  /* E_IOERROR_TIMEOUT: Card didn't acknowledge reset command */
#define E_IOERROR_REASON_NE2K_WAIT4RDMA  E_IOERROR_REASON_NE2K_WAIT4RDMA  /* E_IOERROR_TIMEOUT: Timeout while waiting for `ENISR_RDC' */
#define E_IOERROR_REASON_NE2K_TXTSR      E_IOERROR_REASON_NE2K_TXTSR      /* E_IOERROR_ERRORBIT: [u8 tst = ENISR_*] Transmit error occurred. */
#define E_IOERROR_REASON_NE2K_PACKETSIZE E_IOERROR_REASON_NE2K_PACKETSIZE /* E_IOERROR_BADBOUNDS: [size_t packet_size] Packet is too large */
#else /* __COMPILER_PREFERR_ENUMS */
#define E_IOERROR_REASON_GENERIC         0  /* Generic error reason */
#define E_IOERROR_REASON_ATA_DCR_ERR     1  /* `ATA_DCR_ERR' was set */
#define E_IOERROR_REASON_ATA_DCR_DF      2  /* `ATA_DCR_DF' was set */
#define E_IOERROR_REASON_ATA_DCR_ERR_DF  3  /* `ATA_DCR_ERR' and `ATA_DCR_DF' were set */
#define E_IOERROR_REASON_ATA_DMA_ERR     4  /* `DMA_STATUS_FTRANSPORT_FAILURE' was set */
#define E_IOERROR_REASON_ATA_DCR_BSY     5  /* Timeout while waiting for `ATA_DCR_BSY' */
#define E_IOERROR_REASON_ATA_SECTOR_WAIT 6  /* Timeout while waiting for sector data */
#define E_IOERROR_REASON_USB_SHORTPACKET 7  /* Short-packet-detect during a transfer without the `USB_TRANSFER_FLAG_SHORT' flag set. */
#define E_IOERROR_REASON_USB_TOOMANY     8  /* Too many devices connected (at most 126 (127-1) devices can be supported) */
#define E_IOERROR_REASON_UHCI_BADEP      9  /* A `uhci_qh::qh_ep' field contained a bad value `POINTER[2]' */
#define E_IOERROR_REASON_UHCI_TDCS       10 /* At least one of the error bits of `UHCI_TDCS_*' is set (POINTER[2] is the `td_cs' field) */
#define E_IOERROR_REASON_UHCI_INCOMPLETE 11 /* The `UHCI_TDCS_ACTIVE' bit got cleared without any apparent reason. */
#define E_IOERROR_REASON_TTY_SIGTTIN     12 /* E_IOERROR_NODATA: Attempted to read() a TTY from a background process group. */
#define E_IOERROR_REASON_TTY_SIGTTOU     13 /* E_IOERROR_NODATA: Attempted to write() a TTY from a background process group. */
#define E_IOERROR_REASON_NE2K_RESET_ACK  14 /* E_IOERROR_TIMEOUT: Card didn't acknowledge reset command */
#define E_IOERROR_REASON_NE2K_WAIT4RDMA  15 /* E_IOERROR_TIMEOUT: Timeout while waiting for `ENISR_RDC' */
#define E_IOERROR_REASON_NE2K_TXTSR      16 /* E_IOERROR_ERRORBIT: [u8 tst = ENISR_*] Transmit error occurred. */
#define E_IOERROR_REASON_NE2K_PACKETSIZE 17 /* E_IOERROR_BADBOUNDS: [size_t packet_size] Packet is too large */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/


__DECL_END

#endif /* !_KOS_EXCEPT_REASON_IO_H */
