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
#ifndef GUARD_KERNEL_SRC_MISC_KSYSCTL_C
#define GUARD_KERNEL_SRC_MISC_KSYSCTL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/mfile.h>
#include <kernel/personality.h>
#include <kernel/profiler.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <kos/ioctl/_openfd.h>
#include <kos/ksysctl.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

#undef CONFIG_HAVE_HACKY_REBOOT
#if 0
#define CONFIG_HAVE_HACKY_REBOOT
#endif

#ifdef CONFIG_HAVE_HACKY_REBOOT
#include <kernel/printk.h>
#include <sys/io.h>
#endif /* CONFIG_HAVE_HACKY_REBOOT */

DECL_BEGIN

/* The default library path.
 * By default, this string is simply set to "/os/drivers"
 * NOTE: This path can be restored with
 *      `ksysctl_set_driver_library_path(KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT)' */
INTDEF struct driver_libpath_struct default_library_path;





/************************************************************************/
/* ksysctl()                                                            */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_KSYSCTL) ||     \
     defined(__ARCH_WANT_SYSCALL_FINIT_MODULE))
PRIVATE ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
load_driver_from_file_handles(fd_t fd_node, fd_t fd_path, fd_t fd_dent,
                              USER CHECKED char const *driver_cmdline,
                              bool *pnew_driver_loaded,
                              unsigned int flags) {
	REF struct driver *result;
	REF struct mfile *driver_node;
	REF struct path *driver_path;
	REF struct fdirent *driver_dentry;
	REF struct handle nodehand;
	driver_path   = NULL;
	driver_dentry = NULL;
	driver_node   = NULL;
	RAII_FINALLY {
		xdecref_unlikely(driver_path);
		xdecref_unlikely(driver_dentry);
		decref_unlikely(driver_node);
	};
	if (fd_path != -1)
		driver_path = handles_lookuppath(fd_path);
	if (fd_dent != -1)
		driver_dentry = handles_lookupfdirent(fd_dent);
	nodehand = handles_lookup(fd_node);
	TRY {
		/* (Try to) fill in missing filesystem information from `f_node' */
		if (!driver_path)
			driver_path = (REF struct path *)handle_tryas_noinherit(nodehand, HANDLE_TYPE_PATH);
		if (!driver_dentry)
			driver_dentry = (REF struct fdirent *)handle_tryas_noinherit(nodehand, HANDLE_TYPE_DIRENT);
		/* Lookup the actual INode from which to load the driver. */
		driver_node = handle_as_mfile(nodehand);
	} EXCEPT {
		if (was_thrown(E_INVALID_HANDLE_FILETYPE)) {
			if (!PERTASK_TEST(this_exception_args.e_invalid_handle.ih_fd))
				PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, fd_node);
		}
		RETHROW();
	}
	require(CAP_SYS_MODULE);
	if (flags & KSYSCTL_DRIVER_INSMOD_FNOINIT) {
		result = driver_loadmod(driver_node,
		                        driver_path,
		                        driver_dentry,
		                        driver_cmdline,
		                        pnew_driver_loaded);
	} else {
		result = driver_insmod(driver_node,
		                       driver_path,
		                       driver_dentry,
		                       driver_cmdline,
		                       pnew_driver_loaded);
	}
	return result;
}

