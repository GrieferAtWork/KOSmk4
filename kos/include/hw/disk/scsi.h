/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _HW_DISK_SCSI_H
#define _HW_DISK_SCSI_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>

#include <bits/types.h>

__DECL_BEGIN

/* Interface for SCSI-compliant, USB mass-storage devices. */

#define SCSI_GET_MAX_LUN 0xfe /* Get max logical unit number */

/* Signature for `ms_scsi_cbw::cbw_sig' */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define SCSI_CBW_SIG 0x43425355
#define SCSI_CSW_SIG 0x53425355
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define SCSI_CBW_SIG 0x55534243
#define SCSI_CSW_SIG 0x55534253
#endif /* __BYTE_ORDER__ == ... */

/* Values for `ms_scsi_cbw::cbw_dir' */
#define SCSI_CBW_DIR_WRITE 0x00 /* Write data to the device */
#define SCSI_CBW_DIR_READ  0x80 /* Read data from the device */

/* Command codes for SCSI */
#define SCSI_CMD_TEST_UNIT_READY    0x00
#define SCSI_CMD_READ_6             0x08
#define SCSI_CMD_WRITE_6            0x0a
#define SCSI_CMD_READ_CAPACITY      0x25
#define SCSI_CMD_READ_10            0x28
#define SCSI_CMD_WRITE_10           0x2a
#define SCSI_CMD_READ_12            0xa8
#define SCSI_CMD_WRITE_12           0xaa
#define SCSI_CMD_READ_16            0x88
#define SCSI_CMD_WRITE_16           0x8a
#define SCSI_CMD_SERVICE_ACTION_IN  0x9e
#define    SCSI_CMD_SAI_READ_CAPACITY_16 0x10


/* Values for `struct scsi_csw::csw_status' */
#define SCSI_CSW_STATUS_SUCCESS 0x00 /* Success */
#define SCSI_CSW_STATUS_FAILED  0x01 /* Failure */
#define SCSI_CSW_STATUS_PHASE   0x02 /* Phase error??? */


#ifdef __CC__
struct __ATTR_PACKED scsi_cbw {
	/* SCSI_CommandBlockWrapper */
	/* XXX: Explicitly  annotate  endian? (It  seems that  aside of
	 *      `cbw_cb', this structure is actually defined by USB...) */
	__uint32_t cbw_sig;     /* Signature (== SCSI_CBW_SIG) */
	__uint32_t cbw_tag;     /* Transaction Unique Identifier (used to identify a command and its response) */
	__uint32_t cbw_tx_len;  /* Transfer length (amount of data to read/write) */
	__uint8_t  cbw_dir;     /* Direction (One of `SCSI_CBW_DIR_*') */
	__uint8_t  cbw_lun;     /* Logical unit number */
	__uint8_t  cbw_cb_len;  /* command block length */
	__uint8_t  cbw_cb[16];  /* command block */
};

struct __ATTR_PACKED scsi_csw {
	/* SCSI_CommandStatusWrapper */
	__uint32_t csw_sig;     /* Signature (== SCSI_CSW_SIG) */
	__uint32_t csw_tag;     /* Echo of the tag given in `cbw_tag' */
	__uint32_t csw_residue; /* == cbw_tx_len - <ACTUAL_LENGTH> */
	__uint8_t  csw_status;  /* Status code (One of `SCSI_CSW_STATUS_*') */
};

struct __ATTR_PACKED scsi_capacity {
	/* Buffer returned by `SCSI_CMD_READ_CAPACITY' */
	__be32 cap_sector_max; /* Max valid sectors number. */
	__be32 cap_sector_len; /* Size of a single sector (in bytes). */
};
#endif /* __CC__ */

__DECL_END

#endif /* !_HW_DISK_SCSI_H */
