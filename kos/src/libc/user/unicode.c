/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_UNICODE_C
#define GUARD_LIBC_USER_UNICODE_C 1

#include "../api.h"
/**/

#include "unicode.h"

DECL_BEGIN

typedef union {
#define _UNIDIGIT_ISFRAC     UINT64_C(0x8000000000000000)
#define _UNIDIGIT_WHOLE_MASK UINT64_C(0x7fffffffffffffff)
	uint64_t ud_whole;   /* Whole number (masked by `_UNIDIGIT_WHOLE_MASK') */
	uint32_t ud_frac[2]; /* Fraction numerator/denominator */
#define unidigit_iswhole(self)             (!((self)->ud_whole & _UNIDIGIT_ISFRAC))
#define unidigit_getwhole(self)            ((self)->ud_whole & _UNIDIGIT_WHOLE_MASK)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define unidigit_getfrac_numerator(self)   ((int32_t)((self)->ud_frac[0]))
#define unidigit_getfrac_denominator(self) ((int32_t)((self)->ud_frac[1] & UINT32_C(0x7fffffff)))
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#define unidigit_getfrac_numerator(self)   ((int32_t)((self)->ud_frac[0] & UINT32_C(0x7fffffff)))
#define unidigit_getfrac_denominator(self) ((int32_t)((self)->ud_frac[1]))
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
} unidigit_t;
#define D_INT(value) { .ud_whole = UINT64_C(value) }
#define D_FRAC(a, b) { .ud_frac = { (uint32_t)(int32_t)(a), (uint32_t)(int32_t)(b) } }


#ifdef __INTELLISENSE__
#define UNICODE_FOLD_MAXLEN 3
#define UNICODE_FOLD_COUNT  42
struct unifold {
	uint16_t uf_repl[3];
};
PRIVATE struct unifold const unicode_fold_descriptors[UNICODE_FOLD_COUNT];
#define UNICODE_DIGIT_COUNT 42
PRIVATE unidigit_t const unicode_digits[UNICODE_DIGIT_COUNT];
#define UNICODE_DESCRIPTOR_COUNT 42
PRIVATE struct __unitraits const unicode_descriptors[UNICODE_DESCRIPTOR_COUNT];
#define UNICODE_COUNT                0x10fffe
#define UNICODE_COUNT_VALID          0x110000
#define UNICODE_SHIFT                6
#define UNICODE_TAB1_MASK            0x3f
#define UNICODE_DESCRIPTOR_INDEX(ch) unicode_tab2[(unicode_tab1[(uint32_t)(ch) >> 6] << 6) + ((uint8_t)(ch) & 0x3f)]
#define UNICODE_DESCRIPTOR(ch)       unicode_descriptors[UNICODE_DESCRIPTOR_INDEX(ch)]
#define unicode_default_descriptor   unicode_descriptors[0]
PRIVATE uint16_t const unicode_tab1[42];
PRIVATE uint16_t const unicode_tab2[42];
INTERN_CONST uint16_t const libc___unicode_latin1flags[256];
#else /* __INTELLISENSE__ */
#include "unicode/db.dat"
#endif /* !__INTELLISENSE__ */

STATIC_ASSERT_MSG(UNICODE_FOLD_MAXLEN <= UNICODE_FOLDED_MAX, "UNICODE_FOLDED_MAX must be increased!");

/* Export the latin-1 flags matrix */
DEFINE_PUBLIC_ALIAS(__unicode_latin1flags, libc___unicode_latin1flags);

/*[[[head:libc___unicode_descriptor,hash:CRC-32=0xf10a2df2]]]*/
/* Return the internal descriptor for the given `ch' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_CONST ATTR_RETNONNULL struct __unitraits const *
NOTHROW(LIBCCALL libc___unicode_descriptor)(char32_t ch)
/*[[[body:libc___unicode_descriptor]]]*/
{
	if likely(ch < UNICODE_COUNT_VALID)
		return &UNICODE_DESCRIPTOR(ch);
	return &unicode_default_descriptor;
}
/*[[[end:libc___unicode_descriptor]]]*/

/*[[[head:libc___unicode_descriptor_digit,hash:CRC-32=0xd38c907e]]]*/
/* Return the integer constant associated with a given digit index
 * Returns `0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_CONST uint8_t
NOTHROW(LIBCCALL libc___unicode_descriptor_digit)(uint8_t digit_idx)
/*[[[body:libc___unicode_descriptor_digit]]]*/
{
	unidigit_t const *digit;
	if unlikely(digit_idx >= UNICODE_DIGIT_COUNT)
		return 0;
	digit = &unicode_digits[digit_idx];
	if likely(unidigit_iswhole(digit))
		return (uint8_t)unidigit_getwhole(digit);
	return (uint8_t)(unidigit_getfrac_numerator(digit) /
	                 unidigit_getfrac_denominator(digit));
}
/*[[[end:libc___unicode_descriptor_digit]]]*/

