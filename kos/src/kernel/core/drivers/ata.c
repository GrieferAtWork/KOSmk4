/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_DRIVERS_ATA_C
#define GUARD_KERNEL_CORE_DRIVERS_ATA_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <drivers/ata.h>
#include <drivers/pci.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/heap.h>
#include <kernel/interrupt.h>
#include <kernel/pic.h>
#include <kernel/printk.h>
#include <kernel/compat.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/user.h>
#include <kernel/driver-param.h>
#include <sched/cpu.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/byteorder.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/dev.h>
#include <kos/jiffies.h>
#include <sys/io.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <linux/hdreg.h>

DECL_BEGIN

#if 0
#define ATA_VERBOSE(...)  printk(KERN_DEBUG __VA_ARGS__)
#else
#define ATA_VERBOSE(...) (void)0
#endif


STATIC_ASSERT(sizeof(AtaAIOHandleData) <=
             (AIO_HANDLE_DRIVER_POINTER_COUNT * sizeof(void *)));

/* Initialize a given PRD from various sources.
 * NOTE: Upon successful completion of `AtaPRD_InitFromVirt' or `AtaPRD_InitFromVirtVector',
 *       either `ATA_AIO_HANDLE_FUNLOCK_USER_DMA' or `ATA_AIO_HANDLE_FUNLOCK_KERNEL_DMA' is
 *       added to `*pflags', and the caller is required to unlock the DMA lock of the associated
 *       VM upon completion of the operation.
 * @return: <= prd_siz: SUCCESS. In this case, the return value specifies the number of encoded
 *                     PRD entries, starting at `prd_buf'. Also note that in this case, the caller
 *                     will be required to eventually unlock VM DMA locks in accordance to the
 *                     bits set in `*pflags' if `AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector'
 *                     was called.
 * @return: > prd_siz: ERROR: More than `prd_siz' PRD entires would be required for the encoding
 *                     to succeed. - In this case, the caller should re-attempt the call after
 *                     re-allocating to match a total of at least `return' AtaPRD entries passed
 *                     to `prd_buf', and update `prd_siz' accordingly.
 * @return: 0 : ERROR: The given address range cannot be encoded as a valid PRD
 *                     This can happen for any of the following reasons:
 *                   - An `E_WOULDBLOCK' error was thrown internally (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - Some portion of the given address range(s) isn't mapped (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - Some portion of the given address range(s) maps to VIO memory (`AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector')
 *                   - A physical memory region is located beyond the 32-bit PRD limit and cannot be encoded */
struct ata_dma_acquire_data {
	AtaPRD *ad_base; /* [1..1][const] Pointer to the buffer start. */
	AtaPRD *ad_buf;  /* [1..1] Pointer to the next buffer. */
	size_t  ad_siz;  /* Number of remaining buffer entries. */
	size_t  ad_max;  /* Number of available buffer entries. */
};
PRIVATE NOBLOCK void
NOTHROW(KCALL ata_dma_reset_func)(void *arg) {
	struct ata_dma_acquire_data *data;
	data         = (struct ata_dma_acquire_data *)arg;
	data->ad_buf = data->ad_base;
	data->ad_siz = data->ad_max;
}
PRIVATE NOBLOCK bool
NOTHROW(KCALL ata_dma_acquire_func)(void *arg, vm_phys_t paddr, size_t num_bytes,
                                    struct vm_dmalock *__restrict UNUSED(lock) DFL(NULL)) {
	struct ata_dma_acquire_data *data;
	data = (struct ata_dma_acquire_data *)arg;
	assert(num_bytes != 0);
	assert((vm_phys_t)(paddr + num_bytes) > paddr);
	if ((paddr + num_bytes - 1) > (vm_phys_t)__UINT32_C(0xffffffff))
		return false; /* Cannot be encoded. */
	if ((paddr & 1) || (num_bytes & 1))
		return false; /* Cannot be encoded. */
	for (;;) {
		AtaPRD *ent = data->ad_buf++;
		if likely(data->ad_siz) {
			u16 max_addend;
			--data->ad_siz;
			if (ent > data->ad_base && ent[-1].p_bufsize != 0 &&
			    (ent[-1].p_bufaddr + ent[-1].p_bufsize) == (u32)paddr &&
			    ((ent[-1].p_bufaddr & 0xffff0000) == ((u32)paddr & 0xffff0000))) {
				++data->ad_siz;
				--data->ad_buf;
				max_addend = (u16)((u32)(0x10000 - (ent[-1].p_bufaddr & 0xffff)) - ent[-1].p_bufsize);
				assert(max_addend != 0);
				/* Add the remainder to the predecessor. */
				if (max_addend >= num_bytes) {
					ent[-1].p_bufsize += (u16)num_bytes;
					break;
				}
				ent[-1].p_bufsize += max_addend;
				num_bytes -= max_addend;
				paddr += max_addend;
				continue;
			}
			ent->p_bufaddr = (u32)paddr;
			max_addend     = (u16)(0x10000 - ((u32)paddr & 0xffff));
			if (!max_addend) {
				if (num_bytes <= 0x10000) {
					ent->p_bufsize = (u16)num_bytes;
					ent->p_flags   = PRD_FNORMAL;
					break;
				}
				ent->p_bufsize = 0; /* `0' is equal to `0x10000' */
				ent->p_flags   = PRD_FNORMAL;
				paddr += 0x10000;
				num_bytes -= 0x10000;
				continue;
			}
			if (max_addend >= num_bytes) {
				ent->p_bufsize = (u16)num_bytes;
				ent->p_flags   = PRD_FNORMAL;
				break;
			}
			ent->p_bufsize = max_addend;
			ent->p_flags   = PRD_FNORMAL;
			paddr += max_addend;
			num_bytes -= max_addend;
		} else {
			if (num_bytes <= 0xffff)
				break;
			num_bytes -= 0x10000;
		}
	}
	return true;
}



/* Same as the Phys functions above, however also initialize `handle->hd_dmalock' / `handle->hd_dmalockvec',
 * as well as setting the `ATA_AIO_HANDLE_FONEDMA' bit should this be required.
 * @param: for_writing: When true, the target buffer is intended to be
 *                      written to, else only intended to be read from. */
INTERN WUNUSED size_t KCALL
AtaPRD_InitFromVirt(AtaPRD *__restrict prd_buf, size_t prd_siz, vm_virt_t base,
                    size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct vm *effective_vm = &vm_kernel;
	struct ata_dma_acquire_data data;
	size_t req_locks, req_prd;
	if (ADDR_IS_USER(base))
		effective_vm = THIS_VM;
	data.ad_base = data.ad_buf = prd_buf;
	data.ad_siz = data.ad_max = prd_siz;
	/* Try to start DMAing within the given address range. */
	assert(handle != NULL);
	req_locks = vm_startdma(effective_vm,
	                        &ata_dma_acquire_func,
	                        &ata_dma_reset_func,
	                        &data,
	                        &handle->hd_dmalock,
	                        1,
	                        base,
	                        num_bytes,
	                        for_writing);
	if (!req_locks)
		return 0; /* Not encodeable as PRD physical memory. */
	req_prd = (size_t)(data.ad_buf - data.ad_base);
	assert(req_prd != 0);
	assertf(pagedir_translate(base) == (vm_phys_t)prd_buf->p_bufaddr,
	        "prd_buf->p_bufaddr      = %I64p\n"
	        "pagedir_translate(base) = %I64p\n",
	        (u64)prd_buf->p_bufaddr,
	        (u64)pagedir_translate(base));
	if (req_locks == 1) {
		/* Simple case: only a single lock is required! */
		if unlikely(req_prd > prd_siz) {
			/* Need more PRDs */
			vm_dmalock_release(&handle->hd_dmalock);
			return req_prd;
		}
		handle->hd_flags |= ATA_AIO_HANDLE_FONEDMA;
	} else {
		/* Complicated case: Need multiple DMA locks. */
		struct vm_dmalock *lockvec;
		size_t new_req_locks;
		assert(req_locks > 1);
		if unlikely(req_prd > prd_siz)
			return req_prd; /* Need more PRDs */
		lockvec = (struct vm_dmalock *)kmalloc((req_locks + 1) * sizeof(struct vm_dmalock),
		                                       GFP_LOCKED | GFP_PREFLT);
again_start_dma_lockvec:
		data.ad_base = data.ad_buf = prd_buf;
		data.ad_siz = data.ad_max = prd_siz;
		TRY {
			new_req_locks = vm_startdma(effective_vm,
			                            &ata_dma_acquire_func,
			                            &ata_dma_reset_func,
			                            &data,
			                            lockvec,
			                            req_locks,
			                            base,
			                            num_bytes,
			                            for_writing);
			if unlikely(new_req_locks > req_locks) {
				/* Need _even_ more DMA locks! */
				lockvec = (struct vm_dmalock *)krealloc(lockvec,
				                                        (new_req_locks + 1) * sizeof(struct vm_dmalock),
				                                        GFP_LOCKED | GFP_PREFLT);
				req_locks = new_req_locks;
				goto again_start_dma_lockvec;
			}
		} EXCEPT {
			kfree(lockvec);
			RETHROW();
		}
		req_prd = (size_t)(data.ad_buf - data.ad_base);
		if unlikely(req_prd > prd_siz) {
			/* Need more PRDs */
			vm_stopdma(lockvec, new_req_locks);
			kfree(lockvec);
			return req_prd;
		}
		if unlikely(new_req_locks < req_locks) {
			if unlikely(!new_req_locks) {
				/* No longer encodable. */
				kfree(lockvec);
				return 0;
			}
			if (new_req_locks == 1) {
				handle->hd_dmalock = lockvec[0];
				kfree(lockvec);
				handle->hd_flags |= ATA_AIO_HANDLE_FONEDMA;
			} else {
				struct vm_dmalock *newvec;
				newvec = (struct vm_dmalock *)krealloc_nx(lockvec,
				                                          (new_req_locks + 1) * sizeof(struct vm_dmalock),
				                                          GFP_LOCKED | GFP_PREFLT);
				if likely(newvec)
					lockvec = newvec;
				goto set_lock_vec;
			}
		} else {
set_lock_vec:
			assert(!(handle->hd_flags & ATA_AIO_HANDLE_FONEDMA));
			lockvec[new_req_locks].dl_part = NULL;    /* Sentinel */
			handle->hd_dmalockvec          = lockvec; /* Inherit vector, locks & references */
		}
	}
	assert(req_prd != 0);
	return req_prd;
}
INTERN WUNUSED size_t KCALL
AtaPRD_InitFromVirtVector(AtaPRD *__restrict prd_buf, size_t prd_siz, struct aio_buffer *__restrict buf,
                          size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct vm *effective_vm = &vm_kernel;
	struct ata_dma_acquire_data data;
	size_t req_locks, req_prd;
	if (ADDR_IS_USER(buf->ab_head.ab_base))
		effective_vm = THIS_VM;
	assert(num_bytes == aio_buffer_size(buf));
	data.ad_base = data.ad_buf = prd_buf;
	data.ad_siz = data.ad_max = prd_siz;
	/* Try to start DMAing within the given address range. */
	req_locks = vm_startdmav(effective_vm,
	                         &ata_dma_acquire_func,
	                         &ata_dma_reset_func,
	                         &data,
	                         &handle->hd_dmalock,
	                         1,
	                         buf,
	                         for_writing);
	if (!req_locks)
		return 0; /* Not encodeable as PRD physical memory. */
	req_prd = (size_t)(data.ad_buf - data.ad_base);
	assert(req_prd != 0);
	if (req_locks == 1) {
		/* Simple case: only a single lock is required! */
		if unlikely(req_prd > prd_siz) {
			/* Need more PRDs */
			vm_dmalock_release(&handle->hd_dmalock);
			return req_prd;
		}
		handle->hd_flags |= ATA_AIO_HANDLE_FONEDMA;
	} else {
		/* Complicated case: Need multiple DMA locks. */
		struct vm_dmalock *lockvec;
		size_t new_req_locks;
		assert(req_locks > 1);
		if unlikely(req_prd > prd_siz)
			return req_prd; /* Need more PRDs */
		lockvec = (struct vm_dmalock *)kmalloc((req_locks + 1) * sizeof(struct vm_dmalock),
		                                       GFP_LOCKED | GFP_PREFLT);
again_start_dma_lockvec:
		data.ad_base = data.ad_buf = prd_buf;
		data.ad_siz = data.ad_max = prd_siz;
		TRY {
			new_req_locks = vm_startdmav(effective_vm,
			                             &ata_dma_acquire_func,
			                             &ata_dma_reset_func,
			                             &data,
			                             lockvec,
			                             req_locks,
			                             buf,
			                             for_writing);
			if unlikely(new_req_locks > req_locks) {
				/* Need _even_ more DMA locks! */
				lockvec = (struct vm_dmalock *)krealloc(lockvec,
				                                        (new_req_locks + 1) * sizeof(struct vm_dmalock),
				                                        GFP_LOCKED | GFP_PREFLT);
				req_locks = new_req_locks;
				goto again_start_dma_lockvec;
			}
		} EXCEPT {
			kfree(lockvec);
			RETHROW();
		}
		req_prd = (size_t)(data.ad_buf - data.ad_base);
		if unlikely(req_prd > prd_siz) {
			/* Need more PRDs */
			vm_stopdma(lockvec, new_req_locks);
			kfree(lockvec);
			return req_prd;
		}
		if unlikely(new_req_locks < req_locks) {
			if unlikely(!new_req_locks) {
				/* No longer encodable. */
				kfree(lockvec);
				return 0;
			}
			if (new_req_locks == 1) {
				handle->hd_dmalock = lockvec[0];
				kfree(lockvec);
				handle->hd_flags |= ATA_AIO_HANDLE_FONEDMA;
			} else {
				struct vm_dmalock *newvec;
				newvec = (struct vm_dmalock *)krealloc_nx(lockvec,
				                                          (new_req_locks + 1) * sizeof(struct vm_dmalock),
				                                          GFP_LOCKED | GFP_PREFLT);
				if likely(newvec)
					lockvec = newvec;
				goto set_lock_vec;
			}
		} else {
set_lock_vec:
			assert(!(handle->hd_flags & ATA_AIO_HANDLE_FONEDMA));
			lockvec[new_req_locks].dl_part = NULL;    /* Sentinel */
			handle->hd_dmalockvec          = lockvec; /* Inherit vector, locks & references */
		}
	}
	assert(req_prd != 0);
	return req_prd;
}


