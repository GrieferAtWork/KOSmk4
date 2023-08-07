/* HASH CRC-32:0x40252d9d */
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
#ifndef __local_fsetpos64_unlocked_defined
#define __local_fsetpos64_unlocked_defined
#include <__crt.h>
#include <features.h>
#include <bits/crt/stdio.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_fsetpos64) || defined(__CRT_HAVE__IO_fsetpos64) || defined(__CRT_HAVE_fsetpos64_unlocked) || defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fsetpos64_defined
#define __local___localdep_fsetpos64_defined
#if defined(__CRT_HAVE_fsetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),_IO_fsetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fsetpos64)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),_IO_fsetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos_unlocked) && __SIZEOF_FPOS64_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos64_unlocked)
__CREDIRECT(__ATTR_IN(2) __ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fsetpos64,(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos),fsetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fsetpos) || defined(__CRT_HAVE__IO_fsetpos) || defined(__CRT_HAVE_fsetpos_unlocked) || (defined(__SEEK_SET) && (defined(__CRT_HAVE_fseeko64) || defined(__CRT_HAVE___fseeko64) || defined(__CRT_HAVE_fseek64) || defined(__CRT_HAVE__fseeki64) || defined(__CRT_HAVE_fseeko64_unlocked) || defined(__CRT_HAVE_fseek64_unlocked) || defined(__CRT_HAVE__fseeki64_nolock) || defined(__CRT_HAVE_fseeko) || defined(__CRT_HAVE_fseeko_unlocked) || defined(__CRT_HAVE_fseek) || defined(__CRT_HAVE_fseek_unlocked) || defined(__CRT_HAVE__fseek_nolock)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fsetpos64.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fsetpos64 __LIBC_LOCAL_NAME(fsetpos64)
#else /* ... */
#undef __local___localdep_fsetpos64_defined
#endif /* !... */
#endif /* !__local___localdep_fsetpos64_defined */
__LOCAL_LIBC(fsetpos64_unlocked) __ATTR_IN(2) __ATTR_INOUT(1) int
__NOTHROW_CB(__LIBCCALL __LIBC_LOCAL_NAME(fsetpos64_unlocked))(__FILE *__restrict __stream, __fpos64_t const *__restrict __pos) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fsetpos64)(__stream, __pos);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fsetpos64_unlocked_defined
#define __local___localdep_fsetpos64_unlocked_defined
#define __localdep_fsetpos64_unlocked __LIBC_LOCAL_NAME(fsetpos64_unlocked)
#endif /* !__local___localdep_fsetpos64_unlocked_defined */
#else /* __CRT_HAVE_fsetpos64 || __CRT_HAVE__IO_fsetpos64 || __CRT_HAVE_fsetpos64_unlocked || __CRT_HAVE_fsetpos || __CRT_HAVE__IO_fsetpos || __CRT_HAVE_fsetpos_unlocked || (__SEEK_SET && (__CRT_HAVE_fseeko64 || __CRT_HAVE___fseeko64 || __CRT_HAVE_fseek64 || __CRT_HAVE__fseeki64 || __CRT_HAVE_fseeko64_unlocked || __CRT_HAVE_fseek64_unlocked || __CRT_HAVE__fseeki64_nolock || __CRT_HAVE_fseeko || __CRT_HAVE_fseeko_unlocked || __CRT_HAVE_fseek || __CRT_HAVE_fseek_unlocked || __CRT_HAVE__fseek_nolock)) */
#undef __local_fsetpos64_unlocked_defined
#endif /* !__CRT_HAVE_fsetpos64 && !__CRT_HAVE__IO_fsetpos64 && !__CRT_HAVE_fsetpos64_unlocked && !__CRT_HAVE_fsetpos && !__CRT_HAVE__IO_fsetpos && !__CRT_HAVE_fsetpos_unlocked && (!__SEEK_SET || (!__CRT_HAVE_fseeko64 && !__CRT_HAVE___fseeko64 && !__CRT_HAVE_fseek64 && !__CRT_HAVE__fseeki64 && !__CRT_HAVE_fseeko64_unlocked && !__CRT_HAVE_fseek64_unlocked && !__CRT_HAVE__fseeki64_nolock && !__CRT_HAVE_fseeko && !__CRT_HAVE_fseeko_unlocked && !__CRT_HAVE_fseek && !__CRT_HAVE_fseek_unlocked && !__CRT_HAVE__fseek_nolock)) */
#endif /* !__local_fsetpos64_unlocked_defined */
