/* HASH CRC-32:0x4c87ed10 */
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
#ifndef __local_spawnv_defined
#define __local_spawnv_defined 1
#include <__crt.h>
#include <local/environ.h>
#if (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__LOCAL_environ)
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
/* Dependency: spawnve from process */
#ifndef __local___localdep_spawnve_defined
#define __local___localdep_spawnve_defined 1
#ifdef __CRT_HAVE_spawnve
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),spawnve,(__mode,__path,___argv,___envp))
#elif defined(__CRT_HAVE__spawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),_spawnve,(__mode,__path,___argv,___envp))
#else /* ... */
#undef __local___localdep_spawnve_defined
#endif /* !... */
#endif /* !__local___localdep_spawnve_defined */
__LOCAL_LIBC(spawnv) __ATTR_NONNULL((2, 3)) __pid_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(spawnv))(int __mode, char const *__restrict __path, __TARGV) {
	return __localdep_spawnve(__mode, __path, ___argv, __LOCAL_environ);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_spawnv_defined
#define __local___localdep_spawnv_defined 1
#define __localdep_spawnv __LIBC_LOCAL_NAME(spawnv)
#endif /* !__local___localdep_spawnv_defined */
#else /* (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve) && __LOCAL_environ */
#undef __local_spawnv_defined
#endif /* (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve) || !__LOCAL_environ */
#endif /* !__local_spawnv_defined */
