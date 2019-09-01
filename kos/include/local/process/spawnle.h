/* HASH 0xe556efd9 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_spawnle_defined
#if (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve))
#define __local_spawnle_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "spawnve" */
#ifndef ____localdep_spawnve_defined
#define ____localdep_spawnve_defined 1
#if defined(__CRT_HAVE_spawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),spawnve,(__mode,__path, ___argv, ___envp))
#elif defined(__CRT_HAVE__spawnve)
__CREDIRECT(__ATTR_NONNULL((2, 3, 4)),__pid_t,__NOTHROW_RPC,__localdep_spawnve,(int __mode, char const *__restrict __path, __TARGV, __TENVP),_spawnve,(__mode,__path, ___argv, ___envp))
#else /* LIBC: spawnve */
#undef ____localdep_spawnve_defined
#endif /* spawnve... */
#endif /* !____localdep_spawnve_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(spawnle) __ATTR_SENTINEL_O(1) __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(spawnle))(int __mode,
                                                      char const *__restrict __path,
                                                      char const *__args,
                                                      ... /*, (wchar_t *)NULL, wchar_t **environ*/) {
#line 248 "kos/src/libc/magic/process.c"
	__REDIRECT_SPAWNLE(char, __localdep_spawnve, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) */
#endif /* !__local_spawnle_defined */
