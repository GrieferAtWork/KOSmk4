/* HASH CRC-32:0x364a902b */
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
#ifndef __local_spawnlpe_defined
#define __local_spawnlpe_defined 1
#include <__crt.h>
#include <hybrid/__alloca.h>
#include <libc/local/environ.h>
#if defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__hybrid_alloca))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: spawnvpe from process */
#ifndef __local___localdep_spawnvpe_defined
#define __local___localdep_spawnvpe_defined 1
#ifdef __CRT_HAVE_spawnvpe
__NAMESPACE_LOCAL_END
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
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnvpe,(int __mode, char const *__restrict __file, __TARGV, __TENVP),spawnvpe,(__mode,__file,___argv,___envp))
#elif defined(__CRT_HAVE__spawnvpe)
__NAMESPACE_LOCAL_END
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
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnvpe,(int __mode, char const *__restrict __file, __TARGV, __TENVP),_spawnvpe,(__mode,__file,___argv,___envp))
#elif (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__hybrid_alloca)
__NAMESPACE_LOCAL_END
#include <libc/local/process/spawnvpe.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_spawnvpe __LIBC_LOCAL_NAME(spawnvpe)
#else /* ... */
#undef __local___localdep_spawnvpe_defined
#endif /* !... */
#endif /* !__local___localdep_spawnvpe_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(spawnlpe) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(spawnlpe))(int __mode, char const *__restrict __file, char const *__args, ...) {
	__REDIRECT_SPAWNLE(char, __localdep_spawnvpe, __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_spawnlpe_defined
#define __local___localdep_spawnlpe_defined 1
#define __localdep_spawnlpe __LIBC_LOCAL_NAME(spawnlpe)
#endif /* !__local___localdep_spawnlpe_defined */
#else /* __CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve) && __hybrid_alloca) */
#undef __local_spawnlpe_defined
#endif /* !__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve) || !__hybrid_alloca) */
#endif /* !__local_spawnlpe_defined */
