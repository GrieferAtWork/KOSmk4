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
#ifndef GUARD_MODUSB_STORAGE_SCSI_C
#define GUARD_MODUSB_STORAGE_SCSI_C 1
#define _GNU_SOURCE 1

#include "scsi.h"

#include <kernel/compiler.h>

#include <kernel/fs/blkdev.h>
#include <drivers/usb.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/iovec.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <hybrid/byteorder.h>
#include <hybrid/byteswap.h>
#include <hybrid/unaligned.h>

#include <hw/disk/scsi.h>
#include <hw/usb/usb.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

/* Execute `cmd' and read the result, returning the number of read bytes. */
PRIVATE size_t KCALL
usb_scsi_io(struct usb_controller *__restrict self,
            struct usb_endpoint *__restrict in,
            struct usb_endpoint *__restrict out, u8 lun,
            void const *__restrict cmd, u8 cmdlen,
            void *__restrict buf, u32 buflen) {
	struct scsi_cbw cbw;
	struct scsi_csw csw;
	struct usb_transfer req, resp, status;
	size_t result;
	assert(cmdlen <= sizeof(cbw.cbw_cb));

	/* Setup the command descriptor. */
	cbw.cbw_sig    = SCSI_CBW_SIG;
	cbw.cbw_tag    = 123;
	cbw.cbw_tx_len = buflen;
	cbw.cbw_dir    = SCSI_CBW_DIR_READ;
	cbw.cbw_lun    = lun;
	cbw.cbw_cb_len = cmdlen;
	bzero(mempcpy(cbw.cbw_cb, cmd, cmdlen),
	      sizeof(cbw.cbw_cb) - cmdlen);

	/* The initial command packet. */
	req.ut_endp   = out;
	req.ut_type   = USB_TRANSFER_TYPE_OUT;
	req.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	req.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	req.ut_buf    = &cbw;
	req.ut_buflen = sizeof(cbw);
	req.ut_next   = &resp;

	/* The response send by the device. */
	resp.ut_endp   = in;
	resp.ut_type   = USB_TRANSFER_TYPE_IN;
	resp.ut_flags  = USB_TRANSFER_FLAG_SHORT;
	resp.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	resp.ut_buf    = buf;
	resp.ut_buflen = buflen;
	resp.ut_next   = &status;

	/* Receive the status result.
	 * NOTE: This _has_ to be requested as a separate  packet.
	 *       It will not work if you just plug this at the end
	 *       of the `buf + buflen' */
	status.ut_endp   = in;
	status.ut_type   = USB_TRANSFER_TYPE_IN;
	status.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	status.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	status.ut_buf    = &csw;
	status.ut_buflen = sizeof(csw);
	status.ut_next   = NULL;

	/* Issue the command. */
	result = usb_controller_transfer_sync(self, &req);

	/* Subtract the sizes of the control blocks. */
	assert(result >= sizeof(cbw) + sizeof(csw));
	result -= sizeof(cbw) + sizeof(csw);

	/* TODO: These shouldn't be assertions, but THROW(E_IOERROR) */
	assert(csw.csw_sig == SCSI_CSW_SIG);
	assert(csw.csw_tag == cbw.cbw_tag);
	assert(csw.csw_residue == result - cbw.cbw_tx_len);
	assert(csw.csw_status == SCSI_CSW_STATUS_SUCCESS);

	return result;
}


PRIVATE NOBLOCK void
NOTHROW(KCALL ms_scsi_device_fini)(struct blkdev *__restrict self) {
	struct ms_scsi_device *me;
	me = (struct ms_scsi_device *)self;
	xdecref(me->msd_ctrl);
	xdecref(me->msd_endp_in);
	xdecref(me->msd_endp_out);
}


/* Perform an I/O operation
 * The caller must fill in:
 *  - tx->ut_buftyp
 *  - tx->ut_buflen
 *  - tx->ut_[v]buf[p]  (According to `ut_buftyp')
 * This function is allowed to modify `tx' however
 * it  pleases,  without  having  to  restore  it. */
