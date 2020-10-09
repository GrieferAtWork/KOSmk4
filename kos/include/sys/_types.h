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
#ifndef _SYS__TYPES_H
#define _SYS__TYPES_H 1

/* API_LEVEL: newlib */

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>
#include <machine/_types.h>
#include <sys/config.h>

#include <newlib.h>
//TODO:#include <sys/lock.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __wint_t_defined
#define __wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__wint_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ wint_t;
#endif /* !__size_t_defined */

#ifndef __machine_blkcnt_t_defined
#define __machine_blkcnt_t_defined 1
typedef __FS_TYPE(blkcnt) __blkcnt_t;
#endif /* !__machine_blkcnt_t_defined */

#ifndef __machine_blksize_t_defined
#define __machine_blksize_t_defined 1
#endif /* !__machine_blksize_t_defined */

#ifndef __machine_fsblkcnt_t_defined
#define __machine_fsblkcnt_t_defined 1
typedef __FS_TYPE(fsblkcnt) __fsblkcnt_t;
#endif /* !__machine_fsblkcnt_t_defined */

#ifndef __machine_fsfilcnt_t_defined
#define __machine_fsfilcnt_t_defined 1
typedef __FS_TYPE(fsfilcnt) __fsfilcnt_t;
#endif /* !__machine_fsfilcnt_t_defined */

#ifndef __machine_off_t_defined
#define __machine_off_t_defined 1
typedef __FS_TYPE(off) _off_t;
#endif /* !__machine_off_t_defined */

#ifndef __machine_dev_t_defined
#define __machine_dev_t_defined 1
#endif /* !__machine_dev_t_defined */

#ifndef __machine_uid_t_defined
#define __machine_uid_t_defined 1
#endif /* !__machine_uid_t_defined */

#ifndef __machine_gid_t_defined
#define __machine_gid_t_defined 1
#endif /* !__machine_gid_t_defined */

#ifndef __machine_id_t_defined
#define __machine_id_t_defined 1
#endif /* !__machine_id_t_defined */

#ifndef __machine_ino_t_defined
#define __machine_ino_t_defined 1
#endif /* !__machine_ino_t_defined */

#ifndef __machine_mode_t_defined
#define __machine_mode_t_defined 1
#endif /* !__machine_mode_t_defined */

#ifndef __machine_off64_t_defined
#define __machine_off64_t_defined 1
typedef __off64_t _off64_t;
#endif /* !__machine_off64_t_defined */

#ifndef __off_t
#define __off_t __off_t
typedef _off64_t __off_t;
#endif /* !__off_t */

#ifndef __machine_key_t_defined
#define __machine_key_t_defined 1
#endif /* !__machine_key_t_defined */

#ifndef __machine_fpos_t_defined
#define __machine_fpos_t_defined 1
typedef __pos32_t _fpos_t;
#endif /* !__machine_fpos_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __machine_fpos64_t_defined
#define __machine_fpos64_t_defined 1
typedef __pos64_t _fpos64_t;
#endif /* !__machine_fpos64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __machine_size_t_defined
#define __machine_size_t_defined 1
#endif /* !__machine_size_t_defined */

#ifndef __machine_ssize_t_defined
#define __machine_ssize_t_defined 1
typedef __ssize_t _ssize_t;
#endif /* !__machine_ssize_t_defined */

#ifndef __machine_mbstate_t_defined
#define __machine_mbstate_t_defined 1
#include <bits/crt/mbstate.h>
typedef __mbstate_t _mbstate_t;
#endif /* !__machine_mbstate_t_defined */

#ifndef __machine_iconv_t_defined
#define __machine_iconv_t_defined 1
typedef void *_iconv_t;
#endif /* !__machine_iconv_t_defined */

#ifndef __machine_clock_t_defined
#define __machine_clock_t_defined 1
#define _CLOCK_T_ __clock_t
#endif /* !__machine_clock_t_defined */

#define	_TIME_T_ __TM_TYPE(time)
typedef __TM_TYPE(time) __time_t;

#ifndef __machine_clockid_t_defined
#define __machine_clockid_t_defined 1
#define _CLOCKID_T_ __clockid_t
#endif /* !__machine_clockid_t_defined */

#define _TIMER_T_ __timer_t
#ifndef __machine_sa_family_t_defined
#define __machine_sa_family_t_defined 1
#endif /* !__machine_sa_family_t_defined */

#ifndef __machine_socklen_t_defined
#define __machine_socklen_t_defined 1
#endif /* !__machine_socklen_t_defined */

typedef int __nl_item;
typedef __builtin_va_list __va_list;

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS__TYPES_H */
