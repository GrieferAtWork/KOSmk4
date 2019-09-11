/* HASH 0x47cb0f70 */
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
#ifndef __local__fsopen_defined
#if (defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE_fopen64))
#define __local__fsopen_defined 1
/* Dependency: "fopen" */
#ifndef ____localdep_fopen_defined
#define ____localdep_fopen_defined 1
#if defined(__CRT_HAVE_fopen64) && (defined(__USE_FILE_OFFSET64))
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen,(__filename,__modes))
#elif defined(__CRT_HAVE_fopen64)
/* Create and return a new file-stream for accessing `FILENAME' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__FILE *,__NOTHROW_RPC,__localdep_fopen,(char const *__restrict __filename, char const *__restrict __modes),fopen64,(__filename,__modes))
#else /* LIBC: fopen */
#undef ____localdep_fopen_defined
#endif /* fopen... */
#endif /* !____localdep_fopen_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_fsopen) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __FILE *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(_fsopen))(char const *__filename,
                                                     char const *__modes,
                                                     int __sflag) {
#line 1980 "kos/src/libc/magic/stdio.c"
	(void)__sflag;
	return __localdep_fopen(__filename, __modes);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_fopen) || defined(__CRT_HAVE_fopen64)) */
#endif /* !__local__fsopen_defined */
