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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_VM_DATAPART_READ_WRITE_C_INL
#define GUARD_KERNEL_SRC_MEMORY_VM_VM_DATAPART_READ_WRITE_C_INL 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

DECL_BEGIN

PUBLIC NONNULL((1, 2)) size_t KCALL
vm_datapart_readv(struct vm_datapart *__restrict self,
                  struct aio_buffer const *__restrict buf,
                  pos_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	AIO_BUFFER_FOREACH(ent, buf) {
		temp = vm_datapart_read(self,
		                        ent.ab_base,
		                        ent.ab_size,
		                        src_offset);
		result += temp;
		if (temp != ent.ab_size)
			break;
		src_offset += temp;
	}
	return result;
}

PUBLIC NONNULL((1, 2)) size_t KCALL
vm_datapart_writev(struct vm_datapart *__restrict self,
                   struct aio_buffer const *__restrict buf,
                   size_t split_bytes,
                   pos_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	struct aio_buffer_entry ent;
	size_t temp, result = 0;
	AIO_BUFFER_FOREACH(ent, buf) {
		temp = vm_datapart_write(self,
		                         ent.ab_base,
		                         ent.ab_size,
		                         split_bytes,
		                         dst_offset);
		result += temp;
		if (temp != ent.ab_size)
			break;
		dst_offset += temp;
		if unlikely(OVERFLOW_USUB(split_bytes, temp, &split_bytes))
			split_bytes = 0;
	}
	return result;
}

PUBLIC NONNULL((1, 2)) size_t KCALL
vm_datapart_readv_phys(struct vm_datapart *__restrict self,
                       struct aio_pbuffer const *__restrict buf,
                       pos_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct aio_pbuffer_entry ent;
	size_t temp, result = 0;
	AIO_PBUFFER_FOREACH(ent, buf) {
		temp = vm_datapart_read_phys(self,
		                             ent.ab_base,
		                             ent.ab_size,
		                             src_offset);
		result += temp;
		if (temp != ent.ab_size)
			break;
		src_offset += temp;
	}
	return result;
}

PUBLIC NONNULL((1, 2)) size_t KCALL
vm_datapart_writev_phys(struct vm_datapart *__restrict self,
                        struct aio_pbuffer const *__restrict buf,
                        size_t split_bytes,
                        pos_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct aio_pbuffer_entry ent;
	size_t temp, result = 0;
	AIO_PBUFFER_FOREACH(ent, buf) {
		temp = vm_datapart_write_phys(self,
		                              ent.ab_base,
		                              ent.ab_size,
		                              split_bytes,
		                              dst_offset);
		result += temp;
		if (temp != ent.ab_size)
			break;
		dst_offset += temp;
		if unlikely(OVERFLOW_USUB(split_bytes, temp, &split_bytes))
			split_bytes = 0;
	}
	return result;
}


DECL_END

#ifndef __INTELLISENSE__
#undef DEFINE_IO_READ
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_NOPF

#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#include "datapart-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#include "datapart-read-write-base.c.inl"
#define DEFINE_IO_READ 1
#include "datapart-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#include "datapart-read-write-base.c.inl"

#define DEFINE_IO_READ 1
#define DEFINE_IO_NOPF 1
#include "datapart-read-write-base.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_NOPF 1
#include "datapart-read-write-base.c.inl"

#define DEFINE_IO_READ 1
#include "datapart-read-write-buffered.c.inl"
#define DEFINE_IO_WRITE 1
#include "datapart-read-write-buffered.c.inl"

#define DEFINE_IO_READ 1
#include "datapart-read-write-auto.c.inl"
#define DEFINE_IO_WRITE 1
#include "datapart-read-write-auto.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_DATAPART_READ_WRITE_C_INL */