INTERN WUNUSED size_t
NOTHROW(KCALL AtaPRD_InitFromPhys)(AtaPRD *__restrict prd_buf,
                                   size_t prd_siz,
                                   vm_phys_t base,
                                   size_t num_bytes) {
	ssize_t result;
	struct ata_dma_acquire_data data;
	data.ad_base = prd_buf;
	data.ad_buf = prd_buf;
	data.ad_siz = prd_siz;
	result = ata_dma_acquire_func(&data, base, num_bytes);
	if unlikely(result <= 0)
		result = 0;
	assert(!result || (size_t)result == (size_t)(data.ad_buf - prd_buf));
	return (size_t)result;
}

INTERN WUNUSED size_t
NOTHROW(KCALL AtaPRD_InitFromPhysVector)(AtaPRD *__restrict prd_buf,
                                         size_t prd_siz,
                                         struct aio_pbuffer *__restrict buf,
                                         size_t num_bytes) {
	struct aio_pbuffer_entry ent;
	struct ata_dma_acquire_data data;
	size_t result = 0;
	ssize_t temp;
	assert(aio_pbuffer_size(buf) == num_bytes);
	(void)num_bytes;
	data.ad_base = prd_buf;
	data.ad_buf = prd_buf;
	data.ad_siz = prd_siz;
	AIO_PBUFFER_FOREACH(ent, buf) {
		temp = ata_dma_acquire_func(&data,
		                            ent.ab_base,
		                            ent.ab_size);
		if unlikely(temp <= 0)
			goto err;
		result += (size_t)temp;
	}
	assert(result == (size_t)(data.ad_buf - prd_buf));
	return result;
err:
	return 0;
}



/* PIO-based data transfer helpers for passing data to/from an ATA drive. */
LOCAL error_code_t KCALL Ata_ReceiveDataSectors(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, USER CHECKED byte_t *buffer, u16 num_sectors);
LOCAL error_code_t KCALL Ata_ReceiveDataSectorsPhys(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, vm_phys_t buffer, u16 num_sectors);
LOCAL error_code_t KCALL Ata_ReceiveDataSectorsVector(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, struct aio_buffer *__restrict buffer, u16 num_sectors);
LOCAL error_code_t KCALL Ata_ReceiveDataSectorsVectorPhys(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, struct aio_pbuffer *__restrict buffer, u16 num_sectors);
LOCAL error_code_t KCALL Ata_TransmitDataSectors(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, USER CHECKED byte_t const *buffer, u16 num_sectors);
LOCAL error_code_t KCALL Ata_TransmitDataSectorsPhys(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, vm_phys_t buffer, u16 num_sectors);
LOCAL error_code_t KCALL Ata_TransmitDataSectorsVector(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, struct aio_buffer *__restrict buffer, u16 num_sectors);
LOCAL error_code_t KCALL Ata_TransmitDataSectorsVectorPhys(struct ata_bus *__restrict bus, struct ata_drive *__restrict drive, struct aio_pbuffer *__restrict buffer, u16 num_sectors);



/* ATA specifies a 400ns delay after drive switching,
 * often implemented as 4 Alternative Status queries.
 * XXX: This can probably be optimized away in certain
 *      cases where we don't have to wait, possibly
 *      by detecting modern hardware... */
#define ATA_SELECT_DELAY(ctrl) \
	(inb(ctrl), inb(ctrl), inb(ctrl), inb(ctrl))

PRIVATE NOBLOCK error_code_t
NOTHROW(KCALL Ata_WaitForBusy)(port_t ctrl) {
	u8 status;
	volatile unsigned int timeout;
	if (!(inb(ctrl) & ATA_DCR_BSY))
		return E_OK;
	/* XXX: this is _really_ unspecific. - It'd be better to use some kind of clock... */
	timeout = 0x10000000;
	while ((status = inb(ctrl)) & ATA_DCR_BSY) {
		if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
			return E_IOERROR_ERRORBIT;
		if unlikely(timeout--)
			return E_IOERROR_TIMEOUT;
		task_pause();
		io_delay();
	}
	return E_OK;
}


PRIVATE error_code_t
NOTHROW(KCALL Ata_WaitForBusyTimeout)(port_t ctrl) {
	u8 status;
	jtime_t abs_timeout;
	if (!(inb(ctrl) & ATA_DCR_BSY))
		return E_OK;
	abs_timeout = jiffies + JIFFIES_FROM_SECONDS(3);
	while ((status = inb(ctrl)) & ATA_DCR_BSY) {
		if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
			return E_IOERROR_ERRORBIT;
		if unlikely(jiffies >= abs_timeout)
			return E_IOERROR_TIMEOUT;
		task_tryyield_or_pause();
		io_delay();
	}
	return E_OK;
}

PRIVATE error_code_t
NOTHROW(KCALL Ata_WaitForDrq)(port_t bus, port_t ctrl) {
	u8 status;
	jtime_t abs_timeout;
	if (((status = inb(ctrl)) & ATA_DCR_BSY) == 0) {
		abs_timeout = jiffies + JIFFIES_FROM_SECONDS(3);
		while ((status = inb(ctrl)) & ATA_DCR_BSY) {
			if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
				return E_IOERROR_ERRORBIT;
			if unlikely(jiffies >= abs_timeout)
				return E_IOERROR_TIMEOUT;
			task_tryyield_or_pause();
			io_delay();
		}
	}
	if (status & (ATA_DCR_ERR | ATA_DCR_DF))
		return E_IOERROR_ERRORBIT;
	if (status & ATA_DCR_DRQ)
		return E_OK;
	abs_timeout = jiffies + JIFFIES_FROM_SECONDS(3);
	for (;;) {
		task_tryyield_or_pause();
		io_delay();
		status = inb(ctrl);
		if unlikely(status & (ATA_DCR_ERR | ATA_DCR_DF))
			return E_IOERROR_ERRORBIT;
		if unlikely(jiffies >= abs_timeout)
			return E_IOERROR_TIMEOUT;
		if (status & ATA_DCR_DRQ)
			break;
	}
	return E_OK;
}

PRIVATE NOBLOCK void
NOTHROW(KCALL Ata_ResetBus)(port_t ctrl) {
	outb(ctrl, ATA_CTRL_SRST);
	ATA_SELECT_DELAY(ctrl);
	outb(ctrl, 0);
	ATA_SELECT_DELAY(ctrl);
}



INTERN struct aio_handle_type Ata_DmaHandleType = {
	/* .ht_cancel   = */&Ata_CancelDmaHandle,
	/* .ht_progress = */&Ata_DmaHandleProgress
};

/* Signal the given ATA handle for completion
 * with `status', and perform associated operations. */
