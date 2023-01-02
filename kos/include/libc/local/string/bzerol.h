/* HASH CRC-32:0x49ddfb9f */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_bzerol_defined
#define __local_bzerol_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memsetl_defined
#define __local___localdep_memsetl_defined
#ifdef __CRT_HAVE_memsetl
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),memsetl,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_wmemset) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT(__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__localdep_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),wmemset,(__dst,__dword,__n_dwords))
#elif defined(__CRT_HAVE_KOS$wmemset) && defined(__LIBCCALL_IS_LIBKCALL)
__COMPILER_CREDIRECT(__LIBC,__ATTR_LEAF __ATTR_OUT(1),__UINT32_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memsetl,(void *__restrict __dst, __UINT32_TYPE__ __dword, __SIZE_TYPE__ __n_dwords),KOS$wmemset,(__dst,__dword,__n_dwords))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memsetl.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memsetl __LIBC_LOCAL_NAME(memsetl)
#endif /* !... */
#endif /* !__local___localdep_memsetl_defined */
__LOCAL_LIBC(bzerol) __ATTR_LEAF __ATTR_OUT(1) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(bzerol))(void *__restrict __dst, __SIZE_TYPE__ __num_dwords) {
	(__NAMESPACE_LOCAL_SYM __localdep_memsetl)(__dst, 0, __num_dwords);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_bzerol_defined
#define __local___localdep_bzerol_defined
#define __localdep_bzerol __LIBC_LOCAL_NAME(bzerol)
#endif /* !__local___localdep_bzerol_defined */
#endif /* !__local_bzerol_defined */
