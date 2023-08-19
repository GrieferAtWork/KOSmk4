/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_SYSCALLS_C 1
#define __WANT_MNODE__mn_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/path.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/mman.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mlock.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/msync.h>
#include <kernel/mman/remap.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/paging.h>
#include <sys/mman.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/************************************************************************/
/* munmap()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MUNMAP
DEFINE_SYSCALL2(errno_t, munmap, NCX UNCHECKED void *, addr, size_t, length) {
	mman_unmap(THIS_MMAN, addr, length, MMAN_UNMAP_NOKERNPART);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MUNMAP */





/************************************************************************/
/* mprotect()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MPROTECT
DEFINE_SYSCALL3(errno_t, mprotect,
                NCX UNCHECKED void *, addr,
                size_t, length,
                syscall_ulong_t, prot) {
	VALIDATE_FLAGSET(prot,
	                 PROT_EXEC | PROT_WRITE | PROT_READ,
	                 E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT);
	mman_protect(THIS_MMAN, addr, length,
	             PROT_READ | PROT_WRITE | PROT_EXEC, prot,
	             MMAN_UNMAP_NOKERNPART);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MPROTECT */





/************************************************************************/
/* mmap()                                                               */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_MMAP) ||  \
     defined(__ARCH_WANT_SYSCALL_MMAP2) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_MMAP2))
#define WANT_MMAP 1
#endif /* __ARCH_WANT_... */

