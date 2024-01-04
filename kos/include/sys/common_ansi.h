/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: NetBSD (/sys/sys/common_ansi.h) */
#ifndef _SYS_COMMON_ANSI_H
#define _SYS_COMMON_ANSI_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <sys/cdefs.h>
/*#include <machine/int_types.h>*/

#define _BSD_CLOCK_T_     __clock_t
#define _BSD_PTRDIFF_T_   __PTRDIFF_TYPE__
#define _BSD_SSIZE_T_     __SSIZE_TYPE__
#define _BSD_SIZE_T_      __SIZE_TYPE__
#define _BSD_TIME_T_      __time_t
#define _BSD_CLOCKID_T_   __clockid_t
#define _BSD_TIMER_T_     __timer_t
#define _BSD_SUSECONDS_T_ __suseconds_t
#define _BSD_USECONDS_T_  __useconds_t
#define _BSD_WCHAR_T_     __WCHAR_TYPE__
#define _BSD_WINT_T_      __WINT_TYPE__

#endif /* !_SYS_COMMON_ANSI_H */
