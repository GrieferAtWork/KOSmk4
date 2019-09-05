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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_SYSCALLS_C
#define GUARD_KERNEL_SRC_MEMORY_VM_SYSCALLS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <kernel/vm.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <sys/mman.h>

#include <assert.h>
#include <elf.h>
#include <errno.h>
#include <string.h>

DECL_BEGIN

#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x


LOCAL REF struct vm_datablock *KCALL
getdatablock_from_handle(unsigned int fd,
                         vm_vpage64_t *__restrict pminpage,
                         vm_vpage64_t *__restrict pmaxpage) {
	REF struct vm_datablock *result;
	struct handle hnd = handle_lookup(fd);
	TRY {
		result = handle_mmap(hnd, pminpage, pmaxpage);
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
	return result;
}

DEFINE_SYSCALL2(errno_t, munmap, void *, addr, size_t, length) {
	size_t offset;
	offset = (uintptr_t)addr & (PAGESIZE - 1);
	if (OVERFLOW_UADD(length, offset, &length))
		length = (size_t)-1;
	vm_unmap(THIS_VM,
	         VM_ADDR2PAGE((vm_virt_t)addr),
	         CEILDIV(length, PAGESIZE),
	         VM_UNMAP_ANYTHING |
	         VM_UNMAP_NOKERNPART);
	return -EOK;
}

DEFINE_SYSCALL3(errno_t, mprotect,
                void *, addr, size_t, length,
                syscall_ulong_t, prot) {
	size_t offset;
	offset = (uintptr_t)addr & (PAGESIZE - 1);
	if (OVERFLOW_UADD(length, offset, &length))
		length = (size_t)-1;
	VALIDATE_FLAGSET(prot,
	                 PROT_EXEC | PROT_WRITE | PROT_READ,
	                 E_INVALID_ARGUMENT_CONTEXT_MPROTECT_PROT);
	vm_protect(THIS_VM,
	           VM_ADDR2PAGE((vm_virt_t)addr),
	           CEILDIV(length, PAGESIZE),
	           VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC,
	           prot,
	           VM_UNMAP_ANYTHING | VM_UNMAP_NOKERNPART);
	return -EOK;
}


STATIC_ASSERT(PROT_NONE   == VM_PROT_NONE);
STATIC_ASSERT(PROT_EXEC   == VM_PROT_EXEC);
STATIC_ASSERT(PROT_WRITE  == VM_PROT_WRITE);
STATIC_ASSERT(PROT_READ   == VM_PROT_READ);
STATIC_ASSERT(PROT_LOOSE  == VM_PROT_LOOSE);
STATIC_ASSERT(PROT_SHARED == VM_PROT_SHARED);


PRIVATE void KCALL
unmap_range(struct vm *__restrict v,
            vm_vpage_t loadpage,
            USER CHECKED Elf_Phdr *headers,
            size_t count) {
	Elf_Addr addr;
	Elf_Off offset;
	Elf_Word size;
	while (count--) {
		if (ATOMIC_READ(headers[count].p_type) != PT_LOAD)
			continue;
		addr   = ATOMIC_READ(headers[count].p_vaddr);
		size   = ATOMIC_READ(headers[count].p_memsz);
		offset = ATOMIC_READ(headers[count].p_offset);
		if
			unlikely(!size)
		continue;
		if (ATOMIC_READ(headers[count].p_filesz)) {
			uintptr_t alignment;
			alignment = offset & (PAGESIZE - 1);
			addr -= alignment;
			size += alignment;
		}
		size += addr & (PAGESIZE - 1);
		addr &= ~(PAGESIZE - 1);
		vm_unmap(v,
		         loadpage + VM_ADDR2PAGE((vm_virt_t)addr),
		         CEILDIV(size, PAGESIZE),
		         VM_UNMAP_ANYTHING |
		         VM_UNMAP_NOKERNPART);
	}
}


PRIVATE bool KCALL
contains_illegal_overlap(USER CHECKED Elf_Phdr *headers,
                         size_t count) {
	size_t i, j;
	uintptr_t addr_page_offset = 0;
	bool is_first              = true;
	for (i = 0; i < count; ++i) {
		vm_vpage_t min_page;
		vm_vpage_t max_page;
		Elf_Addr addr;
		Elf_Word size;
		Elf_Off offset;
		if (ATOMIC_READ(headers[i].p_type) != PT_LOAD)
			continue;
		addr   = ATOMIC_READ(headers[i].p_vaddr);
		size   = ATOMIC_READ(headers[i].p_memsz);
		offset = ATOMIC_READ(headers[i].p_offset);
		if (ATOMIC_READ(headers[i].p_filesz)) {
			uintptr_t alignment;
			alignment = offset & (PAGESIZE - 1);
			if (OVERFLOW_USUB(addr, alignment, &addr))
				goto yes;
			if (OVERFLOW_UADD(size, alignment, &size))
				goto yes;
			/* Validate the consistency of the page alignment. */
			if ((addr & (PAGESIZE - 1)) != addr_page_offset) {
				if (!is_first)
					goto yes;
				addr_page_offset = addr & (PAGESIZE - 1);
			}
			addr -= addr_page_offset;
			if (OVERFLOW_UADD(size, addr_page_offset, &size))
				goto yes;
			is_first = false;
			assert(!(addr & (PAGESIZE - 1)));
		} else {
			if (OVERFLOW_UADD(size, addr & (PAGESIZE - 1), &size))
				goto yes;
			addr &= ~(PAGESIZE - 1);
		}
		min_page = VM_ADDR2PAGE((vm_virt_t)addr);
		if (OVERFLOW_UADD(addr, size, &addr))
			goto yes;
		if (OVERFLOW_UADD(addr, (Elf_Addr)(PAGESIZE - 1), &addr))
			goto yes;
		max_page = (vm_vpage_t)(addr / PAGESIZE) - 1;
		for (j = i + 1; j < count; ++j) {
			vm_vpage_t other_min_page;
			vm_vpage_t other_max_page;
			if (ATOMIC_READ(headers[j].p_type) != PT_LOAD)
				continue;
			addr   = ATOMIC_READ(headers[j].p_vaddr);
			size   = ATOMIC_READ(headers[j].p_memsz);
			offset = ATOMIC_READ(headers[j].p_offset);
			if (ATOMIC_READ(headers[j].p_filesz)) {
				uintptr_t alignment;
				alignment = offset & (PAGESIZE - 1);
				if (OVERFLOW_USUB(addr, alignment, &addr))
					goto yes;
				if (OVERFLOW_UADD(size, alignment, &size))
					goto yes;
				/* Validate the consistency of the page alignment. */
				if ((addr & (PAGESIZE - 1)) != addr_page_offset) {
					if (!is_first)
						goto yes;
					addr_page_offset = addr & (PAGESIZE - 1);
				}
				addr -= addr_page_offset;
				if (OVERFLOW_UADD(size, addr_page_offset, &size))
					goto yes;
				is_first = false;
				assert(!(addr & (PAGESIZE - 1)));
			} else {
				if (OVERFLOW_UADD(size, addr & (PAGESIZE - 1), &size))
					goto yes;
				addr &= ~(PAGESIZE - 1);
			}
			other_min_page = VM_ADDR2PAGE((vm_virt_t)addr);
			if (OVERFLOW_UADD(addr, size, &addr))
				goto yes;
			if (OVERFLOW_UADD(addr, (Elf_Addr)(PAGESIZE - 1), &addr))
				goto yes;
			other_max_page = (vm_vpage_t)(addr / PAGESIZE) - 1;
			if (other_min_page < max_page &&
			    other_max_page > min_page)
				goto yes;
		}
	}
	return false;
yes:
	return true;
}


DEFINE_SYSCALL5(void *, maplibrary,
                void *, addr, syscall_ulong_t, flags,
                fd_t, fd, void *, hdrv, size_t, hdrc) {
	vm_vpage_t result;
	struct vm *v = THIS_VM;
	size_t i;
	USER CHECKED Elf_Phdr *headers = (Elf_Phdr *)hdrv;
	uintptr_t addr_page_offset     = 0; /* Sub-page offset for the load address (usually 0) */
	uintptr_t min_page             = 0;
	REF struct vm_datablock *file  = NULL;
	vm_vpage64_t file_minpage = 0;
	vm_vpage64_t file_maxpage = (vm_vpage64_t)-1;
	bool is_first;
	size_t min_page_alignment = 1;
	size_t total_pages        = 0;
	validate_readablem(hdrv, hdrc, sizeof(Elf_Phdr));
	VALIDATE_FLAGSET(flags,
	                 MAP_FIXED | MAP_LOCKED | MAP_NONBLOCK |
	                 MAP_NORESERVE | MAP_POPULATE | MAP_SYNC |
	                 MAP_DONT_MAP | MAP_DONT_OVERRIDE,
	                 E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS);
	if (flags & MAP_FIXED) {
		if unlikely(!hdrc)
			return addr;
		result           = (vm_vpage_t)VM_ADDR2PAGE((uintptr_t)addr);
		addr_page_offset = (uintptr_t)addr & (PAGESIZE - 1);
		if (flags & MAP_DONT_MAP) {
			bool isused;
			uintptr_t min_addr, max_addr;
			if unlikely(!hdrc)
				return (void *)VM_PAGE2ADDR((vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_USER_LIBRARY));
			min_addr = (uintptr_t)-1;
			max_addr = 0;
			/* Figure out the min/max byte offsets for program segments. */
			for (i = 0; i < hdrc; ++i) {
				Elf_Addr addr;
				Elf_Word size;
				if (ATOMIC_READ(headers[i].p_type) != PT_LOAD)
					continue;
				addr = ATOMIC_READ(headers[i].p_vaddr);
				size = ATOMIC_READ(headers[i].p_memsz);
				if unlikely(!size)
					continue;
				if (min_addr > addr)
					min_addr = addr;
				addr += size - 1;
				if (max_addr < addr)
					max_addr = addr;
			}
			total_pages = (CEILDIV(max_addr, PAGESIZE) -
			               FLOORDIV(min_addr, PAGESIZE));
			sync_read(THIS_VM);
			isused = vm_isused(THIS_VM,
			                   result,
			                   result + total_pages - 1);
			sync_endread(THIS_VM);
			if (isused)
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, total_pages);
			goto done;
		}
	} else {
		uintptr_t min_addr, max_addr;
		if unlikely(!hdrc)
			return (void *)VM_PAGE2ADDR((vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_USER_LIBRARY));
		min_addr = (uintptr_t)-1;
		max_addr = 0;
		/* Figure out the min/max byte offsets for program segments. */
		is_first = true;
		for (i = 0; i < hdrc; ++i) {
			Elf_Addr addr;
			Elf_Off offset;
			Elf_Word size, align, filesize;
			if (ATOMIC_READ(headers[i].p_type) != PT_LOAD)
				continue;
			addr     = ATOMIC_READ(headers[i].p_vaddr);
			size     = ATOMIC_READ(headers[i].p_memsz);
			offset   = ATOMIC_READ(headers[i].p_offset);
			filesize = ATOMIC_READ(headers[i].p_filesz);
			align    = ATOMIC_READ(headers[i].p_align);
			if unlikely(!size)
				continue;
			align = CEILDIV(align, PAGESIZE);
			if (min_page_alignment < align)
				min_page_alignment = align;
			if (filesize) {
				uintptr_t alignment;
				alignment = offset & (PAGESIZE - 1);
				addr -= alignment;
				offset -= alignment;
				size += alignment;
				/* Validate the consistency of the page alignment. */
				if ((addr & (PAGESIZE - 1)) != addr_page_offset) {
					if (!(flags & MAP_FIXED) && is_first)
						addr_page_offset = addr & (PAGESIZE - 1);
					else {
						THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
						      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN,
						      (uintptr_t)addr,
						      PAGESIZE - 1,
						      addr_page_offset);
					}
				}
				addr -= addr_page_offset;
				size += addr_page_offset;
				is_first = false;
				assert(!(addr & (PAGESIZE - 1)));
			} else {
				size += addr & (PAGESIZE - 1);
				addr &= ~(PAGESIZE - 1);
			}
			size = CEIL_ALIGN(size, PAGESIZE);
			if (min_addr > addr)
				min_addr = addr;
			addr += size - 1;
			if (max_addr < addr)
				max_addr = addr;
		}
		min_page    = FLOORDIV(min_addr, PAGESIZE);
		total_pages = (CEILDIV(max_addr, PAGESIZE) - min_page);
		if unlikely(min_page_alignment & (min_page_alignment - 1)) {
			THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
			      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECDATAALIGN,
			      (uintptr_t)min_page_alignment,
			      min_page_alignment - 1,
			      0);
		}
		/* Find a suitable target location where we can map the library. */
