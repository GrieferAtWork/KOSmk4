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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBEMU86_EFLAGS_H
#define _LIBEMU86_EFLAGS_H 1

#include "api.h"

#include <bits/types.h>
#include <i386-kos/asm/cpu-flags.h>

/* Helpers for calculating %eflags */
#ifdef __CC__
__DECL_BEGIN


#define emu86_geteflags_SFb(value) ((__int8_t)(value) < 0 ? EFLAGS_SF : 0)
#define emu86_geteflags_SFw(value) ((__int16_t)(value) < 0 ? EFLAGS_SF : 0)
#define emu86_geteflags_SFl(value) ((__int32_t)(value) < 0 ? EFLAGS_SF : 0)

#define emu86_geteflags_ZFb(value) ((__uint8_t)(value) == 0 ? EFLAGS_ZF : 0)
#define emu86_geteflags_ZFw(value) ((__uint16_t)(value) == 0 ? EFLAGS_ZF : 0)
#define emu86_geteflags_ZFl(value) ((__uint32_t)(value) == 0 ? EFLAGS_ZF : 0)

__LOCAL __uint32_t LIBEMU86_CC emu86_geteflags_PFb(__uint8_t value) {
	/* == POPCOUNT(value) & 1 */
	value ^= value >> 4;
	value ^= value >> 2;
	value ^= value >> 1;
	return (value & 1) ? EFLAGS_PF : 0;
}

__LOCAL __uint32_t LIBEMU86_CC emu86_geteflags_PFw(__uint16_t value) {
	/* == POPCOUNT(value) & 1 */
	value ^= value >> 8;
	value ^= value >> 4;
	value ^= value >> 2;
	value ^= value >> 1;
	return (value & 1) ? EFLAGS_PF : 0;
}

__LOCAL __uint32_t LIBEMU86_CC emu86_geteflags_PFl(__uint32_t value) {
	/* == POPCOUNT(value) & 1 */
	value ^= value >> 16;
	value ^= value >> 8;
	value ^= value >> 4;
	value ^= value >> 2;
	value ^= value >> 1;
	return (value & 1) ? EFLAGS_PF : 0;
}

#if CONFIG_LIBEMU86_WANT_64BIT
#define emu86_geteflags_SFq(value) ((__int64_t)(value) < 0 ? EFLAGS_SF : 0)
#define emu86_geteflags_ZFq(value) ((__uint64_t)(value) == 0 ? EFLAGS_ZF : 0)
__LOCAL __uint32_t LIBEMU86_CC emu86_geteflags_PFq(__uint64_t value) {
	/* == POPCOUNT(value) & 1 */
	value ^= value >> 32;
	value ^= value >> 16;
	value ^= value >> 8;
	value ^= value >> 4;
	value ^= value >> 2;
	value ^= value >> 1;
	return (value & 1) ? EFLAGS_PF : 0;
}
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

/* Return a set of `EFLAGS_(SF|ZF|PF)' */
#define emu86_geteflags_testb(value) (emu86_geteflags_SFb(value) | emu86_geteflags_ZFb(value) | emu86_geteflags_PFb(value))
#define emu86_geteflags_testw(value) (emu86_geteflags_SFw(value) | emu86_geteflags_ZFw(value) | emu86_geteflags_PFw(value))
#define emu86_geteflags_testl(value) (emu86_geteflags_SFl(value) | emu86_geteflags_ZFl(value) | emu86_geteflags_PFl(value))
#if CONFIG_LIBEMU86_WANT_64BIT
#define emu86_geteflags_testq(value) (emu86_geteflags_SFq(value) | emu86_geteflags_ZFq(value) | emu86_geteflags_PFq(value))
#endif /* CONFIG_LIBEMU86_WANT_64BIT */

__DECL_END
#endif /* __CC__ */


#endif /* !_LIBEMU86_EFLAGS_H */
