/* HASH CRC-32:0xc6911825 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_srandom_defined
#define __local_srandom_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_srand_defined
#define __local___localdep_srand_defined
#ifdef __CRT_HAVE_srand
__CREDIRECT_VOID(,__NOTHROW,__localdep_srand,(long __seed),srand,(__seed))
#else /* __CRT_HAVE_srand */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__CRT_HAVE_srandom) && __SIZEOF_INT__ == __SIZEOF_LONG__
__CREDIRECT_VOID(,__NOTHROW,__localdep_srand,(long __seed),srandom,(__seed))
#else /* __CRT_HAVE_srandom && __SIZEOF_INT__ == __SIZEOF_LONG__ */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/srand.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_srand __LIBC_LOCAL_NAME(srand)
#endif /* !__CRT_HAVE_srandom || __SIZEOF_INT__ != __SIZEOF_LONG__ */
#endif /* !__CRT_HAVE_srand */
#endif /* !__local___localdep_srand_defined */
__LOCAL_LIBC(srandom) void
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(srandom))(unsigned int __seed) {
	(__NAMESPACE_LOCAL_SYM __localdep_srand)((long)__seed);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_srandom_defined
#define __local___localdep_srandom_defined
#define __localdep_srandom __LIBC_LOCAL_NAME(srandom)
#endif /* !__local___localdep_srandom_defined */
#endif /* !__local_srandom_defined */
