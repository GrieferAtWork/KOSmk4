/* HASH CRC-32:0x113eefe4 */
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
#ifndef __local_strnrev_defined
#define __local_strnrev_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: memrev from string */
#ifndef __local___localdep_memrev_defined
#define __local___localdep_memrev_defined 1
#ifdef __CRT_HAVE_memrev
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memrev,(void *__restrict __base, __SIZE_TYPE__ __n_bytes),memrev,(__base,__n_bytes))
#else /* __CRT_HAVE_memrev */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memrev.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memrev __LIBC_LOCAL_NAME(memrev)
#endif /* !__CRT_HAVE_memrev */
#endif /* !__local___localdep_memrev_defined */
/* Dependency: strnlen from string */
#ifndef __local___localdep_strnlen_defined
#define __local___localdep_strnlen_defined 1
#if __has_builtin(__builtin_strnlen) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CEIREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,{ return __builtin_strnlen(__string, __maxlen); })
#elif defined(__CRT_HAVE_strnlen)
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strnlen,(char const *__restrict __string, __SIZE_TYPE__ __maxlen),strnlen,(__string,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnlen.h>
__NAMESPACE_LOCAL_BEGIN
/* >> strnlen(3)
 * Same as `strlen', but don't exceed `MAX_CHARS' characters (Same as `memlen[...](STR, '\0', MAX_CHARS)´) */
#define __localdep_strnlen __LIBC_LOCAL_NAME(strnlen)
#endif /* !... */
#endif /* !__local___localdep_strnlen_defined */
__LOCAL_LIBC(strnrev) __ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strnrev))(char *__restrict __str, __SIZE_TYPE__ __maxlen) {
	return (char *)__localdep_memrev(__str, __localdep_strnlen(__str, __maxlen));
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strnrev_defined
#define __local___localdep_strnrev_defined 1
#define __localdep_strnrev __LIBC_LOCAL_NAME(strnrev)
#endif /* !__local___localdep_strnrev_defined */
#endif /* !__local_strnrev_defined */
