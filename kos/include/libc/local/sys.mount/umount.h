/* HASH CRC-32:0x32ac9a2e */
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
#ifndef __local_umount_defined
#define __local_umount_defined
#include <__crt.h>
#ifdef __CRT_HAVE_umount2
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_umount2_defined
#define __local___localdep_umount2_defined
__NAMESPACE_LOCAL_END
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,__localdep_umount2,(char const *__special_file, __STDC_INT_AS_UINT_T __flags),umount2,(__special_file,__flags))
#endif /* !__local___localdep_umount2_defined */
__LOCAL_LIBC(umount) __ATTR_IN(1) int
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(umount))(char const *__special_file) {
	return (__NAMESPACE_LOCAL_SYM __localdep_umount2)(__special_file, 0);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_umount_defined
#define __local___localdep_umount_defined
#define __localdep_umount __LIBC_LOCAL_NAME(umount)
#endif /* !__local___localdep_umount_defined */
#else /* __CRT_HAVE_umount2 */
#undef __local_umount_defined
#endif /* !__CRT_HAVE_umount2 */
#endif /* !__local_umount_defined */
