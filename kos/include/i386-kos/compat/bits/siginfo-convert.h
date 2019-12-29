/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _I386_KOS_COMPAT_BITS_SIGINFO_CONVERT_H
#define _I386_KOS_COMPAT_BITS_SIGINFO_CONVERT_H 1

#include <hybrid/host.h> /* __x86_64__ */
#ifdef __x86_64__
#include <bits/siginfo-convert.h>
#define compat_siginfo_to_siginfo siginfo32_to_siginfo
#define siginfo_to_compat_siginfo siginfo_to_siginfo32
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_COMPAT_BITS_SIGINFO_CONVERT_H */
