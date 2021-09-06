/* HASH CRC-32:0xfa480733 */
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
#ifndef __local_execvp_defined
#define __local_execvp_defined 1
#include <__crt.h>
#include <libc/local/environ.h>
#include <hybrid/__alloca.h>
#if (defined(__CRT_HAVE_execvpe) || defined(__CRT_HAVE__execvpe) || ((defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
#include <features.h>
#ifndef __TARGV
#ifdef __USE_DOS_ALTERATIONS
#define __TARGV char const *const *___argv
#define __TENVP char const *const *___envp
#else /* __USE_DOS_ALTERATIONS */
#define __TARGV char *const ___argv[__restrict_arr]
#define __TENVP char *const ___envp[__restrict_arr]
#endif /* !__USE_DOS_ALTERATIONS */
#endif /* !__TARGV */
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_execvpe_defined
#define __local___localdep_execvpe_defined 1
#ifdef __CRT_HAVE_execvpe
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execvpe,(char const *__restrict __file, __TARGV, __TENVP),execvpe,(__file,___argv,___envp))
#elif defined(__CRT_HAVE__execvpe)
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),int,__NOTHROW_RPC,__localdep_execvpe,(char const *__restrict __file, __TARGV, __TENVP),_execvpe,(__file,___argv,___envp))
#elif (defined(__CRT_HAVE_execve) || defined(__CRT_HAVE__execve)) && defined(__hybrid_alloca)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/execvpe.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_execvpe __LIBC_LOCAL_NAME(execvpe)
#else /* ... */
#undef __local___localdep_execvpe_defined
#endif /* !... */
#endif /* !__local___localdep_execvpe_defined */
__LOCAL_LIBC(execvp) __ATTR_NONNULL((1, 2)) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(execvp))(char const *__restrict __file, __TARGV) {
	return __localdep_execvpe(__file, ___argv, __LOCAL_environ);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_execvp_defined
#define __local___localdep_execvp_defined 1
#define __localdep_execvp __LIBC_LOCAL_NAME(execvp)
#endif /* !__local___localdep_execvp_defined */
#else /* (__CRT_HAVE_execvpe || __CRT_HAVE__execvpe || ((__CRT_HAVE_execve || __CRT_HAVE__execve) && __hybrid_alloca)) && __LOCAL_environ */
#undef __local_execvp_defined
#endif /* (!__CRT_HAVE_execvpe && !__CRT_HAVE__execvpe && ((!__CRT_HAVE_execve && !__CRT_HAVE__execve) || !__hybrid_alloca)) || !__LOCAL_environ */
#endif /* !__local_execvp_defined */
