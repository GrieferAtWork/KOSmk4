/* HASH CRC-32:0x73f1cf92 */
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
#ifndef __local_fgetc_unlocked_defined
#define __local_fgetc_unlocked_defined
#include <__crt.h>
#if (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__filbuf_defined
#define __local___localdep__filbuf_defined
#ifdef __CRT_HAVE__filbuf
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep__filbuf,(__FILE *__restrict __stream),_filbuf,(__stream))
#elif defined(__CRT_HAVE___uflow)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep__filbuf,(__FILE *__restrict __stream),__uflow,(__stream))
#elif defined(__CRT_HAVE___underflow)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep__filbuf,(__FILE *__restrict __stream),__underflow,(__stream))
#elif defined(__CRT_HAVE___srget)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB_NCX,__localdep__filbuf,(__FILE *__restrict __stream),__srget,(__stream))
#else /* ... */
#undef __local___localdep__filbuf_defined
#endif /* !... */
#endif /* !__local___localdep__filbuf_defined */
#ifndef __local___localdep_crt_fread_unlocked_defined
#define __local___localdep_crt_fread_unlocked_defined
#ifdef __CRT_HAVE_fread
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread_unlocked)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB_NCX,__localdep_crt_fread_unlocked,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#else /* ... */
#undef __local___localdep_crt_fread_unlocked_defined
#endif /* !... */
#endif /* !__local___localdep_crt_fread_unlocked_defined */
__NAMESPACE_LOCAL_END
#include <bits/crt/io-file.h>
#include <asm/crt/stdio.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fgetc_unlocked) __ATTR_INOUT(1) int
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fgetc_unlocked))(__FILE *__restrict __stream) {
#if defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))
	return --__stream->__f_cnt >= 0 ? (int)((__UINT8_TYPE__)*__stream->__f_ptr++) : (__NAMESPACE_LOCAL_SYM __localdep__filbuf)(__stream);
#else /* __CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget) */
	char __ch;
	if (!(__NAMESPACE_LOCAL_SYM __localdep_crt_fread_unlocked)(&__ch, sizeof(char), 1, __stream))
		return __EOF;
	return (int)__ch;
#endif /* !__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fgetc_unlocked_defined
#define __local___localdep_fgetc_unlocked_defined
#define __localdep_fgetc_unlocked __LIBC_LOCAL_NAME(fgetc_unlocked)
#endif /* !__local___localdep_fgetc_unlocked_defined */
#else /* (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#undef __local_fgetc_unlocked_defined
#endif /* (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock */
#endif /* !__local_fgetc_unlocked_defined */
