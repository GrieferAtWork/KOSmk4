/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_KOS_RUSAGE_CONVERT_H
#define _BITS_OS_KOS_RUSAGE_CONVERT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#include <bits/os/kos/rusage.h>
#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#if __SIZEOF_TIME64_T__ == __SIZEOF_TIME32_T__
#define rusage32_to_rusage64(self, result) (void)(*(result) = *(self))
#define rusage64_to_rusage32(self, result) (void)(*(result) = *(self))
#else /* __SIZEOF_TIME64_T__ == __SIZEOF_TIME32_T__ */
__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rusage32_to_rusage64)(struct __rusage32 const *__restrict __self,
                                    struct __rusage64 *__restrict __result) {
	__result->ru_utime.tv_sec  = (__time64_t)__self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = __self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = (__time64_t)__self->ru_stime.tv_sec;
	__result->ru_stime.tv_usec = __self->ru_stime.tv_usec;
	__result->ru_maxrss        = __self->ru_maxrss;
	__result->ru_ixrss         = __self->ru_ixrss;
	__result->ru_idrss         = __self->ru_idrss;
	__result->ru_isrss         = __self->ru_isrss;
	__result->ru_minflt        = __self->ru_minflt;
	__result->ru_majflt        = __self->ru_majflt;
	__result->ru_nswap         = __self->ru_nswap;
	__result->ru_inblock       = __self->ru_inblock;
	__result->ru_oublock       = __self->ru_oublock;
	__result->ru_msgsnd        = __self->ru_msgsnd;
	__result->ru_msgrcv        = __self->ru_msgrcv;
	__result->ru_nsignals      = __self->ru_nsignals;
	__result->ru_nvcsw         = __self->ru_nvcsw;
	__result->ru_nivcsw        = __self->ru_nivcsw;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rusage64_to_rusage32)(struct __rusage64 const *__restrict __self,
                                    struct __rusage32 *__restrict __result) {
	__result->ru_utime.tv_sec  = (__time32_t)__self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = __self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = (__time32_t)__self->ru_stime.tv_sec;
	__result->ru_stime.tv_usec = __self->ru_stime.tv_usec;
	__result->ru_maxrss        = __self->ru_maxrss;
	__result->ru_ixrss         = __self->ru_ixrss;
	__result->ru_idrss         = __self->ru_idrss;
	__result->ru_isrss         = __self->ru_isrss;
	__result->ru_minflt        = __self->ru_minflt;
	__result->ru_majflt        = __self->ru_majflt;
	__result->ru_nswap         = __self->ru_nswap;
	__result->ru_inblock       = __self->ru_inblock;
	__result->ru_oublock       = __self->ru_oublock;
	__result->ru_msgsnd        = __self->ru_msgsnd;
	__result->ru_msgrcv        = __self->ru_msgrcv;
	__result->ru_nsignals      = __self->ru_nsignals;
	__result->ru_nvcsw         = __self->ru_nvcsw;
	__result->ru_nivcsw        = __self->ru_nivcsw;
}
#endif /* __SIZEOF_TIME64_T__ != __SIZEOF_TIME32_T__ */

#ifdef __USE_TIME_BITS64
#define rusage_to_rusage32               rusage64_to_rusage32
#define rusage_to_rusage64(self, result) (void)(*(result) = *(self))
#define rusage32_to_rusage               rusage32_to_rusage64
#define rusage64_to_rusage(self, result) (void)(*(result) = *(self))
#else /* __USE_TIME_BITS64 */
#define rusage_to_rusage32(self, result) (void)(*(result) = *(self))
#define rusage_to_rusage64               rusage32_to_rusage64
#define rusage32_to_rusage(self, result) (void)(*(result) = *(self))
#define rusage64_to_rusage               rusage64_to_rusage32
#endif /* !__USE_TIME_BITS64 */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_RUSAGE_CONVERT_H */
