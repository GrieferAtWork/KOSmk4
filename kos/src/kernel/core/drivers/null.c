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
#ifndef GUARD_KERNEL_SRC_DRIVERS_NULL_C
#define GUARD_KERNEL_SRC_DRIVERS_NULL_C 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <kernel/driver.h>
#include <kernel/entropy.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/phys.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <sched/cred.h>

#include <hybrid/atomic.h>
#include <hybrid/unaligned.h>

#include <kos/dev.h>
#include <sys/io.h>
#include <sys/param.h>
#include <sys/poll.h>
#include <sys/stat.h>

#include <stddef.h>
#include <string.h>

#include <libvio/vio.h>

DECL_BEGIN

PRIVATE NONNULL((1)) size_t KCALL
dev_null_read(struct chrdev *__restrict UNUSED(self),
              USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes),
              iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_null_write(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void const *UNUSED(src), size_t num_bytes,
               iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_null_pread(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes),
               pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_null_pwrite(struct chrdev *__restrict UNUSED(self),
                USER CHECKED void const *UNUSED(src), size_t num_bytes,
                pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE NONNULL((1)) void KCALL
dev_null_pollconnect(struct chrdev *__restrict UNUSED(self),
                     poll_mode_t UNUSED(what))
		THROWS(...) {
}

PRIVATE NONNULL((1)) poll_mode_t KCALL
dev_null_polltest(struct chrdev *__restrict UNUSED(self),
                  poll_mode_t what)
		THROWS(...) {
	return what & (POLLINMASK | POLLOUTMASK);
}

PRIVATE NONNULL((1, 2)) void KCALL
dev_phys_mmap(struct chrdev *__restrict UNUSED(self),
              struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&mfile_phys);
}

PRIVATE NONNULL((1, 2)) void KCALL
dev_zero_mmap(struct chrdev *__restrict UNUSED(self),
              struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&mfile_zero);
}



PRIVATE NONNULL((1)) size_t KCALL
dev_zero_read(struct chrdev *__restrict UNUSED(self),
              USER CHECKED void *dst, size_t num_bytes,
              iomode_t UNUSED(mode)) THROWS(...) {
	memset(dst, 0, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_zero_pread(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void *dst, size_t num_bytes,
               pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	memset(dst, 0, num_bytes);
	return num_bytes;
}


PRIVATE NONNULL((1)) size_t KCALL
dev_full_write(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes),
               iomode_t UNUSED(mode)) THROWS(...) {
	THROW(E_FSERROR_DISK_FULL);
}

PRIVATE NONNULL((1)) size_t KCALL
dev_full_pwrite(struct chrdev *__restrict UNUSED(self),
                USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes),
                pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	THROW(E_FSERROR_DISK_FULL);
}


