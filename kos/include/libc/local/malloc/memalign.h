/* HASH CRC-32:0xec556376 */
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
#ifndef __local_memalign_defined
#define __local_memalign_defined
#include <__crt.h>
#ifdef __CRT_HAVE_posix_memalign
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_posix_memalign_defined
#define __local___localdep_crt_posix_memalign_defined
__CREDIRECT(__ATTR_OUT(1),int,__NOTHROW_NCX,__localdep_crt_posix_memalign,(void **__restrict __pp, __SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes),posix_memalign,(__pp,__alignment,__n_bytes))
#endif /* !__local___localdep_crt_posix_memalign_defined */
__LOCAL_LIBC(memalign) __ATTR_MALLOC __ATTR_WUNUSED __ATTR_ALLOC_ALIGN(1) __ATTR_ALLOC_SIZE((2)) void *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(memalign))(__SIZE_TYPE__ __alignment, __SIZE_TYPE__ __n_bytes) {
	void *__result;
	if ((__NAMESPACE_LOCAL_SYM __localdep_crt_posix_memalign)(&__result, __alignment, __n_bytes))
		return __NULLPTR;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_memalign_defined
#define __local___localdep_memalign_defined
#define __localdep_memalign __LIBC_LOCAL_NAME(memalign)
#endif /* !__local___localdep_memalign_defined */
#else /* __CRT_HAVE_posix_memalign */
#undef __local_memalign_defined
#endif /* !__CRT_HAVE_posix_memalign */
#endif /* !__local_memalign_defined */
