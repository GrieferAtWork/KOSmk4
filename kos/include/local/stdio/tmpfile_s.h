/* HASH 0x9ac2a896 */
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
#ifndef __local_tmpfile_s_defined
#if (defined(__CRT_HAVE_tmpfile) || defined(__CRT_HAVE_tmpfile64))
#define __local_tmpfile_s_defined 1
#include <parts/errno.h>
/* Dependency: "tmpfile" */
#ifndef ____localdep_tmpfile_defined
#define ____localdep_tmpfile_defined 1
#if defined(__CRT_HAVE_tmpfile64) && (defined(__USE_FILE_OFFSET64))
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,__localdep_tmpfile,(void),tmpfile64,())
#elif defined(__CRT_HAVE_tmpfile)
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,__localdep_tmpfile,(void),tmpfile,())
#elif defined(__CRT_HAVE_tmpfile64)
/* Create and return a new file-stream for accessing a temporary file for reading/writing */
__CREDIRECT(__ATTR_WUNUSED,__FILE *,__NOTHROW_RPC,__localdep_tmpfile,(void),tmpfile64,())
#else /* LIBC: tmpfile */
#undef ____localdep_tmpfile_defined
#endif /* tmpfile... */
#endif /* !____localdep_tmpfile_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(tmpfile_s) __ATTR_NONNULL((1)) __errno_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(tmpfile_s))(__FILE **__pstream) {
#line 2245 "kos/src/libc/magic/stdio.c"
	if (!__pstream)
		return __EINVAL;
	*__pstream = __localdep_tmpfile();
	if (!*__pstream)
		return __libc_geterrno_or(__ENOMEM);
	return 0;
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_HAVE_tmpfile) || defined(__CRT_HAVE_tmpfile64)) */
#endif /* !__local_tmpfile_s_defined */
