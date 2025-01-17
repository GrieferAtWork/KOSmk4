/* HASH CRC-32:0x97e0144d */
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
#ifndef __local_fputs_defined
#define __local_fputs_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf))) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fwrite_defined
#define __local___localdep_fwrite_defined
#if defined(__CRT_HAVE_fwrite_unlocked) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock) && defined(__USE_STDIO_UNLOCKED)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif __has_builtin(__builtin_fwrite) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_fwrite)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,{ return __builtin_fwrite(__buf, __elemsize, __elemcount, __stream); })
#elif defined(__CRT_HAVE_fwrite)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_s)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_s,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_unlocked)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_INOUT(4) __ATTR_IN_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_fwrite,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_putc) || defined(__CRT_HAVE_fputc) || defined(__CRT_HAVE__IO_putc) || defined(__CRT_HAVE_putc_unlocked) || defined(__CRT_HAVE_fputc_unlocked) || defined(__CRT_HAVE__putc_nolock) || defined(__CRT_HAVE__fputc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__flsbuf) || defined(__CRT_HAVE___swbuf)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fwrite.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fwrite __LIBC_LOCAL_NAME(fwrite)
#else /* ... */
#undef __local___localdep_fwrite_defined
#endif /* !... */
#endif /* !__local___localdep_fwrite_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(fputs) __ATTR_IN(1) __ATTR_INOUT(2) __STDC_INT_AS_SSIZE_T
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fputs))(char const *__restrict __string, __FILE *__restrict __stream) {
	__STDC_INT_AS_SIZE_T __result;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_fwrite)(__string,
	                sizeof(char),
	                (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__string),
	                __stream);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fputs_defined
#define __local___localdep_fputs_defined
#define __localdep_fputs __LIBC_LOCAL_NAME(fputs)
#endif /* !__local___localdep_fputs_defined */
#else /* __CRT_HAVE_putc || __CRT_HAVE_fputc || __CRT_HAVE__IO_putc || __CRT_HAVE_putc_unlocked || __CRT_HAVE_fputc_unlocked || __CRT_HAVE__putc_nolock || __CRT_HAVE__fputc_nolock || (__CRT_DOS && (__CRT_HAVE__flsbuf || __CRT_HAVE___swbuf)) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#undef __local_fputs_defined
#endif /* !__CRT_HAVE_putc && !__CRT_HAVE_fputc && !__CRT_HAVE__IO_putc && !__CRT_HAVE_putc_unlocked && !__CRT_HAVE_fputc_unlocked && !__CRT_HAVE__putc_nolock && !__CRT_HAVE__fputc_nolock && (!__CRT_DOS || (!__CRT_HAVE__flsbuf && !__CRT_HAVE___swbuf)) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock */
#endif /* !__local_fputs_defined */
