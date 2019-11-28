/* HASH CRC-32:0x2e001aab */
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
#ifndef __local_fwrite_defined
#if (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE_putc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE_putc_unlocked)
#define __local_fwrite_defined 1
#include <kos/anno.h>
/* Dependency: "fputc" from "stdio" */
#ifndef ____localdep_fputc_defined
#define ____localdep_fputc_defined 1
#if __has_builtin(__builtin_fputc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__FORCELOCAL __ATTR_NONNULL((2)) int (__LIBCCALL __localdep_fputc)(int __ch, __FILE *__restrict __stream) __THROWS(...) { return __builtin_fputc(__ch, __stream); }
#elif defined(__CRT_HAVE_fputc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc_unlocked) && defined(__USE_STDIO_UNLOCKED)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE__IO_putc)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),_IO_putc,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_fputc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),fputc_unlocked,(__ch,__stream)) __THROWS(...)
#elif defined(__CRT_HAVE_putc_unlocked)
/* Write a single character `CH' to `STREAM' */
__CREDIRECT(__ATTR_NONNULL((2)),int,,__localdep_fputc,(int __ch, __FILE *__restrict __stream),putc_unlocked,(__ch,__stream)) __THROWS(...)
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock) || defined(__CRT_HAVE__IO_fwrite)
#include <local/stdio/fputc.h>
/* Write a single character `CH' to `STREAM' */
#define __localdep_fputc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fputc))
#else /* CUSTOM: fputc */
#undef ____localdep_fputc_defined
#endif /* fputc... */
#endif /* !____localdep_fputc_defined */

__NAMESPACE_LOCAL_BEGIN
/* Write up to `ELEMSIZE * ELEMCOUNT' bytes of data from `BUF' into `STREAM' */
__LOCAL_LIBC(fwrite) __ATTR_NONNULL((1, 4)) __SIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(fwrite))(void const *__restrict __buf,
                                       __SIZE_TYPE__ __elemsize,
                                       __SIZE_TYPE__ __elemcount,
                                       __FILE *__restrict __stream) __THROWS(...) {
#line 619 "kos/src/libc/magic/stdio.c"
	__SIZE_TYPE__ __i, __result = 0;
	for (; __elemcount; --__elemcount, ++__result) {
		for (__i = 0; __i < __elemsize; ++__i) {
			unsigned char __byte;
			__byte = *(unsigned char *)__buf;
			if (__localdep_fputc((int)(unsigned int)__byte, __stream) == __EOF)
				goto __done;
			__buf = (unsigned char *)__buf + 1;
		}
	}
__done:
	return __result;
}
__NAMESPACE_LOCAL_END
#endif /* (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fputc || __CRT_HAVE_putc || __CRT_HAVE__IO_putc || __CRT_HAVE_fputc_unlocked || __CRT_HAVE_putc_unlocked */
#endif /* !__local_fwrite_defined */
