/* HASH CRC-32:0x98e9e615 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__CrtIsValidPointer_defined
#define __local__CrtIsValidPointer_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_CrtIsValidPointer) __ATTR_PURE __ATTR_WUNUSED int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_CrtIsValidPointer))(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, int __writable) {
	__COMPILER_IMPURE();
	(void)__num_bytes;
	(void)__writable;
	return __ptr != __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__CrtIsValidPointer_defined
#define __local___localdep__CrtIsValidPointer_defined 1
#define __localdep__CrtIsValidPointer __LIBC_LOCAL_NAME(_CrtIsValidPointer)
#endif /* !__local___localdep__CrtIsValidPointer_defined */
#endif /* !__local__CrtIsValidPointer_defined */
