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
#ifndef GUARD_LIBDL_DL_H
#define GUARD_LIBDL_DL_H 1
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
#include <link.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include <libdl/extension.h>
#include <libdl/module.h>

#include "builtin.h"

#undef TRY
#undef EXCEPT
#undef RETHROW
#define TRY       try
#define EXCEPT    catch (...)
#define RETHROW() throw

DECL_BEGIN

#ifndef DL_VERIFY_TLS_SEGMENT
#define DL_VERIFY_TLS_SEGMENT(p) \
	((p) && ((uintptr_t)(p) & (sizeof(void *) - 1)) == 0)
#endif /* !DL_VERIFY_TLS_SEGMENT */

#ifndef DL_VERIFY_MODULE_HANDLE
#define DL_VERIFY_MODULE_HANDLE(p) \
	((p) && ((uintptr_t)(p) & (sizeof(void *) - 1)) == 0)
#endif /* !DL_VERIFY_MODULE_HANDLE */

#ifndef DL_VERIFY_SECTION_HANDLE
#define DL_VERIFY_SECTION_HANDLE(p) \
	((p) && ((uintptr_t)(p) & (sizeof(void *) - 1)) == 0)
#endif /* !DL_VERIFY_SECTION_HANDLE */

#define DECLARE_INTERN_OVERRIDE(name)        \
	__asm__(".type " #name ", @function\n\t" \
	        ".global " #name "\n\t"          \
	        ".hidden " #name);
BUILTIN_GLOBALS_ENUMERATE(DECLARE_INTERN_OVERRIDE)
#undef DECLARE_INTERN_OVERRIDE


/* Define our own private variants of a couple of  functions
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

/* Invoke all callbacks from the given module finalizers list */
INTDEF NONNULL((1)) void CC
dlmodule_finalizers_run(struct dlmodule_finalizers *__restrict self);

/* [1..1] List of global modules / pointer to the root binary. */
LIST_HEAD(dlmodule_list, dlmodule);
INTDEF struct dlmodule_list DlModule_GlobalList;
INTDEF struct atomic_rwlock DlModule_GlobalLock;

/* [1..1] List of all loaded modules. */
DLIST_HEAD(dlmodule_dlist, dlmodule);
INTDEF struct dlmodule_dlist DlModule_AllList;
INTDEF struct atomic_rwlock DlModule_AllLock;

#define DlModule_GlobalList_FOREACH(mod) \
	LIST_FOREACH (mod, &DlModule_GlobalList, dm_globals)
#define DlModule_AllList_FOREACH(mod) \
	DLIST_FOREACH (mod, &DlModule_AllList, dm_modules)

/* The module describing the RTLD library itself. */
INTDEF DlModule dl_rtld_module;

LOCAL NONNULL((1)) void CC
DlModule_AddToGlobals(DlModule *__restrict self) {
	/* XXX: This right here is a O(n) operation for something  that
	 *      could also be done in O(1) when using other list types.
	 *      However, all list types currently defined in <hybrid/sequence/list.h>
	 *      that offer O(1) INSERT_TAIL, would also require a static  initializer
	 *      that contains a relocation... */
	LIST_INSERT_TAIL(&DlModule_GlobalList, self, dm_globals);
}

LOCAL NONNULL((1)) void CC
DlModule_AddToAll(DlModule *__restrict self) {
	assert(!DLIST_EMPTY(&DlModule_AllList));
	DLIST_INSERT_TAIL(&DlModule_AllList, self, dm_modules);
}

LOCAL NONNULL((1)) void CC
DlModule_RemoveFromAll(DlModule *__restrict self) {
	assert(self != &dl_rtld_module);
	assert(DLIST_PREV(self, dm_modules) != NULL);
	DLIST_REMOVE(&DlModule_AllList, self, dm_modules);
}


/* Lock used to ensure that only a single thread can ever load modules
 * at the same time (used to prevent potential race conditions arising
 * from the fact that various components must be accessed globally). */
INTDEF struct atomic_owner_rwlock DlModule_LoadLock;

/* [1..1][const] The library path set when the program was started (initenv:$LD_LIBRARY_PATH) */
INTDEF char *dl_library_path;

/* Open a DL Module.
 * @return: NULL: Failed to open the module.  (no error is set if  the file could not be  found
 *                in a call to one of `DlModule_OpenFilename' or `DlModule_OpenFilenameInPath') */
INTDEF WUNUSED REF DlModule *DLFCN_CC
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
DlModule_ElfOpenLoadedProgramHeaders(/*inherit(on_success,HEAP)*/ char *__restrict filename,
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
DlModule_ElfInitialize(DlModule *__restrict self, unsigned int flags);
#define DL_MODULE_ELF_INITIALIZE_FNORMAL   0x0000
#define DL_MODULE_ELF_INITIALIZE_FTEXTREL  0x0001 /* Text relocations exist. */
#define DL_MODULE_ELF_INITIALIZE_FBINDNOW  0x0002 /* Bind all symbols now. */

/* Apply relocations for `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
INTDEF WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocations(DlModule *__restrict self,
                          ElfW(Rel) const *__restrict vector,
                          size_t count, unsigned int flags);
#if ELF_ARCH_USESRELA
INTDEF WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocationsWithAddend(DlModule *__restrict self,
                                    ElfW(Rela) const *__restrict vector,
                                    size_t count, unsigned int flags);
#endif /* ELF_ARCH_USESRELA */

/* Verify that `ehdr' is valid */
INTDEF WUNUSED NONNULL((1, 2)) int CC
DlModule_ElfVerifyEhdr(ElfW(Ehdr) const *__restrict ehdr,
                       char const *__restrict filename,
                       bool requires_ET_DYN);



/* Lazily allocate if necessary, and return the file descriptor for `self'
 * @return: -1: Error (s.a. dl_error_message) */
INTDEF WUNUSED NONNULL((1)) fd_t CC
DlModule_GetFd(DlModule *__restrict self);

/* Lazily allocate  if  necessary,  and  return  the vector  of  section  headers  for  `self'
 * NOTE: On success, this function guaranties that the following fields have been initialized:
 *  - self->dm_shnum
 *  - self->dm_elf.de_shoff
 *  - self->dm_elf.de_shstrndx
 *  - self->dm_elf.de_shdr
 * @return: NULL: Error (s.a. dl_error_message) */
INTDEF WUNUSED NONNULL((1)) ElfW(Shdr) *CC
DlModule_ElfGetShdrs(DlModule *__restrict self);

/* Lazily allocate if necessary, and return the section header string table for `self'
 * @return: NULL: Error (s.a. dl_error_message) */
INTDEF WUNUSED NONNULL((1)) char *CC
DlModule_ElfGetShstrtab(DlModule *__restrict self);

/* Return the section header associated with a given `name'
 * @return: NULL: Error (s.a. dl_error_message) */
INTDEF WUNUSED NONNULL((1, 2)) ElfW(Shdr) *CC
DlModule_ElfGetSection(DlModule *__restrict self,
                       char const *__restrict name);

/* Lazily calculates  and  returns  the #  of  symbols  in  `de_dynsym_tab'
 * NOTE: This function may only be called with `de_dynsym_tab' is non-NULL!
 * @return: * : The # of symbols in `de_dynsym_tab'
 * @return: 0 : Error (dlerror() was modified) */
INTDEF WUNUSED NONNULL((1)) size_t CC
DlModule_ElfGetDynSymCnt(DlModule *__restrict self);

/* Return a pointer to the Elf_Sym object assigned with `name'.
 * WARNING: The returned symbol  may not necessarily  be defined by  `self'.
 *          This function merely returns the associated entry from `.dynsym'
 * NOTE: This function ~may~ set `dlerror()' when returning `NULL' in
 *       case of the error is the  result of a corrupted hash  table. */
INTDEF ElfW(Sym) const *CC
DlModule_ElfGetLocalSymbol(DlModule *__restrict self,
                           char const *__restrict name,
                           uintptr_t *__restrict phash_elf,
                           uintptr_t *__restrict phash_gnu);
#define DLMODULE_GETLOCALSYMBOL_HASH_UNSET ((uintptr_t)-1)

/* Find  the  DL   module  mapping   the  specified   file.
 * If no such module is loaded, `NULL' is returned instead.
 * @return: NULL: No such module exists (NOTE: No error was set in this case!) */
INTDEF REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_FindFromFilename(char const *__restrict filename);

/* Find the DL module containing a given static pointer.
 * @return: NULL: Error (s.a. `dl_error_message') */
INTDEF WUNUSED DlModule *CC DlModule_FindFromStaticPointer(void const *static_pointer);


/* Functions made available to applications being loaded. */
INTDEF REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *DLFCN_CC
libdl_dlfopen(/*inherit(on_success)*/ fd_t fd, unsigned int mode);
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *DLFCN_CC
libdl_dlopen(char const *filename, int mode);
INTDEF NONNULL((1)) int DLFCN_CC libdl_dlclose(REF DlModule *handle);
INTDEF NONNULL((1)) int DLFCN_CC libdl_dlexceptaware(DlModule *handle);
INTDEF NONNULL((2)) void *DLFCN_CC libdl_dlsym(DlModule *handle, char const *__restrict name);
INTDEF char *DLFCN_CC libdl_dlerror(void);
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF))
DlModule *DLFCN_CC libdl_dlgethandle(void const *static_pointer, unsigned int flags);
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF))
DlModule *DLFCN_CC libdl_dlgetmodule(char const *name, unsigned int flags);
INTDEF NONNULL((2)) int DLFCN_CC libdl_dladdr(void const *address, Dl_info *info);
INTDEF WUNUSED NONNULL((1)) fd_t DLFCN_CC libdl_dlmodulefd(DlModule *self);
INTDEF WUNUSED NONNULL((1)) char const *DLFCN_CC libdl_dlmodulename(DlModule *self);
INTDEF WUNUSED NONNULL((1)) void *DLFCN_CC libdl_dlmodulebase(DlModule *self);
INTDEF WUNUSED REF DlSection *DLFCN_CC libdl_dllocksection(DlModule *self, char const *__restrict name, unsigned int flags);
INTDEF NONNULL((1)) int DLFCN_CC libdl_dlunlocksection(REF DlSection *sect);
INTDEF NONNULL((1)) char const *DLFCN_CC libdl_dlsectionname(DlSection *sect);
INTDEF NONNULL((1)) size_t DLFCN_CC libdl_dlsectionindex(DlSection *sect);
INTDEF NONNULL((1)) DlModule *DLFCN_CC libdl_dlsectionmodule(DlSection *sect, unsigned int flags);
INTDEF WUNUSED NONNULL((1)) void *DLFCN_CC libdl_dlinflatesection(DlSection *sect, size_t *psize);
INTDEF int DLFCN_CC libdl_dlclearcaches(void);
INTDEF void *DLFCN_CC libdl_dlauxctrl(DlModule *self, unsigned int type, ...);
INTDEF void *LIBCCALL libdl____tls_get_addr(void);
INTDEF void *LIBCCALL libdl___tls_get_addr(void);


