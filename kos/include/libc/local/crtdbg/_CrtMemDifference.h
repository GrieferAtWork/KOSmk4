/* HASH CRC-32:0x1a0c27b8 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__CrtMemDifference_defined
#define __local__CrtMemDifference_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memset_defined
#define __local___localdep_memset_defined
#ifdef __CRT_HAVE_memset
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1)),void *,__NOTHROW_NCX,__localdep_memset,(void *__restrict __dst, int __byte, __SIZE_TYPE__ __n_bytes),memset,(__dst,__byte,__n_bytes))
#else /* __CRT_HAVE_memset */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memset __LIBC_LOCAL_NAME(memset)
#endif /* !__CRT_HAVE_memset */
#endif /* !__local___localdep_memset_defined */
__LOCAL_LIBC(_CrtMemDifference) __ATTR_NONNULL((1, 2, 3)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_CrtMemDifference))(_CrtMemState *__state, _CrtMemState const *__old_state, _CrtMemState const *__new_state) {
	(void)__old_state;
	(void)__new_state;
	(__NAMESPACE_LOCAL_SYM __localdep_memset)(__state, 0, sizeof(*__state));
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__CrtMemDifference_defined
#define __local___localdep__CrtMemDifference_defined
#define __localdep__CrtMemDifference __LIBC_LOCAL_NAME(_CrtMemDifference)
#endif /* !__local___localdep__CrtMemDifference_defined */
#endif /* !__local__CrtMemDifference_defined */
