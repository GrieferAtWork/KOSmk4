/* HASH CRC-32:0x1e8db321 */
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
#ifndef __local_Truncate64_defined
#ifdef __CRT_HAVE_Truncate
#define __local_Truncate64_defined 1
#include <kos/anno.h>
/* Dependency: "Truncate32" from "kos.unistd" */
#ifndef ____localdep_Truncate32_defined
#define ____localdep_Truncate32_defined 1
#ifdef __CRT_HAVE_Truncate
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),,__localdep_Truncate32,(char const *__file, __pos32_t __length),Truncate,(__file,__length)) __THROWS(...)
#else /* LIBC: Truncate */
#undef ____localdep_Truncate32_defined
#endif /* Truncate32... */
#endif /* !____localdep_Truncate32_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__LOCAL_LIBC(Truncate64) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(Truncate64))(char const *__file,
                                           __pos64_t __length) __THROWS(...) {
#line 472 "kos/src/libc/magic/kos.unistd.c"
	__localdep_Truncate32(__file, (__pos32_t)__length);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_Truncate) */
#endif /* !__local_Truncate64_defined */
