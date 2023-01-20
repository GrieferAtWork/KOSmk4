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
#ifndef GUARD_LIBC_LIBC_DL_H
#define GUARD_LIBC_LIBC_DL_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/types.h>
#include <dlfcn.h>

DECL_BEGIN

#ifdef __CC__

#ifndef DLFCN_CC
#define DLFCN_CC __DLFCN_CC
#endif /* !DLFCN_CC */
#ifndef DLFCN_VCC
#define DLFCN_VCC __DLFCN_VCC
#endif /* !DLFCN_VCC */

#undef HAVE_LAZY_LIBDL_RELOCATIONS
#if 1
#define HAVE_LAZY_LIBDL_RELOCATIONS 1
#endif

#ifdef HAVE_LAZY_LIBDL_RELOCATIONS

#ifndef __DLFCN_DLTLSADDR_CC
#define __DLFCN_DLTLSADDR_CC __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR_CC */
#ifndef __DLFCN_DLTLSADDR2_CC
#define __DLFCN_DLTLSADDR2_CC __DLFCN_CC
#endif /* !__DLFCN_DLTLSADDR2_CC */

/* In order to minimize relocations within the final libc binary, we
 * use a custom, lazily initialized function table against functions
 * from libdl (though excluding the function we need to fill in that
 * table, which is `dlsym(3D)')
 *
 * The reason we do this  because on most architectures, each  jump
 * relocation will require some form  of initialization to be  done
 * by libdl during _every_ _single_ _initialization_ of the library
 * in question. And while Glibc and the like couldn't give less  of
 * a ra7'5 a$$ about the performance impact this has on the startup
 * time of practically any application on the system (since  pretty
 * much all applications are linked  against libc), I for one  _do_
 * care.
 *
 * So any lazy relocation against  functions from libdl is  replaced
 * by a lazily initialized indirection call that truly doesn't cause
 * any additional relocations.
 * Using  this, all relocations  to libdl symbols  can (and are) removed
 * this way (except for `dlsym(3D)', as that one is actually required to
 * do the symbol lookups themself, meaning we'd had to do
 * `dlsym(RTLD_DEFAULT, "dlsym")' to get dlsym itself, which obviously
 * wouldn't work)
 *
 * However, in practice there are still some other relocations that we
 * can't easily get rid of, since those are made by compiler-generated
 * function calls:
 *   - __stack_chk_guard  (complete waste: Defined by libc.so itself; !!!Not even a lazy relocation!!!)
 *   - __stack_chk_fail   (complete waste: Defined by libc.so itself)
 *   - _Unwind_Resume     (complete waste: Defined by libc.so itself (and there's no impl. in `libstdc++.so', either))
 *   - __tls_get_addr     (Potential candidate: defined by `libdl.so')
 *   - __cxa_begin_catch  (Defined by libc.so itself, but may be overwritten by `libstdc++.so')
 *   - __cxa_end_catch    (Defined by libc.so itself, but may be overwritten by `libstdc++.so')
 */

#define LIBC_DLOPEN_SECTION          ".crt.except"        /* Used by `except_handler*()' */
#define LIBC_DLCLOSE_SECTION         ".crt.sched.process" /* Used by `__cxa_atexit()' (among others) */
#define LIBC_DLTLSALLOCSEG_SECTION   ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLTLSFREESEG_SECTION    ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLGETHANDLE_SECTION     ".crt.sched.process" /* Used by `__cxa_atexit()' */
#define LIBC_DLGETMODULE_SECTION     ".crt.system.auxv"   /* Used by `getauxval()' */
#define LIBC_DLMODULEFD_SECTION      ".crt.system.auxv"   /* Used by `getauxval()' */
#define LIBC_DLMODULENAME_SECTION    ".crt.system.auxv"   /* Used by `getauxval()' */
#define LIBC_DLAUXCTRL_SECTION       ".crt.sched.process" /* Used by `__cxa_atexit()' */
#define LIBC_DLINFO_SECTION          ".crt.compat.glibc"  /* Used by `_dl_find_object()' */
#define LIBC_DLLOCKSECTION_SECTION   ".crt.compat.glibc"  /* Used by `_dl_find_object()' */
#define LIBC_DLUNLOCKSECTION_SECTION ".crt.compat.glibc"  /* Used by `_dl_find_object()' */
#define LIBC_DLERROR_SECTION         ".crt.heap.utility"  /* Used by `sbrk()' */
#define LIBC_DLMODULEBASE_SECTION    ".crt.system.auxv"   /* Used by `getauxval()' */
#define LIBC_DLEXCEPTAWARE_SECTION   ".crt.except"        /* Used by `except_handler4()' */
#define LIBC_DLTLSADDR_SECTION       ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLTLSADDR2_SECTION      ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLTLSALLOC_SECTION      ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLTLSFREE_SECTION       ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLADDR_SECTION          ".crt.math.math"     /* Used for <math.h> -- `struct exception::name' */

