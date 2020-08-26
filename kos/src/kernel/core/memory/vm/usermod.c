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
#ifndef GUARD_KERNEL_SRC_MEMORY_VM_USERMOD_C
#define GUARD_KERNEL_SRC_MEMORY_VM_USERMOD_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/vm/usermod.h>

#ifdef CONFIG_HAVE_USERMOD
#include <debugger/rt.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/panic.h>
#include <kernel/user.h>
#include <kernel/vm.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include <libunwind/unwind.h>

DECL_BEGIN

/* Assert binary compatibility between USERMOD_SECTION and DRIVER_SECTION */
STATIC_ASSERT(offsetof(struct usermod_section, us_refcnt) == offsetof(struct driver_section, ds_refcnt));
STATIC_ASSERT(offsetof(struct usermod_section, us_data) == offsetof(struct driver_section, ds_data));
STATIC_ASSERT(offsetof(struct usermod_section, us_size) == offsetof(struct driver_section, ds_size));
STATIC_ASSERT(offsetof(struct usermod_section, us_entsize) == offsetof(struct driver_section, ds_entsize));
STATIC_ASSERT(offsetof(struct usermod_section, us_link) == offsetof(struct driver_section, ds_link));
STATIC_ASSERT(offsetof(struct usermod_section, us_info) == offsetof(struct driver_section, ds_info));
STATIC_ASSERT(offsetof(struct usermod_section, us_flags) == offsetof(struct driver_section, ds_flags));
STATIC_ASSERT(offsetof(struct usermod_section, us_index) == offsetof(struct driver_section, ds_index));
STATIC_ASSERT(offsetof(struct usermod_section, us_cdata) == offsetof(struct driver_section, ds_cdata));
STATIC_ASSERT(offsetof(struct usermod_section, us_csize) == offsetof(struct driver_section, ds_csize));

STATIC_ASSERT(USERMOD_SECTION_LOCK_FNORMAL == DRIVER_SECTION_LOCK_FNORMAL);
STATIC_ASSERT(USERMOD_SECTION_LOCK_FINDEX == DRIVER_SECTION_LOCK_FINDEX);
STATIC_ASSERT(USERMOD_SECTION_LOCK_FNODATA == DRIVER_SECTION_LOCK_FNODATA);
/**/



#define HINT_ADDR(x, y) x
#define HINT_MODE(x, y) y
#define HINT_GETADDR(x) HINT_ADDR x
#define HINT_GETMODE(x) HINT_MODE x

/* Destroy the given usermod section. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL usermod_section_destroy)(struct usermod_section *__restrict self) {
	if (self->us_data != (void *)-1) {
		/* Must unmap sections data. */
		uintptr_t sect_base;
		size_t sect_size;
		sect_base = (uintptr_t)self->us_data;
		if (sect_base != (uintptr_t)-1) {
			sect_size = self->us_size;
			sect_size += sect_base & PAGEMASK;
			sect_base &= ~PAGEMASK;
			vm_unmap(&vm_kernel,
			         (void *)sect_base,
			         (size_t)CEIL_ALIGN(sect_size, PAGESIZE));
		}
	}
	/* Free compressed section data. */
	if (self->us_cdata != (void *)-1 && self->us_cdata != self->us_data)
		vpage_free(self->us_cdata, (size_t)CEILDIV(self->us_csize, PAGESIZE));
	kfree(self);
}


/* Destroy the given usermod object. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL usermod_destroy)(struct usermod *__restrict self) {
	if (USERMOD_TYPE_ISELF(self->um_modtype)) {
		uint16_t i;
		kfree(self->um_elf.ue_shdr);
		kfree(self->um_elf.ue_shstrtab);
		for (i = 0; i < self->um_elf.ue_shnum; ++i)
			xdecref_likely(self->um_elf.ue_sections[i]);
	}
	decref(self->um_file);
	xdecref(self->um_fspath);
	xdecref(self->um_fsname);
	kfree(self);
}


/* Lazily load section headers. */
PRIVATE NONNULL((1)) void KCALL
usermod_load_elf_shdr(struct usermod *__restrict self) {
	void *shdrs;
	size_t shdrs_size;
	if (ATOMIC_READ(self->um_elf.ue_shdr))
		return; /* Already loaded. */
	shdrs_size = (size_t)self->um_elf.ue_shnum *
	             (size_t)self->um_elf.ue_shentsize;
	inode_loadattr(self->um_file);
	{
		pos_t temp;
		if unlikely(OVERFLOW_UADD(self->um_elf.ue_shoff, shdrs_size, &temp) ||
		            temp > self->um_file->i_filesize)
			THROW(E_INVALID_ARGUMENT);
	}
	shdrs = kmalloc(shdrs_size, GFP_NORMAL);
	TRY {
		inode_readallk(self->um_file,
		               shdrs,
		               shdrs_size,
		               self->um_elf.ue_shoff);
	} EXCEPT {
		kfree(shdrs);
		RETHROW();
	}
	if unlikely(!ATOMIC_CMPXCH(self->um_elf.ue_shdr,
	                           NULL, shdrs)) {
		/* Race condition: Another thread already did the load in the mean time. */
		kfree(shdrs);
	}
}