find_new_candidate:
		sync_read(v);
		result = vm_getfree(v,
		                    (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_USER_LIBRARY),
		                    total_pages,
		                    min_page_alignment,
		                    HINT_GETMODE(KERNEL_VMHINT_USER_LIBRARY));
		sync_endread(v);
		if unlikely(result == VM_GETFREE_ERROR)
			THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, total_pages);
		result -= min_page;
		if (flags & MAP_DONT_MAP)
			goto done;
	}
again_map_segments:
	i        = 0;
	is_first = true;
	TRY {
		/* Now that we've got a suitable memory location, move on to actually map the library. */
		for (; i < hdrc; ++i) {
			Elf_Addr addr;
			Elf_Word size, unaligned_size;
			Elf_Word filesize, unaligned_filesize;
			Elf_Off offset;
			uintptr_half_t prot;
			Elf_Word segment_flags;
			if (ATOMIC_READ(headers[i].p_type) != PT_LOAD)
				continue;
			addr          = ATOMIC_READ(headers[i].p_vaddr);
			size          = ATOMIC_READ(headers[i].p_memsz);
			filesize      = ATOMIC_READ(headers[i].p_filesz);
			offset        = ATOMIC_READ(headers[i].p_offset);
			segment_flags = ATOMIC_READ(headers[i].p_flags);
			if unlikely(!size)
				continue;
#if PF_R == VM_PROT_READ && PF_W == VM_PROT_WRITE && PF_X == VM_PROT_EXEC
			prot = segment_flags & (VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC);
#else
			prot = VM_PROT_NONE;
			if (segment_flags & PF_R)
				prot |= VM_PROT_READ;
			if (segment_flags & PF_W)
				prot |= VM_PROT_WRITE;
			if (segment_flags & PF_X)
				prot |= VM_PROT_EXEC;
#endif
			if (filesize) {
				uintptr_t alignment;
				alignment = offset & (PAGESIZE - 1);
				addr -= alignment;
				offset -= alignment;
				size += alignment;
				filesize += alignment;
				/* Validate the consistency of the page alignment. */
				if ((addr & (PAGESIZE - 1)) != addr_page_offset) {
					if (!(flags & MAP_FIXED) && is_first)
						addr_page_offset = addr & (PAGESIZE - 1);
					else {
						unmap_range(v, result, headers, i);
						THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
						      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN,
						      (uintptr_t)addr,
						      PAGESIZE - 1,
						      addr_page_offset);
					}
				}
				addr -= addr_page_offset;
				size += addr_page_offset;
				filesize += addr_page_offset;
				unaligned_size     = size;
				unaligned_filesize = filesize;
				filesize      = CEIL_ALIGN(filesize, PAGESIZE);
				size          = CEIL_ALIGN(size, PAGESIZE);
				is_first      = false;
				if unlikely(filesize > size)
					filesize = size;
				assert(!(addr & (PAGESIZE - 1)));
			} else {
				size += addr & (PAGESIZE - 1);
				addr &= ~(PAGESIZE - 1);
				unaligned_size     = size;
				unaligned_filesize = filesize;
				size = CEIL_ALIGN(size, PAGESIZE);
			}
			if (size > filesize) {
				/* Map BSS */
				if (!vm_mapat(v,
				              result + VM_ADDR2PAGE((vm_virt_t)addr + filesize),
				              (size - filesize) / PAGESIZE,
				              &vm_datablock_anonymous_zero,
				              0,
				              prot,
				              VM_NODE_FLAG_NORMAL,
				              0)) {
unmap_check_overlap_and_find_new_candidate:
					/* Check for illegal overlap */
					if (contains_illegal_overlap(headers, hdrc))
						THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, size / PAGESIZE);
					if (!(flags & MAP_FIXED)) {
						unmap_range(v, result, headers, i);
						goto find_new_candidate;
					}
					if (!(flags & MAP_DONT_OVERRIDE)) {
						vm_unmap(v,
						         result + VM_ADDR2PAGE((vm_virt_t)addr),
						         size / PAGESIZE,
						         VM_UNMAP_ANYTHING |
						         VM_UNMAP_NOKERNPART);
						goto again_map_segments;
					}
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY,
					      size / PAGESIZE);
				}
			}
			if (filesize) {
				if ((offset & (PAGESIZE - 1)) != 0) {
					THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
					      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECFILEALIGN,
					      (uintptr_t)(offset + addr_page_offset),
					      PAGESIZE - 1,
					      addr_page_offset);
				}
				if (!file) {
					file = getdatablock_from_handle((unsigned int)fd,
					                                &file_minpage,
					                                &file_maxpage);
				}
				/* Map file contents */
				if (!vm_mapat_subrange(v,
				                       result + VM_ADDR2PAGE((vm_virt_t)addr),
				                       filesize / PAGESIZE,
				                       file,
				                       (vm_vpage64_t)(offset / PAGESIZE),
				                       file_minpage,
				                       file_maxpage,
				                       prot,
				                       VM_NODE_FLAG_NORMAL,
				                       0))
					goto unmap_check_overlap_and_find_new_candidate;
				/* LD sometimes produces really weird .bss sections that are neither whole
				 * pages, nor are placed such that they exist at the end of some given file.
				 * Because of this, we must manually check for segments that end in a
				 * small (< PAGESIZE) section of bss memory when that segment doesn't hug the
				 * end of the actual file, and memset() it to all ZEROes.
				 *
				 * Example (filesize == 0x22060):
				 *     Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
				 *     LOAD           0x000000 0x00000000 0x00000000 0x0e224 0x0e224 R E 0x1000
				 *     LOAD           0x00e224 0x0000f224 0x0000f224 0x000ec 0x000fc RW  0x1000
				 *     DYNAMIC        0x00e228 0x0000f228 0x0000f228 0x000a8 0x000a8 RW  0x4
				 *
				 * The second segment contains a BSS area of 0xfc-0xec == 0x10 bytes at 0xf310...0xf31f
				 * Since this range is still part of the page that gets loaded from disk as a file mapping,
				 * the associated file mapping at 0xf224...0xf30f is extended to the end of the associated
				 * page at 0xffff (which includes (in this case) the entire .bss section).
				 *
				 * In a case like this where the .bss area overlaps with the extended file mapping, the first
				 * page of the .bss area must be re-mapped as writable (if not already), followed by the area
				 * `START_OF_BSS ... MIN(MAX_BSS_BYTE, MAX_BYTE_OF_PAGE(PAGE_OF(START_OF_BSS)))' being forcibly
				 * initialized to all ZEROes, causing the page to be faulted and become initialized properly.
				 */
				assert(unaligned_filesize != 0);
				if (unaligned_size > unaligned_filesize) {
					/* There is a .bss area! */
					vm_virt_t bss_start;
					bss_start = VM_PAGE2ADDR(result) + (vm_virt_t)addr + unaligned_filesize;
					if ((bss_start & (PAGESIZE-1)) != 0) {
						/* The .bss area isn't page-aligned, meaning it overlaps with the data-area... */
						size_t bss_overlap, bss_total_size;
						bss_total_size = unaligned_size - unaligned_filesize;
						bss_overlap    = PAGESIZE - (size_t)(bss_start & (PAGESIZE - 1));
						if (bss_overlap > bss_total_size)
							bss_overlap = bss_total_size;
						/* Must `memset(bss_start, 0, bss_overlap)' */
						if (prot & VM_PROT_WRITE) {
							memset((void *)bss_start, 0, bss_overlap);
						} else {
							/* Complicated case: Must write to memory mapped as read-only...
							 * Note that this really shouldn't be something that happens normally,
							 * since I don't see any reason why one would map .bss as read-only.
							 * But still: It is something that is technically allowed by ELF, and
							 *            maybe someone needed a really large section of 0-bytes
							 *            for some kind of stub-implementation... */
							vm_memset(v, (void *)bss_start, 0, bss_overlap, true);
						}
					}
				}
			}
		}
	} EXCEPT {
		unmap_range(v, result, headers, i);
		xdecref(file);
		RETHROW();
	}
	xdecref(file);
