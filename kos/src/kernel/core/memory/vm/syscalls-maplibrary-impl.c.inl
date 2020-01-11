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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "syscalls.c"
#define DEFINE_COMPAT_MAPLIBRARY 1
#endif /* __INTELLISENSE__ */

#ifdef DEFINE_COMPAT_MAPLIBRARY
#include <compat/kos/exec/elf.h>
#endif /* DEFINE_COMPAT_MAPLIBRARY */

/************************************************************************/
/* maplibrary()                                                         */
/************************************************************************/

DECL_BEGIN

#ifdef DEFINE_COMPAT_MAPLIBRARY
#define FUNC(x) compat_##x
#define MY_ElfW COMPAT_ElfW
#define MY_ELFW COMPAT_ELFW
#else /* DEFINE_COMPAT_MAPLIBRARY */
#define FUNC(x) x
#define MY_ElfW ElfW
#define MY_ELFW ELFW
#endif /* !DEFINE_COMPAT_MAPLIBRARY */

PRIVATE void KCALL
FUNC(unmap_range)(struct vm *__restrict v,
                  PAGEDIR_PAGEALIGNED UNCHECKED void *loadaddr,
                  USER CHECKED MY_ElfW(Phdr) * headers,
                  size_t count) {
	MY_ElfW(Addr) addr;
	MY_ElfW(Off) offset;
	MY_ElfW(Word) size;
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
			alignment = offset & PAGEMASK;
			addr -= alignment;
			size += alignment;
		}
		size += addr & PAGEMASK;
		addr &= ~PAGEMASK;
		vm_unmap(v,
		         (byte_t *)loadaddr + addr,
		         CEIL_ALIGN(size, PAGESIZE),
		         VM_UNMAP_ANYTHING |
		         VM_UNMAP_NOKERNPART);
	}
}

PRIVATE bool KCALL
FUNC(contains_illegal_overlap)(USER CHECKED MY_ElfW(Phdr) *headers,
                               size_t count) {
	size_t i, j;
	uintptr_t addr_page_offset = 0;
	bool is_first              = true;
	for (i = 0; i < count; ++i) {
		uintptr_t min_page;
		uintptr_t max_page;
		MY_ElfW(Addr) addr;
		MY_ElfW(Word) size;
		MY_ElfW(Off) offset;
		if (ATOMIC_READ(headers[i].p_type) != PT_LOAD)
			continue;
		addr   = ATOMIC_READ(headers[i].p_vaddr);
		size   = ATOMIC_READ(headers[i].p_memsz);
		offset = ATOMIC_READ(headers[i].p_offset);
		if (ATOMIC_READ(headers[i].p_filesz)) {
			uintptr_t alignment;
			alignment = offset & PAGEMASK;
			if (OVERFLOW_USUB(addr, alignment, &addr))
				goto yes;
			if (OVERFLOW_UADD(size, alignment, &size))
				goto yes;
			/* Validate the consistency of the page alignment. */
			if ((addr & PAGEMASK) != addr_page_offset) {
				if (!is_first)
					goto yes;
				addr_page_offset = addr & PAGEMASK;
			}
			addr -= addr_page_offset;
			if (OVERFLOW_UADD(size, addr_page_offset, &size))
				goto yes;
			is_first = false;
			assert(!(addr & PAGEMASK));
		} else {
			if (OVERFLOW_UADD(size, addr & PAGEMASK, &size))
				goto yes;
			addr &= ~PAGEMASK;
		}
		min_page = addr / PAGESIZE;
		if (OVERFLOW_UADD(addr, size, &addr))
			goto yes;
		if (OVERFLOW_UADD(addr, (MY_ElfW(Addr))PAGEMASK, &addr))
			goto yes;
		max_page = (addr / PAGESIZE) - 1;
		for (j = i + 1; j < count; ++j) {
			uintptr_t other_min_page;
			uintptr_t other_max_page;
			if (ATOMIC_READ(headers[j].p_type) != PT_LOAD)
				continue;
			addr   = ATOMIC_READ(headers[j].p_vaddr);
			size   = ATOMIC_READ(headers[j].p_memsz);
			offset = ATOMIC_READ(headers[j].p_offset);
			if (ATOMIC_READ(headers[j].p_filesz)) {
				uintptr_t alignment;
				alignment = offset & PAGEMASK;
				if (OVERFLOW_USUB(addr, alignment, &addr))
					goto yes;
				if (OVERFLOW_UADD(size, alignment, &size))
					goto yes;
				/* Validate the consistency of the page alignment. */
				if ((addr & PAGEMASK) != addr_page_offset) {
					if (!is_first)
						goto yes;
					addr_page_offset = addr & PAGEMASK;
				}
				addr -= addr_page_offset;
				if (OVERFLOW_UADD(size, addr_page_offset, &size))
					goto yes;
				is_first = false;
				assert(!(addr & PAGEMASK));
			} else {
				if (OVERFLOW_UADD(size, addr & PAGEMASK, &size))
					goto yes;
				addr &= ~PAGEMASK;
			}
			other_min_page = addr / PAGESIZE;
			if (OVERFLOW_UADD(addr, size, &addr))
				goto yes;
			if (OVERFLOW_UADD(addr, (MY_ElfW(Addr))PAGEMASK, &addr))
				goto yes;
			other_max_page = (addr / PAGESIZE) - 1;
			if (other_min_page <= max_page &&
			    other_max_page >= min_page)
				goto yes;
		}
	}
	return false;
yes:
	return true;
}


