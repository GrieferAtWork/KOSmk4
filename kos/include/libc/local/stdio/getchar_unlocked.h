/* HASH CRC-32:0x7afbe7c3 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_getchar_unlocked_defined
#define __local_getchar_unlocked_defined
#include <__crt.h>
#include <libc/template/stdstreams.h>
#if defined(__LOCAL_stdin) && (defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetc_unlocked_defined
#define __local___localdep_fgetc_unlocked_defined
#ifdef __CRT_HAVE_fgetc_unlocked
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc_unlocked,(__stream))
#elif defined(__CRT_HAVE_getc_unlocked)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc_unlocked,(__stream))
#elif defined(__CRT_HAVE__getc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_getc_nolock,(__stream))
#elif defined(__CRT_HAVE__fgetc_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_fgetc_nolock,(__stream))
#elif defined(__CRT_HAVE_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),getc,(__stream))
#elif defined(__CRT_HAVE_fgetc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),fgetc,(__stream))
#elif defined(__CRT_HAVE__IO_getc) && (!defined(__CRT_DOS) || (!defined(__CRT_HAVE__filbuf) && !defined(__CRT_HAVE___uflow) && !defined(__CRT_HAVE___underflow) && !defined(__CRT_HAVE___srget)))
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fgetc_unlocked,(__FILE *__restrict __stream),_IO_getc,(__stream))
#elif (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetc_unlocked.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetc_unlocked __LIBC_LOCAL_NAME(fgetc_unlocked)
#else /* ... */
#undef __local___localdep_fgetc_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_fgetc_unlocked_defined */
__LOCAL_LIBC(getchar_unlocked) int
__NOTHROW_CB(__LIBCCALL __LIBC_LOCAL_NAME(getchar_unlocked))(void) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fgetc_unlocked)(__LOCAL_stdin);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_getchar_unlocked_defined
#define __local___localdep_getchar_unlocked_defined
#define __localdep_getchar_unlocked __LIBC_LOCAL_NAME(getchar_unlocked)
#endif /* !__local___localdep_getchar_unlocked_defined */
#else /* __LOCAL_stdin && (__CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_HAVE_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE_fgetc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget))) || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock) */
#undef __local_getchar_unlocked_defined
#endif /* !__LOCAL_stdin || (!__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock) */
#endif /* !__local_getchar_unlocked_defined */