PRIVATE NONNULL((1, 2, 6)) void KCALL
ms_scsi_doio(struct ms_scsi_device *__restrict self,
             struct usb_transfer *__restrict tx, bool is_write, size_t num_sectors,
             lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct scsi_cbw cbw;
	struct scsi_csw csw;
	struct usb_transfer req, status;
	assert(num_sectors * self->bd_sector_size == tx->ut_buflen);
#if __SIZEOF_POINTER__ > 8 /* TODO: Split into multiple commands */
	assert(tx->ut_buflen <= 0xffffffff);
#endif
	assert(num_sectors <= 0xffff); /* TODO: Split into multiple commands */

	/* Setup the command descriptor. */
	cbw.cbw_sig    = SCSI_CBW_SIG;
	cbw.cbw_tx_len = (u32)tx->ut_buflen;
	cbw.cbw_dir    = is_write ? SCSI_CBW_DIR_WRITE : SCSI_CBW_DIR_READ;
	cbw.cbw_lun    = self->msd_lun;

	/* Setup the command block. */
	cbw.cbw_cb_len = 10;
	/* TODO: Use higher-order read/write functions if available, and applicable. */
	cbw.cbw_cb[0]  = is_write ? SCSI_CMD_WRITE_10 : SCSI_CMD_READ_10;
	cbw.cbw_cb[1]  = self->msd_lun;
	UNALIGNED_SETBE32(cbw.cbw_cb + 2, (u32)addr);
	cbw.cbw_cb[6]  = 0;
	UNALIGNED_SETBE16(cbw.cbw_cb + 7, (u16)num_sectors);
	cbw.cbw_cb[9]  = 0;
	bzero(cbw.cbw_cb + 10, sizeof(cbw.cbw_cb) - 10);

	/* The initial command packet. */
	req.ut_endp   = self->msd_endp_out;
	req.ut_type   = USB_TRANSFER_TYPE_OUT;
	req.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	req.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	req.ut_buf    = &cbw;
	req.ut_buflen = sizeof(cbw);
	req.ut_next   = tx;

	/* The response send by the device / The payload send to the device. */
	tx->ut_endp   = is_write ? self->msd_endp_out : self->msd_endp_in;
	tx->ut_type   = is_write ? USB_TRANSFER_TYPE_OUT : USB_TRANSFER_TYPE_IN;
	tx->ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	tx->ut_next   = &status;

	/* Receive the status result.
	 * NOTE: This _has_ to be requested as a separate  packet.
	 *       It will not work if you just plug this at the end
	 *       of the `buf + buflen' */
	status.ut_endp   = self->msd_endp_in;
	status.ut_type   = USB_TRANSFER_TYPE_IN;
	status.ut_flags  = USB_TRANSFER_FLAG_NORMAL;
	status.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	status.ut_buf    = &csw;
	status.ut_buflen = sizeof(csw);
	status.ut_next   = NULL;

	/* TODO: Append another set of transaction for
	 *       querying errors via the sense command */

	{
		/* With all of the data  structures set up, acquire  a
		 * lock to the SCSI device and initiate the operation. */
		ms_scsi_device_acquire(self);
		RAII_FINALLY { ms_scsi_device_release(self); };
		cbw.cbw_tag = self->msd_tag++;

		/* TODO: Actually make this part  have ASYNC support by  creating
		 *       a  custom AIO protocol that wraps around the AIO used by
		 *       USB, containing the `csw' block, as well as allowing for
		 *       handling of whatever  kind of error  may be returned  by
		 *       the device.
		 *       Also note that if we do this, we should have the command
		 *       be followed by a secondary  command that calls to  SENSE
		 *       function in order to determine if errors occurred during
		 *       the transfer. */
		usb_controller_transfer_sync(self->msd_ctrl, &req);
	}
	aio_handle_init_noop(aio, AIO_COMPLETION_SUCCESS);
}


PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_read(struct blkdev *__restrict self,
             USER CHECKED void *dst, size_t num_sectors,
             lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_buf    = dst;
	ms_scsi_doio(me, &tx, false, num_sectors, addr, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_read_phys(struct blkdev *__restrict self,
                  physaddr_t dst, size_t num_sectors,
                  lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_PHYS;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_bufp   = dst;
	ms_scsi_doio(me, &tx, false, num_sectors, addr, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_readv(struct blkdev *__restrict self,
              struct iov_buffer *__restrict buf, size_t num_sectors,
              lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_VIRTVEC;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_vbuf   = buf;
	assert(iov_buffer_size(buf) == num_sectors * self->bd_sector_size);
	ms_scsi_doio(me, &tx, false, num_sectors, addr, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_readv_phys(struct blkdev *__restrict self,
                   struct iov_physbuffer *__restrict buf, size_t num_sectors,
                   lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_PHYSVEC;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_vbufp  = buf;
	assert(iov_physbuffer_size(buf) == num_sectors * self->bd_sector_size);
	ms_scsi_doio(me, &tx, false, num_sectors, addr, aio);
}


PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_write(struct blkdev *__restrict self,
              USER CHECKED void const *src, size_t num_sectors,
              lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_VIRT;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_buf    = (void *)src;
	ms_scsi_doio(me, &tx, true, num_sectors, addr, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_write_phys(struct blkdev *__restrict self,
                   physaddr_t src, size_t num_sectors,
                   lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_PHYS;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_bufp   = src;
	ms_scsi_doio(me, &tx, true, num_sectors, addr, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_writev(struct blkdev *__restrict self,
               struct iov_buffer *__restrict buf, size_t num_sectors,
               lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_VIRTVEC;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_vbuf   = buf;
	assert(iov_buffer_size(buf) == num_sectors * self->bd_sector_size);
	ms_scsi_doio(me, &tx, true, num_sectors, addr, aio);
}

PRIVATE NONNULL((1, 5)) void KCALL
ms_scsi_writev_phys(struct blkdev *__restrict self,
                    struct iov_physbuffer *__restrict buf, size_t num_sectors,
                    lba_t addr, /*out*/ struct aio_handle *__restrict aio)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct ms_scsi_device *me;
	struct usb_transfer tx;
	me = (struct ms_scsi_device *)self;
	tx.ut_buftyp = USB_TRANSFER_BUFTYP_PHYSVEC;
	tx.ut_buflen = num_sectors * self->bd_sector_size;
	tx.ut_vbufp  = buf;
	assert(iov_physbuffer_size(buf) == num_sectors * self->bd_sector_size);
	ms_scsi_doio(me, &tx, true, num_sectors, addr, aio);
}



/* Create an SCSI device */
PRIVATE bool KCALL
usb_scsi_create_lun(struct usb_controller *__restrict self,
                    struct usb_endpoint *__restrict in,
                    struct usb_endpoint *__restrict out,
                    u8 lun) {
	REF struct ms_scsi_device *result;
	byte_t cmd[10];
	struct scsi_capacity cap;
	size_t num_read;

	/* TODO: Keep  on issuing `SCSI_CMD_TEST_UNIT_READY' (with some timeout)
	 *       until the device indicates success, meaning that it is ready to
	 *       be used.
	 *       Before it does this, we're technically not allowed to issue any
	 *       other type of command. */

	bzero(cmd, sizeof(cmd));
	cmd[0] = SCSI_CMD_READ_CAPACITY;
	cmd[1] = lun << 5; /* Grub also does this, but calls it `GRUB_SCSI_LUN_SHIFT' */
	num_read = usb_scsi_io(self, in, out, lun,
	                       cmd, sizeof(cmd),
	                       &cap, sizeof(cap));
	if unlikely(num_read < sizeof(cap))
		return false; /* This really shouldn't happen... */

	if (cap.cap_sector_max == (__be32)0xffffffff) {
		/* TODO: Must use `SCSI_CMD_SAI_READ_CAPACITY_16' to get the real size! */
	}
	/* With the disk geometry all figured out, it's time to create the block device! */
	result = (REF struct ms_scsi_device *)block_device_alloc((size_t)BETOH32(cap.cap_sector_len),
	                                                         sizeof(struct ms_scsi_device));
	FINALLY_DECREF_UNLIKELY(result);
	result->bd_type.dt_fini = &ms_scsi_device_fini;

	/* Fill in SCSI->USB interface information. */
	result->msd_ctrl     = (REF struct usb_controller *)incref(self);
	result->msd_endp_in  = incref(in);
	result->msd_endp_out = incref(out);
	result->msd_lun      = lun;
	shared_lock_cinit(&result->msd_lock);
	assert(result->msd_tag == 0);

	/* Fill in missing capacity information. */
	result->bd_sector_count = (lba_t)(u32)BETOH32(cap.cap_sector_max) + 1;
	result->bd_total_bytes  = (pos_t)(result->bd_sector_count * result->bd_sector_size);

	/* Fill in I/O operators. */
	result->bd_type.dt_read        = &ms_scsi_read;
	result->bd_type.dt_read_phys   = &ms_scsi_read_phys;
	result->bd_type.dt_readv       = &ms_scsi_readv;
	result->bd_type.dt_readv_phys  = &ms_scsi_readv_phys;
	result->bd_type.dt_write       = &ms_scsi_write;
	result->bd_type.dt_write_phys  = &ms_scsi_write_phys;
	result->bd_type.dt_writev      = &ms_scsi_writev;
	result->bd_type.dt_writev_phys = &ms_scsi_writev_phys;

	{
		static int n = 0; /* TODO: better naming */
		sprintf(result->bd_name, "usbsd%c", 'a' + n++);
	}

	/* Register the new block-device */
	blkdev_register_auto(result);
	TRY {
		usb_register_blkdev(in->ue_interface->ui_device,
		                          result);
	} EXCEPT {
		blkdev_unregister(result);
		RETHROW();
	}

	/* Automatically scan for partition */
	blkdev_repart(result);
	return true;
}


/* Probe for an SCSI device, and create the /dev file(s) if found. */
INTERN bool KCALL
usb_scsi_create(struct usb_controller *__restrict self,
                struct usb_endpoint *__restrict in,
                struct usb_endpoint *__restrict out) {
	bool result;
	struct usb_request req;
	size_t buflen;
	u8 i, maxlun;
	printk(KERN_NOTICE "[usb-storage] SCSI mass storage device detected\n");

	/* Figure out the max LogicalUnitNumber
	 * >> http://www.shakthimaan.com/downloads/usb/usb-msc-0.2.pdf */
	assert(in->ue_interface == out->ue_interface);
	req.ur_reqtype = USB_REQUEST_RETYPE_DEST_INTF |
	                 USB_REQUEST_RETYPE_TYPE_CLS |
	                 USB_REQUEST_RETYPE_DIR_D2H;
	req.ur_request = SCSI_GET_MAX_LUN;
	req.ur_value   = 0;
	req.ur_index   = in->ue_interface->ui_intf;
	req.ur_length  = 1;
	buflen = usb_controller_request_sync(self, in->ue_interface, &req, &maxlun);
	if unlikely(!buflen) {
		printk(KERN_WARNING "[usb-storage] GET_MAX_LUN failed (assuming maxlun == 0)\n");
		maxlun = 0;
	}
	result = false;
	for (i = 0; i <= maxlun; ++i) {
		result |= usb_scsi_create_lun(self, in, out, i);
	}
	return result;
}



DECL_END

#endif /* !GUARD_MODUSB_STORAGE_SCSI_C */
