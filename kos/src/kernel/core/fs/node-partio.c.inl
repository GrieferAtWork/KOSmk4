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
#ifdef __INTELLISENSE__
#include "node.c"
#define IO_READ 1
#endif

#include <fs/node.h>
#include <kernel/swap.h>

#include <hybrid/overflow.h>

#include "../memory/vm/vm-partapi.h"

DECL_BEGIN

#ifdef IO_READ
/* @param: partrelative_pageno: In data-pages, the part-relative offset to the first uninitialized data-page.
 * @param: num_data_pages:      In data-pages, the number of continuous, modified data-pages. */
#define INODE_DO_LOAD_DATAPART_PAGES_DEFINED 1
INTERN NONNULL((1, 2)) void KCALL
inode_do_load_datapart_pages(struct inode *__restrict self,
                             struct vm_datapart *__restrict part,
                             size_t partrelative_pageno,
                             size_t num_data_pages,
                             struct aio_multihandle *__restrict aio)
#else
/* @param: partrelative_pageno: In data-pages, the part-relative offset to the first modified data-page.
 * @param: num_data_pages:      In data-pages, the number of continuous, modified data-pages. */
INTERN NONNULL((1, 2)) void KCALL
inode_do_save_datapart_pages(struct inode *__restrict self,
                             struct vm_datapart *__restrict part,
                             size_t partrelative_pageno,
                             size_t num_data_pages,
                             struct aio_multihandle *__restrict aio)
#endif
{
	size_t first_ppage_index;
	size_t ppage_offset;
	size_t num_bytes;
	pos_t file_position;

	/* Figure out the physical page indices describing
	 * the outer bounds of modified data-pages. */
	first_ppage_index = partrelative_pageno >> VM_DATABLOCK_PAGESHIFT(self);
	/* Figure out the offset into the associated physical page (in bytes),
	 * where the first modified data page is located. */
	ppage_offset = (partrelative_pageno & VM_DATABLOCK_PAGEMASK(self)) << VM_DATABLOCK_ADDRSHIFT(self);
	num_bytes    = num_data_pages << VM_DATABLOCK_ADDRSHIFT(self);
	/* Figure out the in-file position of the first modified data page (in bytes) */
	file_position = VM_DATABLOCK_DPAGE2DADDR(self,
	                                         vm_datapart_startdpage(part) +
	                                         partrelative_pageno);

	/* Find the associated RAM block(s) and write them to disk. */
	if (part->dp_ramdata.rd_blockv == &part->dp_ramdata.rd_block0) {
		vm_phys_t phys_buf;
		/* Simple case: physical memory was allocated linearly. */
		assert(first_ppage_index < part->dp_ramdata.rd_block0.rb_size);
		phys_buf = VM_PPAGE2ADDR(part->dp_ramdata.rd_block0.rb_start + first_ppage_index);
		phys_buf += ppage_offset;
#ifdef IO_READ
		(*self->i_type->it_file.f_pread)(self,
		                                 phys_buf,
		                                 num_bytes,
		                                 file_position,
		                                 aio);
#else
		(*self->i_type->it_file.f_pwrite)(self,
		                                  phys_buf,
		                                  num_bytes,
		                                  file_position,
		                                  aio);
#endif
	} else {
		/* Complicated case: the write is split across multiple physical memory blocks. */
		size_t i, count;
		struct vm_ramblock *blocks;
		count  = part->dp_ramdata.rd_blockc;
		blocks = part->dp_ramdata.rd_blockv;
		for (i = 0;; ++i) {
			vm_phys_t phys_buf;
			size_t block_size_in_ppages;
			size_t num_block_bytes;
			assert(i < count);
			block_size_in_ppages = blocks[i].rb_size;
			if (first_ppage_index >= block_size_in_ppages) {
				/* We're too early. */
				first_ppage_index -= block_size_in_ppages;
				continue;
			}
			/* (at least) a part of this RAMBLOCK must be written. */
			num_block_bytes = (block_size_in_ppages - first_ppage_index) * pagedir_pagesize();
			if (num_block_bytes > num_bytes)
				num_block_bytes = num_bytes;
			phys_buf = VM_PPAGE2ADDR(blocks[i].rb_start + first_ppage_index);
			phys_buf += ppage_offset;
#ifdef IO_READ
			(*self->i_type->it_file.f_pread)(self,
			                                 phys_buf,
			                                 num_block_bytes,
			                                 file_position,
			                                 aio);
#else
			(*self->i_type->it_file.f_pwrite)(self,
			                                  phys_buf,
			                                  num_block_bytes,
			                                  file_position,
			                                  aio);
#endif
			if (num_block_bytes >= num_bytes)
				break; /* Done! (this was the last part) */
			file_position += num_block_bytes;
			num_bytes -= num_block_bytes;
			ppage_offset      = 0; /* We're now physical-memory aligned. */
			first_ppage_index = 0; /* Continue writing at the start of the next block. */
		}
	}
}

#ifdef IO_READ
INTDEF NONNULL((1, 2)) void KCALL
inode_do_load_datapart_pages_sync(struct inode *__restrict self,
                                  struct vm_datapart *__restrict part,
                                  size_t partrelative_pageno,
                                  size_t num_data_pages) {
	struct aio_multihandle_generic hand;
	aio_multihandle_generic_init(&hand);
	TRY {
		inode_do_load_datapart_pages(self,
		                             part,
		                             partrelative_pageno,
		                             num_data_pages,
		                             &hand);
	} EXCEPT {
		aio_multihandle_fail(&hand);
	}
	aio_multihandle_done(&hand);
	TRY {
		aio_multihandle_generic_waitfor(&hand);
		aio_multihandle_generic_checkerror(&hand);
	} EXCEPT {
		aio_multihandle_fini(&hand);
		RETHROW();
	}
	aio_multihandle_fini(&hand);
}
#endif

#ifdef CONFIG_VIO
#endif /* CONFIG_VIO */


DECL_END

#undef FUNC2
#undef FUNC1
#undef FUNC0
#undef VIRT_BUF
#undef PHYS_BUF
#undef IO_PHYS
#undef IO_READ
