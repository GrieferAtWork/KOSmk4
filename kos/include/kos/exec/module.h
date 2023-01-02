/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_EXEC_MODULE_H
#define _KOS_EXEC_MODULE_H 1

/* Portable (as in: both user- and kernel-space capable)
 * API for  working  with  dynamically  loaded  objects:
 *   kernelspace: `struct module *'  from <kernel/mman/module.h>
 *   userspace:   `void *'           from <dlfcn.h>  (aka: struct dlmodule *)
 */

#include <__stdinc.h>

#ifdef __KERNEL__
#include <kernel/mman/module.h>

#include <hybrid/pp/__va_nargs.h>

#define module_section_t                struct module_section
#define module_t                        struct module
#define module_section_getsize(self)    (self)->ms_size
#define module_section_getentsize(self) (self)->ms_entsize
#define module_section_getlink(self)    (self)->ms_link
#define module_section_getinfo(self)    (self)->ms_info
#define module_section_getflags(self)   (self)->ms_flags
#define module_fromaddr(addr)           module_fromaddr(addr)
#define module_fromaddr_nx(addr)        module_fromaddr_nx(addr)
#define module_getloadaddr(self)        (self)->md_loadaddr
#define module_getloadmin(self)         (self)->md_loadmin
#define module_getloadmax(self)         (self)->md_loadmax

/* For compatibility with user-space, provide versions of `module_locksection()'
 * that take  a flags-argument,  however that  argument is  silently  discarded! */
#undef module_locksection
#undef module_locksection_nx
#undef module_locksection_index
#undef module_locksection_index_nx
#define module_locksection(self, name, ...)           (*(self)->md_ops->mo_locksection)(self, name)
#define module_locksection_nx(self, name, ...)        (module_locksection_nx)(self, name)
#define module_locksection_index(self, index, ...)    (*(self)->md_ops->mo_locksection_index)(self, index)
#define module_locksection_index_nx(self, index, ...) (module_locksection_index_nx)(self, index)

#define module_section_incref(self)           incref(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_decref(self)           decref(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_decref_likely(self)    decref_likely(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_decref_unlikely(self)  decref_unlikely(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_decref_nokill(self)    decref_nokill(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_xincref(self)          xincref(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_xdecref(self)          xdecref(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_xdecref_likely(self)   xdecref_likely(__COMPILER_REQTYPE(module_section_t *, self))
#define module_section_xdecref_unlikely(self) xdecref_unlikely(__COMPILER_REQTYPE(module_section_t *, self))
#define module_incref(self)                   incref(__COMPILER_REQTYPE(module_t *, self))
#define module_decref(self)                   decref(__COMPILER_REQTYPE(module_t *, self))
#define module_decref_likely(self)            decref_likely(__COMPILER_REQTYPE(module_t *, self))
#define module_decref_unlikely(self)          decref_unlikely(__COMPILER_REQTYPE(module_t *, self))
#define module_decref_nokill(self)            decref_nokill(__COMPILER_REQTYPE(module_t *, self))
#define module_xincref(self)                  xincref(__COMPILER_REQTYPE(module_t *, self))
#define module_xdecref(self)                  xdecref(__COMPILER_REQTYPE(module_t *, self))
#define module_xdecref_likely(self)           xdecref_likely(__COMPILER_REQTYPE(module_t *, self))
#define module_xdecref_unlikely(self)         xdecref_unlikely(__COMPILER_REQTYPE(module_t *, self))
#else /* __KERNEL__ */

#include <bits/types.h>

#include <dlfcn.h>
#if defined(__BUILDING_LIBDL) || defined(DL_EXTENSION_FORMAT)
#include <libdl/module.h>
#endif /* __BUILDING_LIBDL || DL_EXTENSION_FORMAT */

#ifndef DLLOCKSECTION_FNORMAL
#define DLLOCKSECTION_FNORMAL   0x0000 /* Normal section locking flags. */
#define DLLOCKSECTION_FINDEX    0x0001 /* The given `name' is actually the `(uintptr_t)name' index of the section */
#define DLLOCKSECTION_FNODATA   0x0002 /* Do not lock section data into memory, though if section data
                                        * had already been loaded, then  this flag is simply  ignored. */
