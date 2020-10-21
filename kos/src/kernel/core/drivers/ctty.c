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
#ifndef GUARD_KERNEL_SRC_DRIVERS_CTTY_C
#define GUARD_KERNEL_SRC_DRIVERS_CTTY_C 1

#include <kernel/compiler.h>

#include <dev/char.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <sched/pid-ctty.h>
#include <sched/pid.h>

#include <kos/dev.h>

#include <assert.h>
#include <stddef.h>

DECL_BEGIN

LOCAL ATTR_RETNONNULL WUNUSED REF struct ttybase_device *
getctty(void) THROWS(E_WOULDBLOCK, E_NO_CTTY) {
	REF struct ttybase_device *result;
	result = task_getctty();
	if unlikely(!result)
		THROW(E_NO_CTTY);
	return result;
}


PRIVATE NONNULL((1)) size_t KCALL
ctty_read(struct character_device *__restrict UNUSED(self),
          USER CHECKED void *dst, size_t num_bytes,
          iomode_t mode) THROWS(...) {
	size_t result;
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	result = character_device_read(ctty, dst, num_bytes, mode);
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
ctty_write(struct character_device *__restrict UNUSED(self),
           USER CHECKED void const *src, size_t num_bytes,
           iomode_t mode) THROWS(...) {
	size_t result;
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	result = character_device_write(ctty, src, num_bytes, mode);
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
ctty_pread(struct character_device *__restrict UNUSED(self),
           USER CHECKED void *dst, size_t num_bytes,
           pos_t addr, iomode_t mode) THROWS(...) {
	size_t result;
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	result = character_device_pread(ctty, dst, num_bytes, addr, mode);
	return result;
}

PRIVATE NONNULL((1)) size_t KCALL
ctty_pwrite(struct character_device *__restrict UNUSED(self),
            USER CHECKED void const *src, size_t num_bytes,
            pos_t addr, iomode_t mode) THROWS(...) {
	size_t result;
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	result = character_device_pwrite(ctty, src, num_bytes, addr, mode);
	return result;
}

PRIVATE NONNULL((1)) syscall_slong_t KCALL
ctty_ioctl(struct character_device *__restrict UNUSED(self),
           syscall_ulong_t cmd,
           USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	syscall_slong_t result;
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	result = character_device_ioctl(ctty, cmd, arg, mode);
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5)) REF struct vm_datablock *KCALL
ctty_mmap(struct character_device *__restrict UNUSED(self),
          pos_t *__restrict pminoffset,
          pos_t *__restrict pnumbytes,
          REF struct path **__restrict pdatablock_fspath,
          REF struct directory_entry **__restrict pdatablock_fsname) THROWS(...) {
	REF struct vm_datablock *result;
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	result = character_device_mmap(ctty,
	                               pminoffset,
	                               pnumbytes,
	                               pdatablock_fspath,
	                               pdatablock_fsname);


	return result;
}

PRIVATE NONNULL((1)) void KCALL
ctty_sync(struct character_device *__restrict UNUSED(self)) THROWS(...) {
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	character_device_sync(ctty);
}

PRIVATE NONNULL((1)) void KCALL
ctty_stat(struct character_device *__restrict UNUSED(self),
          USER CHECKED struct stat *result) THROWS(...) {
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	character_device_stat(ctty, result);
}

PRIVATE NONNULL((1)) void KCALL
ctty_pollconnect(struct character_device *__restrict UNUSED(self),
                 poll_mode_t what) THROWS(...) {
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	character_device_pollconnect(ctty, what);
}

PRIVATE NONNULL((1)) poll_mode_t KCALL
ctty_polltest(struct character_device *__restrict UNUSED(self),
              poll_mode_t what) THROWS(...) {
	poll_mode_t result;
	REF struct ttybase_device *ctty = getctty();
	FINALLY_DECREF_UNLIKELY(ctty);
	result = character_device_polltest(ctty, what);
	return result;
}

PRIVATE NONNULL((1, 2)) void KCALL
ctty_open(struct character_device *__restrict self,
          struct handle *__restrict hand) {
	assert(self == &dev_tty);
	assert(self == hand->h_data);
	assert(hand->h_type == HANDLE_TYPE_CHARACTERDEVICE);
	decref_nokill(self);
	hand->h_data = getctty();
}


/* The character device made available under /dev/tty
 * This device implements all operators as direct aliasing callbacks
 * to the TTY character device addressable through `task_getctty()' */
PUBLIC struct character_device dev_tty = {
	/* .cd_refcnt   = */ 1,
	/* .cd_heapsize = */ sizeof(dev_tty),
	/* .cd_type     = */ {
		/* .ct_driver      = */ &drv_self,
		/* .ct_fini        = */ NULL,
		/* .ct_read        = */ &ctty_read,
		/* .ct_write       = */ &ctty_write,
		/* .ct_pread       = */ &ctty_pread,
		/* .ct_pwrite      = */ &ctty_pwrite,
		/* .ct_ioctl       = */ &ctty_ioctl,
		/* .ct_mmap        = */ &ctty_mmap,
		/* .ct_sync        = */ &ctty_sync,
		/* .ct_stat        = */ &ctty_stat,
		/* .ct_pollconnect = */ &ctty_pollconnect,
		/* .ct_polltest    = */ &ctty_polltest,
		/* .ct_open        = */ &ctty_open
	},
	/* .cd_devlink     = */ { NULL, NULL, 0 },
	/* .cd_flags       = */ CHARACTER_DEVICE_FLAG_NORMAL,
	/* .cd_devfs_inode = */ NULL,
	/* .cd_devfs_entry = */ NULL,
	/* .cd_name        = */ "tty"
};


/* Initialize the /dev/tty alias device */
INTERN ATTR_FREETEXT void
NOTHROW(KCALL kernel_initialize_ctty_device)(void) {
	TRY {
		character_device_register(&dev_tty, MKDEV(5, 0));
	} EXCEPT {
		error_printf(FREESTR("Registering /dev/tty"));
	}
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_DRIVERS_CTTY_C */
