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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H 1

#include <kernel/compiler.h>

#include <kernel/arch/driver.h>
#include <kernel/driver-callbacks.h>
#include <kernel/malloc.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>

#include <hybrid/sequence/list.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <elf.h>

#ifndef ELFW
#if __SIZEOF_POINTER__ == 4
#define ELFW(x) ELF32_##x
#define ElfW(x) Elf32_##x
#elif __SIZEOF_POINTER__ == 8
#define ELFW(x) ELF64_##x
#define ElfW(x) Elf64_##x
#endif
#endif /* !ELFW */

DECL_BEGIN

#ifndef KERNEL_DRIVER_DEFAULT_LIBRARY_PATH
#define KERNEL_DRIVER_DEFAULT_LIBRARY_PATH    "/os/drivers"
#endif /* !KERNEL_DRIVER_DEFAULT_LIBRARY_PATH */


#ifdef __CC__


/* KOS Kernel modules are implemented as shared ELF binaries (libraries)
 * Just like user-space ELF binaries, kernel-space modules (drivers) are
 * allowed to both import and export symbols from other modules (also
 * allowing them to have dependencies on other modules via DT_NEEDED), as
 * well as directly make use of symbols that are exported from the kernel core.
 * To make use of the later, drivers don't need to specify any special
 * dependency, as any symbol lookup will first check if the kernel exports
 * a symbol matching the given name, before moving on to search dependencies,
 * as well as the driver itself for the symbol (during which the kernel will
 * also account for weak symbol declarations) - All symbols exports by the
 * kernel core are non-weak symbols (aka.: Can't be overwritten)
 *
 * Special rules/allowed assumptions:
 *   - All static memory segments defined by a driver are mapped as detached,
 *     pre-faulted, fully initialized, anonymous and locked memory.
 *     -> This way, future changes made to MAP_SHARED mappings of kernel drivers
 *        will _NOT_ affect the data mapped within the kernel core.
 *     -> Additionally, this allows drivers to assume that all static data/text
 *        can safely be used without having to worry about segfaults being
 *        triggered like when a user-space application accesses a swapped, or
 *        not-yet loaded section of memory.
 *     -> All memory marked as `SHT_ALLOC' (found in program headers) is locked,
 *        though memory that doesn't appear in program headers does not get loaded
 *        during driver initialization (e.g. `.debug_line')
 *   - Inter-driver dependencies (DT_NEEDED) are handled somewhat special:
 *      - Dependency resolution happens in a 2-step process,
 *        where the first step takes the name of the driver
 *        dependency and compares it to the DT_SONAME tags
 *        of all drivers already loaded.
 *        If the name matches one of them, that driver is used as the dependency
 *      - If no drivers were found during this step, the `DT_NEEDED' name is appended
 *        to each of the driver library paths (s.a. `driver_library_path.get()')
 *        The resulting string is then used again to search the set of currently
 *        loaded drivers (this time comparing against the filenames of loaded drivers).
 *      - Lastly, the same set of filesystem strings is used once again, only this
 *        time together with `vfs_kernel' in order to try and resolve to a filesystem
 *        location, from which the kernel will then attempt to load the driver.
 *   - Unallocated sections (such as e.g.: `.debug_line') are lazily locked into
 *     memory the first time they are used. (though these are _NOT_ mapped with
 *     GFP_LOCKED, meaning that optional sections may be swapped at any time)
 *   - Modules are _always_ required to have a `DT_SONAME' tag
 *   - Modules are identified by their `DT_SONAME' tags, where only 1 driver
 *     of any number of modules with the same SONAME tag can ever be loaded
 *     at once.
 *     To simplify driver identification, it is recommended to re-use
 *     the driver's filename as its `DT_SONAME'
 *   - Module initializers/finalizers should be declared using
 *     __attribute__((constructor)) and __attribute__((destructor))
 *     During construction, the driver linker will invoke all constructor
 *     callbacks in ascending order. If any callback returns by throwing
 *     an error `THROW(*)', all destructors of the driver itself, as well
 *     as all newly loaded dependencies that aren't used by any other driver
 *     will be invoked.
 *     NOTE: Destructors are also allowed to throw exceptions.
 *   - Driver constructors are allowed (and encouraged) to incref() their
 *     own driver descriptor (s.a. `drv_self') in order to register global
 *     hooks or other kernel components. However, all references created must
 *     be decref()ed by driver destructors, such that a call to `driver_finalize()'
 *     will be able to unload all global hooks of a driver and allow it to be
 *     unloaded once any remaining unaccounted references are lost.
 *   - To safe on space, you are welcome to build modules with `-Wl,--nmagic'
 *     Because drivers don't use file mappings, their images aren't bound to the
 *     usual restrictions of file->memory mappings.
 *   - dynamic RUNPATH tags are ignored. - The kernel module/library paths
 *     are fixed and can only be changed by explicit kernel control commands,
 *     as well as via the kernel command line during boot.
 *   - Cyclic dependencies are not allowed
 *   - Modules must be relocatable and of type `ET_DYN' (shared library)
 *   - A hand full of special symbols are defined for each loaded driver,
 *     and may be used anywhere inside of that driver where an external
 *     symbol reference may appear:
 *      - `struct driver drv_self'          -- The driver descriptor for that module.
 *      - `byte_t        drv_loadaddr[]'    -- Symbol defined at `_this_driver.d_loadaddr'
 *      - `byte_t        drv_start[]'       -- Symbol defined at `_this_driver.d_loadstart'
 *      - `byte_t        drv_end[]'         -- Symbol defined at `_this_driver.d_loadend'
 *      - `char          drv_name[]'        -- Symbol defined at `_this_driver.d_name' (the address of the DT_SONAME tag)
 *      - `char         *drv_filename'      -- Symbol defined at `&_this_driver.d_filename'
 *      - `struct inode *drv_file'          -- Symbol defined at `&_this_driver.d_file'
 *      - `char          drv_commandline[]' -- A string in the form of "foo\0bar\0baz\0\0" representing the invocation commandline of the driver
 *      - `size_t        drv_argc'          -- The number of arguments passed to the driver.
 *      - `char         *drv_argv[]'        -- A vector of arguments passed to the driver. (pointers contained in this symbol are apart of `_this_commandline')
 *                                             NOTE: This vector is also terminated by a NULL-pointer
 *      - `char          drv_arg_${NAME}[]' -- Bound to VALUE of a commandline option `NAME=VALUE'. - If not given, points to an empty string
 *      - `char          drv_argp_${NAME}[]'-- Bound to NAME the commandline argument `NAME' if present, or `NULL' otherwise
 *                                             >> DATDEF char drv_arg_foo[];    // "bar"
 *                                             >> DATDEF char drv_arg_baz[];    // "42"
 *                                             >> DATDEF char drv_arg_nope[];   // ""
 *                                             >> DATDEF char drv_argp_debug[]; // "debug"
 *                                             >> DATDEF char drv_argp_nope[];  // NULL
 *                                             Loaded with `sysctl_insmod("my_driver", "foo=bar debug baz=42")'
 *   - Special symbols which may be exported by a driver,
 *     and will be interacted with on special occasions:
 *      - `PUBLIC NOBLOCK size_t NOTHROW(KCALL drv_clearcache)(void) { ... }'
 *             Try (as in: never throw, or block) to clear global caches, releasing
 *             heap memory as those caches are cleared before returning the total
 *             sum of bytes that were cleared by doing this. (Alternatively, any
 *             non-zero value should be returned if ~some~ kind of optional resource
 *             was released, with 0 being _required_ to be returned when nothing was
 *             freed at all)
 * Building a driver:
 *   $ g++ -fno-rtti -shared -static-libgcc -ffreestanding -o MY_DRIVER.o MY_DRIVER.c
 *   $ g++ -fno-rtti -shared -static-libgcc -ffreestanding -nostdlib -Wl,-soname=MY_DRIVER -o MY_DRIVER MY_DRIVER.o -lgcc
 * NOTE: No need to pass -fPIC as longer driver initialization times
 *       should be preferred above overall slow driver run-times.
 */






