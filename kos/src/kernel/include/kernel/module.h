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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MODULE_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MODULE_H 1

#include <kernel/compiler.h>

/* Convenience hybrid-api to implement a dynamic, compatibility-
 * api between `struct driver' and `struct usermod', as well as
 * their related types. */

#include <kernel/driver.h>
#include <kernel/vm/usermod.h>

#include <hybrid/__atomic.h>


/* Flags for `module_locksection()' */
#define MODULE_LOCKSECTION_FNORMAL DRIVER_SECTION_LOCK_FNORMAL /* Normal section locking flags. */
#define MODULE_LOCKSECTION_FINDEX  DRIVER_SECTION_LOCK_FINDEX  /* The given `NAME' is actually the `(uintptr_t)NAME' index of the section */
#define MODULE_LOCKSECTION_FNODATA DRIVER_SECTION_LOCK_FNODATA /* Do not lock section data into memory, though if the section had already
                                                                * been loaded, then this flag is simply ignored. */



#ifdef CONFIG_HAVE_USERMOD
#define MODULE_TYPE_DRIVER 0 /* Is a `struct driver' or `struct driver_section' */
#define MODULE_TYPE_USRMOD 1 /* Is a `struct usermod' or `struct usermod_section' */
#define MODULE_TYPE_COUNT  2 /* The # of known usermod types. */

#ifdef __CC__
DECL_BEGIN

typedef unsigned int module_type_t;

typedef union {
	struct usermod_section ms_usrmod;
	struct driver_section  ms_driver;
} module_section_t;

typedef union {
	struct usermod m_usrmod;
	struct driver  m_driver;
} module_t;

DECL_END
#endif /* __CC__ */
#else /* CONFIG_HAVE_USERMOD */
#ifdef __CC__
DECL_BEGIN
typedef struct driver_section module_section_t;
typedef struct driver module_t;
DECL_END
#endif /* __CC__ */
#endif /* !CONFIG_HAVE_USERMOD */


#ifdef __CC__
DECL_BEGIN

#if MODULE_TYPE_COUNT >= 2
struct module_abi_struct {
	void /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *ma_section_destroy[MODULE_TYPE_COUNT])(module_section_t *__restrict self);
#ifndef CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA
	void * (ATTR_RETNONNULL NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) KCALL *ma_section_cdata[MODULE_TYPE_COUNT])(module_section_t *__restrict self, gfp_t gfp) /*THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT)*/;
	void * /*NOTHROW*/ (ATTR_RETNONNULL NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) KCALL *ma_section_cdata_nx[MODULE_TYPE_COUNT])(module_section_t *__restrict self, gfp_t gfp);
#endif /* !CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA */
	REF module_section_t *(WUNUSED NONNULL((1)) KCALL *ma_section_lock[MODULE_TYPE_COUNT])(module_t *__restrict self, USER CHECKED char const *name, unsigned int flags);
	REF module_section_t * /*NOTHROW*/ (WUNUSED NONNULL((1)) KCALL *ma_section_lock_nx[MODULE_TYPE_COUNT])(module_t *__restrict self, USER CHECKED char const *name, unsigned int flags);
	void /*NOTHROW*/ (NOBLOCK NONNULL((1)) FCALL *ma_module_destroy[MODULE_TYPE_COUNT])(module_t *__restrict self);
	ptrdiff_t ma_module_offsetof_loadaddr[MODULE_TYPE_COUNT];
	ptrdiff_t ma_module_offsetof_loadstart[MODULE_TYPE_COUNT];
	ptrdiff_t ma_module_offsetof_loadend[MODULE_TYPE_COUNT];
	ptrdiff_t ma_section_offsetof_udata[MODULE_TYPE_COUNT];
};

DATDEF struct module_abi_struct const module_abi;

FUNDEF WUNUSED NONNULL((2)) REF module_t *FCALL
__module_ataddr_impl(void const *addr,
                     module_type_t *__restrict result_typ)
		THROWS(E_WOULDBLOCK, E_BADALLOC)
		ASMNAME("module_ataddr");

FUNDEF WUNUSED NONNULL((2)) REF module_t *
NOTHROW(FCALL __module_ataddr_nx_impl)(void const *addr,
                                       module_type_t *__restrict result_typ)
		ASMNAME("module_ataddr_nx");
#endif /* MODULE_TYPE_COUNT >= 2 */

#if defined(__INTELLISENSE__) && 1

/* This is only needed to get syntax highlighting to work properly. */
#if MODULE_TYPE_COUNT < 2
#undef MODULE_TYPE_COUNT
#define MODULE_TYPE_COUNT 2
#endif /* MODULE_TYPE_COUNT < 2 */


