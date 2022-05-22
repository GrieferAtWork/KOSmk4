/* HASH CRC-32:0x2659ad69 */
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
#ifndef __local_sigemptyset_defined
#define __local_sigemptyset_defined
#include <__crt.h>
#include <bits/os/sigset.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bzeroc_defined
#define __local___localdep_bzeroc_defined
#ifdef __CRT_HAVE_bzeroc
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_VOID(__ATTR_LEAF __ATTR_OUT(1),__NOTHROW_NCX,__localdep_bzeroc,(void *__restrict __dst, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bzeroc,(__dst,__elem_count,__elem_size))
#else /* __CRT_HAVE_bzeroc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/bzeroc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bzeroc __LIBC_LOCAL_NAME(bzeroc)
#endif /* !__CRT_HAVE_bzeroc */
#endif /* !__local___localdep_bzeroc_defined */
__LOCAL_LIBC(sigemptyset) __ATTR_OUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigemptyset))(struct __sigset_struct *__set) {
	(__NAMESPACE_LOCAL_SYM __localdep_bzeroc)(__set->__val, __COMPILER_LENOF(__set->__val), __SIZEOF_POINTER__);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sigemptyset_defined
#define __local___localdep_sigemptyset_defined
#define __localdep_sigemptyset __LIBC_LOCAL_NAME(sigemptyset)
#endif /* !__local___localdep_sigemptyset_defined */
#endif /* !__local_sigemptyset_defined */
