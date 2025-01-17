/* HASH CRC-32:0x1b224974 */
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
#ifndef __local_sym_ntop_defined
#define __local_sym_ntop_defined
#include <__crt.h>
#include <bits/crt/resolv.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_sym_ntos_defined
#define __local___localdep_sym_ntos_defined
#ifdef __CRT_HAVE_sym_ntos
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT_OPT(3),char const *,__NOTHROW_NCX,__localdep_sym_ntos,(struct res_sym const *__symbols, int __wanted_number, int *__p_success),sym_ntos,(__symbols,__wanted_number,__p_success))
#elif defined(__CRT_HAVE___sym_ntos)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT_OPT(3),char const *,__NOTHROW_NCX,__localdep_sym_ntos,(struct res_sym const *__symbols, int __wanted_number, int *__p_success),__sym_ntos,(__symbols,__wanted_number,__p_success))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/resolv/sym_ntos.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_sym_ntos __LIBC_LOCAL_NAME(sym_ntos)
#endif /* !... */
#endif /* !__local___localdep_sym_ntos_defined */
__LOCAL_LIBC(sym_ntop) __ATTR_RETNONNULL __ATTR_IN(1) __ATTR_OUT_OPT(3) char const *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sym_ntop))(struct res_sym const *__symbols, int __wanted_number, int *__p_success) {
	while (__symbols->name != __NULLPTR) {
		if (__symbols->number == __wanted_number) {
			if (__p_success)
				*__p_success = 1;
			return __symbols->humanname;
		}
		++__symbols;
	}
	/* Re-use the fallback path of `sym_ntos(3)' */
	return (__NAMESPACE_LOCAL_SYM __localdep_sym_ntos)(__symbols, __wanted_number, __p_success);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_sym_ntop_defined
#define __local___localdep_sym_ntop_defined
#define __localdep_sym_ntop __LIBC_LOCAL_NAME(sym_ntop)
#endif /* !__local___localdep_sym_ntop_defined */
#endif /* !__local_sym_ntop_defined */
