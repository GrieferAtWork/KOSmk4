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
#ifndef _BITS_ITIMERSPEC_H
#define _BITS_ITIMERSPEC_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/timespec.h>
#include <bits/types.h>

#define __OFFSET_ITIMERSPEC_INTERVAL   0
#define __OFFSET_ITIMERSPEC_VALUE      __SIZEOF_TIMESPEC
#define __SIZEOF_ITIMERSPEC            (2 * __SIZEOF_TIMESPEC)
#define __OFFSET_ITIMERSPEC64_INTERVAL 0
#define __OFFSET_ITIMERSPEC64_VALUE    __SIZEOF_TIMESPEC64
#define __SIZEOF_ITIMERSPEC64          (2 * __SIZEOF_TIMESPEC64)

#if 0
struct itimerspec /*[PREFIX(it_)]*/ {};
struct itimerspec64 /*[PREFIX(it_)]*/ {};
#endif

#ifdef __CC__
__SYSDECL_BEGIN
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("itimerspec")
#pragma push_macro("it_interval")
#pragma push_macro("it_value")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef itimerspec
#undef it_interval
#undef it_value

struct itimerspec {
	struct timespec it_interval;
	struct timespec it_value;
};

#if __TM_SIZEOF(TIME) <= 4
#define __itimerspec64  __itimerspec_alt
#define __itimerspec32  itimerspec
#else /* __TM_SIZEOF(TIME) <= 4 */
#define __itimerspec64  itimerspec
#define __itimerspec32  __itimerspec_alt
#endif /* __TM_SIZEOF(TIME) > 4 */

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= 4
#define __itimerspec_alt itimerspec64
#else /* __TM_SIZEOF(TIME) <= 4 */
#define itimerspec64     itimerspec
#endif /* __TM_SIZEOF(TIME) > 4 */
#endif /* __USE_TIME64 */

#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#if defined(__USE_TIME64) && __TM_SIZEOF(TIME) <= 4
#define itimerspec64     itimerspec
#else /* __USE_TIME64 && __TM_SIZEOF(TIME) <= 4 */
#define __itimerspec_alt itimerspec
#endif /* !__USE_TIME64 || __TM_SIZEOF(TIME) > 4 */
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
struct __itimerspec_alt
/*Keep an empty line here*/
{
	struct __timespec_alt it_interval;
	struct __timespec_alt it_value;
};
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("it_value")
#pragma pop_macro("it_interval")
#pragma pop_macro("itimerspec")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_ITIMERSPEC_H */
