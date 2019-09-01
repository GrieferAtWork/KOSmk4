/* HASH 0x76b66035 */
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
#ifndef __local_setbuffer_defined
#if defined(__CRT_HAVE_setvbuf)
#define __local_setbuffer_defined 1
/* Dependency: "setvbuf" */
#ifndef ____localdep_setvbuf_defined
#define ____localdep_setvbuf_defined 1
#if defined(__CRT_HAVE_setvbuf)
/* Set the buffer and buffer-mode to-be used by the given `STREAM'
 * @param modes: One of `_IOFBF', `_IOLBF' or `_IONBF' */
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,__localdep_setvbuf,(__FILE *__restrict __stream, char *__restrict __buf, int __modes, __SIZE_TYPE__ __bufsize),setvbuf,(__stream,__buf,__modes,__bufsize))
#else /* LIBC: setvbuf */
#undef ____localdep_setvbuf_defined
#endif /* setvbuf... */
#endif /* !____localdep_setvbuf_defined */

__NAMESPACE_LOCAL_BEGIN
/* Specify the location and size for the buffer to-be used by `STREAM' */
__LOCAL_LIBC(setbuffer) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setbuffer))(__FILE *__restrict __stream,
                                                       char *__buf,
                                                       __SIZE_TYPE__ __bufsize) {
#line 1016 "kos/src/libc/magic/stdio.c"
	__localdep_setvbuf(__stream, __buf, __buf ? ___IOFBF : ___IONBF, __buf ? __bufsize : (__SIZE_TYPE__)0);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_setvbuf) */
#endif /* !__local_setbuffer_defined */
