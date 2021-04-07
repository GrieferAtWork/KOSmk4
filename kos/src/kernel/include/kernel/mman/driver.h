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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DRIVER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DRIVER_H 1

#include <kernel/compiler.h>

#ifndef CONFIG_USE_NEW_DRIVER
#include <kernel/driver.h>
#else /* !CONFIG_USE_NEW_DRIVER */
#include <kernel/malloc.h>
#include <kernel/mman/module.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/aref.h>
#include <kos/exec/elf.h>

#ifdef __CC__
DECL_BEGIN


/*
 * Special, per-driver symbols:
 *
 *   - extern struct driver drv_self;         // Current driver
 *   - extern byte_t[]      drv_loadaddr;     // == drv_self.md_loadaddr
 *   - extern byte_t[]      drv_loadmin;      // == drv_self.md_loadmin
 *   - extern byte_t[]      drv_loadmax;      // == drv_self.md_loadmax
 *   - extern char const[]  drv_name;         // == drv_self.d_name
 *   - extern struct mfile* drv_file;         // == driver_getfile(self)
 *   - extern char[]        drv_cmdline;      // == drv_self.d_cmdline
 *   - extern size_t        drv_argc;         // == &drv_self.d_argc
 *   - extern char*[]       drv_argv;         // == drv_self.d_argv
 *
 * TODO: extern bool     drv_arg$foo;         == ARG_EXISTS("foo") ? true : false
 * TODO: extern char*    drv_arg$foo$s;       == ARG_EXISTS("foo=$VALUE") ? "$VALUE" : NULL
 * TODO: extern char[]   drv_arg$foo$S;       == ARG_EXISTS("foo=$VALUE") ? "$VALUE" : ""
 * TODO: extern int      drv_arg$foo$d;       == ARG_EXISTS("foo=$VALUE") ? atoi("$VALUE") : 0
 * TODO: extern int      drv_arg$foo$d$42;    == ARG_EXISTS("foo=$VALUE") ? atoi("$VALUE") : atoi("42")
 * TODO: extern uint32_t drv_arg$foo$I32u$42; == ARG_EXISTS("foo=$VALUE") ? atou32("$VALUE") : atou32("42")
 *
 */


struct mfile;
struct driver_section
#if defined(__cplusplus) && !defined(__WANT_DRIVER_SECTION_ds_sect)
    : module_section
#endif /* __cplusplus && !__WANT_DRIVER_SECTION_ds_sect */
{
#if !defined(__cplusplus) || defined(__WANT_DRIVER_SECTION_ds_sect)
	struct module_section ds_sect;     /* The underlying section. */
#endif /* !__cplusplus || __WANT_DRIVER_SECTION_ds_sect */
	ElfW(Shdr)           *ds_shdr;     /* [1..1][const] Section header. */
	byte_t               *ds_addr;     /* [0..1][lock(WRITE_ONCE)] Section buffer address.
	                                    * Owned for non-`SHF_ALLOC' section. */
	byte_t               *ds_infladdr; /* [0..1][lock(WRITE_ONCE)] Inflated section address. */
	size_t                ds_inflsize; /* [0..1][lock(WRITE_ONCE)] Inflated section size. */
};

#if !defined(__cplusplus) || defined(__WANT_DRIVER_SECTION_ds_sect)
#define __driver_section_as_module_section(self)  (&(self)->ds_sect)
#define __driver_section_destroy(self)    module_section_destroy(&(self)->ds_sect)
#define __driver_section_refcnt(self)     (self)->ds_sect.ms_refcnt
DEFINE_REFCOUNT_FUNCTIONS_P(struct driver_section, __driver_section_refcnt, __driver_section_destroy)
#else /* !__cplusplus || __WANT_DRIVER_SECTION_ds_sect */
#define __driver_section_as_module_section /* nothing */
#endif /* __cplusplus && !__WANT_DRIVER_SECTION_ds_sect */


