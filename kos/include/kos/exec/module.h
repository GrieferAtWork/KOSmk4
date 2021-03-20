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
#ifndef _KOS_EXEC_MODULE_H
#define _KOS_EXEC_MODULE_H 1

/* Portable (as in: both user- and kernel-space capable) API
 * for working with  dynamically loaded objects,  including:
 *   - (kernelspace-only) Userspace modules (`struct usermod')
 *   - (kernelspace-only) Kernel drivers (`struct driver')
 *   - (userspace-only)   libdl.so shared library handles
 */

#include <__stdinc.h>

#ifdef __KERNEL__
#include <kernel/module.h>
#else /* __KERNEL__ */

#include <bits/types.h>

#include <dlfcn.h>
#if defined(__BUILDING_LIBDL) || defined(DL_EXTENSION_FORMAT)
#include <libdl/module.h>
#endif /* __BUILDING_LIBDL || DL_EXTENSION_FORMAT */

#define MODULE_TYPE_DL    0 /* Handle is related to libdl.so. */
#define MODULE_TYPE_COUNT 1 /* The # of known usermod types. */

#define module_type_var(name)    /* nothing */
#define module_type_param(name)  /* nothing */
#define module_type__param(name) /* nothing */
#define module_type_param_(name) /* nothing */
#define module_type_arg(name)    /* nothing */
#define module_type__arg(name)   /* nothing */
#define module_type_arg_(name)   /* nothing */

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
typedef struct dlsection *module_section_t;
struct dlmodule;
typedef struct dlmodule *module_t;
#else /* ... */
#ifndef __dl_section_defined
#define __dl_section_defined 1
struct dl_section {
	void       *const ds_data;    /* [0..ds_size][const] Memory mapping for the section's contents. */
	__size_t    const ds_size;    /* [const] Size of the section (in bytes) */
	__size_t    const ds_entsize; /* [const] Section entity size (or 0 if unknown) */
	__uintptr_t const ds_link;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_info;    /* [const] Index of another section that is linked by this one (or `0' if unused) */
	__uintptr_t const ds_flags;   /* [const] Section flags (set of `SHF_*') */
};
#endif /* !__dl_section_defined */
typedef struct dl_section module_section_t;
typedef void module_t;
#endif /* !... */

#if defined(__BUILDING_LIBDL) || defined(DL_EXTENSION_FORMAT)
#define module_section_destroy(self, typ)   (DL_API_SYMBOL(DlSection_Destroy)(self))
#define _module_section_refcnt(self, typ)   (self)->ds_refcnt
#define module_section_getflags(self, typ)  (self)->ds_elfflags
#define module_section_getindex(self, typ)  (self)->ds_index
#define _module_section_getcdata(self, typ) (self)->ds_cdata
#define module_section_getcsize(self, typ)  (self)->ds_csize
#define module_destroy(self, typ)           DlModule_Destroy(self)
#define _module_refcnt(self, typ)           (self)->dm_refcnt
#define module_getloadaddr(self, typ)       (self)->dm_loadaddr
#define module_getloadstart(self, typ)      (self)->dm_loadstart
#define module_getloadend(self, typ)        (self)->dm_loadend
#endif /* __BUILDING_LIBDL || DL_EXTENSION_FORMAT */

#define module_section_getdata(self, typ)    (self)->ds_data
#define module_section_getsize(self, typ)    (self)->ds_size
#define module_section_getentsize(self, typ) (self)->ds_entsize
#define module_section_getlink(self, typ)    (self)->ds_link
#define module_section_getinfo(self, typ)    (self)->ds_info

#ifndef DLGETHANDLE_FNORMAL
#define DLGETHANDLE_FNORMAL 0x0000 /* Return weak pointer to a module handle */
#define DLGETHANDLE_FINCREF 0x0001 /* Return a new reference, that must be closed by `dlclose(return)' */
#endif /* !DLGETHANDLE_FNORMAL */
#if !defined(__dlgethandle_defined) && defined(__CRT_HAVE_dlgethandle)
#define __dlgethandle_defined 1
__IMPDEF __ATTR_WUNUSED void *
__NOTHROW_NCX(__DLFCN_CC dlgethandle)(void const *__static_pointer,
                                      unsigned int __flags __DFL(DLGETHANDLE_FNORMAL));