extern "C++" {

/* Destroy the given module section */
NOBLOCK NONNULL((1)) void
NOTHROW(module_section_destroy)(module_section_t *__restrict self,
                                module_type_t typ);

/* Return an L-value to the given module section's reference counter. */
NOBLOCK WUNUSED NONNULL((1)) refcnt_t &
NOTHROW(_module_section_refcnt)(module_section_t *__restrict self,
                                module_type_t typ);

/* Access to various common data fields. */
NOBLOCK ATTR_PURE NONNULL((1)) void *NOTHROW(module_section_getdata)(module_section_t const *__restrict self, module_type_t typ);      /* Memory mapping for the section's contents. */
NOBLOCK ATTR_PURE NONNULL((1)) size_t NOTHROW(module_section_getsize)(module_section_t const *__restrict self, module_type_t typ);     /* Size of the section (in bytes) */
NOBLOCK ATTR_PURE NONNULL((1)) size_t NOTHROW(module_section_getentsize)(module_section_t const *__restrict self, module_type_t typ);  /* Section entity size (or 0 if unknown) */
NOBLOCK ATTR_PURE NONNULL((1)) uintptr_t NOTHROW(module_section_getlink)(module_section_t const *__restrict self, module_type_t typ);  /* Index of another section that is linked by this one (or `0' if unused) */
NOBLOCK ATTR_PURE NONNULL((1)) uintptr_t NOTHROW(module_section_getinfo)(module_section_t const *__restrict self, module_type_t typ);  /* Index of another section that is linked by this one (or `0' if unused) */
NOBLOCK ATTR_PURE NONNULL((1)) uintptr_t NOTHROW(module_section_getflags)(module_section_t const *__restrict self, module_type_t typ); /* ELF section flags (set of `SHF_*') */
NOBLOCK ATTR_PURE NONNULL((1)) u16 NOTHROW(module_section_getindex)(module_section_t const *__restrict self, module_type_t typ);       /* Index of this section. */
NOBLOCK ATTR_PURE NONNULL((1)) void *NOTHROW(_module_section_getcdata)(module_section_t const *__restrict self, module_type_t typ);    /* Decompressed section data. */
NOBLOCK ATTR_PURE NONNULL((1)) size_t NOTHROW(module_section_getcsize)(module_section_t const *__restrict self, module_type_t typ);    /* Decompressed section size. */

/* Lazily inflate compressed section data, and return a pointer to the decompressed blob. */
NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *
module_section_getcdata(module_section_t *__restrict self,
                        module_type_t typ,
                        gfp_t gfp)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT);
NOBLOCK_IF(gfp & GFP_ATOMIC) NONNULL((1)) void *
NOTHROW(module_section_getcdata_nx)(module_section_t *__restrict self,
                                    module_type_t typ,
                                    gfp_t gfp);

/* Lookup the module that is loaded at `addr', returning a reference
 * to it, and storing its typing in `result_typ'. If no module exists
 * at the specified `addr', `result_typ' is undefined, and `NULL'
 * is returned. */
NOBLOCK WUNUSED REF module_t *
module_ataddr(void const *addr, module_type_t &result_typ)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Same as `module_ataddr()', but don't throw exceptions. */
NOBLOCK WUNUSED REF module_t *
NOTHROW(module_ataddr_nx)(void const *addr, module_type_t &result_typ);

/* Same as `module_ataddr()', but only check for drivers. Also
 * note that this function doesn't throw any exceptions, either! */
NOBLOCK WUNUSED REF module_t *
NOTHROW(module_ataddr_nouser)(void const *addr);

/* Destroy the given module */
NOBLOCK NONNULL((1)) void
NOTHROW(module_destroy)(module_t *__restrict self,
                        module_type_t typ);

/* Return an L-value to the given module's reference counter. */
NOBLOCK WUNUSED NONNULL((1)) refcnt_t &
NOTHROW(_module_refcnt)(module_t *__restrict self,
                        module_type_t typ);

/* Return the load-offset, lowest mapped byte, and greatest mapped byte. */
NOBLOCK WUNUSED NONNULL((1)) uintptr_t NOTHROW(module_getloadaddr)(module_t const *__restrict self, module_type_t typ);
NOBLOCK WUNUSED NONNULL((1)) uintptr_t NOTHROW(module_getloadstart)(module_t const *__restrict self, module_type_t typ);
NOBLOCK WUNUSED NONNULL((1)) uintptr_t NOTHROW(module_getloadend)(module_t const *__restrict self, module_type_t typ);

/* Return a pointer to the VM inside of which the module has been loaded. */
NOBLOCK WUNUSED ATTR_RETNONNULL NONNULL((1)) struct vm *
NOTHROW(module_vm)(module_t const *__restrict self, module_type_t typ);

