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
#ifndef GUARD_KERNEL_SRC_MEMORY_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_SYSCALLS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/vm.h>
#include <kernel/vm/usermod.h>
#include <sched/cred.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except/reason/inval.h>
#include <kos/exec/elf.h>
#include <sys/mman.h>

#include <assert.h>
#include <elf.h>
#include <errno.h>
#include <string.h>

/* TODO: Completely re-write this file for use with the new mman! */

DECL_BEGIN

STATIC_ASSERT(PROT_NONE   == VM_PROT_NONE);
STATIC_ASSERT(PROT_EXEC   == VM_PROT_EXEC);
STATIC_ASSERT(PROT_WRITE  == VM_PROT_WRITE);
STATIC_ASSERT(PROT_READ   == VM_PROT_READ);
STATIC_ASSERT(PROT_SHARED == VM_PROT_SHARED);
#ifdef VM_PROT_LOOSE
STATIC_ASSERT(PROT_LOOSE  == VM_PROT_LOOSE);
#endif /* VM_PROT_LOOSE */

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

LOCAL void KCALL
getdatablock_from_handle(unsigned int fd,
                         struct handle_mmap_info *__restrict info) {
	struct handle hnd = handle_lookup(fd);
	TRY {
#ifndef NDEBUG
		info->hmi_file = NULL;
#endif /* !NDEBUG */
		info->hmi_minaddr = (pos_t)0;
		info->hmi_maxaddr = (pos_t)-1;
		info->hmi_fspath  = NULL;
		info->hmi_fsname  = NULL;
		handle_mmap(hnd, info);
#ifndef NDEBUG
		assert(info->hmi_file != NULL);
#endif /* !NDEBUG */
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
}





/************************************************************************/
/* munmap()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MUNMAP
DEFINE_SYSCALL2(errno_t, munmap, void *, addr, size_t, length) {
	size_t offset;
	offset = (uintptr_t)addr & PAGEMASK;
	addr   = (void *)((uintptr_t)addr & ~PAGEMASK);
	if (OVERFLOW_UADD(length, offset, &length))
		length = (size_t)-1;
	if (vm_unmap(THIS_MMAN,
	             addr,
	             CEIL_ALIGN(length, PAGESIZE),
	             VM_UNMAP_ANYTHING |
	             VM_UNMAP_NOKERNPART)) {
#ifdef CONFIG_HAVE_USERMOD
		vm_clear_usermod(THIS_MMAN);
#endif /* CONFIG_HAVE_USERMOD */
	}
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
	size_t offset;
	offset = (uintptr_t)addr & PAGEMASK;
	addr   = (void *)((uintptr_t)addr & ~PAGEMASK);
	if (OVERFLOW_UADD(length, offset, &length))
		length = (size_t)-1;
	VALIDATE_FLAGSET(prot,
	                 PROT_EXEC | PROT_WRITE | PROT_READ,
	                 E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT);
	vm_protect(THIS_MMAN,
	           addr,
	           CEIL_ALIGN(length, PAGESIZE),
	           VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC,
	           prot,
	           VM_UNMAP_ANYTHING | VM_UNMAP_NOKERNPART);
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
	byte_t *result;
	uintptr_t result_offset;
	REF struct vm_datablock *datablock;           /* [1..1] */
	REF struct path *datablock_fspath;            /* [0..1] */
	REF struct directory_entry *datablock_fsname; /* [0..1] */
	pos_t file_minoffset;
	pos_t file_maxnumbytes;
	/* Check for unknown flags. */
	assert(!task_wasconnected());
	VALIDATE_FLAGSET(flags,
	                 MAP_AUTOMATIC | MAP_SHARED | MAP_PRIVATE | MAP_FIXED |
	                 MAP_FILE | MAP_ANONYMOUS | MAP_32BIT | MAP_GROWSDOWN |
	                 MAP_GROWSUP | MAP_DENYWRITE | MAP_EXECUTABLE | MAP_LOCKED |
	                 MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK |
	                 MAP_HUGETLB | (MAP_HUGE_MASK << MAP_HUGE_SHIFT) |
	                 MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE |
	                 MAP_OFFSET64_POINTER,
	                 E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG);
	/* Make sure a known type of mapping was requested. */
	if ((flags & MAP_TYPE) != MAP_AUTOMATIC &&
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
	if ((flags & MAP_TYPE) == MAP_SHARED)
		prot |= PROT_SHARED;
	result_offset = (uintptr_t)file_offset & PAGEMASK;
	if (flags & MAP_ANONYMOUS) {
		result_offset = 0;
		if (flags & MAP_FIXED)
			result_offset = (uintptr_t)addr & PAGEMASK;
	} else {
		if (flags & MAP_FIXED) {
			if (result_offset != ((uintptr_t)addr & PAGEMASK)) {
				THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
				      E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR,
				      (uintptr_t)addr,
				      PAGEMASK,
				      result_offset);
			}
		}
	}

	/* Load the requested data block. */
	file_minoffset   = 0;
	file_maxnumbytes = (pos_t)-1;
	/* Figure out which datablock should be mapped. */
	datablock_fspath = NULL;
	datablock_fsname = NULL;
	if (!(flags & MAP_ANONYMOUS)) {
		struct handle_mmap_info info;
		/* File mapping */
		getdatablock_from_handle((unsigned int)fd, &info);
		datablock        = info.hmi_file;
		file_minoffset   = info.hmi_minaddr;
		file_maxnumbytes = (info.hmi_maxaddr - info.hmi_minaddr) + 1;
		datablock_fspath = info.hmi_fspath;
		datablock_fsname = info.hmi_fsname;
	} else if (!(flags & MAP_UNINITIALIZED) ||
	           !capable(CAP_MMAP_UNINITIALIZED)) {
		/* Zero-initialized, anonymous memory */
		datablock = incref(&vm_datablock_anonymous_zero);
	} else {
		/* Uninitialized, anonymous memory */
		datablock = incref(&vm_datablock_anonymous);
	}
	/* Make sure that the offset and byte counts are aligned by the pagesize. */
	if (OVERFLOW_UADD(file_maxnumbytes, file_minoffset & PAGEMASK, &file_maxnumbytes) ||
	    OVERFLOW_UADD(file_maxnumbytes, PAGESIZE - 1, &file_maxnumbytes))
		file_maxnumbytes = (pos_t)-1;
	file_maxnumbytes &= ~PAGEMASK;
	file_minoffset &= ~PAGEMASK;
	TRY {
		size_t num_bytes, guard;
		uintptr_half_t node_flags;
		/* Make sure that the given `length' is neither too small, nor too large. */
		if unlikely(!length) {
err_bad_length:
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
			      length);
		}
		if unlikely(OVERFLOW_UADD(length, (size_t)result_offset, &num_bytes))
			goto err_bad_length;
		num_bytes = CEIL_ALIGN(num_bytes, PAGESIZE);
