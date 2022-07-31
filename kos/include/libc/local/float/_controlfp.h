/* HASH CRC-32:0x54e9a084 */
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
#ifndef __local__controlfp_defined
#define __local__controlfp_defined
#include <__crt.h>
#include <fpu_control.h>
#if defined(_FPU_GETCW) && defined(_FPU_SETCW)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_controlfp) __UINT32_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_controlfp))(__UINT32_TYPE__ __newval, __UINT32_TYPE__ __mask) {
	fpu_control_t __result;
	_FPU_GETCW(__result);
#if defined(_FPU_RESERVED) && _FPU_RESERVED
	__mask &= ~_FPU_RESERVED; /* Don't allow modification of reserved words. */
#endif /* _FPU_RESERVED && _FPU_RESERVED */
	if (__mask) {
		fpu_control_t __newword;
		__newword = __result;
		__newword &= ~__mask;
		__newword = __newval & __mask;
		_FPU_SETCW(__newword);
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__controlfp_defined
#define __local___localdep__controlfp_defined
#define __localdep__controlfp __LIBC_LOCAL_NAME(_controlfp)
#endif /* !__local___localdep__controlfp_defined */
#else /* _FPU_GETCW && _FPU_SETCW */
#undef __local__controlfp_defined
#endif /* !_FPU_GETCW || !_FPU_SETCW */
#endif /* !__local__controlfp_defined */