#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_KSYSCTL
DEFINE_SYSCALL2(syscall_slong_t, ksysctl,
                ioctl_t, command,
                USER UNCHECKED void *, arg) {
	switch (command) {

	case KSYSCTL_SYSTEM_CLEARCACHES: {
		struct ccinfo cc;
		cred_require_sysadmin();
		ccinfo_init(&cc, GFP_NORMAL, (size_t)-1);
		cc.ci_attempt = (unsigned int)-1; /* Infinite attempts. */

		/* Invoke the cache-clearing system. */
		if (system_cc(&cc) && !cc.ci_bytes)
			cc.ci_bytes = 1;

		/* Return how many bytes were cleared. */
		return (syscall_slong_t)cc.ci_bytes;
	}	break;

	case KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS:
		cred_require_sysadmin();
		return (syscall_slong_t)kmalloc_leaks();

	case KSYSCTL_SYSTEM_MEMORY_VALIDATE_PADDING:
		cred_require_sysadmin();
		kmalloc_validate();
		heap_validate_all();
		return 0;

	case KSYSCTL_SYSTEM_BRANCH_DUMP_STATS:
		cred_require_sysadmin();
		dump_branch_stats();
		return 0;

	case KSYSCTL_KERNEL_GET_PERSONALITY: {
		uintptr_t kp;
		if unlikely((uintptr_t)arg & 1) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PERSONALITY,
			      (uintptr_t)arg, 1, 1);
		}
		kp = (uintptr_t)arg >> 1;
		if unlikely(kp == KP_INVALID ||
		            kp >= KP_COUNT) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PERSONALITY,
			      (uintptr_t)arg);
		}
		return has_personality(kp) ? 1 : 0;
	}	break;

	case KSYSCTL_KERNEL_SET_PERSONALITY: {
		uintptr_t kp, index;
		bool enable = ((uintptr_t)arg & 1) != 0;
		byte_t oldbyte, mask;
		kp = (uintptr_t)arg >> 1;
		if unlikely(kp == KP_INVALID ||
		            kp >= KP_COUNT) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_BAD_PERSONALITY,
			      (uintptr_t)arg);
		}
		cred_require_sysadmin();
		index = kp / 8;
		mask  = (byte_t)1 << (kp % 8);
		if (enable) {
			oldbyte = ATOMIC_FETCHOR(kernel_personality[index], mask);
		} else {
			oldbyte = ATOMIC_FETCHAND(kernel_personality[index], ~mask);
		}
		return (oldbyte & mask) != 0 ? 1 : 0;
	}	break;

	case KSYSCTL_DRIVER_LSMOD: {
		struct handle temp;
		require(CAP_SYS_MODULE);
		temp.h_type = HANDLE_TYPE_DRIVER_LOADLIST;
		temp.h_mode = IO_RDWR;
		temp.h_data = get_driver_loadlist();
		FINALLY_DECREF_UNLIKELY((struct driver_loadlist *)temp.h_data);
		return handles_install_openfd(temp, (USER UNCHECKED struct openfd *)arg);
	}	break;

	case KSYSCTL_DRIVER_INSMOD: {
		USER CHECKED struct ksysctl_driver_insmod *data;
		size_t struct_size;
		u16 format;
		USER CHECKED char const *commandline;
		bool new_driver_loaded;
		REF struct driver *drv;
		unsigned int insmod_flags;
		validate_readwrite(arg, sizeof(struct ksysctl_driver_insmod));
		data        = (struct ksysctl_driver_insmod *)arg;
		struct_size = data->im_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(struct ksysctl_driver_insmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_insmod), struct_size);
		format       = data->im_format;
		commandline  = data->im_cmdline;
		insmod_flags = data->im_flags;
		COMPILER_READ_BARRIER();
		validate_readable_opt(commandline, 1);
		VALIDATE_FLAGSET(insmod_flags,
		                 KSYSCTL_DRIVER_INSMOD_FNORMAL |
		                 KSYSCTL_DRIVER_INSMOD_FNOINIT,
		                 E_INVALID_ARGUMENT_CONTEXT_INSMOD_FLAGS);
		switch (format) {

		case KSYSCTL_DRIVER_FORMAT_BLOB: {
			USER CHECKED void const *base;
			size_t size;
			base = data->im_blob.b_base;
			size = data->im_blob.b_size;
			COMPILER_READ_BARRIER();
			validate_readable(base, size);
			require(CAP_SYS_MODULE);
			drv = insmod_flags & KSYSCTL_DRIVER_INSMOD_FNOINIT
			      ? driver_loadmod((byte_t *)base, size, commandline, &new_driver_loaded)
			      : driver_insmod((byte_t *)base, size, commandline, &new_driver_loaded);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_FILE: {
			fd_t fd_node, fd_path, fd_dent;
			fd_node = data->im_file.f_node;
			fd_path = data->im_file.f_path;
			fd_dent = data->im_file.f_dentry;
			COMPILER_READ_BARRIER();
			drv = load_driver_from_file_handles(fd_node, fd_path, fd_dent,
			                                    commandline, &new_driver_loaded,
			                                    insmod_flags);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_NAME: {
			USER CHECKED char const *name;
			name = data->im_name;
			COMPILER_READ_BARRIER();
			validate_readable(name, 1);
			require(CAP_SYS_MODULE);
			drv = insmod_flags & KSYSCTL_DRIVER_INSMOD_FNOINIT
			      ? driver_loadmod(name, commandline, &new_driver_loaded)
			      : driver_insmod(name, commandline, &new_driver_loaded);
		}	break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT,
			      format);
		}
		FINALLY_DECREF_UNLIKELY(drv);
		ATOMIC_WRITE(data->im_newdriver, new_driver_loaded ? 1 : 0);
		{
			struct openfd *drv_fd;
			drv_fd = data->im_driver;
			COMPILER_READ_BARRIER();
			if (drv_fd) {
				struct handle temp;
				temp.h_type = HANDLE_TYPE_MODULE;
				temp.h_mode = IO_RDWR;
				temp.h_data = drv;
				return handles_install_openfd(temp, drv_fd);
			}
		}
	}	break;

	case KSYSCTL_DRIVER_DELMOD: {
		USER CHECKED struct ksysctl_driver_delmod *data;
		size_t struct_size;
		u16 format;
		unsigned int delmod_flags, error;
		static_assert(KSYSCTL_DRIVER_DELMOD_FNORMAL == DRIVER_DELMOD_F_NORMAL);
		static_assert(KSYSCTL_DRIVER_DELMOD_FNODEPEND == DRIVER_DELMOD_F_NODEPEND);
		static_assert(KSYSCTL_DRIVER_DELMOD_FFORCE == DRIVER_DELMOD_F_FORCE);
		static_assert(KSYSCTL_DRIVER_DELMOD_FNONBLOCK == DRIVER_DELMOD_F_NONBLOCK);
		static_assert(KSYSCTL_DRIVER_DELMOD_SUCCESS == DRIVER_DELMOD_ST_SUCCESS);
		static_assert(KSYSCTL_DRIVER_DELMOD_UNKNOWN == DRIVER_DELMOD_ST_UNKNOWN);
		static_assert(KSYSCTL_DRIVER_DELMOD_INUSE == DRIVER_DELMOD_ST_INUSE);
		validate_readwrite(arg, sizeof(struct ksysctl_driver_delmod));
		data        = (struct ksysctl_driver_delmod *)arg;
		struct_size = data->dm_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(struct ksysctl_driver_delmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_delmod), struct_size);
		format       = data->dm_format;
		delmod_flags = data->dm_flags;
		COMPILER_READ_BARRIER();
		VALIDATE_FLAGSET(delmod_flags,
		                 KSYSCTL_DRIVER_DELMOD_FNORMAL |
		                 KSYSCTL_DRIVER_DELMOD_FNODEPEND |
		                 KSYSCTL_DRIVER_DELMOD_FFORCE |
		                 KSYSCTL_DRIVER_DELMOD_FNONBLOCK,
		                 E_INVALID_ARGUMENT_CONTEXT_DELMOD_FLAGS);
		switch (format) {

		case KSYSCTL_DRIVER_FORMAT_FILE: {
			REF struct mfile *file;
			file = handles_lookupmfile(data->dm_file);
			FINALLY_DECREF_UNLIKELY(file);
			require(CAP_SYS_MODULE);
			error = driver_delmod(file, delmod_flags);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_NAME: {
			USER CHECKED char const *name;
			name = data->dm_name;
			COMPILER_READ_BARRIER();
			validate_readable(name, 1);
			require(CAP_SYS_MODULE);
			error = driver_delmod(name, delmod_flags);
		}	break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT,
			      format);
		}
		return error;
	}	break;

	case KSYSCTL_DRIVER_GETMOD: {
		USER CHECKED struct ksysctl_driver_getmod *data;
		size_t struct_size;
		u16 format;
		REF struct driver *drv;
		validate_readwrite(arg, sizeof(struct ksysctl_driver_getmod));
		data        = (struct ksysctl_driver_getmod *)arg;
		struct_size = data->gm_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(struct ksysctl_driver_getmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_getmod), struct_size);
		format = data->gm_format;
		COMPILER_READ_BARRIER();
		switch (format) {

		case KSYSCTL_DRIVER_FORMAT_BLOB: {
			void *addr = data->gm_addr;
			COMPILER_READ_BARRIER();
			require(CAP_SYS_MODULE);
			drv = driver_fromaddr(addr);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_FILE: {
			REF struct mfile *file;
			fd_t fileno = data->gm_file;
			COMPILER_READ_BARRIER();
			file = handles_lookupmfile(fileno);
			FINALLY_DECREF_UNLIKELY(file);
			require(CAP_SYS_MODULE);
			drv = driver_fromfile(file);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_NAME: {
			USER CHECKED char const *name;
			name = data->gm_name;
			COMPILER_READ_BARRIER();
			validate_readable(name, 1);
			require(CAP_SYS_MODULE);
			drv = driver_fromname(name);
		}	break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT,
			      format);
		}
		if (!drv)
			return -ENOENT;
		FINALLY_DECREF_UNLIKELY(drv);
		{
			struct handle temp;
			temp.h_type = HANDLE_TYPE_MODULE;
			temp.h_mode = IO_RDWR;
			temp.h_data = drv;
			return handles_install_openfd(temp, &data->gm_driver);
		}
	}	break;

	case KSYSCTL_DRIVER_GET_LIBRARY_PATH: {
		USER CHECKED struct ksysctl_driver_get_library_path *data;
		size_t struct_size, bufsize, reqsize;
		USER UNCHECKED char *buffer;
		REF struct driver_libpath_struct *libpath;
		validate_readwrite(arg, sizeof(struct ksysctl_driver_get_library_path));
		data        = (struct ksysctl_driver_get_library_path *)arg;
		struct_size = data->glp_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(struct ksysctl_driver_get_library_path))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_get_library_path), struct_size);
		require(CAP_SYS_MODULE);

		/* Read the user-space buffer address/size. */
		buffer  = data->glp_buf;
		bufsize = data->glp_size;
		COMPILER_READ_BARRIER();

		/* Load the library path. */
		libpath = arref_get(&driver_libpath);
		FINALLY_DECREF_UNLIKELY(libpath);

		/* Figure out the required buffer size. */
		reqsize = (strlen(libpath->dlp_path) + 1) * sizeof(char);

		/* Write back the required buffer size. */
		COMPILER_WRITE_BARRIER();
		data->glp_size = reqsize;
		COMPILER_WRITE_BARRIER();

		/* Truncate the used buffer size. */
		if (bufsize > reqsize)
			bufsize = reqsize;

		if (bufsize) {
			/* Copy the library path to user-space. */
			validate_writable(buffer, bufsize);
			COMPILER_WRITE_BARRIER();
			memcpy(buffer, libpath->dlp_path, bufsize);
			COMPILER_WRITE_BARRIER();
		}
	}	break;

	case KSYSCTL_DRIVER_SET_LIBRARY_PATH: {
		USER CHECKED struct ksysctl_driver_set_library_path *data;
		USER UNCHECKED char const *oldpath, *newpath;
		REF struct driver_libpath_struct *newpath_string;
		size_t struct_size;
		validate_readwrite(arg, sizeof(struct ksysctl_driver_set_library_path));
		data        = (struct ksysctl_driver_set_library_path *)arg;
		struct_size = data->slp_struct_size;
		COMPILER_READ_BARRIER();
		if (struct_size != sizeof(struct ksysctl_driver_set_library_path))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_set_library_path), struct_size);
		require(CAP_SYS_MODULE);
		oldpath = data->slp_oldpath;
		newpath = data->slp_newpath;
		COMPILER_READ_BARRIER();
		validate_readable_opt(oldpath, 1);
		if (newpath == KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT) {
			newpath_string = incref(&default_library_path);
		} else {
			size_t newpath_len;
			validate_readable(newpath, 1);
			newpath_len = strlen(newpath);
			COMPILER_READ_BARRIER();
			newpath_string = (REF struct driver_libpath_struct *)kmalloc(offsetof(struct driver_libpath_struct, dlp_path) +
			                                                             (newpath_len + 1) * sizeof(char),
			                                                             GFP_LOCKED | GFP_PREFLT);
			TRY {
				memcpy(newpath_string, newpath, newpath_len, sizeof(char));
				newpath_string->dlp_path[newpath_len] = '\0';
				newpath_string->dlp_refcnt = 1;
				COMPILER_BARRIER();
			} EXCEPT {
				kfree(newpath_string);
				RETHROW();
			}
		}
		if (oldpath) {
			bool oldpath_is_correct;
			size_t oldpath_len;
			REF struct driver_libpath_struct *oldpath_string;
again_get_oldpath:
			oldpath_string = arref_get(&driver_libpath);
			oldpath_len = (strlen(oldpath_string->dlp_path) + 1) * sizeof(char);
			TRY {
				oldpath_is_correct = memcmp(oldpath_string->dlp_path,
				                            oldpath, oldpath_len) == 0;
			} EXCEPT {
				decref_likely(newpath_string);
				decref_unlikely(oldpath_string);
				RETHROW();
			}
			if (!oldpath_is_correct) {
				decref_likely(newpath_string);
				decref_unlikely(oldpath_string);
				return -EPERM;
			}
			/* Compare-exchange the old path for the new one. */
			if (!arref_cmpxch_inherit_new_nokill(&driver_libpath,
			                                     oldpath_string,
			                                     newpath_string)) {
				decref_likely(oldpath_string);
				goto again_get_oldpath;
			}
			decref_likely(oldpath_string);
		} else {
			/* Simply set the new library path without comparing it to the old. */
			arref_set_inherit(&driver_libpath, newpath_string);
		}
	}	break;

	case KSYSCTL_OPEN_KERNEL_DRIVER: {
		struct handle temp;
		require(CAP_SYS_MODULE);
		temp.h_type = HANDLE_TYPE_MODULE;
		temp.h_mode = IO_RDWR;
		temp.h_data = &kernel_driver;
		return handles_install_openfd(temp, (USER UNCHECKED struct openfd *)arg);
	}	break;

	case KSYSCTL_OPEN_BOOT_TASK: {
		struct handle temp;
		require(CAP_SYS_ADMIN);
		temp.h_type = HANDLE_TYPE_PIDFD;
		temp.h_mode = IO_RDWR;
		temp.h_data = FORTASK(&boottask, this_taskpid);
		return handles_install_openfd(temp, (USER UNCHECKED struct openfd *)arg);
	}	break;

