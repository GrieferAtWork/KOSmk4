/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _DLFCN_H
#define _DLFCN_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/dlfcn.h>
#include <bits/types.h>

/* NOTE: To use anything from this file, you must link with '-ldl' */

#if (!defined(__DL_REGISTER_CACHE) && \
     !defined(__NO_DL_REGISTER_CACHE)) || \
     (defined(__KERNEL__) && defined(__KOS__))
#define __NO_DL_REGISTER_CACHE   1
#endif

__SYSDECL_BEGIN

#ifndef __DLFCN_CALL
#define __DLFCN_CALL __LIBCCALL
#endif /* !__DLFCN_CALL */

/* User functions for run-time dynamic loading.
   Copyright (C) 1995-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifdef __USE_GNU

/* If the first argument of `dlsym' or `dlvsym' is set to RTLD_NEXT
 * the run-time address of the symbol called NAME in the next shared
 * object is returned.  The "next" relation is defined by the order
 * the shared objects were loaded. */
#define RTLD_NEXT    ((void *)-1)

/* If the first argument to `dlsym' or `dlvsym' is set to RTLD_DEFAULT
 * the run-time address of the symbol called NAME in the global scope
 * is returned.
 * HINT: The global scope is the same as that of the root executable,
 *       as seen under /proc/PID/exe. */
#define RTLD_DEFAULT  ((void *)0)

/* Type for namespace indeces. */
typedef long int Lmid_t;

/* Special namespace ID values. */
#define LM_ID_BASE    0  /* Initial namespace.  */
#define LM_ID_NEWLM (-1) /* For dlmopen: request new namespace.  */
#endif

#ifdef __CC__

#ifndef __KERNEL__
/* @param: MODE: Set of `RTLD_*' */
__IMPDEF __ATTR_WUNUSED void *__NOTHROW_NCX(__DLFCN_CALL dlopen)(char const *__filename, int __mode);
__IMPDEF __ATTR_NONNULL((1)) int __NOTHROW_NCX(__DLFCN_CALL dlclose)(void *__handle);
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((2)) void *__NOTHROW_NCX(__DLFCN_CALL dlsym)(void *__handle, char const *__restrict __symbol_name);
__IMPDEF char *__NOTHROW_NCX(__DLFCN_CALL dlerror)(void);

#ifdef __USE_BSD
struct __dlfunc_arg { int __dlfunc_dummy; };
typedef void (*dlfunc_t)(struct __dlfunc_arg);
/* Alias for `dlsym()' that allows the return value to be cases to a function prototype. */
__REDIRECT(__IMPDEF,__ATTR_WUNUSED,dlfunc_t,__NOTHROW_NCX,__DLFCN_CALL,
           dlfunc,(void *__handle, char const *__restrict __symbol_name),dlsym,(__handle, __symbol_name))
#endif /* __USE_BSD */

/* BSD also has a function `fdlopen()' that does the same as our's does. */
#if (defined(__USE_KOS) || defined(__USE_BSD)) && defined(__KOS__)
#if __KOS_VERSION__ >= 400
/* Open a library, given a file descriptor previously acquired by `open()'
 * NOTE: This function will inherit the given `FD' on success.
 * @param: MODE: Set of `RTLD_*' */
__REDIRECT(__IMPDEF,__ATTR_WUNUSED,void *,__NOTHROW_NCX,__DLFCN_CALL,fdlopen,(/*inherit(on_success)*/__fd_t __fd, int __mode),dlfopen,(__fd,__mode))
#endif /* __KOS_VERSION__ >= 400 */
#endif /* (__USE_KOS || __USE_BSD) && __KOS__ */


#if defined(__USE_KOS) && defined(__KOS__)
#if __KOS_VERSION__ >= 400
/* New DL Functions added with KOSmk4 */


/* TODO: Some function for enumeration all loaded modules. */


/* Check if a given module is exception aware.
 * TODO: Figure out how we want to detect this condition...
 * @param: HANDLE: The module to check
 * @return: 1:  The given module is exception aware
 * @return: 0:  The given module isn't exception aware
 * @return: -1: The given module handler is invalid (s.a. `dlerror()') */
