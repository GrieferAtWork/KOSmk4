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
#ifndef GUARD_KERNEL_SRC_MISC_KSYSCTL_C
#define GUARD_KERNEL_SRC_MISC_KSYSCTL_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/personality.h>
#include <kernel/profiler.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <kos/except/inval.h>
#include <kos/ksysctl.h>

#include <errno.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* The default library path.
 * By default, this string is simply set to "/os/drivers"
 * NOTE: This path can be restored with
 *      `ksysctl_set_driver_library_path(KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT)' */
INTDEF struct driver_library_path_string default_library_path;





/************************************************************************/
/* ksysctl()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KSYSCTL
DEFINE_SYSCALL2(syscall_slong_t, ksysctl,
                syscall_ulong_t, command,
                USER UNCHECKED void *, arg) {
	switch (command) {

	case KSYSCTL_SYSTEM_CLEARCACHES:
		cred_require_sysadmin();
		return (syscall_slong_t)system_clearcaches();

	case KSYSCTL_SYSTEM_TRIMHEAPS:
		cred_require_sysadmin();
		return (syscall_slong_t)system_trimheaps();

	case KSYSCTL_SYSTEM_MEMORY_DUMP_LEAKS:
		cred_require_sysadmin();
		return (syscall_slong_t)mall_dump_leaks(GFP_NORMAL);

	case KSYSCTL_SYSTEM_MEMORY_VALIDATE_PADDING:
		cred_require_sysadmin();
		mall_validate_padding();
		return 0;

	case KSYSCTL_SYSTEM_BRANCH_DUMP_STATS:
		cred_require_sysadmin();
		dump_branch_stats();
		return 0;

	case KSYSCTL_SYSCALL_GET_PERSONALITY: {
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

	case KSYSCTL_SYSCALL_SET_PERSONALITY: {
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
		require(CAP_DRIVER_QUERY);
		temp.h_type = HANDLE_TYPE_DRIVER_STATE;
		temp.h_mode = IO_RDWR;
		temp.h_data = driver_get_state();
		FINALLY_DECREF_UNLIKELY((struct driver_state *)temp.h_data);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case KSYSCTL_DRIVER_INSMOD: {
		USER CHECKED struct ksysctl_driver_insmod *data;
		size_t struct_size;
		u16 format;
		USER CHECKED char const *commandline;
		bool new_driver_loaded;
		REF struct driver *drv;
		unsigned int insmod_flags;
		STATIC_ASSERT(KSYSCTL_DRIVER_INSMOD_FNORMAL == DRIVER_INSMOD_FLAG_NORMAL);
		STATIC_ASSERT(KSYSCTL_DRIVER_INSMOD_FNOINIT == DRIVER_INSMOD_FLAG_NOINIT);
		validate_readwrite(arg, sizeof(struct ksysctl_driver_insmod));
		data        = (struct ksysctl_driver_insmod *)arg;
		struct_size = ATOMIC_READ(data->im_struct_size);
		if (struct_size != sizeof(struct ksysctl_driver_insmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_insmod), struct_size);
		COMPILER_BARRIER();
		format       = ATOMIC_READ(data->im_format);
		commandline  = ATOMIC_READ(data->im_cmdline);
		insmod_flags = ATOMIC_READ(data->im_flags);
		validate_readable_opt(commandline, 1);
		VALIDATE_FLAGSET(insmod_flags,
		                 KSYSCTL_DRIVER_INSMOD_FNORMAL |
		                 KSYSCTL_DRIVER_INSMOD_FNOINIT,
		                 E_INVALID_ARGUMENT_CONTEXT_INSMOD_FLAGS);
		switch (format) {

		case KSYSCTL_DRIVER_FORMAT_BLOB: {
			USER CHECKED void const *base;
			size_t size;
			base = ATOMIC_READ(data->im_blob.b_base);
			size = ATOMIC_READ(data->im_blob.b_size);
			validate_readable(base, size);
			require(CAP_SYS_MODULE);
			drv = driver_insmod((byte_t *)base,
			                    size,
			                    commandline,
			                    &new_driver_loaded,
			                    insmod_flags);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_FILE: {
			REF struct regular_node *ino;
			REF struct path *driver_path;
			REF struct directory_entry *driver_dentry;
			uint32_t temp;
			ino = handle_get_regular_node((unsigned int)ATOMIC_READ(data->im_file.f_node));
			FINALLY_DECREF_UNLIKELY(ino);
			driver_path = NULL;
			temp        = ATOMIC_READ(data->im_file.f_path);
			if (temp != (uint32_t)-1)
				driver_path = handle_get_path((unsigned int)temp);
			FINALLY_XDECREF_UNLIKELY(driver_path);
			driver_dentry = NULL;
			temp          = ATOMIC_READ(data->im_file.f_dentry);
			if (temp != (uint32_t)-1)
				driver_dentry = handle_get_directory_entry((unsigned int)temp);
			FINALLY_XDECREF_UNLIKELY(driver_dentry);
			require(CAP_SYS_MODULE);
			drv = driver_insmod(ino,
			                    driver_path,
			                    driver_dentry,
			                    commandline,
			                    &new_driver_loaded,
			                    insmod_flags);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_NAME: {
			USER CHECKED char const *name;
			name = ATOMIC_READ(data->im_name);
			validate_readable(name, 1);
			require(CAP_SYS_MODULE);
			drv = driver_insmod(name,
			                    commandline,
			                    &new_driver_loaded,
			                    insmod_flags);
		}	break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_MODULE_FORMAT,
			      format);
		}
		FINALLY_DECREF_UNLIKELY(drv);
		ATOMIC_WRITE(data->im_newdriver, new_driver_loaded ? 1 : 0);
		{
			struct hop_openfd *drv_fd;
			drv_fd = ATOMIC_READ(data->im_driver);
			if (drv_fd) {
				struct handle temp;
				temp.h_type = HANDLE_TYPE_DRIVER;
				temp.h_mode = IO_RDWR;
				temp.h_data = drv;
				return handle_installhop(drv_fd, temp);
			}
		}
	}	break;

	case KSYSCTL_DRIVER_DELMOD: {
		USER CHECKED struct ksysctl_driver_delmod *data;
		size_t struct_size;
		u16 format;
		unsigned int delmod_flags, error;
		STATIC_ASSERT(KSYSCTL_DRIVER_DELMOD_FNORMAL == DRIVER_DELMOD_FLAG_NORMAL);
		STATIC_ASSERT(KSYSCTL_DRIVER_DELMOD_FDEPEND == DRIVER_DELMOD_FLAG_DEPEND);
		STATIC_ASSERT(KSYSCTL_DRIVER_DELMOD_SUCCESS == DRIVER_DELMOD_SUCCESS);
		STATIC_ASSERT(KSYSCTL_DRIVER_DELMOD_UNKNOWN == DRIVER_DELMOD_UNKNOWN);
		STATIC_ASSERT(KSYSCTL_DRIVER_DELMOD_INUSE == DRIVER_DELMOD_INUSE);
		validate_readwrite(arg, sizeof(struct ksysctl_driver_delmod));
		data        = (struct ksysctl_driver_delmod *)arg;
		struct_size = ATOMIC_READ(data->dm_struct_size);
		if (struct_size != sizeof(struct ksysctl_driver_delmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_delmod), struct_size);
		COMPILER_BARRIER();
		format       = ATOMIC_READ(data->dm_format);
		delmod_flags = ATOMIC_READ(data->dm_flags);
		VALIDATE_FLAGSET(delmod_flags,
		                 KSYSCTL_DRIVER_DELMOD_FNORMAL |
		                 KSYSCTL_DRIVER_DELMOD_FDEPEND,
		                 E_INVALID_ARGUMENT_CONTEXT_DELMOD_FLAGS);
		switch (format) {

		case KSYSCTL_DRIVER_FORMAT_FILE: {
			REF struct regular_node *node;
			node = handle_get_regular_node((unsigned int)ATOMIC_READ(data->dm_file));
			FINALLY_DECREF_UNLIKELY(node);
			require(CAP_SYS_MODULE);
			error = driver_delmod(node, delmod_flags);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_NAME: {
			USER CHECKED char const *name;
			name = ATOMIC_READ(data->dm_name);
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
		struct_size = ATOMIC_READ(data->gm_struct_size);
		if (struct_size != sizeof(struct ksysctl_driver_getmod))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_getmod), struct_size);
		COMPILER_BARRIER();
		format = ATOMIC_READ(data->gm_format);
		switch (format) {

		case KSYSCTL_DRIVER_FORMAT_BLOB: {
			void *addr = ATOMIC_READ(data->gm_addr);
			COMPILER_READ_BARRIER();
			require(CAP_DRIVER_QUERY);
			drv = driver_at_address(addr);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_FILE: {
			REF struct regular_node *node;
			unsigned int fileno;
			fileno = (unsigned int)ATOMIC_READ(data->gm_file);
			COMPILER_READ_BARRIER();
			node = handle_get_regular_node(fileno);
			FINALLY_DECREF_UNLIKELY(node);
			require(CAP_DRIVER_QUERY);
			drv = driver_with_file(node);
		}	break;

		case KSYSCTL_DRIVER_FORMAT_NAME: {
			USER CHECKED char const *name;
			name = ATOMIC_READ(data->gm_name);
			validate_readable(name, 1);
			COMPILER_READ_BARRIER();
			require(CAP_DRIVER_QUERY);
			drv = name[0] == '/'
			      ? driver_with_filename(name)
			      : driver_with_name(name);
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
			temp.h_type = HANDLE_TYPE_DRIVER;
			temp.h_mode = IO_RDWR;
			temp.h_data = drv;
			return handle_installhop((struct hop_openfd *)&data->gm_driver, temp);
		}
	}	break;

	case KSYSCTL_DRIVER_GET_LIBRARY_PATH: {
		USER CHECKED struct ksysctl_driver_get_library_path *data;
		size_t struct_size, bufsize, reqsize;
		USER UNCHECKED char *buffer;
		REF struct driver_library_path_string *libpath;
		validate_readwrite(arg, sizeof(struct ksysctl_driver_get_library_path));
		data        = (struct ksysctl_driver_get_library_path *)arg;
		struct_size = ATOMIC_READ(data->glp_struct_size);
		if (struct_size != sizeof(struct ksysctl_driver_get_library_path))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_get_library_path), struct_size);
		require(CAP_DRIVER_QUERY);

		/* Read the user-space buffer address/size. */
		COMPILER_READ_BARRIER();
		buffer  = data->glp_buf;
		bufsize = data->glp_size;
		COMPILER_READ_BARRIER();

		/* Load the library path. */
		libpath = driver_library_path.get();
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
		REF struct driver_library_path_string *newpath_string;
		size_t struct_size;
		validate_readwrite(arg, sizeof(struct ksysctl_driver_set_library_path));
		data        = (struct ksysctl_driver_set_library_path *)arg;
		struct_size = ATOMIC_READ(data->slp_struct_size);
		if (struct_size != sizeof(struct ksysctl_driver_set_library_path))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct ksysctl_driver_set_library_path), struct_size);
		require(CAP_SYS_MODULE);
		COMPILER_READ_BARRIER();
		oldpath = data->slp_oldpath;
		newpath = data->slp_newpath;
		COMPILER_READ_BARRIER();
		validate_readable_opt(oldpath, 1);
		if (newpath == KSYSCTL_DRIVER_LIBRARY_PATH_DEFAULT) {
			newpath_string = incref(&default_library_path);
		} else {
			size_t newpath_len;
			validate_readable(newpath, 1);
			COMPILER_BARRIER();
			newpath_len = strlen(newpath);
			COMPILER_READ_BARRIER();
			newpath_string = (REF struct driver_library_path_string *)kmalloc(offsetof(struct driver_library_path_string, dlp_path) +
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
			REF struct driver_library_path_string *oldpath_string;
again_get_oldpath:
			oldpath_string = driver_library_path.get();
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
			if (!driver_library_path.cmpxch_inherit_new(oldpath_string, newpath_string))
				goto again_get_oldpath;
			decref_likely(oldpath_string);
		} else {
			/* Simply set the new library path without comparing it to the old. */
			driver_library_path.set_inherit_new(newpath_string);
		}
	}	break;

	case KSYSCTL_OPEN_KERNEL_DRIVER: {
		struct handle temp;
		require(CAP_DRIVER_QUERY);
		temp.h_type = HANDLE_TYPE_DRIVER;
		temp.h_mode = IO_RDWR;
		temp.h_data = &kernel_driver;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case KSYSCTL_OPEN_KERNEL_VFS: {
		struct handle temp;
		cred_require_sysadmin();
		temp.h_type = HANDLE_TYPE_PATH;
		temp.h_mode = IO_RDWR;
		temp.h_data = &vfs_kernel;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case KSYSCTL_OPEN_KERNEL_FS: {
		struct handle temp;
		require(CAP_KERNEL_QUERY);
		temp.h_type = HANDLE_TYPE_FS;
		temp.h_mode = IO_RDWR;
		temp.h_data = &fs_kernel;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case KSYSCTL_OPEN_KERNEL_VM: {
		struct handle temp;
		require(CAP_KERNEL_QUERY);
		temp.h_type = HANDLE_TYPE_FS;
		temp.h_mode = IO_RDWR;
		temp.h_data = &vm_kernel;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case KSYSCTL_OPEN_ROOT_PIDNS: {
		struct handle temp;
		require(CAP_KERNEL_QUERY);
		temp.h_type = HANDLE_TYPE_FS;
		temp.h_mode = IO_RDWR;
		temp.h_data = &pidns_root;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case KSYSCTL_OPEN_BOOT_TASK: {
		struct handle temp;
		require(CAP_KERNEL_QUERY);
		temp.h_type = HANDLE_TYPE_TASK;
		temp.h_mode = IO_RDWR;
		temp.h_data = FORTASK(&_boottask, this_taskpid);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_KSYSCTL_COMMAND,
		      command);
		break;
	}
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_KSYSCTL */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_KSYSCTL_C */
