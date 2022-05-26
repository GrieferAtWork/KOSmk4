/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DRIVER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DRIVER_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/malloc.h>
#include <kernel/mman/module.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>

#include <kos/aref.h>
#include <kos/exec/elf.h>

#ifdef __WANT_DRIVER__d_internals
#include <hybrid/sync/atomic-rwlock.h>

#include <kos/lockop.h>
#endif /* __WANT_DRIVER__d_internals */

#ifdef __CC__
DECL_BEGIN


/* Special, per-driver symbols:
 *
 *   - extern struct driver drv_self;         // Current driver
 *   - extern byte_t        drv_loadaddr[];   // == drv_self.md_loadaddr
 *   - extern byte_t        drv_loadmin[];    // == drv_self.md_loadmin
 *   - extern byte_t        drv_loadmax[];    // == drv_self.md_loadmax
 *   - extern char const    drv_name[];       // == drv_self.d_name
 *   - extern struct mfile *drv_file;         // == driver_getfile(self)
 *   - extern char          drv_cmdline[];    // == drv_self.d_cmdline
 *   - extern size_t        drv_argc;         // == &drv_self.d_argc
 *   - extern char         *drv_argv[];       // == drv_self.d_argv
 *
 * These symbols can be referenced from inside of drivers  just
 * like any other symbol can be, and will be resolved to  point
 * at the relevant address as relocations are performed for the
 * associated driver.
 * As such, these symbols are useful for static initialization
 * of control structures.
 *
 * Additionally, driver commandline arguments can be accessed
 * via custom-named symbols:
 *
 *   - char   drv_arg$foo$s$bar[];        // == EXISTS("foo=$value") ? "$value" : "bar"
 *   - byte_t drv_arg$foo$x$00000000[4];  // == EXISTS("foo=$value") ? tohex("$value") : tohex("00000000")
 *   - bool   drv_arg$foo;                // == EXISTS("foo")        ? true : false
 *   - int    drv_arg$foo$d$42;           // == EXISTS("foo=$value") ? atoi("$value") : atoi("42")
 *   - u32    drv_arg$foo$I32u$42;        // == EXISTS("foo=$value") ? atoi("$value") : atoi("42")
 *
 * *NOTE: The  tohex() function is fairly simple, in that
 *        it will silently skip all non-xdigit characters
 *        during parsing!
 *
 * The format for these symbols is:
 *    "drv_arg$" <argument_name> "$" <fmt_spec> ["$" <default_value>]
 *
 *    <argument_name>: The  name  of   the  argument  in   question.
 *                     For this purpose, the driver's argv vector is
 *                     scanned  for  arguments "<argument_name>=..."
 *                     and "<argument_name>:...", where "..." is the
 *                     value that will be interpreted as the initial
 *                     assignment  for   the  pointed-to   location.
 *
 *    <fmt_spec>:      A printf-style  format  specifier  that  describes
 *                     what the symbol should point to. For this purpose,
 *                     you can specify 1  of 4 different encoding  types:
 *                       - signed integer:   [LENGTH_PREFIX] "d"
 *                       - unsigned integer: [LENGTH_PREFIX] "u"
 *                       - hex-blob:         "x"
 *                       - string:           "s"
 *                     Where  `LENGTH_PREFIX' is one of ""; "h", "hh",
 *                     "l", "ll", "I", "I8", "I16", "I32", "I64", "z",
 *                     "t", "L", "j"
 *                     In the case  of hex-blob,  a <default_value>  is
 *                     required, and (via the # of hex-digit characters
 *                     contained), specifies the size of the pointed-to
 *                     blob.
 *
 *    <default_value>: Default initializer  for  the  argument  value.
 *                     When the driver's  commandline doesn't  contain
 *                     <argument_name>, then act as though an argument
 *                     "<argument_name>=<default_value>" had  actually
 *                     been given.
 *                     When no <default_value> is given, and the argument
 *                     isn't given on  the driver  commandline, then  the
 *                     pointed-to blob is simply zero-initialized.
 *
 * Or alternatively:
 *    "drv_arg$" <argument_name>
 * which is a special case that forms a variable which points
 * at a non-zero boolean if <argument_name> exists, and at  a
 * zero-boolean if it does exist.
 *
 * Note that all pointed-to symbol locations are always read/
 * write to the driver that uses them.
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
	ElfW(Shdr) const     *ds_shdr;     /* [1..1][const] Section header. */
	byte_t               *ds_addr;     /* [0..1][lock(WRITE_ONCE)] Section buffer address.
	                                    * Owned for non-`SHF_ALLOC' section. */
	byte_t               *ds_infladdr; /* [0..1][lock(WRITE_ONCE)] Inflated section address. */
	size_t                ds_inflsize; /* [0..1][lock(WRITE_ONCE)] Inflated section size. */
};

#if !defined(__cplusplus) || defined(__WANT_DRIVER_SECTION_ds_sect)
#define __driver_section_as_module_section(self)  (&(self)->ds_sect)
#define __driver_section_destroy(self)    module_section_destroy(&(self)->ds_sect)
#define __driver_section_refcnt(self)     (self)->ds_sect.ms_refcnt
DEFINE_REFCNT_FUNCTIONS_P(struct driver_section, __driver_section_refcnt, __driver_section_destroy)
#else /* !__cplusplus || __WANT_DRIVER_SECTION_ds_sect */
#define __driver_section_as_module_section /* nothing */
#endif /* __cplusplus && !__WANT_DRIVER_SECTION_ds_sect */