__IMPDEF __ATTR_WUNUSED int
__NOTHROW_NCX(__DLFCN_CALL dlexceptaware)(void *__handle);


#define DLGETHANDLE_FNORMAL 0x0000 /* Return weak pointer to a module handle */
#define DLGETHANDLE_FINCREF 0x0001 /* Return a new reference, that must be closed by `dlclose(return)' */
#define DLGETHANDLE_FNOCASE 0x0002 /* For `dlgetmodule()': Ignore casing when comparing module names. */

/* Return the handle of an already loaded library, given a static data/text pointer
 * @param: FLAGS: Set of `DLGETHANDLE_F*' */
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CALL dlgethandle)(void const *__static_pointer,
                                        unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));

/* Return the handle of an already loaded library, given its name
 * @param: NAME:  One of the following (checked in this order):
 *                 - "/lib/libc.so"
 *                 - "libc.so"
 *                 - "libc"
 *                 - "c"
 *                 - "/LIB/LIBC.SO"  (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC.SO"       (requires `DLGETHANDLE_FNOCASE')
 *                 - "LIBC"          (requires `DLGETHANDLE_FNOCASE')
 *                 - "C"             (requires `DLGETHANDLE_FNOCASE')
 *                Alternatively, `NULL' can be passed to return a handle for the caller's module.
 * @param: FLAGS: Set of `DLGETHANDLE_F*' */
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CALL dlgetmodule)(char const *__name,
                                        unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));

/* Return the internally used file descriptor for the given module `HANDLE'
 * Note however that this descriptor is usually only opened for reading!
 * @param: HANDLE: A handle returned by `dlopen()'.
 * @return: * : An open file descriptor for the given module `HANDLE'
 *              WARNING: Attempting to close() this handle may cause future
 *                       operations performed with the associated module to fail!
 * @return: -1: Error (s.a. `dlerror()') */
__IMPDEF __ATTR_WUNUSED __fd_t __NOTHROW_NCX(__DLFCN_CALL dlmodulefd)(void *__handle);

/* Return the internally used filename for the given module `HANDLE'
 * @param: HANDLE: A handle returned by `dlopen()'.
 * @return: * :    The absolute, unambiguous filename for the given module `HANDLE'
 * @return: NULL:  Error (s.a. `dlerror()') */
__IMPDEF __ATTR_WUNUSED char const *__NOTHROW_NCX(__DLFCN_CALL dlmodulename)(void *__handle);

/* Return the base address offset chosen by ASLR, which is added to addresses of the given module `HANDLE'.
 * WARNING: This function usually returns `NULL' for the root executable, in which case dlerror()
 *          is not modified, meaning that in order to safely use this function, you must first
 *          call `dlerror()' in order to clear any existing errors, then invoke this function,
 *          and call `dlerror()' again when NULL is returned to check if an error really occurred.
 *          Or alternatively, you can simply make sure that `HANDLE' isn't invalid, since the
 *          only case when this function can ever fail is when `HANDLE' was already closed, is
 *         `NULL', or isn't a pointer returned by `dlopen()', `dlgetmodule()' or `dlgethandle()'
 * @param: HANDLE: A handle returned by `dlopen()'.
 * @return: * :    The load address / module base for the given `HANDLE'.
 * @return: NULL:  Error (s.a. `dlerror()') */
__IMPDEF __ATTR_WUNUSED void *__NOTHROW_NCX(__DLFCN_CALL dlmodulebase)(void *__handle);


struct dl_section {
	void       *const ds_data;    /* [0..ds_size][const] Memory mapping for the section's contents. */
	__size_t    const ds_size;    /* [const] Size of the section (in bytes) */
	__size_t    const ds_entsize; /* [const] Section entity size (or 0 if unknown) */
	__uintptr_t const ds_link;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_info;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
};

