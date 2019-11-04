/* HASH CRC-32:0x4afaaf73 */
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
#ifndef __local_fgetc_defined
#if (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))
#define __local_fgetc_defined 1
#include <kos/anno.h>
/* Dependency: "_filbuf" */
#ifndef ____localdep__filbuf_defined
#define ____localdep__filbuf_defined 1
#if defined(__CRT_HAVE__filbuf)
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep__filbuf,(__FILE *__restrict __stream),_filbuf,(__stream)) __THROWS(...)
#else /* LIBC: _filbuf */
#undef ____localdep__filbuf_defined
#endif /* _filbuf... */
#endif /* !____localdep__filbuf_defined */

/* Dependency: "crt_fread" from "stdio" */
#ifndef ____localdep_crt_fread_defined
#define ____localdep_crt_fread_defined 1
#if defined(__CRT_HAVE_fread_unlocked) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_crt_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fread_nolock) && (defined(__USE_STDIO_UNLOCKED))
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_crt_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fread)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_crt_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#else /* LIBC: fread */
#undef ____localdep_crt_fread_defined
#endif /* crt_fread... */
#endif /* !____localdep_crt_fread_defined */

__NAMESPACE_LOCAL_BEGIN
/* Read and return a single character from `STREAM'
 * If the given `STREAM' has been exhausted or if an error occurred, `EOF' is
 * returned and the exact cause can be determined by using `ferror' and `feof' */
__LOCAL_LIBC(fgetc) __ATTR_NONNULL((1)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fgetc))(__FILE *__restrict __stream) __THROWS(...) {
#line 410 "kos/src/libc/magic/stdio.c"
#if defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf) && (!defined(__USE_STDIO_UNLOCKED) || !(defined(__CRT_HAVE_fread) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)))))
	return --__stream->__f_cnt >= 0 ? (int)((__UINT8_TYPE__)*__stream->__f_ptr++) : __localdep__filbuf(__stream);
#else
	char __ch;
	if (!__localdep_crt_fread(&__ch, sizeof(char), 1, __stream))
		return __EOF;
	return (int)__ch;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_s) || (defined(__USE_STDIO_UNLOCKED) && (defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))) */
#endif /* !__local_fgetc_defined */