#ifndef __elfw_hashtable_defined
#define __elfw_hashtable_defined
typedef struct elfW(hashtable) {
	ElfW(Word) ht_nbuckts;       /* # of buckets. */
	ElfW(Word) ht_nchains;       /* # of symbols. */
	ElfW(Word) ht_table[1024];   /* [ht_nbuckts] Hash table. */
/*	ElfW(Word) ht_chains[1024];   * [ht_nchains] Hash chains. */
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

struct driver_section;
#ifndef __driver_section_awref_defined
#define __driver_section_awref_defined
AWREF(driver_section_awref, driver_section);
#endif /* !__driver_section_awref_defined */

/* NOTE: Driver states are only allowed to transition as follows:
 *
 *  [initial]                       --> DRIVER_STATE_INIT               // Initial state
 *
 *  DRIVER_STATE_INIT               --> DRIVER_STATE_INIT_DEPS          // Being initialization
 *  DRIVER_STATE_INIT               --> DRIVER_STATE_KILL               // When `driver_finalize()' is called
 *
 *  DRIVER_STATE_INIT_DEPS          --> DRIVER_STATE_INIT_RELO          // Upon success
 *  DRIVER_STATE_INIT_DEPS          --> DRIVER_STATE_KILL               // If loading dependencies fails
 *  DRIVER_STATE_INIT_DEPS          --> DRIVER_STATE_FINI_RDPS          // When `driver_finalize()' is called by the same thread
 *
 *  DRIVER_STATE_INIT_RELO          --> DRIVER_STATE_INIT_CT_PREINITARR // Upon success
 *  DRIVER_STATE_INIT_RELO          --> DRIVER_STATE_FINI_DEPS          // If applying relocations fails
 *  DRIVER_STATE_INIT_RELO          --> DRIVER_STATE_FINI_RDPS          // When `driver_finalize()' is called by the same thread
 *
 *  DRIVER_STATE_INIT_CT_PREINITARR --> DRIVER_STATE_INIT_CT_INITARR    // Upon success
 *  DRIVER_STATE_INIT_CT_PREINITARR --> DRIVER_STATE_FINI_DT_FINIARR    // If a ctor throws an exception
 *  DRIVER_STATE_INIT_CT_PREINITARR --> DRIVER_STATE_FINI_DT_FINIARR    // When `driver_finalize()' is called by the same thread
 *
 *  DRIVER_STATE_INIT_CT_INITARR    --> DRIVER_STATE_INIT_CT_INIT       // Upon success
 *  DRIVER_STATE_INIT_CT_INITARR    --> DRIVER_STATE_FINI_DT_FINIARR    // If a ctor throws an exception
 *  DRIVER_STATE_INIT_CT_INITARR    --> DRIVER_STATE_FINI_DT_FINIARR    // When `driver_finalize()' is called by the same thread
 *
 *  DRIVER_STATE_INIT_CT_INIT       --> DRIVER_STATE_LOADED             // Upon success
 *  DRIVER_STATE_INIT_CT_INIT       --> DRIVER_STATE_FINI_DT_FINI       // If a ctor throws an exception
 *  DRIVER_STATE_INIT_CT_INIT       --> DRIVER_STATE_FINI_DT_FINI       // When `driver_finalize()' is called by the same thread
 *
 *  DRIVER_STATE_LOADED             --> DRIVER_STATE_FINI_DT_FINI       // When `driver_finalize()' is called
 *
 *  DRIVER_STATE_FINI_DT_FINI       --> DRIVER_STATE_FINI_DT_FINIARR    // Upon success
 *  DRIVER_STATE_FINI_DT_FINI       --> DRIVER_STATE_FAIL_DT_FINI       // If the destructor throws an exception
 *
 *  DRIVER_STATE_FAIL_DT_FINI       --> DRIVER_STATE_FINI_DT_FINI       // When `driver_finalize()' is called again
 *
 *  DRIVER_STATE_FINI_DT_FINIARR    --> DRIVER_STATE_FINI_UNBINDGLOB    // Upon success
 *  DRIVER_STATE_FINI_DT_FINIARR    --> DRIVER_STATE_FAIL_DT_FINIARR    // If the destructor throws an exception
 *
 *  DRIVER_STATE_FAIL_DT_FINIARR    --> DRIVER_STATE_FINI_DT_FINIARR    // When `driver_finalize()' is called again
 *
 *  DRIVER_STATE_FINI_UNBINDGLOB    --> DRIVER_STATE_FINI_DEPS          // Upon success
 *  DRIVER_STATE_FINI_UNBINDGLOB    --> DRIVER_STATE_FAIL_UNBINDGLOB    // If the destructor throws an exception
 *
 *  DRIVER_STATE_FAIL_UNBINDGLOB    --> DRIVER_STATE_FINI_UNBINDGLOB    // When `driver_finalize()' is called again
 *
 *  DRIVER_STATE_FINI_RDPS          --> DRIVER_STATE_FINI_DEPS          // Always
 *
 *  DRIVER_STATE_FINI_DEPS          --> DRIVER_STATE_KILL               // Always
 *
 *  DRIVER_STATE_KILL               --> DRIVER_STATE_DEAD               // When `md_refcnt' drops to `0'
 *
 * NOTE: Depending on state, drivers also hold a reference to  themselves.
 *       The reference loop formed by this is intentional, and is used  to
 *       prevent a driver from being destroyed before finalizers have been
 *       executed, thus preventing driver text being unloaded before  that
 *       point in time. */
#define DRIVER_STATE_INIT               0  /* [SELFREF] Currently loading driver dependencies. */
#define DRIVER_STATE_INIT_DEPS          1  /* [SELFREF] Currently loading driver dependencies. */
#define DRIVER_STATE_INIT_RELO          2  /* [SELFREF] Currently applying relocations. */
#define DRIVER_STATE_INIT_CT_PREINITARR 3  /* [SELFREF] Currently executing DT_PREINIT_ARRAY */
#define DRIVER_STATE_INIT_CT_INITARR    4  /* [SELFREF] Currently executing DT_INIT_ARRAY */
#define DRIVER_STATE_INIT_CT_INIT       5  /* [SELFREF] Currently executing DT_INIT */
#define DRIVER_STATE_LOADED             6  /* [SELFREF] Driver has been loaded, and is sitting in memory. */
#define DRIVER_STATE_FINI_DT_FINI       7  /* [SELFREF] Currently executing DT_FINI */
#define DRIVER_STATE_FAIL_DT_FINI       8  /* [SELFREF] Failed to execute DT_FINI */
#define DRIVER_STATE_FINI_DT_FINIARR    9  /* [SELFREF] Currently executing DT_FINI_ARRAY */
#define DRIVER_STATE_FAIL_DT_FINIARR    10 /* [SELFREF] Failed to execute DT_FINI_ARRAY */
#define DRIVER_STATE_FINI_UNBINDGLOB    11 /* [SELFREF] Currently unbinding global hooks */
#define DRIVER_STATE_FAIL_UNBINDGLOB    12 /* [SELFREF] Failed to unbind global hooks */
#define DRIVER_STATE_FINI_RDPS          13 /* [SELFREF] RecrusiveDePendencieS (used internally) */
#define DRIVER_STATE_FINI_DEPS          14 /* [SELFREF] Currently clearing driver dependencies. */
#define DRIVER_STATE_KILL               15 /* Driver was killed. */
#define DRIVER_STATE_DEAD               16 /* Driver `wasdestroyed() == true'. */

/* Signal broadcast whenever the `d_state' of any loaded driver changes. */
DATDEF struct sig driver_state_changed;

/* Return a pointer to a `struct sig' that is  broadcast
 * when the state of the given driver `self' is altered. */
#define driver_changesignal(self) (&driver_state_changed)

struct driver;

#ifndef __driver_axref_defined
#define __driver_axref_defined
AXREF(driver_axref, driver);
#endif /* !__driver_axref_defined */

#ifdef __WANT_DRIVER__d_internals
struct driver_fde_cache;
struct driver_argcash; /* Descriptor for a `drv_arg$...' symbol. */
#ifndef __driver_argcash_slist_defined
#define __driver_argcash_slist_defined
SLIST_HEAD(driver_argcash_slist, driver_argcash);
#endif /* !__driver_argcash_slist_defined */
#ifndef __mnode_slist_defined
#define __mnode_slist_defined
struct mnode;
SLIST_HEAD(mnode_slist, mnode);
#endif /* !__mnode_slist_defined */
#ifndef __module_section_slist_defined
#define __module_section_slist_defined
SLIST_HEAD(module_section_slist, module_section);
#endif /* !__module_section_slist_defined */
#endif /* __WANT_DRIVER__d_internals */


#define __driver_defined
struct driver
#if defined(__cplusplus) && !defined(__WANT_DRIVER_d_module)
    : module
#endif /* __cplusplus && !__WANT_DRIVER_d_module */
{
	/* [OVERRIDE(.md_mman, [1..1][== &mman_kernel][NOT(WEAK REF)])]
	 * iow: For `struct driver', the `md_mman' field is always set to
	 *      `mman_kernel', and doesn't contain any sort of reference! */
#if !defined(__cplusplus) || defined(__WANT_DRIVER_d_module)
	struct module                  d_module;     /* The underlying module. */
#endif /* !__cplusplus || __WANT_DRIVER_d_module */

	/* (weak) reference management for drivers:
	 *
	 *    (d_module.md_refcnt != 0)     ==>  DRIVER_IS_MAPPED               // Driver mnode mappings still exist
	 *    (d_module.md_refcnt != 0)     ==>  REF(d_module.md_weakrefcnt)    // Non-zero refcnt holds a weakref
	 *    (d_module.md_nodecount != 0)  ==>  REF(d_module.md_weakrefcnt)    // Non-zero node count holds a weakref
	 *
	 * When `md_nodecount' drops to 0:
	 *   - Simply `weakdecref()' the driver.
	 *     iow: The existence of memory mappings implies that the associated
	 *     driver  object must  still exist,  but not  necessarily that said
	 *     driver hasn't can't be destroyed  (note that destroying a  driver
	 *     includes the removal of all of its memory nodes!)
	 *
	 * When `md_refcnt' drops to 0:
	 *   - Remove all of the driver's still-loaded module sections from the
	 *     module section cache. Each section destroyed by this was holding
	 *     a weak reference to the associated driver which is dropped as  a
	 *     result of this.
	 *
	 *   - Search the kernel mman for mnodes that point back to the driver,
	 *     and unmap+remove them. As a result of this, `md_nodecount'  must
	 *     drop to `0' (unless it was already `0' to being which, which may
	 *     have been the case when all  mappings of the driver had  already
	 *     been munmap'd explicitly)
	 *     Once `md_nodecount' drops to `0', weakdecref_nokill() the driver,
	 *     as is the usual behavior for this happening.
	 *
	 *   - Once all mem-nodes have been removed, weakdecref() the driver a
	 *     (possibly) second time, which will most likely be the last weak
	 *     reference to be dropped, allowing the driver to be free'd
	 *
	 * When `md_weakrefcnt' drops to 0:
	 *   - Destroy all remaining members  that remained valid following  the
	 *     driver's destruction. Then simply `kfree()' the driver descriptor
	 *     itself and call it a day :)
	 */


	/* NOTE: The following members remain valid, even after `wasdestroyed(self)':
	 *    - d_module.md_refcnt          (always `0')
	 *    - d_module.md_weakrefcnt
	 *    - d_module.md_nodecount       (always `0')
	 *    - d_module.md_ops             (Though all operators other than `mo_free' are off-limits!)
	 *    - d_module.md_mman            (will still be `mman_kernel')
	 *    - d_module.md_loadaddr
	 *    - d_module.md_loadmin
	 *    - d_module.md_loadmax
	 *    - d_module.md_sizeof_pointer
	 *    - d_state                     (Either `DRIVER_STATE_DEAD' or `DRIVER_STATE_KILL')
	 * All other fields must be considered as `[valid_if(!wasdestroyed(self))]',
	 * and may no longer be accessed after that point in time! Additionally, the
	 * driver should be skipped if encountered in driver load-lists! */

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
	ElfW(Half)                     d_shstrndx;   /* [const] Index of the section header names section. */
	ElfW(Half)                     d_shnum;      /* [const] (Max) number of section headers. */
	ElfW(Shdr)                    *d_shdr;       /* [0..d_shnum][const][owned] Vector of section headers (or `NULL' if not loaded). */
	struct driver_section_awref   *d_sections;   /* [0..1][0..d_shnum][const][owned] Vector of locked sections. */
	char                          *d_shstrtab;   /* [0..1][const][owned] Section headers name table (or `NULL' if not loaded). */
	size_t                         d_shstrsiz;   /* [const] Section header name table size. */

	/* Special handling for the `.eh_frame' section. */
	byte_t const                  *d_eh_frame_start;      /* [0..1][<= d_eh_frame_end][const] Starting pointer for the `.eh_frame' section */
	byte_t const                  *d_eh_frame_end;        /* [0..1][>= d_eh_frame_start][const] Ending pointer for the `.eh_frame' section */
#ifdef __WANT_DRIVER__d_internals
	struct driver_fde_cache       *d_eh_frame_cache;      /* [0..1][lock(d_eh_frame_cache)] Tree for an `.eh_frame' lookup cache. */
	struct atomic_rwlock           d_eh_frame_cache_lock; /* Lock for `d_eh_frame_cache' */
	struct driver_argcash_slist    d_argcash;             /* [0..n][lock(d_eh_frame_cache_lock)][owned] Descriptors for `drv_arg$...' symbols. */
#else /* __WANT_DRIVER__d_internals */
	void                         *_d_intern1[3]; /* Used internally */
#endif /* !__WANT_DRIVER__d_internals */

	/* Driver runtime internal temporaries. */
#ifdef __WANT_DRIVER__d_internals
	union {
		Toblockop(mman)            _d_mm_lop;     /* Used internally */
		Tobpostlockop(mman)        _d_mm_postlop; /* Used internally */
		struct lockop              _d_lop;        /* Used internally */
		struct postlockop          _d_postlop;    /* Used internally */
	};
	union {
		struct task               *_d_initthread; /* The thread currently performing init/fini for states:
		                                           *  - DRIVER_STATE_INIT_DEPS
		                                           *  - DRIVER_STATE_INIT_RELO
		                                           *  - DRIVER_STATE_INIT_CT_PREINITARR
		                                           *  - DRIVER_STATE_INIT_CT_INITARR
		                                           *  - DRIVER_STATE_INIT_CT_INIT
		                                           *  - DRIVER_STATE_FINI_DT_FINI
		                                           *  - DRIVER_STATE_FINI_DT_FINIARR
		                                           *  - DRIVER_STATE_FINI_UNBINDGLOB
		                                           *  - DRIVER_STATE_FINI_RDPS */
		struct mnode_slist         _d_deadnodes;  /* Used internally by `DRIVER_STATE_FINI_TEXT' */
		struct module_section_slist _d_deadsect;  /* Used internally */
	};
#else /* __WANT_DRIVER__d_internals */
	void                          *_d_intern2[3]; /* Used internally */
#endif /* !__WANT_DRIVER__d_internals */

	/* Driver program headers */
	ElfW(Half)                     d_phnum;      /* [!0][const] (Max) number of program headers. */
	byte_t                        _d_pad1[sizeof(void *) - sizeof(ElfW(Half))];
	COMPILER_FLEXIBLE_ARRAY(ElfW(Phdr), d_phdr); /* [d_phnum][const] Vector of program headers. */
};

#ifdef __WANT_DRIVER__d_internals
/* Helper macros for `struct driver::d_eh_frame_cache_lock' */
#define driver_eh_frame_cache_mustreap(self)     0
#define driver_eh_frame_cache_reap(self)         (void)0
#define _driver_eh_frame_cache_reap(self)        (void)0
#define driver_eh_frame_cache_write(self)        atomic_rwlock_write(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_write_nx(self)     atomic_rwlock_write_nx(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_trywrite(self)     atomic_rwlock_trywrite(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_endwrite(self)     (atomic_rwlock_endwrite(&(self)->d_eh_frame_cache_lock), driver_eh_frame_cache_reap(self))
#define _driver_eh_frame_cache_endwrite(self)    atomic_rwlock_endwrite(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_read(self)         atomic_rwlock_read(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_read_nx(self)      atomic_rwlock_read_nx(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_tryread(self)      atomic_rwlock_tryread(&(self)->d_eh_frame_cache_lock)
#define _driver_eh_frame_cache_endread(self)     atomic_rwlock_endread(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_endread(self)      (void)(atomic_rwlock_endread(&(self)->d_eh_frame_cache_lock) && (driver_eh_frame_cache_reap(self), 0))
#define _driver_eh_frame_cache_end(self)         atomic_rwlock_end(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_end(self)          (void)(atomic_rwlock_end(&(self)->d_eh_frame_cache_lock) && (driver_eh_frame_cache_reap(self), 0))
#define driver_eh_frame_cache_upgrade(self)      atomic_rwlock_upgrade(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_downgrade(self)    atomic_rwlock_downgrade(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_reading(self)      atomic_rwlock_reading(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_writing(self)      atomic_rwlock_writing(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_canread(self)      atomic_rwlock_canread(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_canwrite(self)     atomic_rwlock_canwrite(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_waitread(self)     atomic_rwlock_waitread(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->d_eh_frame_cache_lock)
#define driver_eh_frame_cache_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->d_eh_frame_cache_lock)
#endif /* __WANT_DRIVER__d_internals */


/* Check if the given driver is/was finalized. */
#define driver_isfinalizing(self) \
	(__hybrid_atomic_load((self)->d_state, __ATOMIC_ACQUIRE) >= DRIVER_STATE_FINI_DT_FINIARR)


#undef __driver_as_module
#if !defined(__cplusplus) || defined(__WANT_DRIVER_d_module)
#undef __driver_destroy
#undef __driver_free
#undef __driver_refcnt
#undef __driver_weakrefcnt
#define __driver_as_module(self)  (&(self)->d_module)
#define __driver_destroy(self)    module_destroy(&(self)->d_module)
#define __driver_free(self)       module_free(&(self)->d_module)
#define __driver_refcnt(self)     (self)->d_module.md_refcnt
#define __driver_weakrefcnt(self) (self)->d_module.md_weakrefcnt
#ifndef __DRIVER_REFCNT_FUNCTIONS_DEFINED
DEFINE_REFCNT_FUNCTIONS_P(struct driver, __driver_refcnt, __driver_destroy)
DEFINE_WEAKREFCNT_FUNCTIONS_P(struct driver, __driver_weakrefcnt, __driver_free)
#endif /* !__DRIVER_REFCNT_FUNCTIONS_DEFINED */
#else /* !__cplusplus || __WANT_DRIVER_d_module */
#define __driver_as_module /* nothing */
#endif /* __cplusplus && !__WANT_DRIVER_d_module */

/* The driver descriptor for the kernel core */
#ifndef __kernel_driver_defined
#define __kernel_driver_defined
DATDEF struct driver kernel_driver;
#endif /* !__kernel_driver_defined */
#undef kernel_driver

#ifndef __drv_self_defined
#define __drv_self_defined
#ifdef CONFIG_BUILDING_KERNEL_CORE
DATDEF struct driver drv_self ASMNAME("kernel_driver");
#else /* CONFIG_BUILDING_KERNEL_CORE */
DATDEF struct driver drv_self;
#endif /* !CONFIG_BUILDING_KERNEL_CORE */
#endif /* !__drv_self_defined */
#undef drv_self

/* Kernel core sections. */
DATDEF struct driver_section kernel_section_text;
DATDEF struct driver_section kernel_section_rodata;
DATDEF struct driver_section kernel_section_gcc_except_table;
DATDEF struct driver_section kernel_section_eh_frame;
DATDEF struct driver_section kernel_section_data;
DATDEF struct driver_section kernel_section_bss;
#ifdef CONFIG_HAVE_DEBUGGER
DATDEF struct driver_section kernel_section_dbg_hooks;
#endif /* CONFIG_HAVE_DEBUGGER */
#ifdef CONFIG_BUILDING_KERNEL_CORE
INTDEF struct driver_section kernel_section_debug_line;
INTDEF struct driver_section kernel_section_debug_info;
INTDEF struct driver_section kernel_section_debug_aranges;
INTDEF struct driver_section kernel_section_debug_abbrev;
INTDEF struct driver_section kernel_section_debug_str;
INTDEF struct driver_section kernel_section_debug_line_str;
INTDEF struct driver_section kernel_section_debug_ranges;
INTDEF struct driver_section kernel_section_debug_loc;
INTDEF struct driver_section kernel_section_pertask;
INTDEF struct driver_section kernel_section_permman;
INTDEF struct driver_section kernel_section_percpu;
INTDEF struct driver_section kernel_section_shstrtab;
#endif /* CONFIG_BUILDING_KERNEL_CORE */



/************************************************************************/
/* Driver enumeration/lookup functions                                  */
/************************************************************************/
/* Note that the `module_*' functions can also be used, however these   */
/* functions will always return `NULL' for non-kernel-space addresses!  */
/* Additionally, these functions are always NOBLOCK+NOTHROW!            */
/************************************************************************/
FUNDEF NOBLOCK WUNUSED REF struct driver *NOTHROW(FCALL driver_fromaddr)(void const *addr);
FUNDEF NOBLOCK WUNUSED REF struct driver *NOTHROW(FCALL driver_aboveaddr)(void const *addr);
FUNDEF NOBLOCK WUNUSED REF struct driver *NOTHROW(FCALL driver_next)(struct module *prev);

/* Lookup an already-loaded driver, given its name, filename, or  file.
 * Note that driver filenames (if  not absolute paths) are  interpreted
 * relative to the calling thread's current CWD, however absolute paths
 * are interpreted relative to `vfs_kernel' (i.e. are _NOT_ affected by
 * chroot(2)) */
FUNDEF WUNUSED REF struct driver *FCALL driver_fromname(USER CHECKED char const *driver_name) THROWS(E_SEGFAULT);
FUNDEF WUNUSED REF struct driver *FCALL driver_fromname_with_len(USER CHECKED char const *driver_name, size_t driver_name_len) THROWS(E_SEGFAULT);
FUNDEF WUNUSED REF struct driver *FCALL driver_fromfilename(USER CHECKED char const *driver_filename) THROWS(E_SEGFAULT);
FUNDEF WUNUSED REF struct driver *FCALL driver_fromfilename_with_len(USER CHECKED char const *driver_filename, size_t driver_name_len) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct driver *NOTHROW(FCALL driver_fromfile)(struct mfile *__restrict driver_file);
#ifdef __cplusplus
extern "C++" {
FUNDEF WUNUSED REF struct driver *FCALL
driver_fromname(USER CHECKED char const *driver_name, size_t driver_name_len)
	THROWS(E_SEGFAULT) ASMNAME("driver_fromname_with_len");
FUNDEF WUNUSED REF struct driver *FCALL
driver_fromfilename(USER CHECKED char const *driver_filename, size_t driver_name_len)
	THROWS(E_SEGFAULT) ASMNAME("driver_fromfilename_with_len");
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
FUNDEF BLOCKING WUNUSED NONNULL((1)) struct mfile *FCALL
driver_getfile(struct driver *__restrict self)
		THROWS(E_IOERROR, E_BADALLOC, ...);


/************************************************************************/
/* Driver symbol lookup functions                                       */
/************************************************************************/

struct driver_syminfo {
	uint32_t                 dsi_elfhash; /* [in|out] ELF symbol name hash. */
	uint32_t                 dsi_gnuhash; /* [in|out] GNU symbol name hash. */
	USER CHECKED char const *dsi_name;    /* [1..1][in] Symbol name */
	void                    *dsi_addr;    /* [out] Symbol address. (absolute) */
	size_t                   dsi_size;    /* [out] Symbol size. */
	unsigned char            dsi_bind;    /* [out] Symbol binding (one of `STB_GLOBAL' or `STB_WEAK') */
};

/* Initialize a given driver symbol info descriptor. */
#define driver_syminfo_init(self, name)        \
	(void)((self)->dsi_elfhash = (uint32_t)-1, \
	       (self)->dsi_gnuhash = (uint32_t)-1, \
	       (self)->dsi_name    = (name))

/* Lookup a symbol  within a driver,  given its  name.
 * Note that this function will _not_ look into driver
 * dependencies in order to resolve that symbol.
 * NOTE: This function also takes care of the special
 *       set of `drv_*' symbols!
 * @return: true:  Found a symbol matching the given name.
 * @return: false: No symbol matching the given name found. */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) __BOOL FCALL
driver_dlsym_local(struct driver *__restrict self,
                   struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...);

/* Same  as `driver_dlsym_local()', but if that function fails,
 * or  returns a weak  symbol, scan all  of the dependencies of
 * `self'  for another symbol with the same name. If a non-weak
 * symbol is found return it. Otherwise, return the first  weak
 * symbol encountered during the search, and if all that fails,
 * return `false' to indicate failure.
 * @return: *   : Found a symbol matching the given name in this driver.
 * @return: NULL: No symbol matching the given name found. */
FUNDEF BLOCKING WUNUSED NONNULL((1, 2)) REF struct driver *FCALL
driver_dlsym(struct driver *__restrict self,
             struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...);

/* Search for a symbol in all loaded drivers, following the order
 * of drivers, as they appear returned by `get_driver_loadlist()'
 * @return: *   : Found a symbol matching the given name in this driver.
 * @return: NULL: No symbol matching the given name found. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) REF struct driver *FCALL
driver_dlsym_global(struct driver_syminfo *__restrict info)
		THROWS(E_SEGFAULT, ...);

/* Helper wrappers for the above functions that simply take the
 * name of the symbol and will return its address, or `NULL' if
 * no such symbol could be found. */
FUNDEF BLOCKING WUNUSED NONNULL((1)) void *FCALL driver_dlsym_local_f(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) void *FCALL driver_dlsym_f(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...);
FUNDEF BLOCKING WUNUSED NONNULL((1)) void *FCALL driver_dlsym_global_f(USER CHECKED char const *name) THROWS(E_SEGFAULT, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING WUNUSED NONNULL((1)) void *FCALL driver_dlsym_local(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...) ASMNAME("driver_dlsym_local_f");
FUNDEF BLOCKING WUNUSED NONNULL((1)) void *FCALL driver_dlsym_global(USER CHECKED char const *name) THROWS(E_SEGFAULT, ...) ASMNAME("driver_dlsym_global_f");
FUNDEF BLOCKING WUNUSED NONNULL((1)) void *FCALL driver_dlsym(struct driver *__restrict self, USER CHECKED char const *name) THROWS(E_SEGFAULT, ...) ASMNAME("driver_dlsym_f");
} /* extern "C++" */
#endif /* __cplusplus */



struct driver_symaddr {
	char const   *dsa_name; /* [1..1][out] Symbol name */
	void         *dsa_addr; /* [out] Symbol address. (absolute) */
	size_t        dsa_size; /* [out] Symbol size. */
	unsigned char dsa_bind; /* [out] Symbol binding (one of `STB_GLOBAL' or `STB_WEAK') */
};


/* Do the reverse of the `dlsym()' functions above, and resolve
 * a  driver-relative `driver_reladdr' to try to determine info
 * about the symbol that contains that address.
 * @return: true:  Success.
 * @return: false: Failure. */
FUNDEF NOBLOCK WUNUSED NONNULL((1, 3)) __BOOL
NOTHROW(FCALL driver_dladdr_local)(struct driver *__restrict self,
                                   uintptr_t driver_reladdr,
                                   struct driver_symaddr *__restrict info);

/* Similar to `driver_dladdr_local()', but uses `driver_fromaddr()'
 * to lookup the module containing  `addr', and follows this up  by
 * using `driver_dladdr_local()' */
FUNDEF NOBLOCK WUNUSED NONNULL((2)) REF struct driver *
NOTHROW(FCALL driver_dladdr)(void const *addr,
                             struct driver_symaddr *__restrict info);


struct unwind_fde_struct;

/* Lookup  the FDE descriptor for a given `absolute_pc',
 * whilst trying to make use of the FDE cache of `self'.
 * @return: * : One of `UNWIND_*' from <libunwind/api.h> */
FUNDEF NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL driver_findfde)(struct driver *__restrict self, void const *absolute_pc,
                              struct unwind_fde_struct *__restrict result);











