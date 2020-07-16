/* HASH CRC-32:0x8a264c2a */
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
#ifndef __local_spawnvpe_defined
#define __local_spawnvpe_defined 1
#include <__crt.h>
#include <hybrid/__alloca.h>
#include <local/environ.h>
#if (defined(__CRT_HAVE_getenv) || defined(__LOCAL_environ)) && (defined(__CRT_HAVE_spawnve) || defined(__CRT_HAVE__spawnve)) && defined(__hybrid_alloca)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: getenv from stdlib */
#ifndef __local___localdep_getenv_defined
#define __local___localdep_getenv_defined 1
#ifdef __CRT_HAVE_getenv
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_getenv,(char const *__varname),getenv,(__varname))
#elif defined(__LOCAL_environ)
__NAMESPACE_LOCAL_END
#include <local/stdlib/getenv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_getenv __LIBC_LOCAL_NAME(getenv)
#else /* ... */
#undef __local___localdep_getenv_defined
#endif /* !... */
#endif /* !__local___localdep_getenv_defined */
/* Dependency: strchrnul from string */
#ifndef __local___localdep_strchrnul_defined
#define __local___localdep_strchrnul_defined 1
#ifdef __CRT_HAVE_strchrnul
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strchrnul,(char const *__restrict __haystack, int __needle),strchrnul,(__haystack,__needle))
#else /* __CRT_HAVE_strchrnul */
__NAMESPACE_LOCAL_END
#include <local/string/strchrnul.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `strchr', but return `strend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_strchrnul __LIBC_LOCAL_NAME(strchrnul)
#endif /* !__CRT_HAVE_strchrnul */
#endif /* !__local___localdep_strchrnul_defined */
/* Dependency: strlen from string */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined 1
#ifdef __CRT_HAVE_strlen
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __string),strlen,(__string))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
/* Return the length of the string in characters (Same as `rawmemlen[...](STR, '\0')') */
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <parts/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(__spawnvpe_impl) __ATTR_NOINLINE __ATTR_NONNULL((2, 4, 6, 7)) __pid_t
(__LIBCCALL __spawnvpe_impl)(int __mode,
                             char const *__restrict __path, __SIZE_TYPE__ __path_len,
                             char const *__restrict __file, __SIZE_TYPE__ __file_len,
                             __TARGV, __TENVP) {
	char *__fullpath, *__dst;
#ifdef _WIN32
	while (__path_len && (__path[__path_len - 1] == '/' ||
	                    __path[__path_len - 1] == '\\'))
		--__path_len;
#else /* _WIN32 */
	while (__path_len && __path[__path_len - 1] == '/')
		--__path_len;
#endif /* !_WIN32 */
	__fullpath = (char *)__hybrid_alloca((__path_len + 1 + __file_len + 1) *
	                                   sizeof(char));
	__dst = (char *)__mempcpyc(__fullpath, __path, __path_len, sizeof(char));
	*__dst++ = '/';
	__dst = (char *)__mempcpyc(__dst, __file, __file_len, sizeof(char));
	*__dst = '\0';
	return __spawnve(__mode, __fullpath, ___argv, ___envp);
}
__NAMESPACE_LOCAL_END
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(spawnvpe) __ATTR_NONNULL((2, 3, 4)) __pid_t
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(spawnvpe))(int __mode, char const *__restrict __file, __TARGV, __TENVP) {
	__SIZE_TYPE__ __filelen = __localdep_strlen(__file);
	char *__env_path = __localdep_getenv("PATH");
	if (__env_path && *__env_path) {
		for (;;) {
			__pid_t __result;
			char *__path_end;
#ifdef _WIN32
			__path_end = __localdep_strchrnul(__env_path, ';');
#else /* _WIN32 */
			__path_end = __localdep_strchrnul(__env_path, ':');
#endif /* !_WIN32 */
			__result = (__NAMESPACE_LOCAL_SYM __spawnvpe_impl)(__mode, __env_path, (__SIZE_TYPE__)(__path_end - __env_path),
			                                                 __file, __filelen, ___argv, ___envp);
			if (__result >= 0)
				return __result;
			if (!*__path_end)
				break;
			__env_path = __path_end + 1;
		}
	} else {
#ifdef __ENOENT
		__libc_seterrno(__ENOENT);
#endif /* __ENOENT */
	}
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_spawnvpe_defined
#define __local___localdep_spawnvpe_defined 1
#define __localdep_spawnvpe __LIBC_LOCAL_NAME(spawnvpe)
#endif /* !__local___localdep_spawnvpe_defined */
#else /* (__CRT_HAVE_getenv || __LOCAL_environ) && (__CRT_HAVE_spawnve || __CRT_HAVE__spawnve) && __hybrid_alloca */
#undef __local_spawnvpe_defined
#endif /* (!__CRT_HAVE_getenv && !__LOCAL_environ) || (!__CRT_HAVE_spawnve && !__CRT_HAVE__spawnve) || !__hybrid_alloca */
#endif /* !__local_spawnvpe_defined */