typedef union {
#ifdef USERMOD_TYPE_ELF32
	Elf32_Shdr e32;
#endif /* USERMOD_TYPE_ELF32 */
#ifdef USERMOD_TYPE_ELF64
	Elf64_Shdr e64;
#endif /* USERMOD_TYPE_ELF64 */
} ElfV_Shdr;

typedef union {
#ifdef USERMOD_TYPE_ELF32
	Elf32_Ehdr e32;
#endif /* USERMOD_TYPE_ELF32 */
#ifdef USERMOD_TYPE_ELF64
	Elf64_Ehdr e64;
#endif /* USERMOD_TYPE_ELF64 */
} ElfV_Ehdr;


typedef union {
#ifdef USERMOD_TYPE_ELF32
	Elf32_Phdr e32;
#endif /* USERMOD_TYPE_ELF32 */
#ifdef USERMOD_TYPE_ELF64
	Elf64_Phdr e64;
#endif /* USERMOD_TYPE_ELF64 */
} ElfV_Phdr;


#if defined(USERMOD_TYPE_ELF32) && defined(USERMOD_TYPE_ELF64)
#define ElfV_field(self, um_modtype, name) (USERMOD_TYPE_ISELF32(um_modtype) ? (self).e32.name : (self).e64.name)
#elif defined(USERMOD_TYPE_ELF32)
#define ElfV_field(self, um_modtype, name) ((self).e32.name)
#elif defined(USERMOD_TYPE_ELF64)
#define ElfV_field(self, um_modtype, name) ((self).e64.name)
#endif /* ... */



/* Lazily load section headers. */
PRIVATE NONNULL((1)) void KCALL
usermod_load_elf_shstrtab(struct usermod *__restrict self) {
	char *shstrtab;
	size_t shstrtab_size;
	pos_t shstrtab_pos;
	assert(self->um_elf.ue_shdr);
	assert(self->um_elf.ue_shstrndx < self->um_elf.ue_shnum);
	if (ATOMIC_READ(self->um_elf.ue_shstrtab))
		return; /* Already loaded. */
	{
		ElfV_Shdr *shstrtab_hdr;
		shstrtab_hdr = (ElfV_Shdr *)((byte_t *)self->um_elf.ue_shdr +
		                             self->um_elf.ue_shstrndx *
		                             self->um_elf.ue_shentsize);
		shstrtab_pos  = (pos_t)ElfV_field(*shstrtab_hdr, self->um_modtype, sh_offset);
		shstrtab_size = (size_t)ElfV_field(*shstrtab_hdr, self->um_modtype, sh_size);
	}
	inode_loadattr(self->um_file);
	{
		pos_t temp;
		if unlikely(OVERFLOW_UADD(shstrtab_pos, shstrtab_size, &temp) ||
		            temp > self->um_file->i_filesize)
			THROW(E_INVALID_ARGUMENT);
	}
	/* Allocate the section header name table. */
	shstrtab = (char *)kmalloc(shstrtab_size, GFP_NORMAL);
	TRY {
		inode_readallk(self->um_file,
		               shstrtab,
		               shstrtab_size,
		               shstrtab_pos);
		{
			size_t usable_size;
			usable_size = kmalloc_usable_size(shstrtab);
			/* Clear out unused trailing memory. */
			memset(shstrtab + shstrtab_size, 0,
			       usable_size - shstrtab_size);
		}
	} EXCEPT {
		kfree(shstrtab);
		RETHROW();
	}
	if unlikely(!ATOMIC_CMPXCH(self->um_elf.ue_shstrtab,
	                           NULL, shstrtab)) {
		/* Race condition: Another thread already did the load in the mean time. */
		kfree(shstrtab);
	}
}