/************************************************************************/
/* Driver load/unload functions                                         */
/************************************************************************/

/* Flags for `driver_initialize()' and `driver_finalize()' */
#define DRIVER_INITFINI_F_NORMAL    0x0000 /* Normal flags */
#define DRIVER_INITFINI_F_FORCEFINI 0x0001 /* Discard exceptions thrown by driver  destructors.
                                            * But note that `driver_finalize()' may still throw
                                            * exceptions when this flag is set, since that func
                                            * may try to task_waitfor() the driver to finalize,
                                            * or need to allocate  memory to remove the  driver
                                            * from some kind of global hook.
                                            * WARNING: Don't  set this flag! Using this flag is
                                            *          considered unsafe, the same way that use
                                            *          of `DRIVER_DELMOD_F_FORCE' is, too!
                                            * Only use this flag to work around buggy drivers
                                            * that  refuse to unload because their finalizers
                                            * might unconditionally throw exceptions. */

/* Initialize the given driver by transitioning its state  to
 * `DRIVER_STATE_LOADED'. If this fails, or if the driver was
 * already finalized, its state is set to `DRIVER_STATE_KILL'
 * instead.
 * @param: flags: Set of `DRIVER_INITFINI_F_*' */
FUNDEF BLOCKING NONNULL((1)) void FCALL
driver_initialize(struct driver *__restrict self,
                  unsigned int flags DFL(DRIVER_INITFINI_F_NORMAL))
		THROWS(E_WOULDBLOCK, E_FSERROR, E_NOT_EXECUTABLE, ...);

