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
#ifndef GUARD_KERNEL_CORE_FS_FILE_C
#define GUARD_KERNEL_CORE_FS_FILE_C 1
#define _KOS_SOURCE 1
#define __DIRENT_TEXTSIZE 1024 /* Just so we can use the type in arrays. */

#include <kernel/compiler.h>

#include <fs/fifo.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/user.h>
#include <sched/cred.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except/fs.h>
#include <kos/except/inval.h>
#include <kos/hop/file.h>

#include <assert.h>
#include <dirent.h>
#include <stdalign.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

PUBLIC NOBLOCK void
NOTHROW(KCALL file_destroy)(struct file *__restrict self) {
	if (INODE_ISDIR(self->f_node))
		xdecref(self->f_curent);
	decref(self->f_node);
	xdecref(self->f_path);
	xdecref(self->f_dirent);
	kfree(self);
}

#undef CONFIG_BLOCKING_REGULAR_FILE_READ
//#define CONFIG_BLOCKING_REGULAR_FILE_READ 1

LOCAL NOBLOCK void
NOTHROW(KCALL translate_read_exceptions)(struct file *__restrict self) {
	if (error_code() == ERROR_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION) &&
	    PERTASK_GET(this_exception_pointers[0]) == E_FILESYSTEM_OPERATION_READ &&
	    INODE_ISDIR(self->f_node)) {
		/* Posix wants us to return -EISDIR when trying to read from a directory... */
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_IS_A_DIRECTORY));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)E_FILESYSTEM_IS_A_DIRECTORY_READ);
	}
}

DEFINE_HANDLE_REFCNT_FUNCTIONS(file, struct file)
INTERN size_t KCALL
handle_file_read(struct file *__restrict self,
                 USER CHECKED void *dst,
                 size_t num_bytes,
                 iomode_t UNUSED(mode)) {
	pos_t old_pos;
	size_t result;
	TRY {
		do {
			old_pos = ATOMIC_READ(self->f_offset);
#ifndef CONFIG_BLOCKING_REGULAR_FILE_READ
			result  = inode_read(self->f_node, dst, num_bytes, old_pos);
#else /* !CONFIG_BLOCKING_REGULAR_FILE_READ */
			result  = mode & IO_NONBLOCK
			         ? inode_read(self->f_node, dst, num_bytes, old_pos)
			         : inode_read_blocking(self->f_node, dst, num_bytes, old_pos);
#endif /* CONFIG_BLOCKING_REGULAR_FILE_READ */
		} while (unlikely(!ATOMIC_CMPXCH(self->f_offset, old_pos, old_pos + result)) && result);
	} EXCEPT {
		translate_read_exceptions(self);
		RETHROW();
	}
	return result;
}

INTERN size_t KCALL
handle_file_write(struct file *__restrict self,
                  USER CHECKED void const *src,
                  size_t num_bytes,
                  iomode_t mode) {
	pos_t old_pos, dst_pos;
	inode_loadattr(self->f_node);
	do {
		old_pos = ATOMIC_READ(self->f_offset);
		/* TODO: This implementation of `IO_APPEND' isn't thread-safe! */
		dst_pos = mode & IO_APPEND ? ATOMIC_READ(self->f_node->i_filesize) : old_pos;
		inode_write(self->f_node, src, num_bytes, dst_pos);
	} while (unlikely(!ATOMIC_CMPXCH(self->f_offset, old_pos, dst_pos + num_bytes)) && num_bytes);
	return num_bytes;
}

INTERN size_t KCALL
handle_file_pread(struct file *__restrict self,
                  USER CHECKED void *dst,
                  size_t num_bytes, pos_t addr,
                  iomode_t UNUSED(mode)) {
	size_t result;
	TRY {
#ifndef CONFIG_BLOCKING_REGULAR_FILE_READ
		result = inode_read(self->f_node, dst, num_bytes, addr);
#else /* !CONFIG_BLOCKING_REGULAR_FILE_READ */
		result = mode & IO_NONBLOCK
		         ? inode_read(self->f_node, dst, num_bytes, addr)
		         : inode_read_blocking(self->f_node, dst, num_bytes, addr);
#endif /* CONFIG_BLOCKING_REGULAR_FILE_READ */
	} EXCEPT {
		translate_read_exceptions(self);
		RETHROW();
	}
	return result;
}

INTERN size_t KCALL
handle_file_pwrite(struct file *__restrict self,
                   USER CHECKED void const *src,
                   size_t num_bytes,
                   pos_t addr, iomode_t mode) {
	(void)mode;
	inode_write(self->f_node, src, num_bytes, addr);
	return num_bytes;
}


