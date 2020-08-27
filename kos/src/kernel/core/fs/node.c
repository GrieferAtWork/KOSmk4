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
#ifndef GUARD_KERNEL_CORE_FS_NODE_C
#define GUARD_KERNEL_CORE_FS_NODE_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <debugger/hook.h>
#include <fs/node.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/aio.h>
#include <kernel/cache.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/heap.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/swap.h>
#include <kernel/types.h>
#include <kernel/vm.h>
#include <kernel/vm/phys.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/rpc.h>
#include <sched/signal.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <bits/dirent.h>
#include <kos/except/fs.h>
#include <kos/except/inval.h>
#include <kos/except/io.h>
#include <linux/magic.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>

#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include <libvio/access.h>

#include "../memory/vm/vm-partapi.h"


/* Define the ABI for the address tree used by vm. */
#define ATREE(x)      inode_tree_##x
#define ATREE_FUN     INTDEF
#define ATREE_IMP     INTERN
#define ATREE_CALL    KCALL
#define ATREE_NOTHROW NOTHROW
#define Tkey       ino_t
#define T          struct inode
#define N_NODEPATH i_filetree
#define ATREE_SINGLE 1
#include <hybrid/sequence/atree-abi.h>
#undef ATREE_SINGLE

DECL_BEGIN

DEFINE_HANDLE_REFCNT_FUNCTIONS(directoryentry, struct directory_entry)

INTERN size_t KCALL
handle_directoryentry_pread(struct directory_entry *__restrict self,
                            USER CHECKED void *dst, size_t num_bytes,
                            pos_t addr, iomode_t UNUSED(mode)) {
	size_t result;
	if unlikely(addr > (pos_t)(self->de_namelen * sizeof(char)))
		return 0;
	result = ((self->de_namelen - (u16)addr) + 1) * sizeof(char);
	if (result > num_bytes)
		result = num_bytes;
	memcpy(dst, self->de_name + (u16)addr, result);
	return result;
}

INTERN size_t KCALL
handle_directoryentry_read(struct directory_entry *__restrict self,
                           USER CHECKED void *dst, size_t num_bytes,
                           iomode_t mode) {
	return handle_directoryentry_pread(self, dst, num_bytes, 0, mode);
}

LOCAL ATTR_PURE NONNULL((1)) size_t KCALL
directory_entry_usersize(struct directory_entry const *__restrict self) {
	return offsetof(struct dirent, d_name) + (self->de_namelen + 1) * sizeof(char);
}

INTERN NONNULL((1)) size_t KCALL
handle_directoryentry_readdir(struct directory_entry *__restrict self,
                              USER CHECKED struct dirent *buf, size_t bufsize,
                              readdir_mode_t UNUSED(readdir_mode),
                              iomode_t UNUSED(mode)) {
	size_t result;
	result = directory_entry_usersize(self);
	if (bufsize >= offsetafter(struct dirent, d_ino64))
		buf->d_ino64 = (__ino64_t)self->de_ino;
	if (bufsize >= offsetafter(struct dirent, d_type))
		buf->d_type = self->de_type;
	if (bufsize >= offsetafter(struct dirent, d_namlen))
		buf->d_namlen = self->de_namelen;
	if (bufsize > offsetof(struct dirent, d_name)) {
		memcpy(buf->d_name, self->de_name,
		       MIN(self->de_namelen * sizeof(char),
		           bufsize - offsetof(struct dirent, d_name)));
	}
	return result;
}

INTERN NONNULL((1)) void KCALL
handle_directoryentry_stat(struct directory_entry *__restrict self,
                           USER CHECKED struct stat *result) {
	memset(result, 0, sizeof(*result));
	result->st_size = (self->de_namelen + 1) * sizeof(char);
	result->st_ino  = (__ino64_t)self->de_ino;
	result->st_mode = DTTOIF(self->de_type);
}

INTERN ATTR_CONST NONNULL((1)) poll_mode_t KCALL
handle_directoryentry_poll(struct directory_entry *__restrict UNUSED(self),
                           poll_mode_t what) {
	return what & POLLIN;
}

INTERN syscall_slong_t KCALL /* TODO: Add hop functions for reading all of the different fields. */
handle_directoryentry_hop(struct directory_entry *__restrict self, syscall_ulong_t cmd,
                          USER UNCHECKED void *arg, iomode_t mode);




PUBLIC WUNUSED ATTR_PURE NONNULL((1)) uintptr_t KCALL
directory_entry_hash(CHECKED USER /*utf-8*/ char const *__restrict name,
                     u16 namelen) THROWS(E_SEGFAULT) {
	size_t const *iter, *end;
	size_t hash = DIRECTORY_ENTRY_EMPTY_HASH;
	end = (iter = (size_t const *)name) + (namelen / sizeof(size_t));
	while (iter < end)
		hash += *iter++, hash *= 9;
	switch (namelen & (sizeof(size_t) - 1)) {
#if __SIZEOF_SIZE_T__ > 4
	case 7:
		hash += (size_t)((byte_t *)iter)[6] << 48;
		ATTR_FALLTHROUGH
	case 6:
		hash += (size_t)((byte_t *)iter)[5] << 40;
		ATTR_FALLTHROUGH
	case 5:
		hash += (size_t)((byte_t *)iter)[4] << 32;
		ATTR_FALLTHROUGH
	case 4:
		hash += (size_t)((byte_t *)iter)[3] << 24;
		ATTR_FALLTHROUGH
#endif
	case 3:
		hash += (size_t)((byte_t *)iter)[2] << 16;
		ATTR_FALLTHROUGH
	case 2:
		hash += (size_t)((byte_t *)iter)[1] << 8;
		ATTR_FALLTHROUGH
	case 1:
		hash += (size_t)((byte_t *)iter)[0];
		break;
	default: break;
	}
	return hash;
}

PUBLIC struct directory_entry empty_directory_entry = {
	/* .de_refcnt   = */ 1,
	/* .de_heapsize = */ sizeof(empty_directory_entry),
	/* .de_next     = */ NULL,
	/* .de_bypos    = */ LLIST_INITNODE,
	/* .de_fsdata   = */ {
		/* .de_start = */ 0,
		/* .de_data  = */ { 0 },
	},
	/* .de_pos      = */ (pos_t)0,
	/* .de_ino      = */ (ino_t)0,
	/* .de_hash     = */ DIRECTORY_ENTRY_EMPTY_HASH,
	/* .de_namelen  = */ 0,
#if 1
	/* .de_type     = */ DT_DIR, /* DIR, because this entry is used as entry in `open("/")' */
#else
	/* .de_type     = */ DT_UNKNOWN,
#endif
	/* .de_name     = */ { 0 }
};

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL directory_entry_destroy)(struct directory_entry *__restrict self) {
	heap_free(FS_HEAP, self, self->de_heapsize, FS_GFP);
}

/* Allocate a new directory entry.
 * The caller must still initialize:
 *   - de_next
 *   - de_bypos
 *   - de_fsdata (as needed)
 *   - de_pos
 *   - de_ino
 *   - de_hash   (`directory_entry_alloc' only)
 *   - de_type
 *   - de_name   (`directory_entry_alloc' only)
 * NOTE: These functions will have already ensured that
 *       `return->de_name[namelen] == '\0''
 */
PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct directory_entry *KCALL
directory_entry_alloc(u16 namelen) THROWS(E_BADALLOC) {
	struct heapptr resptr;
	REF struct directory_entry *result;
	resptr = heap_alloc(FS_HEAP,
	                    offsetof(struct directory_entry, de_name) +
	                    (namelen + 1) * sizeof(char),
	                    FS_GFP);
	result = (REF struct directory_entry *)resptr.hp_ptr;
	result->de_refcnt        = 1;
	result->de_heapsize      = resptr.hp_siz;
	result->de_namelen       = namelen;
	result->de_name[namelen] = '\0';
	return result;
}

PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_entry_alloc_s(USER CHECKED /*utf-8*/ char const *name, u16 namelen)
		THROWS(E_BADALLOC, E_SEGFAULT) {
	REF struct directory_entry *result;
	result = directory_entry_alloc(namelen);
	TRY {
		memcpy(result->de_name, name, namelen, sizeof(char));
	} EXCEPT {
		directory_entry_destroy(result);
		RETHROW();
	}
	result->de_hash = directory_entry_hash(result->de_name, namelen);
	return result;
}







/* RECENTLY USED INODE CACHE */
PRIVATE DEFINE_ATOMIC_RWLOCK(inodes_recent_lock);
DEFINE_DBG_BZERO_OBJECT(inodes_recent_lock);

/* [lock(inodes_recent_lock)][0..1] Chain of recently used nodes. */
PRIVATE REF LLIST(struct inode) inodes_recent_list = NULL;
PRIVATE REF struct inode *inodes_recent_back = NULL;

/* [lock(inodes_recent_lock)] The amount of nodes apart of `inodes_recent_list' */
PRIVATE size_t inodes_recent_size = 0;

/* [lock(atomic)] Max number of INodes to keep cached as recent */
PUBLIC WEAK size_t inodes_recent_lim = 512;

/* Return the number of INodes current stored within the recent-cache. */
PUBLIC NOBLOCK size_t
NOTHROW(KCALL inode_recent_getcur)(void) {
	return ATOMIC_READ(inodes_recent_size);
}


/* Indicate that `self' has been used recently, allowing the INode to be cached
 * such that it will remain allocated for a while, even when not referenced elsewhere. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL inode_recent)(struct inode *__restrict self) {
	if (self->i_recent.ln_pself != NULL)
		return;
	if (sync_trywrite(&inodes_recent_lock)) {
		COMPILER_READ_BARRIER();
		if (self->i_recent.ln_pself == NULL) {
			if (inodes_recent_size < ATOMIC_READ(inodes_recent_lim)) {
				LLIST_INSERT(inodes_recent_list, self, i_recent);
				if (!inodes_recent_back)
					inodes_recent_back = self;
				incref(self);
				++inodes_recent_size;
			} else {
				struct inode *oldest_node;
				/* Pop nodes from the back. */
				oldest_node = inodes_recent_back;
				assert(oldest_node != NULL);
				if unlikely(inodes_recent_back == inodes_recent_list) {
					inodes_recent_list = inodes_recent_back = self;
					self->i_recent.ln_pself = &inodes_recent_list;
					self->i_recent.ln_next  = NULL;
				} else {
					inodes_recent_back = COMPILER_CONTAINER_OF(oldest_node->i_recent.ln_pself,
					                                           struct inode, i_recent.ln_next);
					assert(inodes_recent_back->i_recent.ln_next == oldest_node);
					inodes_recent_back->i_recent.ln_next = NULL;
					LLIST_INSERT(inodes_recent_list, self, i_recent);
				}
				sync_endwrite(&inodes_recent_lock);
				decref(oldest_node);
				return;
			}
		} else {
			/* Bring this node back to the front. */
			LLIST_REMOVE(self, i_recent);
			LLIST_INSERT(inodes_recent_list, self, i_recent);
		}
		sync_endwrite(&inodes_recent_lock);
	}
}

/* Clear the cache of recently used INodes. */
DEFINE_SYSTEM_CACHE_CLEAR(inode_recent_tryclear);
PUBLIC NOBLOCK size_t
NOTHROW(KCALL inode_recent_tryclear)(void) {
	size_t result = 0;
	for (;;) {
		REF struct inode *node;
		if (!sync_trywrite(&inodes_recent_lock))
			break;
		node = inodes_recent_list;
		if (!node) {
			assert(!inodes_recent_back);
			assert(!inodes_recent_size);
			sync_endwrite(&inodes_recent_lock);
			break;
		}
		/* Remove the node from the recent-node cache. */
		inodes_recent_list = node->i_recent.ln_next;
		if (!inodes_recent_list)
			inodes_recent_back = NULL;
		assert(inodes_recent_size);
		--inodes_recent_size;
		assert((inodes_recent_size != 0) == (inodes_recent_list != NULL));
		assert((inodes_recent_size != 0) == (inodes_recent_back != NULL));
		node->i_recent.ln_next  = NULL;
		node->i_recent.ln_pself = NULL;
		sync_endwrite(&inodes_recent_lock);
		assert(!wasdestroyed(node));
		if (ATOMIC_DECFETCH(node->db_refcnt)) {
			if (OVERFLOW_UADD(result, node->i_heapsize, &result))
				result = (size_t)-1;
			destroy(node);
		}
	}
	return result;
}

/* Clear the cache of recently used INodes. */
PUBLIC size_t KCALL
inode_recent_clear(void) THROWS(E_WOULDBLOCK) {
	size_t result = 0;
	for (;;) {
		REF struct inode *node;
		sync_write(&inodes_recent_lock);
		node = inodes_recent_list;
		if (!node) {
			assert(!inodes_recent_back);
			assert(!inodes_recent_size);
			sync_endwrite(&inodes_recent_lock);
			break;
		}
		/* Remove the node from the recent-node cache. */
		inodes_recent_list = node->i_recent.ln_next;
		if (!inodes_recent_list)
			inodes_recent_back = NULL;
		assert(inodes_recent_size);
		--inodes_recent_size;
		assert((inodes_recent_size != 0) == (inodes_recent_list != NULL));
		assert((inodes_recent_size != 0) == (inodes_recent_back != NULL));
		node->i_recent.ln_next  = NULL;
		node->i_recent.ln_pself = NULL;
		sync_endwrite(&inodes_recent_lock);
		assert(!wasdestroyed(node));
		if (ATOMIC_DECFETCH(node->db_refcnt)) {
			if (OVERFLOW_UADD(result, node->i_heapsize, &result))
				result = (size_t)-1;
			destroy(node);
		}
	}
	return result;
}

PUBLIC size_t
NOTHROW(KCALL inode_recent_clear_nx)(void) {
	size_t result = 0;
	for (;;) {
		REF struct inode *node;
		if (!sync_write_nx(&inodes_recent_lock))
			break;
		node = inodes_recent_list;
		if (!node) {
			assert(!inodes_recent_back);
			assert(!inodes_recent_size);
			sync_endwrite(&inodes_recent_lock);
			break;
		}
		/* Remove the node from the recent-node cache. */
		inodes_recent_list = node->i_recent.ln_next;
		if (!inodes_recent_list)
			inodes_recent_back = NULL;
		assert(inodes_recent_size);
		--inodes_recent_size;
		assert((inodes_recent_size != 0) == (inodes_recent_list != NULL));
		assert((inodes_recent_size != 0) == (inodes_recent_back != NULL));
		node->i_recent.ln_next  = NULL;
		node->i_recent.ln_pself = NULL;
		sync_endwrite(&inodes_recent_lock);
		assert(!wasdestroyed(node));
		if (ATOMIC_DECFETCH(node->db_refcnt)) {
			if (OVERFLOW_UADD(result, node->i_heapsize, &result))
				result = (size_t)-1;
			destroy(node);
		}
	}
	return result;
}

/* Try to remove the given INode `self' from the recent-cache.
 * @return: * : One of `INODE_RECENT_TRYREMOVE_*' */
PUBLIC NOBLOCK unsigned int
NOTHROW(KCALL inode_recent_tryremove)(struct inode *__restrict self) {
	if (ATOMIC_READ(self->i_recent.ln_pself) == NULL)
		return INODE_RECENT_TRYREMOVE_NOTRECENT;
	if (!sync_trywrite(&inodes_recent_lock))
		return INODE_RECENT_TRYREMOVE_WOULDBLOCK;
	COMPILER_READ_BARRIER();
	if unlikely(!self->i_recent.ln_pself) {
		sync_endwrite(&inodes_recent_lock);
		return INODE_RECENT_TRYREMOVE_NOTRECENT;
	}
	assert(inodes_recent_list);
	assert(inodes_recent_back);
	assert(inodes_recent_size);
	--inodes_recent_size;
	LLIST_REMOVE(self, i_recent);
	if (self == inodes_recent_back) {
		/* Update the back-pointer. */
		assert((inodes_recent_list == NULL) ==
		       (self->i_recent.ln_pself == &inodes_recent_list));
		if (self->i_recent.ln_pself == &inodes_recent_list) {
			assert(inodes_recent_size == 0);
			inodes_recent_back = NULL;
		} else {
			assert(inodes_recent_size != 0);
			inodes_recent_back = COMPILER_CONTAINER_OF(self->i_recent.ln_pself,
			                                           struct inode,
			                                           i_recent.ln_next);
		}
	}
	self->i_recent.ln_pself = NULL;
	sync_endwrite(&inodes_recent_lock);
	decref_nokill(self); /* Nokill, because the caller must also be holding a reference... */
	return INODE_RECENT_TRYREMOVE_SUCCESS;
}











/* GLOBAL LIST OF ALL KNOWN SUPERBLOCKS */
PUBLIC struct filesystems fs_filesystems = {
	/* .f_superlock   = */ RWLOCK_INIT,
	/* .f_superblocks = */ NULL,
};

DEFINE_DBG_BZERO_OBJECT(fs_filesystems.f_superlock);

PUBLIC ATTR_READMOSTLY WEAK REF
struct superblock *fs_filesystems_delblocks = NULL;


LOCAL NOBLOCK void
NOTHROW(KCALL clear_fs_delblocks)(void) {
	REF struct superblock *chain, *next;
	chain = ATOMIC_XCH(fs_filesystems_delblocks, NULL);
	while (chain) {
		next = *(REF struct superblock **)chain;
		assert(chain->i_heapsize >= sizeof(struct superblock));
		heap_free(FS_HEAP, chain, chain->i_heapsize, FS_GFP);
		chain = next;
	}
}

PUBLIC void KCALL
fs_filesystems_lock_read(void) THROWS(E_WOULDBLOCK) {
	sync_read(&fs_filesystems.f_superlock);
	if (ATOMIC_READ(fs_filesystems_delblocks) != NULL) {
		if (sync_tryupgrade(&fs_filesystems.f_superlock)) {
			clear_fs_delblocks();
			sync_downgrade(&fs_filesystems.f_superlock);
		}
	}
}

PUBLIC void KCALL
fs_filesystems_lock_write(void) THROWS(E_WOULDBLOCK) {
	sync_write(&fs_filesystems.f_superlock);
	clear_fs_delblocks();
}

PUBLIC bool KCALL
fs_filesystems_lock_upgrade(void) THROWS(E_WOULDBLOCK) {
	bool result;
	result = sync_upgrade(&fs_filesystems.f_superlock);
	clear_fs_delblocks();
	return result;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL fs_filesystems_lock_trywrite)(void) {
	if (!sync_trywrite(&fs_filesystems.f_superlock))
		return false;
	clear_fs_delblocks();
	return true;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL fs_filesystems_lock_tryupgrade)(void) {
	if (!sync_tryupgrade(&fs_filesystems.f_superlock))
		return false;
	clear_fs_delblocks();
	return true;
}

PUBLIC NOBLOCK WUNUSED bool
NOTHROW(KCALL fs_filesystems_lock_tryread)(void) {
	if (!sync_tryread(&fs_filesystems.f_superlock))
		return false;
	if (ATOMIC_READ(fs_filesystems_delblocks) != NULL) {
		if (sync_tryupgrade(&fs_filesystems.f_superlock)) {
			clear_fs_delblocks();
			sync_downgrade(&fs_filesystems.f_superlock);
		}
	}
	return true;
}

PUBLIC NOBLOCK void
NOTHROW(KCALL fs_filesystems_lock_endwrite)(void) {
again:
	sync_endwrite(&fs_filesystems.f_superlock);
	if unlikely(ATOMIC_READ(fs_filesystems_delblocks)) {
		if (sync_trywrite(&fs_filesystems.f_superlock)) {
			clear_fs_delblocks();
			goto again;
		}
	}
}

PUBLIC NOBLOCK bool
NOTHROW(KCALL fs_filesystems_lock_endread)(void) {
	if (rwlock_endread(&fs_filesystems.f_superlock))
		return true;
again_checkdel:
	if unlikely(ATOMIC_READ(fs_filesystems_delblocks)) {
		if (sync_trywrite(&fs_filesystems.f_superlock)) {
			clear_fs_delblocks();
			sync_endwrite(&fs_filesystems.f_superlock);
			goto again_checkdel;
		}
	}
	return false;
}


/* Remove the given `block' from `fs_filesystems'
 * NOTE: The caller is required to be holding a lock to `fs_filesystems.f_superlock' */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL fs_filesystems_remove)(struct superblock *__restrict block) {
	struct superblock **piter, *iter;
	assert(sync_writing(&fs_filesystems.f_superlock));
	piter = &fs_filesystems.f_superblocks;
	for (; (iter = *piter) != NULL; piter = &iter->s_filesystems.sn_next) {
		if (iter != block)
			continue;
		*piter = block->s_filesystems.sn_next;
		return true;
	}
	return false;
}

















/* INODE INTERFACE */
PUBLIC NONNULL((1)) bool KCALL
inode_changed_chmtime(struct inode *__restrict self) {
	{
		SCOPED_WRITELOCK((struct vm_datablock *)self);
		/* TODO: Update the INode's last-changed timestamp */
	}
	return inode_changed(self, INODE_FCHANGED | INODE_FATTRCHANGED);
}

/* Ensure that attributes have been loaded for the given INode.
 * Upon return, it is guarantied that the `INODE_FATTRLOADED' flag will be set. */
PUBLIC NONNULL((1)) void KCALL
inode_loadattr(struct inode *__restrict self)
		THROWS(E_IOERROR, ...) {
	if (ATOMIC_READ(self->i_flags) & INODE_FATTRLOADED)
		return; /* Already loaded. */
	/* Must load INode attributes now. */
	SCOPED_WRITELOCK((struct vm_datablock *)self);
	COMPILER_READ_BARRIER();
	assert(self->i_type);
	assert(self->i_type->it_attr.a_loadattr);
	/* Check if attributes have been loaded in the mean time. */
	if likely(!(ATOMIC_READ(self->i_flags) & INODE_FATTRLOADED)) {
		(*self->i_type->it_attr.a_loadattr)(self);
		/* Set the attributes-loaded flag. */
		ATOMIC_FETCHOR(self->i_flags, INODE_FATTRLOADED);
	}
}



/* Assert that the calling thread is allowed to access the given
 * the specified file, throwing an `E_FSERROR_ACCESS_DENIED' if not.
 * @param: type: Set of `R_OK | W_OK | X_OK' */
PUBLIC NONNULL((1)) void KCALL
inode_access(struct inode *__restrict self, unsigned int type)
		THROWS(E_FSERROR_ACCESS_DENIED, E_IOERROR, ...) {
	if unlikely(!inode_tryaccess(self, type))
		THROW(E_FSERROR_ACCESS_DENIED);
}

