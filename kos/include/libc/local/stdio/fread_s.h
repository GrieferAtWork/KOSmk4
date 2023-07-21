/* HASH CRC-32:0x4d13e1ad */
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
#ifndef __local_fread_s_defined
#define __local_fread_s_defined
#include <__crt.h>
#include <features.h>
#if defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget))) || defined(__CRT_HAVE_fread) || defined(__CRT_HAVE__IO_fread) || defined(__CRT_HAVE_fread_unlocked) || defined(__CRT_HAVE__fread_nolock)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fread_defined
#define __local___localdep_fread_defined
#if defined(__CRT_HAVE_fread_unlocked) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock) && defined(__USE_STDIO_UNLOCKED)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__IO_fread)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_IO_fread,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_fread_unlocked)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),fread_unlocked,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE__fread_nolock)
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(4) __ATTR_OUT_OPT(1),__SIZE_TYPE__,__NOTHROW_CB,__localdep_fread,(void *__restrict __buf, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream),_fread_nolock,(__buf,__elemsize,__elemcount,__stream))
#elif defined(__CRT_HAVE_getc) || defined(__CRT_HAVE_fgetc) || defined(__CRT_HAVE__IO_getc) || defined(__CRT_HAVE_fgetc_unlocked) || defined(__CRT_HAVE_getc_unlocked) || defined(__CRT_HAVE__getc_nolock) || defined(__CRT_HAVE__fgetc_nolock) || (defined(__CRT_DOS) && (defined(__CRT_HAVE__filbuf) || defined(__CRT_HAVE___uflow) || defined(__CRT_HAVE___underflow) || defined(__CRT_HAVE___srget)))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fread.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fread __LIBC_LOCAL_NAME(fread)
#else /* ... */
#undef __local___localdep_fread_defined
#endif /* !... */
#endif /* !__local___localdep_fread_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
#include <hybrid/__overflow.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(fread_s) __ATTR_WUNUSED __ATTR_INOUT(5) __ATTR_OUT_OPT(1) __SIZE_TYPE__
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(fread_s))(void *__restrict __buf, __SIZE_TYPE__ __bufsize, __SIZE_TYPE__ __elemsize, __SIZE_TYPE__ __elemcount, __FILE *__restrict __stream) {
	__SIZE_TYPE__ __reqbuf;
	if (__hybrid_overflow_umul(__elemsize, __elemcount, &__reqbuf) ||
	    __reqbuf > __bufsize) {
#ifdef __ERANGE
		(void)__libc_seterrno(__ERANGE);
#endif /* __ERANGE */
		return 0;
	}
	if __unlikely(!__stream || !__buf) {
#ifdef __EINVAL
		(void)__libc_seterrno(__EINVAL);
#endif /* __EINVAL */
		return 0;
	}
	return (__NAMESPACE_LOCAL_SYM __localdep_fread)(__buf, __elemsize, __elemcount, __stream);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fread_s_defined
#define __local___localdep_fread_s_defined
#define __localdep_fread_s __LIBC_LOCAL_NAME(fread_s)
#endif /* !__local___localdep_fread_s_defined */
#else /* __CRT_HAVE_getc || __CRT_HAVE_fgetc || __CRT_HAVE__IO_getc || __CRT_HAVE_fgetc_unlocked || __CRT_HAVE_getc_unlocked || __CRT_HAVE__getc_nolock || __CRT_HAVE__fgetc_nolock || (__CRT_DOS && (__CRT_HAVE__filbuf || __CRT_HAVE___uflow || __CRT_HAVE___underflow || __CRT_HAVE___srget)) || __CRT_HAVE_fread || __CRT_HAVE__IO_fread || __CRT_HAVE_fread_unlocked || __CRT_HAVE__fread_nolock */
#undef __local_fread_s_defined
#endif /* !__CRT_HAVE_getc && !__CRT_HAVE_fgetc && !__CRT_HAVE__IO_getc && !__CRT_HAVE_fgetc_unlocked && !__CRT_HAVE_getc_unlocked && !__CRT_HAVE__getc_nolock && !__CRT_HAVE__fgetc_nolock && (!__CRT_DOS || (!__CRT_HAVE__filbuf && !__CRT_HAVE___uflow && !__CRT_HAVE___underflow && !__CRT_HAVE___srget)) && !__CRT_HAVE_fread && !__CRT_HAVE__IO_fread && !__CRT_HAVE_fread_unlocked && !__CRT_HAVE__fread_nolock */
#endif /* !__local_fread_s_defined */
