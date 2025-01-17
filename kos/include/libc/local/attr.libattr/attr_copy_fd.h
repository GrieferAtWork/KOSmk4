/* HASH CRC-32:0x1dd6cb6a */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_attr_copy_fd_defined
#define __local_attr_copy_fd_defined
#include <__crt.h>
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && defined(__CRT_HAVE_llistxattr) && defined(__CRT_HAVE_flistxattr) && defined(__CRT_HAVE_lgetxattr) && defined(__CRT_HAVE_fgetxattr) && defined(__CRT_HAVE_lsetxattr) && defined(__CRT_HAVE_fsetxattr) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <attr/error_context.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_attr_copy_impl_defined
#define __local___localdep_attr_copy_impl_defined
__NAMESPACE_LOCAL_END
#include <libc/local/attr.libattr/attr_copy_impl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_attr_copy_impl __LIBC_LOCAL_NAME(attr_copy_impl)
#endif /* !__local___localdep_attr_copy_impl_defined */
__LOCAL_LIBC(attr_copy_fd) __ATTR_INOUT_OPT(6) __ATTR_IN_OPT(1) __ATTR_IN_OPT(3) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(attr_copy_fd))(char const *__src_path, __fd_t __src_fd, char const *__dst_path, __fd_t __dst_fd, int (__LIBKCALL *__check)(char const *__attr_name, struct error_context *__ctx), struct error_context *__ctx) {
	return (__NAMESPACE_LOCAL_SYM __localdep_attr_copy_impl)(__src_path, __src_fd, __dst_path, __dst_fd, __check, __ctx);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_attr_copy_fd_defined
#define __local___localdep_attr_copy_fd_defined
#define __localdep_attr_copy_fd __LIBC_LOCAL_NAME(attr_copy_fd)
#endif /* !__local___localdep_attr_copy_fd_defined */
#else /* !__NO_MALLOCA && __CRT_HAVE_llistxattr && __CRT_HAVE_flistxattr && __CRT_HAVE_lgetxattr && __CRT_HAVE_fgetxattr && __CRT_HAVE_lsetxattr && __CRT_HAVE_fsetxattr && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_attr_copy_fd_defined
#endif /* __NO_MALLOCA || !__CRT_HAVE_llistxattr || !__CRT_HAVE_flistxattr || !__CRT_HAVE_lgetxattr || !__CRT_HAVE_fgetxattr || !__CRT_HAVE_lsetxattr || !__CRT_HAVE_fsetxattr || (!__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_attr_copy_fd_defined */