#ifdef CONFIG_HAVE_HACKY_REBOOT
	case 0xcccc0001: {
		PREEMPTION_DISABLE();
		printk(KERN_RAW "Reboot\n\n\n\n\n\n\n\n\n\n\n\n\n"
		                "%{monitor:system_reset\n}\n");
		while (inb((port_t)0x64) & 0x02);
		outb((port_t)0x64, 0xfe);
		PREEMPTION_HALT();
	}	break;
#endif /* CONFIG_HAVE_HACKY_REBOOT */

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_KSYSCTL_COMMAND,
		      command);
		break;
	}
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_KSYSCTL */

#ifdef __ARCH_WANT_SYSCALL_INIT_MODULE
DEFINE_SYSCALL3(errno_t, init_module,
                USER UNCHECKED void const *, module_image, size_t, len,
                USER UNCHECKED char const *, uargs) {
	REF struct driver *drv;
	validate_readable(module_image, len);
	validate_readable(uargs, 1);
	require(CAP_SYS_MODULE);
	drv = driver_insmod_blob((byte_t *)module_image, len, uargs);
	decref_unlikely(drv);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_INIT_MODULE */

#ifdef __ARCH_WANT_SYSCALL_FINIT_MODULE
DEFINE_SYSCALL3(errno_t, finit_module, fd_t, fd,
                USER UNCHECKED char const *, uargs,
                syscall_ulong_t, flags) {
	REF struct driver *drv;
	(void)flags; /* Ignored... (for now) */
	validate_readable(uargs, 1);
	drv = load_driver_from_file_handles(fd, -1, -1, uargs, NULL,
	                                    KSYSCTL_DRIVER_INSMOD_FNORMAL);
	decref_unlikely(drv);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FINIT_MODULE */

#ifdef __ARCH_WANT_SYSCALL_DELETE_MODULE
DEFINE_SYSCALL2(errno_t, delete_module,
                USER UNCHECKED char const *, name,
                oflag_t, flags) {
	unsigned int error;
	unsigned int delmod_flags;
	validate_readable(name, 1);
	VALIDATE_FLAGSET(flags, O_TRUNC | O_NONBLOCK,
	                 E_INVALID_ARGUMENT_CONTEXT_DELETE_MODULE_FLAGS);
#if (O_TRUNC == KSYSCTL_DRIVER_DELMOD_FFORCE && O_NONBLOCK == KSYSCTL_DRIVER_DELMOD_FNONBLOCK)
	delmod_flags = flags & (O_TRUNC | O_NONBLOCK);
#else /* O_TRUNC == KSYSCTL_DRIVER_DELMOD_FFORCE && O_NONBLOCK == KSYSCTL_DRIVER_DELMOD_FNONBLOCK */
	delmod_flags = KSYSCTL_DRIVER_DELMOD_FNORMAL;
	if (flags & O_TRUNC)
		delmod_flags = KSYSCTL_DRIVER_DELMOD_FFORCE;
	if (flags & O_NONBLOCK)
		delmod_flags |= KSYSCTL_DRIVER_DELMOD_FNONBLOCK;
#endif /* O_TRUNC != KSYSCTL_DRIVER_DELMOD_FFORCE || O_NONBLOCK != KSYSCTL_DRIVER_DELMOD_FNONBLOCK */
	require(CAP_SYS_MODULE);
	error = driver_delmod(name, delmod_flags);
	if (error == DRIVER_DELMOD_ST_UNKNOWN)
		return -ENOENT;
	if (error == DRIVER_DELMOD_ST_INUSE)
		return -EBUSY;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_DELETE_MODULE */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_KSYSCTL_C */
