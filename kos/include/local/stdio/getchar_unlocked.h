/* HASH CRC-32:0xfe4e4215 */
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
#ifndef __local_getchar_unlocked_defined
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s))
#define __local_getchar_unlocked_defined 1
#include <kos/anno.h>
#include <local/stdstreams.h>
/* Dependency: "fgetc_unlocked" from "stdio" */
#ifndef ____localdep_fgetc_unlocked_defined
#define ____localdep_fgetc_unlocked_defined 1
#if defined(__CRT_HAVE_fgetc_unlocked)
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc_unlocked)
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream)) __THROWS(...)
#elif ((defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s))
#include <local/stdio/fgetc_unlocked.h>
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fgetc_unlocked (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fgetc_unlocked))
#else /* CUSTOM: fgetc_unlocked */
#undef ____localdep_fgetc_unlocked_defined
#endif /* fgetc_unlocked... */
#endif /* !____localdep_fgetc_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `getchar()', but performs I/O without acquiring a lock to `stdin' */
__LOCAL_LIBC(getchar_unlocked) int
(__LIBCCALL __LIBC_LOCAL_NAME(getchar_unlocked))(void) __THROWS(...) {
#line 1294 "kos/src/libc/magic/stdio.c"
	return __localdep_fgetc_unlocked(__stdin);
}
__NAMESPACE_LOCAL_END
#endif /* !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s)) */
#endif /* !__local_getchar_unlocked_defined */
