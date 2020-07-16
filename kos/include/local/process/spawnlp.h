/* HASH CRC-32:0x7fed0c0 */
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
#ifndef __local_spawnlp_defined
#define __local_spawnlp_defined 1
#include <__crt.h>
#include <local/environ.h>
#include <hybrid/__alloca.h>
#if defined(__CRT_HAVE_spawnvp) || defined(__CRT_HAVE__spawnvp) || ((defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: spawnvp from process */
#ifndef __local___localdep_spawnvp_defined
#define __local___localdep_spawnvp_defined 1
#ifdef __CRT_HAVE_spawnvp
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_spawnvp,(int __mode, char const *__restrict __file, __TARGV),spawnvp,(__mode,__file,___argv))
#elif defined(__CRT_HAVE__spawnvp)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_spawnvp,(int __mode, char const *__restrict __file, __TARGV),_spawnvp,(__mode,__file,___argv))
#elif (defined(__CRT_HAVE_spawnvpe) || defined(__CRT_HAVE__spawnvpe) || ((defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__hybrid_alloca))) && defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <local/process/spawnvp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_spawnvp __LIBC_LOCAL_NAME(spawnvp)
#else /* ... */
#undef __local___localdep_spawnvp_defined
#endif /* !... */
#endif /* !__local___localdep_spawnvp_defined */
__NAMESPACE_LOCAL_END
#include <parts/redirect-exec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(spawnlp) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(spawnlp))(int __mode, char const *__restrict __file, char const *__args, ...) {
	__REDIRECT_SPAWNL(char, __localdep_spawnvp, __mode, __file, __args)
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_spawnlp_defined
#define __local___localdep_spawnlp_defined 1
#define __localdep_spawnlp __LIBC_LOCAL_NAME(spawnlp)
#endif /* !__local___localdep_spawnlp_defined */
#else /* __CRT_HAVE_spawnvp || __CRT_HAVE__spawnvp || ((__CRT_HAVE_spawnvpe || __CRT_HAVE__spawnvpe || ((__CRT_HAVE_spawnve || __CRT_HAVE__spawnve) && __hybrid_alloca)) && __LOCAL_environ) */
#undef __local_spawnlp_defined
#endif /* !__CRT_HAVE_spawnvp && !__CRT_HAVE__spawnvp && ((!__CRT_HAVE_spawnvpe && !__CRT_HAVE__spawnvpe && ((!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve) || !__hybrid_alloca)) || !__LOCAL_environ) */
#endif /* !__local_spawnlp_defined */
