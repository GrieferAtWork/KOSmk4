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
#include <hybrid/sched/atomic-rwlock.h>

#include <kos/anno.h>
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

#ifndef USER
#define USER __USER
#endif /* !USER */
#ifndef THROWS
#define THROWS __THROWS
#endif /* !THROWS */
#ifndef ASMCALL
#define ASMCALL /* nothing */
#endif /* !ASMCALL */

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

#define DECLARE_INTERN_OVERRIDE(name)           \
	__asm__(".type " #name ", \"function\"\n\t" \
	        ".global " #name "\n\t"             \
	        ".hidden " #name);
BUILTIN_GLOBALS_ENUMERATE(DECLARE_INTERN_OVERRIDE)
#undef DECLARE_INTERN_OVERRIDE


/* Define our own private variants of a couple of  functions
 * that aren't already automatically substituted in headers. */
INTDEF NONNULL((2)) ssize_t
NOTHROW_RPC(CC preadall)(fd_t fd, void *buf, size_t bufsize, ElfW(Off) offset);


/* Invoke all callbacks from the given module finalizers list */
INTDEF NONNULL((1)) void CC
dlmodule_finalizers_run(struct dlmodule_finalizers *__restrict self)
		THROWS(...);

/* libdl global variables (as also shared with extension drivers) */
INTDEF struct dlglobals dl_globals;

/* The module describing the RTLD library itself. */
INTDEF DlModule dl_rtld_module;

/* Open a DL Module.
 * @return: NULL: Failed to open the module.  (no error is set if  the file could not be  found
 *                in a call to one of `DlModule_OpenFilename' or `DlModule_OpenFilenameInPath') */
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *DLFCN_CC
DlModule_OpenFd(/*inherit(on_success)*/ fd_t fd, unsigned int mode)
		THROWS(...);

INTDEF WUNUSED NONNULL((1)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilename(USER char const *filename, unsigned int mode)
		THROWS(E_SEGFAULT, ...);

INTDEF WUNUSED NONNULL((1, 3)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilenameInPath(char const *__restrict path, size_t pathlen,
                            USER char const *filename, size_t filenamelen,
                            unsigned int mode, char const *origin_filename)
		THROWS(E_SEGFAULT, ...);

INTDEF WUNUSED NONNULL((1, 2)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilenameInPathList(char const *__restrict path, USER char const *filename,
                                unsigned int mode, char const *origin_filename)
		THROWS(E_SEGFAULT, ...);

INTDEF WUNUSED NONNULL((1)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_OpenFilenameAndFd(/*inherit(on_success,HEAP)*/ char *__restrict filename,
                           /*inherit(on_success)*/ fd_t fd, unsigned int mode)
		THROWS(...);

INTDEF WUNUSED NONNULL((1, 2)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *CC
DlModule_ElfOpenLoadedProgramHeaders(/*inherit(on_success,HEAP)*/ char *__restrict filename,
                                     struct elfexec_info *__restrict info, uintptr_t loadaddr)
		THROWS(...);


/* Try to find an already-loaded module. */
INTDEF WUNUSED NONNULL((1, 3)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *
NOTHROW_NCX(CC DlModule_FindFilenameInPathFromAll)(char const *__restrict path, size_t pathlen,
                                                   USER char const *filename, size_t filenamelen)
		THROWS(E_SEGFAULT);

INTDEF WUNUSED NONNULL((1)) REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *
NOTHROW_NCX(CC DlModule_FindFilenameInPathListFromAll)(USER char const *filename)
		THROWS(E_SEGFAULT);


/* Apply relocations & execute library initialized within `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
INTDEF NONNULL((1)) int CC
DlModule_ElfInitialize(DlModule *__restrict self, unsigned int flags)
		THROWS(...);
#define DL_MODULE_ELF_INITIALIZE_FNORMAL   0x0000
#define DL_MODULE_ELF_INITIALIZE_FTEXTREL  0x0001 /* Text relocations exist. */
#define DL_MODULE_ELF_INITIALIZE_FBINDNOW  0x0002 /* Bind all symbols now. */

/* Apply relocations for `self'
 * @param: flags: Set of `DL_MODULE_INITIALIZE_F*' */
INTDEF WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocations(DlModule *__restrict self,
                          ElfW(Rel) const *__restrict vector,
                          size_t count, unsigned int flags)
		THROWS(...);

#if ELF_ARCH_USESRELA
INTDEF WUNUSED NONNULL((1)) int CC
DlModule_ApplyRelocationsWithAddend(DlModule *__restrict self,
                                    ElfW(Rela) const *__restrict vector,
                                    size_t count, unsigned int flags)
		THROWS(...);
#endif /* ELF_ARCH_USESRELA */

/* Verify that `ehdr' is valid */
INTDEF WUNUSED NONNULL((1, 2)) int
NOTHROW(CC DlModule_ElfVerifyEhdr)(ElfW(Ehdr) const *__restrict ehdr,
                                   char const *__restrict filename,
                                   bool requires_ET_DYN);

/* @param: mode: Set of `0 | RTLD_GLOBAL' (other flags are ignored) */
INTERN NONNULL((1)) void
NOTHROW(CC DlModule_UpdateFlags)(DlModule *__restrict self, int mode);


/* Lazily allocate if necessary, and return the file descriptor for `self'
 * @return: -1: Error (s.a. dlerror()) */
INTDEF WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(CC DlModule_GetFd)(USER DlModule *self)
		THROWS(E_SEGFAULT);

/* Lazily allocate  if  necessary,  and  return  the vector  of  section  headers  for  `self'
 * NOTE: On success, this function guaranties that the following fields have been initialized:
 *  - self->dm_elf.de_shnum
 *  - self->dm_elf.de_shoff
 *  - self->dm_elf.de_shstrndx
 *  - self->dm_elf.de_shdr
 * @return: NULL: Error (s.a. dlerror()) */
INTDEF WUNUSED NONNULL((1)) ElfW(Shdr) *
NOTHROW_NCX(CC DlModule_ElfGetShdrs)(USER DlModule *self)
		THROWS(E_SEGFAULT);

/* Lazily allocate if necessary, and return the section header string table for `self'
 * @return: NULL: Error (s.a. dlerror()) */
INTDEF WUNUSED NONNULL((1)) char *
NOTHROW_NCX(CC DlModule_ElfGetShstrtab)(USER DlModule *self)
		THROWS(E_SEGFAULT);

/* Return the section header associated with a given `name'
 * @return: NULL:             Error (w/ dlerror() set)
 * @return: (ElfW(Shdr) *)-1: Not found (w/o dlerror() set) */
INTDEF WUNUSED NONNULL((1, 2)) ElfW(Shdr) *
NOTHROW_NCX(CC DlModule_ElfGetSection)(USER DlModule *self,
                                       USER char const *name)
		THROWS(E_SEGFAULT);

/* Lazily calculates  and  returns  the #  of  symbols  in  `de_dynsym_tab'
 * NOTE: This function may only be called with `de_dynsym_tab' is non-NULL!
 * @return: * : The # of symbols in `de_dynsym_tab'
 * @return: 0 : Error (dlerror() was modified) */
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(CC DlModule_ElfGetDynSymCnt)(USER DlModule *self)
		THROWS(E_SEGFAULT);

/* Return a pointer to the Elf_Sym object assigned with `name'.
 * WARNING: The returned symbol  may not necessarily  be defined by  `self'.
 *          This function merely returns the associated entry from `.dynsym'
 * NOTE: This function ~may~ set `dlerror()' when returning `NULL' in
 *       case of the error is the  result of a corrupted hash  table. */
INTDEF WUNUSED NONNULL((1, 2, 3, 4)) ElfW(Sym) const *
NOTHROW_NCX(CC DlModule_ElfGetLocalSymbol)(USER DlModule *self,
                                           USER char const *name,
                                           uintptr_t *__restrict phash_elf,
                                           uintptr_t *__restrict phash_gnu)
		THROWS(E_SEGFAULT);
#define DLMODULE_GETLOCALSYMBOL_HASH_UNSET ((uintptr_t)-1)

/* Find  the  DL   module  mapping   the  specified   file.
 * If no such module is loaded, `NULL' is returned instead.
 * @return: NULL: No such module exists (NOTE: No error was set in this case!) */
INTERN REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *
NOTHROW_NCX(CC DlModule_FindFromFilename)(USER char const *filename)
		THROWS(E_SEGFAULT);


/************************************************************************/
/* Functions made available to applications being loaded (<dlfcn.h>).   */
/************************************************************************/

/* Lazily load a shared library file, and return a handle to said file.
 * @param: filename: The filename of the shared library.
 *                   If  this string contains  at least 1 '/'-character,
 *                   the string will be  interpreted as a raw  filename,
 *                   such that passing it to open(2) would return a file
 *                   handle for the named library file.
 *                   In this case, `filename' may either be an absolute path,
 *                   or a path relative to the current working directory,  as
 *                   set by `chdir(2)'
 *                   If  `filename'  doesn't  contain  any  '/'-characters,  the  string
 *                   is  the  filename  of the  library  (e.g. "libc.so"),  and  will be
 *                   searched for in the set  of system library locations, as  specified
 *                   by  a  ':'-separated string  read  from `getenv("LD_LIBRARY_PATH")'
 *                   at  the time of  the process having been  started, or defaulting to
 *                   a set of paths that include at least "/usr/lib:/lib" in that order.
 *                   When `NULL' is  passed for  this argument,  a handle  for the  main
 *                   executable module (i.e.  the `readlink  /proc/self/exe` binary)  is
 *                   returned.
 * @param: mode:     Exactly  one  of  [RTLD_LAZY, RTLD_NOW],  or'd  with
 *                   exactly one of [RTLD_GLOBAL, RTLD_LOCAL], optionally
 *                   or'd with any of the other `RTLD_*' flags.
 * @return: * :   A handle to the library that got loaded.
 * @return: NULL: Failed to load the library. - Call `dlerror()' to get an error message. */
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *DLFCN_CC
libdl_dlopen(USER char const *filename, int mode)
		THROWS(E_SEGFAULT, ...);

/* Close  a  previously  opened  dynamic  module  handle,  as  returned by
 * `dlopen(3D)',  and  some of  the other  functions  found in  this file.
 * Note  that  this call  is implemented  as  a decref()  operation, since
 * multiple calls to `dlopen(3D)' for the same library will try to  ensure
 * that  only  a single  instance of  some unique  library is  ever loaded
 * at the same time. However, every call to `dlopen(3D)' should eventually
 * be followed by a call to `dlclose(3D)' with that same handle, such that
 * once some specific handle is closed for the last time, the library  can
 * be unloaded.
 * Note  also that  if this function  does actually unload  a library, user-
 * defined callbacks may be invoked, including `__attribute__((destructor))'
 * callbacks,  as well  as callbacks  registered dynamically  through use of
 * `DLAUXCTRL_ADD_FINALIZER' (which in turn is used by `__cxa_atexit()')
 * @return: 0 : Successfully closed the given handle.
 * @return: * : Failed to close the handle  (which is likely to simply  be
 *              invalid; s.a. `dlerror()') Warning: Don't just willy-nilly
 *              pass invalid handles  to this function.  Depending on  how
 *              libdl  was  configured,  only  minimal  validation  may be
 *              performed.  The  only guaranty  made is  that NULL-handles
 *              are always handled as fail-safe! */
INTDEF NONNULL((1)) int DLFCN_CC
libdl_dlclose(USER REF_IF(!(self->dm_flags & RTLD_NODELETE)) DlModule *handle)
		THROWS(E_SEGFAULT, ...);

/* Lookup the load address of a symbol within a shared library  `handle',
 * given its `symbol_name'. If no such symbol exists, `NULL' is returned,
 * and `dlerror()' is modified to return a human-readable error message.
 * WARNING: If  the actual address of the symbol is `NULL', then this
 *          function will still return `NULL', though will not modify
 *          the return value of `dlerror()'.
 *          In normal applications, this would normally never be the case,
 *          as  libdl, as well as `ld', will  take care not to link object
 *          files such that symbols could end up overlapping with  `NULL'.
 *          However, with the existence of `STT_GNU_IFUNC' (as usable  via
 *          `__attribute__((ifunc("resolver")))'), it  is easily  possible
 *          to force some symbol to overlap with NULL.
 *          Also  note that  upon success,  `dlerror()' will  not have been
 *          modified, meaning that if a prior error has yet to be consumed,
 *          a NULL return value, and  a non-NULL `dlerror()' may still  not
 *          guaranty that the symbol really doesn't exist. To be absolutely
 *          certain  that  NULL  would  be  correct,  use  the   following:
 *          >> void *result;
 *          >> dlerror(); // Clear preceding error
 *          >> result = dlsym(handle, symbol_name);
 *          >> if (result == NULL) {
 *          >>     char *message = dlerror();
 *          >>     if (message != NULL) // Symbol lookup really failed.
 *          >>         fprintf(stderr, "dlerror: %s\n", message);
 *          >> }
 * @param: handle: The dynamic library handle of  the library which should  be
 *                 searched  for the specified `symbol_name', before moving on
 *                 to also search all of those libraries' dependencies for the
 *                 same `symbol_name', and  so on,  following a  breadth-first
 *                 search approach.
 *                 Alternatively, you may also pass `RTLD_DEFAULT' or `RTLD_NEXT'
 *                 to make use  of special symbol  lookup resolutions  documented
 *                 more extensively alongside these constants.
 * @return: * :    The address of the symbol in question.
 * @return: NULL:  No  such symbol (dlerror()  != NULL), or  the symbol has been
 *                 linked to be loaded at the address `NULL' (dlerror() == NULL) */
INTDEF WUNUSED NONNULL((2)) void *DLFCN_CC
libdl_dlsym(USER DlModule *handle, USER char const *symbol_name)
		THROWS(E_SEGFAULT, ...);

/* Return  and clear the  current libdl error message  string, such that for
 * any error that occurs, this function will only returns non-NULL once. The
 * returned string has a human-readable format and is generated dynamically,
 * meaning that it  may contain  information that  is more  specific than  a
 * simple  `File or directory not found' message, but rather something along
 * the  lines  of  `Symbol "foo" could not be found in library "libfoo.so"'.
 * The implementation of this function looks like:
 * >> return ATOMIC_XCH(error_message_pointer, NULL);
 * Where internally, libdl will set `error_message_pointer' to a non-NULL pointer
 * when an error happens.
 * @return: * :   A pointer  to a  volatile (as  in: the  same memory  area may  be
 *                overwritten once the next dl-error happens in either the calling,
 *                !_or any other thread_!), human-readable description of the  last
 *                error that  happened during  execution of  any of  the  functions
 *                exported from libdl.
 * @return: NULL: No error happened, or the last error has already been consumed. */
INTDEF char *NOTHROW(DLFCN_CC libdl_dlerror)(void);

/* Open a library, given a file descriptor previously acquired by `open(2)'
 * NOTE: This function will inherit the given `fd' on success.
 * @param: fd:   The file descriptor to use & inherit for the shared library
 * @param: mode: Exactly  one  of  [RTLD_LAZY, RTLD_NOW],  or'd  with
 *               exactly one of [RTLD_GLOBAL, RTLD_LOCAL], optionally
 *               or'd with any of the other `RTLD_*' flags. */
INTDEF REF_IF(!(return->dm_flags & RTLD_NODELETE)) DlModule *
NOTHROW(DLFCN_CC libdl_dlfopen)(/*inherit(on_success)*/ fd_t fd, unsigned int mode);

/* Check if a given module is exception aware.
 * TODO: Figure out how we want to detect this condition...
 * @param: handle: The module to check
 * @return: 1 : The given module is exception aware
 * @return: 0 : The given module isn't exception aware
 * @return: * : The given module handler is invalid (s.a. `dlerror()') */
INTDEF WUNUSED NONNULL((1)) int
NOTHROW_NCX(DLFCN_CC libdl_dlexceptaware)(USER DlModule *handle) THROWS(E_SEGFAULT);

/* Return the handle of an already loaded library, given a static data/text pointer
 * @param: flags: Set of `DLGETHANDLE_F*' */
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF)) DlModule *
NOTHROW(DLFCN_CC libdl_dlgethandle)(void const *static_pointer, unsigned int flags);

/* Return the handle of an already loaded library, given its name
 * @param: name:  One of the following (checked in this order):
 *                 - "/lib/libc.so"
 *                 - "libc.so"
 *                 - "libc"
 *                 - "c"
 *                 - "/LIB/LIBC.SO"  (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC.SO"       (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC"          (requires `DLGETHANDLE_FNOCASE')
 *                 - "C"             (requires `DLGETHANDLE_FNOCASE')
 *                Alternatively, `NULL' can be passed to return a handle for the caller's module.
 * @param: flags: Set of `DLGETHANDLE_F*' */
INTDEF WUNUSED REF_IF(!(return->dm_flags & RTLD_NODELETE) && (flags & DLGETHANDLE_FINCREF)) DlModule *
NOTHROW_NCX(DLFCN_CC libdl_dlgetmodule)(USER char const *name, unsigned int flags) THROWS(E_SEGFAULT);

/* >> dladdr(3)
 * Query information on the symbol/module associated with a given `address'
 * @param: address: The address to query information about.
 * @param: info:    Output buffer for where to put information.
 * @return: 0 : Success.
 * @return: -1: Error (s.a. `dlerror()') */
INTDEF NONNULL((2)) int
NOTHROW_NCX(DLFCN_CC libdl_dladdr)(void const *address,
                                   USER Dl_info *info)
		THROWS(E_SEGFAULT);

/* >> dlinfo(3)
 * Query auxiliary information on `handle', according to `request'
 * @param: request: One of `RTLD_DI_*'.
 * @param: arg:     Request-specific data (see docs of `RTLD_DI_*' codes).
 * @return: 0 : Success.
 * @return: -1: Error (s.a. `dlerror()') */
INTDEF NONNULL((1)) int
NOTHROW_NCX(DLFCN_CC libdl_dlinfo)(USER DlModule *self, int request,
                                   USER void *arg);


/* Return the internally used file descriptor for the given module `handle'
 * Note  however that this  descriptor is usually  only opened for reading!
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * : An open file descriptor for the given module `handle'
 *              WARNING: Attempting  to  close()  this  handle  may  cause  future
 *                       operations  performed with the associated module to fail!
 *                       Additionally, using dlclose() to close `handle' after the
 *                       module's fd was already  closed will attempt to  re-close
 *                       that same fd, possibly closing  some other handle if  the
 *                       same slot was re-used in the mean time.
 * @return: -1: Error (s.a. `dlerror()') */
INTDEF WUNUSED NONNULL((1)) fd_t
NOTHROW_NCX(DLFCN_CC libdl_dlmodulefd)(USER DlModule *self) THROWS(E_SEGFAULT);

/* Return the internally  used filename for  the given module  `handle'
 * Note that this path is an absolute, canonical (realpath()) filename.
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * :    The absolute, unambiguous filename for the given module `handle'
 * @return: NULL:  Error (s.a. `dlerror()') */
INTDEF WUNUSED NONNULL((1)) char const *
NOTHROW_NCX(DLFCN_CC libdl_dlmodulename)(USER DlModule *self) THROWS(E_SEGFAULT);

/* Return the base address offset chosen by ASLR, which is added to addresses of the given module `handle'.
 * WARNING: This function  usually returns  `NULL' for  the root  executable, in  which case  dlerror()
 *          is not  modified, meaning  that  in order  to  safely use  this  function, you  must  first
 *          call `dlerror()'  in  order  to clear  any  existing  errors, then  invoke  this  function,
 *          and call `dlerror()'  again when NULL  is returned to  check if an  error really  occurred.
 *          Or alternatively,  you  can  simply  make  sure that  `handle'  isn't  invalid,  since  the
 *          only case  when this  function  can ever  fail  is when  `handle'  was already  closed,  is
 *          `NULL', or isn't a pointer returned by `dlopen(3D)', `dlgetmodule(3D)' or `dlgethandle(3D)'
 * @param: handle: A handle returned by `dlopen(3D)'.
 * @return: * : The load address / module base for the given `handle'.
 * @return: 0 : Error (s.a. `dlerror()'), or load-address of ZERO */
INTDEF WUNUSED NONNULL((1)) uintptr_t
NOTHROW_NCX(DLFCN_CC libdl_dlmodulebase)(USER DlModule *self) THROWS(E_SEGFAULT);

/* Lock a named section of a given dynamic library into memory.
 * @param: handle: Handle for the library who's section `name' should be locked & loaded.
 * @param: name:   Name of the section to load into memory.
 * @return: * :    A reference to a locked section object (s.a. the exposed portion of the struct above),
 *                 and allows the user to access the contents of the section, as it is loaded in  memory.
 *                 Note however that the actual  section data is usually mapped  as read-only, or at  the
 *                 very least `MAP_PRIVATE', meaning that writes aren't written back to the library file!
 * @return: NULL:  Error (s.a. `dlerror()'; usually: unknown section) */
INTDEF WUNUSED NONNULL((2)) REF DlSection *
NOTHROW_NCX(DLFCN_CC libdl_dllocksection)(USER DlModule *self,
                                          USER char const *name,
                                          unsigned int flags)
		THROWS(E_SEGFAULT);

/* Unlock a locked section, as previously returned by `dllocksection(3D)'
 * HINT: Think of this function as a decref(), where `dllocksection(3D)'
 *       returns a reference you inherit as the caller
 * @return: 0 : Successfully unlocked the given section `sect'
 * @return: * : Error (s.a. `dlerror()') */
INTDEF NONNULL((1)) int
NOTHROW_NCX(DLFCN_CC libdl_dlunlocksection)(USER REF DlSection *sect)
		THROWS(E_SEGFAULT);

/* Return the name of a given section, or NULL on error
 * WARNING: The name of a section can no longer be queried after the associated
 *          module  has been unloaded! If this has happened, `NULL' is returned
 *          and dlerror() is set accordingly.
 *          Because the names  of sections  are stored  alongside the  module, if  you
 *          can't guaranty that  the module  associated with the  section doesn't  get
 *          unloaded while you're accessing the section's name, you must first acquire
 *          your own reference  to that module  through use of  `dlsectionmodule(3D)':
 *          >> void *mod = dlsectionmodule(my_sect, DLGETHANDLE_FINCREF);
 *          >> char const *name = dlsectionname(my_sect);
 *          >> // Make use of `name' (also check if `name' is NULL; if it is, `mod'
 *          >> // will probably also be NULL if the module had already been unloaded)
 *          >> ...
 *          >> dlclose(mod); */
INTDEF WUNUSED NONNULL((1)) char const *
NOTHROW_NCX(DLFCN_CC libdl_dlsectionname)(USER DlSection *sect)
		THROWS(E_SEGFAULT);

/* Returns  the index of a given section, or `(size_t)-1' on error. */
INTDEF WUNUSED NONNULL((1)) size_t
NOTHROW_NCX(DLFCN_CC libdl_dlsectionindex)(USER DlSection *sect)
		THROWS(E_SEGFAULT);

/* Return the module associated with a given section, or `NULL' on error.
 * @param: flags: Set of `DLGETHANDLE_F*'
 * @return: * :   A pointer, or reference to the module handle (when `DLGETHANDLE_FINCREF' was given)
 * @return: NULL: Error (s.a. `dlerror()'; usually, the module was already unloaded) */
INTDEF WUNUSED NONNULL((1)) DlModule *
NOTHROW_NCX(DLFCN_CC libdl_dlsectionmodule)(USER DlSection *sect, unsigned int flags)
		THROWS(E_SEGFAULT);

/* Try to inflate compressed  module sections (`SHF_COMPRESSED'), returning  a
 * pointer  to a decompressed  data blob that is  lazily allocated for `sect',
 * and will be freed once the section ends up being unloaded. The given `sect'
 * may  not be loaded  with `DLLOCKSECTION_FNODATA' if  this function shall be
 * used  later; if the (compressed) data used  for backing `sect' has not been
 * loaded, this function will fail.
 * When the given `sect' isn't actually compressed, this function will simply
 * return  a pointer to `sect->ds_data', and fill `*psize' (if non-NULL) with
 * `ds_size'. Otherwise, inflated data and its size are returned.
 * NOTE: This function requires libdl to lazily load the KOS system library
 *       `libzlib.so', as found apart of  the KOS source tree. Should  that
 *       library not be loaded already,  or should loading of said  library
 *       fail for any reason, this function will also fail, and `dlerror()'
 *       will reflect what went wrong when trying to load said library.
 * NOTE: The backing memory for the deflated data blob is allocated lazily and
 *       will not be freed before `sect' is `dlunlocksection(3D)'ed the same #
 *       of times that it was `dllocksection(3D)'ed.
 * @param: psize: When non-NULL, store the size of the inflated (decompressed)
 *                data blob that is returned.
 * @return: * :   A pointer to the inflated data that is backing `sect'. When
 *                `sect'  isn't compressed, this  function will simply return
 *                the section's normal data blob, that is `sect->ds_data'
 * @return: NULL: Error (s.a. `dlerror()') */
INTDEF WUNUSED NONNULL((1)) void *
NOTHROW_NCX(DLFCN_CC libdl_dlinflatesection)(USER DlSection *sect,
                                             USER size_t *psize)
		THROWS(E_SEGFAULT);

/* Clear internal caches used by loaded modules in order to free  up
 * available memory. This function  is automatically called by  libc
 * when `mmap(2)' fails due to lack of available virtual or physical
 * memory. For more information, see `DL_REGISTER_CACHE(3D)'
 * @return: 0: No optional memory could be released.
 * @return: 1: Some optional memory was released. */
INTDEF int DLFCN_CC libdl_dlclearcaches(void) THROWS(...);

/* Perform an auxiliary control command about a given module `handle'
 * This function is used internally, and invocation requirements for different values
 * for `cmd' may change in the future. - It's purpose is to provide access to binary-
 * specific information about loaded modules.
 * @param: handle:   Handle of the module for which to query information,
 *                   or  NULL  to   query  for   the  root   application.
 *                   Some commands  may not  make use  of this  argument.
 * @param: cmd:      The command with which information should be requested.
 * @return: NULL: No information available, or no buffer was provided (depending on `cmd')
 * @return: NULL: Error: Unknown `cmd' (s.a. dlerror())
 * @return: NULL: Error: Invalid `handle' (s.a. dlerror()) */
INTDEF void *DLFCN_CC
libdl_dlauxctrl(USER DlModule *self, unsigned int type, ...)
		THROWS(E_SEGFAULT, ...);

INTDEF void *ASMCALL libdl____tls_get_addr(void); /* Only available on some architectures, with arch-specific semantics */
INTDEF void *LIBCCALL libdl___tls_get_addr(void *arg);


struct dltls_segment;

/* Allocate/Free a static TLS segment
 * These functions are called by by libc in  order to safely create a new thread, such  that
 * all current and future modules are able to store thread-local storage within that thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror()) */
INTDEF ATTR_MALLOC WUNUSED struct dltls_segment *
NOTHROW(DLFCN_CC libdl_dltlsallocseg)(void);

/* Free a previously allocated static TLS segment (usually called by `pthread_exit(3)' and friends). */
INTDEF NONNULL((1)) int DLFCN_CC
libdl_dltlsfreeseg(USER struct dltls_segment *ptr)
		THROWS(E_SEGFAULT, ...);

/* Return a pointer to the base of the given module's
 * TLS  segment,  as  seen form  the  calling thread.
 * In the case of dynamic TLS, allocate missing segments lazily,
 * logging a system error and exiting the calling application if
 * doing so fails. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) void *FCALL
libdl_dltlsbase(DlModule *__restrict self) THROWS(...);

/* DL-based TLS memory management API.
 * These functions may be used to dynamically allocate TLS memory that works everywhere where
 * ATTR_THREAD-based TLS memory also works. - However, using these functions, TLS memory  can
 * be allocated dynamically at runtime (behaving the same as a call to `dlopen(3D)' loading a
 * module containing a TLS segment would).
 * @param: num_bytes:      The size of the TLS segment (in bytes)
 * @param: min_alignment:  The minimum alignment requirements for the TLS segment base address.
 * @param: template_data:  Base address of an initialization template.
 *                         The first `template_size' bytes  of any per-thread data  segment
 *                         that gets allocated will be initialized to the contents of these
 *                         values before `perthread_init' is optionally invoked in order to
 *                         perform additional initialization.
 *                         This template is copied by this function and does not need to  keep
 *                         pointing at a valid memory location after `dltlsalloc(3D)' returns!
 * @param: template_size:  The size of `template_data' in bytes, indicating the number  of
 *                         leading bytes within the TLS segment that should be pre-defined
 *                         to mirror the contents of `template_data' at the time of a call
 *                         to this function (`template_data' itself need not remain  valid
 *                         or accessible after this function returns)
 *                         Any memory after `template_size', but before `num_bytes' is
 *                         initialized to all ZEROes, however `template_size' must not
 *                         be greater than  `num_bytes', and if  it is, this  function
 *                         returns `NULL' and sets `dlerror()' accordingly.
 * @param: perthread_init: An optional callback that will be invoked on a per-thread basis
 *                         in order to perform additional initialization of the associated
 *                         TLS segment within the associated thread.
 *                         This function will be called upon first access of the segment
 *                         within  the  thread  using  the  data  (s.a. `dltlsaddr(3D)')
 *                         @param: arg:  The value of `perthread_callback_arg' passed to `dltlsalloc'
 *                         @param: base: The base  address  of  the  associated  segment  within  the
 *                                       calling thread (same as the return value of `dltlsaddr(3D)')
 *                         @param: tls_segment: The TLS segment  to which `base'  belongs (usually  that
 *                                              of the calling thread, unless `dltlsaddr2(3D)' was used)
 * @param: perthread_fini: An optional callback  that behaves  similar to  `perthread_init',
 *                         but called  by `pthread_exit(3)'  or any  other thread  finalizer
 *                         (more specifically: by `dltlsfreeseg(3D)') within any thread that
 *                         has been seen  using the  associated segment, and  causing it  to
 *                         be allocated and initialized for that thread.
 *                         Note that the actual thread calling this function may not necessarily
 *                         be the same thread that originally called `perthread_init', only that
 *                         any  call to `perthread_init' will always be followed by another call
 *                         to this function at some later point in time!
 * @param: perthread_callback_arg: A user-specified argument passed to the init/fini callbacks.
 * @return: * :            An opaque handle for the newly created TLS segment.
 *                         This handle may be used in future calls to `dltlsaddr(3D)', and can be
 *                         destroyed (causing  all  threads  that had  previously  allocated  the
 *                         segment  to delete  it and  optionally invoke  finalizer callbacks) by
 *                         passing it to `dltlsfree(3D)'
 * @return: NULL:          Failed to allocate the TLS segment (s.a. `dlerror()') */
INTDEF WUNUSED DlModule *
NOTHROW(DLFCN_CC libdl_dltlsalloc)(size_t num_bytes, size_t min_alignment,
                                   USER void const *template_data, size_t template_size,
                                   void (DLFCN_CC USER *perthread_init)(void *arg, void *base, void *tls_segment),
                                   void (DLFCN_CC USER *perthread_fini)(void *arg, void *base, void *tls_segment),
                                   USER void *perthread_callback_arg);

/* Free a TLS segment previously allocated with `dltlsalloc(3D)' */
INTDEF int
NOTHROW_NCX(DLFCN_CC libdl_dltlsfree)(USER DlModule *self)
		THROWS(E_SEGFAULT);

#ifndef __DLFCN_DLTLSADDR_CC
#define __DLFCN_DLTLSADDR_CC  __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR_CC */
#ifndef __DLFCN_DLTLSADDR2_CC
#define __DLFCN_DLTLSADDR2_CC __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR2_CC */


/* Return the calling thread's base address of the TLS segment associated with `tls_handle'
 * NOTE: TLS  Segments are allocated and initialized lazily, meaning that the initializer
 *       passed to `dltlsalloc(3D)' will be called by this function upon the first use of
 *       that  segment within  each individual thread,  also causing the  finalizer to be
 *       enqueued for invocation when the calling thread exits.
 * WARNING: The order in which TLS finalizers are invoked is entirely UNDEFINED!
 * NOTE: the given  `tls_handle' may  also be  a module  handle, as  returned by  `dlopen(3D)',
 *       in which case this function  returns a pointer to the  TLS segment of that module  for
 *       the calling thread (e.g.: Such a pointer is needed by `unwind_emulator_t::sm_tlsbase')
 * @return: * :   Pointer to the base of the TLS segment associated with `tls_handle' within the calling thread.
 * @return: NULL: Invalid `tls_handle', or allocation/initialization failed. (s.a. `dlerror()') */
INTDEF WUNUSED void *__DLFCN_DLTLSADDR_CC
libdl_dltlsaddr(USER DlModule *self)
		THROWS(E_SEGFAULT, ...);

/* Same as `dltlsaddr(3D)', but used to lookup a TLS block relative to a given `tls_segment',
 * where the later was previously  allocated using `dltlsallocseg(3D)'. This function  allows
 * the caller to get a pointer to the TLS  data of another thread, and is used to  initialize
 * the `pthread_self()' of a newly created thread from within `pthread_create()'.
 * @return: * :   Pointer to the base of the TLS segment associated with `tls_handle'
 *                within the given `tls_segment'.
 * @return: NULL: Invalid `tls_handle' or `tls_segment', or
 *                allocation/initialization failed. (s.a. `dlerror()') */
INTDEF WUNUSED void *__DLFCN_DLTLSADDR2_CC
libdl_dltlsaddr2(USER DlModule *self, USER struct dltls_segment *seg)
		THROWS(E_SEGFAULT, ...);
INTDEF WUNUSED void *__DLFCN_DLTLSADDR2_CC
libdl_dltlsaddr2_noinit(DlModule *__restrict self,
                        USER struct dltls_segment *seg);

/* Similar to `libdl_dltlsaddr()', but do no lazy allocation
 * and return NULL if the module doesn't have a TLS segment. */
INTDEF WUNUSED NONNULL((1)) void *
NOTHROW_NCX(CC DlModule_TryGetTLSAddr)(USER DlModule *self)
		THROWS(E_SEGFAULT);

/* Enumerate all loaded modules, as  well as information about  them.
 * Enumeration stops when `*callback' returns a non-zero value, which
 * will then also be returned  by this function. Otherwise, `0'  will
 * be returned after all modules have been enumerated. */
INTDEF NONNULL((1)) int DLFCN_CC
libdl_iterate_phdr(USER __dl_iterator_callback callback, USER void *arg)
		THROWS(E_SEGFAULT, ...);

/* Invoke the  static initializers  of  all currently  loaded  modules.
 * This is called late during  initial module startup once the  initial
 * set of  libraries,  +  the initial  application  have  been  loaded.
 * Note that initializers are invoked in reverse order of those modules
 * appearing within `dl_globals.dg_alllist',  meaning that the  primary
 * application's  __attribute__((constructor))  functions  are  invoked
 * _AFTER_ those from (e.g.) libc. */
INTDEF void CC DlModule_RunAllStaticInitializers(void) THROWS(...);

/* Initialize the static TLS bindings table from the set of currently loaded modules. */
INTDEF WUNUSED int NOTHROW_RPC(CC DlModule_InitStaticTLSBindings)(void);

/* Remove the given module from the table of static TLS bindings. */
INTDEF NONNULL((1)) void NOTHROW(CC DlModule_RemoveTLSExtension)(DlModule *__restrict self);

/* Run finalizers for all TLS segments allocated within the calling thread. */
INTDEF void CC DlModule_RunAllTlsFinalizers(void) THROWS(...);

#ifdef ELF_ARCH_IS_R_JMP_SLOT
/* Called from JMP_SLOT relocations (s.a. `arch/i386/rt32.S') */
INTDEF void ASMCALL dl_load_lazy_relocation(void);

/* Bind a lazy relocation, resolving its JMP relocation entry and returning the
 * absolute address of the bound symbol. - If the symbol can't be resolved, log
 * a system error and exit the calling application. */
INTDEF WUNUSED NONNULL((1)) ElfW(Addr) FCALL
dl_bind_lazy_relocation(DlModule *__restrict self,
#if ELF_ARCH_LAZYINDX
                        uintptr_t jmp_rel_index
#else /* ELF_ARCH_LAZYINDX */
                        uintptr_t jmp_rel_offset
#endif /* !ELF_ARCH_LAZYINDX */
                        )
		THROWS(...);
#endif /* ELF_ARCH_IS_R_JMP_SLOT */

INTDEF ATTR_COLD int NOTHROW(CC dl_seterror_badptr)(USER void *ptr);
INTDEF ATTR_COLD int NOTHROW(CC dl_seterror_badmodule)(USER void *modptr);
INTDEF ATTR_COLD int NOTHROW(CC dl_seterror_badsection)(USER void *sectptr);
INTDEF ATTR_COLD int NOTHROW(CC dl_seterror_nomem)(void);
INTDEF ATTR_COLD int NOTHROW(CC dl_seterror_no_mod_at_addr)(USER void const *static_pointer);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW(CC dl_seterror_header_read_error)(char const *__restrict filename);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW(CC dl_seterror_notelf)(char const *__restrict filename);
INTDEF ATTR_COLD NONNULL((1, 2)) int NOTHROW_NCX(CC dl_seterror_nosect)(USER DlModule const *self, USER char const *name) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW_NCX(CC dl_seterror_nosect_index)(USER DlModule const *self, size_t index) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW_NCX(CC dl_seterror_nosym_global)(USER char const *symname) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1, 2)) int NOTHROW_NCX(CC dl_seterror_nosym_next)(DlModule const *__restrict after, USER char const *symname) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1, 2)) int NOTHROW_NCX(CC dl_seterror_nosym_in)(USER DlModule const *mod, USER char const *symname) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW_NCX(CC dl_seterror_nosym_next_badcaller)(USER char const *symname) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW_NCX(CC dl_seterror_dlopen_failed)(USER char const *libname) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1, 2)) int NOTHROW_NCX(CC dl_seterr_section_mmap_failed)(USER DlModule const *self, USER char const *section_filename) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW_NCX(CC dl_seterr_section_index_mmap_failed)(USER DlModule const *self, size_t section_index) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW_NCX(VCC dl_seterrorf)(char const *__restrict format, ...) THROWS(E_SEGFAULT);
INTDEF ATTR_COLD NONNULL((1)) int NOTHROW_NCX(CC dl_vseterrorf)(char const *__restrict format, va_list args) THROWS(E_SEGFAULT);

