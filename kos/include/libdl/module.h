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
#ifndef _LIBDL_MODULE_H
#define _LIBDL_MODULE_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/__atomic.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sched/atomic-rwlock.h>
#include <hybrid/typecore.h>

#include <kos/anno.h>
#include <kos/exec/elf.h> /* ElfW */
#include <kos/kernel/types.h>
#include <kos/refcnt.h>
#include <kos/types.h>

#ifndef __BUILDING_LIBDL
#ifndef DL_EXTENSION_FORMAT
#error "Must `struct dlmodule_format my_format; #define DL_EXTENSION_FORMAT my_format' before #including this file"
#endif /* !DL_EXTENSION_FORMAT */
#define DL_API_SYMBOL(name) DL_EXTENSION_FORMAT.df_core->name
#else /* !__BUILDING_LIBDL */
#define DL_API_SYMBOL(name) name
#endif /* __BUILDING_LIBDL */

#ifdef __CC__
DECL_BEGIN

/* Flag set while a module is still being loaded.
 * -> Used to detect cyclic dependencies. */
#undef RTLD_LOADING
#define RTLD_LOADING __UINT32_C(0x40000000)

#if ELF_ARCH_USESRELA
/* jmp relocation have addends. */
#define RTLD_JMPRELA __UINT32_C(0x20000000)
#endif /* ELF_ARCH_USESRELA */


#ifndef __DLFCN_CC
#define __DLFCN_CC  __LIBCCALL
#define __DLFCN_VCC __VLIBCCALL
#endif /* !__DLFCN_CC */

#ifndef __DlSection_defined
#define __DlSection_defined
struct dlsection;
typedef struct dlsection DlSection;
#endif /* !__DlSection_defined */

#ifndef __DlModule_defined
#define __DlModule_defined
struct dlmodule;
typedef struct dlmodule DlModule;
#endif /* !__DlModule_defined */

#define DLSECTION_FLAG_NORMAL 0x0000 /* Normal flags */
#define DLSECTION_FLAG_OWNED  0x0001 /* Section data is owned by the section descriptor. */
struct dlsection {
	void                *ds_data;        /* [0..ds_size][lock(WRITE_ONCE)]
	                                      * [owned_if(ds_flags & DLSECTION_FLAG_OWNED)]
	                                      * Memory mapping for the section's contents.
	                                      * NOTE: Set to `(void *)-1' when section data hasn't been loaded, yet. */
	size_t               ds_size;        /* [const] Size of the section (in bytes) */
	size_t               ds_entsize;     /* [const] Section entry size (or 0 if unknown) */
	uintptr_t            ds_link;        /* [const] Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t            ds_info;        /* [const] Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t            ds_elfflags;    /* [const] ELF section flags (Set of `SHF_*') */
	__WEAK refcnt_t      ds_refcnt;      /* Reference counter. */
	struct atomic_rwlock ds_module_lock; /* Lock for `ds_module' */
	__REF DlModule      *ds_module;      /* [0..1][ref_if(!(ds_flags & DLSECTION_FLAG_OWNED))][lock(ds_module_lock)]
	                                      * Pointer to the module (or NULL if section data is owned, and the module was destroyed) */
	__REF DlSection     *ds_dangling;    /* [0..1][lock(ds_module->dm_sections_lock))] Chain of dangling sections.
	                                      * NOTE: Set  to `(REF DlSection *)-1'  if  the section  isn't  dangling. */
	uintptr_half_t       ds_flags;       /* [const] Section flags (Set of `ELF_DLSECTION_FLAG_*') */
	uintptr_half_t       ds_index;       /* [const] Index of this section. */
	void                *ds_cdata;       /* [0..ds_csize][lock(WRITE_ONCE)][owned_if(!= ds_data)]
	                                      * Decompressed section data.  (or same  as `ds_data' if  section isn't  compressed)
	                                      * NOTE: Set to `(void *)-1' when decompressed section data hasn't been loaded, yet.
	                                      * NOTE: A section is compressed when `ds_flags & SHF_COMPRESSED' */
	size_t               ds_csize;       /* [const][lock(WRITE_ONCE)][valid_if(ds_cdata)] Decompressed section size. */
};

