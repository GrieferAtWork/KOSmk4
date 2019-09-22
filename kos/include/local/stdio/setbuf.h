/* HASH CRC-32:0xccb2b63c */
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
#ifndef __local_setbuf_defined
#if defined(__CRT_HAVE_setvbuf)
#define __local_setbuf_defined 1
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
#ifndef __BUFSIZ
#ifdef __USE_DOS
#define __BUFSIZ 512
#else
#define __BUFSIZ 8192
#endif
#endif
#ifdef __CRT_DOS_PRIMARY
#define ___IOFBF 0x0000 /* Fully buffered. */
#define ___IOLBF 0x0040 /* Line buffered. */
#define ___IONBF 0x0004 /* No buffering. */
#else
#define ___IOFBF 0      /* Fully buffered. */
#define ___IOLBF 1      /* Line buffered. */
#define ___IONBF 2      /* No buffering. */
#endif
/* Alias for `setvbuf(STREAM, buf, _IOFBF, BUFSIZ)' */
__LOCAL_LIBC(setbuf) __ATTR_NONNULL((1)) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setbuf))(__FILE *__restrict __stream,
                                                    char *__restrict __buf) {
#line 386 "kos/src/libc/magic/stdio.c"
	__localdep_setvbuf(__stream, __buf,
	        __buf ? ___IOFBF : ___IONBF,
	        __buf ? __BUFSIZ : 0);
}
__NAMESPACE_LOCAL_END
#endif /* defined(__CRT_HAVE_setvbuf) */
#endif /* !__local_setbuf_defined */