#ifndef CONFIG_BUILDING_KERNEL_CORE
/* Special driver symbols */
#ifndef __drv_self_defined
#define __drv_self_defined 1
DATDEF struct driver drv_self;          /* Self-pointer to the current driver's descriptor */
#endif /* !__drv_self_defined */
DATDEF byte_t        drv_loadaddr[];    /* Absolute load-address of the driver (== drv_self.d_loadaddr) */
DATDEF byte_t        drv_start[];       /* Absolute starting address of the driver program (== drv_self.d_loadstart) */
DATDEF byte_t        drv_end[];         /* Absolute end address of the driver program (== drv_self.d_loadend) */
DATDEF char          drv_name[];        /* Name of the driver (== drv_self.d_name) */
DATDEF char         *drv_filename;      /* [0..1] Filename of the driver (== &drv_self.d_filename) */
DATDEF struct inode *drv_file;          /* [0..1] Inode of the of the driver (== drv_self.d_file) */
DATDEF char          drv_commandline[]; /* Driver commandline (== drv_self.d_cmdline) */
DATDEF size_t        drv_argc;          /* Driver argument count (== &drv_self.d_argc) */
DATDEF char         *drv_argv[];        /* [1..1][drv_argc] Driver argument vector (== drv_self.d_argv) */


/* NOTE: This function may be implemented by individual drivers!
 *       This isn't a function that is exported by the kernel itself!
 * Try (as in: never throw, or block) to clear global caches, releasing
 * heap memory as those caches are cleared before returning the total
 * sum of bytes that were cleared by doing this. (Alternatively, any
 * non-zero value should be returned if ~some~ kind of optional resource
 * was released, with 0 being _required_ to be returned when nothing was
 * freed at all)
 * This function is called when the kernel has run out of physical or
 * virtual memory, at which point this function's purpose is to try and
 * reclaim resources to allow the kernel to continue operation without
 * (normally) causing an E_BADALLOC exception to be thrown by the caller.
 * @return: * : Some kind of optional resource(s) was/were freed
 * @return: 0 : Nothing could be freed/released */
FUNDEF NOBLOCK size_t NOTHROW(KCALL drv_clearcache)(void);

#ifndef DRIVER_INIT
#define DRIVER_INIT     __attribute__((__constructor__))
#define DRIVER_FINI     __attribute__((__destructor__))
#endif /* !DRIVER_INIT */
#else /* !CONFIG_BUILDING_KERNEL_CORE */
#ifndef __drv_self_defined
#define __drv_self_defined 1
DATDEF struct driver drv_self ASMNAME("kernel_driver");
#endif /* !__drv_self_defined */
#endif /* CONFIG_BUILDING_KERNEL_CORE */



typedef struct {
	ElfW(Word) ht_nbuckts;      /* Total number of buckets. */
	ElfW(Word) ht_nchains;      /* Total number of symbols. */
	ElfW(Word) ht_table[1024];  /* [ht_nbuckts] Hash table. */
//	ElfW(Word) ht_chains[1024]; /* [ht_nchains] Hash chains. */
} ElfW(HashTable);


