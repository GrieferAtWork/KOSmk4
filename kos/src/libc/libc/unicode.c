/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_LIBC_UNICODE_C
#define GUARD_LIBC_LIBC_UNICODE_C 1

/* Keep this one the first */
#include "../api.h"
/**/

#include <unicode.h>

DECL_BEGIN

#ifndef __UNICODE_FPRINT
#define __UNICODE_FPRINT   0x0001 /* The character is printable, or SPC (` '). */
#define __UNICODE_FALPHA   0x0002 /* The character is alphabetic. */
#define __UNICODE_FSPACE   0x0004 /* The character is a space-character. */
#define __UNICODE_FLF      0x0008 /* Line-feed/line-break character. */
#define __UNICODE_FLOWER   0x0010 /* Lower-case. */
#define __UNICODE_FUPPER   0x0020 /* Upper-case. */
#define __UNICODE_FTITLE   0x0040 /* Title-case. */
#define __UNICODE_FCNTRL   0x0080 /* Control character. */
#define __UNICODE_FDIGIT   0x0100 /* The character is a digit. e.g.: `²' (sqare; `ut_digit' is `2') */
#define __UNICODE_FDECIMAL 0x0200 /* The character is a decimal. e.g: `5' (ascii; `ut_digit' is `5') */
#define __UNICODE_FSYMSTRT 0x0400 /* The character can be used as the start of an identifier. */
#define __UNICODE_FSYMCONT 0x0800 /* The character can be used to continue an identifier. */
/*      __UNICODE_F        0x1000 */
/*      __UNICODE_F        0x2000 */
/*      __UNICODE_F        0x4000 */
/*      __UNICODE_F        0x8000 */
struct __unitraits {
	__UINT16_TYPE__ const __ut_flags; /* Character flags (Set of `__UNICODE_F*') */
	__UINT8_TYPE__  const __ut_digit; /* Digit/decimal value (`unicode_isnumeric'), or 0. */
	__UINT8_TYPE__  const __ut_fold;  /* Unicode fold extension index, or `0xff'. */
	__INT32_TYPE__  const __ut_lower; /* Delta added to the character to convert it to lowercase, or 0. */
	__INT32_TYPE__  const __ut_upper; /* Delta added to the character to convert it to uppercase, or 0. */
	__INT32_TYPE__  const __ut_title; /* Delta added to the character to convert it to titlecase, or 0. */
};
#endif /* !__UNICODE_FPRINT */

#include "unicode_db.h"
DEFINE_PUBLIC_ALIAS(__unicode_asciiflags, libc___unicode_asciiflags);


PRIVATE ATTR_SECTION(".rodata.crt.unicode.UTF.default_traits")
struct __unitraits const default_traits = { 0x0, 0, 0xff, 0, 0, 0 };
INTERN ATTR_SECTION(".text.crt.unicode.UTF.__unicode_descriptor")
ATTR_RETNONNULL ATTR_CONST struct __unitraits *
NOTHROW(LIBCCALL libc___unicode_descriptor)(char32_t ch) {
	if likely(ch < UNICODE_COUNT_VALID)
		return (struct __unitraits *)&UNICODE_DESCRIPTOR(ch);
	return (struct __unitraits *)&default_traits;
}

INTERN ATTR_SECTION(".text.crt.unicode.UTF.unicode_fold")
ATTR_RETNONNULL NONNULL((2)) char32_t *
NOTHROW_NCX(LIBCCALL libc_unicode_fold)(char32_t ch,
                                        char32_t buf[UNICODE_FOLDED_MAX]) {
	struct __unitraits *trt;
	struct unifold const *fold;
	trt = libc___unicode_descriptor(ch);
	if (trt->__ut_fold == 0xff) {
		buf[0] = unicode_tolower(ch);
		return buf + 1;
	}
	fold   = &fold_descriptors[trt->__ut_fold];
	buf[0] = fold->uf_repl[0];
	if ((buf[1] = fold->uf_repl[1]) == 0)
		return buf + 1;
	if ((buf[2] = fold->uf_repl[2]) == 0)
		return buf + 2;
	return buf + 3;
}



DEFINE_PUBLIC_ALIAS(unicode_fold, libc_unicode_fold);
DEFINE_PUBLIC_ALIAS(__unicode_descriptor, libc___unicode_descriptor);

DECL_END

#endif /* !GUARD_LIBC_LIBC_UNICODE_C */
