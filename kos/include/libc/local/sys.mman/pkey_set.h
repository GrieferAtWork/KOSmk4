/* HASH CRC-32:0xb1dfc0be */
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
#ifndef __local_pkey_set_defined
#define __local_pkey_set_defined
#include <__crt.h>
#include <asm/pkey.h>
#ifdef __ARCH_HAVE_PKEY
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(pkey_set) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(pkey_set))(int __pkey, unsigned int __access_rights) {
	if __unlikely(!__arch_pkey_verify_key(__pkey) ||
	            !__arch_pkey_verify_rights(__access_rights))
		goto __badkey_or_rights;
	__arch_pkey_set(__pkey, __access_rights);
	return 0;
__badkey_or_rights:
#ifdef __EINVAL
	return __libc_seterrno(__EINVAL);
#else /* __EINVAL */
	return -1;
#endif /* !__EINVAL */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_pkey_set_defined
#define __local___localdep_pkey_set_defined
#define __localdep_pkey_set __LIBC_LOCAL_NAME(pkey_set)
#endif /* !__local___localdep_pkey_set_defined */
#else /* __ARCH_HAVE_PKEY */
#undef __local_pkey_set_defined
#endif /* !__ARCH_HAVE_PKEY */
#endif /* !__local_pkey_set_defined */