#endif /* !DLLOCKSECTION_FNORMAL */


/* Flags for `module_locksection()' */
#define MODULE_LOCKSECTION_FNORMAL DLLOCKSECTION_FNORMAL /* Normal section locking flags. */
#define MODULE_LOCKSECTION_FINDEX  DLLOCKSECTION_FINDEX  /* The given `name' is actually the `(uintptr_t)name' index of the section */
#define MODULE_LOCKSECTION_FNODATA DLLOCKSECTION_FNODATA /* Do not lock section data into memory, though if section data
                                                          * had already been loaded, then  this flag is simply  ignored. */


#ifdef __CC__
__DECL_BEGIN

#if defined(__BUILDING_LIBDL) || defined(DL_EXTENSION_FORMAT)
struct dlsection;
typedef struct dlsection module_section_t;
struct dlmodule;
typedef struct dlmodule module_t;
#else /* ... */
#ifndef __dl_section_defined
#define __dl_section_defined
struct dl_section {
	void       *const ds_data;    /* [0..ds_size][const] Memory mapping for the section's contents. */
	__size_t    const ds_size;    /* [const] Size of the section (in bytes) */
	__size_t    const ds_entsize; /* [const] Section entity size (or 0 if unknown) */
	__uintptr_t const ds_link;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_info;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_flags;   /* [const] Section flags (set of `SHF_*' from <elf.h>) */
};
#endif /* !__dl_section_defined */
typedef struct dl_section module_section_t;
typedef void module_t;
#endif /* !... */

#if defined(__BUILDING_LIBDL) || defined(DL_EXTENSION_FORMAT)
#define module_section_destroy(self)  (DL_API_SYMBOL(DlSection_Destroy)(self))
#define _module_section_refcnt(self)  (self)->ds_refcnt
#define module_section_getflags(self) (self)->ds_elfflags
#define module_destroy(self)          DlModule_Destroy(self)
#define _module_refcnt(self)          (self)->dm_refcnt
#define module_getloadaddr(self)      (self)->dm_loadaddr
#define module_getloadmin(self)       ((byte_t *)(self)->dm_loadstart)
#define module_getloadmax(self)       ((byte_t *)(self)->dm_loadend - 1)
#else /* __BUILDING_LIBDL || DL_EXTENSION_FORMAT */
#define module_section_getflags(self) (self)->ds_flags
#endif /* __BUILDING_LIBDL || DL_EXTENSION_FORMAT */

#define module_section_getaddr(self)       (self)->ds_data
#define module_section_getaddr_alias(self) (self)->ds_data
#define module_section_getsize(self)       (self)->ds_size
#define module_section_getentsize(self)    (self)->ds_entsize
#define module_section_getlink(self)       (self)->ds_link
#define module_section_getinfo(self)       (self)->ds_info


#ifndef DLGETHANDLE_FNORMAL
#define DLGETHANDLE_FNORMAL 0x0000 /* Return weak pointer to a module handle */
#define DLGETHANDLE_FINCREF 0x0001 /* Return a new reference, that must be closed by `dlclose(return)' */
#endif /* !DLGETHANDLE_FNORMAL */
#if !defined(__dlgethandle_defined) && defined(__CRT_HAVE_dlgethandle)
#define __dlgethandle_defined
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW(__DLFCN_CC dlgethandle)(void const *__static_pointer,
                                  unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* !__dlgethandle_defined && __CRT_HAVE_dlgethandle */
#ifdef __dlgethandle_defined
#define module_fromaddr(addr)    dlgethandle(addr, DLGETHANDLE_FNORMAL)
#define module_fromaddr_nx(addr) dlgethandle(addr, DLGETHANDLE_FNORMAL)
#endif /* __dlgethandle_defined */


#ifndef module_getloadaddr
#if !defined(__dlmodulebase_defined) && defined(__CRT_HAVE_dlmodulebase)
#define __dlmodulebase_defined
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) __uintptr_t
__NOTHROW_NCX(__DLFCN_CC dlmodulebase)(void *__handle);
#endif /* !__dlmodulebase_defined && __CRT_HAVE_dlmodulebase */
#ifdef __dlmodulebase_defined
#define module_getloadaddr(self) dlmodulebase(self)
#endif /* __dlmodulebase_defined */
#endif /* !module_getloadaddr */


