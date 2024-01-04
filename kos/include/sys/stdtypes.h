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
/* (#) Portability: OpenSolaris (/usr/src/lib/libbc/inc/include/sys/stdtypes.h) */
#ifndef _SYS_STDTYPES_H
#define _SYS_STDTYPES_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/typecore.h>

#include <bits/os/termios.h> /* cc_t, speed_t, tcflag_t */
#include <bits/sigset.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t;
#endif /* !__mode_t_defined */

#ifndef __nlink_t_defined
#define __nlink_t_defined
typedef __nlink_t nlink_t;
#endif /* !__nlink_t_defined */

#ifndef __clock_t_defined
#define __clock_t_defined
typedef __clock_t clock_t;
#endif /* !__clock_t_defined */

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t; /* UNIX time in seconds since 01.01.1970 */
#endif /* !__time_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif /* !__ptrdiff_t_defined */

#ifndef __wchar_t_defined
#define __wchar_t_defined
typedef __WCHAR_TYPE__ wchar_t;
#endif /* !__wchar_t_defined */

typedef unsigned char uchar_t;
typedef unsigned short ushort_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_STDTYPES_H */