PRIVATE NOBLOCK void
NOTHROW(FCALL ata_dohandle_signal)(struct aio_handle *__restrict self,
                                   unsigned int status) {
	AtaAIOHandleData *data = (AtaAIOHandleData *)self->ah_data;
	assert(!(data->hd_flags & ~(ATA_AIO_HANDLE_FSINGLE |
	                            ATA_AIO_HANDLE_FWRITING |
	                            ATA_AIO_HANDLE_FSERVED |
	                            ATA_AIO_HANDLE_FONEDMA)));
	if (data->hd_flags & ATA_AIO_HANDLE_FONEDMA) {
		vm_dmalock_release(&data->hd_dmalock);
	} else if (data->hd_dmalockvec) {
		struct vm_dmalock *iter;
		for (iter = data->hd_dmalockvec; iter->dl_part; ++iter)
			vm_dmalock_release(iter);
		kfree(data->hd_dmalockvec);
	}
	if (!(data->hd_flags & ATA_AIO_HANDLE_FSINGLE))
		kfree(data->hd_prd_vector);
	(*self->ah_func)(self, status);
}
PRIVATE NOBLOCK void
NOTHROW(FCALL ata_handle_signal)(struct aio_handle *__restrict self,
                                 unsigned int status) {
	AtaAIOHandleData *data = (AtaAIOHandleData *)self->ah_data;
	if (!(ATOMIC_FETCHOR(data->hd_flags, ATA_AIO_HANDLE_FSERVED) & ATA_AIO_HANDLE_FSERVED))
		ata_dohandle_signal(self, status);
}


PRIVATE NOBLOCK ATTR_NOINLINE void
NOTHROW(FCALL handle_completion_ioerror)(struct aio_handle *__restrict self,
                                         uintptr_t error_code) {
	struct exception_data old_data;
	struct exception_data *mydata = &THIS_EXCEPTION_INFO.ei_data;
	memcpy(&old_data, mydata, sizeof(struct exception_data));
	memset(mydata, 0, sizeof(struct exception_data));
	mydata->e_code        = error_code;
	mydata->e_pointers[0] = E_IOERROR_SUBSYSTEM_HARDDISK;
	COMPILER_WRITE_BARRIER();
	ata_handle_signal(self, AIO_COMPLETION_FAILURE);
	COMPILER_WRITE_BARRIER();
	memcpy(mydata, &old_data, sizeof(struct exception_data));
}

PRIVATE NOBLOCK ATTR_NOINLINE void
NOTHROW(FCALL handle_completion_ioerror_generic)(struct aio_handle *__restrict self,
                                                 uintptr_t error_code) {
	struct exception_data old_data;
	struct exception_data *mydata = &THIS_EXCEPTION_INFO.ei_data;
	memcpy(&old_data, mydata, sizeof(struct exception_data));
	memset(mydata, 0, sizeof(struct exception_data));
	mydata->e_code        = error_code;
	mydata->e_pointers[0] = E_IOERROR_SUBSYSTEM_HARDDISK;
	COMPILER_WRITE_BARRIER();
	aio_handle_fail(self);
	COMPILER_WRITE_BARRIER();
	memcpy(mydata, &old_data, sizeof(struct exception_data));
}

STATIC_ASSERT(sizeof(AtaPRD) == SIZEOF_ATAPRD);

PRIVATE NOBLOCK bool
NOTHROW(FCALL dostart_dma_operation)(struct ata_bus *__restrict self,
                                     struct aio_handle *__restrict handle) {
	AtaAIOHandleData *data;
	error_code_t error;
	unsigned int reset_counter = 0;
	data                       = (AtaAIOHandleData *)handle->ah_data;
again:
	ATA_VERBOSE("[ata] Starting %s-DMA operation [lba=%I64u] [sector_count=%I16u] [prd0:%I32p+%I32u]\n",
	            data->hd_flags & ATA_AIO_HANDLE_FWRITING ? "Write" : "Read",
	            (u64)((u64)data->hd_io_lbaaddr[0] |
	                  (u64)data->hd_io_lbaaddr[1] << 8 |
	                  (u64)data->hd_io_lbaaddr[2] << 16 |
	                  (u64)data->hd_io_lbaaddr[3] << 24 |
	                  (u64)data->hd_io_lbaaddr[4] << 32 |
	                  (u64)data->hd_io_lbaaddr[5] << 40),
	            (u16)((u16)data->hd_io_sectors[0] |
	                  (u16)data->hd_io_sectors[1] << 8),
	            self->b_prdt[0].p_bufaddr,
	            self->b_prdt[0].p_bufsize
	            ? (u32)self->b_prdt[0].p_bufsize
	            : (u32)0x10000);
	assert(data->hd_drive->d_bus == self);
	assert(self->b_dmaio != (port_t)-1);
	assert(handle->ah_type == &Ata_DmaHandleType);
#if 0
	outl(self->b_dmaio + DMA_PRIMARY_PRDT,
	     (u32)pagedir_translate((vm_virt_t)self->b_prdt));
#endif
	outb(self->b_dmaio + DMA_PRIMARY_COMMAND,
	     data->hd_flags & ATA_AIO_HANDLE_FWRITING ? 0 : DMA_COMMAND_FREADMODE);
	outb(self->b_dmaio + DMA_PRIMARY_STATUS,
	     DMA_STATUS_FDMARUNNING |
	     DMA_STATUS_FTRANSPORT_FAILURE |
	     DMA_STATUS_FINTERRUPTED);
	error = Ata_WaitForBusy(self->b_ctrlio);
	if unlikely(error != E_OK)
		goto handle_io_error;
	if (data->hd_io_sectors[1] || (data->hd_io_lbaaddr[3] & 0xf0) ||
	    data->hd_io_lbaaddr[4] || data->hd_io_lbaaddr[5]) {
		assert(data->hd_drive->d_drive == ATA_DRIVE_MASTER ||
		       data->hd_drive->d_drive == ATA_DRIVE_SLAVE);
		outb(self->b_busio + ATA_DRIVE_SELECT, data->hd_drive->d_drive);
		ATA_SELECT_DELAY(self->b_ctrlio);
		outb(self->b_busio + ATA_SECTOR_COUNT, data->hd_io_sectors[1]);
		outb(self->b_busio + ATA_ADDRESS1, data->hd_io_lbaaddr[3]);
		outb(self->b_busio + ATA_ADDRESS2, data->hd_io_lbaaddr[4]);
		outb(self->b_busio + ATA_ADDRESS3, data->hd_io_lbaaddr[5]);
		outb(self->b_busio + ATA_SECTOR_COUNT, data->hd_io_sectors[0]);
		outb(self->b_busio + ATA_ADDRESS1, data->hd_io_lbaaddr[0]);
		outb(self->b_busio + ATA_ADDRESS2, data->hd_io_lbaaddr[1]);
		outb(self->b_busio + ATA_ADDRESS3, data->hd_io_lbaaddr[2]);
		if (data->hd_flags & ATA_AIO_HANDLE_FWRITING) {
			outb(self->b_busio + ATA_COMMAND, ATA_COMMAND_WRITE_DMA_EXT);
			error = Ata_WaitForBusy(self->b_ctrlio);
			if unlikely(error != E_OK)
				goto handle_io_error;
			ATA_VERBOSE("[ata] Switch to `ATA_BUS_STATE_INDMA' to start DMA (LBA48+WRITE)\n");
			ATOMIC_WRITE(self->b_state, ATA_BUS_STATE_INDMA);
			outb(self->b_dmaio + DMA_PRIMARY_COMMAND, DMA_COMMAND_FENABLED);
		} else {
			outb(self->b_busio + ATA_COMMAND, ATA_COMMAND_READ_DMA_EXT);
			error = Ata_WaitForBusy(self->b_ctrlio);
			if unlikely(error != E_OK)
				goto handle_io_error;
			ATA_VERBOSE("[ata] Switch to `ATA_BUS_STATE_INDMA' to start DMA (LBA48+READ)\n");
			ATOMIC_WRITE(self->b_state, ATA_BUS_STATE_INDMA);
			outb(self->b_dmaio + DMA_PRIMARY_COMMAND, DMA_COMMAND_FENABLED | DMA_COMMAND_FREADMODE);
		}
	} else {
		assert(data->hd_drive->d_drive == ATA_DRIVE_MASTER ||
		       data->hd_drive->d_drive == ATA_DRIVE_SLAVE);
		outb(self->b_busio + ATA_DRIVE_SELECT,
		     (0xe0 | (data->hd_drive->d_drive - ATA_DRIVE_MASTER)) |
		     (data->hd_io_lbaaddr[3] & 0xf));
		ATA_SELECT_DELAY(self->b_ctrlio);
		outb(self->b_busio + ATA_SECTOR_COUNT, data->hd_io_sectors[0]);
		outb(self->b_busio + ATA_ADDRESS1, data->hd_io_lbaaddr[0]);
		outb(self->b_busio + ATA_ADDRESS2, data->hd_io_lbaaddr[1]);
		outb(self->b_busio + ATA_ADDRESS3, data->hd_io_lbaaddr[2]);
		if (data->hd_flags & ATA_AIO_HANDLE_FWRITING) {
			outb(self->b_busio + ATA_COMMAND, ATA_COMMAND_WRITE_DMA);
			error = Ata_WaitForBusy(self->b_ctrlio);
			if unlikely(error != E_OK)
				goto handle_io_error;
			ATA_VERBOSE("[ata] Switch to `ATA_BUS_STATE_INDMA' to start DMA (LBA28+WRITE)\n");
			ATOMIC_WRITE(self->b_state, ATA_BUS_STATE_INDMA);
			outb(self->b_dmaio + DMA_PRIMARY_COMMAND, DMA_COMMAND_FENABLED);
		} else {
			outb(self->b_busio + ATA_COMMAND, ATA_COMMAND_READ_DMA);
			error = Ata_WaitForBusy(self->b_ctrlio);
			if unlikely(error != E_OK)
				goto handle_io_error;
			ATA_VERBOSE("[ata] Switch to `ATA_BUS_STATE_INDMA' to start DMA (LBA28+READ)\n");
			ATOMIC_WRITE(self->b_state, ATA_BUS_STATE_INDMA);
			outb(self->b_dmaio + DMA_PRIMARY_COMMAND, DMA_COMMAND_FENABLED | DMA_COMMAND_FREADMODE);
		}
	}
	/* At this point the DMA operation has started! */
	return true;
handle_io_error:
	/* Always reset the bus (even if merely done for the next access) */
	printk(KERN_ERR "[ata] Reseting IDE on DMA-I/O error code %#Ix (bus:%#I16x,ctrl:%#I16x,dma:%#I16x)\n",
	       error, self->b_busio, self->b_ctrlio, self->b_dmaio);
	Ata_ResetBus(self->b_ctrlio);
	{
		vm_phys_t phys;
		/* Re-set the PRDT address. */
		phys = pagedir_translate((vm_virt_t)self->b_prdt);
		assert(phys <= (vm_phys_t)0xffffffff);
		outl(self->b_dmaio + DMA_PRIMARY_PRDT, (u32)phys);
	}
	if (reset_counter < 3) { /* TODO: Make this `3' configurable */
		++reset_counter;
		goto again;
	}
	handle_completion_ioerror(handle, error);
	return false;
}


