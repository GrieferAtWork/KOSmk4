/* HASH CRC-32:0xd2218985 */
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
#ifndef __local_fputc_unlocked_defined
#define __local_fputc_unlocked_defined
#include <__crt.h>
#if (defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)) || defined(__CRT_HAVE_fwrite) || defined(__CRT_HAVE__IO_fwrite) || defined(__CRT_HAVE_fwrite_s) || defined(__CRT_HAVE_fwrite_unlocked) || defined(__CRT_HAVE__fwrite_nolock)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep__flsbuf_defined) && defined(__CRT_HAVE__flsbuf)
#define __local___localdep__flsbuf_defined
__CREDIRECT(__ATTR_NONNULL((2)),int,__THROWING,__localdep__flsbuf,(int __ch, __FILE *__restrict __stream),_flsbuf,(__ch,__stream))
#endif /* !__local___localdep__flsbuf_defined && __CRT_HAVE__flsbuf */
#ifndef __local___localdep_crt_fwrite_unlocked_defined
#define __local___localdep_crt_fwrite_unlocked_defined
#ifdef __CRT_HAVE_fwrite
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_crt_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fwrite)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_crt_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fwrite,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_s)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_crt_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_s,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fwrite_unlocked)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_crt_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fwrite_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fwrite_nolock)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((1, 4)),__SIZE_TYPE__,__THROWING,__localdep_crt_fwrite_unlocked,(void const *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fwrite_nolock,(__buf,__elemsize,__elemcount,__stream))
#else /* ... */
#undef __local___localdep_crt_fwrite_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fwrite_unlocked_defined */
__LOCAL_LIBC(fputc_unlocked) __ATTR_NONNULL((2)) int
(__LIBCCALL __LIBC_LOCAL_NAME(fputc_unlocked))(int __ch, __FILE *__restrict __stream) __THROWS(...) {
#if defined(__CRT_DOS) && defined(__CRT_HAVE__flsbuf)
	return --__stream->__f_cnt >= 0 ? (int)((__UINT8_TYPE__)(*__stream->__f_ptr++ = (char)__ch)) : (__NAMESPACE_LOCAL_SYM __localdep__flsbuf)(__ch, __stream);
#else /* __CRT_DOS && __CRT_HAVE__flsbuf */
	unsigned char __byte = (unsigned char)(unsigned int)__ch;
	if (!(__NAMESPACE_LOCAL_SYM __localdep_crt_fwrite_unlocked)(&__byte, sizeof(unsigned char), 1, __stream))
		return __EOF;
	return __ch;
#endif /* !__CRT_DOS || !__CRT_HAVE__flsbuf */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fputc_unlocked_defined
#define __local___localdep_fputc_unlocked_defined
#define __localdep_fputc_unlocked __LIBC_LOCAL_NAME(fputc_unlocked)
#endif /* !__local___localdep_fputc_unlocked_defined */
#else /* (__CRT_DOS && __CRT_HAVE__flsbuf) || __CRT_HAVE_fwrite || __CRT_HAVE__IO_fwrite || __CRT_HAVE_fwrite_s || __CRT_HAVE_fwrite_unlocked || __CRT_HAVE__fwrite_nolock */
#undef __local_fputc_unlocked_defined
#endif /* (!__CRT_DOS || !__CRT_HAVE__flsbuf) && !__CRT_HAVE_fwrite && !__CRT_HAVE__IO_fwrite && !__CRT_HAVE_fwrite_s && !__CRT_HAVE_fwrite_unlocked && !__CRT_HAVE__fwrite_nolock */
#endif /* !__local_fputc_unlocked_defined */
