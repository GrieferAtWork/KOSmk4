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
#ifndef GUARD_LIBC_USER_BITS_CRT_SYS_ERRLIST_C
#define GUARD_LIBC_USER_BITS_CRT_SYS_ERRLIST_C 1

#include "../api.h"
/**/

#include <kos/exec/idata.h>

#include "../auto/string.h"
#include "../libc/compat.h"
#include "../libc/errno.h"
#include "bits.crt.sys_errlist.h"

DECL_BEGIN

#ifndef ECOUNT
#define ECOUNT (EMAX + 1)
#endif /* !ECOUNT */

#ifndef DOS_ECOUNT
#define DOS_ECOUNT (DOS_EMAX + 1)
#endif /* !DOS_ECOUNT */

#undef sys_nerr
#undef _sys_nerr
#undef sys_errlist
#undef _sys_errlist
INTERN ATTR_SECTION(".data.crt.errno") /*    */ int libc_sys_nerr = ECOUNT;
INTERN ATTR_SECTION(".data.crt.dos.errno") /**/ int libd_sys_nerr = DOS_ECOUNT;
INTERN ATTR_SECTION(".bss.crt.errno") /*     */ char const *libc_sys_errlist[ECOUNT];
INTERN ATTR_SECTION(".bss.crt.dos.errno") /* */ char const *libd_sys_errlist[DOS_ECOUNT];

DEFINE_PUBLIC_ALIAS(sys_nerr, libc_sys_nerr);
DEFINE_PUBLIC_ALIAS(_sys_nerr, libc_sys_nerr);
DEFINE_PUBLIC_ALIAS(DOS$sys_nerr, libd_sys_nerr);
DEFINE_PUBLIC_ALIAS(DOS$_sys_nerr, libd_sys_nerr);

DEFINE_PUBLIC_IDATA(sys_errlist, libc___sys_errlist, ECOUNT * __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(_sys_errlist, libc___sys_errlist, ECOUNT * __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$sys_errlist, libd___sys_errlist, DOS_ECOUNT * __SIZEOF_POINTER__);
DEFINE_PUBLIC_IDATA(DOS$_sys_errlist, libd___sys_errlist, DOS_ECOUNT * __SIZEOF_POINTER__);


/*[[[head:libd___sys_errlist,hash:CRC-32=0xf8951d59]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST ATTR_RETNONNULL WUNUSED char const *const *
NOTHROW(LIBDCALL libd___sys_errlist)(void)
/*[[[body:libd___sys_errlist]]]*/
{
	char const **result = libd_sys_errlist;
	if (!result[0]) {
		unsigned int i = DOS_ECOUNT;
		/* Lazily initialize */
		for (;;) {
			--i;
			result[i] = libd_strerrordesc_np(i);
			COMPILER_WRITE_BARRIER();
			if (!i)
				break;
		}
	}
	return result;
}
/*[[[end:libd___sys_errlist]]]*/

/*[[[head:libc___sys_errlist,hash:CRC-32=0x56fda5bd]]]*/
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST ATTR_RETNONNULL WUNUSED char const *const *
NOTHROW(LIBCCALL libc___sys_errlist)(void)
/*[[[body:libc___sys_errlist]]]*/
{
	char const **result = libc_sys_errlist;
	if (!result[0]) {
		unsigned int i = ECOUNT;
		/* Lazily initialize */
		for (;;) {
			--i;
			result[i] = libc_strerrordesc_np(i);
			COMPILER_WRITE_BARRIER();
			if (!i)
				break;
		}
	}
	return result;
}
/*[[[end:libc___sys_errlist]]]*/

/*[[[head:libd___sys_nerr,hash:CRC-32=0x3c6239c9]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.errno") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW(LIBDCALL libd___sys_nerr)(void)
/*[[[body:libd___sys_nerr]]]*/
{
	return &libd_sys_nerr;
}
/*[[[end:libd___sys_nerr]]]*/

/*[[[head:libc___sys_nerr,hash:CRC-32=0xf746e876]]]*/
INTERN ATTR_SECTION(".text.crt.errno") ATTR_CONST ATTR_RETNONNULL WUNUSED int *
NOTHROW(LIBCCALL libc___sys_nerr)(void)
/*[[[body:libc___sys_nerr]]]*/
{
	return &libc_sys_nerr;
}
/*[[[end:libc___sys_nerr]]]*/

/*[[[start:exports,hash:CRC-32=0x24fd56d9]]]*/
DEFINE_PUBLIC_ALIAS(DOS$__sys_errlist, libd___sys_errlist);
DEFINE_PUBLIC_ALIAS(__sys_errlist, libc___sys_errlist);
DEFINE_PUBLIC_ALIAS(DOS$__sys_nerr, libd___sys_nerr);
DEFINE_PUBLIC_ALIAS(__sys_nerr, libc___sys_nerr);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_BITS_CRT_SYS_ERRLIST_C */
