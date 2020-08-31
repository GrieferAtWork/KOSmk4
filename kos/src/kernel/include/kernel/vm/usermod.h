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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_USERMOD_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_USERMOD_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_NO_USERMOD
#define CONFIG_HAVE_USERMOD 1
#endif /* !CONFIG_NO_USERMOD */

#ifdef CONFIG_HAVE_USERMOD
#include <debugger/config.h> /* CONFIG_HAVE_DEBUGGER */
#include <kernel/arch/vm/usermod.h>
#include <kernel/malloc-defs.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include <elf.h>

/* API for interacting with ELF binaries mapped into user-space. */

DECL_BEGIN

#ifdef __CC__
struct usermod_section {
	/* HINT: This structure shares (some) binary compatibility with `struct driver_section' */
	WEAK refcnt_t us_refcnt;  /* Reference counter. */
	void         *us_data;    /* [0..us_size][lock(WRITE_ONCE)][owned] Memory mapping for the section's contents. (or (void *)-1 if not loaded) */
	size_t        us_size;    /* [const] Size of the section (in bytes) */
	size_t        us_entsize; /* [const] Section entity size (or 0 if unknown) */
	uintptr_t     us_link;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t     us_info;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t     us_flags;   /* [const] ELF section flags (set of `SHF_*') */
	void        *_us_pad1[1]; /* ... */
	USER void    *us_udata;   /* [?..?][valid_if(us_flags & SHF_ALLOC)] User-space section location (if applicable; else: `NULL'). */
	u16          _us_pad2;    /* ... */
	u16           us_index;   /* [const] Index of this section. */
#if __SIZEOF_POINTER__ > 4
	byte_t       _us_pad3[__SIZEOF_POINTER__ - 4]; /* ... */
#endif /* __SIZEOF_POINTER__ > 4 */
	void         *us_cdata;   /* [0..us_csize][lock(WRITE_ONCE)][owned_if(!= us_data)]
	                           * Decompressed section data. (or same as `us_data' if section isn't compressed)
	                           * NOTE: Set to `(void *)-1' when decompressed section data hasn't been loaded, yet.
	                           * NOTE: A section is compressed when `ds_flags & SHF_COMPRESSED' */
	size_t        us_csize;   /* [lock(WRITE_ONCE)][valid_if(ds_cdata)] Decompressed section size. */
};

/* Destroy the given usermod section. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL usermod_section_destroy)(struct usermod_section *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct usermod_section, us_refcnt, usermod_section_destroy)



/* Return a pointer to the decompressed data blob for `self'.
 * If data could not be decompressed, an `E_INVALID_ARGUMENT' exception is thrown.
 * NOTE: The caller must ensure that raw section data of `self' has been loaded,
 *       as in `self->us_data != (void *)-1'!
 * @return: * : A blob of `self->us_csize' (after the caller) bytes of memory,
 *              representing the section's decompressed memory contents. */
FUNDEF ATTR_RETNONNULL NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *KCALL
usermod_section_cdata(struct usermod_section *__restrict self,
                      gfp_t gfp DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT)
		ASMNAME("driver_section_cdata");
/* @return: NULL: Failed to acquire compressed data. */
FUNDEF NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *
NOTHROW(KCALL usermod_section_cdata_nx)(struct usermod_section *__restrict self,
                                        gfp_t gfp DFL(GFP_NORMAL))
		ASMNAME("driver_section_cdata_nx");



struct usermod_elf {
	pos_t     ue_phoff;     /* [const] == Elf_Ehdr::e_phoff. */
	pos_t     ue_shoff;     /* [const] == Elf_Ehdr::e_shoff. */
	uint16_t  ue_phentsize; /* [const] == Elf_Ehdr::e_phentsize. */
	uint16_t  ue_phnum;     /* [const] == Elf_Ehdr::e_phnum. */
	uint16_t  ue_shentsize; /* [const] == Elf_Ehdr::e_shentsize. */
	uint16_t  ue_shnum;     /* [const] == Elf_Ehdr::e_shnum. */
	uint16_t  ue_shstrndx;  /* [const] == Elf_Ehdr::e_shstrndx. (< ue_shnum) */
	uint16_t _ue_pad[3];    /* ... */
	union {
		void       *ue_shdr;   /* [0..ue_shnum][lock(WRITE_ONCE)][owned] Vector of section headers. */
#ifdef USERMOD_TYPE_ELF32
		Elf32_Shdr *ue_shdr32; /* [0..ue_shnum][lock(WRITE_ONCE)][owned] Vector of section headers. */
#endif /* USERMOD_TYPE_ELF32 */
#ifdef USERMOD_TYPE_ELF64
		Elf64_Shdr *ue_shdr64; /* [0..ue_shnum][lock(WRITE_ONCE)][owned] Vector of section headers. */
#endif /* USERMOD_TYPE_ELF64 */
	};
	char     *ue_shstrtab;  /* [0..1][lock(WRITE_ONCE)][owned] Section headers name table. */
	COMPILER_FLEXIBLE_ARRAY(REF struct usermod_section *,
	                        ue_sections); /* [0..1][lock(WRITE_ONCE)][ue_shnum] Section mappings. */
};

