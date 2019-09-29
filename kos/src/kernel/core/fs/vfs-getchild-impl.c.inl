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
#ifdef __INTELLISENSE__
#include "vfs.c"
#define PATH_GETCASECHILD       1
#define ALWAYS_GET_PARENT_INODE 1
#endif /* __INTELLISENSE__ */

#include <kernel/malloc.h>

#include <alloca.h>

DECL_BEGIN

#ifdef PATH_GETCASECHILD
#ifndef MEMCASEEQ_KU_NOPF_DEFINED
#define MEMCASEEQ_KU_NOPF_DEFINED 1
PRIVATE NOBLOCK WUNUSED ssize_t
NOTHROW(KCALL memcaseeq_ku_nopf)(KERNEL void const *kernel_buffer,
                                 USER CHECKED void const *user_buffer,
                                 size_t num_bytes) {
	byte_t rhs_buffer[__SIZEOF_CACHELINE__];
	while (num_bytes) {
		size_t error, temp;
		temp = num_bytes;
		if (temp > __SIZEOF_CACHELINE__)
			temp = __SIZEOF_CACHELINE__;
		error = memcpy_nopf(rhs_buffer, user_buffer, temp);
		if unlikely(error)
			return -1; /* Right buffer is faulty. */
		if (memcasecmp(kernel_buffer, rhs_buffer, temp) != 0)
			return 1;
		num_bytes -= temp;
		kernel_buffer = (byte_t *)kernel_buffer + temp;
		user_buffer = (byte_t *)user_buffer + temp;
	}
	return 0;
}
#endif /* !MEMCASEEQ_KU_NOPF_DEFINED */
#endif /* PATH_GETCASECHILD */

#ifdef ALWAYS_GET_PARENT_INODE
/* Same as `path_getchild_or_parent_inode()', but _always_ store a reference
 * to the INode of the given path `self' within `*pparent_inode' */
#ifdef PATH_GETCASECHILD
PUBLIC REF struct path *KCALL
path_getcasechild_and_parent_inode(struct path *__restrict self,
                                   USER CHECKED /*utf-8*/ char const *name,
                                   u16 namelen, uintptr_t namehash,
                                   REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT)
#else /* PATH_GETCASECHILD */
PUBLIC REF struct path *KCALL
path_getchild_and_parent_inode(struct path *__restrict self,
                               USER CHECKED /*utf-8*/ char const *name,
                               u16 namelen, uintptr_t namehash,
                               REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT)
#endif /* !PATH_GETCASECHILD */
#else /* ALWAYS_GET_PARENT_INODE */
/* Search for a specific child path within `self', _OR_ store a reference
 * to the INode of `self' within `*pparent_inode' when NULL is returned.
 * In the case where non-NULL is returned, `*pparent_inode' is left in an undefined state. */
#ifdef PATH_GETCASECHILD
PUBLIC REF struct path *KCALL
path_getcasechild_or_parent_inode(struct path *__restrict self,
                                  USER CHECKED /*utf-8*/ char const *name,
                                  u16 namelen, uintptr_t namehash,
                                  REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT)
#else /* PATH_GETCASECHILD */
PUBLIC REF struct path *KCALL
path_getchild_or_parent_inode(struct path *__restrict self,
                              USER CHECKED /*utf-8*/ char const *name,
                              u16 namelen, uintptr_t namehash,
                              REF struct directory_node **__restrict pparent_inode)
		THROWS(E_WOULDBLOCK, E_SEGFAULT)
