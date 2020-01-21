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
#ifndef _LIBM_ATAN_H
#define _LIBM_ATAN_H 1

#include <__crt.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/fabs.h>
#include <libm/fdlibm.h>

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
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, atanhif, 4, {
	__IEEE754_FLOAT_C(4.6364760399e-01), /* atan(0.5)hi 0x3eed6338 */
	__IEEE754_FLOAT_C(7.8539812565e-01), /* atan(1.0)hi 0x3f490fda */
	__IEEE754_FLOAT_C(9.8279368877e-01), /* atan(1.5)hi 0x3f7b985e */
	__IEEE754_FLOAT_C(1.5707962513e+00), /* atan(inf)hi 0x3fc90fda */
})
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, atanlof, 4, {
	__IEEE754_FLOAT_C(5.0121582440e-09), /* atan(0.5)lo 0x31ac3769 */
	__IEEE754_FLOAT_C(3.7748947079e-08), /* atan(1.0)lo 0x33222168 */
	__IEEE754_FLOAT_C(3.4473217170e-08), /* atan(1.5)lo 0x33140fb4 */
	__IEEE754_FLOAT_C(7.5497894159e-08), /* atan(inf)lo 0x33a22168 */
})
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, aTf, 11, {
	 __IEEE754_FLOAT_C(3.3333334327e-01), /* 0x3eaaaaaa */
	-__IEEE754_FLOAT_C(2.0000000298e-01), /* 0xbe4ccccd */
	 __IEEE754_FLOAT_C(1.4285714924e-01), /* 0x3e124925 */
	-__IEEE754_FLOAT_C(1.1111110449e-01), /* 0xbde38e38 */
	 __IEEE754_FLOAT_C(9.0908870101e-02), /* 0x3dba2e6e */
	-__IEEE754_FLOAT_C(7.6918758452e-02), /* 0xbd9d8795 */
	 __IEEE754_FLOAT_C(6.6610731184e-02), /* 0x3d886b35 */
	-__IEEE754_FLOAT_C(5.8335702866e-02), /* 0xbd6ef16b */
	 __IEEE754_FLOAT_C(4.9768779427e-02), /* 0x3d4bda59 */
	-__IEEE754_FLOAT_C(3.6531571299e-02), /* 0xbd15a221 */
	 __IEEE754_FLOAT_C(1.6285819933e-02), /* 0x3c8569d7 */
})
#ifndef __libm_onef_defined
#define __libm_onef_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0))
#endif /* !__libm_onef_defined */
#ifndef __libm_hugef_defined
#define __libm_hugef_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, hugef, __IEEE754_FLOAT_C(1.0e30))
#endif /* !__libm_hugef_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_FLOAT_TYPE__
(__LIBCCALL __ieee754_atanf)(__IEEE754_FLOAT_TYPE__ __x) {
	__IEEE754_FLOAT_TYPE__ __w, __s1, __s2, __z;
	__int32_t __ix, __hx, __id;

	__LIBM_GET_FLOAT_WORD(__hx, __x);
	__ix = __hx & 0x7fffffff;
	if (__ix >= 0x50800000) { /* if |x| >= 2^34 */
		if (__LIBM_FLT_UWORD_IS_NAN(__ix))
			return __x + __x; /* NaN */
		if (__hx > 0)
			return __LIBM_LOCAL_VALUE(atanhif)[3] + __LIBM_LOCAL_VALUE(atanlof)[3];
		else {
			return -__LIBM_LOCAL_VALUE(atanhif)[3] - __LIBM_LOCAL_VALUE(atanlof)[3];
		}
	}
	if (__ix < 0x3ee00000) {     /* |x| < 0.4375 */
		if (__ix < 0x31000000) { /* |x| < 2^-29 */
			if (__LIBM_LOCAL_VALUE(hugef) + __x > __LIBM_LOCAL_VALUE(onef))
				return __x; /* raise inexact */
		}
		__id = -1;
	} else {
		__x = __ieee754_fabsf(__x);
		if (__ix < 0x3f980000) {     /* |x| < 1.1875 */
			if (__ix < 0x3f300000) { /* 7/16 <=|x|<11/16 */
				__id = 0;
				__x  = (__IEEE754_FLOAT_C(2.0) * __x - __LIBM_LOCAL_VALUE(onef)) / (__IEEE754_FLOAT_C(2.0) + __x);
			} else { /* 11/16<=|x|< 19/16 */
				__id = 1;
				__x  = (__x - __LIBM_LOCAL_VALUE(onef)) / (__x + __LIBM_LOCAL_VALUE(onef));
			}
		} else {
			if (__ix < 0x401c0000) { /* |x| < 2.4375 */
				__id = 2;
				__x  = (__x - __IEEE754_FLOAT_C(1.5)) / (__LIBM_LOCAL_VALUE(onef) + __IEEE754_FLOAT_C(1.5) * __x);
			} else { /* 2.4375 <= |x| < 2^66 */
				__id = 3;
				__x  = -__IEEE754_FLOAT_C(1.0) / __x;
			}
		}
	}
	/* end of argument reduction */
	__z = __x * __x;
	__w = __z * __z;
	/* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
	__s1 = __z * (__LIBM_LOCAL_VALUE(aTf)[0] +
	              __w * (__LIBM_LOCAL_VALUE(aTf)[2] +
	                     __w * (__LIBM_LOCAL_VALUE(aTf)[4] +
	                            __w * (__LIBM_LOCAL_VALUE(aTf)[6] +
	                                   __w * (__LIBM_LOCAL_VALUE(aTf)[8] +
	                                          __w * __LIBM_LOCAL_VALUE(aTf)[10])))));
	__s2 = __w * (__LIBM_LOCAL_VALUE(aTf)[1] +
	              __w * (__LIBM_LOCAL_VALUE(aTf)[3] +
	                     __w * (__LIBM_LOCAL_VALUE(aTf)[5] +
	                            __w * (__LIBM_LOCAL_VALUE(aTf)[7] +
	                                   __w * __LIBM_LOCAL_VALUE(aTf)[9]))));
	if (__id < 0)
		return __x - __x * (__s1 + __s2);
	else {
		__z = __LIBM_LOCAL_VALUE(atanhif)[__id] - ((__x * (__s1 + __s2) - __LIBM_LOCAL_VALUE(atanlof)[__id]) - __x);
		return (__hx < 0) ? -__z : __z;
	}
}

#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
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
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, atanhi, 4, {
	__IEEE754_DOUBLE_C(4.63647609000806093515e-01), /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
	__IEEE754_DOUBLE_C(7.85398163397448278999e-01), /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
	__IEEE754_DOUBLE_C(9.82793723247329054082e-01), /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
	__IEEE754_DOUBLE_C(1.57079632679489655800e+00), /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
})
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, atanlo, 4, {
	__IEEE754_DOUBLE_C(2.26987774529616870924e-17), /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
	__IEEE754_DOUBLE_C(3.06161699786838301793e-17), /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
	__IEEE754_DOUBLE_C(1.39033110312309984516e-17), /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
	__IEEE754_DOUBLE_C(6.12323399573676603587e-17), /* atan(inf)lo 0x3C91A626, 0x33145C07 */
})
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, aT, 11, {
		 __IEEE754_DOUBLE_C(3.33333333333329318027e-01), /* 0x3FD55555, 0x5555550D */
		-__IEEE754_DOUBLE_C(1.99999999998764832476e-01), /* 0xBFC99999, 0x9998EBC4 */
		 __IEEE754_DOUBLE_C(1.42857142725034663711e-01), /* 0x3FC24924, 0x920083FF */
		-__IEEE754_DOUBLE_C(1.11111104054623557880e-01), /* 0xBFBC71C6, 0xFE231671 */
		 __IEEE754_DOUBLE_C(9.09088713343650656196e-02), /* 0x3FB745CD, 0xC54C206E */
		-__IEEE754_DOUBLE_C(7.69187620504482999495e-02), /* 0xBFB3B0F2, 0xAF749A6D */
		 __IEEE754_DOUBLE_C(6.66107313738753120669e-02), /* 0x3FB10D66, 0xA0D03D51 */
		-__IEEE754_DOUBLE_C(5.83357013379057348645e-02), /* 0xBFADDE2D, 0x52DEFD9A */
		 __IEEE754_DOUBLE_C(4.97687799461593236017e-02), /* 0x3FA97B4B, 0x24760DEB */
		-__IEEE754_DOUBLE_C(3.65315727442169155270e-02), /* 0xBFA2B444, 0x2C6A6C2F */
		 __IEEE754_DOUBLE_C(1.62858201153657823623e-02), /* 0x3F90AD3A, 0xE322DA11 */
})
#ifndef __libm_one_defined
#define __libm_one_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
#ifndef __libm_huge_defined
#define __libm_huge_defined 1
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, huge, __IEEE754_DOUBLE_C(1.0e300))
#endif /* !__libm_huge_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE754_DOUBLE_TYPE__
(__LIBCCALL __ieee754_atan)(__IEEE754_DOUBLE_TYPE__ __x) {
	__IEEE754_DOUBLE_TYPE__ __w, __s1, __s2, __z;
	__int32_t __ix, __hx, __id;
	__LIBM_GET_HIGH_WORD(__hx, __x);
	__ix = __hx & 0x7fffffff;
	if (__ix >= 0x44100000) { /* if |x| >= 2^66 */
		__uint32_t low;
		__LIBM_GET_LOW_WORD(low, __x);
		if (__ix > 0x7ff00000 ||
		    (__ix == 0x7ff00000 && (low != 0)))
			return __x + __x; /* NaN */
		if (__hx > 0)
			return __LIBM_LOCAL_VALUE(atanhi)[3] + __LIBM_LOCAL_VALUE(atanlo)[3];
		else {
			return -__LIBM_LOCAL_VALUE(atanhi)[3] - __LIBM_LOCAL_VALUE(atanlo)[3];
		}
	}
	if (__ix < 0x3fdc0000) {     /* |x| < 0.4375 */
		if (__ix < 0x3e200000) { /* |x| < 2^-29 */
			if (__LIBM_LOCAL_VALUE(huge) + __x > __LIBM_LOCAL_VALUE(one))
				return __x; /* raise inexact */
		}
		__id = -1;
	} else {
		__x = __ieee754_fabs(__x);
		if (__ix < 0x3ff30000) {     /* |x| < 1.1875 */
			if (__ix < 0x3fe60000) { /* 7/16 <=|x|<11/16 */
				__id = 0;
				__x  = (__IEEE754_DOUBLE_C(2.0) * __x - __LIBM_LOCAL_VALUE(one)) / (__IEEE754_DOUBLE_C(2.0) + __x);
			} else { /* 11/16<=|x|< 19/16 */
				__id = 1;
				__x  = (__x - __LIBM_LOCAL_VALUE(one)) / (__x + __LIBM_LOCAL_VALUE(one));
			}
		} else {
			if (__ix < 0x40038000) { /* |x| < 2.4375 */
				__id = 2;
				__x  = (__x - __IEEE754_DOUBLE_C(1.5)) / (__LIBM_LOCAL_VALUE(one) + __IEEE754_DOUBLE_C(1.5) * __x);
			} else { /* 2.4375 <= |x| < 2^66 */
				__id = 3;
				__x  = -__IEEE754_DOUBLE_C(1.0) / __x;
			}
		}
	}
	/* end of argument reduction */
	__z = __x * __x;
	__w = __z * __z;
	/* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
	__s1 = __z * (__LIBM_LOCAL_VALUE(aT)[0] +
	              __w * (__LIBM_LOCAL_VALUE(aT)[2] +
	                     __w * (__LIBM_LOCAL_VALUE(aT)[4] +
	                            __w * (__LIBM_LOCAL_VALUE(aT)[6] +
	                                   __w * (__LIBM_LOCAL_VALUE(aT)[8] +
	                                          __w * __LIBM_LOCAL_VALUE(aT)[10])))));
	__s2 = __w * (__LIBM_LOCAL_VALUE(aT)[1] +
	              __w * (__LIBM_LOCAL_VALUE(aT)[3] +
	                     __w * (__LIBM_LOCAL_VALUE(aT)[5] +
	                            __w * (__LIBM_LOCAL_VALUE(aT)[7] +
	                                   __w * __LIBM_LOCAL_VALUE(aT)[9]))));
	if (__id < 0)
		return __x - __x * (__s1 + __s2);
	else {
		__z = __LIBM_LOCAL_VALUE(atanhi)[__id] - ((__x * (__s1 + __s2) - __LIBM_LOCAL_VALUE(atanlo)[__id]) - __x);
		return (__hx < 0) ? -__z : __z;
	}
}

#endif /* __IEEE754_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_LIBM_ATAN_H */
