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
/*!replace_with_include <bits/os/rusage-convert.h>*/
#ifndef _I386_KOS_BITS_OS_KOS_RUSAGE_CONVERT_H
#define _I386_KOS_BITS_OS_KOS_RUSAGE_CONVERT_H 1

#include <__stdinc.h>
#include <features.h>

#include <hybrid/host.h>

#include "rusage32.h"
#include "rusage64.h"

#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_KOS_ALTERATIONS
#define __PRIVATE_RUAGE_USEC32_T __ULONG32_TYPE__
#define __PRIVATE_RUAGE_USEC64_T __ULONG64_TYPE__
#else /* __USE_KOS_ALTERATIONS */
#define __PRIVATE_RUAGE_USEC32_T __LONG32_TYPE__
#define __PRIVATE_RUAGE_USEC64_T __LONG64_TYPE__
#endif /* !__USE_KOS_ALTERATIONS */


__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rusagex32_to_rusagex32_64)(struct __rusagex32 const *__restrict __self,
                                         struct __rusagex32_64 *__restrict __result) {
	__result->ru_utime.tv_sec  = (__INT64_TYPE__)__self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = __self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = (__INT64_TYPE__)__self->ru_stime.tv_sec;
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
__NOTHROW_NCX(rusagex32_64_to_rusagex32)(struct __rusagex32_64 const *__restrict __self,
                                         struct __rusagex32 *__restrict __result) {
	__result->ru_utime.tv_sec  = (__INT32_TYPE__)__self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = __self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = (__INT32_TYPE__)__self->ru_stime.tv_sec;
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
__NOTHROW_NCX(rusagex32_to_rusagex64)(struct __rusagex32 const *__restrict __self,
                                      struct __rusagex64 *__restrict __result) {
	__result->ru_utime.tv_sec  = (__INT64_TYPE__)__self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = (__PRIVATE_RUAGE_USEC64_T)__self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = (__INT64_TYPE__)__self->ru_stime.tv_sec;
	__result->ru_stime.tv_usec = (__PRIVATE_RUAGE_USEC64_T)__self->ru_stime.tv_usec;
	__result->ru_maxrss        = (__LONG64_TYPE__)__self->ru_maxrss;
	__result->ru_ixrss         = (__LONG64_TYPE__)__self->ru_ixrss;
	__result->ru_idrss         = (__LONG64_TYPE__)__self->ru_idrss;
	__result->ru_isrss         = (__LONG64_TYPE__)__self->ru_isrss;
	__result->ru_minflt        = (__LONG64_TYPE__)__self->ru_minflt;
	__result->ru_majflt        = (__LONG64_TYPE__)__self->ru_majflt;
	__result->ru_nswap         = (__LONG64_TYPE__)__self->ru_nswap;
	__result->ru_inblock       = (__LONG64_TYPE__)__self->ru_inblock;
	__result->ru_oublock       = (__LONG64_TYPE__)__self->ru_oublock;
	__result->ru_msgsnd        = (__LONG64_TYPE__)__self->ru_msgsnd;
	__result->ru_msgrcv        = (__LONG64_TYPE__)__self->ru_msgrcv;
	__result->ru_nsignals      = (__LONG64_TYPE__)__self->ru_nsignals;
	__result->ru_nvcsw         = (__LONG64_TYPE__)__self->ru_nvcsw;
	__result->ru_nivcsw        = (__LONG64_TYPE__)__self->ru_nivcsw;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rusagex32_64_to_rusagex64)(struct __rusagex32_64 const *__restrict __self,
                                         struct __rusagex64 *__restrict __result) {
	__result->ru_utime.tv_sec  = __self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = (__PRIVATE_RUAGE_USEC64_T)__self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = __self->ru_stime.tv_sec;
	__result->ru_stime.tv_usec = (__PRIVATE_RUAGE_USEC64_T)__self->ru_stime.tv_usec;
	__result->ru_maxrss        = (__LONG64_TYPE__)__self->ru_maxrss;
	__result->ru_ixrss         = (__LONG64_TYPE__)__self->ru_ixrss;
	__result->ru_idrss         = (__LONG64_TYPE__)__self->ru_idrss;
	__result->ru_isrss         = (__LONG64_TYPE__)__self->ru_isrss;
	__result->ru_minflt        = (__LONG64_TYPE__)__self->ru_minflt;
	__result->ru_majflt        = (__LONG64_TYPE__)__self->ru_majflt;
	__result->ru_nswap         = (__LONG64_TYPE__)__self->ru_nswap;
	__result->ru_inblock       = (__LONG64_TYPE__)__self->ru_inblock;
	__result->ru_oublock       = (__LONG64_TYPE__)__self->ru_oublock;
	__result->ru_msgsnd        = (__LONG64_TYPE__)__self->ru_msgsnd;
	__result->ru_msgrcv        = (__LONG64_TYPE__)__self->ru_msgrcv;
	__result->ru_nsignals      = (__LONG64_TYPE__)__self->ru_nsignals;
	__result->ru_nvcsw         = (__LONG64_TYPE__)__self->ru_nvcsw;
	__result->ru_nivcsw        = (__LONG64_TYPE__)__self->ru_nivcsw;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rusagex64_to_rusagex32)(struct __rusagex64 const *__restrict __self,
                                      struct __rusagex32 *__restrict __result) {
	__result->ru_utime.tv_sec  = (__INT32_TYPE__)__self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = (__PRIVATE_RUAGE_USEC32_T)__self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = (__INT32_TYPE__)__self->ru_stime.tv_sec;
	__result->ru_stime.tv_usec = (__PRIVATE_RUAGE_USEC32_T)__self->ru_stime.tv_usec;
	__result->ru_maxrss        = (__LONG32_TYPE__)__self->ru_maxrss;
	__result->ru_ixrss         = (__LONG32_TYPE__)__self->ru_ixrss;
	__result->ru_idrss         = (__LONG32_TYPE__)__self->ru_idrss;
	__result->ru_isrss         = (__LONG32_TYPE__)__self->ru_isrss;
	__result->ru_minflt        = (__LONG32_TYPE__)__self->ru_minflt;
	__result->ru_majflt        = (__LONG32_TYPE__)__self->ru_majflt;
	__result->ru_nswap         = (__LONG32_TYPE__)__self->ru_nswap;
	__result->ru_inblock       = (__LONG32_TYPE__)__self->ru_inblock;
	__result->ru_oublock       = (__LONG32_TYPE__)__self->ru_oublock;
	__result->ru_msgsnd        = (__LONG32_TYPE__)__self->ru_msgsnd;
	__result->ru_msgrcv        = (__LONG32_TYPE__)__self->ru_msgrcv;
	__result->ru_nsignals      = (__LONG32_TYPE__)__self->ru_nsignals;
	__result->ru_nvcsw         = (__LONG32_TYPE__)__self->ru_nvcsw;
	__result->ru_nivcsw        = (__LONG32_TYPE__)__self->ru_nivcsw;
}

__LOCAL __ATTR_NONNULL((1, 2)) void
__NOTHROW_NCX(rusagex64_to_rusagex32_64)(struct __rusagex64 const *__restrict __self,
                                         struct __rusagex32_64 *__restrict __result) {
	__result->ru_utime.tv_sec  = __self->ru_utime.tv_sec;
	__result->ru_utime.tv_usec = (__PRIVATE_RUAGE_USEC32_T)__self->ru_utime.tv_usec;
	__result->ru_stime.tv_sec  = __self->ru_stime.tv_sec;
	__result->ru_stime.tv_usec = (__PRIVATE_RUAGE_USEC32_T)__self->ru_stime.tv_usec;
	__result->ru_maxrss        = (__LONG32_TYPE__)__self->ru_maxrss;
	__result->ru_ixrss         = (__LONG32_TYPE__)__self->ru_ixrss;
	__result->ru_idrss         = (__LONG32_TYPE__)__self->ru_idrss;
	__result->ru_isrss         = (__LONG32_TYPE__)__self->ru_isrss;
	__result->ru_minflt        = (__LONG32_TYPE__)__self->ru_minflt;
	__result->ru_majflt        = (__LONG32_TYPE__)__self->ru_majflt;
	__result->ru_nswap         = (__LONG32_TYPE__)__self->ru_nswap;
	__result->ru_inblock       = (__LONG32_TYPE__)__self->ru_inblock;
	__result->ru_oublock       = (__LONG32_TYPE__)__self->ru_oublock;
	__result->ru_msgsnd        = (__LONG32_TYPE__)__self->ru_msgsnd;
	__result->ru_msgrcv        = (__LONG32_TYPE__)__self->ru_msgrcv;
	__result->ru_nsignals      = (__LONG32_TYPE__)__self->ru_nsignals;
	__result->ru_nvcsw         = (__LONG32_TYPE__)__self->ru_nvcsw;
	__result->ru_nivcsw        = (__LONG32_TYPE__)__self->ru_nivcsw;
}

#undef __PRIVATE_RUAGE_USEC32_T
#undef __PRIVATE_RUAGE_USEC64_T

#ifdef __x86_64__
#define rusagex32_to_rusage                 rusagex32_to_rusagex64
#define rusagex32_to_rusage32               rusagex32_to_rusagex64
#define rusagex32_to_rusage64               rusagex32_to_rusagex64
#define rusagex32_64_to_rusage              rusagex32_64_to_rusagex64
#define rusagex32_64_to_rusage32            rusagex32_64_to_rusagex64
#define rusagex32_64_to_rusage64            rusagex32_64_to_rusagex64
#define rusagex64_to_rusage(self, result)   (void)(*(result) = *(self))
#define rusagex64_to_rusage32(self, result) (void)(*(result) = *(self))
#define rusagex64_to_rusage64(self, result) (void)(*(result) = *(self))
#define rusage_to_rusagex32                 rusagex64_to_rusagex32
#define rusage32_to_rusagex32               rusagex64_to_rusagex32
#define rusage64_to_rusagex32               rusagex64_to_rusagex32
#define rusage_to_rusagex32_64              rusagex64_to_rusagex32_64
#define rusage32_to_rusagex32_64            rusagex64_to_rusagex32_64
#define rusage64_to_rusagex32_64            rusagex64_to_rusagex32_64
#define rusage_to_rusagex64(self, result)   (void)(*(result) = *(self))
#define rusage32_to_rusagex64(self, result) (void)(*(result) = *(self))
#define rusage64_to_rusagex64(self, result) (void)(*(result) = *(self))
#define rusage_to_rusage32(self, result)    (void)(*(result) = *(self))
#define rusage_to_rusage64(self, result)    (void)(*(result) = *(self))
#define rusage32_to_rusage(self, result)    (void)(*(result) = *(self))
#define rusage64_to_rusage(self, result)    (void)(*(result) = *(self))
#define rusage32_to_rusage64(self, result)  (void)(*(result) = *(self))
#define rusage64_to_rusage32(self, result)  (void)(*(result) = *(self))
#else /* __x86_64__ */
#define rusagex32_to_rusage32(self, result)    (void)(*(result) = *(self))
#define rusagex32_to_rusage64                  rusagex32_to_rusagex32_64
#define rusagex32_64_to_rusage32               rusagex32_64_to_rusagex32
#define rusagex32_64_to_rusage64(self, result) (void)(*(result) = *(self))
#define rusagex64_to_rusage32                  rusagex64_to_rusagex32
#define rusagex64_to_rusage64                  rusagex64_to_rusagex32_64
#define rusage32_to_rusagex32(self, result)    (void)(*(result) = *(self))
#define rusage64_to_rusagex32                  rusagex32_64_to_rusagex32
#define rusage32_to_rusagex32_64               rusagex32_to_rusagex32_64
#define rusage64_to_rusagex32_64(self, result) (void)(*(result) = *(self))
#define rusage32_to_rusagex64                  rusagex32_to_rusagex64
#define rusage64_to_rusagex64                  rusagex32_64_to_rusagex64
#define rusage32_to_rusage64                   rusagex32_to_rusagex32_64
#define rusage64_to_rusage32                   rusagex32_64_to_rusagex32
#ifdef __USE_TIME_BITS64
#define rusagex32_to_rusage              rusagex32_to_rusage64
#define rusagex32_64_to_rusage           rusagex32_64_to_rusage64
#define rusagex64_to_rusage              rusagex64_to_rusage64
#define rusage_to_rusagex32              rusage64_to_rusagex32
#define rusage_to_rusagex32_64           rusage64_to_rusagex32_64
#define rusage_to_rusagex64              rusage64_to_rusagex64
#define rusage_to_rusage32               rusage64_to_rusage32
#define rusage_to_rusage64(self, result) (void)(*(result) = *(self))
#define rusage32_to_rusage               rusage32_to_rusage64
#define rusage64_to_rusage(self, result) (void)(*(result) = *(self))
#else /* __USE_TIME_BITS64 */
#define rusagex32_to_rusage              rusagex32_to_rusage32
#define rusagex32_64_to_rusage           rusagex32_64_to_rusage32
#define rusagex64_to_rusage              rusagex64_to_rusage32
#define rusage_to_rusagex32              rusage32_to_rusagex32
#define rusage_to_rusagex32_64           rusage32_to_rusagex32_64
#define rusage_to_rusagex64              rusage32_to_rusagex64
#define rusage_to_rusage32(self, result) (void)(*(result) = *(self))
#define rusage_to_rusage64               rusage32_to_rusage64
#define rusage32_to_rusage(self, result) (void)(*(result) = *(self))
#define rusage64_to_rusage               rusage64_to_rusage32
#endif /* !__USE_TIME_BITS64 */
#endif /* !__x86_64__ */

__DECL_END
#endif /* __CC__ */

#endif /* !_I386_KOS_BITS_OS_KOS_RUSAGE_CONVERT_H */
