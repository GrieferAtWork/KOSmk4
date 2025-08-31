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
#ifndef GUARD_LIBC_USER_MONETARY_C
#define GUARD_LIBC_USER_MONETARY_C 1

#include "../api.h"
#include "monetary.h"

DECL_BEGIN

/*[[[head:libd_strfmon,hash:CRC-32=0x12f68638]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.monetary") ATTR_IN(3) ATTR_LIBC_STRFMON(3, 4) ATTR_OUTS(1, 2) ssize_t
NOTHROW_NCX(VLIBDCALL libd_strfmon)(char *__restrict s,
                                    size_t maxsize,
                                    char const *__restrict format,
                                    ...)
/*[[[body:libd_strfmon]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon(s: %q, maxsize: %Ix, format: %q, ...)", s, maxsize, format); /* TODO */
	return libc_seterrno(ENOSYS);
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_strfmon]]]*/

/*[[[head:libc_strfmon,hash:CRC-32=0x3a8a2c85]]]*/
INTERN ATTR_SECTION(".text.crt.utility.monetary") ATTR_IN(3) ATTR_LIBC_STRFMON(3, 4) ATTR_OUTS(1, 2) ssize_t
NOTHROW_NCX(VLIBCCALL libc_strfmon)(char *__restrict s,
                                    size_t maxsize,
                                    char const *__restrict format,
                                    ...)
/*[[[body:libc_strfmon]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon(s: %q, maxsize: %Ix, format: %q, ...)", s, maxsize, format); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_strfmon]]]*/

/*[[[head:libd_strfmon_l,hash:CRC-32=0xf31c6443]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.utility.monetary") ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2) ssize_t
NOTHROW_NCX(VLIBDCALL libd_strfmon_l)(char *__restrict s,
                                      size_t maxsize,
                                      locale_t loc,
                                      char const *__restrict format,
                                      ...)
/*[[[body:libd_strfmon_l]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)loc;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon_l(s: %q, maxsize: %Ix, loc: %p, format: %q, ...)", s, maxsize, loc, format); /* TODO */
	return libc_seterrno(ENOSYS);
}
#endif /* MAGIC:impl_if */
/*[[[end:libd_strfmon_l]]]*/

/*[[[head:libc_strfmon_l,hash:CRC-32=0x20e2f646]]]*/
INTERN ATTR_SECTION(".text.crt.utility.monetary") ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2) ssize_t
NOTHROW_NCX(VLIBCCALL libc_strfmon_l)(char *__restrict s,
                                      size_t maxsize,
                                      locale_t loc,
                                      char const *__restrict format,
                                      ...)
/*[[[body:libc_strfmon_l]]]*/
/*AUTO*/{
	(void)s;
	(void)maxsize;
	(void)loc;
	(void)format;
	CRT_UNIMPLEMENTEDF("strfmon_l(s: %q, maxsize: %Ix, loc: %p, format: %q, ...)", s, maxsize, loc, format); /* TODO */
	return libc_seterrno(ENOSYS);
}
/*[[[end:libc_strfmon_l]]]*/





/*[[[start:exports,hash:CRC-32=0xeef83e5]]]*/
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(DOS$strfmon,libd_strfmon,ATTR_IN(3) ATTR_LIBC_STRFMON(3, 4) ATTR_OUTS(1, 2),ssize_t,NOTHROW_NCX,VLIBDCALL,(char *__restrict s, size_t maxsize, char const *__restrict format, ...),(s,maxsize,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(strfmon,libc_strfmon,ATTR_IN(3) ATTR_LIBC_STRFMON(3, 4) ATTR_OUTS(1, 2),ssize_t,NOTHROW_NCX,VLIBCCALL,(char *__restrict s, size_t maxsize, char const *__restrict format, ...),(s,maxsize,format,));
#ifndef __LIBCCALL_IS_LIBDCALL
DEFINE_PUBLIC_ALIAS_P(DOS$__strfmon_l,libd_strfmon_l,ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2),ssize_t,NOTHROW_NCX,VLIBDCALL,(char *__restrict s, size_t maxsize, locale_t loc, char const *__restrict format, ...),(s,maxsize,loc,format,));
DEFINE_PUBLIC_ALIAS_P(DOS$strfmon_l,libd_strfmon_l,ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2),ssize_t,NOTHROW_NCX,VLIBDCALL,(char *__restrict s, size_t maxsize, locale_t loc, char const *__restrict format, ...),(s,maxsize,loc,format,));
#endif /* !__LIBCCALL_IS_LIBDCALL */
DEFINE_PUBLIC_ALIAS_P(__strfmon_l,libc_strfmon_l,ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2),ssize_t,NOTHROW_NCX,VLIBCCALL,(char *__restrict s, size_t maxsize, locale_t loc, char const *__restrict format, ...),(s,maxsize,loc,format,));
DEFINE_PUBLIC_ALIAS_P(strfmon_l,libc_strfmon_l,ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2),ssize_t,NOTHROW_NCX,VLIBCCALL,(char *__restrict s, size_t maxsize, locale_t loc, char const *__restrict format, ...),(s,maxsize,loc,format,));
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MONETARY_C */
