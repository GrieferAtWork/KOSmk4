/* HASH CRC-32:0xe9d0491e */
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
#ifndef GUARD_LIBC_AUTO_RESOLV_C
#define GUARD_LIBC_AUTO_RESOLV_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/resolv.h"
#include "../user/arpa.nameser.h"
#include "../user/stdio.h"
#include "string.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <bits/crt/resolv.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_IN(1) ATTR_IN(2) ATTR_OUT_OPT(3) int
NOTHROW_NCX(LIBCCALL libc_sym_ston)(struct res_sym const *symbols,
                                    char const *wanted_name,
                                    int *p_success) {
	while (symbols->name != NULL) {
		if (libc_strcasecmp(symbols->name, wanted_name) == 0) {
			if (p_success)
				*p_success = 1;
			goto done;
		}
		++symbols;
	}
	if (p_success)
		*p_success = 0;
done:
	return symbols->number;
}
#include <bits/crt/resolv.h>
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_RETNONNULL ATTR_IN(1) ATTR_OUT_OPT(3) char const *
NOTHROW_NCX(LIBCCALL libc_sym_ntos)(struct res_sym const *symbols,
                                    int wanted_number,
                                    int *p_success) {
#if __SIZEOF_INT__ == 4
	static char fallback_namebuf[COMPILER_LENOF("-2147483648")];
#elif __SIZEOF_INT__ == 8
	static char fallback_namebuf[COMPILER_LENOF("-9223372036854775808")];
#elif __SIZEOF_INT__ == 2
	static char fallback_namebuf[COMPILER_LENOF("-32768")];
#elif __SIZEOF_INT__ == 1
	static char fallback_namebuf[COMPILER_LENOF("-128")];
#else /* ... */
#error "Unsupported sizeof(int)"
#endif /* !... */
	while (symbols->name != NULL) {
		if (symbols->number == wanted_number) {
			if (p_success)
				*p_success = 1;
			return symbols->name;
		}
		++symbols;
	}
	if (p_success)
		*p_success = 0;
	libc_sprintf(fallback_namebuf, "%d", wanted_number);
	return fallback_namebuf;
}
#include <bits/crt/resolv.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_RETNONNULL ATTR_IN(1) ATTR_OUT_OPT(3) char const *
NOTHROW_NCX(LIBCCALL libc_sym_ntop)(struct res_sym const *symbols,
                                    int wanted_number,
                                    int *p_success) {
	while (symbols->name != NULL) {
		if (symbols->number == wanted_number) {
			if (p_success)
				*p_success = 1;
			return symbols->humanname;
		}
		++symbols;
	}
	/* Re-use the fallback path of `sym_ntos(3)' */
	return libc_sym_ntos(symbols, wanted_number, p_success);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") ATTR_IN(1) NONNULL((2)) int
NOTHROW_NCX(LIBCCALL libc_dn_skipname)(u_char const *msg_ptr,
                                       u_char const *end_of_msg) {
	u_char const *orig_msg_ptr = msg_ptr;
	if (libc_ns_name_skip(&msg_ptr, end_of_msg) == -1)
		return -1;
	return (int)(unsigned int)(size_t)(msg_ptr - orig_msg_ptr);
}
#include <hybrid/typecore.h>
INTERN ATTR_SECTION(".text.crt.net.nameser") int
NOTHROW_NCX(LIBCCALL libc_dn_expand)(u_char const *msg_ptr,
                                     u_char const *end_of_msg,
                                     u_char const *srcbuf,
                                     char *dstbuf,
                                     int dstbufsize) {
	int n = libc_ns_name_uncompress(msg_ptr, end_of_msg, srcbuf,
	                           dstbuf, (size_t)dstbufsize);
	if (n > 0 && dstbuf[0] == '.')
		dstbuf[0] = '\0';
	return n;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS(__sym_ston, libc_sym_ston);
DEFINE_PUBLIC_ALIAS(sym_ston, libc_sym_ston);
DEFINE_PUBLIC_ALIAS(__sym_ntos, libc_sym_ntos);
DEFINE_PUBLIC_ALIAS(sym_ntos, libc_sym_ntos);
DEFINE_PUBLIC_ALIAS(__sym_ntop, libc_sym_ntop);
DEFINE_PUBLIC_ALIAS(sym_ntop, libc_sym_ntop);
DEFINE_PUBLIC_ALIAS(__dn_skipname, libc_dn_skipname);
DEFINE_PUBLIC_ALIAS(dn_skipname, libc_dn_skipname);
DEFINE_PUBLIC_ALIAS(__dn_expand, libc_dn_expand);
DEFINE_PUBLIC_ALIAS(dn_expand, libc_dn_expand);
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_RESOLV_C */
