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
#ifndef _KOS_HYBRID_LIBRARY_H
#define _KOS_HYBRID_LIBRARY_H 1
#ifndef _KOS_SOURCE
#define _KOS_SOURCE 1
#ifdef _DLFCN_H
#error "This file must be #include-ed before `<dlfcn.h>'"
#endif /* _DLFCN_H */
#ifndef __USE_KOS
#define __USE_KOS 1
#endif /* !__USE_KOS */
#endif /* !_KOS_SOURCE */

/* A hybrid compatibility header for writing code that work both in user-space,
 * as well as in kernel-space with the functionality to access the intersection
 * of DL-functionality possible on both ends (e.g. section locking).
 * NOTE: Even though insmod() could be compared to dlopen(), don't provide a
 *       compatibility intermediate for these two since their meaning is quite
 *       different. */

#include <__crt.h>
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/bits/library.h>

#ifdef __KERNEL__
#include <kernel/driver.h>
#else
#include <dlfcn.h>
#endif

__DECL_BEGIN

#ifdef __CC__

#ifndef __REF
#ifdef REF
#define __REF REF
#else
#define __REF /* nothing */
#endif
#endif /* !__REF */


#ifdef __INTELLISENSE__
#define LIBRARY_LOCKSECTION_FNORMAL  0x00 /* Normal section locking flags. */
#define LIBRARY_LOCKSECTION_FINDEX   0x01 /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define LIBRARY_LOCKSECTION_FNODATA  0x02 /* Do not lock section data into memory, though if the section had already
                                           * been loaded, then this flag is simply ignored. */

/* Return either the kernel core library, or the library of the base application
 * NOTE: This function does _NOT_ return a reference! */
__ATTR_RETNONNULL library_handle_t library_basemodule(void);

/* Return the file (INode / file-descriptor) from which the library/driver was loaded. */
__ATTR_NONNULL((1)) library_file_t library_getfile(library_handle_t __lib);

/* Return the absolute filename of the driver/library */
__ATTR_NONNULL((1)) char const *library_getfilename(library_handle_t __lib);

/* Return the load address (offset added to module-relative pointers) for the library/driver */
__ATTR_NONNULL((1)) void *library_getbase(library_handle_t __lib);

/* Lookup a symbol within the given library and return its address.
 * Returns NULL if no such symbol exists. */
__ATTR_NONNULL((1, 2)) void *library_symbol(library_handle_t __lib, char const *__symname);

/* Lock a section of the library into memory and return a handle to that section.
 * Returns NULL if no such section exists.
 * Upon success, the following fields of the returned handle can be used portably:
 *   - ds_data    -- [0..ds_size][const] Memory mapping for the section's contents
 *   - ds_size    -- [const] Size of the section (in bytes)
 *   - ds_entsize -- [const] Section entity size (or 0 if unknown)
 *   - ds_link    -- [const] Index of another section that is linked by this one (or `0' if unused)
 *   - ds_info    -- [const] Index of another section that is linked by this one (or `0' if unused) */
__ATTR_NONNULL((1, 2)) __ATTR_WUNUSED __REF section_handle_t
library_locksection(library_handle_t __lib, char const *__sectname, __uintptr_t __flags);

/* Unlock a section previously locked into memory with `library_locksection()'. */
__ATTR_NONNULL((1)) void library_unlocksection(__REF section_handle_t __sect);

/* Return a reference to the library/driver containing `STATIC_POINTER'
 * If no such library/driver exists, return NULL instead. */
__ATTR_WUNUSED __REF library_handle_t library_ataddr(void const *__static_pointer);

/* Decrement the reference counter of a given library. */
__ATTR_NONNULL((1)) void library_decref(library_handle_t __lib);


#elif defined(__KERNEL__)

#define LIBRARY_LOCKSECTION_FNORMAL  DRIVER_SECTION_LOCK_FNORMAL  /* Normal section locking flags. */
#define LIBRARY_LOCKSECTION_FINDEX   DRIVER_SECTION_LOCK_FINDEX   /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define LIBRARY_LOCKSECTION_FNODATA  DRIVER_SECTION_LOCK_FNODATA  /* Do not lock section data into memory, though if the section had already
                                                                   * been loaded, then this flag is simply ignored. */

#define library_basemodule()                      (&kernel_driver)
#define library_getfile(lib)                      driver_getfile(lib)
#define library_getfilename(lib)                  driver_getfilename(lib)
#define library_getbase(lib)                      ((lib)->d_loadaddr)
#define library_symbol(lib, symname)              driver_symbol(lib, symname, __NULLPTR)
#define library_locksection(lib, sectname, flags) driver_section_lock(lib, sectname, flags)
#define library_unlocksection(sect)               decref(sect)
#define library_ataddr(static_pointer)            driver_at_address(static_pointer)
#define library_decref(lib)                       decref(lib)

#else /* __KERNEL__ */

#define LIBRARY_LOCKSECTION_FNORMAL  DLLOCKSECTION_FNORMAL  /* Normal section locking flags. */
#define LIBRARY_LOCKSECTION_FINDEX   DLLOCKSECTION_FINDEX   /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define LIBRARY_LOCKSECTION_FNODATA  DLLOCKSECTION_FNODATA  /* Do not lock section data into memory, though if the section had already
                                                             * been loaded, then this flag is simply ignored. */

#define library_getfile(lib)                      dlmodulefd(lib)
#define library_getfilename(lib)                  dlmodulename(lib)
#define library_getbase(lib)                      dlmodulebase(lib)
#define library_symbol(lib, symname)              dlsym(lib, symname)
#define library_decref(lib)                       dlclose(lib)

#ifdef GUARD_LIBDL_API_H
#define library_locksection(lib, sectname, flags) ((__REF section_handle_t)dllocksection(lib, sectname, flags))
#define library_unlocksection(sect)                 dlunlocksection((__REF struct dl_section *)(sect))
#define library_ataddr(static_pointer)            ((__REF library_handle_t)dlgethandle(static_pointer, DLGETHANDLE_FINCREF))
#define library_basemodule()                      ((library_handle_t)dlopen(__NULLPTR, 0))
#else /* GUARD_LIBDL_API_H */
#define library_locksection(lib, sectname, flags)   dllocksection(lib, sectname, flags)
#define library_unlocksection(sect)                 dlunlocksection(sect)
#define library_ataddr(static_pointer)              dlgethandle(static_pointer, DLGETHANDLE_FINCREF)
#define library_basemodule()                        dlopen(__NULLPTR, 0)
#endif /* !GUARD_LIBDL_API_H */


#endif /* !__KERNEL__ */

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_HYBRID_LIBRARY_H */