#ifdef WANT_MMAP
PRIVATE void *KCALL
sys_mmap_impl(NCX UNCHECKED void *addr, size_t length, syscall_ulong_t prot,
              syscall_ulong_t flags, fd_t fd, pos_t file_offset) {
	void *result;
	struct handle_mmap_info file;

	/* Check for unknown flags:
	 * MAP_TYPE:
	 *    MAP_AUTOMATIC  -- Accept `PROT_SHARED' bit in `prot'
	 *    MAP_SHARED     -- Set `PROT_SHARED'    (`PROT_SHARED' must not be given)
	 *    MAP_PRIVATE    -- Clear `PROT_SHARED'  (`PROT_SHARED' must not be given)
	 * MAP_FIXED:            Supported
	 * MAP_FILE:             Supported
	 * MAP_ANONYMOUS:        Supported
	 * MAP_32BIT:            Supported
	 * MAP_GROWSDOWN:        Supported
	 * MAP_GROWSUP:          Supported
	 * MAP_DENYWRITE:        Supported (Ignored as intended)
	 * MAP_EXECUTABLE:       Supported (Ignored as intended)
	 * MAP_LOCKED:           Supported
	 * MAP_NORESERVE:        Unsupported/Ignored (currently, all mappings behave as NORESERVE)
	 * MAP_POPULATE:         Supported
	 * MAP_NONBLOCK:         Supported
	 * MAP_STACK:            Supported (alters default selection of automatic base addresses)
	 * MAP_HUGETLB:          Unsupported/Ignored (huge paging tables are always created if possible)
	 * MAP_HUGE_MASK:        Unsupported/Ignored (*ditto*)
	 * MAP_UNINITIALIZED:    Supported (but special permissions are required)
	 * MAP_FIXED_NOREPLACE:  Supported
	 * MAP_OFFSET64_POINTER: Supported (but handled in `sys_mmap(2)')
	 */
	VALIDATE_FLAGSET(flags,
	                 MAP_AUTOMATIC | MAP_SHARED | MAP_PRIVATE | MAP_FIXED |
	                 MAP_FILE | MAP_ANONYMOUS | MAP_32BIT | MAP_GROWSDOWN |
	                 MAP_GROWSUP | MAP_DENYWRITE | MAP_EXECUTABLE | MAP_LOCKED |
	                 MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK |
	                 MAP_HUGETLB | (MAP_HUGE_MASK << MAP_HUGE_SHIFT) |
	                 MAP_UNINITIALIZED | MAP_FIXED_NOREPLACE,
	                 E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG);

	/* Make sure a known type of mapping was requested. */
	if unlikely((flags & MAP_TYPE) != MAP_AUTOMATIC &&
	            (flags & MAP_TYPE) != MAP_SHARED &&
	            (flags & MAP_TYPE) != MAP_PRIVATE) {
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_MASK,
		      E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG,
		      flags,
		      MAP_TYPE);
	}

	/* Make sure that at most one of `MAP_GROWSDOWN' and `MAP_GROWSUP' was specified */
	if ((flags & (MAP_GROWSDOWN | MAP_GROWSUP)) == (MAP_GROWSDOWN | MAP_GROWSUP)) {
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG,
		      flags,
		      MAP_GROWSDOWN | MAP_GROWSUP,
		      MAP_GROWSDOWN | MAP_GROWSUP);
	}

	/* Make sure that no unknown protection flags have been set. */
	VALIDATE_FLAGSET(prot,
	                 (flags & MAP_TYPE) == MAP_AUTOMATIC
	                 ? (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED)
	                 : (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM),
	                 E_INVALID_ARGUMENT_CONTEXT_MMAP_PROT);

	/* Handle MAP_SHARED via the associated protection flag. */
	if ((flags & MAP_TYPE) == MAP_SHARED)
		prot |= PROT_SHARED;

	/* Figure out what file is supposed to end up being mapped. */
	file.hmi_minaddr = (pos_t)0;
	file.hmi_maxaddr = (pos_t)-1;
	file.hmi_fspath  = NULL;
	file.hmi_fsname  = NULL;
	if (flags & MAP_ANONYMOUS) {
		/* Anonymous memory! */
		file.hmi_file = &mfile_zero;

		/* If requested by the caller, and  if we're allowed to do  so,
		 * then allow the user to directly mmap() uninitialized memory.
		 * Otherwise,  we ignore the  `MAP_UNINITIALIZED' flag and just
		 * pass back zero-memory no matter what the caller wants! */
		if ((flags & MAP_UNINITIALIZED) && capable(CAP_MMAP_UNINITIALIZED))
			file.hmi_file = &mfile_ndef;

		incref(file.hmi_file);
	} else {
		/* Specific file. */
		REF struct handle hand;
		hand = handles_lookup(fd);
#ifndef NDEBUG
		file.hmi_file = NULL;
#endif /* !NDEBUG */
		TRY {
			if (((hand.h_mode & IO_ACCMODE) == IO_WRONLY) ||
			    ((hand.h_mode & IO_APPEND) && (prot & PROT_WRITE))) {
				/* File mappings always require files to be opened with at least read-access:
				 * """
				 * EACCES [...] a file mapping was requested, but fd is not open for reading. [...]
				 * """
				 *
				 * Additionally,  a IO_APPEND  file must  not be  mapped with write-access.
				 * I don't really understand why this shouldn't be allowed, but whatever...
				 * """
				 * EACCES [...] PROT_WRITE is set, but the file is append-only. [...]
				 * """ */
				THROW(E_INVALID_HANDLE_OPERATION, fd,
				      E_INVALID_HANDLE_OPERATION_MMAP,
				      hand.h_mode);
			} else if ((hand.h_mode & IO_ACCMODE) != IO_RDWR && (prot & PROT_SHARED)) {
				if (prot & PROT_WRITE) {
					/* You're not allowed to create a WRITE+SHARED mapping using a
					 * file  descriptor opened for anything other than read+write.
					 *
					 * """
					 * EACCES [...] MAP_SHARED was requested and PROT_WRITE is set,
					 *        but fd is not open in read/write (O_RDWR) mode. [...]
					 * """ */
					THROW(E_INVALID_HANDLE_OPERATION, fd,
					      E_INVALID_HANDLE_OPERATION_MMAP,
					      hand.h_mode);
				}
				/* Disallow use of mprotect() to gain write-access. */
				prot |= PROT_DENYWRITE;
			}


			handle_mmap(hand, &file);
#ifndef NDEBUG
			assert(file.hmi_file != NULL);
#endif /* !NDEBUG */
		} EXCEPT {
			xdecref_unlikely(file.hmi_fspath);
			xdecref_unlikely(file.hmi_fsname);
			decref(hand);
			RETHROW();
		}
		decref(hand);
	}
	FINALLY_DECREF_UNLIKELY(file.hmi_file);
	FINALLY_XDECREF_UNLIKELY(file.hmi_fspath);
	FINALLY_XDECREF_UNLIKELY(file.hmi_fsname);

	/* Actually perform the requested operation! */
	result = mman_map_subrange(/* self:             */ THIS_MMAN,
	                           /* hint:             */ addr,
	                           /* num_bytes:        */ length,
	                           /* prot:             */ (unsigned int)prot,
	                           /* flags:            */ (unsigned int)flags,
	                           /* file:             */ file.hmi_file,
	                           /* file_fspath:      */ file.hmi_fspath,
	                           /* file_fsname:      */ file.hmi_fsname,
	                           /* file_pos:         */ file.hmi_minaddr + file_offset,
	                           /* file_map_minaddr: */ file.hmi_minaddr,
	                           /* file_map_maxaddr: */ file.hmi_maxaddr);

	/* Return the address where the mapping was created. */
	return result;
}
#endif /* WANT_MMAP */

