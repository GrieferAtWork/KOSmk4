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
#ifndef GUARD_LIBC_USER_CORECRT_WSTRING_C
#define GUARD_LIBC_USER_CORECRT_WSTRING_C 1

#include "../api.h"
/**/

#include "corecrt_wstring.h"

DECL_BEGIN

/*[[[head:libd__wcserror,hash:CRC-32=0x8f600bcb]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char16_t *
NOTHROW_NCX(LIBDCALL libd__wcserror)(int errno_value)
/*[[[body:libd__wcserror]]]*/
/*AUTO*/{
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("DOS$_wcserror(%x)", errno_value); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wcserror]]]*/

/*[[[head:libc__wcserror,hash:CRC-32=0x77616da6]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char32_t *
NOTHROW_NCX(LIBKCALL libc__wcserror)(int errno_value)
/*[[[body:libc__wcserror]]]*/
/*AUTO*/{
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("_wcserror(%x)", errno_value); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wcserror]]]*/

/*[[[head:libd__wcserror_s,hash:CRC-32=0x53717418]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:libd__wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("DOS$_wcserror_s(%p, %Ix, %x)", buf, bufsize, errno_value); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wcserror_s]]]*/

/*[[[head:libc__wcserror_s,hash:CRC-32=0xa0cf5e1f]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBKCALL libc__wcserror_s)(char32_t *buf,
                                       size_t bufsize,
                                       int errno_value)
/*[[[body:libc__wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)errno_value;
	CRT_UNIMPLEMENTEDF("_wcserror_s(%p, %Ix, %x)", buf, bufsize, errno_value); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wcserror_s]]]*/

/*[[[head:libd___wcserror,hash:CRC-32=0x94426558]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char16_t *
NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message)
/*[[[body:libd___wcserror]]]*/
/*AUTO*/{
	(void)message;
	CRT_UNIMPLEMENTEDF("DOS$__wcserror(%p)", message); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd___wcserror]]]*/

/*[[[head:libc___wcserror,hash:CRC-32=0xda75d073]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") char32_t *
NOTHROW_NCX(LIBKCALL libc___wcserror)(char32_t const *message)
/*[[[body:libc___wcserror]]]*/
/*AUTO*/{
	(void)message;
	CRT_UNIMPLEMENTEDF("__wcserror(%p)", message); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc___wcserror]]]*/

/*[[[head:libd___wcserror_s,hash:CRC-32=0x1c1899a8]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf,
                                        size_t bufsize,
                                        char16_t const *message)
/*[[[body:libd___wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)message;
	CRT_UNIMPLEMENTEDF("DOS$__wcserror_s(%p, %Ix, %p)", buf, bufsize, message); /* TODO */
	return ENOSYS;
}
/*[[[end:libd___wcserror_s]]]*/

/*[[[head:libc___wcserror_s,hash:CRC-32=0x896e8dd0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.errno") errno_t
NOTHROW_NCX(LIBKCALL libc___wcserror_s)(char32_t *buf,
                                        size_t bufsize,
                                        char32_t const *message)
/*[[[body:libc___wcserror_s]]]*/
/*AUTO*/{
	(void)buf;
	(void)bufsize;
	(void)message;
	CRT_UNIMPLEMENTEDF("__wcserror_s(%p, %Ix, %p)", buf, bufsize, message); /* TODO */
	return ENOSYS;
}
/*[[[end:libc___wcserror_s]]]*/

/*[[[start:exports,hash:CRC-32=0xb523f28c]]]*/
DEFINE_PUBLIC_ALIAS(DOS$_wcserror, libd__wcserror);
DEFINE_PUBLIC_ALIAS(_wcserror, libc__wcserror);
DEFINE_PUBLIC_ALIAS(DOS$_wcserror_s, libd__wcserror_s);
DEFINE_PUBLIC_ALIAS(_wcserror_s, libc__wcserror_s);
DEFINE_PUBLIC_ALIAS(DOS$__wcserror, libd___wcserror);
DEFINE_PUBLIC_ALIAS(__wcserror, libc___wcserror);
DEFINE_PUBLIC_ALIAS(DOS$__wcserror_s, libd___wcserror_s);
DEFINE_PUBLIC_ALIAS(__wcserror_s, libc___wcserror_s);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WSTRING_C */