#define DLLOCKSECTION_FNORMAL   0x0000 /* Normal section locking flags. */
#define DLLOCKSECTION_FINDEX    0x0001 /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define DLLOCKSECTION_FNODATA   0x0002 /* Do not lock section data into memory, though if the section had already
                                        * been loaded, then this flag is simply ignored. */

/* Lock a named section of a given dynamic library into memory.
 * @param: HANDLE: Handle for the library who's section `NAME' should be locked & loaded.
 * @param: NAME:   Name of the section to load into memory.
 * @return: * :    A reference to a locked section object (s.a. exposed portion of the section above),
 *                 and allows the user to access the contents of the section, as it is loaded in memory.
 *                 Note however that the actual section data is usually mapped as read-only!
 * @return: NULL:  Error (s.a. `dlerror()'; usually: unknown section) */
__IMPDEF __ATTR_WUNUSED /*REF*/struct dl_section *
__NOTHROW_NCX(__DLFCN_CALL dllocksection)(void *__handle,
                                          char const *__restrict __name,
                                          unsigned int __flags __DFL(DLLOCKSECTION_FNORMAL));

/* Unlock a locked section, as previously returned by `dllocksection()'
 * HINT: Think of this function as a decref(), where `dllocksection()'
 *       returns a reference you inherit as the caller
 * @return: 0 : Successfully unlocked the given section `SECT'
 * @return: -1: Error (s.a. `dlerror()') */
__IMPDEF int
__NOTHROW_NCX(__DLFCN_CALL dlunlocksection)(/*REF*/struct dl_section *__sect);

/* Return the name of a given section, or NULL on error
 * WARNING: The name of a section can no longer be queried after the associated
 *          module has been unloaded! If this has happened, NULL is returned
 *          and dlerror() is set accordingly.
 *          Because the names of sections are stored alongside the module, if
 *          you can't guaranty that the module associated with the section doesn't
 *          get unloaded while you're accessing the section's name, you must first
 *          acquire your own reference to that module through use of `dlsectionmodule()':
 *          >> void *mod = dlsectionmodule(my_sect, DLGETHANDLE_FINCREF);
 *          >> char const *name = dlsectionname(my_sect);
 *          >> // Make use of `name' (also check if `name' is NULL; if it is, `mod'
 *          >> // will probably also be NULL if the module had already been unloaded)
 *          >> ...
 *          >> dlclose(mod); */
__IMPDEF __ATTR_WUNUSED char const *
__NOTHROW_NCX(__DLFCN_CALL dlsectionname)(struct dl_section *__sect);

/* Returns the index of a given section, or (size_t)-1 on error. */
__IMPDEF __ATTR_WUNUSED __size_t
__NOTHROW_NCX(__DLFCN_CALL dlsectionindex)(struct dl_section *__sect);

/* Return the module associated with a given section, or NULL on error.
 * @param: FLAGS: Set of `DLGETHANDLE_F*' 
 * @return: * :   A pointer, or reference to the module handle (when `DLGETHANDLE_FINCREF' was given)
 * @return: NULL: Error (s.a. `dlerror()'; usually, the module was already unloaded) */
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CALL dlsectionmodule)(struct dl_section *__sect,
                                            unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));

/* Clear internal caches used by loaded modules in order to free up available memory.
 * This function is automatically called by libc when mmap() fails due to lack
 * of available virtual or physical memory.
 * For more information, see `DL_REGISTER_CACHE()'
 * @return: 0: No optional memory could be released.
 * @return: 1: Some optional memory was released. */
__IMPDEF int __NOTHROW_NCX(__DLFCN_CALL dlclearcaches)(void);

/* Allocate/Free a static TLS segment
 * These functions are called by by libc in order to safely create a new thread, such that
 * all current and future modules are able to store thread-local storage within that thread.
 * NOTE: The caller is responsible to store the returned segment to the appropriate TLS register.
 * @return: * :   Pointer to the newly allocated TLS segment.
 * @return: NULL: Error (s.a. dlerror()) */
__IMPDEF void *__NOTHROW_NCX(__DLFCN_CALL dltlsallocseg)(void);