/* Finalize the given driver. Note that driver finalizers are
 * allowed to block and  throw exceptions (meaning that  this
 * function  may  also block  and throw).  Additionally, this
 * function  may wait  for a  driver that  is currently being
 * initialized or finalized  by another to  finish doing  so,
 * however if it's the caller thread that does the init/fini,
 * then this function will  return immediately, so-as to  not
 * cause a deadlock!
 * @param: flags: Set of `DRIVER_INITFINI_F_*' */
FUNDEF BLOCKING NONNULL((1)) void FCALL
driver_finalize(struct driver *__restrict self,
                unsigned int flags DFL(DRIVER_INITFINI_F_NORMAL))
		THROWS(...);



/* Load & return  a driver from  a given `driver_file'.  The
 * returned driver may  not have been  initialized, yet.  As
 * such, the  caller  should  use  `driver_initialize()'  in
 * order to ensure that the returned driver was initialized.
 * @param: pnew_driver_loaded: When non-NULL, set to true/false in
 *                             order to indicate  if the  returned
 *                             driver was newly loaded, or already
 *                             present before. */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod_file(struct mfile *__restrict driver_file,
                    struct path *driver_path DFL(__NULLPTR),
                    struct fdirent *driver_dentry DFL(__NULLPTR),
                    USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                    __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...);
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod_blob(USER CHECKED void const *base, size_t num_bytes,
                    USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                    __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...);
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_loadmod(USER CHECKED char const *driver_name,
               USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
               __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_FSERROR, E_IOERROR, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod(struct mfile *__restrict driver_file,
               struct path *driver_path DFL(__NULLPTR),
               struct fdirent *driver_dentry DFL(__NULLPTR),
               USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
               __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...)
		ASMNAME("driver_loadmod_file");
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_loadmod(USER CHECKED void const *base, size_t num_bytes,
               USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
               __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...)
		ASMNAME("driver_loadmod_blob");
} /* extern "C++" */
#endif /* __cplusplus */