/* Lock a section into memory, returning a reference to it upon
 * success, or `NULL' if no section exists with the given `name'.
 * The returned section has the same `module_type_t' as `typ'
 * @param: flags: Set of `MODULE_LOCKSECTION_*' */
NOBLOCK WUNUSED NONNULL((1)) REF module_section_t *
module_locksection(module_t *__restrict self, module_type_t typ,
                   USER CHECKED char const *name, unsigned int flags);

/* Same as `module_locksection()', but return NULL, rather than throw an exception. */
NOBLOCK WUNUSED NONNULL((1)) REF module_section_t *
NOTHROW(module_locksection_nx)(module_t *__restrict self, module_type_t typ,
                               USER CHECKED char const *name, unsigned int flags);

} /* extern "C++" */
#elif MODULE_TYPE_COUNT >= 2
#define module_section_destroy(self, typ)             (*module_abi.ma_section_destroy[typ])(self)
#define _module_section_refcnt(self, typ)             (self)->ms_driver.ds_refcnt  /* Binary compatibility! */
#define module_section_getdata(self, typ)             (self)->ms_driver.ds_data    /* Binary compatibility! */
#define module_section_getudata(self, typ)            (*(void USER *const *)((byte_t *)(self) + module_abi.ma_section_offsetof_udata[typ]))
#define module_section_getsize(self, typ)             (self)->ms_driver.ds_size    /* Binary compatibility! */
#define module_section_getentsize(self, typ)          (self)->ms_driver.ds_entsize /* Binary compatibility! */
#define module_section_getlink(self, typ)             (self)->ms_driver.ds_link    /* Binary compatibility! */
#define module_section_getinfo(self, typ)             (self)->ms_driver.ds_info    /* Binary compatibility! */
#define module_section_getflags(self, typ)            (self)->ms_driver.ds_flags   /* Binary compatibility! */
#define module_section_getindex(self, typ)            (self)->ms_driver.ds_index   /* Binary compatibility! */
#define _module_section_getcdata(self, typ)           (self)->ms_driver.ds_cdata   /* Binary compatibility! */
#define module_section_getcsize(self, typ)            (self)->ms_driver.ds_csize   /* Binary compatibility! */
#ifdef CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA
#define module_section_getcdata(self, typ, gfp)       driver_section_cdata(&(self)->ms_driver, gfp)
#define module_section_getcdata_nx(self, typ, gfp)    driver_section_cdata_nx(&(self)->ms_driver, gfp)
#else /* CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA */
#define module_section_getcdata(self, typ, gfp)       (*module_abi.ma_section_cdata[typ])(self, gfp)
#define module_section_getcdata_nx(self, typ, gfp)    (*module_abi.ma_section_cdata_nx[typ])(self, gfp)
#endif /* !CONFIG_USERMOD_SECTION_CDATA_IS_DRIVER_SECTION_CDATA */
#define module_ataddr(addr, result_typ)               __module_ataddr_impl(addr, &(result_typ))
#define module_ataddr_nx(addr, result_typ)            __module_ataddr_nx_impl(addr, &(result_typ))
#define module_ataddr_nouser(addr)                    ((module_t *)driver_at_address(addr))
#define module_destroy(self, typ)                     (*module_abi.ma_module_destroy[typ])(self)
#define _module_refcnt(self, typ)                     (self)->m_driver.d_refcnt /* Binary compatibility! */
#define module_getloadaddr(self, typ)                 (*(uintptr_t *)((byte_t *)(self) + module_abi.ma_module_offsetof_loadaddr[typ]))
#define module_getloadstart(self, typ)                (*(uintptr_t *)((byte_t *)(self) + module_abi.ma_module_offsetof_loadstart[typ]))
#define module_getloadend(self, typ)                  (*(uintptr_t *)((byte_t *)(self) + module_abi.ma_module_offsetof_loadend[typ]))
#define module_vm(self, typ)                          ((typ) == MODULE_TYPE_DRIVER ? &vm_kernel : (self)->m_usrmod.um_vm)
#define module_locksection(self, typ, name, flags)    (*module_abi.ma_section_lock[typ])(self, name, flags)
#define module_locksection_nx(self, typ, name, flags) (*module_abi.ma_section_lock_nx[typ])(self, name, flags)
#else /* CONFIG_HAVE_USERMOD */
#define module_section_destroy(self, typ)             driver_destroy(self)
#define _module_section_refcnt(self, typ)             (self)->ds_refcnt
#define module_section_getdata(self, typ)             (self)->ds_data
#define module_section_getsize(self, typ)             (self)->ds_size
#define module_section_getentsize(self, typ)          (self)->ds_entsize
#define module_section_getlink(self, typ)             (self)->ds_link
#define module_section_getinfo(self, typ)             (self)->ds_info
#define module_section_getflags(self, typ)            (self)->ds_flags
#define module_section_getindex(self, typ)            (self)->ds_index
#define _module_section_getcdata(self, typ)           (self)->ds_cdata
#define module_section_getcsize(self, typ)            (self)->ds_csize
#define module_section_getcdata(self, typ, gfp)       driver_section_cdata(self, gfp)
#define module_section_getcdata_nx(self, typ, gfp)    driver_section_cdata_nx(self, gfp)
#define module_ataddr(addr, result_typ)               driver_at_address(addr)
#define module_ataddr_nx(addr, result_typ)            driver_at_address(addr)
#define module_ataddr_nouser(addr)                    driver_at_address(addr)
#define module_destroy(self, typ)                     driver_destroy(self)
#define _module_refcnt(self, typ)                     (self)->d_refcnt
#define module_getloadaddr(self, typ)                 (self)->d_loadaddr
#define module_getloadstart(self, typ)                (self)->d_loadstart
#define module_getloadend(self, typ)                  (self)->d_loadend
#define module_vm(self, typ)                          (&vm_kernel)
#define module_locksection(self, typ, name, flags)    driver_section_lock(self, name, flags)
#define module_locksection_nx(self, typ, name, flags) driver_section_lock_nx(self, name, flags)
#endif /* !CONFIG_HAVE_USERMOD */

