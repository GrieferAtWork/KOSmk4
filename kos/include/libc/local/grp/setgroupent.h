/* HASH CRC-32:0xb3de3c3b */
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
#ifndef __local_setgroupent_defined
#define __local_setgroupent_defined
#include <__crt.h>
#ifdef __CRT_HAVE_setgrent
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_setgrent_defined
#define __local___localdep_setgrent_defined
__CREDIRECT_VOID(,__NOTHROW_RPC,__localdep_setgrent,(void),setgrent,())
#endif /* !__local___localdep_setgrent_defined */
__LOCAL_LIBC(setgroupent) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(setgroupent))(int __keep_open) {
	(void)__keep_open;
	(__NAMESPACE_LOCAL_SYM __localdep_setgrent)();
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_setgroupent_defined
#define __local___localdep_setgroupent_defined
#define __localdep_setgroupent __LIBC_LOCAL_NAME(setgroupent)
#endif /* !__local___localdep_setgroupent_defined */
#else /* __CRT_HAVE_setgrent */
#undef __local_setgroupent_defined
#endif /* !__CRT_HAVE_setgrent */
#endif /* !__local_setgroupent_defined */
