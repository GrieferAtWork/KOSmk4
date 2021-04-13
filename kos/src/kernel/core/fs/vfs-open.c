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
#ifndef GUARD_KERNEL_CORE_FS_VFS_OPEN_C
#define GUARD_KERNEL_CORE_FS_VFS_OPEN_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <dev/tty.h>
#include <fs/fifo.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/personality.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>

#include <assert.h>
#include <fcntl.h>
#include <malloca.h>
#include <stddef.h>

DECL_BEGIN

PRIVATE ATTR_NOINLINE NONNULL((1, 2, 4, 7, 8, 9, 10, 11, 12, 13)) bool KCALL
openat_create_follow_symlink_dynamic_impl(struct fs *__restrict f,
                                          struct path *__restrict root,
                                          fsmode_t fsmode,
                                          /*in|out*/ u32 *__restrict pmax_remaining_links,
                                          oflag_t oflags, mode_t mode,
                                          struct symlink_node *__restrict sl_node,
                                          /*in|out*/ REF struct path **__restrict presult_containing_path,
                                          /*in|out*/ REF struct directory_node **__restrict presult_containing_directory,
                                          /*in|out*/ REF struct directory_entry **__restrict presult_containing_dirent,
                                          /*in|out*/ REF struct inode **__restrict presult_inode,
                                          /*out*/ bool *__restrict pwas_newly_created,
                                          /*in|out*/ size_t *__restrict pbufsize) {
	char const *last_seg;
	u16 last_seglen;
	REF struct inode *new_result_inode;
	REF struct path *new_result_containing_path;
	REF struct directory_node *new_result_containing_directory;
	REF struct directory_entry *new_result_containing_dirent;
	size_t bufsize = *pbufsize;
	char *buf;
	buf = (char *)malloca(bufsize);
	TRY {
		size_t reqsize;
		assert(sl_node->i_type->it_symlink.sl_readlink_dynamic);
		reqsize = (*sl_node->i_type->it_symlink.sl_readlink_dynamic)(sl_node,
		                                                             buf,
		                                                             bufsize);
		if unlikely(reqsize > bufsize) {
			/* Must try again with a larger buffer size. */
			*pbufsize = reqsize;
			freea(buf);
			return false;
		}
		/* Traverse the symlink text. */
		new_result_containing_path = path_traversen_ex(f,
		                                               *presult_containing_path,
		                                               root,
		                                               buf,
		                                               reqsize,
		                                               &last_seg,
		                                               &last_seglen,
		                                               fsmode,
		                                               pmax_remaining_links);
		decref(*presult_containing_path);
		*presult_containing_path = new_result_containing_path;

		sync_read(*presult_containing_path);
		new_result_containing_directory = (REF struct directory_node *)
		incref((*presult_containing_path)->p_inode);
		sync_endread(*presult_containing_path);
		decref(*presult_containing_directory);
		*presult_containing_directory = new_result_containing_directory;

		/* Repeat the create() function with the symlink's dereferenced text. */
		/* TODO: Permission checks */
		new_result_inode = directory_creatfile(new_result_containing_directory,
		                                       last_seg,
		                                       last_seglen,
		                                       oflags & (O_CREAT | /*O_EXCL|*/ O_DOSPATH),
		                                       fs_getuid(f),
		                                       fs_getgid(f),
		                                       mode,
		                                       &new_result_containing_dirent,
		                                       pwas_newly_created);
		decref(*presult_containing_dirent);
		*presult_containing_dirent = new_result_containing_dirent;
		decref(*presult_inode);
		*presult_inode = new_result_inode;
	} EXCEPT {
		freea(buf);
		RETHROW();
	}
	freea(buf);
	return true;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2, 4, 7, 8, 9, 10, 11, 12)) void KCALL