PRIVATE NOBLOCK bool
NOTHROW(FCALL start_dma_operation)(struct ata_bus *__restrict self,
                                   struct aio_handle *__restrict handle) {
	AtaAIOHandleData *data;
	data = (AtaAIOHandleData *)handle->ah_data;
	/* Copy the PRDT into the bus's buffer. */
	if (data->hd_flags & ATA_AIO_HANDLE_FSINGLE) {
		self->b_prdt[0].p_bufaddr = data->hd_prd0_bufaddr;
		self->b_prdt[0].p_bufsize = data->hd_prd0_bufsize;
		self->b_prdt[0].p_flags   = PRD_FLAST;
	} else {
		assert(data->hd_prd_count <= ATA_PRD_MAXCOUNT);
#if SIZEOF_ATAPRD == 8
		memcpyq(self->b_prdt,
		        data->hd_prd_vector,
		        data->hd_prd_count);
#else
		memcpy(self->b_prdt,
		       data->hd_prd_vector,
		       data->hd_prd_count *
		       sizeof(AtaPRD));
#endif
	}
	return dostart_dma_operation(self, handle);
}


PRIVATE NOBLOCK void
NOTHROW(FCALL ata_check_suspended_and_load_future)(struct ata_bus *__restrict self) {
	struct aio_handle *handle;
again:
	assert(self->b_state == ATA_BUS_STATE_INDMA_SWITCH);
	if (ATOMIC_READ(self->b_flags) & ATA_BUS_FSUSPEND) {
		ATA_VERBOSE("[ata] Switching `ATA_BUS_STATE_INDMA_SWITCH' -> `ATA_BUS_STATE_READY' "
		            "because of suspend request (bus:%#I16x,ctrl:%#I16x,dma:%#I16x)\n",
		            self->b_busio, self->b_ctrlio, self->b_dmaio);
		ATOMIC_WRITE(self->b_state, ATA_BUS_STATE_READY);
		sig_broadcast(&self->b_sigready);
		return;
	}
	/* Check for further pending DMA handles. */
	handle = ATOMIC_XCH(self->b_dma_future, NULL);
	if (handle) {
		/* Service additional requests. */
		struct aio_handle **hand_plast, *hand_last;
		assert(self->b_dmaio != (port_t)-1);

		for (hand_plast = &handle; (hand_last = *hand_plast)->ah_next;
		     hand_plast = &hand_last->ah_next)
			;
		*hand_plast = NULL;
		while (!ATOMIC_CMPXCH(self->b_dma_future, NULL, handle)) {
			struct aio_handle *more, *last;
			more = ATOMIC_XCH(self->b_dma_future, NULL);
			if likely(more) {
				/* Prepend additional requests before those that
				 * existed before we tried to remove the last one. */
				last = more;
				while (last->ah_next)
					last = last->ah_next;
				last->ah_next = handle;
				handle        = more;
			}
		}
		/* Service the first scheduled handle first
		 * (following first-come, first-serve ordering) */
		self->b_dma_current = handle = hand_last;
		/* Actually start this request!
		 * NOTE: If this fails, immediately switch to another operation! */
		if (!start_dma_operation(self, handle))
			goto again;
		ATA_VERBOSE("[ata] Chain-loaded secondary DMA command on bus:%#I16x,ctrl:%#I16x,dma:%#I16x\n",
		            self->b_busio, self->b_ctrlio, self->b_dmaio);
		return;
	}
	/* Nothing left for us to do! - Switch to READY mode. */
	ATA_VERBOSE("[ata] Switching `ATA_BUS_STATE_INDMA_SWITCH' -> `ATA_BUS_STATE_READY' because "
	            "there are no more DMA commands (bus:%#I16x,ctrl:%#I16x,dma:%#I16x)\n",
	            self->b_busio, self->b_ctrlio, self->b_dmaio);
	ATOMIC_WRITE(self->b_state, ATA_BUS_STATE_READY);
	sig_broadcast(&self->b_sigready);
	/* NOTE: Because new jobs may have been scheduled before
	 *       we switched to READY mode, we must check if there
	 *       are new jobs, and switch back to DMA mode if we've
	 *       allowed to do so! */
	COMPILER_BARRIER();
	if unlikely(ATOMIC_READ(self->b_dma_future) != NULL) {
		if (ATOMIC_CMPXCH(self->b_state,
		                  ATA_BUS_STATE_READY,
		                  ATA_BUS_STATE_INDMA_SWITCH))
			goto again;
	}
}

PRIVATE NOBLOCK bool
NOTHROW(FCALL handle_ata_bus_interrupt)(struct ata_bus *__restrict self) {
	u8 status, dma_status;
	if (self->b_dmaio != (port_t)-1) {
		dma_status = inb(self->b_dmaio + DMA_PRIMARY_STATUS);
		if (!(dma_status & DMA_STATUS_FINTERRUPTED))
			return false; /* This bus didn't assert an interrupt */
		outb(self->b_dmaio + DMA_PRIMARY_STATUS,
		     DMA_STATUS_FDMARUNNING |
		     DMA_STATUS_FINTERRUPTED);
		status = inb(self->b_busio + ATA_STATUS); /* Must always be read... */
		ATA_VERBOSE("[ata] IDE interrupt on bus:%#I16x,ctrl:%#I16x,dma:%#I16x [bus_status=0x%.2I8x,dma_status=0x%.2I8x]\n",
		            self->b_busio, self->b_ctrlio, self->b_dmaio, status, dma_status);
again_readstate:
		switch (ATOMIC_READ(self->b_state)) {

		case ATA_BUS_STATE_INDMA_CANCEL:
			/* A DMA operation is being canceled. - Somewhere else, someone is trying
			 * to stop this DMA operation, meaning we mustn't handle this interrupt! */
			ATA_VERBOSE("[ata] IDE interrupt on bus:%#I16x,ctrl:%#I16x,dma:%#I16x during `ATA_BUS_STATE_INDMA_CANCEL'\n",
			            self->b_busio, self->b_ctrlio, self->b_dmaio);
			ATOMIC_WRITE(self->b_cancel_intr_dma_status, dma_status);
			ATOMIC_WRITE(self->b_cancel_intr_bus_status, status);
			if (!ATOMIC_CMPXCH_WEAK(self->b_state,
			                        ATA_BUS_STATE_INDMA_CANCEL,
			                        ATA_BUS_STATE_INDMA_CANCEL_INTR))
				goto again_readstate;
			return true;

		case ATA_BUS_STATE_INDMA: {
			struct aio_handle *handle;
			/* A DMA operation has been completed.
			 * -> Try to change to the DMA-transition state, so we can acknowledge
			 *    its completion, and check if there are further pending operations
			 *    which we are to service next. */
			if (!ATOMIC_CMPXCH_WEAK(self->b_state,
			                        ATA_BUS_STATE_INDMA,
			                        ATA_BUS_STATE_INDMA_SWITCH))
				goto again_readstate;
			handle = self->b_dma_current;
			assert(handle);
			if (dma_status & DMA_STATUS_FTRANSPORT_FAILURE) {
				handle_completion_ioerror(handle, ERROR_CODEOF(E_IOERROR_ERRORBIT));
			} else {
				/* Indicate a successful completion of the data transfer */
				ATA_VERBOSE("[ata] Signal DMA success on bus:%#I16x,ctrl:%#I16x,dma:%#I16x\n",
				            self->b_busio, self->b_ctrlio, self->b_dmaio);
				ata_handle_signal(handle, AIO_COMPLETION_SUCCESS);
			}
			/* Check if we're supposed to suspend operations. */
			ata_check_suspended_and_load_future(self);
		}	break;

		case ATA_BUS_STATE_INPIO:
			/* Broadcast the bus status. */
			if (!sig_altbroadcast(&self->b_piointr, ATA_PIOINTR_ALT_ENCODE(status)))
				goto err_unexpected_interrupt;
			break;

		default:
			printk(KERN_WARNING "[ata] Bus in unexpected state %I16u\n",
			       (u16)ATOMIC_READ(self->b_state));
			goto err_unexpected_interrupt;
		}
	} else {
		/* BUS without DMA support */
		status = inb(self->b_busio + ATA_STATUS);
		ATA_VERBOSE("[ata] IDE interrupt on bus:%#I16x,ctrl:%#I16x,dma:%#I16x [bus_status=0x%.2I8x]\n",
		            self->b_busio, self->b_ctrlio, self->b_dmaio, status);
		switch (ATOMIC_READ(self->b_state)) {

		case ATA_BUS_STATE_INPIO:
			/* Broadcast the  */
			if (!sig_altbroadcast(&self->b_piointr, ATA_PIOINTR_ALT_ENCODE(status)))
				goto err_unexpected_interrupt;
			break;

		default: goto err_unexpected_interrupt;
		}
	}
	return true;
err_unexpected_interrupt:
	printk(KERN_WARNING "[ata] Unexpected IDE interrupt (bus:%#I16x,ctrl:%#I16x,dma:%#I16x)\n",
	       self->b_busio, self->b_ctrlio, self->b_dmaio);
	return true;
}


INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL Ata_CancelDmaHandle)(struct aio_handle *__restrict self) {
	struct ata_bus *bus;
	AtaAIOHandleData *data = (AtaAIOHandleData *)self->ah_data;
	assert(self->ah_type == &Ata_DmaHandleType);
	if (ATOMIC_FETCHOR(data->hd_flags, ATA_AIO_HANDLE_FSERVED) & ATA_AIO_HANDLE_FSERVED)
		return; /* Handle was already serviced! */
	/* The handle is _definitely_ going to get canceled! */
	bus = data->hd_drive->d_bus;
again_cancel:
	if (ATOMIC_READ(bus->b_dma_current) == self) {
		uintptr_t state;
		/* It's the currently active handle! */
		do {
			state = ATOMIC_READ(bus->b_state);
			/* Check for case: another CPU is currently handling an interrupt
			 *                 that caused the handle we're trying to cancel,
			 *                 or another handle that came there-after to be
			 *                 serviced, and is currently switching to start
			 *                 execution of that handle. */
			if (state == ATA_BUS_STATE_INDMA_SWITCH) {
				task_pause();
				continue;
			}
			/* Check for case: The DMA completed before we got here. */
			if (state != ATA_BUS_STATE_INDMA)
				goto done;
			/* Switch states to cancel the currently active DMA operation! */
		} while (!ATOMIC_CMPXCH_WEAK(bus->b_state,
		                             ATA_BUS_STATE_INDMA,
		                             ATA_BUS_STATE_INDMA_CANCEL));
		COMPILER_READ_BARRIER();
		/* Check to ensure that it's still our handle that is active. */
		if unlikely(ATOMIC_READ(bus->b_dma_current) != self) {
			struct aio_handle *completed_handle;
			/* Crap! - Don't interrupt this one! */
			if (ATOMIC_CMPXCH(bus->b_state,
			                  ATA_BUS_STATE_INDMA_CANCEL,
			                  ATA_BUS_STATE_INDMA))
				goto done;
			assert(bus->b_state == ATA_BUS_STATE_INDMA_CANCEL_INTR);
			/* Well crap. - Now we have to do what we prevented the interrupt handler
			 * from doing, and continue execution with the next pending DMA operation.
			 * NOTE: The interrupt that just happened was the one that signified
			 *       the completion of the DMA operation we were trying to cancel.
			 *       However, since we already set the SERVICED bit, we are still
			 *       going to report a canceled operation, as that is what the caller
			 *       wants us to do. */
			ATOMIC_WRITE(bus->b_state, ATA_BUS_STATE_INDMA_SWITCH);
			completed_handle = bus->b_dma_current;
			assert(completed_handle);
			/* Report the completion status to the accidentally canceled handle. */
			if (bus->b_cancel_intr_dma_status & DMA_STATUS_FTRANSPORT_FAILURE) {
				handle_completion_ioerror(completed_handle, ERROR_CODEOF(E_IOERROR_ERRORBIT));
			} else {
				/* Indicate a successful completion of the data transfer */
				ata_handle_signal(completed_handle, AIO_COMPLETION_SUCCESS);
			}
		} else {
			/* The operation we're trying to cancel is running _RIGHT_ now. - Tell the ATA
			 * drive to stop DMA-ing, so we can switch execution to the next pending return
			 * DMA operation, and indicate to the caller that the operation was successfully
			 * canceled. */
			ATA_VERBOSE("[ata] Cancel active DMA on IDE (bus:%#I16x,ctrl:%#I16x,dma:%#I16x)\n",
			            bus->b_busio, bus->b_ctrlio, bus->b_dmaio);
			do {
				outb(bus->b_dmaio + DMA_PRIMARY_COMMAND, 0);
			} while (inb(bus->b_dmaio + DMA_PRIMARY_STATUS) & DMA_STATUS_FDMARUNNING);
			/* Enter DMA-switch mode, so we can check for pending commands below. */
			ATOMIC_WRITE(bus->b_state, ATA_BUS_STATE_INDMA_SWITCH);
		}
		/* Always check for further pending DMA commands. */
		ata_check_suspended_and_load_future(bus);
	} else {
		/* Try to remove the given handle from the bus's chain of pending DMA commands. */
		struct aio_handle *pending, **piter, *iter;
		pflag_t was;
		bool did_find;
		if (ATOMIC_CMPXCH(bus->b_dma_future,
		                  self,
		                  self->ah_next))
			goto done; /* Simple case: no need to fuss about. */
		/* Disable preemption, so we don't run into problems with different threads
		 * trying to cancel AIO operations when a single thread has been preempted
		 * while having XCH-NULL'ed the chain for everyone. */
		did_find = false;
		was      = PREEMPTION_PUSHOFF();
		pending  = ATOMIC_XCH(bus->b_dma_future, NULL);
		/* Search though the chain of pending AIO handles to try and remove ours.
		 * NOTE: If our's isn't apart of the chain, we must assume that `b_dma_future'
		 *       is incomplete, either due to the ATA interrupt handler, or another CPU
		 *       having XCH-NULL'ed the chain just like we did. */
		piter = &pending;
		for (; (iter = *piter) != NULL; piter = &iter->ah_next) {
			if (iter != self)
				continue;
			did_find = true;
			*piter   = iter->ah_next;
			break;
		}
		/* Restore the remaining chain. */
		if (pending) {
restore_pending:
			if (ATOMIC_CMPXCH(bus->b_dma_future, NULL, pending)) {
				union ata_bus_state_and_flags state;
				union ata_bus_state_and_flags newstate;
				PREEMPTION_POP(was);
				/* Check if we must switch from `ATA_BUS_STATE_READY' to `ATA_BUS_STATE_INDMA',
				 * now that we've added additional pending DMA commands to the bus. */
				for (;;) {
					COMPILER_READ_BARRIER();
					state = *ATA_BUSATA_BUS_STATE_AND_FLAGS(bus);
					if (state.b_state != ATA_BUS_STATE_READY)
						break; /* Only start DMAing when the bus is in its ready state */
					if (state.b_flags & ATA_BUS_FSUSPEND)
						break; /* Don't start DMAing when the bus is being suspended */
					newstate.b_state = ATA_BUS_STATE_INDMA_SWITCH;
					newstate.b_flags = state.b_flags;
					if (!ATOMIC_CMPXCH_WEAK(*(uintptr_t *)ATA_BUSATA_BUS_STATE_AND_FLAGS(bus),
					                        state.b_word, newstate.b_word))
						continue;
					ata_check_suspended_and_load_future(bus);
					break;
				}
				goto check_did_find;
			} else {
				/* Search the new chain part, then combine and try to restore again. */
				struct aio_handle *more;
				more  = ATOMIC_XCH(bus->b_dma_future, NULL);
				piter = &more;
				/* Only search the new part of the pending chain. */
				for (; (iter = *piter) != NULL; piter = &iter->ah_next) {
					if (iter != self)
						continue;
					assert(!did_find);
					did_find = true;
					*piter   = iter->ah_next;
					break;
				}
				/* Concat the chains. */
				*piter  = pending;
				pending = more;
				/* Restore the combined chain of pending AIO operations. */
				goto restore_pending;
			}
		}
		PREEMPTION_POP(was);
check_did_find:
		if (!did_find) {
			task_pause();
			goto again_cancel;
		}
	}
done:
	ata_dohandle_signal(self, AIO_COMPLETION_CANCEL);
}

INTERN NOBLOCK NONNULL((1)) unsigned int
NOTHROW(KCALL Ata_DmaHandleProgress)(struct aio_handle *__restrict self,
                                     struct aio_handle_stat *__restrict stat) {
	AtaAIOHandleData *data = (AtaAIOHandleData *)self->ah_data;
	struct ata_bus *bus;
	assert(self->ah_type == &Ata_DmaHandleType);
	stat->hs_total = ((size_t)data->hd_io_sectors[0] |
	                  (size_t)data->hd_io_sectors[1]) *
	                 ATA_SECTOR_SIZE(data->hd_drive);
	bus = data->hd_drive->d_bus;
	if (ATOMIC_READ(bus->b_dma_current) == self) {
		/* XXX: Is there some way of determining how far along a DMA operation has come? */
		stat->hs_completed = stat->hs_total / 2;
		if (ATOMIC_READ(bus->b_dma_current) == self)
			return AIO_PROGRESS_STATUS_INPROGRESS;
	}
	if (data->hd_flags & ATA_AIO_HANDLE_FSERVED) {
		stat->hs_completed = stat->hs_total;
		return AIO_PROGRESS_STATUS_COMPLETED;
	}
	stat->hs_completed = 0;
	return AIO_PROGRESS_STATUS_PENDING;
}



INTERN void KCALL
AtaBus_LockPIO(struct ata_bus *__restrict self) THROWS(E_WOULDBLOCK,...) {
	union ata_bus_state_and_flags state, newstate;
	assert(!task_isconnected());
	for (;;) {
		COMPILER_READ_BARRIER();
		state = *ATA_BUSATA_BUS_STATE_AND_FLAGS(self);
		if (state.b_state == ATA_BUS_STATE_READY &&
		    (state.b_flags & ATA_BUS_FSUSPEND) == 0) {
			/* The bus is available. - immediately try to switch to PIO mode.
			 * NOTE: Technically, we could always do this when the state is `ATA_BUS_STATE_READY',
			 *       regardless of the bus suspension counter. - However in the interest of keeping
			 *       bus access fair, don't take the chance of access away from other threads which
			 *       may intend on accessing the bus as well. */
			if (ATOMIC_CMPXCH_WEAK(self->b_state,
			                       ATA_BUS_STATE_READY,
			                       ATA_BUS_STATE_INPIO))
				return;
			continue;
		}
		if unlikely((state.b_flags & ATA_BUS_FSUSPEND) == ATA_BUS_FSUSPEND) {
			/* No more wait-slots. - wait for some to become available. */
			task_connect(&self->b_sigready);
			if unlikely((ATOMIC_READ(self->b_flags) & ATA_BUS_FSUSPEND) != ATA_BUS_FSUSPEND) {
				task_disconnectall();
				continue;
			}
			task_waitfor();
			continue;
		}
		newstate.b_flags = state.b_flags + 1; /* +1 more thread waiting for suspension */
		newstate.b_state = state.b_state;
		if (ATOMIC_CMPXCH_WEAK(*(uintptr_t *)ATA_BUSATA_BUS_STATE_AND_FLAGS(self),
		                       state.b_word, newstate.b_word))
			break;
	}
	TRY {
		/* The suspension request was made. - Now to wait for the bus to switch to ready-mode. */
		for (;;) {
			task_connect(&self->b_sigready);
			if unlikely(ATOMIC_CMPXCH(self->b_state, ATA_BUS_STATE_READY, ATA_BUS_STATE_INPIO)) {
				task_disconnectall();
				break;
			}
			task_waitfor();
			if (ATOMIC_CMPXCH(self->b_state, ATA_BUS_STATE_READY, ATA_BUS_STATE_INPIO))
				break;
		}
	} EXCEPT {
		/* Drop 1 from the suspend-requested counter. */
		for (;;) {
			state = *ATA_BUSATA_BUS_STATE_AND_FLAGS(self);
			assert((state.b_flags & ATA_BUS_FSUSPEND) != 0);
			newstate = state;
			--newstate.b_flags;
			/* In the unlikely case in the bus complying to our suspension request
			 * just as we are being interrupted, continue execution of the bus by
			 * serving additional DMA commands. */
			if (newstate.b_state == ATA_BUS_STATE_READY &&
			    (newstate.b_flags & ATA_BUS_FSUSPEND) == 0) {
				newstate.b_state = ATA_BUS_STATE_INDMA_SWITCH;
				if (!ATOMIC_CMPXCH_WEAK(*(uintptr_t *)ATA_BUSATA_BUS_STATE_AND_FLAGS(self),
				                        state.b_word, newstate.b_word))
					continue;
				ata_check_suspended_and_load_future(self);
				break;
			}
			if (ATOMIC_CMPXCH_WEAK(*(uintptr_t *)ATA_BUSATA_BUS_STATE_AND_FLAGS(self),
			                       state.b_word, newstate.b_word))
				break;
		}
		RETHROW();
	}
	/* Remove the suspension request which was made above in
	 * order to try and get the bus to stop DMAing, so we can
	 * get PIO access (which we now have). */
	ATOMIC_FETCHDEC(self->b_flags);
}


