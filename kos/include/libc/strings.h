/* HASH CRC-32:0x7a7198fe */
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
#ifndef _LIBC_STRINGS_H
#define _LIBC_STRINGS_H 1

#include <__stdinc.h>

#ifdef __CC__
#include <__crt.h>
#include "core/strings.h"

/* >> explicit_bzero(3)
 * Same  as  `bzero(dst, n_bytes)', however  compilers will  not optimize
 * away uses of this function when they (think) that clearing the  memory
 * wouldn't  have  any  visible side-effects  (though  those side-effects
 * may be a security-conscious application trying to wipe sensitive data) */
#define __libc_explicit_bzero __libc_core_explicit_bzero

#endif /* __CC__ */

#endif /* !_LIBC_STRINGS_H */