#if !defined(__dllocksection_defined) && defined(__CRT_HAVE_dllocksection)
#define __dllocksection_defined
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) /*REF*/ struct dl_section *
__NOTHROW_NCX(__DLFCN_CC dllocksection)(void *__handle,
                                        char const *__restrict __name,
                                        unsigned int __flags __DFL(DLLOCKSECTION_FNORMAL));
#endif /* !__dllocksection_defined && __CRT_HAVE_dllocksection */
#ifdef __dllocksection_defined
#define module_locksection(self, name, flags)    dllocksection(self, name, flags)
#define module_locksection_nx(self, name, flags) dllocksection(self, name, flags)
#endif /* __dllocksection_defined */


#if !defined(__dlinflatesection_defined) && defined(__CRT_HAVE_dlinflatesection)
#define __dlinflatesection_defined
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dlinflatesection)(struct dl_section *__sect,
                                           __size_t *__psize);
#endif /* !__dlinflatesection_defined && __CRT_HAVE_dlinflatesection */

/* void *module_section_getaddr_inflate(module_t *self, size_t *psize); */
#ifdef __dlinflatesection_defined
#define module_section_getaddr_inflate(self, psize) dlinflatesection(self, psize)
#endif /* __dlinflatesection_defined */

/* void *NOTHROW(module_section_getaddr_inflate_nx)(module_t *self, size_t *psize); */
#ifdef __dlinflatesection_defined
#define module_section_getaddr_inflate_nx(self, psize) dlinflatesection(self, psize)
#endif /* __dlinflatesection_defined */


/* Module section reference count control. */
#ifdef _module_section_refcnt
#define module_section_incref(self) \
	__hybrid_atomic_inc(_module_section_refcnt(self), __ATOMIC_SEQ_CST)
#ifdef module_section_destroy
#define module_section_decref(self)                                                    \
	(void)(__hybrid_atomic_decfetch(_module_section_refcnt(self), __ATOMIC_SEQ_CST) || \
	       (module_section_destroy(self), 0))
#define module_section_decref_likely(self)                                                       \
	(void)(unlikely(__hybrid_atomic_decfetch(_module_section_refcnt(self), __ATOMIC_SEQ_CST)) || \
	       (module_section_destroy(self), 0))
#define module_section_decref_unlikely(self)                                                   \
	(void)(likely(__hybrid_atomic_decfetch(_module_section_refcnt(self), __ATOMIC_SEQ_CST)) || \
	       (module_section_destroy(self), 0))
#endif /* module_section_destroy */
#define module_section_decref_nokill(self) \
	__hybrid_atomic_dec(_module_section_refcnt(self), __ATOMIC_SEQ_CST)
#endif /* _module_section_refcnt */
#if !defined(module_section_xincref) && defined(module_section_incref)
#define module_section_xincref(self) (void)(!(self) || (module_section_incref(self), 0))
#endif /* !module_section_xincref && module_section_incref */
#ifndef module_section_decref
#if !defined(__dlunlocksection_defined) && defined(__CRT_HAVE_dlunlocksection)
#define __dlunlocksection_defined
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dlunlocksection)(/*REF*/ struct dl_section *__sect);
#endif /* !__dlunlocksection_defined && __CRT_HAVE_dlunlocksection */
#ifdef __dlunlocksection_defined
#define module_section_decref(self)           dlunlocksection(self)
#define module_section_decref_likely(self)    dlunlocksection(self)
#define module_section_decref_unlikely(self)  dlunlocksection(self)
#endif /* __dlunlocksection_defined */
#endif /* !module_section_decref */

/* Module reference count control. */
#ifdef _module_refcnt
#define module_incref(self) \
	__hybrid_atomic_inc(_module_refcnt(self), __ATOMIC_SEQ_CST)
