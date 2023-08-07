/* HASH CRC-32:0x940e4cfa */
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
#ifndef __local_sgetspent_defined
#define __local_sgetspent_defined
#include <__crt.h>
#include <bits/types.h>
#if defined(__CRT_HAVE_fgetspent) && (defined(__CRT_HAVE_fmemopen) || ((defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))))
#include <bits/crt/db/spwd.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_fclose_defined
#define __local___localdep_fclose_defined
#ifdef __CRT_HAVE_fclose
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fclose,(__FILE *__restrict __stream),fclose,(__stream))
#elif defined(__CRT_HAVE__fclose_nolock)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fclose,(__FILE *__restrict __stream),_fclose_nolock,(__stream))
#elif defined(__CRT_HAVE__IO_fclose)
__CREDIRECT(__ATTR_INOUT(1),int,__NOTHROW_CB,__localdep_fclose,(__FILE *__restrict __stream),_IO_fclose,(__stream))
#else /* ... */
#undef __local___localdep_fclose_defined
#endif /* !... */
#endif /* !__local___localdep_fclose_defined */
#ifndef __local___localdep_fgetspent_defined
#define __local___localdep_fgetspent_defined
__CREDIRECT(__ATTR_WUNUSED __ATTR_INOUT(1),struct spwd *,__NOTHROW_RPC,__localdep_fgetspent,(__FILE *__restrict __stream),fgetspent,(__stream))
#endif /* !__local___localdep_fgetspent_defined */
#ifndef __local___localdep_fmemopen_defined
#define __local___localdep_fmemopen_defined
#ifdef __CRT_HAVE_fmemopen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_WUNUSED __ATTR_IN(3) __ATTR_INOUTS(1, 2),__FILE *,__NOTHROW_NCX,__localdep_fmemopen,(void *__mem, __SIZE_TYPE__ __len, char const *__modes),fmemopen,(__mem,__len,__modes))
#elif (defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)) && ((defined(__CRT_HAVE_funopen2) && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || defined(__CRT_HAVE_funopen2_64) || defined(__CRT_HAVE_funopen2))
__NAMESPACE_LOCAL_END
#include <libc/local/stdio/fmemopen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fmemopen __LIBC_LOCAL_NAME(fmemopen)
#else /* ... */
#undef __local___localdep_fmemopen_defined
#endif /* !... */
#endif /* !__local___localdep_fmemopen_defined */
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
__LOCAL_LIBC(sgetspent) __ATTR_WUNUSED __ATTR_IN(1) struct spwd *
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sgetspent))(char const *__restrict __string) {
	struct spwd *__result = __NULLPTR;
	__FILE *__fp = (__NAMESPACE_LOCAL_SYM __localdep_fmemopen)((void *)__string, (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__string), "rb");
	if __likely(__fp) {
		__result = (__NAMESPACE_LOCAL_SYM __localdep_fgetspent)(__fp);
#if defined(__CRT_HAVE_fclose) || defined(__CRT_HAVE__fclose_nolock) || defined(__CRT_HAVE__IO_fclose)
		(__NAMESPACE_LOCAL_SYM __localdep_fclose)(__fp);
#endif /* __CRT_HAVE_fclose || __CRT_HAVE__fclose_nolock || __CRT_HAVE__IO_fclose */
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sgetspent_defined
#define __local___localdep_sgetspent_defined
#define __localdep_sgetspent __LIBC_LOCAL_NAME(sgetspent)
#endif /* !__local___localdep_sgetspent_defined */
#else /* __CRT_HAVE_fgetspent && (__CRT_HAVE_fmemopen || ((__CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign) && ((__CRT_HAVE_funopen2 && __SIZEOF_OFF64_T__ == __SIZEOF_OFF32_T__) || __CRT_HAVE_funopen2_64 || __CRT_HAVE_funopen2))) */
#undef __local_sgetspent_defined
#endif /* !__CRT_HAVE_fgetspent || (!__CRT_HAVE_fmemopen && ((!__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign) || (!__CRT_HAVE_funopen2_64 && !__CRT_HAVE_funopen2))) */
#endif /* !__local_sgetspent_defined */
