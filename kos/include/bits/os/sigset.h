/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_OS_SIGSET_H
#define _BITS_OS_SIGSET_H 1

/* File:
 *    <bits/os/sigset.h>
 *
 * Definitions:
 *    - struct __sigset_struct { ... };
 *    - ulongptr_t __sigset_mask(signo_t signo);
 *    - ulongptr_t __sigset_word(signo_t signo);
 *    - #define __SIGSET_INIT(ulongptr_t f) { ... }
 */

#include <__stdinc.h>

/**/
#include <bits/os/generic/sigset.h>

#endif /* !_BITS_OS_SIGSET_H */
