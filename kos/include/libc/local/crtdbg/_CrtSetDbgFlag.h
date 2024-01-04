/* HASH CRC-32:0x6a01b697 */
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
#ifndef __local__CrtSetDbgFlag_defined
#define __local__CrtSetDbgFlag_defined
#include <__crt.h>
#ifdef __CRT_HAVE___p__crtDbgFlag
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep___p__crtDbgFlag_defined
#define __local___localdep___p__crtDbgFlag_defined
__COMPILER_CREDIRECT(__LIBC,,int *,__NOTHROW_NCX,__LIBDCALL,__localdep___p__crtDbgFlag,(void),__p__crtDbgFlag,())
#endif /* !__local___localdep___p__crtDbgFlag_defined */
__LOCAL_LIBC(_CrtSetDbgFlag) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(_CrtSetDbgFlag))(int __new_flag) {
	int __result, *__ptr;
	__ptr = (__NAMESPACE_LOCAL_SYM __localdep___p__crtDbgFlag)();
	__result = *__ptr;
	*__ptr = __new_flag;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__CrtSetDbgFlag_defined
#define __local___localdep__CrtSetDbgFlag_defined
#define __localdep__CrtSetDbgFlag __LIBC_LOCAL_NAME(_CrtSetDbgFlag)
#endif /* !__local___localdep__CrtSetDbgFlag_defined */
#else /* __CRT_HAVE___p__crtDbgFlag */
#undef __local__CrtSetDbgFlag_defined
#endif /* !__CRT_HAVE___p__crtDbgFlag */
#endif /* !__local__CrtSetDbgFlag_defined */