#if MODULE_TYPE_COUNT >= 2
#define module_type_var(name)    module_type_t name;
#define module_type_param(name)  module_type_t name __ATTR_UNUSED
#define module_type__param(name) , module_type_t name __ATTR_UNUSED
#define module_type_param_(name) module_type_t name __ATTR_UNUSED,
#define module_type_arg(name)    name
#define module_type__arg(name)   , name
#define module_type_arg_(name)   name,
#else /* MODULE_TYPE_COUNT >= 2 */
#define module_type_var(name)    /* nothing */
#define module_type_param(name)  /* nothing */
#define module_type__param(name) /* nothing */
#define module_type_param_(name) /* nothing */
#define module_type_arg(name)    /* nothing */
#define module_type__arg(name)   /* nothing */
#define module_type_arg_(name)   /* nothing */
#endif /* MODULE_TYPE_COUNT < 2 */


/* Module section reference count control. */
#define module_section_incref(self, typ) \
	__hybrid_atomic_inc(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)
#define module_section_decref(self, typ)                                                    \
	(void)(__hybrid_atomic_decfetch(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST) || \
	       (module_section_destroy(self, typ), 0))
#define module_section_decref_likely(self, typ)                                                       \
	(void)(unlikely(__hybrid_atomic_decfetch(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_section_destroy(self, typ), 0))
#define module_section_decref_unlikely(self, typ)                                                   \
	(void)(likely(__hybrid_atomic_decfetch(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_section_destroy(self, typ), 0))
#define module_section_decref_nokill(self, typ) \
	__hybrid_atomic_dec(_module_section_refcnt(self, typ), __ATOMIC_SEQ_CST)
#define module_section_xincref(self, typ)          (void)(!(self) || (module_section_incref(self, typ), 0))
#define module_section_xdecref(self, typ)          (void)(!(self) || (module_section_decref(self, typ), 0))
#define module_section_xdecref_likely(self, typ)   (void)(!(self) || (module_section_decref_likely(self, typ), 0))
#define module_section_xdecref_unlikely(self, typ) (void)(!(self) || (module_section_decref_unlikely(self, typ), 0))

/* Module reference count control. */
#define module_incref(self, typ) \
	__hybrid_atomic_inc(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)
#define module_decref(self, typ)                                                    \
	(void)(__hybrid_atomic_decfetch(_module_refcnt(self, typ), __ATOMIC_SEQ_CST) || \
	       (module_destroy(self, typ), 0))
#define module_decref_likely(self, typ)                                                       \
	(void)(unlikely(__hybrid_atomic_decfetch(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_destroy(self, typ), 0))
#define module_decref_unlikely(self, typ)                                                   \
	(void)(likely(__hybrid_atomic_decfetch(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)) || \
	       (module_destroy(self, typ), 0))
#define module_decref_nokill(self, typ) \
	__hybrid_atomic_dec(_module_refcnt(self, typ), __ATOMIC_SEQ_CST)
#define module_xincref(self, typ)          (void)(!(self) || (module_incref(self, typ), 0))
#define module_xdecref(self, typ)          (void)(!(self) || (module_decref(self, typ), 0))
#define module_xdecref_likely(self, typ)   (void)(!(self) || (module_decref_likely(self, typ), 0))
#define module_xdecref_unlikely(self, typ) (void)(!(self) || (module_decref_unlikely(self, typ), 0))


DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MODULE_H */
