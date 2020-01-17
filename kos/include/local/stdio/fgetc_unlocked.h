/* HASH CRC-32:0x784fbca6 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fgetc_unlocked_defined
#if (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#define __local_fgetc_unlocked_defined 1
#include <kos/anno.h>
/* Dependency: "_filbuf" */
#ifndef ____localdep__filbuf_defined
#define ____localdep__filbuf_defined 1
#ifdef __CRT_HAVE__filbuf
__CREDIRECT(__ATTR_NONNULL((1)),int,,__localdep__filbuf,(__FILE *__restrict __stream),_filbuf,(__stream)) __THROWS(...)
#else /* LIBC: _filbuf */
#undef ____localdep__filbuf_defined
#endif /* _filbuf... */
#endif /* !____localdep__filbuf_defined */

/* Dependency: "crt_fread_unlocked" from "stdio" */
#ifndef ____localdep_crt_fread_unlocked_defined
#define ____localdep_crt_fread_unlocked_defined 1
#ifdef __CRT_HAVE_fread_unlocked
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fread_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_fread)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fread)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#else /* LIBC: fread_unlocked */
#undef ____localdep_crt_fread_unlocked_defined
#endif /* crt_fread_unlocked... */
#endif /* !____localdep_crt_fread_unlocked_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `fgetc()', but performs I/O without acquiring a lock to `STREAM' */
__LOCAL_LIBC(fgetc_unlocked) __ATTR_NONNULL((1)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fgetc_unlocked))(__FILE *__restrict __stream) __THROWS(...) {
#line 1200 "kos/src/libc/magic/stdio.c"
#if defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)
	return --__stream->__f_cnt >= 0 ? (int)((__UINT8_TYPE__)*__stream->__f_ptr++) : __localdep__filbuf(__stream);
#else
	char __ch;
	if (!__localdep_crt_fread_unlocked(&__ch, sizeof(char), 1, __stream))
		return __EOF;
	return (int)__ch;
#endif
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread || __CRT_HAVE_fread */
#endif /* !__local_fgetc_unlocked_defined */
