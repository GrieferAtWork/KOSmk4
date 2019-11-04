/* HASH CRC-32:0x27d8aecd */
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
#ifndef __local_spawnl_defined
#if defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv)
#define __local_spawnl_defined 1
#include <parts/redirect-exec.h>
/* Dependency: "spawnv" */
#ifndef ____localdep_spawnv_defined
#define ____localdep_spawnv_defined 1
#if defined(__CRT_HAVE_spawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_spawnv,(int __mode, char const *__restrict __path, __TARGV),spawnv,(__mode,__path, ___argv))
#elif defined(__CRT_HAVE__spawnv)
__CREDIRECT(__ATTR_NONNULL((2, 3)),__pid_t,__NOTHROW_RPC,__localdep_spawnv,(int __mode, char const *__restrict __path, __TARGV),_spawnv,(__mode,__path, ___argv))
#else /* LIBC: spawnv */
#undef ____localdep_spawnv_defined
#endif /* spawnv... */
#endif /* !____localdep_spawnv_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(spawnl) __ATTR_SENTINEL __ATTR_NONNULL((2)) __pid_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(spawnl))(int __mode,
                                                     char const *__restrict __path,
                                                     char const *__args,
                                                     ... /*, (char *)NULL*/) {
#line 239 "kos/src/libc/magic/process.c"
	__REDIRECT_SPAWNL(char, __localdep_spawnv, __mode, __path, __args)
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_spawnv) || defined(__CRT_HAVE__spawnv) */
#endif /* !__local_spawnl_defined */
