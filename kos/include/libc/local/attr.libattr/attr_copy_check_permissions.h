/* HASH CRC-32:0xd21717bf */
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
#ifndef __local_attr_copy_check_permissions_defined
#define __local_attr_copy_check_permissions_defined
#include <__crt.h>
#include <attr/error_context.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_attr_copy_action_defined
#define __local___localdep_attr_copy_action_defined
#ifdef __CRT_HAVE_attr_copy_action
__CREDIRECT(__ATTR_IN(1) __ATTR_INOUT_OPT(2),int,__NOTHROW_NCX,__localdep_attr_copy_action,(char const *__attr_name, struct error_context *__ctx),attr_copy_action,(__attr_name,__ctx))
#else /* __CRT_HAVE_attr_copy_action */
__NAMESPACE_LOCAL_END
#include <libc/local/attr.libattr/attr_copy_action.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_attr_copy_action __LIBC_LOCAL_NAME(attr_copy_action)
#endif /* !__CRT_HAVE_attr_copy_action */
#endif /* !__local___localdep_attr_copy_action_defined */
__LOCAL_LIBC(attr_copy_check_permissions) __ATTR_IN(1) __ATTR_INOUT_OPT(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(attr_copy_check_permissions))(char const *__attr_name, struct error_context *__ctx) {
	return (__NAMESPACE_LOCAL_SYM __localdep_attr_copy_action)(__attr_name, __ctx) == 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_attr_copy_check_permissions_defined
#define __local___localdep_attr_copy_check_permissions_defined
#define __localdep_attr_copy_check_permissions __LIBC_LOCAL_NAME(attr_copy_check_permissions)
#endif /* !__local___localdep_attr_copy_check_permissions_defined */
#endif /* !__local_attr_copy_check_permissions_defined */