PRIVATE void FCALL
usermod_section_map_into_kernel(struct usermod_section *__restrict self,
                                struct usermod *__restrict um) {
	void *mapaddr, *real_mapaddr;
	size_t map_offset;
	pos_t file_offset, aligned_file_offset, temp;
	size_t aligned_file_size;
	ElfV_Shdr *shdr;
	if (ATOMIC_READ(self->us_data) != (void *)-1)
		return; /* Already loaded. */
	shdr = (ElfV_Shdr *)((byte_t *)um->um_elf.ue_shdr +
	                     self->us_index *
	                     um->um_elf.ue_shentsize);
	file_offset = (pos_t)ElfV_field(*shdr, um->um_modtype, sh_offset);
	COMPILER_READ_BARRIER();
	inode_loadattr(um->um_file);
	if unlikely(OVERFLOW_UADD(file_offset, self->us_size, &temp) ||
	            temp > um->um_file->i_filesize)
		THROW(E_INVALID_ARGUMENT);
	map_offset          = (size_t)(file_offset & (PAGESIZE - 1));
	aligned_file_offset = file_offset - map_offset;
	aligned_file_size   = self->us_size + map_offset;
	aligned_file_size   = CEIL_ALIGN(aligned_file_size, PAGESIZE);
	/* Map the section into kernel memory. */
	mapaddr = vm_map(/* self:              */ &vm_kernel,
	                 /* hint:              */ HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
	                 /* num_bytes:         */ aligned_file_size,
	                 /* min_alignment:     */ PAGESIZE,
	                 /* getfree_mode:      */ HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
	                 /* data:              */ um->um_file,
	                 /* fspath:            */ um->um_fspath,
	                 /* fsname:            */ um->um_fsname,
	                 /* data_start_offset: */ aligned_file_offset,
	                 /* prot:              */ VM_PROT_READ,
	                 /* flag:              */ VM_NODE_FLAG_NOMERGE,
	                 /* guard:             */ 0);
	/* Store the actual base address of the file mapping. */
	real_mapaddr = (byte_t *)mapaddr + map_offset;
	if unlikely(!ATOMIC_CMPXCH(self->us_data, (void *)-1, real_mapaddr)) {
		/* Race condition: Another thread already did the load in the mean time. */
		vm_unmap(&vm_kernel, mapaddr, aligned_file_size);
	}
}


/* Lock a named section of a given usermod into
 * memory and return a descriptor for that section.
 * @throws: E_SEGFAULT: Only here because `name' is USER
 * @return: * :   Reference to the section descriptor.
 *                This reference must be released with `decref(return)'
 * @return: NULL: The given usermod `self' doesn't contain any section `name' */
PUBLIC WUNUSED NONNULL((1)) REF struct usermod_section *KCALL
usermod_section_lock(struct usermod *__restrict self,
                     USER CHECKED char const *name,
                     unsigned int flags)
		THROWS(E_SEGFAULT, E_BADALLOC) {
	uint16_t section_index;
	size_t shstrtab_size;
	ElfV_Shdr *shdr;
	if (!USERMOD_TYPE_ISELF(self->um_modtype))
		goto nope;
	/* Ensure that lazily initialized components have been loaded. */
	usermod_load_elf_shdr(self);
	usermod_load_elf_shstrtab(self);
	if unlikely(flags & USERMOD_SECTION_LOCK_FINDEX) {
		section_index = (uint16_t)(uintptr_t)name;
		if unlikely(section_index >= self->um_elf.ue_shnum)
			goto nope;
		shdr = (ElfV_Shdr *)((byte_t *)self->um_elf.ue_shdr +
		                     section_index *
		                     self->um_elf.ue_shentsize);
		goto got_section_index;
	}
	/* Now find the index of the appropriate section. */
	shstrtab_size = kmalloc_usable_size(self->um_elf.ue_shstrtab);
	for (section_index = 0;
	     section_index < self->um_elf.ue_shnum; ++section_index) {
		char const *shdr_name;
		uintptr_t shdr_name_offset;
		shdr = (ElfV_Shdr *)((byte_t *)self->um_elf.ue_shdr +
		                     section_index *
		                     self->um_elf.ue_shentsize);
		shdr_name_offset = ElfV_field(*shdr, self->um_modtype, sh_name);
		COMPILER_READ_BARRIER();
		if unlikely(shdr_name_offset >= shstrtab_size)
			continue;
		shdr_name = self->um_elf.ue_shstrtab + shdr_name_offset;
		if (strcmp(shdr_name, name) == 0) { /* found it! */
			REF struct usermod_section *result, *real_result;
got_section_index:
			result = self->um_elf.ue_sections[section_index];
			if (result) {
return_existing_result:
				/* Make sure that the section is mapped into
				 * the kernel, if the caller wants this. */
				if (!(flags & USERMOD_SECTION_LOCK_FNODATA))
					usermod_section_map_into_kernel(result, self);
				incref(result);
				return result;
			}
			/* Lazily allocate the section. */
			result = (REF struct usermod_section *)kmalloc(sizeof(struct usermod_section),
			                                               GFP_NORMAL);
			TRY {
				result->us_refcnt  = 2; /* +1: return; +1: self->um_elf.ue_sections[section_index] */
				result->us_size    = ElfV_field(*shdr, self->um_modtype, sh_size);
				result->us_entsize = ElfV_field(*shdr, self->um_modtype, sh_entsize);
				result->us_link    = ElfV_field(*shdr, self->um_modtype, sh_info);
				result->us_info    = ElfV_field(*shdr, self->um_modtype, sh_info);
				result->us_flags   = ElfV_field(*shdr, self->um_modtype, sh_flags);
				result->us_index   = section_index;
				COMPILER_READ_BARRIER();
				result->us_data  = (void *)-1; /* Lazily initialized. */
				result->us_cdata = (void *)-1; /* Lazily initialized. */
				result->us_udata = NULL;
				if (result->us_flags & SHF_ALLOC) {
					result->us_udata = (USER byte_t *)(self->um_loadaddr +
					                                   ElfV_field(*shdr, self->um_modtype,
					                                              sh_addr));
					validate_user(result->us_udata, result->us_size);
				}
				if (!(flags & USERMOD_SECTION_LOCK_FNODATA)) {
					/* Must map the section into memory. */
					void *mapaddr;
					size_t map_offset;
					pos_t file_offset, aligned_file_offset, temp;
					size_t aligned_file_size;
					file_offset = (pos_t)ElfV_field(*shdr, self->um_modtype, sh_offset);
					COMPILER_READ_BARRIER();
					inode_loadattr(self->um_file);
					if unlikely(OVERFLOW_UADD(file_offset, result->us_size, &temp) ||
					            temp > self->um_file->i_filesize)
						THROW(E_INVALID_ARGUMENT);
					map_offset          = (size_t)(file_offset & (PAGESIZE - 1));
					aligned_file_offset = file_offset - map_offset;
					aligned_file_size   = result->us_size + map_offset;
					aligned_file_size   = CEIL_ALIGN(aligned_file_size, PAGESIZE);
					/* Map the section into kernel memory. */
					mapaddr = vm_map(/* self:              */ &vm_kernel,
					                 /* hint:              */ HINT_GETADDR(KERNEL_VMHINT_TEMPORARY),
					                 /* num_bytes:         */ aligned_file_size,
					                 /* min_alignment:     */ PAGESIZE,
					                 /* getfree_mode:      */ HINT_GETMODE(KERNEL_VMHINT_TEMPORARY),
					                 /* data:              */ self->um_file,
					                 /* fspath:            */ self->um_fspath,
					                 /* fsname:            */ self->um_fsname,
					                 /* data_start_offset: */ aligned_file_offset,
					                 /* prot:              */ VM_PROT_READ,
					                 /* flag:              */ VM_NODE_FLAG_NOMERGE,
					                 /* guard:             */ 0);
					/* Store the actual base address of the file mapping. */
					result->us_data = (byte_t *)mapaddr + map_offset;
				}
			} EXCEPT {
				kfree(result);
				RETHROW();
			}
			real_result = ATOMIC_CMPXCH_VAL(self->um_elf.ue_sections[section_index],
			                                NULL, result);
			if unlikely(real_result) {
				/* Race condition: Another thread already did the load in the mean time. */
				destroy(result);
				result = incref(real_result);
				goto return_existing_result;
			}
			return result;
		}
	}
nope:
	return NULL;
}