INTERN NOBLOCK void
NOTHROW(KCALL AtaBus_UnlockPIO)(struct ata_bus *__restrict self) {
	union ata_bus_state_and_flags state, newstate;
	for (;;) {
		COMPILER_READ_BARRIER();
		state = *ATA_BUSATA_BUS_STATE_AND_FLAGS(self);
		newstate.b_flags = state.b_flags;
		newstate.b_state = ATA_BUS_STATE_READY;
		if (ATOMIC_READ(self->b_dma_future) && !(state.b_flags & ATA_BUS_FSUSPEND))
			newstate.b_state = ATA_BUS_STATE_INDMA_SWITCH;
		if (ATOMIC_CMPXCH_WEAK(*(uintptr_t *)ATA_BUSATA_BUS_STATE_AND_FLAGS(self),
		                       state.b_word, newstate.b_word))
			break;
	}
	/* When transitioning into DMA-switch mode, try to start pending operations. */
	if (newstate.b_state == ATA_BUS_STATE_INDMA_SWITCH)
		ata_check_suspended_and_load_future(self);
	else {
		sig_broadcast(&self->b_sigready);
	}
}


PRIVATE NOBLOCK void
NOTHROW(KCALL Ata_ResetAndReinitializeBus)(struct ata_bus *__restrict self) {
	Ata_ResetBus(self->b_ctrlio);
	if (self->b_dmaio != (port_t)-1) {
		vm_phys_t phys;
		/* Re-set the PRDT address. */
		phys = pagedir_translate((vm_virt_t)self->b_prdt);
		assert(phys <= (vm_phys_t)0xffffffff);
		outl(self->b_dmaio + DMA_PRIMARY_PRDT, (u32)phys);
	}
}

LOCAL pos_t KCALL Ata_GetPartitionStart(struct block_device *__restrict self) {
	if (!block_device_ispartition(self))
		return 0;
	return ((struct block_device_partition *)self)->bp_minaddr;
}

INTERN NONNULL((1)) syscall_slong_t KCALL
Ata_Ioctl(struct ata_drive *__restrict self,
          struct block_device *__restrict partition,
          syscall_ulong_t cmd, USER UNCHECKED void *arg,
          iomode_t mode) THROWS(...) {
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
		data->heads     = self->d_chs_number_of_heads;
		data->cylinders = self->d_chs_cylinders;
		data->sectors   = self->d_chs_sectors_per_track;
		data->start     = (__ULONGPTR_TYPE__)Ata_GetPartitionStart(partition);
		COMPILER_WRITE_BARRIER();
	}	break;

#ifdef __ARCH_HAVE_COMPAT
	case _IOR(_IOC_TYPE(HDIO_GETGEO), _IOC_NR(HDIO_GETGEO), struct hd_geometry_compat): {
		struct hd_geometry_compat *data;
do_compat_hdio_getgeo:
		validate_writable(arg, sizeof(struct hd_geometry_compat));
		data = (struct hd_geometry_compat *)arg;
		COMPILER_WRITE_BARRIER();
		data->heads     = self->d_chs_number_of_heads;
		data->cylinders = self->d_chs_cylinders;
		data->sectors   = self->d_chs_sectors_per_track;
		data->start     = (__ARCH_COMPAT_LONGPTR_TYPE)Ata_GetPartitionStart(partition);
		COMPILER_WRITE_BARRIER();
	}	break;
#endif /* __ARCH_HAVE_COMPAT */

	case HDIO_GET_IDENTITY:
	case _IOR(_IOC_TYPE(HDIO_GET_IDENTITY), _IOC_NR(HDIO_GET_IDENTITY), struct hd_driveid): {
		struct hd_driveid specs;
		struct ata_bus *bus;
		validate_writable(arg, sizeof(specs));
		bus = self->d_bus;
		AtaBus_LockPIO(bus);
		TRY {
			struct sig *signal;
			task_connect(&bus->b_piointr);
			outb(bus->b_busio + ATA_FEATURES, 1); /* ??? */
			outb(bus->b_busio + ATA_COMMAND, ATA_COMMAND_IDENTIFY);
			ATA_SELECT_DELAY(bus->b_ctrlio);
			if ((signal = task_trywait()) == NULL) {
				qtime_t timeout;
				timeout = quantum_time();
				timeout.add_seconds(2);
				signal = task_waitfor(&timeout);
				if (!signal)
					THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HARDDISK);
			}
			if (Ata_WaitForDrq(bus->b_busio, bus->b_ctrlio) != E_OK)
				THROW(E_IOERROR_TIMEOUT, E_IOERROR_SUBSYSTEM_HARDDISK);
			insw(bus->b_busio + ATA_DATA, &specs, 256);
			outb(bus->b_busio + ATA_FEATURES, 0); /* ??? */
		} EXCEPT {
			AtaBus_UnlockPIO(self->d_bus);
			RETHROW();
		}
		AtaBus_UnlockPIO(self->d_bus);
		COMPILER_WRITE_BARRIER();
		memcpy(arg, &specs, sizeof(specs));
		COMPILER_WRITE_BARRIER();
	}	break;

	case HDIO_GET_DMA:
	case _IOR(_IOC_TYPE(HDIO_GET_DMA), _IOC_NR(HDIO_GET_DMA), int): {
		validate_writable(arg, sizeof(int));
		COMPILER_WRITE_BARRIER();
		*(int *)arg = ((void *)self->bd_type.dt_read == (void *)&Ata_DmaDriveRead) ? 1 : 0;
		COMPILER_WRITE_BARRIER();
	}	break;

	case HDIO_GET_WCACHE:
	case _IOR(_IOC_TYPE(HDIO_GET_WCACHE), _IOC_NR(HDIO_GET_WCACHE), int): {
		validate_writable(arg, sizeof(int));
		COMPILER_WRITE_BARRIER();
		*(int *)arg = (self->d_features & ATA_DRIVE_FEATURE_FFLUSH) ? 1 : 0;
		COMPILER_WRITE_BARRIER();
	}	break;

	case HDIO_SET_WCACHE:
	case _IOW(_IOC_TYPE(HDIO_SET_WCACHE), _IOC_NR(HDIO_SET_WCACHE), int): {
		int mode;
		validate_readable(arg, sizeof(int));
		COMPILER_READ_BARRIER();
		mode = *(int *)arg;
		COMPILER_READ_BARRIER();
		if (mode) {
			/* WARNING: The drive may not actually support this... */
			ATOMIC_FETCHOR(self->d_features, ATA_DRIVE_FEATURE_FFLUSH);
		} else {
			ATOMIC_FETCHAND(self->d_features, ~ATA_DRIVE_FEATURE_FFLUSH);
		}
	}	break;

	case HDIO_DRIVE_RESET: {
		struct ata_bus *bus;
		bus = self->d_bus;
		AtaBus_LockPIO(bus);
		TRY {
			Ata_ResetAndReinitializeBus(bus);
		} EXCEPT {
			AtaBus_UnlockPIO(self->d_bus);
			RETHROW();
		}
		AtaBus_UnlockPIO(self->d_bus);
	}	break;

	case HDIO_GET_BUSSTATE:
	case _IOR(_IOC_TYPE(HDIO_GET_BUSSTATE), _IOC_NR(HDIO_GET_BUSSTATE), int): {
		uintptr_half_t state;
		validate_writable(arg, sizeof(int));
		state = ATOMIC_READ(self->d_bus->b_state);
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


STATIC_ASSERT(sizeof(struct hd_driveid) == 512);

PRIVATE ATTR_NOINLINE ATTR_FREETEXT bool
NOTHROW(KCALL Ata_InitializeDrive)(struct ata_ports *__restrict ports,
                                   struct ata_bus **__restrict pbus,
                                   u8 drive_id, bool is_primary_ata,
                                   bool is_default_ide) {
	u8 cl, ch;
	struct hd_driveid specs;
	assert(drive_id == ATA_DRIVE_MASTER ||
	       drive_id == ATA_DRIVE_SLAVE);
	printk(FREESTR(KERN_INFO "[ata] Attempting to initialize %s %s ATA device {%x,%x,%x} (default_ide: %u)\n"),
	       is_primary_ata ? FREESTR("primary") : FREESTR("secondary"),
	       drive_id == ATA_DRIVE_MASTER ? FREESTR("master") : FREESTR("slave"),
	       ports->a_bus, ports->a_ctrl,
	       ports->a_dma, is_default_ide ? 1 : 0);
	TRY {

		/* Do a soft reset on both ATA device control ports. */
		Ata_ResetBus(ports->a_ctrl);

		/* Select the requested drive. */
		outb(ports->a_bus + ATA_DRIVE_SELECT, drive_id);
		ATA_SELECT_DELAY(ports->a_ctrl);

		/* Wait for the command to be acknowledged. */
		if (Ata_WaitForBusyTimeout(ports->a_ctrl) != E_OK)
			return false;

		/* Figure out what kind of drive this is. */
		cl = inb(ports->a_bus + ATA_ADDRESS2);
		ch = inb(ports->a_bus + ATA_ADDRESS3);

		if ((cl == 0x00 && ch == 0x00) || /* PATA */
		    (cl == 0x3c && ch == 0xc3)) { /* SATA */
			struct heapptr busptr;
			struct ata_bus *bus = *pbus;
			busptr.hp_ptr       = NULL;
			busptr.hp_siz       = 0;
			if (!bus) {
				busptr = heap_alloc_untraced(&kernel_heaps[GFP_LOCKED],
				                             sizeof(struct ata_bus),
				                             GFP_LOCKED | GFP_PREFLT);
				*pbus = bus       = (struct ata_bus *)busptr.hp_ptr;
				bus->b_state      = ATA_BUS_STATE_READY;
				bus->b_flags      = ATA_BUS_FNORMAL;
				bus->b_dma_future = NULL;
				sig_init(&bus->b_sigready);
				sig_init(&bus->b_piointr);
				bus->b_busio  = ports->a_bus;
				bus->b_ctrlio = ports->a_ctrl;
				bus->b_dmaio  = ports->a_dma;
				bus->b_prdt   = NULL;
				/* The BUS structure must be registered alongside an interrupt registration. */
				if (is_primary_ata) {
					isr_register_at(0xfe, (isr_function_t)&handle_ata_bus_interrupt, bus);
				} else {
					isr_register_at(0xff, (isr_function_t)&handle_ata_bus_interrupt, bus);
				}
			}
			TRY {
				/* Construct and initialize a new ATA drive for this bus. */
				struct sig *signal;
				struct ata_drive *drive;
				ATOMIC_WRITE(bus->b_state, ATA_BUS_STATE_INPIO);
				if (Ata_WaitForBusyTimeout(bus->b_ctrlio) != E_OK)
					return false;
				task_connect(&bus->b_piointr);
				outb(bus->b_busio + ATA_FEATURES, 1); /* ??? */
				outb(bus->b_busio + ATA_COMMAND, ATA_COMMAND_IDENTIFY);
				ATA_SELECT_DELAY(bus->b_ctrlio);
				if ((signal = task_trywait()) == NULL) {
					qtime_t timeout;
					timeout = quantum_time();
					timeout.add_seconds(2);
					signal = task_waitfor(&timeout);
					if (!signal) {
reset_bus_and_fail:
						Ata_ResetAndReinitializeBus(bus);
						ATOMIC_WRITE(bus->b_state, ATA_BUS_STATE_READY);
						return false;
					}
				}
				if (Ata_WaitForDrq(bus->b_busio, bus->b_ctrlio) != E_OK)
					goto reset_bus_and_fail;
				insw(bus->b_busio + ATA_DATA, &specs, 256);
				outb(bus->b_busio + ATA_FEATURES, 0); /* ??? */
				ATOMIC_WRITE(bus->b_state, ATA_BUS_STATE_READY);
				/* Fix specifications to properly represent implications. */
				if (bus->b_dmaio == (port_t)-1)
					specs.capability &= ~HD_DRIVEID_CAPABILITY_DMA;
				if (!(specs.capability & HD_DRIVEID_CAPABILITY_LBA))
					specs.command_set_2 &= ~HD_DRIVEID_COMMAND_SET_2_LBA48;
				drive = (struct ata_drive *)block_device_alloc(DEFAULT_ATA_SECTOR_SIZE,
				                                               specs.capability & HD_DRIVEID_CAPABILITY_DMA
				                                               ? sizeof(struct ata_dmadrive)
				                                               : sizeof(struct ata_drive));
				drive->d_bus   = bus;
				drive->d_drive = drive_id;
				drive->bd_type.dt_ioctl = (syscall_slong_t (KCALL *)(struct block_device * __restrict,
				                                                     struct block_device * __restrict,
				                                                     syscall_ulong_t, USER UNCHECKED void *,
				                                                     iomode_t))&Ata_Ioctl;
				drive->d_chs_number_of_heads   = (u8)specs.heads;
				drive->d_chs_cylinders         = (u16)specs.cyls;
				drive->d_chs_sectors_per_track = (u8)specs.sectors;
				/*drive->bd_type.dt_fini = NULL;*/
				if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_FLUSH)
					drive->d_features |= ATA_DRIVE_FEATURE_FFLUSH;
				if (specs.capability & HD_DRIVEID_CAPABILITY_DMA) {
					struct ata_dmadrive *ddrive = (struct ata_dmadrive *)drive;
					if (!bus->b_prdt) {
						vm_phys_t phys;
						bus->b_prdt = (AtaPRD *)vpage_alloc_untraced(1, 1, GFP_LOCKED | GFP_PREFLT);
						/* Re-set the PRDT address. */
						phys = pagedir_translate((vm_virt_t)bus->b_prdt);
						/* TODO: Ensure that a physical page <= 0xfffff000 is allocated for this VPAGE */
						assertf(phys <= (vm_phys_t)0xffffffff, "TODO");
						outl(bus->b_dmaio + DMA_PRIMARY_PRDT, (u32)phys);
					}
					ddrive->bd_type.dt_read        = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict))&Ata_DmaDriveRead;
					ddrive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_DmaDriveReadPhys;
					ddrive->bd_type.dt_readv       = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_DmaDriveReadVector;
					ddrive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_DmaDriveReadVectorPhys;
					ddrive->bd_type.dt_write       = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict))&Ata_DmaDriveWrite;
					ddrive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_DmaDriveWritePhys;
					ddrive->bd_type.dt_writev      = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_DmaDriveWriteVector;
					ddrive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_DmaDriveWriteVectorPhys;
					if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_LBA48) {
						if ((specs.capability & HD_DRIVEID_CAPABILITY_LBA) &&
							(u64)specs.lba_capacity_2 == (u64)specs.lba_capacity)
							goto use_28bit_dma;
						ddrive->d_noncanon_read        = &Ata_Lba48DriveRead;
						ddrive->d_noncanon_read_phys   = &Ata_Lba48DriveReadPhys;
						ddrive->d_noncanon_readv       = &Ata_Lba48DriveReadVector;
						ddrive->d_noncanon_readv_phys  = &Ata_Lba48DriveReadVectorPhys;
						ddrive->d_noncanon_write       = &Ata_Lba48DriveWrite;
						ddrive->d_noncanon_write_phys  = &Ata_Lba48DriveWritePhys;
						ddrive->d_noncanon_writev      = &Ata_Lba48DriveWriteVector;
						ddrive->d_noncanon_writev_phys = &Ata_Lba48DriveWriteVectorPhys;
						goto calculate_lba48;
					} else if (specs.capability & HD_DRIVEID_CAPABILITY_LBA) {
use_28bit_dma:
						ddrive->d_noncanon_read        = &Ata_Lba28DriveRead;
						ddrive->d_noncanon_read_phys   = &Ata_Lba28DriveReadPhys;
						ddrive->d_noncanon_readv       = &Ata_Lba28DriveReadVector;
						ddrive->d_noncanon_readv_phys  = &Ata_Lba28DriveReadVectorPhys;
						ddrive->d_noncanon_write       = &Ata_Lba28DriveWrite;
						ddrive->d_noncanon_write_phys  = &Ata_Lba28DriveWritePhys;
						ddrive->d_noncanon_writev      = &Ata_Lba28DriveWriteVector;
						ddrive->d_noncanon_writev_phys = &Ata_Lba28DriveWriteVectorPhys;
						goto calculate_lba28;
					} else {
						ddrive->d_noncanon_read        = &Ata_ChsDriveRead;
						ddrive->d_noncanon_read_phys   = &Ata_ChsDriveReadPhys;
						ddrive->d_noncanon_readv       = &Ata_ChsDriveReadVector;
						ddrive->d_noncanon_readv_phys  = &Ata_ChsDriveReadVectorPhys;
						ddrive->d_noncanon_write       = &Ata_ChsDriveWrite;
						ddrive->d_noncanon_write_phys  = &Ata_ChsDriveWritePhys;
						ddrive->d_noncanon_writev      = &Ata_ChsDriveWriteVector;
						ddrive->d_noncanon_writev_phys = &Ata_ChsDriveWriteVectorPhys;
						goto calculate_chs;
					}
				} else {
					if (specs.command_set_2 & HD_DRIVEID_COMMAND_SET_2_LBA48) {
						if ((specs.capability & HD_DRIVEID_CAPABILITY_LBA) &&
						    (u64)specs.lba_capacity_2 == (u64)specs.lba_capacity)
							goto use_28bit_lba;
						drive->bd_type.dt_read        = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict))&Ata_Lba48DriveRead;
						drive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba48DriveReadPhys;
						drive->bd_type.dt_readv       = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba48DriveReadVector;
						drive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba48DriveReadVectorPhys;
						drive->bd_type.dt_write       = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict))&Ata_Lba48DriveWrite;
						drive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba48DriveWritePhys;
						drive->bd_type.dt_writev      = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba48DriveWriteVector;
						drive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba48DriveWriteVectorPhys;
