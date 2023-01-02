/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin    (/newlib/libc/include/sys/_types.h) */
/* (#) Portability: EMX kLIBC (/libc/include/sys/_types.h) */
/* (#) Portability: FreeBSD   (/sys/sys/_types.h) */
/* (#) Portability: Newlib    (/newlib/libc/include/sys/_types.h) */
/* (#) Portability: OpenBSD   (/sys/sys/_types.h) */
#ifndef _SYS__TYPES_H
#define _SYS__TYPES_H 1

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
#define __wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__wint_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ wint_t;
#endif /* !__size_t_defined */

#ifndef __machine_blkcnt_t_defined
#define __machine_blkcnt_t_defined
typedef __blkcnt_t __blkcnt_t;
#endif /* !__machine_blkcnt_t_defined */

#ifndef __machine_blksize_t_defined
#define __machine_blksize_t_defined
#endif /* !__machine_blksize_t_defined */

#ifndef __machine_fsblkcnt_t_defined
#define __machine_fsblkcnt_t_defined
typedef __fsblkcnt_t __fsblkcnt_t;
#endif /* !__machine_fsblkcnt_t_defined */

#ifndef __machine_fsfilcnt_t_defined
#define __machine_fsfilcnt_t_defined
typedef __fsfilcnt_t __fsfilcnt_t;
#endif /* !__machine_fsfilcnt_t_defined */

#ifndef __machine_off_t_defined
#define __machine_off_t_defined
typedef __off_t _off_t;
#endif /* !__machine_off_t_defined */

#ifndef __machine_dev_t_defined
#define __machine_dev_t_defined
#endif /* !__machine_dev_t_defined */

#ifndef __machine_uid_t_defined
#define __machine_uid_t_defined
#endif /* !__machine_uid_t_defined */

#ifndef __machine_gid_t_defined
#define __machine_gid_t_defined
#endif /* !__machine_gid_t_defined */

#ifndef __machine_id_t_defined
#define __machine_id_t_defined
#endif /* !__machine_id_t_defined */

#ifndef __machine_ino_t_defined
#define __machine_ino_t_defined
#endif /* !__machine_ino_t_defined */

#ifndef __machine_mode_t_defined
#define __machine_mode_t_defined
#endif /* !__machine_mode_t_defined */

#ifndef __machine_off64_t_defined
#define __machine_off64_t_defined
typedef __off64_t _off64_t;
#endif /* !__machine_off64_t_defined */

//#ifndef __off_t
//#define  __off_t  __off_t
//typedef _off64_t __off_t;
//#endif /* !__off_t */

#ifndef __machine_key_t_defined
#define __machine_key_t_defined
#endif /* !__machine_key_t_defined */

#ifndef __machine_fpos_t_defined
#define __machine_fpos_t_defined
typedef __pos32_t _fpos_t;
#endif /* !__machine_fpos_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __machine_fpos64_t_defined
#define __machine_fpos64_t_defined
typedef __pos64_t _fpos64_t;
#endif /* !__machine_fpos64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __machine_size_t_defined
#define __machine_size_t_defined
#endif /* !__machine_size_t_defined */

#ifndef __machine_ssize_t_defined
#define __machine_ssize_t_defined
typedef __ssize_t _ssize_t;
#endif /* !__machine_ssize_t_defined */

#ifndef __machine_mbstate_t_defined
#define __machine_mbstate_t_defined
#include <bits/crt/mbstate.h>
typedef struct __mbstate _mbstate_t;
#endif /* !__machine_mbstate_t_defined */

#ifndef __machine_iconv_t_defined
#define __machine_iconv_t_defined
typedef void *_iconv_t;
#endif /* !__machine_iconv_t_defined */

#ifndef __machine_clock_t_defined
#define __machine_clock_t_defined
#define _CLOCK_T_ __clock_t
#endif /* !__machine_clock_t_defined */

#define _TIME_T_ __time_t
/*typedef __time_t __time_t;*/

#ifndef __machine_clockid_t_defined
#define __machine_clockid_t_defined
#define _CLOCKID_T_ __clockid_t
#endif /* !__machine_clockid_t_defined */

#define _TIMER_T_ __timer_t
#ifndef __machine_sa_family_t_defined
#define __machine_sa_family_t_defined
#endif /* !__machine_sa_family_t_defined */

#ifndef __machine_socklen_t_defined
#define __machine_socklen_t_defined
#endif /* !__machine_socklen_t_defined */

typedef int __nl_item;
#ifndef ____va_list_defined
#define ____va_list_defined
typedef __builtin_va_list __va_list;
#endif /* !____va_list_defined */

/* Some more types from BSD */
typedef __uint32_t __fflags_t;
#ifndef __machine_ino_t_defined
#define __machine_ino_t_defined
typedef __ino_t __ino_t;
#endif /* !__machine_ino_t_defined */
typedef __pid_t __lwpid_t;
typedef int __accmode_t;
/*typedef __int64_t __rlim_t;*/
typedef __fd_t __mqd_t; /* mqd_t */
typedef int __cpuwhich_t;
typedef int __cpulevel_t;
typedef int __cpusetid_t;
typedef int __ct_rune_t;
typedef __ct_rune_t __rune_t;
typedef __WINT_TYPE__ __wint_t;
/*typedef __CHAR16_TYPE__ __char16_t;*/
/*typedef __CHAR32_TYPE__ __char32_t;*/
typedef __MAX_ALIGN_TYPE__ __max_align_t;
typedef __uint32_t __fixpt_t;
#ifndef ____mbstate_t_defined
#define ____mbstate_t_defined
typedef struct __mbstate __mbstate_t;
#endif /* !____mbstate_t_defined */
typedef __uintmax_t __rman_res_t;
#ifndef ____gnuc_va_list_defined
#define ____gnuc_va_list_defined
typedef __builtin_va_list __gnuc_va_list;
#endif /* !____gnuc_va_list_defined */

__DECL_END
#endif /* __CC__ */

#if __SIZEOF_INO_T__ > 4
#define __INO64 /* 64-bit ino_t */
#endif /* __SIZEOF_INO_T__ > 4 */

#endif /* !_SYS__TYPES_H */