/* Helper macros for `struct dlsection::ds_module_lock' */
#define DlSection_ModuleMustReap(self)   0
#define DlSection_ModuleReap(self)       (void)0
#define _DlSection_ModuleReap(self)      (void)0
#define DlSection_ModuleWrite(self)      atomic_rwlock_write(&(self)->ds_module_lock)
#define DlSection_ModuleTryWrite(self)   atomic_rwlock_trywrite(&(self)->ds_module_lock)
#define DlSection_ModuleEndWrite(self)   (atomic_rwlock_endwrite(&(self)->ds_module_lock), DlSection_ModuleReap(self))
#define _DlSection_ModuleEndWrite(self)  atomic_rwlock_endwrite(&(self)->ds_module_lock)
#define DlSection_ModuleRead(self)       atomic_rwlock_read(&(self)->ds_module_lock)
#define DlSection_ModuleTryread(self)    atomic_rwlock_tryread(&(self)->ds_module_lock)
#define _DlSection_ModuleEndRead(self)   atomic_rwlock_endread(&(self)->ds_module_lock)
#define DlSection_ModuleEndRead(self)    (void)(atomic_rwlock_endread(&(self)->ds_module_lock) && (DlSection_ModuleReap(self), 0))
#define _DlSection_ModuleEnd(self)       atomic_rwlock_end(&(self)->ds_module_lock)
#define DlSection_ModuleEnd(self)        (void)(atomic_rwlock_end(&(self)->ds_module_lock) && (DlSection_ModuleReap(self), 0))
#define DlSection_ModuleUpgrade(self)    atomic_rwlock_upgrade(&(self)->ds_module_lock)
#define DlSection_ModuleTryUpgrade(self) atomic_rwlock_tryupgrade(&(self)->ds_module_lock)
#define DlSection_ModuleDowngrade(self)  atomic_rwlock_downgrade(&(self)->ds_module_lock)
#define DlSection_ModuleReading(self)    atomic_rwlock_reading(&(self)->ds_module_lock)
#define DlSection_ModuleWriting(self)    atomic_rwlock_writing(&(self)->ds_module_lock)
#define DlSection_ModuleCanRead(self)    atomic_rwlock_canread(&(self)->ds_module_lock)
#define DlSection_ModuleCanWrite(self)   atomic_rwlock_canwrite(&(self)->ds_module_lock)
#define DlSection_ModuleWaitRead(self)   atomic_rwlock_waitread(&(self)->ds_module_lock)
#define DlSection_ModuleWaitWrite(self)  atomic_rwlock_waitwrite(&(self)->ds_module_lock)


#ifdef __INTELLISENSE__
INTDEF NONNULL((1)) void NOTHROW_NCX(DlSection_Incref)(__USER DlSection *self) __THROWS(E_SEGFAULT);
INTDEF NONNULL((1)) void NOTHROW_NCX(DlSection_Decref)(__USER DlSection *self) __THROWS(E_SEGFAULT);
#else /* __INTELLISENSE__ */
#define DlSection_Incref(self) \
	__hybrid_atomic_inc((self)->ds_refcnt, __ATOMIC_SEQ_CST)
#define DlSection_Decref(self)                                              \
	(void)(__hybrid_atomic_decfetch((self)->ds_refcnt, __ATOMIC_SEQ_CST) || \
	       (DL_API_SYMBOL(DlSection_Destroy)(self), 0))
#endif /* !__INTELLISENSE__ */