calculate_lba48:
						drive->bd_sector_count = (lba_t)specs.lba_capacity_2;
					} else if (specs.capability & HD_DRIVEID_CAPABILITY_LBA) {
use_28bit_lba:
						drive->bd_type.dt_read        = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict))&Ata_Lba28DriveRead;
						drive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba28DriveReadPhys;
						drive->bd_type.dt_readv       = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba28DriveReadVector;
						drive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba28DriveReadVectorPhys;
						drive->bd_type.dt_write       = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict))&Ata_Lba28DriveWrite;
						drive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba28DriveWritePhys;
						drive->bd_type.dt_writev      = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba28DriveWriteVector;
						drive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_Lba28DriveWriteVectorPhys;
calculate_lba28:
						drive->bd_sector_count = (lba_t)specs.lba_capacity;
					} else {
						drive->bd_type.dt_read        = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void *, size_t, lba_t, struct aio_handle *__restrict))&Ata_ChsDriveRead;
						drive->bd_type.dt_read_phys   = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_ChsDriveReadPhys;
						drive->bd_type.dt_readv       = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_ChsDriveReadVector;
						drive->bd_type.dt_readv_phys  = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_ChsDriveReadVectorPhys;
						drive->bd_type.dt_write       = (void(KCALL *)(struct block_device * __restrict, USER CHECKED void const *, size_t, lba_t, struct aio_handle *__restrict))&Ata_ChsDriveWrite;
						drive->bd_type.dt_write_phys  = (void(KCALL *)(struct block_device * __restrict, vm_phys_t, size_t, lba_t, struct aio_handle * __restrict))&Ata_ChsDriveWritePhys;
						drive->bd_type.dt_writev      = (void(KCALL *)(struct block_device * __restrict, struct aio_buffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_ChsDriveWriteVector;
						drive->bd_type.dt_writev_phys = (void(KCALL *)(struct block_device * __restrict, struct aio_pbuffer * __restrict, size_t, lba_t, struct aio_handle * __restrict))&Ata_ChsDriveWriteVectorPhys;
calculate_chs:
						drive->bd_sector_count         = (lba_t)(u8)specs.heads *
						                                 (lba_t)(u16)specs.cyls *
						                                 (lba_t)(u8)specs.sectors;
					}
				}
				drive->bd_total_bytes = ((pos_t)drive->bd_sector_count *
				                         (pos_t)ATA_SECTOR_SIZE(drive));
				TRY {
					/* Register the new device. */
					REF struct block_device_partition *active_part;
					if (is_default_ide) {
						dev_t devno;
						devno = MKDEV(is_primary_ata ? 3 : 22,
						              drive_id == ATA_DRIVE_MASTER ? 0 : 64);
						drive->bd_name[0] = 'h';
						drive->bd_name[1] = 'd';
						drive->bd_name[2] = (is_primary_ata ? 'a' : 'c') +
						                    (drive_id == ATA_DRIVE_MASTER ? 0 : 1);
						drive->bd_name[3] = 0;
						block_device_register(drive, devno);
					} else {
						block_device_register_auto(drive);
					}
					active_part = block_device_autopart(drive);
					if (active_part) {
						printk(FREESTR(KERN_INFO "[ata] Found boot partition: %.2x:%.2x (%q)\n"),
						       MAJOR(active_part->bd_devlink.a_vaddr),
						       MINOR(active_part->bd_devlink.a_vaddr),
						       active_part->bd_name);
						if likely(!boot_partition)
							boot_partition = active_part; /* Inherit reference. */
						else if unlikely(boot_partition == (REF struct basic_block_device *)-1)
							decref(active_part);
						else {
							printk(FREESTR(KERN_WARNING "[ata] Ambigous boot partition: could be %.2x:%.2x (%q) or %.2x:%.2x (%q)\n"),
							       MAJOR(active_part->bd_devlink.a_vaddr),
							       MINOR(active_part->bd_devlink.a_vaddr),
							       active_part->bd_name,
							       MAJOR(boot_partition->bd_devlink.a_vaddr),
							       MINOR(boot_partition->bd_devlink.a_vaddr),
							       boot_partition->bd_name);
							decref(active_part);
							decref(boot_partition);
							boot_partition = (REF struct basic_block_device *)-1;
						}
					}
				} EXCEPT {
					decref(drive);
					RETHROW();
				}
			} EXCEPT {
				if (busptr.hp_siz) {
					if (bus->b_prdt)
						vpage_free_untraced(bus->b_prdt, 1);
					heap_free_untraced(&kernel_heaps[GFP_LOCKED],
					                   busptr.hp_ptr,
					                   busptr.hp_siz,
					                   GFP_LOCKED | GFP_PREFLT);
				}
				RETHROW();
			}
			return true;
		}
		if ((cl == 0x14 && ch == 0xeb) || /* PATAPI */
		    (cl == 0x69 && ch == 0x96)) { /* SATAPI */
			/* TODO (CD drives and the like...) */
		}
	} EXCEPT {
		error_printf("Initializing ATA device");
	}
	return false;
}


