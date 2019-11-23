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
#ifndef GUARD_KERNEL_CORE_FS_VFS_TRAVERSE_C
#define GUARD_KERNEL_CORE_FS_VFS_TRAVERSE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <assert.h>
#include <malloca.h>
#include <string.h>
#include <unicode.h>

DECL_BEGIN

PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 5)) REF struct path *KCALL
path_expandchild_symlink(struct path *cwd,
                         struct path *root,
                         char const *__restrict symlink_path,
                         size_t symlink_size,
                         u32 *__restrict premaining_links);

#define PATH_FOLLOW_SYMLINK_DYNAMIC_GOT_RESULT_PATH 0 /* `*presult_path' was filled */
#define PATH_FOLLOW_SYMLINK_DYNAMIC_GOT_NEW_RESULT  1 /* `*pnew_result' was filled */
#define PATH_FOLLOW_SYMLINK_DYNAMIC_MUST_RETRY      2 /* Only returned by `path_follow_symlink_dynamic_impl()':
                                                       *     retry (the buffer size was already updated) */

/* Follow a given dynamic symlink node */
PRIVATE ATTR_NOINLINE WUNUSED NONNULL((1, 2, 3, 4, 6, 8, 9, 10)) unsigned int KCALL
path_follow_symlink_dynamic_impl(struct fs *__restrict filesystem,
                                 /*in|out*/ struct path **__restrict pcontaining_path,
                                 struct path *root,
                                 struct symlink_node *__restrict sl_node,
                                 fsmode_t mode,
                                 u32 *__restrict premaining_symlinks,
                                 /*out*/ REF struct directory_entry **pcontaining_dirent,
                                 /*out*/ REF struct directory_node **__restrict pnew_containing_directory,
                                 /*out*/ REF struct path **__restrict presult_path,
                                 /*out*/ REF struct inode **__restrict pnew_result,
                                 size_t *__restrict pbufsize) {
	char const *last_seg;
	u16 last_seglen;
	uintptr_t hash;
	REF struct path *new_containing_path;
	size_t bufsize = *pbufsize;
	char *buf;
	buf = (char *)malloca(bufsize);
	TRY {
		size_t reqlen;
		assert(sl_node->i_type->it_symlink.sl_readlink_dynamic);
		reqlen = (*sl_node->i_type->it_symlink.sl_readlink_dynamic)(sl_node, buf, bufsize);
		if unlikely(reqlen > bufsize) {
			*pbufsize = bufsize;
			freea(buf);
			return PATH_FOLLOW_SYMLINK_DYNAMIC_MUST_RETRY;
		}
		new_containing_path = path_traversen_ex_recent(filesystem,
		                                               *pcontaining_path,
		                                               root,
		                                               buf,
		                                               reqlen,
		                                               &last_seg,
		                                               &last_seglen,
		                                               mode,
		                                               premaining_symlinks);
		decref(*pcontaining_path);
		*pcontaining_path = new_containing_path;
		hash = directory_entry_hash(last_seg, last_seglen);
		COMPILER_READ_BARRIER();
		/* Check for mounting points & cached paths. */
		*presult_path = mode & FS_MODE_FDOSPATH
		                ? path_getcasechild_and_parent_inode(*pcontaining_path, last_seg, last_seglen,
		                                                     hash, pnew_containing_directory)
		                : path_getchild_and_parent_inode(*pcontaining_path, last_seg, last_seglen,
		                                                 hash, pnew_containing_directory);
		if (*presult_path) {
			freea(buf);
			return PATH_FOLLOW_SYMLINK_DYNAMIC_GOT_RESULT_PATH;
		}
		TRY {
			if (pcontaining_dirent) {
				decref(*pcontaining_dirent);
				*pcontaining_dirent = NULL;
			}
			/* Lookup the last path segment within the associated directory. */
			*pnew_result = mode & FS_MODE_FDOSPATH
			               ? directory_getcasenode(*pnew_containing_directory, last_seg,
			                                       last_seglen, hash, pcontaining_dirent)
			               : directory_getnode(*pnew_containing_directory, last_seg,
			                                   last_seglen, hash, pcontaining_dirent);
			if unlikely(!*pnew_result)
				THROW(E_FSERROR_FILE_NOT_FOUND);
		} EXCEPT {
			decref(*pnew_containing_directory);
			RETHROW();
		}
	} EXCEPT {
		freea(buf);
		RETHROW();
	}
	freea(buf);
	return PATH_FOLLOW_SYMLINK_DYNAMIC_GOT_NEW_RESULT;
}

