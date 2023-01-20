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
#ifndef _LIBDL_ASM_DLFCN_H
#define _LIBDL_ASM_DLFCN_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

__DECL_BEGIN

#if (defined(__CRT_KOS) || defined(__CRT_GLC) || \
     (defined(__KOS__) && defined(__BUILDING_LIBDL)))
#define __RTLD_NEXT    (__CCAST(void *)-1)
#define __RTLD_LAZY         0x00001 /* Lazy function call binding. */
#define __RTLD_NOW          0x00002 /* Immediate function call binding. */
#define __RTLD_BINDING_MASK 0x00003 /* Mask of binding time value. */
#define __RTLD_NOLOAD       0x00004 /* Do not load the object. */
#define __RTLD_DEEPBIND     0x00008 /* Use deep binding. */
#define __RTLD_GLOBAL       0x00100 /* If the following bit is set in the `mode' argument to `dlopen',
                                     * the  symbols of the loaded object and its dependencies are made
                                     * visible as if the object were linked directly into the program. */
#define __RTLD_LOCAL        0x00000 /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#define __RTLD_NODELETE     0x01000 /* Do not delete object when closed. */


/* KOS Extensions for <dlfcn.h> */
#if (defined(__KOS__) || defined(__CRT_KOS) || \
     (defined(__KOS__) && defined(__BUILDING_LIBDL)))
#define __RTLD_SELF    (__CCAST(void *)-3) /* -3, because that's the value on NetBSD... */
#define __DLCACHES_SECTION_NAME ".dl_caches"
#if __KOS_VERSION__ >= 400
#define __RTLD_NOINIT 0x80000000 /* KOS Extension: Don't run module initializers, and consequently
                                  *                skip running finalizers as well.
                                  * When set, `dlopen(3D)' will immediately return to the caller upon success,
                                  * rather  than  running  initializers  of  all  affected  libraries   first.
                                  * HINT: You may  run  initializers  (and finalizers  during  exit())  at  a
                                  *       later time by calling `dlopen(3D)' again without passing this flag.
                                  * WARNING: Initializers of newly loaded dependencies will not be executed
                                  *          either! */

#define __CRT_HAVE_dlfopen
#define __CRT_HAVE_dlexceptaware
#define __CRT_HAVE_dlgethandle
#define __CRT_HAVE_dlgetmodule
#define __CRT_HAVE_dlmodulefd
#define __CRT_HAVE_dlmodulename
#define __CRT_HAVE_dlmodulebase
#define __CRT_HAVE_dllocksection
#define __CRT_HAVE_dlunlocksection
#define __CRT_HAVE_dlsectionname
#define __CRT_HAVE_dlsectionindex
#define __CRT_HAVE_dlsectionmodule
#define __CRT_HAVE_dlinflatesection
#define __CRT_HAVE_dlclearcaches
#define __CRT_HAVE_dltlsallocseg
#define __CRT_HAVE_dltlsfreeseg
#define __CRT_HAVE_dltlsalloc
#define __CRT_HAVE_dltlsfree
#define __CRT_HAVE_dltlsaddr
#define __CRT_HAVE_dltlsaddr2
#define __CRT_HAVE_dlauxctrl
#if defined(__i386__) && !defined(__x86_64__)
#define __DLFCN_DLTLSADDR_CC  __ATTR_FASTCALL
#define __DLFCN_DLTLSADDR2_CC __ATTR_FASTCALL
#endif /* __i386__ && !__x86_64__ */

#else /* __KOS_VERSION__ >= 400 */
#define __CRT_HAVE_fdlopen /* WARNING: In KOS v300, `fdlopen(3D)' didn't inherit the given `FD' on success! */
#endif /* __KOS_VERSION__ < 400 */
#endif /* __KOS__ || __CRT_KOS || (__KOS__ && __BUILDING_LIBDL) */

/* Stuff from Glibc that also exist under KOS */
#define __CRT_HAVE_dladdr
#define __CRT_HAVE_dl_iterate_phdr
#define __CRT_HAVE_dlinfo

