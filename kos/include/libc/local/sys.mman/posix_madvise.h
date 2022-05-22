/* HASH CRC-32:0xa99c12a */
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
#ifndef __local_posix_madvise_defined
#define __local_posix_madvise_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(posix_madvise) __ATTR_ACCESS_NONE(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_madvise))(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __advice) {
	/* Implement as a no-op, since this function is merely meant as a hint */
	__COMPILER_IMPURE();
	(void)__addr;
	(void)__len;
	(void)__advice;
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_madvise_defined
#define __local___localdep_posix_madvise_defined
#define __localdep_posix_madvise __LIBC_LOCAL_NAME(posix_madvise)
#endif /* !__local___localdep_posix_madvise_defined */
#endif /* !__local_posix_madvise_defined */
