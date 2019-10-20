/* HASH CRC-32:0xe0ef20f9 */
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
#ifndef __local_fgetpos64_defined
#if (defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64))
#define __local_fgetpos64_defined 1
#include <kos/anno.h>
/* Dependency: "crt_ftello64" from "stdio" */
#ifndef ____localdep_crt_ftello64_defined
#define ____localdep_crt_ftello64_defined 1
#if defined(__CRT_HAVE_ftello64_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_ftello)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_ftello64_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,,__localdep_crt_ftello64,(__FILE *__restrict __stream),ftello64_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__ftelli64)
__CREDIRECT(__ATTR_NONNULL((1)),__off64_t,,__localdep_crt_ftello64,(__FILE *__restrict __stream),_ftelli64,(__stream)) __THROWS(...)
#else /* LIBC: ftello */
#undef ____localdep_crt_ftello64_defined
#endif /* crt_ftello64... */
#endif /* !____localdep_crt_ftello64_defined */

/* Dependency: "crt_fgetpos" from "stdio" */
#ifndef ____localdep_crt_fgetpos_defined
#define ____localdep_crt_fgetpos_defined 1
#if defined(__CRT_HAVE_fgetpos_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetpos)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos,(__stream,__pos)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetpos_unlocked)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,,__localdep_crt_fgetpos,(__FILE *__restrict __stream, __pos32_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos)) __THROWS(...)
#else /* LIBC: fgetpos */
#undef ____localdep_crt_fgetpos_defined
#endif /* crt_fgetpos... */
#endif /* !____localdep_crt_fgetpos_defined */

/* Dependency: "crt_ftello" from "stdio" */
#ifndef ____localdep_crt_ftello_defined
#define ____localdep_crt_ftello_defined 1
#if defined(__CRT_HAVE_ftello_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_ftello)
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_ftello_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),__off32_t,,__localdep_crt_ftello,(__FILE *__restrict __stream),ftello_unlocked,(__stream)) __THROWS(...)
#else /* LIBC: ftello */
#undef ____localdep_crt_ftello_defined
#endif /* crt_ftello... */
#endif /* !____localdep_crt_ftello_defined */

/* Dependency: "crt_ftell" from "stdio" */
#ifndef ____localdep_crt_ftell_defined
#define ____localdep_crt_ftell_defined 1
#if defined(__CRT_HAVE_ftell_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_NONNULL((1)),long int,,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_ftell)
__CREDIRECT(__ATTR_NONNULL((1)),long int,,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_ftell_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),long int,,__localdep_crt_ftell,(__FILE *__restrict __stream),ftell_unlocked,(__stream)) __THROWS(...)
#else /* LIBC: ftell */
#undef ____localdep_crt_ftell_defined
#endif /* crt_ftell... */
#endif /* !____localdep_crt_ftell_defined */

__NAMESPACE_LOCAL_BEGIN
/* 64-bit variant of `fgetpos' */
__LOCAL_LIBC(fgetpos64) __ATTR_NONNULL((1, 2)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fgetpos64))(__FILE *__restrict __stream,
                                          __pos64_t *__restrict __pos) __THROWS(...) {
#line 1603 "kos/src/libc/magic/stdio.c"
#if defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64)
	return (__INT64_TYPE__)(*__pos = (__pos64_t)__localdep_crt_ftello64(__stream)) < 0 ? -1 : 0;
#elif defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked)
	__pos32_t __pos32;
	int __result = __localdep_crt_fgetpos(__stream, &__pos32);
	if (!__result)
		*__pos = (__pos64_t)__pos32;
	return __result;
#elif defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked)
	return (__INT64_TYPE__)(*__pos = (__pos64_t)__localdep_crt_ftello(__stream)) < 0 ? -1 : 0;
#else
	return (__INT64_TYPE__)(*__pos = (__pos64_t)__localdep_crt_ftell(__stream)) < 0 ? -1 : 0;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE__ftelli64)) */
#endif /* !__local_fgetpos64_defined */
