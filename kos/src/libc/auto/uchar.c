/* HASH CRC-32:0xee37bf9e */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_UCHAR_C
#define GUARD_LIBC_AUTO_UCHAR_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "uchar.h"
#include "unicode.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <parts/errno.h>
__LOCAL_LIBC_DATA(mbrtoc16_mbs) __mbstate_t mbrtoc16_mbs = __MBSTATE_INIT;
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unicode.mbr.mbrtoc16") size_t
NOTHROW_NCX(LIBCCALL libc_mbrtoc16)(char16_t *__restrict pc16,
                                    char const *__restrict s,
                                    size_t n,
                                    __mbstate_t *__restrict mbs) {
#line 96 "kos/src/libc/magic/uchar.c"
	char16_t c16;
	size_t result;
	if (!s) {
		if (mbs)
			mbs->__word = 0;
		return 0;
	}
	if (!mbs)
		mbs = &mbrtoc16_mbs;
	if (!pc16)
		pc16 = &c16;
	result = libc_unicode_c8toc16(pc16, s, n, mbs);
#ifdef __EILSEQ
	if unlikely(result == (size_t)-1)
		__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
	return result;
}

#include <parts/errno.h>

#include <bits/mbstate.h>
__LOCAL_LIBC_DATA(mbrtoc32_mbs) __mbstate_t mbrtoc32_mbs = __MBSTATE_INIT;
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unicode.mbr.mbrtoc32") size_t
NOTHROW_NCX(LIBCCALL libc_mbrtoc32)(char32_t *__restrict pc32,
                                    char const *__restrict s,
                                    size_t n,
                                    __mbstate_t *__restrict mbs) {
#line 125 "kos/src/libc/magic/uchar.c"
	char32_t c32;
	size_t result;
	if (!s) {
		if (mbs)
			mbs->__word = 0;
		return 0;
	}
	if (!mbs)
		mbs = &mbrtoc32_mbs;
	if (!pc32)
		pc32 = &c32;
	result = libc_unicode_c8toc32(pc32, s, n, mbs);
#ifdef __EILSEQ
	if unlikely(result == (size_t)-1)
		__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
	return result;
}

#include <parts/errno.h>

#include <bits/mbstate.h>
__LOCAL_LIBC_DATA(c16rtomb_mbs) __mbstate_t c16rtomb_mbs = __MBSTATE_INIT;
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unicode.mbr.c16rtomb") size_t
NOTHROW_NCX(LIBCCALL libc_c16rtomb)(char *__restrict s,
                                    char16_t c16,
                                    __mbstate_t *__restrict mbs) {
#line 151 "kos/src/libc/magic/uchar.c"
	char32_t ch32;
	if (!s) {
		if (mbs)
			mbs->__word = __MBSTATE_TYPE_EMPTY;
		return 1;
	}
	if (!mbs)
		mbs = &c16rtomb_mbs;
	switch (mbs->__word & __MBSTATE_TYPE_MASK) {
	case __MBSTATE_TYPE_EMPTY:
		if (c16 >= 0xd800 && c16 <= 0xdbff) {
			/* High surrogate (set the MBS to accept a low surrogate as the next character) */
			mbs->__word = __MBSTATE_TYPE_UTF16_LO | ((c16 - 0xd800) & 0x3ff);
			return 0;
		}
		ch32 = (char32_t)c16;
		break;
	case __MBSTATE_TYPE_UTF16_LO:
		/* c16 should be a low surrogate */
		if unlikely(!(c16 >= 0xdc00 && c16 <= 0xdfff))
			goto error_ilseq;
		ch32 = ((mbs->__word & 0x000003ff) << 10) + 0x10000 + (c16 - 0xdc00);
		mbs->__word = __MBSTATE_TYPE_EMPTY;
		break;

	default:
error_ilseq:
#ifdef __EILSEQ
		__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
		return (size_t)-1;
	}
	/* Write a utf-8 sequence */
	return (size_t)(libc_unicode_writeutf8(s, ch32) - s);
}

#include <parts/errno.h>

#include <bits/mbstate.h>
INTERN ATTR_WEAK ATTR_SECTION(".text.crt.unicode.mbr.c32rtomb") size_t
NOTHROW_NCX(LIBCCALL libc_c32rtomb)(char *__restrict s,
                                    char32_t c32,
                                    __mbstate_t *__restrict mbs) {
#line 191 "kos/src/libc/magic/uchar.c"
	if (!s) {
		if (mbs)
			mbs->__word = __MBSTATE_TYPE_EMPTY;
		return 1;
	}
	if unlikely((c32 > 0x10ffff) || (mbs && (mbs->__word & __MBSTATE_TYPE_MASK) != __MBSTATE_TYPE_EMPTY)) {
#ifdef __EILSEQ
		__libc_seterrno(__EILSEQ);
#endif /* __EILSEQ */
		return (size_t)-1;
	}
	/* Write a utf-8 sequence */
	return (size_t)(libc_unicode_writeutf8(s, c32) - s);
}

#endif /* !__KERNEL__ */
#ifndef __KERNEL__
DEFINE_PUBLIC_WEAK_ALIAS(mbrtoc16, libc_mbrtoc16);
DEFINE_PUBLIC_WEAK_ALIAS(mbrtoc32, libc_mbrtoc32);
DEFINE_PUBLIC_WEAK_ALIAS(c16rtomb, libc_c16rtomb);
DEFINE_PUBLIC_WEAK_ALIAS(c32rtomb, libc_c32rtomb);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_UCHAR_C */
