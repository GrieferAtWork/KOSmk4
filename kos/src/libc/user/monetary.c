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
#ifndef GUARD_LIBC_USER_MONETARY_C
#define GUARD_LIBC_USER_MONETARY_C 1

#include "../api.h"
#include "monetary.h"

DECL_BEGIN

/*[[[head:libd_strfmon,hash:CRC-32=0xfc9bf649]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.monetary") ATTR_LIBC_STRFMON(3, 4) NONNULL((1, 3)) ssize_t
NOTHROW_NCX(VLIBDCALL libd_strfmon)(char *__restrict s,
                                    size_t maxsize,
                                    char const *__restrict format,
                                    ...)
/*[[[body:libd_strfmon]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon(%q, %Ix, %q, ...)", s, maxsize, format); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_strfmon]]]*/

/*[[[head:libc_strfmon,hash:CRC-32=0x52cfa8a8]]]*/
INTERN ATTR_SECTION(".text.crt.utility.monetary") ATTR_LIBC_STRFMON(3, 4) NONNULL((1, 3)) ssize_t
NOTHROW_NCX(VLIBCCALL libc_strfmon)(char *__restrict s,
                                    size_t maxsize,
                                    char const *__restrict format,
                                    ...)
/*[[[body:libc_strfmon]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon(%q, %Ix, %q, ...)", s, maxsize, format); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_strfmon]]]*/

/*[[[head:libd_strfmon_l,hash:CRC-32=0xc7fee8ed]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.monetary") ATTR_LIBC_STRFMON(4, 5) NONNULL((1, 4)) ssize_t
NOTHROW_NCX(VLIBDCALL libd_strfmon_l)(char *__restrict s,
                                      size_t maxsize,
                                      locale_t loc,
                                      const char *__restrict format,
                                      ...)
/*[[[body:libd_strfmon_l]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)loc;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon_l(%q, %Ix, %p, %q, ...)", s, maxsize, loc, format); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_strfmon_l]]]*/

/*[[[head:libc_strfmon_l,hash:CRC-32=0x22732bdf]]]*/
INTERN ATTR_SECTION(".text.crt.utility.monetary") ATTR_LIBC_STRFMON(4, 5) NONNULL((1, 4)) ssize_t
NOTHROW_NCX(VLIBCCALL libc_strfmon_l)(char *__restrict s,
                                      size_t maxsize,
                                      locale_t loc,
                                      const char *__restrict format,
                                      ...)
/*[[[body:libc_strfmon_l]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)loc;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon_l(%q, %Ix, %p, %q, ...)", s, maxsize, loc, format); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_strfmon_l]]]*/





/*[[[start:exports,hash:CRC-32=0xda3de07]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$strfmon, libd_strfmon);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(strfmon, libc_strfmon);
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS(DOS$__strfmon_l, libd_strfmon_l);
DEFINE_PUBLIC_ALIAS(DOS$strfmon_l, libd_strfmon_l);
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS(__strfmon_l, libc_strfmon_l);
DEFINE_PUBLIC_ALIAS(strfmon_l, libc_strfmon_l);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MONETARY_C */