#endif /* !__dlgethandle_defined && __CRT_HAVE_dlgethandle */
#ifdef __dlgethandle_defined
#define module_ataddr(addr, result_typ)    dlgethandle(addr, DLGETHANDLE_FNORMAL)
#define module_ataddr_nx(addr, result_typ) dlgethandle(addr, DLGETHANDLE_FNORMAL)
#endif /* __dlgethandle_defined */


#ifndef module_getloadaddr
#if !defined(__dlmodulebase_defined) && defined(__CRT_HAVE_dlmodulebase)
#define __dlmodulebase_defined 1
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dlmodulebase)(void *__handle);
#endif /* !__dlmodulebase_defined && __CRT_HAVE_dlmodulebase */
#ifdef __dlmodulebase_defined
#define module_getloadaddr(self, typ) ((__uintptr_t)dlmodulebase(self))
#endif /* __dlmodulebase_defined */
#endif /* !module_getloadaddr */


#if !defined(__dllocksection_defined) && defined(__CRT_HAVE_dllocksection)
#define __dllocksection_defined 1
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) /*REF*/ struct dl_section *
__NOTHROW_NCX(__DLFCN_CC dllocksection)(void *__handle,
                                        char const *__restrict __name,
                                        unsigned int __flags __DFL(DLLOCKSECTION_FNORMAL));
#endif /* !__dllocksection_defined && __CRT_HAVE_dllocksection */
#ifdef __dllocksection_defined
#define module_locksection(self, typ, name, flags)    dllocksection(self, name, flags)
#define module_locksection_nx(self, typ, name, flags) dllocksection(self, name, flags)
#endif /* __dllocksection_defined */


#if !defined(__dlinflatesection_defined) && defined(__CRT_HAVE_dlinflatesection)
#define __dlinflatesection_defined 1
__IMPDEF __ATTR_WUNUSED __ATTR_NONNULL((1)) void *
__NOTHROW_NCX(__DLFCN_CC dlinflatesection)(struct dl_section *__sect,
                                           __size_t *__psize);
#endif /* !__dlinflatesection_defined && __CRT_HAVE_dlinflatesection */

/* void *NOTHROW(module_section_inflate)(module_t *self, module_type_t typ, size_t &size); */
#ifdef __dlinflatesection_defined
#define module_section_inflate(self, typ, size) dlinflatesection(self, &(size))
#endif /* __dlinflatesection_defined */


/* Module section reference count control. */
#ifdef _module_section_refcnt
#define module_section_incref(self, typ) \
	__hybrid_atomic_inc(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)
#ifdef module_section_destroy
#define module_section_decref(self, typ)                                                    \
	(void)(__hybrid_atomic_decfetch(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST) || \
	       (module_section_destroy(self, typ), 0))
