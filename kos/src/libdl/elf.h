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
#ifndef GUARD_LIBDL_ELF_H
#define GUARD_LIBDL_ELF_H 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

/* Keep this one the first */
#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-owner-rwlock.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/except.h>
#include <kos/exec/elf-rel.h> /* ELF_ARCH_*_R_* */
#include <kos/exec/elf.h>
#include <kos/kernel/types.h>
#include <kos/thread.h>
#include <kos/types.h>

#include <assert.h>
#include <dlfcn.h>
#include <elf.h>
#include <stdarg.h>
#include <stdint.h>

#undef TRY
#undef EXCEPT
#undef RETHROW
#define TRY         try
#define EXCEPT      catch(...)
#define RETHROW()   throw

DECL_BEGIN

#ifndef ELF_VERIFY_MODULE_HANDLE
#define ELF_VERIFY_MODULE_HANDLE(p) \
	((p) && ((uintptr_t)(p) & (sizeof(void *) - 1)) == 0)
#endif /* !ELF_VERIFY_MODULE_HANDLE */

#ifndef ELF_VERIFY_SECTION_HANDLE
#define ELF_VERIFY_SECTION_HANDLE(p) \
	((p) && ((uintptr_t)(p) & (sizeof(void *) - 1)) == 0)
#endif /* !ELF_VERIFY_SECTION_HANDLE */

