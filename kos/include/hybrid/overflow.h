/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __GUARD_HYBRID_OVERFLOW_H
#define __GUARD_HYBRID_OVERFLOW_H 1

#include <__stdinc.h>
#include "__overflow.h"

/* @return: true:  Overflow  occurred (unlikely; `*res' contains the truncated result)
 *                 Overflow here means that the finite result stored in `*res' doesn't
 *                 match a value that would have been produced when infinite precision
 *                 was available.
 *                 e.g.: `UINT_MAX + 42u' and `11u - 19u' overflow, but `32u + 42u'
 *                       or `11 - 19' don't
 * @return: false: `*res' contains the correct result. */
#define OVERFLOW_UADD __hybrid_overflow_uadd
#define OVERFLOW_SADD __hybrid_overflow_sadd
#define OVERFLOW_USUB __hybrid_overflow_usub
#define OVERFLOW_SSUB __hybrid_overflow_ssub
#define OVERFLOW_UMUL __hybrid_overflow_umul
#define OVERFLOW_SMUL __hybrid_overflow_smul

/* >> bool OVERFLOW_SNEG(T x, T *p_result);
 * >> bool OVERFLOW_SNEG_P2N(T x, T *p_result);    -- @assume(x >= 0)
 * >> bool OVERFLOW_SNEG_N2P(T x, T *p_result);    -- @assume(x < 0)
 * Do the operation `*p_result = -x'
 * @return: true:  Overflow happened
 * @return: false: Overflow didn't happen */
#define OVERFLOW_SENG     __hybrid_overflow_sneg
#define OVERFLOW_SENG_P2N __hybrid_overflow_sneg_p2n
#define OVERFLOW_SENG_N2P __hybrid_overflow_sneg_n2p

#endif /* !__GUARD_HYBRID_OVERFLOW_H */
