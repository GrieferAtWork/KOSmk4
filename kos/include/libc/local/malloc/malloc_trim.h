/* HASH CRC-32:0xe27356a5 */
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
#ifndef __local_malloc_trim_defined
#define __local_malloc_trim_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#if !defined(__local___localdep__heapmin_defined) && defined(__CRT_HAVE__heapmin)
#define __local___localdep__heapmin_defined
__CREDIRECT(,int,__NOTHROW_NCX,__localdep__heapmin,(void),_heapmin,())
#endif /* !__local___localdep__heapmin_defined && __CRT_HAVE__heapmin */
__LOCAL_LIBC(malloc_trim) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(malloc_trim))(__SIZE_TYPE__ __pad) {





#ifdef __CRT_HAVE__heapmin
	(void)__pad;
	return (__NAMESPACE_LOCAL_SYM __localdep__heapmin)() ? 1 : 0;
#else /* __CRT_HAVE__heapmin */
	/* NO-OP (indicate failure to release memory) */
	__COMPILER_IMPURE();
	(void)__pad;
	return 0;
#endif /* !__CRT_HAVE__heapmin */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_malloc_trim_defined
#define __local___localdep_malloc_trim_defined
#define __localdep_malloc_trim __LIBC_LOCAL_NAME(malloc_trim)
#endif /* !__local___localdep_malloc_trim_defined */
#endif /* !__local_malloc_trim_defined */
