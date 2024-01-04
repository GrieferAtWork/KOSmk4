/* HASH CRC-32:0x66cf1c39 */
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
#ifndef __local_shm_unlink_defined
#define __local_shm_unlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || defined(__CRT_HAVE___unlink) || defined(__CRT_HAVE___libc_unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
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
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),mempcpy,(__dst,__src,__n_bytes))
#elif defined(__CRT_HAVE___mempcpy)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_mempcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),__mempcpy,(__dst,__src,__n_bytes))
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
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
#ifndef __local___localdep_unlink_defined
#define __local___localdep_unlink_defined
#ifdef __CRT_HAVE_unlink
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),unlink,(__file))
#elif defined(__CRT_HAVE__unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),_unlink,(__file))
#elif defined(__CRT_HAVE___unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__unlink,(__file))
#elif defined(__CRT_HAVE___libc_unlink)
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_unlink,(char const *__file),__libc_unlink,(__file))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/unlink.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_unlink __LIBC_LOCAL_NAME(unlink)
#else /* ... */
#undef __local___localdep_unlink_defined
#endif /* !... */
#endif /* !__local___localdep_unlink_defined */
__NAMESPACE_LOCAL_END
#include <asm/os/paths.h>
#include <hybrid/typecore.h>
#include <parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(shm_unlink) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(shm_unlink))(char const *__name) {
	int __result;
	char *__fullname;
	__SIZE_TYPE__ __namelen;
#ifdef _WIN32
	while (*__name == '/' || *__name == '\\')
		++__name;
#else /* _WIN32 */
	while (*__name == '/')
		++__name;
#endif /* !_WIN32 */
	__namelen  = (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__name);
	__fullname = (char *)__malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              __namelen + 1) *
	                             sizeof(char));
	if __unlikely(!__fullname)
		return -1;
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)((__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       __fullname,
	       (__namelen + 1) *
	       sizeof(char));
	__result = (__NAMESPACE_LOCAL_SYM __localdep_unlink)(__fullname);
	__freea(__fullname);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_shm_unlink_defined
#define __local___localdep_shm_unlink_defined
#define __localdep_shm_unlink __LIBC_LOCAL_NAME(shm_unlink)
#endif /* !__local___localdep_shm_unlink_defined */
#else /* __CRT_HAVE_unlink || __CRT_HAVE__unlink || __CRT_HAVE___unlink || __CRT_HAVE___libc_unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat) */
#undef __local_shm_unlink_defined
#endif /* !__CRT_HAVE_unlink && !__CRT_HAVE__unlink && !__CRT_HAVE___unlink && !__CRT_HAVE___libc_unlink && (!__AT_FDCWD || !__CRT_HAVE_unlinkat) */
#endif /* !__local_shm_unlink_defined */