INTERN size_t KCALL
handle_file_readv(struct file *__restrict self,
                  struct aio_buffer *__restrict dst,
                  size_t num_bytes,
                  iomode_t UNUSED(mode)) {
	pos_t old_pos;
	size_t result;
	TRY {
		do {
			old_pos = ATOMIC_READ(self->f_offset);
#ifndef CONFIG_BLOCKING_REGULAR_FILE_READ
			result  = inode_readv(self->f_node, dst, num_bytes, old_pos);
#else /* !CONFIG_BLOCKING_REGULAR_FILE_READ */
			result  = mode & IO_NONBLOCK
			         ? inode_readv(self->f_node, dst, num_bytes, old_pos)
			         : inode_readv_blocking(self->f_node, dst, num_bytes, old_pos);
#endif /* CONFIG_BLOCKING_REGULAR_FILE_READ */
		} while (unlikely(!ATOMIC_CMPXCH(self->f_offset, old_pos, old_pos + result)) && result);
	} EXCEPT {
		translate_read_exceptions(self);
		RETHROW();
	}
	return result;
}

INTERN size_t KCALL
handle_file_writev(struct file *__restrict self,
                   struct aio_buffer *__restrict src,
                   size_t num_bytes,
                   iomode_t mode) {
	pos_t old_pos, dst_pos;
	inode_loadattr(self->f_node);
	do {
		old_pos = ATOMIC_READ(self->f_offset);
		/* TODO: This implementation of `IO_APPEND' isn't thread-safe! */
		dst_pos = mode & IO_APPEND ? ATOMIC_READ(self->f_node->i_filesize) : old_pos;
		inode_writev(self->f_node, src, num_bytes, dst_pos);
	} while (unlikely(!ATOMIC_CMPXCH(self->f_offset, old_pos, dst_pos + num_bytes)) && num_bytes);
	return num_bytes;
}

INTERN size_t KCALL
handle_file_preadv(struct file *__restrict self,
                   struct aio_buffer *__restrict dst,
                   size_t num_bytes, pos_t addr,
                   iomode_t UNUSED(mode)) {
	size_t result;
	TRY {
#ifndef CONFIG_BLOCKING_REGULAR_FILE_READ
		result = inode_readv(self->f_node, dst, num_bytes, addr);
#else  /* !CONFIG_BLOCKING_REGULAR_FILE_READ */
		result = mode & IO_NONBLOCK
		         ? inode_readv(self->f_node, dst, num_bytes, addr)
		         : inode_readv_blocking(self->f_node, dst, num_bytes, addr);
#endif /* CONFIG_BLOCKING_REGULAR_FILE_READ */
	} EXCEPT {
		translate_read_exceptions(self);
		RETHROW();
	}
	return result;
}

INTERN size_t KCALL
handle_file_pwritev(struct file *__restrict self,
                    struct aio_buffer *__restrict src,
                    size_t num_bytes,
                    pos_t addr, iomode_t mode) {
	(void)mode;
	inode_writev(self->f_node, src, num_bytes, addr);
	return num_bytes;
}

INTERN pos_t KCALL
handle_file_seek(struct file *__restrict self,
                 off_t offset,
                 unsigned int whence) {
	pos_t oldpos, newpos;
	do {
		oldpos = ATOMIC_READ(self->f_offset);
		switch (whence) {

		case SEEK_SET:
			newpos = (pos_t)offset;
			break;

		case SEEK_CUR:
			newpos = oldpos + (pos_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
			break;

		case SEEK_END:
			inode_loadattr(self->f_node);
			if unlikely(OVERFLOW_USUB(self->f_node->i_filesize, (pos_t)-offset, &newpos))
				THROW(E_OVERFLOW);
			break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
			      whence);
			break;
		}
	} while (!ATOMIC_CMPXCH(self->f_offset, oldpos, newpos));
	return newpos;
}


INTERN syscall_slong_t KCALL
handle_file_ioctl(struct file *__restrict self,
                  syscall_ulong_t cmd,
                  USER UNCHECKED void *arg,
                  iomode_t mode) {
	return inode_ioctl(self->f_node, cmd, arg, mode);
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 4, 5)) REF struct vm_datablock *KCALL
handle_file_mmap(struct file *__restrict self,
                 pos_t *__restrict UNUSED(pminoffset),
                 pos_t *__restrict UNUSED(pnumbytes),
                 REF struct path **__restrict pdatablock_fspath,
                 REF struct directory_entry **__restrict pdatablock_fsname)
		THROWS(...) {
	*pdatablock_fspath = xincref(self->f_path);
	*pdatablock_fsname = xincref(self->f_dirent);
	return incref(self->f_node);
}


INTERN void KCALL
handle_file_truncate(struct file *__restrict self, pos_t new_size) {
	inode_truncate(self->f_node, new_size);
}


INTERN pos_t KCALL /* TODO */
handle_file_allocate(struct file *__restrict self,
                     fallocate_mode_t mode,
                     pos_t start, pos_t length)
		THROWS(...);

