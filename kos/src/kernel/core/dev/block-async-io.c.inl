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
#ifdef __INTELLISENSE__
#include "block.c"
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
//#define DEFINE_IO_SECTOR 1
//#define DEFINE_IO_VECTOR 1
//#define DEFINE_IO_PHYS 1
#endif /* __INTELLISENSE__ */

#include <kernel/aio.h>
#include <kernel/vm/phys.h>

#include <inttypes.h>

#if !defined(DEFINE_IO_READ) && !defined(DEFINE_IO_WRITE)
#error "Must #define DEFINE_IO_READ or DEFINE_IO_WRITE"
#elif defined(DEFINE_IO_READ) && defined(DEFINE_IO_WRITE)
#error "Must not #define both DEFINE_IO_READ and DEFINE_IO_WRITE"
#endif /* ... */


DECL_BEGIN

#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define DST_MEMSET(offset, byte, num_bytes) \
	aio_pbuffer_memset(buf, offset, byte, num_bytes)
#elif defined(DEFINE_IO_VECTOR)
#define DST_MEMSET(offset, byte, num_bytes) \
	aio_buffer_memset(buf, offset, byte, num_bytes)
#elif defined(DEFINE_IO_PHYS)
#define DST_MEMSET(offset, byte, num_bytes) \
	vm_memsetphys((buf) + (offset), byte, num_bytes)
#else /* ... */
#define DST_MEMSET(offset, byte, num_bytes) \
	memset((byte_t *)(buf) + (offset), byte, num_bytes)
#endif /* !... */
#endif /* DEFINE_IO_READ */



#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_readv_phys),                  \
	 (*(self)->bd_type.dt_readv_phys)(self, buf, total_sectors, device_lba, aio))
#elif defined(DEFINE_IO_VECTOR)
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_readv),                       \
	 (*(self)->bd_type.dt_readv)(self, buf, total_sectors, device_lba, aio))
#elif defined(DEFINE_IO_PHYS)
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_read_phys),                   \
	 (*(self)->bd_type.dt_read_phys)(self, buf, total_sectors, device_lba, aio))
#else /* ... */
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_read),                        \
	 (*(self)->bd_type.dt_read)(self, buf, total_sectors, device_lba, aio))
#endif /* !... */
#else  /* DEFINE_IO_READ */
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_writev_phys),                 \
	 (*(self)->bd_type.dt_writev_phys)(self, buf, total_sectors, device_lba, aio))
#elif defined(DEFINE_IO_VECTOR)
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_writev),                      \
	 (*(self)->bd_type.dt_writev)(self, buf, total_sectors, device_lba, aio))
#elif defined(DEFINE_IO_PHYS)
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_write_phys),                  \
	 (*(self)->bd_type.dt_write_phys)(self, buf, total_sectors, device_lba, aio))
#else /* ... */
#define INVOKE_IO(self, buf, total_sectors, device_lba, aio) \
	(assert((self)->bd_type.dt_write),                       \
	 (*(self)->bd_type.dt_write)(self, buf, total_sectors, device_lba, aio))
#endif /* !... */
#endif /* !DEFINE_IO_READ */


#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_readv_phys(self, dst, num_bytes, device_position)
#elif defined(DEFINE_IO_VECTOR)
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_readv(self, dst, num_bytes, device_position)
#elif defined(DEFINE_IO_PHYS)
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_read_phys(self, dst, num_bytes, device_position)
#else /* ... */
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_read(self, dst, num_bytes, device_position)
#endif /* !... */
#else /* DEFINE_IO_READ */
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_writev_phys(self, dst, num_bytes, device_position)
#elif defined(DEFINE_IO_VECTOR)
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_writev(self, dst, num_bytes, device_position)
#elif defined(DEFINE_IO_PHYS)
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_write_phys(self, dst, num_bytes, device_position)
#else /* ... */
#define INVOKE_BUFFERED_IO(self, dst, num_bytes, device_position) \
	block_device_write(self, dst, num_bytes, device_position)