#ifdef CONFIG_BUILDING_KERNEL_CORE
#define DRIVER_CONST  /* nothing */
#else /* CONFIG_BUILDING_KERNEL_CORE */
#define DRIVER_CONST  const
#endif /* !CONFIG_BUILDING_KERNEL_CORE */

struct driver;
#define DRIVER_DLSECTION_FNORMAL 0x0000 /* Normal flags */
#define DRIVER_DLSECTION_FOWNED  0x0001 /* Section data is owned by the section descriptor. */
struct driver_section {
	WEAK refcnt_t          ds_refcnt;      /* Reference counter. */
	void                  *ds_data;        /* [0..ds_size][lock(WRITE_ONCE)]
	                                        * [owned_if(ds_sectflags & DRIVER_DLSECTION_FOWNED)]
	                                        * Memory mapping for the section's contents.
	                                        * NOTE: Set to `(void *)-1' when section data hasn't been loaded, yet. */
	size_t DRIVER_CONST    ds_size;        /* [const] Size of the section (in bytes) */
	size_t DRIVER_CONST    ds_entsize;     /* [const] Section entity size (or 0 if unknown) */
	uintptr_t DRIVER_CONST ds_link;        /* [const] Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t DRIVER_CONST ds_info;        /* [const] Index of another section that is linked by this one (or `0' if unused) */
	uintptr_t DRIVER_CONST ds_flags;       /* [const] ELF section flags (set of `SHF_*') */
	REF struct driver     *ds_module;      /* [1..1][const] Reference to the associated module */
	REF struct driver_section
	                      *ds_dangling;    /* [0..1][lock(INTERN(dangling-sections-lock)))]
	                                        * Chain of dangling sections. (sections that can be unloaded)
	                                        * NOTE: Set to `(REF struct driver_section *)-1' if the section isn't dangling. */
	u16       DRIVER_CONST ds_sectflags;   /* [const] Section flags (Set of `DRIVER_DLSECTION_F*') */
	u16       DRIVER_CONST ds_index;       /* [const] Index of this section. */
};


#define DRIVER_FLAG_NORMAL       0x0000 /* Normal (initial) driver flags. */
#define DRIVER_FLAG_DEPLOADING   0x0001 /* Driver dependencies have been loaded / are being loaded */
#define DRIVER_FLAG_DEPLOADED    0x0002 /* Driver dependencies have been loaded */
#define DRIVER_FLAG_RELOCATING   0x0004 /* Driver relocations have been applied / are being been applied */
#define DRIVER_FLAG_RELOCATED    0x0008 /* Driver relocations have been applied */
#define DRIVER_FLAG_INITIALIZING 0x0010 /* Initializers (constructors) have been executed / are currently being executed. */
#define DRIVER_FLAG_INITIALIZED  0x0020 /* Initializers (constructors) have been executed. */
#define DRIVER_FLAG_FINALIZING   0x0040 /* Finalizers (destructors) have been executed / are currently being executed. */
#define DRIVER_FLAG_FINALIZED    0x0080 /* Finalizers (destructors) have been executed.
                                         * NOTE: This flag also means that the driver is no longer
                                         *       registered as part of the current driver state,
                                         *       meaning that the current driver state no longer
                                         *       holds a reference to the driver in question.
                                         *       Though an older, dangling driver state might still
                                         *       hold such a reference.
                                         * NOTE: When this flag is set, additional driver sections can no
                                         *       longer be mapped into memory! */
#define DRIVER_FLAG_FINALIZED_C  0x0100 /* INTERNAL: Finalizer callbacks were executed (and dependencies were decref()'ed),
                                         *           but other finalization components are still missing. */

struct task;
struct driver_fde_cache_node;

struct driver {
	WEAK refcnt_t             d_refcnt;     /* Reference counter. */
	char const  *DRIVER_CONST d_name;       /* [1..1][const] Name of the driver (the module's `DT_SONAME' tag) */
	char const  *DRIVER_CONST d_filename;   /* [0..1][lock(WRITE_ONCE)][owned]
	                                         * Absolute (relative to `vfs_kernel') filename of the driver,
	                                         * or `NULL' if the driver was loaded as a multiboot module.
	                                         * NOTE: If the filename is needed at a later point in time, the
	                                         *       kernel will search for a driver file matching `d_name'
	                                         *       within the driver library path list. */
	REF struct regular_node *DRIVER_CONST
	                          d_file;       /* [0..1][const] The file-INode from which this driver was loaded, or
	                                         *              `NULL' if the driver was loaded as a multiboot module. */
	char        *DRIVER_CONST d_cmdline;    /* [1..1][const][owned] Driver commandline (in the form of "foo\0bar\0baz\0\0") */
	size_t       DRIVER_CONST d_argc;       /* [const] Driver commandline (in the form of "foo\0bar\0baz\0\0") */
	char       **DRIVER_CONST d_argv;       /* [1..1][1..d_argc][const][owned] Driver argument vector (terminated by a NULL-pointer) */
	uintptr_t                 d_flags;      /* Driver flags (Set of `DRIVER_FLAG_*') */
	struct task              *d_initthread; /* [?..1] Used internally to identify the thread responsible for an in-progress initialization.
	                                         * This in turn is used to perform special handling when a driver constructor calls `driver_finalize()',
	                                         * which essentially allows the driver to be unloaded prematurely.
	                                         * Additionally, this also allows `driver_initialize()' to be called from constructors without
	                                         * having to be afraid about causing a dead-lock when waiting for one-self to finish initialization. */

	/* Module load location. */
	uintptr_t    DRIVER_CONST d_loadaddr;   /* [const] Load address of the module. */
	uintptr_t    DRIVER_CONST d_loadstart;  /* [const] Lowest address mapped by this module (already adjusted for `d_loadaddr'). */
	uintptr_t    DRIVER_CONST d_loadend;    /* [const] Greatest address mapped by this module (already adjusted for `d_loadaddr'). */