INTERN void (KCALL handle_file_sync)(struct file *__restrict self) {
	inode_sync(self->f_node);
}

INTERN void (KCALL handle_file_datasync)(struct file *__restrict self) {
	vm_datablock_sync(self->f_node);
}

INTERN void KCALL
handle_file_stat(struct file *__restrict self,
                 USER CHECKED struct stat *result) {
	inode_stat(self->f_node, result);
}

INTERN poll_mode_t KCALL
handle_file_poll(struct file *__restrict self, poll_mode_t what) {
	if (what & POLLOUT) {
		if (rwlock_pollwrite(&self->f_node->db_lock))
			return POLLOUT | POLLIN;
	} else if (what & POLLIN) {
		/* TODO: Poll until the file is larger than the current read-pointer. */
		if (rwlock_pollread(&self->f_node->db_lock))
			return POLLIN;
	}
	return 0;
}

INTERN size_t KCALL
handle_file_readdir(struct file *__restrict self,
                    USER CHECKED struct dirent *buf,
                    size_t bufsize,
                    readdir_mode_t readdir_mode,
                    iomode_t UNUSED(mode)) {
	struct directory_entry *entry, *orig_entry;
	size_t result;
	pos_t dirpos, req_index, entry_pos;
	if unlikely(!INODE_ISDIR(self->f_node))
		THROW(E_FSERROR_NOT_A_DIRECTORY,
		      E_FILESYSTEM_NOT_A_DIRECTORY_READDIR);
again:
	for (;;) {
		dirpos = ATOMIC_READ(self->f_offset);
		if (dirpos < (pos_t)2) {
			if (readdir_mode & READDIR_SKIPREL) {
				/* Skip special entries. */
				ATOMIC_CMPXCH_WEAK(self->f_offset, dirpos, 2);
				continue;
			}
			/* Emit special entries. */
			COMPILER_BARRIER();
			req_index = dirpos + 1;
			result = (offsetof(struct dirent, d_name) +
			          2 * sizeof(char)); /* 2: `.\0' */
			if (dirpos == (pos_t)1)
				++result; /* The second `.' of `..' */
			if (bufsize >= offsetof(struct dirent, d_name)) {
				u16 namelen;
				char name[3] = { '.', 0, 0 };
				namelen      = 1;
				if (dirpos == (pos_t)1)
					++namelen, name[1] = '.';
				/* Fill in basic members of the user-buffer.
				 * CAUTION: E_SEGFAULT */
				if (dirpos == 0) {
					buf->d_ino = (__ino64_t)self->f_node->i_fileino; /* Self */
				} else {
					ino_t parent_node;
					struct path *parent = self->f_path->p_parent;
					if (!parent || self->f_path == ATOMIC_READ(THIS_FS->f_root)) {
						/* No parent, or parent is hidden from view.
						 * >> Skip the parent directory. */
						assert(dirpos == (pos_t)1);
						assert(req_index == (pos_t)2);
						ATOMIC_CMPXCH(self->f_offset, dirpos, req_index);
						goto again;
					}
					/*  Load the INode number of the parent directory. */
					sync_read(parent);
					parent_node = parent->p_inode->i_fileino;
					sync_endread(parent);
					/* Barrier to prevent the dangerous
					 * write that follows from being moved. */
					COMPILER_BARRIER();
					buf->d_ino = (__ino64_t)parent_node;
				}
				/* Save other fields. */
				buf->d_namlen = namelen;
				buf->d_type   = DT_DIR;
				bufsize -= offsetof(struct dirent, d_name);
				if (bufsize >= (size_t)(namelen + 1))
					bufsize = (size_t)(namelen + 1);
				else if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT) {
					req_index = dirpos;
				}
				/* Copy the name to user-space.
				 * CAUTION: E_SEGFAULT */
				memcpy(buf->d_name, name, bufsize, sizeof(char));
				COMPILER_WRITE_BARRIER();
				if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
					req_index = dirpos;
				COMPILER_WRITE_BARRIER();
			} else {
				if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
					req_index = dirpos;
			}
			if (!ATOMIC_CMPXCH_WEAK(self->f_offset, dirpos, dirpos + 1))
				continue;
			break;
		}
		req_index = dirpos - 2;

		/* Read the current directory stream state. */
		atomic_rwlock_read(&self->f_curlck);
		entry_pos = self->f_curidx;
		entry     = self->f_curent;
		atomic_rwlock_endread(&self->f_curlck);
		orig_entry = entry;

		vm_datablock_lock_read(self->f_node);
		TRY {
			if (!entry) {
read_entry_pos_0:
				assert(entry_pos == 0);
				entry = ((struct directory_node *)self->f_node)->d_bypos;
				/* Load the initial directory entry. */
				if (!entry) {
					entry = directory_readnext((struct directory_node *)self->f_node);
					if (!entry) {
						COMPILER_READ_BARRIER();
						entry = ((struct directory_node *)self->f_node)->d_bypos;
						if (!entry)
							goto eof_unlock_node; /* Empty directory */
					}
					entry = ((struct directory_node *)self->f_node)->d_bypos;
					assert(entry);
				}
			}
			/* Load the effective directory entry. */
			while (req_index != entry_pos) {
				if (req_index > entry_pos) {
					/* Advance forward. */
					if (!entry->de_bypos.ln_next) {
						struct directory_node *dir;
						/* No successor.
						 * Either we're on a dangling entry, the directory has ended,
						 * or the remainder of the directory hasn't been loaded yet. */
						dir = (struct directory_node *)self->f_node;
						if (entry != ATOMIC_READ(dir->d_bypos_end)) {
							/* Danging entry (rewind to find the proper position). */
							COMPILER_READ_BARRIER();
							entry = entry->de_bypos.ln_next;
							if (entry)
								goto got_next_entry;
							entry_pos = 0;
							goto read_entry_pos_0;
						}
						/* Last entry (either end of stream, or directory isn't fully loaded) */
						if (dir->i_flags & INODE_FDIRLOADED)
							goto eof_unlock_node; /* End of directory... */
						/* Keep reading more entries. */
						directory_readnext(dir);
						COMPILER_READ_BARRIER();
						entry = entry->de_bypos.ln_next;
						if (!entry)
							goto eof_unlock_node;
					} else {
						/* Read the next entry that has already been cached. */
						entry = entry->de_bypos.ln_next;
					}
got_next_entry:
					++entry_pos;
					continue;
				}
				/* Move backwards through the directory. */
				assert(req_index < entry_pos);
				if (req_index <= (entry_pos - req_index)) {
					/* Quick solution for rewinding, or seeking close to the start. */
					entry     = ((struct directory_node *)self->f_node)->d_bypos;
					entry_pos = 0;
					if unlikely(!entry)
						goto read_entry_pos_0;
					continue;
				}
				assert(req_index < entry_pos);
				/* Move backwards one-at-a-time. */
				if unlikely(entry == ((struct directory_node *)self->f_node)->d_bypos) {
					/* Our directory index broken when files were added/removed.
					 * We're not on the first entry, so set continue searching
					 * for the one that the user requested. */
					entry_pos = 0;
					continue;
				}
				assert(req_index < entry_pos);
				/* Move backwards by one. */
				entry = COMPILER_CONTAINER_OF(entry->de_bypos.ln_pself,
				                              struct directory_entry,
				                              de_bypos.ln_next);
				--entry_pos;
			}
		} EXCEPT {
			if (vm_datablock_lock_endread(self->f_node))
				goto again;
			RETHROW();
		}
		incref(entry);
		vm_datablock_lock_endread(self->f_node);
		/* Exchange the current entry. */
		atomic_rwlock_write(&self->f_curlck);
		if unlikely(self->f_curent != orig_entry) {
			/* Something changed (try again) */
			atomic_rwlock_endwrite(&self->f_curlck);
			decref(entry);
			goto again;
		}
		/* Override the current position. */
		self->f_curidx = req_index;
		self->f_curent = incref(entry);
		atomic_rwlock_endwrite(&self->f_curlck);
		/* Drop a reference from the original entry. */
		xdecref(orig_entry);
		TRY {
			/* Emit the directory entry `entry' */
			COMPILER_BARRIER();
			req_index = dirpos + 1;
			result = ((offsetof(struct dirent, d_name)) +
			          (entry->de_namelen + 1) * sizeof(char));
			if (bufsize >= offsetof(struct dirent, d_name)) {
				/* Fill in basic members of the user-buffer.
				 * CAUTION: E_SEGFAULT */
				/* Regular directory entry. */
				buf->d_ino    = (__ino64_t)entry->de_ino;
				buf->d_type   = entry->de_type;
				buf->d_namlen = entry->de_namelen;
				bufsize -= offsetof(struct dirent, d_name);
				if (bufsize >= (size_t)(entry->de_namelen + 1))
					bufsize = (size_t)(entry->de_namelen + 1);
				else if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT) {
					req_index = dirpos;
				}
				/* Copy the entry name to user-space.
				 * CAUTION: E_SEGFAULT */
				memcpy(buf->d_name, entry->de_name,
				       bufsize, sizeof(char));
				COMPILER_WRITE_BARRIER();
				if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
					req_index = dirpos;
			} else {
				if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
					req_index = dirpos;
			}
		} EXCEPT {
			decref(entry);
			RETHROW();
		}
		decref(entry);
		/* Save the new stream position.
		 * NOTE: This would be allowed to be a weak access.
		 *       However, after so much work, let's put some
		 *       effort into confirming that we've copied data. */
		if (!ATOMIC_CMPXCH(self->f_offset, dirpos, req_index))
			continue;

		break;
	}
	return result;
