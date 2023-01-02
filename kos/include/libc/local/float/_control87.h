/* HASH CRC-32:0x952be730 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__control87_defined
#define __local__control87_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__controlfp_defined
#define __local___localdep__controlfp_defined
#ifdef __CRT_HAVE__controlfp
__CREDIRECT(,__UINT32_TYPE__,__NOTHROW_NCX,__localdep__controlfp,(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask),_controlfp,(__newval,__mask))
#else /* __CRT_HAVE__controlfp */
__NAMESPACE_LOCAL_END
#include <fpu_control.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(_FPU_GETCW) && defined(_FPU_SETCW)
__NAMESPACE_LOCAL_END
#include <libc/local/float/_controlfp.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__controlfp __LIBC_LOCAL_NAME(_controlfp)
#else /* _FPU_GETCW && _FPU_SETCW */
#undef __local___localdep__controlfp_defined
#endif /* !_FPU_GETCW || !_FPU_SETCW */
#endif /* !__CRT_HAVE__controlfp */
#endif /* !__local___localdep__controlfp_defined */
__LOCAL_LIBC(_control87) __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_control87))(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask) {
	return (__NAMESPACE_LOCAL_SYM __localdep__controlfp)(__newval, __mask);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__control87_defined
#define __local___localdep__control87_defined
#define __localdep__control87 __LIBC_LOCAL_NAME(_control87)
#endif /* !__local___localdep__control87_defined */
#endif /* !__local__control87_defined */