#define DECLARE_INTERN_OVERRIDE(name)        \
	__asm__(".type " #name ", @function\n\t" \
	        ".global " #name "\n\t"          \
	        ".hidden " #name);
BUILTIN_GLOBALS_ENUMERATE(DECLARE_INTERN_OVERRIDE)
#undef DECLARE_INTERN_OVERRIDE


/* Define our own private variants of a couple of functions
 * that aren't already automatically substituted in headers. */
INTDEF NONNULL((2)) ssize_t CC
preadall(fd_t fd, void *buf, size_t bufsize, ElfW(Off) offset);


#undef RTLD_LOADING
/* Flag set while a module is still being loaded.
 * -> Used to detect cyclic dependencies. */
#define RTLD_LOADING    UINT32_C(0x40000000)

#if ELF_ARCH_USESRELA
/* jmp relocation have addends. */
#define RTLD_JMPRELA    UINT32_C(0x20000000)
#endif /* ELF_ARCH_USESRELA */

typedef struct elf_dlsection DlSection;
typedef struct elf_dlmodule DlModule;

typedef struct {
	ElfW(Word) ht_nbuckts;      /* Total number of buckets. */
	ElfW(Word) ht_nchains;      /* Total number of symbols. */
	ElfW(Word) ht_table[1024];  /* [ht_nbuckts] Hash table. */
//	ElfW(Word) ht_chains[1024]; /* [ht_nchains] Hash chains. */
} ElfW(HashTable);

#define ELF_DLSECTION_FLAG_NORMAL 0x0000 /* Normal flags */
#define ELF_DLSECTION_FLAG_OWNED  0x0001 /* Section data is owned by the section descriptor. */
struct elf_dlsection {
	void                *ds_data;        /* [0..ds_size][lock(WRITE_ONCE)]
	                                      * [owned_if(ds_flags & ELF_DLSECTION_FLAG_OWNED)]
	                                      * Memory mapping for the section's contents.
	                                      * NOTE: Set to `(void *)-1' when section data hasn't been loaded, yet. */
	size_t               ds_size;        /* [const] Size of the section (in bytes) */
	size_t               ds_entsize;     /* [const] Section entry size (or 0 if unknown) */
	uintptr_t            ds_link;        /* [const] Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t            ds_info;        /* [const] Index of another section that is linked by this one (or `0' if unused) */
	WEAK refcnt_t        ds_refcnt;      /* Reference counter. */
	struct atomic_rwlock ds_module_lock; /* Lock for `ds_module' */
	REF DlModule        *ds_module;      /* [0..1][ref_if(!(ds_flags & ELF_DLSECTION_FLAG_OWNED))]
	                                      * Pointer to the module (or NULL if section data is owned, and the module was destroyed) */
#ifndef CONFIG_NO_DANGLING_DL_SECTIONS
	REF DlSection       *ds_dangling;    /* [0..1][lock(ds_module->dm_sections_lock))] Chain of dangling sections.
	                                      * NOTE: Set to `(REF DlSection *)-1' if the section isn't dangling. */
#endif /* !CONFIG_NO_DANGLING_DL_SECTIONS */
	uint16_t             ds_flags;       /* [const] Section flags (Set of `ELF_DLSECTION_FLAG_*') */
	uint16_t             ds_index;       /* [const] Index of this section. */
};

#ifdef __INTELLISENSE__
INTDEF NONNULL((1)) void CC DlSection_Incref(DlSection *__restrict self);
INTDEF NONNULL((1)) void CC DlSection_Decref(DlSection *__restrict self);
#else /* __INTELLISENSE__ */
#define DlSection_Incref(self) (ATOMIC_FETCHINC((self)->ds_refcnt))
#define DlSection_Decref(self) (ATOMIC_DECFETCH((self)->ds_refcnt) || (DlSection_Destroy(self), 0))
#endif /* !__INTELLISENSE__ */

FORCELOCAL NONNULL((1)) bool CC
DlSection_TryIncref(DlSection *__restrict self) {
	refcnt_t refcnt;
	do {
		refcnt = ATOMIC_READ(self->ds_refcnt);
		if (!refcnt)
			return false;
	} while (!ATOMIC_CMPXCH_WEAK(self->ds_refcnt, refcnt, refcnt + 1));
	return true;
}

INTDEF NONNULL((1)) void CC
DlSection_Destroy(DlSection *__restrict self);


/* The actual data-structure to which a pointer is returned by `dlopen()' */
struct elf_dlmodule {
	/* TLS variables (PT_TLS). */
	ElfW(Off)                 dm_tlsoff;     /* [valid_if(dm_tlsfsize != 0)] File offset to the TLS template. */
	byte_t const             *dm_tlsinit;    /* [valid_if(dm_tlsfsize != 0)][0..dm_tlsfsize][lock(WRITE_ONCE)] Non-BSS TLS template data. */
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

	/* Lazy relocations (JMPREL). */
	ElfW(Addr)               *dm_pltgot;     /* [0..1][const] Pointed location of the module's `DT_PLTGOT' .dynamic entry. */
#if !ELF_ARCH_USESRELA
	ElfW(Rel)                *dm_jmprel;     /* [0..DlModule_GetJmpCount(self)][const] Pointed jump-relocations to-be loaded lazily. */
#else /* !ELF_ARCH_USESRELA */
	union {
		ElfW(Rel)            *dm_jmprel;     /* [0..DlModule_GetJmpCount(self)][const][valid_if(!RTLD_JMPRELA)] Pointed jump-relocations to-be loaded lazily. */
		ElfW(Rela)           *dm_jmprela;    /* [0..DlModule_GetJmpaCount(self)][const][valid_if(RTLD_JMPRELA)] Pointed jump-relocations to-be loaded lazily. */
	};
#endif /* ELF_ARCH_USESRELA */
#if ELF_ARCH_LAZYINDX
	size_t                    dm_jmpcount;   /* [const] Amount of jump-relocations. */
#define DlModule_GetJmpCount(self)  ((self)->dm_jmpcount)
#if ELF_ARCH_USESRELA
#define DlModule_GetJmpaCount(self) ((self)->dm_jmpcount)
#endif /* ELF_ARCH_USESRELA */
#else /* ELF_ARCH_LAZYINDX */
	size_t                    dm_jmpsize;    /* [const] Size of the jump-relocations table (in bytes). */
#define DlModule_GetJmpCount(self)  ((self)->dm_jmpsize / sizeof(ElfW(Rel)))
#if ELF_ARCH_USESRELA
#define DlModule_GetJmpaCount(self) ((self)->dm_jmpsize / sizeof(ElfW(Rela)))
#endif /* ELF_ARCH_USESRELA */
#endif /* !ELF_ARCH_LAZYINDX */

	/* Module dependencies (DT_NEEDED). */
	size_t                    dm_depcnt;     /* [const] Number of dynamic definition headers. */
	REF_IF(!(->dm_flags & RTLD_NODELETE))
	    DlModule            **dm_depvec;     /* [1..1][const][0..dm_depcnt][owned][const] Vector of dependencies of this module. */

	/* The module's .dynamic section, and derivatives (.dynsym + .dynstr). */
	size_t                    dm_dyncnt;     /* [const] Number of dynamic definition headers. */
	ElfW(Dyn)                *dm_dynhdr;     /* [0..dm_dyncnt][const] Vector of dynamic definition entries. */
	ElfW(Sym)                *dm_dynsym_tab; /* [0..1][const] Vector of dynamic symbols defined by this module.
	                                          * HINT: If also non-NULL, the number of symbols is `dm_hashtab->ht_nchains' */
	ElfW(HashTable)          *dm_hashtab;    /* [0..1][const] Symbol hash table. */
	char                     *dm_dynstr;     /* [0..1][const] Dynamic string table. */
	char                     *dm_runpath;    /* [0..1][const] Library path of this module. */

	/* Named data sections of the module (for use with `dllocksection()'). */
	ElfW(Off)                 dm_shoff;      /* File offset to section headers (or `0' if unknown). */
	ElfW(Half)                dm_shstrndx;   /* Index of the section header names section (or `(ElfW(Half))-1' if unknown). */
	ElfW(Half)                dm_shnum;      /* (Max) number of section headers (or `(ElfW(Half))-1' if unknown). */
	ElfW(Shdr)               *dm_shdr;       /* [lock(WRITE_ONCE)][0..dm_shnum][owned_if(!= empty_shdr)] Vector of section headers (or `NULL' if not loaded). */
	struct atomic_rwlock      dm_sections_lock; /* Lock for `dm_sections' */
	DlSection               **dm_sections;   /* [0..1][weak][0..dm_shnum][owned][lock(dm_sections_lock)] Vector of locked sections. */
#ifndef CONFIG_NO_DANGLING_DL_SECTIONS
	REF DlSection            *dm_sections_dangling; /* [0..1][lock(dm_sections_lock))] Chain of dangling sections. */
#endif /* !CONFIG_NO_DANGLING_DL_SECTIONS */
	char                     *dm_shstrtab;   /* [lock(WRITE_ONCE)][0..1][owned] Section headers name table (or `NULL' if not loaded). */
	unsigned char             dm_abi;        /* [const] The value of `EI_OSABI' */
	unsigned char             dm_abiver;     /* [const] The value of `EI_ABIVERSION' */

	/* Module program headers */
	ElfW(Half)                dm_phnum;      /* [const] (Max) number of program headers. */
	ElfW(Phdr)                dm_phdr[];     /* [const][dm_phnum] Vector of program headers. */
};

/* [1..1] List of global modules / pointer to the root binary. */
INTDEF LLIST(DlModule) DlModule_GlobalList;
INTDEF struct atomic_rwlock DlModule_GlobalLock;

/* [1..1] List of all loaded modules. */
INTDEF LLIST(DlModule) DlModule_AllList;
INTDEF struct atomic_rwlock DlModule_AllLock;

/* The module describing the RTLD library itself. */
INTDEF DlModule ld_rtld_module;

LOCAL NONNULL((1)) void CC
DlModule_AddToGlobals(DlModule *__restrict self) {
	DlModule **plist, *next;
	plist = &DlModule_GlobalList;
	while ((next = *plist) != NULL)
		plist = &next->dm_globals.ln_next;
	self->dm_globals.ln_pself = plist;
	self->dm_globals.ln_next  = NULL;
	*plist                    = self;
}

LOCAL NONNULL((1)) void CC
DlModule_RemoveFromGlobals(DlModule *__restrict self) {
	assert(self != &ld_rtld_module);
	*self->dm_globals.ln_pself = self->dm_globals.ln_next;
}

LOCAL NONNULL((1)) void CC
DlModule_AddToAll(DlModule *__restrict self) {
	DlModule **plist, *next;
	plist = &DlModule_AllList;
	while ((next = *plist) != NULL)
		plist = &next->dm_modules.ln_next;
	self->dm_modules.ln_pself = plist;
	self->dm_modules.ln_next  = NULL;
	*plist                    = self;
}

LOCAL NONNULL((1)) void CC
DlModule_RemoveFromAll(DlModule *__restrict self) {
	assert(self != &ld_rtld_module);
	*self->dm_modules.ln_pself = self->dm_modules.ln_next;
}


/* Lock used to ensure that only a single thread can ever load modules
 * at the same time (used to prevent potential race conditions arising
 * from the fact that various components must be accessed globally). */
INTDEF struct atomic_owner_rwlock DlModule_LoadLock;

/* [1..1][const] The library path set when the program was started */
INTDEF char *ld_library_path_env;

/* Dl Module reference control. */
#ifdef __INTELLISENSE__
INTDEF NONNULL((1)) void CC DlModule_Incref(DlModule *__restrict self);
INTDEF NONNULL((1)) bool CC DlModule_Decref(DlModule *__restrict self);
INTDEF NONNULL((1)) bool CC DlModule_DecrefNoKill(DlModule *__restrict self);
#else /* __INTELLISENSE__ */
#define DlModule_Incref(self)       (ATOMIC_FETCHINC((self)->dm_refcnt))
#define DlModule_Decref(self)       (ATOMIC_DECFETCH((self)->dm_refcnt) || (DlModule_Destroy(self),0))
#define DlModule_DecrefNoKill(self) (ATOMIC_FETCHDEC((self)->dm_refcnt))
#endif /* !__INTELLISENSE__ */

FORCELOCAL NONNULL((1)) bool CC
DlModule_TryIncref(DlModule *__restrict self) {
	refcnt_t refcnt;
	do {
		refcnt = ATOMIC_READ(self->dm_refcnt);
		if (!refcnt)
			return false;
	} while (!ATOMIC_CMPXCH_WEAK(self->dm_refcnt, refcnt, refcnt + 1));
	return true;
}

INTDEF NONNULL((1)) void CC
DlModule_Destroy(DlModule *__restrict self);

/* Open a DL Module.
 * @return: NULL: Failed to open the module. (no error is set if the file could not be found
 *                in a call to one of `DlModule_OpenFilename' or `DlModule_OpenFilenameInPath') */
INTDEF WUNUSED REF DlModule *LIBCCALL
DlModule_OpenFd(/*inherit(on_success)*/ fd_t fd, unsigned int mode);
INTDEF WUNUSED NONNULL((1)) REF DlModule *CC
DlModule_OpenFilename(char const *__restrict filename, unsigned int mode);
INTDEF WUNUSED NONNULL((1, 3)) REF DlModule *CC
DlModule_OpenFilenameInPath(char const *__restrict path, size_t pathlen,
                            char const *__restrict filename, size_t filenamelen,
                            unsigned int mode);
INTDEF WUNUSED NONNULL((1, 2)) REF DlModule *CC
DlModule_OpenFilenameInPathList(char const *__restrict path,
                                char const *__restrict filename,
                                unsigned int mode);
INTDEF WUNUSED NONNULL((1)) REF DlModule *CC
DlModule_OpenFilenameAndFd(/*inherit(on_success,HEAP)*/ char *__restrict filename,
                           /*inherit(on_success)*/ fd_t fd, unsigned int mode);
INTDEF WUNUSED NONNULL((1, 2)) REF DlModule *CC
DlModule_OpenLoadedProgramHeaders(/*inherit(on_success,HEAP)*/ char *__restrict filename,
                                  struct elfexec_info *__restrict info, uintptr_t loadaddr);

/* Try to find an already-loaded module. */
INTDEF WUNUSED NONNULL((1, 3)) REF DlModule *CC
DlModule_FindFilenameInPathFromAll(char const *__restrict path, size_t pathlen,
                                   char const *__restrict filename, size_t filenamelen);
INTDEF WUNUSED NONNULL((1)) REF DlModule *CC
DlModule_FindFilenameInPathListFromAll(char const *__restrict filename);

/* Apply relocations & execute library initialized within `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
INTDEF NONNULL((1)) int CC
DlModule_Initialize(DlModule *__restrict self, unsigned int flags);
#define DL_MODULE_INITIALIZE_FNORMAL   0x0000
#define DL_MODULE_INITIALIZE_FTEXTREL  0x0001 /* Text relocations exist. */
#define DL_MODULE_INITIALIZE_FBINDNOW  0x0002 /* Bind all symbols now. */

/* Apply relocations for `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
INTDEF WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocations(DlModule *__restrict self,
                          ElfW(Rel) *__restrict vector,
                          size_t count, unsigned int flags);
#if ELF_ARCH_USESRELA
INTDEF WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocationsWithAddend(DlModule *__restrict self,
                                    ElfW(Rela) *__restrict vector,
                                    size_t count, unsigned int flags);
#endif /* ELF_ARCH_USESRELA */

/* Run library initializers for `self' */
INTDEF NONNULL((1)) void CC
DlModule_RunInitializers(DlModule *__restrict self);

/* Verify that `ehdr' is valid */
INTDEF WUNUSED NONNULL((1, 2)) int CC
DlModule_VerifyEhdr(ElfW(Ehdr) const *__restrict ehdr,
                    char const *__restrict filename,
                    bool requires_ET_DYN);



/* Lazily allocate if necessary, and return the file descriptor for `self'
 * @return: -1: Error (s.a. elf_dlerror_message) */
INTDEF WUNUSED NONNULL((1)) fd_t CC
DlModule_GetFd(DlModule *__restrict self);

/* Lazily allocate if necessary, and return the vector of section headers for `self'
 * NOTE: On success, this function guaranties that the following fields have been initialized:
 *  - self->dm_shnum
 *  - self->dm_shoff
 *  - self->dm_shstrndx
 *  - self->dm_shdr
 * @return: NULL: Error (s.a. elf_dlerror_message) */
INTDEF WUNUSED NONNULL((1)) ElfW(Shdr) *CC
DlModule_GetShdrs(DlModule *__restrict self);

/* Lazily allocate if necessary, and return the section header string table for `self'
 * @return: NULL: Error (s.a. elf_dlerror_message) */
INTDEF WUNUSED NONNULL((1)) char *CC
DlModule_GetShstrtab(DlModule *__restrict self);

/* Return the section header associated with a given `name'
 * @return: NULL: Error (s.a. elf_dlerror_message) */
INTDEF WUNUSED NONNULL((1, 2)) ElfW(Shdr) *CC
DlModule_GetSection(DlModule *__restrict self,
                    char const *__restrict name);

struct dl_symbol {
	ElfW(Sym)  const *ds_sym;    /* [1..1] The actual symbol. */
	DlModule       *ds_mod;    /* [1..1] The associated module */
};

/* Same as the functions above, but only return symbols defined within the same module! */
INTDEF ElfW(Sym) const *CC
DlModule_GetLocalSymbol(DlModule *__restrict self,
                        char const *__restrict name,
                        uintptr_t *__restrict phash_elf,
                        uintptr_t *__restrict phash_gnu);
#define DLMODULE_GETLOCALSYMBOL_HASH_UNSET ((uintptr_t)-1)

/* Find the DL module mapping the specified file.
 * If no such module is loaded, `NULL' is returned instead.
 * @return: NULL: No such module exists (NOTE: No error was set in this case!) */
INTDEF REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_FindFromFilename(char const *__restrict filename);

/* Find the DL module containing a given static pointer.
 * @return: NULL: Error (s.a. `elf_dlerror_message') */
INTDEF WUNUSED DlModule *CC DlModule_FindFromStaticPointer(void const *static_pointer);


/* Functions made available to applications being loaded. */
INTDEF REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *LIBCCALL
libdl_dlfopen(/*inherit(on_success)*/ fd_t fd, unsigned int mode);
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *LIBCCALL
libdl_dlopen(char const *filename, int mode);
INTDEF NONNULL((1)) int LIBCCALL libdl_dlclose(REF DlModule *handle);
INTDEF NONNULL((1)) int LIBCCALL libdl_dlexceptaware(DlModule *handle);
INTDEF NONNULL((2)) void *LIBCCALL libdl_dlsym(DlModule *handle, char const *__restrict name);
INTDEF char *LIBCCALL libdl_dlerror(void);
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF))
DlModule *LIBCCALL libdl_dlgethandle(void const *static_pointer, unsigned int flags);
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF))
DlModule *LIBCCALL libdl_dlgetmodule(char const *name, unsigned int flags);
INTDEF NONNULL((2)) int LIBCCALL libdl_dladdr(void const *address, Dl_info *info);
INTDEF WUNUSED fd_t LIBCCALL libdl_dlmodulefd(DlModule *self);
INTDEF WUNUSED char const *LIBCCALL libdl_dlmodulename(DlModule *self);
INTDEF WUNUSED void *LIBCCALL libdl_dlmodulebase(DlModule *self);
INTDEF WUNUSED REF DlSection *LIBCCALL libdl_dllocksection(DlModule *self, char const *__restrict name, unsigned int flags);
INTDEF int LIBCCALL libdl_dlunlocksection(REF DlSection *sect);
INTDEF char const *LIBCCALL libdl_dlsectionname(DlSection *sect);
INTDEF size_t LIBCCALL libdl_dlsectionindex(DlSection *sect);
INTDEF DlModule *LIBCCALL libdl_dlsectionmodule(DlSection *sect, unsigned int flags);
INTDEF int LIBCCALL libdl_dlclearcaches(void);
INTDEF void *LIBCCALL libdl_dlauxinfo(DlModule *self, unsigned int type, void *buf, size_t *pauxvlen);
INTDEF void *LIBCCALL libdl____tls_get_addr(void);
INTDEF void *LIBCCALL libdl___tls_get_addr(void);