PUBLIC NONNULL((1)) void KCALL
inode_access_accmode(struct inode *__restrict self, iomode_t iomode)
		THROWS(E_FSERROR_ACCESS_DENIED, E_IOERROR, ...) {
	unsigned int type = 0;
	if ((iomode & IO_ACCMODE) != IO_WRONLY)
		type |= R_OK; /* Test for read-access */
	if ((iomode & IO_ACCMODE) != IO_RDONLY)
		type |= W_OK; /* Test for write-access */
	inode_access(self, type);
}

PUBLIC NONNULL((1)) bool KCALL
inode_tryaccess(struct inode *__restrict self, unsigned int type)
		THROWS(E_IOERROR, ...) {
	mode_t mode;
	unsigned int how;
	if unlikely(!type)
		return true;
	inode_loadattr(self);
	COMPILER_READ_BARRIER();
	mode = self->i_filemode;
	for (how = 1; how <= 4; how <<= 1) {
		if (!(type & how))
			continue; /* Access not checked. */
		if (mode & how)
			continue; /* Access is allowed for everyone. */
		if (mode & (how << 3)) {
			if (cred_isfsgroupmember(self->i_filegid))
				continue; /* The calling thread's user is part of the file owner's group */
		}
		if (mode & (how << 6)) {
			if (self->i_fileuid == cred_getsuid())
				continue; /* The calling thread's user is the file's owner */
			/* CAP_FOWNER: ... Ignore filesystem-uid checks ... */
			if (capable(CAP_FOWNER))
				continue;
		}
		return false;
	}
	return true;
}



/* Collect stat-information about the given INode `self', implementing
 * the behavior of the `stat(2)' system call for INodes, as well as many
 * other handle types, including PATH and FILE objects. */
PUBLIC NONNULL((1)) void KCALL
inode_stat(struct inode *__restrict self,
           USER CHECKED struct stat *result)
		THROWS(E_IOERROR, ...) {
	struct basic_block_device *dev;
	inode_loadattr(self);
	dev                = self->i_super->s_device;
	result->st_dev     = (__dev_t)(dev ? block_device_devno(dev) : 0);
	result->st_ino     = (__FS_TYPE(ino))self->i_fileino;
	result->st_mode    = (__mode_t)self->i_filemode;
	result->st_nlink   = (__nlink_t)self->i_filenlink;
	result->st_uid     = (__uid_t)self->i_fileuid;
	result->st_gid     = (__gid_t)self->i_filegid;
	result->st_rdev    = (__dev_t)self->i_filerdev;
	result->st_size    = (__FS_TYPE(pos))self->i_filesize;
	result->st_blksize = (__blksize_t)VM_DATABLOCK_PAGESIZE(self);
	result->st_blocks  = (__FS_TYPE(blkcnt))CEILDIV(result->st_size, VM_DATABLOCK_PAGESIZE(self)); /* XXX: Add an operator for this? */
#ifdef __TIMESPEC64_HAVE_TV_PAD
	/* Don't accidentally leak kernel data! */
	{
		struct timespec temp;
		temp.tv_sec   = self->i_fileatime.tv_sec;
		temp.tv_nsec  = self->i_fileatime.tv_nsec;
		temp.__tv_pad = 0;
		COMPILER_WRITE_BARRIER();
		result->st_atimespec = temp;

		temp.tv_sec   = self->i_filemtime.tv_sec;
		temp.tv_nsec  = self->i_filemtime.tv_nsec;
		temp.__tv_pad = 0;
		COMPILER_WRITE_BARRIER();
		result->st_mtimespec = temp;

		temp.tv_sec   = self->i_filectime.tv_sec;
		temp.tv_nsec  = self->i_filectime.tv_nsec;
		temp.__tv_pad = 0;
		COMPILER_WRITE_BARRIER();
		result->st_ctimespec = temp;
	}
#else /* __TIMESPEC64_HAVE_TV_PAD */
	result->st_atimespec = self->i_fileatime;
	result->st_mtimespec = self->i_filemtime;
	result->st_ctimespec = self->i_filectime;
#endif /* !__TIMESPEC64_HAVE_TV_PAD */
}


/* Atomically set the `INODE_FCHANGED' or `INODE_FATTRCHANGED' flags
 * and chain the node as part of the associated superblock's list of
 * changed INodes.
 * @param: what:   Set of `INODE_FCHANGED|INODE_FATTRCHANGED',
 *                 of which at least one must be given.
 * @return: true:  Successfully marked the INode for having been changed,
 *                 or the node had already been scheduled as having been
 *                 changed.
 * @return: false: The `INODE_FDELETED' bit has been set for `self' */
PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL inode_changed)(struct inode *__restrict self, uintptr_t what) {
	uintptr_t old_flags;
	assert(what != 0);
	assert(!(what & ~(INODE_FCHANGED | INODE_FATTRCHANGED)));
	assert(!(what & INODE_FCHANGED) || self->i_type->it_file.f_write);
	assert(!(what & INODE_FATTRCHANGED) || self->i_type->it_attr.a_saveattr);
	do {
		old_flags = ATOMIC_READ(self->i_flags);
		if (old_flags & INODE_FDELETED)
			return false;
	} while (!ATOMIC_CMPXCH_WEAK(self->i_flags, old_flags, old_flags | what));
	if (!(old_flags & (INODE_FCHANGED | INODE_FATTRCHANGED))) {
		struct inode *next;
		/* Schedule as pending-changed */
		do {
			next = ATOMIC_READ(self->i_super->s_changed);
			self->i_changed_next = next;
		} while (!ATOMIC_CMPXCH_WEAK(self->i_super->s_changed, next, self));
		incref(self);
	}
	return true;
}


PRIVATE NONNULL((1)) void KCALL
inode_check_deleted(struct inode *__restrict self,
                    uintptr_t reason = E_FILESYSTEM_DELETED_FILE)
                    THROWS(E_FSERROR_DELETED) {
	if (ATOMIC_READ(self->i_flags) & INODE_FDELETED) {
		if (self->i_super->s_flags & SUPERBLOCK_FUNMOUNTED)
			reason = E_FILESYSTEM_DELETED_UNMOUNTED;
		THROW(E_FSERROR_DELETED, reason);
	}
}

PRIVATE NONNULL((1)) void KCALL
inode_loadattr_and_check_deleted(struct inode *__restrict self,
                                 uintptr_t reason = E_FILESYSTEM_DELETED_FILE)
		THROWS(E_FSERROR_DELETED, E_IOERROR, ...) {
	uintptr_t flags = ATOMIC_READ(self->i_flags);
	if (flags & INODE_FDELETED) {
		if (self->i_super->s_flags & SUPERBLOCK_FUNMOUNTED)
			reason = E_FILESYSTEM_DELETED_UNMOUNTED;
		THROW(E_FSERROR_DELETED, reason);
	}
	if (flags & INODE_FATTRLOADED)
		return; /* Already loaded. */
	/* Must load INode attributes now. */
	SCOPED_WRITELOCK((struct vm_datablock *)self);
	COMPILER_READ_BARRIER();
	assert(self->i_type);
	assert(self->i_type->it_attr.a_loadattr);
	/* Check if attributes have been loaded in the mean time. */
	if likely(!(ATOMIC_READ(self->i_flags) & INODE_FATTRLOADED)) {
		(*self->i_type->it_attr.a_loadattr)(self);
		/* Set the attributes-loaded flag. */
		ATOMIC_FETCHOR(self->i_flags, INODE_FATTRLOADED);
	}
}


/* Change the size (in bytes) of the given INode.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:
 *                              [...]
 * @throw: E_FSERROR_DISK_FULL: [...]
 * @throw: E_FSERROR_READONLY:  [...]
 * @throw: E_IOERROR:           Failed to read/write data to/from disk. */
PUBLIC NONNULL((1)) void KCALL
inode_truncate(struct inode *__restrict self, pos_t new_size)
		THROWS(E_FSERROR_DELETED, E_FSERROR_UNSUPPORTED_OPERATION,
		       E_FSERROR_DISK_FULL, E_FSERROR_READONLY, E_IOERROR, ...) {
	bool was_changed           = false;
	struct inode_type *tp_self = self->i_type;
	if (!tp_self->it_file.f_truncate)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_TRUNC);
	inode_loadattr_and_check_deleted(self);
	{
		SCOPED_WRITELOCK((struct vm_datablock *)self);
		if likely(self->i_filesize != new_size) {
			if (new_size < self->i_filesize) {
				/* TODO: Delete/truncate VM data parts */
			}
			TRY {
				(*tp_self->it_file.f_truncate)(self, new_size);
			} EXCEPT {
				if (was_thrown(E_IOERROR_BADBOUNDS))
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_DISK_FULL));
				if (was_thrown(E_IOERROR_READONLY))
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_READONLY));
				RETHROW();
			}
			self->i_filesize = new_size;
			was_changed      = true;
		}
	}
	if (was_changed)
		inode_changed(self, INODE_FATTRCHANGED);
}

/* Perform an ioctl() command on the given INode. */
PUBLIC NONNULL((1)) syscall_slong_t KCALL
inode_ioctl(struct inode *__restrict self, syscall_ulong_t cmd,
            USER UNCHECKED void *arg, iomode_t mode)
		THROWS(...) {
	if (self->i_type->it_attr.a_ioctl)
		return (*self->i_type->it_attr.a_ioctl)(self, cmd, arg, mode);
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}


/* Change all non-NULL the timestamp that are given.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_READONLY: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRATTR: [...] */
PUBLIC NONNULL((1)) void KCALL
inode_chtime(struct inode *__restrict self,
             struct timespec const *new_atime,
             struct timespec const *new_mtime,
             struct timespec const *new_ctime,
             bool check_permissions)
		THROWS(E_FSERROR_DELETED, E_FSERROR_READONLY, E_FSERROR_UNSUPPORTED_OPERATION, ...) {
	struct inode_type *tp_self = self->i_type;
	if (!tp_self->it_attr.a_saveattr)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_WRATTR);
	inode_loadattr_and_check_deleted(self);
	{
		SCOPED_WRITELOCK((struct vm_datablock *)self);
#ifndef CONFIG_EVERYONE_IS_ROOT
		if (check_permissions) {
			/* Permission restrictions:
			 *  - `i_fileuid' must match the caller's fsuid, or the caller must have `CAP_FOWNER' */
			if (self->i_fileuid != cred_getfsuid())
				require(CAP_FOWNER);
			/* KOS-specific: Changing a file's creation timestamp requires special capabilities. */
			if (new_ctime != NULL)
				require(CAP_AT_CHANGE_CTIME);
		}
#else /* !CONFIG_EVERYONE_IS_ROOT */
		(void)check_permissions;
#endif /* CONFIG_EVERYONE_IS_ROOT */
		if (new_atime)
			memcpy(&self->i_fileatime, new_atime, sizeof(struct timespec));
		if (new_mtime)
			memcpy(&self->i_filemtime, new_mtime, sizeof(struct timespec));
		if (new_ctime)
			memcpy(&self->i_filectime, new_ctime, sizeof(struct timespec));
		if (tp_self->it_attr.a_maskattr)
			(*tp_self->it_attr.a_maskattr)(self);
	}
	inode_changed(self, INODE_FATTRCHANGED);
}

/* Change permissions, SUID/SGID and the sticky
 * bit of the given INode (flags mask: 07777)
 * The new file mode is calculated as `(old_mode & perm_mask) | perm_flag',
 * before being masked by what the underlying filesystem is capable of
 * representing.
 * @return: * : The old file mode
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_READONLY: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_ATTRIB: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRATTR: [...] */
PUBLIC NONNULL((1)) mode_t KCALL
inode_chmod(struct inode *__restrict self,
            mode_t perm_mask,
            mode_t perm_flag,
            bool check_permissions)
		THROWS(E_FSERROR_DELETED, E_FSERROR_READONLY,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...) {
	mode_t old_mode;
	bool was_changed           = false;
	struct inode_type *tp_self = self->i_type;
	if (!tp_self->it_attr.a_saveattr)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_WRATTR);
	inode_loadattr_and_check_deleted(self);
	{
		mode_t new_mode;
		SCOPED_WRITELOCK((struct vm_datablock *)self);
#ifndef CONFIG_EVERYONE_IS_ROOT
		if (check_permissions) {
			/* Permission restrictions:
			 *   - `i_fileuid' must match the caller's fsuid, or the caller must have `CAP_FOWNER'
			 *   - If `i_filegid' doesn't relate to the caller, and the caller doesn't
			 *     have `CAP_FSETID', then the `S_ISGID' bit is always turned off.
			 * That is all. - Every user's allowed to set the SETUID bit, since they can only do this
			 * for files they own, and in doing this, only allow programs to impersonate that user!
			 */
			if (self->i_fileuid != cred_getfsuid())
				require(CAP_FOWNER);
			if ((perm_flag & S_ISGID) || (perm_mask & S_ISGID)) {
				/* The Set-gid bit can must be turned off (i.e. cannot be turned on/or left on)
				 * when the caller isn't apart of the group associated with `self->i_filegid' */
				if (!capable(CAP_FSETID) &&
				    !cred_isfsgroupmember(self->i_filegid)) {
					perm_mask &= ~S_ISGID;
					perm_flag &= ~S_ISGID;
				}
			}
		}
#else /* !CONFIG_EVERYONE_IS_ROOT */
		(void)check_permissions;
#endif /* CONFIG_EVERYONE_IS_ROOT */
		old_mode = self->i_filemode & 07777;
		new_mode = ((old_mode & perm_mask) | perm_flag) & 07777;
		assert(!(new_mode & ~07777));
		if (old_mode != new_mode) {
			/* Set the new file mode. */
			ATOMIC_FETCHAND(self->i_filemode, ~07777);
			ATOMIC_FETCHOR(self->i_filemode, new_mode);
			/* Mask unsupported bits if necessary. */
			if (tp_self->it_attr.a_maskattr) {
				(*tp_self->it_attr.a_maskattr)(self);
				if ((self->i_filemode & 07777) != new_mode) {
					ATOMIC_FETCHAND(self->i_filemode, ~07777);
					ATOMIC_FETCHOR(self->i_filemode, old_mode);
					THROW(E_FSERROR_UNSUPPORTED_OPERATION,
					      (uintptr_t)E_FILESYSTEM_OPERATION_ATTRIB);
				}
			}
			was_changed = true;
		}
	}
	if (was_changed)
		inode_changed(self, INODE_FATTRCHANGED);
	return old_mode;
}


/* Change the owner and group of the given file.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_READONLY: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_ATTRIB: [...]
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_WRATTR: [...] */
PUBLIC NONNULL((1)) void KCALL
inode_chown(struct inode *__restrict self,
            uid_t owner, gid_t group,
            uid_t *pold_owner, gid_t *pold_group,
            bool check_permissions)
		THROWS(E_FSERROR_DELETED, E_FSERROR_READONLY,
		       E_FSERROR_UNSUPPORTED_OPERATION, ...) {
	uid_t old_owner;
	gid_t old_group;
	bool was_changed           = false;
	struct inode_type *tp_self = self->i_type;
	if (!tp_self->it_attr.a_saveattr)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_WRATTR);
	inode_loadattr_and_check_deleted(self);
	{
		mode_t new_mode;
		SCOPED_WRITELOCK((struct vm_datablock *)self);
		old_owner = self->i_fileuid;
		old_group = self->i_filegid;
		/* Check for special cases: Don't actually change uid/gid */
		if (owner == (uid_t)-1)
			owner = old_owner;
		if (group == (gid_t)-1)
			group = old_group;
		if (old_owner != owner || old_group != group) {
#ifndef CONFIG_EVERYONE_IS_ROOT
			if (check_permissions) {
				/* Permission restrictions:
				 *   - `owner' must match `old_owner', or the caller needs `CAP_CHOWN'
				 *   - `group' must be apart of the caller's groups, or the caller needs `CAP_CHOWN'
				 */
				if (owner != old_owner)
					require(CAP_CHOWN);
				if (group != old_group && !cred_isfsgroupmember(group))
					require(CAP_CHOWN);
			}
#else /* !CONFIG_EVERYONE_IS_ROOT */
			(void)check_permissions;
#endif /* CONFIG_EVERYONE_IS_ROOT */
			new_mode = self->i_filemode;
			if (new_mode & 0111) {
				/* When changing the owner or group of an executable file,
				 * then the S_ISUID and S_ISGID bits should be cleared.
				 * However, `S_ISGID' is not cleared when `S_IXGRP' isn't set. */
				mode_t mask;
				if (new_mode & S_IXGRP) {
					mask = ~(S_ISUID | S_ISGID);
				} else {
					mask = ~(S_ISUID);
				}
				ATOMIC_FETCHAND(self->i_filemode, mask);
				new_mode &= mask;
			}
			self->i_fileuid = owner;
			self->i_filegid = group;
			if (tp_self->it_attr.a_maskattr) {
				/* Mask unsupported features */
				(*tp_self->it_attr.a_maskattr)(self);
				/* Check if the written attributes were ok. */
				if (self->i_fileuid != owner ||
				    self->i_filegid != group ||
				    self->i_filemode != new_mode) {
					self->i_fileuid = old_owner;
					self->i_filegid = old_group;
					THROW(E_FSERROR_UNSUPPORTED_OPERATION,
					      (uintptr_t)E_FILESYSTEM_OPERATION_ATTRIB);
				}
			}
			was_changed = true;
		}
	}
	if (was_changed)
		inode_changed(self, INODE_FATTRCHANGED);
	/* If requested, return the old owner and group to the caller. */
	if (pold_owner)
		*pold_owner = old_owner;
	if (pold_group)
		*pold_group = old_group;
}




PRIVATE NONNULL((1)) void KCALL
inode_do_sync_attr(struct inode *__restrict self) {
	assert(self->i_type->it_attr.a_saveattr);
	(*self->i_type->it_attr.a_saveattr)(self);
}



/* @param: partrelative_pageno: In data-pages, the part-relative offset to the first modified data-page.
 * @param: num_data_pages:      In data-pages, the number of continuous, modified data-pages. */
INTDEF NONNULL((1, 2)) void KCALL
inode_do_save_datapart_pages(struct inode *__restrict self,
                             struct vm_datapart *__restrict part,
                             size_t partrelative_pageno,
                             size_t num_data_pages,
                             struct aio_multihandle *__restrict aio);




#define INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_FAILED   0 /* Failed to acquire a non-blocking lock to the associated superblock's `s_changed_lock' chain */
#define INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_REMOVED  1 /* Succeeded in removing `self' from the superblock's chain of changed nodes (the caller has inherited a reference to `self') */
#define INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_NOTFOUND 2 /* `self' could not be found as part of the chain of changed nodes. */
PRIVATE NOBLOCK unsigned int
NOTHROW(KCALL inode_try_remove_from_superblock_changed)(struct inode *__restrict self) {
	struct inode **piter, *first, *last;
	struct superblock *super = self->i_super;
	unsigned int result;
	/* Everything that had been changed about the node will be getting synced.
	 * We must therefor remove the node from the changed list.
	 * NOTE: This must be done now, with the node getting re-added if syncing
	 *       fails, because the process of removing the node from the changed
	 *       list is able to cause an E_WOULDBLOCK exception to be thrown. */
	if (!sync_trywrite(&super->s_changed_lock))
		return INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_FAILED;
	result = INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_NOTFOUND;
	/* NOTE: There is a change that we may not find ourself apart of the changed
	 *       list. - This can happen when the superblock itself is also performing
	 *       a synchronization pass at the moment, in which case we don't actually
	 *       need to do anything, though should still perform the sync beforehand,
	 *       just so we don't return normally before the sync is actually done. */
	first = ATOMIC_XCH(super->s_changed, NULL);
	piter = &first;
	while ((last = *piter) != NULL) {
		if (last == self) {
			*piter = self->i_changed_next; /* Unlink. */
			/* Remember that we unlinked ourself in case the sync
			 * fails and we have to re-add ourself as changed. */
			result = INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_REMOVED;
#ifndef NDEBUG
			memset(&self->i_changed_next, 0xcc, sizeof(void *));
#endif
			break;
		}
		piter = &last->i_changed_next;
	}
	while ((last = *piter) != NULL)
		piter = &last->i_changed_next;
	assert((piter == &first) == (first == NULL));
	if (first) {
		/* Re-add all other nodes to the chain of changed nodes. */
		struct inode *next;
		last = COMPILER_CONTAINER_OF(piter, struct inode, i_changed_next);
		do {
			next = ATOMIC_READ(super->s_changed);
			last->i_changed_next = next;
		} while (!ATOMIC_CMPXCH_WEAK(super->s_changed, next, last));
	}
	sync_endwrite(&super->s_changed_lock);
	return result;
}