openat_create_follow_symlink_dynamic(struct fs *__restrict f,
                                     struct path *__restrict root,
                                     fsmode_t fsmode,
                                     /*in|out*/ u32 *__restrict pmax_remaining_links,
                                     oflag_t oflags, mode_t mode,
                                     struct symlink_node *__restrict sl_node,
                                     /*in|out*/ REF struct path **__restrict presult_containing_path,
                                     /*in|out*/ REF struct directory_node **__restrict presult_containing_directory,
                                     /*in|out*/ REF struct directory_entry **__restrict presult_containing_dirent,
                                     /*in|out*/ REF struct inode **__restrict presult_inode,
                                     /*out*/ bool *__restrict pwas_newly_created) {
	size_t bufsize = 128;
	for (;;) {
		bool ok;
		ok = openat_create_follow_symlink_dynamic_impl(f,
		                                               root,
		                                               fsmode,
		                                               pmax_remaining_links,
		                                               oflags,
		                                               mode,
		                                               sl_node,
		                                               presult_containing_path,
		                                               presult_containing_directory,
		                                               presult_containing_dirent,
		                                               presult_inode,
		                                               pwas_newly_created,
		                                               &bufsize);
		if (ok)
			break;
	}
}


/* Check if the given handle `self' refers to a directory. */
PRIVATE ATTR_PURE WUNUSED bool
NOTHROW(KCALL handle_isdirectory)(struct handle self) {
	switch (self.h_type) {

	case HANDLE_TYPE_MFILE: {
		struct inode *ino;
		if (!vm_datablock_isinode((struct vm_datablock *)self.h_data))
			break;
		ino = (struct inode *)self.h_data;
		if (INODE_ISDIR(ino))
			return true;
	}	break;

	case HANDLE_TYPE_FILE: {
		struct file *fp;
		fp = (struct file *)self.h_data;
		if (INODE_ISDIR(fp->f_node))
			return true;
	}	break;

	case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE:
	case HANDLE_TYPE_PATH:
		return true;

	default:
		break;
	}
	return false;
}



/* Back-end implementation of `sys_open()' and friends.
 * WARNING: This function does _NOT_ validate `oflags', `mode' or `fsmode'!
 *          Invalid flags are silently ignored.
 * WARNING: This function does _NOT_ fill in `return.h_mode'
 * @param: oflags: Set of `O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK |
 *                         O_DIRECTORY | O_CREAT | O_EXCL | O_NOATIME |
 *                         O_PATH   |  O_TMPFILE  |  O_SYMLINK  |  O_*'
 * @param: fsmode: Set of `0 | AT_SYMLINK_NOFOLLOW | FS_MODE_FDOSPATH |
 *                         FS_MODE_FEMPTY_PATH | FS_MODE_FSYMLINK_NOFOLLOW' */