#ifndef __elfw_hashtable_defined
#define __elfw_hashtable_defined 1
typedef struct elfW(hashtable) {
	ElfW(Word) ht_nbuckts;      /* # of buckets. */
	ElfW(Word) ht_nchains;      /* # of symbols. */
	ElfW(Word) ht_table[1024];  /* [ht_nbuckts] Hash table. */
/*	ElfW(Word) ht_chains[1024];  * [ht_nchains] Hash chains. */
} ElfW(HashTable);
#endif /* !__elfw_hashtable_defined */

#ifndef __elfw_gnu_hashtable_defined
#define __elfw_gnu_hashtable_defined 1
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

struct driver_section;
#ifndef __driver_section_awref_defined
#define __driver_section_awref_defined
AWREF(driver_section_awref, driver_section);
#endif /* !__driver_section_awref_defined */

/* NOTE: Driver states are only allowed to transition as follows:
 *
 *  [initial]              --> DRIVER_STATE_INIT        // Initial state
 *
 *  DRIVER_STATE_INIT      --> DRIVER_STATE_INIT_DEPS   // Being initialization
 *  DRIVER_STATE_INIT      --> DRIVER_STATE_KILL        // Finalize immediatly
 *
 *  DRIVER_STATE_INIT_DEPS --> DRIVER_STATE_INIT_RELO   // Upon success
 *  DRIVER_STATE_INIT_DEPS --> DRIVER_STATE_KILL        // If loading dependencies fails
 *
 *  DRIVER_STATE_INIT_RELO --> DRIVER_STATE_INIT_CTRS   // Upon success
 *  DRIVER_STATE_INIT_RELO --> DRIVER_STATE_FINI_DEPS   // If applying relocations fails
 *
 *  DRIVER_STATE_INIT_CTRS --> DRIVER_STATE_LOADED      // Upon success
 *  DRIVER_STATE_INIT_CTRS --> DRIVER_STATE_FINI_DTRS   // If a ctor throws an exception
 *
 *  DRIVER_STATE_FINI_DTRS --> DRIVER_STATE_FINI_DEPS   // Always
 *
 *  DRIVER_STATE_FINI_DEPS --> DRIVER_STATE_KILL        // Always
 *
 *  DRIVER_STATE_KILL      --> DRIVER_STATE_DEAD        // When `md_refcnt' drops to `0'
 *
 * NOTE: Depending on state, drivers also hold a reference to  themselves.
 *       The reference loop formed by this is intentional, and is used  to
 *       prevent a driver from being destroyed before finalizers have been
 *       executed, thus preventing driver text being unloaded before  that
 *       point in time. */
#define DRIVER_STATE_INIT      0 /* [SELFREF] Currently loading driver dependencies. */
#define DRIVER_STATE_INIT_DEPS 1 /* [SELFREF] Currently loading driver dependencies. */
#define DRIVER_STATE_INIT_RELO 2 /* [SELFREF] Currently applying relocations. */
#define DRIVER_STATE_INIT_CTRS 3 /* [SELFREF] Currently executing driver constructors. */
#define DRIVER_STATE_LOADED    4 /* [SELFREF] Driver has been loaded, and is sitting in memory. */
#define DRIVER_STATE_FINI_DTRS 5 /* [SELFREF] Currently executing driver destructors. */
#define DRIVER_STATE_FINI_DEPS 6 /* [SELFREF] Currently clearing */
#define DRIVER_STATE_KILL      7 /* Driver was killed. */
#define DRIVER_STATE_DEAD      8 /* Driver `wasdestroyed() == true'. */

/* Signal broadcast whenever the `d_state' of any loaded driver changes. */
DATDEF struct sig driver_state_changed;

struct driver;
struct driver_fde_cache;

#ifndef __driver_axref_defined
#define __driver_axref_defined
AXREF(driver_axref, driver);
#endif /* !__driver_axref_defined */

