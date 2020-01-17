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
#ifndef GUARD_KERNEL_SRC_DRIVERS_NULL_C
#define GUARD_KERNEL_SRC_DRIVERS_NULL_C 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/rand.h>
#include <kernel/syslog.h>
#include <kernel/types.h>
#include <kernel/vio.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>

#include <hybrid/unaligned.h>

#include <kos/dev.h>
#include <sys/io.h>
#include <sys/poll.h>
#include <sys/stat.h>

#include <stddef.h>
#include <string.h>

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

PRIVATE NONNULL((1)) poll_mode_t KCALL
null_poll(struct character_device *__restrict UNUSED(self),
          poll_mode_t what) {
	return what;
}

PRIVATE NONNULL((1)) REF struct vm_datablock *KCALL
phys_mmap(struct character_device *__restrict UNUSED(self),
          pos_t *__restrict UNUSED(pminoffset),
          pos_t *__restrict UNUSED(pnumbytes)) THROWS(...) {
	return incref(&vm_datablock_physical);
}

PRIVATE NONNULL((1)) REF struct vm_datablock *KCALL
zero_mmap(struct character_device *__restrict UNUSED(self),
          pos_t *__restrict UNUSED(pminoffset),
          pos_t *__restrict UNUSED(pnumbytes)) THROWS(...) {
	return incref(&vm_datablock_anonymous_zero);
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
	vm_copyfromphys(dst, (vm_phys_t)addr, num_bytes);
	return num_bytes;
}

