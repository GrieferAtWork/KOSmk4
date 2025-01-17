/* HASH CRC-32:0xf0e5ef83 */
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
#ifndef __local_getline_defined
#define __local_getline_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_getdelim) || defined(__CRT_HAVE_getdelim_unlocked) || defined(__CRT_HAVE___getdelim) || defined(__CRT_HAVE__IO_getdelim) || ((defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_getdelim_defined
#define __local___localdep_getdelim_defined
#if defined(__CRT_HAVE_getdelim_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_INOUT(4),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_INOUT(4),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE_getdelim_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_INOUT(4),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),getdelim_unlocked,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE___getdelim)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_INOUT(4),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),__getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif defined(__CRT_HAVE__IO_getdelim)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_INOUT(4),__SSIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_getdelim,(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, int __delimiter, __FILE *__restrict __stream),_IO_getdelim,(__lineptr,__pcount,__delimiter,__stream))
#elif (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && (defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/getdelim.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getdelim __LIBC_LOCAL_NAME(getdelim)
#else /* ... */
#undef __local___localdep_getdelim_defined
#endif /* !... */
#endif /* !__local___localdep_getdelim_defined */
__LOCAL_LIBC(getline) __ATTR_WUNUSED __ATTR_INOUT(1) __ATTR_INOUT(2) __ATTR_INOUT(3) __SSIZE_TYPE__
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(getline))(char **__restrict __lineptr, __SIZE_TYPE__ *__restrict __pcount, __FILE *__restrict __stream) {
	return (__NAMESPACE_LOCAL_SYM __localdep_getdelim)(__lineptr, __pcount, '\n', __stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getline_defined
#define __local___localdep_getline_defined
#define __localdep_getline __LIBC_LOCAL_NAME(getline)
#endif /* !__local___localdep_getline_defined */
#else /* __CRT_HAVE_getdelim || __CRT_HAVE_getdelim_unlocked || __CRT_HAVE___getdelim || __CRT_HAVE__IO_getdelim || ((__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) && (__CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#undef __local_getline_defined
#endif /* !__CRT_HAVE_getdelim && !__CRT_HAVE_getdelim_unlocked && !__CRT_HAVE___getdelim && !__CRT_HAVE__IO_getdelim && ((!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) || (!__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock)) */
#endif /* !__local_getline_defined */