/* Synchronize data of the given INode and attributes.
 * NOTE: This function is allowed to be called after a node has been
 *       deleted, though only if
 * @param: what: Set of `INODE_FCHANGED|INODE_FATTRCHANGED',
 *               of which at least one must be given.
 * @return: * :  Set of `INODE_FCHANGED|INODE_FATTRCHANGED' describing what was actually synced
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_IOERROR: Failed to read/write data to/from disk. */
PUBLIC NONNULL((1)) uintptr_t KCALL
inode_sync(struct inode *__restrict self, uintptr_t what)
		THROWS(E_FSERROR_DELETED, E_IOERROR, ...) {
	uintptr_t modified;
	bool first_pass = true;
	assert(!(what & ~(INODE_FCHANGED | INODE_FATTRCHANGED)));
again:
	sync_write(self);
	modified = ATOMIC_READ(self->i_flags);
	/* Check if the node has been deleted. */
	if unlikely(modified & INODE_FDELETED) {
		struct superblock *super = self->i_super;
		if (modified & (INODE_FCHANGED | INODE_FATTRCHANGED)) {
			unsigned int error;
again_do_remove_from_super_for_delete:
			error = inode_try_remove_from_superblock_changed(self);
			if unlikely(error == INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_FAILED) {
				sync_endwrite(self);
				sync_write(&super->s_changed_lock);
				sync_endwrite(&super->s_changed_lock);
				sync_write(self);
				if (ATOMIC_READ(self->i_flags) & (INODE_FCHANGED | INODE_FATTRCHANGED))
					goto again_do_remove_from_super_for_delete;
			}
			if (error == INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_REMOVED)
				decref_nokill(self);
		}
		/* Actually unlink the INode. */
		if (superblock_nodeslock_trywrite(super)) {
			struct inode *delnode;
			delnode = inode_tree_remove(&super->s_nodes, self->i_fileino);
			if (unlikely(delnode != self) && delnode)
				inode_tree_insert(&super->s_nodes, delnode);
			superblock_nodeslock_endwrite(super);
			if (delnode == self && (self->i_flags & INODE_FPERSISTENT))
				decref_nokill(self); /* The reference previously stored in the file tree. */
		} else {
			struct inode *next;
			incref(self); /* The reference stored in the `s_unlinknodes' chain. */
			do {
				next = ATOMIC_READ(super->s_unlinknodes);
				self->i_changed_next = next;
			} while (!ATOMIC_CMPXCH_WEAK(super->s_unlinknodes, next, self));
			superblock_nodeslock_tryservice(super);
		}
		goto done;
	}
	/* Check what has actually changed. */
	modified = modified & what;
	/* Check if this isn't simply a no-op */
	if (!modified) {
		sync_endwrite(self);
		return 0;
	}
	if (modified & INODE_FCHANGED) {
		/* Check for further modifications only starting with the second pass! */
		if (!first_pass && !vm_datablock_haschanged(self))
			goto done_data_sync;
		sync_endwrite(self);
		/* Synchronize data. */
		vm_datablock_sync(self);
		first_pass = false;
		goto again;
	}
done_data_sync:
	if (what & INODE_FATTRCHANGED) {
		TRY {
			inode_do_sync_attr(self);
		} EXCEPT {
			sync_endwrite(self);
			RETHROW();
		}
	}
	if (!(ATOMIC_FETCHAND(self->i_flags, ~modified) & (INODE_FCHANGED | INODE_FATTRCHANGED))) {
		/* No more changes (remove the node from the superblock's changed list) */
		unsigned int error;
again_do_remove_from_super:
		error = inode_try_remove_from_superblock_changed(self);
		if unlikely(error == INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_FAILED) {
			/* Failed to remove the INode. - Must blocking-lock the superblock,
			 * then try to acquire a lock to the INode once again in order to
			 * re-check that the node still hasn't been modified. */
			sync_endwrite(self);
			sync_write(&self->i_super->s_changed_lock);
			sync_endwrite(&self->i_super->s_changed_lock);
			sync_write(self);
			if (!(ATOMIC_READ(self->i_flags) & (INODE_FCHANGED | INODE_FATTRCHANGED)))
				goto again_do_remove_from_super; /* The node is still unchanged */
			/* The node has once again changed in the mean time... (just
			 * leave it as part of the superblock's chain of changed nodes) */
		}
		if (error == INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_REMOVED)
			decref_nokill(self);
	}
done:
	sync_endwrite(self);
	return modified;
}



/* Ensure that the given symbolic-link INode has been loaded.
 * This function is a no-op when `self->sl_text != NULL' upon entry,
 * and guaranties that `self->sl_text' will be non-NULL upon success.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_BADALLOC: [...]
 * @throw: E_IOERROR:  [...]
 * @return: true:  The symlink text is now loaded.
 * @return: false: The INode uses the dynamic symlink interface,
 *                 meaning the caller must invoke the `sl_readlink_dynamic'
 *                 operator with their own buffer. */
PUBLIC NONNULL((1)) bool KCALL
symlink_node_load(struct symlink_node *__restrict self)
		THROWS(E_FSERROR_DELETED, E_BADALLOC, E_IOERROR, ...) {
	assert(INODE_ISLNK(self));
	/* Check if the symbolic link has already been loaded. */
	if (self->sl_text == NULL) {
		assert(self->i_type->it_symlink.sl_readlink ||
		       self->i_type->it_symlink.sl_readlink_dynamic);
		if (!self->i_type->it_symlink.sl_readlink)
			return false; /* Dynamic, symbolic link. */
		inode_loadattr_and_check_deleted(self);
		SCOPED_WRITELOCK((struct vm_datablock *)self);
		COMPILER_READ_BARRIER();
		if likely(self->sl_text == NULL) {
			(*self->i_type->it_symlink.sl_readlink)(self);
			assertf(self->sl_text != NULL,
			        "`sl_readlink' should have filled in this field");
		}
	}
	return true;
}


/* Wrapper around `symlink_node_load()' for reading the text of a symbolic
 * link into a user-supplied user-space buffer, whilst returning the number
 * of required bytes of memory (EXCLUDING a trailing NUL-character, which
 * this function will _NOT_ append to the supplied buffer!) */
PUBLIC NONNULL((1)) size_t KCALL
symlink_node_readlink(struct symlink_node *__restrict self,
                      USER CHECKED char *buf, size_t buflen)
		THROWS(E_FSERROR_DELETED, E_BADALLOC, E_IOERROR, E_SEGFAULT, ...) {
	size_t result;
	if (symlink_node_load(self)) {
		/* Copy from the static link buffer. */
		result = (size_t)self->i_filesize;
		memcpy(buf, self->sl_text, MIN(result, buflen), sizeof(char));
	} else {
		/* Use the static interface */
		result = (*self->i_type->it_symlink.sl_readlink_dynamic)(self,
		                                                         buf,
		                                                         buflen);
	}
	return result;
}






PRIVATE NONNULL((1)) void
NOTHROW(KCALL directory_rehash_nx)(struct directory_node *__restrict self) {
	REF struct directory_entry **new_map;
	REF struct directory_entry *iter, *next;
	size_t i, new_mask;
	assert(sync_writing(self));
	new_mask = (self->d_mask << 1) | 1;
	/* Allocate the new directory map. */
	new_map = (REF struct directory_entry **)kmalloc_nx((new_mask + 1) *
	                                                    sizeof(REF struct directory_entry *),
	                                                    FS_GFP | GFP_CALLOC);
	if unlikely(!new_map)
		return; /* Ignore failure to allocate a larger map. */
	/* Rehash all the entries. */
	assert(self->d_map);
	for (i = 0; i <= self->d_mask; ++i) {
		iter = self->d_map[i];
		while (iter) {
			next = iter->de_next;
			/* Insert the entry into the new map. */
			iter->de_next                     = new_map[iter->de_hash & new_mask];
			new_map[iter->de_hash & new_mask] = iter;
			iter                              = next;
		}
	}
	/* Free the old map and setup the new mask. */
	kfree(self->d_map);
	self->d_map  = new_map;
	self->d_mask = new_mask;
}

PRIVATE NONNULL((1)) void
NOTHROW(KCALL directory_rehash_smaller_nx)(struct directory_node *__restrict self) {
	REF struct directory_entry **new_map;
	REF struct directory_entry *iter, *next;
	size_t i, new_mask;
	assert(sync_writing(self));
	new_mask = (self->d_mask >> 1);
	/* Allocate the new directory map. */
	new_map = (REF struct directory_entry **)kmalloc_nx((new_mask + 1) *
	                                                    sizeof(REF struct directory_entry *),
	                                                    FS_GFP | GFP_ATOMIC | GFP_CALLOC);
	if unlikely(!new_map)
		return; /* Ignore failure to allocate a smaller map. */
	/* Rehash all the entries. */
	assert(self->d_map);
	for (i = 0; i <= self->d_mask; ++i) {
		iter = self->d_map[i];
		while (iter) {
			next = iter->de_next;
			/* Insert the entry into the new map. */
			iter->de_next                     = new_map[iter->de_hash & new_mask];
			new_map[iter->de_hash & new_mask] = iter;
			iter                              = next;
		}
	}
	/* Free the old map and setup the new mask. */
	kfree(self->d_map);
	self->d_map  = new_map;
	self->d_mask = new_mask;
}



/* Read the next directory entry from `self' that hasn't been loaded, yet.
 * Return NULL and set the `INODE_FDIRLOADED' flag once the entirety of
 * the directory has been loaded.
 * NOTE: The caller must be holding a read-lock on `self'.
 * @assume(sync_reading(self));
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
PUBLIC WUNUSED NONNULL((1)) struct directory_entry **KCALL
directory_readnext_p(struct directory_node *__restrict self)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry **presult;
	struct directory_entry *result;
	pos_t last_directory_position;
#ifndef NDEBUG
	pos_t entry_start_position;
#endif
	assert(sync_reading(self));
	/* Quick check: has the directory been fully loaded. */
	if (self->i_flags & INODE_FDIRLOADED)
		return NULL;
	/* Make sure that we've got a readdir() operator to work with. */
	if unlikely(!self->i_type->it_directory.d_readdir) {
set_unimplemented:
		ATOMIC_FETCHOR(self->i_flags, INODE_FDIRLOADED);
		return NULL;
	}
continue_reading:
	/* Read more entires. */
	last_directory_position = self->d_dirend;
#ifndef NDEBUG
	entry_start_position = last_directory_position;
#endif
	TRY {
		result = (*self->i_type->it_directory.d_readdir)(self, &last_directory_position);
	} EXCEPT {
		error_code_t code = error_code();
		if (code == ERROR_CODEOF(E_IOERROR_BADBOUNDS)) {
			/* Catch E_IOERROR_BADBOUNDS and handle it as end-of-directory. */
			result = NULL;
		} else if (code == E_FSERROR_UNSUPPORTED_OPERATION &&
		           PERTASK_GET(this_exception_pointers[0]) == E_FILESYSTEM_OPERATION_READDIR) {
			goto set_unimplemented;
		} else {
			RETHROW();
		}
	}
	if (!result) {
		/* End of directory. (Set the flag for that) */
		SCOPED_WRITELOCK((struct vm_datablock *)self);
		ATOMIC_FETCHOR(self->i_flags, INODE_FDIRLOADED);
		return NULL;
	}
	assert(result->de_namelen != 0);
	assert(result->de_hash == directory_entry_hash(result->de_name, result->de_namelen));
	assertf(!memchr(result->de_name, 0, result->de_namelen),
	        "%$[hex]", (size_t)result->de_namelen, result->de_name);
	TRY {
		SCOPED_WRITELOCK((struct vm_datablock *)self);
#ifndef NDEBUG
		/* `rwlock_write()' will have thrown an error if it didn't
		 *  manage to upgrade the associated R/W-lock atomically.
		 *  That error will be propagated until the point where
		 *  the caller originally acquired the first read-lock
		 *  to the node, which will be released, then re-acquired,
		 *  before we try this whole thing again.
		 *  In other words: If we get here, we should be able to
		 *                  assume that the `rwlock_write()' above
		 *                  didn't temporarily grant other threads
		 *                  write-access to the `d_dirend' field. */
		assert(self->d_dirend == entry_start_position);
		assert(result->de_pos >= entry_start_position &&
		       result->de_pos < last_directory_position);
#endif
		/* Set the partially-loaded flag and the directory
		 * end pointer up to which data has now been loaded. */
		self->d_dirend = last_directory_position;
		if (!self->d_bypos_end) {
			assert(!self->d_bypos);
			self->d_bypos             = result;
			self->d_bypos_end         = result;
			result->de_bypos.ln_pself = &self->d_bypos;
			result->de_bypos.ln_next  = NULL;
		} else if (result->de_pos < self->d_bypos_end->de_pos) {
			struct directory_entry *insert_after;
			/* When the directory is being re-loaded after a umount(),
			 * an older entry for this directory entry may still exist,
			 * or we just have to insert the new entry somewhere else. */
			insert_after = self->d_bypos_end;
			do
				insert_after = COMPILER_CONTAINER_OF(insert_after->de_bypos.ln_pself,
				                                     struct directory_entry, de_bypos.ln_next);
			while (insert_after->de_pos > result->de_pos);
			/* Check if the entry already exists! */
			if (insert_after->de_pos == result->de_pos)
				goto unlock_write_and_continue_reading;
			/* Insert the new entry. */
			LLIST_INSERT_AFTER(insert_after, result, de_bypos);
		} else {
			/* Add the directory entry to the by-position chain of directory entries. */
			result->de_bypos.ln_pself           = &self->d_bypos_end->de_bypos.ln_next;
			self->d_bypos_end->de_bypos.ln_next = result;
			result->de_bypos.ln_next            = NULL;
			self->d_bypos_end                   = result;
		}
		/* Add the new entry to the hash-map. */
		assert(self->d_map);
		presult         = &self->d_map[result->de_hash & self->d_mask];
		result->de_next = *presult; /* Inherit reference. */
		*presult        = result;   /* Inherit reference. */
		++self->d_size;
		/* Add the directory entry to the hash-map. */
		if (self->d_size >= (self->d_mask / 3) * 2) {
			struct directory_entry *ent;
			assert(self->d_mask != 0);
			/* Try to re-hash the directory. */
			directory_rehash_nx(self);
			/* Must re-discover the result self-pointer. */
			presult = &self->d_map[result->de_hash & self->d_mask];
			for (;;) {
				ent = *presult;
				assert(ent);
				if (ent == result)
					break;
				presult = &ent->de_next;
			}
		}
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	assert(sync_reading(self));
	return presult;
unlock_write_and_continue_reading:
	decref(result); /* Drop the reference previously returned by the READDIR() callback. */
	goto continue_reading;
}


PUBLIC NONNULL((1)) struct directory_entry *KCALL
directory_readnext(struct directory_node *__restrict self)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry *result;
	pos_t last_directory_position;
#ifndef NDEBUG
	pos_t entry_start_position;
#endif
	assert(sync_reading(self));
	/* Quick check: has the directory been fully loaded. */
	if (self->i_flags & INODE_FDIRLOADED)
		return NULL;
	/* Make sure that we've got a readdir() operator to work with. */
	if unlikely(!self->i_type->it_directory.d_readdir) {
set_unimplemented:
		ATOMIC_FETCHOR(self->i_flags, INODE_FDIRLOADED);
		return NULL;
	}
continue_reading:
	/* Read more entires. */
	last_directory_position = self->d_dirend;
#ifndef NDEBUG
	entry_start_position = last_directory_position;
#endif
	TRY {
		result = (*self->i_type->it_directory.d_readdir)(self, &last_directory_position);
	} EXCEPT {
		error_code_t code = error_code();
		if (code == ERROR_CODEOF(E_IOERROR_BADBOUNDS)) {
			/* Catch E_IOERROR_BADBOUNDS and handle it as end-of-directory. */
			result = NULL;
		} else if (code == E_FSERROR_UNSUPPORTED_OPERATION &&
		           PERTASK_GET(this_exception_pointers[0]) == E_FILESYSTEM_OPERATION_READDIR) {
			goto set_unimplemented;
		} else {
			RETHROW();
		}
	}
	if (!result) {
		/* End of directory. (Set the flag for that) */
		SCOPED_WRITELOCK((struct vm_datablock *)self);
		ATOMIC_FETCHOR(self->i_flags, INODE_FDIRLOADED);
		return NULL;
	}
	assert(result->de_namelen != 0);
	assert(result->de_hash == directory_entry_hash(result->de_name, result->de_namelen));
	assertf(!memchr(result->de_name, 0, result->de_namelen),
	        "%$[hex]", (size_t)result->de_namelen, result->de_name);
	TRY {
		struct directory_entry **presult;
		SCOPED_WRITELOCK((struct vm_datablock *)self);
#ifndef NDEBUG
		/* `rwlock_write()' will have thrown an error if it didn't
		 *  manage to upgrade the associated R/W-lock atomically.
		 *  That error will be propagated until the point where
		 *  the caller originally acquired the first read-lock
		 *  to the node, which will be released, then re-acquired,
		 *  before we try this whole thing again.
		 *  In other words: If we get here, we should be able to
		 *                  assume that the `rwlock_write()' above
		 *                  didn't temporarily grant other threads
		 *                  write-access to the `d_dirend' field. */
		assert(self->d_dirend == entry_start_position);
		assert(result->de_pos >= entry_start_position &&
		       result->de_pos < last_directory_position);
#endif
		/* Set the partially-loaded flag and the directory
		 * end pointer up to which data has now been loaded. */
		self->d_dirend = last_directory_position;
		if (!self->d_bypos_end) {
			assert(!self->d_bypos);
			self->d_bypos             = result;
			self->d_bypos_end         = result;
			result->de_bypos.ln_pself = &self->d_bypos;
			result->de_bypos.ln_next  = NULL;
		} else if (result->de_pos < self->d_bypos_end->de_pos) {
			struct directory_entry *insert_after;
			/* When the directory is being re-loaded after a umount(),
			 * an older entry for this directory entry may still exist,
			 * or we just have to insert the new entry somewhere else. */
			insert_after = self->d_bypos_end;
			do {
				insert_after = COMPILER_CONTAINER_OF(insert_after->de_bypos.ln_pself,
				                                     struct directory_entry, de_bypos.ln_next);
			} while (insert_after->de_pos > result->de_pos);
			/* Check if the entry already exists! */
			if (insert_after->de_pos == result->de_pos)
				goto unlock_write_and_continue_reading;
			/* Insert the new entry. */
			LLIST_INSERT_AFTER(insert_after, result, de_bypos);
		} else {
			/* Add the directory entry to the by-position chain of directory entries. */
			result->de_bypos.ln_pself           = &self->d_bypos_end->de_bypos.ln_next;
			self->d_bypos_end->de_bypos.ln_next = result;
			result->de_bypos.ln_next            = NULL;
			self->d_bypos_end                   = result;
		}
		/* Add the new entry to the hash-map. */
		assert(self->d_map);
		presult         = &self->d_map[result->de_hash & self->d_mask];
		result->de_next = *presult; /* Inherit reference. */
		*presult        = result;   /* Inherit reference. */
		++self->d_size;
		/* Add the directory entry to the hash-map. */
		if (self->d_size >= (self->d_mask / 3) * 2) {
			assert(self->d_mask != 0);
			/* Try to re-hash the directory. */
			directory_rehash_nx(self);
		}
	} EXCEPT {
		decref(result);
		RETHROW();
	}
	assert(sync_reading(self));
	return result;
unlock_write_and_continue_reading:
	decref(result); /* Drop the reference previously returned by the READDIR() callback. */
	goto continue_reading;
}




/* Lookup a directory item, given its name.
 * NOTE: The caller must be holding a read-lock on `self'
 * @assume(sync_reading(self));
 * @return: * :   A reference to the associated INode.
 * @return: NULL: No INode with the given `name' exists.
 *              (`E_FSERROR_(FILE|PATH)_NOT_FOUND'-style)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_SEGFAULT: Failed to access the given `name'.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
PUBLIC WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getentry(struct directory_node *__restrict self,
                   CHECKED USER /*utf-8*/ char const *name,
                   u16 namelen, uintptr_t hash)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry *result;
	assert(sync_reading(self));
	assert(self->d_mask != 0); /* TODO: This fails after all files in a directory were deleted! */
	if (self->i_type->it_directory.d_oneshot.o_lookup) {
		TRY {
			return (*self->i_type->it_directory.d_oneshot.o_lookup)(self,
			                                                        name,
			                                                        namelen,
			                                                        hash,
			                                                        FS_MODE_FNORMAL);
		} EXCEPT {
			error_code_t code = error_code();
			if (code == ERROR_CODEOF(E_FSERROR_FILE_NOT_FOUND))
				return NULL;
			if (code != ERROR_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION) ||
			    PERTASK_GET(this_exception_pointers[0]) != E_FILESYSTEM_OPERATION_READDIR)
				RETHROW();
		}
	}
	if unlikely(!self->d_size)
		goto read_directory;
	assert(self->d_map);
	result = self->d_map[hash & self->d_mask];
	for (; result; result = result->de_next) {
		assert(result->de_hash == directory_entry_hash(result->de_name, result->de_namelen));
		assert((result->de_hash & self->d_mask) == (hash & self->d_mask));
		/* Check hash and name-length. */
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		return incref(result);
	}
	/* Read more directory entries. */
read_directory:
	while ((result = directory_readnext(self)) != NULL) {
		assert(result->de_hash == directory_entry_hash(result->de_name, result->de_namelen));
		/* Check if this is the one. */
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		incref(result);
		break;
	}
	return result;
}


PUBLIC WUNUSED NONNULL((1)) REF struct directory_entry *KCALL
directory_getcaseentry(struct directory_node *__restrict self,
                       CHECKED USER /*utf-8*/ char const *name,
                       u16 namelen, uintptr_t hash)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry *result;
	assert(sync_reading(self));
	assert(self->d_mask != 0);
	if (self->i_type->it_directory.d_oneshot.o_lookup) {
		TRY {
			return (*self->i_type->it_directory.d_oneshot.o_lookup)(self,
			                                                        name,
			                                                        namelen,
			                                                        hash,
			                                                        FS_MODE_FDOSPATH);
		} EXCEPT {
			error_code_t code = error_code();
			if (code == ERROR_CODEOF(E_FSERROR_FILE_NOT_FOUND))
				return NULL;
			if (code != ERROR_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION) ||
			    PERTASK_GET(this_exception_pointers[0]) != E_FILESYSTEM_OPERATION_READDIR)
				RETHROW();
		}
	}
	if unlikely(!self->d_size)
		goto read_directory;
	assert(self->d_map);
	result = self->d_map[hash & self->d_mask];
	for (; result; result = result->de_next) {
		/* Check hash and name-length. */
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		return incref(result);
	}
	/* Search the entirety of the directory's hash-table. */
	{
		size_t i;
		for (i = 0; i <= self->d_mask; ++i) {
			result = self->d_map[i];
			for (; result; result = result->de_next) {
				if (result->de_namelen != namelen)
					continue;
				if unlikely(memcasecmp(result->de_name, name, namelen * sizeof(char)) != 0)
					continue;
				return incref(result);
			}
		}
	}
	/* Read more directory entries. */
read_directory:
	while ((result = directory_readnext(self)) != NULL) {
		/* Check if this is the one. */
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcasecmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		incref(result);
		break;
	}
	return result;
}


/* Same as the function above, but return the entry's self-pointer within the directory node.
 * @param: poneshot_entry:  A storage location for directories implementing the one-shot interface.
 * @return: poneshot_entry: The directory implements the one-shot interface, and the
 *                          located directory entry has been stored in `*poneshot_entry'.
 * @return: * :   A reference to the associated INode.
 * @return: NULL: No INode with the given `name' exists.
 *              (`E_FSERROR_(FILE|PATH)_NOT_FOUND'-style)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_SEGFAULT: Failed to access the given `name'.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
PUBLIC WUNUSED NONNULL((1, 5)) REF struct directory_entry **KCALL
directory_getentry_p(struct directory_node *__restrict self,
                     CHECKED USER /*utf-8*/ char const *name,
                     u16 namelen, uintptr_t hash,
                     /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry **presult, *result;
	assert(sync_reading(self));
	assert(self->d_mask != 0);
	if (self->i_type->it_directory.d_oneshot.o_lookup) {
		TRY {
			result = (*self->i_type->it_directory.d_oneshot.o_lookup)(self,
			                                                          name,
			                                                          namelen,
			                                                          hash,
			                                                          FS_MODE_FNORMAL);
		} EXCEPT {
			error_code_t code = error_code();
			if (code == ERROR_CODEOF(E_FSERROR_FILE_NOT_FOUND))
				return NULL;
			if (code != ERROR_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION) ||
			    PERTASK_GET(this_exception_pointers[0]) != E_FILESYSTEM_OPERATION_READDIR)
				RETHROW();
			result = NULL;
		}
		if (!result)
			return NULL;
		*poneshot_entry = result; /* Inherit reference. */
		return poneshot_entry;
	}
	if unlikely(!self->d_size)
		goto read_directory;
	assert(self->d_map);
	presult = &self->d_map[hash & self->d_mask];
	for (; (result = *presult) != NULL; presult = &result->de_next) {
		/* Check hash and name-length. */
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		*poneshot_entry = NULL;
		return presult;
	}
	/* Read more directory entries. */
