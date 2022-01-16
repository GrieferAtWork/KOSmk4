/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_BITS_OS_KOS_SIGACTION_H
#define _I386_KOS_BITS_OS_KOS_SIGACTION_H 1

/* File:
 *    <i386-kos/bits/os/kos/sigaction.h>
 *
 * Definitions:
 *    - typedef ... __sighandler_t;
 *    - struct sigaction { ... };
 */

#include <__stdinc.h>

#include <hybrid/host.h> /* __x86_64__ */

#ifdef __x86_64__
#include "sigaction64.h"
#else /* __x86_64__ */
#include "sigaction32.h"
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_BITS_OS_KOS_SIGACTION_H */
