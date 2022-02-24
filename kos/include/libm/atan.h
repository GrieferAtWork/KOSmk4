/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBM_ATAN_H
#define _LIBM_ATAN_H 1

#include <__crt.h>

#ifndef __NO_FPU
#include <hybrid/typecore.h>

#include <bits/types.h>

#include <libm/asm/atan.h>
#include <libm/fabs.h>
#include <libm/fdlibm.h>
#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#include <libm/isnan.h>
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

#ifdef __CC__
__DECL_BEGIN

#ifdef __IEEE754_FLOAT_TYPE__
#ifndef __ieee754_atanf
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
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, atanhif, 4) {
	__IEEE754_FLOAT_C(4.6364760399e-01), /* atan(0.5)hi 0x3eed6338 */
	__IEEE754_FLOAT_C(7.8539812565e-01), /* atan(1.0)hi 0x3f490fda */
	__IEEE754_FLOAT_C(9.8279368877e-01), /* atan(1.5)hi 0x3f7b985e */
	__IEEE754_FLOAT_C(1.5707962513e+00), /* atan(inf)hi 0x3fc90fda */
};
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, atanlof, 4) {
	__IEEE754_FLOAT_C(5.0121582440e-09), /* atan(0.5)lo 0x31ac3769 */
	__IEEE754_FLOAT_C(3.7748947079e-08), /* atan(1.0)lo 0x33222168 */
	__IEEE754_FLOAT_C(3.4473217170e-08), /* atan(1.5)lo 0x33140fb4 */
	__IEEE754_FLOAT_C(7.5497894159e-08), /* atan(inf)lo 0x33a22168 */
};
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_FLOAT_TYPE__, aTf, 11) {
	__IEEE754_FLOAT_C( 3.3333334327e-01), /* 0x3eaaaaaa */
	__IEEE754_FLOAT_C(-2.0000000298e-01), /* 0xbe4ccccd */
	__IEEE754_FLOAT_C( 1.4285714924e-01), /* 0x3e124925 */
	__IEEE754_FLOAT_C(-1.1111110449e-01), /* 0xbde38e38 */
	__IEEE754_FLOAT_C( 9.0908870101e-02), /* 0x3dba2e6e */
	__IEEE754_FLOAT_C(-7.6918758452e-02), /* 0xbd9d8795 */
	__IEEE754_FLOAT_C( 6.6610731184e-02), /* 0x3d886b35 */
	__IEEE754_FLOAT_C(-5.8335702866e-02), /* 0xbd6ef16b */
	__IEEE754_FLOAT_C( 4.9768779427e-02), /* 0x3d4bda59 */
	__IEEE754_FLOAT_C(-3.6531571299e-02), /* 0xbd15a221 */
	__IEEE754_FLOAT_C( 1.6285819933e-02), /* 0x3c8569d7 */
};
#ifndef __libm_onef_defined
#define __libm_onef_defined
__LIBM_LOCAL_DECLARE(__IEEE754_FLOAT_TYPE__, onef, __IEEE754_FLOAT_C(1.0000000000e+00)) /* 0x3F800000 */
#endif /* !__libm_onef_defined */
#ifndef __libm_hugef_defined
#define __libm_hugef_defined
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
			if (__ix < 0x3f300000) { /* 7/16 <=|x| < 11/16 */
				__id = 0;
				__x  = (__IEEE754_FLOAT_C(2.0) * __x - __LIBM_LOCAL_VALUE(onef)) / (__IEEE754_FLOAT_C(2.0) + __x);
			} else { /* 11/16<=|x| <  19/16 */
				__id = 1;
				__x  = (__x - __LIBM_LOCAL_VALUE(onef)) / (__x + __LIBM_LOCAL_VALUE(onef));
			}
		} else {
			if (__ix < 0x401c0000) { /* |x| < 2.4375 */
				__id = 2;
				__x  = (__x - __IEEE754_FLOAT_C(1.5)) / (__LIBM_LOCAL_VALUE(onef) + __IEEE754_FLOAT_C(1.5) * __x);
			} else { /* 2.4375 <= |x| < 2^66 */
				__id = 3;
				__x  = __IEEE754_FLOAT_C(-1.0) / __x;
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
#endif /* !__ieee754_atanf */
#endif /* __IEEE754_FLOAT_TYPE__ */


#ifdef __IEEE754_DOUBLE_TYPE__
#ifndef __ieee754_atan
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
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, atanhi, 4) {
	__IEEE754_DOUBLE_C(4.63647609000806093515e-01), /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
	__IEEE754_DOUBLE_C(7.85398163397448278999e-01), /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
	__IEEE754_DOUBLE_C(9.82793723247329054082e-01), /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
	__IEEE754_DOUBLE_C(1.57079632679489655800e+00), /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
};
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, atanlo, 4) {
	__IEEE754_DOUBLE_C(2.26987774529616870924e-17), /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
	__IEEE754_DOUBLE_C(3.06161699786838301793e-17), /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
	__IEEE754_DOUBLE_C(1.39033110312309984516e-17), /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
	__IEEE754_DOUBLE_C(6.12323399573676603587e-17), /* atan(inf)lo 0x3C91A626, 0x33145C07 */
};
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE754_DOUBLE_TYPE__, aT, 11) {
		__IEEE754_DOUBLE_C( 3.33333333333329318027e-01), /* 0x3FD55555, 0x5555550D */
		__IEEE754_DOUBLE_C(-1.99999999998764832476e-01), /* 0xBFC99999, 0x9998EBC4 */
		__IEEE754_DOUBLE_C( 1.42857142725034663711e-01), /* 0x3FC24924, 0x920083FF */
		__IEEE754_DOUBLE_C(-1.11111104054623557880e-01), /* 0xBFBC71C6, 0xFE231671 */
		__IEEE754_DOUBLE_C( 9.09088713343650656196e-02), /* 0x3FB745CD, 0xC54C206E */
		__IEEE754_DOUBLE_C(-7.69187620504482999495e-02), /* 0xBFB3B0F2, 0xAF749A6D */
		__IEEE754_DOUBLE_C( 6.66107313738753120669e-02), /* 0x3FB10D66, 0xA0D03D51 */
		__IEEE754_DOUBLE_C(-5.83357013379057348645e-02), /* 0xBFADDE2D, 0x52DEFD9A */
		__IEEE754_DOUBLE_C( 4.97687799461593236017e-02), /* 0x3FA97B4B, 0x24760DEB */
		__IEEE754_DOUBLE_C(-3.65315727442169155270e-02), /* 0xBFA2B444, 0x2C6A6C2F */
		__IEEE754_DOUBLE_C( 1.62858201153657823623e-02), /* 0x3F90AD3A, 0xE322DA11 */
};
#ifndef __libm_one_defined
#define __libm_one_defined
__LIBM_LOCAL_DECLARE(__IEEE754_DOUBLE_TYPE__, one, __IEEE754_DOUBLE_C(1.0))
#endif /* !__libm_one_defined */
#ifndef __libm_huge_defined
#define __libm_huge_defined
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
			if (__ix < 0x3fe60000) { /* 7/16 <=|x| < 11/16 */
				__id = 0;
				__x  = (__IEEE754_DOUBLE_C(2.0) * __x - __LIBM_LOCAL_VALUE(one)) / (__IEEE754_DOUBLE_C(2.0) + __x);
			} else { /* 11/16<=|x| <  19/16 */
				__id = 1;
				__x  = (__x - __LIBM_LOCAL_VALUE(one)) / (__x + __LIBM_LOCAL_VALUE(one));
			}
		} else {
			if (__ix < 0x40038000) { /* |x| < 2.4375 */
				__id = 2;
				__x  = (__x - __IEEE754_DOUBLE_C(1.5)) / (__LIBM_LOCAL_VALUE(one) + __IEEE754_DOUBLE_C(1.5) * __x);
			} else { /* 2.4375 <= |x| < 2^66 */
				__id = 3;
				__x  = __IEEE754_DOUBLE_C(-1.0) / __x;
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
#endif /* !__ieee754_atan */
#endif /* __IEEE754_DOUBLE_TYPE__ */


#ifdef __IEEE854_LONG_DOUBLE_TYPE__
#ifndef __ieee854_atanl
/* Copyright 2001 by Stephen L. Moshier <moshier@na-net.ornl.gov>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, see
    <http://www.gnu.org/licenses/>.  */



__LIBM_LOCAL_DECLARE_BEGIN
/* arctan(k/8), k = 0, ..., 82 */
__LIBM_LOCAL_DECLARE_ARRAY(__IEEE854_LONG_DOUBLE_TYPE__, atantbll, 84) {
	__IEEE854_LONG_DOUBLE_C(0.0000000000000000000000000000000000000000E0),
	__IEEE854_LONG_DOUBLE_C(1.2435499454676143503135484916387102557317E-1), /* arctan(0.125)  */
	__IEEE854_LONG_DOUBLE_C(2.4497866312686415417208248121127581091414E-1),
	__IEEE854_LONG_DOUBLE_C(3.5877067027057222039592006392646049977698E-1),
	__IEEE854_LONG_DOUBLE_C(4.6364760900080611621425623146121440202854E-1),
	__IEEE854_LONG_DOUBLE_C(5.5859931534356243597150821640166127034645E-1),
	__IEEE854_LONG_DOUBLE_C(6.4350110879328438680280922871732263804151E-1),
	__IEEE854_LONG_DOUBLE_C(7.1882999962162450541701415152590465395142E-1),
	__IEEE854_LONG_DOUBLE_C(7.8539816339744830961566084581987572104929E-1),
	__IEEE854_LONG_DOUBLE_C(8.4415398611317100251784414827164750652594E-1),
	__IEEE854_LONG_DOUBLE_C(8.9605538457134395617480071802993782702458E-1),
	__IEEE854_LONG_DOUBLE_C(9.4200004037946366473793717053459358607166E-1),
	__IEEE854_LONG_DOUBLE_C(9.8279372324732906798571061101466601449688E-1),
	__IEEE854_LONG_DOUBLE_C(1.0191413442663497346383429170230636487744E0),
	__IEEE854_LONG_DOUBLE_C(1.0516502125483736674598673120862998296302E0),
	__IEEE854_LONG_DOUBLE_C(1.0808390005411683108871567292171998202703E0),
	__IEEE854_LONG_DOUBLE_C(1.1071487177940905030170654601785370400700E0),
	__IEEE854_LONG_DOUBLE_C(1.1309537439791604464709335155363278047493E0),
	__IEEE854_LONG_DOUBLE_C(1.1525719972156675180401498626127513797495E0),
	__IEEE854_LONG_DOUBLE_C(1.1722738811284763866005949441337046149712E0),
	__IEEE854_LONG_DOUBLE_C(1.1902899496825317329277337748293183376012E0),
	__IEEE854_LONG_DOUBLE_C(1.2068173702852525303955115800565576303133E0),
	__IEEE854_LONG_DOUBLE_C(1.2220253232109896370417417439225704908830E0),
	__IEEE854_LONG_DOUBLE_C(1.2360594894780819419094519711090786987027E0),
	__IEEE854_LONG_DOUBLE_C(1.2490457723982544258299170772810901230778E0),
	__IEEE854_LONG_DOUBLE_C(1.2610933822524404193139408812473357720101E0),
	__IEEE854_LONG_DOUBLE_C(1.2722973952087173412961937498224804940684E0),
	__IEEE854_LONG_DOUBLE_C(1.2827408797442707473628852511364955306249E0),
	__IEEE854_LONG_DOUBLE_C(1.2924966677897852679030914214070816845853E0),
	__IEEE854_LONG_DOUBLE_C(1.3016288340091961438047858503666855921414E0),
	__IEEE854_LONG_DOUBLE_C(1.3101939350475556342564376891719053122733E0),
	__IEEE854_LONG_DOUBLE_C(1.3182420510168370498593302023271362531155E0),
	__IEEE854_LONG_DOUBLE_C(1.3258176636680324650592392104284756311844E0),
	__IEEE854_LONG_DOUBLE_C(1.3329603993374458675538498697331558093700E0),
	__IEEE854_LONG_DOUBLE_C(1.3397056595989995393283037525895557411039E0),
	__IEEE854_LONG_DOUBLE_C(1.3460851583802539310489409282517796256512E0),
	__IEEE854_LONG_DOUBLE_C(1.3521273809209546571891479413898128509842E0),
	__IEEE854_LONG_DOUBLE_C(1.3578579772154994751124898859640585287459E0),
	__IEEE854_LONG_DOUBLE_C(1.3633001003596939542892985278250991189943E0),
	__IEEE854_LONG_DOUBLE_C(1.3684746984165928776366381936948529556191E0),
	__IEEE854_LONG_DOUBLE_C(1.3734007669450158608612719264449611486510E0),
	__IEEE854_LONG_DOUBLE_C(1.3780955681325110444536609641291551522494E0),
	__IEEE854_LONG_DOUBLE_C(1.3825748214901258580599674177685685125566E0),
	__IEEE854_LONG_DOUBLE_C(1.3868528702577214543289381097042486034883E0),
	__IEEE854_LONG_DOUBLE_C(1.3909428270024183486427686943836432060856E0),
	__IEEE854_LONG_DOUBLE_C(1.3948567013423687823948122092044222644895E0),
	__IEEE854_LONG_DOUBLE_C(1.3986055122719575950126700816114282335732E0),
	__IEEE854_LONG_DOUBLE_C(1.4021993871854670105330304794336492676944E0),
	__IEEE854_LONG_DOUBLE_C(1.4056476493802697809521934019958079881002E0),
	__IEEE854_LONG_DOUBLE_C(1.4089588955564736949699075250792569287156E0),
	__IEEE854_LONG_DOUBLE_C(1.4121410646084952153676136718584891599630E0),
	__IEEE854_LONG_DOUBLE_C(1.4152014988178669079462550975833894394929E0),
	__IEEE854_LONG_DOUBLE_C(1.4181469983996314594038603039700989523716E0),
	__IEEE854_LONG_DOUBLE_C(1.4209838702219992566633046424614466661176E0),
	__IEEE854_LONG_DOUBLE_C(1.4237179714064941189018190466107297503086E0),
	__IEEE854_LONG_DOUBLE_C(1.4263547484202526397918060597281265695725E0),
	__IEEE854_LONG_DOUBLE_C(1.4288992721907326964184700745371983590908E0),
	__IEEE854_LONG_DOUBLE_C(1.4313562697035588982240194668401779312122E0),
	__IEEE854_LONG_DOUBLE_C(1.4337301524847089866404719096698873648610E0),
	__IEEE854_LONG_DOUBLE_C(1.4360250423171655234964275337155008780675E0),
	__IEEE854_LONG_DOUBLE_C(1.4382447944982225979614042479354815855386E0),
	__IEEE854_LONG_DOUBLE_C(1.4403930189057632173997301031392126865694E0),
	__IEEE854_LONG_DOUBLE_C(1.4424730991091018200252920599377292525125E0),
	__IEEE854_LONG_DOUBLE_C(1.4444882097316563655148453598508037025938E0),
	__IEEE854_LONG_DOUBLE_C(1.4464413322481351841999668424758804165254E0),
	__IEEE854_LONG_DOUBLE_C(1.4483352693775551917970437843145232637695E0),
	__IEEE854_LONG_DOUBLE_C(1.4501726582147939000905940595923466567576E0),
	__IEEE854_LONG_DOUBLE_C(1.4519559822271314199339700039142990228105E0),
	__IEEE854_LONG_DOUBLE_C(1.4536875822280323362423034480994649820285E0),
	__IEEE854_LONG_DOUBLE_C(1.4553696664279718992423082296859928222270E0),
	__IEEE854_LONG_DOUBLE_C(1.4570043196511885530074841089245667532358E0),
	__IEEE854_LONG_DOUBLE_C(1.4585935117976422128825857356750737658039E0),
	__IEEE854_LONG_DOUBLE_C(1.4601391056210009726721818194296893361233E0),
	__IEEE854_LONG_DOUBLE_C(1.4616428638860188872060496086383008594310E0),
	__IEEE854_LONG_DOUBLE_C(1.4631064559620759326975975316301202111560E0),
	__IEEE854_LONG_DOUBLE_C(1.4645314639038178118428450961503371619177E0),
	__IEEE854_LONG_DOUBLE_C(1.4659193880646627234129855241049975398470E0),
	__IEEE854_LONG_DOUBLE_C(1.4672716522843522691530527207287398276197E0),
	__IEEE854_LONG_DOUBLE_C(1.4685896086876430842559640450619880951144E0),
	__IEEE854_LONG_DOUBLE_C(1.4698745421276027686510391411132998919794E0),
	__IEEE854_LONG_DOUBLE_C(1.4711276743037345918528755717617308518553E0),
	__IEEE854_LONG_DOUBLE_C(1.4723501675822635384916444186631899205983E0),
	__IEEE854_LONG_DOUBLE_C(1.4735431285433308455179928682541563973416E0), /* arctan(10.25) */
	__IEEE854_LONG_DOUBLE_C(1.5707963267948966192313216916397514420986E0), /* pi/2 */
};

/* arctan t = t + t^3 p(t^2) / q(t^2)
 * |t| <= 0.09375
 * peak relative error 5.3e-37 */
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, p0l, __IEEE854_LONG_DOUBLE_C(-4.283708356338736809269381409828726405572E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, p1l, __IEEE854_LONG_DOUBLE_C(-8.636132499244548540964557273544599863825E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, p2l, __IEEE854_LONG_DOUBLE_C(-5.713554848244551350855604111031839613216E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, p3l, __IEEE854_LONG_DOUBLE_C(-1.371405711877433266573835355036413750118E1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, p4l, __IEEE854_LONG_DOUBLE_C(-8.638214309119210906997318946650189640184E-1))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, q0l, __IEEE854_LONG_DOUBLE_C(1.285112506901621042780814422948906537959E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, q1l, __IEEE854_LONG_DOUBLE_C(3.361907253914337187957855834229672347089E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, q2l, __IEEE854_LONG_DOUBLE_C(3.180448303864130128268191635189365331680E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, q3l, __IEEE854_LONG_DOUBLE_C(1.307244136980865800160844625025280344686E2))
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, q4l, __IEEE854_LONG_DOUBLE_C(2.173623741810414221251136181221172551416E1))
/* __LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, q5l, __IEEE854_LONG_DOUBLE_C(1.000000000000000000000000000000000000000E0)) */
#ifndef __libm_hugeval4930l_defined
#define __libm_hugeval4930l_defined
__LIBM_LOCAL_DECLARE(__IEEE854_LONG_DOUBLE_TYPE__, hugeval4930l, __IEEE854_LONG_DOUBLE_C(1.0e4930))
#endif /* !__libm_hugeval4930l_defined */
__LIBM_LOCAL_DECLARE_END

__LOCAL __ATTR_WUNUSED __ATTR_CONST __IEEE854_LONG_DOUBLE_TYPE__
(__LIBCCALL __ieee854_atanl)(__IEEE854_LONG_DOUBLE_TYPE__ __x) {
	__IEEE854_LONG_DOUBLE_TYPE__ __t, __u, __p, __q;
	__uint32_t __msw;
	__int32_t __k;
	int __sign;
	__LIBM_GET_LDOUBLE_EXP(__k, __x);
	if (__k & 0x8000)
		__sign = 1;
	else {
		__sign = 0;
	}
	/* Check for IEEE special cases. */
	__k &= IEEE854_LONG_DOUBLE_MAXEXP;
	if (__k >= IEEE854_LONG_DOUBLE_MAXEXP) {
		/* NaN. */
		if (__ieee854_isnanl(__x))
			return (__x + __x);
		/* Infinity. */
		if (__sign)
			return -__LIBM_LOCAL_VALUE(atantbll)[83];
		else {
			return __LIBM_LOCAL_VALUE(atantbll)[83];
		}
	}
	if (__k <= 0x3fc5) { /* |x| < 2 ** -58 */
		/* Raise inexact. */
		if (__LIBM_LOCAL_VALUE(hugeval4930l) + __x > __IEEE854_LONG_DOUBLE_C(0.0))
			return __x;
	}
	if (__k >= 0x4072) { /* |x| > 2 ** 115 */
		/* Saturate result to {-,+}pi/2 */
		if (__sign)
			return -__LIBM_LOCAL_VALUE(atantbll)[83];
		else {
			return __LIBM_LOCAL_VALUE(atantbll)[83];
		}
	}
	if (__sign)
		__x = -__x;
	__LIBM_GET_LDOUBLE_MSW(__msw, __x);
	if (__k > 0x4002 || (__k == 0x4002 && __msw >= __UINT32_C(0x48000000))) { /* 10.25 */
		__k = 83;
		__t = __IEEE854_LONG_DOUBLE_C(-1.0) / __x;
	} else {
		/* Index of nearest table element.
		   Roundoff to integer is asymmetrical to avoid cancellation when t < 0
		   (cf. fdlibm). */
		__k = __IEEE854_LONG_DOUBLE_C(8.0) * __x + __IEEE854_LONG_DOUBLE_C(0.25);
		__u = __IEEE854_LONG_DOUBLE_C(0.125) * __k;
		/* Small arctan argument.  */
		__t = (__x - __u) / (__IEEE854_LONG_DOUBLE_C(1.0) + __x * __u);
	}
	/* Arctan of small argument t. */
	__u = __t * __t;
	__p = ((((__LIBM_LOCAL_VALUE(p4l) * __u) + __LIBM_LOCAL_VALUE(p3l)) * __u + __LIBM_LOCAL_VALUE(p2l)) * __u + __LIBM_LOCAL_VALUE(p1l)) * __u + __LIBM_LOCAL_VALUE(p0l);
	__q = ((((__u + __LIBM_LOCAL_VALUE(q4l)) * __u + __LIBM_LOCAL_VALUE(q3l)) * __u + __LIBM_LOCAL_VALUE(q2l)) * __u + __LIBM_LOCAL_VALUE(q1l)) * __u + __LIBM_LOCAL_VALUE(q0l);
	__u = __t * __u * __p / __q + __t;
	/* arctan x = arctan u  +  arctan t */
	__u = __LIBM_LOCAL_VALUE(atantbll)[__k] + __u;
	if (__sign)
		return -__u;
	return __u;
}
#endif /* !__ieee854_atanl */
#endif /* __IEEE854_LONG_DOUBLE_TYPE__ */

__DECL_END
#endif /* __CC__ */
#endif /* !__NO_FPU */

#endif /* !_LIBM_ATAN_H */
