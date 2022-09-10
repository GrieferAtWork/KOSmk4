/* HASH CRC-32:0xc4289250 */
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
/* (#) Portability: libattr (/include/libattr.h) */
#ifndef _ATTR_LIBATTR_H
#define _ATTR_LIBATTR_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <bits/types.h>
#include <attr/asm/libattr.h>

/* Return values  of `attr_copy_action'  (and the  `check'
 * cb passed to `attr_copy_file(3)' and `attr_copy_fd(3)') */
#if !defined(ATTR_ACTION_SKIP) && defined(__ATTR_ACTION_SKIP)
#define ATTR_ACTION_SKIP __ATTR_ACTION_SKIP
#endif /* !ATTR_ACTION_SKIP && __ATTR_ACTION_SKIP */
#if !defined(ATTR_ACTION_PERMISSIONS) && defined(__ATTR_ACTION_PERMISSIONS)
#define ATTR_ACTION_PERMISSIONS __ATTR_ACTION_PERMISSIONS
#endif /* !ATTR_ACTION_PERMISSIONS && __ATTR_ACTION_PERMISSIONS */


#ifdef __CC__
__SYSDECL_BEGIN

struct error_context;

#ifdef __CRT_HAVE_attr_copy_file
/* >> attr_copy_file(3)
 * Copy attributes from `src_path' to `dst_path'. Only attributes for which `check()'
 * returns  non-zero (if  not given,  `attr_copy_check_permissions' is  used) will be
 * copied.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT_OPT(4),int,__NOTHROW_NCX,attr_copy_file,(char const *__src_path, char const *__dst_path, int (__LIBKCALL *__check)(char const *__attr_name, struct error_context *__ctx), struct error_context *__ctx),(__src_path,__dst_path,__check,__ctx))
#else /* __CRT_HAVE_attr_copy_file */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && defined(__CRT_HAVE_llistxattr) && defined(__CRT_HAVE_flistxattr) && defined(__CRT_HAVE_lgetxattr) && defined(__CRT_HAVE_fgetxattr) && defined(__CRT_HAVE_lsetxattr) && defined(__CRT_HAVE_fsetxattr) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/attr.libattr/attr_copy_file.h>
/* >> attr_copy_file(3)
 * Copy attributes from `src_path' to `dst_path'. Only attributes for which `check()'
 * returns  non-zero (if  not given,  `attr_copy_check_permissions' is  used) will be
 * copied.
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
__NAMESPACE_LOCAL_USING_OR_IMPL(attr_copy_file, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_IN(2) __ATTR_INOUT_OPT(4) int __NOTHROW_NCX(__LIBCCALL attr_copy_file)(char const *__src_path, char const *__dst_path, int (__LIBKCALL *__check)(char const *__attr_name, struct error_context *__ctx), struct error_context *__ctx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(attr_copy_file))(__src_path, __dst_path, __check, __ctx); })
#endif /* !__NO_MALLOCA && __CRT_HAVE_llistxattr && __CRT_HAVE_flistxattr && __CRT_HAVE_lgetxattr && __CRT_HAVE_fgetxattr && __CRT_HAVE_lsetxattr && __CRT_HAVE_fsetxattr && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#endif /* !__CRT_HAVE_attr_copy_file */
#ifdef __CRT_HAVE_attr_copy_fd
/* >> attr_copy_fd(3)
 * Copy attributes from `src_fd' to `dst_fd'. Only attributes for which `check()'
 * returns non-zero (if not given, `attr_copy_check_permissions' is used) will be
 * copied.
 * @param: src_path: The name of `src_fd' (only used for error messages)
 * @param: dst_path: The name of `dst_fd' (only used for error messages)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
__CDECLARE(__ATTR_INOUT_OPT(6) __ATTR_IN_OPT(1) __ATTR_IN_OPT(3),int,__NOTHROW_NCX,attr_copy_fd,(char const *__src_path, __fd_t __src_fd, char const *__dst_path, __fd_t __dst_fd, int (__LIBKCALL *__check)(char const *__attr_name, struct error_context *__ctx), struct error_context *__ctx),(__src_path,__src_fd,__dst_path,__dst_fd,__check,__ctx))
#else /* __CRT_HAVE_attr_copy_fd */
#include <parts/malloca.h>
#if !defined(__NO_MALLOCA) && defined(__CRT_HAVE_llistxattr) && defined(__CRT_HAVE_flistxattr) && defined(__CRT_HAVE_lgetxattr) && defined(__CRT_HAVE_fgetxattr) && defined(__CRT_HAVE_lsetxattr) && defined(__CRT_HAVE_fsetxattr) && (defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <libc/local/attr.libattr/attr_copy_fd.h>
/* >> attr_copy_fd(3)
 * Copy attributes from `src_fd' to `dst_fd'. Only attributes for which `check()'
 * returns non-zero (if not given, `attr_copy_check_permissions' is used) will be
 * copied.
 * @param: src_path: The name of `src_fd' (only used for error messages)
 * @param: dst_path: The name of `dst_fd' (only used for error messages)
 * @return: 0 : Success
 * @return: -1: Error (s.a. `errno' and `ctx') */