read_directory:
	while ((presult = directory_readnext_p(self)) != NULL) {
		/* Check if this is the one. */
		result = *presult;
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		break;
	}
	*poneshot_entry = NULL;
	return presult;
}

PUBLIC WUNUSED NONNULL((1, 5)) struct directory_entry **KCALL
directory_getcaseentry_p(struct directory_node *__restrict self,
                         CHECKED USER /*utf-8*/ char const *name,
                         u16 namelen, uintptr_t hash,
                         /*out*/ REF struct directory_entry **__restrict poneshot_entry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry **presult, *result;
	assert(sync_reading(self));
	assert(self->d_mask != 0);
	if (self->i_type->it_directory.d_oneshot.o_lookup) {
		TRY {
			result = (*self->i_type->it_directory.d_oneshot.o_lookup)(self,
			                                                          name,
			                                                          namelen,
			                                                          hash,
			                                                          FS_MODE_FDOSPATH);
		} EXCEPT {
			error_code_t code = error_code();
			if (code == ERROR_CODEOF(E_FSERROR_FILE_NOT_FOUND))
				return NULL;
			if (code != ERROR_CODEOF(E_FSERROR_UNSUPPORTED_OPERATION) ||
			    PERTASK_GET(this_exception_pointers[0]) != E_FILESYSTEM_OPERATION_READDIR)
				RETHROW();
			result = NULL;
		}
		if (!result)
			return NULL;
		*poneshot_entry = result; /* Inherit reference. */
		return poneshot_entry;
	}
	if unlikely(!self->d_size)
		goto read_directory;
	assert(self->d_map);
	presult = &self->d_map[hash & self->d_mask];
	for (; (result = *presult) != NULL; presult = &result->de_next) {
		/* Check hash and name-length. */
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		*poneshot_entry = NULL;
		return presult;
	}
	/* Search the entirety of the directory's hash-table. */
	{
		size_t i;
		for (i = 0; i <= self->d_mask; ++i) {
			result = self->d_map[i];
			for (; result; result = result->de_next) {
				if (result->de_namelen != namelen)
					continue;
				if unlikely(memcasecmp(result->de_name, name, namelen * sizeof(char)) != 0)
					continue;
				*poneshot_entry = NULL;
				return presult;
			}
		}
	}
	/* Read more directory entries. */
read_directory:
	while ((presult = directory_readnext_p(self)) != NULL) {
		/* Check if this is the one. */
		result = *presult;
		if (result->de_hash != hash)
			continue;
		if (result->de_namelen != namelen)
			continue;
		/* Highly likely that this is our guy... */
		if unlikely(memcasecmp(result->de_name, name, namelen * sizeof(char)) != 0)
			continue;
		break;
	}
	*poneshot_entry = NULL;
	return presult;
}



/* Same as `directory_getentry()', but automatically dereference
 * the directory entry to retrieve the associated INode.
 * Additionally, the caller isn't required to already be holding
 * a read-lock for the given directory.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_SEGFAULT: Failed to access the given `name'.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_READDIR:
 *                             [...]
 * @throw: E_IOERROR:          [...] */
PUBLIC WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getnode(struct directory_node *__restrict self,
                  CHECKED USER /*utf-8*/ char const *name,
                  u16 namelen, uintptr_t hash,
                  REF struct directory_entry **pentry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry *entry;
	REF struct inode *result;
again:
	rwlock_read(&self->db_lock);
	TRY {
		/* Load a reference to the entry. */
		entry = directory_getentry(self, name, namelen, hash);
	} EXCEPT {
		if (rwlock_endread(&self->db_lock))
			goto again;
		RETHROW();
	}
	rwlock_endread(&self->db_lock);
	if (!entry)
		return NULL;
	TRY {
		result = superblock_opennode(self->i_super, self, entry);
	} EXCEPT {
		decref(entry);
		RETHROW();
	}
	/* Deal with the remaining reference to the directory entry. */
	if (pentry)
		*pentry = entry;
	else {
		decref_unlikely(entry);
	}
	return result;
}

PUBLIC WUNUSED NONNULL((1)) REF struct inode *KCALL
directory_getcasenode(struct directory_node *__restrict self,
                      CHECKED USER /*utf-8*/ char const *name,
                      u16 namelen, uintptr_t hash,
                      REF struct directory_entry **pentry)
		THROWS(E_FSERROR_DELETED, E_SEGFAULT,
		       E_FSERROR_UNSUPPORTED_OPERATION, E_IOERROR, ...) {
	struct directory_entry *entry;
	REF struct inode *result;
again:
	rwlock_read(&self->db_lock);
	TRY {
		/* Load a reference to the entry. */
		entry = directory_getcaseentry(self, name, namelen, hash);
	} EXCEPT {
		if (rwlock_endread(&self->db_lock))
			goto again;
		RETHROW();
	}
	rwlock_endread(&self->db_lock);
	if (!entry)
		return NULL;
	TRY {
		result = superblock_opennode(self->i_super, self, entry);
	} EXCEPT {
		decref(entry);
		RETHROW();
	}
	/* Deal with the remaining reference to the directory entry. */
	if (pentry)
		*pentry = entry;
	else {
		decref_unlikely(entry);
	}
	return result;
}



PRIVATE NONNULL((1, 2)) void
NOTHROW(KCALL directory_addentry)(struct directory_node *__restrict self,
                                  /*in*/ REF struct directory_entry *__restrict entry) {
	struct directory_entry *insert_after;
	struct directory_entry **pdirent;
	assert(entry);

	/* Add the directory entry to the by-position chain of directory entries. */
	assert((self->d_bypos != NULL) ==
	       (self->d_bypos_end != NULL));
	assertf(!self->d_bypos_end || self->d_bypos_end->de_bypos.ln_next == NULL,
	        "self->d_bypos_end->de_bypos.ln_next = %p",
	        self->d_bypos_end->de_bypos.ln_next);
	insert_after = self->d_bypos_end;
	if unlikely(!insert_after) {
		/* Special case: first entry. */
		self->d_bypos            = entry;
		self->d_bypos_end        = entry;
		entry->de_bypos.ln_pself = &self->d_bypos;
		entry->de_bypos.ln_next  = NULL;
	} else if likely(entry->de_pos >= insert_after->de_pos) {
		/* Likely case: Insert at the back */
		assert(!insert_after->de_bypos.ln_next);
		entry->de_bypos.ln_pself       = &insert_after->de_bypos.ln_next;
		entry->de_bypos.ln_next        = NULL;
		insert_after->de_bypos.ln_next = entry;
		self->d_bypos_end              = entry;
	} else if (entry->de_pos < self->d_bypos->de_pos) {
		/* Insert in the front. */
		entry->de_bypos.ln_next  = self->d_bypos;
		entry->de_bypos.ln_pself = &self->d_bypos;
		assert(entry->de_bypos.ln_next->de_bypos.ln_pself == &self->d_bypos);
		entry->de_bypos.ln_next->de_bypos.ln_pself = &entry->de_bypos.ln_next;
		self->d_bypos                              = entry;
	} else {
		/* Find the entry after which we must insert this one. */
		do {
			insert_after = COMPILER_CONTAINER_OF(insert_after->de_bypos.ln_pself,
			                                     struct directory_entry,
			                                     de_bypos.ln_next);
		} while (entry->de_pos < insert_after->de_pos);
		assert(insert_after->de_bypos.ln_next);
		assert(insert_after != self->d_bypos_end);
		/* Insert in-between two other entries. (Can happen if `d_creat' re-uses older slots) */
		entry->de_bypos.ln_pself                   = &insert_after->de_bypos.ln_next;
		entry->de_bypos.ln_next                    = insert_after->de_bypos.ln_next;
		entry->de_bypos.ln_next->de_bypos.ln_pself = &entry->de_bypos.ln_next;
		insert_after->de_bypos.ln_next             = entry;
	}

	/* Add the new entry to the hash-map. */
	assert(self->d_map);
	pdirent        = &self->d_map[entry->de_hash & self->d_mask];
	entry->de_next = *pdirent; /* Inherit reference. */
	*pdirent       = entry;    /* Inherit reference. */

	/* Track the total number of directory entires. */
	++self->d_size;

	if (self->d_size >= (self->d_mask / 3) * 2) {
		assert(self->d_mask != 0);
		directory_rehash_nx(self);
	}
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL directory_delentry_bypos)(struct directory_node *__restrict self,
                                        struct directory_entry *__restrict entry) {
	/* Remove the entry from the by-position chain. */
	if (entry == self->d_bypos_end) {
		if (entry == self->d_bypos) {
			/* Remove the last entry. */
			assert(entry->de_bypos.ln_pself == &self->d_bypos);
			assert(entry->de_bypos.ln_next  == NULL);
			self->d_bypos_end = NULL;
		} else {
			/* Update `d_bypos_end' to point to the previous entry. */
			self->d_bypos_end = LLIST_PREV(struct directory_entry, entry, de_bypos);
		}
	}
	/* Unlink the entry from the parent directory. */
	LLIST_REMOVE(entry, de_bypos);
}

INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL directory_delentry)(struct directory_node *__restrict self,
                                  /*out*/ REF struct directory_entry *__restrict entry) {
	struct directory_entry **pdirent, *iter;
	/* Remove the entry from the by-position chain. */
	directory_delentry_bypos(self, entry);
	/* Add the new entry to the hash-map. */
	assert(self->d_map);
	pdirent = &self->d_map[entry->de_hash & self->d_mask];
	for (;;) {
		iter = *pdirent;
		if (iter == entry)
			break;
		assert(iter != NULL);
		pdirent = &iter->de_next;
	}
	*pdirent = entry->de_next;
	/* Track the total number of directory entires. */
	assert(self->d_size);
	--self->d_size;
	if (self->d_size <= (self->d_mask / 3)) {
		assert(self->d_mask != 0);
		directory_rehash_smaller_nx(self);
	}
#ifndef NDEBUG
	memset(&entry->de_bypos, 0xcc, sizeof(entry->de_bypos));
	memset(&entry->de_next, 0xcc, sizeof(entry->de_next));
#endif /* !NDEBUG */
}





INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL superblock_delete_inode)(struct superblock *__restrict super,
                                       struct inode *__restrict self) {
	uintptr_t old_flags;
	old_flags = ATOMIC_FETCHOR(self->i_flags, INODE_FDELETED);
	if (old_flags & (INODE_FCHANGED | INODE_FATTRCHANGED)) {
		/* The INode is still marked as having changed, so we must try to remove
		 * it from the chain of changed INodes. If we fail to do this, it doesn't
		 * matter:
		 *  - Error:INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_FAILED:
		 *     - The couldn't acquire a lock to the superblock's `s_changed_lock' chain.
		 *       In this case, whoever is holding that lock will see that the `INODE_FDELETED'
		 *       flag has been set when they come around to syncing our now.
		 *  - Error:INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_NOTFOUND:
		 *     - Same as the other error, only that in this case the other thread has already
		 *       consumed the chain of changed INodes, and will see the `INODE_FDELETED' flag
		 *       just as they would have in the other case.
		 */
		unsigned int error;
		error = inode_try_remove_from_superblock_changed(self);
		if (error != INODE_TRY_REMOVE_FROM_SUPERBLOCK_CHANGED_REMOVED)
			return;
		ATOMIC_FETCHAND(self->i_flags, ~(INODE_FCHANGED | INODE_FATTRCHANGED));
		decref_nokill(self); /* The reference contained in the changed-inode list. */
	}
	if (superblock_nodeslock_trywrite(super)) {
		struct inode *delnode;
		delnode = inode_tree_remove(&super->s_nodes, self->i_fileino);
		if (unlikely(delnode != self) && delnode)
			inode_tree_insert(&super->s_nodes, delnode);
		superblock_nodeslock_endwrite(super);
		if (delnode == self && (self->i_flags & INODE_FPERSISTENT))
			decref_nokill(self); /* The reference previously stored in the file tree. */
	} else {
		struct inode *next;
		incref(self); /* The reference stored in the `s_unlinknodes' chain. */
		do {
			next = ATOMIC_READ(super->s_unlinknodes);
			self->i_changed_next = next;
		} while (!ATOMIC_CMPXCH_WEAK(super->s_unlinknodes, next, self));
		superblock_nodeslock_tryservice(super);
	}
}

#undef path
INTDEF NOBLOCK void
NOTHROW(KCALL path_rehash_smaller_nx)(struct path *__restrict self);


LOCAL NOBLOCK void
NOTHROW(KCALL remove_dirent_from_directory)(struct directory_node *__restrict self,
                                            struct directory_entry *__restrict entry) {
	assert(self->d_size >= 1);
	assert((self->d_bypos != NULL) == (self->d_bypos_end != NULL));
	/* Remove the entry from the by-position chain. */
	directory_delentry_bypos(self, entry);
	/* Update the directory entry counter. */
	--self->d_size;
	/* Do some integrity checks. */
	assert((self->d_bypos != NULL) == (self->d_bypos_end != NULL));
	assert((self->d_bypos != NULL) == (self->d_size != 0));
	/* Rehash the containing directory if the chance to do so comes up. */
	if (self->d_size <= (self->d_mask / 3)) {
		assert(self->d_mask != 0);
		directory_rehash_smaller_nx(self);
	}
}


/* Remove an entry from this directory.
 * @param: mode: Set of `DIRECTORY_REMOVE_F*', or which at least one of
 *              `DIRECTORY_REMOVE_FREGULAR' or `DIRECTORY_REMOVE_FDIRECTORY'
 *               must be given.
 * @param: premoved_inode:  Upon success, store a reference to the removed INode here.
 * @param: premoved_dirent: Upon success, store a reference to the removed INode's directory entry here.
 * @param: containing_path: When non-NULL, try to remove a child directory from this path node upon success.
 *
 * @param: premoved_path:   When non-NULL, store the child directory removed from `containing_path' here, otherwise set to `NULL'.
 * @return: * : Set of `DIRECTORY_REMOVE_STATUS_*'
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified file was already deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (self was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_FILE_NOT_FOUND:      The specified `name' could not be found
 * @throw: E_FSERROR_ACCESS_DENIED:       `DIRECTORY_REMOVE_FCHKACCESS' was set, and the calling thread is not allowed to delete the file.
 * @throw: E_FSERROR_NOT_A_DIRECTORY:E_FILESYSTEM_NOT_A_DIRECTORY_RMDIR:  The given `name' refers to a regular file, but `DIRECTORY_REMOVE_FREGULAR' isn't set
 * @throw: E_FSERROR_IS_A_DIRECTORY:E_FILESYSTEM_IS_A_DIRECTORY_UNLINK:   The given `name' refers to a directory, but `DIRECTORY_REMOVE_FDIRECTORY' isn't set
 * @throw: E_FSERROR_IS_A_MOUNTING_POINT:                                 The given `name' refers to a mounting point when a child directory is being removed, and `containing_path' is given
 * @throw: E_FSERROR_DIRECTORY_NOT_EMPTY:                                 Attempted to remove a non-empty directory.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_UNLINK: Cannot unlink files within `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RMDIR:  Cannot remove sub-directories of `self'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_TRUNC:  Cannot truncate non-empty files to 0 bytes in order to delete their data
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
#undef path
PUBLIC NONNULL((1, 2)) unsigned int KCALL
directory_remove(struct directory_node *__restrict self,
                 CHECKED USER /*utf-8*/ char const *__restrict name,
                 u16 namelen, uintptr_t hash, unsigned int mode,
                 /*out*/ REF struct inode **premoved_inode,
                 /*out*/ REF struct directory_entry **premoved_dirent,
                 struct path *containing_path,
                 /*out*/ REF struct path **premoved_path)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_DIRECTORY_MOVE_TO_CHILD, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_IS_A_MOUNTING_POINT, E_FSERROR_READONLY,
		       E_IOERROR, E_SEGFAULT, ...) {
	struct directory_entry **pentry, *entry;
	REF struct directory_entry *oneshot_entry; /* [0..1] */
	REF struct inode *node;
	REF struct path *removed_path;
	unsigned int result;
	if (premoved_path)
		*premoved_path = NULL;
again:
	rwlock_read(&self->db_lock);
	TRY {
		inode_check_deleted(self, E_FILESYSTEM_DELETED_PATH);
		pentry = (mode & DIRECTORY_REMOVE_FNOCASE) ? directory_getcaseentry_p(self, name, namelen, hash, &oneshot_entry)
		                                           : directory_getentry_p(self, name, namelen, hash, &oneshot_entry);
		if unlikely(!pentry)
			THROW(E_FSERROR_FILE_NOT_FOUND);
		TRY {
			entry = *pentry;
			node  = superblock_opennode(self->i_super, self, entry);
			TRY {
				/* Make sure to load attributes associated with the INode. */
				inode_loadattr(node);
				assert(node->i_filenlink != 0);
				assert(node->i_super == self->i_super);
				/* In order to allow for file deletion, the caller needs
				 * write-access to the containing directory node. */
				if (mode & DIRECTORY_REMOVE_FCHKACCESS)
					inode_access(self, W_OK);
				if (INODE_ISDIR(node)) {
					struct directory_node *dir;
					if (!(mode & DIRECTORY_REMOVE_FDIRECTORY))
						THROW(E_FSERROR_IS_A_DIRECTORY, (uintptr_t)E_FILESYSTEM_IS_A_DIRECTORY_UNLINK);
					dir = (struct directory_node *)node;
					if (dir->d_size != 0)
						THROW(E_FSERROR_DIRECTORY_NOT_EMPTY);
					/* If the directory hasn't been fully loaded,
					 * read one entry to check that it's really empty. */
					if (!(ATOMIC_READ(dir->i_flags) & INODE_FDIRLOADED)) {
						if unlikely(!sync_trywrite(dir))
							goto unlock_directory_and_start_again;
						FINALLY_ENDWRITE((struct vm_datablock *)dir);
						if (!(ATOMIC_READ(dir->i_flags) & INODE_FDIRLOADED) &&
						    directory_readnext(dir) != NULL)
							THROW(E_FSERROR_DIRECTORY_NOT_EMPTY);
					}
					/* The directory is empty except for its self and parent index.
					 * Now to unlink it. */
					if unlikely(!sync_trywrite(dir))
						goto unlock_directory_and_start_again;
					if unlikely(!sync_trywrite(self)) {
						sync_endwrite(dir);
						sync_write(self);
						sync_endwrite(self);
						goto unlock_directory_and_start_again;
					}
					removed_path = NULL;
					if (containing_path) {
						if unlikely(!sync_trywrite(containing_path)) {
							sync_endwrite(self);
							sync_endwrite(dir);
							sync_write(containing_path);
							sync_endwrite(containing_path);
							goto unlock_directory_and_start_again;
						}
						/* Check if the containing path has been re-mounted. */
						if unlikely(containing_path->p_inode != self &&
						            (mode & DIRECTORY_REMOVE_FCHKPMOUNT)) {
							sync_endwrite(containing_path);
							sync_endwrite(self);
							sync_endwrite(dir);
							return DIRECTORY_REMOVE_STATUS_REMOUNT;
						}
						/* Check to make sure that the element being removed isn't a mounting point! */
						if (containing_path->p_cldlist) {
							removed_path = containing_path->p_cldlist[entry->de_hash & containing_path->p_cldmask];
							for (; removed_path; removed_path = removed_path->p_dirnext.ln_next) {
								if (removed_path->p_dirent != entry)
									continue;
								if unlikely(!sync_trywrite(removed_path)) {
									incref(removed_path);
									sync_endwrite(containing_path);
									sync_endwrite(self);
									sync_endwrite(dir);
									goto wait_for_removed_path;
								}
								if unlikely(removed_path->p_mount != NULL) {
									/* Cannot remove mounting points. */
									sync_endwrite(removed_path);
									sync_endwrite(containing_path);
									sync_endwrite(self);
									sync_endwrite(dir);
									THROW(E_FSERROR_IS_A_MOUNTING_POINT);
								}
								break;
							}
						}
					}
					/* All locks have been upgraded/acquired */
					FINALLY_ENDWRITE((struct vm_datablock *)self);
					FINALLY_ENDWRITE((struct vm_datablock *)dir);
					TRY {
						result = DIRECTORY_REMOVE_STATUS_RMDIR;
						if (dir->i_filenlink == (nlink_t)1) {
							vm_datablock_anonymize(self);
							TRY {
								/* Use the rmdir() operator. */
								if unlikely(!self->i_type->it_directory.d_rmdir)
									THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_RMDIR);
								(*self->i_type->it_directory.d_rmdir)(self, entry, dir);
							} EXCEPT {
								vm_datablock_deanonymize(self);
								RETHROW();
							}
							assert(dir->i_filenlink == 0);
							/* Mark the INode as having been deleted. */
							superblock_delete_inode(self->i_super, dir);
							result |= DIRECTORY_REMOVE_STATUS_FDELETED;
						} else {
							/* Use the unlink() operator. */
							if unlikely(!self->i_type->it_directory.d_unlink)
								THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_UNLINK);
							(*self->i_type->it_directory.d_unlink)(self, entry, (struct inode *)dir);
						}
					} EXCEPT {
						if (containing_path) {
							if (removed_path)
								sync_endwrite(removed_path);
							sync_endwrite(containing_path);
						}
						RETHROW();
					}
					if (containing_path) {
						/* Also try to remove the entry from the containing path. */
						if (removed_path) {
							COMPILER_READ_BARRIER();
							if likely(ATOMIC_READ(removed_path->p_dirnext.ln_pself) != NULL) {
								/* Found it! */
								LLIST_REMOVE(removed_path, p_dirnext);
								assert(containing_path->p_cldsize);
								--containing_path->p_cldsize;
								if (containing_path->p_cldsize < (containing_path->p_cldmask / 3))
									path_rehash_smaller_nx(containing_path);
							}
							sync_endwrite(removed_path);
							if (premoved_path)
								*premoved_path = removed_path;
							else {
								decref(removed_path);
							}
						}
						sync_endwrite(containing_path);
					}
					/* Unlink the entry from the parent directory. */
					if (pentry != &oneshot_entry) {
						*pentry = entry->de_next;
						remove_dirent_from_directory(self, entry);
					}
				} else {
					if (!self->i_type->it_directory.d_unlink)
						THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_UNLINK);
					/* Remove a regular file. (If this is the last link, truncate the file first) */
					if unlikely(!sync_trywrite(node))
						goto unlock_directory_and_start_again;
					if unlikely(!sync_trywrite(self)) {
						sync_endwrite(node);
						goto unlock_directory_and_start_again;
					}
					/* All locks have been upgraded/acquired */
					FINALLY_ENDWRITE((struct vm_datablock *)self);
					FINALLY_ENDWRITE((struct vm_datablock *)node);
					if (node->i_filenlink == (nlink_t)1 && node->i_filesize != 0) {
						/* Deallocate file data of the node if this is the last link. */
						if unlikely(!node->i_type->it_file.f_truncate)
							THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_TRUNC);
						/* NOTE: No need to worry about deletion/truncation of VM data parts
						 *       Since the file is going away, nothing needs to be saved! */
						(*node->i_type->it_file.f_truncate)(node, 0);
						node->i_filesize = 0;
					}
					/* Do the actual unlink. */
					result = DIRECTORY_REMOVE_STATUS_UNLINK;
					if (node->i_filenlink == (nlink_t)1) {
						vm_datablock_anonymize(self);
						TRY {
							(*self->i_type->it_directory.d_unlink)(self, entry, node);
							assert(node->i_filenlink == 0);
						} EXCEPT {
							vm_datablock_deanonymize(self);
							RETHROW();
						}
						/* Mark the INode as having been deleted. */
						superblock_delete_inode(node->i_super, node);
						result |= DIRECTORY_REMOVE_STATUS_FDELETED;
					} else {
						(*self->i_type->it_directory.d_unlink)(self, entry, node);
					}
					/* Unlink the entry from the parent directory. */
					if (pentry != &oneshot_entry) {
						*pentry = entry->de_next;
						remove_dirent_from_directory(self, entry);
					}
				}
			} EXCEPT {
				decref(node);
				if (was_thrown(E_IOERROR_READONLY))
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_READONLY));
				RETHROW();
			}
		} EXCEPT {
			xdecref(oneshot_entry);
			RETHROW();
		}
	} EXCEPT {
		if (rwlock_endread(&self->db_lock))
			goto again;
		RETHROW();
	}
	rwlock_endread(&self->db_lock);
	/* Pass inheritable data to the caller. */
	if (premoved_inode) {
		*premoved_inode = node;
	} else {
		decref(node);
	}
	if (premoved_dirent) {
#ifndef NDEBUG
		memset(&entry->de_bypos.ln_pself, 0xcc, sizeof(void *));
		memset(&entry->de_bypos.ln_next, 0xcc, sizeof(void *));
#endif /* !NDEBUG */
		*premoved_dirent = entry;
	} else {
		decref(entry);
	}
	return result;
