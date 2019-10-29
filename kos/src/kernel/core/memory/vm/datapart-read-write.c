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

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/vm.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/alloca.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

/* Read/write data to/from the given data part.
 * NOTE: When given a virtual memory buffer, these functions automatically
 *       check if the memory backing that buffer could potentially overlap
 *       with `self', in which case reading is performed using an intermediate
 *       buffer, so-as to prevent a possible dead-lock when `self' is already
 *       locked, whilst a #PF caused by writing to the target buffer attempts
 *       to acquire another lock to `self'
 * NOTE: The caller must _NOT_ be holding any lock to `self', the associated
 *       block, or any VM-tree when calling this function.
 * @return: * : The number of written bytes. */
PUBLIC NONNULL((1)) size_t KCALL
vm_datapart_read(struct vm_datapart *__restrict self,
                 USER CHECKED void *dst,
                 size_t num_bytes,
                 vm_daddr_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	/* TODO: Check of `dst' overlaps with `self'. - If they don't, directly copy memory! */
	return vm_datapart_read_buffered(self, dst, num_bytes, src_offset);
}

PUBLIC NONNULL((1)) size_t KCALL
vm_datapart_write(struct vm_datapart *__restrict self,
                  USER CHECKED void const *src,
                  size_t num_bytes,
                  size_t split_bytes,
                  vm_daddr_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	/* TODO: Check of `src' overlaps with `self'. - If they don't, directly copy memory! */
	return vm_datapart_write_buffered(self, src, num_bytes, split_bytes, dst_offset);
}


PUBLIC NONNULL((1, 2)) size_t KCALL
vm_datapart_readv(struct vm_datapart *__restrict self,
                  struct aio_buffer const *__restrict buf,
                  vm_daddr_t src_offset)
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
                   vm_daddr_t dst_offset)
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
                       vm_daddr_t src_offset)
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
                        vm_daddr_t dst_offset)
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






PUBLIC NONNULL((1)) size_t KCALL
vm_datapart_read_buffered(struct vm_datapart *__restrict self,
                          USER CHECKED void *dst,
                          size_t num_bytes,
                          vm_daddr_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t temp, bufsize = stack_avail();
	byte_t *buf;
	size_t result = 0;
	/* TODO: Don't use an intermediate buffer!
	 *       Instead, use memcpy_nopf(), and write faulting bytes 1 byte at a time! */
	if (bufsize > 2048 * sizeof(void *))
		bufsize -= 2048 * sizeof(void *);
	else {
		bufsize = 128 * sizeof(void *);
	}
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	buf = (byte_t *)ALLOCA(bufsize);
	while (num_bytes) {
		assert(bufsize <= num_bytes);
		temp = vm_datapart_read_unsafe(self,
		                               buf,
		                               bufsize,
		                               src_offset);
		if (!temp)
			break;
		assert(temp <= bufsize);
		COMPILER_BARRIER();
		memcpy(dst, buf, temp);
		COMPILER_BARRIER();
		dst = (byte_t *)dst + temp;
		result += temp;
		src_offset += temp;
		num_bytes -= temp;
		if (bufsize > num_bytes)
			bufsize = num_bytes;
	}
	return result;
}

PUBLIC NONNULL((1)) size_t KCALL
vm_datapart_write_buffered(struct vm_datapart *__restrict self,
                           USER CHECKED void const *src,
                           size_t num_bytes,
                           size_t split_bytes,
                           vm_daddr_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t temp, bufsize = stack_avail();
	byte_t *buf;
	size_t result = 0;
	/* TODO: Don't use an intermediate buffer!
	 *       Instead, use memcpy_nopf(), and write faulting bytes 1 byte at a time! */
	if (bufsize > 2048 * sizeof(void *))
		bufsize -= 2048 * sizeof(void *);
	else {
		bufsize = 128 * sizeof(void *);
	}
	if (bufsize > num_bytes)
		bufsize = num_bytes;
	buf = (byte_t *)ALLOCA(bufsize);
	while (num_bytes) {
		COMPILER_BARRIER();
		memcpy(buf, src, bufsize);
		COMPILER_BARRIER();
		temp = vm_datapart_write_unsafe(self,
		                                buf,
		                                bufsize,
		                                split_bytes,
		                                dst_offset);
		if (!temp)
			break;
		src = (byte_t *)src + temp;
		result += temp;
		dst_offset += temp;
		num_bytes -= temp;
		if (bufsize > num_bytes)
			bufsize = num_bytes;
	}
	return result;
}

DECL_END

#ifndef __INTELLISENSE__
#define IO_READ 1
#define IO_PHYS 1
#include "datapart-read-write-base.c.inl"
#define IO_WRITE 1
#define IO_PHYS 1
#include "datapart-read-write-base.c.inl"
#define IO_READ 1
#include "datapart-read-write-base.c.inl"
#define IO_WRITE 1
#include "datapart-read-write-base.c.inl"
#endif


#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_VM_DATAPART_READ_WRITE_C_INL */
