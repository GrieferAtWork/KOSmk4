/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/*!replace_with_include <dlfcn.h>*/
#ifndef _LIBDL_BITS_DLFCN_H
#define _LIBDL_BITS_DLFCN_H 1

#include <__crt.h>
#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

#include <libdl/asm/dlfcn.h>

#ifdef __CC__
__DECL_BEGIN

#if defined(__CRT_HAVE_dladdr) || defined(__CRT_HAVE_dladdr1)
struct __dl_info_struct {
#ifdef __CRT_CYG
	char        dli_fname[4096]; /* File name of defining object. */
#else /* __CRT_CYG */
	char const *dli_fname; /* File name of defining object. */
#endif /* !__CRT_CYG */
	void       *dli_fbase; /* Load address of that object. */
	char const *dli_sname; /* Name of nearest symbol. */
#ifdef __USE_NETBSD
	void const *dli_saddr; /* Exact value of nearest symbol. */
#else /* __USE_NETBSD */
	void       *dli_saddr; /* Exact value of nearest symbol. */
#endif /* !__USE_NETBSD */
};
#endif /* __CRT_HAVE_dladdr || __CRT_HAVE_dladdr1 */


#ifdef __CRT_HAVE_dlinfo
#ifdef __RTLD_DI_SERINFO
struct __Dl_serpath {
	char        *dls_name;   /* [1..1] Search path directory */
	unsigned int dls_flags;  /* ??? */
};

struct __Dl_serinfo {
	__size_t            dls_size;       /* [out] Required buffer size (in bytes) */
	unsigned int        dls_cnt;        /* [out] # of entries in `dls_serpath' */
#ifdef __USE_KOS_ALTERATIONS
	__COMPILER_FLEXIBLE_ARRAY(struct __Dl_serpath, dls_serpath); /* [dls_cnt] Array of search path. */
#else /* __USE_KOS_ALTERATIONS */
	struct __Dl_serpath dls_serpath[1]; /* [dls_cnt] Array of search path. */
#endif /* !__USE_KOS_ALTERATIONS */
	/* The buffer for `dls_name' strings goes here. */
};
#endif /* __RTLD_DI_SERINFO */
#ifdef __RTLD_DI_ARGSINFO
#if __SIZEOF_POINTER__ >= 8
typedef struct elf64_auxv_t auxv_t;
#else /* __SIZEOF_POINTER__ >= 8 */
typedef struct elf32_auxv_t auxv_t;
#endif /* __SIZEOF_POINTER__ < 8 */
struct __Dl_argsinfo {
	__LONGPTR_TYPE__ dla_argc; /* s.a. `__argc' from <stdlib.h> */
	char           **dla_argv; /* [1..n] s.a. `__argv' from <stdlib.h> */
	char           **dla_envp; /* [1..n] s.a. `environ' from <unistd.h> */
	auxv_t          *dla_auxv; /* [1..1] NOTE: On KOS, this always pointers to a bzero'd `auxv_t' */
};
#endif /* __RTLD_DI_ARGSINFO */
#endif /* __CRT_HAVE_dlinfo */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBDL_BITS_DLFCN_H */