#ifdef KERNELSPACE_HIGHMEM
		if unlikely(num_bytes > (size_t)KERNELSPACE_BASE)
			goto err_bad_length;
#else /* KERNELSPACE_HIGHMEM */
		if unlikely(num_bytes > ((size_t)0 - KERNELSPACE_END))
			goto err_bad_length;
#endif /* !KERNELSPACE_HIGHMEM */
		/* TODO: MAP_LOCKED */
		/* TODO: MAP_NORESERVE */
		/* TODO: MAP_POPULATE */
		/* TODO: MAP_NONBLOCK */

		if (flags & MAP_FIXED) {
			bool isused;
			result = (byte_t *)((uintptr_t)addr & ~PAGEMASK);
			if (flags & MAP_DONT_MAP) {
				/* Don't actually map memory. - Just check if the region is already in use */
				sync_read(THIS_MMAN);
				isused = vm_isused(THIS_MMAN,
				                   result,
				                   num_bytes);
				sync_endread(THIS_MMAN);
			} else {
				guard      = 0;
				node_flags = VM_NODE_FLAG_NORMAL;
				if (flags & MAP_GROWSUP) {
					guard     = num_bytes - PAGESIZE;
					num_bytes = PAGESIZE;
#ifdef CONFIG_USE_NEW_VM
					node_flags |= MAP_GROWSUP;
#else /* CONFIG_USE_NEW_VM */
					node_flags |= VM_NODE_FLAG_GROWSUP;
#endif /* !CONFIG_USE_NEW_VM */
				} else if (flags & MAP_GROWSDOWN) {
					guard     = num_bytes - PAGESIZE;
					num_bytes = PAGESIZE;
#ifdef CONFIG_USE_NEW_VM
					node_flags |= MAP_GROWSDOWN;
#endif /* CONFIG_USE_NEW_VM */
				}
again_mapat:
				/* XXX: vm_mapat_override(...)? */
				isused = !vm_mapat_subrange(THIS_MMAN,
				                            result,
				                            num_bytes,
				                            datablock,
				                            datablock_fspath,
				                            datablock_fsname,
				                            file_offset & ~PAGEMASK,
				                            file_minoffset,
				                            file_maxnumbytes,
				                            prot & (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_LOOSE | PROT_SHARED),
				                            node_flags,
				                            guard / PAGESIZE);
				if (isused && !(flags & MAP_FIXED_NOREPLACE)) {
					if (vm_unmap(THIS_MMAN,
					             result,
					             num_bytes + guard,
					             VM_UNMAP_ANYTHING |
					             VM_UNMAP_NOKERNPART)) {
#ifdef CONFIG_HAVE_USERMOD
						vm_clear_usermod(THIS_MMAN);
#endif /* CONFIG_HAVE_USERMOD */
						/* Try again, now that the existing mapping was deleted. */
						goto again_mapat;
					}
					/* Check if the given range overlaps with KERNEL-SPACE */
					if (!ADDRRANGE_ISKERN_PARTIAL(result, num_bytes + guard))
						goto again_mapat;
				}
			}
			if unlikely(isused) {
				/* TODO: These aren't the correct arguments for this exception! */
				THROW(E_BADALLOC_ADDRESS_ALREADY_EXISTS, num_bytes);
			}
		} else {
			PAGEDIR_PAGEALIGNED UNCHECKED void *hint;
			unsigned int getfree_mode;
#if __SIZEOF_POINTER__ > 4
			/* TODO: MAP_32BIT */
#endif /* __SIZEOF_POINTER__ > 4 */
			if (!addr) {
				/* Choose the hints for automatic mmap() target selection. */
				if (flags & MAP_STACK) {
					hint         = HINT_GETADDR(KERNEL_VMHINT_USER_STACK);
					getfree_mode = HINT_GETMODE(KERNEL_VMHINT_USER_STACK);
				} else {
					hint         = HINT_GETADDR(KERNEL_VMHINT_USER_HEAP);
					getfree_mode = HINT_GETMODE(KERNEL_VMHINT_USER_HEAP);
				}
			} else {
				hint         = (void *)((uintptr_t)addr & ~PAGEMASK);
				getfree_mode = VM_GETFREE_ABOVE | VM_GETFREE_ASLR;
			}
			if (flags & MAP_DONT_MAP) {
				/* Don't actually map memory. - Just find a free region */
				sync_read(THIS_MMAN);
				result = (byte_t *)vm_getfree(THIS_MMAN,
				                              hint,
				                              num_bytes,
				                              PAGESIZE,
				                              getfree_mode);
				sync_endread(THIS_MMAN);
				if unlikely(result == (byte_t *)VM_GETFREE_ERROR)
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, num_bytes);
			} else {
				/* Support for MAP_GROWSDOWN, MAP_GROWSUP  (create a growing guard mapping) */
				node_flags = VM_NODE_FLAG_NORMAL;
				guard      = 0;
				if (flags & MAP_GROWSUP) {
					guard     = num_bytes - PAGESIZE;
					num_bytes = PAGESIZE;
#ifdef CONFIG_USE_NEW_VM
					node_flags |= MAP_GROWSUP;
#else /* CONFIG_USE_NEW_VM */
					node_flags |= VM_NODE_FLAG_GROWSUP;
#endif /* !CONFIG_USE_NEW_VM */
				} else if (flags & MAP_GROWSDOWN) {
					guard     = num_bytes - PAGESIZE;
					num_bytes = PAGESIZE;
#ifdef CONFIG_USE_NEW_VM
					node_flags |= MAP_GROWSDOWN;
#endif /* CONFIG_USE_NEW_VM */
				}
				result = (byte_t *)vm_map_subrange(THIS_MMAN,
				                                   hint,
				                                   num_bytes,
				                                   PAGESIZE,
				                                   getfree_mode,
				                                   datablock,
				                                   datablock_fspath,
				                                   datablock_fsname,
				                                   file_offset & ~PAGEMASK,
				                                   file_minoffset,
				                                   file_maxnumbytes,
				                                   prot & (PROT_EXEC | PROT_WRITE | PROT_READ |
				                                           PROT_LOOSE | PROT_SHARED),
				                                   node_flags,
				                                   guard / PAGESIZE);
			}
		}
	} EXCEPT {
		xdecref(datablock_fspath);
		xdecref(datablock_fsname);
		decref(datablock);
		RETHROW();
	}
	xdecref_unlikely(datablock_fspath);
	xdecref_unlikely(datablock_fsname);
	decref_unlikely(datablock);
	assert(!task_wasconnected());
	return result + result_offset;
}
#endif /* WANT_MMAP */

