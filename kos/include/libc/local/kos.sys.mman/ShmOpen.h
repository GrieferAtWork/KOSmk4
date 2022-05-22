/* HASH CRC-32:0x2a2dbd04 */
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
#ifndef __local_ShmOpen_defined
#define __local_ShmOpen_defined
#include <__crt.h>
#include <features.h>
#include <asm/os/oflags.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Open64) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_OpenAt64) || defined(__CRT_HAVE_OpenAt))) || defined(__CRT_HAVE_Open)
#include <kos/anno.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep_Mkdir_defined) && defined(__CRT_HAVE_Mkdir)
#define __local___localdep_Mkdir_defined
__CREDIRECT_VOID(__ATTR_ACCESS_RO(1),__THROWING,__localdep_Mkdir,(char const *__pathname, __mode_t __mode),Mkdir,(__pathname,__mode))
#endif /* !__local___localdep_Mkdir_defined && __CRT_HAVE_Mkdir */
#ifndef __local___localdep_Open_defined
#define __local___localdep_Open_defined
#if defined(__CRT_HAVE_Open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__THROWING,__localdep_Open,(char const *__filename, __oflag_t __oflags),Open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_Open64) && (defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_ACCESS_RO(1),__fd_t,__THROWING,__localdep_Open,(char const *__filename, __oflag_t __oflags),Open64,(__filename,__oflags),__oflags,1,(__mode_t))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.fcntl/Open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_Open __LIBC_LOCAL_NAME(Open)
#endif /* !... */
#endif /* !__local___localdep_Open_defined */
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
#ifndef __local___localdep_mempcpy_defined
#define __local___localdep_mempcpy_defined
#ifdef __CRT_HAVE_mempcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_ACCESS_ROS(2, 3) __ATTR_ACCESS_WRS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpy __LIBC_LOCAL_NAME(mempcpy)
#endif /* !... */
#endif /* !__local___localdep_mempcpy_defined */
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/paths.h>
#include <kos/parts/malloca.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ShmOpen) __ATTR_ACCESS_RO(1) __fd_t
(__LIBCCALL __LIBC_LOCAL_NAME(ShmOpen))(char const *__name, __oflag_t __oflags, __mode_t __mode) __THROWS(...) {
	__fd_t __result;
	char *__fullname;
	__SIZE_TYPE__ __namelen;
#ifdef __O_DOSPATH
	if (__oflags & __O_DOSPATH) {
		while (*__name == '/' || *__name == '\\')
			++__name;
	} else {
		while (*__name == '/')
			++__name;
	}
#elif defined(_WIN32)
	while (*__name == '/' || *__name == '\\')
		++__name;
#else /* ... */
	while (*__name == '/')
		++__name;
#endif /* !... */
	__namelen  = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__name);
	__fullname = (char *)__Malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              __namelen + 1) *
	                             sizeof(char));
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)((__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       __fullname,
	       (__namelen + 1) *
	       sizeof(char));
	__result = (__NAMESPACE_LOCAL_SYM __localdep_Open)(__fullname, __oflags, __mode);
#if defined(__ENOENT) && defined(__O_CREAT) && defined(__CRT_HAVE_Mkdir)
	if (__result < 0 && (__oflags & __O_CREAT) != 0 && __libc_geterrno_or(__ENOENT) == __ENOENT) {
		/* Lazily create the SHM directory (/dev/shm), if it hadn't been created already.
		 * XXX:   This    assumes    that    `headof(__PATH_SHM)'    already    exists... */
		(__NAMESPACE_LOCAL_SYM __localdep_Mkdir)(__PATH_SHM, 0777);
		__result = (__NAMESPACE_LOCAL_SYM __localdep_Open)(__fullname, __oflags, __mode);
	}
#endif /* __ENOENT && __O_CREAT && __CRT_HAVE_Mkdir */
	__freea(__fullname);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ShmOpen_defined
#define __local___localdep_ShmOpen_defined
#define __localdep_ShmOpen __LIBC_LOCAL_NAME(ShmOpen)
#endif /* !__local___localdep_ShmOpen_defined */
#else /* __CRT_HAVE_Open64 || (__AT_FDCWD && (__CRT_HAVE_OpenAt64 || __CRT_HAVE_OpenAt)) || __CRT_HAVE_Open */
#undef __local_ShmOpen_defined
#endif /* !__CRT_HAVE_Open64 && (!__AT_FDCWD || (!__CRT_HAVE_OpenAt64 && !__CRT_HAVE_OpenAt)) && !__CRT_HAVE_Open */
#endif /* !__local_ShmOpen_defined */