PUBLIC WUNUSED NONNULL((1, 2, 3)) REF struct handle KCALL
fs_open_ex(struct fs *__restrict filesystem,
           struct path *cwd, struct path *root,
           USER CHECKED /*utf-8*/ char const *upath,
           oflag_t oflags, mode_t mode, fsmode_t fsmode) {
	REF struct handle result;
	if (oflags & O_PATH) {
		/* Only need to lookup the resulting path object. */
		result.h_type = HANDLE_TYPE_PATH;
		result.h_data = path_traverse_ex_recent(filesystem,
		                                        cwd,
		                                        root,
		                                        upath,
		                                        NULL,
		                                        NULL,
		                                        fsmode,
		                                        NULL);
	} else {
		REF struct inode *result_inode;
		REF struct path *result_containing_path;
		REF struct directory_node *result_containing_directory;
		REF struct directory_entry *result_containing_dirent;
		if (!(oflags & O_CREAT)) {
			/* Simple case: open an existing file. */
			result_inode = path_traversefull_ex(filesystem,
			                                    cwd,
			                                    root,
			                                    upath,
			                                    !(fsmode & AT_SYMLINK_NOFOLLOW),
			                                    fsmode,
			                                    NULL,
			                                    &result_containing_path,
			                                    &result_containing_directory,
			                                    &result_containing_dirent);
			/* Clear the file if O_TRUNC was given. */
			if ((oflags & O_TRUNC) && (oflags & O_ACCMODE) != O_RDONLY) {
				TRY {
					inode_truncate(result_inode, 0);
				} EXCEPT {
					decref(result_inode);
					decref(result_containing_path);
					decref(result_containing_directory);
					decref(result_containing_dirent);
					RETHROW();
				}
			}
		} else {
			/* (Potentially) create a new file. */
			char const *last_seg;
			u16 last_seglen;
			u32 max_remaining_links = ATOMIC_READ(filesystem->f_lnkmax);
			/* Properly fill in `O_DOSPATH' */
			oflags &= ~O_DOSPATH;
#if FS_MODE_FDOSPATH == O_DOSPATH
			oflags |= (fsmode & FS_MODE_FDOSPATH);
#else /* FS_MODE_FDOSPATH == O_DOSPATH */
			if (fsmode & FS_MODE_FDOSPATH)
				oflags |= O_DOSPATH;
#endif /* FS_MODE_FDOSPATH != O_DOSPATH */
			result_containing_path = path_traverse_ex(filesystem,
			                                          cwd,
			                                          root,
			                                          upath,
			                                          &last_seg,
			                                          &last_seglen,
			                                          fsmode,
			                                          &max_remaining_links);
			TRY {
				sync_read(result_containing_path);
				result_containing_directory = (REF struct directory_node *)incref(result_containing_path->p_inode);
				sync_endread(result_containing_path);
				TRY {
					bool was_newly_created;
					/* Create/open an existing INode within the associated directory. */
					/* TODO: Permission checks */
					result_inode = directory_creatfile(result_containing_directory,
					                                   last_seg,
					                                   last_seglen,
					                                   oflags & (O_CREAT | /*O_EXCL|*/ O_DOSPATH),
					                                   fs_getuid(filesystem),
					                                   fs_getgid(filesystem),
					                                   mode,
					                                   &result_containing_dirent,
					                                   &was_newly_created);
					TRY {
check_result_inode_for_symlink:
						if (INODE_ISLNK(result_inode) && !(fsmode & AT_SYMLINK_NOFOLLOW) &&
						    !(result_inode->i_flags & INODE_FLNK_DONT_FOLLOW_FINAL_LINK)) {
							/* No  new file was created, and the accessed file turned out to be a symbolic
							 * link. - In this case,  we must continue following  that file's link for  at
							 * most `max_remaining_links' additional links and open/create the file at its
							 * target location. */
							struct symlink_node *sl_node;
							sl_node = (struct symlink_node *)result_inode;

							if (symlink_node_load(sl_node)) {
								REF struct inode *new_result_inode;
								REF struct path *new_result_containing_path;
								REF struct directory_node *new_result_containing_directory;
								REF struct directory_entry *new_result_containing_dirent;
								/* Traverse the symlink text. */
								new_result_containing_path = path_traversen_ex(filesystem,
								                                               result_containing_path,
								                                               root,
								                                               sl_node->sl_text,
								                                               (size_t)sl_node->i_filesize,
								                                               &last_seg,
								                                               &last_seglen,
								                                               fsmode,
								                                               &max_remaining_links);
								decref(result_containing_path);
								result_containing_path = new_result_containing_path;

								sync_read(result_containing_path);
								new_result_containing_directory = (REF struct directory_node *)
								incref(result_containing_path->p_inode);
								sync_endread(result_containing_path);
								decref(result_containing_directory);
								result_containing_directory = new_result_containing_directory;

								/* Repeat the create() function with the symlink's dereferenced text. */
								/* TODO: Permission checks */
								new_result_inode = directory_creatfile(result_containing_directory,
								                                       last_seg,
								                                       last_seglen,
								                                       oflags & (O_CREAT | /*O_EXCL|*/ O_DOSPATH),
								                                       fs_getuid(filesystem),
								                                       fs_getgid(filesystem),
								                                       mode,
								                                       &new_result_containing_dirent,
								                                       &was_newly_created);
								decref(result_containing_dirent);
								result_containing_dirent = new_result_containing_dirent;
								decref(result_inode);
								result_inode = new_result_inode;
							} else {
								/* Use the dynamic interface! */
								openat_create_follow_symlink_dynamic(filesystem,
								                                     root,
								                                     fsmode,
								                                     &max_remaining_links,
								                                     oflags,
								                                     mode,
								                                     sl_node,
								                                     &result_containing_path,
								                                     &result_containing_directory,
								                                     &result_containing_dirent,
								                                     &result_inode,
								                                     &was_newly_created);
							}
							goto check_result_inode_for_symlink;
						}
						if (!was_newly_created) {
							/* If the O_EXCL flag was given, make sure that the file was newly created.
							 * Otherwise, throw an exception.
							 * NOTE: Even though `directory_creatfile()' has builtin support for this  type
							 *       of check when passed the O_EXCL flag, we don't use that functionality,
							 *       as it wouldn't allow for  the special handling of  SMYLINK+!O_NOFOLLOW
							 *       which we do above (which allows open() to create/open files pointed to
							 *       by symbolic links directly) */
							if (oflags & O_EXCL)
								THROW(E_FSERROR_FILE_ALREADY_EXISTS);
							/* Clear the file if O_TRUNC was given. */
							if ((oflags & O_TRUNC) &&
							    (oflags & O_ACCMODE) != O_RDONLY &&
							    INODE_ISREG(result_inode))
								inode_truncate(result_inode, 0);
						}
					} EXCEPT {
						decref(result_containing_dirent);
						decref(result_inode);
						RETHROW();
					}
				} EXCEPT {
					decref(result_containing_directory);
					RETHROW();
				}
			} EXCEPT {
				decref(result_containing_path);
				RETHROW();
			}
		}
		TRY {
			if (INODE_ISLNK(result_inode)) {
				/* Special handling: If the caller was requesting  access to the symlink  itself,
				 *                   then we must  bypass any custom  open protocol and  directly
				 *                   open the pointed-to  symbolic link. This  is similar to  how
				 *                   the O_PATH flag also bypasses a majority of path processing,
				 *                   any simply always returns a `HANDLE_TYPE_PATH' object. */
				if (oflags & O_SYMLINK)
					goto open_result_inode;
				/* The resulting INode is a symbolic link.
				 * -> This is where KOS's `O_SYMLINK' extension comes into play:
				 *   - When `O_SYMLINK' is given, then the symbolic link is opened
				 *     as a regular file.
				 *   - When `O_SYMLINK' isn't given, throw an `E_FSERROR_IS_A_SYMBOLIC_LINK'
				 *     exception   with   `E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN'    context. */
				if (!(result_inode->i_flags & INODE_FLNK_DONT_FOLLOW_FINAL_LINK)) {
					THROW(E_FSERROR_IS_A_SYMBOLIC_LINK,
					      E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN);
				} else {
					/* One last  special case:  When access  was made  to a  symbolic link  with
					 * the  `INODE_FLNK_DONT_FOLLOW_FINAL_LINK'  flag set,  but the  caller also
					 * specified the NOFOLLOW flag (i.e. symbolic links should not be followed),
					 * the we mustn't allow the  link to be opened  (which would likely be  done
					 * through  use  of `result_inode->i_type->it_attr.a_open'),  as  doing this
					 * would also  mean that  the link  would have  been ~followed~  in one  way
					 * or another. */
					if (fsmode & AT_SYMLINK_NOFOLLOW)
						THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS);
				}
			} else {
				/* Special case: O_SYMLINK | O_EXCL must cause  an exception if the  named
				 *               file ended up being something other than a symbolic link! */
				if ((oflags & (O_CREAT | O_SYMLINK | O_EXCL)) == (O_SYMLINK | O_EXCL))
					THROW(E_FSERROR_NOT_A_SYMBOLIC_LINK,
					      E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN);
			}
			if (result_inode->i_type->it_attr.a_open) {
				/* Invoke a custom open-file callback. */
				result = (*result_inode->i_type->it_attr.a_open)(result_inode,
				                                                 oflags,
				                                                 result_containing_path,
				                                                 result_containing_directory,
				                                                 result_containing_dirent);
				/* Implement support for the `O_DIRECTORY' flag by throwing
				 * an  error  if  the  accessed  file  isn't  a  directory. */
				if ((oflags & O_DIRECTORY) && !handle_isdirectory(result)) {
					decref(result);
					THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_OPEN);
				}
				/* Assign a controlling terminal to the calling process. */
				if (!(oflags & O_NOCTTY) &&
				    result.h_type == HANDLE_TYPE_CHARACTERDEVICE &&
				    character_device_isattybase((struct character_device *)result.h_data) &&
				    awref_ptr(&((struct ttybase_device *)result.h_data)->t_cproc) == NULL) {
					/* NOTE: `ttybase_device_setctty()' is NOTHROW(), so no need to guard this call! */
					ttybase_device_setctty((struct ttybase_device *)result.h_data);
				}
				decref(result_inode);
				decref(result_containing_path);
				decref(result_containing_directory);
				decref(result_containing_dirent);
			} else {
				/* Implement support for the `O_DIRECTORY' flag by throwing
				 * an  error  if  the  accessed  file  isn't  a  directory. */
				if (!INODE_ISDIR(result_inode) && (oflags & O_DIRECTORY))
					THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_OPEN);

				/* Create a file handle from all of the gathered object pointers. */
				switch (result_inode->i_filemode & S_IFMT) {

					STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_refcnt) == offsetof(struct file, f_refcnt));
					STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_node) == offsetof(struct file, f_node));
					STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_path) == offsetof(struct file, f_path));
					STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_dirent) == offsetof(struct file, f_dirent));
					STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_offset) == offsetof(struct file, f_offset));

				case S_IFBLK: {
					/* Open the associated block-device. */
					dev_t devno;
					inode_loadattr(result_inode);
					COMPILER_READ_BARRIER();
					devno = result_inode->i_filerdev;
					COMPILER_READ_BARRIER();
					result.h_data = block_device_lookup(devno);
					if unlikely(!result.h_data)
						THROW(E_NO_DEVICE, E_NO_DEVICE_KIND_BLOCK_DEVICE, devno);
					result.h_type = HANDLE_TYPE_BLOCKDEVICE;
					decref(result_inode);
					decref(result_containing_path);
					decref(result_containing_directory);
					decref(result_containing_dirent);
				}	break;

				case S_IFCHR: {
					/* Open the associated character-device. */
					dev_t devno;
					REF struct character_device *cdev;
					inode_loadattr(result_inode);
					COMPILER_READ_BARRIER();
					devno = result_inode->i_filerdev;
					COMPILER_READ_BARRIER();
					cdev = character_device_lookup(devno);
					if unlikely(!cdev)
						THROW(E_NO_DEVICE, E_NO_DEVICE_KIND_CHARACTER_DEVICE, devno);
					result.h_data = cdev; /* Inherit reference. */
					result.h_type = HANDLE_TYPE_CHARACTERDEVICE;
					/* Allow custom callbacks during open(2) */
					if unlikely(cdev->cd_type.ct_open) {
						/* Keep an additional reference around during the callbacks
						 * This is to ensure that the device doesn't get  destroyed
						 * from within one of its  own callbacks in the event  that
						 * the callback chooses to replace the handle data pointer. */
						incref(cdev);
						FINALLY_DECREF_UNLIKELY(cdev);
						(*cdev->cd_type.ct_open)(cdev, &result);
					}
					/* Assign a controlling terminal to the calling process. */
					if (!(oflags & O_NOCTTY) && character_device_isattybase(cdev) &&
					    awref_ptr(&((struct ttybase_device *)cdev)->t_cproc) == NULL) {
						/* NOTE: `ttybase_device_setctty()' is NOTHROW(), so no need to guard this call! */
						ttybase_device_setctty((struct ttybase_device *)cdev);
					}
					decref(result_inode);
					decref(result_containing_path);
					decref(result_containing_directory);
					decref(result_containing_dirent);
				}	break;

				case S_IFIFO: {
					struct fifo_node *fn;
					REF struct fifo_user *user;
					STATIC_ASSERT(IO_ACCMODE == O_ACCMODE);
					STATIC_ASSERT(IO_NONBLOCK == O_NONBLOCK);
					fn   = (struct fifo_node *)result_inode;
					user = fifo_user_create(fn, (iomode_t)(oflags & (O_ACCMODE | O_NONBLOCK)));
					user->fu_path   = result_containing_path;   /* Inherit reference */
					user->fu_dirent = result_containing_dirent; /* Inherit reference */
					COMPILER_WRITE_BARRIER();
					result.h_type = HANDLE_TYPE_FIFO_USER;
					result.h_data = user;
					decref_unlikely(result_containing_directory);
					decref_nokill(result_inode); /* Nokill, because one ref exists in `user->fu_fifo' */
				}	break;

				//TODO:Unix domain sockets:case S_IFSOCK:
				//TODO:Unix domain sockets:    Read up on what kind of object this should return.
				//TODO:Unix domain sockets:    Possibly add a `HANDLE_TYPE_*' specifically for this.

				case S_IFLNK:
					/* Symbolic  */
