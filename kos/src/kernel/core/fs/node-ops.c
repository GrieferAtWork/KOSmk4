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
#ifndef GUARD_KERNEL_CORE_FS_NODE_OPS_C
#define GUARD_KERNEL_CORE_FS_NODE_OPS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/vm.h>

#include <assert.h>

DECL_BEGIN

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x



/* Implementation for `f_pwrite' that uses `f_write' */
PUBLIC NONNULL((1, 5)) void KCALL
inode_file_pwrite_with_write(struct inode *__restrict self, vm_phys_t src,
                             size_t num_bytes, pos_t file_position,
                             struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY,
		       E_IOERROR_BADBOUNDS, E_IOERROR_READONLY,
		       E_IOERROR, ...) {
	vm_ppage_t minpage, maxpage;
	assert(self->i_type->it_file.f_write);
	if (file_position != 0)
		THROW(E_IOERROR_BADBOUNDS, E_IOERROR_SUBSYSTEM_FILE);
	minpage = VM_ADDR2PAGE(src);
	maxpage = VM_ADDR2PAGE(src + num_bytes);
	if (minpage == maxpage) {
		uintptr_t backup;
		vm_vpage_t tramp;
		if unlikely(!num_bytes)
			return;
		tramp = THIS_TRAMPOLINE_PAGE;
		backup = pagedir_push_mapone(tramp, minpage,
		                             PAGEDIR_MAP_FREAD);
		pagedir_syncone(tramp);
		TRY {
			(*self->i_type->it_file.f_write)(self,
			                                 (void *)(VM_PAGE2ADDR(tramp) + (ptrdiff_t)(src & (PAGESIZE - 1))),
			                                 num_bytes, file_position, aio);
		} EXCEPT {
			pagedir_pop_mapone(tramp, backup);
			RETHROW();
		}
		pagedir_pop_mapone(tramp, backup);
	} else {
		vm_vpage_t vp;
		size_t np = (size_t)((maxpage - minpage) + 1);
		/* XXX: Instead of vm_map(), maybe just call `f_write()' multiple times?
		 *      Or at the very least, do so when vm_map() fails! */
		vp = vm_map(&vm_kernel,
		            (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
		            np, 1, HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
		            &vm_datablock_physical,
		            (vm_vpage64_t)minpage,
		            VM_PROT_READ | VM_PROT_SHARED,
		            VM_NODE_FLAG_NOMERGE);
		TRY {
			(*self->i_type->it_file.f_write)(self,
			                                 (void const *)(VM_PAGE2ADDR(vp) +
			                                                (uintptr_t)(src & (pagedir_pagesize() - 1))),
			                                 num_bytes, file_position, aio);
		} EXCEPT {
			vm_unmap(&vm_kernel, vp, np);
			RETHROW();
		}
		vm_unmap(&vm_kernel, vp, np);
	}
}


/* Implementation for `f_writev' that uses `f_write' */
PUBLIC NONNULL((1, 2, 5)) void KCALL
inode_file_writev_with_write(struct inode *__restrict self,
                             struct aio_buffer *__restrict buf,
                             size_t num_bytes, pos_t file_position,
                             struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct aio_buffer_entry ent;
	assert(num_bytes == aio_buffer_size(buf));
	assert(self->i_type->it_file.f_write);
	(void)num_bytes;
	AIO_BUFFER_FOREACH(ent, buf) {
		(*self->i_type->it_file.f_write)(self,
		                                 ent.ab_base,
		                                 ent.ab_size,
		                                 file_position,
		                                 aio);
		file_position += ent.ab_size;
	}
}

/* Implementation for `f_pwritev' that uses `f_pwrite' */
PUBLIC NONNULL((1, 2, 5)) void KCALL
inode_file_pwritev_with_pwrite(struct inode *__restrict self,
                               struct aio_pbuffer *__restrict buf,
                               size_t num_bytes, pos_t file_position,
                               struct aio_multihandle *__restrict aio)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct aio_pbuffer_entry ent;
	assert(num_bytes == aio_pbuffer_size(buf));
	assert(self->i_type->it_file.f_pwrite);
	(void)num_bytes;
	AIO_PBUFFER_FOREACH(ent, buf) {
		(*self->i_type->it_file.f_pwrite)(self,
		                                  ent.ab_base,
		                                  ent.ab_size,
		                                  file_position,
		                                  aio);
		file_position += ent.ab_size;
	}
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_NODE_OPS_C */