struct inode;
struct path;
struct directory_entry;
struct usermod {
	WEAK refcnt_t               um_refcnt;    /* Reference counter. */
	USER uintptr_t              um_loadaddr;  /* [const] Load address of the module. */
	USER uintptr_t              um_loadstart; /* [const] Lowest address mapped by this module (already adjusted for `um_loadaddr'). */
	USER uintptr_t              um_loadend;   /* [const] Greatest address mapped by this module (already adjusted for `um_loadaddr'). */
	REF struct inode           *um_file;      /* [1..1][const] The backing file of the executable. */
	REF struct path            *um_fspath;    /* [0..1][const] Optional mapping path */
	REF struct directory_entry *um_fsname;    /* [0..1][const] Optional mapping name */
	struct vm                  *um_vm;        /* [1..1][const] The associated VM. Warning: not a reference!
	                                           * If the VM is destroyed, this pointer will be dangling! */
	REF struct usermod         *um_next;      /* [0..1][lock(INTERNAL(um_vm))] Next usermod object. */
	uintptr_t                   um_modtype;   /* [const] Module type (one of `USERMOD_TYPE_*') */
	union {
		struct usermod_elf um_elf; /* [valid_if(USERMOD_TYPE_ISELF(um_modtype))] ELF module. */
	};
};

#if defined(USERMOD_TYPE_ELF32) && defined(USERMOD_TYPE_ELF64)
#define usermod_sizeof_pointer(self) (USERMOD_TYPE_ISELF32((self)->um_modtype) ? 4 : 8)
#elif defined(USERMOD_TYPE_ELF32)
#define usermod_sizeof_pointer(self) 4
#elif defined(USERMOD_TYPE_ELF64)
#define usermod_sizeof_pointer(self) 8
#else /* ... */
#define usermod_sizeof_pointer(self) __SIZEOF_POINTER__
#endif /* !... */


/* Destroy the given usermod object. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL usermod_destroy)(struct usermod *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct usermod, um_refcnt, usermod_destroy)

#define USERMOD_SECTION_LOCK_FNORMAL 0x0000 /* Normal section locking flags. */
#define USERMOD_SECTION_LOCK_FINDEX  0x0001 /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define USERMOD_SECTION_LOCK_FNODATA 0x0002 /* Do not lock section data into kernel memory, unless it was already loaded before. */

/* Lock a named section of a given usermod into
 * memory and return a descriptor for that section.
 * @throws: E_SEGFAULT: Only here because `name' is USER
 * @return: * :   Reference to the section descriptor.
 *                This reference must be released with `decref(return)'
 * @return: NULL: The given usermod `self' doesn't contain any section `name' */
FUNDEF WUNUSED NONNULL((1)) REF struct usermod_section *KCALL
usermod_section_lock(struct usermod *__restrict self,
                     USER CHECKED char const *name,
                     unsigned int flags DFL(USERMOD_SECTION_LOCK_FNORMAL))
		THROWS(E_SEGFAULT, E_BADALLOC);


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
FUNDEF REF struct usermod *FCALL
vm_getusermod(struct vm *__restrict self,
              USER void *addr,
              __BOOL addr_must_be_executable DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Find the first usermod object that maps some page containing a pointer `>= addr'
 * If no module fulfills this requirement, return NULL instead. */
FUNDEF REF struct usermod *FCALL
vm_getusermod_above(struct vm *__restrict self,
                    USER void *addr)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Return the first usermod object that has a starting load start address greater than `prev'
 * When `prev' is NULL, behave the same as `vm_getusermod_above(self, (USER void *)0)'.
 * If no module exists that matches this criteria, return `NULL' instead. */
FUNDEF REF struct usermod *FCALL
vm_getusermod_next(struct vm *__restrict self,
                   struct usermod *prev)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as `vm_getusermod()', but automatically determine the VM to which `addr' belongs.
 * When the kernel was configured with the builtin debugger enabled, this function will
 * check if the builtin debugger is enabled, and if so, lookup `addr' in `task_getvm(dbg_current)'.
 * Otherwise, `THIS_VM' will always searched for `addr' instead. */
#ifdef CONFIG_HAVE_DEBUGGER
FUNDEF REF struct usermod *FCALL
getusermod(USER void *addr,
           __BOOL addr_must_be_executable DFL(0))
		THROWS(E_WOULDBLOCK, E_BADALLOC);
#else /* CONFIG_HAVE_DEBUGGER */
#define getusermod(addr, addr_must_be_executable) \
	vm_getusermod(THIS_VM, addr, addr_must_be_executable)
#endif /* !CONFIG_HAVE_DEBUGGER */

/* Clear out all unused usermod objects from `self' and
 * return non-zero if the cache wasn't already empty. */
FUNDEF NOBLOCK size_t
NOTHROW(FCALL vm_clear_usermod)(struct vm *__restrict self);


/* Callback prototype for `vm_enumusermod()'
 * @param: cookie: Same as the `cookie' argument passed to `vm_enumusermod()'
 * @param: um:     The usermod object that is being enumerated.
 * @return: >= 0:  Add the this value to the total sum to-be returned by `vm_enumusermod()'
 * @return: < 0:   Stop enumeration and have `vm_enumusermod()' immediately re-return this value. */
typedef ssize_t (KCALL *vm_enumusermod_callback_t)(void *cookie, struct usermod *__restrict um);

/* Enumerate all user-space modules that may be mapped within `self'
 * Modules are (generally) enumerated in ascending order, based on
 * their `um_loadstart' values. Note though that while you may optimize
 * for this case, do not rely on this actually being the case!
 * @param: cb:     Callback to-be invoked for every user-module found.
 * @param: cookie: Argument that should be passed to `cb'
 * @return: >= 0:  The sum of all return values of `cb'
 * @return: < 0:   The first negative value returned by `cb' */
FUNDEF ssize_t FCALL
vm_enumusermod(struct vm *__restrict self,
               vm_enumusermod_callback_t cb,
               void *cookie)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_USERMOD */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_USERMOD_H */