LOCAL ATTR_ARTIFICIAL NONNULL((1)) __BOOL
NOTHROW_NCX(LIBDL_CC DlSection_TryIncref)(__USER DlSection *self) __THROWS(E_SEGFAULT) {
	refcnt_t refcnt;
	do {
		refcnt = __hybrid_atomic_load(self->ds_refcnt, __ATOMIC_ACQUIRE);
		if (!refcnt)
			return 0;
	} while (!__hybrid_atomic_cmpxch_weak(self->ds_refcnt, refcnt, refcnt + 1,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	return 1;
}

#ifdef __BUILDING_LIBDL
INTDEF NONNULL((1)) void
NOTHROW_NCX(LIBDL_CC DlSection_Destroy)(__USER DlSection *self) __THROWS(E_SEGFAULT);
#endif /* __BUILDING_LIBDL */

struct dlmodule_finalizer {
	void (LIBDL_CC *df_func)(void *arg); /* [1..1] Finalizer callback. */
	void           *df_arg;              /* [?..?] Callback argument. */
};

struct dlmodule_finalizers {
	struct atomic_rwlock       df_lock; /* Lock for finalizer callbacks (left dangling in read-mode for finalizer invocation) */
	size_t                     df_size; /* [lock(df_lock)] # of registered callbacks. */
	struct dlmodule_finalizer *df_list; /* [lock(df_lock)][1..df_size][owned] Vector of callbacks. */
};

#ifndef __elfw_hashtable_defined
#define __elfw_hashtable_defined
typedef struct elfW(hashtable) {
	ElfW(Word) ht_nbuckts;      /* # of buckets. */
	ElfW(Word) ht_nchains;      /* # of symbols. */
	ElfW(Word) ht_table[1024];  /* [ht_nbuckts] Hash table. */
/*	ElfW(Word) ht_chains[1024];  * [ht_nchains] Hash chains. */
} ElfW(HashTable);
#endif /* !__elfw_hashtable_defined */

#ifndef __elfw_gnu_hashtable_defined
#define __elfw_gnu_hashtable_defined
typedef struct elfW(gnu_hashtable) {
	ElfW(Word) gh_nbuckets;      /* # of buckets. */
	ElfW(Word) gh_symoffset;     /* Offset of symbol indices. */
	ElfW(Word) gh_bloom_size;    /* # of elements in the bloom table. */
	ElfW(Word) gh_bloom_shift;   /* Shift for bloom masks */
	ElfW(Addr) gh_bloom[1024];   /* [gh_bloom_size] Bloom filter */
/*	ElfW(Word) gh_buckets[1024];  * [gh_nbuckets] Hash buckest. */
/*	ElfW(Word) gh_chains[];       * Hash chains */
} ElfW(GnuHashTable);
#endif /* !__elfw_gnu_hashtable_defined */

struct dlmodule_elf {
	/* Lazy relocations (JMPREL). */
	ElfW(Addr)               *de_pltgot;     /* [0..1][const] Pointed location of the module's `DT_PLTGOT' .dynamic entry. */
#if !ELF_ARCH_USESRELA
	ElfW(Rel)                *de_jmprel;     /* [0..DlModule_GetJmpCount(self)][const] Pointed jump-relocations to-be loaded lazily. */
#else /* !ELF_ARCH_USESRELA */
	union {
		ElfW(Rel)            *de_jmprel;     /* [0..DlModule_GetJmpCount(self)][const][valid_if(!RTLD_JMPRELA)] Pointed jump-relocations to-be loaded lazily. */
		ElfW(Rela)           *de_jmprela;    /* [0..DlModule_GetJmpaCount(self)][const][valid_if(RTLD_JMPRELA)] Pointed jump-relocations to-be loaded lazily. */
	};
#endif /* ELF_ARCH_USESRELA */
#if ELF_ARCH_LAZYINDX
	size_t                    de_jmpcount;   /* [const] Amount of jump-relocations. */
#define DlModule_GetJmpCount(self)  ((self)->de_jmpcount)
#if ELF_ARCH_USESRELA
#define DlModule_GetJmpaCount(self) ((self)->de_jmpcount)
#endif /* ELF_ARCH_USESRELA */
#else /* ELF_ARCH_LAZYINDX */
	size_t                    de_jmpsize;    /* [const] Size of the jump-relocations table (in bytes). */
#define DlModule_GetJmpCount(self)  ((self)->de_jmpsize / sizeof(ElfW(Rel)))
#if ELF_ARCH_USESRELA
#define DlModule_GetJmpaCount(self) ((self)->de_jmpsize / sizeof(ElfW(Rela)))
#endif /* ELF_ARCH_USESRELA */
#endif /* !ELF_ARCH_LAZYINDX */

	/* The module's .dynamic section, and derivatives (.dynsym + .dynstr). */
	size_t                    de_dyncnt;     /* [const] Number of dynamic definition headers. */
	ElfW(Sym) const          *de_dynsym_tab; /* [0..1][const] Vector of dynamic symbols defined by this module. */
	size_t                    de_dynsym_cnt; /* [lock(WRITE_ONCE)][const] # of symbols in `de_dynsym_tab' (or `0' if not calculated) */
	ElfW(GnuHashTable) const *de_gnuhashtab; /* [0..1][const] GNU Symbol hash table. */
	ElfW(HashTable) const    *de_hashtab;    /* [0..1][const] Symbol hash table. */
	char const               *de_dynstr;     /* [0..1][const] Dynamic string table. */
	char const               *de_runpath;    /* [0..1][const] Library path of this module. */

	/* ELF-specific Named data sections of the module (for use with `dllocksection(3D)'). */
	ElfW(Off)                 de_shoff;      /* File offset to section headers (or `0' if unknown). */
	ElfW(Half)                de_shstrndx;   /* Index of the section header names section (or `(ElfW(Half))-1' if unknown). */
	ElfW(Shdr)               *de_shdr;       /* [lock(WRITE_ONCE)][0..de_shnum][owned_if(!= empty_shdr)] Vector of section headers (or `NULL' if not loaded). */
	char                     *de_shstrtab;   /* [0..1][lock(WRITE_ONCE)][owned] Section headers name table (or `NULL' if not loaded). */
	unsigned char             de_abi;        /* [const] The value of `EI_OSABI' */
	unsigned char             de_abiver;     /* [const] The value of `EI_ABIVERSION' */

	/* Module program headers */
	ElfW(Half)                de_shnum;      /* [lock(WRITE_ONCE)] Number of section headers (or `(ElfW(Half))-1' if unknown).
	                                          * Usually the same as `dm_shnum', except when auxiliary section were loaded,  in
	                                          * which  case this is the number of  ELF sections, while `dm_shnum' includes aux
	                                          * sections, who's indices start after `de_shnum'. */
	ElfW(Half)                de_phnum;      /* [const] (Max) number of program headers. */
#ifdef DL_FIXED_PHDR_COUNT
	ElfW(Phdr)                de_phdr[DL_FIXED_PHDR_COUNT]; /* [const][de_phnum] Vector of program headers. */
#else /* DL_FIXED_PHDR_COUNT */
	COMPILER_FLEXIBLE_ARRAY(ElfW(Phdr), de_phdr); /* [const][de_phnum] Vector of program headers. */
#endif /* !DL_FIXED_PHDR_COUNT */
};


struct dlmodule_format;

/* The actual data-structure to which a pointer is returned by `dlopen(3D)' */
struct dlmodule {
	/* Fields from `struct link_map' (for binary compatibility... *ugh*) */
	uintptr_t                 dm_loadaddr;   /* [const] Load address of the module. */
	char                     *dm_filename;   /* [1..1][owned] Name of the executable binary file (absolute path). */
	ElfW(Dyn) const          *dm_dynhdr;     /* [0..dm_elf.de_dyncnt][const] Vector of dynamic ELF definition entries.
	                                          * WARNING: This field is ELF-only! Other  module formats must keep  this
	                                          *          field set to NULL (it only has to be ~here~ because of binary
	                                          *          compatibility with GNU's `struct link_map') */
	DLIST_ENTRY(dlmodule)     dm_modules;    /* [lock(dl_globals.dg_alllock)] Link entry in the chain of loaded modules. */
	/* --- End of `struct link_map' emulation --- */

	/* TLS variables (PT_TLS). */
	/* TODO: Get  rid of  `dm_tlsoff', and  make `dm_tlsinit'  not be lazy-init.
	 *       The current implementation is a result  of me for the longest  time
	 *       not realizing that ELF .tdata and .tbss are SUPPOSED TO BE PT_LOAD.
	 * This doesn't actually change anything about ABI compat, and as a  matter
	 * of fact: the current implementation is more lenient than it needs to be,
	 * and accepts actually  non-confirming programs (in  addition of  actually
	 * confirming  ones). But as  a result, it's also  more complicated than it
	 * needs to be. */
	ElfW(Off)                 dm_tlsoff;     /* [valid_if(dm_tlsfsize != 0)] File offset to the TLS template. */
	byte_t const             *dm_tlsinit;    /* [valid_if(dm_tlsfsize != 0)][0..dm_tlsfsize][lock(WRITE_ONCE)][owned] Non-BSS TLS template data. */
	size_t                    dm_tlsfsize;   /* [<= dm_tlsmsize] In-file size of this module's TLS template image. */
	size_t                    dm_tlsmsize;   /* [>= dm_tlsfsize] In-member size of this module's TLS template image (or 0 if no TLS is defined). */
	size_t                    dm_tlsalign;   /* [valid_if(dm_tlsmsize != 0)] Minimum alignment required for this module's TLS segment. */
	ptrdiff_t                 dm_tlsstoff;   /* [valid_if(!= 0)] Offset added to the TLS pointer to access this module's static TLS segment.
	                                          * NOTE:  Only modules loaded  by the initial application  are part of  the static TLS segment.
	                                          *    -> All other modules loaded thereafter have their TLS segments lazily loaded on first access. */
	/* WARNING: TLS Initializers/Finalizers are _NOT_ invoked for modules apart of the static TLS image! */
	void         (__DLFCN_CC *dm_tls_init)(void *arg, void *base, void *tls_segment); /* [valid_if(!dm_tlsstoff)][0..1] Optional callback for a TLS initializer. */
	void         (__DLFCN_CC *dm_tls_fini)(void *arg, void *base, void *tls_segment); /* [valid_if(!dm_tlsstoff)][0..1] Optional callback for a TLS finalizer. */
	void                     *dm_tls_arg;    /* [?..?][const] Argument passed to `dm_tls_init' / `dm_tls_fini' */

	/* All  of  the above  was  just so  that  `dltlsalloc(3D)' doesn't
	 * have to allocate the full DlModule structure. The rest following
	 * below is what should be considered the actual module  structure. */
	__WEAK refcnt_t           dm_refcnt;     /* Reference counter. */
	__WEAK refcnt_t           dm_weakrefcnt; /* Weak reference counter. */

	/* Module global binding. */
	TAILQ_ENTRY(__WEAK dlmodule) dm_globals; /* [lock(dl_globals.dg_globallock)][valid_if(dm_flags & RTLD_GLOBAL)]
	                                          * Link entry in the chain of global modules. */

	/* Module identification / data accessor. */
	fd_t                      dm_file;       /* [0..1][lock(WRITE_ONCE)] Readable handle towards the module's file (or -1 if unset). */
	uint32_t                  dm_flags;      /* Module flags (Set of `RTLD_*'). */

	/* Module load location. */
	uintptr_t                 dm_loadstart;  /* [const] Lowest address mapped by this module (already adjusted for `dm_loadaddr'). */
	uintptr_t                 dm_loadend;    /* [const] Greatest address mapped by this module (already adjusted for `dm_loadaddr'). */

	struct dlmodule_finalizers *dm_finalize; /* [0..1][lock(WRITE_ONCE)][owned] Lazily allocated vector of dynamic finalizer callbacks (for `__cxa_atexit()') */

	/* Module dependencies (DT_NEEDED). */
	size_t                    dm_depcnt;     /* [const] Number of dynamic definition headers. */
	__REF_IF(!(->de_flags & RTLD_NODELETE))
	    DlModule            **dm_depvec;     /* [1..1][const][0..dm_depcnt][owned][const] Vector of dependencies of this module. */

	/* Named data sections of the module (for use with `dllocksection(3D)'). */
	struct atomic_rwlock      dm_sections_lock;     /* Lock for `dm_sections' */
	DlSection               **dm_sections;          /* [0..1][weak][0..dm_shnum][owned][lock(dm_sections_lock)] Vector of locked sections. */
	__REF DlSection          *dm_sections_dangling; /* [0..1][lock(dm_sections_lock)] Chain of dangling sections. */
	size_t                    dm_shnum;             /* [lock(dm_sections_lock)] Number of section. */

	/* [0..1] Module operations V-table (or `NULL' for ELF modules)
	 *        Used by libdl extensions for other formats. */
	struct dlmodule_format   *dm_ops;

#ifdef __BUILDING_LIBDL
	struct dlmodule_elf       dm_elf; /* ELF-specific module data. */
#else /* __BUILDING_LIBDL */
	STRUCT_DLMODULE_EXT       DLMODULE_EXT; /* non-ELF-specific module data. */
#endif /* !__BUILDING_LIBDL */
};


/* Helper macros for `struct dlmodule::dm_sections_lock' */
#define DlModule_SectionsMustReap(self)   0
#define DlModule_SectionsReap(self)       (void)0
#define _DlModule_SectionsReap(self)      (void)0
#define DlModule_SectionsWrite(self)      atomic_rwlock_write(&(self)->dm_sections_lock)
#define DlModule_SectionsTryWrite(self)   atomic_rwlock_trywrite(&(self)->dm_sections_lock)
#define DlModule_SectionsEndWrite(self)   (atomic_rwlock_endwrite(&(self)->dm_sections_lock), DlModule_SectionsReap(self))
#define _DlModule_SectionsEndWrite(self)  atomic_rwlock_endwrite(&(self)->dm_sections_lock)
#define DlModule_SectionsRead(self)       atomic_rwlock_read(&(self)->dm_sections_lock)
#define DlModule_SectionsTryread(self)    atomic_rwlock_tryread(&(self)->dm_sections_lock)
#define _DlModule_SectionsEndRead(self)   atomic_rwlock_endread(&(self)->dm_sections_lock)
#define DlModule_SectionsEndRead(self)    (void)(atomic_rwlock_endread(&(self)->dm_sections_lock) && (DlModule_SectionsReap(self), 0))
#define _DlModule_SectionsEnd(self)       atomic_rwlock_end(&(self)->dm_sections_lock)
#define DlModule_SectionsEnd(self)        (void)(atomic_rwlock_end(&(self)->dm_sections_lock) && (DlModule_SectionsReap(self), 0))
#define DlModule_SectionsUpgrade(self)    atomic_rwlock_upgrade(&(self)->dm_sections_lock)
#define DlModule_SectionsTryUpgrade(self) atomic_rwlock_tryupgrade(&(self)->dm_sections_lock)
#define DlModule_SectionsDowngrade(self)  atomic_rwlock_downgrade(&(self)->dm_sections_lock)
#define DlModule_SectionsReading(self)    atomic_rwlock_reading(&(self)->dm_sections_lock)
#define DlModule_SectionsWriting(self)    atomic_rwlock_writing(&(self)->dm_sections_lock)
#define DlModule_SectionsCanRead(self)    atomic_rwlock_canread(&(self)->dm_sections_lock)
#define DlModule_SectionsCanWrite(self)   atomic_rwlock_canwrite(&(self)->dm_sections_lock)
#define DlModule_SectionsWaitRead(self)   atomic_rwlock_waitread(&(self)->dm_sections_lock)
#define DlModule_SectionsWaitWrite(self)  atomic_rwlock_waitwrite(&(self)->dm_sections_lock)


#ifdef __BUILDING_LIBDL
INTDEF NONNULL((1)) void LIBDL_CC DlModule_Destroy(__USER DlModule *self) __THROWS(E_SEGFAULT, ...);
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDL_CC DlModule_Free)(__USER DlModule *self) __THROWS(E_SEGFAULT);
#else /* __BUILDING_LIBDL */
#define DlModule_Destroy(self) (DL_API_SYMBOL(DlModule_Destroy)(self))
#define DlModule_Free(self)    (DL_API_SYMBOL(DlModule_Free)(self))
#endif /* !__BUILDING_LIBDL */

/* Make sure to define the DlModule decref() function such that it can throw exceptions.
 * This  is required  since `DlModule_Destroy()'  invokes module  finalizers which might
 * throw exceptions. (Whether or not they should do that is another story, though) */
#undef __REFCNT_NOTHROW
#define __REFCNT_NOTHROW /* nothing */
__DEFINE_REFCNT_FUNCTIONS(DlModule, dm_refcnt, DlModule_Destroy)
#undef __REFCNT_NOTHROW
#ifdef __KERNEL__
#define __REFCNT_NOTHROW __NOTHROW
#else /* __KERNEL__ */
#define __REFCNT_NOTHROW __NOTHROW_NCX
#endif /* !__KERNEL__ */

__DEFINE_WEAKREFCNT_FUNCTIONS(DlModule, dm_weakrefcnt, DlModule_Free)


#ifndef __dlmodule_tailq_defined
#define __dlmodule_tailq_defined
TAILQ_HEAD(dlmodule_tailq, dlmodule);
#endif /* !__dlmodule_tailq_defined */

#ifndef __dlmodule_dlist_defined
#define __dlmodule_dlist_defined
DLIST_HEAD(dlmodule_dlist, dlmodule);
#endif /* !__dlmodule_dlist_defined */

#ifndef __dltls_segment_list_defined
#define __dltls_segment_list_defined
struct dltls_segment;
LIST_HEAD(dltls_segment_list, dltls_segment);
#endif /* !__dltls_segment_list_defined */

/* Libdl global data (defined here because shared with DL extension drivers) */
struct dlglobals {
	struct process_peb       *dg_peb;              /* [1..1][const] Process environment block (The `__peb' symbol resolves to the address of this struct member) */
	char                     *dg_libpath;          /* [1..1][const] The library path set when the program was started (initenv:$LD_LIBRARY_PATH) */
	struct dlmodule_tailq     dg_globallist;       /* [1..N][lock(dg_globallock)] List of RTLD_GLOBAL modules (first element is main program). */
	struct atomic_rwlock      dg_globallock;       /* Lock for `dg_globallist' */
	struct dlmodule_dlist     dg_alllist;          /* [1..N][lock(dg_alllock)] List of all loaded modules. */
	struct atomic_rwlock      dg_alllock;          /* Lock for `dg_alllist' */
	struct dltls_segment_list dg_tls_segment_list; /* [0..n][lock(dg_tls_segment_lock)] List of all allocated static-tls segments (usually 1 for each thread)
	                                                * The last element in  this list is assumed  to have once  been allocated for the  main thread. Iow:  all
	                                                * additional threads must insert their  segments at the front! (only  empty before TLS was allocated  for
	                                                * the main thread). */
	struct atomic_rwlock      dg_tls_segment_lock; /* Lock for `dg_tls_segment_list' */
	/* TODO: Remove the following 2 and put them into `struct dltls_segment' */
	char                     *dg_errmsg;           /* [0..1] The current DL error message */
	char                      dg_errbuf[128];      /* Default buffer area for error messages. */
};

/* Return a pointer to the `struct dlmodule' for the main application. */
#define dlglobals_mainapp(self) TAILQ_FIRST(&(self)->dg_globallist)

/* Add/Remove elements for the RTLD_GLOBAL/all module lists. */
#define dlglobals_global_add(self, mod) TAILQ_INSERT_TAIL(&(self)->dg_globallist, mod, dm_globals)
#define dlglobals_global_del(self, mod) TAILQ_REMOVE(&(self)->dg_globallist, mod, dm_globals)
#define dlglobals_all_add(self, mod)    DLIST_INSERT_HEAD(&(self)->dg_alllist, mod, dm_modules)
#define dlglobals_all_del(self, mod)    DLIST_REMOVE(&(self)->dg_alllist, mod, dm_modules)

/* Helper macros for `struct dlglobals::dg_globallock' */
#define dlglobals_global_mustreap(self)   0
#define dlglobals_global_reap(self)       (void)0
#define _dlglobals_global_reap(self)      (void)0
#define dlglobals_global_write(self)      atomic_rwlock_write(&(self)->dg_globallock)
#define dlglobals_global_trywrite(self)   atomic_rwlock_trywrite(&(self)->dg_globallock)
#define dlglobals_global_endwrite(self)   (atomic_rwlock_endwrite(&(self)->dg_globallock), dlglobals_global_reap(self))
#define _dlglobals_global_endwrite(self)  atomic_rwlock_endwrite(&(self)->dg_globallock)
#define dlglobals_global_read(self)       atomic_rwlock_read(&(self)->dg_globallock)
#define dlglobals_global_tryread(self)    atomic_rwlock_tryread(&(self)->dg_globallock)
#define _dlglobals_global_endread(self)   atomic_rwlock_endread(&(self)->dg_globallock)
#define dlglobals_global_endread(self)    (void)(atomic_rwlock_endread(&(self)->dg_globallock) && (dlglobals_global_reap(self), 0))
#define _dlglobals_global_end(self)       atomic_rwlock_end(&(self)->dg_globallock)
#define dlglobals_global_end(self)        (void)(atomic_rwlock_end(&(self)->dg_globallock) && (dlglobals_global_reap(self), 0))
#define dlglobals_global_upgrade(self)    atomic_rwlock_upgrade(&(self)->dg_globallock)
#define dlglobals_global_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->dg_globallock)
#define dlglobals_global_downgrade(self)  atomic_rwlock_downgrade(&(self)->dg_globallock)
#define dlglobals_global_reading(self)    atomic_rwlock_reading(&(self)->dg_globallock)
#define dlglobals_global_writing(self)    atomic_rwlock_writing(&(self)->dg_globallock)
#define dlglobals_global_canread(self)    atomic_rwlock_canread(&(self)->dg_globallock)
#define dlglobals_global_canwrite(self)   atomic_rwlock_canwrite(&(self)->dg_globallock)
#define dlglobals_global_waitread(self)   atomic_rwlock_waitread(&(self)->dg_globallock)
#define dlglobals_global_waitwrite(self)  atomic_rwlock_waitwrite(&(self)->dg_globallock)

/* Helper macros for `struct dlglobals::dg_alllock' */
#define dlglobals_all_mustreap(self)   0
#define dlglobals_all_reap(self)       (void)0
#define _dlglobals_all_reap(self)      (void)0
#define dlglobals_all_write(self)      atomic_rwlock_write(&(self)->dg_alllock)
#define dlglobals_all_trywrite(self)   atomic_rwlock_trywrite(&(self)->dg_alllock)
#define dlglobals_all_endwrite(self)   (atomic_rwlock_endwrite(&(self)->dg_alllock), dlglobals_all_reap(self))
#define _dlglobals_all_endwrite(self)  atomic_rwlock_endwrite(&(self)->dg_alllock)
#define dlglobals_all_read(self)       atomic_rwlock_read(&(self)->dg_alllock)
#define dlglobals_all_tryread(self)    atomic_rwlock_tryread(&(self)->dg_alllock)
#define _dlglobals_all_endread(self)   atomic_rwlock_endread(&(self)->dg_alllock)
#define dlglobals_all_endread(self)    (void)(atomic_rwlock_endread(&(self)->dg_alllock) && (dlglobals_all_reap(self), 0))
#define _dlglobals_all_end(self)       atomic_rwlock_end(&(self)->dg_alllock)
#define dlglobals_all_end(self)        (void)(atomic_rwlock_end(&(self)->dg_alllock) && (dlglobals_all_reap(self), 0))
#define dlglobals_all_upgrade(self)    atomic_rwlock_upgrade(&(self)->dg_alllock)
#define dlglobals_all_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->dg_alllock)
#define dlglobals_all_downgrade(self)  atomic_rwlock_downgrade(&(self)->dg_alllock)
#define dlglobals_all_reading(self)    atomic_rwlock_reading(&(self)->dg_alllock)
#define dlglobals_all_writing(self)    atomic_rwlock_writing(&(self)->dg_alllock)
#define dlglobals_all_canread(self)    atomic_rwlock_canread(&(self)->dg_alllock)
#define dlglobals_all_canwrite(self)   atomic_rwlock_canwrite(&(self)->dg_alllock)
#define dlglobals_all_waitread(self)   atomic_rwlock_waitread(&(self)->dg_alllock)
#define dlglobals_all_waitwrite(self)  atomic_rwlock_waitwrite(&(self)->dg_alllock)

/* Helper macros for `struct dlglobals::dg_tls_segment_lock' */
#define dlglobals_tls_segment_mustreap(self)   0
#define dlglobals_tls_segment_reap(self)       (void)0
#define _dlglobals_tls_segment_reap(self)      (void)0
#define dlglobals_tls_segment_write(self)      atomic_rwlock_write(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_trywrite(self)   atomic_rwlock_trywrite(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_endwrite(self)   (atomic_rwlock_endwrite(&(self)->dg_tls_segment_lock), dlglobals_tls_segment_reap(self))
#define _dlglobals_tls_segment_endwrite(self)  atomic_rwlock_endwrite(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_read(self)       atomic_rwlock_read(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_tryread(self)    atomic_rwlock_tryread(&(self)->dg_tls_segment_lock)
#define _dlglobals_tls_segment_endread(self)   atomic_rwlock_endread(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_endread(self)    (void)(atomic_rwlock_endread(&(self)->dg_tls_segment_lock) && (dlglobals_tls_segment_reap(self), 0))
#define _dlglobals_tls_segment_end(self)       atomic_rwlock_end(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_end(self)        (void)(atomic_rwlock_end(&(self)->dg_tls_segment_lock) && (dlglobals_tls_segment_reap(self), 0))
#define dlglobals_tls_segment_upgrade(self)    atomic_rwlock_upgrade(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_tryupgrade(self) atomic_rwlock_tryupgrade(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_downgrade(self)  atomic_rwlock_downgrade(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_reading(self)    atomic_rwlock_reading(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_writing(self)    atomic_rwlock_writing(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_canread(self)    atomic_rwlock_canread(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_canwrite(self)   atomic_rwlock_canwrite(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_waitread(self)   atomic_rwlock_waitread(&(self)->dg_tls_segment_lock)
#define dlglobals_tls_segment_waitwrite(self)  atomic_rwlock_waitwrite(&(self)->dg_tls_segment_lock)

DECL_END
#endif /* __CC__ */

#endif /* !_LIBDL_MODULE_H */