open_result_inode:
					result.h_data = result_inode;
					result.h_type = HANDLE_TYPE_MFILE;
					decref(result_inode);
					decref(result_containing_path);
					decref(result_containing_directory);
					decref(result_containing_dirent);
					break;

				case S_IFDIR:
					if (!result_inode->i_type->it_directory.d_readdir) {
						REF struct oneshot_directory_file *result_file;
						/* Need to return a one-shot-directory-file object. */
						result_file = (REF struct oneshot_directory_file *)kmalloc(sizeof(REF struct oneshot_directory_file),
						                                                           GFP_PREFLT);
						result_file->d_refcnt = 1;
						result_file->d_node   = (REF struct directory_node *)result_inode; /* Inherit reference */
						result_file->d_path   = result_containing_path;                    /* Inherit reference */
						result_file->d_dirent = result_containing_dirent;                  /* Inherit reference */
						atomic64_init(&result_file->d_offset, 0);
						atomic_rwlock_init(&result_file->d_curlck);
						result_file->d_curidx = 0;
						result_file->d_curent = NULL;
						result_file->d_curbuf = NULL;
						result_file->d_buf    = NULL;
						result.h_type  = HANDLE_TYPE_ONESHOT_DIRECTORY_FILE;
						result.h_data  = result_file;
						decref_unlikely(result_containing_directory);
						break;
					}
					ATTR_FALLTHROUGH
				default: {
					REF struct file *result_file;
					/* Simply need to return a regular file object for the given INode. */
					result_file           = (REF struct file *)kmalloc(sizeof(REF struct file), GFP_PREFLT);
					result_file->f_refcnt = 1;
					result_file->f_node   = result_inode;                /* Inherit reference */
					result_file->f_path   = result_containing_path;      /* Inherit reference */
					result_file->f_dirent = result_containing_dirent;    /* Inherit reference */
					atomic64_init(&result_file->f_offset, 0);
					atomic_rwlock_init(&result_file->f_curlck);
					result_file->f_curidx = 0;
					result_file->f_curent = NULL;
					result.h_type  = HANDLE_TYPE_FILE;
					result.h_data  = result_file;
					decref_unlikely(result_containing_directory);
				}	break;

				}
			}
		} EXCEPT {
			decref(result_inode);
			decref(result_containing_path);
			decref(result_containing_directory);
			decref(result_containing_dirent);
			RETHROW();
		}
	}
	return result;
}