#ifdef DEFINE_COMPAT_MAPLIBRARY
DEFINE_COMPAT_SYSCALL5(void *, maplibrary,
                       void *, addr, syscall_ulong_t, flags, fd_t, fd,
                       USER UNCHECKED COMPAT_ElfW(Phdr) *, hdrv, size_t, hdrc)
#else /* DEFINE_COMPAT_MAPLIBRARY */
DEFINE_SYSCALL5(void *, maplibrary,
                void *, addr, syscall_ulong_t, flags, fd_t, fd,
                USER UNCHECKED ElfW(Phdr) *, hdrv, size_t, hdrc)
#endif /* !DEFINE_COMPAT_MAPLIBRARY */
{
	byte_t *result;
	struct vm *v = THIS_VM;
	size_t i;
	uintptr_t addr_page_offset     = 0; /* Sub-page offset for the load address (usually 0) */
	uintptr_t min_page             = 0;
	REF struct vm_datablock *file  = NULL;
	pos_t file_minoffset           = 0;
	pos_t file_maxnumbytes         = (pos_t)-1;
	bool is_first;
	size_t min_alignment = PAGESIZE;
	size_t total_bytes   = 0;
	validate_readablem(hdrv, hdrc, sizeof(MY_ElfW(Phdr)));
	VALIDATE_FLAGSET(flags,
	                 MAP_FIXED | MAP_LOCKED | MAP_NONBLOCK |
	                 MAP_NORESERVE | MAP_POPULATE | MAP_SYNC |
	                 MAP_DONT_MAP | MAP_DONT_OVERRIDE,
	                 E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_FLAGS);
	if (flags & MAP_FIXED) {
		if unlikely(!hdrc)
			return addr;
		result           = (byte_t *)((uintptr_t)addr & ~PAGEMASK);
		addr_page_offset = (uintptr_t)addr & PAGEMASK;
		if (flags & MAP_DONT_MAP) {
			bool isused;
			uintptr_t min_addr, max_addr;
			if unlikely(!hdrc)
				return HINT_GETADDR(KERNEL_VMHINT_USER_LIBRARY);
			min_addr = (uintptr_t)-1;
			max_addr = 0;
			/* Figure out the min/max byte offsets for program segments. */
			for (i = 0; i < hdrc; ++i) {
				MY_ElfW(Addr) addr;
				MY_ElfW(Word) size;
				if (ATOMIC_READ(hdrv[i].p_type) != PT_LOAD)
					continue;
				addr = ATOMIC_READ(hdrv[i].p_vaddr);
				size = ATOMIC_READ(hdrv[i].p_memsz);
				if unlikely(!size)
					continue;
				if (min_addr > addr)
					min_addr = addr;
				addr += size - 1;
				if (max_addr < addr)
					max_addr = addr;
			}
			total_bytes = (CEILDIV(max_addr, PAGESIZE) -
			               FLOORDIV(min_addr, PAGESIZE)) *
			              PAGESIZE;
			sync_read(THIS_VM);
			isused = vm_isused(THIS_VM,
			                   result,
			                   total_bytes);
			sync_endread(THIS_VM);
			if (isused)
				THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, total_bytes);
			goto done;
		}
	} else {
		uintptr_t min_addr, max_addr;
		if unlikely(!hdrc)
			return HINT_GETADDR(KERNEL_VMHINT_USER_LIBRARY);
		min_addr = (uintptr_t)-1;
		max_addr = 0;
		/* Figure out the min/max byte offsets for program segments. */
		is_first = true;
		for (i = 0; i < hdrc; ++i) {
			MY_ElfW(Addr) addr;
			MY_ElfW(Off) offset;
			MY_ElfW(Word) size, align, filesize;
			if (ATOMIC_READ(hdrv[i].p_type) != PT_LOAD)
				continue;
			addr     = ATOMIC_READ(hdrv[i].p_vaddr);
			size     = ATOMIC_READ(hdrv[i].p_memsz);
			offset   = ATOMIC_READ(hdrv[i].p_offset);
			filesize = ATOMIC_READ(hdrv[i].p_filesz);
			align    = ATOMIC_READ(hdrv[i].p_align);
			if unlikely(!size)
				continue;
			if (min_alignment < align)
				min_alignment = align;
			if (filesize) {
				uintptr_t alignment;
				alignment = offset & PAGEMASK;
				addr -= alignment;
				offset -= alignment;
				size += alignment;
				/* Validate the consistency of the page alignment. */
				if ((addr & PAGEMASK) != addr_page_offset) {
					if (!(flags & MAP_FIXED) && is_first)
						addr_page_offset = addr & PAGEMASK;
					else {
						THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
						      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN,
						      (uintptr_t)addr,
						      PAGEMASK,
						      addr_page_offset);
					}
				}
				addr -= addr_page_offset;
				size += addr_page_offset;
				is_first = false;
				assert(!(addr & PAGEMASK));
			} else {
				size += addr & PAGEMASK;
				addr &= ~PAGEMASK;
			}
			size = CEIL_ALIGN(size, PAGESIZE);
			if (min_addr > addr)
				min_addr = addr;
			addr += size - 1;
			if (max_addr < addr)
				max_addr = addr;
		}
		min_page    = FLOORDIV(min_addr, PAGESIZE);
		total_bytes = (CEILDIV(max_addr, PAGESIZE) - min_page) * PAGESIZE;
		if unlikely(min_alignment & (min_alignment - 1)) {
			THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
			      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECDATAALIGN,
			      min_alignment,
			      min_alignment - 1,
			      0);
		}
		/* Find a suitable target location where we can map the library. */