done:
	return (void *)(uintptr_t)(VM_PAGE2ADDR(result) + addr_page_offset);
}


DEFINE_SYSCALL1(time32_t, time, time32_t *,ptm) {
	validate_writable(ptm, sizeof(time32_t));
	if (ptm)
		*ptm = 0;
	return 0;
}


DEFINE_SYSCALL6(void *, mmap,
                void *, addr, size_t, length, syscall_ulong_t, prot,
                syscall_ulong_t, flags, fd_t, fd, syscall_ulong_t, offset) {
	vm_vpage_t result;
	uintptr_t result_offset;
	vm_daddr_t file_offset;
	REF struct vm_datablock *datablock;
	vm_vpage64_t file_minpage, file_maxpage;
	/* Check for unknown flags. */
#ifdef MAP_OFFSET64_POINTER
	VALIDATE_FLAGSET(flags,
	                 MAP_AUTOMATIC | MAP_SHARED | MAP_PRIVATE | MAP_FIXED |
	                 MAP_FILE | MAP_ANONYMOUS | MAP_32BIT | MAP_GROWSDOWN |
	                 MAP_GROWSUP | MAP_DENYWRITE | MAP_EXECUTABLE | MAP_LOCKED |
	                 MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK |
	                 MAP_HUGETLB | (MAP_HUGE_MASK << MAP_HUGE_SHIFT) |
	                 MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE |
	                 MAP_OFFSET64_POINTER,
	                 E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG);
#else /* MAP_OFFSET64_POINTER */
	VALIDATE_FLAGSET(flags,
	                 MAP_AUTOMATIC | MAP_SHARED | MAP_PRIVATE | MAP_FIXED |
	                 MAP_FILE | MAP_ANONYMOUS | MAP_32BIT | MAP_GROWSDOWN |
	                 MAP_GROWSUP | MAP_DENYWRITE | MAP_EXECUTABLE | MAP_LOCKED |
	                 MAP_NORESERVE | MAP_POPULATE | MAP_NONBLOCK | MAP_STACK |
	                 MAP_HUGETLB | (MAP_HUGE_MASK << MAP_HUGE_SHIFT) |
	                 MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE,
	                 E_INVALID_ARGUMENT_CONTEXT_MMAP_FLAG);
#endif /* !MAP_OFFSET64_POINTER */
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
	file_offset = (vm_daddr_t)offset;
#ifdef MAP_OFFSET64_POINTER
	if (flags & (MAP_OFFSET64_POINTER)) {
		validate_readable((byte_t *)(uintptr_t)offset, 8);
		COMPILER_READ_BARRIER();
		file_offset = (vm_daddr_t)(*(u64 *)(uintptr_t)offset);
		COMPILER_READ_BARRIER();
	}
#endif /* MAP_OFFSET64_POINTER */
	result_offset = (uintptr_t)file_offset & (PAGESIZE - 1);
	if (flags & MAP_ANONYMOUS) {
		result_offset = 0;
		if (flags & MAP_FIXED)
			result_offset = (uintptr_t)addr & (PAGESIZE - 1);
	} else {
		if (flags & MAP_FIXED) {
			if (result_offset != ((uintptr_t)addr & (PAGESIZE - 1))) {
				THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
				      E_INVALID_ARGUMENT_CONTEXT_MMAP_ADDR,
				      (uintptr_t)addr,
				      PAGESIZE - 1,
				      result_offset);
			}
		}
	}

	/* Load the requested data block. */
	file_minpage = 0;
	file_maxpage = (vm_vpage64_t)-1;
	datablock = flags & MAP_ANONYMOUS
	            ? (flags & MAP_UNINITIALIZED
	               ? incref(&vm_datablock_anonymous) /* TODO: This must require additional permissions! */
	               : incref(&vm_datablock_anonymous_zero))
	            : getdatablock_from_handle(fd, &file_minpage, &file_maxpage);
	TRY {
		size_t num_pages, guard;
		uintptr_half_t node_flags;
		/* Make sure that the given `length' is neither too small, nor too large. */
		if unlikely(!length) {
err_bad_length:
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_MMAP_LENGTH,
			      length);
		}
		if unlikely(OVERFLOW_UADD(length, (size_t)result_offset, &num_pages))
			goto err_bad_length;
		num_pages = CEILDIV(num_pages, PAGESIZE);
