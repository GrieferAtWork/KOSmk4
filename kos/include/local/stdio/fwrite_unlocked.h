/* HASH CRC-32:0xf5927c0f */
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
#ifndef __local_fwrite_unlocked_defined
#define __local_fwrite_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fputc_unlocked from stdio */
#ifndef __local___localdep_fputc_unlocked_defined
#define __local___localdep_fputc_unlocked_defined 1
#if __has_builtin(__builtin_fputc_unlocked) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CEIREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,{ return __builtin_fputc_unlocked(__ch, __stream); })
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc_unlocked)
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream))
#elif defined(__CRT_HAVE_fputc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_putc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__flsbuf))
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep_fputc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s)
__NAMESPACE_LOCAL_END
#include <local/stdio/fputc_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `fputc()', but performs I/O without acquiring a lock to `STREAM' */
#define __localdep_fputc_unlocked __LIBC_LOCAL_NAME(fputc_unlocked)
#else /* ... */
#undef __local___localdep_fputc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fputc_unlocked_defined */
/* Same as `fwrite()', but performs I/O without acquiring a lock to `STREAM' */
__LOCAL_LIBC(fwrite_unlocked) __ATTR_WUNUSED __ATTR_NONNULL((1, 4)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(fwrite_unlocked))(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) __THROWS(...) {
	__SIZE_TYPE__ __i, __result = 0;
	for (; __elemcount; --__elemcount, ++__result) {
		for (__i = 0; __i < __elemsize; ++__i) {
			unsigned char __byte;
			__byte = *(unsigned char *)__buf;
			if (__localdep_fputc_unlocked((int)(unsigned int)__byte, __stream) == __EOF)
				goto __done;
			__buf = (unsigned char *)__buf + 1;
		}
	}
__done:
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fwrite_unlocked_defined
#define __local___localdep_fwrite_unlocked_defined 1
#define __localdep_fwrite_unlocked __LIBC_LOCAL_NAME(fwrite_unlocked)
#endif /* !__local___localdep_fwrite_unlocked_defined */
#else /* __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_HAVE_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE_fgetc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread || __CRT_HAVE_fread */
#undef __local_fwrite_unlocked_defined
#endif /* !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_HAVE_getc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_HAVE_fgetc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_HAVE__IO_getc || (__CRT_DOS && __CRT_HAVE__filbuf)) && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread */
#endif /* !__local_fwrite_unlocked_defined */
