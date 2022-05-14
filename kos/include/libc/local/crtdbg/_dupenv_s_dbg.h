/* HASH CRC-32:0xc50bdf9b */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__dupenv_s_dbg_defined
#define __local__dupenv_s_dbg_defined
#include <__crt.h>
#include <libc/template/environ.h>
#if defined(__CRT_HAVE__dupenv_s) || ((defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign)))
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__dupenv_s_defined
#define __local___localdep__dupenv_s_defined
#ifdef __CRT_HAVE__dupenv_s
__CREDIRECT(__ATTR_NONNULL((1, 2, 3)),__errno_t,__NOTHROW_NCX,__localdep__dupenv_s,(char **__restrict __pbuf, __SIZE_TYPE__ *__pbuflen, char const *__varname),_dupenv_s,(__pbuf,__pbuflen,__varname))
#elif (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_strdup) || defined(__CRT_HAVE__strdup) || defined(__CRT_HAVE__mbsdup) || defined(__CRT_HAVE___strdup) || defined(__CRT_HAVE_malloc) || defined(__CRT_HAVE___libc_malloc) || defined(__CRT_HAVE_calloc) || defined(__CRT_HAVE___libc_calloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc) || defined(__CRT_HAVE_memalign) || defined(__CRT_HAVE_aligned_alloc) || defined(__CRT_HAVE___libc_memalign) || defined(__CRT_HAVE_posix_memalign))
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/_dupenv_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__dupenv_s __LIBC_LOCAL_NAME(_dupenv_s)
#else /* ... */
#undef __local___localdep__dupenv_s_defined
#endif /* !... */
#endif /* !__local___localdep__dupenv_s_defined */
__LOCAL_LIBC(_dupenv_s_dbg) _Check_return_wat_ __ATTR_NONNULL((3)) __errno_t
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_dupenv_s_dbg))(char **__pbuf, __SIZE_TYPE__ *__pbufsize, char const *__varname, int __block_type, char const *__filename, int __line) {
	(void)__block_type;
	(void)__filename;
	(void)__line;
	return (__NAMESPACE_LOCAL_SYM __localdep__dupenv_s)(__pbuf, __pbufsize, __varname);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__dupenv_s_dbg_defined
#define __local___localdep__dupenv_s_dbg_defined
#define __localdep__dupenv_s_dbg __LIBC_LOCAL_NAME(_dupenv_s_dbg)
#endif /* !__local___localdep__dupenv_s_dbg_defined */
#else /* __CRT_HAVE__dupenv_s || ((__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_strdup || __CRT_HAVE__strdup || __CRT_HAVE__mbsdup || __CRT_HAVE___strdup || __CRT_HAVE_malloc || __CRT_HAVE___libc_malloc || __CRT_HAVE_calloc || __CRT_HAVE___libc_calloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc || __CRT_HAVE_memalign || __CRT_HAVE_aligned_alloc || __CRT_HAVE___libc_memalign || __CRT_HAVE_posix_memalign)) */
#undef __local__dupenv_s_dbg_defined
#endif /* !__CRT_HAVE__dupenv_s && ((!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_strdup && !__CRT_HAVE__strdup && !__CRT_HAVE__mbsdup && !__CRT_HAVE___strdup && !__CRT_HAVE_malloc && !__CRT_HAVE___libc_malloc && !__CRT_HAVE_calloc && !__CRT_HAVE___libc_calloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc && !__CRT_HAVE_memalign && !__CRT_HAVE_aligned_alloc && !__CRT_HAVE___libc_memalign && !__CRT_HAVE_posix_memalign)) */
#endif /* !__local__dupenv_s_dbg_defined */
