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
#ifndef _LIBVM86_INTRIN86_H
#define _LIBVM86_INTRIN86_H 1

#include <hybrid/bit.h>
#include <hybrid/host.h>

#include <bits/types.h>

#include "api.h"
#include "emulator.h"

#if defined(__i386__) || defined(__x86_64__)
#include <asm/cpu-flags.h>
#include <asm/intrin-arith.h>
#include <asm/intrin.h>
#endif

__DECL_BEGIN

#if defined(__INTELLISENSE__) && 1
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_testb(__uint8_t value);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_testw(__uint16_t value);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_testl(__uint32_t value);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_addb(__uint8_t x, __uint8_t y);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_addw(__uint16_t x, __uint16_t y);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_addl(__uint32_t x, __uint32_t y);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_cmpb(__uint8_t x, __uint8_t y);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_cmpw(__uint16_t x, __uint16_t y);
__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_cmpl(__uint32_t x, __uint32_t y);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_adcb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_adcw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_adcl(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_sbbb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_sbbw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_sbbl(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_rclb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_rclw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_rcll(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_rcrb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_rcrw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_rcrl(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_rolb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_rolw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_roll(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_rorb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_rorw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_rorl(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_shlb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_shlw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_shll(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_shrb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_shrw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_shrl(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint8_t LIBVM86_CC f_sarb(__uint8_t  x, __uint8_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint16_t LIBVM86_CC f_sarw(__uint16_t x, __uint16_t y, /*in|out*/ __uint16_t *__restrict pflags);
__LOCAL __ATTR_NONNULL((3)) __uint32_t LIBVM86_CC f_sarl(__uint32_t x, __uint32_t y, /*in|out*/ __uint16_t *__restrict pflags);
#elif (defined(__i386__) || defined(__x86_64__)) && 1
#define f_testb(x)   ((__uint16_t)__testb(x, x))
#define f_testw(x)   ((__uint16_t)__testw(x, x))
#define f_testl(x)   ((__uint16_t)__testl(x, x))
#define f_addb(x, y) ((__uint16_t)__addb_ff(x, y))
#define f_addw(x, y) ((__uint16_t)__addw_ff(x, y))
#define f_addl(x, y) ((__uint16_t)__addl_ff(x, y))
#define f_cmpb(x, y) ((__uint16_t)__cmpb(x, y))
#define f_cmpw(x, y) ((__uint16_t)__cmpw(x, y))
#define f_cmpl(x, y) ((__uint16_t)__cmpl(x, y))

#define LIBVM86_DEFINE_FLAG_PROXY(T, name, cc_mask)     \
	__LOCAL __ATTR_NONNULL((3)) T LIBVM86_CC            \
	f_##name(T x, T y, __uint16_t *__restrict pflags) { \
		T result;                                       \
		__REGISTER_TYPE__ real_flags;                   \
		real_flags = *pflags & (cc_mask);               \
		real_flags |= __rdflags() & ~(cc_mask);         \
		result = __##name(x, y, &real_flags);           \
		*pflags &= ~(cc_mask);                          \
		*pflags |= real_flags & (cc_mask);              \
		return result;                                  \
	}
#define LIBVM86_DEFINE_FLAG_PROXY_ROT(T, name, cc_mask)                \
	__LOCAL __ATTR_NONNULL((3)) T LIBVM86_CC                           \
	f_##name(T x, unsigned int shift, __uint16_t *__restrict pflags) { \
		T result;                                                      \
		__REGISTER_TYPE__ real_flags;                                  \
		if (!shift)                                                    \
			return x;                                                  \
		real_flags = *pflags & (cc_mask);                              \
		real_flags |= __rdflags() & ~(cc_mask);                        \
		result = __##name(x, shift, &real_flags);                      \
		*pflags &= ~(cc_mask);                                         \
		*pflags |= real_flags & (cc_mask);                             \
		return result;                                                 \
	}
#define LIBVM86_DEFINE_FLAG_PROXY_ROT_F(T, name, cc_mask)              \
	__LOCAL __ATTR_NONNULL((3)) T LIBVM86_CC                           \
	f_##name(T x, unsigned int shift, __uint16_t *__restrict pflags) { \
		T result;                                                      \
		__REGISTER_TYPE__ real_flags;                                  \
		if (!shift)                                                    \
			return x;                                                  \
		result = __##name##_f(x, shift, &real_flags);                  \
		*pflags &= ~(cc_mask);                                         \
		*pflags |= real_flags & (cc_mask);                             \
		return result;                                                 \
	}

LIBVM86_DEFINE_FLAG_PROXY(__uint8_t,adcb,EFLAGS_OF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_AF|EFLAGS_PF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY(__uint16_t,adcw,EFLAGS_OF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_AF|EFLAGS_PF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY(__uint32_t,adcl,EFLAGS_OF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_AF|EFLAGS_PF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY(__uint8_t,sbbb,EFLAGS_OF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_AF|EFLAGS_PF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY(__uint16_t,sbbw,EFLAGS_OF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_AF|EFLAGS_PF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY(__uint32_t,sbbl,EFLAGS_OF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_AF|EFLAGS_PF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT(__uint8_t,rclb,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT(__uint16_t,rclw,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT(__uint32_t,rcll,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT(__uint8_t,rcrb,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT(__uint16_t,rcrw,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT(__uint32_t,rcrl,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint8_t,rolb,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint16_t,rolw,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint32_t,roll,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint8_t,rorb,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint16_t,rorw,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint32_t,rorl,EFLAGS_OF|EFLAGS_CF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint8_t,shlb,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint16_t,shlw,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint32_t,shll,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint8_t,shrb,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint16_t,shrw,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint32_t,shrl,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint8_t,sarb,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint16_t,sarw,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
LIBVM86_DEFINE_FLAG_PROXY_ROT_F(__uint32_t,sarl,EFLAGS_OF|EFLAGS_CF|EFLAGS_SF|EFLAGS_ZF|EFLAGS_PF)
#undef LIBVM86_DEFINE_FLAG_PROXY_ROT_F
#undef LIBVM86_DEFINE_FLAG_PROXY_ROT
#undef LIBVM86_DEFINE_FLAG_PROXY

#else

__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_testb(__uint8_t value) {
	__uint16_t result = 0;
	if (!value)
		result |= ZF;
	else {
		if (value & 0x80)
			result |= SF;
		if (PARITY(value))
			result |= PF;
	}
	return result;
}

__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_testw(__uint16_t value) {
	__uint16_t result = 0;
	if (!value)
		result |= ZF;
	else {
		if (value & 0x8000)
			result |= SF;
		if (PARITY(value))
			result |= PF;
	}
	return result;
}

__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_testl(__uint32_t value) {
	__uint16_t result = 0;
	if (!value)
		result |= ZF;
	else {
		if (value & UINT32_C(0x80000000))
			result |= SF;
		if (PARITY(value))
			result |= PF;
	}
	return result;
}

#error "Generic version is not fully implemented (also: why do you need vm86 on this arch?)"
//__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_addb(__uint8_t x, __uint8_t y);
//__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_addw(__uint16_t x, __uint16_t y);
//__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_addl(__uint32_t x, __uint32_t y);
//__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_cmpb(__uint8_t x, __uint8_t y);
//__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_cmpw(__uint16_t x, __uint16_t y);
//__LOCAL __ATTR_CONST __uint16_t LIBVM86_CC f_cmpl(__uint32_t x, __uint32_t y);
//__LOCAL __uint8_t LIBVM86_CC f_adcb(__uint8_t  x, __uint8_t y, __uint16_t *__restrict pflags);
//__LOCAL __uint16_t LIBVM86_CC f_adcw(__uint16_t x, __uint16_t y, __uint16_t *__restrict pflags);
//__LOCAL __uint32_t LIBVM86_CC f_adcl(__uint32_t x, __uint32_t y, __uint16_t *__restrict pflags);
//__LOCAL __uint8_t LIBVM86_CC f_sbbb(__uint8_t  x, __uint8_t y, __uint16_t *__restrict pflags);
//__LOCAL __uint16_t LIBVM86_CC f_sbbw(__uint16_t x, __uint16_t y, __uint16_t *__restrict pflags);
//__LOCAL __uint32_t LIBVM86_CC f_sbbl(__uint32_t x, __uint32_t y, __uint16_t *__restrict pflags);
#endif


__DECL_END

#endif /* !_LIBVM86_INTRIN86_H */