	/* Special module section binding. */
	byte_t const *DRIVER_CONST d_eh_frame_start; /* [0..1][<= d_eh_frame_end][const]
	                                              * Starting pointer for the .eh_frame section */
	byte_t const *DRIVER_CONST d_eh_frame_end;   /* [0..1][>= d_eh_frame_start][const]
	                                              * Ending pointer for the .eh_frame section */
	struct driver_fde_cache_node *d_eh_frame_cache; /* [0..1][lock(d_eh_frame_cache)] ATREE-head for an eh-frame cache. */
	struct atomic_rwlock          d_eh_frame_cache_lock;  /* Lock for `d_eh_frame_cache' */
	uintptr_t        DRIVER_CONST d_eh_frame_cache_semi0; /* [const] SEMI0 for the eh_frame cache */
	unsigned int     DRIVER_CONST d_eh_frame_cache_leve0; /* [const] LEVEL0 for the eh_frame cache */


	/* Driver dependencies. */
	size_t       DRIVER_CONST d_depcnt;     /* [const] Number of dependencies of this driver. */
	REF struct driver *DRIVER_CONST *DRIVER_CONST
	                          d_depvec;     /* [0..1][valid_if(!DRIVER_FLAG_FINALIZED)][0..d_depcnt][const]
	                                         * [if(d_depcnt == 0,[== NULL])][const_if(d_depcnt == 0)]
	                                         * Vector of driver dependencies.
	                                         * NOTE: References to drivers in this vector are cleared
	                                         *       after module finalizers have been executed */

	/* The driver's .dynamic section, and derivatives (.dynsym + .dynstr). */
	size_t       DRIVER_CONST d_dyncnt;     /* [const] Number of dynamic definition headers. */
	ElfW(Dyn) const *DRIVER_CONST
	                          d_dynhdr;     /* [0..d_dyncnt][const] Vector of dynamic definition entries. */
	ElfW(Sym) const *DRIVER_CONST
	                          d_dynsym_tab; /* [0..1][const] Vector of dynamic symbols defined by this module.
	                                         * HINT: If also non-NULL, the number of symbols is `d_hashtab->ht_nchains' */
	size_t       DRIVER_CONST d_dynsym_cnt; /* [const] Number of dynamic symbols defined by this driver. */
	ElfW(HashTable) const *DRIVER_CONST
	                          d_hashtab;    /* [0..1][const] Symbol hash table. */
	char const  *DRIVER_CONST d_dynstr;     /* [0..1][const] Dynamic string table. */
	char const  *DRIVER_CONST d_dynstr_end; /* [0..1][const] End of the dynamic string table. */

	/* Named data sections of the module (for use with `dllocksection()'). */
	ElfW(Off)                 d_shoff;      /* [const] File offset to section headers. */
	ElfW(Half)                d_shstrndx;   /* [const] Index of the section header names section. */
	ElfW(Half)                d_shnum;      /* [const] (Max) number of section headers. */
	ElfW(Shdr) const         *d_shdr;       /* [lock(WRITE_ONCE)][0..d_shnum][owned] Vector of section headers (or `NULL' if not loaded). */
	struct atomic_rwlock      d_sections_lock; /* Lock for `d_sections' */
	struct driver_section   **d_sections;   /* [0..1][weak][0..d_shnum][owned][lock(d_sections_lock)] Vector of locked sections. */
	struct driver_section    *d_deadsect;   /* [0..1][lock(ATOMIC)] Chain of dead sections (cleared whenever `d_sections_lock' is locked) */
	REF struct driver_section*d_dangsect;   /* [0..1][lock(d_sections_lock)] Chain of dangling sections (sections no longer referenced, but kept in memory for caching) */
	char const               *d_shstrtab;   /* [lock(WRITE_ONCE)][0..1][owned] Section headers name table (or `NULL' if not loaded). */
	char const               *d_shstrtab_end;/* [lock(WRITE_ONCE)][0..1] End pointer for the `d_shstrtab' section (points to a NUL-character). */

	/* Module program headers */
	ElfW(Half)   DRIVER_CONST d_phnum;      /* [const][valid_if(!DRIVER_FLAG_FINALIZED)][!0] (Max) number of program headers. */
	ElfW(Phdr)   DRIVER_CONST d_phdr[];     /* [const][valid_if(!DRIVER_FLAG_FINALIZED)][d_phnum] Vector of program headers. */
};

#define driver_isfinalizing(self)                            \
	(__hybrid_atomic_load(self->d_flags, __ATOMIC_ACQUIRE) & \
	 (DRIVER_FLAG_FINALIZING | DRIVER_FLAG_FINALIZED | DRIVER_FLAG_FINALIZED_C))

/* A driver descriptor for the kernel core */
DATDEF struct driver kernel_driver;

FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL driver_section_destroy)(struct driver_section *__restrict self);
FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL driver_destroy)(struct driver *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct driver_section, ds_refcnt, driver_section_destroy)
DEFINE_REFCOUNT_FUNCTIONS(struct driver, d_refcnt, driver_destroy)

struct regular_node;
struct path;
struct directory_entry;

struct driver_state {
	/* Descriptor for a lock-less snapshot of the current loaded-driver state. */
	WEAK refcnt_t                                           ds_refcnt;   /* Reference counter. */
	size_t                                     DRIVER_CONST ds_count;    /* [const] Number of loaded drivers. */
	COMPILER_FLEXIBLE_ARRAY(REF struct driver *DRIVER_CONST,ds_drivers); /* [1..1][const][ds_count] Vector of loaded drivers. */
};

