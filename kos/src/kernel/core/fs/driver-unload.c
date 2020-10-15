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
#ifndef GUARD_KERNEL_CORE_FS_DRIVER_UNLOAD_C
#define GUARD_KERNEL_CORE_FS_DRIVER_UNLOAD_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <kernel/driver.h>
#include <kernel/execabi.h>

DECL_BEGIN

/* Destroy all places where the given driver may still be loaded
 * globally, including registered devices or object types, as well
 * as task callbacks and interrupt hooks, etc...
 * @return: true:  At least one global hook was cleared.
 * @return: false: No global hooks were defined. */
PUBLIC NONNULL((1)) bool KCALL
driver_clear_globals(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	bool result;
	(void)self;
	result = driver_clear_execabis(self);

	/* TODO: Delete global hooks of `self':
	 *   - block_device_register()
	 *   - character_device_register()
	 *   - nic_device_setdefault()
	 *   - register_filesystem_type()
	 *   - fs_filesystems                       (All filesystem implemented by `self')
	 *   - fs_filesystems                       (All filesystem using a block-device implemented by `self')
	 *   - kernel_debugtraps_install()
	 *   - driver_loaded_callbacks
	 *   - driver_finalized_callbacks
	 *   - driver_unloaded_callbacks
	 *   - vm_onexec_callbacks
	 *   - vm_oninit_callbacks
	 *   - vm_onfini_callbacks
	 *   - vm_onclone_callbacks
	 *   - isr_register()
	 *   - syslog_sink_register()
	 *   - vm_rtm_hooks
	 *   - register_async_worker()              (Delete all workers with callbacks apart of `self')
	 *   - async_job_start()                    (Cancel all running jobs with callbacks apart of `self')
	 *   - realtime_clock
	 * XXX:
	 *   - What about file handles that somehow reference the driver,
	 *     including stuff like HANDLE_TYPE_FILE->f_node->i_super->s_device
	 *     We should probably try to find these files, and close them in their
	 *     accompanying handle manager.
	 *     We can enumerate open handle managers by enumerating threads!
	 *   - This function should also have a return value to indicate if it
	 *     even did something, and if it did, the caller should be able to
	 *     call us multiple times to do a kind-of keep-killing-until-it-dies
	 *     functionality, alongside doing other things in-between.
	 */
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_DRIVER_UNLOAD_C */
