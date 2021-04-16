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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_SYSCALLS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/mman.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/remap.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <sys/mman.h>

#include <assert.h>
#include <errno.h>
#include <stddef.h>

DECL_BEGIN

/************************************************************************/
/* munmap()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MUNMAP
DEFINE_SYSCALL2(errno_t, munmap, void *, addr, size_t, length) {
	mman_unmap(THIS_MMAN, addr, length, MMAN_UNMAP_NOKERNPART);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MUNMAP */





/************************************************************************/
/* mprotect()                                                           */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MPROTECT
DEFINE_SYSCALL3(errno_t, mprotect,
                USER UNCHECKED void *, addr,
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
sys_mmap_impl(void *addr, size_t length, syscall_ulong_t prot,
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
	                 ? (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED)
	                 : (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE),
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
		hand = handle_lookup(fd);
#ifndef NDEBUG
		file.hmi_file = NULL;
#endif /* !NDEBUG */
		TRY {
			handle_mmap(hand, &file);
#ifndef NDEBUG
			assert(file.hmi_file != NULL);
#endif /* !NDEBUG */
		} EXCEPT {
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
                void *, addr, size_t, length, syscall_ulong_t, prot,
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
                void *, addr, size_t, length, syscall_ulong_t, prot,
                syscall_ulong_t, flags, fd_t, fd, syscall_ulong_t, pgoffset) {
	return sys_mmap_impl(addr, length, prot, flags, fd, (pos_t)pgoffset * PAGESIZE);
}
#endif /* __ARCH_WANT_SYSCALL_MMAP2 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_MMAP2
DEFINE_COMPAT_SYSCALL6(void *, mmap2,
                       void *, addr, size_t, length, syscall_ulong_t, prot,
                       syscall_ulong_t, flags, fd_t, fd, syscall_ulong_t, pgoffset) {
	return sys_mmap_impl(addr, length, prot, flags, fd, (pos_t)pgoffset * PAGESIZE);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_MMAP2 */




/************************************************************************/
/* mremap()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MREMAP
DEFINE_SYSCALL5(void *, mremap,
                void *, old_address, size_t, old_size, size_t, new_size,
                syscall_ulong_t, flags, void *, new_address) {
	void *result;

	/* Validate flags. */
	VALIDATE_FLAGSET(flags,
	                 MREMAP_MAYMOVE | MREMAP_FIXED | MREMAP_32BIT | MREMAP_GROWSDOWN |
	                 MREMAP_GROWSUP | MREMAP_STACK | MREMAP_FIXED_NOREPLACE | MREMAP_NOASLR,
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



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_SYSCALLS_C */