/*[[[head:libc___unicode_descriptor_digit64,hash:CRC-32=0xc379838e]]]*/
/* Return the integer constant associated with a given digit index
 * Returns `0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_CONST uint64_t
NOTHROW(LIBCCALL libc___unicode_descriptor_digit64)(uint8_t digit_idx)
/*[[[body:libc___unicode_descriptor_digit64]]]*/
{
	unidigit_t const *digit;
	if unlikely(digit_idx >= UNICODE_DIGIT_COUNT)
		return 0;
	digit = &unicode_digits[digit_idx];
	if likely(unidigit_iswhole(digit))
		return (uint64_t)unidigit_getwhole(digit);
	return (uint64_t)(unidigit_getfrac_numerator(digit) /
	                  unidigit_getfrac_denominator(digit));
}
/*[[[end:libc___unicode_descriptor_digit64]]]*/

/*[[[head:libc___unicode_descriptor_digitd,hash:CRC-32=0x681d7284]]]*/
/* Return the floating-point constant associated with a given digit index
 * Returns `0.0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_CONST double
NOTHROW(LIBCCALL libc___unicode_descriptor_digitd)(uint8_t digit_idx)
/*[[[body:libc___unicode_descriptor_digitd]]]*/
{
	unidigit_t const *digit;
	if unlikely(digit_idx >= UNICODE_DIGIT_COUNT)
		return 0.0;
	digit = &unicode_digits[digit_idx];
	if likely(unidigit_iswhole(digit))
		return (double)unidigit_getwhole(digit);
	return (double)(unidigit_getfrac_numerator(digit) /
	                unidigit_getfrac_denominator(digit));
}
/*[[[end:libc___unicode_descriptor_digitd]]]*/

/*[[[head:libc___unicode_descriptor_digitld,hash:CRC-32=0x9a7e5dee]]]*/
/* Return the floating-point constant associated with a given digit index
 * Returns `0.0' if the given index is invalid
 * @param: digit_idx: As read from `__unitraits::__ut_digit_idx' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_CONST __LONGDOUBLE
NOTHROW(LIBCCALL libc___unicode_descriptor_digitld)(uint8_t digit_idx)
/*[[[body:libc___unicode_descriptor_digitld]]]*/
{
	unidigit_t const *digit;
	if unlikely(digit_idx >= UNICODE_DIGIT_COUNT)
		return 0.0L;
	digit = &unicode_digits[digit_idx];
	if likely(unidigit_iswhole(digit))
		return (__LONGDOUBLE)unidigit_getwhole(digit);
	return (__LONGDOUBLE)(unidigit_getfrac_numerator(digit) /
	                      unidigit_getfrac_denominator(digit));
}
/*[[[end:libc___unicode_descriptor_digitld]]]*/

#include <syslog.h>

/*[[[head:libc_unicode_fold,hash:CRC-32=0x6e2a0f6c]]]*/
/* Fold the given unicode character `ch' */
INTERN ATTR_SECTION(".text.crt.unicode.UTF") ATTR_RETNONNULL NONNULL((2)) char32_t *
NOTHROW_NCX(LIBCCALL libc_unicode_fold)(char32_t ch,
                                        char32_t buf[3])
/*[[[body:libc_unicode_fold]]]*/
{
	struct __unitraits const *trt;
	struct unifold const *fold;
	trt = libc___unicode_descriptor(ch);
	syslog(LOG_DEBUG, "libc_unicode_fold(%#I32x)\n", ch);
	syslog(LOG_DEBUG, "	trt->__ut_fold_idx = %#I8x\n", trt->__ut_fold_idx);
	if (trt->__ut_fold_idx >= UNICODE_FOLD_COUNT) {
		buf[0] = unicode_tolower(ch);
		return buf + 1;
	}
	fold   = &unicode_fold_descriptors[trt->__ut_fold_idx];
	buf[0] = fold->uf_repl[0];
	if ((buf[1] = fold->uf_repl[1]) == 0)
		return buf + 1;
	if ((buf[2] = fold->uf_repl[2]) == 0)
		return buf + 2;
	return buf + 3;
}
/*[[[end:libc_unicode_fold]]]*/

/*[[[start:exports,hash:CRC-32=0xccdb6d5b]]]*/
DEFINE_PUBLIC_ALIAS(__unicode_descriptor, libc___unicode_descriptor);
DEFINE_PUBLIC_ALIAS(__unicode_descriptor_digit, libc___unicode_descriptor_digit);
DEFINE_PUBLIC_ALIAS(__unicode_descriptor_digit64, libc___unicode_descriptor_digit64);
DEFINE_PUBLIC_ALIAS(__unicode_descriptor_digitd, libc___unicode_descriptor_digitd);
DEFINE_PUBLIC_ALIAS(__unicode_descriptor_digitld, libc___unicode_descriptor_digitld);
DEFINE_PUBLIC_ALIAS(unicode_fold, libc_unicode_fold);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_UNICODE_C */
