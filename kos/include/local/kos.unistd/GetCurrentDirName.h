/* HASH CRC-32:0xa49c5835 */
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
#ifndef __local_GetCurrentDirName_defined
#if defined(__CRT_HAVE_GetCwd)
#define __local_GetCurrentDirName_defined 1
#include <kos/anno.h>
/* Dependency: "GetCwd" */
#ifndef ____localdep_GetCwd_defined
#define ____localdep_GetCwd_defined 1
#if defined(__CRT_HAVE_GetCwd)
/* >> getcwd(2)
 * Return the path of the current working directory, relative to the filesystem root set by `chdir(2)' */
__CREDIRECT(,char *,,__localdep_GetCwd,(char *__buf, __SIZE_TYPE__ __bufsize),GetCwd,(__buf,__bufsize)) __THROWS(...)
#else /* LIBC: GetCwd */
#undef ____localdep_GetCwd_defined
#endif /* GetCwd... */
#endif /* !____localdep_GetCwd_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(GetCurrentDirName) __ATTR_MALLOC __ATTR_RETNONNULL __ATTR_WUNUSED char *
(__LIBCCALL __LIBC_LOCAL_NAME(GetCurrentDirName))(void) __THROWS(...) {
#line 397 "kos/src/libc/magic/kos.unistd.c"
	return __localdep_GetCwd(__NULLPTR, 0);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_GetCwd) */
#endif /* !__local_GetCurrentDirName_defined */
