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
#ifndef _LIBM_KERNEL_REM_PIO2_H
#define _LIBM_KERNEL_REM_PIO2_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/__bit.h>
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fdlibm.h>
#include <libm/floor.h>
#include <libm/scalbn.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
__LIBM_LOCAL_DECLARE_BEGIN
__LIBM_LOCAL_DECLARE_ARRAY(int, init_jkf, 3) { 4, 7, 9 }; /* initial value for jk */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, PIo2f, 11) {
	__IEEE754_FLOAT_C(1.5703125000e+00), /* 0x3fc90000 */
	__IEEE754_FLOAT_C(4.5776367188e-04), /* 0x39f00000 */
	__IEEE754_FLOAT_C(2.5987625122e-05), /* 0x37da0000 */
	__IEEE754_FLOAT_C(7.5437128544e-08), /* 0x33a20000 */
	__IEEE754_FLOAT_C(6.0026650317e-11), /* 0x2e840000 */
	__IEEE754_FLOAT_C(7.3896444519e-13), /* 0x2b500000 */
	__IEEE754_FLOAT_C(5.3845816694e-15), /* 0x27c20000 */
	__IEEE754_FLOAT_C(5.6378512969e-18), /* 0x22d00000 */
	__IEEE754_FLOAT_C(8.3009228831e-20), /* 0x1fc40000 */
	__IEEE754_FLOAT_C(3.2756352257e-22), /* 0x1bc60000 */
	__IEEE754_FLOAT_C(6.3331015649e-25)  /* 0x17440000 */
};
#ifndef __libm_zerof_defined
#define __libm_zerof_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, zerof, __IEEE754_FLOAT_C(0.0000000000e+00)) /* 0x00000000 */
#endif /* !__libm_zerof_defined */
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00))   /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_two8f_defined
#define __libm_two8f_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, two8f, __IEEE754_FLOAT_C(2.5600000000e+02))  /* 0x43800000 */
#endif /* !__libm_two8f_defined */
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, twon8f, __IEEE754_FLOAT_C(3.9062500000e-03)) /* 0x3b800000 */
/* Table of constants for 2/pi, 396 Hex digits (476 decimal) of 2/pi */
__LIBM_LOCAL_DECLARE_ARRAY(__uint8_t, two_over_pif, 198) {
	0xA2, 0xF9, 0x83, 0x6E, 0x4E, 0x44, 0x15, 0x29, 0xFC,
	0x27, 0x57, 0xD1, 0xF5, 0x34, 0xDD, 0xC0, 0xDB, 0x62,
	0x95, 0x99, 0x3C, 0x43, 0x90, 0x41, 0xFE, 0x51, 0x63,
	0xAB, 0xDE, 0xBB, 0xC5, 0x61, 0xB7, 0x24, 0x6E, 0x3A,
	0x42, 0x4D, 0xD2, 0xE0, 0x06, 0x49, 0x2E, 0xEA, 0x09,
	0xD1, 0x92, 0x1C, 0xFE, 0x1D, 0xEB, 0x1C, 0xB1, 0x29,
	0xA7, 0x3E, 0xE8, 0x82, 0x35, 0xF5, 0x2E, 0xBB, 0x44,
	0x84, 0xE9, 0x9C, 0x70, 0x26, 0xB4, 0x5F, 0x7E, 0x41,
	0x39, 0x91, 0xD6, 0x39, 0x83, 0x53, 0x39, 0xF4, 0x9C,
	0x84, 0x5F, 0x8B, 0xBD, 0xF9, 0x28, 0x3B, 0x1F, 0xF8,
	0x97, 0xFF, 0xDE, 0x05, 0x98, 0x0F, 0xEF, 0x2F, 0x11,
	0x8B, 0x5A, 0x0A, 0x6D, 0x1F, 0x6D, 0x36, 0x7E, 0xCF,
	0x27, 0xCB, 0x09, 0xB7, 0x4F, 0x46, 0x3F, 0x66, 0x9E,
	0x5F, 0xEA, 0x2D, 0x75, 0x27, 0xBA, 0xC7, 0xEB, 0xE5,
	0xF1, 0x7B, 0x3D, 0x07, 0x39, 0xF7, 0x8A, 0x52, 0x92,
	0xEA, 0x6B, 0xFB, 0x5F, 0xB1, 0x1F, 0x8D, 0x5D, 0x08,
	0x56, 0x03, 0x30, 0x46, 0xFC, 0x7B, 0x6B, 0xAB, 0xF0,
	0xCF, 0xBC, 0x20, 0x9A, 0xF4, 0x36, 0x1D, 0xA9, 0xE3,
	0x91, 0x61, 0x5E, 0xE6, 0x1B, 0x08, 0x65, 0x99, 0x85,
	0x5F, 0x14, 0xA0, 0x68, 0x40, 0x8D, 0xFF, 0xD8, 0x80,
	0x4D, 0x73, 0x27, 0x31, 0x06, 0x06, 0x15, 0x56, 0xCA,
	0x73, 0xA8, 0xC9, 0x60, 0xE2, 0x7B, 0xC0, 0x8C, 0x6B
};
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_rem_pio2f) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __int32_t
(__LIBCCALL __ieee754_kernel_rem_pio2f)(__IEEE754_FLOAT_TYPE__ *__x, __IEEE754_FLOAT_TYPE__ *__y,
                                        __int32_t __e0, __int32_t __nx, int __prec) {
	__int32_t __jz, __jx, __jv, __jp, __jk, __carry;
	__int32_t __n, __iq[20], __i, __j, __k, __m, __q0, __ih;
	__IEEE754_FLOAT_TYPE__ __z, __fw, __f[20], __fq[20], __q[20];

	/* initialize jk */
	__jk = __LIBM_LOCAL_VALUE(init_jkf)[__prec];
	__jp = __jk;

	/* determine jx,jv,q0, note that 3>q0 */
	__jx = __nx - 1;
	__jv = (__e0 - 3) / 8;
	if (__jv < 0)
		__jv = 0;
	__q0 = __e0 - 8 * (__jv + 1);

	/* set up f[0] to f[jx+jk] where f[jx+jk] = two_over_pi[jv+jk] */
	__j = __jv - __jx;
	__m = __jx + __jk;
	for (__i = 0; __i <= __m; ++__i, ++__j) {
		__f[__i] = (__j < 0) ? __LIBM_LOCAL_VALUE(zerof)
		                     : (__IEEE754_FLOAT_TYPE__)(__int32_t)__LIBM_LOCAL_VALUE(two_over_pif)[__j];
	}

	/* compute q[0],q[1],...q[jk] */
	for (__i = 0; __i <= __jk; ++__i) {
		for (__j = 0, __fw = 0.0; __j <= __jx; ++__j)
			__fw += __x[__j] * __f[__jx + __i - __j];
		__q[__i] = __fw;
	}

	__jz = __jk;
recompute:
	/* distill q[] into iq[] reversingly */
	for (__i = 0, __j = __jz, __z = __q[__jz]; __j > 0; ++__i, --__j) {
		__fw      = (__IEEE754_FLOAT_TYPE__)((__int32_t)(__LIBM_LOCAL_VALUE(twon8f) * __z));
		__iq[__i] = (__int32_t)(__z - __LIBM_LOCAL_VALUE(two8f) * __fw);
		__z       = __q[__j - 1] + __fw;
	}

	/* compute n */
	__z = __ieee754_scalbnf(__z, (int)__q0);                                                    /* actual value of z */
	__z -= (__IEEE754_FLOAT_TYPE__)8.0 * __ieee754_floorf(__z * (__IEEE754_FLOAT_TYPE__)0.125); /* trim off integer >= 8 */

	__n = (__int32_t)__z;
	__z -= (__IEEE754_FLOAT_TYPE__)__n;
	__ih = 0;
	if (__q0 > 0) { /* need iq[jz-1] to determine n */
		__i = (__iq[__jz - 1] >> (8 - __q0));
		__n += __i;
		__iq[__jz - 1] -= __i << (8 - __q0);
		__ih = __iq[__jz - 1] >> (7 - __q0);
	} else if (__q0 == 0) {
		__ih = __iq[__jz - 1] >> 7;
	} else if (__z >= (__IEEE754_FLOAT_TYPE__)0.5) {
		__ih = 2;
	}

	if (__ih > 0) { /* q > 0.5 */
		__n += 1;
		__carry = 0;
		for (__i = 0; __i < __jz; ++__i) { /* compute 1-q */
			__j = __iq[__i];
			if (__carry == 0) {
				if (__j != 0) {
					__carry   = 1;
					__iq[__i] = 0x100 - __j;
				}
			} else
				__iq[__i] = 0xff - __j;
		}
		if (__q0 > 0) { /* rare case: chance is 1 in 12 */
			switch ((int)__q0) {
			case 1:
				__iq[__jz - 1] &= 0x7f;
				break;
			case 2:
				__iq[__jz - 1] &= 0x3f;
				break;
			}
		}
		if (__ih == 2) {
			__z = __LIBM_LOCAL_VALUE(onef) - __z;
			if (__carry != 0)
				__z -= __ieee754_scalbnf(__LIBM_LOCAL_VALUE(onef), (int)__q0);
		}
	}

	/* check if recomputation is needed */
	if (__z == __LIBM_LOCAL_VALUE(zerof)) {
		__j = 0;
		for (__i = __jz - 1; __i >= __jk; --__i)
			__j |= __iq[__i];
		if (__j == 0) { /* need recomputation */
			for (__k = 1; __iq[__jk - __k] == 0; ++__k)
				; /* k = no. of terms needed */

			for (__i = __jz + 1; __i <= __jz + __k; ++__i) { /* add q[jz+1] to q[jz+k] */
				__f[__jx + __i] = (__IEEE754_FLOAT_TYPE__)(__int32_t)__LIBM_LOCAL_VALUE(two_over_pif)[__jv + __i];
				for (__j = 0, __fw = 0.0; __j <= __jx; ++__j)
					__fw += __x[__j] * __f[__jx + __i - __j];
				__q[__i] = __fw;
			}
			__jz += __k;
			goto recompute;
		}
	}

	/* chop off zero terms */
	if (__z == (__IEEE754_FLOAT_TYPE__)0.0) {
		__jz -= 1;
		__q0 -= 8;
		while (__iq[__jz] == 0) {
			__jz--;
			__q0 -= 8;
		}
	} else { /* break z into 8-bit if necessary */
		__z = __ieee754_scalbnf(__z, (int)-__q0);
		if (__z >= __LIBM_LOCAL_VALUE(two8f)) {
			__fw       = (__IEEE754_FLOAT_TYPE__)((__int32_t)(__LIBM_LOCAL_VALUE(twon8f) * __z));
			__iq[__jz] = (__int32_t)(__z - __LIBM_LOCAL_VALUE(two8f) * __fw);
			__jz += 1;
			__q0 += 8;
			__iq[__jz] = (__int32_t)__fw;
		} else {
			__iq[__jz] = (__int32_t)__z;
		}
	}

	/* convert integer "bit" chunk to floating-point value */
	__fw = __ieee754_scalbnf(__LIBM_LOCAL_VALUE(onef), (int)__q0);
	for (__i = __jz; __i >= 0; --__i) {
		__q[__i] = __fw * (__IEEE754_FLOAT_TYPE__)__iq[__i];
		__fw *= __LIBM_LOCAL_VALUE(twon8f);
	}

	/* compute PIo2[0,...,jp]*q[jz,...,0] */
	for (__i = __jz; __i >= 0; --__i) {
		for (__fw = 0.0, __k = 0; __k <= __jp && __k <= __jz - __i; ++__k)
			__fw += __LIBM_LOCAL_VALUE(PIo2f)[__k] * __q[__i + __k];
		__fq[__jz - __i] = __fw;
	}

	/* compress fq[] into y[] */
	switch (__prec) {
	case 0:
		__fw = 0.0;
		for (__i = __jz; __i >= 0; --__i)
			__fw += __fq[__i];
		__y[0] = (__ih == 0) ? __fw : -__fw;
		break;
	case 1:
	case 2: {
		volatile __IEEE754_FLOAT_TYPE__ fv = 0.0;
		for (__i = __jz; __i >= 0; --__i)
			fv += __fq[__i];
		__y[0] = (__ih == 0) ? fv : -fv;
		fv     = __fq[0] - fv;
		for (__i = 1; __i <= __jz; ++__i)
			fv += __fq[__i];
		__y[1] = (__ih == 0) ? fv : -fv;
	}	break;
	case 3: /* painful */
		for (__i = __jz; __i > 0; --__i) {
			volatile __IEEE754_FLOAT_TYPE__ fv = __fq[__i - 1] + __fq[__i];
			__fq[__i] += __fq[__i - 1] - fv;
			__fq[__i - 1] = fv;
		}
		for (__i = __jz; __i > 1; --__i) {
			volatile __IEEE754_FLOAT_TYPE__ fv = __fq[__i - 1] + __fq[__i];
			__fq[__i] += __fq[__i - 1] - fv;
			__fq[__i - 1] = fv;
		}
		for (__fw = 0.0, __i = __jz; __i >= 2; --__i)
			__fw += __fq[__i];
		if (__ih == 0) {
			__y[0] = __fq[0];
			__y[1] = __fq[1];
			__y[2] = __fw;
		} else {
			__y[0] = -__fq[0];
			__y[1] = -__fq[1];
			__y[2] = -__fw;
		}
	}
	return __n & 7;
}
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_init_jk_defined
#define __libm_init_jk_defined
__LIBM_LOCAL_DECLARE_ARRAY(int, init_jk, 4) { 2, 3, 4, 6 }; /* initial value for jk */
#endif /* !__libm_init_jk_defined */
#ifndef __libm_PIo2_defined
#define __libm_PIo2_defined
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, PIo2, 8) {
	__IEEE754_DOUBLE_C(1.57079625129699707031e+00), /* 0x3FF921FB, 0x40000000 */
	__IEEE754_DOUBLE_C(7.54978941586159635335e-08), /* 0x3E74442D, 0x00000000 */
	__IEEE754_DOUBLE_C(5.39030252995776476554e-15), /* 0x3CF84698, 0x80000000 */
	__IEEE754_DOUBLE_C(3.28200341580791294123e-22), /* 0x3B78CC51, 0x60000000 */
	__IEEE754_DOUBLE_C(1.27065575308067607349e-29), /* 0x39F01B83, 0x80000000 */
	__IEEE754_DOUBLE_C(1.22933308981111328932e-36), /* 0x387A2520, 0x40000000 */
	__IEEE754_DOUBLE_C(2.73370053816464559624e-44), /* 0x36E38222, 0x80000000 */
	__IEEE754_DOUBLE_C(2.16741683877804819444e-51)  /* 0x3569F31D, 0x00000000 */
};
#endif /* !__libm_PIo2_defined */
/* Table of constants for 2/pi, 396 Hex digits (476 decimal) of 2/pi */
__LIBM_LOCAL_DECLARE_ARRAY(__int32_t, two_over_pi, 66) {
	__INT32_C(0xA2F983), __INT32_C(0x6E4E44), __INT32_C(0x1529FC), __INT32_C(0x2757D1), __INT32_C(0xF534DD), __INT32_C(0xC0DB62),
	__INT32_C(0x95993C), __INT32_C(0x439041), __INT32_C(0xFE5163), __INT32_C(0xABDEBB), __INT32_C(0xC561B7), __INT32_C(0x246E3A),
	__INT32_C(0x424DD2), __INT32_C(0xE00649), __INT32_C(0x2EEA09), __INT32_C(0xD1921C), __INT32_C(0xFE1DEB), __INT32_C(0x1CB129),
	__INT32_C(0xA73EE8), __INT32_C(0x8235F5), __INT32_C(0x2EBB44), __INT32_C(0x84E99C), __INT32_C(0x7026B4), __INT32_C(0x5F7E41),
	__INT32_C(0x3991D6), __INT32_C(0x398353), __INT32_C(0x39F49C), __INT32_C(0x845F8B), __INT32_C(0xBDF928), __INT32_C(0x3B1FF8),
	__INT32_C(0x97FFDE), __INT32_C(0x05980F), __INT32_C(0xEF2F11), __INT32_C(0x8B5A0A), __INT32_C(0x6D1F6D), __INT32_C(0x367ECF),
	__INT32_C(0x27CB09), __INT32_C(0xB74F46), __INT32_C(0x3F669E), __INT32_C(0x5FEA2D), __INT32_C(0x7527BA), __INT32_C(0xC7EBE5),
	__INT32_C(0xF17B3D), __INT32_C(0x0739F7), __INT32_C(0x8A5292), __INT32_C(0xEA6BFB), __INT32_C(0x5FB11F), __INT32_C(0x8D5D08),
	__INT32_C(0x560330), __INT32_C(0x46FC7B), __INT32_C(0x6BABF0), __INT32_C(0xCFBC20), __INT32_C(0x9AF436), __INT32_C(0x1DA9E3),
	__INT32_C(0x91615E), __INT32_C(0xE61B08), __INT32_C(0x659985), __INT32_C(0x5F14A0), __INT32_C(0x68408D), __INT32_C(0xFFD880),
	__INT32_C(0x4D7327), __INT32_C(0x310606), __INT32_C(0x1556CA), __INT32_C(0x73A8C9), __INT32_C(0x60E27B), __INT32_C(0xC08C6B)
};
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
#ifndef __libm_two24_defined
#define __libm_two24_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two24, __IEEE754_DOUBLE_C(1.67772160000000000000e+07)) /* 0x41700000, 0x00000000 */
#endif /* !__libm_two24_defined */
#ifndef __libm_twon24_defined
#define __libm_twon24_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, twon24, __IEEE754_DOUBLE_C(5.96046447753906250000e-08)) /* 0x3E700000, 0x00000000 */
#endif /* !__libm_twon24_defined */
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_rem_pio2) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __int32_t
(__LIBCCALL __ieee754_kernel_rem_pio2)(__IEEE754_DOUBLE_TYPE__ *__x, __IEEE754_DOUBLE_TYPE__ *__y,
                                       __int32_t __e0, __int32_t __nx, int __prec) {
	__int32_t __jz, __jx, __jv, __jp, __jk, __carry;
	__int32_t __n, __iq[20], __i, __j, __k, __m, __q0, __ih;
	__IEEE754_DOUBLE_TYPE__ __z, __fw, __f[20], __fq[20], __q[20];

	/* initialize jk */
	__jk = __LIBM_LOCAL_VALUE(init_jk)[__prec];
	__jp = __jk;

	/* determine jx,jv,q0, note that 3>q0 */
	__jx = __nx - 1;
	__jv = (__e0 - 3) / 24;
	if (__jv < 0)
		__jv = 0;
	__q0 = __e0 - 24 * (__jv + 1);

	/* set up f[0] to f[jx+jk] where f[jx+jk] = two_over_pi[jv+jk] */
	__j = __jv - __jx;
	__m = __jx + __jk;
	for (__i = 0; __i <= __m; ++__i, __j++)
		__f[__i] = (__j < 0) ? __LIBM_LOCAL_VALUE(zero) : (__IEEE754_DOUBLE_TYPE__)__LIBM_LOCAL_VALUE(two_over_pi)[__j];

	/* compute q[0],q[1],...q[jk] */
	for (__i = 0; __i <= __jk; ++__i) {
		for (__j = 0, __fw = 0.0; __j <= __jx; __j++)
			__fw += __x[__j] * __f[__jx + __i - __j];
		__q[__i] = __fw;
	}

	__jz = __jk;
recompute:
	/* distill q[] into iq[] reversingly */
	for (__i = 0, __j = __jz, __z = __q[__jz]; __j > 0; ++__i, --__j) {
		__fw      = (__IEEE754_DOUBLE_TYPE__)((__int32_t)(__LIBM_LOCAL_VALUE(twon24) * __z));
		__iq[__i] = (__int32_t)(__z - __LIBM_LOCAL_VALUE(two24) * __fw);
		__z       = __q[__j - 1] + __fw;
	}

	/* compute n */
	__z = __ieee754_scalbn(__z, (int)__q0);    /* actual value of z */
	__z -= 8.0 * __ieee754_floor(__z * 0.125); /* trim off integer >= 8 */
	__n = (__int32_t)__z;
	__z -= (__IEEE754_DOUBLE_TYPE__)__n;
	__ih = 0;
	if (__q0 > 0) { /* need iq[jz-1] to determine n */
		__i = (__iq[__jz - 1] >> (24 - __q0));
		__n += __i;
		__iq[__jz - 1] -= __i << (24 - __q0);
		__ih = __iq[__jz - 1] >> (23 - __q0);
	} else if (__q0 == 0) {
		__ih = __iq[__jz - 1] >> 23;
	} else if (__z >= 0.5) {
		__ih = 2;
	}

	if (__ih > 0) { /* q > 0.5 */
		__n += 1;
		__carry = 0;
		for (__i = 0; __i < __jz; ++__i) { /* compute 1-q */
			__j = __iq[__i];
			if (__carry == 0) {
				if (__j != 0) {
					__carry   = 1;
					__iq[__i] = __INT32_C(0x1000000) - __j;
				}
			} else
				__iq[__i] = __INT32_C(0xffffff) - __j;
		}
		if (__q0 > 0) { /* rare case: chance is 1 in 12 */
			switch ((int)__q0) {
			case 1:
				__iq[__jz - 1] &= __INT32_C(0x7fffff);
				break;
			case 2:
				__iq[__jz - 1] &= __INT32_C(0x3fffff);
				break;
			}
		}
		if (__ih == 2) {
			__z = __LIBM_LOCAL_VALUE(one) - __z;
			if (__carry != 0)
				__z -= __ieee754_scalbn(__LIBM_LOCAL_VALUE(one), (int)__q0);
		}
	}

	/* check if recomputation is needed */
	if (__z == __LIBM_LOCAL_VALUE(zero)) {
		__j = 0;
		for (__i = __jz - 1; __i >= __jk; --__i)
			__j |= __iq[__i];
		if (__j == 0) {                                 /* need recomputation */
			for (__k = 1; __iq[__jk - __k] == 0; ++__k) /* k = no. of terms needed */
				;
			for (__i = __jz + 1; __i <= __jz + __k; ++__i) { /* add q[jz+1] to q[jz+k] */
				__f[__jx + __i] = (__IEEE754_DOUBLE_TYPE__)__LIBM_LOCAL_VALUE(two_over_pi)[__jv + __i];
				for (__j = 0, __fw = 0.0; __j <= __jx; __j++)
					__fw += __x[__j] * __f[__jx + __i - __j];
				__q[__i] = __fw;
			}
			__jz += __k;
			goto recompute;
		}
	}

	/* chop off zero terms */
	if (__z == 0.0) {
		__jz -= 1;
		__q0 -= 24;
		while (__iq[__jz] == 0) {
			__jz--;
			__q0 -= 24;
		}
	} else { /* break z into 24-bit if necessary */
		__z = __ieee754_scalbn(__z, (int)-__q0);
		if (__z >= __LIBM_LOCAL_VALUE(two24)) {
			__fw       = (__IEEE754_DOUBLE_TYPE__)((__int32_t)(__LIBM_LOCAL_VALUE(twon24) * __z));
			__iq[__jz] = (__int32_t)(__z - __LIBM_LOCAL_VALUE(two24) * __fw);
			__jz += 1;
			__q0 += 24;
			__iq[__jz] = (__int32_t)__fw;
		} else {
			__iq[__jz] = (__int32_t)__z;
		}
	}

	/* convert integer "bit" chunk to floating-point value */
	__fw = __ieee754_scalbn(__LIBM_LOCAL_VALUE(one), (int)__q0);
	for (__i = __jz; __i >= 0; --__i) {
		__q[__i] = __fw * (__IEEE754_DOUBLE_TYPE__)__iq[__i];
		__fw *= __LIBM_LOCAL_VALUE(twon24);
	}

	/* compute PIo2[0,...,jp]*q[jz,...,0] */
	for (__i = __jz; __i >= 0; --__i) {
		for (__fw = 0.0, __k = 0; __k <= __jp && __k <= __jz - __i; ++__k)
			__fw += __LIBM_LOCAL_VALUE(PIo2)[__k] * __q[__i + __k];
		__fq[__jz - __i] = __fw;
	}

	/* compress fq[] into y[] */
	switch (__prec) {
	case 0:
		__fw = 0.0;
		for (__i = __jz; __i >= 0; --__i)
			__fw += __fq[__i];
		__y[0] = (__ih == 0) ? __fw : -__fw;
		break;
	case 1:
	case 2: {
		volatile __IEEE754_DOUBLE_TYPE__ fv = 0.0;

		for (__i = __jz; __i >= 0; --__i)
			fv += __fq[__i];
		__y[0] = (__ih == 0) ? fv : -fv;
		fv     = __fq[0] - fv;
		for (__i = 1; __i <= __jz; ++__i)
			fv += __fq[__i];
		__y[1] = (__ih == 0) ? fv : -fv;
	}	break;
	case 3: /* painful */
		for (__i = __jz; __i > 0; --__i) {
			volatile __IEEE754_DOUBLE_TYPE__ fv = (__IEEE754_DOUBLE_TYPE__)(__fq[__i - 1] + __fq[__i]);
			__fq[__i] += __fq[__i - 1] - fv;
			__fq[__i - 1] = fv;
		}
		for (__i = __jz; __i > 1; --__i) {
			volatile __IEEE754_DOUBLE_TYPE__ fv = (__IEEE754_DOUBLE_TYPE__)(__fq[__i - 1] + __fq[__i]);
			__fq[__i] += __fq[__i - 1] - fv;
			__fq[__i - 1] = fv;
		}
		for (__fw = 0.0, __i = __jz; __i >= 2; --__i)
			__fw += __fq[__i];
		if (__ih == 0) {
			__y[0] = __fq[0];
			__y[1] = __fq[1];
			__y[2] = __fw;
		} else {
			__y[0] = -__fq[0];
			__y[1] = -__fq[1];
			__y[2] = -__fw;
		}
	}
	return __n & 7;
}
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
__LIBM_LOCAL_DECLARE_BEGIN
#ifndef __libm_init_jk_defined
#define __libm_init_jk_defined
__LIBM_LOCAL_DECLARE_ARRAY(int, init_jk, 4) { 2, 3, 4, 6 }; /* initial value for jk */
#endif /* !__libm_init_jk_defined */
#ifndef __libm_PIo2_defined
#define __libm_PIo2_defined
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, PIo2, 8) {
	__IEEE754_DOUBLE_C(1.57079625129699707031e+00), /* 0x3FF921FB, 0x40000000 */
	__IEEE754_DOUBLE_C(7.54978941586159635335e-08), /* 0x3E74442D, 0x00000000 */
	__IEEE754_DOUBLE_C(5.39030252995776476554e-15), /* 0x3CF84698, 0x80000000 */
	__IEEE754_DOUBLE_C(3.28200341580791294123e-22), /* 0x3B78CC51, 0x60000000 */
	__IEEE754_DOUBLE_C(1.27065575308067607349e-29), /* 0x39F01B83, 0x80000000 */
	__IEEE754_DOUBLE_C(1.22933308981111328932e-36), /* 0x387A2520, 0x40000000 */
	__IEEE754_DOUBLE_C(2.73370053816464559624e-44), /* 0x36E38222, 0x80000000 */
	__IEEE754_DOUBLE_C(2.16741683877804819444e-51)  /* 0x3569F31D, 0x00000000 */
};
#endif /* !__libm_PIo2_defined */
#ifndef __libm_zero_defined
#define __libm_zero_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, zero, __IEEE754_DOUBLE_C(0.00000000000000000000e+00)) /* 0x00000000, 0x00000000 */
#endif /* !__libm_zero_defined */
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
#ifndef __libm_two24_defined
#define __libm_two24_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, two24, __IEEE754_DOUBLE_C(1.67772160000000000000e+07))  /* 0x41700000, 0x00000000 */
#endif /* !__libm_two24_defined */
#ifndef __libm_twon24_defined
#define __libm_twon24_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, twon24, __IEEE754_DOUBLE_C(5.96046447753906250000e-08)) /* 0x3E700000, 0x00000000 */
#endif /* !__libm_twon24_defined */
/* Table of constants for 2/pi, 5628 hexadecimal digits of 2/pi. */
__LIBM_LOCAL_DECLARE_ARRAY(__int32_t, two_over_pil, 938) {
	__INT32_C(0xa2f983), __INT32_C(0x6e4e44), __INT32_C(0x1529fc), __INT32_C(0x2757d1), __INT32_C(0xf534dd), __INT32_C(0xc0db62),
	__INT32_C(0x95993c), __INT32_C(0x439041), __INT32_C(0xfe5163), __INT32_C(0xabdebb), __INT32_C(0xc561b7), __INT32_C(0x246e3a),
	__INT32_C(0x424dd2), __INT32_C(0xe00649), __INT32_C(0x2eea09), __INT32_C(0xd1921c), __INT32_C(0xfe1deb), __INT32_C(0x1cb129),
	__INT32_C(0xa73ee8), __INT32_C(0x8235f5), __INT32_C(0x2ebb44), __INT32_C(0x84e99c), __INT32_C(0x7026b4), __INT32_C(0x5f7e41),
	__INT32_C(0x3991d6), __INT32_C(0x398353), __INT32_C(0x39f49c), __INT32_C(0x845f8b), __INT32_C(0xbdf928), __INT32_C(0x3b1ff8),
	__INT32_C(0x97ffde), __INT32_C(0x05980f), __INT32_C(0xef2f11), __INT32_C(0x8b5a0a), __INT32_C(0x6d1f6d), __INT32_C(0x367ecf),
	__INT32_C(0x27cb09), __INT32_C(0xb74f46), __INT32_C(0x3f669e), __INT32_C(0x5fea2d), __INT32_C(0x7527ba), __INT32_C(0xc7ebe5),
	__INT32_C(0xf17b3d), __INT32_C(0x0739f7), __INT32_C(0x8a5292), __INT32_C(0xea6bfb), __INT32_C(0x5fb11f), __INT32_C(0x8d5d08),
	__INT32_C(0x560330), __INT32_C(0x46fc7b), __INT32_C(0x6babf0), __INT32_C(0xcfbc20), __INT32_C(0x9af436), __INT32_C(0x1da9e3),
	__INT32_C(0x91615e), __INT32_C(0xe61b08), __INT32_C(0x659985), __INT32_C(0x5f14a0), __INT32_C(0x68408d), __INT32_C(0xffd880),
	__INT32_C(0x4d7327), __INT32_C(0x310606), __INT32_C(0x1556ca), __INT32_C(0x73a8c9), __INT32_C(0x60e27b), __INT32_C(0xc08c6b),
	__INT32_C(0x47c419), __INT32_C(0xc367cd), __INT32_C(0xdce809), __INT32_C(0x2a8359), __INT32_C(0xc4768b), __INT32_C(0x961ca6),
	__INT32_C(0xddaf44), __INT32_C(0xd15719), __INT32_C(0x053ea5), __INT32_C(0xff0705), __INT32_C(0x3f7e33), __INT32_C(0xe832c2),
	__INT32_C(0xde4f98), __INT32_C(0x327dbb), __INT32_C(0xc33d26), __INT32_C(0xef6b1e), __INT32_C(0x5ef89f), __INT32_C(0x3a1f35),
	__INT32_C(0xcaf27f), __INT32_C(0x1d87f1), __INT32_C(0x21907c), __INT32_C(0x7c246a), __INT32_C(0xfa6ed5), __INT32_C(0x772d30),
	__INT32_C(0x433b15), __INT32_C(0xc614b5), __INT32_C(0x9d19c3), __INT32_C(0xc2c4ad), __INT32_C(0x414d2c), __INT32_C(0x5d000c),
	__INT32_C(0x467d86), __INT32_C(0x2d71e3), __INT32_C(0x9ac69b), __INT32_C(0x006233), __INT32_C(0x7cd2b4), __INT32_C(0x97a7b4),
	__INT32_C(0xd55537), __INT32_C(0xf63ed7), __INT32_C(0x1810a3), __INT32_C(0xfc764d), __INT32_C(0x2a9d64), __INT32_C(0xabd770),
	__INT32_C(0xf87c63), __INT32_C(0x57b07a), __INT32_C(0xe71517), __INT32_C(0x5649c0), __INT32_C(0xd9d63b), __INT32_C(0x3884a7),
	__INT32_C(0xcb2324), __INT32_C(0x778ad6), __INT32_C(0x23545a), __INT32_C(0xb91f00), __INT32_C(0x1b0af1), __INT32_C(0xdfce19),
	__INT32_C(0xff319f), __INT32_C(0x6a1e66), __INT32_C(0x615799), __INT32_C(0x47fbac), __INT32_C(0xd87f7e), __INT32_C(0xb76522),
	__INT32_C(0x89e832), __INT32_C(0x60bfe6), __INT32_C(0xcdc4ef), __INT32_C(0x09366c), __INT32_C(0xd43f5d), __INT32_C(0xd7de16),
	__INT32_C(0xde3b58), __INT32_C(0x929bde), __INT32_C(0x2822d2), __INT32_C(0xe88628), __INT32_C(0x4d58e2), __INT32_C(0x32cac6),
	__INT32_C(0x16e308), __INT32_C(0xcb7de0), __INT32_C(0x50c017), __INT32_C(0xa71df3), __INT32_C(0x5be018), __INT32_C(0x34132e),
	__INT32_C(0x621283), __INT32_C(0x014883), __INT32_C(0x5b8ef5), __INT32_C(0x7fb0ad), __INT32_C(0xf2e91e), __INT32_C(0x434a48),
	__INT32_C(0xd36710), __INT32_C(0xd8ddaa), __INT32_C(0x425fae), __INT32_C(0xce616a), __INT32_C(0xa4280a), __INT32_C(0xb499d3),
	__INT32_C(0xf2a606), __INT32_C(0x7f775c), __INT32_C(0x83c2a3), __INT32_C(0x883c61), __INT32_C(0x78738a), __INT32_C(0x5a8caf),
	__INT32_C(0xbdd76f), __INT32_C(0x63a62d), __INT32_C(0xcbbff4), __INT32_C(0xef818d), __INT32_C(0x67c126), __INT32_C(0x45ca55),
	__INT32_C(0x36d9ca), __INT32_C(0xd2a828), __INT32_C(0x8d61c2), __INT32_C(0x77c912), __INT32_C(0x142604), __INT32_C(0x9b4612),
	__INT32_C(0xc459c4), __INT32_C(0x44c5c8), __INT32_C(0x91b24d), __INT32_C(0xf31700), __INT32_C(0xad43d4), __INT32_C(0xe54929),
	__INT32_C(0x10d5fd), __INT32_C(0xfcbe00), __INT32_C(0xcc941e), __INT32_C(0xeece70), __INT32_C(0xf53e13), __INT32_C(0x80f1ec),
	__INT32_C(0xc3e7b3), __INT32_C(0x28f8c7), __INT32_C(0x940593), __INT32_C(0x3e71c1), __INT32_C(0xb3092e), __INT32_C(0xf3450b),
	__INT32_C(0x9c1288), __INT32_C(0x7b20ab), __INT32_C(0x9fb52e), __INT32_C(0xc29247), __INT32_C(0x2f327b), __INT32_C(0x6d550c),
	__INT32_C(0x90a772), __INT32_C(0x1fe76b), __INT32_C(0x96cb31), __INT32_C(0x4a1679), __INT32_C(0xe27941), __INT32_C(0x89dff4),
	__INT32_C(0x9794e8), __INT32_C(0x84e6e2), __INT32_C(0x973199), __INT32_C(0x6bed88), __INT32_C(0x365f5f), __INT32_C(0x0efdbb),
	__INT32_C(0xb49a48), __INT32_C(0x6ca467), __INT32_C(0x427271), __INT32_C(0x325d8d), __INT32_C(0xb8159f), __INT32_C(0x09e5bc),
	__INT32_C(0x25318d), __INT32_C(0x3974f7), __INT32_C(0x1c0530), __INT32_C(0x010c0d), __INT32_C(0x68084b), __INT32_C(0x58ee2c),
	__INT32_C(0x90aa47), __INT32_C(0x02e774), __INT32_C(0x24d6bd), __INT32_C(0xa67df7), __INT32_C(0x72486e), __INT32_C(0xef169f),
	__INT32_C(0xa6948e), __INT32_C(0xf691b4), __INT32_C(0x5153d1), __INT32_C(0xf20acf), __INT32_C(0x339820), __INT32_C(0x7e4bf5),
	__INT32_C(0x6863b2), __INT32_C(0x5f3edd), __INT32_C(0x035d40), __INT32_C(0x7f8985), __INT32_C(0x295255), __INT32_C(0xc06437),
	__INT32_C(0x10d86d), __INT32_C(0x324832), __INT32_C(0x754c5b), __INT32_C(0xd4714e), __INT32_C(0x6e5445), __INT32_C(0xc1090b),
	__INT32_C(0x69f52a), __INT32_C(0xd56614), __INT32_C(0x9d0727), __INT32_C(0x50045d), __INT32_C(0xdb3bb4), __INT32_C(0xc576ea),
	__INT32_C(0x17f987), __INT32_C(0x7d6b49), __INT32_C(0xba271d), __INT32_C(0x296996), __INT32_C(0xacccc6), __INT32_C(0x5414ad),
	__INT32_C(0x6ae290), __INT32_C(0x89d988), __INT32_C(0x50722c), __INT32_C(0xbea404), __INT32_C(0x940777), __INT32_C(0x7030f3),
	__INT32_C(0x27fc00), __INT32_C(0xa871ea), __INT32_C(0x49c266), __INT32_C(0x3de064), __INT32_C(0x83dd97), __INT32_C(0x973fa3),
	__INT32_C(0xfd9443), __INT32_C(0x8c860d), __INT32_C(0xde4131), __INT32_C(0x9d3992), __INT32_C(0x8c70dd), __INT32_C(0xe7b717),
	__INT32_C(0x3bdf08), __INT32_C(0x2b3715), __INT32_C(0xa0805c), __INT32_C(0x93805a), __INT32_C(0x921110), __INT32_C(0xd8e80f),
	__INT32_C(0xaf806c), __INT32_C(0x4bffdb), __INT32_C(0x0f9038), __INT32_C(0x761859), __INT32_C(0x15a562), __INT32_C(0xbbcb61),
	__INT32_C(0xb989c7), __INT32_C(0xbd4010), __INT32_C(0x04f2d2), __INT32_C(0x277549), __INT32_C(0xf6b6eb), __INT32_C(0xbb22db),
	__INT32_C(0xaa140a), __INT32_C(0x2f2689), __INT32_C(0x768364), __INT32_C(0x333b09), __INT32_C(0x1a940e), __INT32_C(0xaa3a51),
	__INT32_C(0xc2a31d), __INT32_C(0xaeedaf), __INT32_C(0x12265c), __INT32_C(0x4dc26d), __INT32_C(0x9c7a2d), __INT32_C(0x9756c0),
	__INT32_C(0x833f03), __INT32_C(0xf6f009), __INT32_C(0x8c402b), __INT32_C(0x99316d), __INT32_C(0x07b439), __INT32_C(0x15200c),
	__INT32_C(0x5bc3d8), __INT32_C(0xc492f5), __INT32_C(0x4badc6), __INT32_C(0xa5ca4e), __INT32_C(0xcd37a7), __INT32_C(0x36a9e6),
	__INT32_C(0x9492ab), __INT32_C(0x6842dd), __INT32_C(0xde6319), __INT32_C(0xef8c76), __INT32_C(0x528b68), __INT32_C(0x37dbfc),
	__INT32_C(0xaba1ae), __INT32_C(0x3115df), __INT32_C(0xa1ae00), __INT32_C(0xdafb0c), __INT32_C(0x664d64), __INT32_C(0xb705ed),
	__INT32_C(0x306529), __INT32_C(0xbf5657), __INT32_C(0x3aff47), __INT32_C(0xb9f96a), __INT32_C(0xf3be75), __INT32_C(0xdf9328),
	__INT32_C(0x3080ab), __INT32_C(0xf68c66), __INT32_C(0x15cb04), __INT32_C(0x0622fa), __INT32_C(0x1de4d9), __INT32_C(0xa4b33d),
	__INT32_C(0x8f1b57), __INT32_C(0x09cd36), __INT32_C(0xe9424e), __INT32_C(0xa4be13), __INT32_C(0xb52333), __INT32_C(0x1aaaf0),
	__INT32_C(0xa8654f), __INT32_C(0xa5c1d2), __INT32_C(0x0f3f0b), __INT32_C(0xcd785b), __INT32_C(0x76f923), __INT32_C(0x048b7b),
	__INT32_C(0x721789), __INT32_C(0x53a6c6), __INT32_C(0xe26e6f), __INT32_C(0x00ebef), __INT32_C(0x584a9b), __INT32_C(0xb7dac4),
	__INT32_C(0xba66aa), __INT32_C(0xcfcf76), __INT32_C(0x1d02d1), __INT32_C(0x2df1b1), __INT32_C(0xc1998c), __INT32_C(0x77adc3),
	__INT32_C(0xda4886), __INT32_C(0xa05df7), __INT32_C(0xf480c6), __INT32_C(0x2ff0ac), __INT32_C(0x9aecdd), __INT32_C(0xbc5c3f),
	__INT32_C(0x6dded0), __INT32_C(0x1fc790), __INT32_C(0xb6db2a), __INT32_C(0x3a25a3), __INT32_C(0x9aaf00), __INT32_C(0x9353ad),
	__INT32_C(0x0457b6), __INT32_C(0xb42d29), __INT32_C(0x7e804b), __INT32_C(0xa707da), __INT32_C(0x0eaa76), __INT32_C(0xa1597b),
	__INT32_C(0x2a1216), __INT32_C(0x2db7dc), __INT32_C(0xfde5fa), __INT32_C(0xfedb89), __INT32_C(0xfdbe89), __INT32_C(0x6c76e4),
	__INT32_C(0xfca906), __INT32_C(0x70803e), __INT32_C(0x156e85), __INT32_C(0xff87fd), __INT32_C(0x073e28), __INT32_C(0x336761),
	__INT32_C(0x86182a), __INT32_C(0xeabd4d), __INT32_C(0xafe7b3), __INT32_C(0x6e6d8f), __INT32_C(0x396795), __INT32_C(0x5bbf31),
	__INT32_C(0x48d784), __INT32_C(0x16df30), __INT32_C(0x432dc7), __INT32_C(0x356125), __INT32_C(0xce70c9), __INT32_C(0xb8cb30),
	__INT32_C(0xfd6cbf), __INT32_C(0xa200a4), __INT32_C(0xe46c05), __INT32_C(0xa0dd5a), __INT32_C(0x476f21), __INT32_C(0xd21262),
	__INT32_C(0x845cb9), __INT32_C(0x496170), __INT32_C(0xe0566b), __INT32_C(0x015299), __INT32_C(0x375550), __INT32_C(0xb7d51e),
	__INT32_C(0xc4f133), __INT32_C(0x5f6e13), __INT32_C(0xe4305d), __INT32_C(0xa92e85), __INT32_C(0xc3b21d), __INT32_C(0x3632a1),
	__INT32_C(0xa4b708), __INT32_C(0xd4b1ea), __INT32_C(0x21f716), __INT32_C(0xe4698f), __INT32_C(0x77ff27), __INT32_C(0x80030c),
	__INT32_C(0x2d408d), __INT32_C(0xa0cd4f), __INT32_C(0x99a520), __INT32_C(0xd3a2b3), __INT32_C(0x0a5d2f), __INT32_C(0x42f9b4),
	__INT32_C(0xcbda11), __INT32_C(0xd0be7d), __INT32_C(0xc1db9b), __INT32_C(0xbd17ab), __INT32_C(0x81a2ca), __INT32_C(0x5c6a08),
	__INT32_C(0x17552e), __INT32_C(0x550027), __INT32_C(0xf0147f), __INT32_C(0x8607e1), __INT32_C(0x640b14), __INT32_C(0x8d4196),
	__INT32_C(0xdebe87), __INT32_C(0x2afdda), __INT32_C(0xb6256b), __INT32_C(0x34897b), __INT32_C(0xfef305), __INT32_C(0x9ebfb9),
	__INT32_C(0x4f6a68), __INT32_C(0xa82a4a), __INT32_C(0x5ac44f), __INT32_C(0xbcf82d), __INT32_C(0x985ad7), __INT32_C(0x95c7f4),
	__INT32_C(0x8d4d0d), __INT32_C(0xa63a20), __INT32_C(0x5f57a4), __INT32_C(0xb13f14), __INT32_C(0x953880), __INT32_C(0x0120cc),
	__INT32_C(0x86dd71), __INT32_C(0xb6dec9), __INT32_C(0xf560bf), __INT32_C(0x11654d), __INT32_C(0x6b0701), __INT32_C(0xacb08c),
	__INT32_C(0xd0c0b2), __INT32_C(0x485551), __INT32_C(0x0efb1e), __INT32_C(0xc37295), __INT32_C(0x3b06a3), __INT32_C(0x3540c0),
	__INT32_C(0x7bdc06), __INT32_C(0xcc45e0), __INT32_C(0xfa294e), __INT32_C(0xc8cad6), __INT32_C(0x41f3e8), __INT32_C(0xde647c),
	__INT32_C(0xd8649b), __INT32_C(0x31bed9), __INT32_C(0xc397a4), __INT32_C(0xd45877), __INT32_C(0xc5e369), __INT32_C(0x13daf0),
	__INT32_C(0x3c3aba), __INT32_C(0x461846), __INT32_C(0x5f7555), __INT32_C(0xf5bdd2), __INT32_C(0xc6926e), __INT32_C(0x5d2eac),
	__INT32_C(0xed440e), __INT32_C(0x423e1c), __INT32_C(0x87c461), __INT32_C(0xe9fd29), __INT32_C(0xf3d6e7), __INT32_C(0xca7c22),
	__INT32_C(0x35916f), __INT32_C(0xc5e008), __INT32_C(0x8dd7ff), __INT32_C(0xe26a6e), __INT32_C(0xc6fdb0), __INT32_C(0xc10893),
	__INT32_C(0x745d7c), __INT32_C(0xb2ad6b), __INT32_C(0x9d6ecd), __INT32_C(0x7b723e), __INT32_C(0x6a11c6), __INT32_C(0xa9cff7),
	__INT32_C(0xdf7329), __INT32_C(0xbac9b5), __INT32_C(0x5100b7), __INT32_C(0x0db2e2), __INT32_C(0x24ba74), __INT32_C(0x607de5),
	__INT32_C(0x8ad874), __INT32_C(0x2c150d), __INT32_C(0x0c1881), __INT32_C(0x94667e), __INT32_C(0x162901), __INT32_C(0x767a9f),
	__INT32_C(0xbefdfd), __INT32_C(0xef4556), __INT32_C(0x367ed9), __INT32_C(0x13d9ec), __INT32_C(0xb9ba8b), __INT32_C(0xfc97c4),
	__INT32_C(0x27a831), __INT32_C(0xc36ef1), __INT32_C(0x36c594), __INT32_C(0x56a8d8), __INT32_C(0xb5a8b4), __INT32_C(0x0ecccf),
	__INT32_C(0x2d8912), __INT32_C(0x34576f), __INT32_C(0x89562c), __INT32_C(0xe3ce99), __INT32_C(0xb920d6), __INT32_C(0xaa5e6b),
	__INT32_C(0x9c2a3e), __INT32_C(0xcc5f11), __INT32_C(0x4a0bfd), __INT32_C(0xfbf4e1), __INT32_C(0x6d3b8e), __INT32_C(0x2c86e2),
	__INT32_C(0x84d4e9), __INT32_C(0xa9b4fc), __INT32_C(0xd1eeef), __INT32_C(0xc9352e), __INT32_C(0x61392f), __INT32_C(0x442138),
	__INT32_C(0xc8d91b), __INT32_C(0x0afc81), __INT32_C(0x6a4afb), __INT32_C(0xd81c2f), __INT32_C(0x84b453), __INT32_C(0x8c994e),
	__INT32_C(0xcc2254), __INT32_C(0xdc552a), __INT32_C(0xd6c6c0), __INT32_C(0x96190b), __INT32_C(0xb8701a), __INT32_C(0x649569),
	__INT32_C(0x605a26), __INT32_C(0xee523f), __INT32_C(0x0f117f), __INT32_C(0x11b5f4), __INT32_C(0xf5cbfc), __INT32_C(0x2dbc34),
	__INT32_C(0xeebc34), __INT32_C(0xcc5de8), __INT32_C(0x605edd), __INT32_C(0x9b8e67), __INT32_C(0xef3392), __INT32_C(0xb817c9),
	__INT32_C(0x9b5861), __INT32_C(0xbc57e1), __INT32_C(0xc68351), __INT32_C(0x103ed8), __INT32_C(0x4871dd), __INT32_C(0xdd1c2d),
	__INT32_C(0xa118af), __INT32_C(0x462c21), __INT32_C(0xd7f359), __INT32_C(0x987ad9), __INT32_C(0xc0549e), __INT32_C(0xfa864f),
	__INT32_C(0xfc0656), __INT32_C(0xae79e5), __INT32_C(0x362289), __INT32_C(0x22ad38), __INT32_C(0xdc9367), __INT32_C(0xaae855),
	__INT32_C(0x382682), __INT32_C(0x9be7ca), __INT32_C(0xa40d51), __INT32_C(0xb13399), __INT32_C(0x0ed7a9), __INT32_C(0x480569),
	__INT32_C(0xf0b265), __INT32_C(0xa7887f), __INT32_C(0x974c88), __INT32_C(0x36d1f9), __INT32_C(0xb39221), __INT32_C(0x4a827b),
	__INT32_C(0x21cf98), __INT32_C(0xdc9f40), __INT32_C(0x5547dc), __INT32_C(0x3a74e1), __INT32_C(0x42eb67), __INT32_C(0xdf9dfe),
	__INT32_C(0x5fd45e), __INT32_C(0xa4677b), __INT32_C(0x7aacba), __INT32_C(0xa2f655), __INT32_C(0x23882b), __INT32_C(0x55ba41),
	__INT32_C(0x086e59), __INT32_C(0x862a21), __INT32_C(0x834739), __INT32_C(0xe6e389), __INT32_C(0xd49ee5), __INT32_C(0x40fb49),
	__INT32_C(0xe956ff), __INT32_C(0xca0f1c), __INT32_C(0x8a59c5), __INT32_C(0x2bfa94), __INT32_C(0xc5c1d3), __INT32_C(0xcfc50f),
	__INT32_C(0xae5adb), __INT32_C(0x86c547), __INT32_C(0x624385), __INT32_C(0x3b8621), __INT32_C(0x94792c), __INT32_C(0x876110),
	__INT32_C(0x7b4c2a), __INT32_C(0x1a2c80), __INT32_C(0x12bf43), __INT32_C(0x902688), __INT32_C(0x893c78), __INT32_C(0xe4c4a8),
	__INT32_C(0x7bdbe5), __INT32_C(0xc23ac4), __INT32_C(0xeaf426), __INT32_C(0x8a67f7), __INT32_C(0xbf920d), __INT32_C(0x2ba365),
	__INT32_C(0xb1933d), __INT32_C(0x0b7cbd), __INT32_C(0xdc51a4), __INT32_C(0x63dd27), __INT32_C(0xdde169), __INT32_C(0x19949a),
	__INT32_C(0x9529a8), __INT32_C(0x28ce68), __INT32_C(0xb4ed09), __INT32_C(0x209f44), __INT32_C(0xca984e), __INT32_C(0x638270),
	__INT32_C(0x237c7e), __INT32_C(0x32b90f), __INT32_C(0x8ef5a7), __INT32_C(0xe75614), __INT32_C(0x08f121), __INT32_C(0x2a9db5),
	__INT32_C(0x4d7e6f), __INT32_C(0x5119a5), __INT32_C(0xabf9b5), __INT32_C(0xd6df82), __INT32_C(0x61dd96), __INT32_C(0x023616),
	__INT32_C(0x9f3ac4), __INT32_C(0xa1a283), __INT32_C(0x6ded72), __INT32_C(0x7a8d39), __INT32_C(0xa9b882), __INT32_C(0x5c326b),
	__INT32_C(0x5b2746), __INT32_C(0xed3400), __INT32_C(0x7700d2), __INT32_C(0x55f4fc), __INT32_C(0x4d5901), __INT32_C(0x8071e0),
	__INT32_C(0xe13f89), __INT32_C(0xb295f3), __INT32_C(0x64a8f1), __INT32_C(0xaea74b), __INT32_C(0x38fc4c), __INT32_C(0xeab2bb),
	__INT32_C(0x47270b), __INT32_C(0xabc3a7), __INT32_C(0x34ba60), __INT32_C(0x52dd34), __INT32_C(0xf8563a), __INT32_C(0xeb7e8a),
	__INT32_C(0x31bb36), __INT32_C(0x5895b7), __INT32_C(0x47f7a9), __INT32_C(0x94c3aa), __INT32_C(0xd39225), __INT32_C(0x1e7f3e),
	__INT32_C(0xd8974e), __INT32_C(0xbba94f), __INT32_C(0xd8ae01), __INT32_C(0xe661b4), __INT32_C(0x393d8e), __INT32_C(0xa523aa),
	__INT32_C(0x33068e), __INT32_C(0x1633b5), __INT32_C(0x3bb188), __INT32_C(0x1d3a9d), __INT32_C(0x4013d0), __INT32_C(0xcc1be5),
	__INT32_C(0xf862e7), __INT32_C(0x3bf28f), __INT32_C(0x39b5bf), __INT32_C(0x0bc235), __INT32_C(0x22747e), __INT32_C(0xa247c0),
	__INT32_C(0xd52d1f), __INT32_C(0x19add3), __INT32_C(0x9094df), __INT32_C(0x9311d0), __INT32_C(0xb42b25), __INT32_C(0x496db2),
	__INT32_C(0xe264b2), __INT32_C(0x5ef135), __INT32_C(0x3bc6a4), __INT32_C(0x1a4ad0), __INT32_C(0xaac92e), __INT32_C(0x64e886),
	__INT32_C(0x573091), __INT32_C(0x982cfb), __INT32_C(0x311b1a), __INT32_C(0x08728b), __INT32_C(0xbdcee1), __INT32_C(0x60e142),
	__INT32_C(0xeb641d), __INT32_C(0xd0bba3), __INT32_C(0xe559d4), __INT32_C(0x597b8c), __INT32_C(0x2a4483), __INT32_C(0xf332ba),
	__INT32_C(0xf84867), __INT32_C(0x2c8d1b), __INT32_C(0x2fa9b0), __INT32_C(0x50f3dd), __INT32_C(0xf9f573), __INT32_C(0xdb61b4),
	__INT32_C(0xfe233e), __INT32_C(0x6c41a6), __INT32_C(0xeea318), __INT32_C(0x775a26), __INT32_C(0xbc5e5c), __INT32_C(0xcea708),
	__INT32_C(0x94dc57), __INT32_C(0xe20196), __INT32_C(0xf1e839), __INT32_C(0xbe4851), __INT32_C(0x5d2d2f), __INT32_C(0x4e9555),
	__INT32_C(0xd96ec2), __INT32_C(0xe7d755), __INT32_C(0x6304e0), __INT32_C(0xc02e0e), __INT32_C(0xfc40a0), __INT32_C(0xbbf9b3),
	__INT32_C(0x7125a7), __INT32_C(0x222dfb), __INT32_C(0xf619d8), __INT32_C(0x838c1c), __INT32_C(0x6619e6), __INT32_C(0xb20d55),
	__INT32_C(0xbb5137), __INT32_C(0x79e809), __INT32_C(0xaf9149), __INT32_C(0x0d73de), __INT32_C(0x0b0da5), __INT32_C(0xce7f58),
	__INT32_C(0xac1934), __INT32_C(0x724667), __INT32_C(0x7a1a13), __INT32_C(0x9e26bc), __INT32_C(0x4555e7), __INT32_C(0x585cb5),
	__INT32_C(0x711d14), __INT32_C(0x486991), __INT32_C(0x480d60), __INT32_C(0x56adab), __INT32_C(0xd62f64), __INT32_C(0x96ee0c),
	__INT32_C(0x212ff3), __INT32_C(0x5d6d88), __INT32_C(0xa67684), __INT32_C(0x95651e), __INT32_C(0xab9e0a), __INT32_C(0x4ddefe),
	__INT32_C(0x571010), __INT32_C(0x836a39), __INT32_C(0xf8ea31), __INT32_C(0x9e381d), __INT32_C(0xeac8b1), __INT32_C(0xcac96b),
	__INT32_C(0x37f21e), __INT32_C(0xd505e9), __INT32_C(0x984743), __INT32_C(0x9fc56c), __INT32_C(0x0331b7), __INT32_C(0x3b8bf8),
	__INT32_C(0x86e56a), __INT32_C(0x8dc343), __INT32_C(0x6230e7), __INT32_C(0x93cfd5), __INT32_C(0x6a8f2d), __INT32_C(0x733005),
	__INT32_C(0x1af021), __INT32_C(0xa09fcb), __INT32_C(0x7415a1), __INT32_C(0xd56b23), __INT32_C(0x6ff725), __INT32_C(0x2f4bc7),
	__INT32_C(0xb8a591), __INT32_C(0x7fac59), __INT32_C(0x5c55de), __INT32_C(0x212c38), __INT32_C(0xb13296), __INT32_C(0x5cff50),
	__INT32_C(0x366262), __INT32_C(0xfa7b16), __INT32_C(0xf4d9a6), __INT32_C(0x2acfe7), __INT32_C(0xf07403), __INT32_C(0xd4d604),
	__INT32_C(0x6fd916), __INT32_C(0x31b1bf), __INT32_C(0xcbb450), __INT32_C(0x5bd7c8), __INT32_C(0x0ce194), __INT32_C(0x6bd643),
	__INT32_C(0x4fd91c), __INT32_C(0xdf4543), __INT32_C(0x5f3453), __INT32_C(0xe2b5aa), __INT32_C(0xc9aec8), __INT32_C(0x131485),
	__INT32_C(0xf9d2bf), __INT32_C(0xbadb9e), __INT32_C(0x76f5b9), __INT32_C(0xaf15cf), __INT32_C(0xca3182), __INT32_C(0x14b56d),
	__INT32_C(0xe9fe4d), __INT32_C(0x50fc35), __INT32_C(0xf5aed5), __INT32_C(0xa2d0c1), __INT32_C(0xc96057), __INT32_C(0x192eb6),
	__INT32_C(0xe91d92), __INT32_C(0x07d144), __INT32_C(0xaea3c6), __INT32_C(0x343566), __INT32_C(0x26d5b4), __INT32_C(0x3161e2),
	__INT32_C(0x37f1a2), __INT32_C(0x209eff), __INT32_C(0x958e23), __INT32_C(0x493798), __INT32_C(0x35f4a6), __INT32_C(0x4bdc02),
	__INT32_C(0xc2be13), __INT32_C(0xbe80a0), __INT32_C(0x0b72a3), __INT32_C(0x115c5f), __INT32_C(0x1e1bd1), __INT32_C(0x0db4d3),
	__INT32_C(0x869e85), __INT32_C(0x96976b), __INT32_C(0x2ac91f), __INT32_C(0x8a26c2), __INT32_C(0x3070f0), __INT32_C(0x041412),
	__INT32_C(0xfc9fa5), __INT32_C(0xf72a38), __INT32_C(0x9c6878), __INT32_C(0xe2aa76), __INT32_C(0x50cfe1), __INT32_C(0x559274),
	__INT32_C(0x934e38), __INT32_C(0x0a92f7), __INT32_C(0x5533f0), __INT32_C(0xa63db4), __INT32_C(0x399971), __INT32_C(0xe2b755),
	__INT32_C(0xa98a7c), __INT32_C(0x008f19), __INT32_C(0xac54d2), __INT32_C(0x2ea0b4), __INT32_C(0xf5f3e0), __INT32_C(0x60c849),
	__INT32_C(0xffd269), __INT32_C(0xae52ce), __INT32_C(0x7a5fdd), __INT32_C(0xe9ce06), __INT32_C(0xfb0ae8), __INT32_C(0xa50cce),
	__INT32_C(0xea9d3e), __INT32_C(0x3766dd), __INT32_C(0xb834f5), __INT32_C(0x0da090), __INT32_C(0x846f88), __INT32_C(0x4ae3d5),
	__INT32_C(0x099a03), __INT32_C(0x2eae2d), __INT32_C(0xfcb40a), __INT32_C(0xfb9b33), __INT32_C(0xe281dd), __INT32_C(0x1b16ba),
	__INT32_C(0xd8c0af), __INT32_C(0xd96b97), __INT32_C(0xb52dc9), __INT32_C(0x9c277f), __INT32_C(0x5951d5), __INT32_C(0x21ccd6),
	__INT32_C(0xb6496b), __INT32_C(0x584562), __INT32_C(0xb3baf2), __INT32_C(0xa1a5c4), __INT32_C(0x7ca2cf), __INT32_C(0xa9b93d),
	__INT32_C(0x7b7b89), __INT32_C(0x483d38)
};
__LIBM_LOCAL_DECLARE_END