PRIVATE ATTR_NOINLINE ATTR_FREETEXT bool
NOTHROW(KCALL initialize_ata)(struct ata_ports *__restrict ports,
                              bool is_primary_ata,
                              bool is_default_ide) {
	struct ata_bus *bus = NULL;
	bool result;
	result  = Ata_InitializeDrive(ports, &bus, ATA_DRIVE_MASTER, is_primary_ata, is_default_ide);
	result |= Ata_InitializeDrive(ports, &bus, ATA_DRIVE_SLAVE, is_primary_ata, is_default_ide);
	if (!result && bus) {
		if (bus->b_prdt)
			vpage_free_untraced(bus->b_prdt, 1);
#if 0
	heap_free_untraced(&kernel_heaps[GFP_LOCKED],
	                    bus,
	                    ???,
	                    GFP_LOCKED | GFP_PREFLT);
#endif
	}
	return result;
}


PRIVATE ATTR_NOINLINE ATTR_FREETEXT bool
NOTHROW(KCALL initialize_ide)(struct ide_ports *__restrict self, bool is_default_ide) {
	struct ata_ports a;
	bool result;
	printk(FREESTR(KERN_INFO "[ata] Attempting to initialize IDE device {%x,%x,%x,%x,%x} (default_ide: %u)\n"),
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



#define DEFAULT_PRIMARY_BUS    __CCAST(port_t)0x1f0
#define DEFAULT_PRIMARY_CTRL   __CCAST(port_t)0x3f6
#define DEFAULT_SECONDARY_BUS  __CCAST(port_t)0x170
#define DEFAULT_SECONDARY_CTRL __CCAST(port_t)0x376


#ifdef CONFIG_BUILDING_KERNEL_CORE
ATTR_FREEBSS
#endif /* CONFIG_BUILDING_KERNEL_CORE */
DEFINE_CMDLINE_FLAG_VAR(ide_nodma, "ide_nodma");

/* @return: true:  Primary IDE device found.
 * @return: false: Secondary IDE device found, or initialization failed. */
PRIVATE ATTR_NOINLINE ATTR_FREETEXT bool
NOTHROW(KCALL kernel_load_pci_ide)(struct pci_device *__restrict dev) {
	bool result = false;
	struct ide_ports i;
	if (dev->pd_res[PD_RESOURCE_BAR0].pr_flags == PCI_RESOURCE_FUNUSED) {
		i.i_primary_bus = DEFAULT_PRIMARY_BUS;
		result          = true;
	} else {
		if (!(dev->pd_res[PD_RESOURCE_BAR0].pr_flags & PCI_RESOURCE_FIO)) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %I32p uses a memory mapping for BAR0 (primary bus)\n"),
			       dev->pd_base);
			return false;
		}
		i.i_primary_bus = (port_t)dev->pd_res[PD_RESOURCE_BAR0].pr_start;
		if (i.i_primary_bus == DEFAULT_PRIMARY_BUS)
			result = true;
	}
	if (dev->pd_res[PD_RESOURCE_BAR1].pr_flags == PCI_RESOURCE_FUNUSED) {
		i.i_primary_ctrl = DEFAULT_PRIMARY_CTRL;
		result           = true;
	} else {
		if (!(dev->pd_res[PD_RESOURCE_BAR1].pr_flags & PCI_RESOURCE_FIO)) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %I32p uses a memory mapping for BAR1 (primary control)\n"),
			       dev->pd_base);
			return false;
		}
		i.i_primary_ctrl = (port_t)dev->pd_res[PD_RESOURCE_BAR1].pr_start;
		if (i.i_primary_ctrl == DEFAULT_PRIMARY_CTRL)
			result = true;
	}
	if (dev->pd_res[PD_RESOURCE_BAR2].pr_flags == PCI_RESOURCE_FUNUSED) {
		i.i_secondary_bus = DEFAULT_SECONDARY_BUS;
		result            = true;
	} else {
		if (!(dev->pd_res[PD_RESOURCE_BAR2].pr_flags & PCI_RESOURCE_FIO)) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %I32p uses a memory mapping for BAR2 (secondary bus)\n"),
			       dev->pd_base);
			return false;
		}
		i.i_secondary_bus = (port_t)dev->pd_res[PD_RESOURCE_BAR2].pr_start;
		if (i.i_secondary_bus == DEFAULT_SECONDARY_BUS)
			result = true;
	}
	if (dev->pd_res[PD_RESOURCE_BAR3].pr_flags == PCI_RESOURCE_FUNUSED) {
		i.i_secondary_ctrl = DEFAULT_SECONDARY_CTRL;
		result             = true;
	} else {
		if (!(dev->pd_res[PD_RESOURCE_BAR3].pr_flags & PCI_RESOURCE_FIO)) {
			printk(FREESTR(KERN_WARNING "[ata] PCI IDE device at %I32p uses a memory mapping for BAR3 (secondary control)\n"),
			       dev->pd_base);
			return false;
		}
		i.i_secondary_ctrl = (port_t)dev->pd_res[PD_RESOURCE_BAR3].pr_start;
		if (i.i_secondary_ctrl == DEFAULT_SECONDARY_CTRL)
			result = true;
	}
	i.i_dma_ctrl = (port_t)-1;
	/* Check if this IDE may support DMA mode. */
	if (dev->pd_res[PD_RESOURCE_BAR4].pr_flags != PCI_RESOURCE_FUNUSED &&
	    (dev->pd_res[PD_RESOURCE_BAR4].pr_flags & PCI_RESOURCE_FIO) &&
	    dev->pd_res[PD_RESOURCE_BAR4].pr_size >= 16) {
		i.i_dma_ctrl = (port_t)dev->pd_res[PD_RESOURCE_BAR4].pr_start;
		pci_write(dev->pd_base, PCI_DEV4,
		          (pci_read(dev->pd_base, PCI_DEV4) & ~(PCI_CDEV4_NOIRQ)) |
		          PCI_CDEV4_BUSMASTER |
		          PCI_CDEV4_ALLOW_MEMWRITE);
	}
	/* Forceably disable DMA, the same way a bus without support would */
	if (ide_nodma)
		i.i_dma_ctrl = (port_t)-1;
	return initialize_ide(&i, result) ? result : false;
}


INTERN ATTR_NOINLINE ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_ide_driver)(void) {
	bool has_primary = false;
	struct pci_device *dev;
	/* Search for IDE PCI devices. */
	PCI_FOREACH_CLASS(dev, PCI_DEV8_CLASS_STORAGE, 1) {
		has_primary |= kernel_load_pci_ide(dev);
	}
	if (!has_primary) {
		/* Check for an IDE device at the default location. */
		struct ide_ports i;
		i.i_primary_bus    = DEFAULT_PRIMARY_BUS;
		i.i_primary_ctrl   = DEFAULT_PRIMARY_CTRL;
		i.i_secondary_bus  = DEFAULT_SECONDARY_BUS;
		i.i_secondary_ctrl = DEFAULT_SECONDARY_CTRL;
		i.i_dma_ctrl       = (port_t)-1;
		initialize_ide(&i, true);
	}
}


DECL_END

#ifndef __INTELLISENSE__

#undef IO_READ
#undef IO_WRITE
#undef IO_PHYS
#undef IO_VECTOR
#undef IO_DMA
#undef IO_LBA28
#undef IO_LBA48
#undef IO_CHS

/* PIO Transfer helper functions. */
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-pio-transfer.c.inl"
#define IO_VECTOR 1
#define IO_READ 1
#include "ata/ata-pio-transfer.c.inl"
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-pio-transfer.c.inl"
#define IO_READ 1
#include "ata/ata-pio-transfer.c.inl"
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-pio-transfer.c.inl"
#define IO_VECTOR 1
#define IO_WRITE 1
#include "ata/ata-pio-transfer.c.inl"
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-pio-transfer.c.inl"
#define IO_WRITE 1
#include "ata/ata-pio-transfer.c.inl"


/* DMA + READ */
#define IO_DMA 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_DMA 1
#define IO_VECTOR 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_DMA 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_DMA 1
#define IO_READ 1
#include "ata/ata-io.c.inl"

/* DMA + WRITE */
#define IO_DMA 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_DMA 1
#define IO_VECTOR 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_DMA 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_DMA 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"

/* CHS + READ */
#define IO_CHS 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_CHS 1
#define IO_VECTOR 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_CHS 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_CHS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"

/* CHS + WRITE */
#define IO_CHS 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_CHS 1
#define IO_VECTOR 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_CHS 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_CHS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"

/* LBA28 + READ */
#define IO_LBA28 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_LBA28 1
#define IO_VECTOR 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_LBA28 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_LBA28 1
#define IO_READ 1
#include "ata/ata-io.c.inl"

/* LBA28 + WRITE */
#define IO_LBA28 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_LBA28 1
#define IO_VECTOR 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_LBA28 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_LBA28 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"

/* LBA48 + READ */
#define IO_LBA48 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_LBA48 1
#define IO_VECTOR 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_LBA48 1
#define IO_PHYS 1
#define IO_READ 1
#include "ata/ata-io.c.inl"
#define IO_LBA48 1
#define IO_READ 1
#include "ata/ata-io.c.inl"

/* LBA48 + WRITE */
#define IO_LBA48 1
#define IO_VECTOR 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_LBA48 1
#define IO_VECTOR 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_LBA48 1
#define IO_PHYS 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"
#define IO_LBA48 1
#define IO_WRITE 1
#include "ata/ata-io.c.inl"

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_DRIVERS_ATA_C */
