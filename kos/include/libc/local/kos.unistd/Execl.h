/* HASH CRC-32:0x87287467 */
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
#ifndef __local_Execl_defined
#define __local_Execl_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE_Execv
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: Execv from kos.unistd */
#ifndef __local___localdep_Execv_defined
#define __local___localdep_Execv_defined 1
__NAMESPACE_LOCAL_END
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
/* >> execv(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's `main()' method, passing the given `argv', and setting `environ' to `envp' */
__CREDIRECT_VOID(__ATTR_NORETURN __ATTR_NONNULL((1, 2)),__THROWING,__localdep_Execv,(char const *__restrict __path, __TARGV),Execv,(__path,___argv))
#endif /* !__local___localdep_Execv_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
/* >> execl(3)
 * Replace the calling process with the application image referred to by `path' / `file'
 * and execute it's `main()' method, passing the list of NULL-terminated `args'-list */
__LOCAL_LIBC(Execl) __ATTR_NORETURN __ATTR_SENTINEL __ATTR_NONNULL((1)) void
(__VLIBCCALL __LIBC_LOCAL_NAME(Execl))(char const *__restrict __path, char const *__args, ...) __THROWS(...) {
	__REDIRECT_XEXECL(char, __localdep_Execv, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_Execl_defined
#define __local___localdep_Execl_defined 1
#define __localdep_Execl __LIBC_LOCAL_NAME(Execl)
#endif /* !__local___localdep_Execl_defined */
#else /* __CRT_HAVE_Execv */
#undef __local_Execl_defined
#endif /* !__CRT_HAVE_Execv */
#endif /* !__local_Execl_defined */
