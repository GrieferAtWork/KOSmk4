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
#ifndef GUARD_MODIDE_OLDPRD_C
#define GUARD_MODIDE_OLDPRD_C 1
#define _KOS_SOURCE 1

#include "oldata.h"
/**/

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_FS
#include <kernel/aio.h>
#include <kernel/iovec.h>
#include <kernel/mman.h>
#include <kernel/mman/dma.h>

#include <hybrid/atomic.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Initialize a given PRD from various sources.
 * NOTE: Upon  successful  completion of  `AtaPRD_InitFromVirt'  or `AtaPRD_InitFromVirtVector',
 *       either  `ATA_AIO_HANDLE_FUNLOCK_USER_DMA'  or  `ATA_AIO_HANDLE_FUNLOCK_KERNEL_DMA'   is
 *       added to `*pflags', and the caller is required to unlock the DMA lock of the associated
 *       VM upon completion of the operation.
 * @return: <= prd_siz: SUCCESS. In this case, the return value specifies the number of encoded
 *                     PRD entries, starting at `prd_buf'. Also note that in this case, the  caller
 *                     will be required  to eventually  unlock VM DMA  locks in  accordance to  the
 *                     bits set in `*pflags' if `AtaPRD_InitFromVirt' / `AtaPRD_InitFromVirtVector'
 *                     was called.
 * @return: > prd_siz: ERROR: More than `prd_siz' PRD entires would be required for the encoding
 *                     to  succeed. - In this case, the  caller should re-attempt the call after
 *                     re-allocating to match a total of at least `return' AtaPRD entries passed
 *                     to `prd_buf', and update `prd_siz' accordingly.
 * @return: 0 : ERROR: The given address range cannot be encoded as a valid PRD
 *                     This can  happen  for  any  of  the  following  reasons:
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