FUNDEF NOBLOCK NONNULL((1)) void NOTHROW(KCALL driver_state_destroy)(struct driver_state *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct driver_state, ds_refcnt, driver_state_destroy)

/* Return a snapshot for the current state of loaded drivers. */
FUNDEF NOBLOCK WUNUSED ATTR_RETNONNULL
REF struct driver_state *NOTHROW(KCALL driver_get_state)(void);


struct driver_library_path_string {
	WEAK refcnt_t                              dlp_refcnt; /* Reference counter. */
	COMPILER_FLEXIBLE_ARRAY(char DRIVER_CONST, dlp_path);  /* Path string. */
};

#ifdef __OMIT_KMALLOC_CONSTANT_P_WRAPPERS
DEFINE_REFCOUNT_FUNCTIONS(struct driver_library_path_string, dlp_refcnt, __os_free);
#else /* __OMIT_KMALLOC_CONSTANT_P_WRAPPERS */
DEFINE_REFCOUNT_FUNCTIONS(struct driver_library_path_string, dlp_refcnt, kfree);
#endif /* !__OMIT_KMALLOC_CONSTANT_P_WRAPPERS */


/* [1..1] The current driver library path.
 * This path is a ':'-separated list of UNIX-style pathnames
 * that are used to resolve dependencies of kernel driver modules.
 * By default, this string is simply set to "/os/drivers" */
DATDEF ATOMIC_REF(struct driver_library_path_string) driver_library_path;


#define DRIVER_INSMOD_FLAG_NORMAL 0x0000 /* Normal insmod flags. */
#define DRIVER_INSMOD_FLAG_NOINIT 0x0001 /* Don't initialize the driver (don't load dependencies, apply relocations, or run initializers).
                                          * When this flag is set, the caller must run `driver_initialize()'
                                          * at some point in the future in order to initialize the driver.
                                          * NOTE: This flag is mainly intended to allow for inter-driver
                                          *       dependencies when multiple drivers are loaded from the
                                          *       bootloader, in which case all drivers must be loaded
                                          *       first, before they can detect each other as dependencies. */


/* Load a new driver into the kernel, either from the
 * specified filesystem location, or via a raw data blob.
 * @param: driver_inode:       The INode from which to load the driver.
 * @param: driver_path:        The parent directory path for `driver_inode'
 * @param: driver_dentry:      The directory entry of `driver_inode' within `driver_path'
 * @param: driver_cmdline:     The commandline to-be passed to the driver, or `NULL'
 * @param: pnew_driver_loaded: When non-NULL, write true to this pointer when the returned
 *                             driver was just newly loaded. - Otherwise, write false.
 * @return: * :                A reference to the freshly loaded driver. */
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct driver *KCALL
driver_insmod_file(struct regular_node *__restrict driver_inode,
                   struct path *driver_path,
                   struct directory_entry *driver_dentry,
                   USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                   __BOOL *pnew_driver_loaded DFL(__NULLPTR),
                   unsigned int flags DFL(DRIVER_INSMOD_FLAG_NORMAL))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct driver *KCALL
driver_insmod_blob(USER CHECKED byte_t *base, size_t num_bytes,
                   USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                   __BOOL *pnew_driver_loaded DFL(__NULLPTR),
                   unsigned int flags DFL(DRIVER_INSMOD_FLAG_NORMAL))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);

/* Load a driver as a dependency of another.
 *   #1: When `driver_name' starts with a `/'-character, interpret
 *       it as an absolute filename and search for an existing
 *       driver with that name before using it as a filesystem
 *       location relative to `vfs_kernel' from which to then try
 *       and load the driver.
 *   #2: Search an existing driver with the name `driver_name'
 *   #3: Using `driver_library_path.get()', search for an existing driver with the
 *       filename `${LIB_PATH}/{driver_name}' (The / only being added if needed)
 *   #4: Using `driver_library_path.get()', form filesystem names the same
 *       was as already done in STEP #3, but this time use the strings as
 *       file names relative to `vfs_kernel'
 */
FUNDEF WUNUSED ATTR_RETNONNULL REF struct driver *KCALL
driver_insmod(USER CHECKED char const *driver_name,
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR),
              unsigned int flags DFL(DRIVER_INSMOD_FLAG_NORMAL))
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR, E_FSERROR);


#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED ATTR_RETNONNULL NONNULL((1)) REF struct driver *KCALL
driver_insmod(struct regular_node *__restrict driver_inode,
              struct path *__restrict driver_path,
              struct directory_entry *__restrict driver_dentry,
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR),
              unsigned int flags DFL(DRIVER_INSMOD_FLAG_NORMAL))
		ASMNAME("driver_insmod_file")
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
FUNDEF WUNUSED ATTR_RETNONNULL REF struct driver *KCALL
driver_insmod(USER CHECKED byte_t *base, size_t num_bytes,
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR),
              unsigned int flags DFL(DRIVER_INSMOD_FLAG_NORMAL))
		ASMNAME("driver_insmod_blob")
		THROWS(E_SEGFAULT, E_NOT_EXECUTABLE, E_BADALLOC, E_IOERROR);
}
#endif /* __cplusplus */



#ifdef __INTELLISENSE__
FUNDEF NOBLOCK WUNUSED NONNULL((1)) char const *
NOTHROW(KCALL driver_getname)(struct driver *__restrict self);
#else
#define driver_getname(self) ((self)->d_name)
#endif

/* Return the INode/filename of a given driver (which is
 * lazily loaded for drivers loaded via the kernel commandline) */
FUNDEF WUNUSED NONNULL((1)) struct regular_node *KCALL
driver_getfile(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC);
FUNDEF WUNUSED NONNULL((1)) char const *KCALL
driver_getfilename(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC);


/* Lazily allocate if necessary, and return the vector of section headers for `self'
 * NOTE: On success, this function guaranties that the following fields have been initialized:
 *  - self->d_shdr
 * @return: * :   Returns `self->d_shdr'
 * @return: NULL: Failed to load the section headers vector (the driver
 *                file wasn't found, or doesn't contain any sections) */
FUNDEF WUNUSED NONNULL((1)) ElfW(Shdr) const *KCALL
driver_getshdrs(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC);

/* Lazily allocate if necessary, and return the section header string table for `self'
 * @return: * :   Returns `self->d_shstrtab'
 * @return: NULL: Failed to load the section headers string table (the driver
 *                file wasn't found, or doesn't contain any sections) */
FUNDEF WUNUSED NONNULL((1)) char const *KCALL
driver_getshstrtab(struct driver *__restrict self)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC);

/* Return the section header associated with a given `name'
 * @return: * :   Returns a pointer to one of `&self->d_shdr[*]'
 * @return: NULL: No section exists that matches the given `name'
 * @return: NULL: Failed to load the section headers string table (the driver
 *                file wasn't found, or doesn't contain any sections) */
