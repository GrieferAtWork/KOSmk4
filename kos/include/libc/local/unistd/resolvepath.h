/* HASH CRC-32:0xe302483c */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_resolvepath_defined
#define __local_resolvepath_defined 1
#include <__crt.h>
#include <asm/fcntl.h>
#if defined(__CRT_HAVE_frealpathat) && defined(__AT_FDCWD)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: frealpathat from stdlib */
#ifndef __local___localdep_frealpathat_defined
#define __local___localdep_frealpathat_defined 1
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Returns the absolute filesystem path for the specified file
 * When `AT_SYMLINK_NOFOLLOW' is given, a final symlink is not dereferenced,
 * causing the path to the symlink itself to be printed. - Otherwise, the
 * filed pointed to by the symblic link is printed.
 * NOTE: You may use `AT_ALTPATH' to cause the path to be printed in alternate
 *       representation mode. This means that if the path would have normally
 *       been printed as a unix path, it would instead be printed as a DOS path.
 *       Similarly, the reverse also applies.
 * NOTE: You may also pass `NULL' for `resolved' to have a buffer of `buflen'
 *       bytes automatically allocated in the heap, ontop of which you may also
 *       pass `0' for `buflen' to automatically determine the required buffer size.
 * @param flags: Set of `0 | AT_ALTPATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH'
 * @return: NULL: [errno=ERANGE]: `buflen' is too small to fit the entire path */
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),char *,__NOTHROW_RPC,__localdep_frealpathat,(__fd_t __dirfd, char const *__filename, char *__resolved, __SIZE_TYPE__ __buflen, __atflag_t __flags),frealpathat,(__dirfd,__filename,__resolved,__buflen,__flags))
#endif /* !__local___localdep_frealpathat_defined */
/* Dependency: free from stdlib */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined 1
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ return __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
/* Similar to `frealpathat(2)' (though use the later for more options)
 * Also note that this function appears to have a weird rule (which KOS simply
 * ignores) that is related to this function not writing more than `PATH_MAX'
 * bytes to `buf'. (Why??? I mean: The whole point of having a `buflen' argument
 * is to be able to handle names of arbitrary lengths)
 * Additionally, the online docs don't mention what happens when `buflen' is too
 * small, so I guess I can just make up what's supposed to happen, and I say that
 * the function will set errno=ERANGE and return -1
 * @return: * : Used buffer size (possibly including a NUL-byte, but maybe not)
 * @return: -1: Error. (s.a. `errno') */
__LOCAL_LIBC(resolvepath) __ATTR_NONNULL((1)) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(resolvepath))(char const *__filename, char *__resolved, __SIZE_TYPE__ __buflen) {
	__STDC_INT_AS_SSIZE_T __retval;
	char *__result;
	__result = __localdep_frealpathat(__AT_FDCWD, __filename, __resolved, __buflen, 0);
	if __unlikely(!__result)
		return -1;
	__retval = (__STDC_INT_AS_SSIZE_T)__localdep_strlen(__result);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree)
	if __unlikely(!__resolved)
		__localdep_free(__result);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree */
	return __retval;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_resolvepath_defined
#define __local___localdep_resolvepath_defined 1
#define __localdep_resolvepath __LIBC_LOCAL_NAME(resolvepath)
#endif /* !__local___localdep_resolvepath_defined */
#else /* __CRT_HAVE_frealpathat && __AT_FDCWD */
#undef __local_resolvepath_defined
#endif /* !__CRT_HAVE_frealpathat || !__AT_FDCWD */
#endif /* !__local_resolvepath_defined */