LOCAL WUNUSED NONNULL((1, 2, 3, 4, 6, 8, 9)) unsigned int KCALL
path_follow_symlink_dynamic(struct fs *__restrict filesystem,
                            struct path **__restrict pcontaining_path,
                            struct path *root,
                            struct symlink_node *__restrict sl_node,
                            fsmode_t mode,
                            u32 *__restrict premaining_symlinks,
                            /*out*/ REF struct directory_entry **pcontaining_dirent,
                            /*out*/ REF struct directory_node **__restrict pnew_containing_directory,
                            /*out*/ REF struct path **__restrict presult_path,
                            /*out*/ REF struct inode **__restrict pnew_result) {
	unsigned int result;
	size_t bufsize = 128;
	for (;;) {
		result = path_follow_symlink_dynamic_impl(filesystem,
		                                          pcontaining_path,
		                                          root,
		                                          sl_node,
		                                          mode,
		                                          premaining_symlinks,
		                                          pcontaining_dirent,
		                                          pnew_containing_directory,
		                                          presult_path,
		                                          pnew_result,
		                                          &bufsize);
		if likely(result != PATH_FOLLOW_SYMLINK_DYNAMIC_MUST_RETRY)
			break;
	}
	return result;
}



/* Returns `NULL' if the stack-allocated name buffer was too small. */
PRIVATE ATTR_NOINLINE REF struct path *KCALL
path_expand_dynamic_symlink(struct path *parent_path,
                            struct path *root_path,
                            struct symlink_node *__restrict node,
                            u32 *__restrict premaining_links,
                            size_t *__restrict required_bufsize) {
	char local_buffer[128];
	size_t reqlen;
	reqlen = (*node->i_type->it_symlink.sl_readlink_dynamic)(node,
	                                                         local_buffer,
	                                                         sizeof(local_buffer));
	if (reqlen <= sizeof(local_buffer))
		return path_expandchild_symlink(parent_path, root_path, local_buffer, reqlen, premaining_links);
	*required_bufsize = reqlen;
	return NULL;
}


PRIVATE ATTR_RETNONNULL REF struct path *KCALL
path_expandchild(struct path *__restrict parent_path,
                 struct path *__restrict root_path,
                 struct inode *__restrict child_node,
                 struct directory_entry *__restrict child_entry,
                 u32 *__restrict premaining_links) {
	/* Simple case: the child is a directory. */
	if (INODE_ISDIR(child_node))
		return path_newchild(parent_path, (struct directory_node *)child_node, child_entry);
	if (INODE_ISLNK(child_node)) {
		char *buffer;
		REF struct path *result;
		size_t reqlen, new_reqlen;
		/* Keep track of the number of allowed symbolic links.
		 * If no more links are allowed, throw an exception. */
		if unlikely(!*premaining_links)
			THROW(E_FSERROR_TOO_MANY_SYMBOLIC_LINKS);
		--*premaining_links;

		/* Traverse symbolic links! */
		if (symlink_node_load((struct symlink_node *)child_node)) {
			return path_expandchild_symlink(parent_path, root_path,
			                                ((struct symlink_node *)child_node)->sl_text,
			                                (size_t)((struct symlink_node *)child_node)->i_filesize,
			                                premaining_links);
		}
		/* Dynamically managed symbolic link. */
		result = path_expand_dynamic_symlink(parent_path, root_path,
		                                     (struct symlink_node *)child_node,
		                                     premaining_links,
		                                     &reqlen);
		if likely(result)
			return result;
		/* Must allocate a larger, heap-based buffer. */
		buffer = (char *)kmalloc(reqlen, FS_GFP);
		TRY {
again_readlink:
			new_reqlen = (*child_node->i_type->it_symlink.sl_readlink_dynamic)((struct symlink_node *)child_node,
			                                                                   buffer,
			                                                                   reqlen);
			if unlikely(new_reqlen > reqlen) {
				buffer = (char *)krealloc(buffer, new_reqlen, FS_GFP);
				reqlen = new_reqlen;
				goto again_readlink;
			}
			/* Expand the symbolic link that was just read. */
			result = path_expandchild_symlink(parent_path,
			                                  root_path,
			                                  buffer,
			                                  new_reqlen,
			                                  premaining_links);
		} EXCEPT {
			kfree(buffer);
			RETHROW();
		}
		kfree(buffer);
		return result;
	}
	THROW(E_FSERROR_NOT_A_DIRECTORY,
	      E_FILESYSTEM_NOT_A_DIRECTORY_WALK);
}


LOCAL ATTR_RETNONNULL REF struct path *KCALL
path_walkchild(struct path *__restrict self,
               struct path *__restrict root_path,
               /*utf-8*/ char const *__restrict name_start,
               u16 name_length,
               u32 *__restrict premaining_links) {
	uintptr_t hash;
	REF struct path *result;
	REF struct directory_node *parent_directory;
	REF struct inode *child_node;
	REF struct directory_entry *child_entry;
	hash = directory_entry_hash(name_start, name_length);
	result = path_getchild_or_parent_inode(self, name_start, name_length,
	                                       hash, &parent_directory);
	if (result)
		return result;
	assertf(parent_directory, "No mounted INode in %p", self);
	assert(!wasdestroyed(parent_directory));
	TRY {
		child_node = directory_getnode(parent_directory,
		                               name_start, name_length,
		                               hash, &child_entry);
	} EXCEPT {
		decref(parent_directory);
		RETHROW();
	}
	decref(parent_directory);
	if (!child_node)
		THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DIR);
	{
		FINALLY_DECREF_UNLIKELY(child_node);
		FINALLY_DECREF_UNLIKELY(child_entry);
		result = path_expandchild(self,
		                          root_path,
		                          child_node,
		                          child_entry,
		                          premaining_links);
	}
	return result;
}