/* Free a previously allocated static TLS segment (usually called by `pthread_exit()' and friends). */
__IMPDEF int __NOTHROW_NCX(__DLFCN_CALL dltlsfreeseg)(void *__ptr);

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
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CALL dltlsalloc)(__size_t __num_bytes, __size_t __min_alignment,
                                       void const *__template_data, __size_t __template_size,
                                       void (__LIBCCALL *__perthread_init)(void *__arg, void *__base),
                                       void (__LIBCCALL *__perthread_fini)(void *__arg, void *__base),
                                       void *__perthread_callback_arg);

/* Free a TLS segment previously allocated with `dltlsalloc' */
__IMPDEF __ATTR_WUNUSED int __NOTHROW_NCX(__DLFCN_CALL dltlsfree)(void *__tls_handle);

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
__IMPDEF __ATTR_WUNUSED void *__NOTHROW_NCX(__DLFCN_CALL dltlsaddr)(void *__tls_handle);


/* Return auxilary information about a given module `HANDLE'
 * This function is used internally, and invocation requirements for different values
 * for `TYPE' may change in the future. - It's purpose is to provide access to binary-
 * specific information about loaded modules.
 * @param: HANDLE:   Handle of the module for which to query information,
 *                   or NULL to query for the root application.
 * @param: TYPE:     The type of information that is being requested.
 *                   This argument affects how (and if) the BUF and PAUXVLEN arguments are used.
 * @param: BUF:      An optional buffer (required for some types of informations)
 * @param: PAUXVLEN: When non-NULL, used as either an IN-field for the given buffer
 *                   size and OUT-field for the used buffer size, or as an OUT-field
 *                   for the number of entires within the returned vector.
 * @return: * :   The base pointer to type-specific aux information.
 * @return: buf:  Information was written to `BUF' (only returned with certain values for `TYPE')
 * @return: NULL: No information available, or no buffer was provided (depending on `TYPE')
 * @return: NULL: Error: Unknown `TYPE' (s.a. dlerror())
 * @return: NULL: Error: Invalid `HANDLE' (s.a. dlerror()) */
__IMPDEF __ATTR_WUNUSED void *__NOTHROW_NCX(__DLFCN_CALL dlauxinfo)(void *__handle, unsigned int __type,
                                                                    void *__buf, __size_t *__pauxvlen);
#define DLAUXINFO_ELF_PHDR       0xef01 /* Returns the module's vector of program headers (`Elf_Phdr *')
                                         * Does not make use of `BUF' and stores the number of headers in `*PAUXVLEN' */
#define DLAUXINFO_ELF_SHDR       0xef02 /* Returns the module's vector of section headers (`Elf_Shdr *')
                                         * Does not make use of `BUF' and stores the number of headers in `*PAUXVLEN' */
#define DLAUXINFO_ELF_DYN        0xef03 /* Returns the module's vector of dynamic tags (`Elf_Dyn *')
                                         * Does not make use of `BUF' and stores the number of headers in `*PAUXVLEN' */
#define DLAUXINFO_ELF_DYNSYM     0xef04 /* Returns the module's vector of dynamic symbol table (`Elf_Sym *')
                                         * Does not make use of `BUF' and stores the number of symbols in `*PAUXVLEN'
                                         * If the number of symbols is unknown, store `(size_t)-1' in `*PAUXVLEN' */
#define DLAUXINFO_ELF_DYNSTR     0xef05 /* Returns the module's dynamic string table (`char const *')
                                         * Does not make use of `BUF' or `PAUXVLEN' */
#define DLAUXINFO_ELF_SHSTRTAB   0xef06 /* Returns the module's section header name string table (`char const *')
                                         * Does not make use of `BUF' or `PAUXVLEN' */
#define DLAUXINFO_ELF_DEPENDS    0xef07 /* Returns the module's vector of module dependencies (`MODULE **')
                                         * Does not make use of `BUF' and stores the number of dependencies in `*PAUXVLEN' */


