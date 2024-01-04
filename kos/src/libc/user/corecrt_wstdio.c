/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CORECRT_WSTDIO_C
#define GUARD_LIBC_USER_CORECRT_WSTDIO_C 1

#include "../api.h"
/**/

#include "corecrt_wstdio.h"

DECL_BEGIN

/*[[[head:libd__wtempnam,hash:CRC-32=0x7a827221]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) char16_t *
NOTHROW_NCX(LIBDCALL libd__wtempnam)(char16_t const *directory,
                                     char16_t const *file_prefix)
/*[[[body:libd__wtempnam]]]*/
/*AUTO*/{
	(void)directory;
	(void)file_prefix;
	CRT_UNIMPLEMENTEDF("DOS$_wtempnam(directory: %p, file_prefix: %p)", directory, file_prefix); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wtempnam]]]*/

/*[[[head:libc__wtempnam,hash:CRC-32=0x1b695b7e]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") WUNUSED ATTR_IN_OPT(1) ATTR_IN_OPT(2) char32_t *
NOTHROW_NCX(LIBKCALL libc__wtempnam)(char32_t const *directory,
                                     char32_t const *file_prefix)
/*[[[body:libc__wtempnam]]]*/
/*AUTO*/{
	(void)directory;
	(void)file_prefix;
	CRT_UNIMPLEMENTEDF("_wtempnam(directory: %p, file_prefix: %p)", directory, file_prefix); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wtempnam]]]*/

/*[[[head:libd__wtmpnam_s,hash:CRC-32=0x206448b]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBDCALL libd__wtmpnam_s)(char16_t *dst,
                                      size_t wchar_count)
/*[[[body:libd__wtmpnam_s]]]*/
/*AUTO*/{
	(void)dst;
	(void)wchar_count;
	CRT_UNIMPLEMENTEDF("DOS$_wtmpnam_s(dst: %p, wchar_count: %Ix)", dst, wchar_count); /* TODO */
	return ENOSYS;
}
/*[[[end:libd__wtmpnam_s]]]*/

/*[[[head:libc__wtmpnam_s,hash:CRC-32=0xe3585487]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") ATTR_OUTS(1, 2) errno_t
NOTHROW_NCX(LIBKCALL libc__wtmpnam_s)(char32_t *dst,
                                      size_t wchar_count)
/*[[[body:libc__wtmpnam_s]]]*/
/*AUTO*/{
	(void)dst;
	(void)wchar_count;
	CRT_UNIMPLEMENTEDF("_wtmpnam_s(dst: %p, wchar_count: %Ix)", dst, wchar_count); /* TODO */
	return ENOSYS;
}
/*[[[end:libc__wtmpnam_s]]]*/

/*[[[head:libd__wtmpnam,hash:CRC-32=0xdb8c85f8]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.fs.utility") char16_t *
NOTHROW_NCX(LIBDCALL libd__wtmpnam)(char16_t *buf)
/*[[[body:libd__wtmpnam]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("DOS$_wtmpnam(buf: %p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libd__wtmpnam]]]*/

/*[[[head:libc__wtmpnam,hash:CRC-32=0x9236e677]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.fs.utility") char32_t *
NOTHROW_NCX(LIBKCALL libc__wtmpnam)(char32_t *buf)
/*[[[body:libc__wtmpnam]]]*/
/*AUTO*/{
	(void)buf;
	CRT_UNIMPLEMENTEDF("_wtmpnam(buf: %p)", buf); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:libc__wtmpnam]]]*/

/*[[[start:exports,hash:CRC-32=0x41fbcb68]]]*/
DEFINE_PUBLIC_ALIAS(DOS$_wtempnam, libd__wtempnam);
DEFINE_PUBLIC_ALIAS(_wtempnam, libc__wtempnam);
DEFINE_PUBLIC_ALIAS(DOS$_wtmpnam_s, libd__wtmpnam_s);
DEFINE_PUBLIC_ALIAS(_wtmpnam_s, libc__wtmpnam_s);
DEFINE_PUBLIC_ALIAS(DOS$_wtmpnam, libd__wtmpnam);
DEFINE_PUBLIC_ALIAS(_wtmpnam, libc__wtmpnam);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WSTDIO_C */