#endif /* !PATH_GETCASECHILD */
#endif /* !ALWAYS_GET_PARENT_INODE */
{
	REF struct path *result;
	sync_read(self);
	char *kernel_name;
	bool kernel_name_is_heap;
	if likely(self->p_cldlist) {
		result = self->p_cldlist[namehash & self->p_cldmask];
		for (; result; result = result->p_dirnext.ln_next) {
			int error;
			if (result->p_dirent->de_hash != namehash)
				continue;
			if (result->p_dirent->de_namelen != namelen)
				continue;
			/* First pass: Assume the likely case that we've already got the
			 *             correct entry and perform the final name-compare
			 *             while not holding a lock to `self' */
			if unlikely(!tryincref(result))
				continue;
#ifdef ALWAYS_GET_PARENT_INODE
			*pparent_inode = (REF struct directory_node *)incref(self->p_inode);
#endif /* ALWAYS_GET_PARENT_INODE */
			sync_endread(self);
			TRY {
				error = memcmp(result->p_dirent->de_name,
				               name, namelen * sizeof(char));
			} EXCEPT {
				decref(result);
#ifdef ALWAYS_GET_PARENT_INODE
				decref(*pparent_inode);
#endif /* ALWAYS_GET_PARENT_INODE */
				RETHROW();
			}
			if unlikely(error != 0) {
				/* Same length/hash, but still a different name... */
				decref(result);
#ifdef ALWAYS_GET_PARENT_INODE
				decref(*pparent_inode);
#endif /* ALWAYS_GET_PARENT_INODE */
				goto find_name_after_initial_missmatch;
			}
			return result;
		}
#ifdef PATH_GETCASECHILD
		/* Failed to find an entry matching the given hash.
		 * In the case of a case-insensitive lookup, this could
		 * very well be happening due to the given name using
		 * a different casing than any of the names we've got. */
		goto find_name_with_different_casing;
#endif /* PATH_GETCASECHILD */
	}
fail_and_unlock:
	/* The containing INode is always returned on error. */
	*pparent_inode = (REF struct directory_node *)incref(self->p_inode);
	sync_endread(self);
	return NULL;
find_name_after_initial_missmatch:
	/* The first candidate wasn't the one, but we released our lock on `self'
	 * in order to quickly match file names. - Re-acquire that lock and perform
	 * the search once again, only this time around, make use of `memeq_ku_nopf()',
	 * thus not having to release the lock on `self', allowing us to keep on
	 * searching through all possible candidates.
	 * If during this we encounter a problem with the given path not being accessible
	 * directly, we'll release our lock on `self', create a kernel-space copy of `name'
	 * by use of alloca() / kmalloc(), the try the search one last time using our non-faulting
	 * copy. */
	sync_read(self);
	if unlikely(!self->p_cldlist)
		goto fail_and_unlock;
	result = self->p_cldlist[namehash & self->p_cldmask];
	for (; result; result = result->p_dirnext.ln_next) {
		ssize_t error;
		if (result->p_dirent->de_hash != namehash)
			continue;
		if (result->p_dirent->de_namelen != namelen)
			continue;
		error = memeq_ku_nopf(result->p_dirent->de_name, name, namelen * sizeof(char));
		if (error != 0) {
			if (error < 0) /* The given `name' is faulty. */
				goto find_name_with_kernel_copy;
			continue; /* Name miss-match */
		}
		/* Found it! */
		if unlikely(!tryincref(result)) {
			sync_endread(self);
			goto find_name_after_initial_missmatch;
		}
#ifdef ALWAYS_GET_PARENT_INODE
		*pparent_inode = (REF struct directory_node *)incref(self->p_inode);
#endif /* ALWAYS_GET_PARENT_INODE */
		sync_endread(self);
		return result;
	}
	/* Failed to find the given name. */
	goto fail_and_unlock;
find_name_with_kernel_copy:
	/* As described above, create a kernel-copy of `name' */
	kernel_name_is_heap = false;
	if unlikely(namelen >= 256) {
		kernel_name_is_heap = true;
		kernel_name = (char *)kmalloc(namelen * sizeof(char),
		                              GFP_LOCKED | GFP_PREFLT);
	} else {
		kernel_name = (char *)alloca(namelen * sizeof(char));
	}
	TRY {
		memcpy(kernel_name, name, namelen * sizeof(char));
		sync_read(self);
	} EXCEPT {
		if (kernel_name_is_heap)
			kfree(kernel_name);
		RETHROW();
	}
	if unlikely(!self->p_cldlist) {
		*pparent_inode = (REF struct directory_node *)incref(self->p_inode);
		sync_endread(self);
		if (kernel_name_is_heap)
			kfree(kernel_name);
		return NULL;
	}
	result = self->p_cldlist[namehash & self->p_cldmask];
	for (; result; result = result->p_dirnext.ln_next) {
		if (result->p_dirent->de_hash != namehash)
			continue;
		if (result->p_dirent->de_namelen != namelen)
			continue;
		if (memcmp(result->p_dirent->de_name, kernel_name, namelen * sizeof(char)) != 0)
			continue;
		if unlikely(!tryincref(result)) {
			sync_endread(self);
			goto find_name_after_initial_missmatch;
		}
#ifdef ALWAYS_GET_PARENT_INODE
		*pparent_inode = (REF struct directory_node *)incref(self->p_inode);
#endif /* ALWAYS_GET_PARENT_INODE */
		sync_endread(self);
		if (kernel_name_is_heap)
			kfree(kernel_name);
		return result;
	}
#ifdef PATH_GETCASECHILD
	/* Search for the given name whilst ignoring casing. */
find_name_with_different_casing_and_kernel_name:
	{
		size_t i;
		for (i = 0; i <= self->p_cldmask; ++i) {
			for (result = self->p_cldlist[i]; result;
			     result = result->p_dirnext.ln_next) {
				if (result->p_dirent->de_namelen != namelen)
					continue;
				if (memcasecmp(result->p_dirent->de_name, kernel_name, namelen) != 0)
					continue;
				/* Found it! */
				if unlikely(!tryincref(result)) {
					sync_endread(self);
					TRY {
						sync_read(self);
					} EXCEPT {
						if (kernel_name_is_heap)
							kfree(kernel_name);
						RETHROW();
					}
					goto find_name_with_different_casing_and_kernel_name;
				}
#ifdef ALWAYS_GET_PARENT_INODE
				*pparent_inode = (REF struct directory_node *)incref(self->p_inode);
#endif /* ALWAYS_GET_PARENT_INODE */
				sync_endread(self);
				if (kernel_name_is_heap)
					kfree(kernel_name);
				return result;
			}
		}
	}
#endif /* PATH_GETCASECHILD */
	if (kernel_name_is_heap)
		kfree(kernel_name);
	/* Failed to find the given name. */
	goto fail_and_unlock;
#ifdef PATH_GETCASECHILD
find_name_with_different_casing_relock:
	sync_read(self);
find_name_with_different_casing:
	assert(sync_reading(self));
	{
		size_t i;
		for (i = 0; i <= self->p_cldmask; ++i) {
			for (result = self->p_cldlist[i]; result;
			     result = result->p_dirnext.ln_next) {
				int error;
				if (result->p_dirent->de_namelen != namelen)
					continue;
				error = memcaseeq_ku_nopf(result->p_dirent->de_name,
				                          name, namelen * sizeof(char));
				if (error != 0) {
					if (error < 0) /* The given `name' is faulty. */
						goto find_name_with_kernel_copy;
					continue; /* Name miss-match */
				}
				/* Found it! */
				if unlikely(!tryincref(result)) {
					sync_endread(self);
					goto find_name_with_different_casing_relock;
				}
#ifdef ALWAYS_GET_PARENT_INODE
				*pparent_inode = (REF struct directory_node *)incref(self->p_inode);
#endif /* ALWAYS_GET_PARENT_INODE */
				sync_endread(self);
				return result;
			}
		}
	}
	/* Failed to find the given name. */
	goto fail_and_unlock;
#endif /* PATH_GETCASECHILD */
}
#undef ALWAYS_GET_PARENT_INODE
#undef PATH_GETCASECHILD

DECL_END
