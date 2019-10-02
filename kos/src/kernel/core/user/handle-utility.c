/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_USER_HANDLE_UTILITY_C
#define GUARD_KERNEL_SRC_USER_HANDLE_UTILITY_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <dev/keyboard.h>
#include <dev/mouse.h>
#include <dev/pty.h>
#include <dev/tty.h>
#include <dev/ttybase.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/pipe.h>
#include <fs/vfs.h>
#include <kernel/driver.h>
#include <kernel/handle.h>
#include <kernel/types.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>

#include <sys/stat.h>

#include <format-printer.h>

DECL_BEGIN

/* Returns the type-kind code for `self' (One of `HANDLE_TYPEKIND_*') */
PUBLIC NOBLOCK uintptr_half_t
NOTHROW(KCALL handle_typekind)(struct handle const *__restrict self) {
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		if (vm_datablock_isinode((struct vm_datablock *)self->h_data)) {
			if (INODE_ISSUPER((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_SUPERBLOCK;
			if (INODE_ISREG((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_REGULARNODE;
			if (INODE_ISDIR((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_DIRECTORY;
			if (INODE_ISLNK((struct inode *)self->h_data))
				return HANDLE_TYPEKIND_DATABLOCK_SYMLINKNODE;
			return HANDLE_TYPEKIND_DATABLOCK_INODE;
		}
		break;

	case HANDLE_TYPE_BLOCKDEVICE:
		if (block_device_ispartition((struct block_device *)self->h_data))
			return HANDLE_TYPEKIND_BLOCKDEVICE_PARTITION;
		return HANDLE_TYPEKIND_BLOCKDEVICE_DRIVEROOT;
		break;

	case HANDLE_TYPE_CHARACTERDEVICE: {
		struct character_device *me;
		me = (struct character_device *)self;
		if (character_device_isattybase(me)) {
			if (ttybase_isapty((struct ttybase_device *)me))
				return HANDLE_TYPEKIND_CHARACTERDEVICE_PTY;
			if (ttybase_isatty((struct ttybase_device *)me))
				return HANDLE_TYPEKIND_CHARACTERDEVICE_TTY;
			return HANDLE_TYPEKIND_CHARACTERDEVICE_TTYBASE;
		}
		if (character_device_isakeyboard(me))
			return HANDLE_TYPEKIND_CHARACTERDEVICE_KEYBOARD;
		if (character_device_isamouse(me))
			return HANDLE_TYPEKIND_CHARACTERDEVICE_MOUSE;
	}	break;

	case HANDLE_TYPE_PATH:
		if (((struct path *)self->h_data)->p_vfs == (struct path *)self->h_data)
			return HANDLE_TYPEKIND_PATH_VFSROOT;
		break;

	default: break;
	}
	return HANDLE_TYPEKIND_GENERIC;
}


LOCAL bool KCALL
character_device_datasize(struct character_device *__restrict self,
                          pos_t *__restrict presult) {
	struct stat st;
	if (!self->cd_type.ct_stat)
		return false;
	/* Check if the stat-operator fills in the size-field. */
	st.st_size64 = UINT64_C(0xaaaaaaaaaaaaaaaa);
	(*self->cd_type.ct_stat)(self, &st);
	if (st.st_size64 == UINT64_C(0xaaaaaaaaaaaaaaaa)) {
		st.st_size64 = UINT64_C(0x5555555555555555);
		(*self->cd_type.ct_stat)(self, &st);
		if (st.st_size64 == UINT64_C(0x5555555555555555))
			return false; /* The size-field isn't filled in. */
	}
	*presult = (pos_t)st.st_size64;
	return true;
}


/* Try to determine the effective data size of the given handle (as returned by `FIOQSIZE')
 * @return: true:  The data size was stored in `*presult'.
 * @return: false: The data size could not be determined. */
PUBLIC bool KCALL
handle_datasize(struct handle const *__restrict self,
                pos_t *__restrict presult) {
	pos_t value;
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK:
		if (!vm_datablock_isinode((struct vm_datablock *)self->h_data))
			goto badtype;
		inode_loadattr((struct inode *)self->h_data);
		value = ATOMIC_READ(((struct inode *)self->h_data)->i_filesize);
		break;

	case HANDLE_TYPE_BLOCKDEVICE:
		value = ((pos_t)((struct basic_block_device *)self->h_data)->bd_sector_count *
		         (pos_t)((struct basic_block_device *)self->h_data)->bd_sector_size);
		break;

	case HANDLE_TYPE_CHARACTERDEVICE:
		return character_device_datasize((struct character_device *)self, presult);

	case HANDLE_TYPE_DIRECTORYENTRY:
		value = (pos_t)((struct directory_entry *)self->h_data)->de_namelen;
		break;

	case HANDLE_TYPE_FILE:
	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE:
		inode_loadattr(((struct file *)self->h_data)->f_node);
		value = ATOMIC_READ(((struct file *)self->h_data)->f_node->i_filesize);
		break;

	case HANDLE_TYPE_PATH: {
		REF struct inode *node;
		sync_read(((struct path *)self->h_data));
		node = (REF struct inode *)incref(((struct path *)self->h_data)->p_inode);
		sync_endread(((struct path *)self->h_data));
		FINALLY_DECREF_UNLIKELY(node);
		inode_loadattr(node);
		value = ATOMIC_READ(node->i_filesize);
	}	break;

	case HANDLE_TYPE_VM:
		value = ((pos_t)(uintptr_t)-1) + 1;
		break;

	case HANDLE_TYPE_DRIVER:
		value = (pos_t)(((struct driver *)self->h_data)->d_loadend -
		                ((struct driver *)self->h_data)->d_loadstart);
		break;

	case HANDLE_TYPE_PIPE:
		value = (pos_t)ATOMIC_READ(((struct pipe *)self->h_data)->p_buffer.rb_avail);
		break;

	case HANDLE_TYPE_PIPE_READER:
	case HANDLE_TYPE_PIPE_WRITER:
		value = (pos_t)ATOMIC_READ(((struct pipe_reader *)self->h_data)->pr_pipe->p_buffer.rb_avail);
		break;

	case HANDLE_TYPE_PIDNS:
		value = (pos_t)ATOMIC_READ(((struct pidns *)self->h_data)->pn_size);
		break;

	case HANDLE_TYPE_DRIVER_STATE:
		value = (pos_t)((struct driver_state *)self->h_data)->ds_count;
		break;

	default:
badtype:
		return false;
	}
	*presult = value;
	return true;
}

/* Print the text that should result from `readlink("/proc/[pid]/fd/[fdno]")' */
PUBLIC ssize_t KCALL
handle_print(struct handle const *__restrict self,
             pformatprinter printer, void *arg) {
	size_t result;
	switch (self->h_type) {

	case HANDLE_TYPE_DATABLOCK: {
		struct vm_datablock *b = (struct vm_datablock *)self->h_data;
		if (vm_datablock_isinode(b)) {
			result = format_printf(printer, arg,
			                       "anon_inode:[inode:%I64u]",
			                       ((struct inode *)b)->i_fileino);
		} else {
			result = format_printf(printer, arg,
			                       "anon_inode:[datablock:%Iu]",
			                       b);
		}
	}	break;

	case HANDLE_TYPE_BLOCKDEVICE: {
		struct block_device *dev = (struct block_device *)self->h_data;
		result = format_printf(printer, arg, "/dev/%s", dev->bd_name);
	}	break;

	case HANDLE_TYPE_DIRECTORYENTRY: {
		struct directory_entry *ent = (struct directory_entry *)self->h_data;
		result = format_printf(printer, arg, "anon_inode:[directory_entry:%$s]",
		                  ent->de_namelen, ent->de_name);
	}	break;

	case HANDLE_TYPE_FILE: {
		struct file *f = (struct file *)self->h_data;
		if (f->f_path && f->f_dirent) {
			result = path_printent(f->f_path,
			                       f->f_dirent,
			                       printer, arg);
		} else {
			result = format_printf(printer, arg,
			                       "anon_inode:[file:inode:%I64u]",
			                       f->f_node->i_fileino);
		}
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
		struct oneshot_directory_file *f = (struct oneshot_directory_file *)self->h_data;
		if (f->d_path && f->d_dirent) {
			result = path_printent(f->d_path,
			                       f->d_dirent,
			                       printer, arg);
		} else {
			result = format_printf(printer, arg, "anon_inode:[oneshot_directory_file:inode:%I64u]",
			                  f->d_node->i_fileino);
		}
	}	break;

	case HANDLE_TYPE_PATH: {
		struct path *p = (struct path *)self->h_data;
		result = path_print(p, printer, arg);
	}	break;

	case HANDLE_TYPE_FS: {
		struct fs *f = (struct fs *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[fs:%Iu]",
		                       f);
	}	break;

	case HANDLE_TYPE_VM: {
		struct vm *f = (struct vm *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[vm:%Iu]",
		                       f);
	}	break;

	case HANDLE_TYPE_TASK: {
		struct taskpid *t = (struct taskpid *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[task:%u]",
		                       taskpid_getpid_s(t));
	}	break;

	case HANDLE_TYPE_CLOCK: {
		struct wall_clock *c = (struct wall_clock *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[wall_clock:%Iu]",
		                       c);
	}	break;

	case HANDLE_TYPE_DRIVER: {
		struct driver *d = (struct driver *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[driver:%s]",
		                       d->d_filename ? d->d_filename
		                                     : d->d_name);
	}	break;

	case HANDLE_TYPE_PIPE: {
		struct pipe *p = (struct pipe *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[pipe:%Iu]",
		                       p);
	}	break;

	case HANDLE_TYPE_PIPE_READER: {
		struct pipe_reader *p = (struct pipe_reader *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[reader:pipe:%Iu]",
		                       p->pr_pipe);
	}	break;

	case HANDLE_TYPE_PIPE_WRITER: {
		struct pipe_writer *p = (struct pipe_writer *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[writer:pipe:%Iu]",
		                       p->pw_pipe);
	}	break;

	case HANDLE_TYPE_PIDNS: {
		struct pidns *ns = (struct pidns *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[pidns:%Iu]",
		                       ns);
	}	break;

	case HANDLE_TYPE_DRIVER_STATE: {
		struct driver_state *st = (struct driver_state *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[driver_state:%Iu]",
		                       st);
	}	break;

	case HANDLE_TYPE_CHARACTERDEVICE: {
		struct character_device *dev = (struct character_device *)self->h_data;
		result = format_printf(printer, arg,
		                       "/dev/%s",
		                       dev->cd_name);
	}	break;

	case HANDLE_TYPE_EVENTFD_FENCE: {
		struct eventfd *efd = (struct eventfd *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[eventfd:fence:%Iu]",
		                       efd);
	}	break;

	case HANDLE_TYPE_EVENTFD_SEMA: {
		struct eventfd *efd = (struct eventfd *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[eventfd:semaphore:%Iu]",
		                       efd);
	}	break;

	case HANDLE_TYPE_SIGNALFD: {
		struct signalfd *sfd = (struct signalfd *)self->h_data;
		result = format_printf(printer, arg,
		                       "anon_inode:[signalfd:%Iu]",
		                       sfd);
	}	break;

	default:
		result = format_printf(printer, arg, "anon_inode:[%s]",
		                       handle_typename(*self));
		break;
	}
	return result;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_USER_HANDLE_UTILITY_C */