/* Helper-wrappers for the functions above that will automatically
 * ensure that the driver is initialized successfully, and if said
 * initialization were to cause an exception, finalize the  driver
 * to have it be unloaded once again. */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_file(struct mfile *__restrict driver_file,
                   struct path *driver_path DFL(__NULLPTR),
                   struct fdirent *driver_dentry DFL(__NULLPTR),
                   USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                   __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...);
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod_blob(USER CHECKED void const *base, size_t num_bytes,
                   USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
                   __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...);
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED REF struct driver *KCALL
driver_insmod(USER CHECKED char const *driver_name,
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_FSERROR, E_IOERROR, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod(struct mfile *__restrict driver_file,
              struct path *driver_path DFL(__NULLPTR),
              struct fdirent *driver_dentry DFL(__NULLPTR),
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...)
		ASMNAME("driver_insmod_file");
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct driver *KCALL
driver_insmod(USER CHECKED void const *base, size_t num_bytes,
              USER CHECKED char const *driver_cmdline DFL(__NULLPTR),
              __BOOL *pnew_driver_loaded DFL(__NULLPTR))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_SEGFAULT, E_NOT_EXECUTABLE, E_IOERROR, ...)
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
FUNDEF BLOCKING NONNULL((1)) unsigned int FCALL
driver_try_decref_and_delmod(/*inherit(always)*/ REF struct driver *__restrict self,
                             unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK, ...);



