/* HASH CRC-32:0xbd58258e */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_fgetpos_unlocked_defined
#define __local_fgetpos_unlocked_defined
#include <__crt.h>
#include <features.h>
#include <bits/crt/stdio.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_fgetpos) || defined(__CRT_HAVE__IO_fgetpos) || defined(__CRT_HAVE_fgetpos_unlocked) || defined(__CRT_HAVE_fgetpos64) || defined(__CRT_HAVE__IO_fgetpos64) || defined(__CRT_HAVE_fgetpos64_unlocked) || defined(__CRT_HAVE_ftello64) || defined(__CRT_HAVE___ftello64) || defined(__CRT_HAVE_ftell64) || defined(__CRT_HAVE__ftelli64) || defined(__CRT_HAVE_ftello64_unlocked) || defined(__CRT_HAVE_ftell64_unlocked) || defined(__CRT_HAVE__ftelli64_nolock) || defined(__CRT_HAVE_ftello) || defined(__CRT_HAVE_ftello_unlocked) || defined(__CRT_HAVE_ftell) || defined(__CRT_HAVE__IO_ftell) || defined(__CRT_HAVE_ftell_unlocked) || defined(__CRT_HAVE__ftell_nolock)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fgetpos_defined
#define __local___localdep_fgetpos_defined
#if defined(__CRT_HAVE_fgetpos_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && defined(__USE_STDIO_UNLOCKED) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),_IO_fgetpos,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE__IO_fgetpos64) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),_IO_fgetpos64,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS32_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),fgetpos_unlocked,(__stream,__pos))
#elif defined(__CRT_HAVE_fgetpos64_unlocked) && __SIZEOF_FPOS_T__ == __SIZEOF_FPOS64_T__
__CREDIRECT(__ATTR_INOUT(1) __ATTR_OUT(2),int,__NOTHROW_CB_NCX,__localdep_fgetpos,(__FILE *__restrict __stream, __fpos_t *__restrict __pos),fgetpos64_unlocked,(__stream,__pos))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fgetpos.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fgetpos __LIBC_LOCAL_NAME(fgetpos)
#endif /* !... */
#endif /* !__local___localdep_fgetpos_defined */
__LOCAL_LIBC(fgetpos_unlocked) __ATTR_INOUT(1) __ATTR_OUT(2) int
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fgetpos_unlocked))(__FILE *__restrict __stream, __fpos_t *__restrict __pos) {
	return (__NAMESPACE_LOCAL_SYM __localdep_fgetpos)(__stream, __pos);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fgetpos_unlocked_defined
#define __local___localdep_fgetpos_unlocked_defined
#define __localdep_fgetpos_unlocked __LIBC_LOCAL_NAME(fgetpos_unlocked)
#endif /* !__local___localdep_fgetpos_unlocked_defined */
#else /* __CRT_HAVE_fgetpos || __CRT_HAVE__IO_fgetpos || __CRT_HAVE_fgetpos_unlocked || __CRT_HAVE_fgetpos64 || __CRT_HAVE__IO_fgetpos64 || __CRT_HAVE_fgetpos64_unlocked || __CRT_HAVE_ftello64 || __CRT_HAVE___ftello64 || __CRT_HAVE_ftell64 || __CRT_HAVE__ftelli64 || __CRT_HAVE_ftello64_unlocked || __CRT_HAVE_ftell64_unlocked || __CRT_HAVE__ftelli64_nolock || __CRT_HAVE_ftello || __CRT_HAVE_ftello_unlocked || __CRT_HAVE_ftell || __CRT_HAVE__IO_ftell || __CRT_HAVE_ftell_unlocked || __CRT_HAVE__ftell_nolock */
#undef __local_fgetpos_unlocked_defined
#endif /* !__CRT_HAVE_fgetpos && !__CRT_HAVE__IO_fgetpos && !__CRT_HAVE_fgetpos_unlocked && !__CRT_HAVE_fgetpos64 && !__CRT_HAVE__IO_fgetpos64 && !__CRT_HAVE_fgetpos64_unlocked && !__CRT_HAVE_ftello64 && !__CRT_HAVE___ftello64 && !__CRT_HAVE_ftell64 && !__CRT_HAVE__ftelli64 && !__CRT_HAVE_ftello64_unlocked && !__CRT_HAVE_ftell64_unlocked && !__CRT_HAVE__ftelli64_nolock && !__CRT_HAVE_ftello && !__CRT_HAVE_ftello_unlocked && !__CRT_HAVE_ftell && !__CRT_HAVE__IO_ftell && !__CRT_HAVE_ftell_unlocked && !__CRT_HAVE__ftell_nolock */
#endif /* !__local_fgetpos_unlocked_defined */
