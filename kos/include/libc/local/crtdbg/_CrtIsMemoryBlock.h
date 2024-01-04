/* HASH CRC-32:0xb414fc64 */
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
#ifndef __local__CrtIsMemoryBlock_defined
#define __local__CrtIsMemoryBlock_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_CrtIsMemoryBlock) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_CrtIsMemoryBlock))(void const *__ptr, __STDC_UINT_AS_SIZE_T __num_bytes, __LONG32_TYPE__ *__prequest_number, char **__filename, int *__line) {
	(void)__ptr;
	(void)__num_bytes;
	if (__prequest_number)
		*__prequest_number = 0;
	if (__filename)
		*__filename = __NULLPTR;
	if (__line)
		*__line = 0;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__CrtIsMemoryBlock_defined
#define __local___localdep__CrtIsMemoryBlock_defined
#define __localdep__CrtIsMemoryBlock __LIBC_LOCAL_NAME(_CrtIsMemoryBlock)
#endif /* !__local___localdep__CrtIsMemoryBlock_defined */
#endif /* !__local__CrtIsMemoryBlock_defined */