/* Find an vm node that is apart of the same continuous block
 * of fully mapped memory that the given `self' is also apart
 * of.
 * The node that this function is on the look-out for must be
 * backed by an INode mapping, as well as share the same prot
 * characteristics as `self'. */
PRIVATE NOBLOCK WUNUSED ATTR_PURE NONNULL((1)) struct vm_node *
NOTHROW(FCALL vm_node_find_inode_mapping)(struct vm_node *__restrict self) {
	struct vm_node *lhs_iter;
	struct vm_node *rhs_iter;
	struct vm_node *next;
	lhs_iter = self;
	rhs_iter = self->vn_byaddr.ln_next;
	if (rhs_iter && (vm_node_getminpageid(rhs_iter) !=
	                 vm_node_getmaxpageid(lhs_iter) + 1))
		rhs_iter = NULL;
	while (lhs_iter && rhs_iter) {
		if (lhs_iter->vn_prot != self->vn_prot ||
		    !lhs_iter->vn_part || !lhs_iter->vn_block) {
			lhs_iter = NULL;
			break;
		}
		/* Check if `lhs_iter' might be what we're looking for. */
		if (vm_datablock_isinode(lhs_iter->vn_block))
			return lhs_iter;
		if (rhs_iter->vn_prot != self->vn_prot ||
		    !rhs_iter->vn_part || !rhs_iter->vn_block) {
			rhs_iter = NULL;
			break;
		}
		/* Check if `rhs_iter' might be what we're looking for. */
		if (vm_datablock_isinode(rhs_iter->vn_block))
			return rhs_iter;

		/* Go to the next node on the left. */
		next = VM_NODE_HASPREV(lhs_iter, self->vn_vm)
		       ? VM_NODE_PREV(lhs_iter)
		       : NULL;
		/* Verify continuity. */
		if (next && (vm_node_getmaxpageid(next) + 1 !=
		             vm_node_getminpageid(lhs_iter)))
			next = NULL;
		lhs_iter = next;

		/* Go to the next node on the right. */
		next = VM_NODE_HASNEXT(rhs_iter, self->vn_vm)
		       ? VM_NODE_NEXT(rhs_iter)
		       : NULL;
		/* Verify continuity. */
		if (next && (vm_node_getminpageid(next) !=
		             vm_node_getmaxpageid(rhs_iter) + 1))
			next = NULL;
		rhs_iter = next;
	}
	/* Walk the remainder. */
	if (lhs_iter) {
		for (;;) {
			if (lhs_iter->vn_prot != self->vn_prot ||
			    !lhs_iter->vn_part || !lhs_iter->vn_block)
				break;
			if (vm_datablock_isinode(lhs_iter->vn_block))
				return lhs_iter;
			if (!VM_NODE_HASPREV(lhs_iter, self->vn_vm))
				break;
			next = VM_NODE_PREV(lhs_iter);
			if (vm_node_getmaxpageid(next) + 1 !=
			    vm_node_getminpageid(lhs_iter))
				break;
			lhs_iter = next;
		}
	} else if (rhs_iter) {
		for (;;) {
			if (rhs_iter->vn_prot != self->vn_prot ||
			    !rhs_iter->vn_part || !rhs_iter->vn_block)
				break;
			if (vm_datablock_isinode(rhs_iter->vn_block))
				return rhs_iter;
			if (!VM_NODE_HASNEXT(rhs_iter, self->vn_vm))
				break;
			next = VM_NODE_NEXT(rhs_iter);
			if (vm_node_getminpageid(next) !=
			    vm_node_getmaxpageid(rhs_iter) + 1)
				break;
			rhs_iter = next;
		}
	}
	/* Nothing of interest found... */
	return NULL;
}


