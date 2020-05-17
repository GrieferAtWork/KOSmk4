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
#ifndef _LINK_H
#define _LINK_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <asm/dlfcn.h>     /* __CRT_HAVE_dl_iterate_phdr */
#include <bits/elfclass.h> /* Defines __ELF_NATIVE_CLASS.  */
#include <bits/types.h>
#include <kos/exec/elf.h> /* ElfW() */
#include <sys/types.h>

#include <dlfcn.h>
#include <elf.h>

/* #include <bits/link.h> */

__SYSDECL_BEGIN

#ifdef __CC__

/* Module handles (as returned by `dlopen()') can be cast to this structure. */
struct link_map {
	/* A mirror of the first couple of fields of the `DlModule' structure.
	 * NOTE: This structure is also defined by GLibC and must
	 *       therefor have binary compatibility under KOS (*ugh*) */
	ElfW(Addr)       l_addr; /* [const] Load address (offset added to `p_vaddr' in `dlpi_phdr') of this module. */
	char            *l_name; /* [1..1][const] Absolute file name of the module. */
	ElfW(Dyn)       *l_ld;   /* [0..1][const] Dynamic section of the shared object. */
	/* WARNING: These link fields are protected by an internal lock, so
	 *          you'll run into problems if some other thread is loading
	 *          or unloading modules... (why did these have to be exposed...) */
	struct link_map *l_next; /* [0..1] Next loaded object. */
	struct link_map *l_prev; /* [0..1] Previous loaded object. */
};


struct dl_phdr_info {
	ElfW(Addr)        dlpi_addr;  /* Load address (offset added to `p_vaddr' in `dlpi_phdr') of this module. */
	char const       *dlpi_name;  /* [1..1] File name of this module. */
	ElfW(Phdr) const *dlpi_phdr;  /* [1..dlpi_phnum] Vector of program headers. */
	ElfW(Half)        dlpi_phnum; /* # of program headers. */
	/* NOTE: Everything that follows may only be available if `size' passed by
	 *      `dl_iterate_phdr()' to the given callback is >= offsetafter(...) */
	__uint64_t        dlpi_adds;      /* Incremented when a new object may have been added.  */
	__uint64_t        dlpi_subs;      /* Incremented when an object may have been removed.  */
	__size_t          dlpi_tls_modid; /* If there is a PT_TLS segment, its module ID as used in TLS relocations, else zero.  */
	void             *dlpi_tls_data;  /* [0..1] The address of the calling thread's instance of this module's
	                                   *        PT_TLS segment, if it has one and it has been allocated in the
	                                   *        calling thread, otherwise a null pointer.  */
};

#ifndef ____dl_iterator_callback_defined
#define ____dl_iterator_callback_defined 1
/* Callback prototype for `dl_iterate_phdr()' */
typedef int (__LIBCCALL *__dl_iterator_callback)(struct dl_phdr_info *__info,
                                                 __size_t __info_size, void *__arg);
#endif /* !____dl_iterator_callback_defined */

/* Enumerate all loaded modules, as well as information about them.
 * Enumeration stops when `*CALLBACK' returns a non-zero value, which
 * will then also be returned by this function. Otherwise, `0' will
 * be returned after all modules have been enumerated. */
#ifdef __CRT_HAVE_dl_iterate_phdr
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dl_iterate_phdr)(__dl_iterator_callback __callback,
                                          void *__arg);
#endif /* __CRT_HAVE_dl_iterate_phdr */

/* The .dynamic section of the calling module. */
#ifdef __ELF__
extern ElfW(Dyn) _DYNAMIC[];
#endif /* __ELF__ */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_LINK_H */
