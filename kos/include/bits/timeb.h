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
#ifndef _BITS_TIMEB_H
#define _BITS_TIMEB_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>

#define __OFFSET_TIMEB_TIME       0
#define __OFFSET_TIMEB_MILLITM    __TM_SIZEOF(TIME)
#define __OFFSET_TIMEB_TIMEZONE   (__TM_SIZEOF(TIME) + 2)
#define __OFFSET_TIMEB_DSTFLAG    (__TM_SIZEOF(TIME) + 4)
#define __SIZEOF_TIMEB            (__TM_SIZEOF(TIME) + 8)
#define __OFFSET_TIMEB64_TIME     0
#define __OFFSET_TIMEB64_MILLITM  __SIZEOF_TIME64_T__
#define __OFFSET_TIMEB64_TIMEZONE (__SIZEOF_TIME64_T__ + 2)
#define __OFFSET_TIMEB64_DSTFLAG  (__SIZEOF_TIME64_T__ + 4)
#define __SIZEOF_TIMEB64          (__SIZEOF_TIME64_T__ + 8)

#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("timeb")
#pragma push_macro("time")
#pragma push_macro("millitm")
#pragma push_macro("timezone")
#pragma push_macro("dstflag")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef timeb
#undef time
#undef millitm
#undef timezone
#undef dstflag

#if 0 /* For assert_types.c */
struct timeb /*[PREFIX()]*/ {};
struct timeb32 /*[PREFIX()]*/ {};
struct timeb64 /*[PREFIX()]*/ {};
#endif

struct timeb {
	__TM_TYPE(time) time;     /* Seconds since epoch, as from `time'. */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};

#if __TM_SIZEOF(TIME) <= 4
#define __timeb64  __timeb_alt
#define __timeb32  timeb
#else /* __TM_SIZEOF(TIME) <= 4 */
#define __timeb64  timeb
#define __timeb32  __timeb_alt
#endif /* __TM_SIZEOF(TIME) > 4 */

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __timeb_alt timeb64
#else /* __TM_SIZEOF(TIME) <= 4 */
#define timeb64     timeb
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_TIME64 */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define timeb64     timeb
#else /* __USE_TIME64 && __TM_SIZEOF(TIME) <= 4 */
#define __timeb_alt timeb
#endif /* !__USE_TIME64 || __TM_SIZEOF(TIME) > 4 */
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __timeb_alt
/*Keep an empty line here*/
{
#if __TM_SIZEOF(TIME) <= 4
	__time64_t      time;     /* Seconds since epoch, as from `time'. */
#else /* __TM_SIZEOF(TIME) <= 4 */
	__time32_t      time;     /* Seconds since epoch, as from `time'. */
#endif /* __TM_SIZEOF(TIME) > 4 */
	__UINT16_TYPE__ millitm;  /* Additional milliseconds. */
	__INT16_TYPE__  timezone; /* Minutes west of GMT. */
	__INT16_TYPE__  dstflag;  /* Nonzero if Daylight Savings Time used. */
	__INT16_TYPE__  __tb_pad; /* ... */
};
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("dstflag")
#pragma pop_macro("timezone")
#pragma pop_macro("millitm")
#pragma pop_macro("time")
#pragma pop_macro("timeb")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_TIMEB_H */
