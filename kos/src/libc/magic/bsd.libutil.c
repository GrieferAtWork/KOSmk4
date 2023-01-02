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
%(c_prefix){
/* (#) Portability: libbsd (/include/bsd/libutil.h) */
}

%[define_replacement(errno_t = __errno_t)]

%[insert:prefix(
#include <asm/crt/humanize_number.h>
)]%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <libutil.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <sys/types.h>
)]%[insert:prefix(
#include <stdint.h>
)]%[insert:prefix(
#include <stdio.h>
)]%{

/* Flags for `humanize_number(3)::flags' */
#if !defined(HN_DECIMAL) && defined(__HN_DECIMAL)
#define HN_DECIMAL      __HN_DECIMAL
#endif /* !HN_DECIMAL && __HN_DECIMAL */
#if !defined(HN_NOSPACE) && defined(__HN_NOSPACE)
#define HN_NOSPACE      __HN_NOSPACE
#endif /* !HN_NOSPACE && __HN_NOSPACE */
#if !defined(HN_B) && defined(__HN_B)
#define HN_B            __HN_B
#endif /* !HN_B && __HN_B */
#if !defined(HN_DIVISOR_1000) && defined(__HN_DIVISOR_1000)
#define HN_DIVISOR_1000 __HN_DIVISOR_1000
#endif /* !HN_DIVISOR_1000 && __HN_DIVISOR_1000 */
#if !defined(HN_IEC_PREFIXES) && defined(__HN_IEC_PREFIXES)
#define HN_IEC_PREFIXES __HN_IEC_PREFIXES
#endif /* !HN_IEC_PREFIXES && __HN_IEC_PREFIXES */

/* Flags for `humanize_number(3)::scale' */
#if !defined(HN_GETSCALE) && defined(__HN_GETSCALE)
#define HN_GETSCALE     __HN_GETSCALE
#endif /* !HN_GETSCALE && __HN_GETSCALE */
#if !defined(HN_AUTOSCALE) && defined(__HN_AUTOSCALE)
#define HN_AUTOSCALE    __HN_AUTOSCALE
#endif /* !HN_AUTOSCALE && __HN_AUTOSCALE */

#ifdef __CC__
__SYSDECL_BEGIN

}

/* Already unconditionally declared in `<libutil.h>' (aka. `<util.h>') */
//%[insert:extern(fparseln)]

%[insert:extern(humanize_number)]

//TODO:int expand_number(const char *_buf, uint64_t *_num);

//TODO:int flopen(const char *_path, int _flags, ...);
//TODO:int flopenat(int dirfd, const char *path, int flags, ...);

//TODO:struct pidfh *pidfile_open(const char *path, mode_t mode, pid_t *pidptr);
//TODO:int pidfile_fileno(const struct pidfh *pfh);
//TODO:int pidfile_write(struct pidfh *pfh);
//TODO:int pidfile_close(struct pidfh *pfh);
//TODO:int pidfile_remove(struct pidfh *pfh);

%{

__SYSDECL_END
#endif /* __CC__ */

}