/* Register a cache-clear function to-be invoked
 * when system/application memory starts to run out.
 * The prototype of such a function looks like:
 * >> DECL_BEGIN // Needs to be declared with `extern "C"' in c++-mode
 * >> DL_REGISTER_CACHE(my_cache_clear_function);
 * >> int my_cache_clear_function(void) {
 * >>     if (clear_my_caches() != NO_CACHES_CLEARED)
 * >>         return 1; // Hint that memory may have become available.
 * >>     return 0;     // Hint that no additional memory became available.
 * >> }
 * >> DECL_END
 * Functions registered like this from all loaded modules will be executed
 * when `dlclearcaches()' is called (which is called when mmap() fails due
 * to lack of memory, which itself is called when malloc() needs to allocate
 * more memory, where failure to acquire some would normally result in it
 * returning NULL. - So long as any one of the DL-cache functions returns
 * non-zero, the mmap() operation will be re-attempted a limited number of
 * times) */
#ifndef DL_REGISTER_CACHE
#ifndef __NO_DL_REGISTER_CACHE
#   define DL_REGISTER_CACHE(func)  __DL_REGISTER_CACHE(func)
#else
#   define DL_REGISTER_CACHE(func)  /* nothing */
#endif
#endif /* !DL_REGISTER_CACHE */

#else /* __KOS_VERSION__ >= 400 */
/* WARNING: In KOS v300, `fdlopen()' didn't inherit the given `FD' on success! */
__IMPDEF __ATTR_WUNUSED void *__NOTHROW_NCX(__DLFCN_CALL fdlopen)(__fd_t __fd, int __mode);
#endif /* __KOS_VERSION__ < 400 */
#endif /* __USE_KOS || __KOS__ */
#endif /* !__KERNEL__ */

#ifdef __USE_GNU

typedef struct {
#ifdef __CYG_COMPAT__
	char        dli_fname[4096]; /* File name of defining object. */
#else
	char const *dli_fname; /* File name of defining object. */
#endif
	void       *dli_fbase; /* Load address of that object. */
	char const *dli_sname; /* Name of nearest symbol. */
	void       *dli_saddr; /* Exact value of nearest symbol. */
} Dl_info;

enum {
	RTLD_DL_SYMENT  = 1,
	RTLD_DL_LINKMAP = 2
};
enum {
	RTLD_DI_LMID        = 1,
	RTLD_DI_LINKMAP     = 2,
	RTLD_DI_CONFIGADDR  = 3,
	RTLD_DI_SERINFO     = 4,
	RTLD_DI_SERINFOSIZE = 5,
	RTLD_DI_ORIGIN      = 6,
	RTLD_DI_PROFILENAME = 7,
	RTLD_DI_PROFILEOUT  = 8,
	RTLD_DI_TLS_MODID   = 9,
	RTLD_DI_TLS_DATA    = 10,
	RTLD_DI_MAX         = 10
};

typedef struct {
	char        *dls_name;
	unsigned int dls_flags;
} Dl_serpath;

typedef struct {
	size_t       dls_size;
	unsigned int dls_cnt;
	Dl_serpath   dls_serpath[1];
} Dl_serinfo;

#ifndef __KERNEL__
__IMPDEF __ATTR_NONNULL((2)) int (__DLFCN_CALL dladdr)(void const *__address, Dl_info *__info);
#ifdef __CRT_GLC
__IMPDEF void *(__DLFCN_CALL dlmopen)(Lmid_t __nsid, char const *__file, int __mode);
__IMPDEF __ATTR_NONNULL((2,3)) void *(__DLFCN_CALL dlvsym)(void *__restrict __handle, char const *__restrict __name, char const *__restrict __version);
__IMPDEF __ATTR_NONNULL((2)) int (__DLFCN_CALL dladdr1)(void const *__address, Dl_info *__info, void **__extra_info, int __flags);
__IMPDEF __ATTR_NONNULL((1,3)) int (__DLFCN_CALL dlinfo)(void *__restrict __handle, int __request, void *__restrict __arg);
#endif /* __CRT_GLC */
#endif /* !__KERNEL__ */

#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_DLFCN_H */