/* Allocate/Free a static TLS segment
 * These functions are called by by libc in order to safely create a new thread, such that
 * all current and future modules are able to store thread-local storage within that thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror()) */
INTDEF WUNUSED ATTR_MALLOC void *LIBCCALL libdl_dltlsallocseg(void);

/* Free a previously allocated static TLS segment (usually called by `pthread_exit()' and friends). */
INTDEF int LIBCCALL libdl_dltlsfreeseg(void *ptr);

/* Return a pointer to the base of the given module's
 * TLS segment, as seen form the calling thread.
 * In the case of dynamic TLS, allocate missing segments lazily,
 * logging a system error and exiting the calling application if
 * doing so fails. */
INTDEF WUNUSED ATTR_RETNONNULL void *ATTR_FASTCALL
libdl_dltlsbase(DlModule *__restrict self);

/* DL-based TLS memory management API.
 * These functions may be used to dynamically allocate TLS memory that works everywhere where
 * ATTR_THREAD-based TLS memory also works. - However using these functions, TLS memory can
 * be allocated dynamically at runtime (behaving the same as a call to dlopen() loading a
 * module containing a TLS segment would).
 * @param: NUM_BYTES:      The size of the TLS segment (in bytes)
 * @param: MIN_ALIGNMENT:  The minimum alignment requirements for the TLS segment base address.
 * @param: TEMPLATE_DATA:  Base address of an initialization template.
 *                         The first `TEMPLATE_SIZE' bytes of any per-thread data segment
 *                         that gets allocated will be initialized to the contents of these
 *                         values before `PERTHREAD_INIT' is optionally invoked in order to
 *                         perform additional initialization.
 * @param: TEMPLATE_SIZE:  The size of `TEMPLATE_DATA' in bytes, indicating the number of
 *                         leading bytes within the TLS segment that should be pre-defined
 *                         to mirror the contents of `TEMPLATE_DATA' at the time of a call
 *                         to this function (`TEMPLATE_DATA' need not remain valid or
 *                         accessible after this function returns)
 *                         Any memory after `TEMPLATE_SIZE', but before `NUM_BYTES' is initialized
 *                         to all ZEROes, however `TEMPLATE_SIZE' must not be greater than
 *                        `NUM_BYTES', and if it is, this function returns `NULL' and sets
 *                        `dlerror()' accordingly.
 * @param: PERTHREAD_INIT: An optional callback that will be invoked on a per-thread basis
 *                         in order to perform additional initialization of the associated
 *                         TLS segment within the associated thread.
 *                         This function will be called upon first access of the segment
 *                         within the thread using the data (s.a. `dltlsaddr()')
 *                         @param: ARG:  The value of `PERTHREAD_CALLBACK_ARG' passed to `dltlsalloc'
 *                         @param: BASE: The base address of the associated segment within the calling
 *                                       thread (same as the return value of `dltlsaddr()')
 * @param: PERTHREAD_FINI: An optional callback that behaves similar to `PERTHREAD_INIT',
 *                         but called by `pthread_exit()' or any other thread finalizer
 *                        (more specifically: by `dltlsfreeseg()') within any thread that
 *                         has been seen using the associated segment, and causing it to
 *                         be allocated and initialized for that thread.
 * @param: PERTHREAD_CALLBACK_ARG: A user-specified argument passed to the init/fini callbacks.
 * @return: * :            An opaque handle for the newly created TLS segment.
 *                         This handle may be used in future calls to `dltlsaddr()', and can be
 *                         destroyed (causing all threads that had previously allocated the
 *                         segment to delete it and optionally invoke finalizer callbacks) by
 *                         passing it to `dltlsfree()'
 * @return: NULL:          Failed to allocate the TLS segment (s.a. `dlerror()') */
