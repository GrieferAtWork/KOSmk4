/* HASH CRC-32:0xd66e5f14 */
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
#ifndef __local_MAdvise_defined
#define __local_MAdvise_defined 1
#include <__crt.h>
#include <kos/anno.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(MAdvise) __ATTR_NONNULL((1)) void
(__LIBCCALL __LIBC_LOCAL_NAME(MAdvise))(void *__addr, __SIZE_TYPE__ __len, __STDC_INT_AS_UINT_T __advice) __THROWS(...) {
	/* Implement as a no-op, since this function is merely meant as a hint */
	__COMPILER_IMPURE();
	(void)__addr;
	(void)__len;
	(void)__advice;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_MAdvise_defined
#define __local___localdep_MAdvise_defined 1
#define __localdep_MAdvise __LIBC_LOCAL_NAME(MAdvise)
#endif /* !__local___localdep_MAdvise_defined */
#endif /* !__local_MAdvise_defined */
