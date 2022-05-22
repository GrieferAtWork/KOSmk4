/* HASH CRC-32:0x11123406 */
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
#ifndef __local_concat_length_defined
#define __local_concat_length_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_strlen_defined
#define __local___localdep_strlen_defined
#ifdef __CRT_HAVE_strlen
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_strlen,(char const *__restrict __str),strlen,(__str))
#else /* __CRT_HAVE_strlen */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strlen.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strlen __LIBC_LOCAL_NAME(strlen)
#endif /* !__CRT_HAVE_strlen */
#endif /* !__local___localdep_strlen_defined */
__LOCAL_LIBC(concat_length) __ATTR_ACCESS_RO_OPT(1) __ULONGPTR_TYPE__
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(concat_length))(char const *__first, ...) {
	__builtin_va_list __args;
	__SIZE_TYPE__ __totlen = 0;
	__builtin_va_start(__args, __first);
	for (; __first; __first = __builtin_va_arg(__args, char *))
		__totlen += (__NAMESPACE_LOCAL_SYM __localdep_strlen)(__first);
	__builtin_va_end(__args);
	return (__ULONGPTR_TYPE__)__totlen;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_concat_length_defined
#define __local___localdep_concat_length_defined
#define __localdep_concat_length __LIBC_LOCAL_NAME(concat_length)
#endif /* !__local___localdep_concat_length_defined */
#endif /* !__local_concat_length_defined */
