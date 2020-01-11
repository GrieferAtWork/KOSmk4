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
#ifndef _LIBDL_MODULE_H
#define _LIBDL_MODULE_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <hybrid/__atomic.h>
#include <hybrid/typecore.h>

#include <kos/kernel/types.h>
#include <kos/types.h>

#ifndef __BUILDING_LIBDL
#ifndef DL_EXTENSION_FORMAT
#error "Must `struct dlmodule_format my_format; #define DL_EXTENSION_FORMAT my_format' before #including this file"
#endif /* !DL_EXTENSION_FORMAT */
#define DL_API_SYMBOL(name) DL_EXTENSION_FORMAT.df_core->name
#else /* !__BUILDING_LIBDL */
#define DL_API_SYMBOL(name) name
#endif /* __BUILDING_LIBDL */

DECL_BEGIN

#ifdef __CC__

#ifndef __DlSection_defined
#define __DlSection_defined 1
struct dlsection;
typedef struct dlsection DlSection;
#endif /* !__DlSection_defined */

#ifndef __DlModule_defined
#define __DlModule_defined 1
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
	WEAK refcnt_t        ds_refcnt;      /* Reference counter. */
	struct atomic_rwlock ds_module_lock; /* Lock for `ds_module' */
	REF DlModule        *ds_module;      /* [0..1][ref_if(!(ds_flags & DLSECTION_FLAG_OWNED))]
	                                      * Pointer to the module (or NULL if section data is owned, and the module was destroyed) */
	REF DlSection       *ds_dangling;    /* [0..1][lock(ds_module->dm_sections_lock))] Chain of dangling sections.
	                                      * NOTE: Set to `(REF DlSection *)-1' if the section isn't dangling. */
	uint16_t             ds_flags;       /* [const] Section flags (Set of `ELF_DLSECTION_FLAG_*') */
	uint16_t             ds_index;       /* [const] Index of this section. */
};

#ifdef __INTELLISENSE__
INTDEF NONNULL((1)) void LIBDL_CC DlSection_Incref(DlSection *__restrict self);
INTDEF NONNULL((1)) void LIBDL_CC DlSection_Decref(DlSection *__restrict self);
#else /* __INTELLISENSE__ */
#define DlSection_Incref(self) \
	(__hybrid_atomic_fetchinc((self)->ds_refcnt, __ATOMIC_SEQ_CST))
#define DlSection_Decref(self)                                        \
	(__hybrid_atomic_decfetch((self)->ds_refcnt, __ATOMIC_SEQ_CST) || \
	 (DL_API_SYMBOL(DlSection_Destroy)(self), 0))
#endif /* !__INTELLISENSE__ */