find_new_candidate:
		sync_read(v);
		result = (byte_t *)vm_getfree(v,
		                              HINT_GETADDR(KERNEL_VMHINT_USER_LIBRARY),
		                              total_bytes,
		                              min_alignment,
		                              HINT_GETMODE(KERNEL_VMHINT_USER_LIBRARY));
		sync_endread(v);
		if unlikely(result == (byte_t *)VM_GETFREE_ERROR)
			THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, total_bytes);
		result -= min_page * PAGESIZE;
		if (flags & MAP_DONT_MAP)
			goto done;
	}
again_map_segments:
	i        = 0;
	is_first = true;
	TRY {
		/* Now that we've got a suitable memory location, move on to actually map the library. */
		for (; i < hdrc; ++i) {
			MY_ElfW(Addr) addr;
			MY_ElfW(Word) size, unaligned_size;
			MY_ElfW(Word) filesize, unaligned_filesize;
			MY_ElfW(Off) offset;
			MY_ElfW(Word) segment_flags;
			uintptr_half_t prot;
			if (ATOMIC_READ(hdrv[i].p_type) != PT_LOAD)
				continue;
			addr          = ATOMIC_READ(hdrv[i].p_vaddr);
			size          = ATOMIC_READ(hdrv[i].p_memsz);
			filesize      = ATOMIC_READ(hdrv[i].p_filesz);
			offset        = ATOMIC_READ(hdrv[i].p_offset);
			segment_flags = ATOMIC_READ(hdrv[i].p_flags);
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
				alignment = offset & PAGEMASK;
				addr -= alignment;
				offset -= alignment;
				size += alignment;
				filesize += alignment;
				/* Validate the consistency of the page alignment. */
				if ((addr & PAGEMASK) != addr_page_offset) {
					if (!(flags & MAP_FIXED) && is_first)
						addr_page_offset = addr & PAGEMASK;
					else {
						FUNC(unmap_range)(v, result, hdrv, i);
						THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
						      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECADDRALIGN,
						      (uintptr_t)addr,
						      PAGEMASK,
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
				assert(!(addr & PAGEMASK));
			} else {
				size += addr & PAGEMASK;
				addr &= ~PAGEMASK;
				unaligned_size     = size;
				unaligned_filesize = filesize;
				size = CEIL_ALIGN(size, PAGESIZE);
			}
			if (size > filesize) {
				/* Map BSS */
				if (!vm_mapat(v,
				              result + addr + filesize,
				              size - filesize,
				              &vm_datablock_anonymous_zero,
				              0,
				              prot,
				              VM_NODE_FLAG_NORMAL,
				              0)) {
unmap_check_overlap_and_find_new_candidate:
					/* Check for illegal overlap */
					if (FUNC(contains_illegal_overlap)(hdrv, hdrc))
						THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, size);
					if (!(flags & MAP_FIXED)) {
						FUNC(unmap_range)(v, result, hdrv, i);
						goto find_new_candidate;
					}
					if (!(flags & MAP_DONT_OVERRIDE)) {
						vm_unmap(v,
						         result + addr,
						         size,
						         VM_UNMAP_ANYTHING |
						         VM_UNMAP_NOKERNPART);
						goto again_map_segments;
					}
					THROW(E_BADALLOC_INSUFFICIENT_VIRTUAL_MEMORY, size);
				}
			}
			if (filesize) {
				if ((offset & PAGEMASK) != 0) {
					THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
					      E_INVALID_ARGUMENT_CONTEXT_LOADLIBRARY_SECFILEALIGN,
					      (uintptr_t)(offset + addr_page_offset),
					      PAGEMASK,
					      addr_page_offset);
				}
				if (!file) {
					file = getdatablock_from_handle((unsigned int)fd,
					                                &file_minoffset,
					                                &file_maxnumbytes);
					/* Make sure that the offset and byte counts are aligned by the pagesize. */
					file_maxnumbytes += file_minoffset & PAGEMASK;
					file_minoffset &= ~PAGEMASK;
					file_maxnumbytes += PAGESIZE - 1;
					file_maxnumbytes &= ~PAGEMASK;
				}
				/* Map file contents */
				if (!vm_mapat_subrange(v,
				                       result + addr,
				                       filesize,
				                       file,
				                       (pos_t)offset,
				                       file_minoffset,
				                       file_maxnumbytes,
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
					byte_t *bss_start;
					bss_start = result + addr + unaligned_filesize;
					if (((uintptr_t)bss_start & PAGEMASK) != 0) {
						/* The .bss area isn't page-aligned, meaning it overlaps with the data-area... */
						size_t bss_overlap, bss_total_size;
						bss_total_size = unaligned_size - unaligned_filesize;
						bss_overlap    = PAGESIZE - (size_t)((uintptr_t)bss_start & PAGEMASK);
						if (bss_overlap > bss_total_size)
							bss_overlap = bss_total_size;
						/* Must `memset(bss_start, 0, bss_overlap)' */
						if (prot & VM_PROT_WRITE) {
							memset(bss_start, 0, bss_overlap);
						} else {
							/* Complicated case: Must write to memory mapped as read-only...
							 * Note that this really shouldn't be something that happens normally,
							 * since I don't see any reason why one would map .bss as read-only.
							 * But still: It is something that is technically allowed by ELF, and
							 *            maybe someone needed a really large section of 0-bytes
							 *            for some kind of stub-implementation... */
							vm_memset(v, bss_start, 0, bss_overlap, true);
						}
					}
				}
			}
		}
	} EXCEPT {
		FUNC(unmap_range)(v, result, hdrv, i);
		xdecref(file);
		RETHROW();
	}
	xdecref(file);
done:
	return result + addr_page_offset;
}

DECL_END

#undef FUNC
#undef MY_ElfW
#undef MY_ELFW
#undef DEFINE_COMPAT_MAPLIBRARY