struct tls_segment;

/* Allocate/Free a static TLS segment
 * These functions are  called by  by libc  in order to  safely create  a new  thread, such  that
 * all current and  future modules are  able to  store thread-local storage  within that  thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror()) */
INTDEF ATTR_MALLOC WUNUSED struct tls_segment *DLFCN_CC libdl_dltlsallocseg(void);

/* Free a previously allocated static TLS segment (usually called by `pthread_exit()' and friends). */
INTDEF NONNULL((1)) int DLFCN_CC libdl_dltlsfreeseg(struct tls_segment *ptr);

/* Return a pointer to the base of the given module's
 * TLS  segment,  as  seen form  the  calling thread.
 * In the case of dynamic TLS, allocate missing segments lazily,
 * logging a system error and exiting the calling application if
 * doing so fails. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) void *ATTR_FASTCALL
libdl_dltlsbase(DlModule *__restrict self);

/* DL-based TLS memory management API.
 * These functions may be used to dynamically allocate TLS memory that works everywhere where
 * ATTR_THREAD-based  TLS memory also works. - However  using these functions, TLS memory can
 * be  allocated dynamically at  runtime (behaving the same  as a call  to dlopen() loading a
 * module containing a TLS segment would).
 * @param: NUM_BYTES:      The size of the TLS segment (in bytes)
 * @param: MIN_ALIGNMENT:  The minimum alignment requirements for the TLS segment base address.
 * @param: TEMPLATE_DATA:  Base address of an initialization template.
 *                         The first `TEMPLATE_SIZE' bytes  of any per-thread data  segment
 *                         that gets allocated will be initialized to the contents of these
 *                         values before `PERTHREAD_INIT' is optionally invoked in order to
 *                         perform additional initialization.
 * @param: TEMPLATE_SIZE:  The size of `TEMPLATE_DATA' in bytes, indicating the number  of
 *                         leading bytes within the TLS segment that should be pre-defined
 *                         to mirror the contents of `TEMPLATE_DATA' at the time of a call
 *                         to this  function (`TEMPLATE_DATA'  need  not remain  valid  or
 *                         accessible after this function returns)
 *                         Any memory after `TEMPLATE_SIZE', but before `NUM_BYTES' is initialized
 *                         to  all  ZEROes,  however  `TEMPLATE_SIZE'  must  not  be  greater than
 *                        `NUM_BYTES', and if it is, this function returns `NULL' and sets
 *                        `dlerror()' accordingly.
 * @param: PERTHREAD_INIT: An optional callback that will be invoked on a per-thread basis
 *                         in order to perform additional initialization of the associated
 *                         TLS segment within the associated thread.
 *                         This function will be called upon first access of the segment
 *                         within   the  thread  using  the  data  (s.a.  `dltlsaddr()')
 *                         @param: ARG:  The value of `PERTHREAD_CALLBACK_ARG' passed to `dltlsalloc'
 *                         @param: BASE: The base address of the associated segment within the calling
 *                                       thread   (same   as  the   return  value   of  `dltlsaddr()')
 * @param: PERTHREAD_FINI: An optional callback that behaves similar to `PERTHREAD_INIT',
 *                         but called by `pthread_exit()'  or any other thread  finalizer
 *                        (more specifically: by `dltlsfreeseg()') within any thread that
 *                         has been seen using the associated segment, and causing it to
 *                         be allocated and initialized for that thread.
 * @param: PERTHREAD_CALLBACK_ARG: A user-specified argument passed to the init/fini callbacks.
 * @return: * :            An opaque handle for the newly created TLS segment.
 *                         This handle may be used in future calls to `dltlsaddr()', and can be
 *                         destroyed (causing  all threads  that had  previously allocated  the
 *                         segment to delete it and  optionally invoke finalizer callbacks)  by
 *                         passing it to `dltlsfree()'
 * @return: NULL:          Failed to allocate the TLS segment (s.a. `dlerror()') */
