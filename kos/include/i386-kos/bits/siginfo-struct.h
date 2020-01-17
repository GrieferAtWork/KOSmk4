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
#ifndef _I386_KOS_BITS_SIGINFO_STRUCT_H
#define _I386_KOS_BITS_SIGINFO_STRUCT_H 1

#include <__stdinc.h>
#include <__crt.h> /* __CRT_CYG_PRIMARY */

#ifdef __CRT_CYG_PRIMARY
#include "siginfo-struct-cygwin.h"
#else /* __CRT_CYG_PRIMARY */
#include <hybrid/host.h> /* __x86_64__ */

#ifdef __x86_64__
#include "siginfo-struct64.h"
#else /* __x86_64__ */
#include "siginfo-struct32.h"
#endif /* !__x86_64__ */

#endif /* !__CRT_CYG_PRIMARY */

#endif /* !_I386_KOS_BITS_SIGINFO_STRUCT_H */