eof_unlock_node:
	vm_datablock_lock_endread(self->f_node);
	return 0;
}



INTERN syscall_slong_t KCALL
handle_file_hop(struct file *__restrict self,
                syscall_ulong_t cmd,
                USER UNCHECKED void *arg,
                iomode_t mode) {
	switch (cmd) {

	case HOP_FILE_CMPXCHG_OFFSET: {
		size_t struct_size;
		struct hop_file_cmpxchg_offset *data;
		pos_t exppos, newpos, oldpos;
		validate_readwrite(arg, sizeof(struct hop_file_cmpxchg_offset));
		data        = (struct hop_file_cmpxchg_offset *)arg;
		struct_size = ATOMIC_READ(data->cxo_struct_size);
		if (struct_size != sizeof(struct hop_file_cmpxchg_offset))
			THROW(E_BUFFER_TOO_SMALL, sizeof(struct hop_file_cmpxchg_offset), struct_size);
		COMPILER_READ_BARRIER();
		exppos = (pos64_t)data->cxo_expoffset;
		newpos = (pos64_t)data->cxo_newoffset;
		COMPILER_BARRIER();

		/* Apply the new position. */
		oldpos = (pos64_t)ATOMIC_CMPXCH(self->f_offset, exppos, newpos);

		COMPILER_BARRIER();
		/* write back the actual old position */
		data->cxo_oldoffset = (uint64_t)oldpos;
		COMPILER_WRITE_BARRIER();
	}	break;

	case HOP_FILE_OPENNODE: {
		struct handle temp;
		temp.h_type = HANDLE_TYPE_DATABLOCK;
		temp.h_mode = mode;
		temp.h_data = self->f_node;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case HOP_FILE_OPENPATH: {
		struct handle temp;
		temp.h_type = HANDLE_TYPE_PATH;
		temp.h_mode = mode;
		temp.h_data = self->f_path;
		if unlikely(!temp.h_data)
			THROW(E_NO_SUCH_OBJECT);
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	case HOP_FILE_OPENDENTRY: {
		struct handle temp;
		temp.h_type = HANDLE_TYPE_DIRECTORYENTRY;
		temp.h_mode = mode;
		temp.h_data = self->f_dirent;
		return handle_installhop((USER UNCHECKED struct hop_openfd *)arg, temp);
	}	break;

	default:
		/* Handle FIFO control operations if we are referring to one. */
		if (INODE_ISFIFO(self->f_node))
			return fifo_hop((struct fifo_node *)self->f_node, cmd, arg, mode);
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_HOP_COMMAND,
		      cmd);
		break;
	}
	return 0;
}




#define ONESHOT_DIRENT_ALIGNMENT alignof(ino_t)

#define ONESHOT_NEXT_ENTRY(p)                                            \
	((struct dirent *)(((uintptr_t)((p)->d_name + ((p)->d_namlen + 1)) + \
	                    (ONESHOT_DIRENT_ALIGNMENT - 1)) &                \
	                   ~(ONESHOT_DIRENT_ALIGNMENT - 1)))

struct alignas(ONESHOT_DIRENT_ALIGNMENT) oneshot_directory_buffer {
	struct oneshot_directory_buffer *odb_next;   /* [0..1][const][owned] Next buffer. */
	struct dirent                   *odb_end;    /* [1..1][const] Pointer past the end of the last buffer. */
	struct dirent                    odb_buf[1];
};
#define ONESHOT_INITIAL_BUFFER_SIZE  768

PRIVATE NOBLOCK void
NOTHROW(KCALL oneshot_freeentries)(struct oneshot_directory_buffer *__restrict buf) {
	struct oneshot_directory_buffer *next;
	do {
		next = buf->odb_next;
		kfree(buf);
		buf = next;
	} while (buf);
}



struct oneshot_generator_data {
	struct oneshot_directory_buffer **previous_buffer;
	struct oneshot_directory_buffer  *current_buffer;
	struct dirent                    *current_ent;
};

PRIVATE void KCALL
oneshot_enum_callback(struct oneshot_generator_data *__restrict data,
                      char const *__restrict name, u16 namelen,
                      unsigned char type, ino_t ino) {
	size_t size_avail, req_size;
	struct oneshot_directory_buffer *buf = data->current_buffer;
	struct dirent *new_entry;
	assert(data->current_ent >= buf->odb_buf);
	assert(data->current_ent <= buf->odb_end);
	size_avail = (uintptr_t)buf->odb_end - (uintptr_t)data->current_ent;
	req_size   = offsetof(struct dirent, d_name) + (namelen + 1) * sizeof(char);
	if unlikely(size_avail < req_size) {
		/* Free unused memory. */
		struct oneshot_directory_buffer *truncated_buffer;
		struct oneshot_directory_buffer *new_buffer;
		/* Finalize the buffer end-pointer to cut-off any trailing data.
		 * This must be done to prevent the caller from reading beyond the
		 * heap block when later traversing the directory. */
		buf->odb_end = data->current_ent;
		/* Try to reclaim unused memory. */
		truncated_buffer = (struct oneshot_directory_buffer *)krealign_nx(buf,
		                                                                  ONESHOT_DIRENT_ALIGNMENT,
		                                                                  (uintptr_t)data->current_ent -
		                                                                  (uintptr_t)buf->odb_buf,
		                                                                  GFP_NORMAL);
		if likely(truncated_buffer)
			*data->previous_buffer = buf = truncated_buffer;
		data->previous_buffer = &buf->odb_next;
		/* Allocate another buffer. */
		size_avail = (offsetof(struct oneshot_directory_buffer, odb_buf) +
		              ONESHOT_INITIAL_BUFFER_SIZE);
		if unlikely(size_avail < offsetof(struct oneshot_directory_buffer, odb_buf) + req_size)
			size_avail = offsetof(struct oneshot_directory_buffer, odb_buf) + req_size;
		new_buffer = (struct oneshot_directory_buffer *)kmemalign(ONESHOT_DIRENT_ALIGNMENT,
		                                                          size_avail, GFP_NORMAL);
		buf->odb_next        = new_buffer;
		data->current_buffer = new_buffer;
		/* Initialize the new buffer. */
		new_buffer->odb_end  = (struct dirent *)((byte_t *)new_buffer + size_avail);
		new_buffer->odb_next = NULL;
		/* Use the new buffer's starting point as the new current entry. */
		data->current_ent = new_buffer->odb_buf;
	}
	/* Figure out where new data will go. */
	new_entry = data->current_ent;
	req_size += ONESHOT_DIRENT_ALIGNMENT - 1;
	req_size &= ~(ONESHOT_DIRENT_ALIGNMENT - 1);
	data->current_ent = (struct dirent *)((uintptr_t)new_entry + req_size);
	/* Write the new directory entry. */
	new_entry->d_ino    = (__ino64_t)ino;
	new_entry->d_namlen = namelen;
	new_entry->d_type   = type;
	memcpy(new_entry->d_name, name, namelen, sizeof(char));
	new_entry->d_name[namelen] = '\0';
}

PRIVATE ATTR_RETNONNULL struct oneshot_directory_buffer *KCALL
oneshot_getentries(struct directory_node *__restrict node) {
	struct oneshot_directory_buffer *result;
	assert(node->i_type->it_directory.d_oneshot.o_enum);
	result = (struct oneshot_directory_buffer *)kmemalign(ONESHOT_DIRENT_ALIGNMENT,
		                                                  offsetof(struct oneshot_directory_buffer, odb_buf) +
	                                                      ONESHOT_INITIAL_BUFFER_SIZE, GFP_NORMAL);
	assert(IS_ALIGNED((uintptr_t)result, ONESHOT_DIRENT_ALIGNMENT));
	result->odb_next = NULL;
	result->odb_end  = (struct dirent *)((byte_t *)result->odb_buf + ONESHOT_INITIAL_BUFFER_SIZE);
	TRY {
		struct oneshot_generator_data data;
		data.previous_buffer = &result;
		data.current_buffer  = result;
		data.current_ent     = result->odb_buf;
		(*node->i_type->it_directory.d_oneshot.o_enum)(node,
		                                               (directory_enum_callback_t)&oneshot_enum_callback,
		                                               &data);
		assert(data.current_ent <= data.current_buffer->odb_end);
		if (data.current_ent < data.current_buffer->odb_end) {
			struct oneshot_directory_buffer *truncated_buffer;
			assert(data.current_buffer == *data.previous_buffer);
			/* Set the final buffer end. */
			data.current_buffer->odb_end = data.current_ent;
			/* Free unused memory. */
			truncated_buffer = (struct oneshot_directory_buffer *)krealign_nx(data.current_buffer,
			                                                                  ONESHOT_DIRENT_ALIGNMENT,
			                                                                  offsetof(struct oneshot_directory_buffer, odb_buf) +
			                                                                  (uintptr_t)data.current_ent -
			                                                                  (uintptr_t)data.current_buffer->odb_buf,
			                                                                  GFP_NORMAL);
			if likely(truncated_buffer)
				*data.previous_buffer = truncated_buffer;
		}
	} EXCEPT {
		oneshot_freeentries(result);
		RETHROW();
	}
	return result;
}


PUBLIC NOBLOCK void
NOTHROW(KCALL oneshot_directory_file_destroy)(struct oneshot_directory_file *__restrict self) {
	if (self->d_buf)
		oneshot_freeentries(self->d_buf);
	decref(self->d_node);
	xdecref(self->d_path);
	xdecref(self->d_dirent);
	kfree(self);
}


INTERN size_t KCALL
handle_oneshot_directory_file_readdir(struct oneshot_directory_file *__restrict self,
                                      USER CHECKED struct dirent *buf,
                                      size_t bufsize,
                                      readdir_mode_t readdir_mode,
                                      iomode_t UNUSED(mode)) {
	struct oneshot_directory_buffer *old_buffer, *buffer;
	struct dirent *old_entry, *entry;
	size_t result;
	pos_t dirpos, req_index, entry_pos;
	assert(INODE_ISDIR(self->d_node));
again:
	for (;;) {
		dirpos = ATOMIC_READ(self->d_offset);
		if (dirpos < (pos_t)2) {
			if (readdir_mode & READDIR_SKIPREL) {
				/* Skip special entries. */
				ATOMIC_CMPXCH_WEAK(self->d_offset, dirpos, 2);
				continue;
			}
			/* Emit special entries. */
			COMPILER_BARRIER();
			req_index = dirpos + 1;
			result    = (offsetof(struct dirent, d_name) + 2 * sizeof(char)); /* 2: `.\0' */
			if (dirpos == (pos_t)1)
				++result; /* The second `.' of `..' */
			if (bufsize >= offsetof(struct dirent, d_name)) {
				char name[3] = { '.', 0, 0 };
				u16 namelen  = 1;
				if (dirpos == (pos_t)1)
					++namelen, name[1] = '.';
				/* Fill in basic members of the user-buffer.
				 * CAUTION: E_SEGFAULT */
				if (dirpos == 0) {
					buf->d_ino = (__ino64_t)self->d_node->i_fileino; /* Self */
				} else {
					ino_t parent_node;
					struct path *parent = self->d_path->p_parent;
					if (!parent || self->d_path == ATOMIC_READ(THIS_FS->f_root)) {
						/* No parent, or parent is hidden from view.
						 * >> Skip the parent directory. */
						assert(dirpos == (pos_t)1);
						assert(req_index == (pos_t)2);
						ATOMIC_CMPXCH(self->d_offset, dirpos, req_index);
						goto again;
					}
					/*  Load the INode number of the parent directory. */
					sync_read(parent);
					parent_node = parent->p_inode->i_fileino;
					sync_endread(parent);
					/* Barrier to prevent the dangerous
					 * write that follows from being moved. */
					COMPILER_BARRIER();
					buf->d_ino = (__ino64_t)parent_node;
				}
				/* Save other fields. */
				buf->d_namlen = namelen;
				buf->d_type   = DT_DIR;
				bufsize -= offsetof(struct dirent, d_name);
				if (bufsize >= (size_t)(namelen + 1))
					bufsize = (size_t)(namelen + 1);
				else if ((readdir_mode & READDIR_MODEMASK) == READDIR_DEFAULT) {
					req_index = dirpos;
				}
				/* Copy the name to user-space.
				 * CAUTION: E_SEGFAULT */
				memcpy(buf->d_name, name, bufsize, sizeof(char));
				COMPILER_WRITE_BARRIER();
				if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
					req_index = dirpos;
				COMPILER_WRITE_BARRIER();
			} else {
				if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
					req_index = dirpos;
			}
			if (!ATOMIC_CMPXCH_WEAK(self->d_offset, dirpos, dirpos + 1))
				continue;
			break;
		}
		req_index = dirpos - 2;

		/* Lazily load the oneshot buffer. */
		if unlikely(!self->d_buf) {
			struct oneshot_directory_buffer *new_buffer;
			buffer = oneshot_getentries((struct directory_node *)self->d_node);
			COMPILER_READ_BARRIER();
			new_buffer = ATOMIC_CMPXCH_VAL(self->d_buf, NULL, buffer);
			/* Another thread allocated the buffer in the
			 * mean time (WRITE_ONCE; keep existing buffer) */
			if unlikely(new_buffer != NULL)
				oneshot_freeentries(buffer);
		}

		/* Read the current directory stream state. */
		sync_read(&self->d_curlck);
		entry_pos  = self->d_curidx;
		old_buffer = self->d_curbuf;
		old_entry  = self->d_curent;
		sync_endread(&self->d_curlck);
		buffer = old_buffer;
		entry  = old_entry;
		assert((buffer == NULL) == (entry == NULL));
		if (!buffer) {
read_entry_pos_0:
			assert(entry_pos == 0);
			buffer = self->d_buf;
			entry  = buffer->odb_buf;
		}

		/* Load the effective directory entry. */
		for (;;) {
			assert(entry);
			assert(buffer->odb_end >= buffer->odb_buf);
			assert(entry >= buffer->odb_buf);
			assert((uintptr_t)entry <= (uintptr_t)buffer->odb_end + ONESHOT_DIRENT_ALIGNMENT);
			if unlikely(entry >= buffer->odb_end) {
				buffer = buffer->odb_next;
				if unlikely(!buffer)
					return 0; /* End of directory */
				entry = buffer->odb_buf;
				assert(entry < buffer->odb_end);
			}
			if (req_index == entry_pos)
				break;
			if (req_index > entry_pos) {
				/* Advance forward. */
				entry = ONESHOT_NEXT_ENTRY(entry);
				++entry_pos;
				continue;
			}
			/* Restart at the beginning. */
			assert(req_index < entry_pos);
			entry_pos = 0;
			goto read_entry_pos_0;
		}

		/* Exchange the current entry. */
		atomic_rwlock_write(&self->d_curlck);
		if unlikely(self->d_curbuf != old_buffer ||
		            self->d_curent != old_entry) {
			/* Something changed (try again) */
			atomic_rwlock_endwrite(&self->d_curlck);
			goto again;
		}
		/* Override the current position. */
		self->d_curidx = req_index;
		self->d_curbuf = buffer;
		self->d_curent = entry;
		atomic_rwlock_endwrite(&self->d_curlck);

		/* Emit the directory entry `entry' */
		COMPILER_BARRIER();
		req_index = dirpos + 1;
		result    = (offsetof(struct dirent, d_name) + (entry->d_namlen + 1) * sizeof(char));
		if (bufsize >= result) {
			memcpy(buf, entry, result);
			if ((readdir_mode & READDIR_MODEMASK) == READDIR_PEEK)
				req_index = dirpos;
		} else {
			memcpy(buf, entry, bufsize);
			if ((readdir_mode & READDIR_MODEMASK) != READDIR_CONTINUE)
				req_index = dirpos;
		}
		/* Save the new stream position.
		 * NOTE: This would be allowed to be a weak access.
		 *       However, after so much work, let's put some
		 *       effort into confirming that we've copied data. */
		if (!ATOMIC_CMPXCH(self->d_offset, dirpos, req_index))
			continue;
		break;
	}
	return result;
}

DEFINE_HANDLE_REFCNT_FUNCTIONS(oneshot_directory_file, struct oneshot_directory_file)
/* TODO: Other handle operators */

DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_read, handle_file_read);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_write, handle_file_write);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_pread, handle_file_pread);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_pwrite, handle_file_pwrite);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_readv, handle_file_readv);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_writev, handle_file_writev);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_preadv, handle_file_preadv);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_pwritev, handle_file_pwritev);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_aread, handle_file_aread);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_awrite, handle_file_awrite);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_apread, handle_file_apread);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_apwrite, handle_file_apwrite);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_areadv, handle_file_areadv);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_awritev, handle_file_awritev);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_apreadv, handle_file_apreadv);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_apwritev, handle_file_apwritev);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_mmap, handle_file_mmap);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_sync, handle_file_sync);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_datasync, handle_file_datasync);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_poll, handle_file_poll);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_stat, handle_file_stat);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_ioctl, handle_file_ioctl);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_hop, handle_file_hop);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_seek, handle_file_seek);
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_truncate, handle_file_truncate);