INTDEF WUNUSED DlModule *DLFCN_CC
libdl_dltlsalloc(size_t num_bytes, size_t min_alignment,
                 void const *template_data, size_t template_size,
                 void (DLFCN_CC *perthread_init)(void *__arg, void *__base),
                 void (DLFCN_CC *perthread_fini)(void *__arg, void *__base),
                 void *perthread_callback_arg);

/* Free a TLS segment previously allocated with `dltlsalloc()' */
INTDEF NONNULL((1)) int DLFCN_CC libdl_dltlsfree(DlModule *self);

#ifndef __DLFCN_DLTLSADDR_CC
#define __DLFCN_DLTLSADDR_CC  __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR_CC */
#ifndef __DLFCN_DLTLSADDR2_CC
#define __DLFCN_DLTLSADDR2_CC __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR2_CC */


/* Return the calling thread's base address of the TLS segment associated with `TLS_HANDLE'
 * NOTE: TLS Segments are allocated and initialized lazily, meaning that the initializer
 *       passed  to `dltlsalloc()' will be called by this function upon the first use of
 *       that  segment within each  individual thread, also causing  the finalizer to be
 *       enqueued for invocation when the calling thread exits.
 * WARNING: The order in which TLS finalizers are invoked is entirely UNDEFINED!
 * NOTE: the  given  `TLS_HANDLE' may  also  be a  module  handle, as  returned  by `dlopen()',
 *       in which case this function  returns a pointer to the  TLS segment of that module  for
 *       the calling thread (e.g.: Such a pointer is needed by `unwind_emulator_t::sm_tlsbase')
 * @return: * :   Pointer to the base of the TLS segment associated with `TLS_HANDLE' within the calling thread.
 * @return: NULL: Invalid `TLS_HANDLE', or allocation/initialization failed. (s.a. `dlerror()') */
