/* HASH CRC-32:0x5f6ef41f */
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
#ifndef __local_Open64_defined
#if defined(__CRT_HAVE_Open)
#define __local_Open64_defined 1
#include <kos/anno.h>
#include <bits/types.h>
#include <bits/types.h>
#include <bits/fcntl.h>
/* Dependency: "Open" from "kos.fcntl" */
#ifndef ____localdep_Open_defined
#define ____localdep_Open_defined 1
#if defined(__CRT_HAVE_Open64) && (defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,,__localdep_Open,(char const *__filename, __oflag_t __oflags),Open64,(__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_Open) && (!defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,,__localdep_Open,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif (defined(__CRT_HAVE_Open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64))))
#include <local/kos.fcntl/Open.h>
#define __localdep_Open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Open))
#else /* CUSTOM: Open */
#undef ____localdep_Open_defined
#endif /* Open... */
#endif /* !____localdep_Open_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(Open64) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
(__VLIBCCALL __LIBC_LOCAL_NAME(Open64))(char const *__filename,
                                        __oflag_t __oflags,
                                        ...) __THROWS(...) {
#line 71 "kos/src/libc/magic/kos.fcntl.c"
	__fd_t __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __oflags);
#ifdef __O_LARGEFILE
	__result = __localdep_Open(__filename, __oflags, __builtin_va_arg(__args, __mode_t));
#else
	__result = __localdep_Open(__filename, __oflags|__O_LARGEFILE, __builtin_va_arg(__args, __mode_t));
#endif
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_Open) */
#endif /* !__local_Open64_defined */
