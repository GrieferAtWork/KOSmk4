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
#ifndef _COMPAT_BITS_OS_GENERIC_RUSAGE_CONVERT_H
#define _COMPAT_BITS_OS_GENERIC_RUSAGE_CONVERT_H 1

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <features.h>

#include <bits/os/rusage-convert.h> /* rusage32_to_rusage64, rusage64_to_rusage32 */
#include <bits/os/rusage.h>

#define compat_rusage32_to_rusage32(self, result) (void)(*(result) = *(self))
#define compat_rusage32_to_rusage64               rusage32_to_rusage64
#define compat_rusage64_to_rusage32               rusage64_to_rusage32
#define compat_rusage64_to_rusage64(self, result) (void)(*(result) = *(self))
#define rusage32_to_compat_rusage32(self, result) (void)(*(result) = *(self))
#define rusage32_to_compat_rusage64               rusage32_to_rusage64
#define rusage64_to_compat_rusage32               rusage64_to_rusage32
#define rusage64_to_compat_rusage64(self, result) (void)(*(result) = *(self))
#ifdef __USE_TIME_BITS64
#define compat_rusage32_to_rusage               rusage32_to_rusage64
#define compat_rusage64_to_rusage(self, result) (void)(*(result) = *(self))
#define rusage_to_compat_rusage32               rusage64_to_rusage32
#define rusage_to_compat_rusage64(self, result) (void)(*(result) = *(self))
#else /* __USE_TIME_BITS64 */
#define compat_rusage32_to_rusage(self, result) (void)(*(result) = *(self))
#define compat_rusage64_to_rusage               rusage64_to_rusage32
#define rusage_to_compat_rusage32(self, result) (void)(*(result) = *(self))
#define rusage_to_compat_rusage64               rusage32_to_rusage64
#endif /* !__USE_TIME_BITS64 */
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_BITS_OS_GENERIC_RUSAGE_CONVERT_H */