#ifdef __ARCH_WANT_SYSCALL_MMAP
DEFINE_SYSCALL6(void *, mmap,
                void *, addr, size_t, length, syscall_ulong_t, prot,
                syscall_ulong_t, flags, fd_t, fd, syscall_ulong_t, offset) {
	pos_t file_offset;
	file_offset = (pos_t)offset;
	if (flags & MAP_OFFSET64_POINTER) {
		validate_readable((byte_t *)(uintptr_t)offset, 8);
		COMPILER_READ_BARRIER();
		file_offset = (pos_t)(*(u64 *)(uintptr_t)offset);
		COMPILER_READ_BARRIER();
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
//TODO:FUNDEF void *(__ARCH_SYSCALLCC sys_mremap)(void *old_address, size_t old_size, size_t new_size, syscall_ulong_t flags, void *new_address) THROWS(...);
#endif /* __ARCH_WANT_SYSCALL_MREMAP */

DECL_END

#ifndef __INTELLISENSE__
#ifdef __ARCH_WANT_SYSCALL_MAPLIBRARY
#include "syscalls-maplibrary-impl.c.inl"
#endif /* __ARCH_WANT_SYSCALL_MAPLIBRARY */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_MAPLIBRARY
#define DEFINE_COMPAT_MAPLIBRARY 1
#include "syscalls-maplibrary-impl.c.inl"
#endif /* __ARCH_WANT_COMPAT_SYSCALL_MAPLIBRARY */

#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_SYSCALLS_C */