/* Stuff from Glibc that doesn't exist under KOS (for now...) */
#if !defined(__KOS__) && !defined(__CRT_KOS)
#define __Lmid_t      __LONGPTR_TYPE__
#define __LM_ID_BASE  0    /* Initial namespace. */
#define __LM_ID_NEWLM (-1) /* For dlmopen: request new namespace. */
#define __CRT_HAVE_dlmopen
#define __CRT_HAVE_dlvsym
#define __CRT_HAVE_dladdr1
#define __CRT_HAVE__dl_mcount_wrapper_check
#endif /* !__KOS__ && !__CRT_KOS */


#ifdef __CRT_HAVE_dlinfo
#define __RTLD_DI_LMID        1  /* Unsupported on KOS */
#define __RTLD_DI_LINKMAP     2  /* [struct link_map **arg] -- *arg = GET_LINK_MAP_FOR(handle) (on KOS: this is the same as `handle') */
#define __RTLD_DI_CONFIGADDR  3  /* [Dl_info *arg] Fill in `dli_fname' (module filename) and `dli_fbase' (module start address; NOT load address! Unsupported by Glibc!) */
#define __RTLD_DI_SERINFO     4  /* [Dl_serinfo *arg] Return search path information */
#define __RTLD_DI_SERINFOSIZE 5  /* [Dl_serinfo *arg] Like `__RTLD_DI_SERINFO', but only fill in `dls_size' and `dls_cnt' */
#define __RTLD_DI_ORIGIN      6  /* [char *arg] strcpy() the `$ORIGIN' of this module (WARNING: UNBOUNDED BUFFER COPY) */
#define __RTLD_DI_PROFILENAME 7  /* Unsupported on KOS (and neither supported by Glibc) */
#define __RTLD_DI_PROFILEOUT  8  /* Unsupported on KOS (and neither supported by Glibc) */
#if defined(__KOS__) || defined(__CRT_GLC)
/* linux / Glibc */
#define __RTLD_DI_TLS_MODID   9  /* [size_t *arg] Store TLS module id (on KOS: this is the same as `handle') */
#define __RTLD_DI_TLS_DATA    10 /* [void **arg] Same as `dltlsaddr(3)', but don't allocate TLS if not already done -- Writes NULL if not allocated or no PT_TLS segment */
#define __RTLD_DI_PHDR        11 /* [ElfW(Phdr) const **] Store PHDR vector pointer, and return # of contained elements (only supported for ELF modules) */
#define __RTLD_DI_MAX         11
#if defined(__KOS__) || defined(__CRT_KOS)
#define __RTLD_DI_ARGSINFO    64 /* [Dl_argsinfo *arg] Return information from the program PEB. */
#endif /* defined(__KOS__) || __CRT_KOS */
#elif defined(__solaris__)
#define __RTLD_DI_GETSIGNAL   9
#define __RTLD_DI_SETSIGNAL   10
#define __RTLD_DI_ARGSINFO    11
#define __RTLD_DI_MMAPS       12
#define __RTLD_DI_MMAPCNT     13
#define __RTLD_DI_MAX         13
#endif /* ... */
#endif /* __CRT_HAVE_dlinfo */

#ifdef __CRT_HAVE_dladdr1
#define __RTLD_DL_SYMENT  1
#define __RTLD_DL_LINKMAP 2
#endif /* __CRT_HAVE_dladdr1 */

#elif defined(__CRT_CYG)
#define __CRT_HAVE_dladdr
#define __RTLD_NEXT         (__CCAST(void *)-1)
#define __RTLD_LAZY         0x00001 /* Lazy function call binding. */
#define __RTLD_NOW          0x00002 /* Immediate function call binding. */
#define __RTLD_BINDING_MASK 0x00003 /* Mask of binding time value. */
#define __RTLD_NODELETE     0x00008 /* Do not delete object when closed. */
#define __RTLD_NOLOAD       0x00010 /* Do not load the object. */
#define __RTLD_DEEPBIND     0x00020 /* Use deep binding. */
#define __RTLD_GLOBAL       0x00100 /* If the following bit is set in the `mode' argument to `dlopen',
                                     * the  symbols of the loaded object and its dependencies are made
                                     * visible as if the object were linked directly into the program. */
