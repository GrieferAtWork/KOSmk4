/* HASH CRC-32:0xc99771d */
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
#ifndef __local_spawnl_defined
#define __local_spawnl_defined 1
#include <__crt.h>
#include <local/environ.h>
#if defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: spawnv from process */
#ifndef __local___localdep_spawnv_defined
#define __local___localdep_spawnv_defined 1
#ifdef __CRT_HAVE_spawnv
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
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_spawnv,(int __mode, char const *__restrict __path, __TARGV),spawnv,(__mode,__path,___argv))
#elif defined(__CRT_HAVE__spawnv)
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
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_spawnv,(int __mode, char const *__restrict __path, __TARGV),_spawnv,(__mode,__path,___argv))
#elif (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <local/process/spawnv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_spawnv __LIBC_LOCAL_NAME(spawnv)
#else /* ... */
#undef __local___localdep_spawnv_defined
#endif /* !... */
#endif /* !__local___localdep_spawnv_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(spawnl) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(spawnl))(int __mode, char const *__restrict __path, char const *__args, ...) {
	__REDIRECT_SPAWNL(char, __localdep_spawnv, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_spawnl_defined
#define __local___localdep_spawnl_defined 1
#define __localdep_spawnl __LIBC_LOCAL_NAME(spawnl)
#endif /* !__local___localdep_spawnl_defined */
#else /* __CRT_HAVE_spawnv || __CRT_HAVE__spawnv || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve) && __LOCAL_environ) */
#undef __local_spawnl_defined
#endif /* !__CRT_HAVE_spawnv && !__CRT_HAVE__spawnv && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve) || !__LOCAL_environ) */
#endif /* !__local_spawnl_defined */
