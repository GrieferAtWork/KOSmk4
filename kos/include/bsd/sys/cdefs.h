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
/* (#) Portability: libbsd (/include/bsd/sys/cdefs.h) */
#ifndef _BSD_SYS_CDEFS_H
#define _BSD_SYS_CDEFS_H 1

#include <sys/cdefs.h>

#include <hybrid/typecore.h>
#ifndef __dead2
#define __dead2 __ATTR_NORETURN
#endif /* !__dead2 */
#ifndef __pure2
#define __pure2 __ATTR_CONST
#endif /* !__pure2 */
#ifndef __packed
#define __packed __ATTR_PACKED
#endif /* !__packed */
#ifndef __aligned
#define __aligned(x) __ATTR_ALIGNED(x)
#endif /* !__aligned */
#ifndef __unused
#define __unused __ATTR_UNUSED
#endif /* !__unused */
#ifndef __printflike
#define __printflike __ATTR_FORMAT_PRINTF
#endif /* !__printflike */
#ifndef __bounded__
#define __bounded__(x, y, z)
#endif /* !__bounded__ */
#ifndef __arraycount
#define __arraycount __COMPILER_LENOF
#endif /* !__arraycount */
#ifndef __offsetof
#define __offsetof __builtin_offsetof
#endif /* !__offsetof */
#ifndef __rangeof
#define __rangeof(type, start, end)  \
	(__builtin_offsetof(type, end) - \
	 __builtin_offsetof(type, start))
#endif /* !__rangeof */
#ifndef __containerof
#define __containerof __COMPILER_CONTAINER_OF
#endif /* !__containerof */
#ifndef __RCSID
#define __RCSID(x) /* nothing */
#endif /* !__RCSID */
#ifndef __FBSDID
#define __FBSDID(x) /* nothing */
#endif /* !__FBSDID */
#ifndef __RCSID_SOURCE
#define __RCSID_SOURCE(x) /* nothing */
#endif /* !__RCSID_SOURCE */
#ifndef __SCCSID
#define __SCCSID(x) /* nothing */
#endif /* !__SCCSID */
#ifndef __COPYRIGHT
#define __COPYRIGHT(x) /* nothing */
#endif /* !__COPYRIGHT */
#ifndef __DECONST
#define __DECONST(type, var) ((type)(__UINTPTR_TYPE__)(void const *)(var))
#endif /* !__DECONST */
#ifndef __DEVOLATILE
#define __DEVOLATILE(type, var) ((type)(__UINTPTR_TYPE__)(void volatile *)(var))
#endif /* !__DEVOLATILE */
#ifndef __DEQUALIFY
#define __DEQUALIFY(type, var) ((type)(__UINTPTR_TYPE__)(void const volatile *)(var))
#endif /* !__DEQUALIFY */

#endif /* !_BSD_SYS_CDEFS_H */
