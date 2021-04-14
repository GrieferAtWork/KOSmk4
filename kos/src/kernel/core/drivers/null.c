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
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/phys.h>
#include <kernel/rand.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <sched/cred.h>

#include <hybrid/unaligned.h>

#include <kos/dev.h>
#include <sys/io.h>
#include <sys/poll.h>
#include <sys/stat.h>

#include <stddef.h>
#include <string.h>

#include <libvio/vio.h>

DECL_BEGIN

PRIVATE NONNULL((1)) size_t KCALL
null_read(struct character_device *__restrict UNUSED(self),
          USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes),
          iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE NONNULL((1)) size_t KCALL
null_write(struct character_device *__restrict UNUSED(self),
           USER CHECKED void const *UNUSED(src), size_t num_bytes,
           iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
null_pread(struct character_device *__restrict UNUSED(self),
           USER CHECKED void *UNUSED(dst), size_t UNUSED(num_bytes),
           pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return 0;
}

PRIVATE NONNULL((1)) size_t KCALL
null_pwrite(struct character_device *__restrict UNUSED(self),
            USER CHECKED void const *UNUSED(src), size_t num_bytes,
            pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	return num_bytes;
}

PRIVATE NONNULL((1)) void KCALL
null_pollconnect(struct character_device *__restrict UNUSED(self),
                 poll_mode_t UNUSED(what))
		THROWS(...) {
}

PRIVATE NONNULL((1)) poll_mode_t KCALL
null_polltest(struct character_device *__restrict UNUSED(self),
              poll_mode_t what)
		THROWS(...) {
	return what & (POLLINMASK | POLLOUTMASK);
}

PRIVATE NONNULL((1, 2)) void KCALL
phys_mmap(struct character_device *__restrict UNUSED(self),
          struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&mfile_phys);
}

PRIVATE NONNULL((1, 2)) void KCALL
zero_mmap(struct character_device *__restrict UNUSED(self),
          struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&mfile_zero);
}