PRIVATE NONNULL((1)) size_t KCALL
dev_mem_pread(struct chrdev *__restrict UNUSED(self),
              USER CHECKED void *dst, size_t num_bytes,
              pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	copyfromphys(dst, (physaddr_t)addr, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_mem_pwrite(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void const *src, size_t num_bytes,
               pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	copytophys((physaddr_t)addr, src, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_kmem_pread(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void *dst, size_t num_bytes,
               pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	memcpy(dst, (void *)(uintptr_t)addr, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_kmem_pwrite(struct chrdev *__restrict UNUSED(self),
                USER CHECKED void const *src, size_t num_bytes,
                pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	memcpy((void *)(uintptr_t)addr, src, num_bytes);
	return num_bytes;
}



PRIVATE NONNULL((1)) size_t KCALL
dev_port_pread(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void *dst, size_t num_bytes,
               pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t i;
	for (i = 0; i < num_bytes; ++i)
		((u8 *)dst)[i] = inb((port_t)(addr + i));
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_port_pwrite(struct chrdev *__restrict UNUSED(self),
                USER CHECKED void const *src, size_t num_bytes,
                pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t i;
	for (i = 0; i < num_bytes; ++i)
		outb((port_t)(addr + i), ((u8 const *)src)[i]);
	return num_bytes;
}

PRIVATE NONNULL((1, 2)) void KCALL
dev_port_open(struct chrdev *__restrict UNUSED(self),
              struct handle *__restrict UNUSED(hand)) THROWS(...) {
	require(CAP_SYS_RAWIO);
}




PRIVATE NONNULL((1)) size_t KCALL
dev_urandom_read(struct chrdev *__restrict UNUSED(self),
                 USER CHECKED void *dst, size_t num_bytes,
                 iomode_t UNUSED(mode)) THROWS(...) {
	urandom_read(dst, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
dev_urandom_pread(struct chrdev *__restrict self,
                  USER CHECKED void *dst, size_t num_bytes,
                  pos_t UNUSED(addr), iomode_t mode) THROWS(...) {
	return dev_urandom_read(self, dst, num_bytes, mode);
}

#define urandom_pollconnect dev_null_pollconnect
PRIVATE NONNULL((1)) poll_mode_t KCALL
dev_urandom_polltest(struct chrdev *__restrict UNUSED(self),
                     poll_mode_t what)
		THROWS(...) {
	return what & POLLINMASK;
}


PRIVATE NONNULL((1)) size_t KCALL
dev_random_read(struct chrdev *__restrict UNUSED(self),
                USER CHECKED void *dst, size_t num_bytes,
                iomode_t mode) THROWS(...) {
	return entropy_read(dst, num_bytes, mode);
}

PRIVATE NONNULL((1)) size_t KCALL
dev_random_pread(struct chrdev *__restrict UNUSED(self),
                 USER CHECKED void *dst, size_t num_bytes,
                 pos_t UNUSED(addr), iomode_t mode) THROWS(...) {
	return entropy_read(dst, num_bytes, mode);
}

PRIVATE NONNULL((1)) void KCALL
dev_random_pollconnect(struct chrdev *__restrict UNUSED(self),
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

PRIVATE NONNULL((1)) poll_mode_t KCALL
dev_random_polltest(struct chrdev *__restrict UNUSED(self),
                    poll_mode_t what)
		THROWS(...) {
	/* Wait for non-deterministic random data to become available! */
	if (what & POLLINMASK) {
		if (ATOMIC_READ(entropy_bits) >= NBBY)
			return what & POLLINMASK;
	}
	return 0;
}


PRIVATE NONNULL((1)) size_t KCALL
dev_kmsg_write(struct chrdev *__restrict UNUSED(self),
               USER CHECKED void const *src, size_t num_bytes,
               iomode_t UNUSED(mode)) THROWS(...) {
	return (size_t)syslog_printer(SYSLOG_LEVEL_RAW, (char const *)src, num_bytes);
}

#define dev_kmsg_pollconnect dev_null_pollconnect
PRIVATE NONNULL((1)) poll_mode_t KCALL
dev_kmsg_polltest(struct chrdev *__restrict UNUSED(self),
                  poll_mode_t what)
		THROWS(...) {
	return what & POLLOUTMASK;
}



#ifdef LIBVIO_CONFIG_ENABLED
PRIVATE u8 KCALL
dev_port_rdb(struct vioargs *__restrict UNUSED(args),
             vio_addr_t addr) {
	return inb((port_t)addr);
}

PRIVATE u16 KCALL
dev_port_rdw(struct vioargs *__restrict UNUSED(args),
             vio_addr_t addr) {
	return inw((port_t)addr);
}

PRIVATE u32 KCALL
dev_port_rdl(struct vioargs *__restrict UNUSED(args),
             vio_addr_t addr) {
	return inl((port_t)addr);
}

PRIVATE void KCALL
dev_port_wrb(struct vioargs *__restrict UNUSED(args),
             vio_addr_t addr, u8 value) {
	outb((port_t)addr, value);
}

PRIVATE void KCALL
dev_port_wrw(struct vioargs *__restrict UNUSED(args),
             vio_addr_t addr, u16 value) {
	outw((port_t)addr, value);
}

PRIVATE void KCALL
dev_port_wrl(struct vioargs *__restrict UNUSED(args),
             vio_addr_t addr, u32 value) {
	outl((port_t)addr, value);
}

PRIVATE struct vio_operators const dev_port_vio =
VIO_OPERATORS_INIT(VIO_CALLBACK_INIT_READ(&dev_port_rdb, &dev_port_rdw, &dev_port_rdl, NULL),
                   VIO_CALLBACK_INIT_WRITE(&dev_port_wrb, &dev_port_wrw, &dev_port_wrl, NULL));
PRIVATE struct mfile dev_port_datablock = MFILE_INIT_VIO(&dev_port_vio);

#define DEV_PORT_MMAP_POINTER (&dev_port_mmap)
PRIVATE NONNULL((1, 2)) void KCALL
dev_port_mmap(struct chrdev *__restrict UNUSED(self),
              struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&dev_port_datablock);
	/* TODO: Don't limit `hmi_maxaddr' here, but pureply rely on the file's size instead! */
	info->hmi_maxaddr = (pos_t)((port_t)-1);
}


PRIVATE u8 KCALL
dev_random_rdb(struct vioargs *__restrict UNUSED(args),
               pos_t UNUSED(addr)) {
	u8 result;
	entropy_readall(&result, sizeof(result));
	return result;
}

PRIVATE u16 KCALL
dev_random_rdw(struct vioargs *__restrict UNUSED(args),
               pos_t UNUSED(addr)) {
	u16 result;
	entropy_readall(&result, sizeof(result));
	return result;
}

PRIVATE u32 KCALL
dev_random_rdl(struct vioargs *__restrict UNUSED(args),
               pos_t UNUSED(addr)) {
	u32 result;
	entropy_readall(&result, sizeof(result));
	return result;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE u64 KCALL
dev_random_rdq(struct vioargs *__restrict UNUSED(args),
               pos_t UNUSED(addr)) {
	u64 result;
	entropy_readall(&result, sizeof(result));
	return result;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE struct vio_operators const dev_random_vio =
VIO_OPERATORS_INIT(VIO_CALLBACK_INIT_READ(&dev_random_rdb, &dev_random_rdw,
                                          &dev_random_rdl, &dev_random_rdq),
                   VIO_CALLBACK_INIT_WRITE(NULL, NULL, NULL, NULL));
PRIVATE struct mfile dev_random_datablock = MFILE_INIT_VIO(&dev_random_vio);

#define DEV_RANDOM_MMAP_POINTER (&dev_random_mmap)
PRIVATE NONNULL((1, 2)) void KCALL
dev_random_mmap(struct chrdev *__restrict UNUSED(self),
                struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&dev_random_datablock);
}

PRIVATE u8 KCALL
dev_urandom_rdb(struct vioargs *__restrict UNUSED(args),
                pos_t UNUSED(addr)) {
	u8 result;
	urandom_read(&result, sizeof(result));
	return result;
}

PRIVATE u16 KCALL
dev_urandom_rdw(struct vioargs *__restrict UNUSED(args),
                pos_t UNUSED(addr)) {
	u16 result;
	urandom_read(&result, sizeof(result));
	return result;
}

PRIVATE u32 KCALL
dev_urandom_rdl(struct vioargs *__restrict UNUSED(args),
                pos_t UNUSED(addr)) {
	u32 result;
	urandom_read(&result, sizeof(result));
	return result;
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE u64 KCALL
dev_urandom_rdq(struct vioargs *__restrict UNUSED(args),
                pos_t UNUSED(addr)) {
	u64 result;
	urandom_read(&result, sizeof(result));
	return result;
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE struct vio_operators const dev_urandom_vio =
VIO_OPERATORS_INIT(VIO_CALLBACK_INIT_READ(&dev_urandom_rdb, &dev_urandom_rdw,
                                          &dev_urandom_rdl, &dev_urandom_rdq),
                   VIO_CALLBACK_INIT_WRITE(NULL, NULL, NULL, NULL));
PRIVATE struct mfile dev_urandom_datablock = MFILE_INIT_VIO(&dev_urandom_vio);

#define DEV_URANDOM_MMAP_POINTER (&dev_urandom_mmap)
PRIVATE NONNULL((1, 2)) void KCALL
dev_urandom_mmap(struct chrdev *__restrict UNUSED(self),
                 struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&dev_urandom_datablock);
}

#else /* LIBVIO_CONFIG_ENABLED */
#define DEV_PORT_MMAP_POINTER    NULL
#define DEV_RANDOM_MMAP_POINTER  NULL
#define DEV_URANDOM_MMAP_POINTER NULL
#endif /* !LIBVIO_CONFIG_ENABLED */




#define INIT_DEVICE(name, mkdev, read, write, pread,          \
                    pwrite, mmap, stat,                       \
                    pollconnect, polltest, open)              \
	{                                                         \
		/* .cd_refcnt   = */ 1,                               \
		/* .cd_heapsize = */ sizeof(struct chrdev), \
		/* .cd_type     = */ {                                \
			/* .ct_driver      = */ &drv_self,                \
			/* .ct_fini        = */ NULL,                     \
			/* .ct_read        = */ read,                     \
			/* .ct_write       = */ write,                    \
			/* .ct_pread       = */ pread,                    \
			/* .ct_pwrite      = */ pwrite,                   \
			/* .ct_ioctl       = */ NULL,                     \
			/* .ct_mmap        = */ mmap,                     \
			/* .ct_sync        = */ NULL,                     \
			/* .ct_stat        = */ stat,                     \
			/* .ct_pollconnect = */ pollconnect,              \
			/* .ct_polltest    = */ polltest,                 \
			/* .ct_open        = */ open                      \
		},                                                    \
		/* .cd_devlink     = */ { NULL, NULL, mkdev },        \
		/* .cd_flags       = */ CHARACTER_DEVICE_FLAG_NORMAL, \
		/* .cd_devfs_inode = */ NULL,                         \
		/* .cd_devfs_entry = */ NULL,                         \
		/* .cd_name     = */ name                             \
	}


PRIVATE struct chrdev null_devices[] = {
	INIT_DEVICE("mem", MKDEV(1, 1), NULL, NULL, &dev_mem_pread, &dev_mem_pwrite, &dev_phys_mmap, NULL, &dev_null_pollconnect, &dev_null_polltest, NULL),
	INIT_DEVICE("kmem", MKDEV(1, 2), NULL, NULL, &dev_kmem_pread, &dev_kmem_pwrite, NULL, NULL, &dev_null_pollconnect, &dev_null_polltest, NULL),
	INIT_DEVICE("null", MKDEV(1, 3), &dev_null_read, &dev_null_write, &dev_null_pread, &dev_null_pwrite, &dev_zero_mmap, NULL, &dev_null_pollconnect, &dev_null_polltest, NULL),
	INIT_DEVICE("port", MKDEV(1, 4), NULL, NULL, &dev_port_pread, &dev_port_pwrite, DEV_PORT_MMAP_POINTER, NULL, &dev_null_pollconnect, &dev_null_polltest, &dev_port_open),
	INIT_DEVICE("zero", MKDEV(1, 5), &dev_zero_read, &dev_null_write, &dev_zero_pread, &dev_null_pwrite, &dev_zero_mmap, NULL, &dev_null_pollconnect, &dev_null_polltest, NULL),
	INIT_DEVICE("full", MKDEV(1, 7), &dev_zero_read, &dev_full_write, &dev_zero_pread, &dev_full_pwrite, &dev_zero_mmap, NULL, &dev_null_pollconnect, &dev_null_polltest, NULL),
	INIT_DEVICE("random", MKDEV(1, 8), &dev_random_read, NULL, &dev_random_pread, NULL, DEV_RANDOM_MMAP_POINTER, NULL, &dev_random_pollconnect, &dev_random_polltest, NULL),
	INIT_DEVICE("urandom", MKDEV(1, 9), &dev_urandom_read, NULL, &dev_urandom_pread, NULL, DEV_URANDOM_MMAP_POINTER, NULL, &urandom_pollconnect, &dev_urandom_polltest, NULL),
	INIT_DEVICE("kmsg", MKDEV(1, 11), NULL, &dev_kmsg_write, NULL, NULL, NULL, NULL, &dev_kmsg_pollconnect, &dev_kmsg_polltest, NULL),
};



/* Initialize special builtin character devices (/dev/null, /dev/zero, etc.) */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_null_devices)(void) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(null_devices); ++i) {
		TRY {
			chrdev_register(&null_devices[i],
			                          chrdev_devno(&null_devices[i]));
		} EXCEPT {
			error_printf(FREESTR("Registering character device /dev/%s"),
			             null_devices[i].cd_name);
		}
	}
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_DRIVERS_NULL_C */
