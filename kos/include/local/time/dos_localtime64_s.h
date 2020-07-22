/* HASH CRC-32:0x73dd875f */
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
#ifndef __local_dos_localtime64_s_defined
#define __local_dos_localtime64_s_defined 1
#include <__crt.h>
#ifdef __CRT_HAVE__localtime32_s
#include <bits/types.h>
#include <bits/crt/tm.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: dos_localtime32_s from time */
#ifndef __local___localdep_dos_localtime32_s_defined
#define __local___localdep_dos_localtime32_s_defined 1
/* Return the `struct tm' representation of *TIMER in local time, using *TP to store the result */
__CREDIRECT(__ATTR_NONNULL((1, 2)),__errno_t,__NOTHROW_NCX,__localdep_dos_localtime32_s,(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time32_t const *__restrict __timer),_localtime32_s,(__tp,__timer))
#endif /* !__local___localdep_dos_localtime32_s_defined */
__LOCAL_LIBC(dos_localtime64_s) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(dos_localtime64_s))(struct __NAMESPACE_STD_SYM tm *__restrict __tp, __time64_t const *__restrict __timer) {
	__time32_t __tm32 = *__timer;
	return __localdep_dos_localtime32_s(__tp, &__tm32);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_dos_localtime64_s_defined
#define __local___localdep_dos_localtime64_s_defined 1
#define __localdep_dos_localtime64_s __LIBC_LOCAL_NAME(dos_localtime64_s)
#endif /* !__local___localdep_dos_localtime64_s_defined */
#else /* __CRT_HAVE__localtime32_s */
#undef __local_dos_localtime64_s_defined
#endif /* !__CRT_HAVE__localtime32_s */
#endif /* !__local_dos_localtime64_s_defined */