#define __driver_defined
struct driver
#if defined(__cplusplus) && !defined(__WANT_DRIVER_d_module)
    : module
#endif /* __cplusplus && !__WANT_DRIVER_d_module */
{
#if !defined(__cplusplus) || defined(__WANT_DRIVER_d_module)
	struct module                  d_module;     /* The underlying module. */
#endif /* !__cplusplus || __WANT_DRIVER_d_module */

	/* NOTE: The following members remain valid, even after `wasdestroyed(self)':
	 *    - d_module.md_ops
	 *    - d_module.md_mman            (will still be `mman_kernel')
	 *    - d_module.md_loadaddr
	 *    - d_module.md_loadmin
	 *    - d_module.md_loadmax
	 *    - d_module.md_sizeof_pointer
	 *    - d_state                     (will eventually be set to `DRIVER_STATE_DEAD')
	 *    - d_name
	 *    - d_eh_frame_start
	 *    - d_eh_frame_end
	 *    - d_dyncnt
	 *    - d_dynhdr
	 *    - d_dynsym_tab
	 *    - d_dynsym_cnt
	 *    - d_gnuhashtab
	 *    - d_hashtab
	 *    - d_dynstr
	 *    - d_dynstr_end
	 *    - d_phnum
	 *    - d_phdr
	 * All other fields must be considered as `[valid_if(!wasdestroyed(self))]',
	 * and no longer be accessed after that point in time! */

	/* Basic driver information */
	uintptr_t                      d_state;      /* [lock(ATOMIC)] Driver state (one of `DRIVER_STATE_*')
	                                              * Whenever this value is changed, `driver_state_changed' is broadcast. */
	char const                    *d_name;       /* [1..1][const] Name of the driver (the module's `DT_SONAME' tag) */
	char                          *d_cmdline;    /* [1..1][const][owned] Driver commandline (in the form of "foo\0bar\0baz\0\0") */
	size_t                         d_argc;       /* [const] # of arguments passed to the driver (# of strings pointed to by `d_argv') */
	char                         **d_argv;       /* [1..1][1..d_argc][const][owned] Driver argument vector (terminated by a NULL-pointer) */

	/* Driver dependencies. */
	size_t                         d_depcnt;     /* [const] # of dependencies of this driver. */
	struct driver_axref           *d_depvec;     /* [0..1][0..d_depcnt][const]    Driver    dependencies.
	                                              * Note  that cyclic dependencies  are allowed, and that
	                                              * the  vector of dependencies  is cleared during driver
	                                              * finalization by `DRIVER_STATE_FINI_DEPS', thus fixing
	                                              * the reference  loops caused  by cyclic  dependencies. */

	/* Special handling for the `.eh_frame' section. */
	byte_t const                  *d_eh_frame_start;      /* [0..1][<= d_eh_frame_end][const] Starting pointer for the `.eh_frame' section */
	byte_t const                  *d_eh_frame_end;        /* [0..1][>= d_eh_frame_start][const] Ending pointer for the `.eh_frame' section */
	struct driver_fde_cache       *d_eh_frame_cache;      /* [0..1][lock(d_eh_frame_cache)] Tree for an `.eh_frame' lookup cache. */
	struct atomic_rwlock           d_eh_frame_cache_lock; /* Lock for `d_eh_frame_cache' */

	/* Special handling for the `.dynamic' section. */
	size_t                         d_dyncnt;     /* [const] Number of dynamic definition headers. */
	ElfW(Dyn) const               *d_dynhdr;     /* [0..d_dyncnt][const] Vector of dynamic definition entries. */
	ElfW(Sym) const               *d_dynsym_tab; /* [0..d_dynsym_cnt][const] Vector of dynamic symbols defined by this module. */
	size_t                         d_dynsym_cnt; /* [const] Number of dynamic symbols defined by this driver. */
	ElfW(GnuHashTable) const      *d_gnuhashtab; /* [0..1][const] GNU Symbol hash table. */
	ElfW(HashTable) const         *d_hashtab;    /* [0..1][const] ELF Symbol hash table. */
	char const                    *d_dynstr;     /* [0..1][const] Dynamic string table. */
	char const                    *d_dynstr_end; /* [0..1][const] End of the dynamic string table. */

	/* Named sections information for the driver. */
	ElfW(Off)                      d_shoff;      /* [const] File offset to section headers. */
	ElfW(Half)                     d_shstrndx;   /* [const] Index of the section header names section. */
	ElfW(Half)                     d_shnum;      /* [const] (Max) number of section headers. */
#if __SIZEOF_POINTER__ > 4
	__byte_t                      _d_pad2[__SIZEOF_POINTER__ - 4];
#endif /* __SIZEOF_POINTER__ > 4 */
	ElfW(Shdr) const              *d_shdr;       /* [lock(WRITE_ONCE)][0..d_shnum][owned] Vector of section headers (or `NULL' if not loaded). */
	struct driver_section_awref   *d_sections;   /* [0..1][0..d_shnum][const][owned] Vector of locked sections. */
	char const                    *d_shstrtab;   /* [lock(WRITE_ONCE)][0..1][owned] Section headers name table (or `NULL' if not loaded). */
	size_t                         d_shstrsiz;   /* [lock(WRITE_ONCE)][valid_if(d_shstrtab)] Section header name table size. */

	/* Driver program headers */
	ElfW(Half)                     d_phnum;      /* [!0][const] (Max) number of program headers. */
	byte_t                        _d_pad3[sizeof(void *) - sizeof(ElfW(Half))];
	COMPILER_FLEXIBLE_ARRAY(ElfW(Phdr), d_phdr); /* [d_phnum][const] Vector of program headers. */
};

