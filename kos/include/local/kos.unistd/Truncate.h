/* HASH CRC-32:0xaa85eda2 */
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
#ifndef __local_Truncate_defined
#if defined(__CRT_HAVE_Truncate64) || defined(__CRT_HAVE_Truncate)
#define __local_Truncate_defined 1
#include <kos/anno.h>
/* Dependency: "Truncate64" from "kos.unistd" */
#ifndef ____localdep_Truncate64_defined
#define ____localdep_Truncate64_defined 1
#if defined(__CRT_HAVE_Truncate64)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),,__localdep_Truncate64,(char const *__file, __pos64_t __length),Truncate64,(__file,__length)) __THROWS(...)
#elif defined(__CRT_HAVE_Truncate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),,__localdep_Truncate64,(char const *__file, __pos64_t __length),Truncate,(__file,__length)) __THROWS(...)
#elif defined(__CRT_HAVE_Truncate)
#include <local/kos.unistd/Truncate64.h>
/* >> truncate64(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
#define __localdep_Truncate64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(Truncate64))
#else /* CUSTOM: Truncate64 */
#undef ____localdep_Truncate64_defined
#endif /* Truncate64... */
#endif /* !____localdep_Truncate64_defined */

/* Dependency: "Truncate32" from "kos.unistd" */
#ifndef ____localdep_Truncate32_defined
#define ____localdep_Truncate32_defined 1
#if defined(__CRT_HAVE_Truncate)
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__CREDIRECT_VOID(__ATTR_NONNULL((1)),,__localdep_Truncate32,(char const *__file, __pos32_t __length),Truncate,(__file,__length)) __THROWS(...)
#else /* LIBC: Truncate */
#undef ____localdep_Truncate32_defined
#endif /* Truncate32... */
#endif /* !____localdep_Truncate32_defined */

__NAMESPACE_LOCAL_BEGIN
/* >> truncate(2)
 * Truncate the given file `FILE' to a length of `LENGTH' */
__LOCAL_LIBC(Truncate) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(Truncate))(char const *__file,
                                         __FS_TYPE(pos) __length) __THROWS(...) {
#line 455 "kos/src/libc/magic/kos.unistd.c"
#ifdef __CRT_HAVE_truncate64
	__localdep_Truncate64(__file, (__pos64_t)__length);
#else /* __CRT_HAVE_truncate64 */
	__localdep_Truncate32(__file, (__pos32_t)__length);
#endif /* !__CRT_HAVE_truncate64 */
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_Truncate64) || defined(__CRT_HAVE_Truncate) */
#endif /* !__local_Truncate_defined */