PRIVATE NONNULL((1)) size_t KCALL
mem_pwrite(struct character_device *__restrict UNUSED(self),
           USER CHECKED void const *src, size_t num_bytes,
           pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	vm_copytophys((vm_phys_t)addr, src, num_bytes);
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

PRIVATE NONNULL((1)) poll_mode_t KCALL
urandom_poll(struct character_device *__restrict UNUSED(self),
             poll_mode_t what) {
	return what & POLLIN;
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

PRIVATE NONNULL((1)) poll_mode_t KCALL
random_poll(struct character_device *__restrict UNUSED(self),
            poll_mode_t what) {
	/* TODO: Wait for non-deterministic random data to become available! */
	return what & POLLIN;
}


PRIVATE NONNULL((1)) size_t KCALL
kmsg_write(struct character_device *__restrict UNUSED(self),
           USER CHECKED void const *src, size_t num_bytes,
           iomode_t UNUSED(mode)) THROWS(...) {
	return (size_t)syslog_printer(SYSLOG_LEVEL_RAW, (char const *)src, num_bytes);
}

PRIVATE NONNULL((1)) poll_mode_t KCALL
kmsg_poll(struct character_device *__restrict UNUSED(self),
          poll_mode_t what) {
	return what & POLLOUT;
}



#ifdef CONFIG_VIO
PRIVATE u8 KCALL port_rdb(struct vio_args *__restrict UNUSED(args), pos_t addr) {
	return inb((port_t)addr);
}

PRIVATE u16 KCALL port_rdw(struct vio_args *__restrict UNUSED(args), pos_t addr) {
	return inw((port_t)addr);
}

PRIVATE u32 KCALL port_rdl(struct vio_args *__restrict UNUSED(args), pos_t addr) {
	return inl((port_t)addr);
}

PRIVATE void KCALL port_wrb(struct vio_args *__restrict UNUSED(args), pos_t addr, u8 value) {
	outb((port_t)addr, value);
}

PRIVATE void KCALL port_wrw(struct vio_args *__restrict UNUSED(args), pos_t addr, u16 value) {
	outw((port_t)addr, value);
}

PRIVATE void KCALL port_wrl(struct vio_args *__restrict UNUSED(args), pos_t addr, u32 value) {
	outl((port_t)addr, value);
}

PRIVATE struct vm_datablock_type_vio const port_vio = {
	.dtv_read = {
		.f_byte  = &port_rdb,
		.f_word  = &port_rdw,
		.f_dword = &port_rdl,
	},
	.dtv_write = {
		.f_byte  = &port_wrb,
		.f_word  = &port_wrw,
		.f_dword = &port_wrl,
	}
};
PRIVATE struct vm_datablock port_datablock = VM_DATABLOCK_INIT_VIO(&port_vio);

#define PORT_MMAP_POINTER (&port_mmap)
PRIVATE NONNULL((1)) REF struct vm_datablock *KCALL
port_mmap(struct character_device *__restrict UNUSED(self),
          pos_t *__restrict UNUSED(pminoffset),
          pos_t *__restrict pnumbytes) THROWS(...) {
	*pnumbytes = (pos_t)((port_t)-1) + 1;
	return incref(&port_datablock);
}


PRIVATE u8 KCALL random_rdb(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return krand8_nondeterministic();
}

PRIVATE u16 KCALL random_rdw(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return krand16_nondeterministic();
}

PRIVATE u32 KCALL random_rdl(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return krand32_nondeterministic();
}

#ifdef CONFIG_VIO_HAS_QWORD
PRIVATE u64 KCALL random_rdq(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return ((u64)krand32_nondeterministic()) |
	       ((u64)krand32_nondeterministic() << 32);
}
#endif /* CONFIG_VIO_HAS_QWORD */

PRIVATE struct vm_datablock_type_vio const random_vio = {
	.dtv_read  = VIO_CALLBACK_INIT(&random_rdb, &random_rdw, &random_rdl, &random_rdq),
};
PRIVATE struct vm_datablock random_datablock = VM_DATABLOCK_INIT_VIO(&random_vio);

#define RANDOM_MMAP_POINTER (&random_mmap)
PRIVATE NONNULL((1)) REF struct vm_datablock *KCALL
random_mmap(struct character_device *__restrict UNUSED(self),
            pos_t *__restrict UNUSED(pminoffset),
            pos_t *__restrict UNUSED(pnumbytes)) THROWS(...) {
	return incref(&random_datablock);
}

PRIVATE u8 KCALL urandom_rdb(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return (u8)krand32();
}

PRIVATE u16 KCALL urandom_rdw(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return (u16)krand32();
}

PRIVATE u32 KCALL urandom_rdl(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return krand32();
}

#ifdef CONFIG_VIO_HAS_QWORD
PRIVATE u64 KCALL urandom_rdq(struct vio_args *__restrict UNUSED(args), pos_t UNUSED(addr)) {
	return krand64();
}
#endif /* CONFIG_VIO_HAS_QWORD */

PRIVATE struct vm_datablock_type_vio const urandom_vio = {
	.dtv_read  = VIO_CALLBACK_INIT(&urandom_rdb, &urandom_rdw, &urandom_rdl, &urandom_rdq),
};

PRIVATE struct vm_datablock urandom_datablock = VM_DATABLOCK_INIT_VIO(&urandom_vio);

#define URANDOM_MMAP_POINTER (&urandom_mmap)
PRIVATE NONNULL((1)) REF struct vm_datablock *KCALL
urandom_mmap(struct character_device *__restrict UNUSED(self),
             pos_t *__restrict UNUSED(pminoffset),
             pos_t *__restrict UNUSED(pnumbytes)) THROWS(...) {
	return incref(&urandom_datablock);
}

#else /* CONFIG_VIO */
#define PORT_MMAP_POINTER    NULL
#define RANDOM_MMAP_POINTER  NULL
#define URANDOM_MMAP_POINTER NULL
#endif /* !CONFIG_VIO */




#define INIT_DEVICE(name, mkdev, read, write, pread, pwrite, mmap, stat, poll) \
	{                                                                          \
		/* .cd_refcnt   = */ 1,                                                \
		/* .cd_heapsize = */ sizeof(struct character_device),                  \
		/* .cd_type     = */ {                                                 \
			/* .ct_driver    = */ &drv_self,                                   \
			/* .ct_fini      = */ NULL,                                        \
			/* .ct_read      = */ read,                                        \
			/* .ct_write     = */ write,                                       \
			/* .ct_pread     = */ pread,                                       \
			/* .ct_pwrite    = */ pwrite,                                      \
			/* .ct_ioctl     = */ NULL,                                        \
			/* .ct_mmap      = */ mmap,                                        \
			/* .ct_sync      = */ NULL,                                        \
			/* .ct_stat      = */ stat,                                        \
			/* .ct_poll      = */ poll                                         \
		},                                                                     \
		/* .cd_devlink     = */ { NULL, NULL, mkdev },                         \
		/* .cd_flags       = */ CHARACTER_DEVICE_FLAG_NORMAL,                  \
		/* .cd_devfs_inode = */ NULL,                                          \
		/* .cd_devfs_entry = */ NULL,                                          \
		/* .cd_name     = */ name                                              \
	}


PRIVATE struct character_device null_devices[] = {
	INIT_DEVICE("mem", MKDEV(1, 1), NULL, NULL, &mem_pread, &mem_pwrite, &phys_mmap, NULL, &null_poll),
	INIT_DEVICE("kmem", MKDEV(1, 2), NULL, NULL, &kmem_pread, &kmem_pwrite, NULL, NULL, &null_poll),
	INIT_DEVICE("null", MKDEV(1, 3), &null_read, &null_write, &null_pread, &null_pwrite, &zero_mmap, NULL, &null_poll),
	INIT_DEVICE("port", MKDEV(1, 4), NULL, NULL, &port_pread, &port_pwrite, PORT_MMAP_POINTER, NULL, &null_poll),
	INIT_DEVICE("zero", MKDEV(1, 5), &zero_read, &null_write, &zero_pread, &null_pwrite, &zero_mmap, NULL, &null_poll),
	INIT_DEVICE("full", MKDEV(1, 7), &zero_read, &full_write, &zero_pread, &full_pwrite, &zero_mmap, NULL, &null_poll),
	INIT_DEVICE("random", MKDEV(1, 8), &random_read, NULL, &random_pread, NULL, RANDOM_MMAP_POINTER, NULL, &random_poll),
	INIT_DEVICE("urandom", MKDEV(1, 9), &urandom_read, NULL, &urandom_pread, NULL, URANDOM_MMAP_POINTER, NULL, &urandom_poll),
	INIT_DEVICE("kmsg", MKDEV(1, 11), NULL, &kmsg_write, NULL, NULL, NULL, NULL, &kmsg_poll),
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