/* Check if the given driver is/was finalized. */
#define driver_isfinalizing(self) \
	(__hybrid_atomic_load((self)->d_state, __ATOMIC_ACQUIRE) >= DRIVER_STATE_FINI_DTRS)


#if !defined(__cplusplus) || defined(__WANT_DRIVER_d_module)
#define __driver_as_module(self)  (&(self)->d_module)
#define __driver_destroy(self)    module_destroy(&(self)->d_module)
#define __driver_free(self)       module_free(&(self)->d_module)
#define __driver_refcnt(self)     (self)->d_module.md_refcnt
#define __driver_weakrefcnt(self) (self)->d_module.md_weakrefcnt
DEFINE_REFCOUNT_FUNCTIONS_P(struct driver, __driver_refcnt, __driver_destroy)
DEFINE_WEAKREFCOUNT_FUNCTIONS_P(struct driver, __driver_weakrefcnt, __driver_free)
#else /* !__cplusplus || __WANT_DRIVER_d_module */
#define __driver_as_module /* nothing */
#endif /* __cplusplus && !__WANT_DRIVER_d_module */

/* The driver descriptor for the kernel core */
#ifndef __kernel_driver_defined
#define __kernel_driver_defined
DATDEF struct driver kernel_driver;
#endif /* !__kernel_driver_defined */

#ifndef __drv_self_defined
#define __drv_self_defined
#ifdef CONFIG_BUILDING_KERNEL_CORE
DATDEF struct driver drv_self ASMNAME("kernel_driver");
#else /* CONFIG_BUILDING_KERNEL_CORE */
DATDEF struct driver drv_self;
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
#endif /* !__drv_self_defined */



/************************************************************************/
/* Driver enumeration/lookup functions                                  */
/************************************************************************/
/* Note that the `module_*' functions can also be used, however these   */
/* functions will always return `NULL' for non-kernel-space addresses!  */
/* Additionally, these functions are alowed NOBLOCK+NOTHROW!            */
/************************************************************************/
FUNDEF NOBLOCK WUNUSED REF struct driver *NOTHROW(FCALL driver_fromaddr)(void const *addr);
FUNDEF NOBLOCK WUNUSED REF struct driver *NOTHROW(FCALL driver_aboveaddr)(void const *addr);
FUNDEF NOBLOCK WUNUSED REF struct driver *NOTHROW(FCALL driver_next)(struct driver *prev);