/* Create a new user module for the given `addr'
 * @return: NULL: No module exists at the given `addr' */
PRIVATE REF struct usermod *FCALL
vm_create_usermod(struct vm *__restrict self,
                  USER CHECKED void *addr,
                  bool addr_must_be_executable)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct usermod *result;
	REF struct inode /*     */ *map_inode;        /* [1..1] The INode that is being mapped. */
	REF struct path /*      */ *map_inode_path;   /* [0..1][const] Optional mapping path */
	REF struct directory_entry *map_inode_name;   /* [0..1][const] Optional mapping name */
	pos_t /*                 */ map_inode_offset; /* File-offset where `map_inode_addr' exists. */
	USER void /*            */ *map_inode_addr;   /* Starting address of `map_inode_offset'. */
	uintptr_t modtype;
	struct vm_node *node;
	sync_read(self);
	node = vm_getnodeofaddress(self, addr);
	if (!node) {
unlock_and_nope:
		sync_endread(self);
		return NULL;
	}
	if (addr_must_be_executable && !(node->vn_prot & VM_PROT_EXEC))
		goto unlock_and_nope;
	node = vm_node_find_inode_mapping(node);
	if (!node)
		goto unlock_and_nope; /* Nope... */
	assert(vm_datablock_isinode(node->vn_block));
	/* Alright! We've found a node we can use!
	 * Garther all of the information we need and release the VM lock. */
	map_inode        = (REF struct inode *)incref(node->vn_block);
	map_inode_path   = xincref(node->vn_fspath);
	map_inode_name   = xincref(node->vn_fsname);
	map_inode_offset = vm_datapart_startbyte(node->vn_part);
	map_inode_addr   = vm_node_getstart(node);
	sync_endread(self);
	TRY {
		ElfV_Ehdr ehdr;
		/* Load the executable header, and verify that this is a supported ELF binary. */
		inode_readallk(map_inode, &ehdr, sizeof(ehdr), 0);
		if (ehdr.e32.e_ident[EI_MAG0] != ELFMAG0 ||
		    ehdr.e32.e_ident[EI_MAG1] != ELFMAG1 ||
		    ehdr.e32.e_ident[EI_MAG2] != ELFMAG2 ||
		    ehdr.e32.e_ident[EI_MAG3] != ELFMAG3) {
decref_and_nope:
			xdecref_unlikely(map_inode_name);
			xdecref_unlikely(map_inode_path);
			decref_unlikely(map_inode);
			return NULL;
		}
#ifdef USERMOD_TYPE_ELF32
		if (ehdr.e32.e_ident[EI_CLASS] == ELFCLASS32)
			modtype = USERMOD_TYPE_ELF32;
		else
#endif /* USERMOD_TYPE_ELF32 */
#ifdef USERMOD_TYPE_ELF64
		if (ehdr.e32.e_ident[EI_CLASS] == ELFCLASS64)
			modtype = USERMOD_TYPE_ELF64;
		else
#endif /* USERMOD_TYPE_ELF64 */
		{
			/* Unsupported class type */
			goto decref_and_nope;
		}
		/* Load program headers. */
		{
			ElfV_Phdr *phdrv;
			uint16_t phentsize, shentsize;
			uint16_t phnum, shnum;
			size_t phsize, shsize;
			pos_t phoff, shoff;
			phentsize = ElfV_field(ehdr, modtype, e_phentsize);
			shentsize = ElfV_field(ehdr, modtype, e_shentsize);
			phnum     = ElfV_field(ehdr, modtype, e_phnum);
			shnum     = ElfV_field(ehdr, modtype, e_shnum);
			phoff     = (pos_t)ElfV_field(ehdr, modtype, e_phoff);
			shoff     = (pos_t)ElfV_field(ehdr, modtype, e_shoff);
			phsize    = phentsize * phnum;
			shsize    = shentsize * shnum;
			{
				pos_t temp;
				inode_loadattr(map_inode);
				/* Validate header fields. */
				if unlikely(OVERFLOW_UADD(phoff, phsize, &temp) ||
				            temp > map_inode->i_filesize)
					goto decref_and_nope;
				if unlikely(OVERFLOW_UADD(shoff, shsize, &temp) ||
				            temp > map_inode->i_filesize)
					goto decref_and_nope;
				if unlikely(ElfV_field(ehdr, modtype, e_shstrndx) >= shnum)
					goto decref_and_nope;
			}
			phdrv = (ElfV_Phdr *)kmalloc(phsize, GFP_NORMAL);
			TRY {
				uint16_t i;
				ElfV_Phdr *phdr;
				size_t aligned_phdr_file_shift;
				pos_t aligned_phdr_file_offset;
				size_t aligned_phdr_file_size;
				inode_readallk(map_inode, phdrv, phsize, phoff);
				/* Find the program header that contains `map_inode_offset' */
				for (i = 0; i < phnum; ++i) {
					pos_t temp;
					phdr = (ElfV_Phdr *)((byte_t *)phdrv + i * phentsize);
					aligned_phdr_file_offset = (pos_t)ElfV_field(*phdr, modtype, p_offset);
					aligned_phdr_file_size   = ElfV_field(*phdr, modtype, p_filesz);
					aligned_phdr_file_shift  = (size_t)(aligned_phdr_file_offset & (PAGESIZE - 1));
					aligned_phdr_file_size   += aligned_phdr_file_shift;
					aligned_phdr_file_offset -= aligned_phdr_file_shift;
					if (map_inode_offset < aligned_phdr_file_offset)
						continue;
					if (OVERFLOW_UADD(aligned_phdr_file_offset, aligned_phdr_file_size, &temp))
						goto free_phdrv_and_decref_and_nope;
					if (map_inode_offset < temp)
						goto found_correct_phdr; /* Found it! */
				}
free_phdrv_and_decref_and_nope:
				kfree(phdrv);
				goto decref_and_nope;
				{
					size_t offset_in_segment;
					USER void *segment_address;
					USER CHECKED uintptr_t loadaddr;
found_correct_phdr:
					offset_in_segment = (size_t)(map_inode_offset - aligned_phdr_file_offset);
					segment_address   = (byte_t *)map_inode_addr - offset_in_segment;
					/* Calculate the effective module load address. */
					loadaddr = (uintptr_t)segment_address - (ElfV_field(*phdr, modtype, p_vaddr) -
					                                         aligned_phdr_file_shift);
					/* Create a new usermod object. */
					result = (REF struct usermod *)kmalloc(offsetof(struct usermod, um_elf.ue_sections) +
					                                       shnum * sizeof(REF struct usermod_section *),
					                                       GFP_CALLOC);
					result->um_loadaddr = loadaddr;

					/* Figure out the module's expected start/end addresses. */
					result->um_loadstart = (uintptr_t)-1;
					result->um_loadend   = 0;
					for (i = 0; i < phnum; ++i) {
						uintptr_t ph_start, ph_end;
						phdr     = (ElfV_Phdr *)((byte_t *)phdrv + i * phentsize);
						ph_start = ElfV_field(*phdr, modtype, p_vaddr);
						ph_end   = ph_start + ElfV_field(*phdr, modtype, p_memsz);
						ph_start = FLOOR_ALIGN(ph_end, PAGESIZE);
						ph_end   = CEIL_ALIGN(ph_end, PAGESIZE);
						if unlikely(ph_end < ph_start) {
free_result_and_free_phdrv_and_decref_and_nope:
							kfree(result);
							goto free_phdrv_and_decref_and_nope;
						}
						if (result->um_loadstart > ph_start)
							result->um_loadstart = ph_start;
						if (result->um_loadend < ph_end)
							result->um_loadend = ph_end;
					}
					if unlikely(OVERFLOW_UADD(result->um_loadstart, loadaddr, &result->um_loadstart))
						goto free_result_and_free_phdrv_and_decref_and_nope;
					if unlikely(OVERFLOW_UADD(result->um_loadend, loadaddr, &result->um_loadend))
						goto free_result_and_free_phdrv_and_decref_and_nope;
				}
			} EXCEPT {
				kfree(phdrv);
				RETHROW();
			}
			kfree(phdrv);
			result->um_elf.ue_phoff     = phoff;
			result->um_elf.ue_shoff     = shoff;
			result->um_elf.ue_phentsize = phentsize;
			result->um_elf.ue_phnum     = phnum;
			result->um_elf.ue_shentsize = shentsize;
			result->um_elf.ue_shnum     = shnum;
			result->um_elf.ue_shstrndx  = ElfV_field(ehdr, modtype, e_shstrndx);
		}
	} EXCEPT {
		xdecref_unlikely(map_inode_name);
		xdecref_unlikely(map_inode_path);
		decref_unlikely(map_inode);
		RETHROW();
	}
	/* Fill in remaining fields of `result' */
	result->um_refcnt  = 1;
	result->um_file    = map_inode;      /* Inherit reference */
	result->um_fspath  = map_inode_path; /* Inherit reference */
	result->um_fsname  = map_inode_name; /* Inherit reference */
	result->um_modtype = modtype;
	result->um_vm      = self;
	return result;
}


