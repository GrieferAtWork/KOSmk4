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
#ifdef __INTELLISENSE__
#include "vfs-traverse.c"
//#define TRAVERSE_N 1
#endif /* __INTELLISENSE__ */

#include <kernel/handle.h>

#include <hybrid/atomic.h>

#include <kos/kernel/handle.h>

DECL_BEGIN

/* Traverse a relative path, starting at `cwd' and walking until the
 * requested path was found, or until a missing path segment was encountered.
 * This function will automatically deal with `.' and `..' segments, always
 * accepting `/' between directories, and `\\' when `FS_MODE_FDOSPATH' is set.
 * Additionally, symbolic links are followed, with the final path segment stored
 * in the provided output arguments, with `*plastlen' set to 0 when the final
 * segment was empty and `FS_MODE_FIGNORE_TRAILING_SLASHES' wasn't set, or
 * when the entire input path is empty and `FS_MODE_FEMPTY_PATH' was set, or
 * if the last segment of the input path was one of `.' or `..', or if the
 * input path referred to the root path, or a drive root (`/' or `C:')
 * Additionally, when `plastseg' itself is `NULL', always walk the entire path.
 *     INPUT      |  RETURN  |  LASTSEG
 *    ------------+----------+------------
 *     ""         |  "."     |  ""         (Throws `E_FSERROR_ILLEGAL_PATH' unless `FS_MODE_FEMPTY_PATH' is set)
 *     "/"        |  "/"     |  ""
 *     "C:"       |  "C:"    |  ""
 *     ".."       |  "./.."  |  ""
 *     "."        |  "."     |  ""
 *     "foo"      |  "."     |  "foo"
 *     "foo/bar"  |  "./foo" |  "bar"
 *     "/foo"     |  "/"     |  "foo"
 *    ------------+----------+------------
 *
 * @param: mode: Set of `FS_MODE_FDOSPATH | FS_MODE_FIGNORE_TRAILING_SLASHES |
 *                       FS_MODE_FEMPTY_PATH | FS_MODE_FSYMLINK_NOFOLLOW'
 *               NOTE: `FS_MODE_FSYMLINK_NOFOLLOW' only has an effect when no last-seg pointers
 *                      were given, in which case the last segment being a symlink will cause an
 *                     `E_FSERROR_TOO_MANY_SYMBOLIC_LINKS' exception to be thrown.
 * @param: premaining_symlinks: [in|out] When non-NULL, load/store the amount of remaining
 *                              symbolic link indirection which the path may have still
 *                              traversed during evaluation (aka.: the limit on how many
 *                              symbolic links may still be traversed during further path
 *                              walks)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH:
 *                                            One of the accessed directory INodes had been deleted.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED:
 *                                            One of the accessed directory INodes had been unmounted.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                                            Failed to read entries from one of the traversed directories.
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_WALK:
 *                                            Attempted to traverse something other than a directory, or symbolic link
 * @throw: E_FSERROR_PATH_NOT_FOUND:          An addressed path could not be found.
 * @throw: E_FSERROR_ILLEGAL_PATH:            The final path segment is longer than `0xffff'
 * @throw: E_SEGFAULT:                        Failed to access the given `upath'
 * @throw: E_FSERROR_ACCESS_DENIED:           Attempted to traverse a directory without privilege.
 * @throw: E_FSERROR_TOO_MANY_SYMBOLIC_LINKS: Too many symbolic links were encountered.
 * @throw: E_IOERROR:                         [...] */
#ifdef TRAVERSE_N
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
path_traversen_ex(struct fs *__restrict filesystem,
                  struct path *cwd,
                  struct path *root,
                  USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                  USER CHECKED /*utf-8*/ char const **plastseg,
                  u16 *plastlen, fsmode_t mode,
                  u32 *premaining_symlinks)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, ...)