FUNDEF WUNUSED NONNULL((1)) ElfW(Shdr) const *KCALL
driver_getsection(struct driver *__restrict self,
                  USER CHECKED char const *name)
		THROWS(E_IOERROR, E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT);



/* Initialize the given driver.
 *  #1: Load driver dependencies.
 *  #2: Apply driver relocations.
 *  #3: Execute driver initializers. */
FUNDEF NONNULL((1)) __BOOL KCALL
driver_initialize(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, E_FSERROR, E_NOT_EXECUTABLE);


/* Finalize the given driver.
 *  #1: Execute destructor callbacks.
 *  #2: Decref (and ATOMIC_XCH(NULL)) each module from the dependency vector.
 * NOTE: In case the driver is being finalized right now, wait for another
 *       thread doing the finalization to either complete, or abort.
 * @return: true:  Successfully finalized the driver.
 * @return: false: The driver had already been finalized (also a success-case). */
FUNDEF NONNULL((1)) __BOOL KCALL driver_finalize(struct driver *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);


#define DRIVER_DELMOD_FLAG_NORMAL  0x0000 /* Normal delmod flags. */
#define DRIVER_DELMOD_FLAG_DEPEND  0x0001 /* Also delete drivers that have dependencies on `self' */
/* Try to unload a driver module.
 * This function will:
 *   - invoke module finalizers (if they haven't been already)
 *   - DRIVER_DELMOD_FLAG_DEPEND:
 *         Search for other modules make use of `self' through
 *         dependencies and finalize all of them such that their
 *         dependency vectors can be cleared, including the
 *         contained references to `self'
 * @param: self:   The driver to try to unload.
 * @param: flags:  Set of `DRIVER_DELMOD_FLAG_*'
 * @return: true:  Successfully unloaded the driver and inherited the reference to `self'
 * @return: false: Failed to unload the driver (there are still unaccounted
 *                 references to it other than the reference given through `self')
 *                 In this case, this function has _NOT_ inherited the reference to `self' */