/* Find the user-space module that resides at the given address.
 * NOTE: After the kernel has been poisoned, this function can no longer be used
 *       to load new user-space modules, but can only be used to access ones that
 *       were already in-cache.
 *       This is done as a safety measure, since loading additional user-space
 *       module descriptors requires the use of filesystem and disk I/O, which
 *       is something that simply goes too far when the system is already unstable.
 * @param: addr_must_be_executable: Unless a know module already exists for the given
 *                                  address, fail unless the backing VM node is executable.
 *                                  Should be set to true if you believe that `addr' should
 *                                  be a program counter position.
 * @return: * :   A reference to the user-module that overlaps with the given address.
 * @return: NULL: No executable object exists at the given location. */
PUBLIC REF struct usermod *FCALL
vm_getusermod(struct vm *__restrict self,
              USER CHECKED void *addr,
              bool addr_must_be_executable)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct usermod *result;

	/* The kernel VM can't possibly contain user-space modules! */
	if unlikely(self == &vm_kernel)
		return NULL;

	/* TODO: Search the cache of `self'. */
	if (kernel_poisoned())
		return NULL;

	result = vm_create_usermod(self, addr, addr_must_be_executable);

	/* TODO: (try to) add to the cache of `self'. */
	return result;
}

/* Clear out all unused usermod objects from `self' and return the
 * amount of memory that became available as the result of this. */