#ifdef __ARCH_WANT_SYSCALL_MMAP
DEFINE_SYSCALL6(void *, mmap,
                NCX UNCHECKED void *, addr, size_t, length, syscall_ulong_t, prot,
                syscall_ulong_t, flags, fd_t, fd, syscall_ulong_t, offset) {
	pos_t file_offset = (pos_t)offset;
	if (flags & MAP_OFFSET64_POINTER) {
		validate_readable((byte_t const *)(uintptr_t)offset, 8);
		COMPILER_READ_BARRIER();
		file_offset = (pos_t)(*(u64 const *)(uintptr_t)offset);
		COMPILER_READ_BARRIER();
		flags &= ~MAP_OFFSET64_POINTER;
	}
	return sys_mmap_impl(addr, length, prot, flags, fd, file_offset);
}
#endif /* __ARCH_WANT_SYSCALL_MMAP */

#ifdef __ARCH_WANT_SYSCALL_MMAP2
DEFINE_SYSCALL6(void *, mmap2,
                NCX UNCHECKED void *, addr, size_t, length, syscall_ulong_t, prot,
                syscall_ulong_t, flags, fd_t, fd, syscall_ulong_t, pgoffset) {
	return sys_mmap_impl(addr, length, prot, flags, fd, (pos_t)pgoffset * PAGESIZE);
}
#endif /* __ARCH_WANT_SYSCALL_MMAP2 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_MMAP2
DEFINE_COMPAT_SYSCALL6(void *, mmap2,
                       NCX UNCHECKED void *, addr, size_t, length, syscall_ulong_t, prot,
                       syscall_ulong_t, flags, fd_t, fd, syscall_ulong_t, pgoffset) {
	return sys_mmap_impl(addr, length, prot, flags, fd, (pos_t)pgoffset * PAGESIZE);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_MMAP2 */




/************************************************************************/
/* mremap()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MREMAP
DEFINE_SYSCALL5(void *, mremap,
                NCX UNCHECKED void *, old_address, size_t, old_size, size_t, new_size,
                syscall_ulong_t, flags, NCX UNCHECKED void *, new_address) {
	void *result;

	/* Validate flags. */
	VALIDATE_FLAGSET(flags,
	                 MREMAP_MAYMOVE | MREMAP_FIXED | MREMAP_32BIT |
	                 MREMAP_GROWSDOWN | MREMAP_GROWSUP | MREMAP_STACK |
	                 MREMAP_POPULATE | MREMAP_NONBLOCK |
	                 MREMAP_FIXED_NOREPLACE | MREMAP_NOASLR,
	                 E_INVALID_ARGUMENT_CONTEXT_MREMAP_FLAGS);

	/* Special case: mman_remap() still uses `new_address' as re-map hint,
	 *               even when `MREMAP_FIXED' isn't  set (so we must  give
	 *               it the default mmap(NULL)-style hint!) */
	if (!(flags & MREMAP_FIXED))
		new_address = NULL;

	/* Do the actual mremap() operation. */
	result = mman_remap(/* self:        */ THIS_MMAN,
	                    /* old_address: */ old_address,
	                    /* old_size:    */ old_size,
	                    /* new_size:    */ new_size,
	                    /* flags:       */ (unsigned int)flags,
	                    /* new_address: */ new_address);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_MREMAP */




/************************************************************************/
/* mlock(), mlock2(), munlock(), mlockall(), munlockall()               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MLOCK
DEFINE_SYSCALL2(errno_t, mlock,
                NCX UNCHECKED void const *, addr, size_t, len) {
	mman_mlock(THIS_MMAN, addr, len);
	return EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MLOCK */

#ifdef __ARCH_WANT_SYSCALL_MLOCK2
DEFINE_SYSCALL3(errno_t, mlock2,
                NCX UNCHECKED void const *, addr, size_t, len,
                syscall_ulong_t, flags) {
	VALIDATE_FLAGSET(flags, 0 | MLOCK_ONFAULT,
	                 E_INVALID_ARGUMENT_CONTEXT_MLOCK2_FLAGS);
	mman_mlock(THIS_MMAN, addr, len, flags);
	return EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MLOCK2 */

#ifdef __ARCH_WANT_SYSCALL_MUNLOCK
DEFINE_SYSCALL2(errno_t, munlock,
                NCX UNCHECKED void const *, addr, size_t, len) {
	mman_munlock(THIS_MMAN, addr, len);
	return EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MUNLOCK */

#ifdef __ARCH_WANT_SYSCALL_MLOCKALL
DEFINE_SYSCALL1(errno_t, mlockall, syscall_ulong_t, flags) {
	unsigned int mlock_flags = MLOCK_NOW;
	VALIDATE_FLAGSET(flags, MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT,
	                 E_INVALID_ARGUMENT_CONTEXT_MLOCKALL_FLAGS);
	/* NOTE: Currently, only `MCL_ONFAULT' has an affect. The
	 *       other  flags  are recognized  (for compatibility
	 *       with linux), but are otherwise ignored. */
	if (flags & MCL_ONFAULT)
		mlock_flags |= MLOCK_ONFAULT;
	mman_mlockall(THIS_MMAN, mlock_flags);
	return EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MLOCKALL */

#ifdef __ARCH_WANT_SYSCALL_MUNLOCKALL
DEFINE_SYSCALL0(errno_t, munlockall) {
	mman_munlockall(THIS_MMAN);
	return EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MUNLOCKALL */




/************************************************************************/
/* msync()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MSYNC
DEFINE_SYSCALL3(errno_t, msync,
                NCX UNCHECKED void *, addr, size_t, len,
                syscall_ulong_t, flags) {
	VALIDATE_FLAGSET(flags, MS_SYNC | MS_ASYNC | MS_INVALIDATE,
	                 E_INVALID_ARGUMENT_CONTEXT_MSYNC_FLAGS);
#if MS_SYNC != 0 && MS_ASYNC != 0 && MS_SYNC != MS_ASYNC
	if unlikely((flags & (MS_SYNC | MS_ASYNC)) == (MS_SYNC | MS_ASYNC)) {
		/* Mustn't specify both of these! */
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_MSYNC_FLAGS,
		      flags, MS_SYNC | MS_ASYNC, MS_SYNC | MS_ASYNC);
	}
#endif /* MS_SYNC != 0 && MS_ASYNC != 0 && MS_SYNC != MS_ASYNC */
	mman_msync(THIS_MMAN, addr, len, flags);
	return EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MSYNC */




/************************************************************************/
/* mincore()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MINCORE
DEFINE_SYSCALL3(errno_t, mincore,
                NCX UNCHECKED void *, addr, size_t, len,
                NCX UNCHECKED uint8_t *, vec) {
#define MPART_BLOCK_ST_MINCORE(st) ((st) >= MPART_BLOCK_ST_LOAD)
	static_assert(!MPART_BLOCK_ST_MINCORE(MPART_BLOCK_ST_NDEF));
	static_assert(!MPART_BLOCK_ST_MINCORE(MPART_BLOCK_ST_INIT));
	static_assert(MPART_BLOCK_ST_MINCORE(MPART_BLOCK_ST_LOAD));
	static_assert(MPART_BLOCK_ST_MINCORE(MPART_BLOCK_ST_CHNG));
	NCX UNCHECKED byte_t *maxaddr;
	NCX PAGEDIR_PAGEALIGNED byte_t *iter;
	struct mman *mm = THIS_MMAN;
	if unlikely(!IS_ALIGNED((uintptr_t)addr, PAGESIZE)) {
		THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
		      E_INVALID_ARGUMENT_CONTEXT_MINCORE_ADDR,
		      addr, PAGEMASK);
	}
	if unlikely(OVERFLOW_UADD(len, PAGEMASK, &len)) {
err_badlen:
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_MINCORE_SIZE,
		      len);
	}
	len &= ~PAGEMASK;
	if unlikely(OVERFLOW_UADD((uintptr_t)addr, len - 1, (uintptr_t *)&maxaddr)) {
		if unlikely(!len)
			return EOK; /* Special case (ignore empty length requests) */
		goto err_badlen;
	}
	validate_writable(vec, (len / PAGESIZE) * sizeof(uint8_t));
#ifdef USERSPACE_END
	if (maxaddr >= (byte_t *)USERSPACE_END) {
		size_t pages_before, pages_after;
		if (ADDR_ISKERN(addr)) {
			bzero(vec, len / PAGESIZE, sizeof(uint8_t));
			return EOK;
		}
		pages_before = ((byte_t *)USERSPACE_END - (byte_t *)addr) / PAGESIZE;
		pages_after  = ((size_t)(maxaddr - (byte_t *)USERSPACE_END) + 1) / PAGESIZE;
		bzero(vec + pages_before, pages_after, sizeof(uint8_t));
		maxaddr = (byte_t *)USERSPACE_END - 1;
	}
#endif /* USERSPACE_END */
#if defined(USERSPACE_START) && USERSPACE_START != 0
	if ((byte_t *)addr < (byte_t *)USERSPACE_START) {
		size_t pages_before;
		if (ADDR_ISKERN(maxaddr)) {
			bzero(vec, len / PAGESIZE, sizeof(uint8_t));
			return EOK;
		}
		pages_before = (size_t)((byte_t *)USERSPACE_START - (byte_t *)addr) / PAGESIZE;
		bzero(vec, pages_before, sizeof(uint8_t));
		vec += pages_before;
		addr = (NCX UNCHECKED void *)USERSPACE_START;
	}
#endif /* USERSPACE_START != 0 */
	for (iter = (NCX PAGEDIR_PAGEALIGNED byte_t *)addr;
	     iter < maxaddr;) {
		struct mnode *node;
		struct mpart *part;
		struct mfile *file;
		byte_t *node_minaddr, *node_maxaddr;
		mpart_reladdr_t partrel_addr;
		size_t partrel_size, partrel_maxsize;
		size_t blocksize;
		uint8_t incore_status;
		size_t partrel_block_index;
		size_t partrel_block_count;
again_lock_mman:
		mman_lock_read(mm);
		node = mman_mappings_locate(mm, iter);
		if unlikely(!node) {
			mman_lock_endread(mm);
			THROW(E_SEGFAULT_UNMAPPED, iter, E_SEGFAULT_CONTEXT_FAULT);
		}
		/* For each page, check if it's been loaded from-disk.
		 * iow: Has a block-state `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG' */
		node_minaddr = (byte_t *)mnode_getminaddr(node);
		node_maxaddr = (byte_t *)mnode_getmaxaddr(node);
		if (node_minaddr < iter)
			node_minaddr = iter;
		if (node_maxaddr > maxaddr)
			node_maxaddr = maxaddr;
		partrel_addr = node->mn_partoff + (size_t)(iter - node_minaddr);
		partrel_size = (size_t)(node_maxaddr - node_minaddr) + 1;
		if ((part = node->mn_part) == NULL) {
			mman_lock_endread(mm);
			assert(partrel_size >= PAGESIZE);
			/* Special case: reserved node */
			incore_status = 0x00;
			goto copyinfo_and_continue;
		}
		/* Acquire a lock to the part while we're still  holding
		 * a lock to the mman, thus ensuring that `partrel_addr'
		 * continues  to be correct, and `partrel_size' is still
		 * going to be in-bounds of the part. */
		incref(part);
		if unlikely(!mpart_lock_tryacquire(part)) {
			mman_lock_endread(mm);
			FINALLY_DECREF_UNLIKELY(part);
			mpart_lock_waitfor(part);
			goto again_lock_mman;
		}
		mman_lock_endread(mm);
		assert(partrel_size >= PAGESIZE);
		/* Calculate the block-status address range that's in control here. */
		file                = part->mp_file;
		partrel_block_index = partrel_addr >> file->mf_blockshift;
		partrel_block_count = (partrel_size + file->mf_part_amask) >> file->mf_blockshift;
		blocksize           = mfile_getblocksize(file);
		assert(partrel_block_count != 0);
#define mpart_isblockincore(self, partrel_block_index) \
	(MPART_BLOCK_ST_MINCORE(mpart_getblockstate(self, partrel_block_index)) ? 0x01 : 0x00)
		incore_status   = mpart_isblockincore(part, partrel_block_index);
		partrel_maxsize = partrel_size;
		partrel_size    = blocksize;
		++partrel_block_index;
		--partrel_block_count;
		/* Scan ahead until we reach the end of the affected block-range, or
		 * until we encounter a block  with a different in-core status  than
		 * what we've seen thus far. */
		for (; partrel_block_count; ++partrel_block_index, --partrel_block_count) {
			uint8_t new_status;
			new_status = mpart_isblockincore(part, partrel_block_index);
			if (new_status != incore_status)
				break;
			partrel_size += blocksize;
		}
#undef mpart_isblockincore
		mpart_lock_release(part);
		decref_unlikely(part);
		if (partrel_size > partrel_maxsize)
			partrel_size = partrel_maxsize;

		/* Copy block status information into the given user-space vector. */
copyinfo_and_continue:
		memset(vec, incore_status, partrel_size / PAGESIZE, sizeof(uint8_t));
		iter += partrel_size;
		vec += partrel_size / PAGESIZE;
	}
	return EOK;
#undef MPART_BLOCK_ST_MINCORE
}
#endif /* __ARCH_WANT_SYSCALL_MINCORE */




/************************************************************************/
/* madvise()                                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MADVISE
DEFINE_SYSCALL3(errno_t, madvise,
                NCX UNCHECKED void *, addr, size_t, num_bytes,
                syscall_ulong_t, advice) {
	switch (advice) {

	case MADV_POPULATE_READ:
	case MADV_POPULATE_WRITE:
		/* Special handling for `MADV_POPULATE_READ' and `MADV_POPULATE_WRITE',
		 * which we implement via `mman_prefault()'  rather than on a  per-node
		 * basis! */
		validate_user(addr, num_bytes);
		mman_prefault(addr, num_bytes,
		              advice == MADV_POPULATE_READ ? MMAN_FAULT_F_NORMAL
		                                           : MMAN_FAULT_F_WRITE);
		break;

	case MADV_NORMAL:
	case MADV_RANDOM:
	case MADV_SEQUENTIAL:
	case MADV_WILLNEED:
	case MADV_DONTNEED:
	case MADV_FREE:
	/*case MADV_REMOVE:*/   /* Unsupported... */
	/*case MADV_DONTFORK:*/ /* TODO: Support me! */
	/*case MADV_DOFORK:*/   /* TODO: Support me! */
	case MADV_MERGEABLE:
	case MADV_UNMERGEABLE:
	case MADV_HUGEPAGE:
	case MADV_NOHUGEPAGE:
	case MADV_DONTDUMP:
	case MADV_DODUMP:
	/*case MADV_WIPEONFORK:*/ /* TODO: Support me! */
	/*case MADV_KEEPONFORK:*/ /* TODO: Support me! */
	case MADV_COLD:
	case MADV_PAGEOUT:
	case MADV_HWPOISON:
	case MADV_SOFT_OFFLINE:
		mman_madvise(THIS_MMAN, addr, num_bytes, advice, MMAN_UNMAP_NOKERNPART);
		break;

	default:
		/* Unsupported advice. */
		THROW(E_INVALID_ARGUMENT_UNEXPECTED_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_MADVISE_BAD_ADVICE,
		      advice);
		break;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MADVISE */

/* TODO: errno_t sys_remap_file_pages(void *start, size_t size, syscall_ulong_t prot, size_t pgoff, syscall_ulong_t flags) */
/* TODO: errno_t sys_uselib(char const *library); */
/* TODO: ssize_t sys_process_vm_readv(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags); */
/* TODO: ssize_t sys_process_vm_writev(pid_t pid, struct iovec const *local_iov, size_t liovcnt, struct iovec const *remote_iov, size_t riovcnt, syscall_ulong_t flags); */

DECL_END




/************************************************************************/
/* maplibrary()                                                         */
/************************************************************************/
#ifndef __INTELLISENSE__
#ifdef __ARCH_WANT_SYSCALL_MAPLIBRARY
#define DEFINE_sys_maplibrary
#include "syscalls-maplibrary.c.inl"
#endif /* __ARCH_WANT_SYSCALL_MAPLIBRARY */
#ifdef __ARCH_WANT_COMPAT_SYSCALL_MAPLIBRARY
#define DEFINE_compat_sys_maplibrary
#include "syscalls-maplibrary.c.inl"
#endif /* __ARCH_WANT_COMPAT_SYSCALL_MAPLIBRARY */
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_SYSCALLS_C */
