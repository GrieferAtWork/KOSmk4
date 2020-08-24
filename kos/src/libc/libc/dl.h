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
#ifndef GUARD_LIBC_LIBC_DL_H
#define GUARD_LIBC_LIBC_DL_H 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <kos/types.h>
#include <dlfcn.h>

DECL_BEGIN

#ifdef __CC__

#undef HAVE_LAZY_LIBDL_RELOCATIONS
#if 1
#define HAVE_LAZY_LIBDL_RELOCATIONS 1
#endif

#ifdef HAVE_LAZY_LIBDL_RELOCATIONS
/* In order to minimize relocations within the final libc binary, we
 * use a custom, lazily initialized function table against functions
 * from libdl (though excluding the function we need to fill in that
 * table, which is `dlsym()')
 * The reason we do this because on most architectures, each jump
 * relocation will require some form of initialization to be done
 * by libdl during _every_ _single_ _initialization_ of the library
 * in question. And while glibc and the like couldn't give less of
 * a ra7'5 a$$ about the performance impact this has on the startup
 * time of practically any application on the system (since pretty
 * much all applications are linked against libc), I personally _do_
 * care.
 * So any lazy relocation against functions from libdl is replaced
 * by a lazily initialized indirection call that truly doesn't cause
 * any additional relocations.
 * Using this, all relocations to libdl symbols can (and are) removed
 * this way (except for `dlsym()', as that one is actually required to
 * do the symbol lookups themself, meaning we'd had to do
 * `dlsym(RTLD_DEFAULT, "dlsym")' to get dlsym itself, which obviously
 * wouldn't work)
 * However, in practice these are still some other relocations that we
 * can't easily get rid of, since those are made by compiler-generated
 * function calls:
 *   - __stack_chk_guard  (complete waste: Defined by libc.so itself; !!!Not even a lazy relocation!!!)
 *   - __stack_chk_fail   (complete waste: Defined by libc.so itself)
 *   - _Unwind_Resume     (complete waste: Defined by libc.so itself (and there's no impl. in `libstdc++.so', either))
 *   - __tls_get_addr     (Potential candidate: defined by `libdl.so')
 *   - __cxa_begin_catch  (Defined by libc.so itself, but may be overwritten by `libstdc++.so')
 *   - __cxa_end_catch    (Defined by libc.so itself, but may be overwritten by `libstdc++.so')
 */

#define LIBC_DLOPEN_SECTION        ".crt.except"        /* Used by `except_handler*()' */
#define LIBC_DLCLOSE_SECTION       ".crt.sched.process" /* Used by `__cxa_atexit()' (among others) */
#define LIBC_DLTLSALLOCSEG_SECTION ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLTLSFREESEG_SECTION  ".crt.sched.pthread" /* Used by pthread */
#define LIBC_DLGETHANDLE_SECTION   ".crt.sched.process" /* Used by `__cxa_atexit()' */
#define LIBC_DLGETMODULE_SECTION   ".crt.system.auxv"   /* Used by `getauxval()' */
#define LIBC_DLMODULEFD_SECTION    ".crt.system.auxv"   /* Used by `getauxval()' */
#define LIBC_DLAUXCTRL_SECTION     ".crt.sched.process" /* Used by `__cxa_atexit()' */
#define LIBC_DLERROR_SECTION       ".crt.heap.utility"  /* Used by `sbrk()' */
#define LIBC_DLMODULEBASE_SECTION  ".crt.system.auxv"   /* Used by `getauxval()' */
#define LIBC_DLEXCEPTAWARE_SECTION ".crt.except"        /* Used by `except_handler4()' */

typedef WUNUSED void * /*NOTHROW_NCX*/ (__DLFCN_CC *PDLOPEN)(char const *filename, int mode);
typedef NONNULL((1)) int /*NOTHROW_NCX*/ (__DLFCN_CC *PDLCLOSE)(void *handle);
typedef WUNUSED void * /*NOTHROW_NCX*/ (__DLFCN_CC *PDLTLSALLOCSEG)(void);
typedef NONNULL((1)) int /*NOTHROW_NCX*/ (__DLFCN_CC *PDLTLSFREESEG)(void *ptr);
typedef WUNUSED void * /*NOTHROW_NCX*/ (__DLFCN_CC *PDLGETHANDLE)(void const *static_pointer, unsigned int flags);
typedef WUNUSED void * /*NOTHROW_NCX*/ (__DLFCN_CC *PDLGETMODULE)(char const *name, unsigned int flags);
typedef WUNUSED NONNULL((1)) fd_t /*NOTHROW_NCX*/ (__DLFCN_CC *PDLMODULEFD)(void *handle);
typedef void * /*NOTHROW_NCX*/ (__DLFCN_VCC *PDLAUXCTRL)(void *handle, unsigned int cmd, ...);
typedef WUNUSED char * /*NOTHROW_NCX*/ (__DLFCN_CC *PDLERROR)(void);
typedef WUNUSED NONNULL((1)) void * /*NOTHROW_NCX*/ (__DLFCN_CC *PDLMODULEBASE)(void *handle);
typedef WUNUSED NONNULL((1)) int /*NOTHROW_NCX*/ (__DLFCN_CC *PDLEXCEPTAWARE)(void *handle);

INTDEF WUNUSED ATTR_RETNONNULL PDLOPEN NOTHROW_NCX(LIBCCALL libc_get_dlopen)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLCLOSE NOTHROW_NCX(LIBCCALL libc_get_dlclose)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLTLSALLOCSEG NOTHROW_NCX(LIBCCALL libc_get_dltlsallocseg)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLTLSFREESEG NOTHROW_NCX(LIBCCALL libc_get_dltlsfreeseg)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLGETHANDLE NOTHROW_NCX(LIBCCALL libc_get_dlgethandle)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLGETMODULE NOTHROW_NCX(LIBCCALL libc_get_dlgetmodule)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLMODULEFD NOTHROW_NCX(LIBCCALL libc_get_dlmodulefd)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLAUXCTRL NOTHROW_NCX(LIBCCALL libc_get_dlauxctrl)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLERROR NOTHROW_NCX(LIBCCALL libc_get_dlerror)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLMODULEBASE NOTHROW_NCX(LIBCCALL libc_get_dlmodulebase)(void);
INTDEF WUNUSED ATTR_RETNONNULL PDLEXCEPTAWARE NOTHROW_NCX(LIBCCALL libc_get_dlexceptaware)(void);

#define dlopen(filename, mode)             (*libc_get_dlopen())(filename, mode)
#define dlclose(handle)                    (*libc_get_dlclose())(handle)
#define dltlsallocseg()                    (*libc_get_dltlsallocseg())()
#define dltlsfreeseg(ptr)                  (*libc_get_dltlsfreeseg())(ptr)
#define dlgethandle(static_pointer, flags) (*libc_get_dlgethandle())(static_pointer, flags)
#define dlgetmodule(name, flags)           (*libc_get_dlgetmodule())(name, flags)
#define dlmodulefd(handle)                 (*libc_get_dlmodulefd())(handle)
#define dlauxctrl(handle, ...)             (*libc_get_dlauxctrl())(handle, __VA_ARGS__)
#define dlerror()                          (*libc_get_dlerror())()
#define dlmodulebase(handle)               (*libc_get_dlmodulebase())(handle)
#define dlexceptaware(handle)              (*libc_get_dlexceptaware())(handle)
#endif /* HAVE_LAZY_LIBDL_RELOCATIONS */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_LIBC_LIBC_DL_H */