__NAMESPACE_LOCAL_USING_OR_IMPL(attr_copy_fd, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_INOUT_OPT(6) __ATTR_IN_OPT(1) __ATTR_IN_OPT(3) int __NOTHROW_NCX(__LIBCCALL attr_copy_fd)(char const *__src_path, __fd_t __src_fd, char const *__dst_path, __fd_t __dst_fd, int (__LIBKCALL *__check)(char const *__attr_name, struct error_context *__ctx), struct error_context *__ctx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(attr_copy_fd))(__src_path, __src_fd, __dst_path, __dst_fd, __check, __ctx); })
#endif /* !__NO_MALLOCA && __CRT_HAVE_llistxattr && __CRT_HAVE_flistxattr && __CRT_HAVE_lgetxattr && __CRT_HAVE_fgetxattr && __CRT_HAVE_lsetxattr && __CRT_HAVE_fsetxattr && (__CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#endif /* !__CRT_HAVE_attr_copy_fd */
#ifdef __CRT_HAVE_attr_copy_check_permissions
/* >> attr_copy_check_permissions(3)
 * Returns non-zero if `attr_name' should be preserved (default handler
 * for `check' argument  of `attr_copy_file(3)' and  `attr_copy_fd(3)')
 * Same as `attr_copy_action(attr_name, ctx) == 0'
 * @return: == 0 : `attr_name' should not be copied
 * @return: != 0 : `attr_name' should be copied */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT_OPT(2),int,__NOTHROW_NCX,attr_copy_check_permissions,(char const *__attr_name, struct error_context *__ctx),(__attr_name,__ctx))
#else /* __CRT_HAVE_attr_copy_check_permissions */
#include <libc/local/attr.libattr/attr_copy_check_permissions.h>
/* >> attr_copy_check_permissions(3)
 * Returns non-zero if `attr_name' should be preserved (default handler
 * for `check' argument  of `attr_copy_file(3)' and  `attr_copy_fd(3)')
 * Same as `attr_copy_action(attr_name, ctx) == 0'
 * @return: == 0 : `attr_name' should not be copied
 * @return: != 0 : `attr_name' should be copied */
__NAMESPACE_LOCAL_USING_OR_IMPL(attr_copy_check_permissions, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT_OPT(2) int __NOTHROW_NCX(__LIBCCALL attr_copy_check_permissions)(char const *__attr_name, struct error_context *__ctx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(attr_copy_check_permissions))(__attr_name, __ctx); })
#endif /* !__CRT_HAVE_attr_copy_check_permissions */
#ifdef __CRT_HAVE_attr_copy_action
/* >> attr_copy_action(3)
 * Return the default action to-be taken for `attr_name'
 * @return: 0 : No special action
 * @return: * : One of `ATTR_ACTION_*' */
__CDECLARE(__ATTR_IN(1) __ATTR_INOUT_OPT(2),int,__NOTHROW_NCX,attr_copy_action,(char const *__attr_name, struct error_context *__ctx),(__attr_name,__ctx))
#else /* __CRT_HAVE_attr_copy_action */
#include <libc/local/attr.libattr/attr_copy_action.h>
/* >> attr_copy_action(3)
 * Return the default action to-be taken for `attr_name'
 * @return: 0 : No special action
 * @return: * : One of `ATTR_ACTION_*' */
__NAMESPACE_LOCAL_USING_OR_IMPL(attr_copy_action, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_INOUT_OPT(2) int __NOTHROW_NCX(__LIBCCALL attr_copy_action)(char const *__attr_name, struct error_context *__ctx) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(attr_copy_action))(__attr_name, __ctx); })
#endif /* !__CRT_HAVE_attr_copy_action */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_ATTR_LIBATTR_H */