FUNDEF WUNUSED NONNULL((1)) __BOOL KCALL
driver_try_decref_and_delmod(/*inherit(on_success)*/ REF struct driver *__restrict self,
                             unsigned int flags DFL(DRIVER_DELMOD_FLAG_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);



#define DRIVER_DELMOD_SUCCESS  0 /* Successfully unloaded the driver. */
#define DRIVER_DELMOD_UNKNOWN  1 /* The specified driver could not be found. */
#define DRIVER_DELMOD_INUSE    2 /* The specified driver has unaccounted references.
                                  * NOTE: in this case, driver finalizers were still executed,
                                  *       meaning that in all likelihood, the unaccounted references
                                  *       stem from another thread currently holding a reference to
                                  *       the driver, such as when trying to resolve addr2line for
                                  *       a static pointer apart of the driver's binary image. */

/* Unload a driver from the kernel core.
 * @param: driver_name: The name of the driver, or its
 *                      filename (when the first character is `/')
 * @param: flags: Set of `DRIVER_DELMOD_FLAG_*'
 * @return: * :   One of `DRIVER_DELMOD_*' */
FUNDEF NONNULL((1)) unsigned int KCALL
driver_delmod(USER CHECKED char const *driver_name,
              unsigned int flags DFL(DRIVER_DELMOD_FLAG_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF NONNULL((1)) unsigned int KCALL
driver_delmod_inode(struct inode *__restrict driver_node,
                    unsigned int flags DFL(DRIVER_DELMOD_FLAG_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);

#ifdef __cplusplus
extern "C++" {
FUNDEF NONNULL((1)) unsigned int KCALL
driver_delmod(struct inode *__restrict driver_node,
              unsigned int flags DFL(DRIVER_DELMOD_FLAG_NORMAL))
		ASMNAME("driver_delmod_inode")
		THROWS(E_WOULDBLOCK);
}
#endif /* __cplusplus */




/* Simplified variant of `driver_symbol_ex()'
 * This function returns `NULL' on error, however thus also
 * creates ambiguity for symbols defined as SHN_ABS:0. */
FUNDEF WUNUSED NONNULL((1)) void *KCALL
driver_symbol(struct driver *__restrict self,
              /*in*/ USER CHECKED char const *name,
              /*out*/ size_t *psymbol_size DFL(__NULLPTR))
		THROWS(E_SEGFAULT, ...);


/* Lookup a symbol exported from a given driver `self'
 * HINT: This function will also resolve special driver symbols
 * @return: true:  The symbol was found.
 * @return: false: The symbol could not be found. */
FUNDEF WUNUSED NONNULL((1, 5, 6)) __BOOL KCALL
driver_symbol_ex(struct driver *__restrict self,
                 /*in*/ USER CHECKED char const *name,
                 /*out*/ void **psymbol_addr,
                 /*out*/ size_t *psymbol_size,
                 /*in|out*/ uintptr_t *__restrict phash_elf,
                 /*in|out*/ uintptr_t *__restrict phash_gnu)
		THROWS(E_SEGFAULT, ...);

/* Check if the given driver `self' is exporting a symbol that
 * contains the given `driver_relative_address', or it exports a symbol
 * with an undefined size that begins before `driver_relative_address',
 * but isn't defined within the SHN_ABS section, nor is followed by another
 * symbol that does have a defined size value.
 * NOTE: This function cannot be used to reverse special driver symbols
 * WARNING: This operation in O(n) | n = number of symbols exported by `self'
 * @return: * :                      The NUL-terminated name of the symbol.
 *                                   This pointer is valid as long as `self' isn't unloaded.
 * @return: NULL:                    No public symbol is defined for `driver_relative_address'
 *                                   Note however that the associated symbol may not necessarily
 *                                   have been made public by the associated driver. In this case,
 *                                   it may be possible to determine the symbol name by looking at
 *                                   the driver's debug data (s.a. `<libdebuginfo/addr2line.h>')
 * @param: driver_relative_address:  A module-relative pointer who's associated symbol should be located.
 * @param: psymbol_relative_address: When non-NULL, store the module-relative base address of the found symbol here.
 * @param: psymbol_size:             When non-NULL, store the size of the symbol here, or 0 if undefined. */
FUNDEF WUNUSED NONNULL((1)) char const *
NOTHROW(KCALL driver_symbol_at)(struct driver *__restrict self,
                                uintptr_t driver_relative_address,
                                uintptr_t *psymbol_relative_address,
                                size_t *psymbol_size);

/* Lookup a locally defined ELF symbol within `self'
 * WARNING: This function cannot be used with `&kernel_driver', as
 *          the kernel core itself implements a custom protocol for
 *          specifying which variables are exported. */
FUNDEF WUNUSED NONNULL((1, 3, 4)) ElfW(Sym) const *KCALL
driver_local_symbol(struct driver *__restrict self,
                    /*in*/ USER CHECKED char const *name,
                    /*in|out*/ uintptr_t *__restrict phash_elf,
                    /*in|out*/ uintptr_t *__restrict phash_gnu)
		THROWS(E_SEGFAULT);
#define DRIVER_SYMBOL_HASH_UNSET  ((uintptr_t)-1)

/* Same as `driver_symbol_at()', but returns the ELF symbol
 * WARNING: This function cannot be used with `&kernel_driver', as
 *          the kernel core itself implements a custom protocol for
 *          specifying which variables are exported. */
FUNDEF WUNUSED NONNULL((1)) ElfW(Sym) const *
NOTHROW(KCALL driver_local_symbol_at)(struct driver *__restrict self,
                                      uintptr_t driver_relative_address);


#ifdef __cplusplus
extern "C++" {
FORCELOCAL WUNUSED NONNULL((1)) __BOOL KCALL
driver_symbol_ex(struct driver *__restrict self,
                 /*in*/ USER CHECKED char const *name,
                 /*out*/ void **psymbol_addr,
                 /*out*/ size_t *psymbol_size DFL(__NULLPTR))
		THROWS(E_SEGFAULT, ...) {
	uintptr_t hash_elf,hash_gnu;
	hash_elf = hash_gnu = DRIVER_SYMBOL_HASH_UNSET;
	return driver_symbol_ex(self,
	                        name,
	                        psymbol_addr,
	                        psymbol_size,
	                       &hash_elf,
	                       &hash_gnu);
}
FORCELOCAL WUNUSED NONNULL((1)) ElfW(Sym) const *KCALL
driver_local_symbol(struct driver *__restrict self,
                    /*in*/ USER CHECKED char const *name)
		THROWS(E_SEGFAULT) {
	uintptr_t hash_elf,hash_gnu;
	hash_elf = hash_gnu = DRIVER_SYMBOL_HASH_UNSET;
	return driver_local_symbol(self,
	                           name,
	                          &hash_elf,
	                          &hash_gnu);
}
}
#endif /* __cplusplus */


#define DRIVER_SECTION_LOCK_FNORMAL   0x0000 /* Normal section locking flags. */
#define DRIVER_SECTION_LOCK_FINDEX    0x0001 /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define DRIVER_SECTION_LOCK_FNODATA   0x0002 /* Do not lock section data into memory, though if the section had already
                                                  * been loaded, then this flag is simply ignored. */
/* Lock a named section of a given driver into
 * memory and return a descriptor for that section.
 * @throws: E_SEGFAULT: Only here because `name' is USER
 * @return: * :   Reference to the section descriptor.
 *                This reference must be released with `decref(return)'
 * @return: NULL: The given driver `self' doesn't contain any section `name' */
FUNDEF WUNUSED NONNULL((1)) REF struct driver_section *KCALL
driver_section_lock(struct driver *__restrict self,
                    USER CHECKED char const *name,
                    unsigned int flags DFL(DRIVER_SECTION_LOCK_FNORMAL))
		THROWS(E_SEGFAULT, E_BADALLOC);

struct unwind_fde_struct;
/* Lookup the FDE descriptor for a given `absolute_pc', whilst trying to
 * make use of the FDE cache of `self'.
 * @return: * : One of `UNWIND_*' from <libunwind/api.h> */
FUNDEF NOBLOCK unsigned int
NOTHROW(KCALL driver_fde_find)(struct driver *__restrict self, void *absolute_pc,
                               struct unwind_fde_struct *__restrict result);

/* Try to clear the FDE cache of the given, or of all loaded drivers.
 * NOTE: Drivers who's caches cannot be locked are skipped.
 * @return: * : The total number of bytes of heap-memory released. */
FUNDEF NOBLOCK size_t NOTHROW(KCALL driver_clear_fde_cache)(struct driver *__restrict self);
FUNDEF NOBLOCK size_t NOTHROW(KCALL driver_clear_fde_caches)(void);

/* Invoke cache clear callbacks for each and every globally reachable
 * component within the entire kernel.
 * This function is called when the kernel has run out of physical/virtual
 * memory, or some other kind of limited, and dynamically allocatable resource.
 * @return: * : At least some amount of some kind of resource was released.
 *              In this case the caller should re-attempt whatever lead them
 *              to try and clear caches to reclaim resource (usually memory)
 * @return: 0 : Nothing was released/freed.
 *              In this case, the caller should indicate failure due to
 *              lack of some necessary resource. */
FUNDEF NOBLOCK size_t NOTHROW(KCALL system_clearcaches)(void);

/* multi-thread-corrected version of `system_clearcaches()'.
 * This function should always be used in favor of `system_clearcaches()', as it
 * solves the scenario of multiple threads calling `system_clearcaches()' at the
 * same time, in which case resources may only get freed by one thread, with the
 * other thread never getting informed about that fact.
 * In this case, `system_clearcaches()' would normally (and correctly I might add)
 * return `0' for some threads, since that thread really didn't release any resources.
 * However, the intended use of this function is inform a caller who just failed to
 * allocate some optional resource, that their resource may have become available,
 * and that they should try again (which is something that isn't fulfilled by the
 * regular `system_clearcaches()' in a multi-threaded environment)
 * That is where this function comes in:
 * >> void *my_alloc_tryhard() {
 * >>     void *result;
 * >>     result = my_alloc();
 * >>     if unlikely(!result) {
 * >>         uintptr_t cache_version;
 * >>         cache_version = 0;
 * >>         for (;;) {
 * >>             result = my_alloc();
 * >>             if (result)
 * >>                 break;
 * >>             if (!system_clearcaches_s(&cache_version))
 * >>                 break;
 * >>         }
 * >>     }
 * >>     return result;
 * >> }
 * WARNING: Do _NOT_ write to `*pversion' after a non-zero value was returned!
 *          In this case, re-attempt your allocation and upon failure, call
 *          `system_clearcaches_s()' again with an unmodified `*pversion' value.
 *          This function makes use of the version number for tracking how many
 *          more times the caller is allowed to make an attempt before giving up.
 * @return: * : At least some amount of some kind of resource (may have) been
 *              released by some thread since the last time the function was called.
 *              In this case the caller should re-attempt whatever lead them
 *              to try and clear caches to reclaim resource (usually memory)
 * @return: 0 : Nothing was released/freed.
 *              In this case, the caller should indicate failure due to
 *              lack of some necessary resource. */
FUNDEF NOBLOCK size_t NOTHROW(KCALL system_clearcaches_s)(uintptr_t *__restrict pversion);

/* Called as part of `system_clearcaches()': Trim standard kernel heaps.
 * @return: * : The total number of trimmed bytes. */
FUNDEF NOBLOCK size_t NOTHROW(KCALL system_trimheaps)(void);


#ifdef CONFIG_BUILDING_KERNEL_CORE
#ifndef DEFINE_SYSTEM_CACHE_CLEAR
/* >> NOBLOCK size_t NOTHROW(KCALL func)(void);
 * Define a function that should be called when `system_clearcaches()' is invoked. */
#define DEFINE_SYSTEM_CACHE_CLEAR(func) DEFINE_CALLBACK(".rodata.cold.callback.system_clearcaches", func)
#endif /* !DEFINE_SYSTEM_CACHE_CLEAR */
#endif /* CONFIG_BUILDING_KERNEL_CORE */


/* Try to lookup a driver stored at a given address.
 * If no such driver exists, return NULL */
FUNDEF NOBLOCK WUNUSED REF struct driver *
NOTHROW(FCALL driver_at_address)(void const *static_pointer);

/* Try to lookup a driver with a given `driver_name'.
 * If no such driver exists, return NULL */
FUNDEF WUNUSED NONNULL((1)) REF struct driver *FCALL
driver_with_name(USER CHECKED char const *driver_name) THROWS(E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) REF struct driver *FCALL
driver_with_namel(USER CHECKED char const *driver_name, size_t driver_name_len) THROWS(E_SEGFAULT);
FUNDEF WUNUSED NONNULL((1)) REF struct driver *FCALL
driver_with_filename(USER CHECKED char const *driver_filename) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver *
NOTHROW(FCALL driver_with_file)(struct regular_node *__restrict driver_file);


/* Callbacks invoked when a new driver is loaded. */
DATDEF CALLBACK_LIST(void KCALL(struct driver *)) driver_loaded_callbacks;

/* Callbacks invoked when a driver is finalized. */
DATDEF CALLBACK_LIST(void KCALL(struct driver *)) driver_finalized_callbacks;

/* Callbacks invoked just before a driver is unloaded. */
DATDEF CALLBACK_LIST(NOBLOCK void /*NOEXCEPT*/ KCALL(struct driver *)) driver_unloaded_callbacks;

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DRIVER_H */
