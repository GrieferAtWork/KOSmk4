/* HASH CRC-32:0x20ce86bd */
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
#ifndef __local_PKeySet_defined
#define __local_PKeySet_defined
#include <__crt.h>
#include <asm/pkey.h>
#if defined(__ARCH_HAVE_PKEY) && defined(__CRT_HAVE_except_thrown)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_except_thrown_defined
#define __local___localdep_except_thrown_defined
__NAMESPACE_LOCAL_END
#include <kos/bits/exception_data.h>
#ifndef __EXCEPT_THROWN_CC
#define __EXCEPT_THROWN_CC __LIBKCALL
#endif /* !__EXCEPT_THROWN_CC */
__NAMESPACE_LOCAL_BEGIN
__LIBC __ATTR_COLD __ATTR_NORETURN void (__EXCEPT_THROWN_CC __localdep_except_thrown)(__except_code_t __code, unsigned int ___argc, ...) __CASMNAME("except_thrown");
#endif /* !__local___localdep_except_thrown_defined */
__NAMESPACE_LOCAL_END
#include <kos/except/codes.h>
#include <kos/except/reason/inval.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(PKeySet) void
(__LIBCCALL __LIBC_LOCAL_NAME(PKeySet))(int __pkey, unsigned int __access_rights) __THROWS(...) {
	if __unlikely(!__arch_pkey_verify_key(__pkey))
		(__NAMESPACE_LOCAL_SYM __localdep_except_thrown)(EXCEPT_CODEOF(E_INVALID_ARGUMENT_BAD_VALUE), 2, E_INVALID_ARGUMENT_CONTEXT_PKEY_SET_PKEY, __pkey);
	if __unlikely(!__arch_pkey_verify_rights(__access_rights))
		(__NAMESPACE_LOCAL_SYM __localdep_except_thrown)(EXCEPT_CODEOF(E_INVALID_ARGUMENT_BAD_VALUE), 2, E_INVALID_ARGUMENT_CONTEXT_PKEY_SET_ACCESS_RIGHTS, __access_rights);
	__arch_pkey_set(__pkey, __access_rights);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_PKeySet_defined
#define __local___localdep_PKeySet_defined
#define __localdep_PKeySet __LIBC_LOCAL_NAME(PKeySet)
#endif /* !__local___localdep_PKeySet_defined */
#else /* __ARCH_HAVE_PKEY && __CRT_HAVE_except_thrown */
#undef __local_PKeySet_defined
#endif /* !__ARCH_HAVE_PKEY || !__CRT_HAVE_except_thrown */
#endif /* !__local_PKeySet_defined */