unlock_directory_and_start_again:
	rwlock_endread(&self->db_lock);
	decref(node);
	xdecref(oneshot_entry);
	task_yield();
	goto again;
wait_for_removed_path:
	TRY {
		sync_write(removed_path);
	} EXCEPT {
		decref(removed_path);
		RETHROW();
	}
	sync_endwrite(removed_path);
	decref(removed_path);
	goto again;
}



/* Rename/move an entry from one directory to another.
 * NOTE: This function will try to emulate an unsupported `rename()' using `link()' + `unlink()'
 * @param: mode: Set of `DIRECTORY_RENAME_F*'
 * @param: source_path:   When non-NULL, try to remove a child directory from this path node upon success.
 * @param: premoved_path: When non-NULL, store the child directory removed from `source_path' here, otherwise set to `NULL'.
 * @return: * : Set of `DIRECTORY_RENAME_STATUS_*'
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_RENAME: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (the specified source file was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`source_directory' or `target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_FILE_NOT_FOUND:      `source_name' wasn't found
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:   [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...] (Only when emulated using `link()' + `unlink()')
 * @throw: E_FSERROR_DIRECTORY_MOVE_TO_CHILD: [...]
 * @throw: E_FSERROR_ACCESS_DENIED:       [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
PUBLIC NONNULL((1, 2, 5, 6)) unsigned int KCALL
directory_rename(struct directory_node *__restrict source_directory,
                 CHECKED USER /*utf-8*/ char const *__restrict source_name,
                 u16 source_namelen, uintptr_t source_namehash,
                 struct directory_node *__restrict target_directory,
                 CHECKED USER /*utf-8*/ char const *__restrict target_name,
                 u16 target_namelen, unsigned int mode,
                 /*out*/ REF struct directory_entry **psource_dirent,
                 /*out*/ REF struct directory_entry **ptarget_dirent,
                 /*out*/ REF struct inode **psource_inode,
                 /*out*/ REF struct inode **ptarget_inode,
                 struct path *source_path,
                 /*out*/ REF struct path **premoved_path)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_FILE_NOT_FOUND,
		       E_FSERROR_ILLEGAL_PATH, E_FSERROR_FILE_ALREADY_EXISTS,
		       E_FSERROR_DISK_FULL, E_FSERROR_TOO_MANY_HARD_LINKS,
		       E_FSERROR_DIRECTORY_MOVE_TO_CHILD, E_FSERROR_ACCESS_DENIED,
		       E_FSERROR_READONLY, E_IOERROR, E_SEGFAULT, ...) {
	REF struct directory_entry *target_entry;
	REF struct inode *source_inode;
	struct path *removed_path;
	/* Check for cross-device links. */
	if unlikely(source_directory->i_super != target_directory->i_super)
		THROW(E_FSERROR_CROSS_DEVICE_LINK);
	if unlikely(!target_namelen)
		THROW(E_FSERROR_ILLEGAL_PATH);
	if (premoved_path)
		*premoved_path = NULL;

	/* Construct a directory entry for the target filename. */
	target_entry = directory_entry_alloc_s(target_name, target_namelen);
	TRY {
		/* Acquire all of the necessary locks to the source and target directories. */
acquire_sourcedir_writelock:
		sync_write(source_directory);
		if unlikely(!sync_trywrite(target_directory)) {
			sync_endwrite(source_directory);
			sync_write(target_directory);
			if unlikely(!sync_trywrite(source_directory)) {
				sync_endwrite(target_directory);
				goto acquire_sourcedir_writelock;
			}
		}
		TRY {
			REF struct directory_entry *source_oneshot = NULL;
			struct directory_entry *source_entry; /* NOTE: Becomes a [0..1]-REF upon successful completion. */
			struct directory_entry **psource_entry;

			/* Check if the source or target directories have been deleted. */
			inode_check_deleted(source_directory, E_FILESYSTEM_DELETED_PATH);
			inode_check_deleted(target_directory, E_FILESYSTEM_DELETED_PATH);

			/* Lookup the source directory entry. */
			psource_entry = mode & DIRECTORY_RENAME_FNOCASE
			                ? directory_getcaseentry_p(source_directory, source_name, source_namelen, source_namehash, &source_oneshot)
			                : directory_getentry_p(source_directory, source_name, source_namelen, source_namehash, &source_oneshot);
			if unlikely(!psource_entry)
				THROW(E_FSERROR_FILE_NOT_FOUND);
			source_entry = *psource_entry;
			TRY {
				/* Lookup the source INode. */
				source_inode = superblock_opennode(source_directory->i_super,
				                                   source_directory,
				                                   source_entry);
				/* Acquire a write-lock to the source INode. */
				if unlikely(!sync_trywrite(source_inode))
					goto wait_for_source_node_and_retry;
				TRY {
					REF struct directory_entry *existing_entry;
					/* Check if the source node has been deleted. */
					inode_check_deleted(source_inode);
					/* In order to allow for file rename, the caller needs
					 * write-access to the containing directory nodes. */
					if (mode & DIRECTORY_RENAME_FCHKACCESS) {
						inode_access(source_directory, W_OK);
						if (source_directory != target_directory)
							inode_access(target_directory, W_OK);
					}
					/* Check if the target directory already contains a file with the given name. */
					existing_entry = directory_getentry(target_directory,
					                                    target_entry->de_name,
					                                    target_entry->de_namelen,
					                                    target_entry->de_hash);
					if unlikely(existing_entry != NULL) {
						decref(existing_entry);
						THROW(E_FSERROR_FILE_ALREADY_EXISTS);
					}
					if (INODE_ISDIR(source_inode)) {
						/* Make sure that the INode to-be renamed isn't a parent of the target. */
						struct directory_node *iter = target_directory;
						do {
							if (source_inode == iter)
								THROW(E_FSERROR_DIRECTORY_MOVE_TO_CHILD);
						} while ((iter = iter->d_parent) != NULL);
					}

					/* Check if anything is even being renamed (if not: don't do anything) */
					if unlikely(source_directory == target_directory &&
					            source_entry->de_hash == target_entry->de_hash &&
					            source_entry->de_namelen == target_entry->de_namelen &&
					            memcmp(source_entry->de_name, target_entry->de_name,
					                   source_entry->de_namelen * sizeof(char)) == 0) {
						/* Pass extended information to the caller. */
						if (psource_dirent)
							*psource_dirent = incref(source_entry);
						if (ptarget_dirent)
							*ptarget_dirent = incref(target_entry);
						if (psource_inode)
							*psource_inode = (REF struct inode *)incref(source_inode);
						if (ptarget_inode)
							*ptarget_inode = (REF struct inode *)incref(source_inode);
						goto after_directories_updated;
					}

					/* Inherit some basic properties from the original INode */
					target_entry->de_type = IFTODT(source_inode->i_filemode);
					target_entry->de_ino  = source_inode->i_fileino;

					/* All right! we've got everything we need! */
					if (source_directory->i_type->it_directory.d_rename) {
						REF struct inode *target_inode;
						struct superblock *super = source_inode->i_super;
						/* Make sure that the source INode is fully synced, so we are safe to remove
						 * it in case of the `d_rename()' operator returning a new INode. */
						inode_sync(source_inode, INODE_FCHANGED | INODE_FATTRCHANGED);

						/* Acquire a write-lock to the associated superblock's file-tree. */
						if unlikely(!superblock_nodeslock_trywrite(super))
							goto wait_for_superblock_and_retry;
						removed_path = NULL;
						if (source_path && source_entry->de_type == DT_DIR) {
							if unlikely(!sync_trywrite(source_path))
								goto wait_for_sourcepath_and_retry;
							/* Check if the source directory has been re-mounted in the mean time. */
							if (mode & DIRECTORY_RENAME_FCHKPMOUNT &&
							    unlikely(source_path->p_inode != source_directory)) {
								sync_endwrite(source_path);
								superblock_nodeslock_endwrite(super);
								sync_endwrite(source_inode);
								sync_endwrite(target_directory);
								sync_endwrite(source_directory);
								xdecref(source_oneshot);
								decref(source_inode);
								decref(target_entry);
								return DIRECTORY_RENAME_STATUS_REMOUNT;
							}
							/* Search for the path to-be removed. */
							if (source_path->p_cldlist) {
								removed_path = source_path->p_cldlist[source_entry->de_hash & source_path->p_cldmask];
								for (; removed_path; removed_path = removed_path->p_dirnext.ln_next) {
									if (removed_path->p_dirent != source_entry)
										continue;
									if (!sync_trywrite(removed_path))
										goto wait_for_removed_path;
									if unlikely(removed_path->p_mount != NULL) {
										/* Cannot rename mounting points. */
										sync_endwrite(source_path);
										superblock_nodeslock_endwrite(super);
										THROW(E_FSERROR_IS_A_MOUNTING_POINT);
									}
									break;
								}
							}
						}
						TRY {
							target_inode = (*source_directory->i_type->it_directory.d_rename)(source_directory,
							                                                                  source_entry,
							                                                                  target_directory,
							                                                                  target_entry,
							                                                                  source_inode);
							assert(target_inode != NULL);
							if (target_inode != source_inode) {
								struct inode *delnode;
								assertf(target_inode->i_fileino == target_entry->de_ino,
								        "d_rename created a new INode, but didn't update the INO number "
								        "within the associated directory entry:\n"
								        "target_inode->i_fileino = %#" PRIxN(__SIZEOF_INO_T__) "\n"
								        "target_entry->de_ino    = %#" PRIxN(__SIZEOF_INO_T__) "\n",
								        target_inode->i_fileino, target_entry->de_ino);
								assertf(target_inode->i_fileino != source_inode->i_fileino,
								        "d_rename created a new INode, but that new INode has the same "
								        "INO number as the old INode:\n"
								        "target_inode->i_fileino = %#" PRIxN(__SIZEOF_INO_T__) " (created)\n"
								        "source_inode->i_fileino = %#" PRIxN(__SIZEOF_INO_T__) " (old)\n",
								        target_inode->i_fileino, source_inode->i_fileino);
								assert(!(ATOMIC_READ(source_inode->i_flags) & (INODE_FCHANGED | INODE_FATTRCHANGED)));
								/* Remove the old node from the superblock's file-tree, and replace it with the new one. */
								ATOMIC_FETCHOR(source_inode->i_flags, INODE_FDELETED);
								delnode = inode_tree_remove(&super->s_nodes, source_inode->i_fileino);
								if (unlikely(delnode != source_inode) && delnode)
									inode_tree_insert(&super->s_nodes, delnode);
								if (delnode == source_inode && (source_inode->i_flags & INODE_FPERSISTENT))
									decref_nokill(source_inode); /* The reference previously stored in the file tree. */
								/* Now insert the new INode
								 * NOTE: Because we've been holding a lock to the source INode, as well as
								 *       to the superblock's INode tree the whole time, it should be guarantied
								 *       that the node won't have been accessed by something else in the mean
								 *       time, meaning that this must never overlap with another node! */
								inode_tree_insert(&super->s_nodes, target_inode);
							}
						} EXCEPT {
							if (source_path && source_entry->de_type == DT_DIR) {
								if (removed_path)
									sync_endwrite(removed_path);
								sync_endwrite(source_path);
							}
							superblock_nodeslock_endwrite(super);
							RETHROW();
						}
						if (source_path && source_entry->de_type == DT_DIR) {
							/* Try to remove the a child from the source path. */
							if (removed_path) {
								COMPILER_READ_BARRIER();
								if (ATOMIC_READ(removed_path->p_dirnext.ln_pself) != NULL) {
									LLIST_REMOVE(removed_path, p_dirnext);
									assert(source_path->p_cldsize);
									--source_path->p_cldsize;
									if (source_path->p_cldsize < (source_path->p_cldmask / 3))
										path_rehash_smaller_nx(source_path);
								}
								sync_endwrite(removed_path);
								if (premoved_path)
									*premoved_path = removed_path;
								else {
									decref(removed_path);
								}
							}
							sync_endwrite(source_path);
						}
						superblock_nodeslock_endwrite(super);
						if (ptarget_inode)
							*ptarget_inode = target_inode; /* Inherit reference. */
						else {
							decref(target_inode);
						}
					} else {
						/* Try to use link() + unlink() */
						struct inode_type *type = source_directory->i_type;
						if (!type->it_directory.d_link || !type->it_directory.d_unlink)
							THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_RENAME);
						/* Make sure that attributes of the source node have been loaded,
						 * so-as to ensure that `i_filenlink' is properly initialized, as
						 * per requirement of the `d_link' operator. */
						inode_loadattr(source_inode);
						removed_path = NULL;
						if (source_path && source_entry->de_type == DT_DIR) {
							if unlikely(!sync_trywrite(source_path))
								goto wait_for_sourcepath_and_retry_nosuper;
							/* Check if the source directory has been re-mounted in the mean time. */
							if (mode & DIRECTORY_REMOVE_FCHKPMOUNT &&
							    unlikely(source_path->p_inode != source_directory)) {
								sync_endwrite(source_path);
								sync_endwrite(source_inode);
								sync_endwrite(target_directory);
								sync_endwrite(source_directory);
								decref(source_inode);
								decref(target_entry);
								return DIRECTORY_RENAME_STATUS_REMOUNT;
							}
							/* Search for the path to-be removed. */
							removed_path = source_path->p_cldlist[source_entry->de_hash & source_path->p_cldmask];
							for (; removed_path; removed_path = removed_path->p_dirnext.ln_next) {
								if (removed_path->p_dirent != source_entry)
									continue;
								if (!sync_trywrite(removed_path)) {
									incref(removed_path);
									goto wait_for_removed_path_nosuper;
								}
								if unlikely(removed_path->p_mount != NULL) {
									/* Cannot rename mounting points. */
									sync_endwrite(source_path);
									THROW(E_FSERROR_IS_A_MOUNTING_POINT);
								}
								break;
							}
						}
						assertf(source_inode->i_fileino == target_entry->de_ino,
						        "Inode number of the directory entry doesn't "
						        "match that of the INode itself (before d_link):\n"
						        "source_inode->i_fileino = %#" PRIxN(__SIZEOF_INO_T__) "\n"
						        "target_entry->de_ino    = %#" PRIxN(__SIZEOF_INO_T__) "\n",
						        source_inode->i_fileino, target_entry->de_ino);
						TRY {
							/* Invoke the LINK-operator. */
							(*type->it_directory.d_link)(target_directory,
							                             target_entry,
							                             source_inode);
							assertf(ATOMIC_READ(source_inode->i_filenlink) >= (nlink_t)2,
							        "There should be at least 2 links: 1 in the "
							        "source directory, +1 in the target directory");
							assertf(source_inode->i_fileino == target_entry->de_ino &&
							        source_inode->i_fileino == source_entry->de_ino,
							        "Inode number of the directory entry doesn't "
							        "match that of the INode itself (after d_link):\n"
							        "source_inode->i_fileino = %#" PRIxN(__SIZEOF_INO_T__) "\n"
							        "target_entry->de_ino    = %#" PRIxN(__SIZEOF_INO_T__) "\n"
							        "source_entry->de_ino    = %#" PRIxN(__SIZEOF_INO_T__) "\n",
							        source_inode->i_fileino,
							        target_entry->de_ino,
							        source_entry->de_ino);
							TRY {
								/* Remove the INode from the source directory. */
								(*type->it_directory.d_unlink)(source_directory,
								                               source_entry,
								                               source_inode);
							} EXCEPT {
								/* Try to remove remove the newly created source-directory entry. */
								struct inode_type *target_type = target_directory->i_type;
								if unlikely(!target_type->it_directory.d_unlink) {
									if likely(!target_directory->i_type->it_directory.d_oneshot.o_lookup)
										directory_addentry(target_directory, incref(target_entry));
								} else {
									TRY {
										/* NOTE: No need to fiddle with some target_path here! Because
										 *       we've been holding a write-lock to `target_directory'
										 *       this entire time, the VFS sub-system would have been
										 *       unable to access the target directory and see the temporary
										 *       file we've accidentally placed there, before this call
										 *       right here will remove that file once again as part of
										 *       the exception cleanup. */
										(*type->it_directory.d_unlink)(target_directory,
										                               target_entry,
										                               source_inode);
									} EXCEPT {
										/* If that fails, ensure a consistent state by still
										 * adding the new entry to the target directory. */
										if likely(!target_directory->i_type->it_directory.d_oneshot.o_lookup)
											directory_addentry(target_directory, incref(target_entry));
										RETHROW();
									}
								}
								RETHROW();
							}
							assertf(source_inode->i_fileino == target_entry->de_ino,
							        "Inode number of the directory entry doesn't "
							        "match that of the INode itself (after d_unlink):\n"
							        "source_inode->i_fileino = %#" PRIxN(__SIZEOF_INO_T__) "\n"
							        "target_entry->de_ino    = %#" PRIxN(__SIZEOF_INO_T__) "\n",
							        source_inode->i_fileino, target_entry->de_ino);
						} EXCEPT {
							if (source_path && source_entry->de_type == DT_DIR) {
								if (removed_path)
									sync_endwrite(source_path);
								sync_endwrite(source_path);
							}
							RETHROW();
						}
						if (source_path && source_entry->de_type == DT_DIR) {
							/* Try to remove the a child from the source path. */
							if (removed_path) {
								COMPILER_READ_BARRIER();
								if (ATOMIC_READ(removed_path->p_dirnext.ln_pself) != NULL) {
									/* Found it! */
									LLIST_REMOVE(removed_path, p_dirnext);
									assert(source_path->p_cldsize);
									--source_path->p_cldsize;
									if (source_path->p_cldsize < (source_path->p_cldmask / 3))
										path_rehash_smaller_nx(source_path);
								}
								sync_endwrite(removed_path);
								if (premoved_path)
									*premoved_path = removed_path;
								else {
									decref(removed_path);
								}
							}
							sync_endwrite(source_path);
						}

						/* Re-use the source INode as target INode. */
						if (ptarget_inode)
							*ptarget_inode = (REF struct inode *)incref(source_inode);
					}
					/* Pass extended information to the caller. */
					if (psource_dirent)
						*psource_dirent = incref(source_entry);
					if (ptarget_dirent)
						*ptarget_dirent = incref(target_entry);
					if (psource_inode)
						*psource_inode = (REF struct inode *)incref(source_inode);

					/* Update the source and target directories. */
					assert(*psource_entry == source_entry);
					if (psource_entry != &source_oneshot) {
						*psource_entry = source_entry->de_next; /* Unlink from the map */
						/* NOTE: inherit_ref(source_entry) */
						assert(source_directory->d_size >= 1);
						--source_directory->d_size;
						/* Remove the entry from the by-position chain. */
						directory_delentry_bypos(source_directory, source_entry);
						if (source_directory->d_size <= (source_directory->d_mask / 3)) {
							assert(source_directory->d_mask != 0);
							directory_rehash_smaller_nx(source_directory);
						}
					} else {
						assert(source_entry == source_oneshot);
						/* Prevent the decref() of `source_entry' below. */
						source_entry = NULL;
					}
					/* Must add the new entry _after_ removing the old one, since the act
					 * of adding new entires may realloc() the d_map vector, which the
					 * `psource_entry' above may point into.
					 * So this has to happen afterwards, else we run the risk of writing to
					 * free()'d memory in the line: `*psource_entry = source_entry->de_next;' */
					if likely(!target_directory->i_type->it_directory.d_oneshot.o_lookup)
						directory_addentry(target_directory, incref(target_entry));
after_directories_updated:
					;
				} EXCEPT {
					/* Translate exception codes. */
					if (was_thrown(E_IOERROR_BADBOUNDS))
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_DISK_FULL));
					if (was_thrown(E_IOERROR_READONLY))
						PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_READONLY));
					sync_endwrite(source_inode);
					decref(source_inode);
					RETHROW();
				}
				sync_endwrite(source_inode);
				decref(source_inode);
			} EXCEPT {
				xdecref(source_oneshot);
				RETHROW();
			}
			xdecref(source_oneshot);
			/* This is the reference stolen from the directory d_map of the source directory.
			 * s.a. `inherit_ref(source_entry)' above! */
			xdecref(source_entry);
		} EXCEPT {
			sync_endwrite(target_directory);
			sync_endwrite(source_directory);
			RETHROW();
		}
		sync_endwrite(target_directory);
		sync_endwrite(source_directory);
		__IF0 {
wait_for_sourcepath_and_retry:
			superblock_nodeslock_endwrite(source_inode->i_super);
wait_for_sourcepath_and_retry_nosuper:
			sync_endwrite(source_inode);
			sync_endwrite(target_directory);
			sync_endwrite(source_directory);
			decref(source_inode);
			sync_write(source_path);
			sync_endwrite(source_path);
			goto acquire_sourcedir_writelock;
wait_for_removed_path:
			incref(removed_path);
			superblock_nodeslock_endwrite(source_inode->i_super);
wait_for_removed_path_nosuper:
			sync_endwrite(source_path);
			sync_endwrite(source_inode);
			sync_endwrite(target_directory);
			sync_endwrite(source_directory);
			decref(source_inode);
			decref(target_entry);
			TRY {
				sync_write(removed_path);
			} EXCEPT {
				decref(removed_path);
				RETHROW();
			}
			sync_endwrite(removed_path);
			decref(removed_path);
			goto acquire_sourcedir_writelock;
wait_for_superblock_and_retry:
			sync_endwrite(source_inode);
			sync_endwrite(target_directory);
			sync_endwrite(source_directory);
			TRY {
				superblock_nodeslock_write(source_inode->i_super);
			} EXCEPT {
				decref(source_inode);
				RETHROW();
			}
			superblock_nodeslock_endwrite(source_inode->i_super);
			decref(source_inode);
			goto acquire_sourcedir_writelock;
wait_for_source_node_and_retry:
			sync_endwrite(target_directory);
			sync_endwrite(source_directory);
			TRY {
				sync_write(source_inode);
			} EXCEPT {
				decref(source_inode);
				RETHROW();
			}
			sync_endwrite(source_inode);
			decref(source_inode);
			goto acquire_sourcedir_writelock;
		}
	} EXCEPT {
		decref(target_entry);
		RETHROW();
	}
	decref(target_entry);
	return DIRECTORY_RENAME_STATUS_RENAMED;
}







