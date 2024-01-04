/* HASH CRC-32:0x6a4b4fa8 */
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
#ifndef __local_mallinfo_defined
#define __local_mallinfo_defined
#include <__crt.h>
#ifdef __CRT_HAVE_mallinfo2
#include <bits/crt/mallinfo.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_crt_mallinfo2_defined
#define __local___localdep_crt_mallinfo2_defined
__CREDIRECT(,struct mallinfo2,__NOTHROW_NCX,__localdep_crt_mallinfo2,(void),mallinfo2,())
#endif /* !__local___localdep_crt_mallinfo2_defined */
__LOCAL_LIBC(mallinfo) struct mallinfo
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(mallinfo))(void) {
	struct mallinfo __result;
	struct mallinfo2 __info = (__NAMESPACE_LOCAL_SYM __localdep_crt_mallinfo2)();
	__result.arena    = (int)(unsigned int)__info.arena;
	__result.ordblks  = (int)(unsigned int)__info.ordblks;
	__result.smblks   = (int)(unsigned int)__info.smblks;
	__result.hblks    = (int)(unsigned int)__info.hblks;
	__result.hblkhd   = (int)(unsigned int)__info.hblkhd;
	__result.usmblks  = (int)(unsigned int)__info.usmblks;
	__result.fsmblks  = (int)(unsigned int)__info.fsmblks;
	__result.uordblks = (int)(unsigned int)__info.uordblks;
	__result.fordblks = (int)(unsigned int)__info.fordblks;
	__result.keepcost = (int)(unsigned int)__info.keepcost;
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_mallinfo_defined
#define __local___localdep_mallinfo_defined
#define __localdep_mallinfo __LIBC_LOCAL_NAME(mallinfo)
#endif /* !__local___localdep_mallinfo_defined */
#else /* __CRT_HAVE_mallinfo2 */
#undef __local_mallinfo_defined
#endif /* !__CRT_HAVE_mallinfo2 */
#endif /* !__local_mallinfo_defined */
