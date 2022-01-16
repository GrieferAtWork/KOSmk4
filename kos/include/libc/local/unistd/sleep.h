/* HASH CRC-32:0x6c581e1d */
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
#ifndef __local_sleep_defined
#define __local_sleep_defined
#include <__crt.h>
#if defined(__CRT_HAVE__sleep) || defined(__CRT_HAVE_sleep)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_dos_sleep_defined
#define __local___localdep_dos_sleep_defined
#ifdef __CRT_HAVE__sleep
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_dos_sleep,(unsigned int __duration),_sleep,(__duration))
#elif defined(__CRT_HAVE_sleep)
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_dos_sleep,(unsigned int __duration),sleep,(__duration))
#else /* ... */
#undef __local___localdep_dos_sleep_defined
#endif /* !... */
#endif /* !__local___localdep_dos_sleep_defined */
__LOCAL_LIBC(sleep) unsigned int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(sleep))(unsigned int __seconds) {
	(__NAMESPACE_LOCAL_SYM __localdep_dos_sleep)((__UINT32_TYPE__)__seconds);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sleep_defined
#define __local___localdep_sleep_defined
#define __localdep_sleep __LIBC_LOCAL_NAME(sleep)
#endif /* !__local___localdep_sleep_defined */
#else /* __CRT_HAVE__sleep || __CRT_HAVE_sleep */
#undef __local_sleep_defined
#endif /* !__CRT_HAVE__sleep && !__CRT_HAVE_sleep */
#endif /* !__local_sleep_defined */