#ifdef HIGH_MEMORY_KERNEL
		if unlikely(num_pages > (size_t)KERNEL_BASE_PAGE)
			goto err_bad_length;
#else /* HIGH_MEMORY_KERNEL */
		if unlikely(num_pages > (((size_t)VM_VPAGE_MAX + 1) - (size_t)KERNEL_CEILING_PAGE))
			goto err_bad_length;
#endif /* !HIGH_MEMORY_KERNEL */
		/* TODO: MAP_LOCKED */
		/* TODO: MAP_NORESERVE */
		/* TODO: MAP_POPULATE */
		/* TODO: MAP_NONBLOCK */

		if (flags & MAP_FIXED) {
			bool isused;
			result = (vm_vpage_t)VM_ADDR2PAGE((uintptr_t)addr);
			if (flags & MAP_DONT_MAP) {
				/* Don't actually map memory. - Just check if the region is already in use */
				sync_read(THIS_VM);
				isused = vm_isused(THIS_VM,
				                   result,
				                   result + num_pages - 1);
				sync_endread(THIS_VM);
			} else {
				guard      = 0;
				node_flags = VM_NODE_FLAG_NORMAL;
				if (flags & MAP_GROWSUP) {
					guard     = num_pages - 1;
					num_pages = 1;
					node_flags |= VM_NODE_FLAG_GROWSUP;
				} else if (flags & MAP_GROWSDOWN) {
					guard     = num_pages - 1;
					num_pages = 1;
				}
again_mapat:
				/* XXX: vm_mapat_override(...)? */
				isused = !vm_mapat_subrange(THIS_VM,
				                            result,
				                            num_pages,
				                            datablock,
				                            (vm_vpage64_t)(file_offset / PAGESIZE),
				                            file_minpage,
				                            file_maxpage,
				                            prot & (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_LOOSE | PROT_SHARED),
				                            node_flags,
				                            guard);
				if (isused && !(flags & MAP_DONT_OVERRIDE)) {
					if (vm_unmap(THIS_VM,
					             result,
					             num_pages + guard,
					             VM_UNMAP_ANYTHING |
					             VM_UNMAP_NOKERNPART) ||
					    /* Check if the given range overlaps with KERNEL-SPACE */
					    !PRANGE_IS_KERNEL_PARTIAL(result, num_pages + guard))
						goto again_mapat; /* Try again, now that the existing mapping was deleted. */
				}
			}
			if unlikely(isused)
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, num_pages);
		} else {
			vm_vpage_t hint;
			unsigned int getfree_mode;
#if __SIZEOF_POINTER__ > 4
			/* TODO: MAP_32BIT */
#endif /* __SIZEOF_POINTER__ > 4 */
			if (!addr) {
				/* Choose the hints for automatic mmap() target selection. */
				if (flags & MAP_STACK) {
					hint         = (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_USER_STACK);
					getfree_mode = HINT_GETMODE(KERNEL_VMHINT_USER_STACK);
				} else {
					hint         = (vm_vpage_t)HINT_GETADDR(KERNEL_VMHINT_USER_HEAP);
					getfree_mode = HINT_GETMODE(KERNEL_VMHINT_USER_HEAP);
				}
			} else {
				hint         = (vm_vpage_t)VM_ADDR2PAGE((uintptr_t)addr);
				getfree_mode = VM_GETFREE_ABOVE | VM_GETFREE_ASLR;
			}
			if (flags & MAP_DONT_MAP) {
				/* Don't actually map memory. - Just find a free region */
				sync_read(THIS_VM);
				result = vm_getfree(THIS_VM,
				                    hint,
				                    num_pages,
				                    1,
				                    getfree_mode);
				sync_endread(THIS_VM);
				if unlikely(result == VM_GETFREE_ERROR)
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, num_pages);
			} else {
				/* Support for MAP_GROWSDOWN, MAP_GROWSUP  (create a growing guard mapping) */
				node_flags = VM_NODE_FLAG_NORMAL;
				guard      = 0;
				if (flags & MAP_GROWSUP) {
					guard     = num_pages - 1;
					num_pages = 1;
					node_flags |= VM_NODE_FLAG_GROWSUP;
				} else if (flags & MAP_GROWSDOWN) {
					guard     = num_pages - 1;
					num_pages = 1;
				}
				result = vm_map_subrange(THIS_VM,
				                         hint,
				                         num_pages,
				                         1,
				                         getfree_mode,
				                         datablock,
				                         (vm_vpage64_t)(file_offset / PAGESIZE),
				                         file_minpage,
				                         file_maxpage,
				                         prot & (PROT_EXEC | PROT_WRITE | PROT_READ | PROT_LOOSE | PROT_SHARED),
				                         node_flags,
				                         guard);
			}
		}
	} EXCEPT {
		decref(datablock);
		RETHROW();
	}
	decref(datablock);
	return (byte_t *)VM_PAGE2ADDR(result) + result_offset;
}

