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
#ifdef __INTELLISENSE__
#include "fat.c"
#define DEFINE_IO_READ 1
//#define DEFINE_IO_WRITE 1
//#define DEFINE_IO_PHYS 1
//#define DEFINE_IO_VECTOR 1
#endif

#include <kernel/aio.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <string.h>

DECL_BEGIN

#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define FUNC0(x) x##VectorPhys
#elif defined(DEFINE_IO_VECTOR)
#define FUNC0(x) x##Vector
#elif defined(DEFINE_IO_PHYS)
#define FUNC0(x) x##Phys
#else
#define FUNC0(x) x
#endif
#ifdef DEFINE_IO_READ
#define FUNC1(x) FUNC0(x##ReadFromINode)
#define FUNC2(x) FUNC0(x##ReadFromRootDirectory)
#else /* DEFINE_IO_READ */
#define FUNC1(x) FUNC0(x##WriteToINode)
#define FUNC2(x) FUNC0(x##WriteToRootDirectory)
#endif /* !DEFINE_IO_READ */


#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define VECTOR_TYPE struct aio_pbuffer
#define BUFFER_TYPE struct aio_pbuffer *__restrict
#define DST_MEMSET(offset, byte, num_bytes) aio_pbuffer_memset(buf, offset, byte, num_bytes)
#elif defined(DEFINE_IO_VECTOR)
#define VECTOR_TYPE struct aio_buffer
#define BUFFER_TYPE struct aio_buffer *__restrict
#define DST_MEMSET(offset, byte, num_bytes) aio_buffer_memset(buf, offset, byte, num_bytes)
#elif defined(DEFINE_IO_PHYS)
#define BUFFER_TYPE vm_phys_t
#define DST_MEMSET(offset, byte, num_bytes) vm_memsetphys((buf) + (offset), byte, num_bytes)
#elif defined(DEFINE_IO_READ)
#define BUFFER_TYPE CHECKED USER void *
#define DST_MEMSET(offset, byte, num_bytes) memset((byte_t *)(buf) + (offset), byte, num_bytes)
#else
#define BUFFER_TYPE CHECKED USER void const *
#endif


#ifdef DEFINE_IO_READ
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_areadv_phys(dev, buf, num_bytes, device_position, aio)
#elif defined(DEFINE_IO_VECTOR)
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_areadv(dev, buf, num_bytes, device_position, aio)
#elif defined(DEFINE_IO_PHYS)
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_aread_phys(dev, buf, num_bytes, device_position, aio)
#else
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_aread(dev, buf, num_bytes, device_position, aio)
#endif
#else /* DEFINE_IO_READ */
#if defined(DEFINE_IO_PHYS) && defined(DEFINE_IO_VECTOR)
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_awritev_phys(dev, buf, num_bytes, device_position, aio)
#elif defined(DEFINE_IO_VECTOR)
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_awritev(dev, buf, num_bytes, device_position, aio)
#elif defined(DEFINE_IO_PHYS)
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_awrite_phys(dev, buf, num_bytes, device_position, aio)
#else
#define BLOCK_DEVICE_IO(dev, buf, num_bytes, device_position, aio) \
        block_device_awrite(dev, buf, num_bytes, device_position, aio)
#endif
#endif /* !DEFINE_IO_READ */


/* Read/Write to/from a given INode at the specified offset.
 * NOTE: These functions do not truncate/update the size value
 *       of the associated INode. However allocating an additional
 *       sector will cause `Fat32_WriteToINode()' to update the
 *       the `a_blocks' attribute of `self'.
 * NOTE: Attempting to read data from beyond the allocated end
 *       of an INode will yield all ZEROes.
 * NOTE: These functions must not be used for I/O operations
 *       on the root directory of a FAT12/FAT16 file system.
 * @throw: E_FILESYSTEM_ERROR.ERROR_FS_DISK_FULL: [...] */