/* Lookup an already-loaded driver, given its name or file. */
FUNDEF WUNUSED REF struct driver *FCALL driver_fromname(USER CHECKED char const *driver_name) THROWS(E_SEGFAULT);
FUNDEF WUNUSED REF struct driver *FCALL driver_fromname_with_len(USER CHECKED char const *driver_name, size_t driver_name_len) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver *NOTHROW(FCALL driver_fromfile)(struct mfile *__restrict driver_file);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED REF struct driver *FCALL
driver_fromname(USER CHECKED char const *driver_name, size_t driver_name_len)
	THROWS(E_SEGFAULT) ASMNAME("driver_fromname_with_len");
} /* extern "C++" */
#endif /* __cplusplus */



/************************************************************************/
/* Driver helper functions                                              */
/************************************************************************/

/* Return the name of the given driver. */
#define driver_getname(self) (self)->d_name

/* Return the mem-file belonging to the given driver.
 * If the driver  wasn't loaded form  a file, try  to search for  that
 * file within the root filesystem within paths from `driver_libpath'.
 * If the file still can't be found, return `NULL'. */
FUNDEF WUNUSED NONNULL((1)) struct mfile *FCALL
driver_getfile(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC);

/* Try to return a mapping for the given driver's section headers.
 * If this fails, return `NULL' instead. */
FUNDEF WUNUSED NONNULL((1)) ElfW(Shdr) const *FCALL
driver_getshdrs(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC);

/* Try to return a mapping for the given driver's .shstrtab section.
 * If this fails, return `NULL' instead. */
FUNDEF WUNUSED NONNULL((1)) char const *FCALL
driver_getshstrtab(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC);


/************************************************************************/
/* Driver symbol lookup functions                                       */
/************************************************************************/

struct driver_syminfo {
	USER CHECKED char const *dsi_name;    /* [1..1][in] Symbol name */
	uint32_t                 dsi_elfhash; /* [in|out] ELF symbol name hash. */
	uint32_t                 dsi_gnuhash; /* [in|out] GNU symbol name hash. */
	void                    *dsi_addr;    /* [out] Symbol address. (absolute) */
	size_t                   dsi_size;    /* [out] Symbol size. */
	unsigned char            dsi_bind;    /* [out] Symbol binding (one of `STB_GLOBAL' or `STB_WEAK') */
};

/* Initialize a given driver symbol info descriptor. */
#define driver_syminfo_init(self, name)        \
	(void)((self)->dsi_name    = (name),       \
	       (self)->dsi_elfhash = (uint32_t)-1, \
	       (self)->dsi_gnuhash = (uint32_t)-1)

/* Lookup a symbol  within a driver,  given its  name.
 * Note that this function will _not_ look into driver
 * dependencies in order to resolve that symbol.
 * NOTE: This function also takes care of the special
 *       set of `drv_*' symbols!
 * @return: true:  Found a symbol matching the given name.
 * @return: false: No symbol matching the given name found. */
FUNDEF WUNUSED NONNULL((1, 2)) __BOOL FCALL
driver_dlsym_local(struct driver *__restrict self,
                   struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...);

/* Same  as `driver_dlsym_local()', but if that function fails,
 * or  returns a weak  symbol, scan all  of the dependencies of
 * `self'  for another symbol with the same name. If a non-weak
 * symbol is found return it. Otherwise, return the first  weak
 * symbol encountered during the search, and if all that fails,
 * return `false' to indicate failure.
 * @return: true:  Found a symbol matching the given name.
 * @return: false: No symbol matching the given name found. */
FUNDEF WUNUSED NONNULL((1, 2)) __BOOL FCALL
driver_dlsym(struct driver *__restrict self,
             struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...);

