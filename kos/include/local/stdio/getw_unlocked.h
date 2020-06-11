/* HASH CRC-32:0x78e832b1 */
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
#ifndef __local_getw_unlocked_defined
#define __local_getw_unlocked_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_getw) || defined(__CRT_HAVE__getw) || ((defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock)))
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getw from stdio */
#ifndef __local___localdep_getw_defined
#define __local___localdep_getw_defined 1
#ifdef __CRT_HAVE_getw
/* Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_getw,(__FILE *__restrict __stream),getw,(__stream))
#elif defined(__CRT_HAVE__getw)
/* Similar to `getc()', but read 2 bytes */
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_getw,(__FILE *__restrict __stream),_getw,(__stream))
#elif (defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE_getc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock) || defined(__CRT_HAVE__IO_fread)) && (defined(__CRT_HAVE_ungetc) || defined(__CRT_HAVE__IO_ungetc) || defined(__CRT_HAVE_ungetc_unlocked) || defined(__CRT_HAVE__ungetc_nolock))
__NAMESPACE_LOCAL_END
#include <local/stdio/getw.h>
__NAMESPACE_LOCAL_BEGIN
/* Similar to `getc()', but read 2 bytes */
#define __localdep_getw __LIBC_LOCAL_NAME(getw)
#else /* ... */
#undef __local___localdep_getw_defined
#endif /* !... */
#endif /* !__local___localdep_getw_defined */
__LOCAL_LIBC(getw_unlocked) __ATTR_NONNULL((1)) int
(__LIBCCALL __LIBC_LOCAL_NAME(getw_unlocked))(__FILE *__restrict __stream) __THROWS(...) {
	return __localdep_getw(__stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getw_unlocked_defined
#define __local___localdep_getw_unlocked_defined 1
#define __localdep_getw_unlocked __LIBC_LOCAL_NAME(getw_unlocked)
#endif /* !__local___localdep_getw_unlocked_defined */
#else /* __CRT_HAVE_getw || __CRT_HAVE__getw || ((__CRT_HAVE_fgetc || __CRT_HAVE_getc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock || __CRT_HAVE__IO_fread) && (__CRT_HAVE_ungetc || __CRT_HAVE__IO_ungetc || __CRT_HAVE_ungetc_unlocked || __CRT_HAVE__ungetc_nolock)) */
#undef __local_getw_unlocked_defined
#endif /* !__CRT_HAVE_getw && !__CRT_HAVE__getw && ((!__CRT_HAVE_fgetc && !__CRT_HAVE_getc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock && !__CRT_HAVE__IO_fread) || (!__CRT_HAVE_ungetc && !__CRT_HAVE__IO_ungetc && !__CRT_HAVE_ungetc_unlocked && !__CRT_HAVE__ungetc_nolock)) */
#endif /* !__local_getw_unlocked_defined */
