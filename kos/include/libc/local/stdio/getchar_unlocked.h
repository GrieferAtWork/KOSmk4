/* HASH CRC-32:0x2014dad */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getchar_unlocked_defined
#define __local_getchar_unlocked_defined 1
#include <__crt.h>
#if !defined(__NO_STDSTREAMS) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))) || (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc_unlocked_defined
#define __local___localdep_fgetc_unlocked_defined 1
#ifdef __CRT_HAVE_fgetc_unlocked
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || !defined(__CRT_HAVE__filbuf))
__CREDIRECT(__ATTR_NONNULL((1)),int,__THROWING,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && defined(__CRT_HAVE__filbuf)) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetc_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetc_unlocked __LIBC_LOCAL_NAME(fgetc_unlocked)
#else /* ... */
#undef __local___localdep_fgetc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <libc/local/stdstreams.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(getchar_unlocked) int
(__LIBCCALL __LIBC_LOCAL_NAME(getchar_unlocked))(void) __THROWS(...) {
	return __localdep_fgetc_unlocked(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getchar_unlocked_defined
#define __local___localdep_getchar_unlocked_defined 1
#define __localdep_getchar_unlocked __LIBC_LOCAL_NAME(getchar_unlocked)
#endif /* !__local___localdep_getchar_unlocked_defined */
#else /* !__NO_STDSTREAMS && (__CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || (__CRT_HAVE_fgetc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf)) || (__CRT_DOS && __CRT_HAVE__filbuf) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) */
#undef __local_getchar_unlocked_defined
#endif /* __NO_STDSTREAMS || (!__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE_fgetc && !__CRT_HAVE_getc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || !__CRT_HAVE__filbuf) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) */
#endif /* !__local_getchar_unlocked_defined */
