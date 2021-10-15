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
#ifndef GUARD_KERNEL_CORE_FILESYS_NULL_C
#define GUARD_KERNEL_CORE_FILESYS_NULL_C 1

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/null.h>
#include <kernel/fs/ramfs.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>

#include <kos/dev.h>
#include <sys/io.h>

#include <stddef.h>
#include <stdint.h>

#include <libvio/api.h>

DECL_BEGIN

#ifdef KERNELSPACE_HIGHMEM
#define KERNELSPACE_MEMBASE ((uint64_t)KERNELSPACE_BASE)
#define KERNELSPACE_MEMSIZE ((uint64_t)(0 - KERNELSPACE_BASE))
#elif defined(KERNELSPACE_LOWMEM)
#define KERNELSPACE_MEMBASE ((uint64_t)0)
#define KERNELSPACE_MEMSIZE ((uint64_t)KERNELSPACE_END)
#else /* ... */
#define KERNELSPACE_MEMBASE (uint64_t)KERNELSPACE_BASE
#define KERNELSPACE_MEMSIZE ((uint64_t)KERNELSPACE_END - (uint64_t)KERNELSPACE_BASE)
#endif /* !... */


/************************************************************************/
/* Read/Write to/from physical memory (/dev/mem)                        */
/************************************************************************/

/* Construct a new mmap-able mem-part for /dev/mem */
PRIVATE ATTR_RETNONNULL NONNULL((1)) REF struct mpart *KCALL
devmem_newpart(struct mfile *__restrict UNUSED(self),
             PAGEDIR_PAGEALIGNED pos_t minaddr,
             PAGEDIR_PAGEALIGNED size_t num_bytes) {
	REF struct mpart *result;
	result = (REF struct mpart *)kmalloc(sizeof(struct mpart), GFP_LOCKED | GFP_PREFLT);
	/* (re-)configure the part to point to static, physical memory. */
	result->mp_flags        = MPART_F_MLOCK | MPART_F_MLOCK_FROZEN | MPART_F_NOFREE;
	result->mp_state        = MPART_ST_MEM;
	result->mp_blkst_ptr    = NULL; /* Disable block status (thus having the system act like all
	                                 * blocks  were using `MPART_BLOCK_ST_CHNG' as their status) */
	result->mp_mem.mc_start = (physpage_t)minaddr >> PAGESHIFT;
	result->mp_mem.mc_size  = num_bytes >> PAGESHIFT;
	result->mp_meta         = NULL;
	return result;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devmem_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
             size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	copyfromphys(dst, (physaddr_t)addr, num_bytes);
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devmem_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
              size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		copyfromphys(ent.ive_base, (physaddr_t)addr, ent.ive_size);
		addr += ent.ive_size;
	}
	return (size_t)num_bytes;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devmem_pwrite(struct mfile *__restrict UNUSED(self), USER CHECKED void const *src,
              size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	copytophys((physaddr_t)addr, src, num_bytes);
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devmem_pwritev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict src,
               size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, src) {
		copytophys((physaddr_t)addr, ent.ive_base, ent.ive_size);
		addr += ent.ive_size;
	}
	return (size_t)num_bytes;
}

PRIVATE struct mfile_stream_ops const devmem_stream_ops = {
	.mso_pread   = &devmem_pread,
	.mso_preadv  = &devmem_preadv,
	.mso_pwrite  = &devmem_pwrite,
	.mso_pwritev = &devmem_pwritev,
};



/************************************************************************/
/* General-purpose, zero-initialized memory (/dev/zero)                 */
/************************************************************************/
INTDEF NONNULL((1)) void /* From "memory/mman/mfile.c" */
NOTHROW(KCALL mfile_zero_loadpages)(struct mfile *__restrict self,
                                    pos_t addr, physaddr_t buf, size_t num_bytes);
#define devzero_loadpages mfile_zero_loadpages

PRIVATE struct mfile_stream_ops const devzero_stream_ops = {}; /* TODO */


PRIVATE struct mfile_stream_ops const devkmem_stream_ops = {}; /* TODO */
PRIVATE struct mfile_stream_ops const devnull_stream_ops = {}; /* TODO */
PRIVATE struct mfile_stream_ops const devport_stream_ops = {}; /* TODO */
PRIVATE struct mfile_stream_ops const devfull_stream_ops = {}; /* TODO */
PRIVATE struct mfile_stream_ops const devrandom_stream_ops = {}; /* TODO */
PRIVATE struct mfile_stream_ops const devurandom_stream_ops = {}; /* TODO */
PRIVATE struct mfile_stream_ops const devkmsg_stream_ops = {}; /* TODO */






#ifdef LIBVIO_CONFIG_ENABLED
#define IF_VIO_ENABLED(...) __VA_ARGS__
#else /* LIBVIO_CONFIG_ENABLED */
#define IF_VIO_ENABLED(...) /* nothing */
#endif /* !LIBVIO_CONFIG_ENABLED */
#define DEVICE_OPS_INIT(mo_newpart, mo_loadblocks, mo_stream, mo_vio)               \
	{                                                                               \
		{                                                                           \
			{                                                                       \
				{                                                                   \
					(void(KCALL *)(struct mfile *__restrict))(void *)(uintptr_t)-1, \
					mo_newpart, mo_loadblocks, NULL, &fnode_v_changed, mo_stream,   \
					IF_VIO_ENABLED(mo_vio)                                          \
				},                                                                  \
				&device_v_wrattr                                                    \
			}                                                                       \
		}                                                                           \
	}
INTERN struct device_ops const dev_mem_ops     = DEVICE_OPS_INIT(&devmem_newpart, NULL, &devmem_stream_ops, NULL);
INTERN struct device_ops const dev_kmem_ops    = DEVICE_OPS_INIT(NULL, NULL, &devkmem_stream_ops, NULL);
INTERN struct device_ops const dev_null_ops    = DEVICE_OPS_INIT(NULL, &devzero_loadpages, &devnull_stream_ops, NULL);
INTERN struct device_ops const dev_port_ops    = DEVICE_OPS_INIT(NULL, NULL, &devport_stream_ops, NULL);
INTERN struct device_ops const dev_zero_ops    = DEVICE_OPS_INIT(NULL, &devzero_loadpages, &devzero_stream_ops, NULL);
INTERN struct device_ops const dev_full_ops    = DEVICE_OPS_INIT(NULL, &devzero_loadpages, &devfull_stream_ops, NULL);
INTERN struct device_ops const dev_random_ops  = DEVICE_OPS_INIT(NULL, NULL, &devrandom_stream_ops, NULL);
INTERN struct device_ops const dev_urandom_ops = DEVICE_OPS_INIT(NULL, NULL, &devurandom_stream_ops, NULL);
INTERN struct device_ops const dev_kmsg_ops    = DEVICE_OPS_INIT(NULL, NULL, &devkmsg_stream_ops, NULL);
#undef DEVICE_OPS_INIT
#undef IF_VIO_ENABLED

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_NULL_C */
