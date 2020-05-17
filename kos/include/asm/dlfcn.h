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
#ifndef _ASM_DLFCN_H
#define _ASM_DLFCN_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

__DECL_BEGIN

#if defined(__KOS__) || defined(__CRT_KOS) || defined(__CRT_GLC)
#define __RTLD_NEXT    (__CCAST(void *)-1)
#define __RTLD_LAZY         0x00001 /* Lazy function call binding. */
#define __RTLD_NOW          0x00002 /* Immediate function call binding. */
#define __RTLD_BINDING_MASK 0x00003 /* Mask of binding time value. */
#define __RTLD_NOLOAD       0x00004 /* Do not load the object. */
#define __RTLD_DEEPBIND     0x00008 /* Use deep binding. */
#define __RTLD_GLOBAL       0x00100 /* If the following bit is set in the MODE argument to `dlopen',
                                     * the symbols of the loaded object and its dependencies are made
                                     * visible as if the object were linked directly into the program. */
#define __RTLD_LOCAL        0x00000 /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#define __RTLD_NODELETE     0x01000 /* Do not delete object when closed. */


/* KOS Extensions for <dlfcn.h> */
#if defined(__KOS__) || defined(__CRT_KOS)
#define __DLCACHES_SECTION_NAME ".dl_caches"
#if __KOS_VERSION__ >= 400
#define __RTLD_NOINIT 0x80000000 /* KOS Extension: Don't run module initializers, and consequently
                                  *                skip running finalizers as well.
                                  * When set, `dlopen()' will immeditaly return to the caller upon success,
                                  * rather than running initializers of all affected libraries first.
                                  * HINT: You may run initializers (and finalizers during exit()) at a
                                  *       later time by calling `dlopen()' again without passing this flag.
                                  * WARNING: Initializers of newly loaded dependencies will not be executed either! */

#define __CRT_HAVE_dlfopen 1
#define __CRT_HAVE_dlexceptaware 1
#define __CRT_HAVE_dlgethandle 1
#define __CRT_HAVE_dlgetmodule 1
#define __CRT_HAVE_dlmodulefd 1
#define __CRT_HAVE_dlmodulename 1
#define __CRT_HAVE_dlmodulebase 1
#define __CRT_HAVE_dllocksection 1
#define __CRT_HAVE_dlunlocksection 1
#define __CRT_HAVE_dlsectionname 1
#define __CRT_HAVE_dlsectionindex 1
#define __CRT_HAVE_dlsectionmodule 1
#define __CRT_HAVE_dlclearcaches 1
#define __CRT_HAVE_dltlsallocseg 1
#define __CRT_HAVE_dltlsfreeseg 1
#define __CRT_HAVE_dltlsalloc 1
#define __CRT_HAVE_dltlsfree 1
#define __CRT_HAVE_dltlsaddr 1
#define __CRT_HAVE_dlauxctrl 1
#else /* __KOS_VERSION__ >= 400 */
#define __CRT_HAVE_fdlopen 1 /* WARNING: In KOS v300, `fdlopen()' didn't inherit the given `FD' on success! */
#endif /* __KOS_VERSION__ < 400 */
#endif /* __KOS__ || __CRT_KOS */

/* Stuff from GLibc that also exist under KOS */
#define __CRT_HAVE_dladdr 1
#define __CRT_HAVE_dl_iterate_phdr 1

/* Stuff from GLibc that doesn't exist under KOS (for now...) */
#if !defined(__KOS__) && !defined(__CRT_KOS)
#define __Lmid_t      __LONGPTR_TYPE__
#define __LM_ID_BASE  0    /* Initial namespace. */
#define __LM_ID_NEWLM (-1) /* For dlmopen: request new namespace. */
#define __CRT_HAVE_dlmopen 1
#define __CRT_HAVE_dlvsym 1
#define __CRT_HAVE_dladdr1 1
#define __CRT_HAVE_dlinfo 1
#define __CRT_HAVE__dl_mcount_wrapper_check 1
#endif /* !__KOS__ && !__CRT_KOS */

#elif defined(__CRT_CYG)
#define __RTLD_NEXT    (__CCAST(void *)-1)
#define __RTLD_LAZY         0x00001 /* Lazy function call binding. */
#define __RTLD_NOW          0x00002 /* Immediate function call binding. */
#define __RTLD_BINDING_MASK 0x00003 /* Mask of binding time value. */
#define __RTLD_NODELETE     0x00008 /* Do not delete object when closed. */
#define __RTLD_NOLOAD       0x00010 /* Do not load the object. */
#define __RTLD_DEEPBIND     0x00020 /* Use deep binding. */
#define __RTLD_GLOBAL       0x00100 /* If the following bit is set in the MODE argument to `dlopen',
                                     * the symbols of the loaded object and its dependencies are made
                                     * visible as if the object were linked directly into the program. */
#define __RTLD_LOCAL        0x00000 /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#define __CRT_HAVE_dladdr 1
#endif /* ... */



/* These functions exist by default, unless explicitly defined as not existing! */
#ifndef __CRT_HAVE_dlopen
#define __CRT_HAVE_dlopen 1
#elif (__CRT_HAVE_dlopen + 0) == 0
#undef __CRT_HAVE_dlopen
#endif /* !__CRT_HAVE_dlopen */

#ifndef __CRT_HAVE_dlclose
#define __CRT_HAVE_dlclose 1
#elif (__CRT_HAVE_dlclose + 0) == 0
#undef __CRT_HAVE_dlclose
#endif /* !__CRT_HAVE_dlclose */

#ifndef __CRT_HAVE_dlsym
#define __CRT_HAVE_dlsym 1
#elif (__CRT_HAVE_dlsym + 0) == 0
#undef __CRT_HAVE_dlsym
#endif /* !__CRT_HAVE_dlsym */

#ifndef __CRT_HAVE_dlerror
#define __CRT_HAVE_dlerror 1
#elif (__CRT_HAVE_dlerror + 0) == 0
#undef __CRT_HAVE_dlerror
#endif /* !__CRT_HAVE_dlerror */


/* Default to defining `RTLD_DEFAULT' as a 0-pointer */
#ifndef __RTLD_DEFAULT
#define __RTLD_DEFAULT (__CCAST(void *)0)
#endif /* !__RTLD_DEFAULT */

#ifndef __RTLD_LOCAL
#define __RTLD_LOCAL 0x00000 /* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL. */
#endif /* !__RTLD_LOCAL */


/* The KOS kernel doesn't implement the <dlfcn.h> interface!
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

#endif /* !_ASM_DLFCN_H */