/* Create a hardlink.
 * @throw: E_FSERROR_UNSUPPORTED_OPERATION:E_FILESYSTEM_OPERATION_LINK: [...]
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_FILE: [...] (`link_target' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_PATH: [...] (`target_directory' was deleted)
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: [...]
 * @throw: E_FSERROR_CROSS_DEVICE_LINK:   [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        [...]
 * @throw: E_FSERROR_ILLEGAL_PATH:        `target_namelen' was ZERO(0)
 * @throw: E_FSERROR_FILE_ALREADY_EXISTS: [...]
 * @throw: E_FSERROR_DISK_FULL:           [...]
 * @throw: E_FSERROR_TOO_MANY_HARD_LINKS: [...]
 * @throw: E_FSERROR_READONLY:            [...]
 * @throw: E_IOERROR:                     [...] */
PUBLIC NONNULL((1, 2, 4)) void KCALL
directory_link(struct directory_node *__restrict target_directory,
               CHECKED USER /*utf-8*/ char const *__restrict target_name,
               u16 target_namelen, struct inode *__restrict link_target, unsigned int link_mode,
               /*out*/ REF struct directory_entry **ptarget_dirent)
		THROWS(E_FSERROR_UNSUPPORTED_OPERATION, E_FSERROR_DELETED,
		       E_FSERROR_CROSS_DEVICE_LINK, E_FSERROR_ILLEGAL_PATH,
		       E_FSERROR_FILE_ALREADY_EXISTS, E_FSERROR_DISK_FULL,
		       E_FSERROR_TOO_MANY_HARD_LINKS, E_FSERROR_READONLY,
		       E_IOERROR, E_SEGFAULT, ...) {
	REF struct directory_entry *target_dirent;
	/* Check for cross-device links. */
	if unlikely(link_target->i_super != target_directory->i_super)
		THROW(E_FSERROR_CROSS_DEVICE_LINK);

	/* Check if the target directory even supports hardlinks. */
	if unlikely(!target_directory->i_type->it_directory.d_link)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_LINK);

	if unlikely(!target_namelen)
		THROW(E_FSERROR_ILLEGAL_PATH);

	/* Construct a directory entry for the target filename. */
	target_dirent = directory_entry_alloc_s(target_name, target_namelen);
	TRY {
		/* Acquire a write-lock to only the target directory at first. */
		sync_write(target_directory);
		sync_write(link_target);
		TRY {
			struct directory_entry *existing_entry;
			inode_check_deleted(target_directory, E_FILESYSTEM_DELETED_PATH);
			/* Check if a directory entry matching the target name already exists. */
			existing_entry = link_mode & DIRECTORY_LINK_FNOCASE
			                 ? directory_getcaseentry(target_directory,
			                                          target_dirent->de_name,
			                                          target_namelen,
			                                          target_dirent->de_hash)
			                 : directory_getentry(target_directory,
			                                      target_dirent->de_name,
			                                      target_namelen,
			                                      target_dirent->de_hash);
			if unlikely(existing_entry) {
				decref(existing_entry);
				THROW(E_FSERROR_FILE_ALREADY_EXISTS);
			}
			/* Make sure that attributes of the link-target have been loaded. */
			inode_loadattr_and_check_deleted(link_target);
			target_dirent->de_ino  = link_target->i_fileino;
			target_dirent->de_type = IFTODT(link_target->i_filemode);
			/* Actually invoke the link operator. */
			(*target_directory->i_type->it_directory.d_link)(target_directory,
			                                                 target_dirent,
			                                                 link_target);
			assert(target_dirent->de_ino == link_target->i_fileino);
		} EXCEPT {
			sync_endwrite(link_target);
			sync_endwrite(target_directory);
			RETHROW();
		}
		sync_endwrite(link_target);
		/* Add the new target directory entry to the target directory. */
		directory_addentry(target_directory, incref(target_dirent));
		sync_endwrite(target_directory);
	} EXCEPT {
		decref(target_dirent);
		if (was_thrown(E_IOERROR_BADBOUNDS))
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_DISK_FULL));
		if (was_thrown(E_IOERROR_READONLY))
			PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_READONLY));
		RETHROW();
	}
	if (ptarget_dirent)
		*ptarget_dirent = target_dirent;
	else {
		decref(target_dirent);
	}
}




#ifndef __INTELLISENSE__
DECL_END

#define DEFINE_DIRECTORY_CREATFILE 1
#include "node-directory-creat.c.inl"

#define DEFINE_DIRECTORY_SYMLINK 1
#include "node-directory-creat.c.inl"

#define DEFINE_DIRECTORY_MKNOD 1
#include "node-directory-creat.c.inl"

#define DEFINE_DIRECTORY_MKDIR 1
#include "node-directory-creat.c.inl"

DECL_BEGIN
#endif /* !__INTELLISENSE__ */

















/* Synchronize all modified nodes within the given superblock.
 * NOTE: This function is allowed to be called after `SUPERBLOCK_FUNMOUNTED' has been set! */
PUBLIC NONNULL((1)) void KCALL
superblock_sync(struct superblock *__restrict self,
                bool sync_device)
		THROWS(E_IOERROR, ...) {
	REF struct inode *chain, *next;
again:
	sync_write(&self->s_changed_lock);
	chain = ATOMIC_XCH(self->s_changed, NULL);
	sync_endwrite(&self->s_changed_lock);
	TRY {
		while (chain) {
			next = chain->i_changed_next;
			inode_sync(chain, INODE_FCHANGED | INODE_FATTRCHANGED);
			chain = next;
		}
	} EXCEPT {
		/* Anything we didn't get to sync must be re-schedule as pending! */
		struct inode *pend;
		next = chain;
		while (next->i_changed_next)
			next = next->i_changed_next;
		do {
			pend = ATOMIC_READ(self->s_changed);
			next->i_changed_next = pend;
		} while (!ATOMIC_CMPXCH_WEAK(self->s_changed, pend, chain));
		RETHROW();
	}
	/* Syncing one node may have caused some other node to become marked as changed. */
	if (ATOMIC_READ(self->s_changed) != NULL)
		goto again;
	/* Invoke the superblock's own synchronization function. */
	if (self->s_type->st_functions.f_sync)
		(*self->s_type->st_functions.f_sync)(self);
	/* Synchronize the underlying block device. */
	if (sync_device && self->s_device)
		block_device_sync(self->s_device);
}


PUBLIC WUNUSED size_t KCALL
fs_filesystems_loadall(REF struct superblock **buffer,
                       size_t buffer_length)
		THROWS(E_WOULDBLOCK) {
	size_t result = 0;
	struct superblock *iter;
	assert(!buffer_length || buffer != NULL);
	fs_filesystems_lock_read();
	iter = fs_filesystems.f_superblocks;
	for (; iter; iter = iter->s_filesystems.sn_next) {
		if (wasdestroyed(iter))
			continue;
		if (result < buffer_length) {
			if (!tryincref(iter))
				continue;
			buffer[result] = iter; /* Inherit reference. */
		}
		++result;
	}
	fs_filesystems_lock_endread();
	if (result > buffer_length) {
		/* Decref everything (we're not supposed to return references in this case!) */
		while (buffer_length--)
			decref_unlikely(buffer[buffer_length]);
	}
	return result;
}



/* Call `superblock_sync()' for all system-wide existing superblock.
 * NOTE: Underlying block-devices will be synced as well. */
PUBLIC void KCALL superblock_syncall(void) THROWS(E_IOERROR, ...) {
	REF struct superblock *local_buffer[32];
	size_t i, req_length;
	req_length = fs_filesystems_loadall(local_buffer, COMPILER_LENOF(local_buffer));
	if likely(req_length <= COMPILER_LENOF(local_buffer)) {
		i = 0;
		TRY {
			for (; i < req_length; ++i) {
				/* Synchronize this superblock. */
				superblock_sync(local_buffer[i], true);
				decref_unlikely(local_buffer[i]);
			}
		} EXCEPT {
			for (; i < req_length; ++i)
				decref_unlikely(local_buffer[i]);
			RETHROW();
		}
	} else {
		/* Highly unlikely: there are a sh$t-ton of filesystems loaded. */
		REF struct superblock **pbuf;
		size_t new_req_length;
		pbuf = (REF struct superblock **)kmalloc(req_length * sizeof(REF struct superblock *),
		                                         GFP_NORMAL);
		TRY {
			new_req_length = fs_filesystems_loadall(pbuf, req_length);
			while (new_req_length > req_length) {
				pbuf = (REF struct superblock **)krealloc(pbuf,
				                                          new_req_length * sizeof(REF struct superblock *),
				                                          GFP_NORMAL);
				new_req_length = fs_filesystems_loadall(pbuf, req_length);
			}
			i = 0;
			TRY {
				for (; i < new_req_length; ++i) {
					/* Synchronize this superblock. */
					superblock_sync(local_buffer[i], true);
					decref_unlikely(local_buffer[i]);
				}
			} EXCEPT {
				for (; i < new_req_length; ++i)
					decref_unlikely(local_buffer[i]);
				RETHROW();
			}
		} EXCEPT {
			kfree(pbuf);
			RETHROW();
		}
		kfree(pbuf);
	}
}


LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL inode_set_closed)(struct inode *__restrict self) {
	uintptr_t old_flags;
	do {
		old_flags = ATOMIC_READ(self->i_flags);
		if (old_flags & INODE_FDELETED)
			return; /* Node has already been deleted. */
		assert(!(old_flags & INODE_FSUPERDEL));
	} while (!ATOMIC_CMPXCH_WEAK(self->i_flags, old_flags,
	                             old_flags | (INODE_FDELETED | INODE_FSUPERDEL)));
	/* Trigger some signals to wake up blocking operations
	 * that may still be in progress on this node.
	 * Any piece of code that won't understand this part will
	 * just have to deal with a sporadic wake-up, which is
	 * allowed to happen irregardless. */
	sig_broadcast(&self->db_lock.rw_chmode);
	sig_broadcast(&self->db_lock.rw_unshare);
}

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL inode_unset_closed)(struct inode *__restrict self) {
	uintptr_t old_flags;
	do {
		old_flags = ATOMIC_READ(self->i_flags);
		if (!(old_flags & INODE_FSUPERDEL))
			return; /* Node was not deleted by the superblock. */
		assert(old_flags & INODE_FDELETED);
	} while (!ATOMIC_CMPXCH_WEAK(self->i_flags, old_flags,
	                             old_flags & ~(INODE_FDELETED | INODE_FSUPERDEL)));
}

PRIVATE NONNULL((1)) void KCALL
inode_anonymize_tree(struct inode *__restrict self)
		THROWS(E_WOULDBLOCK) {
	struct inode *minnode;
	struct inode *maxnode;
again:
	minnode = self->i_filetree.a_min;
	maxnode = self->i_filetree.a_max;
	incref(self);
	vm_datablock_anonymize(self);
	decref_likely(self);
	if (minnode) {
		if (maxnode)
			inode_anonymize_tree(maxnode);
		self = minnode;
		goto again;
	}
	if (maxnode) {
		self = maxnode;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL inode_set_closed_tree)(struct inode *__restrict self) {
again:
	inode_set_closed(self);
	if (self->i_filetree.a_min) {
		if (self->i_filetree.a_max)
			inode_set_closed_tree(self->i_filetree.a_max);
		self = self->i_filetree.a_min;
		goto again;
	}
	if (self->i_filetree.a_max) {
		self = self->i_filetree.a_max;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL inode_unset_closed_tree)(struct inode *__restrict self) {
again:
	inode_unset_closed(self);
	if (self->i_filetree.a_min) {
		if (self->i_filetree.a_max)
			inode_unset_closed_tree(self->i_filetree.a_max);
		self = self->i_filetree.a_min;
		goto again;
	}
	if (self->i_filetree.a_max) {
		self = self->i_filetree.a_max;
		goto again;
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_remove_persistent_nodes)(struct inode **__restrict pnode,
                                                  ATREE_SEMI_T(ino_t) addr_semi,
                                                  ATREE_LEVEL_T addr_level) {
	struct inode *node;
again:
	node = *pnode;
	if unlikely(!node)
		return;
	if (node->i_flags & INODE_FPERSISTENT) {
		decref(inode_tree_pop_at(pnode, addr_semi, addr_level));
		goto again;
	}
	if (node->i_filetree.a_min) {
		if (node->i_filetree.a_max) {
			ATREE_SEMI_T(ino_t)
			temp_semi                = addr_semi;
			ATREE_LEVEL_T temp_level = addr_level;
			ATREE_WALKMAX(ino_t, temp_semi, temp_level);
			superblock_remove_persistent_nodes(&node->i_filetree.a_max,
			                                   temp_semi, temp_level);
		}
		ATREE_WALKMIN(ino_t, addr_semi, addr_level);
		pnode = &node->i_filetree.a_min;
		goto again;
	}
	if (node->i_filetree.a_max) {
		ATREE_WALKMAX(ino_t, addr_semi, addr_level);
		pnode = &node->i_filetree.a_max;
		goto again;
	}
}

INTERN NONNULL((1)) void KCALL
superblock_set_unmounted_impl(struct superblock *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	assert(self->s_nodes != NULL);
	inode_set_closed_tree(self->s_nodes);
	TRY {
		/* Synchronize all remaining nodes to flush changes. */
		superblock_sync(self);
		/* Anonymize all remaining nodes (any changes not synced prior
		 * to the final `superblock_sync()' before will not be persistent) */
		inode_anonymize_tree(self->s_nodes);
	} EXCEPT {
		/* Undo what we did so far. */
		assert(self->s_nodes != NULL);
		inode_unset_closed_tree(self->s_nodes);
		ATOMIC_FETCHAND(self->s_flags, ~SUPERBLOCK_FUNMOUNTED);
		RETHROW();
	}
	assert(self->s_nodes);
	/* Remove all INodes with the PERSISTENT flag from the file-free */
	superblock_remove_persistent_nodes(&self->s_nodes,
	                                   ATREE_SEMI0(ino_t),
	                                   ATREE_LEVEL0(ino_t));
}


PUBLIC NONNULL((1)) bool KCALL
superblock_set_unmounted(struct superblock *__restrict self)
		THROWS(E_WOULDBLOCK, E_IOERROR, ...) {
	bool result = false;
	superblock_nodeslock_write(self);
	TRY {
		/* Set the unmounted-flag. */
		if (!(ATOMIC_FETCHOR(self->s_flags, SUPERBLOCK_FUNMOUNTED) & SUPERBLOCK_FUNMOUNTED)) {
			result = true;
			superblock_set_unmounted_impl(self);
		}
	} EXCEPT {
		superblock_nodeslock_endwrite(self);
		RETHROW();
	}
	superblock_nodeslock_endwrite(self);
	/* Clear recently used INodes, thus uncaching any that were apart of `self' */
#if 0 /* Always do this in case it failed on a previous invocation.             \
       * TODO: A proper solution would be to prepare a BLOCKING_CLEANUP         \
       *       descriptor that will be scheduled to call `inode_recent_clear()' \
       *       in another thread in order to ensure that INodes are cleared! */
	if (result)
#endif
	{
		inode_recent_clear();
	}
	return result;
}

PRIVATE size_t KCALL
inode_tree_clear_caches(struct inode *__restrict self) {
	size_t temp, result = 0;
again:
	if (self->i_type->it_attr.a_clearcache) {
		temp = (*self->i_type->it_attr.a_clearcache)(self);
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;
	}
	if (self->i_filetree.a_min) {
		if (self->i_filetree.a_max) {
			temp = inode_tree_clear_caches(self->i_filetree.a_max);
			if (OVERFLOW_UADD(result, temp, &result))
				result = (size_t)-1;
		}
		self = self->i_filetree.a_min;
		goto again;
	}
	if (self->i_filetree.a_max) {
		self = self->i_filetree.a_max;
		goto again;
	}
	return result;
}


/* Clear all of the caches associated with the given superblock. */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL superblock_clear_caches)(struct superblock *__restrict self) {
	size_t result;
	result = 0;
	if (superblock_nodeslock_trywrite(self)) {
		result = inode_tree_clear_caches(self->s_nodes);
		superblock_nodeslock_endwrite(self);
	}
	/* Invoke the user-defined, superblock-level clear-cache function. */
	if (self->s_type->st_functions.f_clearcache) {
		size_t temp;
		temp = (*self->s_type->st_functions.f_clearcache)(self);
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;
	}
	return result;
}

PRIVATE NOBLOCK size_t
NOTHROW(KCALL superblock_clear_all_caches_impl)(void) {
	size_t result                 = 0;
	struct superblock *last_block = NULL;
	REF struct superblock *block;
again:
	if (!fs_filesystems_lock_tryread())
		goto done;
again_locked:
	block = fs_filesystems.f_superblocks;
	for (; block; block = block->s_filesystems.sn_next) {
		if (last_block) {
			if (last_block == block)
				last_block = NULL;
			continue;
		}
		if (tryincref(block))
			goto got_block;
	}
	if (last_block) {
		last_block = NULL;
		goto again_locked;
	}
got_block:
	fs_filesystems_lock_endread();
	if (block) {
		size_t temp;
		/* Clear caches for this filesystem.  */
		temp = superblock_clear_caches(block);
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;

		last_block = block;
		assert(!wasdestroyed(block));
		if (ATOMIC_DECFETCH(block->db_refcnt) == 0) {
			if (OVERFLOW_UADD(result, block->i_heapsize, &result))
				result = (size_t)-1;
			destroy(block);
			last_block = NULL;
		}
		goto again;
	}
done:
	return result;
}

DEFINE_SYSTEM_CACHE_CLEAR(superblock_clear_all_caches);
PRIVATE ATTR_USED NOBLOCK size_t
NOTHROW(KCALL superblock_clear_all_caches)(void) {
	size_t temp, result;
	result = superblock_clear_all_caches_impl();
	for (;;) {
		temp = superblock_clear_all_caches_impl();
		if (!temp)
			break;
		if (OVERFLOW_UADD(result, temp, &result))
			result = (size_t)-1;
	}
	return result;
}




#define SUPERBLOCK_HAS_NODES_JOBS(self) \
	(ATOMIC_READ((self)->s_delnodes) != NULL || \
	 ATOMIC_READ((self)->s_unlinknodes) != NULL)

LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_clear_delnodes)(struct superblock *__restrict self) {
	struct inode *chain, *next, *delnode;
	chain = ATOMIC_XCH(self->s_delnodes, NULL);
	while (chain) {
		next    = chain->i_changed_next;
		delnode = inode_tree_remove(&self->s_nodes, chain->i_fileino);
		if (unlikely(delnode != chain) && delnode)
			inode_tree_insert(&self->s_nodes, delnode);
		heap_free(FS_HEAP, chain, chain->i_heapsize, FS_GFP);
		chain = next;
	}
	chain = ATOMIC_XCH(self->s_unlinknodes, NULL);
	while (chain) {
		next    = chain->i_changed_next;
		delnode = inode_tree_remove(&self->s_nodes, chain->i_fileino);
		if (unlikely(delnode != chain) && delnode)
			inode_tree_insert(&self->s_nodes, delnode);
		if (chain->i_flags & INODE_FPERSISTENT)
			decref_nokill(chain); /* The reference previously stored within the INode tree. */
		decref(chain); /* The reference previously stored within the `s_unlinknodes' chain. */
		chain = next;
	}
}


INTERN NONNULL((1)) void *
NOTHROW(FCALL superblock_cleanup_unmounted)(void *pfun, unsigned int action) {
	void *result;
	bool did_unmount = false;
	REF struct superblock *self;
	self = COMPILER_CONTAINER_OF((struct path **)pfun, struct superblock, s_mount);
	if (action == BLOCKING_CLEANUP_ACTION_GETNEXT)
		return (void *)&self->s_cblock_next;
	result = self->s_cblock_next;
	if (!sync_write_nx(&self->s_nodes_lock))
		return BLOCKING_CLEANUP_RETURN_XPENDING;
	superblock_clear_delnodes(self);
	/* Set the unmounted-flag. */
	if (!(ATOMIC_FETCHOR(self->s_flags, SUPERBLOCK_FUNMOUNTED) & SUPERBLOCK_FUNMOUNTED)) {
		struct exception_info old_except;
		assert(self->s_nodes != NULL);
		inode_set_closed_tree(self->s_nodes);
		memcpy(&old_except, &THIS_EXCEPTION_INFO, sizeof(old_except));
		TRY {
			/* Synchronize all remaining nodes to flush changes. */
			superblock_sync(self);
		} EXCEPT {
			error_printf("Synchronizing unmounted superblock");
			goto restore_old_except;
		}
		__IF0 {
restore_old_except:
			memcpy(&THIS_EXCEPTION_INFO, &old_except, sizeof(old_except));
		}
		assert(self->s_nodes);
		/* Remove all INodes with the PERSISTENT flag from the file-free */
		superblock_remove_persistent_nodes(&self->s_nodes,
		                                   ATREE_SEMI0(ino_t),
		                                   ATREE_LEVEL0(ino_t));
		did_unmount = true;
	}
	superblock_nodeslock_endwrite(self);
	decref(self);
	/* Clear recently used INodes, thus uncaching any that were apart of `self' */
	if (did_unmount) {
		/* FIXME: This call may throw an exception! */
		inode_recent_clear();
	}
	return result;
}

INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_schedule_set_unmounted)(struct superblock *__restrict self) {
	/* This function is used to implement the remote unmounting of
	 * superblock that need to be unmounted after `vfs_clearmounts()'
	 * was used to clear all mounting points, following which the associated
	 * path segments being destroyed lead to all mounting points for some
	 * specific superblock being removed, causing the superblock to have to
	 * be unloaded in its entirety.
	 * This is quite the complicated situation, because in order to actually
	 * synchronize a superblock (as is required before actually proceeding to
	 * unload it), we need to be able to block, and be allowed to throw exceptions!
	 * However, since this function gets called as the result of a decref() operation,
	 * we aren't allowed to do either. (Also: what would be the fallback to causing
	 * an exception here? The superblock is already gone, and we can't bring back its
	 * mounting points. So the only alternative to doing our job and cleaning it up
	 * would be to leave it as a memory leak...) */
	assert(self->s_flags & SUPERBLOCK_FMUSTUNMOUNT);
	assert(self->s_mount == NULL);
	assert(self->s_umount_pend == NULL);
	incref(self); /* The reference stored in the cleanup chain. */
	*(void **)&self->s_mount = (void *)&superblock_cleanup_unmounted;
	BLOCKING_CLEANUP_SCHEDULE(self, s_mount, s_cblock_next);
}


PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_nodeslock_tryread)(struct superblock *__restrict self) {
	if (!sync_tryread(&self->s_nodes_lock))
		return false;
	if (SUPERBLOCK_HAS_NODES_JOBS(self)) {
		if (sync_tryupgrade(&self->s_nodes_lock)) {
			superblock_clear_delnodes(self);
			sync_downgrade(&self->s_nodes_lock);
		}
	}
	return true;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_nodeslock_tryservice)(struct superblock *__restrict self) {
again:
	if (sync_trywrite(&self->s_nodes_lock)) {
		superblock_clear_delnodes(self);
		sync_endwrite(&self->s_nodes_lock);
		COMPILER_READ_BARRIER();
		if unlikely(SUPERBLOCK_HAS_NODES_JOBS(self))
			goto again;
	}
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_nodeslock_trywrite)(struct superblock *__restrict self) {
	if (!sync_trywrite(&self->s_nodes_lock))
		return false;
	superblock_clear_delnodes(self);
	return true;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_nodeslock_tryupgrade)(struct superblock *__restrict self) {
	if (!sync_tryupgrade(&self->s_nodes_lock))
		return false;
	superblock_clear_delnodes(self);
	return true;
}