INTDEF WUNUSED NONNULL((1)) void *__DLFCN_DLTLSADDR_CC
libdl_dltlsaddr(DlModule *self);

/* Same as `dltlsaddr()', but used to lookup a TLS block relative to a given `TLS_SEGMENT',
 * where the later was previously  allocated using `dltlsallocseg()'. This function  allows
 * the caller to get a pointer to the TLS data of another thread, and is used to initialize
 * the `pthread_self()' of a newly created thread from within `pthread_create()'.
 * @return: * :   Pointer to the base of the TLS segment associated with `TLS_HANDLE'
 *                within the given `TLS_SEGMENT'.
 * @return: NULL: Invalid `TLS_HANDLE' or `TLS_SEGMENT', or
 *                allocation/initialization failed. (s.a. `dlerror()') */
INTDEF WUNUSED NONNULL((1, 2)) void *__DLFCN_DLTLSADDR2_CC
libdl_dltlsaddr2(DlModule *self, struct tls_segment *seg);

/* Similar to `libdl_dltlsaddr()', but do no lazy allocation
 * and return NULL if the module doesn't have a TLS segment. */
INTDEF WUNUSED NONNULL((1)) void *CC DlModule_TryGetTLSAddr(DlModule *__restrict self);

/* Enumerate all loaded modules, as  well as information about  them.
 * Enumeration stops when `*CALLBACK' returns a non-zero value, which
 * will then also be returned  by this function. Otherwise, `0'  will
 * be returned after all modules have been enumerated. */