/* A somplified wrapper for `fs_open_ex()'
 * WARNING: This function does _NOT_ validate `oflags' or `fsmode'!
 *          Invalid flags are silently ignored.
 * WARNING: This function does _NOT_ fill in `return.h_mode'
 * @param: oflags: Set of `O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK |
 *                         O_DIRECTORY | O_CREAT | O_EXCL | O_NOATIME |
 *                         O_PATH | O_TMPFILE | O_SYMLINK | O_DOSPATH |
 *                         O_NOFOLLOW | O_*' */
PUBLIC WUNUSED NONNULL((1)) REF struct handle KCALL
fs_open(struct fs *__restrict filesystem, unsigned int dirfd,
        USER CHECKED /*utf-8*/ char const *upath,
        oflag_t oflags, mode_t mode) {
	REF struct path *root, *cwd;
	REF struct handle result;
	fsmode_t fsmode;
	/* Figure out how we want to access the filesystem. */
	fsmode = (fsmode_t)0;
	if (oflags & (O_NOFOLLOW | O_SYMLINK))
		fsmode |= (fsmode_t)AT_SYMLINK_NOFOLLOW;
	if (oflags & O_DOSPATH)
		fsmode |= (fsmode_t)AT_DOSPATH;
	fsmode = fs_getmode_for(filesystem, (atflag_t)fsmode);
	/* Load base directory paths. */
	sync_read(&filesystem->f_pathlock);
	root = incref(filesystem->f_root);
	if (dirfd == HANDLE_SYMBOLIC_FDCWD) {
		cwd = incref(filesystem->f_cwd);
		sync_endread(&filesystem->f_pathlock);
	} else if (dirfd == HANDLE_SYMBOLIC_FDROOT) {
		cwd = incref(root);
		sync_endread(&filesystem->f_pathlock);
	} else {
		sync_endread(&filesystem->f_pathlock);
		TRY {
			cwd = handle_get_path(dirfd);
		} EXCEPT {
			decref(root);
			RETHROW();
		}
	}
	FINALLY_DECREF_UNLIKELY(root);
	FINALLY_DECREF_UNLIKELY(cwd);
	/* Forward to the extended open call */
	result = fs_open_ex(filesystem,
	                    cwd,
	                    root,
	                    upath,
	                    oflags,
	                    mode,
	                    fsmode);
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_VFS_OPEN_C */
