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
#ifndef _BITS_CRT_UNICODE_H
#define _BITS_CRT_UNICODE_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
#ifdef __CRT_KOS
__DECL_BEGIN

#define __UNICODE_ISCNTRL  0x0001                                  /* iscntrl: 00-1F, 7F */
#define __UNICODE_ISCTAB   0x0002                                  /*          09 */
#define __UNICODE_ISXTAB   0x0004                                  /*          0B-0C */
#define __UNICODE_ISTAB    (__UNICODE_ISCTAB | __UNICODE_ISXTAB)   /*          09, 0B-0C */
#define __UNICODE_ISWHITE  0x0008                                  /*          20 */
#define __UNICODE_ISEMPTY  (__UNICODE_ISTAB | __UNICODE_ISWHITE)   /*          09, 0B-0C, 20 */
#define __UNICODE_ISLF     0x0010                                  /*          0A, 0D */
#define __UNICODE_ISSPACE  (__UNICODE_ISEMPTY | __UNICODE_ISLF)    /* isspace: 09-0D, 20 */
#define __UNICODE_ISLOWER  0x0020                                  /* islower: 61-7A */
#define __UNICODE_ISUPPER  0x0040                                  /* isupper: 41-5A */
#define __UNICODE_ISXALPHA 0x0080                                  /* <Misc alpha characters> (doesn't appear in ASCII) */
#define __UNICODE_ISALPHA  (__UNICODE_ISLOWER | __UNICODE_ISUPPER | __UNICODE_ISTITLE | __UNICODE_ISXALPHA) /* isalpha: 41-5A, 61-7A */
#define __UNICODE_ISDIGIT  0x0100                                  /*          30-39 */
#define __UNICODE_ISHEX    0x0200                                  /*          41-46, 61-66 */
#define __UNICODE_ISXDIGIT (__UNICODE_ISDIGIT | __UNICODE_ISHEX)   /* isxdigit: 30-39, 41-46, 61-66 */
#define __UNICODE_ISALNUM  (__UNICODE_ISALPHA | __UNICODE_ISDIGIT) /* isalnum: 30-39, 41-5A, 61-7A */
#define __UNICODE_ISPUNCT  0x0400                                  /* ispunct: 21-2F, 3A-40, 5B-60, 7B-7E */
#define __UNICODE_ISGRAPH  (__UNICODE_ISPUNCT | __UNICODE_ISALNUM | __UNICODE_ISXNUMERIC) /* isgraph: 21-7E */
#define __UNICODE_ISPRINT  (__UNICODE_ISWHITE | __UNICODE_ISGRAPH) /* isprint: 20-7E */
#define __UNICODE_ISBLANK  (__UNICODE_ISCTAB | __UNICODE_ISWHITE)  /* isblank: 09, 20 */
/* Extended unicode flags. */
#define __UNICODE_ISTITLE    0x0800 /* Is title cased */
#define __UNICODE_ISXNUMERIC 0x1000 /* + all other characters that contain numbers, such as ² */
#define __UNICODE_ISNUMERIC  (__UNICODE_ISDIGIT | __UNICODE_ISXNUMERIC) /* All numeric characters */
#define __UNICODE_ISSYMSTRT  0x2000 /* Symbol start character */
#define __UNICODE_ISSYMCONT  0x4000 /* Symbol continue character */
/*efine __UNICODE_IS         0x8000  * ... */

/* When `__ut_digit_idx < __UNICODE_DIGIT_IDENTITY_COUNT', then the associated unicode
 * character  has a digit value equal to  `__ut_digit_idx' (iow: the digit decode step
 * can be skipped, since `__ut_digit_idx' _is_ the digit value) */
#define __UNICODE_DIGIT_IDENTITY_COUNT 51

struct __unitraits {
	__UINT16_TYPE__ const __ut_flags;     /* Character flags (Set of `__UNICODE_IS*') */
	__UINT8_TYPE__  const __ut_digit_idx; /* Digit/decimal extension index, or `0xff'.
	                                       * When `< __UNICODE_DIGIT_IDENTITY_COUNT', this _is_ the digit value. */
	__UINT8_TYPE__  const __ut_fold_idx;  /* Unicode fold extension index, or `0xff'. */
	__INT32_TYPE__  const __ut_lower;     /* Delta added to the character to convert it to lowercase, or 0. */
	__INT32_TYPE__  const __ut_upper;     /* Delta added to the character to convert it to uppercase, or 0. */
	__INT32_TYPE__  const __ut_title;     /* Delta added to the character to convert it to titlecase, or 0. */
};

__DECL_END
#endif /* __CRT_KOS */
#endif /* __CC__ */

#endif /* !_BITS_CRT_UNICODE_H */