/* Alias the handle_file_tryas() to some other handle types. */
DEFINE_INTERN_ALIAS(handle_oneshot_directory_file_tryas, handle_file_tryas);
DEFINE_INTERN_ALIAS(handle_fifo_user_tryas, handle_file_tryas);

STATIC_ASSERT(offsetof(struct file, f_node) == offsetof(struct oneshot_directory_file, d_node));
STATIC_ASSERT(offsetof(struct file, f_path) == offsetof(struct oneshot_directory_file, d_path));
STATIC_ASSERT(offsetof(struct file, f_dirent) == offsetof(struct oneshot_directory_file, d_dirent));
STATIC_ASSERT(offsetof(struct file, f_node) == offsetof(struct fifo_user, fu_fifo));
STATIC_ASSERT(offsetof(struct file, f_path) == offsetof(struct fifo_user, fu_path));
STATIC_ASSERT(offsetof(struct file, f_dirent) == offsetof(struct fifo_user, fu_dirent));

/* This is the most-used handle converter function,
 * since most open() calls return FILE-objects. */
INTERN NONNULL((1)) REF void *KCALL
handle_file_tryas(struct file *__restrict self,
                  uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK) {
	switch (wanted_type) {

	case HANDLE_TYPE_DATABLOCK:
		return incref(self->f_node);

	case HANDLE_TYPE_DIRECTORYENTRY:
		if (!self->f_dirent)
			break;
		return incref(self->f_dirent);

	case HANDLE_TYPE_PATH:
		if (!self->f_path)
			break;
		return incref(self->f_path);

	default:
		break;
	}
	return NULL;
}



DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_FILE_C */
