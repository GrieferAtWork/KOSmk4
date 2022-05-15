/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_NULL_C
#define GUARD_KERNEL_CORE_FILESYS_NULL_C 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/driver.h>
#include <kernel/entropy.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/chrdev.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/null.h>
#include <kernel/fs/ramfs.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <kernel/syslog.h>
#include <kernel/user.h>
#include <sched/group.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <kos/dev.h>
#include <sys/filio.h>
#include <sys/io.h>
#include <sys/param.h> /* NBBY */
#include <sys/stat.h>

#include <assert.h>
#include <int128.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <libvio/vio.h>


DECL_BEGIN

/* TODO: All of the user-buffer-transfer  function below should be  interruptible,
 *       as  in: if the calling thread receives an RPC (even if it's a synchronous
 *       RPC),  then the copy operation should stop and return the # of bytes that
 *       were already copied. If no bytes were copied, throw E_INTERRUPT_USER_RPC,
 *       and if any were copied, return the # of bytes copied. */
#define interruptible_copyfromphys(dst, src, num_bytes) (copyfromphys(dst, src, num_bytes), num_bytes)
#define interruptible_copytophys(dst, src, num_bytes)   (copytophys(dst, src, num_bytes), num_bytes)
#define interruptible_bzero(dst, num_bytes)             (bzero(dst, num_bytes), num_bytes)
#define interruptible_memcpy(dst, src, num_bytes)       (memcpy(dst, src, num_bytes), num_bytes)
#define interruptible_insb(port, buf, num_bytes)        (insb(port, buf, num_bytes), num_bytes)
#define interruptible_outsb(port, buf, num_bytes)       (outsb(port, buf, num_bytes), num_bytes)


/************************************************************************/
/* Common stat() operator (populated with `boottime')                   */
/************************************************************************/

INTERN NONNULL((1)) void KCALL /* `INTERN' because also re-used for pre-defined mounts */
nullfile_v_stat(struct mfile *__restrict UNUSED(self),
                USER CHECKED struct stat *result) {
	result->st_atime     = boottime.tv_sec;
	result->st_atimensec = boottime.tv_nsec;
	result->st_mtime     = boottime.tv_sec;
	result->st_mtimensec = boottime.tv_nsec;
	result->st_ctime     = boottime.tv_sec;
	result->st_ctimensec = boottime.tv_nsec;
	result->st_btime     = boottime.tv_sec;
	result->st_btimensec = boottime.tv_nsec;
}




/************************************************************************/
/* Read/Write to/from physical memory (/dev/mem)                        */
/************************************************************************/

/* Construct a new mmap-able mem-part for /dev/mem */
PRIVATE ATTR_RETNONNULL NONNULL((1)) REF struct mpart *KCALL
devmem_v_newpart(struct mfile *__restrict UNUSED(self),
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
devmem_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
               size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_copyfromphys(dst, (physaddr_t)addr, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devmem_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                size_t UNUSED(num_bytes), pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		TRY {
			result += interruptible_copyfromphys(ent.ive_base, (physaddr_t)addr, ent.ive_size);
		} EXCEPT {
			if (was_thrown(E_INTERRUPT_USER_RPC) && result != 0)
				goto done;
			RETHROW();
		}
		addr += ent.ive_size;
	}
done:
	return (size_t)result;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devmem_v_pwrite(struct mfile *__restrict UNUSED(self), USER CHECKED void const *src,
                size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_copytophys((physaddr_t)addr, src, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devmem_v_pwritev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict src,
                 size_t UNUSED(num_bytes), pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, src) {
		TRY {
			result += interruptible_copytophys((physaddr_t)addr, ent.ive_base, ent.ive_size);
		} EXCEPT {
			if (was_thrown(E_INTERRUPT_USER_RPC) && result != 0)
				goto done;
			RETHROW();
		}
		addr += ent.ive_size;
	}
done:
	return (size_t)result;
}

PRIVATE BLOCKING NONNULL((1)) syscall_slong_t KCALL
devmem_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	switch (_IO_WITHSIZE(cmd, 0)) {

	case _IO_WITHSIZE(FIODTYPE, 0):
		return ioctl_intarg_setuint(cmd, arg, D_MEM);

	default: break;
	}
	return chrdev_v_ioctl(self, cmd, arg, mode);
}




PRIVATE struct mfile_stream_ops const devmem_stream_ops = {
	.mso_pread   = &devmem_v_pread,
	.mso_preadv  = &devmem_v_preadv,
	.mso_pwrite  = &devmem_v_pwrite,
	.mso_pwritev = &devmem_v_pwritev,
	.mso_stat    = &nullfile_v_stat,
	.mso_ioctl   = &devmem_v_ioctl,
};