INTDEF WUNUSED DlModule *LIBCCALL
libdl_dltlsalloc(size_t num_bytes, size_t min_alignment,
                 void const *template_data, size_t template_size,
                 void (LIBCCALL *perthread_init)(void *__arg, void *__base),
                 void (LIBCCALL *perthread_fini)(void *__arg, void *__base),
                 void *perthread_callback_arg);

/* Free a TLS segment previously allocated with `dltlsalloc' */
INTDEF WUNUSED int LIBCCALL libdl_dltlsfree(DlModule *self);

/* Return the calling thread's base address of the TLS segment associated with `TLS_HANDLE'
 * NOTE: TLS Segments are allocated and initialized lazily, meaning that the initializer
 *       passed to `dltlsalloc()' will be called by this function upon the first use of
 *       that segment within each individual thread, also causing the finalizer to be
 *       enqueued for invocation when the calling thread exists.
 * WARNING: The order in which TLS finalizers are invoked is entirely UNDEFINED!
 * NOTE: the given `TLS_HANDLE' may also be a module handle, as returned by `dlopen()',
 *       in which case this function returns a pointer to the TLS segment of that module for
 *       the calling thread (e.g.: Such a pointer is needed by `unwind_emulator_t::sm_tlsbase')
 * @return: * :   Pointer to the base of the TLS segment associated with `TLS_HANDLE' within the calling thread.
 * @return: NULL: Invalid `TLS_HANDLE', or allocation/initialization failed. (s.a. `dlerror()') */
