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
#ifndef _KOS_HOP_BLOCKDEVICE_H
#define _KOS_HOP_BLOCKDEVICE_H 1

#include "api.h"

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include "openfd.h"

__DECL_BEGIN

#ifndef BLOCK_DEVICE_FLAG_NORMAL
#define BLOCK_DEVICE_FLAG_NORMAL    0x0000 /* Normal block-device flags. */
#define BLOCK_DEVICE_FLAG_READONLY  0x0001 /* Read-only device / partition (attempting to write will cause `E_IOERROR_READONLY' to be thrown). */
#define BLOCK_DEVICE_FLAG_PARTITION 0x8000 /* [const] This one's a partition */
#endif /* !BLOCK_DEVICE_FLAG_NORMAL */

#define __OFFSET_HOP_BLOCKDEVICE_STAT_STRUCT_SIZE  0
#define __OFFSET_HOP_BLOCKDEVICE_STAT_TOTAL_BYTES  8
#define __OFFSET_HOP_BLOCKDEVICE_STAT_SECTOR_COUNT 16
#define __OFFSET_HOP_BLOCKDEVICE_STAT_SECTOR_SIZE  24
#define __OFFSET_HOP_BLOCKDEVICE_STAT_DEVICE_FLAG  32
#define __OFFSET_HOP_BLOCKDEVICE_STAT_PARTCOUNT    36
#define __OFFSET_HOP_BLOCKDEVICE_STAT_DEVNO        40
#define __OFFSET_HOP_BLOCKDEVICE_STAT_NAME         48
#define __SIZEOF_HOP_BLOCKDEVICE_STAT              128
#ifdef __CC__
struct hop_blockdevice_stat /*[PREFIX(bs_)]*/ {
	__uint32_t   bs_struct_size;   /* [== sizeof(struct hop_blockdevice_stat)]
	                                * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                * this value is too small or doesn't match any recognized
	                                * structure version. */
	__uint32_t __bs_pad;           /* ... */
	__uint64_t   bs_total_bytes;   /* Total number of bytes available. */
	__uint64_t   bs_sector_count;  /* Total number of sectors available. */
	__uint64_t   bs_sector_size;   /* Size of a single sector (in bytes). */
	__uint32_t   bs_device_flag;   /* Active device flags (Set of `BD_F*').
	                                * NOTE: If this device is a partition, the `BLOCK_DEVICE_FLAG_PARTITION' bit is set */
	__uint32_t   bs_partcount;     /* Number of child partitions of thsi block device. */
	__uint64_t   bs_devno;         /* Device number (`dev_t') */
	char         bs_name[80];      /* Name of the device (as used for the auto-node that may appear in `/dev') */
};
#endif /* __CC__ */

#define __OFFSET_HOP_BLOCKDEVICE_OPENPART_STRUCT_SIZE 0
#define __OFFSET_HOP_BLOCKDEVICE_OPENPART_PARTNO      4
#define __OFFSET_HOP_BLOCKDEVICE_OPENPART_OPENFD      8
#define __SIZEOF_HOP_BLOCKDEVICE_OPENPART             16
#ifdef __CC__
struct hop_blockdevice_openpart /*[PREFIX(bop_)]*/ {
	__uint32_t        bop_struct_size; /* [== sizeof(struct hop_blockdevice_openpart)]
	                                    * The kernel may throw an `E_BUFFER_TOO_SMALL' exception if
	                                    * this value is too small or doesn't match any recognized
	                                    * structure version. */
	__uint32_t        bop_partno;      /* Partition index. */
	struct hop_openfd bop_openfd;      /* File descriptor open controller. */
};
#endif /* __CC__ */


/* For `HANDLE_TYPE_BLOCKDEVICE' */
#define HOP_BLOCKDEVICE_STAT          0x00020001 /* [struct hop_blockdevice_stat *result] Read information about the datablock */
#define HOP_BLOCKDEVICE_SYNC          0x00020002 /* Write any modified, but unsaved sectors to disk. */
#define HOP_BLOCKDEVICE_RDREADONLY    0x00020003 /* @return: (0|1): Check if the given block-device is in read-only mode */
#define HOP_BLOCKDEVICE_WRREADONLY    0x00020004 /* [uint32_t enabled] Set the read-only mode for the given block-device.
                                                  * WARNING: Setting a drive root to read-only will prevent writes to partitions,
                                                  *          even though the partitions will continue to indicate being writable!
                                                  * To ensure that read-only is disabled for a partition & drive, do this:
                                                  * >> hop(fd, HOP_BLOCKDEVICE_WRREADONLY, 0);  // Drive
                                                  * >> struct hop_openfd root;
                                                  * >> root.of_mode  = HOP_OPENFD_MODE_AUTO;
                                                  * >> root.of_flags = 0;
                                                  * >> hop(fd, HOP_BLOCKDEVICE_OPENDRIVEROOT, &root);
                                                  * >> hop(root.of_hint, HOP_BLOCKDEVICE_WRREADONLY, 0);
                                                  * >> close(root.of_hint); */
#define HOP_BLOCKDEVICE_OPENDRIVEROOT 0x00020005 /* [struct hop_openfd *arg] Open the drive root of a partition, or re-open a partition.
                                                  * @return: == arg->of_hint
                                                  * @throw: E_INVALID_HANDLE_FILETYPE: The given handle wasn't a block-device. */
#define HOP_BLOCKDEVICE_OPENDRIVEPART 0x00020006 /* [struct hop_blockdevice_openpart *arg] Open a given partition.
                                                  * If the given handle already refers to a partition, open a sibling partition instead.
                                                  * @return: == arg->of_hint
                                                  * @throw: E_INVALID_HANDLE_FILETYPE:   The given handle wasn't a block-device.
                                                  * @throw: E_INDEX_ERROR_OUT_OF_BOUNDS: The given partition index is invalid. */


__DECL_END

#endif /* !_KOS_HOP_BLOCKDEVICE_H */