FORCELOCAL NONNULL((1)) bool LIBDL_CC
DlSection_TryIncref(DlSection *__restrict self) {
	refcnt_t refcnt;
	do {
		refcnt = __hybrid_atomic_load(self->ds_refcnt, __ATOMIC_ACQUIRE);
		if (!refcnt)
			return false;
	} while (!__hybrid_atomic_cmpxch_weak(self->ds_refcnt, refcnt, refcnt + 1,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	return true;
}

#ifdef __BUILDING_LIBDL
INTDEF NONNULL((1)) void LIBDL_CC
DlSection_Destroy(DlSection *__restrict self);
#endif /* __BUILDING_LIBDL */

struct dlmodule_finalizer {
	void (__LIBCCALL *df_func)(void *arg); /* [1..1] Finalizer callback. */
	void             *df_arg;              /* [?..?] Callback argument. */
};

struct dlmodule_finalizers {
	struct atomic_rwlock       df_lock; /* Lock for finalizer callbacks (left dangling in read-mode for finalizer invocation) */
	size_t                     df_size; /* [lock(df_lock)] # of registered callbacks. */
	struct dlmodule_finalizer *df_list; /* [lock(df_lock)][1..df_size][owned] Vector of callbacks. */
};

typedef struct elfW(hashtable) {
	ElfW(Word) ht_nbuckts;      /* Total number of buckets. */
	ElfW(Word) ht_nchains;      /* Total number of symbols. */
	ElfW(Word) ht_table[1024];  /* [ht_nbuckts] Hash table. */
//	ElfW(Word) ht_chains[1024]; /* [ht_nchains] Hash chains. */
} ElfW(HashTable);

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
	ElfW(Dyn)                *de_dynhdr;     /* [0..de_dyncnt][const] Vector of dynamic definition entries. */
	ElfW(Sym)                *de_dynsym_tab; /* [0..1][const] Vector of dynamic symbols defined by this module.
	                                          * HINT: If also non-NULL, the number of symbols is `de_hashtab->ht_nchains' */
	ElfW(HashTable)          *de_hashtab;    /* [0..1][const] Symbol hash table. */
	char                     *de_dynstr;     /* [0..1][const] Dynamic string table. */
	char                     *de_runpath;    /* [0..1][const] Library path of this module. */

	/* ELF-specific Named data sections of the module (for use with `dllocksection()'). */
	ElfW(Off)                 de_shoff;      /* File offset to section headers (or `0' if unknown). */
	ElfW(Half)                de_shstrndx;   /* Index of the section header names section (or `(ElfW(Half))-1' if unknown). */
	ElfW(Shdr)               *de_shdr;       /* [lock(WRITE_ONCE)][0..:dm_shnum][owned_if(!= empty_shdr)] Vector of section headers (or `NULL' if not loaded). */
	char                     *de_shstrtab;   /* [0..1][lock(WRITE_ONCE)][owned] Section headers name table (or `NULL' if not loaded). */
	unsigned char             de_abi;        /* [const] The value of `EI_OSABI' */
	unsigned char             de_abiver;     /* [const] The value of `EI_ABIVERSION' */

	/* Module program headers */
	ElfW(Half)                de_phnum;      /* [const] (Max) number of program headers. */
#ifdef DL_FIXED_PHDR_COUNT
	ElfW(Phdr)                de_phdr[DL_FIXED_PHDR_COUNT]; /* [const][de_phnum] Vector of program headers. */
#else /* DL_FIXED_PHDR_COUNT */
	COMPILER_FLEXIBLE_ARRAY(ElfW(Phdr), de_phdr); /* [const][de_phnum] Vector of program headers. */
#endif /* !DL_FIXED_PHDR_COUNT */
};


struct dlmodule_format;

/* The actual data-structure to which a pointer is returned by `dlopen()' */
struct dlmodule {
	/* TLS variables (PT_TLS). */
	ElfW(Off)                 dm_tlsoff;     /* [valid_if(dm_tlsfsize != 0)] File offset to the TLS template. */
	byte_t const             *dm_tlsinit;    /* [valid_if(dm_tlsfsize != 0)][0..dm_tlsfsize][lock(WRITE_ONCE)][owned] Non-BSS TLS template data. */
	size_t                    dm_tlsfsize;   /* [<= dm_tlsmsize] In-file size of this module's TLS template image. */
	size_t                    dm_tlsmsize;   /* [>= dm_tlsfsize] In-member size of this module's TLS template image (or 0 if no TLS is defined). */
	size_t                    dm_tlsalign;   /* [valid_if(dm_tlsmsize != 0)] Minimum alignment required for this module's TLS segment. */
	ptrdiff_t                 dm_tlsstoff;   /* [valid_if(!= 0)] Offset added to the TLS pointer to access this module's static TLS segment.
	                                          * NOTE: Only modules loaded by the initial application are part of the static TLS segment.
	                                          *    -> All other modules loaded thereafter have their TLS segments lazily loaded on first access. */
	/* WARNING: TLS Initializers/Finalizers are _NOT_ invoked for modules apart of the static TLS image! */
	void                    (*dm_tls_init)(void *arg, void *base); /* [valid_if(!dm_tlsstoff)][0..1] Optional callback for a TLS initializer. */
	void                    (*dm_tls_fini)(void *arg, void *base); /* [valid_if(!dm_tlsstoff)][0..1] Optional callback for a TLS finalizer. */
	void                     *dm_tls_arg;    /* [?..?][const] Argument passed to `dm_tls_init' / `dm_tls_fini' */

	/* All of the above was just so that `libdl_dltlsalloc()' doesn't
	 * have to allocate the full DlModule structure. The rest following
	 * below is what should be considered the actual module structure. */
	WEAK refcnt_t             dm_refcnt;     /* Reference counter. */

	/* Module global binding. */
	LLIST_NODE(WEAK DlModule) dm_modules;    /* [lock(DlModule_AllLock)] Link entry in the chain of loaded modules. */
	LLIST_NODE(WEAK DlModule) dm_globals;    /* [lock(DlModule_GlobalLock)][valid_if(dm_flags & RTLD_GLOBAL)]
	                                          * Link entry in the chain of global modules. */

	/* Module identification / data accessor. */
	char                     *dm_filename;   /* [1..1][owned] Name of the executable binary file (absolute path). */
	fd_t                      dm_file;       /* [0..1][lock(WRITE_ONCE)] Readable handle towards the module's file (or -1 if unset). */
	uint32_t                  dm_flags;      /* Module flags (Set of `RTLD_*'). */

	/* Module load location. */
	uintptr_t                 dm_loadaddr;   /* [const] Load address of the module. */
	uintptr_t                 dm_loadstart;  /* [const] Lowest address mapped by this module (already adjusted for `dm_loadaddr'). */
	uintptr_t                 dm_loadend;    /* [const] Greatest address mapped by this module (already adjusted for `dm_loadaddr'). */

	struct dlmodule_finalizers *dm_finalize; /* [0..1][lock(WRITE_ONCE)][owned] Lazily allocated vector of dynamic finalizer callbacks (for `__cxa_atexit()') */

	/* Module dependencies (DT_NEEDED). */
	size_t                    dm_depcnt;     /* [const] Number of dynamic definition headers. */
	REF_IF(!(->de_flags & RTLD_NODELETE))
	    DlModule            **dm_depvec;     /* [1..1][const][0..dm_depcnt][owned][const] Vector of dependencies of this module. */

	/* Named data sections of the module (for use with `dllocksection()'). */
	struct atomic_rwlock      dm_sections_lock; /* Lock for `dm_sections' */
	DlSection               **dm_sections;   /* [0..1][weak][0..dm_shnum][owned][lock(dm_sections_lock)] Vector of locked sections. */
	REF DlSection            *dm_sections_dangling; /* [0..1][lock(dm_sections_lock))] Chain of dangling sections. */
	size_t                    dm_shnum;      /* (Max) number of section headers (or `(size_t)-1' if unknown). */

	/* [0..1] Module operations V-table (or `NULL' for ELF modules)
	 *        Used by libdl extensions for other formats. */
	struct dlmodule_format      *dm_ops;

#ifdef __BUILDING_LIBDL
	struct dlmodule_elf       dm_elf; /* ELF-specific module data. */
#else /* __BUILDING_LIBDL */
	STRUCT_DLMODULE_EXT       DLMODULE_EXT; /* non-ELF-specific module data. */
#endif /* !__BUILDING_LIBDL */
};


/* Dl Module reference control. */
#ifdef __INTELLISENSE__
INTDEF NONNULL((1)) void LIBDL_CC DlModule_Incref(DlModule *__restrict self);
INTDEF NONNULL((1)) bool LIBDL_CC DlModule_Decref(DlModule *__restrict self);
INTDEF NONNULL((1)) bool LIBDL_CC DlModule_DecrefNoKill(DlModule *__restrict self);
#else /* __INTELLISENSE__ */
#define DlModule_Incref(self)       (__hybrid_atomic_fetchinc((self)->dm_refcnt, __ATOMIC_SEQ_CST))
#define DlModule_Decref(self)       (__hybrid_atomic_decfetch((self)->dm_refcnt, __ATOMIC_SEQ_CST) || (DlModule_Destroy(self),0))
#define DlModule_DecrefNoKill(self) (__hybrid_atomic_fetchdec((self)->dm_refcnt, __ATOMIC_SEQ_CST))
#endif /* !__INTELLISENSE__ */

FORCELOCAL NONNULL((1)) bool LIBDL_CC
DlModule_TryIncref(DlModule *__restrict self) {
	refcnt_t refcnt;
	do {
		refcnt = __hybrid_atomic_load(self->dm_refcnt, __ATOMIC_ACQUIRE);
		if (!refcnt)
			return false;
	} while (!__hybrid_atomic_cmpxch_weak(self->dm_refcnt, refcnt, refcnt + 1,
	                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));
	return true;
}

#ifdef __BUILDING_LIBDL
INTDEF NONNULL((1)) void LIBDL_CC DlModule_Destroy(DlModule *__restrict self);
#endif /* __BUILDING_LIBDL */


#endif /* __CC__ */

DECL_END

#endif /* !_LIBDL_MODULE_H */