LOCAL ATTR_RETNONNULL REF struct path *KCALL
path_walkcasechild(struct path *__restrict self,
                   struct path *__restrict root_path,
                   /*utf-8*/ char const *__restrict name_start,
                   u16 name_length,
                   u32 *__restrict premaining_links) {
	uintptr_t hash;
	REF struct path *result;
	REF struct directory_node *parent_directory;
	REF struct inode *child_node;
	REF struct directory_entry *child_entry;
	hash = directory_entry_hash(name_start, name_length);
	result = path_getcasechild_or_parent_inode(self, name_start, name_length,
	                                           hash, &parent_directory);
	if (result)
		return result;
	assertf(parent_directory, "No mounted INode in %p", self);
	assert(!wasdestroyed(parent_directory));
	TRY {
		child_node = directory_getcasenode(parent_directory,
		                                   name_start, name_length,
		                                   hash, &child_entry);
	} EXCEPT {
		decref(parent_directory);
		RETHROW();
	}
	decref(parent_directory);
	if (!child_node)
		THROW(E_FSERROR_PATH_NOT_FOUND, E_FILESYSTEM_PATH_NOT_FOUND_DIR);
	{
		FINALLY_DECREF_UNLIKELY(child_node);
		FINALLY_DECREF_UNLIKELY(child_entry);
		result = path_expandchild(self,
		                          root_path,
		                          child_node,
		                          child_entry,
		                          premaining_links);
	}
	return result;
}


PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3, 5)) REF struct path *KCALL
path_expandchild_symlink(struct path *cwd,
                         struct path *root,
                         char const *__restrict symlink_path,
                         size_t symlink_size,
                         u32 *__restrict premaining_links) {
	char const *segment_start, *segment_end;
	char const *path_end;
	char32_t ch;
	segment_start = symlink_path;
	path_end      = symlink_path + symlink_size;
	/* Deal with leading slashes. */
	ch = unicode_readutf8_n((char const **)&symlink_path, path_end);
	if unlikely(!ch) {
		/* Empty path. */
return_cwd:
		return incref(cwd);
	}
	if (ch == '/') {
		/* Start at the root directory. */
		cwd = root;
		do {
			segment_start = symlink_path;
			ch = unicode_readutf8_n((char const **)&symlink_path, path_end);
		} while (ch == '/');
		if (!ch) /* Reference to the filesystem root. */
			goto return_cwd;
	}
	incref(cwd);
	for (;;) {
		segment_end = symlink_path;
		ch = unicode_readutf8_n((char const **)&symlink_path, path_end);
		if (ch == '/') {
			u16 segment_length;
			char const *next_segment_start;
			REF struct path *next_path;
at_segment_seperator:
			/* Load the child segment. */
			if ((size_t)(segment_end - segment_start) > 0xffff)
				THROW(E_FSERROR_ILLEGAL_PATH);
			next_segment_start = symlink_path;
			if (ch) {
				do {
					next_segment_start = symlink_path,
					ch = unicode_readutf8_n((char const **)&symlink_path, path_end);
				} while (ch == '/');
			}
			segment_length = (u16)(segment_end - segment_start);
			switch (segment_length) {

			case 0:
				break;

			case 2:
				if (segment_start[0] != '.')
					goto generic_directory_child;
				if (segment_start[1] != '.')
					goto generic_directory_child;
				/* Parent directory reference. */
				next_path = cwd->p_parent;
				if (cwd == root || !next_path)
					next_path = cwd;
				incref(next_path);
				goto set_next_path;

			case 1:
				if (segment_start[0] == '.')
					break; /* Current directory reference. */
				ATTR_FALLTHROUGH
			default:
generic_directory_child:
				TRY {
					next_path = path_walkchild(cwd,
					                           root,
					                           segment_start,
					                           segment_length,
					                           premaining_links);
				} EXCEPT {
					decref(cwd);
					RETHROW();
				}
set_next_path:
				decref(cwd);
				cwd = next_path;
				break;
			}
			if (!ch)
				break;
			segment_start = next_segment_start;
			continue;
		}
		if (!ch)
			goto at_segment_seperator;
	}
	return cwd;
}




DECL_END

#ifndef __INTELLISENSE__
#define TRAVERSE_N 1
#include "vfs-traverse-impl.c.inl"
#include "vfs-traverse-impl.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_FS_VFS_TRAVERSE_C */