PUBLIC NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL superblock_nodeslock_endread)(struct superblock *__restrict self) {
again:
	if (rwlock_endread(&self->s_nodes_lock))
		return true;
	if (SUPERBLOCK_HAS_NODES_JOBS(self) &&
	    sync_trywrite(&self->s_nodes_lock)) {
		superblock_clear_delnodes(self);
		sync_downgrade(&self->s_nodes_lock);
		goto again;
	}
	return false;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_nodeslock_downgrade)(struct superblock *__restrict self) {
again:
	if (!rwlock_downgrade(&self->s_nodes_lock))
		return;
	if (SUPERBLOCK_HAS_NODES_JOBS(self) &&
	    sync_tryupgrade(&self->s_nodes_lock)) {
		superblock_clear_delnodes(self);
		goto again;
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_nodeslock_endwrite)(struct superblock *__restrict self) {
again:
	sync_endwrite(&self->s_nodes_lock);
	if (SUPERBLOCK_HAS_NODES_JOBS(self) &&
	    sync_trywrite(&self->s_nodes_lock)) {
		superblock_clear_delnodes(self);
		goto again;
	}
}

PUBLIC NONNULL((1)) void KCALL
superblock_nodeslock_read(struct superblock *__restrict self) THROWS(E_WOULDBLOCK) {
	sync_read(&self->s_nodes_lock);
	if (SUPERBLOCK_HAS_NODES_JOBS(self) &&
	    sync_tryupgrade(&self->s_nodes_lock)) {
		superblock_clear_delnodes(self);
		sync_downgrade(&self->s_nodes_lock);
	}
}

PUBLIC NONNULL((1)) void KCALL
superblock_nodeslock_write(struct superblock *__restrict self) THROWS(E_WOULDBLOCK) {
	sync_write(&self->s_nodes_lock);
	superblock_clear_delnodes(self);
}

PUBLIC NONNULL((1)) bool KCALL
superblock_nodeslock_upgrade(struct superblock *__restrict self) THROWS(E_WOULDBLOCK) {
	bool result = sync_upgrade(&self->s_nodes_lock);
	superblock_clear_delnodes(self);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_nodeslock_read_nx)(struct superblock *__restrict self) {
	if (!sync_read_nx(&self->s_nodes_lock))
		return false;
	if (SUPERBLOCK_HAS_NODES_JOBS(self) &&
	    sync_tryupgrade(&self->s_nodes_lock)) {
		superblock_clear_delnodes(self);
		sync_downgrade(&self->s_nodes_lock);
	}
	return true;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_nodeslock_write_nx)(struct superblock *__restrict self) {
	if (!sync_write_nx(&self->s_nodes_lock))
		return false;
	superblock_clear_delnodes(self);
	return true;
}

PUBLIC WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL superblock_nodeslock_upgrade_nx)(struct superblock *__restrict self) {
	unsigned int result;
	result = sync_upgrade_nx(&self->s_nodes_lock);
	if (result != 0)
		superblock_clear_delnodes(self);
	return result;
}

#define SUPERBLOCK_HAS_MOUNT_JOBS(self) \
	(ATOMIC_READ((self)->s_umount_pend) != NULL)

#undef path
LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_clear_delmount)(struct superblock *__restrict self) {
	struct path *pend, *next;
	pend = ATOMIC_XCH(self->s_umount_pend, NULL);
	if likely(!pend)
		return;
	for (;;) {
		next = pend->p_mount->mp_pending;
		if (pend->p_mount->mp_fsmount.ln_pself != NULL)
			LLIST_REMOVE(pend, p_mount->mp_fsmount);
		kfree(pend->p_mount);
		path_free(pend);
		if (!next)
			break;
		pend = next;
	}
	if (!self->s_mount) {
		if (!(ATOMIC_FETCHOR(self->s_flags, SUPERBLOCK_FMUSTUNMOUNT) & SUPERBLOCK_FMUSTUNMOUNT))
			superblock_schedule_set_unmounted(self);
	}
}



PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_mountlock_tryread)(struct superblock *__restrict self) {
	if (!sync_tryread(&self->s_mount_lock))
		return false;
	if (SUPERBLOCK_HAS_MOUNT_JOBS(self)) {
		if (sync_tryupgrade(&self->s_mount_lock)) {
			superblock_clear_delmount(self);
			sync_downgrade(&self->s_mount_lock);
		}
	}
	return true;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_mountlock_tryservice)(struct superblock *__restrict self) {
	if (sync_trywrite(&self->s_mount_lock)) {
		superblock_clear_delmount(self);
		sync_endwrite(&self->s_mount_lock);
	}
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_mountlock_trywrite)(struct superblock *__restrict self) {
	if (!sync_trywrite(&self->s_mount_lock))
		return false;
	superblock_clear_delmount(self);
	return true;
}

PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_mountlock_tryupgrade)(struct superblock *__restrict self) {
	if (!sync_tryupgrade(&self->s_mount_lock))
		return false;
	superblock_clear_delmount(self);
	return true;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_mountlock_endread)(struct superblock *__restrict self) {
again:
	sync_endread(&self->s_mount_lock);
	if (SUPERBLOCK_HAS_MOUNT_JOBS(self)) {
		if (sync_trywrite(&self->s_mount_lock)) {
			superblock_clear_delmount(self);
			sync_downgrade(&self->s_mount_lock);
			goto again;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_mountlock_downgrade)(struct superblock *__restrict self) {
again:
	sync_downgrade(&self->s_mount_lock);
	if (SUPERBLOCK_HAS_MOUNT_JOBS(self)) {
		if (sync_tryupgrade(&self->s_mount_lock)) {
			superblock_clear_delmount(self);
			goto again;
		}
	}
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL superblock_mountlock_endwrite)(struct superblock *__restrict self) {
again:
	sync_endwrite(&self->s_mount_lock);
	if (SUPERBLOCK_HAS_MOUNT_JOBS(self)) {
		if (sync_trywrite(&self->s_mount_lock)) {
			superblock_clear_delmount(self);
			goto again;
		}
	}
}

PUBLIC NONNULL((1)) void KCALL
superblock_mountlock_read(struct superblock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	sync_read(&self->s_mount_lock);
	if (SUPERBLOCK_HAS_MOUNT_JOBS(self)) {
		if (sync_tryupgrade(&self->s_mount_lock)) {
			superblock_clear_delmount(self);
			sync_downgrade(&self->s_mount_lock);
		}
	}
}

PUBLIC NONNULL((1)) void KCALL
superblock_mountlock_write(struct superblock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	sync_write(&self->s_mount_lock);
	superblock_clear_delmount(self);
}

PUBLIC NONNULL((1)) bool KCALL
superblock_mountlock_upgrade(struct superblock *__restrict self)
		THROWS(E_WOULDBLOCK) {
	bool result = sync_upgrade(&self->s_mount_lock);
	superblock_clear_delmount(self);
	return result;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_mountlock_read_nx)(struct superblock *__restrict self) {
	if (!sync_read_nx(&self->s_mount_lock))
		return false;
	if (SUPERBLOCK_HAS_MOUNT_JOBS(self)) {
		if (sync_tryupgrade(&self->s_mount_lock)) {
			superblock_clear_delmount(self);
			sync_downgrade(&self->s_mount_lock);
		}
	}
	return true;
}

PUBLIC WUNUSED NONNULL((1)) bool
NOTHROW(KCALL superblock_mountlock_write_nx)(struct superblock *__restrict self) {
	if (!sync_write_nx(&self->s_mount_lock))
		return false;
	superblock_clear_delmount(self);
	return true;
}

PUBLIC WUNUSED NONNULL((1)) unsigned int
NOTHROW(KCALL superblock_mountlock_upgrade_nx)(struct superblock *__restrict self) {
	unsigned int result;
	result = sync_upgrade_nx(&self->s_mount_lock);
	if (result != 0)
		superblock_clear_delmount(self);
	return result;
}


/* Open the INode associated with a given directory entry.
 * @throw: E_FSERROR_DELETED:E_FILESYSTEM_DELETED_UNMOUNTED: The superblock has been unmounted.
 * @throws: E_IOERROR:   [...]
 * @throws: E_BADALLOC:  [...] */
PUBLIC ATTR_RETNONNULL NONNULL((1, 2, 3)) REF struct inode *KCALL
superblock_opennode(struct superblock *__restrict self,
                    struct directory_node *__restrict parent_directory,
                    struct directory_entry *__restrict parent_directory_entry)
		THROWS(E_FSERROR_DELETED, E_IOERROR, E_BADALLOC, ...) {
	REF struct inode *result;
	struct heapptr resptr;
again:
	superblock_nodeslock_read(self);
	if unlikely(self->s_flags & SUPERBLOCK_FUNMOUNTED) {
		superblock_nodeslock_endread(self);
		THROW(E_FSERROR_DELETED, (uintptr_t)E_FILESYSTEM_DELETED_UNMOUNTED);
	}

	/* Search for an existing INode. */
	assert(self->s_nodes);
	result = inode_tree_locate(self->s_nodes, parent_directory_entry->de_ino);
	if (result && tryincref(result)) {
		superblock_nodeslock_endread(self);
check_result_for_deletion:
		/* Must remove an INode from the tree that has been deleted. */
		if unlikely(ATOMIC_READ(result->i_flags) & INODE_FDELETED) {
			struct inode *new_node;
			TRY {
				superblock_nodeslock_write(self);
			} EXCEPT {
				decref_unlikely(result);
				RETHROW();
			}
			new_node = inode_tree_remove(&self->s_nodes, parent_directory_entry->de_ino);
			if (unlikely(new_node != result) && new_node)
				inode_tree_insert(&self->s_nodes, new_node);
			superblock_nodeslock_endwrite(self);
			if (new_node == result && ATOMIC_READ(result->i_flags) & INODE_FPERSISTENT)
				decref_nokill(result); /* The reference usually stored for persistent INodes. */
			decref(result);            /* The reference acquired by the `tryincref()' above. */
			goto again;
		}
		return result;
	}
	TRY {
		if (!superblock_nodeslock_upgrade(self)) {
			result = inode_tree_locate(self->s_nodes, parent_directory_entry->de_ino);
			if (result && tryincref(result)) {
				superblock_nodeslock_endwrite(self);
				goto check_result_for_deletion;
			}
		}
	} EXCEPT {
		if (superblock_nodeslock_endread(self))
			goto again;
		RETHROW();
	}
	TRY {
		/* Node wasn't in cache. Allocate a new descriptor. */
		switch (parent_directory_entry->de_type) {

		case DT_REG:
			resptr = heap_alloc(FS_HEAP, sizeof(struct regular_node), FS_GFP | GFP_CALLOC);
			result = (struct inode *)resptr.hp_ptr;
			break;

		case DT_LNK:
			resptr = heap_alloc(FS_HEAP, sizeof(struct symlink_node), FS_GFP | GFP_CALLOC);
			result = (struct inode *)resptr.hp_ptr;
			break;

		case DT_DIR: {
			REF struct directory_node *me;
			resptr = heap_alloc(FS_HEAP, sizeof(struct directory_node), FS_GFP | GFP_CALLOC);
			result = me = (struct directory_node *)resptr.hp_ptr;
			TRY {
				me->d_map = (REF struct directory_entry **)kmalloc((DIRECTORY_DEFAULT_MASK + 1) *
				                                                   sizeof(REF struct directory_entry *),
				                                                   FS_GFP | GFP_CALLOC);
			} EXCEPT {
				heap_free(FS_HEAP,
				          resptr.hp_ptr,
				          resptr.hp_siz,
				          FS_GFP | GFP_CALLOC);
				RETHROW();
			}
			me->d_mask   = DIRECTORY_DEFAULT_MASK;
			me->d_parent = (REF struct directory_node *)incref(parent_directory);
		}	break;

		default: break;
		}

		/* Initialize common INode members. */
		result->db_refcnt = 1;
		rwlock_cinit(&result->db_lock);
		result->db_type      = &inode_datablock_type;
		result->db_pageshift = self->db_pageshift;
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
		result->db_addrshift = self->db_addrshift;
		result->db_pagealign = self->db_pagealign;
		result->db_pagemask  = self->db_pagemask;
		result->db_pagesize  = self->db_pagesize;
#endif /* !CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
		result->i_super    = (struct superblock *)incref(self);
		result->i_heapsize = resptr.hp_siz;
#if INODE_FNORMAL != 0
		result->i_flags = INODE_FNORMAL;
#endif /* INODE_FNORMAL != 0 */
		result->i_fileino  = parent_directory_entry->de_ino;
		result->i_filemode = DTTOIF(parent_directory_entry->de_type);

		TRY {
			/* Invoke the open-node operator. */
			(*self->s_type->st_functions.f_opennode)(self,
			                                         result,
			                                         parent_directory,
			                                         parent_directory_entry);
		} EXCEPT {
			assert(!isshared(result));
			if (parent_directory_entry->de_type == DT_DIR) {
				decref(((struct directory_node *)result)->d_parent);
				kffree(((struct directory_node *)result)->d_map, GFP_CALLOC);
			}
			heap_free(FS_HEAP, result, result->i_heapsize, FS_GFP);
			RETHROW();
		}
		assertf(result->i_type != NULL, "`f_opennode' must fill in `i_type'");
		assert(result->i_fileino == parent_directory_entry->de_ino);
		assertf((result->i_filemode & S_IFMT) ==
		        (DTTOIF(parent_directory_entry->de_type) & S_IFMT),
		        "%u != %u",
		        IFTODT(result->i_filemode & S_IFMT),
		        parent_directory_entry->de_type);
		if unlikely(ATOMIC_READ(result->i_flags) & INODE_FDELETED) {
			/* Might happen due to race conditions. (start over...) */
			superblock_nodeslock_endwrite(self);
			decref_likely(result);
			goto again;
		}
		/* Construct the reference stored in the INode tree
		 * when the generated node is said to be persistent. */
		if (ATOMIC_READ(result->i_flags) & INODE_FPERSISTENT)
			incref(result);
		/* Insert the new node into the INode tree. */
		inode_tree_insert(&self->s_nodes, result);
	} EXCEPT {
		superblock_nodeslock_endwrite(self);
		RETHROW();
	}
	superblock_nodeslock_endwrite(self);
	return result;
}


/* Find some mounting point that is apart of the given `ns'
 * If multiple such paths exist, arbitrarily return one of them.
 * If no such paths exist, return NULL instead. */
PUBLIC WUNUSED NONNULL((1, 2)) REF struct path *KCALL
superblock_find_mount_from_vfs(struct superblock *__restrict self,
                               struct vfs const *__restrict ns) {
	REF struct path *result;
	superblock_mountlock_read(self);
	for (result = self->s_mount; result;
	     result = result->p_mount->mp_fsmount.ln_next) {
		assert(result->p_mount);
		/* Check if this mounting point exists within the given `ns' */
		if (result->p_vfs == ns) {
			/* Try to acquire a reference to the mounting point.
			 * This may fail if the mounting point is currently being unmounted. */
			if (tryincref(result))
				break;
		}
	}
	superblock_mountlock_endread(self);
	return result;
}




/* Gather information about the filesystem and store that information in `*result' */
PUBLIC NONNULL((1, 2)) void KCALL
superblock_statfs(struct superblock *__restrict self,
                  USER CHECKED struct statfs *result)
		THROWS(E_IOERROR, E_SEGFAULT, ...) {
	syscall_ulong_t fsflags;
	assert(self);
	assert(self->s_type);
	memset(result, 0, sizeof(*result));
	if likely(self->s_type->st_functions.f_statfs)
		(*self->s_type->st_functions.f_statfs)(self, result);
	fsflags = 0;
	if (!(self->s_flags & SUPERBLOCK_FDOATIME))
		fsflags |= (ST_NOATIME | ST_NODIRATIME);
	/* Check if the associated device is marked as read-only */
	if (self->s_device) {
		struct basic_block_device *dev;
		dev = self->s_device;
		if (dev->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
			fsflags |= ST_RDONLY;
		else if (block_device_ispartition(dev)) {
			dev = ((struct block_device_partition *)dev)->bp_master;
			if (dev->bd_flags & BLOCK_DEVICE_FLAG_READONLY)
				fsflags |= ST_RDONLY;
		}
	}
	//TODO: ST_NOSUID      2    /* Ignore suid and sgid bits. */
	//TODO: ST_NODEV       4    /* Disallow access to device special files. */
	//TODO: ST_NOEXEC      8    /* Disallow program execution. */
	//TODO: ST_SYNCHRONOUS 16   /* Writes are synced at once. */
	//TODO: ST_MANDLOCK    64   /* Allow mandatory locks on an FS. */
	//TODO: ST_WRITE       128  /* Write on file/directory/symlink. */
	//TODO: ST_APPEND      256  /* Append-only file. */
	//TODO: ST_IMMUTABLE   512  /* Immutable file. */
	//TODO: ST_NOATIME     1024 /* Do not update access times. */
	//TODO: ST_NODIRATIME  2048 /* Do not update directory access times. */
	//TODO: ST_RELATIME    4096 /* Update atime relative to mtime/ctime. */
	result->f_flags = fsflags;
}


/* Figure out where a given filesystem is mounted with a given namespace. */
PUBLIC WUNUSED NONNULL((1)) REF struct path *KCALL
superblock_getmountloc(struct superblock *__restrict self,
                       struct vfs const *__restrict ns)
		THROWS(E_WOULDBLOCK) {
	REF struct path *result;
	superblock_mountlock_read(self);
	result = self->s_mount;
	while (result) {
		if (result->p_vfs == ns) {
			/* Got it! */
			incref(result);
			break;
		}
		assert(result->p_mount);
		result = result->p_mount->mp_fsmount.ln_next;
	}
	superblock_mountlock_endread(self);
	return result;
}





PUBLIC NONNULL((1)) void KCALL
register_filesystem_type(struct superblock_type *__restrict type)
		THROWS(E_WOULDBLOCK) {
	struct superblock_type *iter;
	assertf(type->st_driver, "No owner defined");
	sync_write(&fs_filesystem_types.ft_typelock);
	/* Prevent the same filesystem type from being registered multiple times. */
	for (iter = fs_filesystem_types.ft_types; iter;
	     iter = iter->st_chain.sn_next) {
		if unlikely(iter == type) {
			sync_endwrite(&fs_filesystem_types.ft_typelock);
			return;
		}
	}
	SLIST_INSERT(fs_filesystem_types.ft_types, type, st_chain);
	incref(type->st_driver);
	sync_endwrite(&fs_filesystem_types.ft_typelock);
}

PUBLIC NONNULL((1)) void KCALL
unregister_filesystem_type(struct superblock_type *__restrict type)
		THROWS(E_WOULDBLOCK) {
	bool did_remove = false;
	struct superblock_type **piter, *iter;
	assertf(type->st_driver, "No owner defined");
	sync_write(&fs_filesystem_types.ft_typelock);
	for (piter = &fs_filesystem_types.ft_types;
	     (iter = *piter) != NULL; piter = &iter->st_chain.sn_next) {
		if (iter != type)
			continue;
		*piter     = type->st_chain.sn_next;
		did_remove = true;
		break;
	}
	sync_endwrite(&fs_filesystem_types.ft_typelock);
	if likely(did_remove)
		decref(type->st_driver);
}



PUBLIC struct filesystem_types fs_filesystem_types = {
	/* .ft_typelock = */ ATOMIC_RWLOCK_INIT,
	/* .ft_types    = */ NULL
};
DEFINE_DBG_BZERO_OBJECT(fs_filesystem_types.ft_typelock);


PUBLIC NONNULL((1)) REF struct superblock_type *KCALL
lookup_filesystem_type(USER CHECKED char const *name)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	REF struct superblock_type *result;
	char kernel_name[SUPERBLOCK_TYPE_NAME_MAX];
	size_t namelen = strnlen(name, SUPERBLOCK_TYPE_NAME_MAX - 1);
	assert(namelen <= SUPERBLOCK_TYPE_NAME_MAX - 1);
	if unlikely(namelen == SUPERBLOCK_TYPE_NAME_MAX - 1 &&
	            name[SUPERBLOCK_TYPE_NAME_MAX - 1] != 0)
		return NULL;
	memcpy(kernel_name, name, namelen, sizeof(char));
	kernel_name[namelen] = 0;
	atomic_rwlock_read(&fs_filesystem_types.ft_typelock);
	result = fs_filesystem_types.ft_types;
	for (; result; result = result->st_chain.sn_next) {
		if (strcmp(result->st_name, kernel_name) != 0)
			continue;
		if (driver_isfinalizing(result->st_driver))
			continue;
		if (!tryincref(result->st_driver))
			continue;
		break;
	}
	sync_endread(&fs_filesystem_types.ft_typelock);
	return result;
}






/* Open the given block-device as a superblock.
 * NOTE: If the given `device' has already been opened, return the existing
 *       filesystem or throw an `E_FSERROR_DEVICE_ALREADY_MOUNTED'
 *       error if the given type doesn't match the existing association.
 * @param: flags: Set of `SUPERBLOCK_F*'
 * @throws: E_FSERROR_DEVICE_ALREADY_MOUNTED: [...]
 * @throws: E_FSERROR_UNKNOWN_FILE_SYSTEM:    The driver associated with `type' is finalizing
 * @throws: E_FSERROR_NO_BLOCK_DEVICE:        [...]
 * @throws: E_FSERROR_WRONG_FILE_SYSTEM:      [...]
 * @throws: E_FSERROR_CORRUPTED_FILE_SYSTEM:  [...]
 * @throws: E_IOERROR:                        [...]
 * @throws: E_BADALLOC:                       [...] */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct superblock *KCALL
superblock_open(struct superblock_type *__restrict type,
                struct basic_block_device *device,
                uintptr_t flags, UNCHECKED USER char *args,
                bool *pnew_superblock_created)
		THROWS(E_FSERROR_DEVICE_ALREADY_MOUNTED, E_FSERROR_UNKNOWN_FILE_SYSTEM,
		       E_FSERROR_WRONG_FILE_SYSTEM, E_FSERROR_NO_BLOCK_DEVICE,
		       E_FSERROR_CORRUPTED_FILE_SYSTEM, E_IOERROR, E_BADALLOC,
		       E_SEGFAULT, E_WOULDBLOCK, ...) {
	struct heapptr resptr;
	REF struct superblock *result;
	assert(type);
	assert(type->st_sizeof_superblock >= sizeof(struct superblock));
	assert(!(flags & SUPERBLOCK_FUNMOUNTED));
	if (type->st_flags & SUPERBLOCK_TYPE_FSINGLE) {
		if (pnew_superblock_created)
			*pnew_superblock_created = false;
		/* Verify the basic integrity of the singleton superblock. */
		assert(type->st_driver);
		assert(type->st_singleton);
		assert(vm_datablock_isinode(type->st_singleton));
		assert(S_ISDIR(type->st_singleton->i_filemode));
		assert(type->st_singleton->s_type); /* NOTE: This doesn't have to be the same as `type'! */
		assert(type->st_singleton->i_super == type->st_singleton);
		assert(type->st_singleton->d_parent == NULL);
		return (REF struct superblock *)incref(type->st_singleton);
	}
	assert(type->st_open != NULL);
	if (type->st_flags & SUPERBLOCK_TYPE_FNODEV) {
		fs_filesystems_lock_write();
	} else {
		if unlikely(!device)
			THROW(E_FSERROR_NO_BLOCK_DEVICE);
		/* Search for an existing mapping of the given block-device. */
		fs_filesystems_lock_read();
		result = fs_filesystems.f_superblocks;
		for (; result; result = result->s_filesystems.sn_next) {
			if (result->s_device != device)
				continue;
			if (!tryincref(result))
				continue;
			if (result->s_type == type) {
				fs_filesystems_lock_endread();
				if (pnew_superblock_created)
					*pnew_superblock_created = false;
				return result;
			}
			fs_filesystems_lock_endread();
			decref_unlikely(result);
			THROW(E_FSERROR_DEVICE_ALREADY_MOUNTED);
		}
		if unlikely(!fs_filesystems_lock_upgrade()) {
			result = fs_filesystems.f_superblocks;
			for (; result; result = result->s_filesystems.sn_next) {
				if likely(result->s_device != device)
					continue;
				if (!tryincref(result))
					continue;
				if (result->s_type == type) {
					fs_filesystems_lock_endwrite();
					if (pnew_superblock_created)
						*pnew_superblock_created = false;
					return result;
				}
				fs_filesystems_lock_endwrite();
				decref_unlikely(result);
				THROW(E_FSERROR_DEVICE_ALREADY_MOUNTED);
			}
		}
	}
	TRY {
		/* Now that we're holding a lock to the filesystem list, check
		 * if the driver is being finalized. - If it is, don't allow new
		 * filesystems to be mounted with it. */
		if unlikely(driver_isfinalizing(type->st_driver))
			THROW(E_FSERROR_UNKNOWN_FILE_SYSTEM);

		/* Allocate a new superblock. */
		resptr = heap_alloc(FS_HEAP, type->st_sizeof_superblock, FS_GFP | GFP_CALLOC);
		TRY {
			assert(resptr.hp_siz >= type->st_sizeof_superblock);

			result            = (struct superblock *)resptr.hp_ptr;
			result->db_refcnt = 1;
			rwlock_cinit(&result->db_lock);
			result->db_type     = &inode_datablock_type;
			result->i_super     = result;
			result->i_heapsize  = resptr.hp_siz;
			result->i_filemode  = S_IFDIR;
			result->i_filenlink = (nlink_t)1;
			result->d_mask      = DIRECTORY_DEFAULT_MASK;
			result->d_map = (REF struct directory_entry **)kmalloc((DIRECTORY_DEFAULT_MASK + 1) *
			                                                       sizeof(REF struct directory_entry *),
			                                                       FS_GFP | GFP_CALLOC);
			result->s_type = type;
			if (!(type->st_flags & SUPERBLOCK_TYPE_FNODEV))
				result->s_device = incref(device);
			result->s_driver = type->st_driver;
			incref(result->s_driver);
			result->s_nodes = result;
			result->s_flags = flags;
			atomic_rwlock_cinit(&result->s_changed_lock);
			rwlock_cinit(&result->s_nodes_lock);
			atomic_rwlock_cinit(&result->s_mount_lock);
			/* Fill in filesystem features with documented default values. */
			result->s_features.sf_symlink_max = (pos_t)-1;
			result->s_features.sf_link_max    = (nlink_t)-1;
			assert(result->s_features.sf_rec_incr_xfer_size == 0);
			assert(result->s_features.sf_rec_max_xfer_size == 0);
			assert(result->s_features.sf_rec_min_xfer_size == 0);
			assert(result->s_features.sf_rec_xfer_align == 0);
			result->s_features.sf_name_max     = (u16)-1;
			result->s_features.sf_filesizebits = 64;
#ifndef NDEBUG
			/* The devfs is initialized statically, so `st_open' should never
			 * try to fill in the magic-field with its magic number. As such,
			 * we can check for an `st_open' callback that forgot to fill in
			 * this field by later checking if it's still set to this constant. */
			result->s_features.sf_magic = DEVFS_SUPER_MAGIC;
#endif /* !NDEBUG */
			/* Open the new superblock. */
			TRY {
				(*type->st_open)(result, args);
			} EXCEPT {
				kfree(result->d_map);
				decref(result->s_driver);
				decref_unlikely(result->s_device);
				if (was_thrown(E_IOERROR_BADBOUNDS) || was_thrown(E_DIVIDE_BY_ZERO) ||
				    was_thrown(E_OVERFLOW) || was_thrown(E_INDEX_ERROR))
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_CORRUPTED_FILE_SYSTEM));
				if (was_thrown(E_IOERROR_READONLY))
					PERTASK_SET(this_exception_code, ERROR_CODEOF(E_FSERROR_READONLY));
				RETHROW();
			}
#ifndef NDEBUG
			assertf(result->s_features.sf_magic != DEVFS_SUPER_MAGIC,
			        "Superblock initializer for %q forgot to fill in `s_features.sf_magic'",
			        type->st_name);
#endif /* !NDEBUG */
			/* Substitute default feature values. */
			if (result->s_features.sf_rec_incr_xfer_size == 0)
				result->s_features.sf_rec_incr_xfer_size = VM_DATABLOCK_PAGESIZE(result);
			if (result->s_features.sf_rec_max_xfer_size == 0)
				result->s_features.sf_rec_max_xfer_size = VM_DATABLOCK_PAGESIZE(result);
			if (result->s_features.sf_rec_min_xfer_size == 0)
				result->s_features.sf_rec_min_xfer_size = VM_DATABLOCK_PAGESIZE(result);
			if (result->s_features.sf_rec_xfer_align == 0)
				result->s_features.sf_rec_xfer_align = VM_DATABLOCK_PAGESIZE(result);
		} EXCEPT {
			heap_free(FS_HEAP, resptr.hp_ptr, resptr.hp_siz, FS_GFP);
			RETHROW();
		}
		/* Check that required fields have been initialized. */
		assert(result->db_refcnt != 0);
		assert(result->i_type != NULL);
		assert(result->s_type == type);
#ifndef CONFIG_VM_DATABLOCK_MIN_PAGEINFO
		result->db_addrshift = PAGESHIFT - result->db_pageshift;
		result->db_pagealign = (size_t)1 << result->db_pageshift;
		result->db_pagemask  = result->db_pagealign - 1;
		result->db_pagesize  = (size_t)PAGESIZE >> result->db_pageshift;
#endif /* !CONFIG_VM_DATABLOCK_MIN_PAGEINFO */
		/* Add the new superblock to the chain of known file-systems. */
		SLIST_INSERT(fs_filesystems.f_superblocks, result, s_filesystems);
	} EXCEPT {
		fs_filesystems_lock_endwrite();
		RETHROW();
	}
	fs_filesystems_lock_endwrite();
	if (pnew_superblock_created)
		*pnew_superblock_created = true;
	return result;
}












