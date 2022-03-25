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
#ifndef GUARD_LIBC_USER_CORECRT_WCONIO_C
#define GUARD_LIBC_USER_CORECRT_WCONIO_C 1

#include "../api.h"
/**/

#include "corecrt_wconio.h"

DECL_BEGIN

/*[[[head:libd___conio_common_vcwscanf,hash:CRC-32=0xf8bcf677]]]*/
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_LIBC_C16SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBDCALL libd___conio_common_vcwscanf)(uint64_t options,
                                                   char16_t const *format,
                                                   locale_t locale,
                                                   va_list args)
/*[[[body:libd___conio_common_vcwscanf]]]*/
/*AUTO*/{
	(void)options;
	(void)format;
	(void)locale;
	(void)args;
	CRT_UNIMPLEMENTEDF("DOS$__conio_common_vcwscanf(%" PRIx64 ", %p, %p, %p)", options, format, locale, args); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libd___conio_common_vcwscanf]]]*/

/*[[[head:libc___conio_common_vcwscanf,hash:CRC-32=0x40127be0]]]*/
INTERN ATTR_SECTION(".text.crt.dos.wchar.conio") WUNUSED ATTR_LIBC_C32SCANF(2, 0) NONNULL((2)) __STDC_INT_AS_SSIZE_T
NOTHROW_NCX(LIBKCALL libc___conio_common_vcwscanf)(uint64_t options,
                                                   char32_t const *format,
                                                   locale_t locale,
                                                   va_list args)
/*[[[body:libc___conio_common_vcwscanf]]]*/
/*AUTO*/{
	(void)options;
	(void)format;
	(void)locale;
	(void)args;
	CRT_UNIMPLEMENTEDF("__conio_common_vcwscanf(%" PRIx64 ", %p, %p, %p)", options, format, locale, args); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc___conio_common_vcwscanf]]]*/

/*[[[start:exports,hash:CRC-32=0x5bd6b6c0]]]*/
DEFINE_PUBLIC_ALIAS(DOS$__conio_common_vcwscanf, libd___conio_common_vcwscanf);
DEFINE_PUBLIC_ALIAS(__conio_common_vcwscanf, libc___conio_common_vcwscanf);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WCONIO_C */