/* Search for a symbol in all loaded drivers, following the order
 * of drivers, as they appear returned by `get_driver_loadlist()' */
FUNDEF WUNUSED NONNULL((1)) __BOOL FCALL
driver_dlsym_global(struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...);

/* Helper wrappers for the above functions that simply take the
 * name of the symbol and will return its address, or `NULL' if
 * no such symbol could be found. */
FUNDEF WUNUSED NONNULL((1)) void *FCALL driver_dlsym_local_f(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1)) void *FCALL driver_dlsym_f(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...);
FUNDEF WUNUSED NONNULL((1)) void *FCALL driver_dlsym_global_f(USER CHECKED char const *name) THROWS(E_SEGFAULT, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED NONNULL((1)) void *FCALL driver_dlsym_local(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...) ASMNAME("driver_dlsym_local_f");
FUNDEF WUNUSED NONNULL((1)) void *FCALL driver_dlsym(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...) ASMNAME("driver_dlsym_f");
FUNDEF WUNUSED NONNULL((1)) void *FCALL driver_dlsym_global(USER CHECKED char const *name) THROWS(E_SEGFAULT, ...) ASMNAME("driver_dlsym_global_f");
} /* extern "C++" */
#endif /* __cplusplus */



struct driver_symaddr {
	void         *dsa_addr;    /* [out] Symbol address. (absolute) */
	size_t        dsa_size;    /* [out] Symbol size. */
	char const   *dsa_name;    /* [1..1][out] Symbol name */
	unsigned char dsa_bind;    /* [out] Symbol binding (one of `STB_GLOBAL' or `STB_WEAK') */
};


/* Do the reverse of the `dlsym()' functions above, and resolve
 * a  driver-relative `driver_reladdr' to try to determine info
 * about the symbol that contains that address.
 * @return: true:  Success.
 * @return: false: Failure. */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 2)) __BOOL
NOTHROW(FCALL driver_dladdr_local)(struct driver *__restrict self,
                                   struct driver_symaddr *__restrict info,
                                   uintptr_t driver_reladdr);

/* Similar to `driver_dladdr_local()', but uses `driver_fromaddr()'
 * to lookup the module containing  `addr', and follows this up  by
 * using `driver_dladdr_local()' */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver *
NOTHROW(FCALL driver_dladdr)(struct driver_symaddr *__restrict info,
                             void const *addr);


struct unwind_fde_struct;

/* Lookup the FDE descriptor for a given `absolute_pc', whilst trying to
 * make use of the FDE cache of `self'.
 * @return: * : One of `UNWIND_*' from <libunwind/api.h> */
FUNDEF NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL driver_findfde)(struct driver *__restrict self, void const *absolute_pc,
                              struct unwind_fde_struct *__restrict result);











/************************************************************************/
/* Driver load/unload functions                                         */
/************************************************************************/

/* Initialize the given driver by transitioning its state  to
 * `DRIVER_STATE_LOADED'. If this fails, or if the driver was
 * already finalized, its state is set to `DRIVER_STATE_KILL'
 * instead. */
FUNDEF NONNULL((1)) void FCALL
driver_initialize(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR, E_NOT_EXECUTABLE);

/* Finalize the given driver. Note that this function is NOTHROW,
 * but isn't necessarily NOBLOCK! - Driver finalizers are allowed
 * to block and throw exceptions (meaning that this function  may
 * also block), and any exception  thrown will be written to  the
 * system log. However, any such exceptions are silently ignored,
 * and driver finalization will always continue regardless.
 *
 * Note however that driver program text/data will only be
 * unmapped once the driver's weak reference counter drops
 * to `0'! */
FUNDEF NONNULL((1)) void
NOTHROW(FCALL driver_finalize)(struct driver *__restrict self);