INTDEF WUNUSED void *LIBCCALL libdl_dltlsaddr(DlModule *self);

/* Invoke the static initializers of all currently loaded modules.
 * This is called late during initial module startup once the initial
 * set of libraries, + the initial application have been loaded.
 * Note that initializers are invoked in reverse order of those modules
 * appearing within `DlModule_AllList', meaning that the primary
 * application's __attribute__((constructor)) functions are invoked
 * _AFTER_ those from (e.g.) libc. */
INTDEF void LIBCCALL DlModule_RunAllStaticInitializers(void);

/* Initialize the static TLS bindings table from the set of currently loaded modules. */
INTDEF WUNUSED int LIBCCALL DlModule_InitStaticTLSBindings(void);

/* Remove the given module from the table of static TLS bindings. */
INTDEF NONNULL((1)) void LIBCCALL DlModule_RemoveTLSExtension(DlModule *__restrict self);

#ifdef ELF_ARCH_IS_R_JMP_SLOT
/* Called from JMP_SLOT relocations (s.a. `arch/i386/rt32.S') */
INTDEF void /*ASMCALL*/ libdl_load_lazy_relocation(void);

/* Bind a lazy relocation, resolving its JMP relocation entry and returning the
 * absolute address of the bound symbol. - If the symbol can't be resolved, log
 * a system error and exit the calling application. */
