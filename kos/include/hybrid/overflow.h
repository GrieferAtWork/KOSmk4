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
#ifndef __GUARD_HYBRID_OVERFLOW_H
#define __GUARD_HYBRID_OVERFLOW_H 1

#include <__stdinc.h>
#include "__overflow.h"

/* @return: true:  Overflow occurred (unlikely; `*res' remains unmodified)
 *                 Overflow  here  means  that  the  finite  result stored
 *                 in  `*res'  doesn't  match  a  value  that  would  have
 *                 been produced  when infinite  precision was  available.
 *                 e.g.: `UINT_MAX + 42u' and `11u - 19u' overflow,
 *                       but   `32u + 42u'   or   `11 - 19'   don't
 * @return: false: `*res' contains the correct result. */
#ifdef __INTELLISENSE__
#define OVERFLOW_UADD __hybrid_overflow_uadd
#define OVERFLOW_SADD __hybrid_overflow_sadd
#define OVERFLOW_USUB __hybrid_overflow_usub
#define OVERFLOW_SSUB __hybrid_overflow_ssub
#define OVERFLOW_UMUL __hybrid_overflow_umul
#define OVERFLOW_SMUL __hybrid_overflow_smul
#else /* __INTELLISENSE__ */
#define OVERFLOW_UADD(x, y, res) __hybrid_overflow_uadd(x, y, res)
#define OVERFLOW_SADD(x, y, res) __hybrid_overflow_sadd(x, y, res)
#define OVERFLOW_USUB(x, y, res) __hybrid_overflow_usub(x, y, res)
#define OVERFLOW_SSUB(x, y, res) __hybrid_overflow_ssub(x, y, res)
#define OVERFLOW_UMUL(x, y, res) __hybrid_overflow_umul(x, y, res)
#define OVERFLOW_SMUL(x, y, res) __hybrid_overflow_smul(x, y, res)
#endif /* !__INTELLISENSE__ */


#endif /* !__GUARD_HYBRID_OVERFLOW_H */