/* Load & return  a driver from  a given `driver_file'.  The
 * returned driver may  not have been  initialized, yet.  As
 * such, the  caller  should  use  `driver_initialize()'  in
 * order to ensure that the returned driver was initialized.
 * @param: pnew_driver_loaded: When non-NULL, set to true/false in
 *                             order to indicate  if the  returned
 *                             driver was newly loaded, or already
 *                             present before. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod_file(struct mfile *__restrict driver_file,
                    struct path *driver_path DFL(__NULLPTR),
                    struct directory_entry *driver_dentry DFL(__NULLPTR),
                    USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                    __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod_blob(USER CHECKED void const *base, size_t num_bytes,
                    USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                    __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
FUNDEF ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_loadmod(USER CHECKED char const *driver_name,
               USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
               __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR, E_FSERROR);
#ifdef __cplusplus
extern "C++" {
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod(struct mfile *__restrict driver_file,
               struct path *driver_path DFL(__NULLPTR),
               struct directory_entry *driver_dentry DFL(__NULLPTR),
               USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
               __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR)
		ASMNAME("driver_loadmod_file");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod(USER CHECKED void const *base, size_t num_bytes,
               USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
               __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR)
		ASMNAME("driver_loadmod_blob");
} /* extern "C++" */
#endif /* __cplusplus */


/* Helper-wrappers for the functions above that will automatically
 * ensure that the driver is initialized successfully, and if said
 * initialization were to cause an exception, finalize the  driver
 * to have it be unloaded once again. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_file(struct mfile *__restrict driver_file,
                   struct path *driver_path DFL(__NULLPTR),
                   struct directory_entry *driver_dentry DFL(__NULLPTR),
                   USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                   __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_blob(USER CHECKED void const *base, size_t num_bytes,
                   USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                   __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
FUNDEF ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_insmod(USER CHECKED char const *driver_name,
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR, E_FSERROR);
#ifdef __cplusplus
extern "C++" {
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod(struct mfile *__restrict driver_file,
              struct path *driver_path DFL(__NULLPTR),
              struct directory_entry *driver_dentry DFL(__NULLPTR),
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR)
		ASMNAME("driver_insmod_file");
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod(USER CHECKED void const *base, size_t num_bytes,
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR)
		ASMNAME("driver_insmod_blob");
} /* extern "C++" */
#endif /* __cplusplus */


/* Flags for driver unloading functions. */
#define DRIVER_DELMOD_F_NORMAL   0x0000 /* Normal delmod flags. */
#define DRIVER_DELMOD_F_NODEPEND 0x0001 /* Don't try to delete drivers that have dependencies on `self' */
#define DRIVER_DELMOD_F_FORCE    0x0200 /* Force unload the driver, even if unaccounted references remain
                                         * WARNING: Doing this may compromise system integrity! */
#define DRIVER_DELMOD_F_NONBLOCK 0x0800 /* Don't wait for the driver to fully go away.
                                         * Instead, the driver  will have  gone away once  it can  no longer  be
                                         * enumerated. In the event that the driver has a (possibly intentional)
                                         * reference   leak,  you  must  use  `KSYSCTL_DRIVER_DELMOD_FFORCE'  to
                                         * unload the driver (though doing this is _very_ dangerous) */

#define DRIVER_DELMOD_ST_SUCCESS  0 /* Successfully unloaded the driver. */
#define DRIVER_DELMOD_ST_UNKNOWN  1 /* The specified driver could not be found. */
#define DRIVER_DELMOD_ST_INUSE    2 /* The specified driver has unaccounted references.
                                     * NOTE: in  this  case,  driver  finalizers  were  still executed,
                                     *       meaning that in all likelihood, the unaccounted references
                                     *       stem from another thread currently holding a reference  to
                                     *       the driver, such as when  trying to resolve addr2line  for
                                     *       a static pointer apart of the driver's binary image. */



/* Try to unload a driver module.
 * This function will:
 *   - Call `driver_finalize()'
 *   - if (!DRIVER_DELMOD_F_NODEPEND):
 *         Search for other modules  make use of `self'  through
 *         dependencies and finalize all of them such that their
 *         dependency vectors  can  be  cleared,  including  the
 *         contained references to `self'
 *   - weakincref(self);
 *   - if (DRIVER_DELMOD_F_FORCE):
 *         force the refcnt of `self' to 0
 *     else:
 *         Drop a reference from `self'
 *   - if (!DRIVER_DELMOD_F_NONBLOCK):
 *         Wait for `self' to reach its `DRIVER_STATE_DEAD'-state
 *   - weakdecref(self);
 * @param: self:                      The driver to try to unload.
 * @param: flags:                     Set of `DRIVER_DELMOD_F_*'
 * @return: DRIVER_DELMOD_ST_SUCCESS: Successfully unloaded the driver and inherited the reference to `self'
 * @return: DRIVER_DELMOD_ST_INUSE:   Only when  `DRIVER_DELMOD_F_NONBLOCK' is  given: There  are
 *                                    still other references to `self' that aren't accounted for.
 * @return: DRIVER_DELMOD_ST_INUSE:   The given driver `self' is `kernel_driver' */