/************************************************************************/
/* General-purpose, write-swallow file (/dev/null)                      */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devnull_v_read(struct mfile *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst),
               size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devnull_v_readv(struct mfile *__restrict UNUSED(self),
                struct iov_buffer *__restrict UNUSED(dst),
                size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devnull_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *UNUSED(dst),
                size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devnull_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(dst),
                 size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devnull_v_write(struct mfile *__restrict UNUSED(self),
                USER CHECKED void const *UNUSED(src),
                size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devnull_v_writev(struct mfile *__restrict UNUSED(self),
                 struct iov_buffer *__restrict UNUSED(src),
                 size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devnull_v_pwrite(struct mfile *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src),
                 size_t num_bytes, pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devnull_v_pwritev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(src),
                  size_t num_bytes, pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE NONNULL((1)) pos_t KCALL
devnull_v_seek(struct mfile *__restrict UNUSED(self), off_t UNUSED(offset),
               unsigned int UNUSED(whence)) THROWS(...) {
	return 0;
}

#define devnull_v_loadpages devzero_v_loadpages

PRIVATE struct mfile_stream_ops const devnull_stream_ops = {
	.mso_read    = &devnull_v_read,
	.mso_readv   = &devnull_v_readv,
	.mso_write   = &devnull_v_write,
	.mso_writev  = &devnull_v_writev,
	.mso_pread   = &devnull_v_pread,
	.mso_preadv  = &devnull_v_preadv,
	.mso_pwrite  = &devnull_v_pwrite,
	.mso_pwritev = &devnull_v_pwritev,
	.mso_seek    = &devnull_v_seek,
	.mso_stat    = &nullfile_v_stat,
	.mso_ioctl   = &chrdev_v_ioctl,
};





/************************************************************************/
/* General-purpose, zero-initialized memory (/dev/zero)                 */
/************************************************************************/
INTDEF NONNULL((1)) void /* From "memory/mman/mfile.c" */
NOTHROW(KCALL mfile_zero_loadpages)(struct mfile *__restrict self,
                                    pos_t addr, physaddr_t buf, size_t num_bytes,
                                    struct aio_multihandle *__restrict aio);
#define devzero_v_loadpages mfile_zero_loadpages

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devzero_v_read(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
               size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_bzero(dst, num_bytes);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devzero_readv(struct iov_buffer *__restrict dst, size_t UNUSED(num_bytes)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		TRY {
			result += interruptible_bzero(ent.ive_base, ent.ive_size);
		} EXCEPT {
			if (was_thrown(E_INTERRUPT_USER_RPC) && result != 0)
				goto done;
			RETHROW();
		}
	}
done:
	return (size_t)result;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devzero_v_readv(struct mfile *__restrict UNUSED(self),
                struct iov_buffer *__restrict dst,
                size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	return devzero_readv(dst, num_bytes);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devzero_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
                size_t num_bytes, pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_bzero(dst, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devzero_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                 size_t num_bytes, pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return devzero_readv(dst, num_bytes);
}

#define devzero_v_write     devnull_v_write
#define devzero_v_writev    devnull_v_writev
#define devzero_v_pwrite    devnull_v_pwrite
#define devzero_v_pwritev   devnull_v_pwritev
#define devzero_v_seek      devnull_v_seek

PRIVATE struct mfile_stream_ops const devzero_stream_ops = {
	.mso_read    = &devzero_v_read,
	.mso_readv   = &devzero_v_readv,
	.mso_write   = &devzero_v_write,
	.mso_writev  = &devzero_v_writev,
	.mso_pread   = &devzero_v_pread,
	.mso_preadv  = &devzero_v_preadv,
	.mso_pwrite  = &devzero_v_pwrite,
	.mso_pwritev = &devzero_v_pwritev,
	.mso_seek    = &devzero_v_seek,
	.mso_stat    = &nullfile_v_stat,
	.mso_ioctl   = &chrdev_v_ioctl,
};





/************************************************************************/
/* General-purpose, always-full file (/dev/full)                        */
/************************************************************************/
PRIVATE ATTR_NORETURN void KCALL throw_disk_full(void) {
	THROW(E_FSERROR_DISK_FULL);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devfull_v_write(struct mfile *__restrict UNUSED(self),
                USER CHECKED void const *UNUSED(src),
                size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) {
	throw_disk_full();
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devfull_v_writev(struct mfile *__restrict UNUSED(self),
                 struct iov_buffer *__restrict UNUSED(src),
                 size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) {
	throw_disk_full();
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devfull_v_pwrite(struct mfile *__restrict UNUSED(self), USER CHECKED void const *UNUSED(src),
                 size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	throw_disk_full();
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devfull_v_pwritev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict UNUSED(src),
                  size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	throw_disk_full();
}

#define devfull_v_read      devzero_v_read
#define devfull_v_readv     devzero_v_readv
#define devfull_v_pread     devzero_v_pread
#define devfull_v_preadv    devzero_v_preadv
#define devfull_v_seek      devzero_v_seek
#define devfull_v_loadpages devzero_v_loadpages
PRIVATE struct mfile_stream_ops const devfull_stream_ops = {
	.mso_read    = &devfull_v_read,
	.mso_readv   = &devfull_v_readv,
	.mso_write   = &devfull_v_write,
	.mso_writev  = &devfull_v_writev,
	.mso_pread   = &devfull_v_pread,
	.mso_preadv  = &devfull_v_preadv,
	.mso_pwrite  = &devfull_v_pwrite,
	.mso_pwritev = &devfull_v_pwritev,
	.mso_seek    = &devfull_v_seek,
	.mso_stat    = &nullfile_v_stat,
	.mso_ioctl   = &chrdev_v_ioctl,
};





/************************************************************************/
/* Full, unfiltered, kernel memory access (/dev/kmem)                   */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devkmem_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
                size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_memcpy(dst, (UNCHECKED void const *)(uintptr_t)addr, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devkmem_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                 size_t UNUSED(num_bytes), pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		TRY {
			result += interruptible_memcpy(ent.ive_base, (UNCHECKED void const *)(uintptr_t)addr, ent.ive_size);
		} EXCEPT {
			if (was_thrown(E_INTERRUPT_USER_RPC) && result != 0)
				goto done;
			RETHROW();
		}
		addr += ent.ive_size;
	}
done:
	return (size_t)result;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devkmem_v_pwrite(struct mfile *__restrict UNUSED(self), USER CHECKED void const *src,
                 size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_memcpy((UNCHECKED void *)(uintptr_t)addr, src, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devkmem_v_pwritev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                 size_t UNUSED(num_bytes), pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		TRY {
			result += interruptible_memcpy((UNCHECKED void *)(uintptr_t)addr, ent.ive_base, ent.ive_size);
		} EXCEPT {
			if (was_thrown(E_INTERRUPT_USER_RPC) && result != 0)
				goto done;
			RETHROW();
		}
		addr += ent.ive_size;
	}
done:
	return (size_t)result;
}

#define devkmem_v_ioctl devmem_v_ioctl

PRIVATE struct mfile_stream_ops const devkmem_stream_ops = {
	.mso_open    = &mfile_v_open,
	.mso_pread   = &devkmem_v_pread,
	.mso_preadv  = &devkmem_v_preadv,
	.mso_pwrite  = &devkmem_v_pwrite,
	.mso_pwritev = &devkmem_v_pwritev,
	.mso_stat    = &nullfile_v_stat,
	.mso_ioctl   = &devkmem_v_ioctl,
};

#ifdef LIBVIO_CONFIG_ENABLED
PRIVATE ATTR_PURE NONNULL((1)) uint8_t LIBVIO_CC
devkmem_v_rdb(struct vioargs *__restrict UNUSED(args), vio_addr_t addr) {
	return *(uint8_t const *)(uintptr_t)addr;
}

PRIVATE ATTR_PURE NONNULL((1)) uint16_t LIBVIO_CC
devkmem_v_rdw(struct vioargs *__restrict UNUSED(args), vio_addr_t addr) {
	return *(uint16_t const *)(uintptr_t)addr;
}

PRIVATE ATTR_PURE NONNULL((1)) uint32_t LIBVIO_CC
devkmem_v_rdl(struct vioargs *__restrict UNUSED(args), vio_addr_t addr) {
	return *(uint32_t const *)(uintptr_t)addr;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE ATTR_PURE NONNULL((1)) uint64_t LIBVIO_CC
devkmem_v_rdq(struct vioargs *__restrict UNUSED(args), vio_addr_t addr) {
	return *(uint64_t const *)(uintptr_t)addr;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE NONNULL((1)) void LIBVIO_CC
devkmem_v_wrb(struct vioargs *__restrict UNUSED(args), vio_addr_t addr, uint8_t value) {
	*(uint8_t *)(uintptr_t)addr = value;
}

PRIVATE NONNULL((1)) void LIBVIO_CC
devkmem_v_wrw(struct vioargs *__restrict UNUSED(args), vio_addr_t addr, uint16_t value) {
	*(uint16_t *)(uintptr_t)addr = value;
}

PRIVATE NONNULL((1)) void LIBVIO_CC
devkmem_v_wrl(struct vioargs *__restrict UNUSED(args), vio_addr_t addr, uint32_t value) {
	*(uint32_t *)(uintptr_t)addr = value;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE NONNULL((1)) void LIBVIO_CC
devkmem_v_wrq(struct vioargs *__restrict UNUSED(args), vio_addr_t addr, uint64_t value) {
	*(uint64_t *)(uintptr_t)addr = value;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE NONNULL((1)) uint8_t LIBVIO_CC
devkmem_v_cmpxchb(struct vioargs *__restrict UNUSED(args), vio_addr_t addr,
                  uint8_t oldvalue, uint8_t newvalue, bool UNUSED(atomic)) {
	return ATOMIC_CMPXCH_VAL(*(uint8_t *)(uintptr_t)addr, oldvalue, newvalue);
}

PRIVATE NONNULL((1)) uint16_t LIBVIO_CC
devkmem_v_cmpxchw(struct vioargs *__restrict UNUSED(args), vio_addr_t addr,
                  uint16_t oldvalue, uint16_t newvalue, bool UNUSED(atomic)) {
	return ATOMIC_CMPXCH_VAL(*(uint16_t *)(uintptr_t)addr, oldvalue, newvalue);
}

PRIVATE NONNULL((1)) uint32_t LIBVIO_CC
devkmem_v_cmpxchl(struct vioargs *__restrict UNUSED(args), vio_addr_t addr,
                  uint32_t oldvalue, uint32_t newvalue, bool UNUSED(atomic)) {
	return ATOMIC_CMPXCH_VAL(*(uint32_t *)(uintptr_t)addr, oldvalue, newvalue);
}

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
PRIVATE NONNULL((1)) uint64_t LIBVIO_CC
devkmem_v_cmpxchq(struct vioargs *__restrict UNUSED(args), vio_addr_t addr,
                  uint64_t oldvalue, uint64_t newvalue, bool UNUSED(atomic)) {
	return ATOMIC_CMPXCH_VAL(*(uint64_t *)(uintptr_t)addr, oldvalue, newvalue);
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#if 1
#define P_devkmem_v_cmpxchx NULL
#else
#define P_devkmem_v_cmpxchx (&devkmem_v_cmpxchx)
PRIVATE NONNULL((1)) uint128_t LIBVIO_CC
devkmem_v_cmpxchx(struct vioargs *__restrict UNUSED(args), vio_addr_t addr,
                  uint128_t oldvalue, uint128_t newvalue, bool UNUSED(atomic)) {
#ifndef __INTELLISENSE__
	return ATOMIC_CMPXCH_VAL(*(uint128_t *)(uintptr_t)addr, oldvalue, newvalue);
#endif /* !__INTELLISENSE__ */
}
#endif
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

PRIVATE struct vio_ops const devkmem_vio_ops = {
	VIO_CALLBACK_INIT_READ(&devkmem_v_rdb, &devkmem_v_rdw, &devkmem_v_rdl, &devkmem_v_rdq),
	VIO_CALLBACK_INIT_WRITE(&devkmem_v_wrb, &devkmem_v_wrw, &devkmem_v_wrl, &devkmem_v_wrq),
	VIO_CALLBACK_INIT_CMPXCH(&devkmem_v_cmpxchb, &devkmem_v_cmpxchw, &devkmem_v_cmpxchl, &devkmem_v_cmpxchq, P_devkmem_v_cmpxchx),
};
#endif /* LIBVIO_CONFIG_ENABLED */





/************************************************************************/
/* Full, unfiltered, system port access (/dev/port)                     */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devport_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
                size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_insb((port_t)addr, dst, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devport_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                 size_t UNUSED(num_bytes), pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		TRY {
			result += interruptible_insb((port_t)addr, ent.ive_base, ent.ive_size);
		} EXCEPT {
			if (was_thrown(E_INTERRUPT_USER_RPC) && result != 0)
				goto done;
			RETHROW();
		}
		addr += ent.ive_size;
	}
done:
	return (size_t)result;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devport_v_pwrite(struct mfile *__restrict UNUSED(self), USER CHECKED void const *src,
                 size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	return interruptible_outsb((port_t)addr, src, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devport_v_pwritev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                 size_t UNUSED(num_bytes), pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		TRY {
			result += interruptible_outsb((port_t)addr, ent.ive_base, ent.ive_size);
		} EXCEPT {
			if (was_thrown(E_INTERRUPT_USER_RPC) && result != 0)
				goto done;
			RETHROW();
		}
		addr += ent.ive_size;
	}
done:
	return (size_t)result;
}

PRIVATE struct mfile_stream_ops const devport_stream_ops = {
	.mso_open    = &mfile_v_open,
	.mso_pread   = &devport_v_pread,
	.mso_preadv  = &devport_v_preadv,
	.mso_pwrite  = &devport_v_pwrite,
	.mso_pwritev = &devport_v_pwritev,
	.mso_stat    = &nullfile_v_stat,
	.mso_ioctl   = &chrdev_v_ioctl,
};

#ifdef LIBVIO_CONFIG_ENABLED
PRIVATE NONNULL((1)) uint8_t LIBVIO_CC
devport_v_rdb(struct vioargs *__restrict UNUSED(args), vio_addr_t addr) {
	return inb((port_t)addr);
}

PRIVATE NONNULL((1)) uint16_t LIBVIO_CC
devport_v_rdw(struct vioargs *__restrict UNUSED(args), vio_addr_t addr) {
	return inw((port_t)addr);
}

PRIVATE NONNULL((1)) uint32_t LIBVIO_CC
devport_v_rdl(struct vioargs *__restrict UNUSED(args), vio_addr_t addr) {
	return inl((port_t)addr);
}

PRIVATE NONNULL((1)) void LIBVIO_CC
devport_v_wrb(struct vioargs *__restrict UNUSED(args), vio_addr_t addr, uint8_t value) {
	outb((port_t)addr, value);
}

PRIVATE NONNULL((1)) void LIBVIO_CC
devport_v_wrw(struct vioargs *__restrict UNUSED(args), vio_addr_t addr, uint16_t value) {
	outw((port_t)addr, value);
}

PRIVATE NONNULL((1)) void LIBVIO_CC
devport_v_wrl(struct vioargs *__restrict UNUSED(args), vio_addr_t addr, uint32_t value) {
	outl((port_t)addr, value);
}

PRIVATE struct vio_ops const devport_vio_ops = {
	VIO_CALLBACK_INIT_READ(&devport_v_rdb, &devport_v_rdw, &devport_v_rdl, NULL),
	VIO_CALLBACK_INIT_WRITE(&devport_v_wrb, &devport_v_wrw, &devport_v_wrl, NULL),
};
#endif /* LIBVIO_CONFIG_ENABLED */





/************************************************************************/
/* True random number generator access (/dev/random)                    */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devrandom_readv(struct iov_buffer *__restrict dst, iomode_t mode) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		size_t part;
		if (!ent.ive_size)
			continue;
		part = entropy_read(ent.ive_base, ent.ive_size, mode);
		if (!part)
			break;
		result += part;
		/* Don't keep blocking if at least 1 byte was read! */
		mode |= IO_NONBLOCK | IO_NODATAZERO;
	}
	return (size_t)result;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devrandom_v_read(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
                 size_t num_bytes, iomode_t mode) THROWS(...) {
	return entropy_read(dst, num_bytes, mode);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devrandom_v_readv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                  size_t UNUSED(num_bytes), iomode_t mode) THROWS(...) {
	return devrandom_readv(dst, mode);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devrandom_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
                  size_t num_bytes, pos_t UNUSED(addr), iomode_t mode) THROWS(...) {
	return entropy_read(dst, num_bytes, mode);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devrandom_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                   size_t UNUSED(num_bytes), pos_t UNUSED(addr), iomode_t mode) THROWS(...) {
	return devrandom_readv(dst, mode);
}

PRIVATE NONNULL((1)) void KCALL
devrandom_v_pollconnect(struct mfile *__restrict UNUSED(self),
                        poll_mode_t what)
		THROWS(...) {
	if (what & POLLINMASK) {
		task_connect_for_poll(&entropy_request_sig);
		/* Make sure that the signal is broadcast once
		 * at least NBBY  bits have become  available. */
		for (;;) {
			size_t oldval;
			oldval = ATOMIC_READ(entropy_request_bits);
			if (oldval <= NBBY)
				break;
			if (ATOMIC_CMPXCH_WEAK(entropy_request_bits,
			                       oldval, NBBY))
				break;
		}
	}
}

PRIVATE WUNUSED NONNULL((1)) poll_mode_t KCALL
devrandom_v_polltest(struct mfile *__restrict UNUSED(self),
                     poll_mode_t what)
		THROWS(...) {
	/* Wait for non-deterministic random data to become available! */
	if (what & POLLINMASK) {
		if (ATOMIC_READ(entropy_bits) >= NBBY)
			return what & POLLINMASK;
	}
	return 0;
}

PRIVATE NONNULL((1)) void KCALL
devrandom_v_stat(struct mfile *__restrict self,
                 USER CHECKED struct stat *result)
		THROWS(...) {
	/* Expose the # of available entropy bytes via stat. */
	result->st_size = ATOMIC_READ(entropy_bits) / NBBY;

	/* Forward to filling in timestamp information. */
	nullfile_v_stat(self, result);
}


PRIVATE struct mfile_stream_ops const devrandom_stream_ops = {
	.mso_read        = &devrandom_v_read,
	.mso_readv       = &devrandom_v_readv,
	.mso_pread       = &devrandom_v_pread,
	.mso_preadv      = &devrandom_v_preadv,
	.mso_stat        = &devrandom_v_stat,
	.mso_pollconnect = &devrandom_v_pollconnect,
	.mso_polltest    = &devrandom_v_polltest,
	.mso_ioctl       = &chrdev_v_ioctl,
};

#ifdef LIBVIO_CONFIG_ENABLED
PRIVATE NONNULL((1)) uint8_t LIBVIO_CC
devrandom_v_rdb(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint8_t result;
	entropy_readall(&result, sizeof(result));
	return result;
}

PRIVATE NONNULL((1)) uint16_t LIBVIO_CC
devrandom_v_rdw(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint16_t result;
	entropy_readall(&result, sizeof(result));
	return result;
}

PRIVATE NONNULL((1)) uint32_t LIBVIO_CC
devrandom_v_rdl(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint32_t result;
	entropy_readall(&result, sizeof(result));
	return result;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE NONNULL((1)) uint64_t LIBVIO_CC
devrandom_v_rdq(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint64_t result;
	entropy_readall(&result, sizeof(result));
	return result;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE struct vio_ops const devrandom_vio_ops = {
	VIO_CALLBACK_INIT_READ(&devrandom_v_rdb, &devrandom_v_rdw,
	                       &devrandom_v_rdl, &devrandom_v_rdq),
};
#endif /* LIBVIO_CONFIG_ENABLED */





/************************************************************************/
/* Pseudo (unlimited) random number generator access (/dev/urandom)     */
/************************************************************************/
PRIVATE NONNULL((1)) void KCALL
devurandom_readv(struct iov_buffer *__restrict dst) THROWS(...) {
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, dst) {
		urandom_read(ent.ive_base, ent.ive_size);
	}
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devurandom_v_read(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
                 size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	urandom_read(dst, num_bytes);
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devurandom_v_readv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                  size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	devurandom_readv(dst);
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devurandom_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
                  size_t num_bytes, pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	urandom_read(dst, num_bytes);
	return num_bytes;
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devurandom_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                   size_t num_bytes, pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	devurandom_readv(dst);
	return num_bytes;
}


PRIVATE struct mfile_stream_ops const devurandom_stream_ops = {
	.mso_read   = &devurandom_v_read,
	.mso_readv  = &devurandom_v_readv,
	.mso_pread  = &devurandom_v_pread,
	.mso_preadv = &devurandom_v_preadv,
	.mso_stat   = &nullfile_v_stat,
	.mso_ioctl  = &chrdev_v_ioctl,
};

#ifdef LIBVIO_CONFIG_ENABLED
PRIVATE NONNULL((1)) uint8_t LIBVIO_CC
devurandom_v_rdb(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint8_t result;
	urandom_read(&result, sizeof(result));
	return result;
}

PRIVATE NONNULL((1)) uint16_t LIBVIO_CC
devurandom_v_rdw(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint16_t result;
	urandom_read(&result, sizeof(result));
	return result;
}

PRIVATE NONNULL((1)) uint32_t LIBVIO_CC
devurandom_v_rdl(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint32_t result;
	urandom_read(&result, sizeof(result));
	return result;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE NONNULL((1)) uint64_t LIBVIO_CC
devurandom_v_rdq(struct vioargs *__restrict UNUSED(args), vio_addr_t UNUSED(addr)) {
	uint64_t result;
	urandom_read(&result, sizeof(result));
	return result;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE struct vio_ops const devurandom_vio_ops = {
	VIO_CALLBACK_INIT_READ(&devurandom_v_rdb, &devurandom_v_rdw,
	                       &devurandom_v_rdl, &devurandom_v_rdq),
};
#endif /* LIBVIO_CONFIG_ENABLED */





/************************************************************************/
/* Raw output to the system log (/dev/kmsg)                             */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devkmsg_v_write(struct mfile *__restrict UNUSED(self),
                USER CHECKED void const *src,
                size_t num_bytes, iomode_t UNUSED(mode)) THROWS(...) {
	return (size_t)syslog_printer(SYSLOG_LEVEL_RAW, (char const *)src, num_bytes);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devkmsg_v_writev(struct mfile *__restrict UNUSED(self),
                 struct iov_buffer *__restrict src,
                 size_t UNUSED(num_bytes), iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, src) {
		result += (size_t)syslog_printer(SYSLOG_LEVEL_RAW,
		                                 (char const *)ent.ive_base,
		                                 ent.ive_size);
	}
	return result;
}

PRIVATE struct mfile_stream_ops const devkmsg_stream_ops = {
	.mso_write  = &devkmsg_v_write,
	.mso_writev = &devkmsg_v_writev,
	.mso_stat   = &nullfile_v_stat,
	.mso_ioctl  = &chrdev_v_ioctl,
};





/************************************************************************/
/* Alias device for the process's controlling terminal (/dev/tty)       */
/************************************************************************/

LOCAL ATTR_RETNONNULL WUNUSED REF struct ttydev *
getctty(void) THROWS(E_NO_CTTY) {
	REF struct ttydev *result;
	result = task_getctty();
	if unlikely(!result)
		THROW(E_NO_CTTY);
	return result;
}

PRIVATE NONNULL((1, 2)) void KCALL
devtty_v_open(struct mfile *__restrict UNUSED(self),
              /*in|out*/ REF struct handle *__restrict hand,
              struct path *access_path,
              struct fdirent *access_dent, oflag_t oflags) {
	assert(hand->h_data == &dev_tty);
	hand->h_data = getctty(); /* Inherit reference */
	decref_nokill(&dev_tty); /* Old reference from `hand->h_data' */
	/* Recursive open */
	mfile_open((struct device *)hand->h_data,
	           hand, access_path, access_dent,
	           oflags);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devtty_v_read(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
              size_t num_bytes, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_uread(dev, dst, num_bytes, mode);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devtty_v_readv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
               size_t num_bytes, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_ureadv(dev, dst, num_bytes, mode);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devtty_v_write(struct mfile *__restrict UNUSED(self), USER CHECKED void const *src,
               size_t num_bytes, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_uwrite(dev, src, num_bytes, mode);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devtty_v_writev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict src,
                size_t num_bytes, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_uwritev(dev, src, num_bytes, mode);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devtty_v_pread(struct mfile *__restrict UNUSED(self), USER CHECKED void *dst,
               size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_upread(dev, dst, num_bytes, addr, mode);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devtty_v_preadv(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict dst,
                size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_upreadv(dev, dst, num_bytes, addr, mode);
}

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
devtty_v_pwrite(struct mfile *__restrict UNUSED(self), USER CHECKED void const *src,
                size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_upwrite(dev, src, num_bytes, addr, mode);
}

PRIVATE WUNUSED NONNULL((1, 2)) size_t KCALL
devtty_v_pwritev(struct mfile *__restrict UNUSED(self), struct iov_buffer *__restrict src,
                 size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_upwritev(dev, src, num_bytes, addr, mode);
}

PRIVATE NONNULL((1)) pos_t KCALL
devtty_v_seek(struct mfile *__restrict UNUSED(self), off_t offset,
              unsigned int whence) THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_useek(dev, offset, whence);
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
devtty_v_ioctl(struct mfile *__restrict UNUSED(self), ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_uioctl(dev, cmd, arg, mode);
}

PRIVATE NONNULL((1)) void KCALL
devtty_v_truncate(struct mfile *__restrict UNUSED(self), pos_t new_size)
		THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	mfile_utruncate(dev, new_size);
}

PRIVATE NONNULL((1, 2)) void KCALL
devtty_v_mmap(struct mfile *__restrict UNUSED(self),
              struct handle_mmap_info *__restrict info)
		THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	mfile_ummap(dev, info);
}

PRIVATE NONNULL((1)) pos_t KCALL
devtty_v_allocate(struct mfile *__restrict UNUSED(self),
                  fallocate_mode_t mode,
                  pos_t start, pos_t length)
		THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_uallocate(dev, mode, start, length);
}

PRIVATE NONNULL((1)) void KCALL
devtty_v_stat(struct mfile *__restrict UNUSED(self),
              USER CHECKED struct stat *result)
		THROWS(...) {
	struct stat ctty_stat;
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	mfile_ustat(dev, &ctty_stat);

	/* Only include certain information within stat. If we'd included
	 * everything, then it would be impossible to tell the difference
	 * between /dev/tty and /dev/<actual-tty> */
	result->st_size      = ctty_stat.st_size;
	result->st_blocks    = ctty_stat.st_blocks;
	result->st_blksize   = ctty_stat.st_blksize;
	result->st_atime     = ctty_stat.st_atime;
	result->st_atimensec = ctty_stat.st_atimensec;
	result->st_mtime     = ctty_stat.st_mtime;
	result->st_mtimensec = ctty_stat.st_mtimensec;
	result->st_ctime     = ctty_stat.st_ctime;
	result->st_ctimensec = ctty_stat.st_ctimensec;
	result->st_btime     = ctty_stat.st_btime;
	result->st_btimensec = ctty_stat.st_btimensec;
}

PRIVATE NONNULL((1)) void KCALL
devtty_v_pollconnect(struct mfile *__restrict UNUSED(self),
                     poll_mode_t what)
		THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	mfile_upollconnect(dev, what);
}

PRIVATE WUNUSED NONNULL((1)) poll_mode_t KCALL
devtty_v_polltest(struct mfile *__restrict UNUSED(self),
                  poll_mode_t what)
		THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_upolltest(dev, what);
}

PRIVATE NONNULL((1)) REF void *KCALL
devtty_v_tryas(struct mfile *__restrict UNUSED(self), uintptr_half_t wanted_type)
		THROWS(...) {
	REF struct ttydev *dev = getctty();
	FINALLY_DECREF_UNLIKELY(dev);
	return mfile_utryas(dev, wanted_type);
}

PRIVATE struct mfile_stream_ops const devtty_stream_ops = {
	.mso_open        = &devtty_v_open,
	.mso_read        = &devtty_v_read,
	.mso_readv       = &devtty_v_readv,
	.mso_write       = &devtty_v_write,
	.mso_writev      = &devtty_v_writev,
	.mso_pread       = &devtty_v_pread,
	.mso_preadv      = &devtty_v_preadv,
	.mso_pwrite      = &devtty_v_pwrite,
	.mso_pwritev     = &devtty_v_pwritev,
	.mso_seek        = &devtty_v_seek,
	.mso_truncate    = &devtty_v_truncate,
	.mso_mmap        = &devtty_v_mmap,
	.mso_allocate    = &devtty_v_allocate,
	.mso_stat        = &devtty_v_stat,
	.mso_pollconnect = &devtty_v_pollconnect,
	.mso_polltest    = &devtty_v_polltest,
	.mso_ioctl       = &devtty_v_ioctl,
	.mso_tryas       = &devtty_v_tryas,
//TODO:	BLOCKING WUNUSED NONNULL((1, 2)) ssize_t
//TODO:	(KCALL *mso_printlink)(struct mfile *__restrict self, __pformatprinter printer, void *arg)
//TODO:			THROWS(E_WOULDBLOCK, ...);
//TODO:	BLOCKING NONNULL((1)) void
//TODO:	(KCALL *mso_sync)(struct mfile *__restrict self)
//TODO:			THROWS(E_WOULDBLOCK, E_IOERROR, ...);
//TODO:	NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
//TODO:	/*NOTHROW*/ (KCALL *mso_cc)(struct mfile *__restrict self,
//TODO:	                            struct ccinfo *__restrict info);
};

INTERN_CONST struct device_ops const dev_tty_ops = {{{
	.no_file = {
		.mo_destroy = (void(KCALL *)(struct mfile *__restrict))(void *)(uintptr_t)-1,
		.mo_changed = &device_v_changed,
		.mo_stream  = &devtty_stream_ops,
	},
	.no_wrattr = &device_v_wrattr
}}};






#ifdef LIBVIO_CONFIG_ENABLED
#define IF_VIO_ENABLED(...) __VA_ARGS__
#else /* LIBVIO_CONFIG_ENABLED */
#define IF_VIO_ENABLED(...) /* nothing */
#endif /* !LIBVIO_CONFIG_ENABLED */
#define DEVICE_OPS_INIT(mo_newpart, mo_loadblocks, mo_stream, mo_vio)       \
	{{{{                                                                    \
		{                                                                   \
			(void(KCALL *)(struct mfile *__restrict))(void *)(uintptr_t)-1, \
			mo_newpart, mo_loadblocks, NULL, &device_v_changed, mo_stream,  \
			IF_VIO_ENABLED(mo_vio)                                          \
		},                                                                  \
		&device_v_wrattr                                                    \
	}}}}
INTERN_CONST struct chrdev_ops const dev_mem_ops     = DEVICE_OPS_INIT(&devmem_v_newpart, NULL, &devmem_stream_ops, NULL);
INTERN_CONST struct chrdev_ops const dev_kmem_ops    = DEVICE_OPS_INIT(NULL, NULL, &devkmem_stream_ops, &devkmem_vio_ops);
INTERN_CONST struct chrdev_ops const dev_null_ops    = DEVICE_OPS_INIT(NULL, &devnull_v_loadpages, &devnull_stream_ops, NULL);
INTERN_CONST struct chrdev_ops const dev_port_ops    = DEVICE_OPS_INIT(NULL, NULL, &devport_stream_ops, &devport_vio_ops);
INTERN_CONST struct chrdev_ops const dev_zero_ops    = DEVICE_OPS_INIT(NULL, &devzero_v_loadpages, &devzero_stream_ops, NULL);
INTERN_CONST struct chrdev_ops const dev_full_ops    = DEVICE_OPS_INIT(NULL, &devfull_v_loadpages, &devfull_stream_ops, NULL);
INTERN_CONST struct chrdev_ops const dev_random_ops  = DEVICE_OPS_INIT(NULL, NULL, &devrandom_stream_ops, &devrandom_vio_ops);
INTERN_CONST struct chrdev_ops const dev_urandom_ops = DEVICE_OPS_INIT(NULL, NULL, &devurandom_stream_ops, &devurandom_vio_ops);
INTERN_CONST struct chrdev_ops const dev_kmsg_ops    = DEVICE_OPS_INIT(NULL, NULL, &devkmsg_stream_ops, NULL);
#undef DEVICE_OPS_INIT
#undef IF_VIO_ENABLED

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_NULL_C */
