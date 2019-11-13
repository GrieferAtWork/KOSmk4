/* HASH CRC-32:0xab0aef89 */
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
#ifndef __local_fread_s_defined
#if (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked)
#define __local_fread_s_defined 1
#include <kos/anno.h>
#include <parts/errno.h>
/* Dependency: "fread" from "stdio" */
#ifndef ____localdep_fread_defined
#define ____localdep_fread_defined 1
#if defined(__CRT_HAVE_fread_unlocked) && (defined(__USE_STDIO_UNLOCKED))
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fread_nolock) && (defined(__USE_STDIO_UNLOCKED))
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_fread) && (defined(__USE_STDIO_UNLOCKED))
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fread)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fread_unlocked)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__fread_nolock)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_fread)
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1, 4)),__SIZE_TYPE__,,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked)
#include <local/stdio/fread.h>
/* Read up to `ELEMSIZE * ELEMCOUNT' bytes of data from `STREAM' into `BUF' */
#define __localdep_fread (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fread))
#else /* CUSTOM: fread */
#undef ____localdep_fread_defined
#endif /* fread... */
#endif /* !____localdep_fread_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fread_s) __ATTR_WUNUSED __ATTR_NONNULL((1, 5)) __SIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fread_s))(void *__restrict __buf,
                                                     __SIZE_TYPE__ __bufsize,
                                                     __SIZE_TYPE__ __elemsize,
                                                     __SIZE_TYPE__ __elemcount,
                                                     __FILE *__restrict __stream) {
#line 2672 "kos/src/libc/magic/stdio.c"
	__bufsize = __elemsize ? __bufsize / __elemsize : 0;
	return __localdep_fread(__buf, __elemsize, __bufsize < __elemcount ? __bufsize : __elemcount, __stream);
}
__NAMESPACE_LOCAL_END
#endif /* (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) */
#endif /* !__local_fread_s_defined */
