/* HASH CRC-32:0x4fc2d2c4 */
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
#ifndef __local_setbuf_defined
#define __local_setbuf_defined
#include <__crt.h>
#include <asm/crt/stdio.h>
#include <features.h>
#if defined(___IOFBF) && defined(___IONBF) && defined(__BUFSIZ) && (defined(__CRT_HAVE_setvbuf) || defined(__CRT_HAVE__IO_setvbuf) || defined(__CRT_HAVE_setvbuf_unlocked))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setvbuf_defined
#define __local___localdep_setvbuf_defined
#if defined(__CRT_HAVE_setvbuf_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_setvbuf,(__FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, __SIZE_TYPE__ __bufsize),setvbuf_unlocked,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_setvbuf,(__FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, __SIZE_TYPE__ __bufsize),setvbuf,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE__IO_setvbuf)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_setvbuf,(__FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, __SIZE_TYPE__ __bufsize),_IO_setvbuf,(__stream,__buf,__modes,__bufsize))
#elif defined(__CRT_HAVE_setvbuf_unlocked)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_NCX,__localdep_setvbuf,(__FILE *__restrict __stream, char *__restrict __buf, __STDC_INT_AS_UINT_T __modes, __SIZE_TYPE__ __bufsize),setvbuf_unlocked,(__stream,__buf,__modes,__bufsize))
#else /* ... */
#undef __local___localdep_setvbuf_defined
#endif /* !... */
#endif /* !__local___localdep_setvbuf_defined */
__LOCAL_LIBC(setbuf) __ATTR_INOUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setbuf))(__FILE *__restrict __stream, char *__buf) {
	(__NAMESPACE_LOCAL_SYM __localdep_setvbuf)(__stream, __buf,
	        __buf ? ___IOFBF : ___IONBF,
	        __buf ? __BUFSIZ : 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setbuf_defined
#define __local___localdep_setbuf_defined
#define __localdep_setbuf __LIBC_LOCAL_NAME(setbuf)
#endif /* !__local___localdep_setbuf_defined */
#else /* ___IOFBF && ___IONBF && __BUFSIZ && (__CRT_HAVE_setvbuf || __CRT_HAVE__IO_setvbuf || __CRT_HAVE_setvbuf_unlocked) */
#undef __local_setbuf_defined
#endif /* !___IOFBF || !___IONBF || !__BUFSIZ || (!__CRT_HAVE_setvbuf && !__CRT_HAVE__IO_setvbuf && !__CRT_HAVE_setvbuf_unlocked) */
#endif /* !__local_setbuf_defined */