//TODO:FUNDEF void *(__ARCH_SYSCALLCC sys_mremap)(void *old_address, size_t old_size, size_t new_size, syscall_ulong_t flags, void *new_address) THROWS(...);


//DEFINE_SYSCALL5(syscall_slong_t, lfutex,
//                USER UNCHECKED uintptr_t *, uaddr, syscall_ulong_t, futex_op, uintptr_t, val,
//                USER UNCHECKED struct timespec64 const *, timeout, uintptr_t, val2) {
//	/* TODO */
//	return -ENOSYS;
//}

//TODO:#define __NR_lfutex                     0x80000012 /* syscall_slong_t lfutex(uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct timespec64 const *timeout, uintptr_t val2) */
//TODO:#define __NR_lfutexlock                 0x80000014 /* syscall_slong_t lfutexlock(uintptr_t *ulockaddr, uintptr_t *uaddr, syscall_ulong_t futex_op, uintptr_t val, struct timespec64 const *timeout, uintptr_t val2) */
//TODO:#define __NR_lfutexexpr                 0x80000015 /* errno_t lfutexexpr(uintptr_t *uaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct timespec64 const *timeout, syscall_ulong_t timeout_flags) */
//TODO:#define __NR_lfutexlockexpr             0x80000016 /* errno_t lfutexlockexpr(uintptr_t *ulockaddr, void *base, struct lfutexexpr const *exprv, size_t exprc, struct timespec64 const *timeout, syscall_ulong_t timeout_flags) */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_SYSCALLS_C */