#define module_section_decref_likely(self, typ)                                                       \
	(void)(unlikely(__hybrid_atomic_decfetch(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_section_destroy(self, typ), 0))
#define module_section_decref_unlikely(self, typ)                                                   \
	(void)(likely(__hybrid_atomic_decfetch(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_section_destroy(self, typ), 0))
#endif /* module_section_destroy */
#define module_section_decref_nokill(self, typ) \
	__hybrid_atomic_dec(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)
#endif /* _module_section_refcnt */
#if !defined(module_section_xincref) && defined(module_section_incref)
#define module_section_xincref(self, typ) (void)(!(self) || (module_section_incref(self, typ), 0))
#endif /* !module_section_xincref && module_section_incref */
#ifndef module_section_decref
#if !defined(__dlunlocksection_defined) && defined(__CRT_HAVE_dlunlocksection)
#define __dlunlocksection_defined 1
__IMPDEF __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__DLFCN_CC dlunlocksection)(/*REF*/ struct dl_section *__sect);
#endif /* !__dlunlocksection_defined && __CRT_HAVE_dlunlocksection */
#ifdef __dlunlocksection_defined
#define module_section_decref(self, typ)           dlunlocksection(self)
#define module_section_decref_likely(self, typ)    dlunlocksection(self)
#define module_section_decref_unlikely(self, typ)  dlunlocksection(self)
#endif /* __dlunlocksection_defined */
#endif /* !module_section_decref */
#ifndef module_section_xdecref
#define module_section_xdecref(self, typ)          (void)(!(self) || (module_section_decref(self, typ), 0))
#define module_section_xdecref_likely(self, typ)   (void)(!(self) || (module_section_decref_likely(self, typ), 0))
#define module_section_xdecref_unlikely(self, typ) (void)(!(self) || (module_section_decref_unlikely(self, typ), 0))
#endif /* !module_section_xdecref */

/* Module reference count control. */
#ifdef _module_refcnt
#define module_incref(self, typ) \
	__hybrid_atomic_inc(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)
#ifdef module_destroy
#define module_decref(self, typ)                                                    \
	(void)(__hybrid_atomic_decfetch(_module_refcnt(self, typ), __ATOMIC_SEQ_CST) || \
	       (module_destroy(self, typ), 0))
#define module_decref_likely(self, typ)                                                       \
	(void)(unlikely(__hybrid_atomic_decfetch(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_destroy(self, typ), 0))
#define module_decref_unlikely(self, typ)                                                   \
	(void)(likely(__hybrid_atomic_decfetch(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_destroy(self, typ), 0))
#endif /* module_destroy */
#define module_decref_nokill(self, typ) \
	__hybrid_atomic_dec(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)
#endif /* _module_refcnt */
#if !defined(module_xincref) && defined(module_incref)
#define module_xincref(self, typ) (void)(!(self) || (module_incref(self, typ), 0))
#endif /* !module_xincref && module_incref */
#if !defined(module_decref) && defined(__CRT_HAVE_dlclose)
#define module_decref(self, typ)          dlclose(self)
#define module_decref_likely(self, typ)   dlclose(self)
#define module_decref_unlikely(self, typ) dlclose(self)
#endif /* !module_decref && __CRT_HAVE_dlclose */
#ifndef module_xdecref
#define module_xdecref(self, typ)          (void)(!(self) || (module_decref(self, typ), 0))
#define module_xdecref_likely(self, typ)   (void)(!(self) || (module_decref_likely(self, typ), 0))
#define module_xdecref_unlikely(self, typ) (void)(!(self) || (module_decref_unlikely(self, typ), 0))
#endif /* !module_xdecref */

__DECL_END
#endif /* __CC__ */

#endif /* !__KERNEL__ */

#ifdef __CC__
/* Implement some (otherwise) user-space only operations for kernel-space. */
#if (!defined(module_section_inflate) && \
     (defined(module_section_getcdata_nx) && defined(module_section_getcsize)))
__DECL_BEGIN
__FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) void *
__NOTHROW(__module_section_inflate_impl)(module_section_t *__restrict __self,
                                         __size_t *__restrict __size
                                         module_type__param(__typ)) {
	void *__result;
	__result = module_section_getcdata_nx(__self, __typ, 0);
	*__size  = module_section_getcsize(__self, __typ);
	return __result;
}
__DECL_END
#define module_section_inflate(self, typ, size) \
	__module_section_inflate_impl(self, &(size)module_type__arg(typ))
#endif /* !module_section_inflate && (module_section_getcdata_nx && module_section_getcsize) */

#if (!defined(module_section_getudata) && defined(module_section_getdata))
#define module_section_getudata(self, typ) module_section_getdata(self, typ)
#endif /* !module_section_getudata && module_section_getdata */
#endif /* __CC__ */


#endif /* !_KOS_EXEC_MODULE_H */