PRIVATE NONNULL((1)) size_t KCALL
zero_read(struct character_device *__restrict UNUSED(self),
          USER CHECKED void *dst, size_t num_bytes,
          iomode_t UNUSED(mode)) THROWS(...) {
	memset(dst, 0, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
zero_pread(struct character_device *__restrict UNUSED(self),
           USER CHECKED void *dst, size_t num_bytes,
           pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	memset(dst, 0, num_bytes);
	return num_bytes;
}


PRIVATE NONNULL((1)) size_t KCALL
full_write(struct character_device *__restrict UNUSED(self),
           USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes),
           iomode_t UNUSED(mode)) THROWS(...) {
	THROW(E_FSERROR_DISK_FULL);
}

PRIVATE NONNULL((1)) size_t KCALL
full_pwrite(struct character_device *__restrict UNUSED(self),
            USER CHECKED void const *UNUSED(src), size_t UNUSED(num_bytes),
            pos_t UNUSED(addr), iomode_t UNUSED(mode)) THROWS(...) {
	THROW(E_FSERROR_DISK_FULL);
}


PRIVATE NONNULL((1)) size_t KCALL
mem_pread(struct character_device *__restrict UNUSED(self),
          USER CHECKED void *dst, size_t num_bytes,
          pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	copyfromphys(dst, (physaddr_t)addr, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
mem_pwrite(struct character_device *__restrict UNUSED(self),
           USER CHECKED void const *src, size_t num_bytes,
           pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	copytophys((physaddr_t)addr, src, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
kmem_pread(struct character_device *__restrict UNUSED(self),
           USER CHECKED void *dst, size_t num_bytes,
           pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	memcpy(dst, (void *)(uintptr_t)addr, num_bytes);
	return num_bytes;
}
PRIVATE NONNULL((1)) size_t KCALL
kmem_pwrite(struct character_device *__restrict UNUSED(self),
            USER CHECKED void const *src, size_t num_bytes,
            pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	memcpy((void *)(uintptr_t)addr, src, num_bytes);
	return num_bytes;
}



PRIVATE NONNULL((1)) size_t KCALL
port_pread(struct character_device *__restrict UNUSED(self),
           USER CHECKED void *dst, size_t num_bytes,
           pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t i;
	for (i = 0; i < num_bytes; ++i)
		((u8 *)dst)[i] = inb((port_t)(addr + i));
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
port_pwrite(struct character_device *__restrict UNUSED(self),
            USER CHECKED void const *src, size_t num_bytes,
            pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	size_t i;
	for (i = 0; i < num_bytes; ++i)
		outb((port_t)(addr + i), ((u8 const *)src)[i]);
	return num_bytes;
}

PRIVATE NONNULL((1, 2)) void KCALL
port_open(struct character_device *__restrict UNUSED(self),
          struct handle *__restrict UNUSED(hand)) THROWS(...) {
	require(CAP_SYS_RAWIO);
}




PRIVATE NONNULL((1)) size_t KCALL
urandom_read(struct character_device *__restrict UNUSED(self),
             USER CHECKED void *dst, size_t num_bytes,
             iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = num_bytes;
	while (num_bytes >= 4) {
		*(u32 *)dst = krand32();
		dst         = (byte_t *)dst + 4;
		num_bytes -= 4;
	}
	if (num_bytes) {
		union {
			u32 r;
			u8 b[4];
		} x;
		x.r = krand32();
		while (num_bytes--)
			((u8 *)dst)[num_bytes] = x.b[num_bytes];
	}
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
urandom_pread(struct character_device *__restrict self,
              USER CHECKED void *dst, size_t num_bytes,
              pos_t UNUSED(addr), iomode_t mode) THROWS(...) {
	return urandom_read(self, dst, num_bytes, mode);
}

#define urandom_pollconnect null_pollconnect
PRIVATE NONNULL((1)) poll_mode_t KCALL
urandom_polltest(struct character_device *__restrict UNUSED(self),
                 poll_mode_t what)
		THROWS(...) {
	return what & POLLINMASK;
}


PRIVATE u32 KCALL krand32_nondeterministic(void) {
	/* TODO */
	return krand32();
}

PRIVATE u16 KCALL krand16_nondeterministic(void) {
	return (u16)krand32_nondeterministic();
}

PRIVATE u8 KCALL krand8_nondeterministic(void) {
	return (u8)krand32_nondeterministic();
}

PRIVATE NONNULL((1)) size_t KCALL
random_read(struct character_device *__restrict UNUSED(self),
            USER CHECKED void *dst, size_t num_bytes,
            iomode_t UNUSED(mode)) THROWS(...) {
	size_t result = num_bytes;
	while (num_bytes >= 4) {
		UNALIGNED_SET32((u32 *)dst, krand32_nondeterministic());
		dst = (byte_t *)dst + 4;
		num_bytes -= 4;
	}
	switch (num_bytes) {
	case 3:
		((u8 *)dst)[2] = krand8_nondeterministic();
		ATTR_FALLTHROUGH
	case 2:
		UNALIGNED_SET16((u16 *)dst, krand16_nondeterministic());
		break;
	case 1:
		*(u8 *)dst = krand8_nondeterministic();
		break;
	default: break;
	}
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
random_pread(struct character_device *__restrict self,
             USER CHECKED void *dst, size_t num_bytes,
             pos_t UNUSED(addr), iomode_t mode) THROWS(...) {
	return random_read(self, dst, num_bytes, mode);
}

#define random_pollconnect null_pollconnect
PRIVATE NONNULL((1)) poll_mode_t KCALL
random_polltest(struct character_device *__restrict UNUSED(self),
                poll_mode_t what)
		THROWS(...) {
	/* TODO: Wait for non-deterministic random data to become available! */
	return what & POLLINMASK;
}


PRIVATE NONNULL((1)) size_t KCALL
kmsg_write(struct character_device *__restrict UNUSED(self),
           USER CHECKED void const *src, size_t num_bytes,
           iomode_t UNUSED(mode)) THROWS(...) {
	return (size_t)syslog_printer(SYSLOG_LEVEL_RAW, (char const *)src, num_bytes);
}

#define kmsg_pollconnect null_pollconnect
PRIVATE NONNULL((1)) poll_mode_t KCALL
kmsg_polltest(struct character_device *__restrict UNUSED(self),
              poll_mode_t what)
		THROWS(...) {
	return what & POLLOUTMASK;
}



#ifdef LIBVIO_CONFIG_ENABLED
PRIVATE u8 KCALL
port_rdb(struct vioargs *__restrict UNUSED(args),
         vio_addr_t addr) {
	return inb((port_t)addr);
}

PRIVATE u16 KCALL
port_rdw(struct vioargs *__restrict UNUSED(args),
         vio_addr_t addr) {
	return inw((port_t)addr);
}

PRIVATE u32 KCALL
port_rdl(struct vioargs *__restrict UNUSED(args),
         vio_addr_t addr) {
	return inl((port_t)addr);
}

PRIVATE void KCALL
port_wrb(struct vioargs *__restrict UNUSED(args),
         vio_addr_t addr, u8 value) {
	outb((port_t)addr, value);
}

PRIVATE void KCALL
port_wrw(struct vioargs *__restrict UNUSED(args),
         vio_addr_t addr, u16 value) {
	outw((port_t)addr, value);
}

PRIVATE void KCALL
port_wrl(struct vioargs *__restrict UNUSED(args),
         vio_addr_t addr, u32 value) {
	outl((port_t)addr, value);
}

PRIVATE struct vio_operators const port_vio =
VIO_OPERATORS_INIT(VIO_CALLBACK_INIT_READ(&port_rdb, &port_rdw, &port_rdl, NULL),
                   VIO_CALLBACK_INIT_WRITE(&port_wrb, &port_wrw, &port_wrl, NULL));
PRIVATE struct mfile port_datablock = MFILE_INIT_VIO(&port_vio);

#define PORT_MMAP_POINTER (&port_mmap)
PRIVATE NONNULL((1, 2)) void KCALL
port_mmap(struct character_device *__restrict UNUSED(self),
          struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&port_datablock);
	/* TODO: Don't limit `hmi_maxaddr' here, but pureply rely on the file's size instead! */
	info->hmi_maxaddr = (pos_t)((port_t)-1);
}


PRIVATE u8 KCALL
random_rdb(struct vioargs *__restrict UNUSED(args),
           pos_t UNUSED(addr)) {
	return krand8_nondeterministic();
}

PRIVATE u16 KCALL
random_rdw(struct vioargs *__restrict UNUSED(args),
           pos_t UNUSED(addr)) {
	return krand16_nondeterministic();
}

PRIVATE u32 KCALL
random_rdl(struct vioargs *__restrict UNUSED(args),
           pos_t UNUSED(addr)) {
	return krand32_nondeterministic();
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE u64 KCALL
random_rdq(struct vioargs *__restrict UNUSED(args),
           pos_t UNUSED(addr)) {
	return ((u64)krand32_nondeterministic()) |
	       ((u64)krand32_nondeterministic() << 32);
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE struct vio_operators const random_vio =
VIO_OPERATORS_INIT(VIO_CALLBACK_INIT_READ(&random_rdb,
                                          &random_rdw,
                                          &random_rdl,
                                          &random_rdq),
                   VIO_CALLBACK_INIT_WRITE(NULL, NULL, NULL, NULL));
PRIVATE struct mfile random_datablock = MFILE_INIT_VIO(&random_vio);

#define RANDOM_MMAP_POINTER (&random_mmap)
PRIVATE NONNULL((1, 2)) void KCALL
random_mmap(struct character_device *__restrict UNUSED(self),
            struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&random_datablock);
}

PRIVATE u8 KCALL
urandom_rdb(struct vioargs *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return (u8)krand32();
}

PRIVATE u16 KCALL
urandom_rdw(struct vioargs *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return (u16)krand32();
}

PRIVATE u32 KCALL
urandom_rdl(struct vioargs *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return krand32();
}

#ifdef LIBVIO_CONFIG_HAVE_QWORD
PRIVATE u64 KCALL
urandom_rdq(struct vioargs *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return krand64();
}
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

PRIVATE struct vio_operators const urandom_vio =
VIO_OPERATORS_INIT(VIO_CALLBACK_INIT_READ(&urandom_rdb, &urandom_rdw, &urandom_rdl, &urandom_rdq),
                   VIO_CALLBACK_INIT_WRITE(NULL, NULL, NULL, NULL));
PRIVATE struct mfile urandom_datablock = MFILE_INIT_VIO(&urandom_vio);

#define URANDOM_MMAP_POINTER (&urandom_mmap)
PRIVATE NONNULL((1, 2)) void KCALL
urandom_mmap(struct character_device *__restrict UNUSED(self),
             struct handle_mmap_info *__restrict info)
		THROWS(...) {
	info->hmi_file = incref(&urandom_datablock);
}

#else /* LIBVIO_CONFIG_ENABLED */
#define PORT_MMAP_POINTER    NULL
#define RANDOM_MMAP_POINTER  NULL
#define URANDOM_MMAP_POINTER NULL
#endif /* !LIBVIO_CONFIG_ENABLED */




#define INIT_DEVICE(name, mkdev, read, write, pread,          \
                    pwrite, mmap, stat,                       \
                    pollconnect, polltest, open)              \
	{                                                         \
		/* .cd_refcnt   = */ 1,                               \
		/* .cd_heapsize = */ sizeof(struct character_device), \
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


PRIVATE struct character_device null_devices[] = {
	INIT_DEVICE("mem", MKDEV(1, 1), NULL, NULL, &mem_pread, &mem_pwrite, &phys_mmap, NULL, &null_pollconnect, &null_polltest, NULL),
	INIT_DEVICE("kmem", MKDEV(1, 2), NULL, NULL, &kmem_pread, &kmem_pwrite, NULL, NULL, &null_pollconnect, &null_polltest, NULL),
	INIT_DEVICE("null", MKDEV(1, 3), &null_read, &null_write, &null_pread, &null_pwrite, &zero_mmap, NULL, &null_pollconnect, &null_polltest, NULL),
	INIT_DEVICE("port", MKDEV(1, 4), NULL, NULL, &port_pread, &port_pwrite, PORT_MMAP_POINTER, NULL, &null_pollconnect, &null_polltest, &port_open),
	INIT_DEVICE("zero", MKDEV(1, 5), &zero_read, &null_write, &zero_pread, &null_pwrite, &zero_mmap, NULL, &null_pollconnect, &null_polltest, NULL),
	INIT_DEVICE("full", MKDEV(1, 7), &zero_read, &full_write, &zero_pread, &full_pwrite, &zero_mmap, NULL, &null_pollconnect, &null_polltest, NULL),
	INIT_DEVICE("random", MKDEV(1, 8), &random_read, NULL, &random_pread, NULL, RANDOM_MMAP_POINTER, NULL, &random_pollconnect, &random_polltest, NULL),
	INIT_DEVICE("urandom", MKDEV(1, 9), &urandom_read, NULL, &urandom_pread, NULL, URANDOM_MMAP_POINTER, NULL, &urandom_pollconnect, &urandom_polltest, NULL),
	INIT_DEVICE("kmsg", MKDEV(1, 11), NULL, &kmsg_write, NULL, NULL, NULL, NULL, &kmsg_pollconnect, &kmsg_polltest, NULL),
};



/* Initialize special builtin character devices (/dev/null, /dev/zero, etc.) */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_null_devices)(void) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(null_devices); ++i) {
		TRY {
			character_device_register(&null_devices[i],
			                          character_device_devno(&null_devices[i]));
		} EXCEPT {
			error_printf(FREESTR("Registering character device /dev/%s"),
			             null_devices[i].cd_name);
		}
	}
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_DRIVERS_NULL_C */
