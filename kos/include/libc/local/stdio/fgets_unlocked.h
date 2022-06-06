/* HASH CRC-32:0xce4eff52 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fgets_unlocked_defined
#define __local_fgets_unlocked_defined
#include <__crt.h>
#include <features.h>
#if (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)) && (defined(__CRT_HAVE_ferror) || defined(__CRT_HAVE__IO_ferror) || defined(__CRT_HAVE_ferror_unlocked))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_ferror_unlocked_defined
#define __local___localdep_ferror_unlocked_defined
#if defined(__CRT_HAVE_ferror_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#elif defined(__CRT_HAVE_ferror)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror,(__stream))
#elif defined(__CRT_HAVE__IO_ferror)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),_IO_ferror,(__stream))
#elif defined(__CRT_HAVE_ferror_unlocked)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),int,__NOTHROW_NCX,__localdep_ferror_unlocked,(__FILE __KOS_FIXED_CONST *__restrict __stream),ferror_unlocked,(__stream))
#else /* ... */
#undef __local___localdep_ferror_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_ferror_unlocked_defined */
#ifndef __local___localdep_fgetc_unlocked_defined
#define __local___localdep_fgetc_unlocked_defined
#ifdef __CRT_HAVE_fgetc_unlocked
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow)))
__CREDIRECT(__ATTR_INOUT(1),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetc_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetc_unlocked __LIBC_LOCAL_NAME(fgetc_unlocked)
#else /* ... */
#undef __local___localdep_fgetc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_unlocked_defined */
#ifndef __local___localdep_ungetc_unlocked_defined
#define __local___localdep_ungetc_unlocked_defined
#ifdef __CRT_HAVE_ungetc_unlocked
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc_unlocked,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <asm/crt/stdio.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fgets_unlocked) __ATTR_WUNUSED __ATTR_INOUT(3) __ATTR_OUTS(1, 2) char *
(__LIBCCALL __LIBC_LOCAL_NAME(fgets_unlocked))(char *__restrict __buf, __STDC_INT_AS_SIZE_T __bufsize, __FILE *__restrict __stream) __THROWS(...) {
	__SIZE_TYPE__ __n;
	if __unlikely(!__buf || !__bufsize) {
		/* The buffer cannot be empty! */
#ifdef __ERANGE
		(void)__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
		return __NULLPTR;
	}
	for (__n = 0; __n < __bufsize - 1; ++__n) {
		int __ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc_unlocked)(__stream);
		if (__ch == __EOF) {
			if (__n == 0 || (__NAMESPACE_LOCAL_SYM __localdep_ferror_unlocked)(__stream))
				return __NULLPTR;
			break;
		}
		if (__ch == '\r') {
			/* Special handling to convert both `\r' and `\r\n' into `\n' */
			__buf[__n++] = '\n';
			__ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc_unlocked)(__stream);
			if (__ch == __EOF) {
				if (__n == 0 || (__NAMESPACE_LOCAL_SYM __localdep_ferror_unlocked)(__stream))
					return __NULLPTR;
				break;
			}
			if (__ch == '\r')
				continue;
			(__NAMESPACE_LOCAL_SYM __localdep_ungetc_unlocked)(__ch, __stream);
			break;
		}
		__buf[__n] = (char)__ch;
		if (__ch == '\n')
			break;
	}
	__buf[__n] = '\0';
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fgets_unlocked_defined
#define __local___localdep_fgets_unlocked_defined
#define __localdep_fgets_unlocked __LIBC_LOCAL_NAME(fgets_unlocked)
#endif /* !__local___localdep_fgets_unlocked_defined */
#else /* (__CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) && (__CRT_HAVE_ferror || __CRT_HAVE__IO_ferror || __CRT_HAVE_ferror_unlocked) */
#undef __local_fgets_unlocked_defined
#endif /* (!__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) || (!__CRT_HAVE_ferror && !__CRT_HAVE__IO_ferror && !__CRT_HAVE_ferror_unlocked) */
#endif /* !__local_fgets_unlocked_defined */
