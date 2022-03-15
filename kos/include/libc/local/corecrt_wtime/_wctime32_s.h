/* HASH CRC-32:0x2c623195 */
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
#ifndef __local__wctime32_s_defined
#define __local__wctime32_s_defined
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__wctime64_s_defined
#define __local___localdep__wctime64_s_defined
#ifdef __CRT_HAVE__wctime64_s
__CREDIRECT(__ATTR_NONNULL((1, 3)),__errno_t,__NOTHROW_NCX,__localdep__wctime64_s,(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __time64_t const *__timer),_wctime64_s,(__buf,__buflen,__timer))
#else /* __CRT_HAVE__wctime64_s */
__NAMESPACE_LOCAL_END
#include <libc/local/corecrt_wtime/_wctime64_s.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__wctime64_s __LIBC_LOCAL_NAME(_wctime64_s)
#endif /* !__CRT_HAVE__wctime64_s */
#endif /* !__local___localdep__wctime64_s_defined */
__LOCAL_LIBC(_wctime32_s) __ATTR_NONNULL((1, 3)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_wctime32_s))(__WCHAR_TYPE__ *__buf, __SIZE_TYPE__ __buflen, __time32_t const *__timer) {
	__time64_t __timer64 = (__time64_t)*__timer;
	return (__NAMESPACE_LOCAL_SYM __localdep__wctime64_s)(__buf, __buflen, &__timer64);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__wctime32_s_defined
#define __local___localdep__wctime32_s_defined
#define __localdep__wctime32_s __LIBC_LOCAL_NAME(_wctime32_s)
#endif /* !__local___localdep__wctime32_s_defined */
#endif /* !__local__wctime32_s_defined */