/* Unload a driver from the kernel core.
 * @param: driver_name: The name of the driver, or its
 *                      filename (when the first character is `/')
 * @param: flags: Set of `DRIVER_DELMOD_F_*'
 * @return: * :   One of `DRIVER_DELMOD_ST_*' */
FUNDEF BLOCKING NONNULL((1)) unsigned int FCALL
driver_delmod(USER CHECKED char const *driver_name,
              unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
FUNDEF BLOCKING NONNULL((1)) unsigned int FCALL
driver_delmod_file(struct mfile *__restrict driver_file,
                   unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...);
#ifdef __cplusplus
extern "C++" {
FUNDEF BLOCKING NONNULL((1)) unsigned int FCALL
driver_delmod(struct mfile *__restrict driver_file,
              unsigned int flags DFL(DRIVER_DELMOD_F_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...)
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
DEFINE_REFCNT_FUNCTIONS(struct driver_loadlist, dll_refcnt, driver_loadlist_destroy)

/* Return the list of currently loaded drivers.
 * Note that this function is  NOBLOCK+NOTHROW! */
FUNDEF NOBLOCK ATTR_RETNONNULL WUNUSED REF struct driver_loadlist *
NOTHROW(FCALL get_driver_loadlist)(void);

#ifndef __driver_loadlist_arref_defined
#define __driver_loadlist_arref_defined
ARREF(driver_loadlist_arref, driver_loadlist);
#endif /* !__driver_loadlist_arref_defined */

/* [1..1] A descriptor for the set of currently loaded drivers.
 * NOTE: To retrieve this list, don't use `arref_get(&drivers)',
 *       but make use  of `get_driver_loadlist()' instead.  This
 *       must be done since the later will automatically try  to
 *       get rid of drivers that  have been destroyed, but  were
 *       unable to remove themselves from the load-list. */
DATDEF struct driver_loadlist_arref drivers;





struct driver_libpath_struct {
	WEAK refcnt_t                 dlp_refcnt; /* Reference counter. */
	COMPILER_FLEXIBLE_ARRAY(char, dlp_path);  /* Path string. */
};
#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */
DEFINE_REFCNT_FUNCTIONS(struct driver_libpath_struct, dlp_refcnt, __os_free);

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

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_DRIVER_H */