#endif /* !... */
#endif /* !DEFINE_IO_READ */






#ifdef DEFINE_IO_READ
#ifdef DEFINE_IO_SECTOR
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_areadv_phys_sector)(struct block_device *__restrict self,
                                                struct aio_pbuffer *__restrict buf,
                                                size_t num_sectors, lba_t addr,
                                                /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_areadv_sector)(struct block_device *__restrict self,
                                           struct aio_buffer *__restrict buf,
                                           size_t num_sectors, lba_t addr,
                                           /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_PHYS)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_aread_phys_sector)(struct block_device *__restrict self,
                                               physaddr_t buf, size_t num_sectors, lba_t addr,
                                               /*out*/ struct aio_handle *__restrict aio)
#else /* ... */
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_aread_sector)(struct block_device *__restrict self,
                                          USER CHECKED void *buf, size_t num_sectors,
                                          lba_t addr, /*out*/ struct aio_handle *__restrict aio)
#endif /* !... */
#else /* DEFINE_IO_SECTOR */
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_areadv_phys)(struct block_device *__restrict self,
                                         struct aio_pbuffer *__restrict buf, size_t num_bytes,
                                         pos_t device_position,
                                         /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_areadv)(struct block_device *__restrict self,
                                    struct aio_buffer *__restrict buf, size_t num_bytes,
                                    pos_t device_position,
                                    /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_PHYS)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_aread_phys)(struct block_device *__restrict self,
                                        physaddr_t buf, size_t num_bytes,
                                        pos_t device_position,
                                        /*out*/ struct aio_handle *__restrict aio)
#else /* ... */
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_aread)(struct block_device *__restrict self,
                                   USER CHECKED void *buf, size_t num_bytes,
                                   pos_t device_position,
                                   /*out*/ struct aio_handle *__restrict aio)
#endif /* !... */
#endif /* !DEFINE_IO_SECTOR */
#elif defined(DEFINE_IO_WRITE)
#ifdef DEFINE_IO_SECTOR
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awritev_phys_sector)(struct block_device *__restrict self,
                                                 struct aio_pbuffer *__restrict buf,
                                                 size_t num_sectors, lba_t addr,
                                                 /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awritev_sector)(struct block_device *__restrict self,
                                            struct aio_buffer *__restrict buf,
                                            size_t num_sectors, lba_t addr,
                                            /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_PHYS)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awrite_phys_sector)(struct block_device *__restrict self,
                                                physaddr_t buf, size_t num_sectors,
                                                lba_t addr, /*out*/ struct aio_handle *__restrict aio)
#else /* ... */
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awrite_sector)(struct block_device *__restrict self,
                                           USER CHECKED void const *buf, size_t num_sectors,
                                           lba_t addr, /*out*/ struct aio_handle *__restrict aio)
#endif /* !... */
#else /* DEFINE_IO_SECTOR */
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awritev_phys)(struct block_device *__restrict self,
                                          struct aio_pbuffer *__restrict buf,
                                          size_t num_bytes, pos_t device_position,
                                          /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_VECTOR)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awritev)(struct block_device *__restrict self,
                                     struct aio_buffer *__restrict buf,
                                     size_t num_bytes, pos_t device_position,
                                     /*out*/ struct aio_handle *__restrict aio)
#elif defined(DEFINE_IO_PHYS)
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awrite_phys)(struct block_device *__restrict self,
                                         physaddr_t buf, size_t num_bytes,
                                         pos_t device_position,
                                         /*out*/ struct aio_handle *__restrict aio)
#else /* ... */
PUBLIC NONNULL((1, 5)) void
NOTHROW(KCALL _block_device_awrite)(struct block_device *__restrict self,
                                    USER CHECKED void const *buf, size_t num_bytes,
                                    pos_t device_position,
                                    /*out*/ struct aio_handle *__restrict aio)