INTDEF int DLFCN_CC libdl_iterate_phdr(__dl_iterator_callback callback, void *arg);

/* Invoke the  static initializers  of  all currently  loaded  modules.
 * This is called late during  initial module startup once the  initial
 * set of  libraries,  +  the initial  application  have  been  loaded.
 * Note that initializers are invoked in reverse order of those modules
 * appearing   within  `DlModule_AllList',  meaning  that  the  primary
 * application's  __attribute__((constructor))  functions  are  invoked
 * _AFTER_ those from (e.g.) libc. */
INTDEF void CC DlModule_RunAllStaticInitializers(void);

/* Initialize the static TLS bindings table from the set of currently loaded modules. */
INTDEF WUNUSED int CC DlModule_InitStaticTLSBindings(void);

/* Remove the given module from the table of static TLS bindings. */
INTDEF NONNULL((1)) void CC DlModule_RemoveTLSExtension(DlModule *__restrict self);

/* Run finalizers for all TLS segments allocated within the calling thread. */
INTDEF void CC DlModule_RunAllTlsFinalizers(void);

#ifdef ELF_ARCH_IS_R_JMP_SLOT
/* Called from JMP_SLOT relocations (s.a. `arch/i386/rt32.S') */
INTDEF void /*ASMCALL*/ dl_load_lazy_relocation(void);

/* Bind a lazy relocation, resolving its JMP relocation entry and returning the
 * absolute address of the bound symbol. - If the symbol can't be resolved, log
 * a system error and exit the calling application. */
INTDEF WUNUSED NONNULL((1)) ElfW(Addr) ATTR_FASTCALL
dl_bind_lazy_relocation(DlModule *__restrict self,
#if ELF_ARCH_LAZYINDX
                        uintptr_t jmp_rel_index
#else /* ELF_ARCH_LAZYINDX */
                        uintptr_t jmp_rel_offset
#endif /* !ELF_ARCH_LAZYINDX */
                        );
#endif /* ELF_ARCH_IS_R_JMP_SLOT */

/* PEB for the main executable. */
INTDEF struct process_peb *root_peb;

INTDEF char dl_error_buffer[128];
INTDEF char *dl_error_message;
INTDEF ATTR_COLD int CC dl_seterror_badptr(void *ptr);
INTDEF ATTR_COLD int CC dl_seterror_badmodule(void *modptr);
INTDEF ATTR_COLD int CC dl_seterror_badsection(void *sectptr);
INTDEF ATTR_COLD int CC dl_seterror_nomem(void);
INTDEF ATTR_COLD int CC dl_seterror_no_mod_at_addr(void const *static_pointer);
INTDEF ATTR_COLD int CC dl_seterror_header_read_error(char const *__restrict filename);
INTDEF ATTR_COLD int CC dl_seterror_notelf(DlModule *__restrict self);
INTDEF ATTR_COLD NONNULL((1, 2)) int CC dl_seterror_nosect(DlModule *__restrict self, char const *__restrict name);
INTDEF ATTR_COLD NONNULL((1)) int CC dl_seterror_nosect_index(DlModule *__restrict self, size_t index);
INTDEF ATTR_COLD NONNULL((1)) int VCC dl_seterrorf(char const *__restrict format, ...);
INTDEF ATTR_COLD NONNULL((1)) int CC dl_vseterrorf(char const *__restrict format, va_list args);

/* Return the address of a builtin function (e.g. `dlopen()') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *FCALL dlsym_builtin(char const *__restrict name);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) DlSection *FCALL dlsec_builtin(char const *__restrict name);
INTDEF WUNUSED ATTR_CONST DlSection *FCALL dlsec_builtin_index(size_t sect_index);
INTDEF WUNUSED ATTR_CONST char const *FCALL dlsec_builtin_name(size_t sect_index);

/* Return the address of a function `name'  that is required by the RTLD  core
 * and  must be defined by one of the  loaded libraries. - If no such function
 * is defined, log an error message to the system log and terminate the hosted
 * application ungracefully. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
dl_require_global(char const *__restrict name);

/* Set to true if the sys_debugtrap() system call is disabled. */
INTDEF bool sys_debugtrap_disabled;

/* [0..1][ATOMIC(APPEND)] Chain of registered DL extensions.
 * NOTE: Once registered, a DL extension cannot be  deleted! */
INTDEF struct dlmodule_format *dl_extensions;

/* Lazily initialize and return the libdl core ops V-table. */
INTDEF ATTR_RETNONNULL WUNUSED struct dlcore_ops *CC dl_getcoreops(void);



DECL_END

#endif /* !GUARD_LIBDL_DL_H */