/* DATA BLOCK INTERFACE IMPLEMENTATION FOR INODES */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL inode_destroy)(struct inode *__restrict self) {
	assertf(!(self->i_flags & (INODE_FCHANGED | INODE_FATTRCHANGED)) ||
	        self == self->i_super,
	        "The changed-inode chain should have kept a reference");
	assertf(self->i_recent.ln_pself == NULL,
	        "The recently-used cache should have kept a reference");
	/* Run custom finalizers.
	 * NOTE: `i_type' may be `NULL' if the INode wasn't fully constructed. */
	if (self->i_type &&
	    self->i_type->it_fini)
		(*self->i_type->it_fini)(self);

	/* Finalize node-class-specific data. */
	if (INODE_ISDIR(self)) {
		struct directory_node *me;
		size_t i;
		assert(self->i_heapsize >= sizeof(struct directory_node));
		me = (struct directory_node *)self;
		if (me->d_map) { /* NOTE: `d_map' may be `NULL' if the INode wasn't fully constructed. */
			for (i = 0; i <= me->d_mask; ++i) {
				struct directory_entry *iter, *next;
				iter = me->d_map[i];
				while (iter) {
					next = iter->de_next;
					decref_likely(iter);
					iter = next;
				}
			}
			kfree(me->d_map);
		}
		xdecref(me->d_parent);
	} else if (INODE_ISLNK(self)) {
		assert(self->i_heapsize >= sizeof(struct symlink_node));
		if (self->i_flags & INODE_FLNKLOADED &&
		    ((struct symlink_node *)self)->sl_text != ((struct symlink_node *)self)->sl_stext)
			kfree(((struct symlink_node *)self)->sl_text);
	}
	if (INODE_ISSUPER(self)) {
		struct superblock *me;
		assert(INODE_ISDIR(self));
		assert(self->i_heapsize >= sizeof(struct superblock));
		me = (struct superblock *)self;
		/* Clear any remaining nodes still left to-be deleted. */
		superblock_clear_delnodes(me);
		assertf(me->s_nodes == self &&
		        self->i_filetree.a_min == NULL &&
		        self->i_filetree.a_max == NULL,
		        "Other nodes should have kept the superblock alive");
		assertf(me->s_mount == NULL || (me->s_flags & SUPERBLOCK_FMUSTUNMOUNT),
		        "Mounting point locations should have kept the superblock alive");
		assert(me->s_changed == NULL || (me->s_changed == self &&
		                                 (self->i_flags & (INODE_FCHANGED | INODE_FATTRCHANGED))));
		/* Invoke custom finalizers. */
		if (me->s_type &&
		    me->s_type->st_functions.f_fini)
			(*me->s_type->st_functions.f_fini)(me);
		xdecref(me->s_device);
		decref_unlikely(me->s_driver);

		if (!fs_filesystems_lock_trywrite()) {
			struct superblock *next;
			do {
				next = ATOMIC_READ(fs_filesystems_delblocks);
				*(struct superblock **)me = next;
			} while (!ATOMIC_CMPXCH_WEAK(fs_filesystems_delblocks, next, me));
			return;
		}
		fs_filesystems_remove(me);
		fs_filesystems_lock_endwrite();
	} else {
		struct superblock *super = self->i_super;
#if 0 /* Don't check this. - Something may have gone wrong \
       * during initialization of an otherwise persistent INode. */
		/* NOTE: If the INode was persistent, the caller must have already
		 *       removed it from the superblock's file tree. - Otherwise,
		 *       our reference counter should not have reached ZERO(0), as
		 *       the file tree itself should have carried one of our references! */
		if (!(self->i_flags & INODE_FPERSISTENT))
#endif
		{
			/* Remove the INode from the file tree of the associated superblock. */
			struct inode *next;
			if (!superblock_nodeslock_trywrite(super)) {
				do
					self->i_changed_next = next = ATOMIC_READ(super->s_delnodes);
				while (!ATOMIC_CMPXCH_WEAK(super->s_delnodes, next, self));
				superblock_nodeslock_tryservice(super);
				decref(super);
				return;
			}
			next = inode_tree_remove(&super->s_nodes, self->i_fileino);
			if (unlikely(next != self) && next) /* Re-insert if it wasn't us. */
				inode_tree_insert(&super->s_nodes, next);
			superblock_nodeslock_endwrite(super);
		}
		decref(super);
	}
	/* Free the INode. */
	heap_free(FS_HEAP, self, self->i_heapsize, FS_GFP);
}

PRIVATE NONNULL((1)) void KCALL
db_inode_loadpart(struct inode *__restrict self, datapage_t start,
                  vm_phys_t buffer, size_t num_data_pages) {
	struct inode_type *type = self->i_type;
	assert(type);
	if (!type->it_file.f_pread)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_READ);
	inode_loadattr(self);
	{
		size_t num_bytes;
		pos_t daddr, filesize;
		struct aio_multihandle_generic hand;
		daddr     = VM_DATABLOCK_DPAGE2DADDR(self, start);
		num_bytes = num_data_pages << VM_DATABLOCK_ADDRSHIFT(self);
		filesize  = self->i_filesize;
		COMPILER_READ_BARRIER();
		/* Deal with out-of-bound reads. */
		if unlikely(daddr + num_bytes >= filesize) {
			size_t num_oob_bytes;
			if unlikely(daddr >= filesize) {
				/* Entirely out-of-bounds */
				/* TODO: This can be skipped if the page was allocated from ZERO-memory! */
				vm_memsetphys(buffer, 0, num_bytes);
				return;
			}
			/* Partially out-of-bounds */
			num_oob_bytes = (size_t)((daddr + num_bytes) - filesize);
			assert(num_oob_bytes < num_bytes);
			num_bytes -= num_oob_bytes;
			/* TODO: This can be skipped if the page was allocated from ZERO-memory! */
			vm_memsetphys(buffer + num_bytes, 0, num_oob_bytes);
		}
		aio_multihandle_generic_init(&hand);
		TRY {
			SCOPED_READLOCK((struct vm_datablock *)self);
			(*type->it_file.f_pread)(self, buffer, num_bytes, daddr, &hand);
			aio_multihandle_done(&hand);
		} EXCEPT {
			aio_multihandle_fail(&hand);
		}
		TRY {
			aio_multihandle_generic_waitfor(&hand);
			aio_multihandle_generic_checkerror(&hand);
		} EXCEPT {
			aio_multihandle_generic_fini(&hand);
			RETHROW();
		}
		aio_multihandle_generic_fini(&hand);
	}
}

PRIVATE NONNULL((1)) void KCALL
db_inode_savepart(struct inode *__restrict self, datapage_t start,
                  vm_phys_t buffer, size_t num_data_pages) {
	struct inode_type *type = self->i_type;
	assert(type);
	if (!type->it_file.f_pwrite)
		THROW(E_FSERROR_UNSUPPORTED_OPERATION, (uintptr_t)E_FILESYSTEM_OPERATION_WRITE);
	{
		size_t num_bytes;
		pos_t daddr, filesize;
		struct aio_multihandle_generic hand;
		daddr     = VM_DATABLOCK_DPAGE2DADDR(self, start);
		num_bytes = num_data_pages << VM_DATABLOCK_ADDRSHIFT(self);
		filesize  = self->i_filesize;
		COMPILER_READ_BARRIER();
		/* Deal with out-of-bound writes. */
		if unlikely(daddr + num_bytes > filesize) {
			if unlikely(daddr >= filesize)
				return; /* Entirely out-of-bounds */
			/* Partially out-of-bounds */
			assert((size_t)(filesize - daddr) < num_bytes);
			num_bytes = (size_t)(filesize - daddr);
		}
		aio_multihandle_generic_init(&hand);
		TRY {
			SCOPED_WRITELOCK((struct vm_datablock *)self);
			(*type->it_file.f_pwrite)(self, buffer, num_bytes, daddr, &hand);
			aio_multihandle_done(&hand);
		} EXCEPT {
			aio_multihandle_fail(&hand);
		}
		TRY {
			aio_multihandle_generic_waitfor(&hand);
			aio_multihandle_generic_checkerror(&hand);
		} EXCEPT {
			aio_multihandle_generic_fini(&hand);
			RETHROW();
		}
		aio_multihandle_generic_fini(&hand);
	}
}

PRIVATE NONNULL((1, 2)) void KCALL
db_inode_changed(struct inode *__restrict self,
                 struct vm_datapart *__restrict UNUSED(part)) {
	inode_changed(self, INODE_FCHANGED);
}

PUBLIC struct vm_datablock_type inode_datablock_type = {
	/* .dt_destroy  = */ (NOBLOCK void(KCALL *)(struct vm_datablock *__restrict))&inode_destroy,
	/* .dt_initpart = */ NULL,
	/* .dt_loadpart = */ (void(KCALL *)(struct vm_datablock *__restrict,datapage_t,vm_phys_t,size_t))&db_inode_loadpart,
	/* .dt_savepart = */ (void(KCALL *)(struct vm_datablock *__restrict,datapage_t,vm_phys_t,size_t))&db_inode_savepart,
	/* .dt_changed  = */ (void(KCALL *)(struct vm_datablock *__restrict,struct vm_datapart *__restrict))&db_inode_changed
};



DECL_END

#ifndef __INTELLISENSE__
#undef DEFINE_IO_READ
#undef DEFINE_IO_WRITE
#undef DEFINE_IO_ASYNC
#undef DEFINE_IO_PHYS
#undef DEFINE_IO_VECTOR
#undef DEFINE_IO_KERNEL


#define DEFINE_IO_READ 1
#include "node-partio.c.inl"
#define DEFINE_IO_WRITE 1
#include "node-partio.c.inl"

/* Define `inode_a(read|write)[v][p]' */
#define DEFINE_IO_READ 1
#define DEFINE_IO_ASYNC 1
#include "node-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_PHYS 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_ASYNC 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_PHYS 1
#include "node-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_KERNEL 1
#include "node-io.c.inl"
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_READ 1
#define DEFINE_IO_KERNEL 1
#include "node-io.c.inl"

/* Define `inode_(read|write)[v][p]' */
#define DEFINE_IO_READ 1
#include "node-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#include "node-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_VECTOR 1
#include "node-io.c.inl"
#define DEFINE_IO_WRITE 1
#define DEFINE_IO_KERNEL 1
#include "node-io.c.inl"
#define DEFINE_IO_READ 1
#define DEFINE_IO_KERNEL 1
#include "node-io.c.inl"


/* Define `inode_[a]readall[v,p]' */
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_VECTOR 1
#include "node-extio.c.inl"
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_VECTOR 1
#include "node-extio.c.inl"
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_PHYS 1
#include "node-extio.c.inl"
#define DEFINE_IO_ASYNC 1
#define DEFINE_IO_KERNEL 1
#include "node-extio.c.inl"
#define DEFINE_IO_ASYNC 1
#include "node-extio.c.inl"
#define DEFINE_IO_PHYS 1
#define DEFINE_IO_VECTOR 1
#include "node-extio.c.inl"
#define DEFINE_IO_VECTOR 1
#include "node-extio.c.inl"
#define DEFINE_IO_PHYS 1
#include "node-extio.c.inl"
#define DEFINE_IO_KERNEL 1
#include "node-extio.c.inl"
/**/
#include "node-extio.c.inl"

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_CORE_FS_NODE_C */
