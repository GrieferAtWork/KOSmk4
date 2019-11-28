/* HASH CRC-32:0xa55b2138 */
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
#ifndef __local_Creat_defined
#if (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64))) || defined(__CRT_HAVE_Open) || defined(__CRT_HAVE_Open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64) || (defined(__CRT_HAVE_Openat64) && defined(__USE_FILE_OFFSET64))))
#define __local_Creat_defined 1
#include <kos/anno.h>
#include <bits/types.h>
#include <bits/types.h>
#include <bits/fcntl.h>
/* Dependency: "Open" from "kos.fcntl" */
#ifndef ____localdep_Open_defined
#define ____localdep_Open_defined 1
#if defined(__CRT_HAVE_Open64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,,__localdep_Open,(char const *__filename, __oflag_t __oflags),Open64,(__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif defined(__CRT_HAVE_Open) && (!defined(__USE_FILE_OFFSET64))
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,,__localdep_Open,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t)) __THROWS(...)
#elif (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64))) || defined(__CRT_HAVE_Open) || defined(__CRT_HAVE_Open64) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_OpenAt) || defined(__CRT_HAVE_OpenAt64) || (defined(__CRT_HAVE_Openat64) && defined(__USE_FILE_OFFSET64))))
#include <local/kos.fcntl/Open.h>
#define __localdep_Open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Open))
#else /* CUSTOM: Open */
#undef ____localdep_Open_defined
#endif /* Open... */
#endif /* !____localdep_Open_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(Creat) __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t
(__LIBCCALL __LIBC_LOCAL_NAME(Creat))(char const *__filename,
                                      __mode_t __mode) __THROWS(...) {
#line 63 "kos/src/libc/magic/kos.fcntl.c"
	return __localdep_Open(__filename, O_CREAT | O_WRONLY | O_TRUNC, __mode);
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_AT_FDCWD && (__CRT_HAVE_OpenAt || __CRT_HAVE_OpenAt64)) || __CRT_HAVE_Open || __CRT_HAVE_Open64 || (__CRT_AT_FDCWD && (__CRT_HAVE_OpenAt || __CRT_HAVE_OpenAt64 || (__CRT_HAVE_Openat64 && __USE_FILE_OFFSET64))) */
#endif /* !__local_Creat_defined */