PRIVATE NOBLOCK bool
NOTHROW(KCALL ata_dma_acquire_func)(void *arg, physaddr_t paddr, size_t num_bytes,
                                    struct mdmalock *__restrict UNUSED(lock) DFL(NULL)) {
	struct ata_dma_acquire_data *data;
	data = (struct ata_dma_acquire_data *)arg;
	assert(num_bytes != 0);
	assert((physaddr_t)(paddr + num_bytes) > paddr);
	if ((paddr + num_bytes - 1) > (physaddr_t)__UINT32_C(0xffffffff))
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
 * @param: for_writing: When true, the target buffer is intended to  be
 *                      written to, else only intended to be read from. */
INTERN WUNUSED size_t KCALL
AtaPRD_InitFromVirt(AtaPRD *__restrict prd_buf, size_t prd_siz, CHECKED void *base,
                    size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct mman *effective_mm = &mman_kernel;
	struct ata_dma_acquire_data data;
	size_t req_locks, req_prd;
	if (ADDR_ISUSER(base))
		effective_mm = THIS_MMAN;
	data.ad_base = data.ad_buf = prd_buf;
	data.ad_siz = data.ad_max = prd_siz;
	/* Try to start DMAing within the given address range. */
	assert(handle != NULL);
	req_locks = mman_startdma(effective_mm,
	                          &ata_dma_acquire_func,
	                          &data,
	                          &handle->hd_dmalock,
	                          1,
	                          base,
	                          num_bytes,
	                          for_writing ? MMAN_FAULT_F_WRITE : 0);
	if (!req_locks)
		return 0; /* Not encodable as PRD physical memory. */
	req_prd = (size_t)(data.ad_buf - data.ad_base);
	assert(req_prd != 0);
	assertf(pagedir_translate(base) == (physaddr_t)prd_buf->p_bufaddr,
	        "prd_buf->p_bufaddr      = %" PRIpN(__SIZEOF_PHYSADDR_T__) "\n"
	        "pagedir_translate(base) = %" PRIpN(__SIZEOF_PHYSADDR_T__) "\n",
	        (physaddr_t)prd_buf->p_bufaddr,
	        (physaddr_t)pagedir_translate(base));
	if (req_locks == 1) {
		/* Simple case: only a single lock is required! */
		if unlikely(req_prd > prd_siz) {
			/* Need more PRDs */
			mman_dmalock_release(&handle->hd_dmalock);
			return req_prd;
		}
		handle->hd_flags |= ATA_AIO_HANDLE_FONEDMA;
	} else {
		/* Complicated case: Need multiple DMA locks. */
		struct mdmalock *lockvec;
		size_t new_req_locks;
		assert(req_locks > 1);
		if unlikely(req_prd > prd_siz)
			return req_prd; /* Need more PRDs */
		lockvec = (struct mdmalock *)kmalloc((req_locks + 1) *
		                                     sizeof(struct mdmalock),
		                                     GFP_LOCKED | GFP_PREFLT);
again_start_dma_lockvec:
		data.ad_base = data.ad_buf = prd_buf;
		data.ad_siz = data.ad_max = prd_siz;
		TRY {
			new_req_locks = mman_startdma(effective_mm,
			                              &ata_dma_acquire_func,
			                              &data,
			                              lockvec,
			                              req_locks,
			                              base,
			                              num_bytes,
			                              for_writing ? MMAN_FAULT_F_WRITE : 0);
			if unlikely(new_req_locks > req_locks) {
				/* Need _even_ more DMA locks! */
				lockvec = (struct mdmalock *)krealloc(lockvec,
				                                      (new_req_locks + 1) *
				                                      sizeof(struct mdmalock),
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
			mman_stopdma(lockvec, new_req_locks);
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
				struct mdmalock *newvec;
				newvec = (struct mdmalock *)krealloc_nx(lockvec,
				                                        (new_req_locks + 1) *
				                                        sizeof(struct mdmalock),
				                                        GFP_LOCKED | GFP_PREFLT);
				if likely(newvec)
					lockvec = newvec;
				goto set_lock_vec;
			}
		} else {
set_lock_vec:
			assert(!(handle->hd_flags & ATA_AIO_HANDLE_FONEDMA));
			lockvec[new_req_locks].mdl_part = NULL;    /* Sentinel */
			handle->hd_dmalockvec           = lockvec; /* Inherit vector, locks & references */
		}
	}
	assert(req_prd != 0);
	return req_prd;
}

INTERN WUNUSED size_t KCALL
AtaPRD_InitFromVirtVector(AtaPRD *__restrict prd_buf, size_t prd_siz, struct iov_buffer *__restrict buf,
                          size_t num_bytes, AtaAIOHandleData *__restrict handle, bool for_writing)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct mman *effective_mm = &mman_kernel;
	struct ata_dma_acquire_data data;
	size_t req_locks, req_prd;
	if (ADDR_ISUSER(buf->iv_head.ive_base))
		effective_mm = THIS_MMAN;
	assert(num_bytes == iov_buffer_size(buf));
	data.ad_base = data.ad_buf = prd_buf;
	data.ad_siz = data.ad_max = prd_siz;
	/* Try to start DMAing within the given address range. */
	req_locks = mman_startdmav(effective_mm,
	                           &ata_dma_acquire_func,
	                           &data,
	                           &handle->hd_dmalock,
	                           1,
	                           buf,
	                           for_writing ? MMAN_FAULT_F_WRITE : 0);
	if (!req_locks)
		return 0; /* Not encodable as PRD physical memory. */
	req_prd = (size_t)(data.ad_buf - data.ad_base);
	assert(req_prd != 0);
	if (req_locks == 1) {
		/* Simple case: only a single lock is required! */
		if unlikely(req_prd > prd_siz) {
			/* Need more PRDs */
			mman_dmalock_release(&handle->hd_dmalock);
			return req_prd;
		}
		handle->hd_flags |= ATA_AIO_HANDLE_FONEDMA;
	} else {
		/* Complicated case: Need multiple DMA locks. */
		struct mdmalock *lockvec;
		size_t new_req_locks;
		assert(req_locks > 1);
		if unlikely(req_prd > prd_siz)
			return req_prd; /* Need more PRDs */
		lockvec = (struct mdmalock *)kmalloc((req_locks + 1) *
		                                     sizeof(struct mdmalock),
		                                     GFP_LOCKED | GFP_PREFLT);
again_start_dma_lockvec:
		data.ad_base = data.ad_buf = prd_buf;
		data.ad_siz = data.ad_max = prd_siz;
		TRY {
			new_req_locks = mman_startdmav(effective_mm,
			                               &ata_dma_acquire_func,
			                               &data,
			                               lockvec,
			                               req_locks,
			                               buf,
			                               for_writing ? MMAN_FAULT_F_WRITE : 0);
			if unlikely(new_req_locks > req_locks) {
				/* Need _even_ more DMA locks! */
				lockvec = (struct mdmalock *)krealloc(lockvec,
				                                      (new_req_locks + 1) *
				                                      sizeof(struct mdmalock),
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
			mman_stopdma(lockvec, new_req_locks);
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
				struct mdmalock *newvec;
				newvec = (struct mdmalock *)krealloc_nx(lockvec,
				                                        (new_req_locks + 1) *
				                                        sizeof(struct mdmalock),
				                                        GFP_LOCKED | GFP_PREFLT);
				if likely(newvec)
					lockvec = newvec;
				goto set_lock_vec;
			}
		} else {
set_lock_vec:
			assert(!(handle->hd_flags & ATA_AIO_HANDLE_FONEDMA));
			lockvec[new_req_locks].mdl_part = NULL;    /* Sentinel */
			handle->hd_dmalockvec           = lockvec; /* Inherit vector, locks & references */
		}
	}
	assert(req_prd != 0);
	return req_prd;
}


INTERN WUNUSED size_t
NOTHROW(KCALL AtaPRD_InitFromPhys)(AtaPRD *__restrict prd_buf,
                                   size_t prd_siz,
                                   physaddr_t base,
                                   size_t num_bytes) {
	size_t result;
	struct ata_dma_acquire_data data;
	data.ad_base = prd_buf;
	data.ad_buf  = prd_buf;
	data.ad_siz  = prd_siz;
	if (!ata_dma_acquire_func(&data, base, num_bytes))
		return 0;
	result = (size_t)(data.ad_buf - data.ad_base);
	return result;
}

INTERN WUNUSED size_t
NOTHROW(KCALL AtaPRD_InitFromPhysVector)(AtaPRD *__restrict prd_buf,
                                         size_t prd_siz,
                                         struct iov_physbuffer *__restrict buf,
                                         size_t num_bytes) {
	size_t result;
	struct iov_physentry ent;
	struct ata_dma_acquire_data data;
	assert(iov_physbuffer_size(buf) == num_bytes);
	(void)num_bytes;
	data.ad_base = prd_buf;
	data.ad_buf  = prd_buf;
	data.ad_siz  = prd_siz;
	IOV_PHYSBUFFER_FOREACH(ent, buf) {
		if (!ata_dma_acquire_func(&data,
		                          ent.ive_base,
		                          ent.ive_size))
			goto err;
	}
	result = (size_t)(data.ad_buf - data.ad_base);
	return result;
err:
	return 0;
}

DECL_END
#endif /* !CONFIG_USE_NEW_FS */

#endif /* !GUARD_MODIDE_OLDPRD_C */
