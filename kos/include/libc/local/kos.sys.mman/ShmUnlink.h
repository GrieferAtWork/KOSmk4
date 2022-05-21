/* HASH CRC-32:0x2fe0b1cd */
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
#ifndef __local_ShmUnlink_defined
#define __local_ShmUnlink_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_Unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt))
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_Unlink_defined
#define __local___localdep_Unlink_defined
#ifdef __CRT_HAVE_Unlink
__CREDIRECT_VOID(__ATTR_NONNULL((1)),__THROWING,__localdep_Unlink,(char const *__file),Unlink,(__file))
#elif defined(__AT_FDCWD) && defined(__CRT_HAVE_UnlinkAt)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.unistd/Unlink.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_Unlink __LIBC_LOCAL_NAME(Unlink)
#else /* ... */
#undef __local___localdep_Unlink_defined
#endif /* !... */
#endif /* !__local___localdep_Unlink_defined */
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
#include <hybrid/typecore.h>
#include <kos/parts/malloca.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(ShmUnlink) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(ShmUnlink))(char const *__name) __THROWS(...) {
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
	__fullname = (char *)__Malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              __namelen + 1) *
	                             sizeof(char));
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)((__NAMESPACE_LOCAL_SYM __localdep_mempcpy)(__fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       __fullname,
	       (__namelen + 1) *
	       sizeof(char));
	(__NAMESPACE_LOCAL_SYM __localdep_Unlink)(__fullname);
	__freea(__fullname);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_ShmUnlink_defined
#define __local___localdep_ShmUnlink_defined
#define __localdep_ShmUnlink __LIBC_LOCAL_NAME(ShmUnlink)
#endif /* !__local___localdep_ShmUnlink_defined */
#else /* __CRT_HAVE_Unlink || (__AT_FDCWD && __CRT_HAVE_UnlinkAt) */
#undef __local_ShmUnlink_defined
#endif /* !__CRT_HAVE_Unlink && (!__AT_FDCWD || !__CRT_HAVE_UnlinkAt) */
#endif /* !__local_ShmUnlink_defined */