__LIBM_LOCAL_FUNC(kernel_rem_pio2l) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __int32_t
(__LIBCCALL __ieee854_kernel_rem_pio2l)(__IEEE754_DOUBLE_TYPE__ *__x, __IEEE754_DOUBLE_TYPE__ *__y,
                                        __int32_t __e0, __int32_t __nx, int __prec) {
	__int32_t __jz, __jx, __jv, __jp, __jk, __carry;
	__int32_t __n, __iq[20], __i, __j, __k, __m, __q0, __ih;
	__IEEE754_DOUBLE_TYPE__ __z, __fw, __f[20], __fq[20], __q[20];

	/* initialize jk */
	__jk = __LIBM_LOCAL_VALUE(init_jk)[__prec];
	__jp = __jk;

	/* determine jx,jv,q0, note that 3>q0 */
	__jx = __nx - 1;
	__jv = (__e0 - 3) / 24;
	if (__jv < 0)
		__jv = 0;
	__q0 = __e0 - 24 * (__jv + 1);

	/* set up f[0] to f[jx+jk] where f[jx+jk] = two_over_pi[jv+jk] */
	__j = __jv - __jx;
	__m = __jx + __jk;
	for (__i = 0; __i <= __m; ++__i, __j++)
		__f[__i] = (__j < 0) ? __LIBM_LOCAL_VALUE(zero) : (__IEEE754_DOUBLE_TYPE__)__LIBM_LOCAL_VALUE(two_over_pil)[__j];

	/* compute q[0],q[1],...q[jk] */
	for (__i = 0; __i <= __jk; ++__i) {
		for (__j = 0, __fw = 0.0; __j <= __jx; __j++)
			__fw += __x[__j] * __f[__jx + __i - __j];
		__q[__i] = __fw;
	}

	__jz = __jk;
recompute:
	/* distill q[] into iq[] reversingly */
	for (__i = 0, __j = __jz, __z = __q[__jz]; __j > 0; ++__i, --__j) {
		__fw      = (__IEEE754_DOUBLE_TYPE__)((__int32_t)(__LIBM_LOCAL_VALUE(twon24) * __z));
		__iq[__i] = (__int32_t)(__z - __LIBM_LOCAL_VALUE(two24) * __fw);
		__z       = __q[__j - 1] + __fw;
	}

	/* compute n */
	__z = __ieee754_scalbn(__z, (int)__q0);    /* actual value of z */
	__z -= 8.0 * __ieee754_floor(__z * 0.125); /* trim off integer >= 8 */
	__n = (__int32_t)__z;
	__z -= (__IEEE754_DOUBLE_TYPE__)__n;
	__ih = 0;
	if (__q0 > 0) { /* need iq[jz-1] to determine n */
		__i = (__iq[__jz - 1] >> (24 - __q0));
		__n += __i;
		__iq[__jz - 1] -= __i << (24 - __q0);
		__ih = __iq[__jz - 1] >> (23 - __q0);
	} else if (__q0 == 0) {
		__ih = __iq[__jz - 1] >> 23;
	} else if (__z >= 0.5) {
		__ih = 2;
	}

	if (__ih > 0) { /* q > 0.5 */
		__n += 1;
		__carry = 0;
		for (__i = 0; __i < __jz; ++__i) { /* compute 1-q */
			__j = __iq[__i];
			if (__carry == 0) {
				if (__j != 0) {
					__carry   = 1;
					__iq[__i] = __INT32_C(0x1000000) - __j;
				}
			} else
				__iq[__i] = __INT32_C(0xffffff) - __j;
		}
		if (__q0 > 0) { /* rare case: chance is 1 in 12 */
			switch ((int)__q0) {
			case 1:
				__iq[__jz - 1] &= __INT32_C(0x7fffff);
				break;
			case 2:
				__iq[__jz - 1] &= __INT32_C(0x3fffff);
				break;
			}
		}
		if (__ih == 2) {
			__z = __LIBM_LOCAL_VALUE(one) - __z;
			if (__carry != 0)
				__z -= __ieee754_scalbn(__LIBM_LOCAL_VALUE(one), (int)__q0);
		}
	}

	/* check if recomputation is needed */
	if (__z == __LIBM_LOCAL_VALUE(zero)) {
		__j = 0;
		for (__i = __jz - 1; __i >= __jk; --__i)
			__j |= __iq[__i];
		if (__j == 0) { /* need recomputation */
			for (__k = 1; __iq[__jk - __k] == 0; ++__k)
				; /* k = no. of terms needed */

			for (__i = __jz + 1; __i <= __jz + __k; ++__i) { /* add q[jz+1] to q[jz+k] */
				__f[__jx + __i] = (__IEEE754_DOUBLE_TYPE__)__LIBM_LOCAL_VALUE(two_over_pil)[__jv + __i];
				for (__j = 0, __fw = 0.0; __j <= __jx; __j++)
					__fw += __x[__j] * __f[__jx + __i - __j];
				__q[__i] = __fw;
			}
			__jz += __k;
			goto recompute;
		}
	}

	/* chop off zero terms */
	if (__z == 0.0) {
		__jz -= 1;
		__q0 -= 24;
		while (__iq[__jz] == 0) {
			__jz--;
			__q0 -= 24;
		}
	} else { /* break z into 24-bit if necessary */
		__z = __ieee754_scalbn(__z, (int)-__q0);
		if (__z >= __LIBM_LOCAL_VALUE(two24)) {
			__fw       = (__IEEE754_DOUBLE_TYPE__)((__int32_t)(__LIBM_LOCAL_VALUE(twon24) * __z));
			__iq[__jz] = (__int32_t)(__z - __LIBM_LOCAL_VALUE(two24) * __fw);
			__jz += 1;
			__q0 += 24;
			__iq[__jz] = (__int32_t)__fw;
		} else {
			__iq[__jz] = (__int32_t)__z;
		}
	}

	/* convert integer "bit" chunk to floating-point value */
	__fw = __ieee754_scalbn(__LIBM_LOCAL_VALUE(one), (int)__q0);
	for (__i = __jz; __i >= 0; --__i) {
		__q[__i] = __fw * (__IEEE754_DOUBLE_TYPE__)__iq[__i];
		__fw *= __LIBM_LOCAL_VALUE(twon24);
	}

	/* compute PIo2[0,...,jp]*q[jz,...,0] */
	for (__i = __jz; __i >= 0; --__i) {
		for (__fw = 0.0, __k = 0; __k <= __jp && __k <= __jz - __i; ++__k)
			__fw += __LIBM_LOCAL_VALUE(PIo2)[__k] * __q[__i + __k];
		__fq[__jz - __i] = __fw;
	}

	/* compress fq[] into y[] */
	switch (__prec) {
	case 0:
		__fw = 0.0;
		for (__i = __jz; __i >= 0; --__i)
			__fw += __fq[__i];
		__y[0] = (__ih == 0) ? __fw : -__fw;
		break;
	case 1:
	case 2: {
		volatile __IEEE754_DOUBLE_TYPE__ fv = 0.0;
		for (__i = __jz; __i >= 0; --__i)
			fv += __fq[__i];
		__y[0] = (__ih == 0) ? fv : -fv;
		fv   = __fq[0] - fv;
		for (__i = 1; __i <= __jz; ++__i)
			fv += __fq[__i];
		__y[1] = (__ih == 0) ? fv : -fv;
	}	break;
	case 3: /* painful */
		for (__i = __jz; __i > 0; --__i) {
			volatile __IEEE754_DOUBLE_TYPE__ fv = (__IEEE754_DOUBLE_TYPE__)(__fq[__i - 1] + __fq[__i]);
			__fq[__i] += __fq[__i - 1] - fv;
			__fq[__i - 1] = fv;
		}
		for (__i = __jz; __i > 1; --__i) {
			volatile __IEEE754_DOUBLE_TYPE__ fv = (__IEEE754_DOUBLE_TYPE__)(__fq[__i - 1] + __fq[__i]);
			__fq[__i] += __fq[__i - 1] - fv;
			__fq[__i - 1] = fv;
		}
		for (__fw = 0.0, __i = __jz; __i >= 2; --__i)
			__fw += __fq[__i];
		if (__ih == 0) {
			__y[0] = __fq[0];
			__y[1] = __fq[1];
			__y[2] = __fw;
		} else {
			__y[0] = -__fq[0];
			__y[1] = -__fq[1];
			__y[2] = -__fw;
		}
	}
	return __n & 7;
}
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_KERNEL_REM_PIO2_H */