INTERN NONNULL((1, 5)) void KCALL
FUNC1(Fat32_)(struct inode *__restrict self,
              BUFFER_TYPE buf, size_t bufsize, pos_t pos,
              struct aio_multihandle *__restrict aio) {
#ifdef DEFINE_IO_VECTOR
	VECTOR_TYPE view;
	VECTOR_TYPE view2;
#endif /* DEFINE_IO_VECTOR */
	FatSuperblock *fat = (FatSuperblock *)self->i_super;
	assert(fat != self || fat->f_type == FAT32);
	assert(sync_reading(self));
	if (!bufsize)
		return;
	for (;;) {
		struct aio_handle *handle;
		FatClusterIndex cluster;
		pos_t diskpos;
		size_t cluster_number = (size_t)(pos / fat->f_clustersize);
		size_t cluster_offset = (size_t)(pos % fat->f_clustersize);
		size_t max_io;
		assert(sync_reading(self));
		cluster = Fat_GetFileCluster(self, cluster_number,
#ifdef DEFINE_IO_READ
		                             FAT_GETCLUSTER_MODE_FNORMAL
#else /* DEFINE_IO_READ */
		                             FAT_GETCLUSTER_MODE_FCREATE |
		                             FAT_GETCLUSTER_MODE_FNOZERO
#endif /* !DEFINE_IO_READ */
		                             );
#ifdef DEFINE_IO_READ
		if (cluster >= fat->f_cluster_eof) {
			/* Read all ZEROes after EOF. */
			DST_MEMSET(0, 0, bufsize);
			return;
		}
#endif /* DEFINE_IO_READ */
		diskpos = FAT_CLUSTERADDR(fat, cluster);
		diskpos += cluster_offset;
		max_io = fat->f_clustersize - cluster_offset;
		/* Optimization: When reading large amounts of data, check if the
		 *               underlying disk chunks were allocated consecutively.
		 *               If they were, then we can simply do one continuous
		 *               read, processing more than one cluster at a time. */
		while (max_io < bufsize &&
		       Fat_GetFileCluster(self, cluster_number + 1,
#ifdef DEFINE_IO_READ
		                          FAT_GETCLUSTER_MODE_FNORMAL
#else /* DEFINE_IO_READ */
		                          FAT_GETCLUSTER_MODE_FCREATE |
		                          FAT_GETCLUSTER_MODE_FNOZERO
#endif /* !DEFINE_IO_READ */
		                          ) ==
		       cluster + 1) {
			max_io += fat->f_clustersize;
			++cluster_number;
			++cluster;
		}
		if (max_io > bufsize)
			max_io = bufsize;
		handle = aio_multihandle_allochandle(aio);
		BLOCK_DEVICE_IO(self->i_super->s_device,
		                buf,
		                max_io,
		                diskpos,
		                handle);
		if (max_io >= bufsize)
			break;
		bufsize -= max_io;
		pos += max_io;
#ifdef DEFINE_IO_VECTOR
		if (buf == &view) {
#ifdef DEFINE_IO_PHYS
			aio_pbuffer_init_view_after(&view2, &view, max_io);
#else /* DEFINE_IO_PHYS */
			aio_buffer_init_view_after(&view2, &view, max_io);
#endif /* !DEFINE_IO_PHYS */
			buf = &view2;
		} else {
#ifdef DEFINE_IO_PHYS
			aio_pbuffer_init_view_after(&view, buf, max_io);
#else /* DEFINE_IO_PHYS */
			aio_buffer_init_view_after(&view, buf, max_io);
#endif /* !DEFINE_IO_PHYS */
			buf = &view;
		}
#elif defined(DEFINE_IO_PHYS)
		buf += max_io;
#else
		buf = (byte_t *)buf + max_io;
#endif
	}
}

/* Same as the functions above, but used for
 * operating with the FAT12/16 root directory.
 * @throw: E_FILESYSTEM_ERROR.ERROR_FS_DISK_FULL:
 *         The given `pos + bufsize' extends beyond
 *         the max size of the root directory. */
INTERN NONNULL((1, 5)) void KCALL
FUNC2(Fat16_)(FatSuperblock *__restrict self,
              BUFFER_TYPE buf, size_t bufsize, pos_t pos,
              struct aio_multihandle *__restrict aio) {
	size_t max_io;
	struct aio_handle *handle;
	assert(self->i_super == self);
	assert(self->f_type != FAT32);
	max_io = self->i_fsdata->i16_root.f16_rootsiz;
	if (pos >= (pos_t)max_io) {
#ifdef DEFINE_IO_READ
		DST_MEMSET(0, 0, bufsize);
		return;
#else /* DEFINE_IO_READ */
		goto too_large;
#endif /* !DEFINE_IO_READ */
	}
	handle = aio_multihandle_allochandle(aio);
	max_io -= (size_t)pos;
	/* Clear out trailing memory. */
	if (max_io < bufsize) {
#ifdef DEFINE_IO_READ
		DST_MEMSET(max_io, 0, bufsize - max_io);
#ifdef DEFINE_IO_VECTOR
		{
			VECTOR_TYPE view;
#ifdef DEFINE_IO_PHYS
			aio_pbuffer_init_view_before(&view, buf, max_io);
#else /* DEFINE_IO_PHYS */
			aio_buffer_init_view_before(&view, buf, max_io);
#endif /* !DEFINE_IO_PHYS */
			BLOCK_DEVICE_IO(self->s_device,
			                &view,
			                max_io,
			                self->i_fsdata->i16_root.f16_rootpos + pos,
			                handle);
			return;
		}
#endif /* DEFINE_IO_VECTOR */
#else /* DEFINE_IO_READ */
		goto too_large;
#endif /* !DEFINE_IO_READ */
	} else {
		max_io = bufsize;
	}
	/* Read actual data. */
	BLOCK_DEVICE_IO(self->s_device,
	                buf,
	                max_io,
	                self->i_fsdata->i16_root.f16_rootpos + pos,
	                handle);
#ifndef DEFINE_IO_READ
	return;
too_large:
	THROW(E_FSERROR_DISK_FULL);
#endif /* !DEFINE_IO_READ */
}

/* Hybrid of the functions above:
 * Determine the type, then read from the INode. */
INTERN NONNULL((1, 5)) void KCALL
FUNC1(Fat_)(struct inode *__restrict self,
            BUFFER_TYPE buf, size_t bufsize, pos_t pos,
            struct aio_multihandle *__restrict aio) {
	if (self != self->i_super || ((FatSuperblock *)self)->f_type == FAT32) {
		FUNC1(Fat32_)(self, buf, bufsize, pos, aio);
	} else {
		FUNC2(Fat16_)((FatSuperblock *)self, buf, bufsize, pos, aio);
	}
}



DECL_END

#undef BLOCK_DEVICE_IO
#undef BUFFER_TYPE
#undef VECTOR_TYPE
#undef DST_MEMSET

#undef FUNC2
#undef FUNC1
#undef FUNC0

#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_READ

