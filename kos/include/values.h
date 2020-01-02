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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _VALUES_H
#define _VALUES_H 1

#include "__stdinc.h"
#include "features.h"

#include <hybrid/floatcore.h>
#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

/* GLibc includes these two headers unconditionally,
 * but as an extension KOS doesn't. */
#ifndef __USE_KOS
#include "limits.h"
#include "float.h"
#endif /* !__USE_KOS */

#define _TYPEBITS(type) (sizeof(type)*__CHAR_BIT__)
#define CHARBITS    __CHAR_BIT__
#define SHORTBITS  (__CHAR_BIT__*__SIZEOF_SHORT__)
#define INTBITS    (__CHAR_BIT__*__SIZEOF_INT__)
#define LONGBITS   (__CHAR_BIT__*__SIZEOF_LONG__)
#define PTRBITS    (__CHAR_BIT__*__SIZEOF_POINTER__)
#define DOUBLEBITS (__CHAR_BIT__*__SIZEOF_DOUBLE__)
#define FLOATBITS  (__CHAR_BIT__*__SIZEOF_FLOAT__)

#define MINSHORT    __SHRT_MIN__
#define MAXSHORT    __SHRT_MAX__
#define MININT      __INT_MIN__
#define MAXINT      __INT_MAX__
#define MINLONG     __LONG_MIN__
#define MAXLONG     __LONG_MAX__
#define HIBITS      __SHRT_MIN__
#define HIBITL      __LONG_MIN__
#define MAXDOUBLE   __DBL_MAX__
#define MAXFLOAT    __FLT_MAX__
#define MINDOUBLE   __DBL_MIN__
#define MINFLOAT    __FLT_MIN__
#define DMINEXP     __DBL_MIN_EXP__
#define FMINEXP     __FLT_MIN_EXP__
#define DMAXEXP     __DBL_MAX_EXP__
#define FMAXEXP     __FLT_MAX_EXP__

#ifdef __USE_MISC
#define BITSPERBYTE __CHAR_BIT__
#endif /* __USE_MISC */

#endif /* !_VALUES_H */