#else /* TRAVERSE_N */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct path *KCALL
path_traverse_ex(struct fs *__restrict filesystem,
                 struct path *cwd,
                 struct path *root,
                 USER CHECKED /*utf-8*/ char const *upath,
                 USER CHECKED /*utf-8*/ char const **plastseg,
                 u16 *plastlen, fsmode_t mode,
                 u32 *premaining_symlinks)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, ...)
#endif /* !TRAVERSE_N */
{
	char32_t ch;
	u32 remaining_links;
#ifdef TRAVERSE_N
	char const *path_end;
#endif /* TRAVERSE_N */
	char const *segment_start = upath;
	char const *segment_end;
	struct vfs *v   = filesystem->f_vfs;
	remaining_links = premaining_symlinks
	                  ? *premaining_symlinks
	                  : ATOMIC_READ(filesystem->f_lnkmax);
#ifdef TRAVERSE_N
	path_end = upath + max_pathlen;
	if unlikely(path_end < upath)
		path_end = (char *)(uintptr_t)-1;
#define READCH() unicode_readutf8_n(&upath, path_end)
#else /* TRAVERSE_N */
#define READCH() unicode_readutf8(&upath)
#endif /* !TRAVERSE_N */
	/* Deal with leading slashes. */
	ch = READCH();
	if unlikely(!ch) {
		/* Empty path. */
		if (mode & FS_MODE_FEMPTY_PATH) {
return_cwd:
			if (plastlen)
				*plastlen = 0;
			if (premaining_symlinks)
				*premaining_symlinks = remaining_links;
			return incref(cwd);
		}
		THROW(E_FSERROR_ILLEGAL_PATH);
	}
	if (mode & FS_MODE_FDOSPATH) {
		if (ch == '/' || ch == '\\') {
			/* Start at the root of the current drive. */
			while (cwd != root && cwd->p_parent &&
			       ATOMIC_READ(cwd->p_isdrive) == 0)
				cwd = cwd->p_parent;
			/* XXX: `\\samba\share' */
			do {
				segment_start = upath;
				ch            = READCH();
			} while (ch == '/' || ch == '\\');
			if (!ch) /* Reference to the drive root. */
				goto return_cwd;
			incref(cwd);
		} else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
			/* Load the next character to check if this is referencing a drive name. */
			char32_t next_ch;
			next_ch = READCH();
			if (next_ch == ':') {
				if (ch >= 'a' && ch <= 'z')
					ch -= 'a' - 'A';
				ch -= 'A';
				sync_read(&v->v_drives_lock);
				cwd = v->v_drives[ch];
				if unlikely(!cwd) {
					sync_endread(&v->v_drives_lock);
					THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DRIVE);
				}
				incref(cwd);
				sync_endread(&v->v_drives_lock);
				TRY {
					do {
						segment_start = upath;
						ch            = READCH();
					}  while (ch == '/' || ch == '\\');
				} EXCEPT {
					decref(cwd);
					RETHROW();
				}
			} else {
				incref(cwd);
				if (!ch)
					goto dos_at_segment_end;
				if (ch == '/' || ch == '\\')
					goto dos_at_segment_seperator;
			}
		} else {
			incref(cwd);
		}
		for (;;) {
			segment_end = upath;
			TRY {
				ch = READCH();
			} EXCEPT {
				decref(cwd);
				RETHROW();
			}
			if (ch == '/' || ch == '\\') {
				u16 segment_length;
				char const *next_segment_start;
				REF struct path *next_path;
dos_at_segment_seperator:
				/* Load the child segment. */
				if ((size_t)(segment_end - segment_start) > 0xffff)
					THROW(E_FSERROR_ILLEGAL_PATH);
				next_segment_start = upath;
				if (ch) {
					TRY {
						do {
							next_segment_start = upath;
							ch                 = READCH();
						} while (ch == '/' || ch == '\\');
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					if (!ch && (mode & FS_MODE_FIGNORE_TRAILING_SLASHES))
						goto dos_at_segment_end;
				}
				segment_length = (u16)(segment_end - segment_start);
				switch (segment_length) {

				case 0:
					if (!(mode & FS_MODE_FEMPTY_PATH))
						THROW(E_FSERROR_ILLEGAL_PATH);
					break;

				case 2:
					TRY {
						if (segment_start[0] != '.')
							goto dos_generic_directory_child;
						if (segment_start[1] != '.')
							goto dos_generic_directory_child;
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					/* Parent directory reference. */
					next_path = cwd->p_parent;
					if (cwd == root || !next_path)
						next_path = cwd;
					incref(next_path);
					goto dos_set_next_path;

				case 1:
					TRY {
						if (segment_start[0] == '.')
							break; /* Current directory reference. */
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					ATTR_FALLTHROUGH
				default:
dos_generic_directory_child:
					TRY {
						next_path = path_walkcasechild(cwd,
						                               root,
						                               segment_start,
						                               segment_length,
						                               &remaining_links);
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
dos_set_next_path:
					decref(cwd);
					cwd = next_path;
					break;
				}
				if (!ch) {
					if (plastlen)
						*plastlen = 0;
					break;
				}
				segment_start = next_segment_start;
				continue;
			}
			if (!ch) {
dos_at_segment_end:
				if (!plastlen) {
					if (mode & FS_MODE_FSYMLINK_NOFOLLOW)
						remaining_links = 0; /* Don't allow any further symlinks */
					goto dos_at_segment_seperator;
				}
				goto common_at_segment_end;
			}
		}
	} else {
		if (ch == '/') {
			/* Start at the root directory. */
			cwd = root;
			do {
				segment_start = upath;
				ch            = READCH();
			} while (ch == '/');
			if (!ch) /* Reference to the filesystem root. */
				goto return_cwd;
		}
		incref(cwd);
		for (;;) {
			segment_end = upath;
			TRY {
				ch = READCH();
			} EXCEPT {
				decref(cwd);
				RETHROW();
			}
			if (ch == '/') {
				u16 segment_length;
				char const *next_segment_start;
				REF struct path *next_path;
at_segment_seperator:
				/* Load the child segment. */
				if ((size_t)(segment_end - segment_start) > 0xffff)
					THROW(E_FSERROR_ILLEGAL_PATH);
				next_segment_start = upath;
				if (ch) {
					TRY {
						do {
							next_segment_start = upath;
							ch                 = READCH();
						} while (ch == '/');
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					if (!ch && (mode & FS_MODE_FIGNORE_TRAILING_SLASHES))
						goto at_segment_end;
				}
				segment_length = (u16)(segment_end - segment_start);
				switch (segment_length) {

				case 0:
					if (!(mode & FS_MODE_FEMPTY_PATH))
						THROW(E_FSERROR_ILLEGAL_PATH);
					break;

				case 2:
					TRY {
						if (segment_start[0] != '.')
							goto generic_directory_child;
						if (segment_start[1] != '.')
							goto generic_directory_child;
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					/* Parent directory reference. */
					next_path = cwd->p_parent;
					if (cwd == root || !next_path)
						next_path = cwd;
					incref(next_path);
					goto set_next_path;

				case 1:
					TRY {
						if (segment_start[0] == '.')
							break; /* Current directory reference. */
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					ATTR_FALLTHROUGH
				default:
generic_directory_child:
					TRY {
						next_path = path_walkchild(cwd,
						                           root,
						                           segment_start,
						                           segment_length,
						                           &remaining_links);
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
set_next_path:
					decref(cwd);
					cwd = next_path;
					break;
				}
				if (!ch) {
					if (plastlen)
						*plastlen = 0;
					break;
				}
				segment_start = next_segment_start;
				continue;
			}
			if (!ch) {
				u16 segment_length;
at_segment_end:
				if (!plastlen) {
					if (mode & FS_MODE_FSYMLINK_NOFOLLOW)
						remaining_links = 0; /* Don't allow any further symlinks */
					goto at_segment_seperator;
				}
common_at_segment_end:
				if ((size_t)(segment_end - segment_start) > 0xffff)
					THROW(E_FSERROR_ILLEGAL_PATH);
				segment_length = (u16)(segment_end - segment_start);
				assert(segment_length != 0);
				/* Check for special case: The path ends with a trailing `.' or `..' */
				switch (segment_length) {

				case 1:
					TRY {
						if (segment_start[0] != '.')
							break;
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					/* Current directory */
					*plastlen = 0;
					goto done;

				case 2:
					TRY {
						if (segment_start[0] != '.')
							break;
						if (segment_start[1] != '.')
							break;
					} EXCEPT {
						decref(cwd);
						RETHROW();
					}
					/* Parent directory */
					*plastlen = 0;
					/* Parent directory reference. */
					{
						REF struct path *next_path;
						next_path = cwd->p_parent;
						if (cwd == root || !next_path)
							next_path = cwd;
						incref(next_path);
						decref(cwd);
						cwd = next_path;
					}
					goto done;

				default:
					break;
				}
				*plastlen = segment_length;
				*plastseg = segment_start;
				goto done;
			}
		}
	}
done:
	if (premaining_symlinks)
		*premaining_symlinks = remaining_links;
	return cwd;
#undef READCH
}


#ifdef TRAVERSE_N
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traversen(struct fs *__restrict filesystem,
               USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
               USER CHECKED /*utf-8*/ char const **plastseg,
               u16 *plastlen, fsmode_t mode,
               u32 *premaining_symlinks)
#else /* TRAVERSE_N */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct path *KCALL
path_traverse(struct fs *__restrict filesystem,
              USER CHECKED /*utf-8*/ char const *upath,
              USER CHECKED /*utf-8*/ char const **plastseg,
              u16 *plastlen, fsmode_t mode,
              u32 *premaining_symlinks)
#endif /* !TRAVERSE_N */
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...) {
	REF struct path *result, *root, *cwd;
	sync_read(&filesystem->f_pathlock);
	root = incref(filesystem->f_root);
	cwd  = incref(filesystem->f_cwd);
	sync_endread(&filesystem->f_pathlock);
	TRY {
#ifdef TRAVERSE_N
		result = path_traversen_ex(filesystem,
		                           cwd,
		                           root,
		                           upath,
		                           max_pathlen,
		                           plastseg,
		                           plastlen,
		                           mode,
		                           premaining_symlinks);
#else /* TRAVERSE_N */
		result = path_traverse_ex(filesystem,
		                          cwd,
		                          root,
		                          upath,
		                          plastseg,
		                          plastlen,
		                          mode,
		                          premaining_symlinks);
#endif /* !TRAVERSE_N */
	} EXCEPT {
		decref(cwd);
		decref(root);
		RETHROW();
	}
	decref(cwd);
	decref(root);
	return result;
}



#ifdef TRAVERSE_N
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *KCALL
path_traversen_at(struct fs *__restrict filesystem, unsigned int dirfd,
                  USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                  USER CHECKED /*utf-8*/ char const **plastseg,
                  u16 *plastlen, fsmode_t mode, u32 *premaining_symlinks)
#else /* TRAVERSE_N */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct path *KCALL
path_traverse_at(struct fs *__restrict filesystem, unsigned int dirfd,
                 USER CHECKED /*utf-8*/ char const *upath,
                 USER CHECKED /*utf-8*/ char const **plastseg,
                 u16 *plastlen, fsmode_t mode, u32 *premaining_symlinks)
#endif /* !TRAVERSE_N */
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...) {
	REF struct path *result, *root, *cwd;
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
	TRY {
#ifdef TRAVERSE_N
		result = path_traversen_ex(filesystem,
		                           cwd,
		                           root,
		                           upath,
		                           max_pathlen,
		                           plastseg,
		                           plastlen,
		                           mode,
		                           premaining_symlinks);
#else /* TRAVERSE_N */
		result = path_traverse_ex(filesystem,
		                          cwd,
		                          root,
		                          upath,
		                          plastseg,
		                          plastlen,
		                          mode,
		                          premaining_symlinks);
#endif /* !TRAVERSE_N */
	} EXCEPT {
		decref(cwd);
		decref(root);
		RETHROW();
	}
	decref(cwd);
	decref(root);
	return result;
}



/* Traverse the entirety of a given `upath', returning the point-to node,
 * as well as optionally related components. */
#ifdef TRAVERSE_N
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct inode *KCALL
path_traversenfull_ex(struct fs *__restrict filesystem,
                      struct path *cwd,
                      struct path *root,
                      USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                      bool follow_final_link, fsmode_t mode,
                      u32 *premaining_symlinks,
                      REF struct path **pcontaining_path,
                      REF struct directory_node **pcontaining_directory,
                      REF struct directory_entry **pcontaining_dirent)
#else /* TRAVERSE_N */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) REF struct inode *KCALL
path_traversefull_ex(struct fs *__restrict filesystem,
                     struct path *cwd,
                     struct path *root,
                     USER CHECKED /*utf-8*/ char const *upath,
                     bool follow_final_link, fsmode_t mode,
                     u32 *premaining_symlinks,
                     REF struct path **pcontaining_path,
                     REF struct directory_node **pcontaining_directory,
                     REF struct directory_entry **pcontaining_dirent)
#endif /* !TRAVERSE_N */
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...) {
	char const *last_seg;
	u16 last_seglen;
	REF struct path *containing_path;
	u32 remaining_symlinks;
	REF struct inode *result;
	REF struct directory_node *containing_directory;
	remaining_symlinks = premaining_symlinks
	                     ? *premaining_symlinks
	                     : ATOMIC_READ(filesystem->f_lnkmax);
#ifdef TRAVERSE_N
	containing_path = path_traversen_ex_recent(filesystem,
	                                           cwd,
	                                           root,
	                                           upath,
	                                           max_pathlen,
	                                           &last_seg,
	                                           &last_seglen,
	                                           mode,
	                                           &remaining_symlinks);
#else /* TRAVERSE_N */
	containing_path = path_traverse_ex_recent(filesystem,
	                                          cwd,
	                                          root,
	                                          upath,
	                                          &last_seg,
	                                          &last_seglen,
	                                          mode,
	                                          &remaining_symlinks);
#endif /* !TRAVERSE_N */
	TRY {
		/* Check if the given filename refers to a path (must be done explicitly since
		 * that path may in turn refer to a mounting point which we must dereference) */
		REF struct path *result_path;
		if (!last_seglen) {
			sync_read(containing_path);
			containing_directory = (REF struct directory_node *)incref(containing_path->p_inode);
			sync_endread(containing_path);
			/* Special case: Immediate directory access. */
			result = (REF struct inode *)incref(containing_directory);
			if (pcontaining_dirent)
				*pcontaining_dirent = incref(&empty_directory_entry);
		} else {
			uintptr_t hash;
			hash = directory_entry_hash(last_seg, last_seglen);
			COMPILER_READ_BARRIER();
			result_path = mode & FS_MODE_FDOSPATH
			              ? path_getcasechild_and_parent_inode(containing_path, last_seg, last_seglen,
			                                                   hash, &containing_directory)
			              : path_getchild_and_parent_inode(containing_path, last_seg, last_seglen,
			                                               hash, &containing_directory);
			if (result_path) {
got_result_path:
				if (pcontaining_directory)
					*pcontaining_directory = containing_directory;
				else {
					decref(containing_directory);
				}
				TRY {
					sync_read(result_path);
				} EXCEPT {
					if (pcontaining_directory)
						decref(*pcontaining_directory);
					decref_unlikely(result_path);
					RETHROW();
				}
				result = (REF struct inode *)incref(result_path->p_inode);
				sync_endread(result_path);
				/* Return the containing directory if that was requested. */
				if (pcontaining_dirent)
					*pcontaining_dirent = incref(result_path->p_dirent);
				decref_unlikely(result_path);
				goto done_after_containing_directory;
			}
			TRY {
				result = mode & FS_MODE_FDOSPATH
				         ? directory_getcasenode(containing_directory, last_seg, last_seglen, hash, pcontaining_dirent)
				         : directory_getnode(containing_directory, last_seg, last_seglen, hash, pcontaining_dirent);
				if unlikely(!result)
					THROW(E_FSERROR_FILE_NOT_FOUND);
				if (follow_final_link && INODE_ISLNK(result)) {
					TRY {
						REF struct inode *new_result;
						struct symlink_node *sl_node;
						/* Follow this INode. */
again_follow_symlink:
						sl_node = (struct symlink_node *)result;
						if (symlink_node_load(sl_node)) {
							REF struct directory_node *new_containing_directory;
							REF struct path *new_containing_path;
							uintptr_t symlink_hash;
							new_containing_path = path_traverse_ex_recent(filesystem,
							                                              containing_path,
							                                              root,
							                                              sl_node->sl_text,
							                                              &last_seg,
							                                              &last_seglen,
							                                              mode,
							                                              &remaining_symlinks);
							decref(containing_path);
							containing_path = new_containing_path;
							symlink_hash = directory_entry_hash(last_seg, last_seglen);
							COMPILER_READ_BARRIER();
							/* Check for mounting points & cached paths. */
							result_path = mode & FS_MODE_FDOSPATH
							              ? path_getcasechild_and_parent_inode(containing_path, last_seg, last_seglen,
							                                                   symlink_hash, &new_containing_directory)
							              : path_getchild_and_parent_inode(containing_path, last_seg, last_seglen,
							                                               symlink_hash, &new_containing_directory);
							if (result_path) {
								decref(containing_directory);
								containing_directory = new_containing_directory;
								goto got_result_path;
							}
							TRY {
								if (pcontaining_dirent) {
									decref(*pcontaining_dirent);
									*pcontaining_dirent = NULL;
								}
								/* Lookup the last path segment within the associated directory. */
								new_result = mode & FS_MODE_FDOSPATH
								             ? directory_getcasenode(new_containing_directory, last_seg,
								                                     last_seglen, symlink_hash,
								                                     pcontaining_dirent)
								             : directory_getnode(new_containing_directory, last_seg,
								                                 last_seglen, symlink_hash,
								                                 pcontaining_dirent);
								if unlikely(!new_result)
									THROW(E_FSERROR_FILE_NOT_FOUND);
							} EXCEPT {
								decref(new_containing_directory);
								RETHROW();
							}
							decref(containing_directory);
							containing_directory = new_containing_directory;
						} else {
							/* Use the dynamic interface! */
							unsigned int follow_mode;
							REF struct directory_node *new_containing_directory;
							follow_mode = path_follow_symlink_dynamic(filesystem,
							                                          &containing_path,
							                                          root,
							                                          sl_node,
							                                          mode,
							                                          premaining_symlinks,
							                                          pcontaining_dirent,
							                                          &new_containing_directory,
							                                          &result_path,
							                                          &new_result);
							decref(containing_directory);
							containing_directory = new_containing_directory;
							if (follow_mode == PATH_FOLLOW_SYMLINK_DYNAMIC_GOT_RESULT_PATH)
								goto got_result_path;
						}
						decref(result);
						result = new_result;
						if (INODE_ISLNK(result))
							goto again_follow_symlink;
					} EXCEPT {
						if (pcontaining_dirent)
							xdecref(*pcontaining_dirent);
						decref(result);
						RETHROW();
					}
				}
			} EXCEPT {
				decref(containing_directory);
				RETHROW();
			}
		}
	} EXCEPT {
		decref(containing_path);
		RETHROW();
	}
	if (pcontaining_directory)
		*pcontaining_directory = containing_directory;
	else {
		decref(containing_directory);
	}
done_after_containing_directory:
	if (pcontaining_path)
		*pcontaining_path = containing_path;
	else {
		decref(containing_path);
	}
	if (premaining_symlinks)
		*premaining_symlinks = remaining_symlinks;
	return result;
}


#ifdef TRAVERSE_N
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversenfull_at(struct fs *__restrict filesystem, unsigned int dirfd,
                      USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                      bool follow_final_link, fsmode_t mode,
                      u32 *premaining_symlinks,
                      REF struct path **pcontaining_path,
                      REF struct directory_node **pcontaining_directory,
                      REF struct directory_entry **pcontaining_dirent)
#else /* TRAVERSE_N */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversefull_at(struct fs *__restrict filesystem, unsigned int dirfd,
                     USER CHECKED /*utf-8*/ char const *upath,
                     bool follow_final_link, fsmode_t mode,
                     u32 *premaining_symlinks,
                     REF struct path **pcontaining_path,
                     REF struct directory_node **pcontaining_directory,
                     REF struct directory_entry **pcontaining_dirent)
#endif /* !TRAVERSE_N */
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...) {
	REF struct path *root, *cwd;
	REF struct inode *result;
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
	TRY {
#ifdef TRAVERSE_N
		result = path_traversenfull_ex(filesystem,
		                               cwd,
		                               root,
		                               upath,
		                               max_pathlen,
		                               follow_final_link,
		                               mode,
		                               premaining_symlinks,
		                               pcontaining_path,
		                               pcontaining_directory,
		                               pcontaining_dirent);
#else /* TRAVERSE_N */
		result = path_traversefull_ex(filesystem,
		                              cwd,
		                              root,
		                              upath,
		                              follow_final_link,
		                              mode,
		                              premaining_symlinks,
		                              pcontaining_path,
		                              pcontaining_directory,
		                              pcontaining_dirent);
#endif /* !TRAVERSE_N */
	} EXCEPT {
		decref(cwd);
		decref(root);
		RETHROW();
	}
	decref(cwd);
	decref(root);
	return result;
}



#ifdef TRAVERSE_N
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversenfull(struct fs *__restrict filesystem,
                   USER CHECKED /*utf-8*/ char const *upath, size_t max_pathlen,
                   bool follow_final_link, fsmode_t mode,
                   u32 *premaining_symlinks,
                   REF struct path **pcontaining_path,
                   REF struct directory_node **pcontaining_directory,
                   REF struct directory_entry **pcontaining_dirent)
#else /* TRAVERSE_N */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct inode *KCALL
path_traversefull(struct fs *__restrict filesystem,
                  USER CHECKED /*utf-8*/ char const *upath,
                  bool follow_final_link, fsmode_t mode,
                  u32 *premaining_symlinks,
                  REF struct path **pcontaining_path,
                  REF struct directory_node **pcontaining_directory,
                  REF struct directory_entry **pcontaining_dirent)
#endif /* !TRAVERSE_N */
		THROWS(E_FSERROR_DELETED, E_SEGFAULT, E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_TOO_MANY_SYMBOLIC_LINKS, E_IOERROR, E_BADALLOC, E_FSERROR_PATH_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_NOT_A_DIRECTORY, ...) {
	REF struct inode *result;
	REF struct path *root, *cwd;
	sync_read(&filesystem->f_pathlock);
	root = incref(filesystem->f_root);
	cwd  = incref(filesystem->f_cwd);
	sync_endread(&filesystem->f_pathlock);
	TRY {
#ifdef TRAVERSE_N
		result = path_traversenfull_ex(filesystem,
		                               cwd,
		                               root,
		                               upath,
		                               max_pathlen,
		                               follow_final_link,
		                               mode,
		                               premaining_symlinks,
		                               pcontaining_path,
		                               pcontaining_directory,
		                               pcontaining_dirent);
#else /* TRAVERSE_N */
		result = path_traversefull_ex(filesystem,
		                              cwd,
		                              root,
		                              upath,
		                              follow_final_link,
		                              mode,
		                              premaining_symlinks,
		                              pcontaining_path,
		                              pcontaining_directory,
		                              pcontaining_dirent);
#endif /* !TRAVERSE_N */
	} EXCEPT {
		decref(cwd);
		decref(root);
		RETHROW();
	}
	decref(cwd);
	decref(root);
	return result;
}


DECL_END

#undef TRAVERSE_N