INTDEF WUNUSED NONNULL((1)) ElfW(Addr) ATTR_FASTCALL
libdl_bind_lazy_relocation(DlModule *__restrict self,
#if ELF_ARCH_LAZYINDX
                           uintptr_t jmp_rel_index
#else /* ELF_ARCH_LAZYINDX */
                           uintptr_t jmp_rel_offset
#endif /* !ELF_ARCH_LAZYINDX */
                           );
#endif /* ELF_ARCH_IS_R_JMP_SLOT */



/* PEB for the main executable. */
INTDEF struct process_peb *root_peb;

INTDEF char elf_dlerror_buffer[128];
INTDEF char *elf_dlerror_message;
INTDEF ATTR_COLD int CC elf_setdlerror_badmodule(void *modptr);
INTDEF ATTR_COLD int CC elf_setdlerror_badsection(void *sectptr);
INTDEF ATTR_COLD int CC elf_setdlerror_nomem(void);
INTDEF ATTR_COLD int CC elf_setdlerror_nomodataddr(void const *static_pointer);
INTDEF ATTR_COLD NONNULL((1, 2)) int CC elf_setdlerror_nosect(DlModule *__restrict self, char const *__restrict name);
INTDEF ATTR_COLD NONNULL((1)) int VCC elf_setdlerrorf(char const *__restrict format, ...);
INTDEF ATTR_COLD NONNULL((1)) int CC elf_vsetdlerrorf(char const *__restrict format, va_list args);

/* Return the address of a builtin function (e.g. `dlopen()') */
INTDEF WUNUSED ATTR_PURE NONNULL((1)) void *FCALL dlsym_builtin(char const *__restrict name);
INTDEF WUNUSED ATTR_PURE NONNULL((1)) struct elf_dlsection *FCALL dlsec_builtin(char const *__restrict name);
INTDEF WUNUSED ATTR_CONST struct elf_dlsection *FCALL dlsec_builtin_index(size_t sect_index);
INTDEF WUNUSED ATTR_CONST char const *FCALL dlsec_builtin_name(size_t sect_index);

/* Return the address of a function `name' that is required by the RTLD core
 * and must be defined by one of the loaded libraries. - If no such function
 * is defined, log an error message to the system log and terminate the hosted
 * application ungracefully. */
INTDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) void *FCALL
require_global(char const *__restrict name);

/* Set to true if the sys_debugtrap() system call is disabled. */
INTDEF bool sys_debugtrap_disabled;

DECL_END

#endif /* !GUARD_LIBDL_ELF_H */