typedef WUNUSED_T void *(DLFCN_CC *PDLOPEN)(char const *filename, int mode) /*THROWS(...)*/;
typedef NONNULL_T((1)) int (DLFCN_CC *PDLCLOSE)(void *handle) /*THROWS(...)*/;
typedef WUNUSED_T void *NOTHROW_NCX_T(DLFCN_CC *PDLTLSALLOCSEG)(void);
typedef NONNULL_T((1)) int NOTHROW_NCX_T(DLFCN_CC *PDLTLSFREESEG)(void *ptr);
typedef WUNUSED_T void *NOTHROW_NCX_T(DLFCN_CC *PDLGETHANDLE)(void const *static_pointer, unsigned int flags);
typedef WUNUSED_T void *NOTHROW_NCX_T(DLFCN_CC *PDLGETMODULE)(char const *name, unsigned int flags);
typedef WUNUSED_T NONNULL_T((1)) fd_t NOTHROW_NCX_T(DLFCN_CC *PDLMODULEFD)(void *handle);
typedef WUNUSED_T NONNULL_T((1)) char const * NOTHROW_NCX_T(DLFCN_CC *PDLMODULENAME)(void *handle);
typedef void * (DLFCN_VCC *PDLAUXCTRL)(void *handle, unsigned int cmd, ...) /*THROWS(...)*/;
typedef NONNULL_T((1, 3)) int NOTHROW_NCX_T(DLFCN_CC *PDLINFO)(void *__restrict handle, int request, void *arg);
typedef WUNUSED_T NONNULL_T((1)) /*REF*/ struct dl_section *NOTHROW_NCX_T(DLFCN_CC *PDLLOCKSECTION)(void *handle, char const *__restrict name, unsigned int flags);
typedef NONNULL_T((1)) int NOTHROW_NCX_T(DLFCN_CC *PDLUNLOCKSECTION)(/*REF*/ struct dl_section *sect);
typedef WUNUSED_T char *NOTHROW_NCX_T(DLFCN_CC *PDLERROR)(void);
typedef WUNUSED_T NONNULL_T((1)) void *NOTHROW_NCX_T(DLFCN_CC *PDLMODULEBASE)(void *handle);
typedef WUNUSED_T NONNULL_T((1)) int NOTHROW_NCX_T(DLFCN_CC *PDLEXCEPTAWARE)(void *handle);
typedef WUNUSED_T NONNULL_T((1)) void *(__DLFCN_DLTLSADDR_CC *PDLTLSADDR)(void *tls_handle) /*THROWS(...)*/;
typedef WUNUSED_T NONNULL_T((1, 2)) void *(__DLFCN_DLTLSADDR2_CC *PDLTLSADDR2)(void *tls_handle, void *tls_segment) /*THROWS(...)*/;
typedef WUNUSED_T void * NOTHROW_T(DLFCN_CC *PDLTLSALLOC)(size_t num_bytes, size_t min_alignment,
                                                          void const *template_data, size_t template_size,
                                                          void (LIBCCALL *perthread_init)(void *arg, void *base, void *tls_segment),
                                                          void (LIBCCALL *perthread_fini)(void *arg, void *base, void *tls_segment),
                                                          void *perthread_callback_arg);
typedef NONNULL_T((1)) int (DLFCN_CC *PDLTLSFREE)(void *tls_handle) /*THROWS(...)*/;
typedef NONNULL_T((2)) int NOTHROW_NCX_T(DLFCN_CC *PDLADDR)(void const *address, Dl_info *info);
typedef WUNUSED_T NONNULL_T((2)) void *NOTHROW_NCX_T(DLFCN_CC *PDLSYM)(void *handle, char const *symbol_name);

INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLOPEN NOTHROW_NCX(LIBCCALL libc_get_dlopen)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLCLOSE NOTHROW_NCX(LIBCCALL libc_get_dlclose)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLTLSALLOCSEG NOTHROW_NCX(LIBCCALL libc_get_dltlsallocseg)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLTLSFREESEG NOTHROW_NCX(LIBCCALL libc_get_dltlsfreeseg)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLGETHANDLE NOTHROW_NCX(LIBCCALL libc_get_dlgethandle)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLGETMODULE NOTHROW_NCX(LIBCCALL libc_get_dlgetmodule)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLMODULEFD NOTHROW_NCX(LIBCCALL libc_get_dlmodulefd)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLMODULENAME NOTHROW_NCX(LIBCCALL libc_get_dlmodulename)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLAUXCTRL NOTHROW_NCX(LIBCCALL libc_get_dlauxctrl)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLINFO NOTHROW_NCX(LIBCCALL libc_get_dlinfo)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLLOCKSECTION NOTHROW_NCX(LIBCCALL libc_get_dllocksection)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLUNLOCKSECTION NOTHROW_NCX(LIBCCALL libc_get_dlunlocksection)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLERROR NOTHROW_NCX(LIBCCALL libc_get_dlerror)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLMODULEBASE NOTHROW_NCX(LIBCCALL libc_get_dlmodulebase)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLEXCEPTAWARE NOTHROW_NCX(LIBCCALL libc_get_dlexceptaware)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLTLSADDR NOTHROW_NCX(LIBCCALL libc_get_dltlsaddr)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLTLSADDR2 NOTHROW_NCX(LIBCCALL libc_get_dltlsaddr2)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLTLSALLOC NOTHROW_NCX(LIBCCALL libc_get_dltlsalloc)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLTLSFREE NOTHROW_NCX(LIBCCALL libc_get_dltlsfree)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLADDR NOTHROW_NCX(LIBCCALL libc_get_dladdr)(void);
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED PDLSYM NOTHROW_NCX(LIBCCALL libc_get_dlsym)(void); /* Only here as export for `__libc_dlsym(3)' */

#define dlopen(filename, mode)              (*libc_get_dlopen())(filename, mode)
#define dlclose(handle)                     (*libc_get_dlclose())(handle)
#define dltlsallocseg()                     (*libc_get_dltlsallocseg())()
#define dltlsfreeseg(ptr)                   (*libc_get_dltlsfreeseg())(ptr)
#define dlgethandle(static_pointer, flags)  (*libc_get_dlgethandle())(static_pointer, flags)
#define dlgetmodule(name, flags)            (*libc_get_dlgetmodule())(name, flags)
#define dlmodulefd(handle)                  (*libc_get_dlmodulefd())(handle)
#define dlmodulename(handle)                (*libc_get_dlmodulename())(handle)
#define dlauxctrl(handle, ...)              (*libc_get_dlauxctrl())(handle, __VA_ARGS__)
#define dlinfo(handle, request, arg)        (*libc_get_dlinfo())(handle, request, arg)
#define dllocksection(handle, name, flags)  (*libc_get_dllocksection())(handle, name, flags)
#define dlunlocksection(sect)               (*libc_get_dlunlocksection())(sect)
#define dlerror()                           (*libc_get_dlerror())()
#define dlmodulebase(handle)                (*libc_get_dlmodulebase())(handle)
#define dlexceptaware(handle)               (*libc_get_dlexceptaware())(handle)
#define dltlsaddr(tls_handle)               (*libc_get_dltlsaddr())(tls_handle)
#define dltlsaddr2(tls_handle, tls_segment) (*libc_get_dltlsaddr2())(tls_handle, tls_segment)
#define dltlsalloc(...)                     (*libc_get_dltlsalloc())(__VA_ARGS__)
#define dltlsfree(tls_handle)               (*libc_get_dltlsfree())(tls_handle)
#define dladdr(address, info)               (*libc_get_dladdr())(address, info)
#if 0 /* Don't do this. -- `dlsym(3)' is one of the few symbol we're allowed to have relocations against! */
#define dlsym(handle, symbol_name)          (*libc_get_dlsym())(handle, symbol_name)
#endif
#endif /* HAVE_LAZY_LIBDL_RELOCATIONS */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_DL_H */