FUNDEF NONNULL((1)) unsigned int FCALL
driver_try_decref_and_delmod(/*inherit(always)*/ REF struct driver *__restrict self,
                             unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK);



/* Unload a driver from the kernel core.
 * @param: driver_name: The name of the driver, or its
 *                      filename (when the first character is `/')
 * @param: flags: Set of `DRIVER_DELMOD_F_*'
 * @return: * :   One of `DRIVER_DELMOD_ST_*' */
FUNDEF NONNULL((1)) unsigned int FCALL
driver_delmod(USER CHECKED char const *driver_name,
              unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) unsigned int FCALL
driver_delmod_file(struct mfile *__restrict driver_file,
                   unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF NONNULL((1)) unsigned int FCALL
driver_delmod(struct mfile *__restrict driver_file,
              unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK)
		ASMNAME("driver_delmod_file");
}
#endif /* __cplusplus */





/************************************************************************/
/* Loaded driver enumeration (lockless!)                                */
/************************************************************************/
struct driver_loadlist {
	WEAK refcnt_t                                     dll_refcnt;   /* Reference counter. */
	size_t                                            dll_count;    /* [!= 0][const] Number of loaded drivers. */
	COMPILER_FLEXIBLE_ARRAY(WEAK REF struct driver *, dll_drivers); /* [1..1][const][ds_count] Vector of loaded drivers.
	                                                                 * NOTE: This vector always contains `kernel_driver'
	                                                                 * NOTE: This vector is sorted by `md_loadmin' */
};
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(FCALL driver_loadlist_destroy)(struct driver_loadlist *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct driver_loadlist, dll_refcnt, driver_loadlist_destroy)

/* Return the list of currently loaded drivers.
 * Note that this function is  NOBLOCK+NOTHROW! */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED REF struct driver_loadlist *
NOTHROW(FCALL get_driver_loadlist)(void);



struct driver_libpath_struct {
	WEAK refcnt_t                 dlp_refcnt; /* Reference counter. */
	COMPILER_FLEXIBLE_ARRAY(char, dlp_path);  /* Path string. */
};
DEFINE_REFCOUNT_FUNCTIONS(struct driver_libpath_struct, dlp_refcnt, kfree);

#ifndef __driver_libpath_arref_defined
#define __driver_libpath_arref_defined
ARREF(driver_libpath_arref, driver_libpath_struct);
#endif /* !__driver_libpath_arref_defined */

/* [1..1] The current driver library path.
 * This path  is  a  ':'-separated list  of  UNIX-style  pathnames
 * that are used to resolve dependencies of kernel driver modules.
 * By default, this  string is  KERNEL_DRIVER_DEFAULT_LIBRARY_PATH */
DATDEF struct driver_libpath_arref driver_libpath;


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_DRIVER */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DRIVER_H */
