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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_COMPAT_BITS_RUSAGE_CONVERT_H
#define _I386_KOS_COMPAT_BITS_RUSAGE_CONVERT_H 1

#include <hybrid/host.h> /* __x86_64__ */
#ifdef __x86_64__
#include <bits/rusage-convert.h>
#define compat_rusage32_to_rusage   rusagex32_to_rusage32
#define compat_rusage64_to_rusage   rusagex32_64_to_rusage32
#define compat_rusage32_to_rusage32 rusagex32_to_rusage32
#define compat_rusage64_to_rusage32 rusagex32_64_to_rusage32
#define compat_rusage32_to_rusage64 rusagex32_to_rusage64
#define compat_rusage64_to_rusage64 rusagex32_64_to_rusage64
#define rusage_to_compat_rusage32   rusage32_to_rusagex32
#define rusage_to_compat_rusage64   rusage32_to_rusagex32_64
#define rusage32_to_compat_rusage32 rusage32_to_rusagex32
#define rusage32_to_compat_rusage64 rusage32_to_rusagex32_64
#define rusage64_to_compat_rusage32 rusage64_to_rusagex32
#define rusage64_to_compat_rusage64 rusage64_to_rusagex32_64

#endif /* !__x86_64__ */

#endif /* !_I386_KOS_COMPAT_BITS_RUSAGE_CONVERT_H */