PUBLIC NOBLOCK size_t
NOTHROW(FCALL vm_clear_usermod)(struct vm *__restrict self) {
	/* TODO: Clear the cache for `self' */
	COMPILER_IMPURE();
	(void)self;
	return 0;
}



/* Enumerate all user-space modules that may be mapped within `self'
 * Modules are (generally) enumerated in ascending order, based on
 * their `um_loadstart' values. Note though that while you may optimize
 * for this case, do not rely on this actually being the case!
 * @param: cb:     Callback to-be invoked for every user-module found.
 * @param: cookie: Argument that should be passed to `cb'
 * @return: >= 0:  The sum of all return values of `cb'
 * @return: < 0:   The first negative value returned by `cb' */
PUBLIC ssize_t FCALL
vm_enumusermod(struct vm *__restrict self,
               vm_enumusermod_callback_t cb,
               void *cookie)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	/* Special case: the kernel VM can never house user-space modules */
	if (self == &vm_kernel)
		return 0;
	/* TODO */
	COMPILER_IMPURE();
	(void)self;
	(void)cb;
	(void)cookie;
	return 0;
}


#ifdef CONFIG_HAVE_DEBUGGER
PUBLIC REF struct usermod *FCALL
getusermod(USER CHECKED void *addr,
           bool addr_must_be_executable)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	REF struct usermod *result;
	REF struct vm *current_vm;
	if (!dbg_active) {
		/* Use the current VM */
		return vm_getusermod(THIS_VM, addr, addr_must_be_executable);
	}
	/* Use the VM of the thread currently selected by the debugger. */
	current_vm = task_getvm(dbg_current);
	{
		FINALLY_DECREF_UNLIKELY(current_vm);
		result = vm_getusermod(current_vm,
		                       addr,
		                       addr_must_be_executable);
	}
	return result;
}
#endif /* CONFIG_HAVE_DEBUGGER */