#define __RTLD_LOCAL        0x00000 /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#elif defined(__NetBSD__)
#define __CRT_HAVE_dladdr
#define __CRT_HAVE_dlctl
#define __CRT_HAVE_dlinfo
#define __CRT_HAVE_dlvsym
#define __CRT_HAVE__dlauxinfo
#define __CRT_HAVE___dl_cxa_refcount
#define __RTLD_DI_LINKMAP 3
#define __RTLD_LAZY       1
#define __RTLD_NOW        2
#define __RTLD_GLOBAL     0x0100
#define __RTLD_LOCAL      0x0200
#define __RTLD_NODELETE   0x1000
#define __RTLD_NOLOAD     0x2000
#define __RTLD_NEXT       (__CCAST(void *)-1)
#define __RTLD_DEFAULT    (__CCAST(void *)-2)
#define __RTLD_SELF       (__CCAST(void *)-3)
#define __DL_GETERRNO     1
#define __DL_GETSYMBOL    2
#endif /* ... */



/* These functions exist by default, unless explicitly defined as not existing! */
#ifndef __CRT_HAVE_dlopen
#define __CRT_HAVE_dlopen
#elif (-__CRT_HAVE_dlopen - 1) == -1
#undef __CRT_HAVE_dlopen
#endif /* !__CRT_HAVE_dlopen */

#ifndef __CRT_HAVE_dlclose
#define __CRT_HAVE_dlclose
#elif (-__CRT_HAVE_dlclose - 1) == -1
#undef __CRT_HAVE_dlclose
#endif /* !__CRT_HAVE_dlclose */

#ifndef __CRT_HAVE_dlsym
#define __CRT_HAVE_dlsym
#elif (-__CRT_HAVE_dlsym - 1) == -1
#undef __CRT_HAVE_dlsym
#endif /* !__CRT_HAVE_dlsym */

#ifndef __CRT_HAVE_dlerror
#define __CRT_HAVE_dlerror
#elif (-__CRT_HAVE_dlerror - 1) == -1
#undef __CRT_HAVE_dlerror
#endif /* !__CRT_HAVE_dlerror */


/* Default to defining `RTLD_DEFAULT' as a 0-pointer */
#ifndef __RTLD_DEFAULT
#define __RTLD_DEFAULT (__CCAST(void *)0)
#endif /* !__RTLD_DEFAULT */

#ifndef __RTLD_LOCAL
#define __RTLD_LOCAL 0x00000 /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#endif /* !__RTLD_LOCAL */


/* The   KOS   kernel   doesn't  implement   the   <dlfcn.h>  interface!
 * Instead, a functionally similar interface exists in <kernel/driver.h> */
#if defined(__KOS__) && defined(__KERNEL__)
#undef __CRT_HAVE_dlopen
#undef __CRT_HAVE_dlclose
#undef __CRT_HAVE_dlsym
#undef __CRT_HAVE_dlerror
#undef __CRT_HAVE_dlfopen
#undef __CRT_HAVE_dlgethandle
#undef __CRT_HAVE_dlgetmodule
#undef __CRT_HAVE_dlmodulefd
#undef __CRT_HAVE_dlmodulename
#undef __CRT_HAVE_dlmodulebase
#undef __CRT_HAVE_dlexceptaware
#undef __CRT_HAVE_dllocksection
#undef __CRT_HAVE_dlunlocksection
#undef __CRT_HAVE_dlsectionname
#undef __CRT_HAVE_dlsectionindex
#undef __CRT_HAVE_dlsectionmodule
#undef __CRT_HAVE_dlinflatesection
#undef __CRT_HAVE_dlclearcaches
#undef __CRT_HAVE_dltlsallocseg
#undef __CRT_HAVE_dltlsfreeseg
#undef __CRT_HAVE_dltlsalloc
#undef __CRT_HAVE_dltlsfree
#undef __CRT_HAVE_dltlsaddr
#undef __CRT_HAVE_dlauxctrl
#undef __CRT_HAVE_fdlopen
#endif /* __KOS__ && __KERNEL__ */

__DECL_END

#endif /* !_LIBDL_ASM_DLFCN_H */
