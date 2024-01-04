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
#ifndef GUARD_MODUSB_STORAGE_SCSI_H
#define GUARD_MODUSB_STORAGE_SCSI_H 1

#include <kernel/compiler.h>

#include <drivers/usb.h>
#include <kernel/fs/blkdev.h>
#include <kernel/types.h>

#include <kos/sched/shared-lock.h>

DECL_BEGIN


/* MassStorageSCSIDevice */
struct ms_scsi_device
#ifdef __cplusplus
	: blkdev
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct blkdev              msd_device;   /* The underlying block-device. */
#endif /* !__cplusplus */
	REF struct usb_controller *msd_ctrl;     /* [1..1][const] The associated USB controller. */
	REF struct usb_endpoint   *msd_endp_in;  /* [1..1][const] Input endpoint (for reading from the device) */
	REF struct usb_endpoint   *msd_endp_out; /* [1..1][const] Output endpoint (for writing to the device) */
	struct shared_lock         msd_lock;     /* Lock for reading/writing data */
	u32                        msd_tag;      /* [lock(msd_lock)] Next tag to-be used for I/O */
	u8                         msd_lun;      /* [const] Logical unit number (think of it as a drive selector). */
};


/* Helper macros for `struct ms_scsi_device::msd_lock' */
#define _ms_scsi_device_reap(self)      (void)0
#define ms_scsi_device_reap(self)       (void)0
#define ms_scsi_device_mustreap(self)   0
#define ms_scsi_device_tryacquire(self) shared_lock_tryacquire(&(self)->msd_lock)
#define ms_scsi_device_acquire(self)    shared_lock_acquire(&(self)->msd_lock)
#define ms_scsi_device_acquire_nx(self) shared_lock_acquire_nx(&(self)->msd_lock)
#define _ms_scsi_device_release(self)   shared_lock_release(&(self)->msd_lock)
#define ms_scsi_device_release(self)    (shared_lock_release(&(self)->msd_lock), ms_scsi_device_reap(self))
#define ms_scsi_device_acquired(self)   shared_lock_acquired(&(self)->msd_lock)
#define ms_scsi_device_available(self)  shared_lock_available(&(self)->msd_lock)

/* Probe for an SCSI device, and create the /dev file(s) if found. */
INTDEF bool KCALL
usb_scsi_create(struct usb_controller *__restrict self,
                struct usb_endpoint *__restrict in,
                struct usb_endpoint *__restrict out);



DECL_END

#endif /* !GUARD_MODUSB_STORAGE_SCSI_H */
