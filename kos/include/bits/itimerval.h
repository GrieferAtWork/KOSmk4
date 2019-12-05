/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _BITS_ITIMERVAL_H
#define _BITS_ITIMERVAL_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/timeval.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if __TM_SIZEOF(TIME) <= __SIZEOF_TIME32_T__
#define __itimerval64   __itimerval_alt
#define __itimerval32   itimerval
#else /* __TM_SIZEOF(TIME) <= __SIZEOF_TIME32_T__ */
#define __itimerval64   itimerval
#define __itimerval32   __itimerval_alt
#endif /* __TM_SIZEOF(TIME) > __SIZEOF_TIME32_T__ */

#ifdef __USE_TIME64
#if __TM_SIZEOF(TIME) <= __SIZEOF_TIME32_T__
#define __itimerval_alt itimerval64
#else /* __TM_SIZEOF(TIME) <= __SIZEOF_TIME32_T__ */
#define itimerval64     itimerval
#endif /* __TM_SIZEOF(TIME) > __SIZEOF_TIME32_T__ */
#endif /* __USE_TIME64 */

struct itimerval {
	struct timeval       it_interval; /* Value to put into `it_value' when the timer expires. */
	struct timeval       it_value;    /* Time to the next timer expiration. */
};

struct __itimerval_alt {
	struct __timeval_alt it_interval; /* Value to put into `it_value' when the timer expires. */
	struct __timeval_alt it_value;    /* Time to the next timer expiration. */
};

__SYSDECL_END
#endif /* __CC__ */


#endif /* !_BITS_ITIMERVAL_H */