#endif /* !... */
#endif /* !DEFINE_IO_SECTOR */
#endif /* ... */

#ifdef DEFINE_IO_READ
		THROWS_INDIRECT(E_IOERROR, E_BADALLOC, ...)
#elif defined(DEFINE_IO_WRITE)
		THROWS_INDIRECT(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...)
#endif /* ... */
{
#ifdef DEFINE_IO_SECTOR
#ifdef DEFINE_IO_VECTOR
#ifdef DEFINE_IO_PHYS
	assertf(aio_pbuffer_size(buf) == num_sectors * self->bd_sector_size,
	        "aio_pbuffer_size(buf)              = %" PRIuSIZ "\n"
	        "num_sectors                        = %" PRIuSIZ "\n"
	        "self->bd_sector_size               = %" PRIuSIZ "\n"
	        "num_sectors * self->bd_sector_size = %" PRIuSIZ "\n",
	        (size_t)aio_pbuffer_size(buf),
	        (size_t)num_sectors,
	        (size_t)self->bd_sector_size,
	        (size_t)(num_sectors * self->bd_sector_size));
#else /* DEFINE_IO_PHYS */
	assertf(aio_buffer_size(buf) == num_sectors * self->bd_sector_size,
	        "aio_buffer_size(buf)               = %" PRIuSIZ "\n"
	        "num_sectors                        = %" PRIuSIZ "\n"
	        "self->bd_sector_size               = %" PRIuSIZ "\n"
	        "num_sectors * self->bd_sector_size = %" PRIuSIZ "\n",
	        (size_t)aio_buffer_size(buf),
	        (size_t)num_sectors,
	        (size_t)self->bd_sector_size,
	        (size_t)(num_sectors * self->bd_sector_size));
#endif /* !DEFINE_IO_PHYS */
#endif /* DEFINE_IO_VECTOR */
	{
		lba_t end_addr;
		if unlikely(!num_sectors)
			goto done_success;
		/* Deal with memory that was accessed outside the bounds of the block-device. */
		TRY {
#ifdef DEFINE_IO_WRITE
			if unlikely(self->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
				THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
#endif /* DEFINE_IO_WRITE */
			if unlikely(OVERFLOW_UADD(addr, num_sectors, &end_addr) ||
			            end_addr > self->bd_sector_count) {
#ifdef DEFINE_IO_WRITE
				THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
#else /* DEFINE_IO_WRITE */
				size_t new_num_sectors;
				if (addr >= self->bd_sector_count) {
					DST_MEMSET(0, 0, num_sectors * self->bd_sector_size);
					goto done_success;
				}
				new_num_sectors = (size_t)(self->bd_sector_count - addr);
				assert(new_num_sectors < num_sectors);
				DST_MEMSET((new_num_sectors * self->bd_sector_size), 0,
				           (num_sectors - new_num_sectors) * self->bd_sector_size);
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
				{
					struct aio_pbuffer view;
					aio_pbuffer_init_view_before(&view, buf, new_num_sectors * self->bd_sector_size);
					assert(self->bd_type.dt_readv_phys);
					(*self->bd_type.dt_readv_phys)(self, &view, num_sectors, addr, aio);
					return;
				}
#elif defined(DEFINE_IO_VECTOR)
				{
					struct aio_buffer view;
					aio_buffer_init_view_before(&view, buf, new_num_sectors * self->bd_sector_size);
					assert(self->bd_type.dt_readv);
					(*self->bd_type.dt_readv)(self, &view, num_sectors, addr, aio);
					return;
				}
#else /* DEFINE_IO_VECTOR */
				num_sectors = new_num_sectors;
#endif /* !DEFINE_IO_VECTOR */
#endif /* !DEFINE_IO_WRITE */
			}
			INVOKE_IO(self, buf, num_sectors, addr, aio);
		} EXCEPT {
			aio_handle_init_noop(aio, AIO_COMPLETION_FAILURE);
		}
	}
	return;
done_success:
	aio_handle_init_noop(aio, AIO_COMPLETION_SUCCESS);
#else /* DEFINE_IO_SECTOR */
	pos_t end_addr;
	lba_t device_lba;
	size_t unaligned_head;
	size_t unaligned_tail;
	size_t total_sectors;
#ifdef DEFINE_IO_VECTOR
#ifdef DEFINE_IO_PHYS
	assertf(aio_pbuffer_size(buf) == num_bytes,
	        "aio_pbuffer_size(buf) = %" PRIuSIZ "\n"
	        "num_bytes             = %" PRIuSIZ "\n",
	        (size_t)aio_pbuffer_size(buf), (size_t)num_bytes);
#else /* DEFINE_IO_PHYS */
	assertf(aio_buffer_size(buf) == num_bytes,
	        "aio_buffer_size(buf) = %" PRIuSIZ "\n"
	        "num_bytes            = %" PRIuSIZ "\n",
	        (size_t)aio_buffer_size(buf), (size_t)num_bytes);
#endif /* !DEFINE_IO_PHYS */
#endif /* !DEFINE_IO_VECTOR */
	if unlikely(!num_bytes)
		goto done_success;
	TRY {
#ifdef DEFINE_IO_WRITE
		if unlikely(self->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
			THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
#endif /* DEFINE_IO_WRITE */
		if unlikely(OVERFLOW_UADD(device_position, num_bytes, &end_addr) ||
		            end_addr > self->bd_total_bytes) {
#ifdef DEFINE_IO_WRITE
			THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
#else /* DEFINE_IO_WRITE */
			size_t new_num_bytes;
			if (device_position >= self->bd_total_bytes) {
				DST_MEMSET(0, 0, num_bytes);
				return;
			}
			new_num_bytes = (size_t)(self->bd_total_bytes - device_position);
			assert(new_num_bytes < num_bytes);
			DST_MEMSET(new_num_bytes, 0, num_bytes - new_num_bytes);
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
			{
				struct aio_pbuffer view;
				aio_pbuffer_init_view_before(&view, buf, new_num_bytes * self->bd_sector_size);
				_block_device_areadv_phys(self, &view, new_num_bytes, device_position, aio);
				return;
			}
#elif defined(DEFINE_IO_VECTOR)
			{
				struct aio_buffer view;
				aio_buffer_init_view_before(&view, buf, new_num_bytes * self->bd_sector_size);
				_block_device_areadv(self, &view, new_num_bytes, device_position, aio);
				return;
			}
#else /* DEFINE_IO_VECTOR */
			num_bytes = new_num_bytes;
#endif /* !DEFINE_IO_VECTOR */
#endif /* !DEFINE_IO_WRITE */
		}
		/* Deal with partition offsets. */
		if likely(block_device_ispartition(self)) {
			device_position += ((struct block_device_partition *)self)->bp_minaddr;
			self = ((struct block_device_partition *)self)->bp_master;
			assert(!block_device_ispartition(self));
#ifdef DEFINE_IO_WRITE
			/* Also check the drive master for being read-only. */
			if unlikely(self->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
				THROW(E_IOERROR_READONLY, (uintptr_t)E_IOERROR_SUBSYSTEM_HARDDISK);
#endif /* DEFINE_IO_WRITE */
		}
		assert(self->bd_type.dt_write);
		assert(self->bd_type.dt_write_phys);
		assert(self->bd_type.dt_writev);
		assert(self->bd_type.dt_writev_phys);
		device_lba     = (lba_t)(device_position / self->bd_sector_size);
		unaligned_head = (size_t)(device_position % self->bd_sector_size);
		if unlikely(unaligned_head != 0)
			++device_lba;
		total_sectors  = (size_t)(num_bytes / self->bd_sector_size);
		unaligned_tail = (size_t)(num_bytes % self->bd_sector_size);
		if likely(!unaligned_head && !unaligned_tail) {
			assert(total_sectors != 0);
			INVOKE_IO(self, buf, total_sectors, device_lba, aio);
			return;
		}
		if (unaligned_head) {
#ifdef DEFINE_IO_VECTOR
#ifdef DEFINE_IO_PHYS
			struct aio_pbuffer view;
			aio_pbuffer_init_view_before(&view, buf, unaligned_head);
#else /* DEFINE_IO_PHYS */
			struct aio_buffer view;
			aio_buffer_init_view_before(&view, buf, unaligned_head);
#endif /* !DEFINE_IO_PHYS */
			INVOKE_BUFFERED_IO(self, &view, unaligned_head, device_position);
#else /* DEFINE_IO_VECTOR */
			INVOKE_BUFFERED_IO(self, buf, unaligned_head, device_position);
#endif /* !DEFINE_IO_VECTOR */
		}
		if (unaligned_tail) {
#ifdef DEFINE_IO_VECTOR
#ifdef DEFINE_IO_PHYS
			struct aio_pbuffer view;
			aio_pbuffer_init_view_after(&view, buf, num_bytes - unaligned_tail);
#else /* DEFINE_IO_PHYS */
			struct aio_buffer view;
			aio_buffer_init_view_after(&view, buf, num_bytes - unaligned_tail);
#endif /* !DEFINE_IO_PHYS */
			INVOKE_BUFFERED_IO(self, &view, unaligned_tail,
			                   (device_position + (pos_t)num_bytes) - (pos_t)unaligned_tail);
#elif defined(DEFINE_IO_PHYS)
			INVOKE_BUFFERED_IO(self, buf + num_bytes - unaligned_tail, unaligned_tail,
			                   (device_position + (pos_t)num_bytes) - (pos_t)unaligned_tail);
#else /* ... */
			INVOKE_BUFFERED_IO(self, (byte_t *)buf + num_bytes - unaligned_tail, unaligned_tail,
			                   (device_position + (pos_t)num_bytes) - (pos_t)unaligned_tail);
#endif /* !... */
		}
		if (total_sectors) {
#ifdef DEFINE_IO_VECTOR
#ifdef DEFINE_IO_PHYS
			struct aio_pbuffer view;
			aio_pbuffer_init_view(&view, buf, unaligned_head, total_sectors * self->bd_sector_size);
#else /* DEFINE_IO_PHYS */
			struct aio_buffer view;
			aio_buffer_init_view(&view, buf, unaligned_head, total_sectors * self->bd_sector_size);
#endif /* !DEFINE_IO_PHYS */
			INVOKE_IO(self, &view, total_sectors, device_lba, aio);
#elif defined(DEFINE_IO_PHYS)
			INVOKE_IO(self, buf + unaligned_head, total_sectors, device_lba, aio);
#else /* ... */
			INVOKE_IO(self, (byte_t *)buf + unaligned_head, total_sectors, device_lba, aio);
#endif /* !... */
		} else {
			/* All IO had to be performed synchronously. - Signal success to the AIO handle. */
			goto done_success;
		}
	} EXCEPT {
		aio_handle_init_noop(aio, AIO_COMPLETION_FAILURE);
	}
	return;
done_success:
	aio_handle_init_noop(aio, AIO_COMPLETION_SUCCESS);
#endif /* !DEFINE_IO_SECTOR */
}



#ifndef DEFINE_IO_SECTOR
PUBLIC NONNULL((1)) void
#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
(KCALL _block_device_readv_phys_sync)(struct block_device *__restrict self,
                                      struct aio_pbuffer *__restrict buf,
                                      size_t num_bytes, pos_t device_position)
#elif defined(DEFINE_IO_VECTOR)
(KCALL _block_device_readv_sync)(struct block_device *__restrict self,
                                 struct aio_buffer *__restrict buf,
                                 size_t num_bytes, pos_t device_position)
#elif defined(DEFINE_IO_PHYS)
(KCALL _block_device_read_phys_sync)(struct block_device *__restrict self,
                                     physaddr_t buf, size_t num_bytes,
                                     pos_t device_position)
#else /* ... */
(KCALL _block_device_read_sync)(struct block_device *__restrict self,
                                USER CHECKED void *buf, size_t num_bytes,
                                pos_t device_position)
#endif /* !... */
#else /* DEFINE_IO_READ */
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
(KCALL _block_device_writev_phys_sync)(struct block_device *__restrict self,
                                       struct aio_pbuffer *__restrict buf,
                                       size_t num_bytes, pos_t device_position)
#elif defined(DEFINE_IO_VECTOR)
(KCALL _block_device_writev_sync)(struct block_device *__restrict self,
                                  struct aio_buffer *__restrict buf,
                                  size_t num_bytes, pos_t device_position)
#elif defined(DEFINE_IO_PHYS)
(KCALL _block_device_write_phys_sync)(struct block_device *__restrict self,
                                      physaddr_t buf, size_t num_bytes,
                                      pos_t device_position)
#else /* ... */
(KCALL _block_device_write_sync)(struct block_device *__restrict self,
                                 USER CHECKED void const *buf,
                                 size_t num_bytes, pos_t device_position)
#endif /* !... */
#endif /* !DEFINE_IO_READ */
#ifdef DEFINE_IO_READ
#ifdef DEFINE_IO_PHYS
		THROWS(E_IOERROR, E_BADALLOC, ...)
#else /* DEFINE_IO_PHYS */
		THROWS(E_IOERROR, E_BADALLOC, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
#else /* DEFINE_IO_READ */
#ifdef DEFINE_IO_PHYS
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, ...)
#else /* DEFINE_IO_PHYS */
		THROWS(E_IOERROR, E_IOERROR_READONLY, E_IOERROR_BADBOUNDS, E_BADALLOC, E_SEGFAULT, ...)
#endif /* !DEFINE_IO_PHYS */
#endif /* !DEFINE_IO_READ */
{
	struct aio_handle_generic hand;
	aio_handle_generic_init(&hand);
#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
	_block_device_areadv_phys(self, buf, num_bytes, device_position, &hand);
#elif defined(DEFINE_IO_VECTOR)
	_block_device_areadv(self, buf, num_bytes, device_position, &hand);
#elif defined(DEFINE_IO_PHYS)
	_block_device_aread_phys(self, buf, num_bytes, device_position, &hand);
#else /* ... */
	_block_device_aread(self, buf, num_bytes, device_position, &hand);
#endif /* !... */
#else /* DEFINE_IO_READ */
#if defined(DEFINE_IO_VECTOR) && defined(DEFINE_IO_PHYS)
	_block_device_awritev_phys(self, buf, num_bytes, device_position, &hand);
#elif defined(DEFINE_IO_VECTOR)
	_block_device_awritev(self, buf, num_bytes, device_position, &hand);
#elif defined(DEFINE_IO_PHYS)
	_block_device_awrite_phys(self, buf, num_bytes, device_position, &hand);
#else /* ... */
	_block_device_awrite(self, buf, num_bytes, device_position, &hand);
#endif /* !... */
#endif /* !DEFINE_IO_READ */
	TRY {
		aio_handle_generic_waitfor(&hand);
		aio_handle_generic_checkerror(&hand);
	} EXCEPT {
		aio_handle_generic_fini(&hand);
		RETHROW();
	}
	aio_handle_generic_fini(&hand);
}
#endif /* !DEFINE_IO_SECTOR */


#undef DST_MEMSET
#undef INVOKE_BUFFERED_IO
#undef INVOKE_IO


#undef DEFINE_IO_PHYS
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_SECTOR
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_READ

DECL_END
