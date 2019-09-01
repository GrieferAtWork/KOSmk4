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
#ifndef _I386_KOS_BITS_TIMESPEC64_H
#define _I386_KOS_BITS_TIMESPEC64_H 1

#include <__stdinc.h>
#include <hybrid/typecore.h>
#include <bits/timespec-cxx-support.h>

#ifdef __x86_64__
#include <features.h>
#define __OFFSET_TIMESPEC_SEC    __OFFSET_TIMESPECX64_SEC
#define __OFFSET_TIMESPEC_NSEC   __OFFSET_TIMESPECX64_NSEC
#define __SIZEOF_TIMESPEC        __SIZEOF_TIMESPECX64
#define timespecx64              timespec
#define __timespec32             timespec
#define __timespec64             timespec
#define __timespec_alt           timespec
#ifdef __USE_TIME64
#define timespec64               timespec
#define __OFFSET_TIMESPEC64_SEC  __OFFSET_TIMESPECX64_SEC
#define __OFFSET_TIMESPEC64_NSEC __OFFSET_TIMESPECX64_NSEC
#define __SIZEOF_TIMESPEC64      __SIZEOF_TIMESPECX64
#endif /* __USE_TIME64 */
#endif /* __x86_64__ */


#define __OFFSET_TIMESPECX64_SEC   0
#define __OFFSET_TIMESPECX64_NSEC  8
#define __SIZEOF_TIMESPECX64       16

#ifdef __CC__
__DECL_BEGIN
__TIMESPEC_CXX_DECL_BEGIN

/* timespec for x86_64 */
struct timespecx64 /*[PREFIX(tv_)]*/ {
	__INT64_TYPE__    tv_sec;   /* Seconds */
	__UINT64_TYPE__   tv_nsec;  /* Nano seconds (<= 1000000000 == 1_000_000_000) */
	__TIMESPEC_CXX_SUPPORT(struct timespecx64, __INT64_TYPE__, __UINT64_TYPE__)
};
__TIMESPEC_CXX_SUPPORT2(struct timespecx64, __INT64_TYPE__, __UINT64_TYPE__)

__TIMESPEC_CXX_DECL_END
__DECL_END
#endif /* __CC__ */


#endif /* !_I386_KOS_BITS_TIMESPEC64_H */
