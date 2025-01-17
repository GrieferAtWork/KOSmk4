/* HASH CRC-32:0xbda8cdcf */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getdelim_defined
#define __local_getdelim_defined
#include <__crt.h>
#include <features.h>
#if (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc_defined
#define __local___localdep_fgetc_defined
#if defined(__CRT_HAVE_fgetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif defined(__CRT_HAVE_fgetc_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep_fgetc,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetc __LIBC_LOCAL_NAME(fgetc)
#else /* ... */
#undef __local___localdep_fgetc_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_defined */
#ifndef __local___localdep_realloc_defined
#define __local___localdep_realloc_defined
#if __has_builtin(__builtin_realloc) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_realloc)
__CEIREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,{ return __builtin_realloc(__mallptr, __num_bytes); })
#elif defined(__CRT_HAVE_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),realloc,(__mallptr,__num_bytes))
#elif defined(__CRT_HAVE___libc_realloc)
__CREDIRECT(__ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ALLOC_SIZE((2)),void *,__NOTHROW_NCX,__localdep_realloc,(void *__mallptr, __SIZE_TYPE__ __num_bytes),__libc_realloc,(__mallptr,__num_bytes))
#else /* ... */
#undef __local___localdep_realloc_defined
#endif /* !... */
#endif /* !__local___localdep_realloc_defined */
#ifndef __local___localdep_ungetc_defined
#define __local___localdep_ungetc_defined
#if defined(__CRT_HAVE_ungetc_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE__IO_ungetc)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_IO_ungetc,(__ch,__stream))
#elif defined(__CRT_HAVE_ungetc_unlocked)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),ungetc_unlocked,(__ch,__stream))
#elif defined(__CRT_HAVE__ungetc_nolock)
__CREDIRECT(__ATTR_INOUT(2),int,__NOTHROW_NCX,__localdep_ungetc,(int __ch, __FILE *__restrict __stream),_ungetc_nolock,(__ch,__stream))
#else /* ... */
#undef __local___localdep_ungetc_defined
#endif /* !... */
#endif /* !__local___localdep_ungetc_defined */
__NAMESPACE_LOCAL_END
#include <asm/crt/stdio.h>
#include <hybrid/__assert.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getdelim) __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_INOUT(4) __SSIZE_TYPE__
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getdelim))(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream) {
	int __ch;
	char *__buffer;
	__SIZE_TYPE__ __bufsize, __result = 0;
	__buffer  = *__lineptr;
	__bufsize = __buffer ? *__pcount : 0;
	for (;;) {
		if (__result + 1 >= __bufsize) {
			/* Allocate more memory. */
			__SIZE_TYPE__ __new_bufsize = __bufsize * 2;
			if (__new_bufsize <= __result + 1)
				__new_bufsize = 16;
			__hybrid_assert(__new_bufsize > __result + 1);
			__buffer = (char *)(__NAMESPACE_LOCAL_SYM __localdep_realloc)(__buffer,
			                         __new_bufsize *
			                         sizeof(char));
			if __unlikely(!__buffer)
				return -1;
			__bufsize  = __new_bufsize;
			*__lineptr = __buffer;
			*__pcount  = __bufsize;
		}
		__ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
		if (__ch == __EOF)
			break; /* EOF */
		__buffer[__result++] = (char)__ch;
		if (__ch == __delimiter)
			break; /* Delimiter reached */
		/* Special case for line-delimiter. */
		if (__delimiter == '\n' && __ch == '\r') {
			/* Deal with '\r\n', as well as '\r' */
			__ch = (__NAMESPACE_LOCAL_SYM __localdep_fgetc)(__stream);
			if (__ch != __EOF && __ch != '\n')
				(__NAMESPACE_LOCAL_SYM __localdep_ungetc)(__ch, __stream);
			/* Unify linefeeds (to use POSIX notation) */
			__buffer[__result - 1] = '\n';
			break;
		}
	}
	/* NUL-Terminate the buffer. */
	__buffer[__result] = '\0';
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getdelim_defined
#define __local___localdep_getdelim_defined
#define __localdep_getdelim __LIBC_LOCAL_NAME(getdelim)
#endif /* !__local___localdep_getdelim_defined */
#else /* (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock) */
#undef __local_getdelim_defined
#endif /* (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock) */
#endif /* !__local_getdelim_defined */