/* Return the address of a builtin function (e.g. `dlopen(3D)') */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) void *NOTHROW_NCX(CC dlsym_builtin)(USER char const *name) THROWS(E_SEGFAULT);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) size_t NOTHROW_NCX(CC dlsym_builtin_size)(USER char const *name) THROWS(E_SEGFAULT);
INTDEF ATTR_PURE WUNUSED NONNULL((1)) DlSection *NOTHROW_NCX(CC dlsec_builtin)(USER char const *name) THROWS(E_SEGFAULT);
INTDEF ATTR_CONST WUNUSED DlSection *NOTHROW(CC dlsec_builtin_index)(size_t sect_index);
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(CC dlsec_builtin_name)(size_t sect_index);

/* Return the address of a function `name'  that is required by the RTLD  core
 * and  must be defined by one of the  loaded libraries. - If no such function
 * is defined, log an error message to the system log and terminate the hosted
 * application ungracefully. */
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) void *
NOTHROW(FCALL dl_require_global)(char const *__restrict name);

/* Set to true if the sys_debugtrap() system call is disabled. */
INTDEF bool sys_debugtrap_disabled;

/* [0..1][ATOMIC(APPEND)] Chain of registered DL extensions.
 * NOTE: Once registered, a DL extension cannot be  deleted! */
INTDEF struct dlmodule_format *dl_extensions;

/* Lazily initialize and return the libdl core ops V-table. */
INTDEF ATTR_RETNONNULL WUNUSED struct dlcore_ops *NOTHROW(CC dl_getcoreops)(void);



DECL_END

#endif /* !GUARD_LIBDL_DL_H */