#ifdef module_destroy
#define module_decref(self)                                                    \
	(void)(__hybrid_atomic_decfetch(_module_refcnt(self), __ATOMIC_SEQ_CST) || \
	       (module_destroy(self), 0))
#define module_decref_likely(self)                                                       \
	(void)(unlikely(__hybrid_atomic_decfetch(_module_refcnt(self), __ATOMIC_SEQ_CST)) || \
	       (module_destroy(self), 0))
#define module_decref_unlikely(self)                                                   \
	(void)(likely(__hybrid_atomic_decfetch(_module_refcnt(self), __ATOMIC_SEQ_CST)) || \
	       (module_destroy(self), 0))
#endif /* module_destroy */
#define module_decref_nokill(self) \
	__hybrid_atomic_dec(_module_refcnt(self), __ATOMIC_SEQ_CST)
#endif /* _module_refcnt */
#if !defined(module_xincref) && defined(module_incref)
#define module_xincref(self) (void)(!(self) || (module_incref(self), 0))
#endif /* !module_xincref && module_incref */
#if !defined(module_decref) && defined(__CRT_HAVE_dlclose)
#define module_decref(self)          dlclose(self)
#define module_decref_likely(self)   dlclose(self)
#define module_decref_unlikely(self) dlclose(self)
#endif /* !module_decref && __CRT_HAVE_dlclose */

#if defined(__USE_KOS) && defined(__CRT_HAVE_dlauxctrl)
#define module_get_tbase(self) ((void const *)dlauxctrl(self, DLAUXCTRL_GET_TEXTBASE))
#define module_get_dbase(self) ((void const *)dlauxctrl(self, DLAUXCTRL_GET_DATABASE))
#endif /* __USE_KOS && __CRT_HAVE_dlauxctrl */

__DECL_END
#endif /* __CC__ */

#endif /* !__KERNEL__ */

/* Substitute missing functions when possible... */
#if !defined(module_section_decref_likely) && defined(module_section_decref)
#define module_section_decref_likely(self) module_section_decref(self)
#endif /* !module_section_decref_likely && module_section_decref */
#if !defined(module_section_decref_unlikely) && defined(module_section_decref)
#define module_section_decref_unlikely(self) module_section_decref(self)
#endif /* !module_section_decref_unlikely && module_section_decref */
#if !defined(module_decref_likely) && defined(module_decref)
#define module_decref_likely(self) module_decref(self)
#endif /* !module_decref_likely && module_decref */
#if !defined(module_decref_unlikely) && defined(module_decref)
#define module_decref_unlikely(self) module_decref(self)
#endif /* !module_decref_unlikely && module_decref */
#if !defined(module_section_xdecref) && defined(module_section_decref)
#define module_section_xdecref(self) (void)(!(self) || (module_section_decref(self), 0))
#endif /* !module_section_xdecref && module_section_decref */
#if !defined(module_section_xdecref_likely) && defined(module_section_decref_likely)
#define module_section_xdecref_likely(self) (void)(!(self) || (module_section_decref_likely(self), 0))
#endif /* !module_section_xdecref_likely && module_section_decref_likely */
#if !defined(module_section_xdecref_unlikely) && defined(module_section_decref_unlikely)
#define module_section_xdecref_unlikely(self) (void)(!(self) || (module_section_decref_unlikely(self), 0))
#endif /* !module_section_xdecref_unlikely && module_section_decref_unlikely */
#if !defined(module_xdecref) && defined(module_xdecref)
#define module_xdecref(self) (void)(!(self) || (module_decref(self), 0))
#endif /* !module_xdecref && module_xdecref */
#if !defined(module_xdecref_likely) && defined(module_xdecref_ikely)
#define module_xdecref_likely(self) (void)(!(self) || (module_decref_likely(self), 0))
#endif /* !module_xdecref_likely && module_xdecref_ikely */
#if !defined(module_xdecref_unlikely) && defined(module_xdecref_nlikely)
#define module_xdecref_unlikely(self) (void)(!(self) || (module_decref_unlikely(self), 0))
#endif /* !module_xdecref_unlikely && module_xdecref_nlikely */

#endif /* !_KOS_EXEC_MODULE_H */