PRIVATE ATTR_NOINLINE NONNULL((2, 4)) unsigned int LIBUNWIND_CC
unwind_userspace(void *absolute_pc,
                 unwind_getreg_t reg_getter, void const *reg_getter_arg,
                 unwind_setreg_t reg_setter, void *reg_setter_arg) {
	/* Unwind a user-space location. */
	unsigned int result = UNWIND_NO_FRAME;
	struct exception_info exinfo;
	REF struct usermod *um;
	REF struct usermod_section *eh_frame;
	/* Preserve exception information. */
	memcpy(&exinfo, error_info(), sizeof(struct exception_info));
	TRY {
		um = getusermod(absolute_pc, true);
		if (!um)
			goto done;
		/* In order to properly unwind memory, we'd have to switch our VM to
		 * match `um->um_vm'. An operation like that would be too dangerous
		 * to perform after the kernel's already been poisoned. */
		if (kernel_poisoned() && um->um_vm != THIS_VM) {
			decref_unlikely(um);
			goto done;
		}
		/* Search for the `.eh_frame' section. */
		TRY {
			eh_frame = usermod_section_lock(um, ".eh_frame",
			                                DRIVER_SECTION_LOCK_FNODATA);
		} EXCEPT {
			decref_unlikely(um);
			goto restore_except;
		}
	} EXCEPT {
		goto restore_except;
	}
	if unlikely(!eh_frame)
		goto done_um;
	/* Make sure that the `.eh_frame' section is allocated in the user-program. */
	if unlikely(!(eh_frame->us_flags & SHF_ALLOC))
		goto done_um_eh_frame;
	/* Now that everything's been loaded, any further exceptions (like
	 * those thrown by the callback's we've been given) must be propagated
	 * normally. */
	TRY {
		REF struct vm *oldvm;
		oldvm = incref(THIS_VM);
		TRY {
			/* Must switch VM to the one of `um' in order to get user-space memory
			 * into the expected state for the unwind handler to do its thing. */
			if (oldvm != um->um_vm)
				task_setvm(um->um_vm);
			TRY {
				unwind_fde_t fde;
				/* NOTE: We use the user-space's mapping of the .eh_frame section here,
				 *       since `.eh_frame' often uses pointer encodings that are relative
				 *       to the .eh_frame-section itself, meaning that in order to properly
				 *       decode the contained information, its mapping must be placed at
				 *       the correct location.
				 * Another alternative to fixing this would be to add a load-offset argument
				 * to `dwarf_decode_pointer()', as well as recursively all of the eh_frame-
				 * related functions that somehow make use of it, where this argument then
				 * describes the offset from the .eh_frame that was loaded, towards the one
				 * that would actually exist for user-space.
				 * However the added complexity it's worth it for this one special case, and
				 * since we already have to switch VM to the user-space's one in order to
				 * restore registers that were spilled onto the stack, we might as well also
				 * make use of the actual `.eh_frame' section (assuming that it is where it
				 * should be) */
				result = unwind_fde_scan((byte_t *)eh_frame->us_udata,
				                         (byte_t *)eh_frame->us_udata + eh_frame->us_size,
				                         absolute_pc,
				                         &fde,
				                         usermod_sizeof_pointer(um));
				if (result == UNWIND_SUCCESS) {
					/* Found the FDE. - Now to execute it's program! */
					unwind_cfa_state_t cfa;
					result = unwind_fde_exec(&fde, &cfa, absolute_pc);
					if unlikely(result == UNWIND_SUCCESS) {
						/* And finally: Apply register modifications. */
						result = unwind_cfa_apply(&cfa, &fde, absolute_pc,
						                          reg_getter, reg_getter_arg,
						                          reg_setter, reg_setter_arg);
					}
				}
			} EXCEPT {
				if (oldvm != um->um_vm)
					task_setvm(oldvm);
				RETHROW();
			}
			if (oldvm != um->um_vm)
				task_setvm(oldvm);
		} EXCEPT {
			decref_unlikely(oldvm);
			RETHROW();
		}
		decref_unlikely(oldvm);
	} EXCEPT {
		decref_unlikely(eh_frame);
		decref_unlikely(um);
		RETHROW();
	}
done_um_eh_frame:
	decref_unlikely(eh_frame);
done_um:
	decref_unlikely(um);
done:
	return result;
restore_except:
	memcpy(error_info(), &exinfo, sizeof(struct exception_info));
	goto done;
}

LIBUNWIND_DECL NONNULL((2, 4)) unsigned int LIBUNWIND_CC
unwind_for_debug(void *absolute_pc,
                 unwind_getreg_t reg_getter, void const *reg_getter_arg,
                 unwind_setreg_t reg_setter, void *reg_setter_arg) {
	/* For non-userspace addresses, use the regular, old unwind() function! */
	unsigned int result;
	if (!ADDR_ISUSER(absolute_pc)) {
		result = unwind(absolute_pc,
		                reg_getter, reg_getter_arg,
		                reg_setter, reg_setter_arg);
	} else {
		result = unwind_userspace(absolute_pc,
		                          reg_getter, reg_getter_arg,
		                          reg_setter, reg_setter_arg);
	}
	return result;
}



DECL_END

#endif /* CONFIG_HAVE_USERMOD */

#endif /* !GUARD_KERNEL_SRC_MEMORY_VM_USERMOD_C */
